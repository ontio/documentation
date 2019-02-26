## 概述

移动版dApi目前只提供几个重要dapi接口

- 获取账号或身份信息
- 登录
- 调用合约

查询其他信息可以直接调用区块链浏览器的api接口查询 [explorer api](http://dev-docs.ont.io/#/docs-en/explorer/overview).

## 钱包内打开dApp交互流程说明

### 登录场景
- 钱包内打开dApp
- dApp向钱包发送登录请求，钱包返回签名数据
- dApp验证通过，登录成功

### 调用智能合约场景
- dApp向钱包发起调用智能合约请求
- 钱包签名，预执行，发送到链，向dApp返回交易hash

![](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/scenario3.png)


另外，为了满足dApp同时适用于网页版和移动版，我们提供了兼容两种dapi的例子：

* 移动版dApi使用方法: [dapi for mobile](https://github.com/ontio-cyano/cyano-bridge)
* Chrome插件钱包的dApi使用方法[dapi for chrome](https://github.com/ontio/ontology-dapi)
* 兼容移动版和Chrome插件版dApi的代码例子：[dapi-universal](https://github.com/ontio-cyano/dapi-universal)

## 移动版dApi安装和使用

### dApi接口初始化

```
import { client } from 'cyanobridge'
client.registerClient();

```

### 获取账号或身份信息

获取账号或身份信息，移动端可以可以选择填dapp信息也可以不填写。

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


### 登录

登录是由钱包方签名，dApp验证签名。

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

### 调用合约


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

## 代码参考

##### 签名验证方法
* [java sdk验签](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/interface.md#%E7%AD%BE%E5%90%8D%E9%AA%8C%E7%AD%BE)
* [ts sdk验签](https://github.com/ontio/ontology-ts-sdk/blob/master/test/message.test.ts)

##### DApp后端查询交易事件
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
