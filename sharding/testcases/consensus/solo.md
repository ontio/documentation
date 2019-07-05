## Solo Consensus

solo 的共识流程如下:

1. 构建一个区块
2. 账本 ExecuteBlock，得到对应的 执行结果
3. 账本 SubmitBlock，将执行结果 提交到账本中
4. 清除已经打包到区块中的 CrossShardMsg
5. 将这个区块中产生的 CrossShardMsg 广播到其他分片
6. 更新ParentHeight


#### Make Block

1. 从交易池中获取当前分片的交易
2. 从 CrossShardPool 中获取跨分片消息
  * Parent Shard的跨分片消息，通过Event方式产生
  * Sib Shard的跨分片消息，通过P2P接收


##### To Fix

1. parent height check int MakeBlock()
