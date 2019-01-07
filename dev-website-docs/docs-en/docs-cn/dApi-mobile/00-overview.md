
## 移动版dApi与chrome插件dApi区别

移动版dApi与chrome插件dApi接口类似，但只提供几个重要接口，查询相关的接口可以直接调用区块链浏览器的api接口查询,[explorer api](http://dev-docs.ont.io/#/docs-en/explorer/overview).

移动版dApi详细使用方法： [cyano-bridge](https://github.com/ontio-cyano/cyano-bridge)

Chrome插件钱包的dApi详细使用方法：[cyano-dapi](https://github.com/ontio/ontology-dapi)

### dApi接口初始化

chrome插件版需要注册，移动版不需要。

#### 移动版本
```
import { client } from 'cyanobridge'
client.registerClient();

```

#### chrome插件版
```
import {client} from 'ontology-dapi'
client.registerClient({})

```

### 获取账号或身份信息

获取账号或身份信息，移动端可以可以选择填dapp信息也可以不填写。

#### 移动版本

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


#### chrome插件版
```
account = await client.api.asset.getAccount()
res = await client.api.identity.getIdentity();
```

### 登录

登录是由钱包方签名，dApp验证签名。

#### 移动版本

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

#### chrome插件版
```
const result = await client.api.message.signMessage({ message });
```

### 调用合约



#### 移动版本

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

#### chrome插件版
```
const contract = '16edbe366d1337eb510c2ff61099424c94aeef02';
const gasLimit = 30000;
const gasPrice = 500;

parameters = [
   {
	name: "msg",
	type: "String",
	value: "hello world"
   } 
]
 params = {
            contract,
            method,
            parameters,
            gasPrice,
            gasLimit
}
await client.api.smartContract.invoke(params)

```