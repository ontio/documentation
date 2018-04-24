---
title: 
sidebar: ont_doc_zh
permalink: ontology_ts_sdk_smartcontract_zh.html
folder: doc_zh
---


[English](./ontology_ts_sdk_smartcontract_en.html) / 中文

<h1 align="center">智能合约的部署和调用</h1>
<p align="center" class="version">Version 0.7.0 </p>

## 1. 部署合约

部署合约需要构建并发送相应的交易到链上执行。

构建合约需要提供合约内容的十六进制字符串，和一些配置参数。

合约内容一般.avm文件(对于NEO虚拟机)和.wasm文件(对于WASM虚拟机)提供。

配置参数如下：

```code``` 合约内容，十六进制的字符串。

```vmType``` 虚拟机类型。目前可选值有：

```
export enum VmType {
    NativeVM = 0xFF,
    NEOVM    = 0x80,
    WASMVM   = 0x90
}
```

```name``` 合约的名称。普通字符串。可选值。

```codeVersion``` 合约的版本。普通字符串。可选值。

```author``` 合约作者。普通字符串。可选值。

```email``` 合约作者的邮件地址。普通字符串。可选值。

```desp``` 合约的描述。普通字符串。可选值。

```needStorage``` 是否需要存储。布尔值。可选值。

````
import * as core from '../src/core'

//获取合约内容
var fs = require('fs')
var path = require('path')
let idContractAvm = fs.readFileSync(path.join(__dirname, '../src/smartcontract/data/IdContract.avm'))
var idContractAvmCode = ab2hexstring(idContractAvm)
var name = 'test',
	codeVersion = '1.0',
	author = 'alice',
	email = '',
	desp = '',
	needStorage = true;
//构建交易	
var tx = core.makeDeployCodeTransaction(idContractAvmCode, VmType.NEOVm, name, codeVersion, author, email, desp, needStorage)
//发送交易
var param = buildRestfulParam(tx)
var url = TEST_ONT_URL.sendRawTxByRestful
axios.post(url, param).then((res:any)=> {
	console.log('deploy res: '+ JSON.stringify(res.data))
	//6秒后查看部署结果。
    setTimeout(function () {
    	getContract(code, vmType)
    }, 6000)
    }).catch(err => {
   	   console.log('err: '+ err)
})

//从链上查询合约
const getContract = (avmCode, vmType=VmType.NEOVM) => {
    const codeHash = getContractHash(avmCode,vmType)
    let url = `${TEST_ONT_URL.REST_URL}/api/v1/contract/${codeHash}`
    console.log('url : '+ url)
    axios.get(url).then((res)=>{
        console.log(res.data)
    }).catch(err => {
        console.log(err)
    })
}
````

## 2. 调用合约

合约必须在成功部署后才能调用。 调用合约需要构建并发送相应的交易到链上执行。

### 2.1 通过abi文件构建交易

一般智能合约可以编译出相应的.avm文件和.abi文件(对于NEO虚拟机)。.abi文件是以JSON格式，描述智能合约的方法和参数。可以通过读取.abi文件方便的构建调用合约的交易。构建的交易可能还需要使用用户的私钥签名。

TS SDK 中与Abi相关的类有AbiInfo, AbiFunction, Parameter。

```
class AbiInfo {
    hash : string
    entrypoint : string
    functions : Array<AbiFunction>
}

```

```hash``` 智能合约hash值。也称合约地址。用来区别不通合约的标志。

```entrypoint``` 合约的入口函数名。

```functions``` 合约提供的函数集合。

````
class AbiFunction {
    name : string
    returntype : string
    parameters : Array<Parameter>
}
````

```name``` 函数名称。

```returntype``` 函数返回值类型。

```parameters``` 函数参数列表。

````
class Parameter {
    name : string
    type : ParameterType
    value : any
}
````

```name``` 参数名称。

```type``` 参数类型。

```value```  参数值。

