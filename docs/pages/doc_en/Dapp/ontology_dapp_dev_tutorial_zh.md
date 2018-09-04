---
title:
keywords: sample homepage
sidebar: Dapp_en
permalink: ontology_dapp_dev_tutorial_zh.html
folder: doc_en/Dapp
giturl: https://github.com/ontio/documentation/blob/master/walletDevDocs/ontology_dapp_dev_tutorial_zh.md
---

[English](./ontology_dapp_dev_tutorial_en.html) / 中文

<h1 align="center">Ontology DAPP开发教材</h1>
<p align="center" class="version">Version 1.0.0 </p>


这个教程是给对开发DAPP的初学者，包含以下几个部分：

1. 搭建开发环境

2. 创建工程

3. 写智能合约

4. 编译、部署、调用智能合约

5. 测试智能合约

7. DAPP集成


## 1. 搭建开发环境

开始前我们需要安装软件：

* [Node.js v6+ LTS and npm](https://nodejs.org/en/)

* [Git](https://git-scm.com/)


## 2. Creating a project

### 2.1 dAPI

dAPI是前端开发sdk，下载 dapi 包并使用 [dAPI](https://github.com/ontio/ontology-dapi)

```
npm i ontology-dapi
```

查看 provider 是否存在.

```
const result = await client.api.provider.getProvider();

```

与链交互接口
```
const network = await client.api.network.getNetwork();
const height = await client.api.network.getBlockHeight();
const block = await client.api.network.getBlock({ block: 1 });
const transaction = await client.api.network.getTransaction({txHash: '314e24e5bb0bd88852b2f13e673e5dcdfd53bdab909de8b9812644d6871bc05f'});
const balance = await client.api.network.getBalance({ address: 'AcyLq3tokVpkMBMLALVMWRdVJ83TTgBUwU' });

```

请求 provider 确认交易

```
import { client } from 'ontology-dapi';

//makeTransfer
const result = await client.api.asset.makeTransfer({ recipient, asset, amount });

//invoke
const result = await client.api.smartContract.invoke({contract,method,parameters,gasPrice,gasLimit,requireIdentity});

//prepare execution
const result = await client.api.smartContract.invokeRead({ contract, method, parameters });

//deploy
const result = await client.api.smartContract.deploy({code,name,version,author,email,description,needStorage,gasPrice,gasLimit});

```

### 2.2 dAPI Demo

下载DAPP例子: [dAPI Demo](https://github.com/OntologyCommunityDevelopers/ontology-dapi-demo)

下载并启动例子:

```
git clone https://github.com/OntologyCommunityDevelopers/ontology-dapi-demo.git

npm install

npm run start
```

并在浏览器打开例子 http://localhost:3000

## 3. 写智能合约

智能合约可以用来写后端逻辑和数据存储。我们可以使用SmartX编写智能合约。

打开SmartX并注册[SmartX](http://smartx.ont.io/)


![SmartX Login](../docs/lib/images/smartx.png)


## 4. 编译、部署、调用智能合约

SmartX 使用Cyano Wallet支持部署和调用合约。请确保你的浏览器上已经安装了Chrome扩展程序——Cyano Wallet, 并且创建好了钱包账户。

### 按照和配置Cyano Wallet


![Cyano Wallet](./lib/images/cyano-wallet.png)

Cyano钱包是Chrome/firebox的扩展程序.[Cyano Wallet](https://github.com/OntologyCommunityDevelopers/cyano-wallet)

### 4.1 编译智能合约

在smartx中编译智能合约

![smart contract deploy and invoke](./lib/images/smartx-deploy.png)

### 4.2 Deploy/invoke smart contract

编译和部署智能合约，如果没有测试网的ONG，需要在上申请Discard.

[申请测试网ONG](https://discordapp.com/channels/400884201773334540/453499298097922068)

使用SmartX部署合约。

![Deploy](https://s1.ax1x.com/2018/09/03/PzhTCd.png)

使用SmartX调用合约。

![Invoke](https://s1.ax1x.com/2018/09/03/Pz5JO0.png)

## 5. 测试智能合约

智能合约自动化测试框架.[Testing framework](https://github.com/lucas7788/pythontest)

如果你需要搭建私链，请下载发布版 [Ontology](https://github.com/ontio/ontology/releases)

```
./ontology --testmode --gasprice 0

```


## 6. 开始使用DAPP


### 6.1 启动程序:

启动dAPI Demo
```
npm run start

```

### 6.2 转账或调用智能合约

点击 ```make``` 按钮.会自动弹出Cyano Wallet。

### 6.3 Cyano Wallet中授权并发送交易

点击Cyano Wallet上的确认按钮，授权并发送交易。

![Cyano Wallet Confirm](./lib/images/demo.png)

### 6.4 检查交易

在Cyano Wallet查看交易列表是否有该交易