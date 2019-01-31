
[OEP-6](https://github.com/backslash47/OEPs/blob/oep-dapp-api/OEP-6/OEP-6.mediawiki) 提案定义了浏览器端的 dApi 规范。基于该提案，我们提供了 `ontology-dapi`，用于供 Chrome 浏览器上的 dApp 使用。

## 安装

### npm 安装

你可以使用 `npm` 进行安装

```shell
npm install ontology-dapi
```

### CDN

目前可以通过 `jsDelivr` 获取到最新版本的资源，在页面上引入 js 文件即可开始使用。

```html
<script src="https://cdn.jsdelivr.net/npm/ontology-dapi@0.4.6/lib/browser.min.js"></script>
```

## 导入

### CommonJS

```JavaScript
var client = require('ontology-dapi').client;
```

### ES6 模块

```JavaScript
import { client } from 'ontology-dapi';
```

### Web require

导入 `./lib` 文件夹下的 `browser.js` 文件:

```html
<script src="./lib/browser.js"></script>
```

## 初始化

```JavaScript
import { client } from 'ontology-dapi';

var client = dApi.client;
client.registerClient({});
```