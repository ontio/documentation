---
title: 
keywords: sample homepage
sidebar: ont_doc_zh
permalink: ontology_ts_sdk_asset_zh.html
folder: doc_zh
---

[English](./ontology_ts_sdk_asset_en.html) / 中文

<h1 align="center">数字资产管理 </h1>
<p align="center" class="version">Version 0.7.0 </p>

## 钱包 Wallet

钱包Wallet是一个Json格式的数据存储文件。在本体Ontology中， Wallet既可存储数字身份，也可以存储数字资产。

### Wallet 数据规范

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

```defaultOntid``` 是钱包默认的数字身份的ONT ID。

```defaultAccountAddress``` 是钱包默认的资产账户的地址

```createTime``` 是ISO格式表示的钱包的创建时间，如 : "2018-02-06T03:05:12.360Z"

`version` 目前为固定值1.0，留待未来功能升级使用。

`scrypt` 是加密算法所需的参数，该算法是在钱包加密和解密私钥时使用。

`identities` 是钱包中所有数字身份对象的数组

```accounts``` 是钱包中所有数字资产账户对象的数组

```extra``` 是客户端由开发者用来存储额外数据字段，可以为null。

希望了解更多钱包数据规范请参考[Wallet_File_Specification](./Wallet_File_Specification.md).

### 创建钱包

用户可以从零开始创建自己的钱包。

#### 1）创建一个空的钱包

用户只需要传入钱包名称。

````
import {Wallet} from 'Ont'
var wallet = new Wallet()
wallet.create( name )
````

#### 2) 创建账户并添加到钱包中

用户需要提供**私钥，密码，账户名称**来创建新的账户，其中**私钥**可以使用SDK提供的方法生成。。也可以指定创建账户所需的算法对象。算法对象的结构如下：

```
{
  algorithm: string // 算法名称
  parameters: {}    // 算法的参数
}
```

如果不传，SDK会使用默认的算法创建账户。

创建好账户后添加到钱包中。

````
import {Account, Core} from 'Ont'
var account = new Account()
var privateKey = Core.generatePrivateKeyStr()
account.create( privateKey, password, name )
wallet.addAccount(account)
````

### Account 数据结构。

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

```address``` 是base58编码的账户地址。

```label``` 是账户的名称。

`lock` 表明账户是否是被用户锁住的。客户端不能消费掉被锁的账户中的资金。

`algorithm` 是加密算法名称。

`parameters` 是加密算法所需参数。

`key` 是NEP-2格式的私钥。该字段可以为null（对于只读地址或非标准地址）。

`extra` 是客户端存储额外信息的字段。该字段可以为null。

###  创建账户

````
import {Account, Core} from 'Ont'
var privateKey = Core.generatePrivateKeyStr()
var account = new Account()
//@param {string} privateKey 用户的私钥
//@param {string} password 密码
//@param {string} label 账户的名称
//@param {object} algorithmObj 可选参数，加密算法对象
account.create(privateKey, password, label, algorithmObj)
````

###  导入账户

可以通过备份的数据导入账户。

导入账户的过程中会验证密码和加密后的私钥，如果不正确会抛出相应错误码。

````
import { Account } from 'Ont'
//@param {label} 账户的名称
//@param {encryptedPrivateKey} 加密后的私钥
//@param {password} 用来加密私钥的密码
var account;
try {
    account = Account.importAccount(label, encryptedPrivateKey, password)
} catch(error) {
    //密码或私钥不正确
}
````


## 数字资产转账 Transfer

####  转账函数说明
````
function makeTransferTransaction(tokenType:string, from : string, to : string, value : string,  privateKey : string)

tokenType: token 类型
from: 转账者的公钥哈希地址
to: 接收者的公钥哈希地址
value: 转账数值，需要乘以10^8以避免小数点后精度损失
privateKey: 转账者公钥对应的私钥
````

####Token类型
````
TOKEN_TYPE = {
  ONT : 'ONT',  //Ontology Token
  ONG : 'ONG'   //Ontology Gas
}
````

#### 样例
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

## 数字资产查询 getBalance

### 查询余额链接

````
//nodeURL 节点的IP地址
//HTTP_REST_PORT 节点暴露给Restful接口的端口
//address 查询余额的地址
http://${nodeURL}:${HTTP_REST_PORT}/api/v1/balance/${address}
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