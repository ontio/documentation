
本体客户端 `Ontology-CLI` 提供了构造交易模块，用于构造对原生资产 `ONT` 与 `ONG` 进行操作的交易。

> **注意**：为了使所构造的交易有效，交易在发送到链上之前，还需要使用钱包账户进行签名。

## 转账

在构造交易模块中，`transfer` 命令用于构造转账交易。

- `--gasprice` 用于指定交易的 `gasprice`（默认为 `500`）。
- `--gaslimit` 用于指定交易的 `gaslimit`（默认为 `20000`）。
- `--from` 用于指定转账交易的扣款账户。
- `--to` 用于指定转账交易的收款账户。
- `--payer` 用于指定支付交易手续费的钱包账户（默认使用转账交易的扣款账户）。
- `--asset` 用于指定资产类型（`ONT` 与 `ONG`）。
- `--amount` 用于指定转账金额。
- `--wallet` 用于指定钱包路径（当且仅当账户使用了非默认钱包文件的索引或标签时，才需要此参数）。
- `--rpcport` 用于指定 JSON RPC 服务器的监听端口（默认为 `20336`）。

> **Tips**：
> - `--from`、`--to`、`--payer` 的参数可以用 Base58 编码的账户地址、索引或标签来表示。
> - `ONT` 的精度为 `1`。
> - `ONG` 的精度为 `9`。

你可以在第一个终端启动本地测试网。

```shell
ontology --testmode
```

然后在第二个终端中构造转账交易。

```shell
$ ontology buildtx transfer --from 1 --to AaCe8nVkMRABnp5YgEjYZ9E5KYCxks2uce --asset ont --amount 10
Transfer raw tx:
00d1810144e2f401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c156e00c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a5ac86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
```

```shell
$ ontology buildtx transfer --from 1 --to AaCe8nVkMRABnp5YgEjYZ9E5KYCxks2uce --asset ong --amount 0.05
Transfer raw tx:
00d19c0aaabef401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c157200c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a0480f0fa02c86c51c1087472616e736665721400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
```

对 `ONG` 转账交易使用扣款账户进行签名。

```shell
$ ontology sigtx --account AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa 00d19c0aaabef401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c157200c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a0480f0fa02c86c51c1087472616e736665721400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
Password:
RawTx after signed:
00d19c0aaabef401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c157200c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a0480f0fa02c86c51c1087472616e736665721400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b65000142410a8e9bf3e5740d34fdf0b6c8167b2aa1a6cc06ef9d87818cc75e4c6bd9911f82a74c45d4aaec8d0cb6e09d54ef632950388e2d1bab6703dc28d36c9a1f4de38c0624221419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f36817042801013ac
```

将 `ONG` 转账交易发送到测试网。

```shell
$ ontology sendtx 00d19c0aaabef401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c157200c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a0480f0fa02c86c51c1087472616e73666572140
0000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b65000142410a8e9bf3e5740d34fdf0b6c8167b2aa1a6cc06ef9d87818cc75e4c6bd9911f82a74c45d4aaec8d0cb6e09d54ef632950388e2d1bab6703dc28d36c9a1f4de38c0624221419e9b0d726b0712fb92015b8e41
ee5e5bb3d0321485b13322c6f36817042801013ac
Send transaction success.
  TxHash:7a0e5bdfe126182717bed3efc4b55d5dd268a6d483455d8df8cafaf5b9a6cd9a

Tip:
  Using './ontology info status 7a0e5bdfe126182717bed3efc4b55d5dd268a6d483455d8df8cafaf5b9a6cd9a' to query transaction status.
```

根据交易哈希查询交易状态。

