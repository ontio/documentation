

CyanoBridge封装了与provider通信的协议，方便DApp开发者集成手机版dApi功能。

> 手机端钱包中用webview打开DApp, 例如 ONTO或cyano钱包.

## 如何使用

CyanoBridge 能够用CommonJS/ES6模块导入或直接在html中引用。

### 安装 CommonJS/ES 

```
npm install cyanobridge
```

### 导入 CommonJS

```
var client = require('cyanobridge').client
client.registerClient();
```

### 导入 ES6 

```
import { client } from 'cyanobridge'
client.registerClient();
```

### Web中引用



```
<script src="./lib/browser.js"></script>

var client = CyanoMobile.client;
client.registerClient();
```


## 使用步骤

参考例子 [demo app](https://github.com/ontio-cyano/mobile-dapp-demo).


### 1. 安装

```
import { client } from 'cyanobridge'
client.registerClient();
```



### 2. getAccount

从钱包获取账号。

#### 参数:

`params` Optional. Defines the name and icon of the dapp.

#### 返回:

```
{
    action: 'getAccount',
    "version": "v1.0.0",
    error: 0,
    desc: 'SUCCESS',
    result: '' // User's address in base58 format
}
```



### 例子:

```
import { client } from 'cyanobridge'

const params = {
    dappName: 'My dapp',
    dappIcon: '' // some url points to the dapp icon
}

try {
    const res = await client.api.asset.getAccount(params);
    console.log(res)
} catch(err) {
    console.log(err)
}

```

### 2. getIdentity

从钱包获取身份.

#### 参数:

`params` Optional. Defines the name and icon of the dapp.

#### 返回值:

```
{
    action: 'getIdentity',
    "version": "v1.0.0",
    error: 0,
    desc: 'SUCCESS',
    result: '' // User's ONT ID
}
```



#### 例子:

```
const params = {
    dappName: 'My dapp',
    dappIcon: '' // some url points to the dapp icon
}
try {
   const res = await client.api.identity.getIdentity(params);
    console.log(res)
} catch(err) {
    console.log(err)
}
```



### 3. 登录

请求钱包对数据做签名.

#### 参数:

Parameter is  a JSON object. It contains:

`type` Define use account or identity to sign message

`dappName` dApp's name

`dappIcon` A url that points to the dApp's icon.

`message` Message to sign.

`expired` Timestamp for expire date.

`callback` Callback url for dapp.

#### 返回:

```
{
	"action": "login",
	"version": "v1.0.0",
	"params": {
		"type": "ontid or account",
		"user": "did:ont:AUEKhXNsoAT27HJwwqFGbpRy8QLHUMBMPz",
		"message": "helloworld",
		"publickey": "0205c8fff4b1d21f4b2ec3b48cf88004e38402933d7e914b2a0eda0de15e73ba61",
		"signature": "01abd7ea9d79c857cd838cabbbaad3efb44a6fc4f5a5ef52ea8461d6c055b8a7cf324d1a58962988709705cefe40df5b26e88af3ca387ec5036ec7f5e6640a1754"
	}
}
```



#### 例子:

```
const params = {
    type: 'account',// account or identity that will sign the message
    dappName: 'My dapp', // dapp's name
    dappIcon: 'http://mydapp.com/icon.png', // some url that points to the dapp's icon
    message: 'test message', // message sent from dapp that will be signed by native client
    expired: new Date('2019-01-01').getTime(), // expired date of login
    callback: '' // callback url of dapp
}
let res;
try {
    res = await client.api.message.login(params);
    console.log(res)
}catch(err) {
    console.log(err)
}
// verify signature here

```



### 4. 调用合约

请求调用合约.

#### 参数:

Parameter are as below:

`scriptHash` Script hash of smart contract

`operation` Method to invoke

`args` Array of parameters. Each parameter should contain `type` and `value`

All supported parameters  see [Supported parameters list](#supported-parameters-list)

`gasPrice` Gas price

`gasLimit` Gas limit

`payer` base58 format address of the payer.

`config` Optional config.

> `config` can contains 
>
> {	
>
> ​	login: bool // define if user logined
>
> ​	message:  string // some message to show in cyano provider
>
> ​	url: string // callback url for dapp
>
> }

#### 返回:

```
{
	"action": "invoke",
	"version": "v1.0.0",
	"error": 0,
	"desc": "SUCCESS",
	"result": "txhash" // Transaction hash
}
```

> dApp then use the Ontology restful api to query the event of this invokation.  Restful api 文档 [here](http://dev-docs.ont.io/#/docs-en/API/02-restful_api)

### 例子:

```
const scriptHash = 'cd948340ffcf11d4f5494140c93885583110f3e9';
const operation = 'test'
const args = [
    {
        type: 'String',
        value: 'helloworld'
    }
]
const gasPrice = 500;
const gasLimit = 20000;
const payer = 'AecaeSEBkt5GcBCxwz1F41TvdjX3dnKBkJ'
const config = {
    "login": true,
    "message": "invoke smart contract test",
    "url": ""  
}
const params = {
          scriptHash,
          operation,
          args,
          gasPrice,
          gasLimit,
          payer,
          config
        }
try {
   const res = await client.api.smartContract.invoke(params);
   } catch(err) {
    console.log(err)
}

```

### 5. 预执行合约

预执行交易，参数与调用合约相同。

### 例子:

```
const scriptHash = 'b5a1f2cd4e27b7453111a2f5eb737714ead8fded';
      const operation = 'balanceOf';
      const args = [{
          "name": "account",
          "type" : 'Address',
          "value": "AQf4Mzu1YJrhz9f3aRkkwSm9n3qhXGSh4p"
        }]
        const gasPrice = 500;
        const gasLimit = 20000;
        const config = {
          "login": true,
          "message": "invoke read smart contract test",
          "url": ""
        }
        const params = {
          scriptHash,
          operation,
          args,
          gasPrice,
          gasLimit,
          config
        }
        try{
          const res = await client.api.smartContract.invokeRead(params);
          console.log('dapp receive: ' + JSON.stringify(res));
          this.invokeReadRes = JSON.stringify(res);
        }catch(err) {
          console.log(err);
        }
```

### 6. 免密调用合约

有些游戏会用到自动投注功能，比如每隔10秒投注一次，用户只需要输入一次密码。我们只信任固定的方法和参数，而不是信任整个合约的所有方法。

#### 例子:

```
const scriptHash = 'cd948340ffcf11d4f5494140c93885583110f3e9';
const operation = 'test'
const args = [
    {
        type: 'String',
        value: 'helloworld'
    }
]
const gasPrice = 500;
const gasLimit = 20000;
const payer = 'AecaeSEBkt5GcBCxwz1F41TvdjX3dnKBkJ'
const config = {
    "login": true,
    "message": "invoke smart contract test",
    "url": ""  
}
const params = {
          scriptHash,
          operation,
          args,
          gasPrice,
          gasLimit,
          payer,
          config
        }
try {
   const res = await client.api.smartContract.invokePasswordFree(params);
   } catch(err) {
    console.log(err)
}
```

### 支持的参数列表

#### Integer

```
{
    type: "Integer",
    value: 10
}
```

#### Long

```
{
    type: 'Long',
    value: '12345678901234567'
}
```

#### String

```
{
    type: 'String',
    value: 'hello world'
}
```

#### ByteArray

```
{
    type: 'ByteArray',
    value: 'abababab'
}
```

#### Address

```
{
    type: 'Address',
    value: 'AXK2KtCfcJnSMyRzSwTuwTKgNrtx5aXfFX'
}
```

### Array

```
{
    type: 'Array',
    value: [
        {
            type: 'String',
            value: 'hello world'
        }
    ]
}
```

#### Map

```
{
    type: 'Map',
    value: {
        key1: {
            type: 'Integer',
            value: 100
        }
    }
}
```



