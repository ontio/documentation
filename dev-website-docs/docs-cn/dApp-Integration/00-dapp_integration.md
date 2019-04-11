
# 概述

本文针对来到本体公链开发DApp的开发者，提供了通用的DApp接入解决方案，让开发者可以快速上手搭建出DApp。

## 主要 DApp 功能介绍

DApp与本体链产生交互时主要有以下功能：

### 登录

允许验证用户身份或直接查询账号/身份信息。

### 支付

通过调用智能合约实现DApp的支付功能。

### 调用智能合约

对于DApp而言，智能合约实现了其全部或部分业务逻辑。以游戏举例，可以实现购买，出售，租赁，或获取随机数等不同的业务及功能。详细业务逻辑参见智能合约。

### 资产上链（可选）

资产上链并不是DApp开发必须的，但是有些DApp需要特定的链上资产来运行其内部逻辑。
根据对资产的需求不同，本体提供了OEP4，OEP5，OEP8这三种不同类型的链上资产类型。

[什么是OEP-4，OEP-5，OEP-8 ？](#1-什么是OEP-4，OEP-5，OEP-8-？)

## 接入技术实现

为了实现上述的几种功能，我们提供了两种Dapp接入技术方案，两种接入方式都可以实现登录，调用智能合约等功能，开发者可以根据自身需求选择其中一种进行接入的开发

### ONT ID 开放平台接入

ONT ID 开放平台为第三方应用提供第三方登录、支付、智能合约执行、KYC等服务。

ONT ID 开放平台的优势在于，采用可信任的托管模式后，用户登录DApp将不再依赖于用户本地的钱包，大大扩展了DApp的使用范围。

- [ONT ID 开放平台接入](docs-cn/dApp-Integration/08-ontid_integration.md)

### DApi 接入

介绍了 DApp 如何在各种场景下调用 DApi，实现包括登录，调用智能合约等操作。

DApi 接入的优势在于，去中心化程度更高，用户自己可以掌握自己所有的资产和信息，目前也可以较为便利地使用已经支持的钱包登录DApp。

- [DApi 接入](docs-cn/dApp-Integration/09-dapi_integration.md)


## 常见问题

### 1 什么是OEP-4，OEP-5，OEP-8 ？

ONT Enhancement Proposals（OEP）描述了ONT平台的标准，包括核心协议规范，客户端API和合同标准。

OEP-4提案是令牌的标准接口，该标准允许在智能合约中实现令牌的标准API。OEP-4 是标准化的令牌。[OEP-4令牌列表](https://explorer.ont.io/token/list/oep4/10/1)

OEP-5提案是NFT的标准接口，该标准允许在智能合约中实施令牌的标准API。NFT的标准令牌接口允许ONT上的令牌方便其他应用程序使用。[云斗龙](https://hyd-go.alfakingdom.com/) 游戏中的斗龙就是OEP-5标准的令牌。

OEP-8提案是Crypto Item的标准接口，该标准允许您将差异加密项的任意数量的令牌从一个地址传输到另一个地址。 它结合了OEP-4和OEP-5的优点，可以非常方便地传输不同类型的Crypto Item。[本体南瓜](https://explorer.ont.io/token/detail/oep8/edf64937ca304ea8180fa92e2de36dc0a33cc712/10/1) 就是OEP-8标准的令牌。

### 2 使用 DApi 接入目前支持哪些场景？

DApi 接入目前支持以下场景：
- [在手机钱包内打开 DApp](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/01-DAppDocking-Wallet-Opens-DApp)
- [使用手机钱包扫码](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/02-DAppDocking-QRcode)
- [使用 chrome 插件钱包](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/03-DAppDocking-use-chrome-extension-wallet)
- [唤醒手机钱包](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/06-DAppDocking-Wake-up)

### 3 我的DApp需要同步链上信息该怎么做？

当dApp需要查询链上数据（比如交易记录等），可以通过公开的[浏览器接口](https://dev-docs.ont.io/#/docs-cn/explorer/overview) 进行查询，这种方式适用于一些查询频率，查询量不大的dApp，对一些高频次查询需求的dApp，通过浏览器接口查询的方式就无法满足其业务需求，所以我们推出了同步链上数据到应用本地数据库的方法。详情请参考[同步链上信息](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/05-DAppDocking-Sync)

