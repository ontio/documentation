---
title:
keywords: sample homepage
sidebar: Wallet_zh
permalink: ontology_wallet_dev_ts_sdk_zh.html
folder: doc_zh/Wallet
giturl: https://github.com/ontio/documentation/blob/master/walletDevDocs/ontology_wallet_dev_ts_sdk_zh.md
---




<h1 align="center">钱包集成</h1>
<p align="center" class="version">Version 1.0.0 </p>

内容:
* [钱包集成](#钱包集成)
* [Typescript Sdk 教程](#typescript-sdk-教程)
  * [1. 钱包](#1-钱包)
  * [2. 资产账户](#2-资产账户)
  * [3. Native 资产](#3-native-资产)
  * [4. 与链交互](#4-与链交互)
  * [5. 节点质押](#4-节点质押)
* [Native 合约地址](#native-合约地址)

<h1 align="center">钱包集成</h1>





钱包包括资产账户和身份两部分.详情请参考文档 [钱包规范](Wallet_Specification_cn.md)

钱包集成需要完成如下功能:

| 模块                |                    子模块                    |     测试用例     |
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



这些SDK已经完成了钱包规范:

Java SDK ：[Java SDK](https://github.com/ontio/ontology-java-sdk/blob/master/docs) 

Typescript SDK ：[Ts SDK](https://github.com/ontio/ontology-ts-sdk/tree/master/docs) 

Android SDK ：[Android SDK](https://github.com/ontio-community/ontology-andriod-sdk)

Golang SDK ：[Go SDK](https://github.com/ontio/ontology-go-sdk) 

Python SDK ：[Python SDK](https://github.com/ontio/ontology-python-sdk)

# 1 钱包

Wallet is a data storing file in JSON format. In Ontology, Wallet can store not only the digital identity but also digital assets.

[Wallet Specification]()


## 1.1 创建钱包

Users could create their wallet from scratch.

Users only need to pass the name of their wallets.

````
import {Wallet} from 'ontology-ts-sdk';
var wallet = Wallet.create('my_wallet')
````

## 1.2 钱包管理

添加资产账户

````
wallet.addAccount(account)

````

# 2 资产账户


## 2.1 创建随机账户

根据不同算法随机创建账户:

* ECDSA
* SM2
* EDDSA

 默认使用ECDSA。


````
import {Account, Crypto} from 'ontology-ts-sdk';

cont keyType = Crypto.KeyType.ECDSA;
const privateKey = Crypto.PrivateKey.random();
const params = {
    cost: 4096,
    blockSize: 8,
    parallel: 8,
    size: 64
}
var account = Account.create( privateKey, password, name, params );

wallet.addAccount(account)

````

|  Param    | Desc  |
|:--------    |:--   |
|   privateKey      | An instance of class PrivateKey..|
|   password      | User's password to encrypt the private key. |
|   name       |  Name of the account. |
|   params   | Parameters used to encrypt the privatekey. |


## 2.2 导入账户

导入账户.

````
import { Account } from 'ontology-ts-sdk'
//@param label {string} Name of the account
//@param encryptedPrivateKey {PrivateKey} The encrypted private key
//@param password {string} The password used to decrypt private key
//@param address {Address} The address of the account
//@param saltBase64 {string} The salt in base64 format
//@param params {ScryptParams} Optional scrypt params to decrypt private key
var account;
try {
    account = Account.importAccount(label, encryptedPrivateKey, password, address, saltBase64, params);
} catch(error) {
    //password or private key incorrect
}
````

## 2.3 通过助记词创建账户

通过助记词创建账户. BIP44 path ： "m/44'/1024'/0'/0/0".

````
import { Account } from 'ontology-ts-sdk';
//@param label {string} Name of the account;
//@param mnemonic {string} User's mnemonic;
//@param password {string} Usr's password to encrypt the private key
//@param params? {ScryptParams} Optional scrypt params to encrypt the private key
var account;
try {
    account = Account.importWithMnemonic(label, mnemonic, password, params);
} catch(error) {
    //mnemonic is invalid
}
````

### 如何产生助记词?

```
import { utils } from 'ontology-ts-sdk'
//@param size {number} The length of bytes for derived key.16 is the default value.
const mnemonic = utils.generateMnemonic(size);
```

### 如果从助记词获取到私钥?

```
import {Crypto} from 'ontology-ts-sdk'
//@param mnemonic {string} Space separated words
//@param derivePath {string} Default value is "m/44'/1024'/0'/0/0"
const privateKey = Crypto.PrivateKey.generateFromMnemonic(mnemonic, derivePath)
```

## 2.4 通过WIF创建账号 

````
import {Crypto, Account} from 'ontology-ts-sdk';
//@param wif {string} User's WIF
//@param password {string} User's password
//@param name {string} Name of account;
//@param params {ScryptParams} Optional scrypt params to encrypt the private key

//get private key from WIF
const privateKey = Crypto.PrivateKey.deserializeWIF(wif);
const account = Account.create(privateKey, password, name, params);
````

## 2.5 导入导出 keystore

请参考Keystore数据结构，  [Wallet Specification](Wallet_Specification_en.md)

#### 导出 keystore

````
//Suppose we have an account object
//export keystore
const keystore = {
            type: 'A', // Implies this is an account 
            label: obj.label, // Name of the account
            algorithm: 'ECDSA', // The algorithm of the key-pair generation
            scrypt: { // Scrypt parameters used to encrypt the private key
                n: 4096,
                p: 8,
                r: 8,
                dkLen: 64
            },
            key: obj.encryptedKey.key, //Encrypted private key
            salt: obj.salt, // Salt used to encrypt private key
            address: obj.address.toBase58(), // Address used to encrypt private key
            parameters: { // Parameters used in key-pair generation algorithm
                curve: 'secp256r1'
            }
        };

````

#### 导入 keystore

请参考 **2.2 Import An Account**

# 3 Native 资产

Native 资产包括: ONT 和 ONG.

````
TOKEN_TYPE = {
  ONT : 'ONT',  //Ontology Token
  ONG : 'ONG'   //Ontology Gas
}
````

## 3.1 查询 

包括多种方式查询

### 3.1.1 查询余额
````typescript
const address = new Address('AXpNeebiUZZQxLff6czjpHZ3Tftj8go2TF');
const nodeUrl = 'http://polaris1.ont.io:20334' // Testnet
const rest = new RestClient(nodeUrl); // Query the balance on testnet
rest.getBalance(address).then(res => {
	console.log(res)
})
````


### 3.1.2 查询 Unbound ong

通过地址查询余额，ONT, ONG, claimable ONG and unbound ONG.

测试网服务器  https://polarisexplorer.ont.io

主网服务器 https://explorer.ont.io

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

### 3.1.3 查询交易历史

We can use the explorer api to fetch the transaction history of an address with pagination.

````
url：/api/v1/explorer/address/{address}/{pagesize}/{pagenumber} or /api/v1/explorer/address/{address}/{assetname}/{pagesize}/{pagenumber}
method：GET
successResponse：
{
    "Action": "QueryAddressInfo",
    "Error": 0,
    "Desc": "SUCCESS",
    "Version": "1.0",
    "Result": {
        "AssetBalance": [
            {
                "Balance": "1.93199363",
                "AssetName": "ong"
            },
            {
                "Balance": "0.0020775",
                "AssetName": "waitboundong"
            },
            {
                "Balance": "0.0019375",
                "AssetName": "unboundong"
            },
            {
                "Balance": "1500",
                "AssetName": "ont"
            }
        ],
        "TxnList": [
            {
                "TxnTime": 1535894950,
                "TxnType": 209,
                "ConfirmFlag": 1,
                "Fee": "0.010000000",
                "TxnHash": "a8a75e3d44e5aff5de6dabcbee1492c89da1561e244da47327f178956b7c0015",
                "Height": 261617,
                "BlockIndex": 1,
                "TransferList": [
                    {
                        "FromAddress": "AUmzW4MYCtDakB59hFybV7aGFZVi2S7FLc",
                        "Amount": "1.000000000",
                        "ToAddress": "AUmzW4MYCtDakB59hFybV7aGFZVi2S7FLc",
                        "AssetName": "ont"
                    }
                ]
            },
            {
                "TxnTime": 1535310138,
                "TxnType": 209,
                "ConfirmFlag": 1,
                "Fee": "0.010000000",
                "TxnHash": "819a67b5c7c29fd234178ba9b901c6ed5af0734bafc76ffba6d1380cf2e07e8e",
                "Height": 218711,
                "BlockIndex": 1,
                "TransferList": [
                    {
                        "FromAddress": "AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV",
                        "Amount": "1.627527000",
                        "ToAddress": "AUmzW4MYCtDakB59hFybV7aGFZVi2S7FLc",
                        "AssetName": "ong"
                    }
                ]
            }
        ],
        "TxnTotal": 33
    }
}
````

## 3.2 资产转账

### 创建转账交易

创建转账交易. 

````typescript
import {OntAssetTxBuilder} from 'ontology-ts-sdk'
//supppose we have an account with enough ONT and ONG
//Sender's address, instance of class Address
const from = account.address;
//Receiver's address
const to = new Address('AXpNeebiUZZQxLff6czjpHZ3Tftj8go2TF')
//Amount to send
const amount = 100
//Asset type
const assetType = 'ONT'
//Gas price and gas limit are to compute the gas costs of the transaction.
const gasPrice = '500';
const gasLimit = '20000';
//Payer's address to pay for the transaction gas
const payer = from;
const tx = OntAssetTxBuilder.makeTransferTx(assetType, from, to, amount, gasPrice, gasLimit, payer);
````

|  参数    | 描述  |
|:--------    |:--   |
|   assetType      | ONT or ONG.|
|   from      | Sender's address to withdraw ONG.|
|   to       |  Receiver's address to receive ONG.|
|   amount   | ONG  Need to multiply 1e9 to keep precision.|
|   gasPrice | Gas price.|
|   gasLimit | Gas limit.|
|   payer | Payer's address to pay for the transaction gas.|


## 3.3 提取 ong

### 创建 withdraw 交易

.

````typescript
import {OntAssetTxBuilder} from 'ontology-ts-sdk'

//suppose we have an account already
const from = account.address;
const to = account.address;
const amount = 10 * 1e9;
const gasPrice = '500';
const gasLimit = '20000';
const payer = account.address;
const tx = OntAssetTxBuilder.makeWithdrawOngTx(from, to, amount, payer, gasPrice, gasLimit);
````

|  参数    | 描述  |
|:--------    |:--   |
|   from      | Sender's address to withdraw ONG.|
|   to       |  Receiver's address to receive ONG.|
|   amount   | ONG  Need to multiply 1e9 to keep precision.|
|   gasPrice | Gas price.|
|   gasLimit | Gas limit.|
|   payer | Payer's address to pay for the transaction gas.|

## 3.4 签名和发送交易

通过私钥做签名


> RestClient.getSmartCodeEvent

````typescript
//sign transaction before send it
import {RestClient, CONST, TransactionBuilder} from 'ontology-ts-sdk'

//we already got the transaction we created before

//we have to sign the transaction before sent it
//Use user's private key to sign the transaction
TransactionBuilder.signTransaction(tx, privateKey)
//If the transaction needs more than one signatures. We can add signature to it.
//TransactionBuilder.addSign(tx, otherPrivateKey)

const rest = new RestClient(CONST.TEST_ONT_URL.REST_URL);
rest.sendRawTransaction(tx.serialize()).then(res => {
	console.log(res)	
})

````

> Use WebSocket API and wait for the transaction notice.

响应:

```
{ 
  Action: 'sendrawtransaction',
  Desc: 'SUCCESS',
  Error: 0,
  Result: 'dfc598649e0f3d9ff94486a80020a2775e1d474b843255f8680a3ac862c58741',
  Version: '1.0.0' 
}
```



## 4 与链交互 

可以通过restful，rpc，websocket与链交互。

```
import {RestClient} from 'ontology-ts-sdk'

const rest = new RestClient();

//@param hexData {string} Hex encoded data of transaction
//@param preExec {boolean} Default value is false.Decides if it is pre execution.
//@param userId {string} Not necessary
rest.sendRawTransaction(hexData, preExec, userId)

rest.getRawTransaction(txHash: string)

rest.getNodeCount()

rest.getBlockHeight()

rest.getContract(codeHash: string)

//Get the transaction execution result
//@param value {string|number} The transaction hash or the block height.
rest.getSmartCodeEvent(value: string | number)

rest.getStorage(codeHash: string, key: string)

rest.getBalance(address: Address)

rest.getAllowance(asset: string, from: Address, to: Address)
```

## 5 节点质押

### 5.1 注册候选节点

注册候选节点.

````
import {GovernanceTxBuilder} from 'ontology-ts-sdk'

//@param ontid {string} User's ONT ID
//@param peerPubkey {string} Peer's public key
//@param keyNo {number} Id of public key.Usually set as 1.
//@param userAddr {Address} User's address to pay the ONT and ONG for register
//@param initPos {number} Number of ONT to pay for register
//@param payer {Address} User's address to pay for the transaction fee.
//@param gasPrice {string} Usually set as '500'
//@param gasLimit {string} Usually set as '20000'
const tx = GovernanceTxBuilder.makeRegisterCandidate(ontid, peerPubkey, keyNo, userAddr, initPos, payer, gasPrice, gasLimit)
````

### 5.2 取消注册

取消注册.

```
import {GovernanceTxBuilder} from 'ontology-ts-sdk'

//@param userAddr {Address} User's address that paied for the register
//@param peerPubkey {string} Peer's public key
//@param payer {Address} Payer to pay for the transaction fee.
//@param gasPrice {string} Usually set as '500'
//@param gasLimit {string} Usually set as '20000'
const tx = GovernanceTxBuilder.makeUnregisterCandidateTx(userAddr, peerPubkey, payer, gasPrice, gasLimit)
```

### 5.3 提取 

提取 ONT.

```
import {GovernanceTxBuilder} from 'ontology-ts-sdk'

//@param userAddr {Address} User's address that paied for the register
//@param peerPubkeys {[string]} Array of peer's public keys
//@param withdrawList {[number]} Array of ONT to withdraw
//@param payer {Address} Payer to pay for the transaction fee.
//@param gasPrice {string} Usually set as '500'
//@param gasLimit {string} Usually set as '20000'
const tx = GovernanceTxBuilder.makeWithdrawTx(userAddr, peerPubkeys, withdrawList, payer, gasPrice, gasLimit)
```

### 5.4 退出

退出.

```
import {GovernanceTxBuilder} from 'ontology-ts-sdk'

//@param userAddr {Address} User's address that paied for the register
//@param peerPubkey {string} Array of peer's public keys
//@param payer {Address} Payer to pay for the transaction fee.
//@param gasPrice {string} Usually set as '500'
//@param gasLimit {string} Usually set as '20000'
const tx = GovernanceTxBuilder.makeQuitNodeTx(userAddr, peerPubkey, payer, gasPrice, gasLimit)
```

# Native 智能合约

contract | contract u160 address | Address
---|---|---
ONT Token | 0100000000000000000000000000000000000000| AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV
ONG Token | 0200000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbvhfRZMHJ
ONT ID | 0300000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6Ubvho7BUwN
Global Params | 0400000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbvhrUqmc2
Oracle | 0500000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbvhzQYRMK
Authorization Manager(Auth) | 0600000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6Ubvi9BuggV
Governance | 0700000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK
DDXF(Decentralized Exchange) | 0800000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbviKTaSnK