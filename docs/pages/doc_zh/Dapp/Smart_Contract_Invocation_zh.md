---
title:
keywords: sample homepage
sidebar: Dapp_zh
permalink: Smart_Contract_Invocation_zh.html
folder: doc_zh/Dapp
giturl: https://github.com/ontio/ontology-smartcontract/master/smart-contract-tutorial/Smart_Contract_Invocation_cn.md
---

<h1 align="center">智能合约调用</h1>

<p align="center" class="version">Version 1.0.0 </p>

[English](./Smart_Contract_Invocation_en.html) / 中文
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
