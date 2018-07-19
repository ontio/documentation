---
title:
keywords: sample homepage
sidebar: Dapp_en
permalink: Smart_Contract_Invocation_en.html
folder: doc_en/Dapp
giturl: https://github.com/ontio/ontology-smartcontract/blob/master/smart-contract-tutorial/Smart_Contract_Invocation.md
---

<h1 align="center">Smart Contract Invocation</h1>

<p align="center" class="version">Version 1.0.0 </p>

English / [中文](./Smart_Contract_Invocation_zh.html)

## 1. Construct a transaction

When a smart contract is deployed on the blockchain, we can construct a transaction to invoke a contract's method.

Before constructing a transaction, we need to know the contract's abi file and the hash address of the contract.

### What is an abi file

After a smart contract is written, the developer will use the corresponding compiler to compile the contract. After the compilation, the abi file and avm file will be generated. The avm file is the bytecode of the contract. When the contract is deployed on the blockchain, the contract bytecode is stored in the storage area allocated to the contract. The abi file is a JSON file that describes the specific structure of a contract, including the entry function, the interface functions, the parameter list of functions, the return value and events. From contract's abi file, we can learn about the detailed features of the contract.

Using SmartX as an example, we have a template contract "Arith" that can do simple addition calculation. After the contract is compiled, the abi content in JSON format will be displayed on the operation panel. Users can choose to download the abi.json file.

![](http://wx2.sinaimg.cn/mw690/0060lm7Tly1fsqydcu9nzj30ep09udg9.jpg)

### What is a contract hash?

A contract hash is a value obtained by performing some hash operations on the avm content of the contract. This unique value is used to distinguish different contracts. An abi file also contains contract hash.

### Construct a transaction by SDK

We can easily construct a transaction through the SDK. Using TS SDK as an example. The contract we want to invoke is the template contract "Arith", and the method to be invoked is "Add" function of the contract.

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

Now we follow the above steps to construct a transaction object. During the construction process, the method name and method parameters need to be consistent with the description in the abi file; otherwise, an error will occur.

Generally, executing a smart contract needs to consume gas. Therefore, gasPrice and gasLimit must be set in the transaction object. If these two values are too small, the transaction will not be packed into the block and the contract method will fail to execute. In the current TestNet, gasPrice is allowed to be set to 0, that is, it does not need to consume gas. In the MainNet, a certain amount of gas is needed  to ensure that the contract is properly invoked.

A correct transaction also requires a signature before it is sent to the blockchain for execution. Suppose now we have account and private key.

````
//assume we have an account and the private key
tx.payer = account.address;
signTransaction(tx, privateKey);
````

Now the signed transaction can be sent to the blockchain for execution.

## 2. Send a transaction

We have multiple ways to send transaction:

1. Send a transaction via the rpc interface
2. Send a transactions via the restful interface
3. Send a transactions via the websocket

Sending a transaction through the rpc and restful interfaces, the result returned is the status of the transaction and the transaction hash;

Sending a transaction through websocket, if the contract method has event pushes, it can listen for pushed messages, which are usually the result of contract execution.

We can also send a pre-executed transaction to the blockchain through the above interface. Pre-execution means that the transaction only runs on the node that received the transaction, and the result of the execution can be obtained directly from this node instead of result after blockchain consensus. By pre-executing the transaction, it can easily verify whether the transaction is constructed correctly and the gas is expected to consume.

We use the restful interface of the TS SDK as an example to show how to send a transaction.

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

## 3. Get the transaction result

In the previous step, we sent the transaction to the blockchain via the restful interface. The results returned are as follows:

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

The value of the Result field is the transaction hash. We can query the execution result of the transaction through the restful interface.

````
import {RestClient} from 'Ont'
const client = new RestClient();
client.getSmartCodeEvent('886b2cd35af7ea65e502077b70966652f4cf281244868814b8f3b2cf82776214').then(res => {
console.log(res)
})
````

We can query the execution result of the transaction through the restful interface of the TS SDK, or query it through web tools such as postman. The query url is as follows:

````
http://{{NODE_URL}}/api/v1/smartcode/event/txhash/03295a1b38573f3a40cf75ae2bdda7e7fb5536f067ff5e47de44aeaf5447259b
````

The NODE_URL can be either a TestNet node or a local node.

The result of the query is as follows:

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

By observing the data in the results, you can judge whether the transaction is executed successfully.

```State``` is equal to 1 indicating successful execution and equal to 0 indicating failure.

````Notify```` is a message push in the execution of a contract method.

