## XShard 



#### Receive XShard Msg

```
CrossShardPayload {
	Version
	ShardID
	Data  []byte
}
Data解析为：

CrossShardMsg {
	CrossShardMsgInfo		*CrossShardMsgInfo
	ShardMsg				[]CommonShardMsg
}
CrossShardmsgInfo {
	SignMsgHeight
	PreCrossShardMsgHash		// 上一个跨分片消息的MsgHash
	Index
	ShardMsgInfo				// 跨分片消息的节点签名
}
CommonShardMsg {				// 跨分片消息的接口，支持以下几种消息
	* XShardNotify
	* XShardTxReq
	* XShardTxRsp
	* XShardPrepareMsg
	* XShardPreparedMsg
	* XShardCommitMsg
	* XShardAbortMsg
}
```

Chainmgr 将所有CrossShardPayload 保存到Shard ledger中。

1. 将CrossShardMsg 保存到 chainMgr 中 CrossShardPool中
2. 将 CrossShardMsg 保存到 ledger 中
   * PreCrossShardMsgHash -> CrossShardMsg
   * SourceShardID -> PreCrossShardMsgHash
3. 将 ShardID 保存到 ledger 中 

### Get Cross Shard Tx from CrossShardPool

共识模块从 ChainMgr 的 CrossShardPool 中获取来自其他分片的跨分片消息

##### Solo

共识构建区块时，从 CrossShardPool 中获取跨分片消息。
在共识落帐后，将对应的跨分片消息从 CrossShardPool 中删除。


### XShard Tx in block

```

区块中的ShardTx：
map[uint64][]*CrossShardTxInfos

CrossShardTxInfos {
	ShardMsg 		*CrossShardMsgInfo
	Tx				*Transaction
}

Tx-Type : XShardTx的交易类型：ShardCall
Tx-Params:  XShardTx中的Payload为 ShardCall

ShardCall {
	Msgs 		[]CommonShardMsg
}
```

##### XShardTx 的构建

NewCrossShardTxMsg 将所有的ShardMsg封装到 ShardCall的交易中。 **交易的Payer为当前节点。**

输入参数：
  * shard ledger
  * toShardID
  * parentBlockNum

1. 根据 ParentBlockNum，获取 parent 发送到当前 toShard 的 message
2. 将 parent shard 发送的消息构建为 []CrossShardTxInfos
3. 遍历 CrossShardPool 中的所有shard
   1. 获取 fromShard -> toShard 的当前 msgHashRoot
   2. 从 CrossShardInfo 中获取对应的 ShardMsg，如果没找到，从 ledger 中查询对应的 ShardMsg
   3. 将所有的 Shard Msg，构建为 ShardTx
4. 返回所有的Shard Tx



