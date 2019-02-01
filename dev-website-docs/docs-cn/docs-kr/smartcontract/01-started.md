
## Smart Contract Deployment

Before deploying a contract, the developer needs to prepare the contract that has been properly compiled as an .avm file.

The developer also needs Ontology's wallet account and guarantees that there are enough ONGs on the account to pay for the contract deployment.

Currently, the gasprice can be set to 500 for deploying contracts on the test network.

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


## Smart Contract Invocation

### 1. Construct a transaction

When a smart contract is deployed on the blockchain, we can construct a transaction to invoke a contract's method.

Before constructing a transaction, we need to know the contract's abi file and the hash address of the contract.

#### What is an abi file

After a smart contract is written, the developer will use the corresponding compiler to compile the contract. After the compilation, the abi file and avm file will be generated. The avm file is the bytecode of the contract. When the contract is deployed on the blockchain, the contract bytecode is stored in the storage area allocated to the contract. The abi file is a JSON file that describes the specific structure of a contract, including the entry function, the interface functions, the parameter list of functions, the return value and events. From contract's abi file, we can learn about the detailed features of the contract.

Using SmartX as an example, we have a template contract "Arith" that can do simple addition calculation. After the contract is compiled, the abi content in JSON format will be displayed on the operation panel. Users can choose to download the abi.json file.

![](http://wx2.sinaimg.cn/mw690/0060lm7Tly1fsqydcu9nzj30ep09udg9.jpg)

#### What is a contract hash?

A contract hash is a value obtained by performing some hash operations on the avm content of the contract. This unique value is used to distinguish different contracts. An abi file also contains contract hash.

#### Construct a transaction by SDK

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

### 2. Send a transaction

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

### 3. Get the transaction result

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

