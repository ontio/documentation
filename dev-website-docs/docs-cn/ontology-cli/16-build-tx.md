
本体客户端 `Ontology-CLI` 提供了构造交易模块，用于构造对原生资产 `ONT` 与 `ONG` 进行操作的交易。

<p class="warning">为了使所构造的交易有效，交易在发送到链上之前，需要使用钱包账户进行签名。</p>

## 转账

在构造交易模块中，`transfer` 命令用于构造转账交易，其包含以下参数：

- `--gasprice`：指定交易的 `gasprice`（默认为 `500`）。
- `--gaslimit`：指定交易的 `gaslimit`（默认为 `20000`）。
- `--from`：指定转账交易的扣款账户。
- `--to` ：指定转账交易的收款账户。
- `--payer`：指定支付交易手续费的钱包账户（默认使用转账交易的扣款账户）。
- `--asset`：指定资产类型（`ONT` 与 `ONG`）。
- `--amount`：指定转账金额。
- `--wallet`：指定钱包路径（当且仅当账户使用了非默认钱包文件的索引或标签时，才需要此参数）。
- `--rpcport`：指定 JSON RPC 服务器的监听端口（默认为 `20336`）。

<section class="info">
  <ul>
   <li><code>--from</code>、<code>--to</code>、<code>--payer</code> 的参数可以用 Base58 编码的账户地址、索引或标签来表示。</li>
   <li><code>ONT</code> 的（小数点后）精度为 <code>0</code>。</li>
   <li><code>ONG</code> 的（小数点后）精度为 <code>9</code>。</li>
  </ul>
</section>

你可以在第一个终端启动本地测试网：

```shell
ontology --testmode
```
> Note: testmode模式下，gasprice会设置成0, 链上的交易不会收取手续费,方便开发者进行测试。

然后在第二个终端中构造转账交易：

构造ont转账交易
```shell
$ ontology buildtx transfer --from 1 --to AaCe8nVkMRABnp5YgEjYZ9E5KYCxks2uce --asset ont --amount 10 --gasprice 0
Transfer raw tx:
00d1810144e2f401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c156e00c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a5ac86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
```
`--from` 1 表示从钱包文件中的第一个账户向其他地址转账,可以通过`ontology account list`查看钱包里面的所有地址信息。请确认该地址，构造好的交易需要该地址进行签名。
> Note: 构造交易的时候若不指定gasprice的值，系统会默认设置成500, gaslimit会默认设置成20000, 若测试账户没有足够的ong余额,请设置gasprice的值为0。

构造ong转账交易
```shell
$ ontology buildtx transfer --from 1 --to AaCe8nVkMRABnp5YgEjYZ9E5KYCxks2uce --asset ong --amount 0.05
Transfer raw tx:
00d19c0aaabef401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c157200c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a0480f0fa02c86c51c1087472616e736665721400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
```

对 `ONG` 转账交易使用扣款账户进行签名：

```shell
$ ontology sigtx --account AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa 00d19c0aaabef401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c157200c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a0480f0fa02c86c51c1087472616e736665721400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
Password:
RawTx after signed:
00d19c0aaabef401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c157200c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a0480f0fa02c86c51c1087472616e736665721400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b65000142410a8e9bf3e5740d34fdf0b6c8167b2aa1a6cc06ef9d87818cc75e4c6bd9911f82a74c45d4aaec8d0cb6e09d54ef632950388e2d1bab6703dc28d36c9a1f4de38c0624221419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f36817042801013ac
```
>Note: 请确保`--account`指定的地址和buildtx时`--from`指定的地址一致。


将 `ONG` 转账交易发送到测试网：

```shell
$ ontology sendtx 00d19c0aaabef401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c157200c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a0480f0fa02c86c51c1087472616e73666572140
0000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b65000142410a8e9bf3e5740d34fdf0b6c8167b2aa1a6cc06ef9d87818cc75e4c6bd9911f82a74c45d4aaec8d0cb6e09d54ef632950388e2d1bab6703dc28d36c9a1f4de38c0624221419e9b0d726b0712fb92015b8e41
ee5e5bb3d0321485b13322c6f36817042801013ac
Send transaction success.
  TxHash:7a0e5bdfe126182717bed3efc4b55d5dd268a6d483455d8df8cafaf5b9a6cd9a

Tip:
  Using './ontology info status 7a0e5bdfe126182717bed3efc4b55d5dd268a6d483455d8df8cafaf5b9a6cd9a' to query transaction status.
```

根据交易哈希查询交易状态：

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

### 授权转账

在构造交易模块中，`approve` 命令用于构造授权转账交易，其包含以下参数：

