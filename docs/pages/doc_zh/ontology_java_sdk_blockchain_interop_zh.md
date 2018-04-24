---
title: 
keywords: sample homepage
sidebar: ont_doc_zh
permalink: ontology_java_sdk_blockchain_interop_zh.html
folder: doc_zh
---

[English](./ontology_java_sdk_blockchain_interop_en.html) / 中文

<h1 align="center"> Ontology Java SDK User Guide </h1>
<p align="center" class="version">Version 0.7.0 </p>

# 区块链交互基本操作

以下针对使用SDK和区块交互的基本操作，以及相关数据结构定义。

用Java SDK之前，请使用以下方式初始化OntSDK实例。

```
OntSdk ontSdk = OntSdk.getInstance();
ontSdk.setRpc(rpcUrl);
ontSdk.setRestful(restUrl);
ontSdk.setDefaultConnect(wm.getRestful());
ontSdk.openWalletFile("OntAssetDemo.json");
```
> Note: setRestful表示采用restful接口建立连接，setRpc表示采用rpc接口建立连接,setDefaultConnect表示设置默认的链接方式。

## 基本操作接口

* 获取当前区块高度
```
int height = ontSdk.getConnectMgr().getBlockHeight();
```

* 获取区块

```
Block block = ontSdk.getConnectMgr().getBlock(9757);
```

* 获取区块链节点数

```
System.out.println(ontSdk.getConnectMgr().getNodeCount());
```

* 获取出块时间

```
System.out.println(ontSdk.getConnectMgr().getGenerateBlockTime());
```

* 从区块链中获取交易

```
String info = ontSdk.getConnectMgr().getTransaction(txhash);
System.out.println(info);
```
* 从区块链中获取InvokeCodeTransaction

```
InvokeCodeTransaction t = (InvokeCodeTransaction) ontSdk.getConnectMgr().getTransaction(txhash);
System.out.println(t);
```
## 数据结构说明

* Block区块

| Field     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    version|   int|  版本号  |
|    prevBlockHash|   UInt256|  前一个区块的散列值|
|    transactionsRoot|   UInt256|  该区块中所有交易的Merkle树的根|
|    blockRoot|   UInt256| 区块根|
|    timestamp|   int| 区块时间戳，unix时间戳  |
|    height|   int|  区块高度  |
|    consensusData|   long |  共识数据 |
|    nextBookKeeper|   UInt160 |  下一个区块的记账合约的散列值 |
|    sigData|   array|  签名 |
|    bookKeepers|   array|  验签者 |
|    hash|   UInt256 |  该区块的hash值 |
|    transactions|   Transaction[] |  该区块的交易列表 |


* Transaction交易

| Field     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    version|   int|  版本号  |
|    txType|   TransactionType|  交易类型|
|    nonce|   int |  随机数|
|    attributes|   Attribute[]|  交易属性列表 |
|    fee|   Fee[] |  交易手续费列表 |
|    networkFee|   long| 网络手续费  |
|    sigs|   Sign[]|   签名数组  |
|    payload| Payload |  payload  |


* TransactionType交易类型

| Value     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    208|   int |  部署智能合约交易|
|    209|   int | 调用智能合约交易 |
|      0|   int |     Bookkeeping   |
|      4|   int |     注册       |
|      5|   int |     投票 |


* 签名字段

| Field     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    pubKeys|   array |  公钥数组|
|    M|   int | M |
|    sigData|   array | 签名值数组 |


* Fee交易手续费

| Field     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    amount|   long|  金额|
|    payer|   Address | 付费者 |

* Attribute交易属性

| Field    |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    usage |   AttributeUsage |  用途|
|    data|   byte[] | 属性值 |


* TransactionAttributeUsage属性用途

| Value     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    0|   int|  Nonce|
|    32|   int | Script |
|    129|   int | DescriptionUrl |
|    144|   int | Description |