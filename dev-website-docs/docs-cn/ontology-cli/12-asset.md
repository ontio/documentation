
本体客户端 `Ontology-CLI` 提供了资产管理模块，可以在命令行中通过 `asset` 命令实现：

- 查询账户资产信息
- 对账户资产进行控制，如执行 `ONT/ONG` 转账，提取 `ONG` 以及查看未绑定的 `ONG` 等

此外，你可以通过 `help` 命令获取信息获取模块的帮助信息 。

```shell
ontology asset help
```

## 1. 账户余额

要查询指定账户在所接入网络中的余额信息，使用 `balance` 命令。

你可以在第一个终端启动本地测试网。

```shell
ontology --testmode
```

然后在第二个终端中查询指定账户在本地测试网中的账户余额。

```shell
$ ontology asset balance 1
BalanceOf:AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa
  ONT:1000000000
  ONG:0
```

```shell
$ ontology account set 1 --label default
Set Account:AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa Label:acct to default successfully.

$ ontology asset balance default
BalanceOf:AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa
  ONT:1000000000
  ONG:0
```

```shell
$ ontology asset balance AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa
BalanceOf:AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa
  ONT:1000000000
  ONG:0
```

## 2. 查询可提取的 ONG

要查询指定账户在所接入网络中的可提取 `ONG` 信息，使用 `unboundong` 命令。

你可以在第一个终端启动本地测试网。

```shell
ontology --testmode
```

然后在第二个终端中查询指定账户在本地测试网中的可提取 `ONG`。

```shell
$ ontology asset unboundong 1
Unbound ONG:
  Account:AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa
  ONG:91693660
```

## 3. 提取 ONG

在资产管理模块中， `unboundong` 命令用法：

你可以在第一个终端启动本地测试网。

```shell
ontology --testmode
```

然后在第二个终端中提取指定账户在所接入网络中的 `ONG`。

```shell
$ ontology asset withdrawong 1
Password:
Withdraw ONG:
  Account:AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa
  Amount:91693660
  TxHash:03d6967360481a68d564ce0f3051932cf80a2fa3bfe2f735f2bc7ae499af5c85

Tip:
  Using './ontology info status 03d6967360481a68d564ce0f3051932cf80a2fa3bfe2f735f2bc7ae499af5c85' to query transaction status.
```

<p class = "warning">由于 <code>ONG</code> 的（小数点后）精度是 9，因此超出小数点后 9 位的小数部分将会被丢弃。</p>

###  转账

在资产管理模块中，`transfer` 命令用法：

你可以在第一个终端启动本地测试网。

```shell
ontology --testmode
```

然后在第二个终端中转移指定账户在所接入网络中的 `ONT`。

```shell
$  ontology asset transfer --from 1 --to AM6WtTARSpGsF8ugSnx9QZRu2wnP2Dk8Vo --asset ont --amount 10
Password:
Transfer ONT
  From:AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa
  To:AM6WtTARSpGsF8ugSnx9QZRu2wnP2Dk8Vo
  Amount:10
  TxHash:8e11fffce52ce2aa1b792a95ae75d6a715d90f27ccb9d1b19bfc38fee4a2a5e6

Tip:
  Using './ontology info status 8e11fffce52ce2aa1b792a95ae75d6a715d90f27ccb9d1b19bfc38fee4a2a5e6' to query transaction status.
```

<section class = "warning">
  <ul>
    <li>由于 <code>ONT</code> 的（小数点后）精度是 0，因此如果输入浮点数，那么小数部分将会被丢弃。</li>
    <li>由于 <code>ONG</code> 的（小数点后）精度是 9，因此超出小数点后 9 位的小数部分将会被丢弃。</li>
  </ul>
</section>

