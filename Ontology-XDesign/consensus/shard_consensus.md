# **shard consensus**

##  主要技术点

### 1.分片共识创世区块的配置文件，是由rootChain注册好以后,通过Active来自动启动shardChain process.当rootChain重启时，对应的shardChain process同时需要重新启动。当shard chain process关闭，rootChain还在运行时，shard chain需要自动重新开起来。

### 2.shardChain，需要同步rootChain block数据，同时在shardChain上记录rootChainHeight(parrentHeight)。shardChain共识过程中，在proposal阶段，需要verify rootchain block上的shardTx,当获取parrent height高度不一致时，需要先同步rootChain,直到达到对应的高度，再verify shardTx。

### 3.shardChain通过shard治理合约读取最新的chainconfig,来进行共识周期的切换和chainconfig文件的更新。

## 实现逻辑

### constructBlock

当前proposer节点构建区块，获取rootChain上对应高度区间内的shardTx

#### 构建区块
```
blk := &types.Block{
		Header:       blkHeader,
		ShardTxs:     shardTxs, // Cross-Shard Txs
		Transactions: txs,
	}
```
### processProposalMsg,验证proposalmsg

verify ShardTx,get shardTx from GetShardTxsByParentHeight()


### AddBlock


![](../img/shard_consensus.png)

## shard Consensus Cycle Switching

### 处理逻辑

1、判断是否满足changeView;

2、从shard治理合约读取最新的chainconfig,打包到当前区块中;

3、构建系统交易createShardGovTransaction();

4、开启新一轮的startNewRound()，其中检查上个区块中chainconfig是否有新的内容;

5、更新chainconfig,用新的chainconfig开始shardChain共识;

