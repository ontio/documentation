---
title: 
keywords: sample homepage
sidebar: ont_doc_en
permalink: ontology_ts_sdk_smartcontract_en.html
folder: doc_en
---


English / [中文](./ontology_ts_sdk_smartcontract_zh.html)

<h1 align="center">Deploy & invoke smart contract</h1>
<p align="center" class="version">Version 0.7.0 </p>

## 1. Deploy smart contract

This process needs to construct related transaction and send it to the blockchain.

Users should offer the contract's content in hex string and some configuration parameters to construct the transaction.

Normally, contracts are stored in .avm files (for NEO VM) and .wasm files (for WASM VM).

The configuration parameters are as follow:

```code``` contract's content，hexadecimal string。

```vmType``` type of virtual machine。Now we supports these types：

```
export enum VmType {
    NativeVM = 0xFF,
    NEOVM    = 0x80,
    WASMVM   = 0x90
}
```

```name ``` name of the contract, optional string value.

```codeVersion``` version of  the contract, optional string value.

```author``` author of the contract, optional string value.

```email``` email of the contract's author, optional string value.

```desp``` description of the contract, optional string value.

```needStorage``` the contract needs storage or not. Default as true.

```
import * as core from '../src/core'

//get the content of the contract
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
//construct the transaction
var tx = core.makeDeployCodeTransaction(idContractAvmCode, VmType.NEOVm, name, codeVersion, author, email, desp, needStorage)
//send the transaction
var param = buildRestfulParam(tx)
var url = TEST_ONT_URL.sendRawTxByRestful
axios.post(url, param).then((res:any)=> {
	console.log('deploy res: '+ JSON.stringify(res.data))
	//check the result of deploying contract in 6 seconds
    setTimeout(function () {
    	getContract(code, vmType)
    }, 6000)
    }).catch(err => {
   	   console.log('err: '+ err)
})

//query the contract from blockchain.
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
```

## 2. Invoke smart contract

You can not invoke smart contract before deploying it. Invoking contract needs to construct related transaction and send it to the blockchain.

### 2.1 Construct transaction with abi file

```.abi```file is in JSON format that describes the methods and parameters of the smart contract. We can construct the transaction to invoke contract easily with abi files. Some transactions may need to be signed with user's privatekey.

There are some class related to abi in TS SDK.

```
class AbiInfo {
    hash : string
    entrypoint : string
    functions : Array<AbiFunction>
}
```

```hash``` hash value of the contract. Also called contract address. It can be used to distinguish each contract.

```entrypoint``` the entry function name of the contract.

```functions```  the set of functions that the contract contains.

```
class AbiFunction {
    name : string
    returntype : string
    parameters : Array<Parameter>
}
```

```name``` name of the function.

```returntype``` the return type of the function.

```parameters``` the parameters of the function.

```
class Parameter {
    name : string
    type : ParameterType
    value : any
}
```

```name``` name of the parameter.

```type```  type of the parameter.

```value```  value of the parameter.

The function that constructs transaction to invoke contract needs parameters as follow:

````
function makeInvokeTransaction(funcName : string, parameters : Array<Parameter>, contractHash : string, vmType : VmType = VmType.NEOVM, fees : Array<Fee> = [])
````

```funcName``` the function to be called in the contract.

```parameters``` the parameters of the function.

```contractHash``` the hash of the contract.

```vmType``` the virtual machine type.

```fees``` the fees required to send transaction.

Here is a example about invoking ONT ID smart contract to register ONT ID.

```
//read abi file. Here the file exports a JSON object.
import abiJson from '../smartcontract/data/idContract.abi'

//parse the abi content
const abiInfo = AbiInfo.parseJson(JSON.stringify(abiJson))

//get the AbiFunction
const abiFunction = abiInfo.getFunction('RegIdWithPublicKey')

const privateKey = '7c47df9664e7db85c1308c080f398400cb24283f5d922e76b478b5429e821b95'
const publicKey = '1202037fa2bbad721197da4f2882e4f8e4ef6a77dbc7cfbd72267cdd72dd60ac30b41e'
const ontid = '6469643a6f6e743a544d7876617353794747486e7574674d67657158443556713265706b6a476f737951'

//construct parameters. Notice that all the parameters are hex string here.
let p1 = new Parameter(f.parameters[0].getName(), ParameterType.ByteArray, ontid)
let p2 = new Parameter(f.parameters[1].getName(), ParameterType.ByteArray, publicKey)

//set parameters
abiFunction.setParasValue(p1, p2)

//construct transaction
let fees = []
let vmType = VmType.NEOVM
let tx = makeInvokeTransaction(abiFunction.name, abiFunction.parameters, abiInfo.hash, vmType, fees)

//sign the transaction.
signTransaction(tx, privateKey)
```

### 2.2 Construct transactions based on WASM vm

This process is mostly the same as above. Though we do not have abi files. We can use the same method as long as we can offer the exact function name and parameters.

````
const codeHash = '9007be541a1aef3d566aa219a74ef16e71644715'
const params = [
		new Parameter('p1', ParameterType.Int, 20), 
		new Parameter('p2', ParameterType.Int, 30)
	]
const funcName = 'add'
let tx = makeInvokeTransaction(funcName, params, codeHash, VmType.WASMVM)
````

### 2.3 Send transactions

There are multiple ways to send transactions.

#### 2.3.1 Restful

```
//use the wrapped class
let restClient = new RestClient()
//use the transaction created before to build parameters
restClient.sendRawTransaction(tx.serialize()).then(res => {
    console.log(res)
})
```

The response of the request contains the hash of the transaction. We need to query the execution result of invoking the contract with the hash. A simple way is to query the result on [Ontology's blockchain browser](https://explorer.ont.io/).

#### 2.3.2 Rpc

```
let rpcClient = new RpcClient()
rpcClient.sendRawTransaction(tx.serialize()).then(res => {
    console.log(res)
})
```

Rpc request is similar to Restful request.  The response is also the transaction hash.

#### 2.3.3 Websocket

We can use websocket to send transactions and listen to the messages. Notifications will be sent back if there are event push definitions in the contract.

```
let param = buildTxParam(tx)
let txSender = new TxSender(TEST_ONT_URL.SOCKET_URL)
//define the callback
//@param err : error result
//@param res : messages pushed from blockchain
//@param socket websocket object
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
```
