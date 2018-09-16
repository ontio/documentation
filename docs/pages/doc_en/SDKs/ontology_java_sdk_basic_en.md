---
title:
keywords: sample homepage
sidebar: SDKs_en
permalink: ontology_java_sdk_basic_en.html
folder: doc_en/SDKs
giturl: https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/basic.md
---

<h1 align="center"> Blockhain Interaction </h1>

<p align="center" class="version">Version 1.0.0 </p>

English / [中文](./ontology_java_sdk_basic_zh.html)


The following describes the basic blockchain interaction functions of the Java SDK and defines relevant data structures.

Please use the following methods to initialize OntSDK before launching JAVA SDK.


```
OntSdk wm = OntSdk.getInstance();
wm.setRpc(rpcUrl);
wm.setRestful(restUrl);
wm.setDefaultConnect(wm.getRestful());
wm.openWalletFile("OntAssetDemo.json");
```

Note: setRestful indicates that the connection is established using the restful interface, and setRpc indicates that the connection is established using the rpc interface. setDefaultConnect is used to set this as the default connection method.


## Basic operation interfaces


**Get the current block height**
```
int height = ontSdk.getConnectMgr().getBlockHeight();
```

**Get block**

***Get block by block height***
```
Block block = ontSdk.getConnect().getBlock(9757);
```

***Get block by block hash***
```
Block block = ontSdk.getConnect().getBlock(blockhash);
```

**Get block json**


***Get block by block height***
```
Object block = ontSdk.getConnect().getBlockJson(9757);
```

***Get block by block hash***

```
Object block = ontSdk.getConnect().getBlockJson(blockhash);
```

**Get contract code**

***Get contract code by contract hash***
```
Object contract =  ontSdk.getConnect().getContract(contractHash)
```

***Get contract json  by contract hash***
```
Object contractJson = ontSdk.getConnect().getContractJson(hash)
```

**Get balance**
```
Object  balance = ontSdk.getConnect().getBalance(address)
```

**Get blockchain node count**
```
ontSdk.getConnect().getNodeCount();
```

**Get block height**

```
int blockheight = ontSdk.getConnect().getBlockHeight()
```

**Get smartcontract event**

***Get smartcontract event by block height***
```
Object  event = ontSdk.getConnect().getSmartCodeEvent(height)
```

***Get smartcontract event by transaction hash***
```
Object  event = ontSdk.getConnect().getSmartCodeEvent(hash)
```

**Get block height by transaction hash**
```
int blockheight = ontSdk.getConnect().getBlockHeightByTxHash(txhash)
```

**Get data stored in smart contract by key**
```
String value = ontSdk.getConnect().getStorage(codehash,key)
```

**Get merkle proof**
```
Object proof =  ontSdk.getConnect().getMerkleProof(String hash)
```

**Get transaction**
```
Transaction info = ontSdk.getConnect().getTransaction(hash);
```

**Get transaction json by transaction hash**
```
Object info = ontSdk.getConnect().getTransactionJson(txhash);
```

**Get InvokeTransaction**
```
InvokeCodeTransaction t = (InvokeCodeTransaction) ontSdk.getConnect().getTransaction(hash);
```

## Data structure

**Block**

| Field     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    version|   int|  Version  |
|    prevBlockHash|   UInt256|  Scripthash of the previous block|
|    transactionsRoot|   UInt256|  Merkel root of all the transactions in the block|
|    blockRoot|   UInt256| Block root|
|    timestamp|   int| Block time stamp, unix time stamp|
|    height|   int|  Block height |
|    consensusData|   long |  Consensus data |
|    consensusPayload|   byte[] |  Consensus payload |
|    nextBookKeeper|   UInt160 |  Bookkeeping contract scripthash of the next block |
|    sigData|   array|  Signature |
|    bookKeepers|   array|  Bookkeepers |
|    hash|   UInt256 |  Hash value of the block |
|    transactions|   Transaction[] |  Transaction list in the block |


**Transaction**

| Field     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    version|   int|  Version  |
|    txType|   TransactionType|Transaction type|
|    nonce|   int |  Random number|
|    attributes|   Attribute[]|  Transaction attribute list |
| gasPrice|  long |  Gas price|
| gasLimit|  long |  Gas limit|
|    payer|   Address |  Account used to pay fee|
|    sigs|   Sign[]|   Signature array  |
|    payload| Payload |  Payload  |


**Transaction type**

| Value     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    208|   int |  Smart contract deployment |
|    209|   int | Smart contract invocation |
|      0|   int |        Bookkeeping  |
|      4|   int |     Enrollment       |
|      5|   int |     Vote |

**Signature area**

| Field     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    pubKeys|   array |  Public key array|
|    M|   int | M |
|    sigData|   array | Signature value array |


**Fee**

| Field     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    amount|   long|  Amount|
|    payer|   UInt160 | Payer |

**Attribute**

| Field    |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    usage |   AttributeUsage |  Usage|
|    data|   byte[] | Attribute value |


**TransactionAttributeUsage**

| Value     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    0  |   int|  Nonce|
|    32 |   int | Script |
|    129|   int | DescriptionUrl |
|    144|   int | Description |
