<h1 align="center">本体分布式身份框架(ONTID)  </h1>

## ONT ID 能为你做什么？

ONT ID为每个用户，公司，物品等任何实体建立基于密码学的综合账户系统，可一站式管理身份、管理资产和支付。ONT ID基于本体区块链技术，不受制于任何中心化机构，完全由用户自己掌控。

在本体，用户可以使用ONT ID做以下事情：

* 使用ONT ID认证和关联自己的多元身份，并授权给第三方证明自己的身份；
* 使用ONT ID管理ONT/ONG等各种数字资产；
* 使用ONT ID在各种场景中进行支付；
* 对于那些没有私钥管理能力的用户，本体基金会可提供账户托管服务，用户可以直接开通；
* ONT ID还可以关联用户的声誉、评分，形成更有用的数据分析报告，而这些都被用户自己掌控。

![](https://github.com/ontio/ontology-DID/raw/master/images/ontid.jpg)
<p align="center">
<b>本体社区提供的概念图展示[1]</b>
</p>


## 为什么需要ONT ID

* 用户自主掌控密钥和对ID的控制权，无需担心任何机构窃取您的数据；

我们使用多种方法帮助用户保护隐私。首先ONT ID为每个人/机构生成公钥等完整属性信息（称之为：DDO），并将这些信息登记到区块链，只有拥有私钥的拥有者才可以控制。出于隐私保护的考虑，区块链上的DDO不包含任何实体真实身份相关的明文，而是采用HASH算法或其他加密算法生成的密文。ONT ID还采用了零知识证明协议和C-L签名算法来保护用户的隐私，数据所有者可指定特定的数据进行开放，使数据的开放和提供增强针对性和匹配性。比如说，某交易所希望证明用户的中国中国公民身份和年收入大于300,000的证明，用户无需提供身份证照片和银行流水信息，而是说，提供一个Y/N的可信证明结果，大大降低用户隐私暴露风险。

* 本体已建立覆盖全球的信任锚和数据验证源，支持218个国家的身份验证；

本体的信任生态已经连接了覆盖全球的信任锚（TrustAnchor），可以对ONT ID进行认证，建立多维度的可信声明，从而可以帮助用户证明自己的身份。

* 完全兼容 W3C DID 国际标准。

* ONT ID是完全开放的，如果您是开发者，可以自由、方便地集成ONT ID所有功能；

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
