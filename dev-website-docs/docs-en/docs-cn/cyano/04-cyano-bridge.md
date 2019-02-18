
[CEP-1](https://github.com/ontio-cyano/CEPs/blob/master/CEPS/CEP1.mediawiki) 提案定义了手机端的 dApi 规范。基于该提案，我们提供了 `cyano-bridge`，用于供手机端的 dApp 使用。

## 安装

### npm 安装

你可以使用 `npm` 进行安装

```shell
npm install cyanobridge
```

### CDN

目前可以通过 `jsDelivr` 获取到最新版本的资源，在页面上引入 js 文件即可开始使用。

```html
<script src="https://cdn.jsdelivr.net/npm/cyanobridge/lib/browser.min.js"></script>
```

!> 建议使用 CDN 引入 `cyano-bridge` 的用户在链接地址上锁定版本，以免将来 `cyano-bridge` 升级时受到非兼容性更新的影响。

## 导入

### CommonJS

```javascript
var client = require('cyanobridge').client
```

### ES6 模块

```javascript
import { client } from 'cyanobridge'
```

### Web require

导入 `./lib` 文件夹下的 `browser.js` 文件:

```html
<script src="./lib/browser.js"></script>

var client = CyanoMobile.client;
```

## 初始化

```javascript
import { client } from 'cyanobridge'

client.registerClient();
```

## 使用

### 查询钱包账户

```javascript
const params = {
    dappName: 'My dapp',
    dappIcon: ''
}

try {
    const res = await client.api.asset.getAccount(params);
    console.log(res)
} catch(err) {
    console.log(err)
}
```

### 查询身份

```javascript
const params = {
    dappName: 'My dapp',
    dappIcon: ''
}
try {
   const res = await client.api.identity.getIdentity(params);
    console.log(res)
} catch(err) {
    console.log(err)
}
```

### 登陆

```javascript
const params = {
    type: 'account',
    dappName: 'My dapp',
    dappIcon: 'http://mydapp.com/icon.png',
    message: 'test message',
    expired: new Date('2019-01-01').getTime(),
    callback: ''
}
let res;
try {
    res = await client.api.message.login(params);
    console.log(res)
}catch(err) {
    console.log(err)
}
```

### 智能合约

#### 执行智能合约

```javascript
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

#### 免密执行智能合约

在免密执行智能合约中，第一次执行时需要用户输入密码，此后执行相同的合约方法时将不再需要用户输入密码。

```javascript
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

在免密执行智能合约中，我们所信任的是固定的方法和参数，而不是信任整个合约的所有方法，所以输入密码后会保存该交易的参数，当且仅当下次请求为同样的交易参数时才不需要再次输入密码。

> 出于安全考虑，当用户离开当前的 dApp 时，必须清空内存中的私钥和参数。

#### 预执行智能合约

```javascript
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