```shell
$ ontology info status 7a0e5bdfe126182717bed3efc4b55d5dd268a6d483455d8df8cafaf5b9a6cd9a
Transaction states:
{
   "TxHash": "7a0e5bdfe126182717bed3efc4b55d5dd268a6d483455d8df8cafaf5b9a6cd9a",
   "State": 1,
   "GasConsumed": 10000000,
   "Notify": [
      {
         "ContractAddress": "0200000000000000000000000000000000000000",
         "States": [
            "transfer",
            "AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa",
            "AaCe8nVkMRABnp5YgEjYZ9E5KYCxks2uce",
            50000000
         ]
      },
      {
         "ContractAddress": "0200000000000000000000000000000000000000",
         "States": [
            "transfer",
            "AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa",
            "AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK",
            10000000
         ]
      }
   ]
}
```

## 授权转账

在构造交易模块中，`approve` 命令用于构造授权转账交易。

- `--gasprice` 用于指定交易的 `gasprice`（默认为 `500`）。
- `--gaslimit` 用于指定交易的 `gaslimit`（默认为 `20000`）。
- `--from` 用于指定转账交易的扣款账户。
- `--to` 用于指定转账交易的收款账户。
- `--payer` 用于指定支付交易手续费的钱包账户（默认使用转账交易的扣款账户）。
- `--asset` 用于指定资产类型（`ONT` 与 `ONG`，默认为 `ONT`）。
- `--amount` 用于指定转账金额。
- `--wallet` 用于指定钱包路径（当且仅当账户使用了非默认钱包文件的索引或标签时，才需要此参数）。
- `--rpcport` 用于指定 JSON RPC 服务器的监听端口（默认为 `20336`）。

> **Tips**：
> - `--from`、`--to`、`--payer` 的参数可以用 Base58 编码的账户地址、索引或标签来表示。
> - `ONT` 的精度为 `1`。
> - `ONG` 的精度为 `9`。

你可以在第一个终端启动本地测试网。

```shell
ontology --testmode
```

然后在第二个终端中构造授权转账交易。

```shell
$ ontology buildtx approve --from 1 --to AaCe8nVkMRABnp5YgEjYZ9E5KYCxks2uce --asset ont --amount 10
Approve raw tx:
00d1ea037f0bf401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c156b00c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a5ac86c07617070726f76651400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
```

```shell
$ ontology buildtx approve --from 1 --to 2 --asset ong --amount 0.05
Approve raw tx:
00d1ba72da78f401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c156f00c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a142f12240d851c5c1fdc6e95bfe22efe4e480e50b5c86a0480f0fa02c86c07617070726f76651400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
```

使用扣款账户对 `ONG` 转账交易进行签名。

```shell
$ ontology sigtx --account 1 00d1ba72da78f401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd617
48b69d0c156f00c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a142f12240d851c5c1fdc6e95bfe22efe4e480e50b5c86a0480f0fa
02c86c07617070726f76651400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
Password:
RawTx after signed:
00d1ba72da78f401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c156f00c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a142f12240d851c5c1fdc6e95bfe22efe4e480e50b5c86a0480f0fa02c86c07617070726f76651400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b65000142410a3a57a79a52a616e6b1c2c83a1fda6c4582b3011cc0aa52057ff4693f14cb9757a2ccd62e5d2c371ae084248251e6c526e09b2e33c5a1f3d73fcbbb5dff4e330324221419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f36817042801013ac
```

将交易发送到本地测试网。

```shell
$ ontology sendtx 00d1ba72da78f401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c156f00c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a142f12240d851c5c1fdc6e95bfe22efe4e480e50b5c86a0480f0fa02c86c07617070726f76651400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b65000142410a3a57a79a52a616e6b1c2c83a1fda6c4582b3011cc0aa52057ff4693f14cb9757a2ccd62e5d2c371ae084248251e6c526e09b2e33c5a1f3d73fcbbb5dff4e330324221419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f36817042801013ac
Send transaction success.
  TxHash:71573d550d0985d44f217b91185c14f83cec669ce431f9998522525084662e51

Tip:
  Using './ontology info status 71573d550d0985d44f217b91185c14f83cec669ce431f9998522525084662e51' to query transaction status.
```

根据交易哈希查询交易状态。

