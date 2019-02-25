
默认情况下，WebSocket 接口监听在 `20335` 端口。

- 使用 `--ws` 选项可以开启客户端的 WebSocket 服务。

  ```shell
  ontology --ws
  ```

- 使用 `--wsport` 选项为客户端指定 WebSocket 监听端口。

  ```shell
  ontology --wsport 1024
  ```

本体客户端 WebSocket 接口所支持的方法如下表所示。

| 方法                                                                                            | 说明                                                 |
| :---------------------------------------------------------------------------------------------- | :--------------------------------------------------- |
| [heartbeat](docs-cn/ontology-cli/10-ws-specification#heartbeat)                                 | 发送心跳信号                                         |
| [subscribe](docs-cn/ontology-cli/10-ws-specification#subscribe)                                 | 订阅某个服务                                         |
| [getconnectioncount](docs-cn/ontology-cli/10-ws-specification#getconnectioncount)               | 得到当前连接的节点数量                               |
| [getblocktxsbyheight](docs-cn/ontology-cli/10-ws-specification#getblocktxsbyheight)             | 返回对应高度的区块中落账的所有交易哈希               |
| [getblockbyheight](docs-cn/ontology-cli/10-ws-specification#getblockbyheight)                   | 得到该高度的区块的详细信息                           |
| [getblockbyhash](docs-cn/ontology-cli/10-ws-specification#getblockbyhash)                       | 通过区块哈希得到区块信息                             |
| [getblockheight](docs-cn/ontology-cli/10-ws-specification#getblockheight)                       | 得到当前网络上的区块高度                             |
| [getblockhash](docs-cn/ontology-cli/10-ws-specification#getblockhash)                           | 根据高度得到对应区块的哈希                           |
| [gettransaction](docs-cn/ontology-cli/10-ws-specification#gettransaction)                       | 通过交易哈希得到该交易的信息                         |
| [sendrawtransaction](docs-cn/ontology-cli/10-ws-specification#sendrawtransaction)               | 向本体网络发送交易, 如果 `preExec=1`，则交易为预执行 |
| [getstorage](docs-cn/ontology-cli/10-ws-specification#getstorage)                               | 通过合约地址哈希和键得到对应的值                     |
| [getbalance](docs-cn/ontology-cli/10-ws-specification#getbalance)                               | 得到该地址的账户的余额                               |
| [getcontract](docs-cn/ontology-cli/10-ws-specification#getcontract)                             | 根据合约地址哈希得到合约信息                         |
| [getsmartcodeeventbyheight](docs-cn/ontology-cli/10-ws-specification#getsmartcodeeventbyheight) | 得到该高度区块上的智能合约执行结果                   |
| [getsmartcodeeventbyhash](docs-cn/ontology-cli/10-ws-specification#getsmartcodeeventbyhash)     | 通过交易哈希得到该交易的执行结果                     |
| [getblockheightbytxhash](docs-cn/ontology-cli/10-ws-specification#getblockheightbytxhash)       | 通过交易哈希得到该交易落账的区块高度                 |
| [getmerkleproof](docs-cn/ontology-cli/10-ws-specification#getmerkleproof)                       | 通过交易哈希得到该交易的 merkle 证明                 |
| [getsessioncount](docs-cn/ontology-cli/10-ws-specification#getsessioncount)                     | 得到会话数量                                         |
| [getgasprice](docs-cn/ontology-cli/10-ws-specification#getgasprice)                             | 得到 GAS 的价格                                      |
| [getallowance](docs-cn/ontology-cli/10-ws-specification#getallowance)                           | 返回允许从 from 账户转出到 to 账户的额度             |
| [getunboundong](docs-cn/ontology-cli/10-ws-specification#getunboundong)                         | 返回该账户未提取的ONG 数量                           |
| [getmempooltxstate](docs-cn/ontology-cli/10-ws-specification#getmempooltxstate)                 | 通过交易哈希得到内存中该交易的状态                   |
| [getmempooltxcount](docs-cn/ontology-cli/10-ws-specification#getmempooltxcount)                 | 得到内存中的交易的数量                               |
| [getversion](docs-cn/ontology-cli/10-ws-specification#getversion)                               | 得到版本信息                                         |
| [getnetworkid](docs-cn/ontology-cli/10-ws-specification#getnetworkid)                           | 得到 `network id`                                    |
| [getgrantong](docs-cn/ontology-cli/10-ws-specification#getgrantong)                             | 得到 `grant ong`                                     |