- `--gasprice`：指定交易的 `gasprice`（默认为 `500`）。
- `--gaslimit`：指定交易的 `gaslimit`（默认为 `20000`）。
- `--from`：指定转账交易的扣款账户。
- `--to`：指定转账交易的收款账户。
- `--payer`：指定支付交易手续费的钱包账户（默认使用转账交易的扣款账户）。
- `--asset`：指定资产类型（`ONT` 与 `ONG`，默认为 `ONT`）。
- `--amount`：指定转账金额。
- `--wallet`：指定钱包路径（当且仅当账户使用了非默认钱包文件的索引或标签时，才需要此参数）。
- `--rpcport` ：指定 JSON RPC 服务器的监听端口（默认为 `20336`）。

<section class="info">
  <ul>
   <li><code>--from</code>、<code>--to</code>、<code>--payer</code> 的参数可以用 Base58 编码的账户地址、索引或标签来表示。</li>
   <li><code>ONT</code> 的（小数点后）精度为 <code>0</code>。</li>
   <li><code>ONG</code> 的（小数点后）精度为 <code>9</code>。</li>
  </ul>
</section>

你可以在第一个终端启动本地测试网：

```shell
ontology --testmode
```

然后在第二个终端中构造授权转账交易：

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

使用扣款账户对 `ONG` 转账交易进行签名：

```shell
$ ontology sigtx --account 1 00d1ba72da78f401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd617
48b69d0c156f00c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a142f12240d851c5c1fdc6e95bfe22efe4e480e50b5c86a0480f0fa
02c86c07617070726f76651400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
Password:
RawTx after signed:
00d1ba72da78f401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c156f00c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a142f12240d851c5c1fdc6e95bfe22efe4e480e50b5c86a0480f0fa02c86c07617070726f76651400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b65000142410a3a57a79a52a616e6b1c2c83a1fda6c4582b3011cc0aa52057ff4693f14cb9757a2ccd62e5d2c371ae084248251e6c526e09b2e33c5a1f3d73fcbbb5dff4e330324221419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f36817042801013ac
```

将交易发送到本地测试网：

```shell
$ ontology sendtx 00d1ba72da78f401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c156f00c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a142f12240d851c5c1fdc6e95bfe22efe4e480e50b5c86a0480f0fa02c86c07617070726f76651400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b65000142410a3a57a79a52a616e6b1c2c83a1fda6c4582b3011cc0aa52057ff4693f14cb9757a2ccd62e5d2c371ae084248251e6c526e09b2e33c5a1f3d73fcbbb5dff4e330324221419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f36817042801013ac
Send transaction success.
  TxHash:71573d550d0985d44f217b91185c14f83cec669ce431f9998522525084662e51

Tip:
  Using './ontology info status 71573d550d0985d44f217b91185c14f83cec669ce431f9998522525084662e51' to query transaction status.
```

根据交易哈希查询交易状态：

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

### 授权账户转账

在构造交易模块中，`transferfrom` 命令用于构造授权账户转账交易，其包含以下参数：

- `--gasprice`：指定交易的 `gasprice`（默认为 `500`）。
- `--gaslimit` ：指定交易的 `gaslimit`（默认为 `20000`）。
- `--sender`：指定转账交易的发送账户（被授权账户，默认使用收款人账户）。
- `--from`：指定转账交易的扣款账户（授权账户）。
- `--to`：指定转账交易的收款账户。
- `--payer`：指定支付交易手续费的钱包账户（默认使用转账交易的扣款账户）。
- `--asset`：指定资产类型（`ONT` 与 `ONG`，默认为 `ONT`）。
- `--amount`：指定转账金额。
- `--wallet`：指定钱包路径（当且仅当账户使用了非默认钱包文件的索引或标签时，才需要此参数）。
- `--rpcport`：指定 JSON RPC 服务器的监听端口（默认为 `20336`）。

<section class="info">
  <ul>
   <li><code>--sender</code>、<code>--from</code>、<code>--to</code>、<code>--payer</code> 的参数可以用 Base58 编码的账户地址、索引或标签来表示。</li>
   <li><code>ONT</code> 的（小数点后）精度为 <code>0</code>。</li>
   <li><code>ONG</code> 的（小数点后）精度为 <code>9</code>。</li>
  </ul>
</section>

你可以在第一个终端启动本地测试网：

```shell
ontology --testmode
```

然后在第二个终端中构造授权转账交易：

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

查询账户余额：

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

使用被授权账户进行签名：

