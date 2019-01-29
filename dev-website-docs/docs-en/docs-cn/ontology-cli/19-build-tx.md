
本体客户端 `Ontology-CLI` 提供了构造交易模块，用于构造对原生资产 `ONT` 与 `ONG` 进行操作的交易。

> **注意**：为了使所构造的交易有效，交易在发送到链上之前，还需要使用钱包账户进行签名。

## 转账交易

在构造交易模块中，`transfer` 命令用于构造转账交易。

- `--gasprice` 用于指定交易的 `gasprice`（默认为 `500`）。
- `--gaslimit` 用于指定交易的 `gaslimit`（默认为 `20000`）。
- `--from` 用于指定转账交易的扣款账户。
- `--payer` 用于指定支付交易手续费的钱包账户（默认使用转账交易的扣款账户）。
- `--asset` 用于指定资产类型（`ONT` 与 `ONG`）。
- `--to` 用于指定转账交易的收款账户。
- `--amount` 用于指定转账金额。
- `--wallet` 用于指定钱包路径（当且仅当账户使用了非默认钱包文件的索引或标签时，才需要此参数）。

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
$ ontology buildtx transfer --from 1 --to AaCe8nVkMRABnp5YgEjYZ9E5KYCxks2uce --asset ong --amount 0.01
Transfer raw tx:
00d134898788f401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c157200c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a0480969800c86c51c1087472616e736665721400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
```