<h1 align="center">ONTPass产品及服务介绍 </h1>

## ONTPass是什么？

ONTPass基于ONTID及本体信任生态，是一个开放的、去中心化的认证平台，为人、财、物、事提供丰富的认证服务。本体信任生态已聚集了提供全球身份认证服务能力的信任锚，包括IdentityMind、CFCA、商汤科技、Shufti Pro等等，同时还支持邮箱、手机、社交媒体认证方式。详细[了解本体信任锚](https://info.ont.io/trust-anchor/en)。

## ONTPass能为你做什么？

如果您拥有自己的APP或平台，希望帮助您的用户并通过ONTPass认证您的用户，您可以把集成ONTPass到您的平台或产品中，用于KYC（Know Your Customer）、身份认证、Login等多种业务场景。

ONTPass具有以下优势：

* 本体信任生态已经连接了全球的认证服务机构，覆盖218个国家的用户；
* 低成本，一次认证，可以多次使用，总体降低了多次认证成本;
* 协议使用[End-to-End加密规范](https://github.com/ontio/ontology-DID/blob/master/docs/cn/end-to-end-encryption.md)，全程保护用户数据；
* 基于本体区块链，所有认证动作和认证结果被区块链存证。
* 规范支持零知识证明等密码学算法，用户可以选择性出示自己的身份信息，最大限度保护用户隐私。

[>> 开始使用ONTPass服务](http://pro-docs.ont.io/#/docs-cn/ontpass/ontpass-auth)。


## 了解ONTPass的工作原理？

> ONTPass基于ONT ID，了解ONTID 和 可信声明的使用方法，请先了解[ONT ID](https://github.com/ontio/ontology-DID/blob/master/docs/cn/get_started_cn.md)。

ONTPass开放认证服务，其原理如下：
![](http://assets.processon.com/chart_image/5a5fff53e4b0abe85d5e3e5f.png)

ONTPass的主要职责是：
* 登记本体生态上的信任锚及其认证服务，并提供认证服务发现功能；
* 登记本体生态可以提供的认证模板及可信声明模板，并提供模板发现功能；
* 用户可信声明信息传递；
* 为用户认证需求匹配对应的可信声明模板。

流程中涉及到的参与方包括：
* 认证需求方（Requester）: 需要对自有用户进行认证的DApp，机构或服务场景，是本体信任生态中认证服务的需求方。
* ONTPass：基于本体区块链的去中心化身份交易平台，ONTPass主要用于协同用户和需求方进行数据交换，数据全程被加密，ONTPass并不会触碰用户隐私数据。
* TrustAnchor：本体信任生态中的信任锚，为全球用户提供认证服务并能签发可信声明，背后连接了服务全球的身份认证服务供应商，能帮助用户实现身份认证。

