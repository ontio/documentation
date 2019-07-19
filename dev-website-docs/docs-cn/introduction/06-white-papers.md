
### 白皮书
- 白皮书概览
    - [英语](https://ont.io/wp/Ontology-Introductory-White-Paper-EN.pdf) 
    - [中文](https://ont.io/wp/Ontology-Introductory-White-Paper-ZH.pdf)
    - [韩语](https://ont.io/wp/Ontology-Introductory-White-Paper-KR.pdf) translated by @Sunghwan Kim
    - [荷兰语](https://github.com/ontio/documentation/blob/master/nl-NL/Introductory%20White%20Paper%20-%20Dutch%20V1.pdf) translated by @Mark Westerweel
    - [日语](https://github.com/ontio/documentation/blob/master/jp_JP/Ontology%20Introductory%20White%20Paper%20JP.pdf) translated by @Miho Nakauchi
    - [西班牙语](https://github.com/ontio/documentation/blob/master/es-ES/Introductory%20White%20Paper%20-%20Spanish.pdf) translated by @Alejandro Garcia
    - [土耳其语](https://github.com/ontio/documentation/blob/master/tr_TR/Introductory%20White%20Paper%20-%20Turkish.pdf) translated by @Hakan
- 技术白皮书
    - [英语](https://github.com/ontio/Documentation/blob/master/Ontology-technology-white-paper-EN.pdf)
    - [中文](https://ont.io/wp/Ontology-technology-white-paper-ZH.pdf)
    - [韩语](https://ont.io/wp/Ontology-technology-white-paper-KR.pdf) translated by @Sunghwan Kim
    - [荷兰语](https://github.com/ontio/documentation/blob/master/nl-NL/Technology%20White%20Paper%20-%20Dutch%20V1.pdf) translated by @Mark Westerweel
    - [日语](https://github.com/ontio/documentation/blob/master/jp_JP/Ontology%20Technology%20White%20Paper%20JP.pdf) translated by @Miho Nakauchi
- 生态白皮书
    - [英语](https://ont.io/wp/Ontology-Ecosystem-White-Paper-EN.pdf)
    - [中文](https://ont.io/wp/Ontology-Ecosystem-White-Paper-ZH.pdf)
    - [韩语](https://ont.io/wp/Ontology-Ecosystem-White-Paper-KR.pdf) translated by @Sunghwan Kim
    - [荷兰语](https://github.com/ontio/documentation/blob/master/nl-NL/Ecosystem%20White%20Paper%20-%20Dutch%20V1.pdf) translated by @Mark Westerweel
    - [日语](https://github.com/ontio/documentation/blob/master/jp_JP/Ontology%20Ecosystem%20White%20Paper-JP.pdf) translated by @Miho Nakauchi
- 框架白皮书
    - [英语](https://ont.io/wp/Ontology-Framework-White-Paper-EN-2.0.0.pdf)
    - [中文](https://ont.io/wp/Ontology-Framework-White-Paper-CH-2.0.0.pdf)
- 基础设施白皮书
    - [英语](https://ont.io/wp/Ontology-Infrastructure-White-Paper-EN-2.0.0.pdf)
    - [中文](https://ont.io/wp/Ontology-Infrastructure-White-Paper-CH-2.0.0.pdf)
- 信任框架白皮书
    - [英语](https://ont.io/wp/Ontology-Trust-Framework-White-Paper-EN-2.0.0.pdf)
    - [中文](https://ont.io/wp/Ontology-Trust-Framework-White-Paper-CH-2.0.0.pdf)

- [OEPs](https://github.com/ontio/OEPs)

## 1. 基础架构体系

- 本体 - [主仓库](https://github.com/ontio/ontology)

  本体致力于创建一个组件化、可自由配置、跨链支持、高性能、横向可扩展的区块链底层基础设施。 让部署及调用去中心化应用变得非常简单。

- 本体 WASM - [主仓库](https://github.com/ontio/ontology-wasm)

  本体 `WASM` 是本体区块链项目执行 `WASM` 智能合约的虚拟机，也可以独立运行于其他的环境。

- 本体 Crypto - [主仓库](https://github.com/ontio/ontology-crypto)

  本体网络加密库。

- 本体 Eventbus - [主仓库](https://github.com/ontio/ontology-eventbus)

  本体 `Eventbus` 是基于 `actor` 模型的消息中间件，提供高性能的模块间或节点间通信功能。

- 本体 RPC 、 Restful 和 WebSocket - [主仓库](https://github.com/ontio/documentation/tree/master/ontology-API)

  本体 `RPC API` 、 `Restful API` 和 `WebSocket API` 。

- 本体预言机 - [主仓库](https://github.com/ontio/ontology-oracle-py)

  预言机是现实世界与区块链数据交互的入口。

- 本体 FPGA - [主仓库](https://github.com/ontio/ontology-fpga)

  高速数字签名验证的 `FPGA` 设计与实现。

## 2. 协议体系及 SDK

- 本体 DID - [主仓库](https://github.com/ontio/ontology-DID)

  去中心化身份标识协议，实现现实世界中的人财物事在链上的标识、认证和确权。

- 本体 Java SDK - [主仓库](https://github.com/ontio/ontology-java-sdk)

  该项目是本体官方的 `Java SDK` ，它是一个综合性 `SDK` ，目前支持：本地钱包管理、数字身份管理、数字资产管理、智能合约部署和调用、与节点通信等。

- 本体 TS SDK - [主仓库](https://github.com/ontio/ontology-ts-sdk)

  该项目是本体官方 `Typescript SDK` ，目前支持：本地钱包管理、数字身份管理、数字资产管理、智能合约部署和调用以及资产转账等。

- 本体 Python SDK - [主仓库](https://github.com/ontio/ontology-python-sdk)

  该项目是本体官方 `Python SDK` ，目前支持： `RPC` 接口、本地钱包管理、数字身份管理、数字资产管理、资产转账等。

## 3. 应用

- ONTO - [主仓库](https://github.com/ontio/onto)

  ONTO 是基于本体的综合客户端产品，是本体信任搜索引擎和区块链体系的入口。 

  `ONTO`  将帮助用户实现包括数字身份管理、数字资产管理、分布式数据交换等综合性功能。 

  `ONTO` 将数字身份与现实身份进行映射关联，用户可以利用这款产品建立自己的数字身份和多维的身份画像，通过密码学算法实现隐私保护。

  `ONTO` 可以安全可靠地管理数字资产，并将其应用到各种场景中。同时，`ONTO` 通过授权体系和加密算法建立一个对用户来说可靠的、可掌控的数据交易体系。未来，基于`ONTO` 的数字身份和数字资产，将进一步支持各类社交场景和协作需求。

- 本体分布式数据交易框架 - [主仓库](https://github.com/ontio/ontology-ddxf)

  分布式数据交易框架，支持业务伙伴定制各类数据交易市场应用，保证数据和资金安全。
