

## 启用 RPC 服务

默认情况下，RPC 接口监听在 20336 端口。

使用 `--rpcport` 选项为客户端指定 RPC 监听端口：

```shell
ontology --rpcport 1024
```

使用 `--disable-rpc` 选项可以关闭客户端的 RPC 服务：

```shell
ontology --disable-rpc
```

本体客户端 RPC 接口所支持的方法如下表所示。

|                             方法                             |                      描述                      |
| :----------------------------------------------------------: | :--------------------------------------------: |
| [getbestblockhash](04-interface-specification.md#getbestblokhash) |          获取当前节点最高区块的哈希值          |
|      [getblock](04-interface-specification.md#getblock)      |       根据区块哈希或区块高度查询区块信息       |
|               [getblockcount](#getblockcount)                |               查询当前的区块数量               |
|                [getblockhash](#getblockhash)                 |             查询指定高度的区块哈希             |
|          [getconnectioncount](#getconnectioncount)           |            查询当前节点的连接节点数            |
|           [getrawtransaction](#getrawtransaction)            |            通过交易哈希得到交易详情            |
|          [sendrawtransaction](#sendrawtransaction)           |                向网络中发送交易                |
|                  [getstorage](#getstorage)                   |         获取合约存储中指定键值对应的值         |
|                  [getversion](#getversion)                   |             获取当前连接节点的版本             |
|            [getcontractstate](#getcontractstate)             |            根据合约地址获取合约信息            |
|           [getmempooltxcount](#getmempooltxcount)            |        获取交易池（内存）中的交易的数量        |
|           [getmempooltxstate](#getmempooltxstate)            |        获取交易池（内存）中的交易的状态        |
|           [getsmartcodeevent](#getsmartcodeevent)            |             获取智能合约的执行结果             |
|      [getblockheightbytxhash](#getblockheightbytxhash)       |             获取交易落账的区块高度             |
|                  [getbalance](#getbalance)                   |               获取账户地址的余额               |
|              [getmerkleproof](#getmerkleproof)               |             获取交易的 merkle 证明             |
|                 [getgasprice](#getgasprice)                  |           获取当前节点的 `gas price`           |
|                [getallowance](#getallowance)                 |    获取一方账户允许另一方账户转出的通证额度    |
|                 [getgrantong](#getgrantong)                  | 获取根据当前所持有 ONT 估算出的可提取 ONG 数量 |
|               [getunboundong](#getunboundong)                |       获取账户当前实际可提取的 ONG 数量        |
|         [getblocktxsbyheight](#getblocktxsbyheight)          |             获取指定高度的区块哈希             |
|                [getnetworkid](#getnetworkid)                 |                  获取网络编号                  |