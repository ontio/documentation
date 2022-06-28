
DAPI是为基于Ontology开发的DAPP提供的轻量级去中心化API，支持DAPP通过chrome插件钱包、手机钱包、桌面钱包与Ontology通信。本文介绍如何使用dAPI for chrome，手机版DApp请对接dAPI for mobile。

<!-- TOC -->

- [安装开发环境](#安装开发环境)
- [Ontology dAPI](#ontology-dapi)
    - [dAPI 安装](#dapi-安装)
    - [dAPI 实例](#dapi-实例)
    - [dAPI 方法](#dapi-方法)
        - [与链交互方法](#与链交互方法)
        - [转账方法](#转账方法)
        - [智能合约方法](#智能合约方法)
        - [数据签名](#数据签名)
- [运行例子](#运行例子)
    - [如何填写gaslimit和gasprice](#如何填写gaslimit和gasprice)

<!-- /TOC -->

### 安装开发环境

请确保安装以下软件。

- [Node.js v6+ LTS with npm](https://nodejs.org/en/)

- [Cyano Wallet]( https://chrome.google.com/webstore/detail/ontology-web-wallet/dkdedlpgdmmkkfjabffeganieamfklkm)

- [Git](https://git-scm.com/)


### Ontology dAPI
#### dAPI 安装
创建dApp时，Ontology dAPI是与Ontology链交互的核心API之一，可以从这里下载源码。 [这里](https://github.com/ontio/ontology-dapi). 通过 ```npm``` 安装```ontology-dapi``` :

```
$ npm install @ont-dev/ontology-dapi
```

#### dAPI 实例

创建dAPI 实例时，要先导入库ontology-dapi，并注册客户端:

```typescript
import { client, provider } from '@ont-dev/ontology-dapi';

client.registerClient({
        extension: provider.ExtensionType.Cyano
  })
```

#### dAPI 方法
创建dAPI 实例成功后, 就可以在你的dApp中调用 dAPI 方法.
##### 与链交互方法
```typescript
const network = await client.api.network.getNetwork();
const height = await client.api.network.getBlockHeight();
const block = await client.api.network.getBlock({ block: 1 });
const transaction = await client.api.network.getTransaction({txHash: '314e24e5bb0bd88852b2f13e673e5dcdfd53bdab909de8b9812644d6871bc05f'});
const balance = await client.api.network.getBalance({ address: 'AcyLq3tokVpkMBMLALVMWRdVJ83TTgBUwU' });
```
##### 转账方法
```
const result = await client.api.asset.makeTransfer({ recipient, asset, amount });
```
##### 智能合约方法
```typescript
const result = await client.api.smartContract.invoke({contract,method,parameters,gasPrice,gasLimit,requireIdentity});
const result = await client.api.smartContract.invokeRead({ contract, method, parameters });
const result = await client.api.smartContract.deploy({code,name,version,author,email,description,needStorage,gasPrice,gasLimit});
```
##### 数据签名

```
const message: string = values.message;
const signature: Signature = {
  data,
  publicKey
};
const result = await client.api.message.signMessage({ message });
const result = await client.api.message.verifyMessage({ message, signature });
```

所有方法列表可以在文档中找到 [dAPI 规范](https://github.com/backslash47/OEPs/blob/oep-dapp-api/OEP-6/OEP-6.mediawiki). <br>


### 运行例子

拷贝 [dAPI 例子](https://github.com/ontio/ontology-dapi-demo) ，可以测试dAPI提供了哪些功能.

```
$ git clone https://github.com/ontio/ontology-dapi-demo.git

$ npm install

$ npm run start
```

启动成功后，在浏览器打开页面 http://localhost:3000

页面成功打开后, 点击 Provider->GetProvider.

![dApp Demo Provider](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/dappdemofirstscreen.png)
![dApp Demo Get Provider](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/dappdemoregisterprovider.png)

就通过 API 调用与链交互了.  例如, 点击 Network->Get Block ，结果如下:

![dApp Demo getBlock](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/dappdemonetworkblock.png)

运行转账例子，点击 Asset->Make Transfer ， Cyano Wallet会弹出确认框. 点击 ```Confirm``` 确认交易.

![Cyano Wallet Confirm](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/demo.png)

#### 如何填写gaslimit和gasprice

每笔交易都包含gas limit和gas price。gasprice 会影响到该笔交易被打包所需等待的时间，目前主网和测试网最小值都是500。

gaslimit根据合约执行复杂性而定，可以通过预执行查询该调用需要的最小gaslimit值。Native合约调用gaslimit默认是20000。部署合约根据合约而定，gaslimit一般是20000000以上。
