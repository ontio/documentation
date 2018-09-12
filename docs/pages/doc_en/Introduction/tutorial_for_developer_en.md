---
title:
keywords: sample homepage
sidebar: Introduction_en
permalink: tutorial_for_developer_en.html
folder: doc_en/Introduction
giturl: https://github.com/ontio/documentation/blob/master/get_started_en.md
---


English / [中文](./tutorial_for_developer_zh.html)

<h1 align="center">Ontology Developer Guide</h1>

<p align="center" class="version">Version 1.0.0 </p> 

Ontology is a new generation of high-performance public blockchains. The infrastructure is scalable, stable and allow low level customization for different business requirements. After Ontology MainNet release, we have welcomed many new developers to the Ontology technical community and launched our [Developer Center ](https://bounty.ont.io/index.php/index/developer) 

This documentation is an entry to the Ontology ecosystem for new Ontology developers as well as experienced. The Ontology community and Ontology core team maintain the documentation - we welcome you to help us with this! The documentation serves the purpose of providing a a clear understanding of Ontology's technology and ecosystem. This document is an overview of the Ontology documentation center and provides an introduction of each section, which help developers familiarize themselves with Ontology quickly.

- [Ontology](#ontology)
    - [What is Ontology](#what-is-ontology)
    - [How to get and install Ontology](#how-to-get-and-install-ontology)
    - [Introduction of the Ontology nodes](#introduction-of-the-ontology-nodes)
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
    - [Environment setup](#environment-setup)
    - [Contract writing, deployment and invocation](#contract-writing-deployment-and-invocation)
    - [Development DAPP tutorial](#development-dapp-tutorial)
    - [Wallet intergration tutorial](#wallet-intergration-tutorial)

## Ontology

### What is Ontology

Ontology is an infrastructure that integrates the fragmented industries in order to build a true and complete trust system. It's a platform that bridge the digital world with the real world. From a high-level perspective we can Ontology understand form two views:

<p align="center">Public blockchains with a new architecture (Infrastructure)</p>
Ontology is a new generation of a public chain infrastructure with high-performance (+5000 TPS for Ontology 1.0, 8000-10000 TPS for Ontology 2.0). The open-source framework allow low level customization so that different business requirements and scenarios can be implemented.

<p align="center">A distributed trust collaboration platform</p>
With Ontology organizations, people, objects and communities can engage with each other in a trustful way. The platform links the digital economy with the real economy and support scenarios for e.g. distributed identity services, distributed data exchange and reputation. 

The features of Ontology are outlined in [Ontology Features](https://ontio.github.io/documentation/install_en.html#features). 

### How to get and install Ontology

Ontology's source code is open-source on our [GitHub Repository](https://github.com/ontio/ontology), free to download and compile. You can download the latest Ontology binary file with `curl  https://dev.ont.io/ontology_install | sh`, or directly download the latest version at  [Release Version](https://github.com/ontio/ontology/releases). For detailed download and installation instructions, please refer to [Ontology Installation Instructions](https://ontio.github.io/documentation/install_en.html).

### Introduction of the Ontology nodes

After installing Ontology, you can run Ontology locally and connect it to the Ontology network. Before that, you need to identify the node types which run in the Ontology network. Currently, the network nodes are divided into two categories: synchronization nodes and consensus nodes. The consensus nodes participate in the consensus, package the transaction and generate the block. The synchronization nodes synchronize the latest block and do not participate in the consensus itself.

#### Synchronization node

The synchronization node can connect to MainNet or TestNet. When connecting to a different network, the node will synchronize the information and create two folders in the current directory: Chain and Log. The Chain folder will store the synchronized block data, including all transaction data, account data, etc. The Log will store the log information generated when the data is synchronized.

#### Consensus node

The consensus node is similar to the synchronization node and can run on MainNet and TestNet. The Chain and Log folders will be generated while running the node. The difference is that the consensus node itself will package the transaction information to generate the block, which is not an option for the synchronization node.

### Ontology consensus mechanism

Now that you understand the different types of Ontology network nodes, we will introduce the Ontology network's consensus mechanism VBFT, which is running on MainNet and TestNet. 

VBFT is a new consensus algorithm that combines PoS, VRF (Verifiable Random Function), and BFT. It is the core consensus algorithm of OCE (Ontology Consensus Engine). VBFT can support scalability of consensus groups, through VRF guarantee the randomness and fairness of the consensus population generation, and ensure that state finality can be reached quickly. For further introduction please read [VBFT Introduction](https://ontio.github.io/documentation/vbft_intro_en.html)

For more detailed information, please refer to the source code repository of [Ontology VBFT](https://github.com/ontio/ontology/tree/master/consensus/vbft)

### Connect to ontology

Next, you can try to connect to the Ontology network. [Run ontology](https://github.com/ontio/ontology/blob/master/README.md#run-ontology) will introduce you to how to connect and how to start Ontology in test mode.

### Ontology special features

#### Ontology DID

Ontology DID（also called ONT ID) is a decentralized identity identification protocol based on W3C DID specifications. Please find a detailed introduction here [Ontology Distributed Identity Framework (ONTID)](https://ontio.github.io/documentation/ontology_DID_en.html).

#### Distributed data transaction

The idea of centralized data exchanges face many challenges such as data cache, privacy data usage without user authorization, and data copyright protection. To cope with these challenges Ontology proposes ONT DATA, a distributed data management protocol. Based on ONT DATA, Ontology has launched a decentralized data transaction framework DDXF. For more details, please refer to [Distributed Data Exchange Framework](https://ontio.github.io/documentation/DDXF_en.html).

## How to interact with Ontology

### Ontology command line tool

Developing on Ontology often includes a lot of command line parameters. For detailed information about these parameters, please refer to [Ontology CLI User Guide](https://ontio.github.io/documentation/cli_user_guide_en.html). These command line parameters are also executed through the Ontology CLI tool. The CLI can execute and invoke most of the functions of the ontology network, which is the first entry of the Ontology network. In addition to the documentation, you can get a brief description of the command line parameters by executing `./ontology --help`.

### Ontology signature server

In order to accommodate needs, Ontology provides a service called a signature machine. This service use specified wallets to sign the transaction sent to the service. For details, please refer to [Ontology Signature Server Tutorials](https://ontio.github.io/documentation/sigsvr_en.html).

### Ontology API

In addition to the command line tools, Ontology provides APIs for a more convenient blockchain interaction interface. The current Ontology APIs contains: [RPC API](https://ontio.github.io/documentation/rpc_api_en.html), 
[Restful API](https://ontio.github.io/documentation/restful_api_en.html), [Websocket API](https://ontio.github.io/documentation/websocket_api_en.html).

With these APIs, developers can easily send transactions and query data to the Ontology network.

### Ontology SDK

SDK is a tool that is invoked directly in the program. Currently, Ontology provides three SDKs for developers, [Java SDK](https://ontio.github.io/documentation/ontology_java_sdk_en.html), [Typescript SDK](https://ontio.github.io/documentation/ontology_ts_sdk_en.html), and [Golang SDK](https://github.com/ontio/ontology-go-sdk). 

We recommended to read the [Overview of the SDK](https://ontio.github.io/documentation/ontology_overview_sdks_en.html) and the [Wallet File Specification](https://ontio.github.io/documentation/Wallet_File_Specification_en.html) before using the SDK.


## Ontology smart contract

Smart contract is a very important function of the blockchain and Ontology also has its own smart contract system. Please refer to [Introduction of Ontology Smart Contract](https://ontio.github.io/documentation/Introduction_of_Ontology_Smart_Contract_en.html).

### Ontology smart contract IDE--SmartX

SmartX is a one-stop smart contract tool developed by Ontology. It integrates functions such as writing, compiling, deploying and debugging, which improve the efficiency of smart contract development. Please refer to [SmartX Tutorial](https://ontio.github.io/documentation/SmartX_Tutorial_en.html).

### How to write a smart contract

For a better understand of our smart contract framework we recommend you to try our [Hello World smart contract](https://ontio.github.io/documentation/The_Hello_World_Contract_en.html)

When developing smart contracts, there is a lot of smart contract APIs that must be invoked. For introduction to these APIs, please refer to [API of Smart Contract](https://apidoc.ont.io/smartcontract/).

### Contract deployment and invocation

Although SmartX provides a one-click deployment and invocation method, there are other ways to implement contract deployment and invocation. For deployment method please refer to [Smart Contract Deployment](https://ontio.github.io/documentation/Smart_Contract_Deployment_en.html). For invocation method please refer to [Smart Contract Invocation](https://ontio.github.io/documentation/Smart_Contract_Invocation_en.html).

### Authority management of smart contract

By default, functions of a smart contract can be invoked by anyone, which obviously does not meet the requirements in all cases. The idea of ​​role-based authority management is that each role can call a particular function, and each entity can be assigned multiple roles (the entity is identified by its ONT ID). [Ontology Authority manager](https://ontio.github.io/documentation/auth_en.html) introduces authority management methods for Ontology smart contracts.


## Use Ontology

Now that you have a better understanding of Ontology we can move on to a simple example to explore development on the Ontology network.

### Environment setup

A. Set up your own test network as described in [Connect to ontology](#connect-to-ontology). You can run ontology in test mode or connect to Ontology's public test network called Polaris (TestNet).

The remaining part of this example is performed in test mode!

B. Use the command `./ontology --rest --ws --localrpc --gaslimit 20000 --gasprice 0 --testmode --networkid 3` to start the testing network and enter the wallet account password.

C. Use the REST interface to query the balance of the initial account (the biller in solo mode).

* Enter `http://localhost:20334/api/v1/balance/APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh` in your browser. `localhost` is the IP address of node，`20334` is the default rest port. This port can also be specified by yourself with this command `--rest --restport 20339`, `api/v1/balance/` is the URL path of the rest interface and `APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh` is the address of the initial biller. This entire URL constitutes the rest interface call method for the balance query.

* The browser returns a response `{"Action":"getbalance","Desc":"SUCCESS","Error":0,"Result":{"ont":"1000000000","ong":"0"},"Version":"1.0.0"}`，which is a response string in JSON format. You can see there are 1000000000 ONT and 0 ONG.

D. Almost all operations at the Ontology network will consume ONG (Ontology gas), a.k.a gas (Utility token). In this example, the `--gasprice 0` parameter is set to 0 at startup so subsequent operations do not consume any gas, however you can still pay for gas. Following steps will demonstrate how to extract ONG from your account.

* ONG is the associated gas of ONT, which is gradually released from ONT, but it needs to be manually extracted into your own account;

* Use `./ontology asset unboundong 1` to query the number of ONGs that can be extracted. You can use `./ontology asset --help`to learn more details.

```
Unbound ONG:
Account:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh
ONG:0
```

 * The reason why the number of ONGs that can be extracted at this time is zero is because the account has not activated the release of ONG. You can use below transfer method to activate it;

* Use `./ontology account add -d`  to create another Ontology account. The address is `AGrJQhb7bZsy57MoQk6YDt3hDP7zRioHia`. Use `./ontology account list` to query the account status of the default wallet;

```
Index:1    Address:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh  Label: (default)
Index:2    Address:AGrJQhb7bZsy57MoQk6YDt3hDP7zRioHia  Label:
```

* Use `./ontology asset transfer --from 1 --to 2 --amount 100000000` command to transfer 100 million ONT from Account 1 to Account 2. After entering Password 1, the transfer is successful;

```
Transfer ONT
From:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh
To:AGrJQhb7bZsy57MoQk6YDt3hDP7zRioHia
Amount:100000000
TxHash:73a3d24b7dfd0d96b23f93fd38afe4638b70f921c278202443d0dd29a036236f

Tip:
Using './ontology info status 73a3d24b7dfd0d96b23f93fd38afe4638b70f921c278202443d0dd29a036236f' to query transaction status
```

* Check the balance of Account 1 and Account 2 by the command line `./ontology asset balance 1` and `./ontology asset balance 2`：

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

A. Open [Ontology smart contract IDE--SmartX](#ontology-smart-contract-IDE--SmartX) and use the Hello World smart contract according to [How to Write a Smart Contract](#how-to-write-a-smart-contract). For convenient calling functions of the contract, we change the Hello World contract code to following form and then compile it into AVM bytecode. You can download the AVM bytecode and name it `hello.avm`:

```csharp
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

This tutorial will take you through the process of intergration ONT/ONG in your wallet.[Android](https://ontio.github.io/documentation/ontology_wallet_dev_android_en.html) and [IOS](https://ontio.github.io/documentation/ontology_wallet_dev_ts_sdk_en.html)
