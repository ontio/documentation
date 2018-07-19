---
title:
keywords: sample homepage
sidebar: DID_zh
permalink: ontology_DID_zh.html
folder: doc_zh/DID
giturl: https://github.com/ontio/ontology-DID/master/README_cn.md
---

[English](./ontology_DID_en.html) / 中文


<h1 align="center">本体分布式身份框架(ONTID)  </h1>
<p align="center" class="version">Version 0.7.0 </p>

## 概述

Ontology DID（简称：ONT ID）是一个去中心化的身份标识协议，基于W3C的DID规范。协议支持各类实体包括人、组织机构、物品及内容的分布式和多样化的确权、识别、认证等协同服务。ONT ID为每个主体建立基于密码学的数字身份，使得数据授权、确权自主化，使身份和数据真正变为用户可以掌控的资产。ONT ID具有去中心化、自主管理、隐私保护、安全易用等特点。

本体基于ONT ID及可验证声明协议建立去中心化的信任模型和分布式信任传递体系，同时引入C-L签名算法、西格玛协议等密码学技术来实现可验证声明的隐私保护。同时本体还将基于ONT ID纳入各种认证服务机构，建立对主体身份的多源认证，实现完整身份画像。

去中心化的信任模型不仅仅依赖特定的中心实体构建信任关系，实体之间还能够自发、对等地产生信任关系。信任的传递由实体间的相互认证实现。一个实体被数量越多的实体认证，其可信度就越高；被可信度越高的实体认证的实体，亦将获得更高的可信度。

## 工作原理

在使用平台之前，您可以先大致了解整个去中心化信任机制的原理.

在整个信任生态中,会包括以下参与角色.

* **用户Recipient** ONT ID的持有者,可以接受Verifier签发的可信声明,也可以为他人签发可信声明。 

* **声明发行方 Claim Issuer** 可以是本体生态的任何一个ONT ID持有者，其中包括本体生态上的信任锚（提供认证服务的合作方），其可能是政府机关、大学、银行、第三方认证服务机构（比如CA机构）、生物识别科技公司等等，这些企业为本体ONT ID的持有者（Owner）提供多维度的认证，并第一时间通过Ontology BlockChain来记录认证行为和认证结果HASH，从而为用户认证需求方/场景方提供了标准化、可信的认证方式。

* **声明验证方 Claim Verifier** 接受用户可信声明,并进行验证的场景,比如需要验证面试者的身份信息/学历/行业技能等雇主.

* **应用开发者 Developer** 基于ONT ID协议和接口为用户和各种场景提供各种应用开发服务。


### **身份标识协议**

实体是指现实世界中的个人、组织（组织机构、企事业单位等）、物品（手机、汽车、IOT设备等）、内容（文章、版权等），而身份是指实体在网络上的对应标识。本体网络使用本体身份标识（ONT ID）来标识和管理实体在链上的数字身份。在本体区块链上，一个实体可以对应到多个身份标识，且多个身份标识之间没有任何关联。

[>> 详细了解](./ONTID_protocol_spec_zh.html)

### **可信声明协议**

可信声明(Verifiable Claim)是指，一个实体对另一个实体（包括自己）的某些属性作出的描述性声明，并附加自己的数字签名，用以证明这些属性的真实性，可被其他实体验证。可验证声明协议详细描述了声明的签发、存储、验证等流程及规范。


![](./lib/images/20180316233010.png)
[>> 详细了解](./claim_spec_zh.html)

## 部署安装

> 注：ONT ID 身份标识协议及信任框架已经被完整地通过NeoVM智能合约实现在本体区块链上。同时，**ONT ID是一个开放的协议，我们支持使用不同底层账本技术和不同的智能合约体系来实现**。以下我们以Ontology区块链和NeoVM智能合约来进行部署。

* 第一步 部署区块链

    [>> Ontology Blockchain](https://github.com/ontio/ontology) 开始部署区块链；

* 第二步 部署IDContract智能合约
    
    请在[这里](./resources/smart-contract/NeoVM/IdContract.avm)下载部署文件，并进入[本体智能合约开发指南](https://github.com/ontio/documentation/tree/master/smart-contract-tutorial)，将这本智能合约部署到区块链。



## 开始使用

进入 [>>快速开发指南](https://github.com/ontio/ontology-DID/blob/master/docs/cn/get_started_cn.html)开始了解.

当然您也可以直接参考我们的各种SDK和RPC接口,包括以下:

* [>> JAVA SDK](https://github.com/ontio/ontology-java-sdk) 

* [>> TS SDK](https://github.com/ontio/ontology-ts-sdk)  


## 信任锚

信任锚Trust Anchor是指在本体生态上提供认证服务的合作方，其可能是政府机关、大学、银行、第三方认证服务机构（比如CA机构）、生物识别科技公司等等，我们欢迎加入本体生态，共建新一代分布式信任链网。

希望成为信任锚，[这里](https://info.ont.io/cooperation/zh)申请加入。

如果您是信任锚，请进入[>> 本体信任锚接入标准](./verification_provider_specification_zh.html)了解接入流程和标准。
