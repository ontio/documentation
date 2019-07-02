


## 1. 概述

该项目是本体官方 `Typescript SDK`。

目前支持：

本地钱包管理、数字身份管理、数字资产管理、智能合约部署和调用以及资产转账等等。未来还将支持更丰富的功能和应用。

### 主要功能
* 钱包文件规范
* 数字身份及可信声明
* 数字资产
* 智能合约的部署和调用
* 错误码

## 2. 数字资产管理


### 2.1 钱包 Wallet

钱包 `Wallet` 是一个 `Json` 格式的数据存储文件。

在本体 `Ontology` 中， `Wallet` 既可存储数字身份，也可以存储数字资产。

#### 2.1.1 Wallet 数据规范

````
{
	name: string;
    defaultOntid: string;
    defaultAccountAddress : string;
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

`name` 是用户为钱包所取的名称。

```defaultOntid``` 是钱包默认的数字身份的 ONT ID。

```defaultAccountAddress``` 是钱包默认的资产账户的地址

```createTime``` 是 ISO 格式表示的钱包的创建时间，如 :  "2018-02-06T03:05:12.360Z"。

`version` 目前为固定值 1.0，留待未来功能升级使用。

`scrypt` 是加密算法所需的参数，该算法是在钱包加密和解密私钥时使用。

`identities` 是钱包中所有数字身份对象的数组。

```accounts``` 是钱包中所有数字资产账户对象的数组。

```extra``` 是客户端由开发者用来存储额外数据字段，可以为 null。

希望了解更多钱包数据规范请参考[ Wallet_File_Specification ](./Wallet_File_Specification.md)。

#### 2.1.2 创建钱包

用户可以从零开始创建自己的钱包。

#### 1）创建一个空的钱包

用户只需要传入钱包名称。

````
import {Wallet} from 'Ont'
//@param name {string} Name of the wallet
var wallet = Wallet.create( name )
````

#### 2) 创建账户并添加到钱包中

需要提供以下参数来创建账户：

```privateKey``` **PrivateKey** 实例。

```password``` 用户的密码，用来加密私钥。

```label``` 账户名称。

```params``` 额外的参数用来加密解密私钥。它具有以下结构，如果不传，SDK 会使用默认值创建账户。

```
interface ScryptParams {
    cost: number;
    blockSize: number;
    parallel: number;
    size: number;
}
```
默认值如下：

```
const DEFAULT_SCRYPT = {
    cost: 4096,
    blockSize: 8,
    parallel: 8,
    size: 64
};
```

> 该参数在加密和解密时必须使用一致的值，否则解密会失败。

### 2.1) 生成私钥

我们可以使用相应的算法和曲线生成随机的私钥。

SDK 支持以下三种公私钥生成算法：

* ECDSA
* SM2
* EDDSA

ECDSA 是默认的算法. `SECP256R1` 是默认的曲线。

```typescript
import { Crypto } from 'ontology-ts-sdk';

cont keyType = Crypto.KeyType.ECDSA;

const keyParameters = new Crypto.KeyParameters(Crypto.CurveLabel.SECP256R1);

const privateKey = Crypto.PrivateKey.random(keyType, keyParameters)

const privateKey2 = Crypto.PrivateKey.random() // Use default params
```

### 2.2) 创建账户
然后我们可以创建账户并添加到钱包中。

````
import {Account, Crypto} from 'ontology-ts-sdk';

var account = Account.create( privateKey, password, name ); //Use the default scrypt params

wallet.addAccount(account)

````

## 3. 账户

账户是作用是用来管理用户的资产。

### 3.1 账户的数据结构

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

```address``` 账户地址。 base58 格式

```label``` 账户名称

`lock` 声明账户是否锁定

`algorithm` 公私钥生成算法名称

`parameters`算法的参数

`curve` 算法使用的曲线

`key` 加密后私钥

`enc-alg` 加密私钥的算法

`salt` 加密算法的盐值。 base64 格式

`isDefault` 声明是否是默认账户

`publicKey` 账户的公钥

`signatureScheme` 签名算法


####  创建账户

````
import {Account} from 'ontology-ts-sdk'
//@param {PrivateKey} The user's private key
//@param {string} The user's password
//@param {string} Optional. Name of the account
//@param {object} Optional parameter. The encryption algorithm object.
var account = Account.create(privateKey, password, label, params)

````

##  3.2 导入账户

可以通过备份的数据导入账户。

### 导入 keystore

导入账户的过程中会验证密码和加密后的私钥，如果不正确会抛出相应错误码。

````
import { Account, Crypto } from 'ontology-ts-sdk'

//@param label {srint} Name of the account
//@param encryptedPrivateKey {PrivateKey} The encrypted private key
//@param password {string} The password used to decrypt private key
//@param address {Address} The address of the account
//@param salt {string} The salt in base64 format
//@param params {Scryp

1. tParams} Optional scrypt params to decrypt private key

