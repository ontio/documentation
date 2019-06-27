
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
| Root Shard    | **Peer1** | 139.217.111.185  | 20334    | 20338 | 
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

该入口可供一个地址申请一次1000 Ont和10 Ong的分片测试币。


## 获取Ontology

首先通过从 github.com/ontio/ontology.git 获取ontology源代码。

```
$ git clone https://github.com/ontio/ontology.git
```

从中checkout sharding分支。

```
$ git checkout -b sharding remotes/origin/sharding
```

用第三方包管理工具glide拉取依赖库

```
$ cd $GOPATH/src/github.com/ontio/ontology
$ glide install
```

如果项目有新的第三方依赖包，使用glide更新依赖库

```
$ cd $GOPATH/src/github.com/ontio/ontology
$ glide update
```

用make编译源码

```
$ make all
```

成功编译后会生成的ontology应用程序即为支持 Ontology Sharding 的Ontology节点程序。

#### 获取Ontology分片管理工具

首先通过从 https://github.com/qiluge/ontology-tool.git 获取Ontology-tool的代码

```
$ git clone https://github.com/qiluge/ontology-tool.git
```

通过go build编译源码

```
$ go build main.go -o ontology-tool
```

配置Ontology tool目录中的 config_test.json，更新如下字段。

```
  "JsonRpcAddress": "http://139.217.111.185:20336",
  "WalletFile": "./your-wallet.dat",
  "Password": "your-password",
```

#### 启动分片节点
（可选操作）
下载Ontology Sharding测试网的配置文件。(./Config/config.json) 保存到Ontology应用程序相同的目录中。
启动Ontology分片测试网的同步节点。

```
$ ./ontology --config config.json --networkid 606
```

一个分片的完整启动流程为：

1. 创建分片：在Root Shard中申请Shard ID
2. 配置分片：配置新的Shard的参数，包括共识，Gas相关参数
3. 节点加入分片：Root Shard中的节点通过质押stake加入到新的分片网络中
4. 启动分片

#### 创建分片
通过Ontology-tool申请创建分片。创建分片的参数保存于 params/shardmgmt/ShardCreate.json。创建命令为：
```
$ ./ontology-tool -t ShardInit
```

分片创建请求处理完成后，将为申请的分片分配一个Shard ID。后续对此分片的配置和操作都将基于此Shard ID。

#### 配置分片
得到对应的Shard ID后，分片的创建者首先需要对分片进行配置。
配置分片的参数保存于 params/shardmgmt/ShardConfig.json。
当前分片配置的参数如下（可能根据功能需求而增加）：

* Network Size : 分片网络的节点规模
* N ： 分片网络的共识节点数目
* Block Msg Delay ：分片网络共识过程中区块消息传播的最大delay (ms为单位)
* Max Block Change View ：分片网络共识周期切换时间（以区块数目计算）
* Min Init Stake ：加入分片网络节点需要质押的最少Stake数目

配置分片的命令为：
```
$ ./ontology-tool -t ShardConfig
```

#### 节点加入分片

分片完成配置后，Root Shard中的节点将可以通过质押Stake神器加入到分片网络中。
加入到分片网络中的节点需要为此分片启动新的Ontology节点。
申请加入分片也需要使用Ontology-tool进行申请操作，参数保存于 params/shardmgmt/ShardPeerJoin.json。
当前节点申请加入分片的参数如下：

* Shard ID : 要申请加入分片的Shard ID
* IP Address : 将为此分片启动的分片节点IP地址和P2P端口号
* Public Key : 节点的公钥
* Stake Amount : 为此节点质押的Staking

节点申请加入分片的命令为：

```
$ ./ontology-tool -t ShardPeerApply
```

节点加入分片后，可以随时申请退出分片。
如果申请退出时分片尚未完成启动，节点将可以立即退出，并得到自己质押的staking。
如果分片已经完成启动，根据节点在分片中担任的角色，在共识周期后才能够完成节点退出操作。
节点退出的命令为：

```
$ ./ontology-tool -t ShardPeerExit
```

#### 启动Ontology sharding节点

在节点加入到分片后，即可以启动分片分片客户端，开始同步root shard区块。
启动命令为：
```
$ ./ontology  --ShardID  <shard-ID>  --config config.json --networkid 606 --enable-consensus
```
Ontology Sharding节点启动后，将首先同步root shard区块，同时等待对应Shard的启动。

#### 启动分片

在有足够多的节点加入到分片后，分片可以开始启动运行。
启动运行操作由分片的创建者完成。
启动分片的参数保存于 params/shardmgmt/ShardActivate.json。
启动分片命令为：
```
$ ./ontology-tool -t ShardActivate
```

#### 分片资产初始化



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


