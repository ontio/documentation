---
title:
keywords: sample homepage
sidebar: SDKs_zh
permalink: ontology_java_sdk_get_start_zh.html
folder: doc_zh/SDKs
giturl: https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/sdk_get_start.md
---

<h1 align="center"> Java sdk 使用说明 </h1>

<p align="center" class="version">Version 1.0.0 </p>

[English](./ontology_java_sdk_get_start_en.html) / 中文

ONT中有两种资产：原生资产和合约资产。原生资产如ont和ong。交易所对接时，主要处理这两种类型资产的充值、提现等操作。

sdk文档：[sdk文档](https://github.com/ontio/ontology-java-sdk/tree/master/docs/cn) 

本文大纲如下：
* [Java sdk 使用说明](#java-sdk-使用说明)
	* [1. 公私钥和地址](#1-公私钥和地址)
		* [1.1 创建公私钥](#11-创建公私钥)
			* [1.1.1 不使用钱包管理：](#111-不使用钱包管理)
				* [随机创建账号：](#随机创建账号)
				* [根据私钥创建账号](#根据私钥创建账号)
			* [1.1.2 使用钱包管理：](#112-使用钱包管理)
		* [1.2 地址生成](#12-地址生成)
	* [2. 原生资产ont和ong转账](#2-原生资产ont和ong转账)
		* [2.1 初始化](#21-初始化)
		* [2.2 查询](#22-查询)
			* [ 查询ont，ong余额](#查询ontong余额)
			* [ 查询交易是否在交易池中](#查询交易是否在交易池中)
			* [ 查询交易是否调用成功](#查询交易是否调用成功)
			* [ 同步查询智能合约event](#同步查询智能合约event)
			* [其他与链交互接口列表：](#其他与链交互接口列表)
		* [2.3 交易反序](#23-交易反序)	
		* [2.4 ont转账](#24-ont转账)
			* [ 构造转账交易并发送](#构造转账交易并发送)
			* [ 多次签名](#多次签名)
			* [ 一转多或多转多](#一转多或多转多)
			* [使用签名机签名](#使用签名机签名)
		* [2.5 ong转账](#25-ong转账)
			* [ ong转账](#ong转账)
			* [ 提取ong](#提取ong)
	* [3. NEP5转账](#3-nep5转账)
		* [3.1 查询](#31-查询)
		* [3.2 转账](#32-转账)

## 1. 公私钥和地址

###  1.1 **创建公私钥**

#### 1.1.1 不使用钱包管理：
#####  随机创建账号：
```
com.github.ontio.account.Account acct = new com.github.ontio.account.Account(ontSdk.defaultSignScheme);
acct.serializePrivateKey();//私钥
acct.serializePublicKey();//公钥
acct.getAddressU160().toBase58();//base58地址
```            
##### 根据私钥创建账号            
```          
com.github.ontio.account.Account acct0 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey0), ontSdk.defaultSignScheme);
com.github.ontio.account.Account acct1 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey1), ontSdk.defaultSignScheme);
com.github.ontio.account.Account acct2 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey2), ontSdk.defaultSignScheme);

```

#### 1.1.2 使用钱包管理：
[例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/WalletDemo.java) 

```


#### 在钱包中批量创建账号:
ontSdk.getWalletMgr().createAccounts(10, "passwordtest");
ontSdk.getWalletMgr().writeWallet();

随机创建:
AccountInfo info0 = ontSdk.getWalletMgr().createAccountInfo("passwordtest");

通过私钥创建:
AccountInfo info = ontSdk.getWalletMgr().createAccountInfoFromPriKey("passwordtest","e467a2a9c9f56b012c71cf2270df42843a9d7ff181934068b4a62bcdd570e8be");

获取账号
com.github.ontio.account.Account acct0 = ontSdk.getWalletMgr().getAccount(info.addressBase58,"passwordtest",salt);

```




###  1.2 **地址生成**


包括单签地址和多签地址,生成方式与NEO地址相同。


```
单签地址生成：
String privatekey0 = "c19f16785b8f3543bbaf5e1dbb5d398dfa6c85aaad54fc9d71203ce83e505c07";
String privatekey1 = "49855b16636e70f100cc5f4f42bc20a6535d7414fb8845e7310f8dd065a97221";
String privatekey2 = "1094e90dd7c4fdfd849c14798d725ac351ae0d924b29a279a9ffa77d5737bd96";

//生成账号，获取地址
com.github.ontio.account.Account acct0 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey0), ontSdk.defaultSignScheme);
Address sender = acct0.getAddressU160();

//base58地址解码
sender = Address.decodeBase58("AVcv8YBABi9m6vH7faq3t8jWNamDXYytU2")；

多签地址生成：
Address recvAddr = Address.addressFromMultiPubKeys(2, acct1.serializePublicKey(), acct2.serializePublicKey());


```


| 方法名 | 参数 | 参数描述 |
| :--- | :--- | :--- |
| addressFromMultiPubkeys | int m,byte\[\]... pubkeys | 最小验签个数(<=公钥个数)，公钥 |

## 2. 原生资产ont和ong转账

参考例子：[例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/MakeTxWithoutWalletDemo.java)


### 2.1 初始化


```

String ip = "http://polaris1.ont.io";
String rpcUrl = ip + ":" + "20336";
OntSdk ontSdk = OntSdk.getInstance();
ontSdk.setRpc(rpcUrl);
ontSdk.setDefaultConnect(wm.getRpc());

或使用restful：
String restUrl = ip + ":" + "20334";
ontSdk.setRestful(restUrl);
ontSdk.setDefaultConnect(wm.getRestful());

也可以选择websocket：
String wsUrl = ip + ":" + "20335";
ontSdk.setWesocket(wsUrl, lock);
ontSdk.setDefaultConnect(wm.getWebSocket());

```


### 2.2 查询


####  **查询ont，ong余额**

```
ontSdk.getConnect().getBalance("AVcv8YBABi9m6vH7faq3t8jWNamDXYytU2");
ontSdk.nativevm().ont().queryBalanceOf("AVcv8YBABi9m6vH7faq3t8jWNamDXYytU2")
ontSdk.nativevm().ong().queryBalanceOf("AVcv8YBABi9m6vH7faq3t8jWNamDXYytU2")

查ont信息：
System.out.println(ontSdk.nativevm().ont().queryName());
System.out.println(ontSdk.nativevm().ont().querySymbol());
System.out.println(ontSdk.nativevm().ont().queryDecimals());
System.out.println(ontSdk.nativevm().ont().queryTotalSupply());

查ong信息：
System.out.println(ontSdk.nativevm().ong().queryName());
System.out.println(ontSdk.nativevm().ong().querySymbol());
System.out.println(ontSdk.nativevm().ong().queryDecimals());
System.out.println(ontSdk.nativevm().ong().queryTotalSupply());



```

#### **查询交易是否在交易池中**


```

ontSdk.getConnect().getMemPoolTxState("d441a967315989116bf0afad498e4016f542c1e7f8605da943f07633996c24cc")


response 交易池存在此交易:

{
    "Action": "getmempooltxstate",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": {
        "State":[
            {
              "Type":1,
              "Height":744,
              "ErrCode":0
            },
            {
              "Type":0,
              "Height":0,
              "ErrCode":0
            }
       ]
    },
    "Version": "1.0.0"
}

或 交易池不存在此交易

{
    "Action": "getmempooltxstate",
    "Desc": "UNKNOWN TRANSACTION",
    "Error": 44001,
    "Result": "",
    "Version": "1.0.0"
}

```


#### **查询交易是否调用成功**

查询智能合约推送内容

```
ontSdk.getConnect().getSmartCodeEvent("d441a967315989116bf0afad498e4016f542c1e7f8605da943f07633996c24cc")


response:
{
    "Action": "getsmartcodeeventbyhash",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": {
        "TxHash": "20046da68ef6a91f6959caa798a5ac7660cc80cf4098921bc63604d93208a8ac",
        "State": 1,
        "GasConsumed": 0,
        "Notify": [
            {
                "ContractAddress": "ff00000000000000000000000000000000000001",
                "States": [
                    "transfer",
                    "T9yD14Nj9j7xAB4dbGeiX9h8unkKHxuWwb",
                    "TA4WVfUB1ipHL8s3PRSYgeV1HhAU3KcKTq",
                    1000000000
                ]
            }
        ]
    },
    "Version": "1.0.0"
}

```

根据块高查询智能合约事件，返回有事件的交易hash


```

ontSdk.getConnect().getSmartCodeEvent(10)

response:
{
    "Action": "getsmartcodeeventbyheight",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": [{
	"GasConsumed": 0,
	"Notify": [{
		"States": ["transfer", "AFmseVrdL9f9oyCzZefL9tG6UbvhPbdYzM", "APrfMuKrAQB5sSb5GF8tx96ickZQJjCvwG", 1000000000],
		"ContractAddress": "0100000000000000000000000000000000000000"
	}],
	"TxHash": "b8a4f77e19fcae04faa576fbc71fa5a9775166d4485ce13f1ba5ff30ce264c52",
	"State": 1
     }, {
	"GasConsumed": 0,
	"Notify": [{
		"States": ["transfer", "AFmseVrdL9f9oyCzZefL9tG6UbvhPbdYzM", "AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV", 1000000000000000000],
		"ContractAddress": "0200000000000000000000000000000000000000"
	}],
	"TxHash": "7e8c19fdd4f9ba67f95659833e336eac37116f74ea8bf7be4541ada05b13503e",
	"State": 1
     }, {
	"GasConsumed": 0,
	"Notify": [],
	"TxHash": "80617b4a97eb4266e5e38886f234f324d57587362b5039a01c45cf413461f53b",
	"State": 1
     }, {
	"GasConsumed": 0,
	"Notify": [],
	"TxHash": "ede7ecc6e4e7e699b8ba1f07f2e5f8af3b65e70f126d82f7765d20a506080d2d",
	"State": 0
}],
    "Version": "1.0.0"
}

```

#### **同步查询智能合约event**

```
//发完交易每隔3秒请求一次，最长等待60秒

Object object = ontSdk.getConnect().waitResult(tx.hash().toString());
System.out.println(object);

response success:
{"GasConsumed":0,"Notify":[],"TxHash":"cb9e0d4a7a4aea0518bb39409613b8ef76798df3962feb8f8040e05329674890","State":1}

response fail,reject by txpool:
com.github.ontio.sdk.exception.SDKException: {"Action":"getmempooltxstate","Desc":"UNKNOWN TRANSACTION","Error":44001,"Result":"","Version":"1.0.0"}

```

#### 其他与链交互接口列表：

```

      |                     Main   Function                      |           Description            
 -----|----------------------------------------------------------|---------------------------------------------
    1 | ontSdk.getConnect().getNodeCount()                       |  查询节点数量
    2 | ontSdk.getConnect().getBlock(15)                         |  查询块
    3 | ontSdk.getConnect().getBlockJson(15)                     |  查询块    
    4 | ontSdk.getConnect().getBlockJson("txhash")               |  查询块    
    5 | ontSdk.getConnect().getBlock("txhash")                   |  查询块     
    6 | ontSdk.getConnect().getBlockHeight()                     |  查询当前块高
    7 | ontSdk.getConnect().getTransaction("txhash")             |  查询交易                                     
    8 | ontSdk.getConnect().getStorage("contractaddress", key)   |  查询智能合约存储
    9 | ontSdk.getConnect().getBalance("address")                |  查询余额
   10 | ontSdk.getConnect().getContractJson("contractaddress")   |  查询智能合约          
   11 | ontSdk.getConnect().getSmartCodeEvent(59)                |  查询智能合约事件
   12 | ontSdk.getConnect().getSmartCodeEvent("txhash")          |  查询智能合约事件
   13 | ontSdk.getConnect().getBlockHeightByTxHash("txhash")     |  查询交易所在高度
   14 | ontSdk.getConnect().getMerkleProof("txhash")             |  获取merkle证明
   15 | ontSdk.getConnect().sendRawTransaction("txhexString")    |  发送交易
   16 | ontSdk.getConnect().sendRawTransaction(Transaction)      |  发送交易
   17 | ontSdk.getConnect().sendRawTransactionPreExec()          |  发送预执行交易
   18 | ontSdk.getConnect().getAllowance("ont","from","to")      |  查询允许使用值
   19 | ontSdk.getConnect().getMemPoolTxCount()                  |  查询交易池中交易总量
   20 | ontSdk.getConnect().getMemPoolTxState()                  |  查询交易池中交易状态
```  

### 2.3 交易反序

获取交易
```  
http://polaris1.ont.io:20334/api/v1/transaction/8f4ab5db768e41e56643eee10ad9749be0afa54a891bcd8e5c45543a8dd0cf7d?raw=0

{
    "Action": "gettransaction",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": {
        "Version": 0,
        "Nonce": 391455426,
        "GasPrice": 500,
        "GasLimit": 20000,
        "Payer": "ASyx6be9APCR6BzcM81615FgBU26gqr1JL",
        "TxType": 209,
        "Payload": {
            "Code": "00c66b147af216ff3da82b999b26f5efe165de5f944ac5496a7cc814d2c124dd088190f709b684e0bc676d70c41b37766a7cc80800ca9a3b000000006a7cc86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65"
        },
        "Attributes": [],
        "Sigs": [
            {
                "PubKeys": [
                    "0369d1e9a5a1d83fa1798bbd162e8d8d8ef8e4e1a0e03aa2753b472943e235e219"
                ],
                "M": 1,
                "SigData": [
                    "017b80d5f0826b52b2037ee564be55f0ada1d0cb714a80967deb2d04b49a59f6c4358c57d06ee8f7666aec3fc570c5251c30be1cd134acb791775de9e11cacd22c"
                ]
            }
        ],
        "Hash": "8f4ab5db768e41e56643eee10ad9749be0afa54a891bcd8e5c45543a8dd0cf7d",
        "Height": 95796
    },
    "Version": "1.0.0"
}

```  

获取交易
```  
http://polaris1.ont.io:20334/api/v1/transaction/8f4ab5db768e41e56643eee10ad9749be0afa54a891bcd8e5c45543a8dd0cf7d?raw=1


{
    "Action": "gettransaction",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": "00d1c2225517f401000000000000204e0000000000007af216ff3da82b999b26f5efe165de5f944ac5497900c66b147af216ff3da82b999b26f5efe165de5f944ac5496a7cc814d2c124dd088190f709b684e0bc676d70c41b37766a7cc80800ca9a3b000000006a7cc86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b6500014241017b80d5f0826b52b2037ee564be55f0ada1d0cb714a80967deb2d04b49a59f6c4358c57d06ee8f7666aec3fc570c5251c30be1cd134acb791775de9e11cacd22c23210369d1e9a5a1d83fa1798bbd162e8d8d8ef8e4e1a0e03aa2753b472943e235e219ac",
    "Version": "1.0.0"
}

``` 

反序列化交易
``` 
//版本号    交易类型  随机数   gasprice    gaslimit              网络费付款人       交易数据 
(version(1) type(1) nonce(4) gasprice(8) gaslimit(8))22 bytes + (payer)21 bytes + payload code bytes( any bytes)

claim ong 
//             claim address                                                 ont contract address                         to   address                                 amount                       "transferFrom"                           ong                   SYSCALL         "Ontology.Native.Invoke"
//00 c66b 14bb2d5b718efeac060ac825338ca440216da4d8dc 6a7cc8 140000000000000000000000000000000000000001 6a7cc8 14bb2d5b718efeac060ac825338ca440216da4d8dc 6a7cc8 08 806a735501000000 6a7cc8 6c 0c7472616e7366657246726f6d 140000000000000000000000000000000000000002 0068 164f6e746f6c6f67792e4e61746976652e496e766f6b65
ont and ong transfer
//                     from                                           to                                        amount                                 "transfer"                                                                       ont or ong                SYSCALL           "Ontology.Native.Invoke"
//00 c66b 147af216ff3da82b999b26f5efe165de5f944ac549 6a7cc8 14d2c124dd088190f709b684e0bc676d70c41b3776 6a7cc8 08 00ca9a3b00000000 6a7cc8 6c 51c1 087472616e73666572                                                      140000000000000000000000000000000000000001 0068 164f6e746f6c6f67792e4e61746976652e496e766f6b65

For amount ：   1-16  is  0x51-0x60  .     >=16 is  long,  08 is the total amount bytes .  
Example: 1000 is  0xe803000000000000 -> 0x00000000000003e8   change from little endian to big endian if print.

```  

### 2.4 ont转账



#### **构造转账交易并发送**

```
转出方与收款方地址：
Address sender = acct0.getAddressU160();
Address recvAddr = acct1;
//多签地址生成
//Address recvAddr = Address.addressFromMultiPubKeys(2, acct1.serializePublicKey(), acct2.serializePublicKey());

构造转账交易：
long amount = 1000;
Transaction tx = ontSdk.nativevm().ont().makeTransfer(sender.toBase58(),recvAddr.toBase58(), amount,sender.toBase58(),30000,0);
String hash = tx.hash().toString()

对交易做签名：
ontSdk.signTx(tx, new com.github.ontio.account.Account[][]{{acct0}});
//多签地址的签名方法：
ontSdk.signTx(tx, new com.github.ontio.account.Account[][]{{acct1, acct2}});
//如果转出方与网络费付款人不是同一个地址，需要添加网络费付款人的签名


发送预执行（可选）：
Object obj = ontSdk.getConnect().sendRawTransactionPreExec(tx.toHexString());
System.out.println(obj);
成功返回：
{"State":1,"Gas":30000,"Result":"01"}
余额不足返回异常：
com.github.ontio.network.exception.RestfulException: {"Action":"sendrawtransaction","Desc":"SMARTCODE EXEC ERROR","Error":47001,"Result":"","Version":"1.0.0"}


发送交易：
ontSdk.getConnect().sendRawTransaction(tx.toHexString());


同步发送交易：
Object obj = ontSdk.getConnect().syncSendRawTransaction(tx.toHexString());

response success:
{"GasConsumed":0,"Notify":[],"TxHash":"cb9e0d4a7a4aea0518bb39409613b8ef76798df3962feb8f8040e05329674890","State":1}

response fail,reject by txpool:
com.github.ontio.sdk.exception.SDKException: {"Action":"getmempooltxstate","Desc":"UNKNOWN TRANSACTION","Error":44001,"Result":"","Version":"1.0.0"}

```



| 方法名 | 参数 | 参数描述 |
| :--- | :--- | :--- |
| makeTransfer | String sender，String recvAddr,long amount,String payer,long gaslimit,long gasprice | 发送方地址，接收方地址，金额，网络费付款人地址，gaslimit，gasprice |
| makeTransfer | State\[\] states,String payer,long gaslimit,long gasprice | 一笔交易包含多个转账。 |


#### **多次签名**

如果转出方与网络费付款人不是同一个地址，需要添加网络费付款人的签名

```

1.添加单签签名
ontSdk.addSign(tx,acct0);

2.添加多签签名
ontSdk.addMultiSign(tx,2,new byte[][]{acct.serializePublicKey(),acct2.serializePublicKey()},acct);
ontSdk.addMultiSign(tx,2,new byte[][]{acct.serializePublicKey(),acct2.serializePublicKey()},acct2);

3.多签签名分多次签
acct0签名：
ontSdk.addMultiSign(tx,2,new byte[][]{acct.serializePublicKey(),acct2.serializePublicKey()},acct);

acct1签名：
ontSdk.addMultiSign(tx,2,new byte[][]{acct.serializePublicKey(),acct2.serializePublicKey()},acct2);

```


 
#### **一转多或多转多**

1. 构造多个state的交易
2. 签名
3. 一笔交易上限为1024笔转账


```

Address sender1 = acct0.getAddressU160();
Address sender2 = Address.addressFromMultiPubKeys(2, acct1.serializePublicKey(), acct2.serializePublicKey());
int amount = 10;
int amount2 = 20;

State state = new State(sender1, recvAddr, amount);
State state2 = new State(sender2, recvAddr, amount2);
Transaction tx = ontSdk.nativevm().ont().makeTransfer(new State[]{state1,state2},sender1.toBase58(),30000,0);

//第一个转出方是单签地址，第二个转出方是多签地址：
ontSdk.signTx(tx, new com.github.ontio.account.Account[][]{{acct0}});
ontSdk.addMultiSign(tx,2,new byte[][]{acct1.serializePublicKey(),acct2.serializePublicKey()},acct1);
ontSdk.addMultiSign(tx,2,new byte[][]{acct1.serializePublicKey(),acct2.serializePublicKey()},acct2);
```

#### 使用签名机签名

 **构造交易并签名**

1. 构造交易，序列化交易，发送交易给签名机
2. 签名机接收到交易，反序列化，检查交易，添加签名
3. 发送交易

```

序列化交易发送给签名机：
Transaction tx = ontSdk.nativevm().ont().makeTransfer(sender.toBase58(),recvAddr.toBase58(), amount,sender.toBase58(),30000,0);
String txHex = tx.toHexString();

接收方反序列化交易并签名：

Transaction txRx = Transaction.deserializeFrom(Helper.hexToBytes(txHex));


签名：
ontSdk.addSign(txRx,acct0);
```

**SDK与签名机交互**：

[例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/SignServerDemo.java)

```
节点启动时打开签名机服务：
go run SigSvr.go


设置签名机URL：
String url = ip + ":" + "20000/cli";
OntSdk ontSdk = OntSdk.getInstance();
ontSdk.setSignServer(url);
        

String txHex = tx.toHexString();

请求单签交易：
ontSdk.getSignServer().sendSigRawTx(txHex);
 
请求多签交易： 
String[] signs = new String[]{"02039b196d5ed74a4d771ade78752734957346597b31384c3047c1946ce96211c2a7",
                    "0203428daa06375b8dd40a5fc249f1d8032e578b5ebb5c62368fc6c5206d8798a966"};
ontSdk.getSignServer().sendMultiSigRawTx(txHex,2,signs);

请求构造转账交易并签名：
ontSdk.getSignServer().sendSigTransferTx("ont","TU5exRFVqjRi5wnMVzNoWKBq9WFncLXEjK","TA5SgQXTeKWyN4GNfWGoXqioEQ4eCDFMqE",10,30000,0);
            

```

 **对数据做签名**


[例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/SignatureDemo.java) 


```
com.github.ontio.account.Account acct = new com.github.ontio.account.Account(ontSdk.defaultSignScheme);

byte[] data = "12345".getBytes();
byte[] signature = ontSdk.signatureData(acct, data);

System.out.println(ontSdk.verifySignature(acct.serializePublicKey(), data, signature));

```



### 2.5 ong转账


####  **ong转账**

接口与ont类似：

```
ontSdk.nativevm().ong().makeTransfer...
```

####  **提取ong**

1. 查询是否有ong可以提取
2. 发送提取ong交易

```
查询未提取ong:
String addr = acct0.getAddressU160().toBase58();
String ong = sdk.nativevm().ong().unboundOng(addr);

//提取ong
com.github.ontio.account.Account account = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey0), ontSdk.signatureScheme);
String hash = sdk.nativevm().ong().withdrawOng(account,toAddr,64000L,payerAcct,30000,500);

```



## 3. NEP5转账

参考例子：[例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/Nep5Demo.java)

### 3.1 查询

```
String balance = ontSdk.neovm().nep5().queryBalanceOf(acct.address);
System.out.println(new BigInteger(Helper.reverse(Helper.hexToBytes(balance))).longValue());

String totalSupply = ontSdk.neovm().nep5().queryTotalSupply();
System.out.println(new BigInteger(Helper.reverse(Helper.hexToBytes(totalSupply))).longValue());

String decimals = ontSdk.neovm().nep5().queryDecimals();
System.out.println(decimals);

String name = ontSdk.neovm().nep5().queryName();
System.out.println(new String(Helper.hexToBytes(name)));

String symbol = ontSdk.neovm().nep5().querySymbol();
System.out.println(new String(Helper.hexToBytes(symbol)));

System.out.println(Address.decodeBase58(acct.address).toHexString());
```

### 3.2 转账

```
ontSdk.neovm().nep5().sendTransfer(acct,"AVcv8YBABi9m6vH7faq3t8jWNamDXYytU2",46440000L,acct,gasLimit,0);
```

