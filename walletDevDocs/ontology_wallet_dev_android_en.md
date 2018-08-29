


<h1 align="center">Ontology Wallet Integration</h1>
<p align="center" class="version">Version 1.0.0 </p>

The outline of this document is as follows:

* [Wallet Integration](#wallet-integration)
* [Java Sdk Tutorial](#java-sdk-tutorial)
    * [1. Blockchain](#1-blockchain)
        * [1.1 Initial](#11-initial)
        * [1.2 Query](#12-query)
            * [Query Unbound ong](#Query-unbound-ong)
            * [Query Transaction history](#query-transaction-history)
        * [1.3 Other interface：](#13-other-interface)
            * [Query ONT/ONG balance](#query-ont/ong-balance)
            * [Query transaction in transaction pool](#query-transaction-in-transaction-pool)
            * [Query transaction success](#Query-transaction-success)
    * [2. Account](#2-account)
        * [2.1 Mnemonic code and keystore](#21-Mnemonic-code-and-keystore)
        * [2.2 Random create account](#22-random-create-account)
        * [2.3 Create account by privatekey](#23-create-account-by-privatekey)
        * [2.4 Create account by WIF](#24-create-account-by-wif)
        * [2.5 Address](#25-address)
    * [3. Native asset](#3-native-asset)
        * [3.1 ONT transfer](#31-ont-transfer)
        * [3.2 ONG transfer](#32-ong-transfer)
        * [3.3 Withdraw ONG](#withdraw-ong)
        * [3.4 Make transfer by yourself](#33-make-transfer-by-yourself)
            * [Transfer](#transfer)
            * [Signature](#signature)
            * [Multi-state signature](#multi-state-signature)
    * [4. Digital identity](#4-digital-identity)
        * [4.1 Registry](#41-registry)
        * [4.2 Query identity](#42-query-identity)
        * [4.3 Identity keystore](#identity-keystore)
    * [5. Node Stake](#5-node-stake)
        * [5.1 Register Candidate Node](#51-register-candidate-node)
        * [5.2 Unregister Candidate](#52-unregister-candidate)
        * [5.3 Withdraw](#53-withdraw)
        * [5.4 Quit Node](#54-quit-node)
* [Native contract address](#native-contract-address)		


​
# Wallet Integration

The wallet function includes digit asset account ant digital identity. [Wallet Specification](Wallet_Specification_en.md)

Wallet function list:

| Module                |                    Sub Module                    |     Test case      |
| ------------------    | :----------------------------------------------: | :------------------: |
| Wallet management    |           create                                 |     Use the mnemonic words when creating wallet(Based on BIP39 and BIP44 specifications)   |
|                       |          export                                 |    Export keystore      |
|                      |           import                                 |   Import keystore to wallet  |
|                      |                                                  |   Import from the mnemonic words  |
|                      |                                                  |   Import from private key      |
|                      |                                                  |    Import from WIF            |
|                      |         delete                                   |   Delete wallet account     |
|                      |        Information service                      |    Query balance of ONT&ONG |
|                      |                                                  |   Query details of ONT&ONG  |
|                      |                                                  |  Query unclaim ONT&ONG   |
|    Transfer Assets   |          Transfer                                |    ONT/ONG transfer        |
|                      |                                                  |      ONG Claim              |
|   ONT ID management  |         Create                                   |   Create a new ONT ID and write onto blockchain   |
|                      |        Import                                    |     Import keystore of ONT ID |
|                      |        Export                                    |     Export keystore of ONT ID |
|                      |       Information service                        |    Query ONT ID events , create, delete,etc.    |
|                      |                                                  |    Query ONT ID             |



These sdk implementations wallet specification Currently:

Java SDK ：[Java SDK](https://github.com/ontio/ontology-java-sdk/blob/master/docs) 

Typescript SDK ：[Ts SDK](https://github.com/ontio/ontology-ts-sdk/tree/master/docs) 

Android SDK ：[Android SDK](https://github.com/ontio-community/ontology-andriod-sdk)

Golang SDK ：[Go SDK](https://github.com/ontio/ontology-go-sdk) 

Python SDK ：[Python SDK](https://github.com/ontio/ontology-python-sdk)


# Java Sdk Tutorial

The example below is in Java, android sdk the same with java sdk.

## 1. BlockChain

### 1.1 Initial

```
String ip = "http://polaris1.ont.io"; //test net
String ip = "http://dappnode1.ont.io"; //main net
String rpcUrl = ip + ":" + "20336";
OntSdk ontSdk = OntSdk.getInstance();
ontSdk.setRpc(rpcUrl);
ontSdk.setDefaultConnect(ontSdk.getRpc());

```

### 1.2 Query

#### Query Unbound ong

There is one useful api from our explorer that can be used to query all the balance of an address.It includes

ONT, ONG, claimable ONG and unbound ONG.

For testnet, api host is  https://polarisexplorer.ont.io

For mainnet, dapi host is https://explorer.ont.io

````
/api/v1/explorer/address/balance/{address}
method：GET
{
    "Action": "QueryAddressBalance",
    "Error": 0,
    "Desc": "SUCCESS",
    "Version": "1.0",
    "Result": [
        {
            "Balance": "138172.922008484",
            "AssetName": "ong"
        },
        {
            "Balance": "14006.83021186",
            "AssetName": "waitboundong"// This is the unbound ONG
        },
        {
            "Balance": "71472.14798338",
            "AssetName": "unboundong" // This is the claimable ONG
        },
        {
            "Balance": "8637767",
            "AssetName": "ont"
        }
    ]
}
````

#### Query Transaction history

We can use the explorer api to fetch the transaction history of an address with pagination.

````
url：/api/v1/explorer/address/{address}/{assetname}/{pagesize}/{pagenumber}
method：GET
successResponse：
{
    "Action":"QueryAddressInfo",
    "Version":"1.0",
    "Error":0,
    "Desc":"SUCCESS",
    "Result":{
        "AssetBalance":[
            {
                "AssetName":"ont",
                "Balance":"123.200000000"
            }
        ],
        "TxnTotal":20,
        "TxnList":[
            {
                "TxnHash":"09e599ecde6eec18608bdecd0cf0a54b02bc9d55239e1b1bd291558e5a6ef3fa",
                "ConfirmFlag":1,
                "TxnType":208,
                "TxnTime":1522207168,
                "Height":11,
                "Fee":"0.010000000",
                "BlockIndex":1,
                "TransferList": [
                    {
                        "Amount": "100.000000000",
                        "FromAddress": "AA5NzM9iE3VT9X8SGk5h3dii6GPFQh2vme",
                        "ToAddress":"AA8fwY3wWhit3bnsAKRdoiCsKqp2qr4VBx",
                        "AssetName":"ont"
                    }
                ]
            }
        ]
    }
}
````


### 1.3 Other interface：


| No   |                    Main   Function                     |     Description      |
| ---- | :----------------------------------------------------: | :------------------: |
| 1    |           ontSdk.getConnect().getNodeCount()           |     node count     |
| 2    |            ontSdk.getConnect().getBlock(15)            |        get block        |
| 3    |          ontSdk.getConnect().getBlockJson(15)          |        get block in json        |
| 4    |       ontSdk.getConnect().getBlockJson("blockhash")       |        get block by blockhash       |
| 5    |         ontSdk.getConnect().getBlock("blockhash")         |        get block by blockhash       |
| 6    |          ontSdk.getConnect().getBlockHeight()          |     get Block Height     |
| 7    |      ontSdk.getConnect().getTransaction("txhash")      |       get Transaction       |
| 8    | ontSdk.getConnect().getStorage("contractaddress", key) |   get Storage   |
| 9   |       ontSdk.getConnect().getBalance("address")        |       get Balance       |
| 10   | ontSdk.getConnect().getContractJson("contractaddress") |     get Contract     |
| 11   |       ontSdk.getConnect().getSmartCodeEvent(59)        |   get SmartContract Event   |
| 12   |    ontSdk.getConnect().getSmartCodeEvent("txhash")     |   get SmartContract Event   |
| 13   |  ontSdk.getConnect().getBlockHeightByTxHash("txhash")  |   get Block Height of Tx Hash   |
| 14   |      ontSdk.getConnect().getMerkleProof("txhash")      |    get Merkle Proof    |
| 15   | ontSdk.getConnect().sendRawTransaction("txhexString")  |       send Raw Transaction       |
| 16   |  ontSdk.getConnect().sendRawTransaction(Transaction)   |       send Raw Transaction       |
| 17   |    ontSdk.getConnect().sendRawTransactionPreExec()     |    send RawTransaction PreExec    |
| 18   |  ontSdk.getConnect().getAllowance("ont","from","to")   |    get Allowance    |
| 19   |        ontSdk.getConnect().getMemPoolTxCount()         | getMemPoolTxCount |
| 20   |        ontSdk.getConnect().getMemPoolTxState("")         | getMemPoolTxState |


#### Query ONT/ONG balance

```
ontSdk.getConnect().getBalance("AVcv8YBABi9m6vH7faq3t8jWNamDXYytU2");

ont：
System.out.println(ontSdk.nativevm().ont().queryName());
System.out.println(ontSdk.nativevm().ont().querySymbol());
System.out.println(ontSdk.nativevm().ont().queryDecimals());
System.out.println(ontSdk.nativevm().ont().queryTotalSupply());

ong：
System.out.println(ontSdk.nativevm().ong().queryName());
System.out.println(ontSdk.nativevm().ong().querySymbol());
System.out.println(ontSdk.nativevm().ong().queryDecimals());
System.out.println(ontSdk.nativevm().ong().queryTotalSupply());



```

#### Query transaction in transaction pool

```
ontSdk.getConnect().getMemPoolTxState("d441a967315989116bf0afad498e4016f542c1e7f8605da943f07633996c24cc")


response in pool:

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

or not in pool

{
    "Action": "getmempooltxstate",
    "Desc": "UNKNOWN TRANSACTION",
    "Error": 44001,
    "Result": "",
    "Version": "1.0.0"
}

```

#### Query transaction success

query smartcontract event: 

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
                "ContractAddress": "0100000000000000000000000000000000000000",
                "States": [
                    "transfer",
                    "Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT",
                    "AS3SCXw8GKTEeXpdwVw7EcC4rqSebFYpfb",
                    1000000000
                ]
            }
        ]
    },
    "Version": "1.0.0"
}

```

query smartcontract event by block height

```
ontSdk.getConnect().getSmartCodeEvent(10)

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
                "ContractAddress": "0100000000000000000000000000000000000000",
                "States": [
                    "transfer",
                    "Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT",
                    "AS3SCXw8GKTEeXpdwVw7EcC4rqSebFYpfb",
                    1000000000
                ]
            }
        ]
    },
    "Version": "1.0.0"
}

```


## 2. Account




### 2.1 Mnemonic code and keystore

Users can use the menmonic code to create an account. The BIP44 path Ontology uses is "m/44'/1024'/0'/0/0".

Mnemonic code
```

//generate Mnemonic Code
String code = MnemonicCode.generateMnemonicCodesStr();

//get private keyfrom Mnemonic Code
byte[] prikey = MnemonicCode.getPrikeyFromMnemonicCodesStrBip44(code);
System.out.println(Helper.toHexString(prikey));

//create account
com.github.ontio.sdk.wallet.Account acct = ontSdk.getWalletMgr().createAccountFromPriKey("name",prikey,"password");

```

Keystore is  a data structure to backup user's account.And it can saved in QR code.Then users can use mobile to scan that QR code to read the data and recover the account. You can check the [Wallet Specification](Wallet_Specification_en.md) to see more info.

```
//get keystore
Scrypt scrypt = new Scrypt();
com.github.ontio.sdk.wallet.Account account = OntSdk.getInstance().getWalletMgr().getWallet().getAccount("address");
//TODO change scrypt and account value

//export keystore
Map keystore = WalletQR.exportAccountQRCode(scrypt,account);
System.out.println(JSON.toJSONString(keystore));

//import keystore
String prikey2 = WalletQR.getPriKeyFromQrCode(JSON.toJSONString(keystore),"password");

//
Account acct2 = new Account(prikey2,SignatureScheme.SHA256WITHECDSA);
 ```

import keystore

 ```
 
String prikey2 = WalletQR.getPriKeyFromQrCode(JSON.toJSONString(keystore),"password");

 ```

### 2.2 Random create account


```
com.github.ontio.sdk.wallet.Account acct = ontSdk.getWalletMgr().createAccount("name","password");
ontSdk.getWalletMgr().writeWallet();
```

remove account from wallet:

```

ontSdk.getWalletMgr().getWallet().removeAccount("")
ontSdk.getWalletMgr().writeWallet();

```

### 2.3 Create account by privatekey


```
com.github.ontio.sdk.wallet.Account acct = ontSdk.getWalletMgr().createAccountFromPriKey("name",prikey,"password");
ontSdk.getWalletMgr().writeWallet();
```

### 2.4 Create account by WIF

```

byte[] prikey = com.github.ontio.account.Account.getPrivateKeyFromWIF("");
com.github.ontio.sdk.wallet.Account acct = ontSdk.getWalletMgr().createAccountFromPriKey("name",prikey,"password");
ontSdk.getWalletMgr().writeWallet();

```



### 2.5 Address

single signature address and multi-signature address

```

String privatekey0 = "c19f16785b8f3543bbaf5e1dbb5d398dfa6c85aaad54fc9d71203ce83e505c07";
String privatekey1 = "49855b16636e70f100cc5f4f42bc20a6535d7414fb8845e7310f8dd065a97221";
String privatekey2 = "1094e90dd7c4fdfd849c14798d725ac351ae0d924b29a279a9ffa77d5737bd96";

//
com.github.ontio.account.Account acct0 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey0), ontSdk.defaultSignScheme);
Address sender = acct0.getAddressU160();

com.github.ontio.sdk.wallet.Account acct = ontSdk.getWalletMgr().createAccountFromPriKey("name",prikey,"password");
acct.address

//base58 address decode
sender = Address.decodeBase58("AVcv8YBABi9m6vH7faq3t8jWNamDXYytU2")；

multi-signature address：
Address recvAddr = Address.addressFromMultiPubKeys(2, acct1.serializePublicKey(), acct2.serializePublicKey());


```

| Function                  | Params                      | Desc                       |
| :---------------------- | :------------------------ | :----------------------------- |
| addressFromMultiPubkeys | int m,byte\[\]... pubkeys | M,pubkey |



## 3. Native asset



### 3.1 ONT tansfer

example：[demo](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/OntDemo.java)

```
String hash = ontSdk.nativevm().ont().sendTransfer(acct0,"AUe2KKPnNMnM7hLHj6dEPJ4PA2m4pyJt2d",200,payerAcct,20000,500);

```
| Function       | Params                                                     | Desc                       |
| :----------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| sendTransfer | String sendTransfer(Account sendAcct, String recvAddr, long amount, Account payerAcct, long gaslimit, long gasprice) | sendAcct,recvAddr,amount,payer,gaslimit,gasprice |



### 3.2 ONG transfer

example：[demo](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/OngDemo.java)



same to ONT：

```
String hash = ontSdk.nativevm().ong().sendTransfer(acct0,"AUe2KKPnNMnM7hLHj6dEPJ4PA2m4pyJt2d",200,payerAcct,20000,500);

```

### 3.3 Withdraw ONG

1. query unboundOng
2. withdrawOng

```
query unboundOng:
String addr = acct0.getAddressU160().toBase58();
String ong = sdk.nativevm().ong().unboundOng(addr);

//withdrawOng
com.github.ontio.account.Account account = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey0), ontSdk.signatureScheme);
String hash = sdk.nativevm().ong().withdrawOng(account,toAddr,64000L,payerAcct,30000,500);

```

| Function      | Params                      | Desc                       |
| :----------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| withdrawOng | String claimer,String to,long amount,String payer,long gaslimit,long gasprice | from,to,amount,payer,gaslimit,gasprice |




## 3.4 Make transfer by yourself

example：[demo](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/MakeTxWithoutWalletDemo.java)

#### Transfer

```

Address sender = acct0.getAddressU160();
Address payer = acct1.getAddressU160();
Address recvAddr = acct1;

//Address recvAddr = Address.addressFromMultiPubKeys(2, acct1.serializePublicKey(), acct2.serializePublicKey());


long amount = 1000;
Transaction tx = ontSdk.nativevm().ont().makeTransfer(sender.toBase58(),recvAddr.toBase58(), amount,payer.toBase58(),30000,0);


ontSdk.signTx(tx, new com.github.ontio.account.Account[][]{{acct0}});//sender
ontSdk.addSign(tx,new com.github.ontio.account.Account[][]{{acct1}});//payer

ontSdk.getConnect().sendRawTransaction(tx.toHexString());


```



| Function      | Params                      | Desc                       |
| :----------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| makeTransfer | String sender，String recvAddr,long amount,String payer,long gaslimit,long gasprice | sender,to,amount,payer,gaslimit,gasprice |
| makeTransfer | State\[\] states,String payer,long gaslimit,long gasprice    | multi state                                   |

#### Signature

if sender is different with payer, both of them need signature transaction.

```
1.add Sign
ontSdk.addSign(tx,acct0);

2.add MultiSign if address is MultiSign address
ontSdk.addMultiSign(tx,2,new com.github.ontio.account.Account[]{acct0,acct1});

```



#### Multi-state transfer

1. contruct multi state
2. signature

```
Address sender1 = acct0.getAddressU160();
Address sender2 = Address.addressFromMultiPubKeys(2, acct1.serializePublicKey(), acct2.serializePublicKey());
int amount = 10;
int amount2 = 20;

State state = new State(sender1, recvAddr, amount);
State state2 = new State(sender2, recvAddr, amount2);
Transaction tx = ontSdk.nativevm().ont().makeTransfer(new State[]{state1,state2},sender1.toBase58(),30000,0);

//signature：
ontSdk.signTx(tx, new com.github.ontio.account.Account[][]{{acct0}});
ontSdk.addMultiSign(tx,2,new com.github.ontio.account.Account[]{acct1, acct2});

```



## 4. Digital identity

#### 4.1 Registry

example：[demo](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/NativeOntIdDemo.java)

```

Identity identity = ontSdk.getWalletMgr().createIdentity(password);
ontSdk.nativevm().ontId().sendRegister(identity,password,payerAcct,ontSdk.DEFAULT_GAS_LIMIT,0);
 
```

#### 4.2 Query identity

example：[demo](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/NativeOntIdDemo.java)

```

String ddo2 = ontSdk.nativevm().ontId().sendGetDDO(identity.ontid);
 
```

#### 4.3 Identity keystore

export keystore

```
//export keystore
Scrypt scrypt = new Scrypt();
com.github.ontio.sdk.wallet.Identity identity = OntSdk.getInstance().getWalletMgr().getWallet().getIdentity("ontid");
Map keystore = WalletQR.exportIdentityQRCode(scrypt,identity);
System.out.println(JSON.toJSONString(keystore));


 ```

import keystore

 ```
 
String prikey2 = WalletQR.getPriKeyFromQrCode(JSON.toJSONString(keystore),"password");

 ```


## 5. Node Stake

### 5.1 Register Candidate Node

Make transaction to register candidate node.

````

//@param ontid {string} User's ONT ID
//@param peerPubkey {string} Peer's public key
//@param keyNo {int} Id of public key.Usually set as 1.
//@param payerAcct {Address} User's address to pay fee
//@param initPos {long} Number of ONT to pay for register

String peerPubkey = Helper.toHexString(account8.serializePublicKey());
String txhash = sdk.nativevm().governance().registerCandidate(account,peerPubkey,initPos,identity.ontid,password,identity.controls.get(0).getSalt(),keyNo,payerAcct,gasLimit,gasPrice);

````

### 5.2 Unregister Candidate

Make transaction to cancel the register.

```
String peerPubkey = Helper.toHexString(account8.serializePublicKey());
String txhash = sdk.nativevm().governance().unRegisterCandidate(account,peerPubkey,payerAcct,gasLimit,gasPrice);

```

### 5.3 Withdraw 

Make transaction to withdraw the paied ONT.

```

String[] peerPubkeys = new String[]{"03e1e09221c9f513df76273f3cec0d033ee6056b159300d7b1072fc7020eadccbb"};
String txhash = sdk.nativevm().governance().withdraw(account,peerPubkeys,new long[]{9999},payerAcct,gasLimit,gasPrice);

```

### 5.4 Quit Node

Make transaction to quit node.

```
String[] peerPubkeys = new String[]{"03e1e09221c9f513df76273f3cec0d033ee6056b159300d7b1072fc7020eadccbb"};
String txhash = sdk.nativevm().governance().quitNode(account,peerPubkey,payerAcct,gasLimit,gasPrice);

```



# Native contract address

contract | contract u160 address | Address
---|---|---
ONT Token | 0000000000000000000000000000000000000001| AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV
ONG Token | 0000000000000000000000000000000000000002 | AFmseVrdL9f9oyCzZefL9tG6UbvhfRZMHJ
ONT ID | 0000000000000000000000000000000000000003 | AFmseVrdL9f9oyCzZefL9tG6Ubvho7BUwN
Global Params | 0000000000000000000000000000000000000004 | AFmseVrdL9f9oyCzZefL9tG6UbvhrUqmc2
Oracle | 0000000000000000000000000000000000000005 | AFmseVrdL9f9oyCzZefL9tG6UbvhzQYRMK
Authorization Manager(Auth) | 0000000000000000000000000000000000000006 | AFmseVrdL9f9oyCzZefL9tG6Ubvi9BuggV
Governance | 0000000000000000000000000000000000000007 | AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK
DDXF(Decentralized Exchange) | 0000000000000000000000000000000000000008 | AFmseVrdL9f9oyCzZefL9tG6UbviKTaSnK



