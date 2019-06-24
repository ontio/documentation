# Cross Shard Msg Queue

跨链的消息通过 Xshard Msg Queue的方式实现。

## XShard Msg Queue

每个Xshard Msg定义为：

```
    SourceShardID
    TargetShardID
    MsgID : length of current Msg Queue
    HashRoot: 添加Msg后，msg queue的hash root
    []Tx：msg中包括的子交易
    []Signature：共识节点对Hash root的签名
```

Msg Queue定义为：

```
Qin : (localShardID, remoteShardID, MsgID) -> ([]Tx, []signature, MerklePath)
Qout : (localShardID, remoteShardID, MsgID) -> ([]Tx, MerkelPath)
```

Msg Queue状态数据保存在sysmsg\_q的智能合约中，Qin和Qout分别保存

在Msg Queue的HashRoot计算中，只包括MsgID/[]Tx


每个子交易定义为：

```
    SourceShardID
    SourceHeight
    TargetShardID
    Type
    Payload
```

其中子交易类型有：

* SHARD-NOTIFY
* SHARD-TXREQ
* SHARD-TXRSP
* SHARD-PREPARE
* SHARD-PREPARED
* SHARD-COMMIT
* SHARD-ABORT

其中Payload中封装了

* target smart contract
* target method
* target args

## 1. Add Msg to Queue

智能合约通过调用sysmsg\_q的Notify／Revoke接口，触发对remote shard的远程调用。

将调用信息封装到Payload中，作为一个子交易添加到对应的Qout中，同时更新Merkle Path

## 2. Consensus

在区块执行完成后，

* 共识Proposer中将MerkelPath的root添加到Proposal，并做签名
* Endorser/Committer都将对Proposal进行签名
* 区块共识完成后，每个Q的Merkel root都得到了足够多的共识节点签名

## 3. Forward 

* consensus通知chainMgr将 XShard消息 转发到目标分片中
* 每个XShard消息中包括了一个区块中产生的所有跨分片交易
* 节点对XShard消息封装到一个消息中，通过http接口发送到目标分片中

## 4. Process Msg in Queue

* XShard Tx发送到交易池中
* 交易池中的xshard validator验证消息的有效性
* 共识算法从交易池中获取有效的xshard Tx添加到区块中的 xshard部分
* 共识后，处理xshard Tx

