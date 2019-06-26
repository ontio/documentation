
# Ontology Sharding

Ontology致力于创建一个组件化、可自由配置、跨链支持、高性能、横向可扩展的区块链底层基础设施。 让部署及调用去中心化应用变得更加非常简单。

Ontology Sharding TestNet 目前已经上线，邀请广大开发者体验。很多新的功能还处于快速的开发过程中，希望开发者在使用过程中提出宝贵的意见和建议。

## 特性

- 多层分片的网络架构
- 基于智能合约的分片策略
- 支持分片间智能合约消息通讯
- 支持分片间的原子调用


## 测试网环境

本体分片测试网包含三个分片，分片之间可以完成跨链业务。

|         |           | IP Address       | Rest     | P2P   |
| ----    | --------- | ---------------  | -------- | ----- |
| Root    | **Peer1** | 139.217.111.185  | 20334    | 20338 | 
|         | **Peer2** | 139.217.103.126  | 20334    | 20338 | 
|         | **Peer3** | 139.217.111.232  | 20334    | 20338 | 
|         | **Peer4** | 139.217.80.65    | 20334    | 20338 | 
|         | **Peer5** | 139.217.111.194  | 20334    | 20338 | 
|         | **Peer6** | 139.217.111.250  | 20334    | 20338 | 
|         | **Peer7** | 139.217.103.26   | 20334    | 20338 | 
| Shard-A | **Peer1** | 139.217.111.185  | 30334    | 30338 | 
|         | **Peer2** | 139.217.103.126  | 30334    | 30338 | 
|         | **Peer3** | 139.217.111.232  | 30334    | 30338 | 
|         | **Peer4** | 139.217.80.65    | 30334    | 30338 | 
|         | **Peer5** | 139.217.111.194  | 30334    | 30338 | 
|         | **Peer6** | 139.217.111.250  | 30334    | 30338 | 
|         | **Peer7** | 139.217.103.26   | 30334    | 30338 | 
| Shard-B | **Peer1** | 139.217.111.185  | 40334    | 40338 | 
|         | **Peer2** | 139.217.103.126  | 40334    | 40338 | 
|         | **Peer3** | 139.217.111.232  | 40334    | 40338 | 
|         | **Peer4** | 139.217.80.65    | 40334    | 40338 | 
|         | **Peer5** | 139.217.111.194  | 40334    | 40338 | 
|         | **Peer6** | 139.217.111.250  | 40334    | 40338 | 
|         | **Peer7** | 139.217.103.26   | 40334    | 40338 | 


## 测试币获取

测试币获取申请入口：https://developer.ont.io/applyOng

该入口可供一个地址申请一次1000 Ont和1000 Ong的测试币，跨链测试只会用到Ong。

该入口会同时发放polaris测试网、多链测试网和分片测试网的测试代币。

## 创建分片

#### 启动分片节点

#### 创建分片

#### 配置分片

#### 节点加入分片

#### 启动分片

## 分片智能合约开发

#### 跨分片智能合约开发


## 部署分片智能合约

分片环境下支持了新的智能合约特性，最重要的两个特性以OEP的形式提出了，可以参阅[OEP-9](https://github.com/ontio/OEPs/pull/50)以及[OEP-11](https://github.com/ontio/OEPs/pull/54)了解详情。

为了支持这些新的特性，智能合约的编译器也做了升级，增加了新的分片的特有的Runtime API。目前只有Python版本的编译器做了升级，升级之后的编译器参阅[Ontology Sharding Compiler](https://github.com/qiluge/ontology-python-compiler/tree/sharding)，使用方法与之前一致。

这里提供一个跨分片合约调用的例子，该合约是[OEP-9的例子](https://github.com/qiluge/ontology-xshard-contract/blob/master/xshardasset/xshardassetdemo.py)。

### 编译

```
git clone https://github.com/qiluge/ontology-python-compiler
git clone https://github.com/qiluge/ontology-xshard-contract
cd ontology-python-compiler
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
git checkout -b sharding origin/sharding
./run.py -n ../ontology-xshard-contract/xshardasset/xshardassetdemo.py -m 1
```
编译完成之后进入

#### 部署分片资产合约

#### 部署分片业务合约

#### 配置跨分片合约


## 调用分片智能合约

#### 资产合约的分片调用

#### 业务合约的分片调用