```shell
$ ontology sigtx --account 2 00d1c219ac50f401000000000000204e0000000000002f12240d851c5c1fdc6e95bfe22efe4e480e50b58b00c66b6a142f12240d851c5c1fdc6e95bfe22efe4e480e50b5c86a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a143a5f33fe68147164f2fbc523d18c5a065956fed0c86a0480f0fa02c86c0c7472616e7366657246726f6d1400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
Password:
RawTx after signed:
00d1c219ac50f401000000000000204e0000000000002f12240d851c5c1fdc6e95bfe22efe4e480e50b58b00c66b6a142f12240d851c5c1fdc6e95bfe22efe4e480e50b5c86a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a143a5f33fe68147164f2fbc523d18c5a065956fed0c86a0480f0fa02c86c0c7472616e7366657246726f6d1400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b6500014140d7e56108265d152353df33025f214a74d24957ebf2e4a48bacfe264c3776b5111929b5901ed164ce086873c2a7498966ae1954f815084090fe36bc0544c7a8dc232102b76e86481df6e9814b203a41a0b040c87807d1bcfd18f8ea69c7d73ebf2b944aac
```

将授权账户的转账交易发送到本地测试网：

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

再次查询账户余额：

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

在构造交易模块中，`withdrawong` 命令用于构造提取 `ONG` 交易，其包含以下参数：

- `--gasprice`：指定交易的 `gasprice`（默认为 `500`）。
- `--gaslimit`：指定交易的 `gaslimit`（默认为 `20000`）。
- `--receive`：指定所提取 `ONG` 的收款账户（默认使用提取账户作为收款账户）。
- `--payer`：指定支付交易手续费的钱包账户（默认使用转账交易的扣款账户）。
- `--asset`：指定资产类型（`ONT` 与 `ONG`，默认为 `ONT`）。
- `--amount`：指定转账金额。
- `--wallet`：指定钱包路径（当且仅当账户使用了非默认钱包文件的索引或标签时，才需要此参数）。
- `--rpcport`：指定 JSON RPC 服务器的监听端口（默认为 `20336`）。

<section class="info">
  <ul>
   <li><code>--receive</code>、<code>--payer</code> 的参数可以用 Base58 编码的账户地址、索引或标签来表示。</li>
   <li><code>ONG</code> 的（小数点后）精度为 <code>9</code>。</li>
  </ul>
</section>

你可以在第一个终端启动本地测试网：

```shell
ontology --testmode
```

然后在第二个终端中构造提取 `ONG` 交易：

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

查询可提取 `ONG`：

```shell
$ ontology asset unboundong 1
Unbound ONG:
  Account:AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa
  ONG:387455
```

查询账户余额：

```shell
$ ontology asset balance 2
BalanceOf:AL4m8xiSrmxAjCEGVdZWADQgVuasozpnF9
  ONT:0
  ONG:0
```

发送提取 `ONG` 交易：

```shell
$ ontology sendtx 00d138b00f75f401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c158d00c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a140000000000000000000000000000000000000001c86a142f12240d851c5c1fdc6e95bfe22efe4e480e50b5c86a0600804271ee00c86c0c7472616e7366657246726f6d1400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b65000142410af2e3a6929e1dd3ac5e441724fc2c8c55f57cd1825d3afac628b03fe90c4f7ad4d4f57f4e201a2f23cf1333cabe3587addc21afc92352111eeef75f9fd4916c0b24221419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f36817042801013ac
Send transaction success.
  TxHash:91c7604ed261b86a0f2bc95dd1a4ad357519255e50fd6590656f1e8e76e979a4

Tip:
  Using './ontology info status 91c7604ed261b86a0f2bc95dd1a4ad357519255e50fd6590656f1e8e76e979a4' to query transaction status.
```

根据交易哈希查询交易状态：

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

再次查询可提取 `ONG`：

```shell
$ ontology asset unboundong 1
Unbound ONG:
  Account:AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa
  ONG:386430.8976
```

再次查询账户余额：

```shell
$ ontology asset balance 2
BalanceOf:AL4m8xiSrmxAjCEGVdZWADQgVuasozpnF9
  ONT:0
  ONG:1024.1024
```


## 签名


本体客户端 `Ontology-CLI` 提供了交易签名模块，用于对以十六进制字符串显示的序列化交易进行签名。可以在命令行中通过 `sigtx` 命令使用。

- `--wallet`：指定钱包路径。
- `--prepare`：启用对签名交易的本地预执行。
- `--account`：指定签名账户（默认为钱包默认账户）。
- `--send`：指定将签名后的交易直接发送到网络中。
- `--rpcport`：指定 RPC 服务器的监听端口号（默认为 `20336`）。

<section class="info">
  <ul>
    <li>使用 <code>buildtx</code> 命令构造的交易，在发送到链上之前，还需要使用钱包账户进行签名。</li>
    <li>如果支付交易手续费的账户和交易中的签名账户不同，则该交易还需要支付手续费的账户进行签名。</li>
  </ul>
</section>

