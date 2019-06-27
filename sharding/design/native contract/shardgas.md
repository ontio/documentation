# Shard Gas [replace by shard asset]

## 功能

1. 用户质押gas到分片

2. 从分片提取gas到主链；

3. 分片共识切换的CommitDpos入口；

## 实现

Ong合约在Init时，会将所有ONG转入到ShardSysMsg合约；由于主链ONG合约已经init，所以这笔交易在主链上不会发生，shard创建时，初始化Ong合约，所以shard上所有ONG在最初的时候都在ShardSysMsg合约里；

### 质押gas到分片

用户调用DepositGas方法，将Gas质押到分片。

#### 参数

```
type DepositGasParam struct {
	User    common.Address // 用户地址
	ShardId types.ShardID // 目标shard
	Amount  uint64 // 质押数量
}
```

#### 处理过程

1. 取shardBalance，加上param.Amount，保存；
2. 将ONG转入到shardGas合约；
3. 推送DepositGasEvent，chainMgr处理此event，chainMgr收到此event后，将event放到区块里下发给目标shard；
4. 目标shard收到event后，构造调用ShardSYSMsg合约处理此event的交易，将构造好的交易打包到自己的区块里；
5. 区块落账时，执行交易，将ONG从ShardSYSMsg合约转到用户地址；

#### DepositGasEvent

```
type DepositGasEvent struct {
	ImplSourceTargetShardID
	Height uint32
	User   common.Address
	Amount uint64
}
```

### 从分片提取gas [待完善]
![img](../img/shardgas-userwithdraw.png)

用户调用UserWithdrawGas方法，提取Gas到主链。

该方法通过为每个用户的每笔提取调用分配唯一的id来实现。

每次在分片上提取gas，无论这笔gas有没有在主链上释放，这笔gas都会先在分片上回收到shardSysMsg。

#### 参数

```
type UserWithdrawGasParam struct {
	User   common.Address // 用户地址
	Amount uint64 // 提取数量
}
```
用户只能向shard发送提取Gas的请求，向哪个shard发，提取在哪个shard上质押的Gas，所以参数中不带有shardId；

#### 处理过程

1. 在shard上通过预执行拿到用户的gas余额，与param.Amount比较，余额小于Amount则返回错误；
2. 给这笔提取分配唯一的WithdrawId；
3. 以WithdrawId记录用户这笔尚未完成的提取的金额，保存在合约的数据里；
4. 将提取的ONG转回到ShardSysMsg合约；
5. 推送WithdrawGasReqEvent；
6. 分片chainMgr收到event后，分片的共识节点构造交易并签名，然后将此交易发送到root，构造的交易为调用root上的ShardGas的PeerConfirmWithdraw方法，传入withdrawId；
7. PeerConfirmWithdraw方法会收集Shard当前共识节点的确认，当确认数超过ShardConfig里的K-C之后，释放该笔提取的gas，减少记录的Shard的GasBalance，并且将withdrawId放到WithdrawGasDoneEvent里推出；
8. 主链ChainMgr收到WithdrawGasDoneEvent之后，随block一起下发到shard；
9. Shard收到WithdrawGasDoneEvent之后，将event里的withdrawId对应的提取的金额设成零，提取结束；

#### WithdrawGasReqEvent

```
type WithdrawGasReqEvent struct {
	ImplSourceTargetShardID
	Height     uint32
	User       common.Address
	WithdrawId uint64
	Amount     uint64
}
```

### 重试提取gas

当用户提取gas失败时，可以通过这种方式重试提取。

主链确认失败，即PeerConfirmWithdraw调用失败，可能是分片的共识节点签名数量不够导致的，也可能是分片共识节点构造的交易在传播过程中丢失了；
在失败的情况下，主链将不会下发WithdrawGasDoneEvent，分片在没有收到此event时，不管gas在主链上有没有释放，都认为这笔提取没有成功，此时用户可以重试提取。

用户可以通过预执行查询自己在分片上有哪些提取没有完成，预执行返回的结果为一个map，key是withdrawId，value是对应的金额；拿到未完成的withdrawId后，可以将其当成参数调用UserWithdrawRetry方法。

