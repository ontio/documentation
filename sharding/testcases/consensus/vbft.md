
## VBFT Consensus

VBFT 共识



#### Make Proposal

CheckNeedUpdateChainConfig

    从上一个区块中读取 LastConfigBlockNum，如果当前区块高度超过了 config.MaxBlockChainView，则启动epoch change

CheckUpdateChainConfig

    xshard.GetShardView(parentLedger, shardID) 从 parentLedger 中读取当前 shard 的 epoch num

GetShardConfig

    直接从 parent ledger读取分片管理合约的 shardState， shardState中保存了VBFT的所有配置信息，根据VBFT的配置信息构建新的Chain config。

Contruct Block

1. 从 txnpool 中获取待打包的交易
2. 从 CrossShardPool 中获取 跨分片ShardTx
3. 构建 blockheader 和 block

Construct CrossShard Hash

1. 从当前chain store中取出上一区块的 execute result中的所有 shard event
2. 对每个消息的hash，计算 hash root
3. 签名，构建出 CrossShardMsgHash

#### Verify Proposal

processProposalMsg

1. 验证 previous block hash
2. 验证 block header 中的 LastConfigBlockNum
3. 验证 proposal 的 VBFT config
4. 验证 last block timestamp
5. 验证 VRF
6. 验证 parent ledger 的区块高度
  1. 如果parent ledger没有达到对应的区块高度，发送 SyncBlock 请求p2p同步对应的区块
7. 验证分片中上一个区块的CrossMsgHash，是当前分片向所有其他分片的msg hash root
8. 验证跨分片交易
9. 验证区块中的所有分片内交易


verifyShardEventMsg

    验证上一个区块的产生的，要发到其他分片的跨分片消息的 msg hash root

verifyCrossShardTx

    验证每个 CrossTxMsg，从parent ledger读取对应的shard的节点列表，验证对应的签名


##### To Fix

1. parent block cached in constructBlock
2. xshard.GetShardView 直接读取 parent ledger？
3. parent block height checking in processProposalMsg
4. constructCrossShardHashMsg 中只计算了当前区块的msg hash，没有将历史区块的hash root构成完整的 msg hash root
