<h1 align="center">ONT ID Application Suite集成指南 </h1>

## 前言

我们假定您是一个应用（以下简称：应用方），希望集成ONT ID。现在，我们提供您ONT ID Application Suite，ONT ID Applcation Suite集成了ONT ID的全部功能，您可以参考这篇文档帮助您集成ONT ID。


## 创建ONT ID


在Ontology上注册ONT ID需要消耗ONG手续费。首先需要你拥有数字资产账户，且账户里至少有0.01个ONG，然后使用该资产账户为注册ONT ID进行手续费代付，完成ONT ID链上注册。

> 如何创建数字资产账户，使用资产账户创建ONT ID，获取ONT ID相关信息并进行签名。可参考[附录DEMO](https://pro-docs.ont.io/#/docs-cn/ontpass/specification?id=demo)或[SDK开发者文档中心](https://dev-docs.ont.io/#/docs-en/SDKs/00-overview)


> 测试网ONG可到Ontology开发者中心直接申请：[测试网ONG申请入口](https://developer.ont.io/applyOng)

创建成功之后，应用方需要将ONT ID和加密后的Keystore提供给用户保存，用户可以在任意一个本体生态客户端导入和管理自己的ONT ID。



## 认证您的用户

此时您只是建立了一个有公私钥的ONT ID，你还需要实名认证您的用户。

ONTPass基于ONTID及本体信任生态，是一个开放的、去中心化的认证平台，为人、财、物、事提供丰富的认证服务。本体信任生态已聚集了提供全球身份认证服务能力的信任锚，包括IdentityMind、CFCA、商汤科技、Shufti Pro等等，同时还支持邮箱、手机、社交媒体认证方式。

[>> 开始使用ONTPass 认证您的用户](https://pro-docs.ont.io/#/docs-cn/ontpass/overview)

## ONT ID 管理

ONT ID是一个用户自主管理的账户，应用方需要对ONT ID 提供标准化的导入，导出和查询功能。

* **导入**，支持WIF 私钥、KeyStore、助记词三种方式导入；
* **查询和导出**，应用方可随时可以显示ONT ID的地址，并在输入密码的情况下，导出WIF私钥和 Keystore信息。 
* **加密存储规范**，应用方使用[ONT ID Keystore存储规范](https://dev-docs.ont.io/#/docs-en/SDKs/01-wallet-file-specification)标准化加密存储ONT ID；

> NOTE: 如果应用方有自己的用户系统，可以将将自己的用户和ONT ID进行关联。

## 使用托管模式的ONT ID

为便于用户使用，应用方更方便集成，本体基金会提供了安全的、基于低风险账户的托管服务。

托管服务服务下应用方可以更方便地集成，开放集成接口将很快提供。












