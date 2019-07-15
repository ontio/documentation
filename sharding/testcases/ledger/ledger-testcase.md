# 账本测试用例

## 账本介绍
Shard中会执行root区块和shard区块，因此有root和shard两个账本。
为什么需要root账本？

* 每个shard可以有不同version／height的root账本，保证分片中的状态一致性
* 实现shard账本与root block height状态的绑定

## 测试用例

### case1, shard基本信息保存在rootshard上
shard的基本信息包括shardID、shard的creator、shard的状态state、shard创建时父shard的区块高度、shard的配置信息以及参与该shard共识的的peer信息。

#### 步骤
1. 构造创建shard的交易
2. 将交易发往rootshard 等待交易落账
3. 构建查询shardInfo的交易
4. 将该交易分别发往rootshard和子shard

#### 预期

发往rootshard交易能够查询到子shard的基本信息

发往子shard的交易执行失败

### case2, 首次启动分片

#### 步骤

1. 创建好shard, 激活该shard
2. 启动shard， 记录下启动shard时对应的rootshard 区块高度
3. 查看账本的变化(Chain文件的变化)

#### 预期

shard会先启动同步线程，同时生成rootshard Chain文件，此时shard并不会出块，也就不会有shard账本，待同步到启动shard的区块高度时，shard开始出块，shard ledger开始生成


### case3, rootshard推出来的子shard事件消息(分片治理相关的事件)
rootshard推出来的shard治理事件消息保存在rootshard的eventstore中。
该类事件有shard配置更新事件、shard激活事件。
#### 步骤
1. 构造shard config更新的交易和shard激活交易
2. 将交易发往rootshard，等待落账
3. 根据shardId和rootshard的高度,查询event, 通过rootshard查询

#### 预期

通过rootshard查询成功

#### case4, 跨分片消息保存在子shard crosssharddb中

合约中调用`NotifyRemoteShard`和`InvokeRemoteShard`方法推出来的跨分片调用的消息保存在shardID对应的子shard的crosssharddb中

#### 步骤

1. 准备两个合约A和合约B,合约A中有通过`NotifyRemoteShard`和`InvokeRemoteShard`调用合约B中的方法
2. 合约A和合约B部署到rootshard, 合约A的shardID 配置为0，`InvokedContract`配置成合约B的地址，合约B的shardID配置成1。
3. 先初始化合约B的MetaData，再初始化合约A的MetaData.
4. 调用合约A中的方法，该方法会调用合约B中的方法
5. 根据shardId可以查询msghash, 通过子shard查询
6. 根据msgHash可以查询shardMsg, 通过子shard查询

#### 预期

第5和6步发往子shard的查询请求均成功

### case5, 合约MetaData存储在rootshard的StateStore中

#### 步骤

1. 初始化合约的MetaDeta
2. 查询合约的MetaData,该查询是通过rootshard查询的
#### 预期

查询成功

### case6, 合约部署事件存储在rootshard eventstore中
合约部署的时候，会推送`ContractLifetimeEvent`类型的事件
#### 步骤

1. 部署合约到rootshard
2. 查询合约部署的事件

#### 预期

查询成功

### case7, 区块中的shardTx保存在blockStore中
shard中的区块包含Header, shardTx和Tx三个部分组成，shard交易数据结构是key为shardID， value为CrossShardInfo的数组的map。

#### 步骤
1. 构造调用合约A中的方法，该方法会调用子shard上的合约B中的某个方法，
2. 发送交易等待落账

#### 预期

根据高度查询shard中的区块