---
title: 
keywords: sample homepage
sidebar: ont_doc_zh
permalink: verification_provider_specification_zh.html
folder: doc_zh
---


[English](./verification_provider_specification_en.html) / 中文


<h1 align="center">信任锚接入标准 </h1>
<p align="center" class="version">Version 0.7.0 </p>

## 概述

信任锚Trust Anchor是指在本体生态上提供认证服务的合作方，其可能是政府机关、大学、银行、第三方认证服务机构（比如CA机构）、生物识别科技公司等等，这些企业为本体ONT ID的持有者（Owner）提供多维度的认证，并第一时间通过Ontology BlockChain来记录认证行为和认证结果HASH，从而为用户认证需求方/场景方提供了标准化、可信的认证方式。

## 交互流程说明

根据情况，有两个具体的交互流程。

* 在线申请-自动签发模式

    该模式指，用户可以通过客户端（如：本体官方ONTO客户端）发起，实时认证，认证通过后立即获取到可信声明Verified Claim。比如Face++是按照如下流程。

    ![信任锚](lib/images/5a92d69de4b0874437cfe5f3.png)


* 线下签发模式
    该模式指，信任锚通过线下或者其他渠道，为用户进行认证，并签发可信申明的一种模式。

## 主要服务条款

* 信任锚如果没有相应资质或用户许可，不可留存任何用户数据。
* 信任锚在其官方网站上公布将作为本体的身份识别、认证服务提供者（Verify Provider），并指定其注册的OntID。
* 信任锚应保证其用户信息准确性与真实性。本体团队对信任锚提交的用户信息的真实性不承担责任。因用户信息虚假、不完整，而导致有关法律文件的效力瑕疵，本体团队不承担责任，有关责任由信任锚自行向其用户或第三人承担。
* 信任锚具备身份识别、认证管理配置能力，原则性要求如下，指标性要求可以由甲方根据具体服务要求来具体指定。
* 具有身份识别、认证需要的硬件和网络设施；
* 具有一定的安全防护标准；
* 部署身份识别、认证管理软件，本体将开源标准软件代码；
* 基于身份识别、认证的管理流程，信任锚将提供包括不限于以下的可信申明服务：1、可信申明的颁发；2、可信申明的吊销；3、以其官方域名URL对外开放可信申明验证服务。

## 接入步骤


* **注册ONT ID**

    需要首先注册ONT ID，我们建议通过官方SDK进行注册。

    [ont-java-sdk](https://github.com/ontio/ontology-java-sdk) - 使用创建数字身份接口.

* **集成可信声明管理功能**

    实现标准可信申明的签发和管理。支持功能包括：签发、吊销、验证、查询、发布可信声明模板。
    
    我们提供了快速集成这些功能的组件。

* **定制化开发**

    Step1 结合现有身份验证方式，定制化A1，并开放给客户端；

    Step2 使用SDK实现A2接口，用于验证用户ONT ID身份；
    [ont-java-sdk](https://github.com/ontio/ontology-java-sdk) - 验证用户签名接口.

    Step3 需要根据您的业务情况，设定可信申明模板；
    
    Step4 通过CWC来使用接口（A3），如上图A3接口将帮助Verication Provider实现签发、发送至可信存储和登记区块链。

    > Note：请以其官方域名URL对外开放可信申明验证API接口。

    典型的可信申明例子如下：
```
 {
        "Context":"claim:linkedin_authentication",
        "Id":"6KJKbctyin962nfdfvdf",
        "Content":{
            "Id": "yL5FdXB-um",
            "Name": "lifeng",
            "FirstName": "feng",
            "LastName": "li",
            "Bio": "Blockchain App Developer",
            "Avatar": "https://media.licdn.com/mpr/mprx/0_-HOmp1u9zNCxbF3iKoYjplm9clNP53AiyuoAplgLHN8Cs56_YaaCtAdIJ0qS66rf1IpK19_gajZa",
            "HomePage": "https://www.linkedin.com/in/%E4%BA%9A%E5%B3%B0-%E6%9D%8E-b56b8b79"
        },
        "Metadata":{
            "CreateTime":"2017-01-01T22:01:20Z",
            "Issuer":"did:ont:4XirzuHiNnTrwfjCMtBEJ6",
            "IssuerName":"onchain",
            "Subject":"did:ont:8uQhQMGzWxR8vw5P3UWH1j"
        },
        "Signature":{
            "Format":"pgp",
            "Algorithm":"ECDSAwithSHA256",
            "Value": ""
        }
    }     
```



## 奖励或分润机制

* 用户只要完成认证后，参与的认证服务商将得到奖励，具体政策将在本体《治理白皮书》发布。

* 用户使用可信申明进行身份认证，参与的认证服务商将得到分润或奖励，这个部分由各个去中心化数据交易所同本体共同制定政策。