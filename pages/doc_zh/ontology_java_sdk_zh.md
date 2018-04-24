---
title: 
keywords: sample homepage
sidebar: ont_doc_zh
permalink: ontology_java_sdk_zh.html
folder: doc_zh
---

[English](./ontology_java_sdk_en.html) / 中文

<h1 align="center"> Ontology Java SDK User Guide </h1>
<p align="center" class="version">Version 0.7.0 </p>

# 总体介绍

该项目是本体官方Java SDK，它是一个综合性SDK，目前支持：本地钱包管理、数字身份管理、数字资产管理、智能合约部署和调用、与节点通信等。未来还将支持更丰富的功能和应用。

## 主要功能


- [区块链节点基本操作](./ontology_java_sdk_blockchain_interop_zh.html)
- [钱包文件及规范](./ontology_wallet_file_specification_zh.html)
- [数字身份及可信声明管理](./ontology_java_sdk_identity_claim_zh.html)
- [数字资产](./ontology_java_sdk_asset_zh.html)
- [智能合约部署和调用](./ontology_java_sdk_smartcontract_zh.html)
- [错误码](./ontology_java_sdk_error_code_zh.html)


## 代码结构说明：

* acount：账号相关操作，如生成公私钥
* common：通用基础接口
* core：核心层，包括合约、交易、签名等
* crypto：加密相关，如ECC/SM
* io：io操作
* network：用restful或rpc接口与链通信
* sdk：对底层做封装、Info信息、通信管理、UTXO管理、钱包文件管理、异常类。
* ontsdk类：提供管理器和交易实例，管理器包括：walletMgr、connManager。walletMgr钱包管理器主要管理数字身份及数字资产账户，用户向链上发送交易需要私钥做签名。 connManager与链上通信管理。任何发送交易和查询都需要通过连接管理器。

## 安装说明

### 请配置JDK 8的开发环境

> **注意:**  SDK用的key的长度超过128位，由于java的安全策略文件对key的长度的限制，需要下载local_policy.jar和US_export_policy.jar这两个jar包，替换JRE库${java_home}/jre/lib/security目录下对应的jar包。

jar包下载地址：

>http://www.oracle.com/technetwork/java/javase/downloads/jce8-download-2133166.html


### Build

```
mvn clean install
```

### 预准备

* 启动Ontology节点，rpc端口已经打开，并且SDK可以连接RPC服务器来初始化。