
## ONT ID 是什么？

ONT ID为每个用户，公司，物品等任何实体建立基于密码学的综合账户系统，可一站式管理身份、管理资产和支付。ONT ID基于本体区块链技术，不受制于任何中心化机构，完全由用户自己掌控。

在本体，可以使用ONT ID做以下事情：

* 统一身份登录

区块链世界的唯一身份，无需记住众多应用账号，只需一个ONT ID，账户登录问题全解决SSO。

* 资产管理

众多区块链资产的管理是个很令人头疼的问题，不要担心，ONT ID可以将你的资产关联起来，管理更方便。

* 快捷支付

通过ONT ID将你的资产私钥和你的验证方式关联，例如指纹、faceID，手机验证等。

* 多源认证

基于本体信任生态，不仅可以支持近200个国家的实名身份认证，可以关联用户的学历、声誉、信用，形成多源数据，而这些都被用户自己掌控。

![](https://github.com/ontio/ontology-DID/raw/master/images/ontid.jpg)
<p align="center">
<b>本体社区提供的概念图展示[1]</b>
</p>


## 了解ONT ID特性

ONT ID有如下特点：

* 可信身份

基于区块链技术，具有不可篡改的天然属性；多维度的身份验证和数据验证，保证身份可信。

* 数据安全

所有数据通过加密技术存储，用来加密的密钥可以自我保存也可以选择托管到可信的第三方；同时，所有数据的读取和验证都需要获得您的私钥授权。

* 使用便捷

摒弃繁琐，通过ONT ID将您的自身特性和数据之间做关联，实现快速验证触达数据，方便快捷。

* 国际标准和全球覆盖

ONT ID完全兼容 W3C DID 国际标准，您的身份和数据适用于世界上每一个支持ONT ID协议的机构和应用，没有国家和地域的限制，真正做到信息和价值全球自由传递。 


## 如何集成ONT ID

ONT ID是完全开放的，如果您是开发者，可以自由、方便地集成ONT ID Application Suite所有功能。

>> [开始集成](https://pro-docs.ont.io/#/docs-cn/ontid/get_started)

## 了解去中心化身份协议

您可以先大致了解ONT ID的工作原理。在ONT ID使用和协作过程中,会包括以下参与角色.

* **用户Recipient** ONT ID的持有者,可以接受Verifier签发的可信声明,也可以为他人签发可信声明。 

* **声明发行方 Claim Issuer** 可以是本体生态的任何一个ONT ID持有者，其中包括本体生态上的信任锚（提供认证服务的合作方），其可能是政府机关、大学、银行、第三方认证服务机构（比如CA机构）、生物识别科技公司等等，这些企业为本体ONT ID的持有者（Owner）提供多维度的认证，并第一时间通过Ontology BlockChain来记录认证行为和认证结果HASH，从而为用户认证需求方/场景方提供了标准化、可信的认证方式。

* **声明验证方 Claim Verifier** 接受用户可信声明,并进行验证的场景,比如需要验证面试者的身份信息/学历/行业技能等雇主.

* **应用开发者 Developer** 基于ONT ID协议和接口为用户和各种场景提供各种应用开发服务。

![](https://github.com/ontio/ontology-DID/raw/master/images/claim_workflow_cn.png)


ONT ID协议体系包括两个部分，身份标识协议（Ontology DID）和可信声明协议（Verifiable Claim Protocol）。

### Ontology DID 协议

Ontology DID是一个去中心化的身份标识协议，基于[W3C](https://www.w3.org/2017/vc/WG/)的[DID规范](https://w3c-ccg.github.io/did-spec/)。本体ONT ID基于这个协议来标识和管理链上的数字身份。[>> 详细了解身份标识协议](https://github.com/ontio/ontology-DID/blob/master/docs/cn/ONTID_protocol_spec_cn.md)

### Verifiable Claim 协议

可信声明(Verifiable Claim)是指，一个实体对另一个实体（包括自己）的某些属性作出的描述性声明，并附加自己的数字签名，用以证明这些属性的真实性，可被其他实体验证。可验证声明协议详细描述了声明的签发、存储、验证等流程及规范。本体可验证声明协议建立去中心化的信任模型和分布式信任传递体系，同时引入C-L签名算法、西格玛协议等密码学技术来实现可验证声明的隐私保护。
[>> 详细了解可信声明协议](https://github.com/ontio/ontology-DID/blob/master/docs/cn/claim_spec_cn.md)


## 为什么需要去中心化身份

美国时间2018年3月18日，美国社交媒体巨头Facebook被爆出超过5000万用户信息数据被泄露。3月27日，Facebook CEO扎克伯格在多家报纸上刊登文章，进行公开道歉，表示“辜负了用户的信任”。他说：“我们有责任保护你们的信息，如果我们不能，我们也不配，这是一种违背信任的行为，我很抱歉我们当时没有做更多的事情。” 
显然，Facebook信息泄露丑闻只是问题的一次集中爆发。对于公众而言，扎克伯格的道歉更多是情感的表达，更需要的是通过法律、技术等方式来保护用户的数据隐私，保护健康的网络公共领域环境。


## 参考

- [1] "Ontology Trust Network" by https://twitter.com/musuko_crypto
