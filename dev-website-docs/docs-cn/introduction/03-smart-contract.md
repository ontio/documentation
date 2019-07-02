
## 简介

本体智能合约是一个集多功能、轻量级、高可用、可并发、多语言、跨合约、跨虚拟机等于一体的完备体系。本体智能合约支持多种主流开发语言，如 C#, Python 等，开发者不需要学习新的语言即可很方便的开发本体智能合约，未来将支持更多主流开发语言，包括：Java, C++, Rust, Go, JavaScript 等。

本体智能合约具有确定性、高性能、扩展性的特性，包括两大模块：交互服务和虚拟机。交互服务提供了虚拟机和区块链账本之间的交互。虚拟机提供了智能合约的运行环境。交互服务包括原生服务和 NEO 虚拟机服务。原生服务提供了基础链上特殊智能合约的实现，这种合约能被快速方便地使用。NEO 虚拟机服务提供了外部访问 NEO 虚拟机的 API, 它能增强智能合约的调用功能。

![ontology smart contract architecture.png](https://raw.githubusercontent.com/ontio/ontology-smartcontract/master/smart-contract-tutorial/images/smartcontract_architecture.png)

### 合约类型

本体智能合约有两种类型：Native 合约和 NeoVm 合约。Native 合约是在本体底层直接编写的合约，不需要像部署普通合约那样编写合约代码，具有很高的执行效率，是对普通合约的极大优化，通用的服务包括：Oracle，DID 和权限管理，数据交易所都将采用 Native 合约实现。NeoVm 合约是采用 NeoVm 虚拟机运行的合约，需要编写相应的合约代码，现支持的语言包含：Java，C#，Python，NeoVm 本身具有轻量级、可扩展、高性能的特性，通过结合 Interop Service 层能很好的打通虚拟机与账本层间的交互。

![ontology smart contract type.png](https://raw.githubusercontent.com/ontio/ontology-smartcontract/master/smart-contract-tutorial/images/smartcontract_type.png)

### 合约调度

- 虚拟机类型

```go
type VmType byte

const (
   Native = VmType(0xFF)
   NEOVM  = VmType(0x80)
   WASMVM = VmType(0x90)
)
```

- 合约结构体

```go
type VmCode struct {
   VmType VmType
   Code   []byte
}
```

- 调用智能合约

```go
type InvokeCode struct {
   GasLimit common.Fixed64
   Code     stypes.VmCode
}
```

本体智能合约运行需要传入合约运行所需要的脚本，以及运行合约的虚拟机类型，智能合约调度中心会更根据虚拟机类型，启动不同的虚拟机运行合约。当执行过程中，合约调用了 AppCall 指令(其中包含了运行合约的必要参数)，触发智能合约调度中心，调度中心将会根据传入的参数启动对应的虚拟机运行对应的脚本，直到合约运行完成为止。

![process](http://upload-images.jianshu.io/upload_images/150344-ac402b1c8eb3aa9a.jpeg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

## 费用模型

### GAS 上限

Gas limit 是在执行智能合约的 opcode 过程中计步时使用，理论上智能合约越复杂，需要的 GAS limit 数量越高，Ontology 交易设定最低的 GAS limit 数量是 20000。

### GAS 价格

GAS price 是给执行 opcode 定价，GAS price 越高，共识节点会优先打包该笔交易。

### 交易费用

交易费用是 GAS limit 和 GAS price 的乘积，实际的交易费用分以下三种情形：

- 执行 opcode 步数等于 GAS limit

   Transaction Fee =  GAS Price * GAS limit

- 执行 opcode 步数大于 GAS limit

  Transaction Fee =  GAS Price * GAS limit

  交易失败，但 GAS 不会退还。

- 执行 opcode 步数小于 GAS limit
  Transaction Fee =  GAS Price * (opcode实际消耗)

  多余的 GAS 会退还，但最低消费是 20000。

<p class = "info"> 所有的 ONT, ONG 的转账 GAS limit 消费固定都是20000。</p>