```shell
$ ontology sigtx --account AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa 00d19c0aaabef401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c157200c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a0480f0fa02c86c51c1087472616e736665721400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
Password:
RawTx after signed:
00d19c0aaabef401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c157200c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a0480f0fa02c86c51c1087472616e736665721400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b65000142410a8e9bf3e5740d34fdf0b6c8167b2aa1a6cc06ef9d87818cc75e4c6bd9911f82a74c45d4aaec8d0cb6e09d54ef632950388e2d1bab6703dc28d36c9a1f4de38c0624221419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f36817042801013ac
```

在对交易进行签名时，我们可以通过 `-p` 选项指定对交易签名后进行本地预执行，以验证交易是否存在问题。

```shell
ontology sigtx --account AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa 00d19c0aaabef401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c157200c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a0480f0fa02c86c51c1087472616e736665721400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b650000 -p
Password:
RawTx after signed:
00d19c0aaabef401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c157200c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a0480f0fa02c86c51c1087472616e736665721400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b65000142410a8e9bf3e5740d34fdf0b6c8167b2aa1a6cc06ef9d87818cc75e4c6bd9911f82a74c45d4aaec8d0cb6e09d54ef632950388e2d1bab6703dc28d36c9a1f4de38c0624221419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f36817042801013ac

Prepare execute transaction success.
Gas limit:20000
Result:01
```


### 多签地址

本体客户端 `Ontology-CLI` 提供了多签地址模块，用于根据公钥列表及签名门限 `M` 生成多重签名地址。可以在命令行中通过 `multisigaddr` 命令使用。

- `--pubkey`：用于指定多重签名地址的公钥列表，公钥之间用 `,` 分隔。
- `-m`：用于指定签名门限（默认为 `1`）。

要查看当前钱包账户中的公钥列表，使用 `ontology account list -v` 命令。

```shell
$ ontology multisigaddr --pubkey 1419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f36817042801013,02b76e86481df6e9814b203a41a0b040c87807d1bcfd18f8ea69c7d73ebf2b944a,02929e9d107f318d2cf8d99e4de47731e2d6a8eb8da5164e8d012373f06ac78157 -m 2
Pub key list:
Index 1 Address:AM6WtTARSpGsF8ugSnx9QZRu2wnP2Dk8Vo PubKey:02929e9d107f318d2cf8d99e4de47731e2d6a8eb8da5164e8d012373f06ac78157
Index 2 Address:AL4m8xiSrmxAjCEGVdZWADQgVuasozpnF9 PubKey:02b76e86481df6e9814b203a41a0b040c87807d1bcfd18f8ea69c7d73ebf2b944a
Index 3 Address:AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa PubKey:1419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f36817042801013

MultiSigAddress:ARCSXp1YYX5KUTogyTVczoypaAKc1h6o3h
```

<p class="warning">目前多重签名所支持的最大公钥数为 <code>16</code>。</p>


### 交易多签


本体客户端 `Ontology-CLI` 提供了多重签名模块，用于对以十六进制字符串显示的序列化交易进行签名。可以在命令行中通过 `multisigtx` 命令使用。

- `--wallet`：指定钱包路径。
- `--account`：指定签名账户（默认使用钱包默认账户）。
- `--pubkey`：指定多重签名的公钥列表，公钥之间用 `,` 分隔。
- `-m`：指定签名门限（默认为 `1`）。
- `--send`：指定将签名后的交易直接发送到网络中。
- `--prepare`：启用对签名后交易的预执行。
- `--rpcport`：指定 RPC 服务器的监听端口号（默认为 `20336`）。

<p class="warning">在多重签名中，需要使用公钥列表中的不同的账户对同一笔交易进行签名，一个账户签名后，返回的带签名交易需要作为下一个账户签名的输入，直到满足签名门限 <code>m</code>。</p>

```shell
$ ontology multisigtx --account AM6WtTARSpGsF8ugSnx9QZRu2wnP2Dk8Vo  --pubkey 1419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f36817042801013,02b76e86481df6e9814b203a41a0b040c87807d1bcfd18f8ea69c7d73ebf2b944a,02929e9d107f318d2cf8d99e4de47731e2d6a8eb8da5164e8d012373f06ac78157 -m 2 00d17d3efaa1f401000000000000204e000000000000675e90df552510f7485cbb947472bbfb1ccef3d66e00c66b6a14675e90df552510f7485cbb947472bbfb1ccef3d6c86a143a5f33fe68147164f2fbc523d18c5a065956fed0c86a55c86c51c1087472616e736665721400000000000000000000
000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
Password:
RawTx after multi signed:
00d17d3efaa1f401000000000000204e000000000000675e90df552510f7485cbb947472bbfb1ccef3d66e00c66b6a14675e90df552510f7485cbb947472bbfb1ccef3d6c86a143a5f33fe68147164f2fbc523d18c5a065956fed0c86a55c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65000141406b7af12334496c508bbb725726af7f50b17614b8ac6ec3180aeee741fc5a1d2524123ecf7b92e6c05a462fc38d2223476c82ef45483da6ad333ec0cdef48a27d6a522102929e9d107f318d2cf8d99e4de47731e2d6a8eb8da5164e8d012373f06ac781572102b76e86481df6e9814b203a41a0b040c87807d1bcfd18f8ea69c7d73ebf2b944a221419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f3681704280101353ae
```

