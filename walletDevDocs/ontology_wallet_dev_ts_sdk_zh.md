[English](./ontology_wallet_dev_ts_sdk_en.html) / 中文



<h1 align="center">iOS钱包集成</h1>
<p align="center" class="version">Version 1.0.0 </p>

内容:

* [Typescript Sdk 教程](#typescript-sdk-教程)
  * [1. 钱包](#1-钱包)
  * [2. 资产账户](#2-资产账户)
  * [3. Native 资产](#3-native-资产)
  * [4. 与链交互](#4-与链交互)
  * [5. 节点质押](#5-节点质押)
  * [6. 授权质押](#6-授权质押)


## 1 钱包

Wallet is a data storing file in JSON format. In Ontology, Wallet can store not only the digital identity but also digital assets.

[Wallet Specification](Wallet_Specification_en.md)


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

```js
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

````js
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

```js
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

```js
import {GovernanceTxBuilder} from 'ontology-ts-sdk'

//@param userAddr {Address} User's address that paied for the register
//@param peerPubkeys {[string]} Array of peer's public keys
//@param withdrawList {[number]} Array of ONT to withdraw
//@param payer {Address} Payer to pay for the transaction fee.
//@param gasPrice {string} Usually set as '500'
//@param gasLimit {string} Usually set as '20000'
const tx = GovernanceTxBuilder.makeWithdrawTx(userAddr, peerPubkeys, withdrawList, payer, gasPrice, gasLimit)
```

### 5.4 退出质押

退出质押.

```js
import {GovernanceTxBuilder} from 'ontology-ts-sdk'

//@param userAddr {Address} User's address that paied for the register
//@param peerPubkey {string} Array of peer's public keys
//@param payer {Address} Payer to pay for the transaction fee.
//@param gasPrice {string} Usually set as '500'
//@param gasLimit {string} Usually set as '20000'
const tx = GovernanceTxBuilder.makeQuitNodeTx(userAddr, peerPubkey, payer, gasPrice, gasLimit)
```
## 6.授权质押

### 6.1 查询开发授权质押的节点列表

```js
import {GovernanceTxBuilder} from 'ontology-ts-sdk'
const url = 'http://polaris1.ont.io:20334';
const peerMap = await GovernanceTxBuilder.getPeerPoolMap(url)
```
该接口返回的结果是所有的节点详情。展示的列表需要对返回结果做一些处理，如按质押总数进行排序，匹配节点名称等。具体步骤可以参考OWallet的处理方式[NodeAuthorization.js --> fetchNodeList()](https://github.com/ontio/OWallet/blob/master/src/renderer/store/modules/NodeAuthorization.js)



### 6.2 查询授权质押详情

```js
//@param pk {string} Public key of the node to stake
//@param userAddr {Address} Address of user
//@param url Url of network to connect

import {GovernanceTxBuilder, Crypto} from 'ontology-ts-sdk'
const url = getNodeUrl();
const userAddr = new Crypto.Address(address);
const authorizeInfo = await GovernanceTxBuilder.getAuthorizeInfo(pk, userAddr, url)
```
AuthorizeInfo 具有以下结构：

```js
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
> 用户质押总数 = consensusPos + freezePos + newPos

> 用户锁定中的ONT = withdrawPos + withdrawFreezePos

> 用户可提取的ONT = withdrawUnfreezePos

### 6.3 查询授权质押收益

```js
//@param userAddr {Address} User's wallet address
//@param url {string} Url of node

const url = getNodeUrl();
const userAddr = new Crypto.Address(address);        
const splitFee = await GovernanceTxBuilder.getSplitFeeAddress(userAddr, url)
```

```js
class SplitFeeAddress {
    address: Address; // User's wallet address
    amount: number = 0; // Stake profit ONG number
}
```

> The amount should divide by 1e9.

### 6.4 查询ONT解绑的ONG

```js
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


### 6.5 给某个节点授权质押

```js
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

### 6.6 取消对某个节点的授权质押

```js
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


### 6.7 提取可提取的ONT

```js
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

### 6.8 提取解绑的ONG

```js
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

### 6.9 提取授权质押的收益

```js
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

### 6.10 查询用户质押的总数

```
//@param userAddr {Address} Address of user
//@param url Url of network to connect

import {GovernanceTxBuilder, Crypto} from 'ontology-ts-sdk'
const url = getNodeUrl();
const userAddr = new Crypto.Address(address);
const totalStake = await GovernanceTxBuilder.getTotalStake(userAddr, url)
class TotalStake {
    address: Address; // User's address
    stake: number; // Total num of stake
    timeOffset: number; //Start time for calculating the unbound ONG
}
```



### 6.11 查询当前周期结束所需的区块数量

```javascript
import {GovernanceTxBuilder, RestClient} from 'ontology-ts-sdk'

const url = 'http://polaris1.ont.io:20334' // Url of node.
const rest = new RestClient(url);
try {
  const view = await GovernanceTxBuilder.getGovernanceView(url);
  const blockRes = await rest.getBlockHeight();
  const blockHeight = blockRes.Result;
  const countdown = 120000 - (blockHeight - view.height);
  return countdown; // The amount of blocks to the end of current round
}catch(err) {
  // alert('Network error.')
  console.log(err)
}
```

