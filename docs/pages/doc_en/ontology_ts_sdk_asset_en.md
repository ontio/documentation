---
title: 
keywords: sample homepage
sidebar: ont_doc_en
permalink: ontology_ts_sdk_asset_en.html
folder: doc_en
---

English / [中文](./ontology_ts_sdk_asset_zh.html)


<h1 align="center">Digital Asset Management </h1>
<p align="center" class="version">Version 0.7.0 </p>


## Wallet

Wallet is a data storing file of JSON format. In the terms of Ontology, Wallet could store not only the digital identity but also digital assets.



### Wallet Data Specification

````
{
	name: string;
    ontid: string;
    createTime: string;
    version: string;
    scrypt: {
        "n": number;
        "r": number;
        "p": number;
    };
    identities: Array<Identity>;
    accounts: Array<Account>;
    extra: null;
}
````

`name` is the name of wallet given by user.

```ontid``` is the unique ontid of wallet.

```createTime``` is the creation time of wallet of ISO format, such as "2018-02-06T03:05:12.360Z"

`version` is set to a constant 1.0. It is provided for the future update.

`scrypt` is the parameters used in the encryption algorithm, which is used in the encryption of wallet and decryption of private key.

`identities` is the array of all digital identity object in the wallet.

```accounts``` is the array of all digital asset object in the wallet.

```extra``` is the field used by client developer to store extra informations. It can be null.

More detail about wallet data specification could be found in [Wallet_File_Specification](./Wallet_File_Specification.md).

----


### 1.1 Create An Wallet

Users could create their wallet from scratch.

#### 1）Create an empty wallet

Users only need to pass the name of their wallets.

````
import {Wallet} from 'Ont'
var wallet = new Wallet()
wallet.create( name )
````

----



#### 2) Create an account and add it to your wallet

Users need to provide **private key, password as well as acccount name** to create an new account. In particular, **the private key** could be generated functions provided by SDK. The algorithm used in account creation would be specified as well. The data structure of algorithm object is shown as follow:

```
{
  algorithm: string // The name of algorithm
  parameters: {}    // The parameters used in the algorithm
}
```

SDK will use the default algorithm to create account if no algorithm object is specified.

The created account could then be added to the wallet.

````
import {Account, Core} from 'Ont'
var account = new Account()
var privateKey = Core.generatePrivateKeyStr()
account.create( privateKey, password, name )
wallet.addAccount(account)
````

----



### Account Data Structure。

````
{
  address : string,
  label : string,
  lock : boolean,
  algorithm : string,
  parameters : {},
  key : string,
  extra : null
}
````

```address``` is the account address encoded in base58

```label``` is the name of account

`lock` specifies whether the account is locked by user. The client cannot spend assets in a locked account.

`algorithm` is the name of encryption algorithm

`parameters` is the list of parameters used in the encryption algorithm

`key` is the private key of NEP-2 format. This field can be null (for read-only or non-standard address).

`extra` is the field used by client developer to store extra informations. It can be null.

----


###  Create An Account

````
import {Account} from 'Ont'
var account = new Account()
//@param {string} privateKey The user's private key
//@param {string} password The user's password
//@param {string} label The name of account账户的名称
//@param {object} algorithmObj optional parameter. The encryption algorithm object.
account.create(privateKey, password, label, algorithmObj)
````

----



### Import An Account

Users cuold import an account by the backup data.

The process of importing an account will need to verify the password as well as encrypted private key, and return the corresponding error if not correct.

````
import { Account } from 'Ont'
//@param {accountDataStr} The JSON string of account
//@param {encryptedPrivateKey} The encrypted private key
//@param {password} The password used for encrypt private key
var account;
try {
    account = Account.importAccount(accountDataStr, encryptedPrivateKey, password)
} catch(error) {
    //password or private key incorrect
}
````

----


## Digital Asset Transfer

####  Introduction of Asset Transfer Function
````
function makeTransferTransaction(tokenType:string, from : string, to : string, value : string,  privateKey : string)

tokenType: token Type of token
from: The hashed-public-key address of transferer
to: The hashed-public-key address of transferee
value: Transfer amount. The amounnt should be motiplied with 10^8 in order to avoid of any accuracy loss
privateKey: The private key of transferer that is corresponding to the publick key
````

----

### Type of Token
````
TOKEN_TYPE = {
  ONT : 'ONT',  //Ontology Token
  ONG : 'ONG'   //Ontology Gas
}
````

### An example
````
import { makeTransferTransaction, buildRestParam } from "../src/transaction/transactionBuilder";

var tx = makeTransferTransaction( 'ONT', '0144587c1094f6929ed7362d6328cffff4fb4da2', 'ffeeddccbbaa99887766554433221100ffeeddcc', '1000000000', '760bb46952845a4b91b1df447c2f2d15bb40ab1d9a368d9f0ee4bf0d67500160' )

var restData = buildRestParam(tx)

axios.post('127.0.0.1:20386', restData).then(res => {
       console.log('transfer response: ' + JSON.stringify(res.data))
   }).catch(err => {
       console.log(err)
   })
````

----



## Inquiry of Digital Asset: getBalance

### Link of Balance Inquiry

````
//nodeURL The IP address of note
//httpRestPort The port exposed to the Restful interface by node
//address The address of Blanace Inquiry
http://${nodeURL}:${httpRestPort}/api/v1/balance/${address}
````

### 样例：

````
let request = `http://127.0.0.1:20384/api/v1/balance/TA5uYzLU2vBvvfCMxyV2sdzc9kPqJzGZWq`
	axios.get(request).then((res : any) => {
		if(res.data.Error === 0) {
			let obj = {
				error : 0,
				result : res.data.Result
			}
		} else {
			let obj = {
				error: res.data.Error,
				result : ''
			}
		}
	}).catch( (err:any) => {
		let obj = {
			error: JSON.stringify(err),
			result: ''
		}
	})
````
