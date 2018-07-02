---
title: 
keywords: sample homepage
sidebar: ont_doc_zh
permalink: smart_contract_tutorial_introduction_zh.html
folder: doc_zh
---


[English](./smart_contract_tutorial_introduction_en.html) / 中文

<h1 align="center">Introduction of Ontology Smart Contract</h1>
<p align="center" class="version">Version 1.0.0 </p>

## What is smart contract

A smart contract is a set of commitments that are defined in digital form, including the agreement on how contract participants shall fulfill these commitments. Blockchain technology gives us a decentralized, non-tamperable, highly reliable system in which smart contracts are extremely useful. Smart contracts are one of the most important features of blockchain technology and the reason why blockchains can be called a “disruptive” technology.

![smart contract.png](https://upload-images.jianshu.io/upload_images/150344-0bb1f898d948837e.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

## Features of Ontology smart contract

Ontology smart contract have certainty, high-performance, and expandable features. It includes two modules: Interactive Service and Virtual Machine. Interactive Service provides interaction between virtual machine and blockchain ledger. Virtual Machine provides smart contract execution environment.

Interactive Service includes native service, NeoVM service, and WasmVM service. Native service provides special smart contract implementation in the blockchain, which can be quickly and conveniently used. NeoVM service provides the API of NeoVM to communicate externally, which can enhance the invoke function of the smart contract. WasmVM service provides the API of WasmVM to communicate with the external virtual machine.

Virtual Machine includes NeoVM and WasmVM. NeoVM is a lightweight virtual machine, which has been proven to perform well on public chains. WasmVM is a high-performance and universal virtual machine.

Ontology smart contracts support multiple contract types such as native smart contracts, NeoVM smart contracts, Wasm smart contracts. Currently, SmartX supports NeoVM-based C# and Python, and will support Wasm online compilation and more mainstream programming languages such as Java, Rust, Go, and JavaScript.

## Write smart contracts in any language

The languages currently supported are: 

C#, Python

The languages that we plan to support include:

JavaScript, Go, C, C++, Java
