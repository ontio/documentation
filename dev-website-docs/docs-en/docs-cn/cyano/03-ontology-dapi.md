
[OEP-6](https://github.com/backslash47/OEPs/blob/oep-dapp-api/OEP-6/OEP-6.mediawiki) 提案定义了浏览器端的 dAPI 规范。基于该提案，我们提供了 `ontology-dapi`，用于供 Chrome 浏览器上的 dApp 使用。dAPI 使用 TypeScript 实现，同时也支持在 javascript 工程中使用。

## 安装

### npm 安装

你可以使用 `npm` 进行安装

```shell
npm install ontology-dapi
```

### CDN

目前可以通过 `jsDelivr` 获取到最新版本的资源，在页面上引入 js 文件即可开始使用。

```html
<script src="https://cdn.jsdelivr.net/npm/ontology-dapi/lib/browser.min.js"></script>
```

!> 建议使用 CDN 引入 `ontology-dapi` 的用户在链接地址上锁定版本，以免将来 `ontology-dapi` 升级时受到非兼容性更新的影响。

## 导入

### CommonJS

```javascript
var client = require('ontology-dapi').client;
```

### ES6 模块

```javascript
import { client } from 'ontology-dapi';
```

### Web require

导入 `./lib` 文件夹下的 `browser.js` 文件:

```html
<script src="./lib/browser.js"></script>
```

## 初始化

```javascript
import { client } from 'ontology-dapi';

var client = dApi.client;
client.registerClient({});
```

## 使用

在 `ontology-dapi` 中，有7个模块：`asset`、`identity`、`message`、`network`、`provider`、`smartContract` 和 `utils`。

### 网络

- 查询所接入网络

```javascript
const network = await client.api.network.getNetwork();
```

- 查询当前区块高度

```javascript
const height = await client.api.network.getBlockHeight();
```

- 查询区块信息

```javascript
const block = await client.api.network.getBlock({ block: 1 });
```

- 查询交易

```javascript
const transaction = await client.api.network.getTransaction({txHash: '314e24e5bb0bd88852b2f13e673e5dcdfd53bdab909de8b9812644d6871bc05f'});
```

- 查询账户余额

```javascript
const balance = await client.api.network.getBalance({ address: 'AcyLq3tokVpkMBMLALVMWRdVJ83TTgBUwU' });
```

### 资产

`makeTransfer` 接口用于构造交易。

```javascript
const result = await client.api.asset.makeTransfer({ recipient, asset, amount });
```

### 智能合约

- 执行智能合约

```javascript
const result = await client.api.smartContract.invoke({contract,method,parameters,gasPrice,gasLimit,requireIdentity});
```

- 预执行智能合约

```javascript
const result = await client.api.smartContract.invokeRead({ contract, method, parameters });
```

- 部署智能合约

```javascript
const result = await client.api.smartContract.deploy({code,name,version,author,email,description,needStorage,gasPrice,gasLimit});
```

### 消息

- 签名

```javascript
const message: string = values.message;
const result = await client.api.message.signMessage({ message });
```

- 验证签名

```javascript
const message: string = values.message;
const signature: Signature = {
  data,
  publicKey
};
const result = await client.api.message.verifyMessage({ message, signature });
```

!> 你也可以点击[这里](https://github.com/OntologyCommunityDevelopers/ontology-dapi-demo)获取 `ontology-dapi` 的实例程序。
