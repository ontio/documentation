
默认情况下，Restful 接口监听在 20334 端口。

- 使用 `--rest` 选项可以开启客户端的 Restful 服务。

```shell
ontology --rest
```

- 使用 `--restport` 选项为客户端指定 Restful 监听端口。

```shell
ontology --rest --restport 1024
```
本体客户端 Restful 接口所支持的方法如下表所示。

|          方法          |                 描述                 |
| :--------------------: | :----------------------------------: |
|     get_conn_count     |        得到当前连接的节点数量        |
| get_blk_txs_by_height  |    得到该高度的区块的所有交易哈希    |
|   get_blk_by_height    |         得到该高度的区块信息         |
|    get_blk_by_hash     |       通过区块哈希得到区块信息       |
|     get_blk_height     |       得到当前网络上的区块高度       |
|      get_blk_hash      |         得到该高度的区块哈希         |
|         get_tx         |     通过交易哈希得到该交易的信息     |
|      get_storage       |   通过合约地址哈希和键得到对应的值   |
|      get_balance       |        得到该地址的账户的余额        |
|   get_contract_state   |             得到合约状态             |
| get_sc_event_by_height |  得到该高度区块上的智能合约执行结果  |
|    get_smtcode_evts    |   通过交易哈希得到该交易的执行结果   |
| get_blk_hgt_by_txhash  | 通过交易哈希得到该交易落账的区块高度 |
|    get_merkle_proof    |  通过交易哈希得到该交易的merkle证明  |
|      get_gasprice      |            得到gas的价格             |
|     get_allowance      | 返回允许从from账户转出到to账户的额度 |
|     get_unboundong     |      返回该账户未提取的ong数量       |
|   get_mempooltxcount   |        得到内存中的交易的数量        |
|   get_mempooltxstate   |  通过交易哈希得到内存中该交易的状态  |
|      get_version       |             得到版本信息             |
|      post_raw_tx       |        向ontology网络发送交易        |
|     get_networkid      |            获取网络编号           |
|      get_grantong      |            得到grant ong             |
