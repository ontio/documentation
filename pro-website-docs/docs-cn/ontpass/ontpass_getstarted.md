<h1 align="center">ONTPass产品及服务介绍 </h1>

## ONTPass是什么？

ONTPass基于ONTID及本体信任生态，是一个开放的、去中心化认证服务平台，为您提供KYC（Know Your Customer）服务和多种用户认证服务。本体信任生态已聚集了提供全球身份认证服务能力的信任锚，包括IdentityMind、CFCA、商汤科技、Shufti Pro等等，同时还支持邮箱、手机、社交媒体认证方式。详细[了解本体信任锚](https://info.ont.io/trust-anchor/en)。


## ONTPass的工作原理？

ONTPass的主要职责是：
* 登记本体生态上的信任锚及其认证服务，并提供认证服务发现功能；
* 登记本体生态可以提供的认证模板及可信声明模板，并提供模板发现功能；
* 用户可信声明信息传递；
* 为用户认证需求匹配对应的可信声明模板。

> 注意，如果对于可信声明规范还不了解，可以到[这里](https://github.com/ontio/ontology-DID/blob/master/docs/cn/claim_spec_cn.md)详细了解。 已经注册的认证服务和模板可以到[这里](./ontpass_template.md)了解。

ONTPass开放认证服务，其原理如下：

![](http://assets.processon.com/chart_image/5a5fff53e4b0abe85d5e3e5f.png)

流程中涉及到的参与方包括：

* 需求方（Requester）: 需要对用户进行认证的DApp,机构或服务场景，是本体信任生态中认证服务的需求方。
* ONTPass：基于本体区块链的去中心化身份交易平台，ONTPass主要用于协同用户和需求方进行数据交换，数据全程被加密，ONTPass并不会触碰用户隐私数据。
* TrustAnchor：本体信任生态中的信任锚，为用户提供认证服务并能签发可信声明，背后连接了服务全球的身份认证服务供应商，能帮助用户实现身份认证。

## 为什么要使用ONTPass

ONTPass具有以下优势：

* 本体信任生态已经连接了全球的认证服务机构，覆盖218个国家的用户；
* 低成本，一次认证，可以多次使用，总体降低了多次认证成本;
* ONTPass保护用户隐私，协议使用[End-to-End加密规范]()，全程保护用户数据；
* 基于本体区块链，所有认证动作和认证结果被区块链存证。
* Claim规范支持零知识证明等密码学算法，用户可以选择性出示自己的身份信息，最大限度保护用户隐私。

## 开始使用

### 1 如果您有自己的APP或平台，希望帮助您的用户建立ONTID，并认证您的用户。

首先您需要理解ONTID和可信声明体系，并可以把他们集成到您的系统中。了解ONTID 和 可信声明的使用方法，请先到[这里](https://github.com/ontio/ontology-DID/blob/master/docs/cn/get_started_cn.md)了解。

现在可以[开始使用ONTPass服务]()。

### 2 如果您没有额外开发资源，只希望快速认证您的用户。 

[ONTO](https://onto.app)已经帮助用户完成了认证并管理好了可信声明，您只要提出认证请求，用户通过ONTO授权后即可提交用户认证信息。这个选项的好处是，您不必开发和管理用户ONTID和Claim系统。

现在可以[开始使用ONTPass服务](https://github.com/ontio/documentation/blob/master/pro-website-docs/docs-cn/ontpass/thirdparty_kyc.md)。



