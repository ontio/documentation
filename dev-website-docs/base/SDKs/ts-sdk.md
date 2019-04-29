



# Overview

The Ontology official TypeScript SDK is a comprehensive SDK which also supports JavaScript. Currently, it supports local wallet management, digital identity management, digital asset management, deploying and invoking smart contract as well as communicating with the Ontology blockchain. The TS SDK will also support more functions and applications in the future.






# Wallet

Wallet is a data storing file in JSON format. In Ontology, Wallet can store not only the digital identity but also digital assets.



## Wallet Data Specification

````JSON
{
	name: string;
	defaultOntid: string;
	defaultAccountAddress: string;
	createTime: string;
	version: string;
	scrypt: {
	    "n": number;
	    "r": number;
	    "p": number;
	    "dkLen": number;
	};
	identities: Array<Identity>;
	accounts: Array<Account>;
	extra: null;
}
````

`name` is the name of wallet given by user.

```defaultOntid``` is the default ontid of wallet.

```defaultAccountAddress``` is the default account address of wallet.

```createTime``` is the creation time of wallet of ISO format, such as "2018-02-06T03:05:12.360Z".

`version` is set to a constant 1.0. It is provided for future updates.

`scrypt` is the parameter used in the encryption algorithm, which is used in the encryption of wallet and decryption of private key.

`identities` is the array of all digital identity objects in the wallet.

```accounts``` is the array of all digital asset objects in the wallet.

```extra``` is the field used by client developer to store extra informations. It can be null.

More details about wallet data specification can be found in [Wallet_File_Specification](./Wallet_File_Specification.md).


## 1.1 Create a Wallet

Users could create their wallet from scratch.

### 1) Create an empty wallet

Users only need to pass the name of their wallets.

````
import {Wallet} from 'ontology-ts-sdk';
var wallet = Wallet.create('my_wallet')
````

### 2) Create an account and add it to your wallet

Users need to provide below parameters to create an account:

```privateKey``` An instance of class **PrivateKey**.

```password``` User's password to encrypt the private key.

```label``` Name of the account.

```params``` Optional params used to encrypt the private key. It has below structure. If it is not given, the default value will used.

```
interface ScryptParams {
    cost: number;
    blockSize: number;
    parallel: number;
    size: number;
}
```
The default scrypt params are as below:

```
const DEFAULT_SCRYPT = {
    cost: 4096,
    blockSize: 8,
    parallel: 8,
    size: 64
};
```

> Scrypt params must be same in the encryption and decryption, or the decryption will fail.

### 2.1) Generate PrivateKey

We can generate a random private key with specific keypair algorithm and elliptic curve. There are three kinds of algorithms we support:

* ECDSA
* SM2
* EDDSA

ECDSA is the default one. You can check TS SDK API reference for info.

```typescript
import { Crypto } from 'ontology-ts-sdk';

cont keyType = Crypto.KeyType.ECDSA;

const keyParameters = new Crypto.KeyParameters(Crypto.CurveLabel.SECP256R1);

const privateKey = Crypto.PrivateKey.random(keyType, keyParameters)
```

### 2.2) Create account
Then we can create the account and add it to the wallet.

````
import {Account, Crypto} from 'ontology-ts-sdk';

var account = Account.create( privateKey, password, name );

wallet.addAccount(account)

````

# Account
Account is used to manage user's assets.

## Account Data Structure

````
{
	"address": "AJQLNWy9X6qdeEFrSH6UzgEjadSsRiYDCS",
	"label": "mickey",
	"lock": false,
	"algorithm": "ECDSA",
	"parameters": {
	    "curve": "P-256"
	},
	"key": "qFbemAbu7fEjOJzAZZhGkmzp2YNxdSCuK7xyvhBAnUBX/FmAj2Ns84Y7frh6hfQv",
	"enc-alg": "aes-256-gcm",
	"salt": "u+SiqpRk17b0vIPesh4xXA==",
	"isDefault": false,
	"publicKey": "037fb6dfc9420e1d8275d9133d6d69fe64e8e3567241e7583234b9efa8b2ce7ae1",
	"signatureScheme": "SHA256withECDSA"
}
````

```address``` is the account address encoded in base58.

```label``` is the name of account.

`lock` specifies whether the account is locked by user. The client cannot spend assets in a locked account.

`algorithm` is the name of encryption algorithm.

`parameters` is the parameters used in the keypair generation algorithm.

`curve` is the elliptic curve of the keypair generation algorithm.

`key` is the encrypted private key. This field can be null (for read-only or non-standard address).

`enc-alg` is the encryption algorithm used to encrypt the private key.

`salt` is used to encrypt and decrypt the private key.

`isDefault` decides if it is the default account.

`publicKey` is the public key of the account.

`signatureScheme` is the signature scheme used in signature.


###  Create an Account

````
import {Account} from 'ontology-ts-sdk'
//@param {PrivateKey} The user's private key
//@param {string} The user's password
//@param {string} Optional. Name of the account
//@param {object} Optional parameter. The encryption algorithm object.
var account = Account.create(privateKey, password, label, params)
````