```shell
$ ontology sendtx 00d17d3efaa1f401000000000000204e000000000000675e90df552510f7485cbb947472bbfb1ccef3d66e00c66b6a14675e90df552510f7485cbb947472bbfb1ccef3d6c86a143a5f33fe68147164f2fbc523d18c5a065956fed0c86a55c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65000141406b7af12334496c508bbb725726af7f50b17614b8ac6ec3180aeee741fc5a1d2524123ecf7b92e6c05a462fc38d2223476c82ef45483da6ad333ec0cdef48a27d6a522102929e9d107f318d2cf8d99e4de47731e2d6a8eb8da5164e8d012373f06ac781572102b76e86481df6e9814b203a41a0b040c87807d1bcfd18f8ea69c7d73ebf2b944a221419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f3681704280101353ae
{"desc":"","error":45021,"id":"cli","jsonrpc":"2.0","result":"transaction verify signature fail"}
```

```shell
$ontology multisigtx --account 2  --pubkey 1419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f36817042801013,02b76e86481df6e9814b203a41a0b040c87807d1bcfd18f8ea69c7d73ebf2b944a,02929e9d107f318d2cf8d99e4de47731e2d6a8eb8da5164e8d012373f06ac78157 -m 2
00d17d3efaa1f401000000000000204e000000000000675e90df552510f7485cbb947472bbfb1ccef3d66e00c66b6a14675e90df552510f7485cbb947472bbfb1ccef3d6c86a143a5f33fe68147164f2fbc523d18c5a065956fed0c86a55c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65000141406b7af12334496c508bbb725726af7f50b17614b8ac6ec3180aeee741fc5a1d2524123ecf7b92e6c05a462fc38d2223476c82ef45483da6ad333ec0cdef48a27d6a522102929e9d107f318d2cf8d99e4de47731e2d6a8eb8da5164e8d012373f06ac781572102b76e86481df6e9814b203a41a0b040c87807d1bcfd18f8ea69c7d73ebf2b944a221419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f3681704280101353ae
Password:
RawTx after multi signed:
00d17d3efaa1f401000000000000204e000000000000675e90df552510f7485cbb947472bbfb1ccef3d66e00c66b6a14675e90df552510f7485cbb947472bbfb1ccef3d6c86a143a5f33fe68147164f2fbc523d18c5a065956fed0c86a55c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65000182406b7af12334496c508bbb725726af7f50b17614b8ac6ec3180aeee741fc5a1d2524123ecf7b92e6c05a462fc38d2223476c82ef45483da6ad333ec0cdef48a27d408488b2fd12407671a59430f23c8af6875c7f7959dd050c42f34320dbc8d1a2fd9ebedf44ff8763054c447a142f0058e43aea07d9e6f2d96689342b31d26362c76a522102929e9d107f318d2cf8d99e4de47731e2d6a8eb8da5164e8d012373f06ac781572102b76e86481df6e9814b203a41a0b040c87807d1bcfd18f8ea69c7d73ebf2b944a221419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f3681704280101353ae
```

```shell
$ ontology sendtx 00d17d3efaa1f401000000000000204e000000000000675e90df552510f7485cbb947472bbfb1ccef3d66e00c66b6a14675e90df552510f7485cbb947472bbfb1ccef3d6c86a143a5f33fe68147164f2fbc523d18c5a065956fed0c86a55c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65000182406b7af12334496c508bbb725726af7f50b17614b8ac6ec3180aeee741fc5a1d2524123ecf7b92e6c05a462fc38d2223476c82ef45483da6ad333ec0cdef48a27d408488b2fd12407671a59430f23c8af6875c7f7959dd050c42f34320dbc8d1a2fd9ebedf44ff8763054c447a142f0058e43aea07d9e6f2d96689342b31d26362c76a522102929e9d107f318d2cf8d99e4de47731e2d6a8eb8da5164e8d012373f06ac781572102b76e86481df6e9814b203a41a0b040c87807d1bcfd18f8ea69c7d73ebf2b944a221419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f3681704280101353ae
Send transaction success.
  TxHash:8a153e69a39ce5f2bab1092bf15ae428388af1b57ecb29d75b45cce32fe7addb

Tip:
  Using './ontology info status 8a153e69a39ce5f2bab1092bf15ae428388af1b57ecb29d75b45cce32fe7addb' to query transaction status.
```

