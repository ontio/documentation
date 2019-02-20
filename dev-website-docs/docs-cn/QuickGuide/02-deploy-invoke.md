<h1 align="center">智能合约部署和调用</h1>

<p align="center" class="version">Version 1.0.0 </p>




## 部署合约

在部署合约之前，开发者需要准备好要部署的合约，且该合约已经被正确编译为.avm文件。

开发者还需要有Ontology的钱包账户，且保证账户上有足够的ONG，用以支付部署合约的费用。

目前，在测试网上部署合约，gasprice可以设为500。

部署合约需要用户构建特定的交易，并发送到区块链上执行。当交易执行完成后，合约就部署完成。

Ontology提供了不同的SDK和合约开发工具SmartX，帮助用户部署合约。

### 部署合约所需gas消耗计算

通过智能合约的预执行，可以获得当前合约执行所需要的`Gaslimit`,从而为智能合约的实际执行设置`Gaslimit`设置提供参考，避免由于**ONG**余额不足造成的执行失败。

```
$ ./ontology contract invoke --address 79102ef95cf75cab8e7f9a583c9d2b2b16fbce70 --params string:Hello,[string:Hello] --prepare --return bool
Invoke:70cefb162b2b9d3c589a7f8eab5cf75cf92e1079 Params:["Hello",["Hello"]]
Contract invoke successfully
  Gaslimit:20000
  Return:true
```

### 通过SDK部署合约

Ontology提供了不同的SDK。这里我们以[Typescript SDK](https://github.com/ontio/ontology-ts-sdk)为例，说明部署合约的过程。

Ts sdk提供了部署合约的接口，该接口的参数如下：

```avmCode``` 合约的avm code。必须值。

```name``` 合约的名称。可选值。默认为空字符串。

```version``` 合约的版本。可选值。默认为空字符串。

```author``` 合约的作者名。可选值。默认为空字符串。

```email``` 合约作者的邮件。可选值。默认为空字符串。

```desc``` 合约的描述。可选值。默认为空字符串。

```needStorage``` 合约是否需要存储。可选值。默认为true。

```gasPrice``` 部署合约支付的gas price。必须值。该值如果过小，交易将执行失败。

```gasLimit``` 部署合约支付的gas limit。必须值。该值如果过小，交易将执行失败。

```payer``` 支付部署费用的账户地址。必须值。

````
import { makeDeployCodeTransaction } from 'Ont'
const avmCode = '5ac56b6c766b00527ac46c766b51527ac4616c766b00c.........';
const name = 'test_contract';
const version = '1.0';
const author = 'Alice';
const email = 'alice@onchain.com'
const desc  = 'a test contract';
const needStorage = true;
const gasPrice = '0'; //set 0 for test in testnet
const gasLimit = '30000000'; // should be big enough
const payer = new Address('AazEvfQPcQ2GEFFPLF1ZLwQ7K5jDn81hve')
const privateKey = new PrivateKey('75de8489fcb2dcaf2ef3cd607feffde18789de7da129b5e97c81e001793cb7cf')
// construct transaction for deploy
const tx = makeDeployCodeTransaction(avmCode, name, version, author, email, desc, needStorage, gasPrice, gasLimit, payer);
//sign transaction with privateKey
signTransaction(tx, privateKey)
````

按照如上步骤构造好交易对象后，接下来需要发送交易到区块链上。有多种方式发送交易。更多信息可参考文档[智能合约调用]()。

这里我们用TS SDK里的方法为例，说明发送交易的过程。

````
import { RestClient } from 'Ont''
const restClient = new RestClient('http://polaris1.ont.io');
restClient.sendRawTransaction(tx.serialize()).then(res => {
    console.log(res);
})
````

该请求返回的结果类似如下：

````
{
	"Action": "sendrawtransaction",
	"Desc": "SUCCESS",
	"Error": 0,
	"Result": "70b81e1594afef4bb0131602922c28f47273e1103e389441a2e18ead344f4bd0",
	"Version": "1.0.0"
}
````

```Result``` 是该次交易的hash。可以用来查询交易是否执行成功。如果成功执行，说明合约部署成功。

我们仍然通过restful接口查询交易的执行结果。

````
restClient.getSmartCodeEvent('70b81e1594afef4bb0131602922c28f47273e1103e389441a2e18ead344f4bd0').then(res => {
    console.log(res);
})
````

该请求返回的结果类似如下：

````
{
    "Action": "getsmartcodeeventbyhash",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": {
        "TxHash": "70b81e1594afef4bb0131602922c28f47273e1103e389441a2e18ead344f4bd0",
        "State": 1,
        "GasConsumed": 0,
        "Notify": []
    },
    "Version": "1.0.0"
}
````

```State``` 值为1时， 说明交易执行成功，即合约部署成功；值为0时，说明交易执行失败，即合约部署失败。

另外，我们还可以通过合约的hash值，查询链上是否有合约。合约hash值是根据合约avm内容hash运算得到。

假设我们已知合约的hash值为**bcb08a0977ed986612c29cc9a7cbf92c6bd66d86**。

