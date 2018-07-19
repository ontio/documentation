---
title:
keywords: sample homepage
sidebar: Dapp_zh
permalink: Introduction_of_Ontology_Smart_Contract_zh.html
folder: doc_zh/Dapp
giturl: https://github.com/ontio/ontology-smartcontract/master/smart-contract-tutorial/Introduction_of_Ontology_Smart_Contract_cn.md
---

<h1 align="center">本体智能合约简介</h1>
<p align="center" class="version">Version 1.0.0 </p>

[English](./Introduction_of_Ontology_Smart_Contract_en.html) / 中文

## 什么是智能合约?

智能合约是1994年由尼克萨博首次提出的理念，是一种旨在以信息化方式传播、验证或执行合约的计算机协议。智能合约允许在没有第三方的情况下进行可信交易。这些交易可追踪且不可逆。

区块链技术给我们带来了一个去中心化的，不可篡改的，高可靠性的系统，在这种环境下，智能合约才大有用武之地。智能合约是区块链最重要的特性之一，也是区块链能够被称为颠覆性技术的主要原因。

## 本体智能合约有哪些特点？

Ontology智能合约是一个多功能、轻量级、高可用、可并发、多语言、跨合约、跨虚拟机等集于一体的完备体系。Ontology智能合约支持丰富的智能合约开发语言，开发者不需要学习新的合约开发语言，即可很方便的开发Ontology智能合约，现支持的语言种类包含：C#, Python等，同时，在不远的将来我们将会支持更多类型的主流开发语言，包括：Java, C++, Rust, Go, and JavaScript等。

本体智能合约具有确定性、高性能、扩展性的特性，包括两大模块：交互服务和虚拟机。交互服务提供了虚拟机和区块链账本之间的交互。虚拟机提供了智能合约的运行环境。交互服务包括原生服务和Neo虚拟机服务。原生服务提供了基础链上特殊智能合约的实现，这种合约能被快速方便地使用。Neo虚拟机服务提供了外部访问Neo虚拟机的API, 它能增强智能合约的调用功能。

![ontology smart contract architecture.png](./lib/images/smartcontract_architecture.png)


## 合约类型

Ontology智能合约现包含2种类型的合约：Native合约和NeoVm合约。Native合约是在Ontology底层直接编写的合约，不需要像部署普通合约那样编写合约代码，具有很高的执行效率，是对普通合约的极大优化，通用的服务包括：Oracle，DID，权限管理，数据交易所都将采用Native合约实现。NeoVm合约是采用NeoVm虚拟机运行的合约，需要编写相应的合约代码，现支持的语言包含：Java，C#，Python，NeoVm本身具有轻量级、可扩展、高性能的特性，通过结合Interop Service层能很好的打通虚拟机与账本层间的交互。

![ontology smart contract type.png](./lib/images/smartcontract_type.png)


## 合约调度

虚拟机类型

```
// Prefix of address
type VmType byte

const (
Native = VmType(0xFF)
NEOVM  = VmType(0x80)
WASMVM = VmType(0x90)
)

```

合约结构体

```
type VmCode struct {
VmType VmType
Code   []byte
}

```

调用transaction payload

```
// InvokeCode is an implementation of transaction payload for invoke smartcontract
type InvokeCode struct {
GasLimit common.Fixed64
Code     stypes.VmCode
}

```

Ontology智能合约运行需要传入合约运行所需要的脚本，以及需要运行合约的虚拟机类型，智能合约调度中心会更根据虚拟机类型，启动不同的虚拟机运行合约，当执行过程中，合约调用了AppCall指令(其中包含了运行合约的必要参数)，触发智能合约调度中心，调度中心将会根据传入的参数启动对应的虚拟机运行对应的脚本，直到合约运行完成为止。

![process](http://upload-images.jianshu.io/upload_images/150344-ac402b1c8eb3aa9a.jpeg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)




