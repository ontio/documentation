# Get Started

本体是新一代高性能公有式区块链，在主网上线之后，已经有非常多的开发者加入了本体技术社区。文档是开发者加入本体生态的入口，完善的文档体系能大大提高
开发者的开发效率，通过文档，开发者们将对本体生态、本体技术有清晰的认识。本篇文档是本体文档中心的概览，将会大致介绍文档中心的各个组成本分，这将为
开发者提供一个快速熟悉本体技术、本体生态的方法。

* [本体](#本体)
     * [什么是本体？](#什么是本体)
     * [如何获取本体？](#如何获取本体)
     * [本体节点介绍](#本体节点介绍)
        * [同步节点](#同步节点)
        * [共识节点](#共识节点)
     * [本体的共识机制](#本体的共识机制)
     * [本体网络搭建](#本体网络搭建)
     * [本体的特殊功能](#本体的特殊功能)
        * [本体DID](#本体did)
        * [分布式数据交易](#分布式数据交易)
* [如何与本体交互](#如何与本体交互)
     * [本体命令行工具](#本体命令行工具)
     * [本体签名机](#本体签名机)
     * [本体的API](#本体的api)
     * [本体的SDK](#本体的sdk)
* [本体智能合约](#本体智能合约)
     * [本体智能合约IDE——Smartx](#本体智能合约idesmartx)
     * [如何编写智能合约](#如何编写智能合约)
     * [合约的部署与调用](#合约的部署与调用)
     * [智能合约的权限管理](#智能合约的权限管理)
  
## 本体

### 什么是本体？

本体的特性在[这里](https://ontio.github.io/documentation/ontology_features_zh.html)有大致的介绍。同时，
又以[公开信](https://ontio.github.io/documentation/first_open_letter_zh.html)的形式，介绍了本体的各个组成部分，并且对广大技术人员发出了邀请，希望大家
能积极加入本体技术社区，共建本体开发者生态。
  
### 如何获取本体？

目前本体的所有源码均在GitHub上开源，用户可以自行前往[代码库](https://github.com/ontio/ontology)中下载源码编译安装，也可以直接获取稳定的
[release版本](https://github.com/ontio/ontology/releases)。具体的获取、安装方法可以参考[这里](https://ontio.github.io/documentation/ontology_install_zh.html)。
  
### 本体节点介绍

获取了本体之后，可以在本地启动本体程序，连接到本体网络。但是在这之前，需要先了解一下目前本体网络中的节点类型，

本体的网络节点目前分为两类：共识节点与同步节点。
  
共识节点参与共识，打包交易并产生区块；

同步节点同步最新的区块信息，不参与共识。
  
#### 同步节点

同步节点可以连接到主网，也可以连接到本体的公共测试网，甚至可以连接到自己搭建的私网上。连接到不同的网络时，节点将会同步不同的信息，并且将在当前目录下
建立两个文件夹：Chain和Log。Chain中将存放同步下来的区块数据，包括所有的交易数据，账户数据等；Log将存放同步数据时产生的Log信息。
   
#### 共识节点

共识节点与同步节点类似，可以运行在主网、测试网与私网中。运行过程中，也将生成Chain和Log文件夹。不同的是，共识节点自己会打包交易信息产生区块，这一点是
同步节点所不能做的。

### 本体的共识机制

了解完本体网络节点类型之后，将介绍本体网络的共识机制。本体已支持DBFT与VBFT共识，目前主网与测试网均使用VBFT共识，
[这里](https://ontio.github.io/documentation/vbft_intro_zh.html)有VBFT共识网络的介绍，更详细的信息请参照本体的源码库。

### 本体网络搭建

现在，可以试着搭建本体网络了。[这篇文档](https://ontio.github.io/documentation/ontology_testnet_zh.html)将详细介绍同步节点如何启动以及如何搭建自己的
本体私网。

### 本体的特殊功能

#### 本体DID

Ontology DID（简称：ONT ID）基于W3C的DID规范，是一个去中心化的身份标识协议。具体的介绍可参看[这篇文档](https://ontio.github.io/documentation/ontology_DID_zh.html)。

#### 分布式数据交易

针对目前中心化数据交易所的痛点如：数据缓存、隐私数据未经用户授权、数据版权无法保护等问题，本体提出分布式数据管理协议ONT DATA，并基于此协议推出去中心化数
据交易框架DDXF。更详细的内容可以参考[这篇文档](https://ontio.github.io/documentation/DDXF_zh.html)。

## 如何与本体交互
   
### 本体命令行工具

在搭建本体网络，并启动的时候，你可能使用很多命令行参数。这些参数在[这里](https://ontio.github.io/documentation/ontology_cli_sample_zh.html)有详细的说
明。这些命令行参数也是通过ontology可执行程序来执行，统称为ontology CLI工具。CLI可以执行、调用本体网络的大部分功能，是本体网络的第一个入口。除了文档之
外，还能通过执行`./ontology --help`获取命令行参数的简略信息。
  
### 本体签名机

为了适应更多的需求，本体提供了一种叫做签名机的服务。该服务使用指定的钱包，对发送到该服务的交易进行签名。详情可以参考[这篇文档](https://ontio.github.io/documentation/sigsvr_zh.html)。

### 本体的API

在命令行之外，本体提供了一套更方便的区块链交互接口。这些接口以API的形式提供，目前本体的API包含三类：[本体RPC API](https://ontio.github.io/documentation/ontrpcapi_zh.html)，
[本体Restful API](https://ontio.github.io/documentation/restfulapi_zh.html)，[本体Websocket API](https://ontio.github.io/documentation/websocket_zh.html)。
通过使用API，开发者可以十分便捷的向本体网络发送交易、查询数据。

### 本体的SDK

对于开发者而言，SDK是直接在程序中调用工具。目前，本体提供了三套SDK供开发者使用，分别是[Java SDK](https://ontio.github.io/documentation/ontology_java_sdk_zh.html)，
[Typescript SDK](https://ontio.github.io/documentation/ontology_ts_sdk_zh.html)与[Golang SDK](https://github.com/ontio/ontology-go-sdk)。在使用SDK之前，
建议先阅读SDK的[总体说明](https://ontio.github.io/documentation/overview_of_sdks_zh.html)和本体的[钱包文件规范](https://ontio.github.io/documentation/ontology_wallet_file_specification_zh.html)。
   
## 本体智能合约
   
智能合约是当前区块链最重要的功能，本体也有自己的智能合约体系，详情请参考[这里](https://ontio.github.io/documentation/smart_contract_tutorial_introduction_zh.html)。
   
### 本体智能合约IDE——Smartx

Smartx是本体推出的一站式智能合约编写工具，集成了编写、编译、部署与调试等功能，极大地提升了智能合约的开发效率。Smartx的使用方法请参考[这篇文档](https://ontio.github.io/documentation/smart_contract_tutorial_smartx_zh.html)。
   
### 如何编写智能合约

这里以[Hello World](https://ontio.github.io/documentation/smart_contract_tutorial_helloworld_zh.html)为例给出了一个简单的智能合约的例子。在编写智能合约的过程中，
会用到许多智能合约API，这些API在[这里]()给出。
   
### 合约的部署与调用

虽然smartx提供了一键式部署调用方法，但是仍有其他方法可以实现合约的部署和调用。部署方法可以参考[这篇文档](https://ontio.github.io/documentation/smart_contract_tutorial_deployment_zh.html)，
调用方法可以参考[这篇文档](https://ontio.github.io/documentation/smart_contract_tutorial_invocation_zh.html)。
   
### 智能合约的权限管理

当前，智能合约的函数可以被任何人调用，这显然不符合现实要求。基于角色的权限管理的基本思想是，每个角色可以调用部分函数，每个实体可以被赋予多种角色（实体是由其ONT ID
来标识）。[这篇文档](https://ontio.github.io/documentation/smart_contract_tutorial_auth_zh.html)详细介绍了本体智能合约的权限管理方式。