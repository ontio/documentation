# Smart Contract

Smart contract operations support the deployment of NeoVM smart contract, and the pre-execution and execution of NeoVM smart contract.

* [Smart Contract Deployment](#smart-contract-deployment)
* [Smart Contract Execution](#smart-contract-execution)
* [Smart Contract Code Execution Directly](#smart-contract-code-execution-directly)


## Smart Contract Deployment

Before smart deployment, you need to compile the NeoVM contract compiler such as [SmartX](http://smartx.ont.io) and save the compiled code in a local text file.

```
./Ontology contract deploy --name=xxx --code=xxx --author=xxx --desc=xxx --email=xxx --needstore --gaslimit=100000000
```

After deployment, the TxHash of the transaction and the contract address will be returned. For example:

```
Deploy contract:
  Contract Address:806fbee1fcfb554af47844edd4d4ce2918737747
  TxHash:99d719f51837acfa48f9cd2a21983fb993bc8d5a763b497802f7b872be2338fe
```

You can query the contract execution status with the `./Ontology info status <TxHash>` command. If an error such as UNKNOWN TRANSACTION is returned, it means that the transaction has not been posted. The transaction may be queued in the transaction pool to be packaged, or the transaction may be rejected because the gas limit or gas price is set too low.

If the returned execution state - State is equal to 0, it indicates that the transaction execution fails. If State is equal to 1, the transaction execution is successful and the contract deployment is successful. Such as:

```
Transaction states:
{
   "TxHash": "99d719f51837acfa48f9cd2a21983fb993bc8d5a763b497802f7b872be2338fe",
   "State": 1,
   "GasConsumed": 0,
   "Notify": []
}
```

*Parameters:*

#### `--wallet` or `-w`
The wallet parameter specifies the wallet path of account for deploying smart contracts. Default: "./wallet.dat".

#### `--account` or `-a`
The account parameter specifies the account that a contract deploys.

#### `--gasprice`
The gasprice parameter specifies the gas price of the transfer transaction. The gas price of the transaction cannot be less than the lowest gas price set by node's transaction pool, otherwise the transaction will be rejected. The default value is 500 (0 in testmode). When there are transactions that are queued for packing into the block in the transaction pool, the transaction pool will deal with transactions according to the gas price and transactions with high gas prices will be prioritized.

#### `--gaslimit`
The gaslimit parameter specifies the gas limit of the transfer transaction. The gas limit of the transaction cannot be less than the minimum gas limit set by the node's transaction pool, otherwise the transaction will be rejected. Gasprice * gaslimit is actual ONG costs. The default value is 20000.

**For contract deployments, the gaslimit value must be greater than 20000000, and there must be sufficient ONG balance in the account.**

#### `--needstore`
The needstore parameter specifies whether the smart contract needs to use persistent storage. If needed, this parameter is required. The default is not used.

#### `--code`
The code parameter specifies the code path of a smart contract.

#### `--name`
The name parameter specifies the name of a smart contract.

#### `--version`
The version parameter specifies the version number of a smart contract.

#### `--author`
The author parameter specifies the author information of a smart contract.

#### `--email`
The email parameter specifies the contact email of a smart contract.

#### `--desc`
The desc parameter specifies the description of a smart contract.

#### `--prepare` or `-p`
The prepare parameter indicates that the current deploy is a pre-deploy contract. The transactions executed will not be packaged into blocks, nor will they consume any ONG. Via pre-deploy contract, user can known the the gas limit required for the current deploy.


## Smart Contract Execution

The NeoVM smart contract supports the following input argument types:

	array - array of objects, which can nest any number and any type of parameters that NeoVM supports
	bytearray - needs to be hexadecimal encoded into a string, such as []byte("HelloWorld"). : 48656c6c6f576f726c64
	string - a string literal
	int - an integer. The NeoVM virtual machine does not support floating-point values, so it is necessary to convert the floating-point numbers into integers
	bool - true or false.

Parameters will be provided with their type as a prefix, followed by a colon(`:`), and the value. Multiple parameters can be separated by commas.

Input parameters example：

```
string:testMethod,[int:10,string:hello,bool:true]
```

### Smart Contract Read Only Execution (Prepare Invoke Execution)

```
./Ontology contract invoke --address=XXX --params=XXX --return=XXX --p
```
Return example:

```
Contract invoke successfully
Gas consumed:20000
Return:0
```
### Smart Contract Invoke Execution**

```
./Ontology contract invoke --address=XXX --params=XXX --gaslimit=XXX
```

Before the smart contract is executed, the gas limit required by the current execution can be calculated through pre-execution to avoid execution failure due to insufficient ONG balance.

*Parameters:*

#### `--wallet` or `-w`
The wallet parameter specifies the account wallet path for smart contract execution. Default: "./wallet.dat".

#### `--account` or `-a`
The account parameter specifies the account that will execute the contract.

#### `--gasprice`
The gasprice parameter specifies the gas price of the transfer transaction. The gas price of the transaction cannot be less than the lowest gas price set by node's transaction pool, otherwise the transaction will be rejected. The default value is 500 (0 in testmode). When there are transactions that are queued for packing into the block in the transaction pool, the transaction pool will deal with transactions according to the gas price and transactions with high gas prices will be prioritized.

#### `--gaslimit`
The gaslimit parameter specifies the gas limit of the transfer transaction. The gas limit of the transaction cannot be less than the minimum gas limit set by the node's transaction pool, otherwise the transaction will be rejected. Gasprice * gaslimit is actual ONG costs. The default value is 20000.

#### `--address`
The address parameter specifies the calling contract address.

#### `--params`
The params parameter is used to input the parameters of the contract invocation. The input parameters need to be encoded as described above.

#### `--prepare` or `-p`
The prepare parameter indicates that the current execution is a pre-executed contract. The transactions executed will not be packaged into blocks, nor will they consume any ONG. Pre-execution will return the contract method's return value, as well as the gas limit required for the current call.

#### `--return`
The return parameter is used with the --prepare parameter, which parses the return value of the contract by the return type of the --return parameter when the pre-execution is performed, otherwise returns the original value of the contract method call. Multiple return types are separated by "," such as string,int.


## Smart Contract Code Execution Directly

Ontology supports direct execution of smart contact code after deploying a contract.

```
./Ontology contract invokeCode --code=XXX --gaslimit=XXX
```

*Parameters:*

#### `--wallet` or `-w`
The wallet parameter specifies the account wallet path for smart contract execution. Default: "./wallet.dat".

#### `--account` or `-a`
The account parameter specifies the account that will execute the contract.

#### `--gasprice`
The gasprice parameter specifies the gas price of the transfer transaction. The gas price of the transaction cannot be less than the lowest gas price set by node's transaction pool, otherwise the transaction will be rejected. The default value is 500 (0 in testmode). When there are transactions that are queued for packing into the block in the transaction pool, the transaction pool will deal with transactions according to the gas price and transactions with high gas prices will be prioritized.

#### `--gaslimit`
The gaslimit parameter specifies the gas limit of the transfer transaction. The gas limit of the transaction cannot be less than the minimum gas limit set by the node's transaction pool, otherwise the transaction will be rejected. Gasprice * gaslimit is actual ONG costs. The default value is 20000.

#### `--prepare` or `-p`
The prepare parameter indicates that the current execution is a pre-executed contract. The transactions executed will not be packaged into blocks, nor will they consume any ONG. Pre-execution will return the contract method's return value, as well as the gas limit required for the current call.

#### `--code`
The code parameter specifies the code path of a smart contract.
