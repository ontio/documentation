## 智能合约API文档
从区块链查询数据的 API：

| API                                      | 返回值         | 说明               |
| ---------------------------------------- | ----------- | ---------------- |
| Blockchain.GetHeight()                   | uint        | 获得当前区块高度         |
| Blockchain.GetHeader(uint height)        | Header      | 通过区块高度，查找区块头     |
| Blockchain.GetBlock(byte[] hash)         | Block       | 通过区块 Hash，查找区块   |
| Blockchain.GetTransaction(byte[] txid)   | Transaction | 通过交易 ID 查找交易     |
| Blockchain.GetContract(byte[] script_hash) | Contract    | 根据合约散列获取合约内容     |
| Blockchain.GetTransactionHeight(byte[] txid) | uint64      | 通过交易 ID 获取交易所在高度 |

区块类 API：

| API                             | 返回值           | 说明                         |
| ------------------------------- | ------------- | -------------------------- |
| Header.Hash                     | byte[]        | 获得该区块的散列                   |
| Header.Version                  | uint          | 获得区块版本号                    |
| Header.PrevHash                 | byte[]        | 获得前一个区块的散列                 |
| Header.Index                    | uint          | 获得该区块的高度                   |
| Header.MerkleRoot               | byte[]        | 获得该区块中所有交易的 Merkle Tree 的根 |
| Header.Timestamp                | uint          | 获得区块的时间戳                   |
| Header.ConsensusData            | ulong         | 获得该区块的共识数据（共识节点生成的伪随机数）    |
| Header.NextConsensus            | byte[]        | 获得下一个记账合约的散列值              |


| API                             | 返回值           | 说明                         |
| ------------------------------- | ------------- | -------------------------- |
| Block.GetTransactionCount()     | int           | 获得当前区块中交易的数量               |
| Block.GetTransactions()         | Transaction[] | 获得当前区块中所有的交易               |
| Block.GetTransaction(int index) | Transaction   | 获得当前区块中指定的交易               |

交易类 API：

| API                       | 返回值                    | 说明           |
| ------------------------- | ---------------------- | ------------ |
| Transaction.Hash          | byte[]                 | 获得当前交易的 Hash |
| Transaction.Type          | byte                   | 获得当前交易的类型    |
| Transaction.GetAttributes | TransactionAttribute[] | 查询当前交易的所有属性  |



合约类 API：

| API                                      | 返回值            | 说明          |
| ---------------------------------------- | -------------- | ----------- |
| Contract.Script                          | byte[]         | 获得该合约的脚本    |
| Contract.Create(byte[] script, bool need_storage, string name, string version, string author, string email, string desc) | Contract       | 发布智能合约      |
| Contract.Migrate(byte[] script, bool need_storage, string name, string version, string author, string email, string desc) | Contract       | 迁移 / 更新智能合约 |
| Contract.Destroy()                       | void           | 销毁合约        |
| Contract.StorageContext                  | StorageContext | 获得合约的存储上下文  |

存储类 API：

| API                                      | 返回值            | 说明                               |
| ---------------------------------------- | -------------- | -------------------------------- |
| Storage.CurrentContext                   | StorageContext | 获取当前存储区上下文                       |
| Storage.Get(StorageContext,string)       | byte[]         | 查询操作，在持久化存储区中通过 key 查询对应的 value  |
| Storage.Get(StorageContext,byte[])       | byte[]         | 查询操作，在持久化存储区中通过 key 查询对应的 value  |
| Storage.Put(StorageContext, string,string) | void           | 插入操作，以 key-value 的形式向持久化存储区中插入数据 |
| Storage.Put(StorageContext, byte[],byte[]) | void           | 插入操作，以 key-value 的形式向持久化存储区中插入数据 |
| Storage.Put(StorageContext, byte[],string) | void           | 插入操作，以 key-value 的形式向持久化存储区中插入数据 |
| Storage.Put(StorageContext, string,byte[]) | void           | 插入操作，以 key-value 的形式向持久化存储区中插入数据 |
| Storage.Put(StorageContext, string,BigInteger) | void           | 插入操作，以 key-value 的形式向持久化存储区中插入数据 |
| Storage.Put(StorageContext, byte[],BigInteger) | void           | 插入操作，以 key-value 的形式向持久化存储区中插入数据 |
| Storage.Delete(StorageContext, byte[])   | void           | 删除操作，在持久化存储区中通过 key 删除对应的 value  |
| Storage.Delete(StorageContext, string)   | void           | 删除操作，在持久化存储区中通过 key 删除对应的 value  |

运行时相关的 API：

| API                          | 返回值  | 说明                                       |
| ---------------------------- | ---- | ---------------------------------------- |
| Runtime.Time                 | uint | 获取当前区块时间                                 |
| Runtime.CheckWitness(byte[]) | bool | 验证是否具有操作权限(包含合约或人)                       |
| Runtime.Notify(object[])     | void | 在智能合约中向执行该智能合约的客户端发送通知(包含socket通知或rpc查询) |
| Runtime.Log(string)          | void | 在智能合约中向执行该智能合约的客户端发送日志(socket及时通知)       |

System API：

| API                        | 返回值              | 说明                         |
| -------------------------- | ---------------- | -------------------------- |
| System.ScriptContainer     | IScriptContainer | 获得该智能合约的脚本容器               |
| System.ExecutingScriptHash | byte[]           | 获得该智能合约执行的脚本散列             |
| System.CallingScriptHash   | byte[]           | 获得该智能合约的调用者的脚本散列           |
| System.EntryScriptHash     | byte[]           | 获得该智能合约的入口点（合约调用链的起点）的脚本散列 |

System API：

| API                                      | 返回值    | 说明                                       |
| ---------------------------------------- | ------ | ---------------------------------------- |
| Native.Invoke(byte version, byte[] address, byte[] method, object args) | byte[] | 调用native合约。1、version 合约版本号， 2、address 合约地址， 3、method 合约方法， 4、合约参数 |






