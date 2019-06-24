
# Chain Manager

Chain Manager的主要功能

1. shard启动时，从RootShard中获得配置
2. 初始化Shard ledger，包括rootLedger和shardLedger
3. 从RootShard获得最新的区块
4. 为共识模块提供RootShard区块高度和区块
5. 处理shard中智能合约的Event
6. 维护当前所有shard的配置信息
7. 维护shard与root的eventbus链接


## ChainMgr 初始化

1. 链接到parent shard
2. 从parent shard获取当前shard的配置信息
3. 加载local账本
4. 验证rootLedger有效性
5. 验证shardLedger有效性
6. 从rootLedger中加载所有sib shard信息
7. 从LocalLedger加载本地信息

## RemoteShard 消息处理

RemoteShard消息为处理来自parent shard通过eventbus发送的消息，包括：

* HELLO\_MSG
* CONFIG\_MSG
* BLOCK\_REQ\_MSG
* BLOCK\_RSP\_MSG

其中HELLO为shard启动时向root shard发送的配置请求消息。

CONFIG为root shard对shard的hello消息的回复。
**CONFIG将不再发送shard的配置信息，而由shard通过自己的root ledger获取自己的配置**

BLOCK\_REQ为shard中收到其他节点的parent block height超过当前节点，向root shard节点请求最新的区块信息。

BLOCK\_RSP为root shard向shard中同步root shard的最新区块，chainmgr将缓存一定数目的root shard区块。

## LocalShard 消息处理

LocalShard消息为当前shard的治理合约中对外发送的系统事件，包括

* SHARD\_CREATE
* SHARD\_CONFIG\_UPDATE
* SHARD\_PEER\_JOIN
* SHARD\_ACTIVATED

以及一些资产质押相关的事件。

其中最重要事件为 SHARD\_ACTIVATED，chainMgr将启动shard进程。

## ChainMgr与cross Shard消息

shard中每个区块finalized后，chainmgr将检查是否有需要发送的cross shard消息。
如果需要，将构建对应的交易，转发到其他shard中。

## ChainMgr 内部状态

* shard-info，包括parent shard信息和sib shard信息
* parent-shard-pending-blocks
* parent-ledger
* local-ledger


