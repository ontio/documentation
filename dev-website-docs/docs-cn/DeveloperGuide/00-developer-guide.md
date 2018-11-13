
<h1 align="center">开发者快速指南</h1> 

<p align="center" class="version">Version 1.0.0 </p> 

本体是新一代高性能公有式区块链，在主网上线之后，已经有非常多的开发者加入了本体技术社区。文档是开发者加入本体生态的入口，完善的文档体系能大大提高
开发者的开发效率，通过文档，开发者们将对本体生态、本体技术有清晰的认识。本篇文档是本体文档中心的概览，将会大致介绍文档中心的各个组成本分，这将为
开发者提供一个快速熟悉本体技术、本体生态的方法。

* [本体](#本体)
     * [什么是本体？](#什么是本体)
     * [如何获取本体？](#如何获取本体)
     * [本体节点介绍](#本体节点介绍)
        * [同步节点](#同步节点)
        * [共识节点](#共识节点)
     * [本体的共识机制](#本体的共识机制)
     * [连接到本体网络](#连接到本体网络)
     * [本体的特殊功能](#本体的特殊功能)
        * [本体DID](#本体did)
        * [分布式数据交易](#分布式数据交易)
* [如何与本体交互](#如何与本体交互)
     * [本体命令行工具](#本体命令行工具)
     * [本体签名机](#本体签名机)
     * [本体的API](#本体的api)
     * [本体的SDK](#本体的sdk)
* [本体智能合约](#本体智能合约)
     * [本体智能合约IDE——Smartx](#本体智能合约idesmartx)
     * [如何编写智能合约](#如何编写智能合约)
     * [合约的部署与调用](#合约的部署与调用)
     * [智能合约的权限管理](#智能合约的权限管理)
* [使用本体](#使用本体)
     * [环境部署](#环境部署)
     * [合约编写、部署与调用](#合约编写部署与调用)

## 本体

### 什么是本体？

本体的特性在[这里](https://ontio.github.io/documentation/install_zh.html#特性)有大致的介绍。

### 如何获取本体？

目前本体的所有源码均在GitHub上开源，用户可以自行前往[代码库](https://github.com/ontio/ontology)中下载源码编译安装，你也可以通过命令 `curl https://dev.ont.io/ontology_install | sh `  获取最新的ontology版本。或者直接获取不同版本号的
[release版本](https://github.com/ontio/ontology/releases)。具体的获取、安装方法可以参考[这里](https://ontio.github.io/documentation/install_zh.html)。

### 本体节点介绍

获取了本体之后，可以在本地启动本体程序，连接到本体网络。但是在这之前，需要先了解一下目前本体网络中的节点类型，

本体的网络节点目前分为两类：共识节点与同步节点。

共识节点参与共识，打包交易并产生区块；

同步节点同步最新的区块信息，不参与共识。

#### 同步节点

同步节点可以连接到主网，也可以连接到本体的公共测试网。连接到不同的网络时，节点将会同步不同的信息，并且将在当前目录下
建立两个文件夹：Chain和Log。Chain中将存放同步下来的区块数据，包括所有的交易数据，账户数据等；Log将存放同步数据时产生的Log信息。

#### 共识节点

共识节点与同步节点类似，可以运行在主网、测试网中。运行过程中，也将生成Chain和Log文件夹。不同的是，共识节点自己会打包交易信息产生区块，这一点是
同步节点所不能做的。

### 本体的共识机制

了解完本体网络节点类型之后，将介绍本体网络的共识机制。本体已支持DBFT与VBFT共识，目前主网与测试网均使用VBFT共识，
[这里](https://ontio.github.io/documentation/vbft_intro_zh.html)有VBFT共识网络的介绍，更详细的信息请参照本体的源码库。

### 连接到本体网络

现在，可以试着连接到本体网络了。[这里](https://github.com/ontio/ontology/blob/master/README_CN.md#运行ontology)详细介绍了如何连接到本体网络以及如何启动ontology的测试模式。

### 本体的特殊功能

#### 本体DID

Ontology DID（简称：ONT ID）基于W3C的DID规范，是一个去中心化的身份标识协议。具体的介绍可参看[这篇文档](https://ontio.github.io/documentation/ontology_DID_zh.html)。

#### 分布式数据交易

针对目前中心化数据交易所的痛点如：数据缓存、隐私数据未经用户授权、数据版权无法保护等问题，本体提出分布式数据管理协议ONT DATA，并基于此协议推出去中心化数
据交易框架DDXF。更详细的内容可以参考[这篇文档](https://ontio.github.io/documentation/DDXF_zh.html)。

## 如何与本体交互

### 本体命令行工具

在搭建本体网络，并启动的时候，你可能使用很多命令行参数。这些参数在[这里](https://ontio.github.io/documentation/cli_user_guide_zh.html)有详细的说
明。这些命令行参数也是通过ontology可执行程序来执行，统称为ontology CLI工具。CLI可以执行、调用本体网络的大部分功能，是本体网络的第一个入口。除了文档之
外，还能通过执行`./ontology --help`获取命令行参数的简略信息。

### 本体签名机

为了适应更多的需求，本体提供了一种叫做签名机的服务。该服务使用指定的钱包，对发送到该服务的交易进行签名。详情可以参考[这篇文档](https://ontio.github.io/documentation/sigsvr_zh.html)。

### 本体的API

在命令行之外，本体提供了一套更方便的区块链交互接口。这些接口以API的形式提供，目前本体的API包含三类：[本体RPC API](https://ontio.github.io/documentation/rpc_api_zh.html)，
[本体Restful API](https://ontio.github.io/documentation/restful_api_zh.html)，[本体Websocket API](https://ontio.github.io/documentation/websocket_api_zh.html)。
通过使用API，开发者可以十分便捷的向本体网络发送交易、查询数据。

### 本体的SDK

对于开发者而言，SDK是直接在程序中调用工具。目前，本体提供了三套SDK供开发者使用，分别是[Java SDK](https://ontio.github.io/documentation/ontology_java_sdk_zh.html)，
[Typescript SDK](https://ontio.github.io/documentation/ontology_ts_sdk_zh.html)与[Golang SDK](https://github.com/ontio/ontology-go-sdk)。在使用SDK之前，
建议先阅读SDK的[总体说明](https://ontio.github.io/documentation/ontology_overview_sdks_zh.html)和本体的[钱包文件规范](https://ontio.github.io/documentation/Wallet_File_Specification_en.html)。

## 本体智能合约

智能合约是当前区块链最重要的功能，本体也有自己的智能合约体系，详情请参考[这里](https://ontio.github.io/documentation/Introduction_of_Ontology_Smart_Contract_zh.html)。

### 本体智能合约IDE——Smartx

Smartx是本体推出的一站式智能合约编写工具，集成了编写、编译、部署与调试等功能，极大地提升了智能合约的开发效率。Smartx的使用方法请参考[这篇文档](https://ontio.github.io/documentation/SmartX_Tutorial_zh.html)。

### 如何编写智能合约

这里以[Hello World](https://ontio.github.io/documentation/The_Hello_World_Contract_zh.html)为例给出了一个简单的智能合约的例子。在编写智能合约的过程中，
会用到许多智能合约API，这些API在[这里](https://apidoc.ont.io/smartcontract/)给出。

### 合约的部署与调用

虽然smartx提供了一键式部署调用方法，但是仍有其他方法可以实现合约的部署和调用。部署方法可以参考[这篇文档](https://ontio.github.io/documentation/Smart_Contract_Deployment_zh.html)，
调用方法可以参考[这篇文档](https://ontio.github.io/documentation/Smart_Contract_Invocation_zh.html)。

### 智能合约的权限管理

当前，智能合约的函数可以被任何人调用，这显然不符合现实要求。基于角色的权限管理的基本思想是，每个角色可以调用部分函数，每个实体可以被赋予多种角色（实体是由其ONT ID
来标识）。[这篇文档](https://ontio.github.io/documentation/ontology_java_sdk_auth_zh.html)详细介绍了本体智能合约的权限管理方式。

## 使用本体

在对本体有了充分了解之后，这里将使用一个简单的例子来描述如何在本体网络上进行开发。

### 环境部署

1. 按照[连接到本体网络](#连接到本体网络)所述，建议使用单机环境下的测试模式。当然，你也可以选择连接到本体的公共测试网络Polaris。
接下来的步骤将以单机环境下的测试模式为例进行。

2. 使用命令`./ontology --rest --ws --localrpc --gaslimit 20000 --gasprice 0 --testmode --networkid 3`启动测试网络，输入对应的钱包里的账户的密码。

3. 使用rest接口查询初始账户（solo模式下的记账人）的余额。

   * 在浏览器中输入`http://localhost:20334/api/v1/balance/APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh`。其中`localhost`是节点的ip，`20334`是默认的rest端口，这个端口也可以自己指定，命令为
   `--rest --restport 20339`；`api/v1/balance/`为rest接口的url 路径，后接的`APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh`为初始记账人的地址。这整个URL构成了余额查询的rest接口调用方式。
   
   * 浏览器返回响应`{"Action":"getbalance","Desc":"SUCCESS","Error":0,"Result":{"ont":"1000000000","ong":"0"},"Version":"1.0.0"}`，这是一段json格式的响应字符串，可以看到该账户的ont
   数量为十亿，ong数量为0。

4. 在本体网络中，几乎所有的操作都需要消耗gas，即ong，在本例中，启动时使用了`--gasprice 0`参数将gas消耗置位0，所以后续的操作不消耗gas，但仍可以支付gas。这一步将演示如何给账户提取ong。

   * ong是ont的伴生燃料，随ONT逐步释放，但是需要手动提取到自己的账户里；
   
   * 使用`./ontology asset unboundong 1`查询默认钱包里第一个账户可提取的ONG数量，可以使用`./ontology asset --help`了解命令的详细信息；
   
       ```
       Unbound ONG:
       Account:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh
       ONG:0
       ```
   
   * 此时可提取的ong数量为零，是因为此账户还未激活ONG的释放，可以使用转账方式来激活；
   
   * 使用`./ontology account add -d`创建另一个ontology账户，地址为`AGrJQhb7bZsy57MoQk6YDt3hDP7zRioHia`，使用`./ontology account list`查询默认钱包的账户情况；
   
       ```
       Index:1    Address:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh  Label: (default)
       Index:2    Address:AGrJQhb7bZsy57MoQk6YDt3hDP7zRioHia  Label:
       ```
   
   * 使用`./ontology asset transfer --from 1 --to 2 --amount 100000000`命令，从账户1向账户2转入一亿个ont，输入账户1的密码后，转入成功；
   
       ```
       Transfer ONT
       From:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh
       To:AGrJQhb7bZsy57MoQk6YDt3hDP7zRioHia
       Amount:100000000
       TxHash:73a3d24b7dfd0d96b23f93fd38afe4638b70f921c278202443d0dd29a036236f
    
       Tip:
          Using './ontology info status 73a3d24b7dfd0d96b23f93fd38afe4638b70f921c278202443d0dd29a036236f' to query transaction status
       ```
   
   * 查询账户1和账户2的余额，这次使用命令行的方式查询，命令为`./ontology asset balance 1`和`./ontology asset balance 2`：
   
       ```
       BalanceOf:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh
       ONT:900000000
       ONG:0
       
       BalanceOf:AGrJQhb7bZsy57MoQk6YDt3hDP7zRioHia
       ONT:100000000
       ONG:0
       ```
   
   * 再次使用`./ontology asset unboundong 1`查询账户1可提取的ong数量，可以发现可提取的数量大于0（实际执行过程中，这个数额受区块高度和转出的数额影响）：
   
       ```
       Unbound ONG:
       Account:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh
       ONG:5242930
       ```
   
   * 使用`./ontology asset withdrawong 1`命令，输入账户1的密码后提取账户1的ong：
   
       ```
       Withdraw ONG:
       Account:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh
       Amount:5242930
       TxHash:6e10592e52cb7a3645eecd987c0161a8811f25ed5e183614d0e9cd9c58ab8a33
    
       Tip:
         Using './ontology info status 6e10592e52cb7a3645eecd987c0161a8811f25ed5e183614d0e9cd9c58ab8a33' to query transaction status
       ```
   
   * 使用命令行方式查询账户1的余额，可以看到，该账户里已经有ong了：
   
       ```
       BalanceOf:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh
       ONT:900000000
       ONG:5242930
       ```
   
### 合约编写、部署与调用

1. 打开[smartx](#本体智能合约idesmartx)，按照[HelloWorld示例](#如何编写智能合约)编写一个Hello World智能合约，为方便调用，我们将合约代码改成如下形式，然后编译成AVM字节码，
将AVM字节码下载下来，命名为`hello.avm`：

    ```csharp
    using Neo.SmartContract.Framework.Services.Neo;
    using Neo.SmartContract.Framework;
    using System;
    using System.ComponentModel;
    
    namespace Neo.SmartContract
    {
        public class HelloWorld : Framework.SmartContract
        {
            public static object Main(string operation, params object[] args)
            {
                switch (operation)
                {
                    case "Hello":
                        Hello((string)args[0]);
                        return true;
                    default:
                        return false;
                }
            }
            public static void Hello(string msg)
            {
                Runtime.Notify(msg);
            }
        }
    }
    ```

    >说明：Hello方法中，Runtime.Notify将传入的参数在链上做一个通知。

2. 使用命令`./ontology contract deploy --code hello.avm --name 'Hello' --version '1.0' --author 'ester' --email 'tester@test.com' --desc 'helloworld' --account 1 --gaslimit 100000000`将
合约部署到网络上，部署合约命令的详细信息可以使用`./ontology contract deploy -h`获取；

    ```
    Deploy contract:
      Contract Address:362cb5608b3eca61d4846591ebb49688900fedd0
      TxHash:c49865b16009177ed4b06add97f7be1b0b1c246e4d4575c367e918da294d3287
    
    Tip:
      Using './ontology info status c49865b16009177ed4b06add97f7be1b0b1c246e4d4575c367e918da294d3287' to query transaction status
    ```

3. 在浏览器中输入`http://localhost:20334/api/v1/contract/362cb5608b3eca61d4846591ebb49688900fedd0`，调用rest接口查询合约信息：
  
    ```
    {"Action":"getcontract","Desc":"SUCCESS","Error":0,"Result":{"Code":"54c56b6c7...","NeedStorage":false,"Name":"Hello","CodeVersion":"1.0","Author":"ester","Email":
    "tester@test.com","Description":"helloworld"},"Version":"1.0.0"}
    ```

4. 使用命令`./ontology contract invoke --address 362cb5608b3eca61d4846591ebb49688900fedd0 --params string:Hello,[string:tester] --gaslimit 200000`调用部署的合约：

    ```
    Invoke:d0ed0f908896b4eb916584d461ca3e8b60b52c36 Params:["Hello",["tester"]]
    Password:
      TxHash:2cc94de8c26fce3be233bef007ec3492043ffc304b79a02d9b612df96e950186
    
    Tip:
      Using './ontology info status 2cc94de8c26fce3be233bef007ec3492043ffc304b79a02d9b612df96e950186' to query transaction status
    ```

    >说明：`--params string:Hello,[string:tester]`指定调用合约传入的参数，这里传入了两个参数，分别是`string:Hello`和`[string:tester]`，这些参数即是传入到合约代码中Main函数执行的参数。

5. 根据提示使用命令`./ontology info status 2cc94de8c26fce3be233bef007ec3492043ffc304b79a02d9b612df96e950186`查询交易情况：

    ```
    Transaction states:
    {
       "TxHash": "2cc94de8c26fce3be233bef007ec3492043ffc304b79a02d9b612df96e950186",
       "State": 1,
       "GasConsumed": 0,
       "Notify": [
          {
             "ContractAddress": "362cb5608b3eca61d4846591ebb49688900fedd0",
             "States": [
                "746573746572"
             ]
          }
       ]
    }
    ```

6. 返回的结果中，States即为调用合约通知的msg信息，返回的是一个十六进制字符串，使用编码转换器转化后，得到的结果正是`tester`，即我们在第四步中传入的第二个参数。