```shell
$ ontology info status 71573d550d0985d44f217b91185c14f83cec669ce431f9998522525084662e51
Transaction states:
{
   "TxHash": "71573d550d0985d44f217b91185c14f83cec669ce431f9998522525084662e51",
   "State": 1,
   "GasConsumed": 10000000,
   "Notify": [
      {
         "ContractAddress": "0200000000000000000000000000000000000000",
         "States": [
            "transfer",
            "AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa",
            "AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK",
            10000000
         ]
      }
   ]
}
```

## 授权账户转账

在构造交易模块中，`transferfrom` 命令用于构造授权账户转账交易。

- `--gasprice` 用于指定交易的 `gasprice`（默认为 `500`）。
- `--gaslimit` 用于指定交易的 `gaslimit`（默认为 `20000`）。
- `--sender` 用于指定转账交易的发送账户（被授权账户，默认使用收款人账户）。
- `--from` 用于指定转账交易的扣款账户（授权账户）。
- `--to` 用于指定转账交易的收款账户。
- `--payer` 用于指定支付交易手续费的钱包账户（默认使用转账交易的扣款账户）。
- `--asset` 用于指定资产类型（`ONT` 与 `ONG`，默认为 `ONT`）。
- `--amount` 用于指定转账金额。
- `--wallet` 用于指定钱包路径（当且仅当账户使用了非默认钱包文件的索引或标签时，才需要此参数）。
- `--rpcport` 用于指定 JSON RPC 服务器的监听端口（默认为 `20336`）。

> **Tips**：
> - `--sender`、`--from`、`--to`、`--payer` 的参数可以用 Base58 编码的账户地址、索引或标签来表示。
> - `ONT` 的精度为 `1`。
> - `ONG` 的精度为 `9`。

你可以在第一个终端启动本地测试网。

```shell
ontology --testmode
```

然后在第二个终端中构造授权转账交易。

```shell
$ ontology buildtx transferfrom --sender 2 --from 1 --to AaCe8nVkMRABnp5YgEjYZ9E5KYCxks2uce --asset ont --amount 10
Approve raw tx:
00d144327ed4f401000000000000204e000000000000ca216237583e7c32ba82ca352ecc30782f5a902d8700c66b6a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a5ac86c0c7472616e7366657246726f6d1400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
```

```shell
$ ontology buildtx transferfrom --sender 2 --from 1 --to 3 --asset ong --amount 0.05
Approve raw tx:
00d1c219ac50f401000000000000204e0000000000002f12240d851c5c1fdc6e95bfe22efe4e480e50b58b00c66b6a142f12240d851c5c1fdc6e95bfe22efe4e480e50b5c86a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a143a5f33fe68147164f2fbc523d18c5a065956fed0c86a0480f0fa02c86c0c7472616e7366657246726f6d1400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
```

查询账户余额。

```shell
$ ontology asset balance 2
BalanceOf:AL4m8xiSrmxAjCEGVdZWADQgVuasozpnF9
  ONT:0
  ONG:0.01
$ ontology asset balance 3
BalanceOf:AM6WtTARSpGsF8ugSnx9QZRu2wnP2Dk8Vo
  ONT:0
  ONG:0
```

使用被授权账户进行签名。

```shell
$ ontology sigtx --account 2 00d1c219ac50f401000000000000204e0000000000002f12240d851c5c1fdc6e95bfe22efe4e480e50b58b00c66b6a142f12240d851c5c1fdc6e95bfe22efe4e480e50b5c86a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a143a5f33fe68147164f2fbc523d18c5a065956fed0c86a0480f0fa02c86c0c7472616e7366657246726f6d1400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
Password:
RawTx after signed:
00d1c219ac50f401000000000000204e0000000000002f12240d851c5c1fdc6e95bfe22efe4e480e50b58b00c66b6a142f12240d851c5c1fdc6e95bfe22efe4e480e50b5c86a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a143a5f33fe68147164f2fbc523d18c5a065956fed0c86a0480f0fa02c86c0c7472616e7366657246726f6d1400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b6500014140d7e56108265d152353df33025f214a74d24957ebf2e4a48bacfe264c3776b5111929b5901ed164ce086873c2a7498966ae1954f815084090fe36bc0544c7a8dc232102b76e86481df6e9814b203a41a0b040c87807d1bcfd18f8ea69c7d73ebf2b944aac
```

