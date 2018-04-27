[English](README.md) | 中文

<h1 align="center">本体智能合约</h1>
<p align="center" class="version">Version V0.7.0 </p>

## 什么是智能合约?

智能合约是一套以数字形式定义的承诺，包括合约参与方可以在上面执行这些承诺的协议。区块链技术给我们带来了一个去中心化的，不可篡改的，高可靠性的系统，在这种环境下，智能合约才大有用武之地。智能合约是区块链最重要的特性之一，也是区块链能够被称为颠覆性技术的主要原因。
## 本体智能合约有哪些特点？

本体智能合约具有确定性、高性能、扩展性的特性，包括两大模块：交互服务和虚拟机。交互服务提供了虚拟机和区块链账本之间的交互。虚拟机提供了智能合约的运行环境。

交互服务包括原生服务，Neo虚拟机服务，和Wasm虚拟机服务。原生服务提供了基础链上特殊智能合约的实现，这种合约能被快速方便地使用。Neo虚拟机服务提供了外部访问Neo虚拟机的API, 它能增强智能合约的调用功能。Wasm虚拟机服务提供了访问外部虚拟机的Wasm虚拟机的API。

虚拟机包括Neo虚拟机和Wasm虚拟机。Neo虚拟机是一种轻量级的虚拟机，已被证明在公链上运行良好。Wasm虚拟机是一种高效能的通用虚拟机。

本体智能合约也支持在不同的虚拟机上调用合约。开发者可以通过本体智能合约方便地构建项目。

## 用什么语言编写智能合约？

当前支持的语言有：

C#, VB.Net, F#

Java, Kotlin

Python

C, C++

我们计划支持的语言有：

Rust

Golang

JavaScript

## 如何开发智能合约？


我们已经开发了一个在线工具[Smartx](http://smartx.ont.io)，来帮助应用开发者。

SmartX是一个可用于编译，部署和调用智能合约的一站式IDE。它提供了丰富的智能合约模板以及强大的在线编辑器。基于SmartX这个工具，智能合约的需求方可以参考和使用模板合约，或者委托社区开发人员定制开发所需的合约。未来，智能合约的开发人员可以交易自己编写的智能合约，或者协作多人开发智能合约，利用自己的专业知识获得收益。

本体智能合约支持了Native智能合约、NeoVm智能合约、WASM智能合约等多种合约类型，目前，Smartx支持基于NeoVM的C＃和Python两种语言，未来还会支持WASM在线编译功能及更多主流开发语言，包括Java、Rust、Go、JavaScript等。

下一步，我们将像类似GitHub等分布式软件项目代码托管平台一样，支持多人共同参与、分享一份复杂的合约；并同时实施一套的经济激励措施，融入公正的治理政策，反映每一个参与者的贡献，使智能合约编写、智能合约交易、协作、社区建设等相结合，形成一个良好的智能合约开发生态。


下面介绍了使用Smartx来创建智能合约的主要流程。



### 第一步 - 编写&编译智能合约  

目前，我们支持运行于**NEO虚拟机**和**WASM虚拟机**的智能合约。

* **对于NEO虚拟机**，我们提供了[Smartx](http://smartx.ont.io)来帮助你编写和编译智能合约。
* **对于WASM虚拟机**, 请查阅 [>>WASM智能合约](README_wasm.md)文档。

首先你需要创建一个项目并选择你喜欢的语言，开始编写智能合约。

![Select language](https://s1.ax1x.com/2018/03/24/9bxJYR.png)

然后进入项目编辑页面。

中间主要部分是合约的编辑器。

右侧是操作面板。

中间下部打印操作的输出结果。

![Compile contract](https://s1.ax1x.com/2018/04/04/CpIdpR.png)

#### 编写智能合约
接下里你可以开始编写你的智能合约。我们提供众多实用的模板供你参考。

[>>> 更多具体实例](https://github.com/ontio/documentation/tree/master/smart-contract-tutorial/examples) 

#### 编译智能合约
在你完成编写合约之后，你可以点击操作面板上的**编译**按钮，编译你的合约。

如果你的合约语法正确，将会被编译出相应的ABI文件和AVM文件，并展示在右侧。


### 第二步 - 部署合约
接下来，你可以将合约部署到区块链上。当选择的网络是测试网时，这一步不需要消耗gas。点击**部署**按钮来部署合约。部署的结果将会打印在输出框里。你可以拷贝结果里的交易hash到本体的[区块链浏览器](https://explorer.ont.io)上，进一步确认部署是否成功。

除了Smartx外，你还可以使用本体的SDK来部署合约。更多信息请查阅相关文档。


[>> Java SDK](https://ontio.github.io/documentation/ontology_java_sdk_smartcontract_zh.html)

[>> TS SDK](https://ontio.github.io/documentation/ontology_ts_sdk_smartcontract_zh.html)

![Deploy contract](https://s1.ax1x.com/2018/04/04/CpIcAe.png)


### 第三步 - 调用智能合约
最后，你可以运行合约中的方法。你可以选择想要运行的方法，输入正确的参数值，点击**运行**按钮，调用智能合约。调用的结果将会打印在输出框里。


![Invoke smart contract](https://s1.ax1x.com/2018/04/04/CpoCEF.png)

除了Smartx，你还可以使用本体的SDK来调用智能合约。更多信息请查阅相关文档。

[>> Java SDK](https://ontio.github.io/documentation/ontology_java_sdk_smartcontract_zh.html)

[>> TS SDK](https://ontio.github.io/documentation/ontology_ts_sdk_smartcontract_zh.html)