#### 处理过程

1. 根据用户传入的withdrawId取出对应的金额，如果金额为零，说明用户的提取完成了，返回err；
2. 使用withdrawId和amount构造WithdrawGasReqEvent并推出；
3. 分片chainMgr收到WithdrawGasReqEvent，之后的步骤与正常的提取过程一致；

### 节点确认提取

分片上的共识节点的chainMgr收到WithdrawGasReqEvent之后，会构造发往主链的交易并签名；

这笔交易是调用主链的ShardGas的PeerConfirmWithdraw，传入signer，ShardID，User，WithdrawId，Amount；

#### 参数

```
type PeerWithdrawGasParam struct {
   	Signer     common.Address
   	PeerPubKey string
   	User       common.Address
   	ShardId    types.ShardID
   	Amount     uint64
   	WithdrawId uint64
   }
```

#### 处理过程

1. 根据shardID取出对应的Shard的详细信息；
2. 验证Signer，并且signer是shard的当前的共识节点；
3. 记录确认这笔withdrawId的shard的共识节点，不会重复记录；
4. 当对这笔withdrawId确认的shard的共识节点数量首次达到config.K-config.C时，将amount数量的gas转回到用户地址，并且推出WithdrawGasDoneEvent；
5. 主链上的ChainMgr收到WithdrawGasDoneEvent，将它随区块一起下发至shard；

#### WithdrawGasDoneEvent

```
type WithdrawGasDoneEvent struct {
	ImplSourceTargetShardID
	Height     uint32
	User       common.Address
	WithdrawId uint64
}
```

### 提取成功

当shard收到WithdrawGasDoneEvent之后，会将ShardGas里记录的对应的withdrawId的提取金额置位0，用户的此次提取结束。

#### 参数

```
type UserWithdrawSuccessParam struct {
	User       common.Address
	WithdrawId uint64
}
```

#### 处理过程

1. shard上chainMgr收到WithdrawGasDoneEvent后，构造调用ShardSysMsg合约的交易，将WithdrawGasDoneEvent交由ShardSysMsg合约处理；
2. ShardSysMsg会根据event构造参数，调用ShardGas的UserWithdrawSuccess方法；
3. UserWithdrawSuccess中，会根据WithdrawId取出对应的amount，如果amount为零，说明该笔提取已经成功了，返回error；
4. 将withdrawId对应的amount设为0，结束该笔提取。

### 分片切共识 [待完善]

当分片上共识完成一轮之后，需要调用ShardGas的ShardCommitDpos方法，进行共识切换和当轮手续费回收。

由于分片上的每笔交易的手续费都支付到ShardGas合约，所以每轮共识结束后，都需要将当前轮的手续费回收到ShardSysMsg。

#### 处理过程

1. ShardGas取自身的ONG余额，将其全部转入ShardSysMsg；
2. 调用ShardMgmt合约的ShardCommitDpos方法；
3. 推出ShardCommitDposEvent；
4. 分片上的共识节点ChainMgr收到event之后，构造调用主链上ShardGas的CommitDpos方法的交易，进行主链切分片共识。

#### ShardCommitDposEvent

```
type ShardCommitDposEvent struct {
	ImplSourceTargetShardID
	Height    uint32
	FeeAmount uint64
}
```

### 主链切分片共识 [待完善]

分片在共识周期切换时，会将手续费回收，这部分回收的手续费需要在主链上分给参与分片治理的用户。

处理过程与PeerConfirmWithdraw有些类似，都是先收集分片的共识节点的确认，确认数够了之后执行具体的逻辑。

#### 参数

```
type CommitDposParam struct {
	Signer     common.Address
	PeerPubKey string
	*shardmgmt.CommitDposParam
}
```

```
type shardmgmt.CommitDposParam struct {
	ShardID   types.ShardID
	FeeAmount uint64
}
```

#### 处理过程

1. 收集分片上的共识节点的确认数，确认数首次达到config.K-config.C之后，执行下面的逻辑；
2. 将参数的amount的ONG转入ShardStake，供手续费分润用；
3. 调用ShardMgmt合约的CommitDpos方法，传入shardmgmt.CommitDposParam作为参数；