通过读取合约的abi文件，构造相应的对象，能方便地提供构建交易时需要的函数名，参数，调用的合约哈希。

构造交易的函数所需参数如下：

```
function makeInvokeTransaction(funcName : string, parameters : Array<Parameter>, contractHash : string, vmType : VmType = VmType.NEOVM, fees : Array<Fee> = [])
```

```funcName``` 调用的合约中函数名称。

```parameters``` 函数的参数对象列表。

```contractHash``` 合约hash。

```vmType``` 虚拟机类型。

```fees``` 发送交易的费用。

下面以ONT ID智能合约中注册ONT ID的方法为例说明这个过程。

````
//读取abi文件。这里文件导出的是JSON
import abiJson from '../smartcontract/data/idContract.abi'
//解析abi内容
const abiInfo = AbiInfo.parseJson(JSON.stringify(abiJson))

//获取AbiFunction
const abiFunction = abiInfo.getFunction('RegIdWithPublicKey')

const privateKey = '7c47df9664e7db85c1308c080f398400cb24283f5d922e76b478b5429e821b95'
const publicKey = '1202037fa2bbad721197da4f2882e4f8e4ef6a77dbc7cfbd72267cdd72dd60ac30b41e'
const ontid = '6469643a6f6e743a544d7876617353794747486e7574674d67657158443556713265706b6a476f737951'

//构造参数。注意这里的参数类型是ByteArray，即十六进制字符串。
let p1 = new Parameter(f.parameters[0].getName(), ParameterType.ByteArray, ontid)
let p2 = new Parameter(f.parameters[1].getName(), ParameterType.ByteArray, publicKey)

//设置参数
abiFunction.setParasValue(p1, p2)

//构造交易对象
let fees = []
let vmType = VmType.NEOVM
let tx = makeInvokeTransaction(abiFunction.name, abiFunction.parameters, abiInfo.hash, vmType, fees)

//签名交易。现在得到最终构造好的交易。
signTransaction(tx, privateKey)
````

### 2.2 构建基于WASM合约的交易

对于基于WASM虚拟机的智能合约，编译合约没有产生abi文件。但提供准确的函数名和参数对象也可以使用同样的方法构造交易。

````
const codeHash = '9007be541a1aef3d566aa219a74ef16e71644715'
const params = [
		new Parameter('p1', ParameterType.Int, 20), 
		new Parameter('p2', ParameterType.Int, 30)
	]
const funcName = 'add'
let tx = makeInvokeTransaction(funcName, params, codeHash, VmType.WASMVM)
````

### 2.3 发送交易

有多种方式发送交易到链上执行。

#### 2.3.1 Restful

```
//使用封装的对象发送请求
let restClient = new RestClient()
//使用之前构造的交易对象，创建请求参数
restClient.sendRawTransaction(tx.serialize()).then(res => {
    console.log(res)
})
```

请求会返回该交易的hash。需要通过交易hash去查询合约的执行结果。比较简单的方法是，到本体的区块链浏览器上查询。

#### 2.3.2 Rpc

````
let rpcClient = new RpcClient()
rpcClient.sendRawTransaction(tx.serialize()).then(res => {
    console.log(res)
})
````

Rpc请求与Restful类似。返回的结果也是交易hash。

#### 2.3.3 Websocket

通过websocket发送请求，可以监听后台推送的消息。如果合约里写明了事件推送，合约方法调用后会有相应的推送消息。

````
//构造请求参数
let param = buildTxParam(tx)
let txSender = new TxSender(TEST_ONT_URL.SOCKET_URL)
//定义回调函数
//@param err 错误结果
//@param res 监听到的消息
//@param socket websocket对象
const callback = (err, res, socket) => {
    if(err) {
        console.log(err)
        socket.close()
        return;
    }
    if(res.Action === 'Notify') {
        console.log('Notify: '+ JSON.stringify(res))
        socket.close()
    }
}
txSender.sendTxWithSocket(param, callback)
````














