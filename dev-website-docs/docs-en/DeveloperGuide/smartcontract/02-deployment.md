<h1 align="center">Smart Contract Deployment</h1>

<p align="center" class="version">Version 1.0.0 </p>


## Preparation

Before deploying a contract, the developer needs to prepare the contract that has been properly compiled as an .avm file.

The developer also needs Ontology's wallet account and guarantees that there are enough ONGs on the account to pay for the contract deployment.

Currently, the cost can be set to 0 for deploying contracts on the test network.

## How to deploy

Contract deployment require users to build specific transactions and send them to the blockchain for execution. When the execution of the transaction is completed, the contract is deployed.

Ontology provides different SDK and contract development tools SmartX to help users deploy contracts.

## Calculate the gas consumed by deploying a smart contract

Through the pre-execution to a smart contract, the `Gaslimit` required for the current contract execution can be obtained, which provides a reference for `Gaslimit` setting in real execution and avoids execution failure due to insufficient **ONG** balance.

```
$ ./ontology contract invoke --address 79102ef95cf75cab8e7f9a583c9d2b2b16fbce70 --params string:Hello,[string:Hello] --prepare --return bool
Invoke:70cefb162b2b9d3c589a7f8eab5cf75cf92e1079 Params:["Hello",["Hello"]]
Contract invoke successfully
  Gaslimit:20000
  Return:true
```

## Contract deployment by SDK

Ontology provides different SDKs. Here we use the [Typescript SDK](https://github.com/ontio/ontology-ts-sdk)as an example to illustrate the process of deploying a contract.

TS SDK provides the interface for deploying a contract. The parameters of the interface are as follows:

```avmCode``` contract's avm code, required parameter 

```name``` contract's name. Optional parameter. The default value is an empty string.

```version``` contract's version. Optional parameter. The default value is an empty string.

```author``` contract's author. Optional parameter. The default value is an empty string.

```email``` the email of the contract's author. Optional parameter. The default value is an empty string.

```desc``` the description of contract. Optional parameter. The default value is an empty string.

```needStorage``` Whether the contract needs to be stored. Optional value. The default value is true.

```gasPrice``` the gas price for contract deployment. Required value. If this value is too small, the transaction will fail to execute.

```gasLimit``` the gas limit for contract deployment. Required value. If this value is too small, the transaction will fail to execute.

```payer``` The account address that pays deployment fee. Required value.

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

After constructing the transaction object according to the above steps, it is necessary to send the transaction to the blockchain. There are many ways to send transactions. For more information, please refer to [How to invoke a contract](./Smart_Contract_Invocation.md).

Here we use the method in the TS SDK as an example to illustrate the process of sending a transaction.

````
import { RestClient } from 'Ont''
const restClient = new RestClient('http://polaris1.ont.io');
restClient.sendRawTransaction(tx.serialize()).then(res => {
	console.log(res);
})
````

The result returned by this request is as follows:

````
{
"Action": "sendrawtransaction",
"Desc": "SUCCESS",
"Error": 0,
"Result": "70b81e1594afef4bb0131602922c28f47273e1103e389441a2e18ead344f4bd0",
"Version": "1.0.0"
}
````

```Result``` is the hash of this transaction, which can be used to query whether the transaction is successfully executed.

We can also query the execution result of the transaction via the restful interface.

````
restClient.getSmartCodeEvent('70b81e1594afef4bb0131602922c28f47273e1103e389441a2e18ead344f4bd0').then(res => {
	console.log(res);
})
````

The result returned by this request is as follows:

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

When the ```State``` value is 1, it means that the transaction execution is successful, that is, the contract is deployed successfully; when the value is 0, the transaction execution fails, that is, the contract deployment fails.

In addition, we can also check whether there is a contract on the blockchain by the contract hash. The contract hash value is calculated by hash operation of
the contract avm content.

Suppose we know that the hash value of the contract is **bcb08a0977ed986612c29cc9a7cbf92c6bd66d86**.

````
restClient.getContract('bcb08a0977ed986612c29cc9a7cbf92c6bd66d86').then(res => {
	console.log(res)
})
````

If the request returns the avm content of the contract, the contract has been successfully deployed to the blockchain.

## Contract deployment by SmartX

[SmartX](http://smartx.ont.io) is a one-stop tool for developers to write, deploy, and invoke smart contracts.
For specific instructions, please refer to [smart document](https://github.com/ontio/ontology-smartcontract/blob/master/smart-contract-tutorial/SmartX_Tutorial.md).


First, we need to compile the contract on SmartX. When the contract is successfully compiled, the next step is to deploy the contract.


<p>
  <img width="300px" src="http://wx1.sinaimg.cn/mw690/0060lm7Tly1fss9ydpl3ij30f90m840c.jpg">
  <img width="300px" src="http://wx2.sinaimg.cn/mw690/0060lm7Tly1fss9v7mp42j30ex0m5t9z.jpg">
</p>

In testing network, SmartX provides a default account to pay for the fee of contract deployment and sign the transaction.

SmartX deploys the contract for us by clicking the "Deploy" button.

