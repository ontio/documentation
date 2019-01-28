
本体客户端提供了大量的调用接口，你可以通过 RPC、 Restful 或者 WebSockek 进行访问。

默认情况下，Restful 接口监听在 20334 端口，Websocket 接口监听在 20335 端口，RPC 接口监听在 20336 端口。

## 基于客户端进行调用

本体的 Go 客户端提供了大量调用命令，这些命令默认会向本地启动的节点按照 JSON-RPC 协议发送调用命令。

一个简单的例子是分别在测试模式和主网同步模式查询账户余额。

1. 在第一个终端中开启测试模式

```shell
ontology --testmode
```

2. 在第二个终端中查询账户余额

```shell
ontology asset balance 1
```

3. 将第一个终端切换到主网同步模式

```shell
ontology
```

4. 在第二个终端中查询账户余额

```shell
ontology asset balance 1
```

## 基于 SDK 进行调用

我们提供了众多SDK 供开发者使用，你可以选择自己熟悉的语言，快速开始你在本体网络上的区块链之旅！

|          库          |    语言     |                        项目地址                         |
| :------------------: | :---------: | :-----------------------------------------------------: |
|    ontology-dapi     | TypeScript  |         https://github.com/ontio/ontology-dapi          |
|   ontology-ts-sdk    | TypeScript  |        https://github.com/ontio/ontology-ts-sdk         |
|   ontology-go-sdk    |     Go      |        https://github.com/ontio/ontology-go-sdk         |
|  ontology-java-sdk   |    Java     |       https://github.com/ontio/ontology-java-sdk        |
| ontology-python-sdk  |   Python    |      https://github.com/ontio/ontology-python-sdk       |
|   ontology-oc-sdk    | Objective-C | https://github.com/ontio-community/ontology-andriod-sdk |
|   ontology-php-sdk   |     PHP     |   https://github.com/ontio-community/ontology-php-sdk   |
|  ontology-swift-sdk  |    Swift    |  https://github.com/ontio-community/ontology-swift-sdk  |
| ontology-andriod-sdk |    Java     | https://github.com/ontio-community/ontology-andriod-sdk |

以 `ontology-python-sdk` 为例，你可以在安装 SDK 后用简洁的代码快速连接到运行中的节点。

```shell
pip install ontology-python-sdk
```

- 连接到主网

```Python
from ontology.ont_sdk import OntologySdk


sdk = OntologySdk()
sdk.rpc.connect_to_main_net()
sdk.restful.connect_to_main_net()
sdk.websocket.connect_to_main_net()
```

- 连接到测试网

```Python
from ontology.ont_sdk import OntologySdk


sdk = OntologySdk()
sdk.rpc.connect_to_test_net()
sdk.restful.connect_to_test_net()
sdk.websocket.connect_to_test_net()
```

- 连接到本地节点

```Python
from ontology.ont_sdk import OntologySdk


sdk = OntologySdk()
sdk.rpc.connect_to_localhost()
sdk.restful.connect_to_localhost()
sdk.websocket.connect_to_localhost()
```

- 连接到自定义节点

```Python
from ontology.ont_sdk import OntologySdk


sdk = OntologySdk()
rpc_address = 'http://localhost:20336'
restful_address = 'http://localhost:20334'
websocket_address = 'http://localhost:20335'
sdk.rpc.set_address(rpc_address)
sdk.restful.set_address(restful_address)
sdk.websocket.set_address(websocket_address)
```

关于函数库的更多信息可以在下列章节中找到：

- [ontology-dapi](docs-cn/SDKs/ontology-dapi.md)
- [ontology-ts-sdk](docs-cn/SDKs/ts-sdk.md)
- [ontology-java-sdk](docs-cn/SDKs/java-sdk.md)
- [ontology-python-sdk](docs-cn/SDKs/python-sdk.md)

## 使用公开节点

通常情况下，开发者自己运行节点是极为不便的。因此，我们提供了 polaris 测试网节点以及主网节点供开发者使用，它们均支持 RPC、 Restful 以及 WebSockek 调用，并使用默认的端口号。

- polaris 测试网节点
  - http://polaris1.ont.io
  - http://polaris2.ont.io
  - http://polaris3.ont.io
  - http://polaris4.ont.io
  - http://polaris5.ont.io

- 主网节点
  - http://dappnode1.ont.io
  - http://dappnode2.ont.io
  - http://dappnode3.ont.io
  - http://dappnode4.ont.io

此外，我们也提供了[测试网水龙头](https://developer.ont.io/applyOng)供开发者获取本体网络的原生通证 `ONT` 与 `ONG`。
