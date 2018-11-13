---
title:
keywords: sample homepage
sidebar: Dapp_zh
permalink: ontology_dapp_dapi_zh.html
folder: doc_zh/Dapp
giturl: https://github.com/ontio/ontology-dapi/blob/master/README_cn.md
---

<h1 align="center"> ontology dApi </h1>

[English](./ontology_dapp_dapi_en.html) / 中文

<h1 align="center">ontology-dapi</h1>

<p align="center" class="version">Version 1.0.0 </p>



DAPI是基于Ontology blockchain开发dApp的轻量级去中心化API。本工程是根据OEP-6实现了dAPI ，请参考[OEP-6](https://github.com/backslash47/OEPs/blob/oep-dapp-api/OEP-6/OEP-6.mediawiki) 协议。

使用前请先安装 **dAPI provider** . 比如 [Cyano Wallet](https://github.com/OntologyCommunityDevelopers/cyano-wallet).

dAPI使用TypeScript实现, 同时也支持在JavaScript工程中使用.

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

## 使用例子

请参考例子， [](EXAMPLES.md) 或 [demo app](https://github.com/OntologyCommunityDevelopers/ontology-dapi-demo)

# 文档

所有dAPI方法分成这几个模块: **asset**, **identity**, **message**, **network**, **provider**, **smartContract** and **utils**.
方法定义请参考 [OEP-6](https://github.com/backslash47/OEPs/blob/oep-dapp-api/OEP-6/OEP-6.mediawiki).

# Build

### 安装工具与依赖

* Node
* Npm

### 开发

执行如下命令:

#### 下载
```
git clone 'https://github.com/OntologyCommunityDevelopers/ontology-dapi.git'
cd ontology-dapi
```

#### 安装

```
npm install
```

#### 开发Build

````
npm run build:dev
````


#### 产品Build

````
npm run build:prod
````


## 创建工具

* [TypeScript](https://www.typescriptlang.org/) - Used language
* [Node.js](https://nodejs.org) - JavaScript runtime for building

## 作者

* **Matus Zamborsky** - *Initial work* - [Backslash47](https://github.com/backslash47)

## License

This project is licensed under the ISC License - see the [LICENSE.md](LICENSE.md) file for details
