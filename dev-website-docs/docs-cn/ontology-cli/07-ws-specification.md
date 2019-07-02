
## 简介

默认情况下，`WebSocket` 接口监听在 `20335` 端口。

- 使用 `--ws` 选项可以开启客户端的 `WebSocket` 服务。

  ```shell
  ontology --ws
  ```

- 使用 `--wsport` 选项为客户端指定 `WebSocket` 监听端口。

  ```shell
  ontology --wsport 1024
  ```

## 方法列表

本体客户端 `WebSocket` 接口所支持的方法如下表所示。

| 方法                                                                                            | 说明                                                 |
| :---------------------------------------------------------------------------------------------- | :--------------------------------------------------- |
| [heartbeat](docs-cn/ontology-cli/07-ws-specification#_1-heartbeat)                                 | 发送心跳信号                                         |
| [subscribe](docs-cn/ontology-cli/07-ws-specification#_2-subscribe)                                 | 订阅某个服务                                         |
| [getconnectioncount](docs-cn/ontology-cli/07-ws-specification#_3-getconnectioncount)               | 得到当前连接的节点数量                               |
| [getblocktxsbyheight](docs-cn/ontology-cli/07-ws-specification#_4-getblocktxsbyheight)             | 返回对应高度的区块中落账的所有交易哈希               |
| [getblockbyheight](docs-cn/ontology-cli/07-ws-specification#_5-getblockbyheight)                   | 得到该高度的区块的详细信息                           |
| [getblockbyhash](docs-cn/ontology-cli/07-ws-specification#_6-getblockbyhash)                       | 通过区块哈希得到区块信息                             |
| [getblockheight](docs-cn/ontology-cli/07-ws-specification#_7-getblockheight)                       | 得到当前网络上的区块高度                             |
| [getblockhash](docs-cn/ontology-cli/07-ws-specification#_8-getblockhash)                           | 根据高度得到对应区块的哈希                           |
| [gettransaction](docs-cn/ontology-cli/07-ws-specification#_9-gettransaction)                       | 通过交易哈希得到该交易的信息                         |
| [sendrawtransaction](docs-cn/ontology-cli/07-ws-specification#_10-sendrawtransaction)               | 向本体网络发送交易, 如果 `preExec=1`，则交易为预执行 |
| [getstorage](docs-cn/ontology-cli/07-ws-specification#_11-getstorage)                               | 通过合约地址哈希和键得到对应的值                     |
| [getbalance](docs-cn/ontology-cli/07-ws-specification#_12-getbalance)                               | 得到该地址的账户的余额                               |
| [getcontract](docs-cn/ontology-cli/07-ws-specification#_13-getcontract)                             | 根据合约地址哈希得到合约信息                         |
| [getsmartcodeeventbyheight](docs-cn/ontology-cli/07-ws-specification#_14-getsmartcodeeventbyheight) | 得到该高度区块上的智能合约执行结果                   |
| [getsmartcodeeventbyhash](docs-cn/ontology-cli/07-ws-specification#_15-getsmartcodeeventbyhash)     | 通过交易哈希得到该交易的执行结果                     |
| [getblockheightbytxhash](docs-cn/ontology-cli/07-ws-specification#_16-getblockheightbytxhash)       | 通过交易哈希得到该交易落账的区块高度                 |
| [getmerkleproof](docs-cn/ontology-cli/07-ws-specification#_17-getmerkleproof)                       | 通过交易哈希得到该交易的 `merkle` 证明                 |
| [getsessioncount](docs-cn/ontology-cli/07-ws-specification#_18-getsessioncount)                     | 得到会话数量                                         |
| [getgasprice](docs-cn/ontology-cli/07-ws-specification#_19-getgasprice)                             | 得到 `GAS` 的价格                                      |
| [getallowance](docs-cn/ontology-cli/07-ws-specification#_20-getallowance)                           | 返回允许从 `from` 账户转出到 `to` 账户的额度             |
| [getunboundong](docs-cn/ontology-cli/07-ws-specification#_21-getunboundong)                         | 返回该账户未提取的 `ONG` 数量                           |
| [getmempooltxstate](docs-cn/ontology-cli/07-ws-specification#_22-getmempooltxstate)                 | 通过交易哈希得到内存中该交易的状态                   |
| [getmempooltxcount](docs-cn/ontology-cli/07-ws-specification#_23-getmempooltxcount)                 | 得到内存中的交易的数量                               |
| [getversion](docs-cn/ontology-cli/07-ws-specification#_24-getversion)                               | 得到版本信息                                         |
| [getnetworkid](docs-cn/ontology-cli/07-ws-specification#_25-getnetworkid)                           | 得到 `network id`                                    |
| [getgrantong](docs-cn/ontology-cli/07-ws-specification#_26-getgrantong)                             | 得到 `grant ong`                                     |

## 接口定义

本体客户端的 `Websocket` 接口规范定义如下：

- 默认接口监听端口号：`20335`

- 响应参数

| 字段    | 类型   | 描述         |
|:--------|:-------|:-------------|
| Action  | string | 响应动作名称 |
| Desc    | string | 响应结果描述 |
| Error   | int64  | 错误代码     |
| Result  | object | 执行结果     |
| Version | string | 版本号       |
| Id      | int64  | 请求 ID      |

- 错误码

| 字段  | 类型  | 描述             |
|:------|:------|:-----------------|
| 0     | int64 | 成功             |
| 41001 | int64 | 无效或超时的会话 |
| 41002 | int64 | 达到服务上限     |
| 41003 | int64 | 不合法的数据格式 |
| 41004 | int64 | 无效的版本号     |
| 42001 | int64 | 无效的方法       |
| 42002 | int64 | 无效的参数       |
| 43001 | int64 | 无效的交易       |
| 43002 | int64 | 无效的资源       |
| 43003 | int64 | 无效的区块       |
| 44001 | int64 | 未知的交易       |
| 44002 | int64 | 未知的资源       |
| 44003 | int64 | 未知的区块       |
| 45001 | int64 | 内部错误         |
| 47001 | int64 | 智能合约执行错误 |

## 1. heartbeat

#### 调用示例

请求：

```json
{
    "Action": "heartbeat",
    "Id":12345, //optional
    "Version": "1.0.0"
}
```

响应：

```json
{
    "Action": "heartbeat",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": {
        "SubscribeEvent":false,
        "SubscribeJsonBlock":false,
        "SubscribeRawBlock":false,
        "SubscribeBlockTxHashs":false
    },
    "Version": "1.0.0"
}
```

!> 如果超过五分钟没有发送心跳信号，则连接关闭。

## 2. subscribe

`subscribe` 接口用于订阅消息推送服务。

#### 调用示例

请求：

```json
{
    "Action": "subscribe",
    "Version": "1.0.0",
    "Id":12345, //optional
    "ContractsFilter":["contractAddress"], //optional
    "SubscribeEvent":false, //optional
    "SubscribeJsonBlock":true, //optional
    "SubscribeRawBlock":false, //optional
    "SubscribeBlockTxHashs":false //optional
}
```

响应：

```json
{
    "Action": "subscribe",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": {
        "ContractsFilter":["contractAddress"],
        "SubscribeEvent":false,
        "SubscribeJsonBlock":true,
        "SubscribeRawBlock":false,
        "SubscribeBlockTxHashs":false
    },
    "Version": "1.0.0"
}
```

## 3. getconnectioncount

得到当前连接的节点数量。

#### 调用示例

请求：

```json
{
    "Action": "getconnectioncount",
    "Id":12345, //optional
    "Version": "1.0.0"
}
```

响应：

```json
{
    "Action": "getconnectioncount",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": 4,
    "Version": "1.0.0"
}
```

## 4. getblocktxsbyheight

返回对应高度的区块中落账的所有交易哈希。

#### 调用示例

请求：

```json
{
    "Action": "getblocktxsbyheight",
    "Version": "1.0.0",
    "Id":12345, //optional
    "Height": 100
}
```

响应：

```json
{
    "Action": "getblocktxsbyheight",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": {
        "Hash": "ea5e5219d2f1591f4feef89885c3f38c83d3a3474a5622cf8cd3de1b93849603",
        "Height": 100,
        "Transactions": [
            "37e017cb9de93aa93ef817e82c555812a0a6d5c3f7d6c521c7808a5a77fc93c7"
        ]
    },
    "Version": "1.0.0"
}
```

## 5. getblockbyheight

得到该高度的区块的详细信息。

#### 调用示例

请求：

```json
{
    "Action": "getblockbyheight",
    "Version": "1.0.0",
    "Id":12345, //optional
    "Raw": "0",
    "Height": 100
}
```

<section class="warning"><code>raw</code> 为可选参数，默认为 <code>0</code>。
  <ul>
    <li>当 <code>raw</code> 为 <code>1</code> 时，接口返回以十六进制字符串表示的序列化区块信息。</li>
    <li>当 <code>raw</code> 为 <code>0</code> 时，接口返回以 <code>JSON</code> 格式表示的区块详细信息.</li>
  </ul>
</section>

响应：

```json
{
    "Action": "getblockbyheight",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": {
        "Hash": "ea5e5219d2f1591f4feef89885c3f38c83d3a3474a5622cf8cd3de1b93849603",
        "Header": {
            "Version": 0,
            "PrevBlockHash": "fc3066adb581c5aee8edaa47eecda2b7cc039c8662757f8b1e3c3aed60314353",
            "TransactionsRoot": "37e017cb9de93aa93ef817e82c555812a0a6d5c3f7d6c521c7808a5a77fc93c7",
            "BlockRoot": "7154a6dcb3c23254334bc1f5d8f054c143a39ff28f46fdeb8a9c7488147ccec6",
            "Timestamp": 1522313652,
            "Height": 100,
            "ConsensusData": 18012644264110396442,
            "NextBookkeeper": "TABrSU6ABhj6Rdw5KozV53wvZNSUATgKHW",
            "Bookkeepers": [
                "120203fe4f9ba2022b68595dd163f4a92ac80f918919674de2d6e2a7e04a10c59d0066"
            ],
            "SigData": [
                "01a2369280b0ff75bed85f351d3ef0dd58add118328c1ed2f7d3320df32cb4bd55541f1bb8e11ad093bd24da3de4cd12464800310bfdb49dc62d42d97ca0549762"
            ],
            "Hash": "ea5e5219d2f1591f4feef89885c3f38c83d3a3474a5622cf8cd3de1b93849603"
        },
        "Transactions": [
            {
                "Version": 0,
                "Nonce": 0,
                "TxType": 0,
                "Payload": {
                    "Nonce": 1522313652068190000
                },
                "Attributes": [],
                "Fee": [],
                "NetworkFee": 0,
                "Sigs": [
                    {
                        "PubKeys": [
                            "120203fe4f9ba2022b68595dd163f4a92ac80f918919674de2d6e2a7e04a10c59d0066"
                        ],
                        "M": 1,
                        "SigData": [
                            "017d3641607c894dd85f455c71a94afaea2661acbe372ff8f3f4c7921b0c768756e3a6e9308a4c4c8b1b58e717f1486a2f10f5bc809b803a27c10a2cd579778a54"
                        ]
                    }
                ],
                "Hash": "37e017cb9de93aa93ef817e82c555812a0a6d5c3f7d6c521c7808a5a77fc93c7"
            }
        ]
    },
    "Version": "1.0.0"
}
```

## 6. getblockbyhash

通过区块哈希得到区块信息。

#### 调用示例

请求：

```json
{
    "Action": "getblockbyhash",
    "Version": "1.0.0",
    "Id":12345, //optional
    "Raw": "0",
    "Hash": "7c3e38afb62db28c7360af7ef3c1baa66aeec27d7d2f60cd22c13ca85b2fd4f3"
}
```

<section class="warning"><code>raw</code> 为可选参数，默认为 <code>0</code>。
  <ul>
    <li>当 <code>raw</code> 为 <code>1</code> 时，接口返回以十六进制字符串表示的序列化区块信息。</li>
    <li>当 <code>raw</code> 为 <code>0</code> 时，接口返回以 <code>JSON</code> 格式表示的区块详细信息.</li>
  </ul>
</section>

响应：

```json
{
    "Action": "getblockbyhash",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": {
        "Hash": "ea5e5219d2f1591f4feef89885c3f38c83d3a3474a5622cf8cd3de1b93849603",
        "Header": {
            "Version": 0,
            "PrevBlockHash": "fc3066adb581c5aee8edaa47eecda2b7cc039c8662757f8b1e3c3aed60314353",
            "TransactionsRoot": "37e017cb9de93aa93ef817e82c555812a0a6d5c3f7d6c521c7808a5a77fc93c7",
            "BlockRoot": "7154a6dcb3c23254334bc1f5d8f054c143a39ff28f46fdeb8a9c7488147ccec6",
            "Timestamp": 1522313652,
            "Height": 100,
            "ConsensusData": 18012644264110396442,
            "NextBookkeeper": "TABrSU6ABhj6Rdw5KozV53wvZNSUATgKHW",
            "Bookkeepers": [
                "120203fe4f9ba2022b68595dd163f4a92ac80f918919674de2d6e2a7e04a10c59d0066"
            ],
            "SigData": [
                "01a2369280b0ff75bed85f351d3ef0dd58add118328c1ed2f7d3320df32cb4bd55541f1bb8e11ad093bd24da3de4cd12464800310bfdb49dc62d42d97ca0549762"
            ],
            "Hash": "ea5e5219d2f1591f4feef89885c3f38c83d3a3474a5622cf8cd3de1b93849603"
        },
        "Transactions": [
            {
                "Version": 0,
                "Nonce": 0,
                "TxType": 0,
                "Payload": {
                    "Nonce": 1522313652068190000
                },
                "Attributes": [],
                "Fee": [],
                "NetworkFee": 0,
                "Sigs": [
                    {
                        "PubKeys": [
                            "120203fe4f9ba2022b68595dd163f4a92ac80f918919674de2d6e2a7e04a10c59d0066"
                        ],
                        "M": 1,
                        "SigData": [
                            "017d3641607c894dd85f455c71a94afaea2661acbe372ff8f3f4c7921b0c768756e3a6e9308a4c4c8b1b58e717f1486a2f10f5bc809b803a27c10a2cd579778a54"
                        ]
                    }
                ],
                "Hash": "37e017cb9de93aa93ef817e82c555812a0a6d5c3f7d6c521c7808a5a77fc93c7"
            }
        ]
    },
    "Version": "1.0.0"
}
```

## 7. getblockheight

得到当前网络上的区块高度。

#### 调用示例

请求：

```json
{
    "Action": "getblockheight",
    "Id":12345, //optional
    "Version": "1.0.0"
}
```

响应：

```json
{
    "Action": "getblockheight",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": 327,
    "Version": "1.0.0"
}
```

## 8. getblockhash

根据高度得到对应区块的哈希。

#### 调用示例

请求：

```json
{
    "Action": "getblockhash",
    "Id":12345, //optional
    "Version": "1.0.0",
    "Height": 100
}
```

响应：

```json
{
    "Action": "getblockhash",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": "3b90ddc4d33c4954c3d87736120e94915f963546861987757f358c9376422255",
    "Version": "1.0.0"
}
```

## 9. gettransaction

通过交易哈希得到该交易的信息。

#### 调用示例

请求：

```json
{
    "Action": "gettransaction",
    "Version": "1.0.0",
    "Id":12345, //optional
    "Hash": "3b90ddc4d33c4954c3d87736120e94915f963546861987757f358c9376422255",
    "Raw": "0"
}
```

<section class="warning"><code>raw</code> 为可选参数，默认为 <code>0</code>。
  <ul>
    <li>当 <code>raw</code> 为 <code>1</code> 时，接口返回以十六进制字符串表示的序列化交易信息。</li>
    <li>当 <code>raw</code> 为 <code>0</code> 时，接口返回以 <code>JSON</code> 格式表示的交易详细信息.</li>
  </ul>
</section>

响应：

```json
{
    "Action": "gettransaction",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": {
        "Version": 0,
        "Nonce": 3743545316,
        "GasPrice": 500,
        "GasLimit": 20000,
        "Payer": "AWM9vmGpAhFyiXxg8r5Cx4H3mS2zrtSkUF",
        "TxType": 209,
        "Payload": {
            "Code": "00c66b149fdd13f41303beb7771ddd0aad6b2d815dcd62916a7cc81400000000000000000000000000000000000000016a7cc8149fdd13f41303beb7771ddd0aad6b2d815dcd62916a7cc8085da07645000000006a7cc86c0c7472616e7366657246726f6d1400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b65"
        },
        "Attributes": [],
        "Sigs": [
            {
                "PubKeys": [
                    "03e9ac636107c8d5a22e87bf6ae76a5e7a1394930972db72e0c3bebf54e8210a37"
                ],
                "M": 1,
                "SigData": [
                    "01dfcf5328a6587b2e2b30d6fae73bc18343ce7e5db2c00b3c92415a7274cfb1367d74604121dfd2eb8aef95b1a5e688bdde5633f1bde0fe85881db55ea2fd112d"
                ]
            }
        ],
        "Hash": "5623dbd283a99ff1cd78068cba474a22bed97fceba4a56a9d38ab0fbc178c4ab",
        "Height": 175888
    },
    "Version": "1.0.0"
}
```

## 10. sendrawtransaction

向本体网络发送交易。

如果 `preExec=1`，则交易为预执行。

#### 调用示例

请求：

```json
{
    "Action":"sendrawtransaction",
    "Version":"1.0.0",
    "Id":12345, //optional
    "PreExec": 0,
    "Data":"80000001195876cb34364dc38b730077156c6bc3a7fc570044a66fbfeeea56f71327e8ab0000029b7cffdaa674beae0f930ebe6085af9093e5fe56b34a5c220ccdcf6efc336fc500c65eaf440000000f9a23e06f74cf86b8827a9108ec2e0f89ad956c9b7cffdaa674beae0f930ebe6085af9093e5fe56b34a5c220ccdcf6efc336fc50092e14b5e00000030aab52ad93f6ce17ca07fa88fc191828c58cb71014140915467ecd359684b2dc358024ca750609591aa731a0b309c7fb3cab5cd0836ad3992aa0a24da431f43b68883ea5651d548feb6bd3c8e16376e6e426f91f84c58232103322f35c7819267e721335948d385fae5be66e7ba8c748ac15467dcca0693692dac"
}
```

响应：

```json
{
    "Action": "sendrawtransaction",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": "22471ab3f4b4307a99f00c9a717dbf8b26f5bf63bf47f9c560477da8181de777",
    "Version": "1.0.0"
}
```

<p class="info">在交易成功的情况下，响应中 <code>Result</code> 字段对应的值为交易哈希。</p>

## 11. getstorage

通过合约地址哈希和键得到对应的值。

#### 调用示例

请求：

```json
{
    "Action": "getstorage",
    "Version": "1.0.0",
    "Id":12345, //optional
    "Hash": "0144587c1094f6929ed7362d6328cffff4fb4da2",
    "Key" : "4587c1094f6"
}
```

响应：

```json
{
    "Action": "getstorage",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": "58d15e17628000",
    "Version": "1.0.0"
}
```

<section class = "info">
  <ul>
    <li>请求中的 <code>key</code> 为十六进制字符串形式的合约存储键值。</li>
    <li>响应中的 <code>result</code> 所对应的值为序列化后的十六进制字符串，可以使用 <code>SDK</code> 进行反序列化。</li>
  </ul>
</section>

根据智能合约编译后所得到的 `avm code`，可以使用 `SDK` 生成合约地址。

```python
from ontology.common.address import Address
from ontology.utils.contract_data import ContractDataParser

code = '0000000000000000000000000000000000000001'
contract_address = Address.address_from_vm_code(code).to_hex_str()
```

```go
package demo

import (
    "fmt"
    "github.com/ontio/ontology/common"
    "testing"
)

func TestAddressFromVmCode(t *testing.T) {
    var avmCode, _ = common.HexToBytes("0000000000000000000000000000000000000001")
    addr := common.AddressFromVmCode(avmCode)
    var contractAddr = addr.ToHexString()
}
```

```java
package demo;

import com.github.ontio.OntSdk;
import com.github.ontio.common.Address;

public class NetworkDemo {
    public static void main(String[] args) {
        try {
            OntSdk sdk = OntSdk.getInstance();
            String code = "0000000000000000000000000000000000000004";
            String contractAddress = Address.AddressFromVmCode(code).toHexString();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

## 12. getbalance

得到该地址的账户的余额。

#### 调用示例

请求：

```json
{
    "Action": "getbalance",
    "Version": "1.0.0",
    "Id":12345, //optional
    "Addr": "TA63xZXqdPLtDeznWQ6Ns4UsbqprLrrLJk"
}
```

响应：

```json
{
    "Action": "getbalance",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": {
        "ont": "2500",
        "ong": "0"
    },
    "Version": "1.0.0"
}
```

## 13. getcontract

根据合约地址哈希得到合约信息。

#### 调用示例

请求：

```json
{
    "Action": "getcontract",
    "Version": "1.0.0",
    "Id":12345, //optional
    "Hash": "0100000000000000000000000000000000000000"
}
```

响应：

```json
{
    "Action": "getcontract",
    "Desc": "SUCCESS",
    "Error": 0,
    "Version": "1.0.0",
    "Result": {
        "Code": "0000000000000000000000000000000000000001",
        "NeedStorage": true,
        "Name": "ONT",
        "CodeVersion": "1.0",
        "Author": "Ontology Team",
        "Email": "contact@ont.io",
        "Description": "Ontology Network ONT Token"
    }
}
```

## 14. getsmartcodeeventbyheight

得到该高度区块上的智能合约执行结果。

#### 调用示例

请求：

```json
{
    "Action": "getsmartcodeeventbyheight",
    "Version": "1.0.0",
    "Id":12345, //optional
    "Height": 100
}
```

响应：

```json
{
    "Action": "getsmartcodeeventbyheight",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": [
                     {
                          "TxHash": "7e8c19fdd4f9ba67f95659833e336eac37116f74ea8bf7be4541ada05b13503e",
                          "State": 1,
                          "GasConsumed": 0,
                          "Notify": [
                              {
                                  "ContractAddress": "0200000000000000000000000000000000000000",
                                  "States": [
                                      "transfer",
                                      "AFmseVrdL9f9oyCzZefL9tG6UbvhPbdYzM",
                                      "AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV",
                                      1000000000000000000
                                  ]
                              }
                          ]
                      },
                      {
                          "TxHash": "fc82cd363271729367098fbabcfd0c02cf6ded1e535700d04658b596d53cf07d",
                          "State": 1,
                          "GasConsumed": 0,
                          "Notify": [
                              {
                                  "ContractAddress": "0200000000000000000000000000000000000000",
                                  "States": [
                                      "transfer",
                                      "AFmseVrdL9f9oyCzZefL9tG6UbvhPbdYzM",
                                      "AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV",
                                      1000000000000000000
                                  ]
                              }
                          ]
                      },
                      {
                          "TxHash": "6b391812b6a3230c057b108227f78a1c7caa9fa934817c60540af55e62167507",
                          "State": 1, //执行成功
                          "GasConsumed": 0, //消耗的gasLimit * gasprice的值
                          "Notify": [
                              {
                                  "ContractAddress": "49f0908f08b3ebce1e71dc5083cb9a8a54cc4a24", //合约地址
                                  "States": "57b108227f78a1c7caa9fa934817c60540af55e62167507" //只返回一个字段时，State为字符串类型
                              }
                          ]
                      }
    ],
    "Version": "1.0.0"
}
```

<p class="info">返回的结果是交易简略信息的集合，并不是完整的交易信息。</p>

## 15. getsmartcodeeventbyhash

通过交易哈希得到该交易的执行结果。

#### 调用示例

请求：

```json
{
    "Action": "getsmartcodeeventbyhash",
    "Version": "1.0.0",
    "Id":12345, //optional
    "Hash": "20046da68ef6a91f6959caa798a5ac7660cc80cf4098921bc63604d93208a8ac"
}
```

响应：

```json
{
    "Action": "getsmartcodeeventbyhash",
    "Desc": "SUCCESS",
    "Error": 0,
    "Version": "1.0.0",
    "Result": {
             "TxHash": "20046da68ef6a91f6959caa798a5ac7660cc80cf4098921bc63604d93208a8ac",
             "State": 1,
             "GasConsumed": 0,
             "Notify": [
                    {
                      "ContractAddress": "ff00000000000000000000000000000000000001",
                      "States": [
                            "transfer",
                            "A9yD14Nj9j7xAB4dbGeiX9h8unkKHxuWwb",
                            "AA4WVfUB1ipHL8s3PRSYgeV1HhAU3KcKTq",
                            1000000000
                         ]
                     }
              ]
    }
}
```

## 16. getblockheightbytxhash

通过交易哈希得到该交易落账的区块高度。

#### 调用示例

请求：

```json
{
    "Action": "getblockheightbytxhash",
    "Version": "1.0.0",
    "Id":12345, //optional
    "Hash": "3e23cf222a47739d4141255da617cd42925a12638ac19cadcc85501f907972c8"
}
```

响应：

```json
{
    "Action": "getblockheightbytxhash",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": 100,
    "Version": "1.0.0"
}
```

## 17. getmerkleproof

通过交易哈希得到该交易的 `merkle` 证明。

#### 调用示例

请求：

```json
{
    "Action": "getmerkleproof",
    "Version": "1.0.0",
    "Id":12345, //optional
    "Hash": "0087217323d87284d21c3539f216dd030bf9da480372456d1fa02eec74c3226d"
}

```

响应：

```json
{
    "Action": "getmerkleproof",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": {
        "Type": "MerkleProof",
        "TransactionsRoot": "fe3a4ee8a44e3e588de55de1b8fe08f08b6184d9c062cf7316fb9481eb57b9e6",
        "BlockHeight": 600,
        "CurBlockRoot": "57476eba688531dec8555cb712835c7eda48a478431a2cfd3372aeee5298e711",
        "CurBlockHeight": 6478,
        "TargetHashes": [
            "270cd10ea235cc18cba83a070fdf18ae576983b6b9a7bb9a3fec540b3786c85c",
            "24e4697f9dd6cb944d0736bd3e11b64f64edec94fb599e25d4e5461d54174f0e",
            "9a47ab04acf6bba7bb97b83eddeb0db20e11c0627b8079b40b60031d5bd63154",
            "d1b513810b9b983014c9f8b7084b8ea8744eca8e7c942586c2b7c63f910363ca",
            "54e88360efedcf5dbbc486ea0267724a98b027b3ba780617e32569bb3fbe56e8",
            "e0c5ebca3ca191617d42e11db64778b047cd9a520538efd95d5a688cbba0c8d5",
            "52bfb23b6456cac4e5e7143287e1518dd923c5b5d32d0bfe8d825dc8195ea62b",
            "86d6be166ae1a53c052adc40b9b66c4f95f5e3b6ecc88afaea3750e1cbe98276",
            "5588530cfc4d92e979717f8ae399ac4553a76e7537a981e8eaf078d60f1d39a6",
            "3f15bec38bcf054e4f32efe475a09d3e80c2e90d3345a1428aaa262606f13267",
            "f238ed8ceb1c10a08f7eaa390cdde44ed7d160abbde4702028407b55671e7aa8",
            "b4813f1f27c0457726b58f8bf20bee70c100a4d5c5f1805e53dcd20f38479615",
            "83893713ea8ace9214b28af854b75671c8aaa62bb74b0d43ad6fb83e3dee42db"
        ]
    },
    "Version": "1.0.0"
}
```

## 18. getsessioncount

得到会话数量。

#### 调用示例

请求：

```json
{
    "Action": "getsessioncount",
    "Version": "1.0.0",
    "Id":12345, //optional
}
```

响应：

```json
{
    "Action": "getsessioncount",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": 10,
    "Version": "1.0.0"
}
```

## 19. getgasprice

得到 `GAS` 的价格。

#### 调用示例

请求：

```json
{
    "Action": "getgasprice",
    "Version": "1.0.0",
    "Id":12345, //optional
}
```

响应：

```json
{
    "Action": "getgasprice",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": {
         "gasprice": 0,
         "height": 1
     },
    "Version": "1.0.0"
}
```

## 20. getallowance

得到允许从 `from` 账户转出到 `to` 账户的额度。

#### 调用示例

请求：

```json
{
    "Action": "getallowance",
    "Id":12345, //optional
    "Asset": "ont",
    "From" :  "A9yD14Nj9j7xAB4dbGeiX9h8unkKHxuWwb",
    "To"   :  "AA4WVfUB1ipHL8s3PRSYgeV1HhAU3KcKTq",
    "Version": "1.0.0"
}
```

响应：

```json
{
    "Action": "getallowance",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": "10",
    "Version": "1.0.0"
}
```

## 21. getunboundong

得到该账户未提取的 `ONG` 数量。

#### 调用示例

请求：

```json
{
    "Action": "getunboundong",
    "Id":12345, //optional
    "Addr": "ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6",
    "Version": "1.0.0"
}
```

响应：

```json
{
    "Action": "getunboundong",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": "204957950400000",
    "Version": "1.0.0"
}
```

## 22. getmempooltxstate

通过交易哈希得到内存中该交易的状态。

#### 调用示例

请求：

```json
{
    "Action": "getmempooltxstate",
    "Id":12345, //optional
    "Hash": "0b437771a42d18d292741c5d4f1300a135fa6e65b0594e39dc299e7f8279221a",
    "Version": "1.0.0"
}
```

响应：

```json
{
    "Action": "getmempooltxstate",
    "Desc": "SUCCESS",
    "Error": 0,
    "Version": "1.0.0",
    "Result": {
              	"State": [{
              		"Type": 1,
              		"Height": 342,
              		"ErrCode": 0
              	}, {
              		"Type": 0,
              		"Height": 0,
              		"ErrCode": 0
              	}]
    }
}
```

## 23. getmempooltxcount

得到内存中的交易的数量。

#### 调用示例

请求：

```json
{
    "Action": "getmempooltxcount",
    "Id":12345, //optional
    "Version": "1.0.0"
}
```

响应：

```json
{
    "Action": "getmempooltxcount",
    "Desc": "SUCCESS",
    "Error": 0,
    "Version": "1.0.0",
    "Result": [100,50]
}
```

## 24. getversion

得到版本信息。

#### 调用示例

请求：

```json
{
    "Action": "getversion",
    "Id":12345, //optional
    "Version": "1.0.0"
}
```

响应：

```json
{
    "Action": "getversion",
    "Desc": "SUCCESS",
    "Error": 0,
    "Version": "1.0.0",
    "Result": "0.9"
}
```

## 25. getnetworkid

获取 `network id`

#### 调用示例

请求：

```json
{
    "Action": "getnetworkid",
    "Id":12345, //optional
    "Version": "1.0.0"
}
```

响应：

```json
{
    "Action": "getnetworkid",
    "Desc": "SUCCESS",
    "Error": 0,
    "Version": "1.0.0",
    "Result": 1
}
```

## 26. getgrantong

获取 `grant ong`

#### 调用示例

请求：

```json
{
    "Action": "getgrantong",
    "Id":12345, //optional
    "Addr":"AKDFapcoUhewN9Kaj6XhHusurfHzUiZqUA",
    "Version": "1.0.0"
}
```

响应：

```json
{
    "Action": "getgrantong",
    "Desc": "SUCCESS",
    "Error": 0,
    "Version": "1.0.0",
    "Result": 4995625
}
```
