# 分片VBFT共识测试用例

#### VBFT共识类型，分片启动以后，就会像主链一样经历Proposal,Endorser,Commiter三个阶段，共识确认以后产生新的区块。
##出块流程
###case 1、区块构建(make proposal)

####步骤:
 1、打包跨分片消息到proposal block
 
 2、打包shardTx到proposal block
 
 3、检查当前的parent height高度,设置proposal block parent height
 
 4、对跨分片消息进行签名处理
 
####预期:
1、如果当前有跨分片消息proposal block中crossmag 不为nil

2、如果当前有shardTx, proposal block中shardTx有内容

3、proposal block中parent height高度为当前parent ledger current block height高度范围(通过cli可以设置这个阈值)

4、如果有跨分片消息，签名len(map) 不为0

###case 2、其他节点对proposal block内容进行有效性验证

####步骤:
1、proposal block中parent height如果大于当前节点parent ledger current block height。当前节点需终止校验，发送p2p同步请求到parent chain,请求同步对应高度的区块。

2、proposal block中parent height如果小于等于当前节点parent ledger current block height,执行后面验证逻辑。

3、proposal block中如果有跨分片消息，需要对消息hash进行有效性验证。

4、proposal block中如果有shardTx，需要对shardTx进行有效验证。

	4.1、如果shardTx中包含cross shard msg来自于parent chain,需要对msg hash进行有效性验证。

	4.2、如果shardTx中包括其他子shard的cross shard msg。首先需要拿到msg中签名高度，通过高度去event store中获取对应高度范围内,对应子shard的chainconfig信息，用其pubkey对cross shard msg中sigData进行验签。同时需要根据shardTx中payload获取msg,对msg进行hash处理，进行有效性验证。

####预期:
1、当节点parent height高度小于proposal block中parent height，触发sync区块请求。

2、proposal block中有跨分片消息，verifyShardEventMsg()返回为true。

3、proposal block中有shardTx消息，verifyCrossShardTx() 返回为true。


###case 3、Endorser阶段

####步骤:
1、prorosal验证通过以后,Endorser节点会对proposal消息,进行sign操作。除了对正常区块hash进行签名，还需要对跨分片消息进行sign操作。

2、其他节点，同时会收集别的Endorser节点发送过来的Endorser msg并且缓冲下来。

####期望:
1、Endorser节点对proposal消息处理完毕后,检查是否已经有跨分片消息签名。

2、其他节点，是否会收集到别的Endorser节点发来的Endorser消息。

###case 4、Commiter阶段

####步骤:
1、Commiter节点对proposal消息，进行sign操作。除了对正常区块hash进行签名，还需要对跨分片消息进行sign操作。

2、在commit阶段，节点会收到其他Commiter节点的commit msg。

3、把之前收集到的Endorser签名和Commiter签名,proposal 签名汇总到一起,确认签名数量满足2/3。seal block 产生新的区块。

####期望:
1、Commiter节点,对proposal消息进行sign操作完毕后,检查是否已经commit签名。

2、其他节点，是否会收到别的commiter节点发来的Commit消息。

3、检查收集的签名数量是否满2/3。


###case 5、在共识模块中，通过p2p把跨分片消息，发送到对应的shard上#

####步骤:
1、区块在chainstore执行完AddBlock以后。如果有跨分片消息，校验消息的签名和hash root，是否符合2/3数量。

2、保存以key:targetShardID,value:hash root 数据到DB。

3、保存以key:prevMsgHash,value:msg 数据到DB。

4、p2p广播msg to other shard。

####期望:
1、检查crosss shard msg签名数量。

2、检查msg hash root是否对应一致。

3、检查数据库中是否已经保存当前要发送cross shard msg的hash root。

4、检查数据库中是否已经保存当前要发送的msg。

3、检查p2p广播消息是否成功。

