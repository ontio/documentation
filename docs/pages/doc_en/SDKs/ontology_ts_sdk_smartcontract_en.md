---
title:
keywords: sample homepage
sidebar: SDKs_en
permalink: ontology_ts_sdk_smartcontract_en.html
folder: doc_en/SDKs
giturl: https://github.com/ontio/ontology-ts-sdk/master/docs/en/smart_contract.md
---

[中文](./ontology_ts_sdk_smartcontract_zh.html) | English

<h1 align="center">Deploy & invoke smart contract</h1>
<h4 align="center">Version V0.9.0 </h4>
<h1 align="center">Deploy and invoke smart contract</h1>

<p align="center" class="version">Version 1.0.0 </p>



## 1. Deploy smart contract

This process needs to construct related transaction and send it to the blockchain.

Users should offer the contract's content in hex string and some configuration parameters to construct the transaction.


The configuration parameters are as follow:

```code``` Avm code of contract's content，hex encoded string。

```name ``` name of the contract, optional string value.

```codeVersion``` version of  the contract, optional string value.

```author``` author of the contract, optional string value.

```email``` email of the contract's author, optional string value.

```desp``` description of the contract, optional string value.

```needStorage``` the contract needs storage or not. Default as true.

```typescript
import {TransactionBuilder, RestClient} from 'ontology-ts-sdk';

const code = '5ac56b6c766b00527ac46c766b51527ac4616c766b00c303507......';
const name = 'Test';
const codeVersion = '1.0';
const author = 'Jack';
const email = 'jack@ont.com';
const desp = 'test';
const needStorage = true;
const gasPrice = '500';
const gasLimit = '3000000';
const tx = TransactionBuilder.makeDeployCodeTransaction(code, name, codeVersion, author, email,desp,needStorage, gasPrice, gasLimit);

//we need add payer's address and sign the transaction
//suppose we have the account and private key
tx.payer = account.address;
TransactionBuilder.signTransaction(tx, privateKey)

//Then send the transaction
const rest = new RestClient();
rest.sendRawTransaction(tx.serialize()).then(res => {
	console.log(res)
//query the contract from blockchain.
	rest.getContract(res.Result).then(result => {
		console.log(result)
	})
})



```

## 2. Invoke smart contract
Invoking contract needs to construct related transaction and send it to the blockchain.

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

Here is a example about invoking a smart contract for attest claim record to the blockchain.

```
//read abi file. Here the file exports a JSON object.
import abiJson from '../smartcontract/data/attestClaim.ts'
import {utils, TransactionBuilder, RestClient} from 'ontology-ts-sdk'

//parse the abi content
const abiInfo = AbiInfo.parseJson(JSON.stringify(abiJson))

//get the AbiFunction
const abiFunction = abiInfo.getFunction('Commit')

const claimId = 'claim123';
const issuer = 'did:ont:ALnvzTMkbanffAKzQwxJ3EGoBqYuR6WqcG';
const subject = 'did:ont:AUG62qrHboRc4oNn8SvJ31ha6BkwLPKvvG';

//construct parameters. Notice that all the parameters are hex string here.
let p1 = new Parameter(f.parameters[0].getName(), ParameterType.ByteArray, utils.str2hexstr(claimId))
let p2 = new Parameter(f.parameters[1].getName(), ParameterType.ByteArray,utils.str2hexstr(issuer))
let p3 = new Parameter(f.parameters[2].getName(), ParameterType.ByteArray,utils.str2hexstr(subject))

//set parameters
abiFunction.setParasValue(p1, p2, p3)

//construct transaction
const gasPrice = '500';
const gasLimit = '20000';
//we need to know the contract's address, it can be the reversed value of hash in abiInfo
const hash = abiInfo.getHash().replace('0x', '');
const contractAddr = new Address(utils.reverseHex(hash));
let tx = Transactoinbuilder.makeInvokeTransaction(abiFunction.name, abiFunction.parameters, contractAddr, gasPrice, gasLimit)

//add payer to pay for gas.Suppose we have an account with enough balance
tx.payer = account.address;

//sign the transaction.
signTransaction(tx, privateKey)

//Send transaction
const rest = new RestClient();
rest.sendRawTransaction(tx.serialize()).then(res => {
	console.log(res)
})

```


