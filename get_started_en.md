
English / [中文](./get_started_cn.md)

<h1 align="center">Ontology Developer Guide</h1>

<p align="center" class="version">Version 1.0.0 </p> 

Ontology is a new generation high-performance public blockchain. After its MainNet release, many excellent developers have joined the Ontology technical community. For developers, these documents are an entry to the Ontology ecosystem, therefore, a perfect documentation system can greatly improve the development efficiency. Through the documentation, developers will have a clear understanding of Ontology's technology and ecosystem. This document is an overview of the Ontology Documentation Center and provides an introduction of each section, which help developers familiarize with Ontology quickly.

- [Ontology](#ontology)
    - [What is Ontology](#what-is-ontology)
    - [How to get Ontology](#how-to-get-ontology)
    - [The introduction of Ontology node](#the-introduction-of-ontology-node)
        - [Synchronization node](#synchronization-node)
        - [Consensus node](#consensus-node)
    - [Ontology consensus mechanism](#ontology-consensus-mechanism)
    - [Connect to ontology](#connect-to-ontology)
    - [Ontology special features](#ontology-special-features)
        - [Ontology DID](#ontology-did)
        - [Distributed data transaction](#distributed-data-transaction)
- [How to interact with Ontology](#how-to-interact-with-ontology)
    - [Ontology command line tool](#ontology-command-line-tool)
    - [Ontology signature server](#ontology-signature-server)
    - [Ontology API](#ontology-api)
    - [Ontology SDK](#ontology-sdk)
- [Ontology smart contract](#ontology-smart-contract)
    - [Ontology smart contract IDE--SmartX](#ontology-smart-contract-ide--smartx)
    - [How to write a smart contract](#how-to-write-a-smart-contract)
    - [Contract deployment and invocation](#contract-deployment-and-invocation)
    - [Authority management of smart contract](#authority-management-of-smart-contract)
- [Use Ontology](#use-ontology)
    - [Environmental deployment](#environmental-deployment)
    - [Contract writing, deployment and invocation](#contract-writing-deployment-and-invocation)
    - [Development DAPP tutorial](#development-dapp-tutorial)
    - [Wallet intergration tutorial](#wallet-intergration-tutorial)

## Ontology

### What is Ontology

The features of Ontology are outlined in [Ontology Features](https://github.com/ontio/ontology/blob/master/docs/specifications/features.md). 

### How to get Ontology

At present, all of Ontology's source code are open source on GitHub. Users can go to the [GitHub Repository](https://github.com/ontio/ontology) to download the source code and compile it. Users can download latest ontology binary file with `curl  https://dev.ont.io/ontology_install | sh`.or directly download other vesion at  [Release Version](https://github.com/ontio/ontology/releases). For detailed download and installation instructions, please refer to [Ontology Installation Instructions](https://ontio.github.io/documentation/install_en.html).

### The introduction of Ontology node

After installing Ontology, you can run Ontology locally and connect it to the Ontology network. 

Before that, you need to know the node types in the current Ontology network.

The network nodes of Ontology are currently divided into two categories: consensus nodes and synchronization nodes.

The consensus nodes participate in the consensus, package the transaction and generate the block;

The synchronization nodes synchronize the latest block and do not participate in the consensus.

#### Synchronization node

The synchronization node can be connected to the MainNet, or the public testing network. When connecting to a different network, the node will synchronize the information and create two folders in the current directory: Chain and Log. The Chain folder will store the synchronized block data, including all transaction data, account data, etc.; Log will store the log information generated when the data is synchronized.

#### Consensus node

The consensus node is similar to the synchronization node and can run on the MainNet, the testing network. The Chain and Log folders will be generated in the running. The difference is that the consensus node itself will package the transaction information to generate the block, which is impossible for the synchronization node.

### Ontology consensus mechanism

After understanding the type of Ontology network node, we will introduce the consensus mechanism of the Ontology network next. Ontology has already supported the DBFT and VBFT consensus. Now, both the MainNet and the testing network use the VBFT consensus.

[VBFT Introduction](https://ontio.github.io/documentation/vbft_intro_en.html) is an introduction to the VBFT consensus network. For more detailed information, please refer to the source code repository of Ontology.

### Connect to ontology

Now, we can try to connect to Ontology network. [Run ontology](https://github.com/ontio/ontology/blob/master/README.md#run-ontology) will introduce how to connect ontology network and how to start ontology in test mode.

### Ontology special features

#### Ontology DID

Ontology DID（also called ONT ID) is a decentralized identity identification protocol based on the W3C DID specification. A detailed introduction can be found in [Ontology Distributed Identity Framework (ONTID)](https://ontio.github.io/documentation/ontology_DID_en.html).

#### Distributed data transaction

In view of the pain points of the current centralized data exchange such as data cache, privacy data usage without user authorization, and data copyright protection, Ontology proposes a distributed data management protocol ONT DATA. And based on this protocol, Ontology launched the decentralized data transaction framework DDXF. For more details, please refer to [Distributed Data Exchange Framework](https://ontio.github.io/documentation/DDXF_en.html).


## How to interact with Ontology

### Ontology command line tool

You may use a lot of command line parameters when building an Ontology network. For more detailed information about these parameters, please refer to [Ontology CLI User Guide](https://ontio.github.io/documentation/cli_user_guide_en.html). These command line parameters are also executed through the Ontology CLI tool. The CLI can execute and invoke most of the functions of the ontology network, which is the first entry of the Ontology network. In addition to the documentation, you can get a brief description of the command line parameters by executing `./ontology --help`.

### Ontology signature server

In order to adapt to more needs, Ontology provides a service called a signature machine. The service uses the specified wallet to sign the transaction sent to the service. For details, please refer to [Ontology Signature Server Tutorials](https://ontio.github.io/documentation/sigsvr_en.html).

### Ontology API

In addition to the command line, Ontology provides a more convenient blockchain interaction interface. These interfaces are provided in the form of APIs. The current Ontology API contains: [RPC API](https://ontio.github.io/documentation/rpc_api_en.html), 
[Restful API](https://ontio.github.io/documentation/restful_api_en.html), [Websocket API](https://ontio.github.io/documentation/websocket_api_en.html).

By these APIs, developers can easily send transactions and query data through the Ontology network.

### Ontology SDK

For developers, the SDK is a tool invoked directly in the program. Currently, Ontology provides three sets of SDKs for developers to use, [Java SDK](https://ontio.github.io/documentation/ontology_java_sdk_en.html), [Typescript SDK](https://ontio.github.io/documentation/ontology_ts_sdk_en.html), and [Golang SDK](https://github.com/ontio/ontology-go-sdk). 

Before using the SDK, it is recommended to read the [Overview of the SDK](https://ontio.github.io/documentation/ontology_overview_sdks_en.html) and the [Wallet File Specification](https://ontio.github.io/documentation/Wallet_File_Specification_en.html).


## Ontology smart contract

Smart contract are the most important function of the current blockchain, and Ontology also has its own smart contract system. For details, please refer to [Introduction of Ontology Smart Contract](https://ontio.github.io/documentation/Introduction_of_Ontology_Smart_Contract_en.html).

### Ontology smart contract IDE--SmartX

SmartX is a one-stop smart contract writing tool launched by Ontology. It integrates functions such as writing, compiling, deploying and debugging, which greatly improve the development efficiency of smart contract. Please refer to [SmartX Tutorial](https://ontio.github.io/documentation/SmartX_Tutorial_en.html) for how to use SmartX.

### How to write a smart contract

Here is an example of a simple smart contract - [Hello World](https://ontio.github.io/documentation/The_Hello_World_Contract_en.html)

In the process of writing a smart contract, many smart contract APIs should be invoked. For introductions of APIs, please refer to [API of Smart Contract](https://apidoc.ont.io/smartcontract/).

### Contract deployment and invocation

Although SmartX provides a one-click deployment and invocation method, there are other ways to implement contract deployment and invocation. The deployment method can be referred to [Smart Contract Deployment](https://ontio.github.io/documentation/Smart_Contract_Deployment_en.html). The invocation method can be referred to [Smart Contract Invocation](https://ontio.github.io/documentation/Smart_Contract_Invocation_en.html).

### Authority management of smart contract

Currently, the functions of a smart contract can be invoked by anyone, which obviously does not meet the actual requirements. The basic idea of ​​role-based authority management is that each role can call a partial function, and each entity can be assigned multiple roles (the entity is identified by its ONT ID). [Ontology Authority manager](https://ontio.github.io/documentation/auth_en.html) introduces authority management methods for Ontology smart contracts.


## Use Ontology

After a full understanding of Ontology, a simple example is introduced to describe how to develop on the Ontology network.

### Environmental deployment

A. Set up your own test network as described in [Connect to ontology](#connect-to-ontology). You can run ontology in test mode. Of course, you can also choose to connect to the Ontology's public testing network called Polaris.

The next step will take the test mode as an example.

B. Use the command `./ontology --rest --ws --localrpc --gaslimit 20000 --gasprice 0 --testmode --networkid 3` to start the testing network and enter the wallet account password.

C. Use the rest interface to query the balance of the initial account (the biller in solo mode).

* Enter `http://localhost:20334/api/v1/balance/APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh` in your browser. `localhost` is the IP address of node，`20334` is the default rest port，and this port can also be specified by yourself, the command is `--rest --restport 20339`；`api/v1/balance/` is the URL path of the rest interface and `APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh` is the address of the initial biller. This entire URL constitutes the rest interface call method for the balance query.

* The browser returns a response `{"Action":"getbalance","Desc":"SUCCESS","Error":0,"Result":{"ont":"1000000000","ong":"0"},"Version":"1.0.0"}`，which is a response string in json format. You can see there are 1000000000 ONT and 0 ONG.

D. In the Ontology network, almost all operations need to consume gas, ie ong. In this example, the `--gasprice 0` parameter is set to be 0 at startup, so subsequent operations do not consume any gas. But you can still pay for gas. This step will demonstrate how to extract ONG from your account.

* ONG is the associated fuel of ONT, which is gradually released with ONT, but it needs to be manually extracted into your own account;

* Use `./ontology asset unboundong 1` to query the number of ONGs that can be extracted. You can use `./ontology asset --help`to learn more details.

```
Unbound ONG:
Account:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh
ONG:0
```

 * The reason why the number of ONGs that can be extracted at this time is zero is the account has not activated the release of ONG. You can use transfer method to activate it;

* Use `./ontology account add -d`  to create another Ontology account. The address is `AGrJQhb7bZsy57MoQk6YDt3hDP7zRioHia`. Use `./ontology account list`  to query the account status of the default wallet;

```
Index:1    Address:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh  Label: (default)
Index:2    Address:AGrJQhb7bZsy57MoQk6YDt3hDP7zRioHia  Label:
```

* Use `./ontology asset transfer --from 1 --to 2 --amount 100000000` command to transfer 100 million ONT from Account 1 to Account 2. After entering the Password 1, the transfer is successful;

```
Transfer ONT
From:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh
To:AGrJQhb7bZsy57MoQk6YDt3hDP7zRioHia
Amount:100000000
TxHash:73a3d24b7dfd0d96b23f93fd38afe4638b70f921c278202443d0dd29a036236f

Tip:
Using './ontology info status 73a3d24b7dfd0d96b23f93fd38afe4638b70f921c278202443d0dd29a036236f' to query transaction status
```

* Check the balance of Account 1 and Account 2 by the command line that is `./ontology asset balance 1` and `./ontology asset balance 2`：

```
BalanceOf:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh
ONT:900000000
ONG:0

BalanceOf:AGrJQhb7bZsy57MoQk6YDt3hDP7zRioHia
ONT:100000000
ONG:0
```

* Use `./ontology asset unboundong 1`  again to query the number of ONGs that can be extracted by Account 1. You can find that the number of extractable ONG is greater than 0 (in actual execution, this amount is affected by the block height and the amount transferred out):

```
Unbound ONG:
Account:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh
ONG:5242930
```

* Use the `./ontology asset withdrawong 1` command to extract ONG of Account 1 after entering password:

```
Withdraw ONG:
Account:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh
Amount:5242930
TxHash:6e10592e52cb7a3645eecd987c0161a8811f25ed5e183614d0e9cd9c58ab8a33

Tip:
Using './ontology info status 6e10592e52cb7a3645eecd987c0161a8811f25ed5e183614d0e9cd9c58ab8a33' to query transaction status
```

* Use the command line to check the balance of Account 1, and you can see that there are ONGs in the account:

```
BalanceOf:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh
ONT:900000000
ONG:5242930
```

### Contract writing, deployment and invocation

A. Open [Ontology smart contract IDE--SmartX](#ontology-smart-contract-ide--smartx), and write a Hello World smart contract according to [How to Write a Smart Contract](#how-to-write-a-smart-contract). For the convenience of calling, we change the contract code to the following form and then compile it into AVM bytecode, download the AVM bytecode and name it `hello.avm`:

```
using Neo.SmartContract.Framework.Services.Neo;
using Neo.SmartContract.Framework;
using System;
using System.ComponentModel;

namespace Neo.SmartContract
{
public class HelloWorld : Framework.SmartContract
{
public static object Main(string operation, params object[] args)
{
switch (operation)
{
case "Hello":
Hello((string)args[0]);
return true;
default:
return false;
}
}
public static void Hello(string msg)
{
Runtime.Notify(msg);
}
}
}
```

> Description: In the Hello method, Runtime.Notify will make a notification on the chain for the passed parameters.


B. Use the command `./ontology contract deploy --code hello.avm --name 'Hello' --version '1.0' --author 'ester' --email 'tester@test.com' --desc 'helloworld' --account 1 --gaslimit 100000000` to deploy the contract on the network. The contract deployment command can be obtained using `./ontology contract deploy -h`;


```
Deploy contract:
Contract Address:362cb5608b3eca61d4846591ebb49688900fedd0
TxHash:c49865b16009177ed4b06add97f7be1b0b1c246e4d4575c367e918da294d3287

Tip:
Using './ontology info status c49865b16009177ed4b06add97f7be1b0b1c246e4d4575c367e918da294d3287' to query transaction status
```

C. Enter `http://localhost:20334/api/v1/contract/362cb5608b3eca61d4846591ebb49688900fedd0`  in the browser and call the rest interface to query the contract information:

```
{"Action":"getcontract","Desc":"SUCCESS","Error":0,"Result":{"Code":"54c56b6c7...","NeedStorage":false,"Name":"Hello","CodeVersion":"1.0","Author":"ester","Email":
"tester@test.com","Description":"helloworld"},"Version":"1.0.0"}
```

D. Use the command `./ontology contract invoke --address 362cb5608b3eca61d4846591ebb49688900fedd0 --params string:Hello,[string:tester] --gaslimit 200000` to invoke the contract：

```
Invoke:d0ed0f908896b4eb916584d461ca3e8b60b52c36 Params:["Hello",["tester"]]
Password:
TxHash:2cc94de8c26fce3be233bef007ec3492043ffc304b79a02d9b612df96e950186

Tip:
Using './ontology info status 2cc94de8c26fce3be233bef007ec3492043ffc304b79a02d9b612df96e950186' to query transaction status
```

>Description: `--params string:Hello,[string:tester]` specifies the parameters passed in the call contract. Here are two parameters, `string:Hello` and `[string:tester]`. The argument is the argument passed to the main function in the contract code.

E. Use the command`./ontology info status 2cc94de8c26fce3be233bef007ec3492043ffc304b79a02d9b612df96e950186` to query the transaction status as prompted:

```
Transaction states:
{
"TxHash": "2cc94de8c26fce3be233bef007ec3492043ffc304b79a02d9b612df96e950186",
"State": 1,
"GasConsumed": 0,
"Notify": [
{
"ContractAddress": "362cb5608b3eca61d4846591ebb49688900fedd0",
"States": [
"746573746572"
]
}
]
}
```

F. In the returned result, States is the message information of the call contract notification. The returned value is a hexadecimal string. After conversion by the transcoder, the result is `tester`.


### Development DAPP tutorial

This tutorial will take you through the process of building your first dapp.[Tutorial](https://ontio.github.io/documentation/ontology_dapp_dev_tutorial_en.html)

### Wallet intergration tutorial

This tutorial will take you through the process of intergration ONT/ONG in your wallet.[Android](https://ontio.github.io/documentation/ontology_wallet_dev_android_en.html) and [IOS](https://ontio.github.io/documentation/ontology_wallet_dev_js_en.html)