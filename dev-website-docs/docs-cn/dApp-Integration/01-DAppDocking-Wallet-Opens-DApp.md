
## 概述

当前来看，各个移动版钱包 App 是 DApp 的重要入口，我们提供了 `cyano-bridge` 组件，DApp 安装后，通过调用符合 [CEP-1](https://github.com/ontio-cyano/CEPs/blob/master/CEPS/CEP1.mediawiki) 规范的 DAPI，与任何一个集成了 `Provider-SDK` 的钱包 App 通信，实现对链的操作。

> 已支持 DAPI 的钱包: [麦子钱包](http://www.mathwallet.org/en/)、[Onion](http://onion.fun/) 等

目前比较主流的DApp使用渠道除了钱包中直接打开，还有接入了插件钱包的chrome浏览器，在chrome中使用DApp的接入方案为[使用 chrome 插件钱包](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/03-DAppDocking-use-chrome-extension-wallet)。

为了满足 DApp 同时适用于网页版和移动版，我们提供了兼容两种 DAPI 的例子：

* 移动版 DAPI 使用方法：[dapi for mobile](https://github.com/ontio-cyano/cyano-bridge)
* Chrome 插件钱包的 DAPI 使用方法 [dapi for chrome](https://github.com/ontio/ontology-dapi)
* 兼容移动版和 Chrome 插件版 DAPI 的代码例子：[dapi-universal](https://github.com/ontio-cyano/dapi-universal)

## 钱包内打开 DApp 的交互流程

### 登录场景
1. 钱包内打开 DApp
2. DApp 向钱包发送登录请求，钱包返回签名数据
3. DApp 验证通过，登录成功

### 调用智能合约场景
1. DApp 向钱包发起调用智能合约请求 (图中 4.1)
2. 钱包签名，预执行，发送到链，向 DApp  返回交易 hash (图中 4.2)

![](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/scenario3.png)


## 移动版 DAPI 的安装和使用

### 安装

你可以选择以下一种安装方式：

- npm 安装
- CDN


#### npm 安装

使用 `npm` 进行安装：

```shell
npm install cyanobridge
```

#### CDN

目前可以通过 `jsDelivr` 获取到最新版本的资源，在页面上引入 js 文件即可开始使用。

```html
<script src="https://cdn.jsdelivr.net/npm/cyanobridge/lib/browser.min.js"></script>
```

<p class = "info">建议使用 CDN 引入 `cyano-bridge` 的用户在链接地址上锁定版本，以免将来 `cyano-bridge` 升级时受到非兼容性更新的影响。</p> 

### 导入

#### CommonJS

```javascript
var client = require('cyanobridge').client
```

#### ES6 模块

```javascript
import { client } from 'cyanobridge'
```

#### Web require

导入 `./lib` 文件夹下的 `browser.js` 文件:

```html
<script src="./lib/browser.js"></script>

var client = CyanoMobile.client;
```

### 初始化

在使用前需要进行初始化：

```javascript
import { client } from 'cyanobridge'

client.registerClient();
```

### 使用

#### 获取账号或身份信息

获取账号或身份信息，移动端可以选择填 DApp 信息也可以不填写。

```
import { client } from 'cyanobridge'

const params = {
​    dappName: 'My dapp',
​    dappIcon: '' // some url points to the dapp icon
}

try {
​    const res = await client.api.asset.getAccount(params);
    const res = await client.api.identity.getIdentity(params);
​    console.log(res)
} catch(err) {
​    console.log(err)
}

```


#### 登录

登录是由钱包方签名，DApp 验证签名。

```
const params = {
​    type: 'account',// account or identity that will sign the message
​    dappName: 'My dapp', // dapp's name
​    dappIcon: 'http://mydapp.com/icon.png', // some url that points to the dapp's icon
​    message: 'test message', // message sent from dapp that will be signed by native client
​    expired: new Date('2019-01-01').getTime(), // expired date of login
​    callback: '' // callback url of dapp
}
let res;
try {
​    res = await client.api.message.login(params);
​    console.log(res)
}catch(err) {
​    console.log(err)
}
```

#### 调用合约


```
const scriptHash = 'cd948340ffcf11d4f5494140c93885583110f3e9';
const operation = 'test'
const args = [
​    {
​        type: 'String',
​        value: 'helloworld'
​    }
]
const gasPrice = 500;
const gasLimit = 20000;
const payer = 'AecaeSEBkt5GcBCxwz1F41TvdjX3dnKBkJ'
const config = {
​    "login": true,
​    "message": "invoke smart contract test",
​    "qrcodeUrl": "" ,
    "callback": ""
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
​    console.log(err)
}

```

===错误码===

response示例:
<pre>
{
	"action": "login",
	"error": 0,
	"desc": "SUCCESS",
	"result": true
}

</pre>
   | Error Code |  Description
   | :------- | :------- | :------- |
   | 0 | Success
   | 80001| Params error
   | 80002| Method error
   | 80003| Internal error

## 代码参考

##### 签名验证方法
* [java sdk验签](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/interface.md#%E7%AD%BE%E5%90%8D%E9%AA%8C%E7%AD%BE)
* [ts sdk验签](https://github.com/ontio/ontology-ts-sdk/blob/master/test/ecdsa.crypto.test.ts)

##### DApp 后端查询交易事件
* [java sdk 交易事件查询方法](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/basic.md#%E4%B8%8E%E9%93%BE%E4%BA%A4%E4%BA%92%E6%8E%A5%E5%8F%A3)
* [ts sdk 交易事件查询方法](https://github.com/ontio/ontology-ts-sdk/blob/master/test/websocket.test.ts)

##### 钱包
* [cyano-android](https://github.com/ontio-cyano/cyano-android)
* [cyano-ios](https://github.com/ontio-cyano/cyano-ios)

##### dApi-mobile client sdk
* [cyano-bridge](https://github.com/ontio-cyano/cyano-bridge)

##### dApi-mobile provider sdk
* [cyano-android-sdk](https://github.com/ontio-cyano/cyano-android-sdk)
* [cyano-ios-sdk](https://github.com/ontio-cyano/cyano-ios-sdk)
