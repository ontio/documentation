---
title: 
sidebar: ont_doc_zh
permalink: documentation_cn.html
folder: doc_zh
---

<p align="center">
  <img
    src="https://github.com/ontio/documentation/blob/master/zh-CN/Ontology_CH.png"
    width="200px"
  >
</p>
<h1 align="center"></h1>
<p align="center">
  新一代多链式公有链平台 & 分布式信任生态
</p>

---

[English](/README.md) | 中文

## 本体基础架构体系

- [本体](#Ontology) :hatching_chick:
- [本体 WASM](#Ontology-wsam) :hatching_chick:
- [本体 Crypto](#Ontology-crypto) :hatching_chick:
- [本体 Eventbus](#Ontology-eventbus) :hatching_chick:
- [本体 RPC and Restful](#Ontology-rpc-and-restful) :hatching_chick:
- [本体预言机](#Ontology-oracle) :hatching_chick:
- [本体 FPGA](#Ontology-fpga) :egg:

## 本体协议体系及SDK

- [本体 DID](#Ontology-did) :hatched_chick:
- [本体 Java SDK](#Ontology-java-sdk) :hatched_chick:
- [本体 TS SDK](#Ontology-ts-sdk) :hatched_chick:

## 本体应用
- [ONTO](#onto) :hatching_chick:
- [本体分布式数据交易框架](#Ontology-ddxf) :hatched_chick:

---

## 本体文档

- 白皮书概览<br/>[英语](https://ont.io/wp/Ontology-Introductory-White-Paper-EN.pdf) / [中文](https://ont.io/wp/Ontology-Introductory-White-Paper-ZH.pdf)  translated by  [@Onchain](http://www.onchain.com)
- 技术白皮书<br/>[英语](https://github.com/ontio/Documentation/blob/master/Ontology-technology-white-paper-EN.pdf) / [中文](https://ont.io/wp/Ontology-technology-white-paper-ZH.pdf)  translated by  [@Onchain](http://www.onchain.com)
- 生态白皮书<br/>[英语](https://ont.io/wp/Ontology-Ecosystem-White-Paper-EN.pdf) / [中文](https://ont.io/wp/Ontology-Ecosystem-White-Paper-ZH.pdf)  translated by  [@Onchain](http://www.onchain.com)
- [智能合约](https://github.com/ontio/documentation/tree/master/smart-contract-tutorial)
- [OEPs](https://github.com/ontio/OEPs)

---

### <a name="Ontology"></a>本体 <sup>[top⇈](#本体基础架构体系)</sup>
> 本体致力于创建一个组件化、可自由配置、跨链支持、高性能、横向可扩展的区块链底层基础设施。 让部署及调用去中心化应用变得非常简单。
- [本体](https://github.com/ontio/ontology) - 主仓库

### <a name="Ontology-wsam"></a>本体 WASM <sup>[top⇈](#本体基础架构体系)</sup>
> 本体 wasm是本体区块链项目的执行wasm智能合约虚拟机， 也可以独立运行于其他的环境。
- [本体 WASM](https://github.com/ontio/ontology-wasm) - 主仓库

### <a name="Ontology-crypto"></a>本体 Crypto <sup>[top⇈](#本体基础架构体系)</sup>
> 本体网络加密库。
- [本体 Crypto](https://github.com/ontio/ontology-crypto) - 主仓库

### <a name="Ontology-eventbus"></a>本体 Eventbus <sup>[top⇈](#本体基础架构体系)</sup>
> 本体 eventbus是基于actor模型的消息中间件，提供高性能的模块间或节点间通信功能。
- [本体 Eventbus](https://github.com/ontio/ontology-eventbus) - 主仓库

### <a name="Ontology-rpc-and-restful"></a>本体 RPC and Restful <sup>[top⇈](#本体基础架构体系)</sup>
> 本体 Rpc Api 和本体 Restful API。
- [本体 RPC and Restful](https://github.com/ontio/documentation/tree/master/ontology-API) - 主仓库

### <a name="Ontology-oracle"></a>本体预言机 <sup>[top⇈](#本体基础架构体系)</sup>
> 预言机是现实世界与区块链数据交互的入口。
- [本体预言机](https://github.com/ontio/ontology-oracle-py) - 主仓库

### <a name="Ontology-fpga"></a>本体 FPGA <sup>[top⇈](#本体基础架构体系)</sup>
> 高速数字签名验证的FPGA设计与实现。
- [本体 FPGA](https://github.com/ontio/ontology-fpga) - 主仓库

### <a name="Ontology-did"></a>本体 DID <sup>[top⇈](#本体基础架构体系)</sup>
> 去中心化身份标识协议，实现现实世界中的人财物事在链上的标识、认证和确权。
- [本体 DID](https://github.com/ontio/ontology-DID) - 主仓库

### <a name="Ontology-java-sdk"></a>本体 Java SDK <sup>[top⇈](#本体基础架构体系)</sup>
> 该项目是本体官方Java SDK，它是一个综合性SDK，目前支持：本地钱包管理、数字身份管理、数字资产管理、智能合约部署和调用、与节点通信等。未来还将支持更丰富的功能和应用。
- [本体 Java SDK](https://github.com/ontio/ontology-java-sdk) - 主仓库

### <a name="Ontology-ts-sdk"></a>本体 TS SDK <sup>[top⇈](#本体基础架构体系)</sup>
> 该项目是本体官方Typescript SDK，目前支持：本地钱包管理、数字身份管理、数字资产管理、智能合约部署和调用以及资产转账等等。未来还将支持更丰富的功能和应用。
- [本体 TS SDK](https://github.com/ontio/ontology-ts-sdk) - 主仓库

### <a name="onto"></a>ONTO <sup>[top⇈](#本体基础架构体系)</sup>
> ONTO是基于本体的综合客户端产品，是本体信任搜索引擎和区块链体系的入口。ONTO将帮助用户实现包括数字身份管理、数字资产管理、分布式数据交换等综合性功能。ONTO将数字身份与现实身份进行映射关联，用户可以利用这款产品建立自己的数字身份和多维的身份画像，通过密码学算法实现隐私保护。ONTO可以安全可靠地管理数字资产，并将其应用到各种场景中。同时，ONTO通过授权体系和加密算法建立一个对用户来说可靠的、可掌控的数据交易体系。未来，基于ONTO的数字身份和数字资产，将进一步支持各类社交场景和协作需求。
- [ONTO](https://github.com/ontio/onto) - 主仓库

### <a name="Ontology-ddxf"></a>本体分布式数据交易框架 <sup>[top⇈](#本体基础架构体系)</sup>
> 分布式数据交易框架，支持业务伙伴定制各类数据交易市场应用，保证数据和资金安全。
- [本体分布式数据交易框架](https://github.com/ontio/ontology-ddxf) - 主仓库