```shell
$ ontology info status 8a153e69a39ce5f2bab1092bf15ae428388af1b57ecb29d75b45cce32fe7addb
Transaction states:
{
   "TxHash": "8a153e69a39ce5f2bab1092bf15ae428388af1b57ecb29d75b45cce32fe7addb",
   "State": 1,
   "GasConsumed": 10000000,
   "Notify": [
      {
         "ContractAddress": "0100000000000000000000000000000000000000",
         "States": [
            "transfer",
            "ARCSXp1YYX5KUTogyTVczoypaAKc1h6o3h",
            "AM6WtTARSpGsF8ugSnx9QZRu2wnP2Dk8Vo",
            5
         ]
      },
      {
         "ContractAddress": "0200000000000000000000000000000000000000",
         "States": [
            "transfer",
            "ARCSXp1YYX5KUTogyTVczoypaAKc1h6o3h",
            "AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK",
            10000000
         ]
      }
   ]
}
```

## 发送交易


本体客户端 `Ontology-CLI` 提供了交易发送模块，用于将以十六进制字符串显示的序列化交易发送到所接入的网络。可以在命令行中通过 `sendtx` 命令使用。

- `--rpcport`：用于指定 RPC 服务器的监听端口号（默认为 `20336`）。
- `--prepare`：用于指定预执行交易。

```shell
$ ontology sendtx 00d17d3efaa1f401000000000000204e000000000000675e90df552510f7485cbb947472bbfb1ccef3d66e00c66b6a14675e90df552510f7485cbb947472bbfb1ccef3d6c86a143a5f33fe68147164f2fbc523d18c5a065956fed0c86a55c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65000182406b7af12334496c508bbb725726af7f50b17614b8ac6ec3180aeee741fc5a1d2524123ecf7b92e6c05a462fc38d2223476c82ef45483da6ad333ec0cdef48a27d408488b2fd12407671a59430f23c8af6875c7f7959dd050c42f34320dbc8d1a2fd9ebedf44ff8763054c447a142f0058e43aea07d9e6f2d96689342b31d26362c76a522102929e9d107f318d2cf8d99e4de47731e2d6a8eb8da5164e8d012373f06ac781572102b76e86481df6e9814b203a41a0b040c87807d1bcfd18f8ea69c7d73ebf2b944a221419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f3681704280101353ae
Send transaction success.
  TxHash:8a153e69a39ce5f2bab1092bf15ae428388af1b57ecb29d75b45cce32fe7addb

Tip:
  Using './ontology info status 8a153e69a39ce5f2bab1092bf15ae428388af1b57ecb29d75b45cce32fe7addb' to query transaction status.
```

```shell
$ ontology info status 8a153e69a39ce5f2bab1092bf15ae428388af1b57ecb29d75b45cce32fe7addb
Transaction states:
{
   "TxHash": "8a153e69a39ce5f2bab1092bf15ae428388af1b57ecb29d75b45cce32fe7addb",
   "State": 1,
   "GasConsumed": 10000000,
   "Notify": [
      {
         "ContractAddress": "0100000000000000000000000000000000000000",
         "States": [
            "transfer",
            "ARCSXp1YYX5KUTogyTVczoypaAKc1h6o3h",
            "AM6WtTARSpGsF8ugSnx9QZRu2wnP2Dk8Vo",
            5
         ]
      },
      {
         "ContractAddress": "0200000000000000000000000000000000000000",
         "States": [
            "transfer",
            "ARCSXp1YYX5KUTogyTVczoypaAKc1h6o3h",
            "AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK",
            10000000
         ]
      }
   ]
}
```

## 查询交易


本体客户端 `Ontology-CLI` 提供了交易反序列化模块，用于将以十六进制字符串显示的序列化交易反序列化为 JSON 格式。可以在命令行中通过 `showtx` 命令使用。

<p class="info">你可以在需要的时候通过 <code>help</code> 命令获取交易反序列化模块的帮助信息。</p>

