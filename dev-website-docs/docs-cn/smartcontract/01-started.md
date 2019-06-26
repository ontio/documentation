

## 1. 什么是智能合约

智能合约是一种旨在以信息化方式传播、验证或执行合约的计算机协议。

智能合约允许在没有第三方的情况下进行可信交易。这些交易 **可追踪且不可逆**。

区块链技术给我们带来了一个去中心化的，不可篡改的，高可靠性的系统，在这种环境下，智能合约才大有用武之地。

智能合约是区块链最重要的特性之一，也是区块链能够被称为颠覆性技术的主要原因。

## 2. 相关工具

* [SmartX](https://smartx.ont.io/#/) - 一站式智能合约 IDE，支持编译、部署、测试、Debug。
* [VSCode 插件](https://dev-docs.ont.io/#/docs-cn/Punica/sc-extension) - 智能合约开发。
* [IDEA 插件](https://dev-docs.ont.io/#/docs-cn/Punica/sc-idea-extension) - 智能合约开发。
* [测试币申请](https://developer.ont.io/applyOng) - 测试币申请网站
* [Punica](http://punica.ont.io/) - 支持智能合约编译，部署，调用，测试一体化开发框架。
* [dAPI](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/09-dapi_integration) - 简洁的去中心化 ```API```，通过钱包与本体链交互。
* [SDKs](https://dev-docs.ont.io/#/docs-cn/SDKs/00-overview) - 本体链不同编程语言的 ```SDK``` 。

## 3. 合约部署

在部署合约之前，开发者需要准备好要部署的合约，且该合约已经被正确编译为 ```.avm``` 文件。

开发者还需要有本体的钱包账户，且保证账户上有足够的 ```ONG``` ，用以支付部署合约的费用。

目前，在测试网上部署合约，```gasprice``` 可以设为 500。

部署合约需要用户构建特定的交易，并发送到区块链上执行。当交易执行完成后，合约就部署完成。

本体链提供了不同的 ```SDK``` 和合约开发工具 ```SmartX```，帮助用户部署合约。

## 4. 合约调用

### 4.1 GAS 计算

通过智能合约的预执行，可以获得当前合约执行所需要的 `Gaslimit` ,从而为智能合约的实际执行设置 `Gaslimit` 设置提供参考，避免由于 ```ONG``` 余额不足造成的执行失败。

```shell
$ ./ontology contract invoke --address 79102ef95cf75cab8e7f9a583c9d2b2b16fbce70 --params string:Hello,[string:Hello] --prepare --return bool
Invoke:70cefb162b2b9d3c589a7f8eab5cf75cf92e1079 Params:["Hello",["Hello"]]
Contract invoke successfully
  Gaslimit:20000
  Return:true
```

### 4.2 智能合约调用

#### 4.2.1 构建交易

当智能合约被部署到区块链上后，我们可以通过构建交易，调用合约中的相应方法。

在构建交易之前，我们需要知道合约的 ```abi``` 文件和合约的 ```hash``` 地址。

##### 什么是智能合约 abi 文件？

应用程序二进制接口（Application Binary Interface，ABI）定义了一组在系统软件上编译应用程序所需要遵循的一套规则。

主要包括基本数据类型，参数的传递规则等。

一般开发者智能合约在编写完成后，会将使用相应编译器对合约进行编译，编译后一般会得到合约的 ```abi``` 文件和 ```avm``` 文件。

```avm``` 文件是合约的字节码。当合约部署到区块链上时，合约字节码会存储在分配给合约的存储区里。

 ```abi``` 文件是描述了合约的具体结构的 ```JSON``` 文件，包含了合约的入口函数，接口函数，函数的参数列表和返回值，事件等。当我们了解了合约的 ```abi``` 文件，我们就了解了该合约的具体功能。

以 ```SmartX``` 为例，我们有一个可以做简单加法计算的模板合约 ```Arith``` ，编译完合约后，页面上会显示 ```JSON``` 格式的 ```abi``` 内容。用户可以选择下载 ```abi.json``` 文件。

![](https://upload-images.jianshu.io/upload_images/150344-297f0b59eb7b3e94.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

根据合约的 ```abi``` 文件中的合约 ```hash``` 和合约方法，可以通过 `sdk` 构造调用合约方法的交易。这里以 `ontology-ts-sdk` 为例。

```javascript
import {Parameter, ParameterType, Crypto, utils, TransactionBuilder} from 'ontology-ts-sdk'
//set the function name to call
const funcName = 'Add';

//set the parameters of the function,
// Please pay attention to the parameter type and value.
const p1 = new Parameter('a', ParameterType.Integer, 1);
const p2 = new Parameter('b', ParameterType.Integer, 2);

//set the contract address
const contractAddr = new Crypto.Address(utils.reverseHex('c76d6764213612597cb815b6d444047e91a576bd));

//set gasPrice and gasLimit
const gasPrice = '0';
const gasLimit = '30000';

//make transaction
const tx = TransactionBuilder.makeInvokeTransaction(funcName, [p1, p2], contractAddr, gasPrice, gasLimit)

// we need to add the payer and signature before we send it to blockchain
const adminPrivateKey = new Crypto.PrivateKey('7c47df9664e7db85c1308c080f398400cb24283f5d922e76b478b5429e821b97');
const adminAddress = new Crypto.Address('AdLUBSSHUuFaak9j169hiamXUmPuCTnaRz');
tx.payer = adminAddress;
TransactionBuilder.signTransaction(tx, adminPrivateKey);

```

##### 参数构造

构造交易时请注意参数的类型和参数值必须对应，且符合合约中方法的参数要求。 ```TS SDK``` 提供了 `Parameter` 和 `ParameterType` 类，用于辅助参数构造。

以下是常用参数构造的例子。更多参数构造的示例请参考 [ts sdk的测试用例](https://github.com/ontio/ontology-ts-sdk/blob/master/test/scParams.test.ts)

```javascript
const account = new Address('AdLUBSSHUuFaak9j169hiamXUmPuCTnaRz')
new Parameter('arg1', ParameterType.Boolean, false),
new Parameter('arg2', ParameterType.Integer, 3),
new Parameter('arg3', ParameterType.ByteArray, account.serialize()),
new Parameter('arg4', ParameterType.String, 'arg4')
new Parameter('arg5', ParameterType.Address, account')
new Parameter('arg6', ParameterType.Long, '100000000000000000')
```

##### 什么是合约 hash？

合约 ```hash``` 是对合约的 ```avm``` 内容进行某些 ```hash``` 运算得到的值，该值是用来区分不同合约的唯一值。```abi``` 文件里一般也含有合约 ```hash``` 值。

发送交易

我们有多种方式发送交易：

1. 通过 ```rpc``` 接口发送交易
2. 通过 ```restful``` 接口发送交易
3. 通过 ```websocket``` 发送交易

通过 ```rpc``` 和 ```restful``` 接口发送交易，返回的结果是交易发送的状态和交易 ```Hash```；

通过 ```websocket``` 发送交易，如果合约方法有事件推送，可以监听到推送的消息，该消息一般是合约执行成功的结果。

我们还可以通过以上接口，发送预执行的交易到链上。

预执行意味着交易只在接收到该交易的节点上运行，不用等到区块共识后才能获得执行的结果。通过预执行交易，可以验证构建的交易是否正确，和获得该交易预计消耗的 ```gas``` 。

我们以 ```TS SDK``` 的 ```restful``` 接口为例，说明如何简单地发送交易。

```javascript
import {RestClient} from 'ontology-ts-sdk'
//construct the restful client
const client = new RestClient();// default connects to TestNet

//we use the tx made in last step
client.sendRawTransaction(tx.serialize()).then(res => {
	//here is the result
    console.log(res);
})
```

> `sendRawTransaction` 方法的第二个参数 `preExec` 表示是否发送预执行交易，该参数是 `boolean` 类型，默认值为 `false` 表示正常执行交易，设为 `true` 表示发送预执行交易。
> 
> 预执行交易会立即返回合约方法的返回值，执行该方法所需 `gasLimit` ，可以用来查询合约或者检查交易的构造是否正确。

#### 4.2.2 获取交易结果

在上一步我们通过 ```restful``` 的接口发送了交易到链上，返回的结果如下：

```json
{
	"Action": "sendrawtransaction",
	"Desc": "SUCCESS",
	"Error": 0,
	"Id": null,
	"Result": "886b2cd35af7ea65e502077b70966652f4cf281244868814b8f3b2cf82776214",
	"Version": "1.0.0"
}
```

其中 `Result` 字段的值就是交易 `hash` 。我们可以通过 `restful` 接口查询交易的执行结果。

```javascript
import {RestClient} from 'Ont'
const client = new RestClient();
client.getSmartCodeEvent('886b2cd35af7ea65e502077b70966652f4cf281244868814b8f3b2cf82776214').then(res => {
    console.log(res)
})
```

我们可以通过 ```TS SDK``` 中封装的 ```restful``` 接口查询该交易的执行结果，也可以通过 ```postman``` 等网络工具查询。查询的`url` 如下：

```
http://{{NODE_URL}}/api/v1/smartcode/event/txhash/03295a1b38573f3a40cf75ae2bdda7e7fb5536f067ff5e47de44aeaf5447259b
```

这里的 ```NODE_URL``` 可以是测试网节点，也可以是本地节点。

查询得到的结果如下：

```json
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
```

通过观察结果里的数据可以判断该次交易是否执行成功。

```State``` 等于1表示执行成功；等于0表示执行失败。

 ```Notify``` 是合约方法执行中的消息推送。
