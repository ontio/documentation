
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

- NEO VM 合约调用，以 `OEP4` 合约转账操作的十六进制 `payload` 为例。
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