### Import an Account

Users can import an account by the backup data.

This method will check the password and the private key, an error will be thrown if they are not match.

````
import { Account } from 'ontology-ts-sdk'
//@param label {srint} Name of the account
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



# Digital Asset Transfer

##  Transfer native asset
There are two kinds of native asset in Ontology: ONT and ONG.

In order to transfer native asset, we can create the specific transaction and send it to the blockchain. After the transaction has been packaged in the block, the transaction will succeed.

### Type of native asset
````
TOKEN_TYPE = {
  ONT : 'ONT',  //Ontology Token
  ONG : 'ONG'   //Ontology Gas
}
````

## An example of transfer asset
### Create transaction

First we need to create the transaction for transfer.
The parameters are as below:

`assetType` ONT or ONG.

`from` Sender's address. Must be with enough balance.

`to	` Receiver's address.

`amount` Can not be more than the sender's balance.

`gasPrice` The limit is set by blockchain node. Can not be less than the limit.

`gasLimit` The limit is set by blockchain node. Can not be less than the limit.

`payer` Payer's address to pay for the gas. If not given, use sender's address is the default.

In TestNet, we can set `gasPrice` as 0 for test.

````typescript
import {OntAssetTxBuilder} from 'ontology-ts-sdk'
//supppose we have an account with enough ONT and ONG
//Sender's address
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

### Send transaction
We can use RESTful API, RPC API, or WebSocket API to send transaction. Here we use RESTful API as an example.

> Use WebSocket API and wait for the transaction notice.

````typescript
import {RestClient, CONST, TransactionBuilder} from 'ontology-ts-sdk'

//we already got the transaction we created before

//we have to sign the transaction before sent it
//Use user's private key to sign the transaction
TransactionBuilder.signTransaction(tx, privateKey)

const rest = new RestClient(CONST.TEST_ONT_URL.REST_URL);
rest.sendRawTransaction(tx.serialize()).then(res => {
	console.log(res)	
})

````
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

> RestClient.getSmartCodeEvent


## Digital Asset Inquiry: getBalance

### Balance Inquiry

We can use RESTful API, RPC API and WebSocket API to query the balance. Here we use RESTful API as example.

### Example:

````typescript
const address = new Address('AXpNeebiUZZQxLff6czjpHZ3Tftj8go2TF');
const rest = new RestClient();
rest.getBalance(address).then(res -> {
	console.log(res)
})
````
The result contains balance of ONT and ONG.

## Claimable ONG Inquiry

The are two ways to query the claimable ONG.

### Query with Blockchain API

We take RESTful API as an example here:

#### Example:

````typescript
const address = new Address('AdLUBSSHUuFaak9j169hiamXUmPuCTnaRz');
const rest = new RestClient();// default connects to Testnet
const result = await restClient.getAllowance('ong', new Address(ONT_CONTRACT), addr);
        console.log(result);
````

The returned result is like:

````json
{ 
    Action: 'getallowance',
      Desc: 'SUCCESS',
      Error: 0,
      Result: '534420890',
      Version: '1.0.0'
}
````

**Result** is the claimable ONG amount with decimal.

### Query with Native contract API

#### Example：

````typescript
import {OntAssetTxBuilder} from 'ontology-ts-sdk'
const ONT_CONTRACT = '0000000000000000000000000000000000000001'
const address = new Address('AdLUBSSHUuFaak9j169hiamXUmPuCTnaRz');
const rest = new RestClient();// default connects to Testnet
const tx = OntAssetTxBuilder.makeQueryAllowanceTx('ong', new Address(ONT_CONTRACT), address);
const result = await restClient.sendRawTransaction(tx.serialize(), true);
console.log(result);
if (result.Result) {
    const num = parseInt(reverseHex(result.Result.Result), 16);
    console.log(num);
}
````

**num** is the claimable ONG amount with decimal. We need to transform the returned result to get the actual amount.

## Withdraw ONG
Withdraw generated ONG from user's account address and send to other address. They can be the same address.
### Create transaction

`from` Sender's address to withdraw ONG.

`to` Receiver's address to receive ONG.

`amount` Amount of ONG to withdraw. Need to multiply 1e9 to keep precision.

`gasPrice` Gas price.

`gasLimit` Gas limit.

`payer` Payer's address to pay for the transaction gas.


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

### Send transaction
We can use RESTful API, RPC API, or WebSocket API to send a transaction. Here we use RESTful API as an example.

````typescript
//sign transaction before send it
import {RestClient, CONST, TransactionBuilder} from 'ontology-ts-sdk'

//we already got the transaction we created before

//we have to sign the transaction before sent it
//Use user's private key to sign the transaction
TransactionBuilder.signTransaction(tx, privateKey)

const rest = new RestClient(CONST.TEST_ONT_URL.REST_URL);
rest.sendRawTransaction(tx.serialize()).then(res => {
	console.log(res)	
})

````
Then we can query the balance to check if the withdraw succeeded.