```shell
$ ontology showtx 00d17d3efaa1f401000000000000204e000000000000675e90df552510f7485cbb947472bbfb1ccef3d66e00c66b6a14675e90df552510f7485cbb947472bbfb1ccef3d6c86a143a5f33fe68147164f2fbc523d18c5a065956fed0c86a55c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65000182406b7af12334496c508bbb725726af7f50b17614b8ac6ec3180aeee741fc5a1d2524123ecf7b92e6c05a462fc38d2223476c82ef45483da6ad333ec0cdef48a27d408488b2fd12407671a59430f23c8af6875c7f7959dd050c42f34320dbc8d1a2fd9ebedf44ff8763054c447a142f0058e43aea07d9e6f2d96689342b31d26362c76a522102929e9d107f318d2cf8d99e4de47731e2d6a8eb8da5164e8d012373f06ac781572102b76e86481df6e9814b203a41a0b040c87807d1bcfd18f8ea69c7d73ebf2b944a221419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f3681704280101353ae
{
   "Version": 0,
   "Nonce": 2717531773,
   "GasPrice": 500,
   "GasLimit": 20000,
   "Payer": "ARCSXp1YYX5KUTogyTVczoypaAKc1h6o3h",
   "TxType": 209,
   "Payload": {
      "Code": "00c66b6a14675e90df552510f7485cbb947472bbfb1ccef3d6c86a143a5f33fe68147164f2fbc523d18c5a065956fed0c86a55c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65"
   },
   "Attributes": [],
   "Sigs": [
      {
         "PubKeys": [
            "02929e9d107f318d2cf8d99e4de47731e2d6a8eb8da5164e8d012373f06ac78157",
            "02b76e86481df6e9814b203a41a0b040c87807d1bcfd18f8ea69c7d73ebf2b944a",
            "1419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f36817042801013"
         ],
         "M": 2,
         "SigData": [
            "6b7af12334496c508bbb725726af7f50b17614b8ac6ec3180aeee741fc5a1d2524123ecf7b92e6c05a462fc38d2223476c82ef45483da6ad333ec0cdef48a27d",
            "8488b2fd12407671a59430f23c8af6875c7f7959dd050c42f34320dbc8d1a2fd9ebedf44ff8763054c447a142f0058e43aea07d9e6f2d96689342b31d26362c7"
         ]
      }
   ],
   "Hash": "8a153e69a39ce5f2bab1092bf15ae428388af1b57ecb29d75b45cce32fe7addb",
   "Height": 0
}
```

此外，你也可以通过 `SDK` 对以十六进制字符串显示的序列化交易进行反序列化，以 `ontology-python-sdk` 为例。

```python
import json

from ontology.utils import utils
from ontology.core.transaction import Transaction

tx_hex = '00d17d3efaa1f401000000000000204e000000000000675e90df552510f7485cbb947472bbfb1ccef3d66e00c66b6a14675' \
         'e90df552510f7485cbb947472bbfb1ccef3d6c86a143a5f33fe68147164f2fbc523d18c5a065956fed0c86a55c86c51c108' \
         '7472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496' \
         'e766f6b65000182406b7af12334496c508bbb725726af7f50b17614b8ac6ec3180aeee741fc5a1d2524123ecf7b92e6c05a' \
         '462fc38d2223476c82ef45483da6ad333ec0cdef48a27d408488b2fd12407671a59430f23c8af6875c7f7959dd050c42f34' \
         '320dbc8d1a2fd9ebedf44ff8763054c447a142f0058e43aea07d9e6f2d96689342b31d26362c76a522102929e9d107f318d' \
         '2cf8d99e4de47731e2d6a8eb8da5164e8d012373f06ac781572102b76e86481df6e9814b203a41a0b040c87807d1bcfd18f' \
         '8ea69c7d73ebf2b944a221419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f3681704280101353ae'
tx_bytes = utils.hex_to_bytes(tx_hex)
tx = Transaction.deserialize_from(tx_bytes)
json_tx = json.dumps(dict(tx), indent=2)
```

其最终结果如下所示。

```json
{
  "version": 0,
  "txType": 209,
  "nonce": 2717531773,
  "gasPrice": 500,
  "gasLimit": 20000,
  "payer": "ARCSXp1YYX5KUTogyTVczoypaAKc1h6o3h",
  "payload": "00c66b6a14675e90df552510f7485cbb947472bbfb1ccef3d6c86a143a5f33fe68147164f2fbc523d18c5a065956fed0c86a55c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65",
  "attributes": "",
  "sigs": [
    {
      "M": 2,
      "publicKeys": [
        "02929e9d107f318d2cf8d99e4de47731e2d6a8eb8da5164e8d012373f06ac78157",
        "02b76e86481df6e9814b203a41a0b040c87807d1bcfd18f8ea69c7d73ebf2b944a",
        "1419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f36817042801013"
      ],
      "sigData": [
        "6b7af12334496c508bbb725726af7f50b17614b8ac6ec3180aeee741fc5a1d2524123ecf7b92e6c05a462fc38d2223476c82ef45483da6ad333ec0cdef48a27d",
        "8488b2fd12407671a59430f23c8af6875c7f7959dd050c42f34320dbc8d1a2fd9ebedf44ff8763054c447a142f0058e43aea07d9e6f2d96689342b31d26362c7"
      ]
    }
  ]
}
```

