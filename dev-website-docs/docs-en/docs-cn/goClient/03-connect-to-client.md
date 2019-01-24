
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

|         库          |    语言    |                   项目地址                   |
| :-----------------: | :--------: | :------------------------------------------: |
|   ontology-go-sdk   |     Go     |   https://github.com/ontio/ontology-go-sdk   |
|   ontology-ts-sdk   | TypeScript |   https://github.com/ontio/ontology-ts-sdk   |
|  ontology-java-sdk  |    Java    |  https://github.com/ontio/ontology-java-sdk  |
| ontology-python-sdk |   Python   | https://github.com/ontio/ontology-python-sdk |