
## VBFT Consensus

VBFT 共识



#### Make Proposal

**CheckNeedUpdateChainConfig**

从上一个区块中读取 LastConfigBlockNum，如果当前区块高度超过了 config.MaxBlockChainView，则启动epoch change

**CheckUpdateChainConfig**

xshard.GetShardView(parentLedger, shardID) 从 parentLedger 中读取当前 shard 的 epoch num

**GetShardConfig**

直接从 parent ledger读取分片管理合影的 shardState，
shardState中保存了VBFT的所有配置信息，根据VBFT的配置信息构建新的Chain config。

#### Contruct Block

1. 从 txnpool 中获取待打包的交易
2. 从 CrossShardPool 中获取 跨分片ShardTx
3. 构建 blockheader 和 block



##### To Fix

1. parent block cached in constructBlock
2. xshard.GetShardView 直接读取 parent ledger？