var account;
const encryptedPrivateKey = new Crypto.PrivateKey(key);//key is the encrypted private key
try {
    account = Account.importAccount(
    	label, 
    	encryptedPrivateKey
    	password,
	    address,
	    salt,
	    params)
} catch(error) {
    //密码或私钥不正确
}
````


## 4 数字资产转账 Transfer

###  4.1 转账函数说明
````
function makeTransferTransaction(tokenType:string, from : string, to : string, value : string,  privateKey : string)

tokenType: token 类型
from: 转账者的公钥哈希地址
to: 接收者的公钥哈希地址
value: 转账数值，需要乘以10^8以避免小数点后精度损失
privateKey: 转账者公钥对应的私钥
````

### 4.2 Token 类型
````
TOKEN_TYPE = {
  ONT : 'ONT',  //Ontology Token
  ONG : 'ONG'   //Ontology Gas
}
````

### 4.3 样例
````
import { Crypto, OntAssetTxBuilder, TransactionBuilder, WebsocketClient } from 'ontology-ts-sdk'

const gasLimit = '20000';
const gasPrice = '500';
const fromPrivateKey = new Crypto.PrivateKey('7c47df9664e7db85c1308c080f398400cb...83f5d922e76b478b5429e821b97');
const from = new Crypto.Address('AdLUBSSHUuFaak9j169hiamXUmPuCTnaRz');
const to = new Crypto.Address('AH9B261xeBXdKH4jPyafcHcLkS2EKETbUj');
const tx = OntAssetTxBuilder.makeTransferTx('ONT', from, to, 1, gasPrice, gasLimit); // 'from' is default as payer
//tx.payer = from;
TransactionBuilder.signTransaction(tx, fromPrivateKey);

// we can use RestClient, RpcClient or WebsocketClient to send the trasanction
const socketClient = new WebsocketClient('ws://polaris1.ont.io:20335');
const response = await socketClient.sendRawTransaction(tx.serialize(), false, true);
// tslint:disable:no-console
console.log(JSON.stringify(response));
````

## 5. 数字资产查询 getBalance

### 5.1 查询余额

````
//nodeURL 节点的IP地址
//HTTP_REST_PORT 节点暴露给Restful接口的端口
//address 查询余额的地址
http://${nodeURL}:${HTTP_REST_PORT}/api/v1/balance/${address}
````

### 5.2 样例：

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

## 6 查询可提取的 ONG

有两种方式查询可提取的 `ONG`。

### 6.1 使用区块链 API 查询

这里以 `Restful API` 为例：

#### Example:

```typescript
const address = new Address('AdLUBSSHUuFaak9j169hiamXUmPuCTnaRz');
const rest = new RestClient();// default connects to Testnet
const result = await restClient.getAllowance('ong', new Address(ONT_CONTRACT), addr);
        console.log(result);
```

返回结果类似如下：

```json
{ 
    Action: 'getallowance',
      Desc: 'SUCCESS',
      Error: 0,
      Result: '534420890',
      Version: '1.0.0'
}
```

**Result** 是带精度的可提取 `ONG` 数额.

### 6.2 使用合约 API 查询

#### Example：

```typescript
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
```

**num** 是可提取 `ONG` 数额。我们需要将返回的结果处理下得到实际的数额。

## 7. 提取 ONG

提取ONG的步骤如下：

### 7.1 构造交易

`from` Sender's address to withdraw ONG.

`to` Receiver's address to receive ONG.

`amount` Amount of ONG to withdraw. Need to multiply 1e9 to keep precision.

`gasPrice` Gas price.

`gasLimit` Gas limit.

`payer` Payer's address to pay for the transaction gas.

```typescript
import {OntAssetTxBuilder} from 'ontology-ts-sdk'

//suppose we have an account already
const from = account.address;
const to = account.address;
const amount = 10 * 1e9;
const gasPrice = '500';
const gasLimit = '20000';
const payer = account.address;
const tx = OntAssetTxBuilder.makeWithdrawOngTx(from, to, amount, payer, gasPrice, gasLimit);
```

### 7.2 发送交易

我们以 `Restful API` 为例。

```typescript
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

```

发送了交易后，我们可以查询余额来检查提取 `ONG` 过程是否成功。









