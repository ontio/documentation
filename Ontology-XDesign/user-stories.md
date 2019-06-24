
# User Stories in Sharding

UserStory 从用户角度出发，描述shard对于用户所应该展示的信息。

## Create Shard

1. 用户调用shardmgmt合约，CreateShard
2. 用户调用shardmgmt合约，ConfigShard，更新shard的参数

结果：所有分片中都可以得到最新的shard信息

## Start Shard Node

1. 节点启动，命令行中指定shard ID
2. 节点开始同步main chain的区块，并执行区块中交易
3. 节点处理交易触发的 shard\_activated 事件
4. 如果节点参与到分片中，构建分片的config （**区分shard config 与 main chain config**）
5. 根据root ledger中的信息，初始化shard ledger
6. 启动shard的共识

结果：

1. 在main chain中完成shard activate后，所有的shard节点完成main chain账本同步后，参与shard的共识。
2. 对于shard共识节点：
如果没有到达proposal中的parent height，停止endorse／commit
3. 对于shard同步节点：
如果没有到达区块中的parent height，同步parent block，addBlock时确认parent block的有效性。

## Sync Shard

1. 节点启动，命令行中指定shard ID
2. 同步main chain区块，执行区块中交易
3. 节点处理交易触发的 shard\_activated 事件
4. 初始化shard ledger
5. 同步main chain区块和shard区块

结果：

1. shard的同步节点同时同步main chain账本和shard账本。

## Deploy Contract to Shard

1. 用户在main chain上部署合约
2. 用户配置合约在shard中运行

可运行在分片中的智能合约有两种类型：
* all-shard
* one-shard

结果：

1. shard中自动获得合约以及配置信息 (root账本中)

#### all-shard类型的智能合约

此类智能合约在main chain中部署完成后，可以同时运行在所有分片中。
比如资产类智能合约。

此类智能合约不支持shard间的迁移，此合约在每个shard中账本相互独立。
如果OEP中资产类合约需要在shard间迁移，可以通过 使用此合约的所有用户通过质押／提取的方式将shard中所有资产从shard转移到main chain中，然后再从main chain转移到shard中。

#### one-shard类型的智能合约

此类智能合约在main chain中部署完成后，同一时刻只能运行在一个分片中。
比如业务类智能合约。

此类智能合约，在后期可以支持shard间的迁移。迁移将在智能合约owner的控制下完成。

one-shard智能合约状态为：
* deployed : 合约owner在main chain上完成了合约部署。在此状态下，owner可以对智能合约运行环境进行配置，包括all-shard/one-shard运行方式的配置。owner在部署交易中也可以直接配置合约为all-shard／one-shard类型，指定shard。
* active : 合约可以被调用
* frozen ：合约不可以被调用，可以进行状态迁移。在此状态下，owner可以修改target shard。

Shard migration中的状态验证: 两种contract state migration方式，

* 直接从source shard中读取所有状态数据，保存到target shard。
* 从source shard中同步所有区块，重新生成新的状态数据。

#### Asset Contract的部署

？如何在shard中初始化资产，init函数在main chain中执行， owner在shard中依然可以重新执行init

**需要新的OEP支持分片中资产管理**

现有main chain的资产将不能在shard中使用，需要提供新的智能合约，完成main chain资产到shard资产的转化。
ONT／ONG合约可以通过shard sys合约完成main chain到shard的资产转换。

## Transactions in Shard

1. 执行共识的区块
2. 检查parent height，
3. 如果block pool中没有对应的parent block，请求parent block
4. 执行parent 区块
5. 执行cross-shard 消息
6. 执行 shard内部的 transactions

结果：

1. 用户发送的main chain交易，在shard节点中可以查询
2. 用户发送的shard交易，在shard节点也可以查询

## Deposite Asset to Shard

1. 用户在main chain向shard中质押资产
2. shard中的资产将自动生成到分片中的资产合约中
3. 用户可以在shard中查询shard中质押的资产


结果：
1. 用户只可以向active shard质押资产
2. 资产合约可以运行在任何shard中

## Withdraw Asset from Shard

用户已经在Shard中质押资产

1. 用户在shard中发起withdraw操作

## Withdraw Asset from Main Chain

用户已经在Shard中质押资产


## Transfer Asset between Shard


## Transaction Fee in Shard


## Cross Shard Notify in shard


## Governance of Shard


### Staking for some Shard Node


### Withdraw stakes


