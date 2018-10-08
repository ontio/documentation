---
title:
keywords: sample homepage
sidebar: Wallet_en
permalink: ontology_wallet_dev_ts_sdk_en.html
folder: doc_en/Wallet
giturl: https://github.com/ontio/documentation/blob/master/walletDevDocs/ontology_wallet_dev_ts_sdk_en.md
---

English / [中文](./ontology_wallet_dev_ts_sdk_zh.html)



<h1 align="center">iOS Wallet Integration</h1>
<p align="center" class="version">Version 1.0.0 </p>

The outline of this document is as follows:
* [Typescript Sdk Tutorial](#typescript-sdk-tutorial)
  * [1. Wallet](#1-wallet)
  * [2. Account](#2-account)
  * [3. Native Asset](#3-native-asset)
  * [4. Blockchain](#4-blockchain)
  * [5. Node Stake](#5-node-stake)
  * [6. Stake Authorization](#6-stake-authorization)


## 1 Wallet

Wallet is a data storing file in JSON format. In Ontology, Wallet can store not only the digital identity but also digital assets.

[Wallet Specification](./Wallet_File_Specification_en.html)


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

<h1 align="center">2 Account</h1>




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

Keystore is  a data structure to backup user's account.And it can saved in QR code.Then users can use mobile to scan that QR code to read the data and recover the account. You can check the [Wallet Specification](./Wallet_File_Specification_en.html) to see more info.

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

## 6. Stake Authorization

### 6.1 Query nodes that allow stake authorization

```
import {GovernanceTxBuilder} from 'ontology-ts-sdk'
const url = 'http://polaris1.ont.io:20334';
const peerMap = await GovernanceTxBuilder.getPeerPoolMap(url)
```
The result returned is the details of all nodes.We need to handle the result for display.You can refer to the method in OWallet. [NodeAuthorization.js --> fetchNodeList()](https://github.com/ontio/OWallet/blob/master/src/renderer/store/modules/NodeAuthorization.js)

Now the nodes that allow stake authorization are as below:

```
{
    name: 'Dubhe',
    pk: '02bcdd278a27e4969d48de95d6b7b086b65b8d1d4ff6509e7a9eab364a76115af7'
  },
  {
    name: 'Merak',
    pk: '0251f06bc247b1da94ec7d9fe25f5f913cedaecba8524140353b826cf9b1cbd9f4'
  },
  {
    name: 'Phecda',
    pk: '022e911fb5a20b4b2e4f917f10eb92f27d17cad16b916bce8fd2dd8c11ac2878c0'
  },
  {
    name: 'Megrez',
    pk: '0253719ac66d7cafa1fe49a64f73bd864a346da92d908c19577a003a8a4160b7fa'
  },
  {
    name: 'Alioth',
    pk: '022bf80145bd448d993abffa237f4cd06d9df13eaad37afce5cb71d80c47b03feb'
  },
  {
    name: 'Mixar',
    pk: '02765d98bb092962734e365bd436bdc80c5b5991dcf22b28dbb02d3b3cf74d6444'
  },
  {
    name: 'Alkaid',
    pk: '03c8f63775536eb420c96228cdccc9de7d80e87f1b562a6eb93c0838064350aa53'
  }
```

### 6.2 Query the detail of stake authorization

```
//@param pk {string} Public key of the node to stake
//@param userAddr {Address} Address of user
//@param url Url of network to connect

import {GovernanceTxBuilder, Crypto} from 'ontology-ts-sdk'
const url = getNodeUrl();
const userAddr = new Crypto.Address(address);
const authorizeInfo = await GovernanceTxBuilder.getAuthorizeInfo(pk, userAddr, url)
```

```
class AuhtorizeInfo {
    peerPubkey: string = ''; //Node's public key
    address: Address; // User's wallet address
    consensusPos: number = 0; // Stake amount in consensus round
    freezePos: number = 0; // Stake amount in freeze status
    newPos: number = 0; // New stake amount
    withdrawPos: number = 0; // Stake amount locked in two round
    withdrawFreezePos: number = 0; Stake amount locked in one round
    withdrawUnfreezePos: number = 0; Claimable ONT
    }
```
> Total amount of stake authorization = consensusPos + freezePos + newPos

> Locked ONT = withdrawPos + withdrawFreezePos

> Claimable ONT = withdrawUnfreezePos

### 6.3 Query rewards of stake authorization

```
//@param userAddr {Address} User's wallet address
//@param url {string} Url of node

const url = getNodeUrl();
const userAddr = new Crypto.Address(address);        
const splitFee = await GovernanceTxBuilder.getSplitFeeAddress(userAddr, url)
```

```
class SplitFeeAddress {
    address: Address; // User's wallet address
    amount: number = 0; // Stake profit ONG number
}
```

> The amount should divide by 1e9.

### 6.4 Query unbound ONG

```
//@param addr {Address} User's wallet address
//@param url {string} Network's url

const url = getNodeUrl();
const addr = new Crypto.Address(address);
try {   
    let peerUnboundOng = await GovernanceTxBuilder.getPeerUnboundOng(addr, url);
    peerUnboundOng = new BigNumber(peerUnboundOng).div(1e9).toNumber();
    return peerUnboundOng;
} catch(err) {
    console.log(err);
}
```
> The result should divide by 1e9.


### 6.5 Authorize stake for some node

```
import {GovernanceTxBuilder, Crypto} from 'ontology-ts-sdk'

//@param userAddr {Address} User's wallet address
//@param pks {[string]} Array of nodes' public keys
//@param amounts {[number]} Array of stake amounts
//@param payer {Address} Payer of the transaction
//@param GAS_PRICE {string} Normally set as 500
//@param GAS_LIMIT {string} Normally set as 20000

const userAddr = new Crypto.Address(this.stakeWallet.address)
const tx = GovernanceTxBuilder.makeAuthorizeForPeerTx(
    userAddr,
    pks,
    amounts,
    payer,
    GAS_PRICE,
    GAS_LIMIT
)
```
> User can stake some units.Stake amount = 500 ONT * units

### 6.6 Cancel the stake authorization of some node

```
import {GovernanceTxBuilder, Crypto} from 'ontology-ts-sdk'

//@param userAddr {Address} User's wallet address
//@param pks {[string]} Array of nodes' public keys
//@param amounts {[number]} Array of stake amounts
//@param payer {Address} Payer of the transaction
//@param GAS_PRICE {string} Normally set as 500
//@param GAS_LIMIT {string} Normally set as 20000

const userAddr = new Crypto.Address(this.stakeWallet.address);
const amount = Number(this.cancelAmount) * 500;
const tx = GovernanceTxBuilder.makeUnauthorizeForPeerTx(
    userAddr,
    pks,
    amounts,
    payer,
    GAS_PRICE,
    GAS_LIMIT
)
```
> The amount to cancel can not exceed the total amount in authorization.
> The amount to cancel = 500 * units


### 6.7 Redeem claimable ONT

```
import {GovernanceTxBuilder, Crypto} from 'ontology-ts-sdk'

//@param userAddr {Address} User's wallet address
//@param pks {[string]} Array of nodes' public keys
//@param amounts {[number]} Array of stake amounts
//@param payer {Address} Payer of the transaction
//@param GAS_PRICE {string} Normally set as 500
//@param GAS_LIMIT {string} Normally set as 20000

const tx = GovernanceTxBuilder.makeWithdrawTx(
	userAddr,
	pks,
	amounts,
	payer,
	GAS_PRICE,
	GAS_LIMIT
)
```

### 6.8 Redeem unbound ONG

```
import {GovernanceTxBuilder, Crypto} from 'ontology-ts-sdk'

//@param userAddr {Address} User's wallet address
//@param payer {Address} Payer of the transaction
//@param GAS_PRICE {string} Normally set as 500
//@param GAS_LIMIT {string} Normally set as 20000

const tx = GovernanceTxBuilder.makeWithdrawPeerUnboundOngTx(
    userAddr,
    payer,
    GAS_PRICE,
    GAS_LIMIT
)
```

### 6.9 Redeem rewards of stake authorization

```
import {GovernanceTxBuilder, Crypto} from 'ontology-ts-sdk'

//@param userAddr {Address} User's wallet address
//@param payer {Address} Payer of the transaction
//@param GAS_PRICE {string} Normally set as 500
//@param GAS_LIMIT {string} Normally set as 20000

const tx = GovernanceTxBuilder.makeWithdrawFeeTx(
    userAddr,
    payer,
    GAS_PRICE,
    GAS_LIMIT
)
```
