


## 概述

使用 [dAPI for chrome](https://github.com/ontio/ontology-dapi) 前请先安装实现了 ```dAPI provider``` 功能的钱包，比如 [Cyano Wallet of Chrome](https://github.com/OntologyCommunityDevelopers/cyano-wallet)。

DAPI 使用 TypeScript 实现，同时也支持在 JavaScript 工程中使用。

目前比较主流的DApp使用渠道除了在chrome中打开，还有在手机钱包中打开，在手机钱包中使用DApp的接入方案为 [手机钱包内打开](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/01-DAppDocking-Wallet-Opens-DApp)。

为了满足 ```DAPP``` 同时适用于网页版和移动版，我们提供了兼容两种 DAPI 的例子：

* 移动版 ```dAPI``` 使用方法：[dapi for mobile](https://github.com/ontio-cyano/cyano-bridge)
* Chrome 插件钱包的 ```dAPI``` 使用方法 [dapi for chrome](https://github.com/ontio/ontology-dapi)
* 兼容移动版和 ```Chrome``` 插件版 ```dAPI``` 的代码例子：[dapi-universal](https://github.com/ontio-cyano/dapi-universal)

## 安装开发环境

请确保安装以下软件：

- [Node.js v6+ LTS with npm](https://nodejs.org/en/)
- [Cyano Wallet]( https://chrome.google.com/webstore/detail/ontology-web-wallet/dkdedlpgdmmkkfjabffeganieamfklkm)
- [Git](https://git-scm.com/)


## dAPI 协议介绍

介绍应用如何集成 ```dAPI``` 协议。

#### dAPI 安装
创建 DAPP 时，本体 DAPI 是与本体链交互的核心 API 之一，可以从 [这里](https://github.com/ontio/ontology-dapi) 下载源码。 通过 ```npm``` 安装 ontology-DAPI：

```shell
$ npm install ontology-dapi
```

#### 创建 dAPI 实例

创建 DAPI 实例时，要先导入库 ontology-dapi，并注册客户端，如下所示：

```javascript
import { client } from 'ontology-dapi';

client.registerClient({});
```

#### dAPI 方法
创建 dAPI 实例成功后，就可以在你的 DAPP 中调用 dAPI 方法。

##### 获取账号或身份信息

```javascript
account = await client.api.asset.getAccount()
res = await client.api.identity.getIdentity();
```


##### 智能合约方法
```javascript
const result = await client.api.smartContract.invoke({contract,method,parameters,gasPrice,gasLimit,requireIdentity});
const result = await client.api.smartContract.invokeRead({ contract, method, parameters });
const result = await client.api.smartContract.deploy({code,name,version,author,email,description,needStorage,gasPrice,gasLimit});
```

##### 与链交互方法
```javascript
const network = await client.api.network.getNetwork();
const height = await client.api.network.getBlockHeight();
const block = await client.api.network.getBlock({ block: 1 });
const transaction = await client.api.network.getTransaction({txHash: '314e24e5bb0bd88852b2f13e673e5dcdfd53bdab909de8b9812644d6871bc05f'});
const balance = await client.api.network.getBalance({ address: 'AcyLq3tokVpkMBMLALVMWRdVJ83TTgBUwU' });
```
##### 转账方法
```javascript
const result = await client.api.asset.makeTransfer({ recipient, asset, amount });
```

##### 数据签名

可以用做登录时验证用户身份。
```javascript
const message: string = values.message;
const signature: Signature = {
  data,
  publicKey
};
const result = await client.api.message.signMessage({ message });
const result = await client.api.message.verifyMessage({ message, signature });
```

所有方法列表可参考 [DAPI 规范](https://github.com/backslash47/OEPs/blob/oep-dapp-api/OEP-6/OEP-6.mediawiki)。


## 演示例子

拷贝 [dAPI 例子](https://github.com/OntologyCommunityDevelopers/ontology-dapi-demo)，可以测试 DAPI 提供了哪些功能。

```shell
$ git clone https://github.com/OntologyCommunityDevelopers/ontology-dapi-demo.git

$ npm install

$ npm run start
```

启动成功后，在浏览器打开页面 ```http://localhost:3000```

页面成功打开后, 点击 Provider->GetProvider。

![dApp Demo Provider](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/dappdemofirstscreen.png)
![dApp Demo Get Provider](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/dappdemoregisterprovider.png)

就通过 API 调用与链交互了。例如，点击 Network->Get Block，结果如下:

![dApp Demo getBlock](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/dappdemonetworkblock.png)

运行转账例子，点击 Asset->Make Transfer，Cyano Wallet 会弹出确认框。点击 ```Confirm``` 确认交易。

![Cyano Wallet Confirm](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/demo.png)

#### 如何填写 gaslimit 和 gasprice

每笔交易都包含 ```gas limit``` 和 ```gas price```。

gasprice 会影响到该笔交易被打包所需等待的时间，目前主网和测试网最小值都是500。

gaslimit 根据合约执行复杂性而定，可以通过预执行查询该调用需要的最小 gaslimit 值。```Native``` 合约调用 ```gaslimit``` 默认是 20000。部署合约根据合约而定，```gaslimit``` 一般是 20000000 以上。

#### 地址的处理

Chrome 插件钱包 Cyano wallet 在处理传入的地址时，只接受 ByteArray 类型，在使用 [SmartX](https://smartx.ont.io/#/) 进行调试的时候，SmartX 会自动将识别到的 address 类型转化为 ByteArray 类型，所以调用不会有问题，但是在开发者自身的环境下，如果没有做类型转换，Cyano wallet 就会报错。

以下是 js 中获取 ByteArray 格式地址的例子：

```javascript
import {Crypto} from 'ontology-ts-sdk';
var address = new Crypto.Address(account).serialize() // 此处得到的 address 就是 ByteArray 格式
```
