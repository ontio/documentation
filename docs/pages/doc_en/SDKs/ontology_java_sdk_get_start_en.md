---
title:
keywords: sample homepage
sidebar: SDKs_en
permalink: ontology_java_sdk_get_start_en.html
folder: doc_en/SDKs
giturl: https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/sdk_get_start.md
---

<h1 align="center"> Ontology Java SDK Tutorials </h1>

<p align="center" class="version">Version 1.0.0 </p>

English / [中文](./ontology_java_sdk_get_start_zh.html)

There are two kinds of assets in ONT: native assets and contract assets. Native assets are ONT and ONG. When docking with the exchange, it mainly processes deposit and withdrawal of these two assets.

SDK document：[SDK document](https://github.com/ontio/ontology-java-sdk/tree/master/docs/en) 

The outline of this document is as follows:
* [Java SDK Tutorials](#java-sdk-tutorials)
	* [1. Public and private key, and address](#1-public-and-private-key,-and-address)
		* [1.1 Create public and private key](#11-create-public-and-private-key)
			* [1.1.1 Do not use wallet management](#111-do-not-use-wallet-management)
				* [Create account randomly](#create-account-randomly)
				* [Create account based on private key](#create-account-based-on-private-key)
			* [1.1.2 Use wallet management](#112-use-wallet-management)
		* [1.2 Address generation](#12-address-generation)
	* [2. ONT and ONG transfer](#2-ont-and-ong-transfer)
		* [2.1 Initialization](#21-initialization)
		* [2.2 Query](#22-query)
			* [ Query ONT, ONG Balance](#query-ont,-ong-balance)
			* [ Query whether the transaction is in the transaction pool](#query-whether-the-transaction-is-in-the-transaction-pool)
			* [ Query whether the transaction is successful](#query-whether-the-transaction-is-successful)
			* [ The list of chain interaction interface](#the-list-of-chain-interaction-interface)
		* [2.3 ONT transfer](#23-ont-transfer)
			* [ Construct transfer transaction and send](#construct-transfer-transaction-and-send)
			* [ Multiple signatures](#multiple-signatures)
			* [ One to multiple or multiple to multiple](#one-to-multiple-or-multiple-to-multiple)
			* [Use signature server to sign](#use-signature-server-to-sign)
		* [2.4 ONG transfer](#24-ong-transfer)
			* [ ONG transfer](#ong transfer)
			* [ Withdraw ONG](#Withdraw-ong)
	* [3. NEP5 Transfer](#3-nep5-transfer)
		* [3.1 Query](#31-query)
		* [3.2 Transfer](#32-transfer)

## 1. Public and private key, and address

###  1.1 **Create public and private key**

#### 1.1.1 Do not use wallet management
#####  Create account randomly
```
com.github.ontio.account.Account acct = new com.github.ontio.account.Account(ontSdk.defaultSignScheme);
acct.serializePrivateKey();//Private key
acct.serializePublicKey();//Public key
acct.getAddressU160().toBase58();//Base58 address
```            
##### Create account based on private key
```          
com.github.ontio.account.Account acct0 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey0), ontSdk.defaultSignScheme);
com.github.ontio.account.Account acct1 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey1), ontSdk.defaultSignScheme);
com.github.ontio.account.Account acct2 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey2), ontSdk.defaultSignScheme);

```

#### 1.1.2 Use wallet management
[Example](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/WalletDemo.java) 

```


// Create a batch of account in the wallet
ontSdk.getWalletMgr().createAccounts(10, "passwordtest");
ontSdk.getWalletMgr().writeWallet();

// Create account randomly
AccountInfo info0 = ontSdk.getWalletMgr().createAccountInfo("passwordtest");

// Create account based on private key:
AccountInfo info = ontSdk.getWalletMgr().createAccountInfoFromPriKey("passwordtest","e467a2a9c9f56b012c71cf2270df42843a9d7ff181934068b4a62bcdd570e8be");

// Get account
com.github.ontio.account.Account acct0 = ontSdk.getWalletMgr().getAccount(info.addressBase58,"passwordtest",salt);

```




###  1.2 **Address generation**


The address includes single-signature address and multi-signature address, and the generation method is the same as the NEO address.


```
// single-signature address generation
String privatekey0 = "c19f16785b8f3543bbaf5e1dbb5d398dfa6c85aaad54fc9d71203ce83e505c07";
String privatekey1 = "49855b16636e70f100cc5f4f42bc20a6535d7414fb8845e7310f8dd065a97221";
String privatekey2 = "1094e90dd7c4fdfd849c14798d725ac351ae0d924b29a279a9ffa77d5737bd96";

//Generate account and get address
com.github.ontio.account.Account acct0 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey0), ontSdk.defaultSignScheme);
Address sender = acct0.getAddressU160();

//base58 address decode
sender = Address.decodeBase58("AVcv8YBABi9m6vH7faq3t8jWNamDXYytU2")；

//multi-signature address generation
Address recvAddr = Address.addressFromMultiPubKeys(2, acct1.serializePublicKey(), acct2.serializePublicKey());


```


| Method Name                  | Parameter                      | Parameter Description                       |
| :--- | :--- | :--- |
| addressFromMultiPubkeys | int m,byte\[\]... pubkeys | The minimum number of signatures (<=the number of public keys)，public key |

## 2. ONT and ONG transfer

Example：[Example](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/MakeTxWithoutWalletDemo.java)

### 2.1 Initialization


```

String ip = "http://polaris1.ont.io";
String rpcUrl = ip + ":" + "20336";
OntSdk ontSdk = OntSdk.getInstance();
ontSdk.setRpc(rpcUrl);
ontSdk.setDefaultConnect(wm.getRpc());

// or use restful
String restUrl = ip + ":" + "20334";
ontSdk.setRestful(restUrl);
ontSdk.setDefaultConnect(wm.getRestful());

// use websocket
String wsUrl = ip + ":" + "20335";
ontSdk.setWesocket(wsUrl, lock);
ontSdk.setDefaultConnect(wm.getWebSocket());

```


### 2.2  Query


####  **Query ONT, ONG Balance**

```
ontSdk.getConnect().getBalance("AVcv8YBABi9m6vH7faq3t8jWNamDXYytU2");
ontSdk.nativevm().ont().queryBalanceOf("AVcv8YBABi9m6vH7faq3t8jWNamDXYytU2")
ontSdk.nativevm().ong().queryBalanceOf("AVcv8YBABi9m6vH7faq3t8jWNamDXYytU2")

View ONT information:
System.out.println(ontSdk.nativevm().ont().queryName());
System.out.println(ontSdk.nativevm().ont().querySymbol());
System.out.println(ontSdk.nativevm().ont().queryDecimals());
System.out.println(ontSdk.nativevm().ont().queryTotalSupply());

View ONG information:
System.out.println(ontSdk.nativevm().ong().queryName());
System.out.println(ontSdk.nativevm().ong().querySymbol());
System.out.println(ontSdk.nativevm().ong().queryDecimals());
System.out.println(ontSdk.nativevm().ong().queryTotalSupply());



```

#### **Query whether the transaction is in the transaction pool**


```

ontSdk.getConnect().getMemPoolTxState("d441a967315989116bf0afad498e4016f542c1e7f8605da943f07633996c24cc")


response: the transaction is in the transaction pool:

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

Or the transaction is not in the transaction pool

{
    "Action": "getmempooltxstate",
    "Desc": "UNKNOWN TRANSACTION",
    "Error": 44001,
    "Result": "",
    "Version": "1.0.0"
}

```


#### **Query whether the transaction is successful**

Query pushing content of a smart contract

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

You can use the block height to query a smart contract event, and the event transaction hash will be returned.


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

#### **synchronize query smartcontract event**

```
//query event per 3s after send transaction, maximum is 60s

Object object = ontSdk.getConnect().waitResult(tx.hash().toString());
System.out.println(object);

response success:
{"GasConsumed":0,"Notify":[],"TxHash":"cb9e0d4a7a4aea0518bb39409613b8ef76798df3962feb8f8040e05329674890","State":1}

response fail,reject by txpool:
com.github.ontio.sdk.exception.SDKException: {"Action":"getmempooltxstate","Desc":"UNKNOWN TRANSACTION","Error":44001,"Result":"","Version":"1.0.0"}

```


#### The list of chain interaction interfaces

| No   |                    Main   Function                     |     Description      |
| ---- | :----------------------------------------------------: | :------------------: |
| 1    |       ontSdk.getConnect().getGenerateBlockTime()       |   Query VBFT block-out time   |
| 2    |           ontSdk.getConnect().getNodeCount()           |     Query the number of nodes     |
| 3    |            ontSdk.getConnect().getBlock(15)            |        Query block info        |
| 4    |          ontSdk.getConnect().getBlockJson(15)          |        Query block info        |
| 5    |       ontSdk.getConnect().getBlockJson("txhash")       |        Query block info        |
| 6    |         ontSdk.getConnect().getBlock("txhash")         |        Query block info        |
| 7    |          ontSdk.getConnect().getBlockHeight()          |     Query current block height     |
| 8    |      ontSdk.getConnect().getTransaction("txhash")      |       Query transaction       |
| 9    | ontSdk.getConnect().getStorage("contractaddress", key) |   Query smart contract storage   |
| 10   |       ontSdk.getConnect().getBalance("address")        |       Query balance       |
| 11   | ontSdk.getConnect().getContractJson("contractaddress") |     Query smart contract     |
| 12   |       ontSdk.getConnect().getSmartCodeEvent(59)        |   Query the event in the smart contract   |
| 13   |    ontSdk.getConnect().getSmartCodeEvent("txhash")     |   Query the event in the smart contract   |
| 14   |  ontSdk.getConnect().getBlockHeightByTxHash("txhash")  |   Query the block height by transaction hash   |
| 15   |      ontSdk.getConnect().getMerkleProof("txhash")      |    Get merkle proof    |
| 16   | ontSdk.getConnect().sendRawTransaction("txhexString")  |       Send transaction       |
| 17   |  ontSdk.getConnect().sendRawTransaction(Transaction)   |       Send transaction       |
| 18   |    ontSdk.getConnect().sendRawTransactionPreExec()     |    Send a pre-execution transaction    |
| 19   |  ontSdk.getConnect().getAllowance("ont","from","to")   |    Query Allowed Values    |
| 20   |        ontSdk.getConnect().getMemPoolTxCount()         | Query total transaction volumn in the transaction pool  |
| 21   |        ontSdk.getConnect().getMemPoolTxState()         | Query transaction status in the transaction pool |


### 2.3 ONT transfer



#### **Construct transfer transaction and send**

```
// Transferee and payee address
Address sender = acct0.getAddressU160();
Address recvAddr = acct1;

// Multiple address generation
//Address recvAddr = Address.addressFromMultiPubKeys(2, acct1.serializePublicKey(), acct2.serializePublicKey());

// Construct a transfer transaction
long amount = 1000;
Transaction tx = ontSdk.nativevm().ont().makeTransfer(sender.toBase58(),recvAddr.toBase58(), amount,sender.toBase58(),30000,0);

// Sign a transaction
ontSdk.signTx(tx, new com.github.ontio.account.Account[][]{{acct0}});
//Signature scheme of multiple address
ontSdk.signTx(tx, new com.github.ontio.account.Account[][]{{acct1, acct2}});
//If the addresses of the transferee and the payer who pay the network fee are different, the payer’s signature needs to be added.


//Send prepare execution transaction（optional）：
Object obj = ontSdk.getConnect().sendRawTransactionPreExec(tx.toHexString());
System.out.println(obj);
Success：
{"State":1,"Gas":30000,"Result":"01"}
Fail: if balance insufficient, get this Exception：
com.github.ontio.network.exception.RestfulException: {"Action":"sendrawtransaction","Desc":"SMARTCODE EXEC ERROR","Error":47001,"Result":"","Version":"1.0.0"}


// Send a transaction
ontSdk.getConnect().sendRawTransaction(tx.toHexString());

// Send a transaction synchronize 
Object obj = ontSdk.getConnect().syncSendRawTransaction(tx.toHexString());

response success:
{"GasConsumed":0,"Notify":[],"TxHash":"cb9e0d4a7a4aea0518bb39409613b8ef76798df3962feb8f8040e05329674890","State":1}

response fail,reject by txpool:
com.github.ontio.sdk.exception.SDKException: {"Action":"getmempooltxstate","Desc":"UNKNOWN TRANSACTION","Error":44001,"Result":"","Version":"1.0.0"}

```

| Method Name  | Parameter  | Parameter Description |
| :--- | :--- | :--- |
| makeTransfer | String sender，String recvAddr,long amount,String payer,long gaslimit,long gasprice | sender address, receiver address, amount, network fee payer address, gaslimit, gasprice |
| makeTransfer | State\[\] states,String payer,long gaslimit,long gasprice | A transaction contains multiple transfers |


#### **Multiple signatures**

If the addresses of the transferee and the payer who pay the network fee are different, the payer’s signature needs to be added.

```
// 1.Add single signature 
ontSdk.addSign(tx,acct0);

// 2.Add multiple signatures 
ontSdk.addMultiSign(tx,2,new byte[][]{acct.serializePublicKey(),acct2.serializePublicKey()},acct);
ontSdk.addMultiSign(tx,2,new byte[][]{acct.serializePublicKey(),acct2.serializePublicKey()},acct2);

//3.multiple signatures splite
acct0 signature：
ontSdk.addMultiSign(tx,2,new byte[][]{acct.serializePublicKey(),acct2.serializePublicKey()},acct);

acct1 signature：
ontSdk.addMultiSign(tx,2,new byte[][]{acct.serializePublicKey(),acct2.serializePublicKey()},acct2);

```

 #### **One to multiple or multiple to multiple**

1. Construct a transaction with multiple states
2. Signature
3. A transaction includes 1024 transfers at most


```

Address sender1 = acct0.getAddressU160();
Address sender2 = Address.addressFromMultiPubKeys(2, acct1.serializePublicKey(), acct2.serializePublicKey());
int amount = 10;
int amount2 = 20;

State state = new State(sender1, recvAddr, amount);
State state2 = new State(sender2, recvAddr, amount2);
Transaction tx = ontSdk.nativevm().ont().makeTransfer(new State[]{state1,state2},sender1.toBase58(),30000,0);

//The first transferee is a single-signature address, and the second transferee is a multiple-signature address
ontSdk.signTx(tx, new com.github.ontio.account.Account[][]{{acct0}});
ontSdk.addMultiSign(tx,2,new byte[][]{acct1.serializePublicKey(),acct2.serializePublicKey()},acct1);
ontSdk.addMultiSign(tx,2,new byte[][]{acct1.serializePublicKey(),acct2.serializePublicKey()},acct2);

```

#### Use signature server to sign

 **Construct transaction and sign**

1. Construct a transaction, serialize a transaction, send a transaction to the signature server
2. The signature server receives the transaction, deserializes, checks the transaction, and adds the signature
3. Send transaction

```

//Send serialized transaction to signature server
Transaction tx = ontSdk.nativevm().ont().makeTransfer(sender.toBase58(),recvAddr.toBase58(), amount,sender.toBase58(),30000,0);
String txHex = tx.toHexString();

//The receiver deserializes the transaction and signs it
Transaction txRx = Transaction.deserializeFrom(Helper.hexToBytes(txHex));


//Sign
ontSdk.addSign(txRx,acct0);
```

**Interaction between SDK and signature server**：

[Example](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/SignServerDemo.java)

```
//Start the signature server service when nodes start：
go run SigSvr.go


// Set signature server URL
String url = ip + ":" + "20000/cli";
OntSdk ontSdk = OntSdk.getInstance();
ontSdk.setSignServer(url);
        

String txHex = tx.toHexString();

// Request a transaction with single signature
ontSdk.getSignServer().sendSigRawTx(txHex);
 
// Request a transaction with multiple signature
String[] signs = new String[]{"1202039b196d5ed74a4d771ade78752734957346597b31384c3047c1946ce96211c2a7",
                    "120203428daa06375b8dd40a5fc249f1d8032e578b5ebb5c62368fc6c5206d8798a966"};
ontSdk.getSignServer().sendMultiSigRawTx(txHex,2,signs);

// Construct transfer transaction and sign
ontSdk.getSignServer().sendSigTransferTx("ont","TU5exRFVqjRi5wnMVzNoWKBq9WFncLXEjK","TA5SgQXTeKWyN4GNfWGoXqioEQ4eCDFMqE",10,30000,0);
            

```

 **Sign data**


[Example](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/SignatureDemo.java) 


```
com.github.ontio.account.Account acct = new com.github.ontio.account.Account(ontSdk.defaultSignScheme);

byte[] data = "12345".getBytes();
byte[] signature = ontSdk.signatureData(acct, data);

System.out.println(ontSdk.verifySignature(acct.serializePublicKey(), data, signature));

```



### 2.4 ONG transfer


####  **ONG transfer**

The interface is similar to ONT:

```
ontSdk.nativevm().ong().makeTransfer...
```

####  **Withdraw ONG**

1. Check the balance of non-withdrawal ONG
2. Send a transaction that withdraws ONG

```

//Query non-withdrawal ONG:
String addr = acct0.getAddressU160().toBase58();
String ong = sdk.nativevm().ong().unboundOng(addr);

//withdraw ONG
com.github.ontio.account.Account account = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey0), ontSdk.signatureScheme);
String hash = sdk.nativevm().ong().withdrawOng(account,toAddr,64000L,payerAcct,30000,500);

```



## 3. NEP5 Transfer

Example：[example](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/Nep5Demo.java)

### 3.1 Query

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

### 3.2 Transfer

```
ontSdk.neovm().nep5().sendTransfer(acct,"AVcv8YBABi9m6vH7faq3t8jWNamDXYytU2",46440000L,acct,gasLimit,0);
```

