---
title: 
keywords: sample homepage
sidebar: ont_doc_zh
permalink: smart_contract_tutorial_overview_zh.html
folder: doc_zh
---


[English](./smart_contract_tutorial_overview_en.html) / 中文


<h1 align="center">智能合约总体介绍 </h1>
<p align="center" class="version">Version 0.7.0 </p>

## 1. 简介
智能合约是1994年由尼克萨博首次提出的理念，是一种旨在以信息化方式传播、验证或执行合约的计算机协议。智能合允许在没有第三方的情况下进行可信交易。这些交易可追踪且不可逆。Ontology智能合约是一个多功能、轻量级、高可用、可并发、多语言、跨合约、跨虚拟机等集于一体的完备体系。Ontology智能合约支持多种智能合约类型，包含：Native智能合约、NeoVm智能合约、Wasm智能合约。Ontology智能合约支持丰富的智能合约开发语言，开发者不需要学习新的合约开发语言，即可很方便的开发Ontology智能合约，现支持的语言种类包含：Java, C#, Python, C, C++, Kotlin等，同时，在不远的将来我们将会支持更多类型的主流开发语言，包括：Rust, Go, JavaScript等。

![image](./lib/images/architecture.jpeg)
## 2. 合约类型
Ontology智能合约现包含3种类型的合约：Native合约、NeoVm合约、WasmVm合约。Native合约是在Ontology底层直接编写的合约，不需要像部署普通合约那样编写合约代码，具有很高的执行效率，是对普通合约的极大优化，通用的服务包括：Oracle，DID，权限管理，数据交易所都将采用Native合约实现。NeoVm合约是采用NeoVm虚拟机运行的合约，需要编写相应的合约代码，现支持的语言包含：Java，C#，Python，NeoVm本身具有轻量级、可扩展、高性能的特性，通过结合Interop Service层能很好的打通虚拟机与账本层间的交互。WasmVm合约是采用Wasm虚拟机运行的合约，需要编写相应的合约代码，现支持的语言包含：C，C++，Wasm本身具有良好的编译器支持，同时，Wasm虚拟机具有轻量级、高性能的特性。
![image](./lib/images/type.jpeg)
## 3. 合约调度
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

![image](./lib/images/invoke.jpeg)