```shell
$ ontology info status 8e11fffce52ce2aa1b792a95ae75d6a715d90f27ccb9d1b19bfc38fee4a2a5e6
Transaction states:
{
   "TxHash": "8e11fffce52ce2aa1b792a95ae75d6a715d90f27ccb9d1b19bfc38fee4a2a5e6",
   "State": 1,
   "GasConsumed": 0,
   "Notify": [
      {
         "ContractAddress": "0100000000000000000000000000000000000000",
         "States": [
            "transfer",
            "AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa",
            "AM6WtTARSpGsF8ugSnx9QZRu2wnP2Dk8Vo",
            10
         ]
      }
   ]
}
```

## 4. 常见问题

- 如何确认对账户资产的操作是否成功？

  所有对账户资产的操作，本质上都对应着交易的发送，在完成账户资产的操作后，你可以查看返回的交易哈希，确认操作是否成功。

  ```shell
  $ ontology info status 03d6967360481a68d564ce0f3051932cf80a2fa3bfe2f735f2bc7ae499af5c85
  Transaction states:
  {
    "TxHash": "03d6967360481a68d564ce0f3051932cf80a2fa3bfe2f735f2bc7ae499af5c85",
    "State": 1,
    "GasConsumed": 0,
    "Notify": [
        {
          "ContractAddress": "0200000000000000000000000000000000000000",
          "States": [
              "transfer",
              "AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV",
              "AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa",
              91693660000000000
          ]
        }
    ]
  }
  ```

- 如何在本地测试网中获取 `ONG`？
  
  在你第一次使用本地测试网时，你的默认账户会拥有所有的 `ONT`，但 `ONG` 余额为 0，可提取的 `ONG` 也为 0。

  ```shell
  $ ontology asset balance 1
  BalanceOf:AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa
    ONT:1000000000
    ONG:0
  ```

  同时，你的可提取 `ONG` 也为 0。

  ```shell
  $ ontology asset unboundong 1
  Unbound ONG:
    Account:AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa
    ONG:0
  ```

  你可以在不损失所拥有的 `ONT` 的情况下，通过自己给自己转账产生可提取的 `ONG`。

  ```shell
  $ ontology asset transfer --from 1 -to 1 --asset ont --amount 1000000000
  Password:
  Transfer ONT
    From:AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa
    To:AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa
    Amount:1000000000
    TxHash:ede7102fe6587612121b5b9961ea9998aa7e56de8857fec923b3092a0031a5f4

  Tip:
    Using './ontology info status ede7102fe6587612121b5b9961ea9998aa7e56de8857fec923b3092a0031a5f4' to query transaction status.

  $ ontology info status ede7102fe6587612121b5b9961ea9998aa7e56de8857fec923b3092a0031a5f4
    Transaction states:
    {
      "TxHash": "ede7102fe6587612121b5b9961ea9998aa7e56de8857fec923b3092a0031a5f4",
      "State": 1,
      "GasConsumed": 0,
      "Notify": [
          {
            "ContractAddress": "0100000000000000000000000000000000000000",
            "States": [
                "transfer",
                "AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa",
                "AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa",
                1000000000
            ]
          }
      ]
    }
  ```

  完成转账后，你可使用 `unboundong` 查看当前可提取的 `ONG` 总量。

  ```shell
  $ ontology asset unboundong 1
    Unbound ONG:
      Account:AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa
      ONG:91693660
  ```

  当确认账户具有可提取的 `ONG` 后，你可以使用 `withdrawong` 命令提取 `ONG`。

  ```shell
  $ ontology asset withdrawong 1
  Password:
  Withdraw ONG:
    Account:AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa
    Amount:91693660
    TxHash:03d6967360481a68d564ce0f3051932cf80a2fa3bfe2f735f2bc7ae499af5c85

  Tip:
    Using './ontology info status 03d6967360481a68d564ce0f3051932cf80a2fa3bfe2f735f2bc7ae499af5c85' to query transaction status.
  ```

  你可以在完成提取后使用账户管理模块中的 `balance` 命令查看账户余额。

  ```shell
  $ ontology asset balance 1
  BalanceOf:AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa
    ONT:1000000000
    ONG:91693660
  ```
