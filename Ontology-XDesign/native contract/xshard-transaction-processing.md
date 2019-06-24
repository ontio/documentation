# 跨分片事务处理

## 主要技术点

1. 分片消息分为notify和request/response两种。交易执行中发出notify消息后可以继续执行至结束或者遇到往其他分片request为止；交易执行中遇到发送request消息时需要中断当前交易执行，直到其他分片发送回response消息后在原交易中断处恢复继续执行，这和部分编程语言里的async/await异步机制类似。由于直接支持中断恢复机制过于复杂，所以目前采用的方式是持久化交易执行的输入环境参数，通过重放的方式执行至中断点处继续执行。
2. 两阶段提交：为保证跨分片的request/response在分片之间做原子性提交，采用2pc的方式。目前2pc的协调者是发起分片事务的源交易方。在prepare阶段相关分片执行得到结果并锁定相关合约，直到commit或者abort。

### 2pc的协调者
目前认为2pc的协调者就是用户发送的跨分片的交易，但有一个例外会导致问题: 用户在shardA发起的交易T1向shardB发送notify，shardB在执行该notify消息时向shardC发起了request。然而T1在shardA上发完notify时就已经结束，不可能再作为2pc的协调者，只能由shardB来做,因此需要增加协调者的逻辑。


### 分片事务的标识
1. 采用用户发送的交易hash： 由于交易本身包含了shard id,所以交易hash可以认为是全局分片中唯一的，然而作为分片事务的唯一标识，依然存在冲突的可能性。考虑以下场景：

```
user : {
	send transaction T1 to shard A;
}

shard A : {
	1. notify-> shard B;
	2. request-> shard C;
}

shard B : {
	1. handle notify from shard A;
	2. request -> shard C;
}
```
交易T1触发了两个事务，一个是交易本身触发，另一个是通过向shard B发送notify间接触发。如果采用交易T1的hash作为事务标识，则在shard C上将产生冲突。

2. 采用2pc的协调者交易hash：由于目前的设计是将区块里的跨分片消息打包在一整个交易里，采用这个交易的hash本身依然会产生冲突；目前对于notify消息的处理采用构造虚拟交易的方式处理，使用这个虚拟交易的hash做标识的话，得确保虚拟交易不会重复。
3. 每个shard维护一个递增的事务id，事务标识以shardid+事务id的方式作为全局标识。缺点是标识的生成依赖外部状态。

### 错误处理
跨分片事务处理的过程中会出现各种错误，不同错误的处理方式有极大的差别。根据错误处理的方式可以分为以下几类:
合约应用级错误：以交易失败的方式落账处理，如合约参数构造错误，事务消息和message queue的merkle根校验不一致等；
合约系统级错误： 以区块落账失败方式处理，典型的如账本读取错误，事务内部数据不一致等。
合约事务级错误： 事务消息经过message queue的检查，确保消息是由其他shard发送过来的，但在后续的处理中出现的应用级错误，应当把错误以response的形式响应其他shard。

## 实现

### sA向sB发送notify处理
消息内容
```go
type XShardNotify struct {
    Contract common.Address `json:"contract"`
    Payer    common.Address `json:"payer"`
    Fee      uint64         `json:"fee"`
    Method   string         `json:"method"`
    Args     []byte         `json:"payload"`
}

type CommonShardMsg struct {
    SourceShardID types.ShardID  `json:"source_shard_id"`
    SourceHeight  uint64         `json:"source_height"`
    TargetShardID types.ShardID  `json:"target_shard_id"`
    SourceTxHash  common.Uint256 `json:"source_tx_hash"`
    Type          int            `json:"type"`
    Payload       []byte         `json:"payload"`
    Msg           XShardMsg      `json:"-"`
}

```
流程： 将消息写入message queue中。如果最终这个交易以合约应用级错误或者合约系统级错误终止，message queue中写入的数据理应被回滚。目前该message queue存放在事务管理的store中，缺少相关的回滚机制。

