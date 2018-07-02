---
title: 
keywords: sample homepage
sidebar: ont_doc_zh
permalink: smart_contract_tutorial_smartx_zh.html
folder: doc_zh
---


[English](./smart_contract_tutorial_smartx_en.html) / 中文

<h1 align="center">SmartX 教程</h1>
<p align="center" class="version">Version 1.0.0 </p>

## 什么是 SmartX

SmartX是一个可用于编译，部署和调用智能合约的一站式IDE。它提供了丰富的智能合约模板以及强大的在线编辑器。基于SmartX这个工具，智能合约的需求方可以参考和使用模板合约，或者委托社区开发人员定制开发所需的合约。未来，智能合约的开发人员可以交易自己编写的智能合约，或者协作多人开发智能合约，利用自己的专业知识获得收益。

下一步，我们将像类似GitHub等分布式软件项目代码托管平台一样，支持多人共同参与、分享一份复杂的合约；并同时实施一套的经济激励措施，融入公正的治理政策，反映每一个参与者的贡献，使智能合约编写、智能合约交易、协作、社区建设等相结合，形成一个良好的智能合约开发生态。

## 注册

[SmartX 网站](http://smartx.ont.io/#/)

首先，您需要创建ONT ID管理您的智能合约项目。请在主页点击“注册”按钮注册您的账户，如下图所示。

![注册](https://upload-images.jianshu.io/upload_images/150344-6beeb3324ef05ac9.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

在输入两次密码之后（密码长度至少大于6），点击“生成ONT ID”注册账号。您需要点击“下载”按钮下载ONT ID文件并备份私钥。ONT ID文件存储了您加密后的ONT ID和私钥，私钥是您唯一恢复ONT ID账户的凭证，请妥善保管。

![ONT ID 文件](https://upload-images.jianshu.io/upload_images/150344-a312b6edd22caf32.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![](https://upload-images.jianshu.io/upload_images/150344-5b2f2519b025cebe.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

如果您已经拥有了ONT ID，您可以点击“恢复 ONT ID”按钮来找回您的ONT ID. 在输入私钥和两遍密码之后，点击“恢复 ONT ID”按钮找回ONT ID。

![恢复](https://upload-images.jianshu.io/upload_images/150344-4bf4133ccb19f075.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

## 登录

在注册之后，您已经拥有了ONT ID文件，您仅需要选择这个文件并输入密码来登录您的账户，如下图所示。

![登录](https://upload-images.jianshu.io/upload_images/150344-e3848962a4dfe0d1.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

在登录之后，您将进入项目列表页面。您可以选择已存在的项目或者选择创新新项目。

![创建项目](https://upload-images.jianshu.io/upload_images/150344-17ec830db0f4d948.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

## 第一步 - 编写&编译智能合约 

* **对于NEO虚拟机**, 我们提供了[SmartX](http://smartx.ont.io) 来帮助您编写，编译，调用智能合约。

首先你需要创建一个项目并选择你喜欢的语言，开始编写智能合约。

![选择语言](https://upload-images.jianshu.io/upload_images/150344-de1bad190b1c6c66.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

然后进入项目编辑页面。中间主要部分是合约的编辑器。右侧是操作面板。中间下部打印操作的输出结果。

![编译](https://upload-images.jianshu.io/upload_images/150344-d100aa119363ec2c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 编写智能合约

接下里你可以开始编写你的智能合约。我们提供众多实用的模板供你参考。

[更多具体实例](https://github.com/ontio/documentation/tree/master/smart-contract-tutorial/examples) 

### 编译智能合约

在你完成编写合约之后，你可以点击操作面板上的编译按钮，编译你的合约。

如果你的合约语法正确，将会被编译出相应的ABI文件和AVM文件，并展示在操作面板上。


## 第二步 - 部署智能合约

接下来，你可以将合约部署到区块链上。当选择的网络是测试网时，这一步不需要消耗gas。点击部署按钮来部署合约。部署的结果将会打印在输出框里。你可以拷贝结果里的交易hash到本体的[区块链浏览器](https://explorer.ont.io/)上，进一步确认部署是否成功。

除了SmartX外，你还可以使用本体的SDK来部署合约。更多信息请查阅相关文档。

[>> Java SDK](https://ontio.github.io/documentation/ontology_java_sdk_smartcontract_en.html)

[>> TS SDK](https://ontio.github.io/documentation/ontology_ts_sdk_smartcontract_en.html)

![部署智能合约](https://upload-images.jianshu.io/upload_images/150344-d0160bc4a38a804d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


## 第三步 - 调用智能合约

最后，你可以运行合约中的方法。你可以选择想要运行的方法，输入正确的参数值，点击运行按钮，调用智能合约。调用的结果将会打印在输出框里。

![调用智能合约](https://upload-images.jianshu.io/upload_images/150344-5229fe6d34a67372.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

除了Smartx，你还可以使用本体的SDK来调用智能合约。更多信息请查阅相关文档。

[>> Java SDK](https://ontio.github.io/documentation/ontology_java_sdk_smartcontract_en.html)

[>> TS SDK](https://ontio.github.io/documentation/ontology_ts_sdk_smartcontract_en.html)

