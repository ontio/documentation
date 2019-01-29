

默认情况下，WebSocket 接口监听在 20335 端口。

- 使用 `--wsport` 选项为客户端指定 WebSocket 监听端口。

  ```shell
  ontology --wsport 1024
  ```

- 使用 `--disable-rpc` 选项可以关闭客户端的 WebSocket 服务。

  ```shell
  ontology --disable-rpc
  ```

本体客户端 WebSocket 接口所支持的方法如下表所示。

| 方法 | 参数 | 说明                                                 |
| :---| :---| :---|
| [heartbeat](#1-heartbeat) |  | 发送心跳信号 |
| [subscribe](#2-subscribe) | [ConstractsFilter],[SubscribeEvent],[SubscribeJsonBlock],[SubscribeRawBlock],[SubscribeBlockTxHashs] | 订阅某个服务 |
| [getconnectioncount](#3-getconnectioncount) |  | 得到当前连接的节点数量 |
| [getblocktxsbyheight](#4-getblocktxsbyheight) | height | 返回对应高度的区块中落账的所有交易哈希 |
| [getblockbyheight](#5-getblockbyheight) | height | 得到该高度的区块的详细信息 |
| [getblockbyhash](#6-getblockbyhash) | hash | 通过区块哈希得到区块信息 |
| [getblockheight](#7-getblockheight) |  | 得到当前网络上的区块高度 |
| [getblockhash](#8-getblockhash) | height | 根据高度得到对应区块的哈希 |
| [gettransaction](#9-gettransaction) | hash,[raw] | 通过交易哈希得到该交易的信息 |
| [sendrawtransaction](#10-sendrawtransaction) | data,[PreExec] | 向本体网络发送交易, 如果 `preExec=1`，则交易为预执行 |
| [getstorage](#11-getstorage) | hash,key | 通过合约地址哈希和键得到对应的值 |
| [getbalance](#12-getbalance) | address | 得到该地址的账户的余额 |
| [getcontract](#13-getcontract) | hash | 根据合约地址哈希得到合约信息 |
| [getsmartcodeeventbyheight](#14-getsmartcodeeventbyheight) | height | 得到该高度区块上的智能合约执行结果 |
| [getsmartcodeeventbyhash](#15-getsmartcodeeventbyhash) | hash | 通过交易哈希得到该交易的执行结果 |
| [getblockheightbytxhash](#16-getblockheightbytxhash) | hash | 通过交易哈希得到该交易落账的区块高度 |
| [getmerkleproof](#17-getmerkleproof) | hash | 通过交易哈希得到该交易的 merkle 证明 |
| [getsessioncount](#18-getsessioncount) |  | 得到会话数量 |
| [getgasprice](#19-getgasprice) |  | 得到 GAS 的价格 |
| [getallowance](#20-getallowance) | asset, from, to | 返回允许从 from 账户转出到 to 账户的额度 |
| [getunboundong](#21-getunboundong) | address | 返回该账户未提取的ONG 数量 |
| [getmempooltxstate](#22-getmempooltxstate) | hash | 通过交易哈希得到内存中该交易的状态 |
| [getmempooltxcount](#23-getmempooltxcount) |  | 得到内存中的交易的数量 |
| [getversion](#24-getversion) |  | 得到版本信息 |
| [getnetworkid](#25-getnetworkid) |  | 得到 `network id` |
| [getgrantong](#26-getgrantong) |  | 得到 `grant ong` |

