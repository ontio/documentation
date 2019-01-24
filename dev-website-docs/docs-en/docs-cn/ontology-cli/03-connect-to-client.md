
本体客户端提供了大量的调用接口，你可以通过 RPC、 Restful 或者 WebSocket 进行访问。

### 基于客户端进行调用

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

### 基于函数库进行调用

|          库          |    语言     |                        项目地址                         |
| :------------------: | :---------: | :-----------------------------------------------------: |
|   ontology-go-sdk    |     Go      |        https://github.com/ontio/ontology-go-sdk         |
|   ontology-ts-sdk    | TypeScript  |        https://github.com/ontio/ontology-ts-sdk         |
|  ontology-java-sdk   |    Java     |       https://github.com/ontio/ontology-java-sdk        |
| ontology-python-sdk  |   Python    |      https://github.com/ontio/ontology-python-sdk       |
| ontology-andriod-sdk |    JAVA     | https://github.com/ontio-community/ontology-andriod-sdk |
|   ontology-oc-sdk    | Objective-C | https://github.com/ontio-community/ontology-andriod-sdk |
|   ontology-php-sdk   |     PHP     |   https://github.com/ontio-community/ontology-php-sdk   |
|  ontology-swift-sdk  |    Swift    |  https://github.com/ontio-community/ontology-swift-sdk  |
|    ontology-dapi     | TypeScript  |         https://github.com/ontio/ontology-dapi          |

以 `ontology-python-sdk` 为例，你可以用极其简洁的代码快速连接到运行中的节点。

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
sdk.rpc.set_address(rpc_address)
sdk.restful.set_address(restful_address)
sdk.websocket.set_address(websocket_address)
```

关于函数库的更多信息可以在下列章节中找到：

- [ontology-python-sdk](docs-cn/SDKs/python-sdk.md)