将授权账户的转账交易发送到本地测试网。

```shell
$ ontology sendtx 00d1c219ac50f401000000000000204e0000000000002f12240d851c5c1fdc6e95bfe22efe4e480e50b58b00c66b6a142f12240d851c5c1fdc6e95bfe22efe4e480e50b5c86a145c0708fbe99dcf821c1acf261dd61748b69d0c15c
86a143a5f33fe68147164f2fbc523d18c5a065956fed0c86a0480f0fa02c86c0c7472616e7366657246726f6d1400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b6500014140d7e56108265d152353df33025f214
a74d24957ebf2e4a48bacfe264c3776b5111929b5901ed164ce086873c2a7498966ae1954f815084090fe36bc0544c7a8dc232102b76e86481df6e9814b203a41a0b040c87807d1bcfd18f8ea69c7d73ebf2b944aac
Send transaction success.
  TxHash:c3c28b72ca2b5613a8702a6f6c12e85d5e8b423b38543e5e3f4a4fa8c74149d4

Tip:
  Using './ontology info status c3c28b72ca2b5613a8702a6f6c12e85d5e8b423b38543e5e3f4a4fa8c74149d4' to query transaction status.
```

```shell
$ ontology info status c3c28b72ca2b5613a8702a6f6c12e85d5e8b423b38543e5e3f4a4fa8c74149d4
Transaction states:
{
   "TxHash": "c3c28b72ca2b5613a8702a6f6c12e85d5e8b423b38543e5e3f4a4fa8c74149d4",
   "State": 1,
   "GasConsumed": 10000000,
   "Notify": [
      {
         "ContractAddress": "0200000000000000000000000000000000000000",
         "States": [
            "transfer",
            "AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa",
            "AM6WtTARSpGsF8ugSnx9QZRu2wnP2Dk8Vo",
            50000000
         ]
      },
      {
         "ContractAddress": "0200000000000000000000000000000000000000",
         "States": [
            "transfer",
            "AL4m8xiSrmxAjCEGVdZWADQgVuasozpnF9",
            "AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK",
            10000000
         ]
      }
   ]
}
```

再次查询账户余额。

```shell
$ ontology asset balance 2
BalanceOf:AL4m8xiSrmxAjCEGVdZWADQgVuasozpnF9
  ONT:0
  ONG:0
$ ontology asset balance 3
BalanceOf:AM6WtTARSpGsF8ugSnx9QZRu2wnP2Dk8Vo
  ONT:0
  ONG:0.05
```

## 提取 ONG

在构造交易模块中，`withdrawong` 命令用于构造提取 `ONG` 交易。

- `--gasprice` 用于指定交易的 `gasprice`（默认为 `500`）。
- `--gaslimit` 用于指定交易的 `gaslimit`（默认为 `20000`）。
- `--receive` 用于指定所提取 `ONG` 的收款账户（默认使用提取账户作为收款账户）。
- `--payer` 用于指定支付交易手续费的钱包账户（默认使用转账交易的扣款账户）。
- `--asset` 用于指定资产类型（`ONT` 与 `ONG`，默认为 `ONT`）。
- `--amount` 用于指定转账金额。
- `--wallet` 用于指定钱包路径（当且仅当账户使用了非默认钱包文件的索引或标签时，才需要此参数）。
- `--rpcport` 用于指定 JSON RPC 服务器的监听端口（默认为 `20336`）。

> **Tips**：
> - `--receive`、`--payer` 的参数可以用 Base58 编码的账户地址、索引或标签来表示。
> - `ONG` 的精度为 `9`。

你可以在第一个终端启动本地测试网。

```shell
ontology --testmode
```

