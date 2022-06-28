
[OEP-6 ](https://github.com/backslash47/OEPs/blob/oep-dapp-api/OEP-6/OEP-6.mediawiki) 提案定义了浏览器端的 `dAPI` 规范。

基于该提案，我们提供了 `ontology-dapi`，用于供 `Chrome` 浏览器上的 `DAPP` 使用。dAPI 使用 `TypeScript` 实现，同时也支持在 `javascript` 工程中使用。

## 1. 安装

### 1.1 npm 安装

你可以使用 `npm` 进行安装

```shell
npm install @ont-dev/ontology-dapi
```

### 1.2 CDN 安装

目前可以通过 `jsDelivr` 获取到最新版本的资源，在页面上引入 `js`  文件即可开始使用。

```html
<script src="https://cdn.jsdelivr.net/npm/ontology-dapi/lib/browser.min.js"></script>
```

!> 建议使用 `CDN` 引入 `ontology-dapi` 的用户在链接地址上锁定版本，以免将来 `ontology-dapi` 升级时受到非兼容性更新的影响。

## 2. 导入

### 2.1 CommonJS

```javascript
var client = require('@ont-dev/ontology-dapi').client;
```

### 2.2 ES6 模块

```javascript
import { client } from '@ont-dev/ontology-dapi';
```

### 2.3 Web require

导入 `./lib` 文件夹下的 `browser.js` 文件:

```html
<script src="./lib/browser.js"></script>
```

## 3. 初始化

```javascript
import { client, provider } from '@ont-dev/ontology-dapi';

client.registerClient({
        extension: provider.ExtensionType.Cyano
  })
```

!> `Mobile Provider` 需要注册，`Chrome Provider` 不需要注册。

## 4. 使用

在 `ontology-dapi` 中，有 7 个模块： `asset` 、 `identity` 、 `message` 、 `network` 、 `provider` 、 `smartContract` 和  `utils` 。

### 4.1 网络

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

### 4.2 资产

`makeTransfer` 接口用于构造交易。

```javascript
const result = await client.api.asset.makeTransfer({ recipient, asset, amount });
```

### 4.3 智能合约

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

### 4.4 消息

你可以通过钱包插件签名，`DAPP` 验证签名实现你的 `DAPP` 登陆流程。

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

!> 如果希望获得更多的示例代码，你可以点击[ 这里 ](https://github.com/ontio/ontology-dapi-demo)获取 `ontology-dapi` 的实例程序。

## 5. 常见问题

- 我可以利用 `cyano` 将我的 `DAPP` 同时兼容移动端与浏览器端吗？
  
  完全没问题！你可以参考我们提供的示例项目[ dapi-universal ](https://github.com/ontio-cyano/dapi-universal)。