````
restClient.getContract('bcb08a0977ed986612c29cc9a7cbf92c6bd66d86').then(res => {
    console.log(res)
})
````

如果该请求返回合约的avm内容，说明合约已成功部署到链上。

### 通过SmartX部署合约

[SmartX](http://smartx.ont.io) 是开发者编写、部署和调用智能合约的一站式工具。具体使用说明请参考[smart文档](https://github.com/ontio/ontology-smartcontract/blob/master/smart-contract-tutorial/SmartX_Tutorial_cn.md)。


首先，我们需要在smartx上编译写好的合约。当合约编译成功后，下一步，选择部署合约。


<p>
  <img width="300px" src="https://upload-images.jianshu.io/upload_images/150344-1186fa3b18f9752f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240">
  <img width="300px" src="https://upload-images.jianshu.io/upload_images/150344-5f94d283e690512d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240">
</p>

在选择测试网环境时，SmartX提供了默认的账户，用来支付部署合约的费用和对交易签名。

通过简单的点击“部署”按钮，SmartX就为我们部署好了合约。




## 智能合约调用

### 1. 构建交易

当智能合约被部署到区块链上后，我们可以通过构建交易（Transaction），调用合约中的相应方法。

在构建交易之前，我们需要知道合约的abi文件和合约的hash地址。

#### 什么是abi文件？

一般开发者智能合约在编写完成后，会将使用相应编译器对合约进行编译，编译后一般会得到合约的abi文件和avm文件。avm文件是合约的字节码。当合约部署到区块链上时，合约字节码会存储在分配给合约的存储区里。 abi文件是描述了合约的具体结构的json文件，包含了合约的入口函数，接口函数，函数的参数列表和返回值，事件等。当我们了解了合约的abi文件，我们就了解了该合约的具体功能。

以smartx为例，我们有一个可以做简单加法计算的模板合约Arith， 编译完合约后，页面上会显示JSON格式的abi内容。用户可以选择下载abi.json文件。

![](https://upload-images.jianshu.io/upload_images/150344-297f0b59eb7b3e94.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 什么是合约hash？

合约hash是对合约的avm内容进行某些hash运算得到的值，该值是用来区分不同合约的唯一值。abi文件里一般也含有合约hash值。

#### 通过SDK构建交易

我们通过SDK可以方便的构建交易，调用合约中的方法。下面以TS SDK为例说明。我们要调用的合约是模板合约Arith，要调用的方法是合约中的加法Add。

````
import {Parameter, ParameterType, Address, reverseHex, TransactionBuilder} from 'Ont'
//set the function name to call
const funcName = 'Add';

//set the parameters of the function
const p1 = new Parameter('a', ParameterType.Integer, 1);
const p2 = new Parameter('b', ParameterType.Integer, 2);

//set the contract address
const contractAddr = new Address(reverseHex('c76d6764213612597cb815b6d444047e91a576bd));

//set gasPrice and gasLimit
const gasPrice = '0';
const gasLimit = '30000';

//make transaction
const tx = TransactionBuilder.makeInvokeTransaction(funcName, [p1, p2], contractAddr, gasPrice, gasLimit)
````

现在我们按照如上步骤构建好了交易对象。在构建过程中，方法名和方法参数需要跟abi文件中的描述一致，否则会执行出错。

一般执行智能合约是需要消耗gas的，所以交易对象中需要设置gasPrice和gasLimit, 这两个值如果太小，是不会被打包到区块中，合约方法就执行失败。在当前的测试网环境中，允许将gasPrice设置为0，这样就不需要耗费gas了。在正式环境中需要适当的gas才能保证合约正确调用。

正确的交易还需要签名，才能发送到区块链上执行。假设我们事先准备好了账户和私钥。

````
//assume we have an account and the private key
tx.payer = account.address;
signTransaction(tx, privateKey);
````

现在可以将签名过的交易发送到链上执行。

### 2. 发送交易

我们有多种方式发送交易：

1. 通过rpc接口发送交易
2. 通过restful接口发送交易
3. 通过websocket发送交易

通过rpc和restful接口发送交易，返回的结果是交易发送的状态和交易hash；

通过websocket发送交易，如果合约方法有事件推送，可以监听到推送的消息，该消息一般是合约执行成功的结果。

我们还可以通过以上接口，发送预执行的交易到链上。预执行意味着交易只在接收到该交易的节点上运行，不用等到区块共识后才能获得执行的结果。通过预执行交易，可以验证构建的交易是否正确，和获得该交易预计消耗的gas。

我们以TS SDK的restful接口为例，说明如何简单地发送交易。

````
import {RestClient} from 'Ont'
//construct the restful client
const client = new RestClient();

//we use the tx made in last step
client.sendRawTransaction(tx.serialize()).then(res => {
	//here is the result
    console.log(res);
})
````

### 3. 获取交易结果

在上一步我们通过restful的接口发送了交易到链上，返回的结果如下：

````
{
	"Action": "sendrawtransaction",
	"Desc": "SUCCESS",
	"Error": 0,
	"Id": null,
	"Result": "886b2cd35af7ea65e502077b70966652f4cf281244868814b8f3b2cf82776214",
	"Version": "1.0.0"
}
````

其中Result字段的值就是交易hash。我们可以通过restful接口查询交易的执行结果。

````
import {RestClient} from 'Ont'
const client = new RestClient();
client.getSmartCodeEvent('886b2cd35af7ea65e502077b70966652f4cf281244868814b8f3b2cf82776214').then(res => {
    console.log(res)
})
````

我们可以通过TS SDK中封装的restful接口查询该交易的执行结果，也可以通过postman等网络工具查询。查询的url如下：

````
http://{{NODE_URL}}/api/v1/smartcode/event/txhash/03295a1b38573f3a40cf75ae2bdda7e7fb5536f067ff5e47de44aeaf5447259b
````

这里的NODE_URL可以是测试网节点，也可以是本地节点。

查询得到的结果如下：

````
{
    "Action": "getsmartcodeeventbyhash",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": {
        "TxHash": "03295a1b38573f3a40cf75ae2bdda7e7fb5536f067ff5e47de44aeaf5447259b",
        "State": 1,
        "GasConsumed": 0,
        "Notify": [
            {
                "ContractAddress": "bd76a5917e0444d4b615b87c5912362164676dc7",
                "States": [
                    "02"
                ]
            }
        ]
    },
    "Version": "1.0.0"
}
````

通过观察结果里的数据可以判断该次交易是否执行成功。

```State``` 等于1表示执行成功；等于0表示执行失败。

````Notify```` 是合约方法执行中的消息推送。



## 智能合约模板

###  智能合约教程

[智能合约教程](https://github.com/ontio/ontology-smartcontract/tree/master/smart-contract-tutorial)


### 智能合约模板

| # | Smart contract                             | Link         |        Language      |   Description   |
| -----| ---------------------------------------- | ----------- | ---------------- | ---------------- |
| 1| Oep4                                   | [Here](https://github.com/ONT-Avocados/python-template/blob/master/OEP4Sample/OEP4Sample.py)        |    Python     |    Oep4  |
| 2| Oep5                               | [Here](https://github.com/ONT-Avocados/python-template/blob/master/OEP5Sample/OEP5Sample.py)        |  Python   |  Oep5   |
| 3| Invoke Oep4       | [Here](https://github.com/ONT-Avocados/python-template/blob/master/Static_Call_Oep4/static_call_Oep4.py)         |  Python  |  Invoke Oep4 method in SC   |
| 4| Storage example            | [Here](https://github.com/ONT-Avocados/python-template/blob/master/Storage_Example/storage_example.py)   |   Python  |  Storage example   |
| 5| Struct example            | [Here](https://github.com/ONT-Avocados/python-template/blob/master/Struct_Example/struct_example.py)      |   Python  |   Struct example  |
| 6| Invoke native in sc         | [Here](https://github.com/ONT-Avocados/python-template/blob/master/NativeAssetInvoke/native_asset_invoke.py)        | Python |   Invoke native in sc  |
| 7| Migrate Contract         | [Here](https://github.com/ONT-Avocados/python-template/blob/master/MigrateDestruct/migrate_destroyWithinContract.py)        | Python |   Migrate Contract  |
| 8| Event test        | [Here](https://github.com/ONT-Avocados/python-template/blob/master/EventTest/event_test.py)        | Python|  Event test   |
| 9| Smart contract libs         | [Here](https://github.com/ONT-Avocados/python-template/tree/master/libs)        | Python|  Smart contract libs    |

### 案例

| # | Smart contract                             | Link         |        Language      |   Description   |
| -----| ---------------------------------------- | ----------- | ---------------- | ---------------- |
| 1| Spokkz                                   | [Here](https://github.com/Spuul/spokkz-ontology-smart-contracts/blob/master/contracts/contracts/SpokkzCoin.py)        |    Python     |      |
| 2| Muzika                                   | [Here](https://github.com/MuzikaFoundation/ontology-smart-contract/blob/master/contracts/contracts/MuzikaCoin.py)        |    Python     |      |
| 3| Pumpkin                                  | [Here](https://github.com/skyinglyh1/CollectPumpkin/blob/master/collectPumpkin.py)        |    Python     |      |



### Native合约API

[Native Contract API](https://github.com/ontio/ontology/blob/master/docs/specifications/native_contract/paramapi.md).

[Native Contract Spec](https://github.com/ontio/ontology-smartcontract/tree/master/smartcontract/native)

### Native合约地址

contract | contract u160 address | Address
---|---|---
ONT Token | 0100000000000000000000000000000000000000| AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV
ONG Token | 0200000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbvhfRZMHJ
ONT ID | 0300000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6Ubvho7BUwN
Global Params | 0400000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbvhrUqmc2
Oracle | 0500000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbvhzQYRMK
Authorization Manager(Auth) | 0600000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6Ubvi9BuggV
Governance | 0700000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK
DDXF(Decentralized Exchange) | 0800000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbviKTaSnK



## 智能合约API文档

详细的API和例子可以参考[API doc](https://apidoc.ont.io/smartcontract/).

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

