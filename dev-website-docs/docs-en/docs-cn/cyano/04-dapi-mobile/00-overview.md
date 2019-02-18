
cyano-bridge
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

```JavaScript
var client = require('cyanobridge').client
```

### ES6 模块

```JavaScript
import { client } from 'cyanobridge'
```

### Web require

导入 `./lib` 文件夹下的 `browser.js` 文件:

```html
<script src="./lib/browser.js"></script>

var client = CyanoMobile.client;
```

## 初始化

```JavaScript
import { client } from 'cyanobridge'

client.registerClient();
```
