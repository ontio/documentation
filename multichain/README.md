<h1 align="center">本体多链开发手册 </h1>
<h4 align="center">Version 1.0 </h4>

Ontology致力于创建一个组件化、可自由配置、跨链支持、高性能、横向可扩展的区块链底层基础设施。 让部署及调用去中心化应用变得更加非常简单。

Ontology MultiChain TestNet 目前已经上线，邀请广大开发者体验。很多新的功能还处于快速的开发过程中，希望开发者在使用过程中提出宝贵的意见和建议。

## 特性

- 多链之间独立性强，业务隔离
- 只需同步少部分区块头
- 跨链功能模块化，与业务解耦，轻松完成跨链合约开发
- 完整的矿工激励方案
- 支持侧链之间直接交互

## 目录

- [测试网环境](#测试网环境)
- [测试币获取](#测试币获取)
- [资产转移](#资产转移)
  - [主链向侧链转移资产](#主链向侧链转移资产)
  - [侧链向主链转移资产](#侧链向主链转移资产)
- [跨链合约开发](#跨链合约开发)
  - [跨链合约概述](#跨链合约概述)
  - [跨链接口](#跨链接口)
  - [跨链合约开发示例](#跨链合约开发示例)
- [测试网使用指南](#测试网使用指南)
  - [跨链合约开发和测试](#跨链合约开发和测试)

## 测试网环境

本体多链测试网包含一条主链和侧链，两条链之间可以完成跨链业务。

- 主链ip：138.91.6.125

  rest port:  20334
  
  ws port:    20335
  
  rpc port：20336

  主链链ID：0

- 侧链ip：138.91.6.193

  rest port:  20334
  
  ws port:    20335
  
  rpc port：20336

  侧链链ID：1

## 测试币获取

测试币获取申请入口：https://developer.ont.io/applyOng

该入口可供一个地址申请一次10 Ont和100 Ong的测试币，跨链测试只会用到Ong。

该入口会同时发放polaris测试网和multi-chain测试网的测试代币。

## 资产转移

用户申请到的测试币是主网的ong，用户想要使用侧链的功能，必须要有侧链的ong用于支付手续费，主链和侧链之间可以自由转移资产，例如用户可以将1个主链的ong兑换为1个子链的ong，反之亦然。

目前还没有钱包支持资产转移功能，因此在测试网中只能通过工具来完成。

资产转移工具：<https://github.com/siovanus/multichain-transfer>

### 主链向侧链转移资产

修改config.json文件：

```
{
  "ChainID": 0,
  "JsonRpcAddress":"http://138.91.6.125:20336",
  "GasPrice":500,
  "GasLimit":20000
}
```

运行命令行`./main --fee 10000000000 --chain-id 1 --amount 150000000000`

--fee表示矿工费，--chain-id表示目标链的链ID， --amount表示要转移ong的数量（精度为9）

### 侧链向主链转移资产

修改config.json文件：

```
{
  "ChainID": 1,
  "JsonRpcAddress":"http://138.91.6.193:20336",
  "GasPrice":500,
  "GasLimit":20000
}
```

运行命令行`./main --fee 10000000000 --chain-id 0 --amount 150000000000`

--fee表示矿工费，--chain-id表示目标链的链ID， --amount表示要转移ong的数量（精度为9）

## 跨链合约开发

本体多链生态支持跨链合约，所谓跨链合约就是合约的逻辑贯穿两条甚至多条链，例如：

发布一本OEP4，该OEP4合约资产可以在主链和侧链之间转移。

一本dApp合约，该合约部分逻辑在主链完成，部分逻辑在子链完成。

### 跨链合约概述

本体跨链合约实际上是多本合约，例如dApp开发者需要在链A和链B上实现跨链业务，此时开发者需要分别在链A和链B上部署智能合约（暂时称之为智能合约A和智能合约B）。

本体跨链合约的开发总的来说可以分为两部分，业务部分和跨链部分：

业务部分是指在某条链中运行的逻辑代码，按照标准的智能合约开发方式开发，完成合约在该链中的业务。

当需要跨链时，如链A的逻辑执行完，接下来需要执行链B的逻辑，那么就需要用到跨链接口。

### 跨链接口

合约的跨链对开发者来说只需要关注一个跨链接口，也就是跨链管理合约的“createCrossChainTx”接口，该接口将链A上已经执行的业务存入merkle tree，会有矿工生成该跨链交易的merkle证明，并将其提交到链B的跨链管理合约中，跨链管理合约会验证merkle证明，并按照参数调用智能合约B中对应的方法。

### 跨链合约开发示例

#### OEP4

某开发者想在链A和链B上发行资产，但是希望链A和链B上的资产互通，也就是说其需要发行一种OEP4资产，这种OEP4资产能够在链A和链B上同时使用，并且可以在链A和链B上自由转移。

开发者首先下载OEP4合约模板，智能合约A部署在链A上，调用init方法，初始化10亿token给某个owner地址。智能合约B部署在链B上，调用init方法，初始化10亿token给该智能合约B的地址。

为了使智能合约A和智能合约B的资产可以在链A和链B之间互相转移，在OEP4标准接口的基础上，需要增加lock和unlock接口，用户在链A中调用lock接口将资产锁定在智能合约A，该接口调用跨链管理合约实现跨链调用智能合约B中的unlock接口，unlock接口在链B中将智能合约B中的资产释放给该用户。反之亦然。

lock接口实现：

```python
def lock(fee, to_chain_id, destination_contract, address, amount):
    """
    lock some amount of tokens of this contract, call cross chain method to release to_amount of tokens of another chain's contract
    :param fee: miner fee of this cross chain tx
    :param to_chain_id: chain id of destination chain
    :param address: address of caller
    :param to_amount: amount to lock
    :return:
    """
    if len(address) != 20:
        raise Exception("address length error")
    if CheckWitness(address) == False:
        raise Exception("address checkwitness failed.")
        
    # transfer asset
    res = transfer(address, CONTRACT_ADDRESS, amount)
    if not res:
        raise Exception("transfer failed.")
    
    # call cross chain contract
    input_map = {
        "address": address,
        "amount": amount
    }
    input_bytes = Serialize(input_map)
    param = state(fee, address, to_chain_id, destination_contract, "unlock", input_bytes)
    res = Invoke(0, CROSS_CHAIN_CONTRACT_ADDRESS, "createCrossChainTx", param)
    if not res:
        raise Exception("call cross chain contract failed.")
    
    LockEvent(fee, to_chain_id, destination_contract, address, amount)
    return True
```
参数为：
```
fee: 跨链交易的矿工费
to_chain_id: 目标链的链ID
destination_contract：目标合约的合约地址的反序
address: 调用发起者地址，矿工费从该地址扣除
amount：转移资产的数量
```

可以看到该接口先执行转账操作来冻结用户的链A资产，然后调用了跨链管理合约中的createCrossChainTx方法，该方法接受六个参数：

```
fee: 跨链交易的矿工费
address: 调用发起者地址，矿工费从该地址扣除
to_chain_id: 目标链的链ID
destination_contract：目标合约的合约地址的反序
function: 要跨链调用的目标合约方法名
input_bytes：序列化之后的输入参数
```

该方法会跨链调用目标合约地址的方法名，输入参数为input_bytes。

unlock接口实现：

```python
def unlock(args):
    """
    lock some amount of tokens of this contract, call cross chain method to release to_amount of tokens of another chain's contract
    :param fee: miner fee of this cross chain tx
    :param to_chain_id: chain id of destination chain
    :param address: address of caller
    :param to_amount: amount to lock
    :return:
    """
    if CheckWitness(CROSS_CHAIN_CONTRACT_ADDRESS) == False:
        raise Exception("cross chain contract address checkwitness failed.")
    
    input_map = Deserialize(args)
    address = input_map["address"]
    amount = input_map["amount"]
        
    # unlock asset
    res = transfer(CONTRACT_ADDRESS, address, amount)
    if not res:
        raise Exception("transfer failed.")

    UnlockEvent(address, amount)    
    
    return True
```

该接口接受input_bytes作为输入参数，反序列化出原始的input_map，然后执行下面的逻辑，解锁链B资产给用户。

需要注意的是该方法作为跨链的目标方法，只能接受跨链管理合约的调用。

目前跨链方法的返回值只支持布尔类型。

智能合约A和智能合约B模板：<https://github.com/siovanus/multiChainContract>

## 测试网使用指南

### 跨链合约开发和测试

在测试网上进行跨链合约的开发和测试工作，最便捷的方法是依赖于cyano和smartx。

cyano中可以通过设置实现主链和侧链之间的自由切换。

![cyano](https://i.loli.net/2019/05/09/5cd3b7a625342.png)

配置好主链和侧链的cyano钱包后，用户可以在smartx中开发、部署、测试跨链合约。

![smartx](https://i.loli.net/2019/05/17/5cde17939f24148708.png)

详细教程见[教程](Tutorial_Case.md)
