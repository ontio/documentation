---
title: 
keywords: sample homepage
sidebar: Dapp_zh
permalink: smart_contract_tutorial_introduction_zh.html
folder: doc_zh/Dapp
---


[English](./smart_contract_tutorial_introduction_en.html) / 中文

<h1 align="center">本体智能合约简介</h1>
<p align="center" class="version">Version 1.0.0 </p>

## 什么是智能合约?

智能合约是一套以数字形式定义的承诺，包括合约参与方可以在上面执行这些承诺的协议。区块链技术给我们带来了一个去中心化的，不可篡改的，高可靠性的系统，在这种环境下，智能合约才大有用武之地。智能合约是区块链最重要的特性之一，也是区块链能够被称为颠覆性技术的主要原因。

![smart contract.png](https://upload-images.jianshu.io/upload_images/150344-1fc2cde39ab0e8cb.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

## 本体智能合约有哪些特点？

本体智能合约具有确定性、高性能、扩展性的特性，包括两大模块：交互服务和虚拟机。交互服务提供了虚拟机和区块链账本之间的交互。虚拟机提供了智能合约的运行环境。

交互服务包括原生服务，Neo虚拟机服务，和Wasm虚拟机服务。原生服务提供了基础链上特殊智能合约的实现，这种合约能被快速方便地使用。Neo虚拟机服务提供了外部访问Neo虚拟机的API, 它能增强智能合约的调用功能。Wasm虚拟机服务提供了访问外部虚拟机的Wasm虚拟机的API。

虚拟机包括Neo虚拟机和Wasm虚拟机。Neo虚拟机是一种轻量级的虚拟机，已被证明在公链上运行良好。Wasm虚拟机是一种高效能的通用虚拟机。

本体智能合约支持了Native智能合约、NeoVm智能合约、WASM智能合约等多种合约类型，目前，Smartx支持基于NeoVM的C＃和Python两种语言，未来还会支持WASM在线编译功能及更多主流开发语言，包括Java、Rust、Go、JavaScript等。

关于智能合约更多信息请参考[智能合约总体介绍](https://ontio.github.io/documentation/smart_contract_tutorial_overview_zh.html)

## 用什么语言编写智能合约？

当前支持的语言有：

C#, Python

我们计划支持的语言有：

JavaScript, Go, C, C++, Java