序列化交易的数据结构中包括了版本号、交易类型、随机数、`gasprice`、`gaslimit`、`gas` 费付款人、交易数据。

```shell
|+-+-+-+-+-+-+-+-+-+-+-+-+-+ 22 bytes +-+-+-+-+-+-+-+-+-+-+-+-+-+-+|+-+ 21 bytes +-+|+-+-+-+ any bytes +-+-+-+|
|| version(1) || type(1) || nonce(4) || gasprice(8) || gaslimit(8) ||   payer(21)  ||      payload code       ||
```

对于 `payload` 信息，其结构大致如下。

- Native 合约调用，以 `ONG` 转账操作的十六进制 `payload` 为例。
  - 00c66b：`NeoVm` 操作码，此处为参数序列化开始的标志。
  - 14：第一个参数的长度。
  - 46b1a18af6b7c9f8a4602f9f73eeb3030f0c29b7：转出地址。
  - 6a7cc8：`NeoVm` 操作码，此处为第一个参数序列化完成的标志。
  - 14：第二个参数的长度。
  - feec06b79ed299ea06fcb94abac41aaf3ead7658：转入地址。
  - 6a7cc8：`NeoVm` 操作码，此处为第二个参数序列化完成的标志。
  - 51：转移数量。
  - 6a7cc8：`NeoVm` 操作码，此处为第三个参数序列化完成的标志。
  - 6c51c1：`NeoVm` 操作码，此处为参数序列化完成的标志。
  - 08：方法名长度。
  - 7472616e73666572：`transfer` 方法。
  - 14：合约地址长度。
  - 0000000000000000000000000000000000000001：`ONG` 合约地址。
  - 00：版本号。
  - 68：`NeoVm` 操作码。
  - 16：原生合约调用名长度。
  - 4f6e746f6c6f67792e4e61746976652e496e766f6b65：原生合约调用 "Ontology.Native.Invoke"。

上述序列化后的十六进制数据可以在终端中使用 `ontology-python-sdk` 方便地查看。

```shell
$ python
>>> from ontology.utils.contract_data import ContractDataParser
>>> ContractDataParser.to_int('14')
20
>>> ContractDataParser.to_b58_address('46b1a18af6b7c9f8a4602f9f73eeb3030f0c29b7')
'ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD'
>>> ContractDataParser.to_int('14')
20
>>> ContractDataParser.to_b58_address('feec06b79ed299ea06fcb94abac41aaf3ead7658')
'Af1n2cZHhMZumNqKgw9sfCNoTWu9de4NDn'
>>> ContractDataParser.to_int('08')
8
>>> ContractDataParser.to_utf8_str('7472616e73666572')
'transfer'
>>> ContractDataParser.op_code_to_int('51')
1
>>> ContractDataParser.to_int('16')
22
>>> ContractDataParser.to_utf8_str('4f6e746f6c6f67792e4e61746976652e496e766f6b65')
'Ontology.Native.Invoke'
>>> len('Ontology.Native.Invoke')
22
```

- `NeoVm` 合约调用，以 `OEP4` 合约转账操作的十六进制 `payload` 为例。
  - 5a：第三个参数，转移数量。
  - 14：第二个参数的长度。
  - feec06b79ed299ea06fcb94abac41aaf3ead7658：转入地址。
  - 14：第一个参数的长度。
  - 46b1a18af6b7c9f8a4602f9f73eeb3030f0c29b7：转出地址。
  - 53：参数个数。
  - c1：`NeoVm` 操作码，此处为参数序列化完成的标志。
  - 08：方法名的长度。
  - 7472616e73666572：`transfer` 方法。
  - 67：`NeoVm` 操作码，对应 `APPCALL`。
  - e94e5c8c35a9979e41ff712b9e9d3e7482b6db1d：十六进制字符串形式的智能合约地址。

上述序列化后的十六进制数据可以在终端中使用 `ontology-python-sdk` 方便地查看。

```shell
$ python
>>> from ontology.utils.contract_data import ContractDataParser
>>> ContractDataParser.op_code_to_int('5a')
10
>>> ContractDataParser.to_int('14')
20
>>> ContractDataParser.to_b58_address('feec06b79ed299ea06fcb94abac41aaf3ead7658')
'Af1n2cZHhMZumNqKgw9sfCNoTWu9de4NDn'
>>> ContractDataParser.to_b58_address('46b1a18af6b7c9f8a4602f9f73eeb3030f0c29b7')
'ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD'
>>> ContractDataParser.op_code_to_int('53')
3
>>> ContractDataParser.to_int('08')
8
>>> ContractDataParser.to_reserve_hex_str('e94e5c8c35a9979e41ff712b9e9d3e7482b6db1d')
'1ddbb682743e9d9e2b71ff419e97a9358c5c4ee9'
```
