---
title: 
keywords: sample homepage
sidebar: ont_doc_zh
permalink: tutorial_for_developer_zh.html
folder: doc_zh
---


[English](./tutorial_for_developer_en.html) / 中文


<h1 align="center"> 本体开发者新手指南</h1>
<p align="center" class="version">版本 0.7.0 </p>

## 概述

欢迎来到本体开发者社区！

本体是一个规划较为庞大的基础性公有链，在正式使用本体开发之前，您首先需要了解本体技术社区的激励计划，并确定您的开发需求，便于我们指导您如何获取开发资源。

## 本体技术社区激励计划

技术社区是公有链项目的核心力量，本体在技术社区的激励计划中，设置了10% 的ONT 用于技术社区的激励，这是目前公有链项目中技术社区激励的最大比例。随着本体第一批项目在github上开源，技术社区也正式启动了。无论你身处全球的任何地方，你都可以以各种方式参与到技术社区中来。在第一阶段，你可以有以下方式参与：

* 个人技术贡献者

每个个人技术参与者，可以在本体的项目群中选择感兴趣的项目参与，提交新的Enhancement Proposal (OEP)、实现代码、解决BUG等等多种方式。也可以申请提出新的项目。本体基金会会根据不同的贡献参与度进行不同程度的支持。

* 技术社区小组

技术人员可以根据技术方向的爱好自己组织不同的技术社区小组，来开展更大规模的分布式技术协作，可以设定自己小组的名称、制定自己的小组章程、选择执行委员会、评估和筛选项目、开设自己的github等，本体基金会会根据不同技术社区小组的发展计划评估给予支持。（我们已经收到一些技术社区小组的名字建议，如“雅典学院”、“奥林匹亚山”等）

* 机构技术贡献者

机构可以与本体合作开展与自身业务相关的技术研究，共同进行底层产品技术和业务通用模块的研究，双方可以共同在技术、经费、资源等各方面进行灵活合作。

[>> 社区贡献标准流程](https://github.com/ontio/documentation/blob/master/zh-CN/standard_process_for_contributor.md)

## 了解您的开发需求

我们建议您确定您的开发需求和目标，根据以下多种选项，进入正确的入口。

### **搭建测试网TESTNET**

如果您需要独立部署区块链，建立自有链（公有链/联盟链/私有链），并在自有链上开发特定的应用。

* 第一步，安装Ontology并搭建测试网络。[>> 进入安装](https://github.com/ontio/ontology)

* 第二步，构建ONT ID体系。Ontology DID（简称：ONT ID）是一个去中心化的身份标识协议，基于W3C的DID规范。协议支持各类实体包括人、组织机构、物品及内容的分布式和多样化的确权、识别、认证等协同服务。ONT ID是本体区块链体系重要的基础设施。ONT ID 身份标识协议及信任框架已经被完整地通过NeoVM智能合约实现在本体区块链上。[>> 进入安装](https://github.com/ontio/ontology-DID)

* 第三步，部署区块链浏览器（可选）。[>> 进入安装](https://github.com/ontio/ontology-explorer)

### **DAPP应用开发**

如果您是DAPP开发者，您可以直接基于本体已经发布的测试网络TestNet开发DAPP应用。我们建议您可以聚焦智能合约和SDK的使用。

SDK已经封装了本体的标准化交易，我们推荐您使用SDK来和本体进行交互。目前支持：本地钱包管理、数字身份管理、数字资产管理、智能合约部署和调用、与节点通信等。

* [>> JAVA SDK](https://github.com/ontio/ontology-java-sdk) 

* [>> TS SDK](https://github.com/ontio/ontology-ts-sdk)  

* [>> Go SDK](https://github.com/ontio/ontology-go-sdk)  

另外可以参考我们的RPC和RESTFUL接口,包括以下:
* [>> RPC & RESTFUL](https://github.com/ontio/documentation/tree/master/ontology-API)


智能合约是一套以数字形式定义的承诺，包括合约参与方可以在上面执行这些承诺的协议。区块链技术给我们带来了一个去中心化的，不可篡改的，高可靠性的系统，在这种环境下，智能合约才大有用武之地。智能合约是区块链最重要的特性之一，也是区块链能够被称为颠覆性技术的主要原因。

进入 [>>本体智能合约开发指南](./smart-contract-tutorial)开始了解如何通过智能合约开发和配置您的应用。


### **成为本体信任锚**

信任锚Trust Anchor是指在本体生态上提供认证服务的合作方，其可能是政府机关、大学、银行、第三方认证服务机构（比如CA机构）、生物识别科技公司等等，我们欢迎加入本体生态，共建新一代分布式信任链网。

希望成为信任锚，[这里](https://info.ont.io/cooperation/zh)申请加入。

如果您是信任锚，请进入[>> 本体信任锚接入标准](./docs/cn/verification_provider_specification_cn.md)了解接入流程和标准。


### **其他生态开发者**

其他生态开发者可以仔细阅读我们的文档中心、GitHub主库、Discord讨论组，选择感兴趣的主题进行更深入了解。

Ontology GitHub: https://github.com/ontio/

Ontology Discord: https://discord.gg/4TQujHj/