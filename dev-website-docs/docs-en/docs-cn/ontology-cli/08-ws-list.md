


- [介绍](#介绍)
- [Websocket接口列表](#websocket接口列表)

## 介绍

本文档是Ontology的websocket接口文档，详细定义了各个接口所需的参数与返回值。

## Websocket接口列表

| Method | Parameter | Description |
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
| [sendrawtransaction](#10-sendrawtransaction) | data,[PreExec] | 向ontology网络发送交易, 如果 preExec=1，则交易为预执行 |
| [getstorage](#11-getstorage) | hash,key | 通过合约地址哈希和键得到对应的值 |
| [getbalance](#12-getbalance) | address | 得到该地址的账户的余额 |
| [getcontract](#13-getcontract) | hash | 根据合约地址哈希得到合约信息 |
| [getsmartcodeeventbyheight](#14-getsmartcodeeventbyheight) | height | 得到该高度区块上的智能合约执行结果 |
| [getsmartcodeeventbyhash](#15-getsmartcodeeventbyhash) | hash | 通过交易哈希得到该交易的执行结果 |
| [getblockheightbytxhash](#16-getblockheightbytxhash) | hash | 通过交易哈希得到该交易落账的区块高度 |
| [getmerkleproof](#17-getmerkleproof) | hash | 通过交易哈希得到该交易的merkle证明 |
| [getsessioncount](#18-getsessioncount) |  | 得到会话数量 |
| [getgasprice](#19-getgasprice) |  | 得到gas的价格 |
| [getallowance](#20-getallowance) | asset, from, to | 返回允许从from账户转出到to账户的额度 |
| [getunboundong](#21-getunboundong) | address | 返回该账户未提取的ong数量 |
| [getmempooltxstate](#22-getmempooltxstate) | hash | 通过交易哈希得到内存中该交易的状态 |
| [getmempooltxcount](#23-getmempooltxcount) |  | 得到内存中的交易的数量 |
| [getversion](#24-getversion) |  | 得到版本信息 |
| [getnetworkid](#25-getnetworkid) |  | 得到network id |
| [getgrantong](#26-getgrantong) |  | 得到grant ong |