### sB接收sA的notify消息处理逻辑
流程： 
1. 根据notify消息的相关字段调用相关合约的方法。
2. 如果执行成功，正常commit数据到下一层db
3. 如果执行失败，回滚修改的数据
4. 如果执行yield，说明处理过程中发生了跨分片invoke，保存事务数据，回滚合约修改

### 事务上下文的保存
由于我们采用重放的方式进行中断恢复，因此需要保存相关的事务状态信息：
```go
type TxState struct {
    State     int
    Shards    map[types.ShardID]int // 事务涉及的shard，以及他们的当前状态TxExec，TxPrepared，TxAbort等
    TxPayload []byte  // 需要重放的交易
    NextReqID int32   // 该交易的下一个request的编号
    Reqs      map[int32]*shardstates.XShardTxReq // 发出去的请求
    Rsps      map[int32]*shardstates.XShardTxRsp // 收到的响应
    Result    []byte                    // 最终结果
    ResultErr error
    WriteSet  *overlaydb.MemDB
    Notify    *event.ExecuteNotify
}
```

### sA向sB发送invoke处理
流程：
1. 创建该交易的事务状态，因为invoke是发起跨分片事务的入口。
2. 构建要发送的invoke消息
3. 如果当前invoke处于重放过程的话，需要校验构造的invoke消息和之前保存在事务状态中的一致。
4. 如果不一致，走事务abort流程。
5. 如果处于重放过程，从事务状态中获取response并返回；
6. 否则，将消息存入message queue和事务状态中，重置合约修改，保存事务状态，并返回yield

### sB接收sA的invoke请求处理
1. 构造事务状态，如果response存在(重放模式)，直接返回
2. 根据invoke消息的相关字段调用相关合约的方法。
3. 如果执行成功或者事务级错误，保存事务状态，清理合约修改，将消息写入message queue
4. 如果执行yield，说明处理过程中发生了跨分片invoke，保存事务数据，回滚合约修改（目前实现需要完善，同时事务状态需要增加inrequest和outrequest字段？）


### sA接收sB的invoke响应处理
1. 将响应加入事务状态中
2. 重新执行原交易
3. 如果执行失败，abort事务
4. 如果执行yield，说明处理过程中发生了跨分片invoke，保存事务数据，回滚合约修改（目前实现没有考虑到？）
5. 如果执行成功，向所有shard发送prepare消息，进入两阶段提交

### sB对prepare消息的处理
1. 读取事务状态，
2. 遍历每一个request，进行执行得到response
3. 与存储的response进行比较，如果不一致则abort
4. 发送prepared消息给sA, 保存执行的结果，锁定相关合约，返回yield

### sA对prepared消息的处理
1. 读取事务状态，
2. 保存相关shard的状态
3. 如果所有shard都prepared了，则发送commit消息，解锁相关合约，保存交易修改


### sB对commit消息的处理
1. 读取事务状态，
2. 解锁相关合约，保存交易修改


### abort消息的处理
1. 读取事务状态，
2. 解锁相关合约，丢弃交易修改
3. 如果是事务协调者，向所有shard发送abort消息

### 跨分片手续费的结算

前置条件：native支持neovm调用，并且能拿到neovm合约执行时消耗的gas；

1. 目标shard收到notify或者req的时候，将结构体内包含的原始payer加到context.Tx.SignedAddress里，使后续调用获得原始payer的权限；
2. 现在当前分片上已经有了原始payer的权限，所以可以在当前分片上扣除原始payer的手续费；
3. 在当前分片上，原始payer可能需要调用neovm的合约，这一部分消耗的gas计入原始payer的手续费消耗中，而不是记到交易构造者（当前分片当前区块的proposal）的手续费里；
4. 不重复扣费需要通过在native合约执行即ShardSysMsg合约执行的时候，改变context的gas值来实现：将neovm合约执行时消耗的gas在native里面直接从原始payer的账户里转走，将消耗的gas加回到context里，避免重复扣proposal的钱；
5. proposal需要支付每个大交易的0.01手续费（native），原始的payer需要为每次跨分片调用至少支付0.01个ong，包括req/notify/prepare/commit；