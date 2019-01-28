
本体客户端 `Ontology-CLI` 提供了信息获取模块，可以在命令行中通过 `info` 命令使用。

- 查询交易信息
- 查询交易状态
- 查询区块信息
- 查询区块高度

此外，你可以通过 `help` 命令获取信息获取模块的帮助信息 。

```shell
ontology info help
```

## 查询交易信息

在信息获取模块中，`tx` 命令用于根据交易哈希查询交易信息。

你可以在第一个终端将客户端连接到 `polaris` 测试网。

```shell
ontology --testmode
```

然后在第二个终端中查询 `polaris` 测试网中的交易信息。

- 请求

```shell
$ ontology info tx 1ebde66ec3f309dad20a63f8929a779162a067c36ce7b00ffbe8f4cfc8050d79
{
   "Version": 0,
   "Nonce": 0,
   "GasPrice": 0,
   "GasLimit": 18446744073709551615,
   "Payer": "AFmseVrdL9f9oyCzZefL9tG6UbvhPbdYzM",
   "TxType": 209,
   "Payload": {
      "Code": "1c010114c27820271114214d747b0b577daf32a19911dcb90400ca9a3b04696e69741400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65"
   },
   "Attributes": [],
   "Sigs": [],
   "Hash": "1ebde66ec3f309dad20a63f8929a779162a067c36ce7b00ffbe8f4cfc8050d79",
   "Height": 0
}
```

在返回的交易状态中，各字段的含义如下：

- `GasPrice`：交易对应的 gas 价格。
- `GasLimit`：交易对应的 gas 上限。
- `Payer`：支付交易费的账户。
- `Hash`：交易哈希。

## 查询交易状态

在信息获取模块中，`status` 命令用于根据交易哈希查询交易信息。

你可以在第一个终端将客户端连接到 `polaris` 测试网。

```shell
$ ontology --testmode
```

然后在第二个终端中查询 `polaris` 测试网中的交易信息。

- 请求

```shell
$ ontology info status 1ebde66ec3f309dad20a63f8929a779162a067c36ce7b00ffbe8f4cfc8050d79
Transaction states:
{
   "TxHash": "1ebde66ec3f309dad20a63f8929a779162a067c36ce7b00ffbe8f4cfc8050d79",
   "State": 1,
   "GasConsumed": 0,
   "Notify": [
      {
         "ContractAddress": "0100000000000000000000000000000000000000",
         "States": [
            "transfer",
            "AFmseVrdL9f9oyCzZefL9tG6UbvhPbdYzM",
            "AZW8eBkXh5qgRjmeZjqY2KFGLXhKcX4i2Y",
            1000000000
         ]
      }
   ]
}
```

在返回的交易状态中，各字段的含义如下：

- `State` 字段对应着交易执行结果，若值为 `1`，表示交易执行成功。
- `GasConsumed` 字段对应着执行交易所消耗的 `ONG`。
- `Notify` 字段对应着交易执行时所触发的事件。

## 查询区块信息

在信息获取模块中，`block` 命令用于根据区块高度或者区块哈希查询区块信息。

你可以在第一个终端将客户端连接到 `polaris` 测试网。

```shell
ontology --testmode
```

然后在第二个终端中查询 `polaris` 测试网中的区块信息。

```shell
ontology info block 0
ontology info block 44425ae42a394ec0c5f3e41d757ffafa790b53f7301147a291ab9b60a956394c
```
