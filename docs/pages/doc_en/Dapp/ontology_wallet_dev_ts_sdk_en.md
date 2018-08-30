---
title:
keywords: sample homepage
sidebar: Dapp_en
permalink: ontology_wallet_dev_ts_sdk_en.html
folder: doc_en/Dapp
giturl: https://github.com/ontio/documentation/blob/master/walletDevDocs/ontology_wallet_dev_ts_sdk_en.md
---




<h1 align="center">Ontology Wallet Integration</h1>
<p align="center" class="version">Version 1.0.0 </p>

The outline of this document is as follows:
* [Wallet Integration](#wallet-integration)
* [Typescript Sdk Tutorial](#typescript-sdk-tutorial)
  * [1. Wallet](#1-wallet)
  * [2. Account](#2-account)
  * [3. Native Asset](#3-native-asset)
  * [4. Blockchain](#4-blockchain)
  * [5. Node Stake](#4-node-stake)
* [Native contract address](#native-contract-address)

<h1 align="center">Wallet Integration</h1>





The wallet function includes digit asset account ant digital identity. [wallet Specification]()

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

# 1 Wallet

Wallet is a data storing file in JSON format. In Ontology, Wallet can store not only the digital identity but also digital assets.

[Wallet Specification](Wallet_Specification_en.md)


## 1.1 Create a Wallet

Users could create their wallet from scratch.

Users only need to pass the name of their wallets.

````
import {Wallet} from 'ontology-ts-sdk';
var wallet = Wallet.create('my_wallet')
````

## 1.2 Manager Wallet

 add account

````
wallet.addAccount(account)

````

# 2 Account
Account is used to manage user's assets.


## 2.1 Create a random account

We can generate a random private key with specific keypair algorithm and elliptic curve. There are three kinds of algorithms we support:

* ECDSA
* SM2
* EDDSA

ECDSA is the default one. You can check TS SDK API reference for more info.

Then we can create the account and add it to the wallet.

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


## 2.2 Import an Account

Users can import an account by the backup data.

This method will check the password and the private key, an error will be thrown if they are not match.

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

## 2.3 Create an account from mnemonic code

Users can use the menmonic code to create an account. The BIP44 path Ontology uses is "m/44'/1024'/0'/0/0".

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

### How to generate mnemonic?

```
import { utils } from 'ontology-ts-sdk'
//@param size {number} The length of bytes for derived key.16 is the default value.
const mnemonic = utils.generateMnemonic(size);
```

### Genera private key from mnemonic?

```
import {Crypto} from 'ontology-ts-sdk'
//@param mnemonic {string} Space separated words
//@param derivePath {string} Default value is "m/44'/1024'/0'/0/0"
const privateKey = Crypto.PrivateKey.generateFromMnemonic(mnemonic, derivePath)
```

## 2.4 Create an account from WIF 

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

## 2.5 Import and export keystore

Keystore is  a data structure to backup user's account.And it can saved in QR code.Then users can use mobile to scan that QR code to read the data and recover the account. You can check the [Wallet Specification](Wallet_Specification_en.md) to see more info.

#### Export keystore

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

#### Import keystore

The process is the same as **2.2 Import An Account**

# 3 Native Asset

There are two kinds of native asset in Ontology: ONT and ONG.

In order to transfer native asset, we can create the specific transaction and send it to the blockchain. After the transaction has been packaged in the block, the transaction will succeed.

Type of native asset:
````
TOKEN_TYPE = {
  ONT : 'ONT',  //Ontology Token
  ONG : 'ONG'   //Ontology Gas
}
````

## 3.1 Query 

We can use RESTful API, RPC API and WebSocket API to query the balance. Here we use RESTful API as example. And we have explorer apis that are more easy to use.

### 3.1.1 Query Balance
````typescript
const address = new Address('AXpNeebiUZZQxLff6czjpHZ3Tftj8go2TF');
const nodeUrl = 'http://polaris1.ont.io:20334' // Testnet
const rest = new RestClient(nodeUrl); // Query the balance on testnet
rest.getBalance(address).then(res => {
	console.log(res)
})
````
The result contains balance of ONT and ONG.

### 3.1.2 Query Unbound ong

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

### 3.1.3 Query Transaction history

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

## 3.2 Transfer asset

### Create transfer transaction

First we need to create the transaction for transfer. 

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

|  Param    | Desc  |
|:--------    |:--   |
|   assetType      | ONT or ONG.|
|   from      | Sender's address to withdraw ONG.|
|   to       |  Receiver's address to receive ONG.|
|   amount   | ONG  Need to multiply 1e9 to keep precision.|
|   gasPrice | Gas price.|
|   gasLimit | Gas limit.|
|   payer | Payer's address to pay for the transaction gas.|


## 3.3 Withdraw ong

### Create withdraw transaction

Withdraw generated ONG from user's account address and send to other address. They can be the same address. Users can only withdraw the claimable ONG.

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

|  Param    | Desc  |
|:--------    |:--   |
|   from      | Sender's address to withdraw ONG.|
|   to       |  Receiver's address to receive ONG.|
|   amount   | ONG  Need to multiply 1e9 to keep precision.|
|   gasPrice | Gas price.|
|   gasLimit | Gas limit.|
|   payer | Payer's address to pay for the transaction gas.|

## 3.4 Sign and Send transaction

We use private key to sign transaction.

We can use RESTful API, RPC API, or WebSocket API to send a transaction. Here we use RESTful API as an example.


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

The result may look like:

```
{ 
  Action: 'sendrawtransaction',
  Desc: 'SUCCESS',
  Error: 0,
  Result: 'dfc598649e0f3d9ff94486a80020a2775e1d474b843255f8680a3ac862c58741',
  Version: '1.0.0' 
}
```

The `Result` of the response is the transaction hash, it can be used to query the event of the transaction.

Then we can query the balance to check if the transaction succeeded.

## 4 Blockchain 

Users can use restful api, rpc api or websocket api to access info from the blockchain.Here we use restful api for example.The result is promise.

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

## 5 Node Stake

### 5.1 Register Candidate Node

Make transaction to register candidate node.

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

### 5.2 Unregister Candidate

Make transaction to cancel the register.

```
import {GovernanceTxBuilder} from 'ontology-ts-sdk'

//@param userAddr {Address} User's address that paied for the register
//@param peerPubkey {string} Peer's public key
//@param payer {Address} Payer to pay for the transaction fee.
//@param gasPrice {string} Usually set as '500'
//@param gasLimit {string} Usually set as '20000'
const tx = GovernanceTxBuilder.makeUnregisterCandidateTx(userAddr, peerPubkey, payer, gasPrice, gasLimit)
```

### 5.3 Withdraw 

Make transaction to withdraw the paied ONT.

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

### 5.4 Quit Node

Make transaction to quit node.

```
import {GovernanceTxBuilder} from 'ontology-ts-sdk'

//@param userAddr {Address} User's address that paied for the register
//@param peerPubkey {string} Array of peer's public keys
//@param payer {Address} Payer to pay for the transaction fee.
//@param gasPrice {string} Usually set as '500'
//@param gasLimit {string} Usually set as '20000'
const tx = GovernanceTxBuilder.makeQuitNodeTx(userAddr, peerPubkey, payer, gasPrice, gasLimit)
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