然后在第二个终端中构造提取 `ONG` 交易。

```shell
$ ontology buildtx withdrawong 1 --receive AL4m8xiSrmxAjCEGVdZWADQgVuasozpnF9 --amount 1024.1024
Withdraw account:AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa
Receive account:AL4m8xiSrmxAjCEGVdZWADQgVuasozpnF9
Withdraw ONG amount:1024102400000
Withdraw raw tx:
00d138b00f75f401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c158d00c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a140000000000000000000000000000000000000001c86a142f12240d851c5c1fdc6e95bfe22efe4e480e50b5c86a0600804271ee00c86c0c7472616e7366657246726f6d1400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
```

```shell
$ ontology sigtx --account 1 00d138b00f75f401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c158d00c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a14000000000000000000000000000000
0000000001c86a142f12240d851c5c1fdc6e95bfe22efe4e480e50b5c86a0600804271ee00c86c0c7472616e7366657246726f6d1400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
Password:
RawTx after signed:
00d138b00f75f401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c158d00c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a140000000000000000000000000000000000000001c86a142f12240d851c5c1fdc6e95bfe22efe4e480e50b5c86a0600804271ee00c86c0c7472616e7366657246726f6d1400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b65000142410af2e3a6929e1dd3ac5e441724fc2c8c55f57cd1825d3afac628b03fe90c4f7ad4d4f57f4e201a2f23cf1333cabe3587addc21afc92352111eeef75f9fd4916c0b24221419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f36817042801013ac
```

查询可提取 `ONG`。

```shell
$ ontology asset unboundong 1
Unbound ONG:
  Account:AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa
  ONG:387455
```

查询账户余额。

```shell
$ ontology asset balance 2
BalanceOf:AL4m8xiSrmxAjCEGVdZWADQgVuasozpnF9
  ONT:0
  ONG:0
```

发送提取 `ONG` 交易。

```shell
$ ontology sendtx 00d138b00f75f401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c158d00c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a140000000000000000000000000000000000000001c
86a142f12240d851c5c1fdc6e95bfe22efe4e480e50b5c86a0600804271ee00c86c0c7472616e7366657246726f6d1400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b65000142410af2e3a6929e1dd3ac5e44172
4fc2c8c55f57cd1825d3afac628b03fe90c4f7ad4d4f57f4e201a2f23cf1333cabe3587addc21afc92352111eeef75f9fd4916c0b24221419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f36817042801013ac
Send transaction success.
  TxHash:91c7604ed261b86a0f2bc95dd1a4ad357519255e50fd6590656f1e8e76e979a4

Tip:
  Using './ontology info status 91c7604ed261b86a0f2bc95dd1a4ad357519255e50fd6590656f1e8e76e979a4' to query transaction status.
```

根据交易哈希查询交易状态。

```shell
$ ontology info status 91c7604ed261b86a0f2bc95dd1a4ad357519255e50fd6590656f1e8e76e979a4
Transaction states:
{
   "TxHash": "91c7604ed261b86a0f2bc95dd1a4ad357519255e50fd6590656f1e8e76e979a4",
   "State": 1,
   "GasConsumed": 10000000,
   "Notify": [
      {
         "ContractAddress": "0200000000000000000000000000000000000000",
         "States": [
            "transfer",
            "AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV",
            "AL4m8xiSrmxAjCEGVdZWADQgVuasozpnF9",
            1024102400000
         ]
      },
      {
         "ContractAddress": "0200000000000000000000000000000000000000",
         "States": [
            "transfer",
            "AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa",
            "AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK",
            10000000
         ]
      }
   ]
}
```

再次查询可提取 `ONG`。

```shell
$ ontology asset unboundong 1
Unbound ONG:
  Account:AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa
  ONG:386430.8976
```

再次查询账户余额。

```shell
$ ontology asset balance 2
BalanceOf:AL4m8xiSrmxAjCEGVdZWADQgVuasozpnF9
  ONT:0
  ONG:1024.1024
```
