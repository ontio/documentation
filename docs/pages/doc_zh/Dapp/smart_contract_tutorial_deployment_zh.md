---
title: 
keywords: sample homepage
sidebar: Dapp_zh
permalink: smart_contract_tutorial_deployment_zh.html
folder: doc_zh/Dapp
---


[English](./smart_contract_tutorial_deployment_en.html) / 中文

<h1 align="center">智能合约部署</h1>
<p align="center" class="version">Version 1.0.0 </p>

## 准备工作

在部署合约之前，开发者需要准备好要部署的合约，且该合约已经被正确编译为.avm文件。

开发者还需要有Ontology的钱包账户，且保证账户上有足够的ONG，用以支付部署合约的费用。

目前，在测试网上部署合约，费用可以设为0。

## 如何部署

部署合约需要用户构建特定的交易，并发送到区块链上执行。当交易执行完成后，合约就部署完成。

Ontology提供了不同的SDK和合约开发工具SmartX，帮助用户部署合约。

## 通过SDK部署合约

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

## 通过SmartX部署合约

[SmartX](http://smartx.ont.io) 是开发者编写、部署和调用智能合约的一站式工具。具体使用说明请参考[smart文档]()。

![](https://upload-images.jianshu.io/upload_images/150344-1186fa3b18f9752f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

首先，我们需要在smartx上编译写好的合约。当合约编译成功后，下一步，选择部署合约。

![](https://upload-images.jianshu.io/upload_images/150344-5f94d283e690512d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

在选择测试网环境时，SmartX提供了默认的账户，用来支付部署合约的费用和对交易签名。

通过简单的点击“部署”按钮，SmartX就为我们部署好了合约。
