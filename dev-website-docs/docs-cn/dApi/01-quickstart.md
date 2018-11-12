## 如何使用 
ontology-dapi 可以作为 CommonJS/ES6 模块或在网页中直接使用. 

### 安装 CommonJS/ES 模块
```
npm install ontology-dapi
```

### 导入 CommonJS
```
var client = require('ontology-dapi').client;
```

### 导入 ES6 模块
```
import { client } from 'ontology-dapi';
```

### Web require
导入 '/lib' 文件夹下的 browser.js 文件:
```
<script src="./lib/browser.js"></script>
```

使用方法.
```
var client = dApi.client;
```

### 初始化
dApp 先注册 **dAPI provider**的客户端.

```
import { client } from 'ontology-dapi';

client.registerClient({});
```

## 接口调用例子

请参考例子， [EXAMPLES.md](EXAMPLES.md) 或 [demo app](https://github.com/OntologyCommunityDevelopers/ontology-dapi-demo)

