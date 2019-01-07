<h1 align="center">本体智能合约简介</h1>
<p align="center" class="version">Version 1.0.0 </p>


## 什么是智能合约?

智能合约是1994年由尼克萨博首次提出的理念，是一种旨在以信息化方式传播、验证或执行合约的计算机协议。智能合约允许在没有第三方的情况下进行可信交易。这些交易可追踪且不可逆。

区块链技术给我们带来了一个去中心化的，不可篡改的，高可靠性的系统，在这种环境下，智能合约才大有用武之地。智能合约是区块链最重要的特性之一，也是区块链能够被称为颠覆性技术的主要原因。

### 本体智能合约有哪些特点？

Ontology智能合约是一个多功能、轻量级、高可用、可并发、多语言、跨合约、跨虚拟机等集于一体的完备体系。Ontology智能合约支持丰富的智能合约开发语言，开发者不需要学习新的合约开发语言，即可很方便的开发Ontology智能合约，现支持的语言种类包含：C#, Python等，同时，在不远的将来我们将会支持更多类型的主流开发语言，包括：Java, C++, Rust, Go, and JavaScript等。

本体智能合约具有确定性、高性能、扩展性的特性，包括两大模块：交互服务和虚拟机。交互服务提供了虚拟机和区块链账本之间的交互。虚拟机提供了智能合约的运行环境。交互服务包括原生服务和Neo虚拟机服务。原生服务提供了基础链上特殊智能合约的实现，这种合约能被快速方便地使用。Neo虚拟机服务提供了外部访问Neo虚拟机的API, 它能增强智能合约的调用功能。

![ontology smart contract architecture.png](https://raw.githubusercontent.com/ontio/ontology-smartcontract/master/smart-contract-tutorial/images/smartcontract_architecture.png)
                                                

### 合约类型

Ontology智能合约现包含2种类型的合约：Native合约和NeoVm合约。Native合约是在Ontology底层直接编写的合约，不需要像部署普通合约那样编写合约代码，具有很高的执行效率，是对普通合约的极大优化，通用的服务包括：Oracle，DID，权限管理，数据交易所都将采用Native合约实现。NeoVm合约是采用NeoVm虚拟机运行的合约，需要编写相应的合约代码，现支持的语言包含：Java，C#，Python，NeoVm本身具有轻量级、可扩展、高性能的特性，通过结合Interop Service层能很好的打通虚拟机与账本层间的交互。

![ontology smart contract type.png](https://raw.githubusercontent.com/ontio/ontology-smartcontract/master/smart-contract-tutorial/images/smartcontract_type.png)


### 合约调度

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

## GAS费用模型

### 1、费用模型

#### GAS Limit
Gas limit是在执行智能合约的opcode过程中计步时使用，理论上智能合约越复杂，需要的gas limit的数量越高，ontology交易设定最低的Gas limit数量是20000

#### GAS Price
Gas price是给执行opcode定价，gas price的价格越高，共识节点会优先打包该笔交易。

#### Transaction Fee

交易费是gas limit 和 gas price乘积，实际的交易费分以下三种情形

- 执行opcode步数等于gas limit

 transaction fee =  gas price * gas limit

-  执行opcode步数大于gas limit

transaction fee =  gas price * gas limit 

交易失败，但gas不会退还

- 执行opcode步数小于gas limit
transaction fee =  gas price * (opcode实际消耗)

多余的gas 会退还，但最低消费是20000



**所有ONT,ONG的转账GAS LIMIT消费固定都是20000**




### 2、怎样设置Gas Fee

####  CLI

以ONT转账为例，使用Ontology CLI手动设置gas price 和 gas limit 参数，

\--gasprice  


\--gaslimit   


- 查询余额：

```
./ontology asset balance TA7FwLmuX6qMcWTgZtUxt6tjzFgfaBM5sz
```

![image](https://ws4.sinaimg.cn/large/006tKfTcgy1fs3ot3e084j30tc03q0tn.jpg)

- 转账：
```
./ontology asset transfer --from TA7FwLmuX6qMcWTgZtUxt6tjzFgfaBM5sz  --to TA7FwLmuX6qMcWTgZtUxt6tjzFgfaBM5sz  --amount 1000 --gasprice 5 --gaslimit 40000
```

![image](https://ws4.sinaimg.cn/large/006tKfTcgy1fs3ot31uq6j30sc03qaav.jpg)


可以看到，转账1000个ONT，gas price  = 5，gas limit = 40000，

最终消耗的gas =  1787019.99985 - 1787019.9997 = 0.00015

#### SDK

目前使用Java SDK和Golang SDK都可以设置GAS LIMIT 和GAS PRICE

以JAVA SDK 转账为例

```
String sendTransfer(Account sendAcct, String recvAddr, long amount, Account payerAcct, long gaslimit, long gasprice)(Account sendAcct, String recvAddr, long amount, Account payerAcct, long gaslimit, long gasprice)
```

可以在**sendTransfer**函数参数调用指定gas价格

[JAVA SDK](https://github.com/ontio/ontology-java-sdk/tree/master/docs/cn)

[Golang SDK](https://github.com/ontio/ontology-go-sdk)


## DApp去中心化应用

DApp是去中心化应用程序的缩写形式。 DApp由在去中心化的P2P网络上运行的后端代码组成。 DApp还可以有一个用户界面，由可以调用后端服务的前端代码创建。 DApp不需要中央权限来运行：它们允许用户和提供者之间的直接交互。

![dapp](https://upload-images.jianshu.io/upload_images/150344-450fe6ab35cca843.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![app vs dapp.png](https://upload-images.jianshu.io/upload_images/150344-db176bdda1168c42.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

DApp具有的特点:

*   **开源**. 理想情况下，它应该由自治来管理，所有变更必须由其用户的共识（或占大多数）决定。 它的代码库应该可供审查。

*   **去中心化**. 应用程序操作的所有记录必须存储在公共和去中心化的区块链中，以避免集中化的陷阱。

*   **激励**. 应通过使用加密令牌相应地奖励区块链的验证者，来激励它们。

*   **协议** 应用程序社区必须就加密算法达成一致，以显示价值证明. 例如, 比特币 使用 [Proof of Work (PoW)](https://en.bitcoin.it/wiki/Proof_of_work) 和 Ethereum 使用 [hybrid PoW/Proof of Stake (PoS)](https://github.com/ethereum/wiki/wiki/Proof-of-Stake-FAQ)[5](https://blockgeeks.com/guides/dapps/#sdfootnote5sym).


