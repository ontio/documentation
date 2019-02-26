
## 简介

默认情况下，RPC 接口监听在 20336 端口。

使用 `--rpcport` 选项为客户端指定 RPC 监听端口：

```shell
ontology --rpcport 1024
```

使用 `--disable-rpc` 选项可以关闭客户端的 RPC 服务：

```shell
ontology --disable-rpc
```

<p class = "info">远程过程调用（RPC）也称为函数调用或子例程调用，用于供位于网络上的一台计算机向另一台计算机中请求服务（无需了解网络的详细信息）。</p>

## 方法列表

本体客户端 RPC 接口所支持的方法如下表所示。

| 方法                                                                                       | 描述                                           |
| :----------------------------------------------------------------------------------------- | :--------------------------------------------- |
| [getbestblockhash](docs-cn/ontology-cli/05-rpc-specification#getbestblokhash)              | 获取当前节点最高区块的哈希值                   |
| [getblock](docs-cn/ontology-cli/05-rpc-specification#getblock)                             | 根据区块哈希或区块高度查询区块信息             |
| [getblockcount](docs-cn/ontology-cli/05-rpc-specification#getblockcount)                   | 查询当前的区块数量                             |
| [getblockhash](docs-cn/ontology-cli/05-rpc-specification#getblockhash)                     | 查询指定高度的区块哈希                         |
| [getconnectioncount](docs-cn/ontology-cli/05-rpc-specification#getconnectioncount)         | 查询当前节点的连接节点数                       |
| [getrawtransaction](docs-cn/ontology-cli/05-rpc-specification#getrawtransaction)           | 通过交易哈希得到交易详情                       |
| [sendrawtransaction](docs-cn/ontology-cli/05-rpc-specification#sendrawtransaction)         | 向网络中发送交易                               |
| [getstorage](docs-cn/ontology-cli/05-rpc-specification#getstorage)                         | 获取合约存储中指定键值对应的值                 |
| [getversion](docs-cn/ontology-cli/05-rpc-specification#getversion)                         | 获取当前连接节点的版本                         |
| [getcontractstate](docs-cn/ontology-cli/05-rpc-specification#getcontractstate)             | 根据合约地址获取合约信息                       |
| [getmempooltxcount](docs-cn/ontology-cli/05-rpc-specification#getmempooltxcount)           | 获取交易池（内存）中的交易的数量               |
| [getmempooltxstate](docs-cn/ontology-cli/05-rpc-specification#getmempooltxstate)           | 获取交易池（内存）中的交易的状态               |
| [getsmartcodeevent](docs-cn/ontology-cli/05-rpc-specification#getsmartcodeevent)           | 获取智能合约的执行结果                         |
| [getblockheightbytxhash](docs-cn/ontology-cli/05-rpc-specification#getblockheightbytxhash) | 获取交易落账的区块高度                         |
| [getbalance](docs-cn/ontology-cli/05-rpc-specification#getbalance)                         | 获取账户地址的余额                             |
| [getmerkleproof](docs-cn/ontology-cli/05-rpc-specification#getmerkleproof)                 | 获取交易的 merkle 证明                         |
| [getgasprice](docs-cn/ontology-cli/05-rpc-specification#getgasprice)                       | 获取当前节点的 `gas price`                     |
| [getallowance](docs-cn/ontology-cli/05-rpc-specification#getallowance)                     | 获取一方账户允许另一方账户转出的通证额度       |
| [getgrantong](docs-cn/ontology-cli/05-rpc-specification#getgrantong)                       | 获取根据当前所持有 ONT 估算出的可提取 ONG 数量 |
| [getunboundong](docs-cn/ontology-cli/05-rpc-specification#getunboundong)                   | 获取账户当前实际可提取的 ONG 数量              |
| [getblocktxsbyheight](docs-cn/ontology-cli/05-rpc-specification#getblocktxsbyheight)       | 获取指定高度的区块哈希                         |
| [getnetworkid](docs-cn/ontology-cli/05-rpc-specification#getnetworkid)                     | 获取网络编号                                   |

## 接口定义

本体客户端的 JSON-RPC 接口定义如下：

- 默认接口监听端口号：`20336`

- 请求参数

| 字段    | 类型   | 定义            |
| ------- | ------ | --------------- |
| jsonrpc | 字符串 | JSON-RPC 版本号 |
| method  | 字符串 | 方法名称        |
| params  | 字符串 | 方法参数        |
| id      | 整型   | 任意值          |

- 返回参数

| 字段    | 类型      | 定义            |
| ------- | --------- | --------------- |
| desc    | 字符串    | 请求结果描述    |
| error   | 整型      | 错误代码        |
| jsonrpc | 字符串    | JSON-RPC 版本号 |
| id      | 整型      | 任意值          |
| result  | JSON 对象 | RPC 执行结果    |

- 错误码

| 字段  | 类型  | 含义             |
| ----- | ----- | ---------------- |
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

## getbestblockhash

获取当前节点最高区块的哈希值。

- 请求：

```json
{
  "jsonrpc": "2.0",
  "method": "getbestblockhash",
  "params": [],
  "id": 1
}
```

- 响应：

```json
{
  "desc":"SUCCESS",
  "error":0,
  "jsonrpc": "2.0",
  "id": 1,
  "result": "773dd2dae4a9c9275290f89b56e67d7363ea4826dfd4fc13cc01cf73a44b0d0e"
}
```

## getblock

根据区块哈希或区块高度查询区块信息。

- `block_hash` / `block_height`：区块哈希/高度。
- `verbose`：当值为 0 时，返回以十六进制字符串表示序列化后的区块信息。当值为1时，将以 json 格式返回对应区块的详细信息。

- 请求：

```json
{
  "jsonrpc": "2.0",
  "method": "getblock",
  "params": ["773dd2dae4a9c9275290f89b56e67d7363ea4826dfd4fc13cc01cf73a44b0d0e"],
  "id": 1
}
```

- 响应：

```json
{
  "desc":"SUCCESS",
  "error":0,
  "jsonrpc": "2.0",
  "id": 1,
  "result": "00000000ccc7612928aab25db55ab31c35c64929ce4d89f9a16d0753fddf9da63d0c339b77be0e825f3180b4d706045e42a101f5becea5d59a7d6aac58cdff0c0bd0b6a949c6405eae477bb053406c0a4f56a830289798e2d70dc77e0a1d927fa9fb93c47625f316f1bb594150e0f4c3b4c4c6394e0444f876c766b0130527ac46c766b0130c3648c00616c766b51c3c0519c009c6c766b0131527ac46c766b0131c3641000616c766b52c30052c461625400616c766b51c300c36c766b0132527ac46c766b0132c36165b3206c..."
}
```

- 请求：

```json
{
  "jsonrpc": "2.0",
  "method": "getblock",
  "params": [100],
  "id": 1
}
```

- 响应：

```json
{
    "desc": "SUCCESS",
    "error": 0,
    "id": 1,
    "jsonrpc": "2.0",
    "result": {
        "Hash": "95555da65d6feaa7cde13d6bf12131f750b670569d98c63813441cf24a99c0d2",
        "Header": {
            "Version": 0,
            "PrevBlockHash": "205c905493c7c1e3be7cd58542e45aafb007edcb8363f8ff555f63745f1b7ce5",
            "TransactionsRoot": "4452db2634d81e80048002c2f327b25ded4e547ebfcc1b28f28608938b9d2154",
            "BlockRoot": "42e01a2b27c182d4e115883c3b166a0fbc019efe2498b568b7febcc83a35346e",
            "Timestamp": 1522295648,
            "Height": 2,
            "ConsensusData": 10322907760044199803,
            "NextBookkeeper": "TAAr9AH4NqxXSKur7XTUbmP8wsKD4KPL2t",
            "Bookkeepers": [
                "120203e45fe0189a36b284e6080c6983cf12879d239886ecee1e257ab992970ecaa000"
            ],
            "SigData": [
                "014ed021011a6e0a4e9771b0be9fd156f9fc411968ce1dc4aed18382c85f6827d50373f3e3931966066cdc7dfab52823b79c80df8af25569c33ddf8140df5385b6"
            ],
            "Hash": "95555da65d6feaa7cde13d6bf12131f750b670569d98c63813441cf24a99c0d2"
        },
        "Transactions": [
            {
                "Version": 0,
                "Nonce": 0,
                "TxType": 0,
                "Payload": {
                    "Nonce": 1522295648487066000
                },
                "Attributes": [],
                "Fee": [],
                "NetworkFee": 0,
                "Sigs": [
                    {
                        "PubKeys": [
                            "120203e45fe0189a36b284e6080c6983cf12879d239886ecee1e257ab992970ecaa000"
                        ],
                        "M": 1,
                        "SigData": [
                            "01021197ad4140a50442b700ad814aeb2595578bf4d97e187a69aacf35917be4a27f76bc1dad2ee9bb386be79ca9638e78e14c869edbc3556499b06cc9c9b9452e"
                        ]
                    }
                ],
                "Hash": "4452db2634d81e80048002c2f327b25ded4e547ebfcc1b28f28608938b9d2154"
            }
        ]
    }
}
```

## getblockcount

查询当前的区块数量。

- 请求：

```json
{
  "jsonrpc": "2.0",
  "method": "getblockcount",
  "params": [],
  "id": 1
}
```

- 响应：

```json
{
  "desc":"SUCCESS",
  "error":0,
  "jsonrpc": "2.0",
  "id": 1,
  "result": 2519
}
```

## getblockhash

返回对应高度的区块哈希。

`block_height`：区块高度

- 请求：

```json
{
  "jsonrpc": "2.0",
  "method": "getblockhash",
  "params": [10000],
  "id": 1
}
```

- 响应：

```json
{
  "desc":"SUCCESS",
  "error":0,
  "jsonrpc": "2.0",
  "id": 1,
  "result": "4c1e879872344349067c3b1a30781eeb4f9040d3795db7922f513f6f9660b9b2"
}
```

## getconnectioncount

得到当前网络上连接的节点数。

- 请求：

```json
{
  "jsonrpc": "2.0",
  "method": "getconnectioncount",
  "params": [],
  "id": 1
}
```

- 响应：

```json
{
  "desc":"SUCCESS",
  "error":0,
  "jsonrpc": "2.0",
  "id": 1,
  "result": 10
}
```

## getrawtransaction

通过交易哈希得到交易详情。

- `tx_hash`：交易哈希
- `verbose`：当值为 0 时，返回以十六进制字符串表示的序列化交易信息；当值为 1 时，将以 json 格式返回对应的交易详细信息。

- 请求：

```json
{
  "jsonrpc": "2.0",
  "method": "getrawtransaction",
  "params": ["f4250dab094c38d8265acc15c366dc508d2e14bf5699e12d9df26577ed74d657"],
  "id": 1
}
```

- 响应：

```json
{
  "desc":"SUCCESS",
  "error":0,
  "jsonrpc": "2.0",
  "id": 1,
  "result": "80000001195876cb34364dc38b730077156c6bc3a7fc570044a66fbfeeea56f71327e8ab0000029b7cffdaa674beae0f930ebe6085af9093e5fe56b34a5c220ccdcf6efc336fc500c65eaf440000000f9a23e06f74cf86b8827a9108ec2e0f89ad956c9b7cffdaa674beae0f930ebe6085af9093e5fe56b34a5c220ccdcf6efc336fc50092e14b5e00000030aab52ad93f6ce17ca07fa88fc191828c58cb71014140915467ecd359684b2dc358024ca750609591aa731a0b309c7fb3cab5cd0836ad3992aa0a24da431f43b68883ea5651d548feb6bd3c8e16376e6e426f91f84c58232103322f35c7819267e721335948d385fae5be66e7ba8c748ac15467dcca0693692dac"
}
```

请求：

```json
{
  "jsonrpc": "2.0",
  "method": "getrawtransaction",
  "params": ["5623dbd283a99ff1cd78068cba474a22bed97fceba4a56a9d38ab0fbc178c4ab", 1],
  "id": 1
}
```

响应：

```json
{
    "desc": "SUCCESS",
    "error": 0,
    "id": 1,
    "jsonrpc": "2.0",
    "result": {
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
    }
}
```

## sendrawtransaction

向网络中发送交易。

#### 参数说明

- `hex_tx`：十六进制字符串表示的交易序列化数据
- `pre_exec`：值为 1 表示为预执行交易

#### 调用示例

请求：

```json
{
  "jsonrpc": "2.0",
  "method": "sendrawtransaction",
  "params": ["80000001195876cb34364dc38b730077156c6bc3a7fc570044a66fbfeeea56f71327e8ab0000029b7cffdaa674beae0f930ebe6085af9093e5fe56b34a5c220ccdcf6efc336fc500c65eaf440000000f9a23e06f74cf86b8827a9108ec2e0f89ad956c9b7cffdaa674beae0f930ebe6085af9093e5fe56b34a5c220ccdcf6efc336fc50092e14b5e00000030aab52ad93f6ce17ca07fa88fc191828c58cb71014140915467ecd359684b2dc358024ca750609591aa731a0b309c7fb3cab5cd0836ad3992aa0a24da431f43b68883ea5651d548feb6bd3c8e16376e6e426f91f84c58232103322f35c7819267e721335948d385fae5be66e7ba8c748ac15467dcca0693692dac",0],
  "id": 1
}
```

响应：

```json
{
    "desc": "SUCCESS",
    "error": 0,
    "id": 1,
    "jsonrpc": "2.0",
    "result": "498db60e96828581eff991c58fa46abbfd97d2f4a4f9915a11f85c54f2a2fedf"
}
```

<p class = "info"> 响应中 <code>result</code> 所对应的值为交易哈希。</p>

## getstorage

获取合约存储中指定键值对应的值。

#### 参数说明

- `hex_contract_address`：以十六进制字符串表示智能合约哈希地址
- `key`：以十六进制字符串表示的存储键值

#### 调用示例

请求：

```json
{
    "jsonrpc": "2.0",
    "method": "getstorage",
    "params": ["03febccf81ac85e3d795bc5cbd4e84e907812aa3", "5065746572"],
    "id": 15
}
```

响应：

```json
{
    "desc":"SUCCESS",
    "error":0,
    "jsonrpc": "2.0",
    "id": 15,
    "result": "4c696e"
}
```

<section class = "info">
  <ul>
    <li>请求中的 <code>key</code> 为十六进制字符串形式的合约存储键值。</li>
    <li>响应中的 <code>result</code> 所对应的值为序列化后的十六进制字符串，可以使用 SDK 进行反序列化。</li>
  </ul>
</section>

根据智能合约编译后所得到的 `avm code`，可以使用 SDK 生成合约地址。

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

## getversion

获取当前连接节点的版本。

#### 调用示例

请求：

```json
{
  "jsonrpc": "2.0",
  "method": "getversion",
  "params": [],
  "id": 3
}
```

响应：

```json
{
  "desc":"SUCCESS",
  "error":0,
  "jsonrpc": "2.0",
  "id": 3,
  "result": "v0.9.2-1-g231e"
}
```

## getcontractstate

根据合约地址获取合约信息。

#### 参数说明

- `hex_contract_address`：以十六进制字符串表示的合约哈希地址
- `verbose`：当值为 0 时，返回以十六进制字符串表示的序列化合约信息；当值为 1 时，将以 json 格式返回对应的合约详细信息。

#### 调用示例

请求：

```json
{
  "jsonrpc": "2.0",
  "method": "getcontractstate",
  "params": ["0100000000000000000000000000000000000000",1],
  "id": 1
}
```

响应：

```json
{
    "desc": "SUCCESS",
    "error": 0,
    "id": 1,
    "jsonrpc": "2.0",
    "result": {
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

## getmempooltxcount

获取内存中的交易的数量。

#### 调用示例

请求：

```json
{
  "jsonrpc": "2.0",
  "method": "getmempooltxcount",
  "params": [],
  "id": 1
}
```

响应：

```json
{
    "desc":"SUCCESS",
    "error":0,
    "jsonrpc": "2.0",
    "id": 1,
    "result": [100,50]
}
```

## getmempooltxstate

获取交易池（内存）中的交易的状态。

#### 参数说明

`tx_hash`：交易哈希值

#### 调用示例

请求：

```json
{
  "jsonrpc": "2.0",
  "method": "getmempooltxstate",
  "params": ["773dd2dae4a9c9275290f89b56e67d7363ea4826dfd4fc13cc01cf73a44b0d0e"],
  "id": 1
}
```

响应：

```json
{
    "desc":"SUCCESS",
    "error":0,
    "jsonrpc": "2.0",
    "id": 1,
    "result": {
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

## getsmartcodeevent

获取智能合约的执行结果。

#### 参数说明

`block_height` / `txHash`：区块高度 / 交易哈希值

#### 调用示例

请求：

```json
{
  "jsonrpc": "2.0",
  "method": "getsmartcodeevent",
  "params": [3],
  "id": 3
}
```

响应：

```json
{
  "desc":"SUCCESS",
  "error":0,
  "jsonrpc": "2.0",
  "id": 3,
  "result": [
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
        }
    ]
}
```

请求：

```json
{
  "jsonrpc": "2.0",
  "method": "getsmartcodeevent",
  "params": ["3ba4b4e463a717635614595378f2aac78feacc7d4dfda075bfcf9328cbbcdb7c"],
  "id": 3
}
```

响应：

```json
{
    "desc": "SUCCESS",
    "error": 0,
    "id": 1,
    "jsonrpc": "2.0",
    "result": {
             "TxHash": "20046da68ef6a91f6959caa798a5ac7660cc80cf4098921bc63604d93208a8ac",
             "State": 1,
             "GasConsumed": 0,
             "Notify": [
                    {
                      "ContractAddress": "ff00000000000000000000000000000000000001",
                      "States": [
                            "transfer",
                            "T9yD14Nj9j7xAB4dbGeiX9h8unkKHxuWwb",
                            "TA4WVfUB1ipHL8s3PRSYgeV1HhAU3KcKTq",
                            1000000000
                         ]
                     }
              ]
    }
}
```

响应结果中 `result` 字段所对应信息的含义如下表所示。

|    字段     |                     含义                     |
| :---------: | :------------------------------------------: |
|   TxHash    |                  交易哈希值                  |
|    State    | 交易的执行状态，0表示执行失败，1表示执行成功 |
| GasConsumed |              交易所消耗的手续费              |
|   Notify    |           交易所触发的合约事件列表           |

此外，`Notify` 字段所对应信息的含义如下表所示。

|      字段       |        含义        |
| :-------------: | :----------------: |
| ContractAddress | 事件所属的合约地址 |
|     States      |   事件的具体内容   |

> **注意**：
>
> - 如果参数是区块高度，返回执行结果的集合。
> - 如果是交易哈希，返回对应交易的执行结果。
>

## getblockheightbytxhash

得到该交易哈希所落账的区块的高度。

#### 参数说明

`txhash`: 交易哈希

#### 调用示例

请求：

```json
{
  "jsonrpc": "2.0",
  "method": "getblockheightbytxhash",
  "params": ["c453557af780fe403db6e954ebc9adeafd5818c596c6c60e5cc42851c5b41884"],
  "id": 1
}
```

响应：

```json
{
    "desc": "SUCCESS",
    "error": 0,
    "id": 1,
    "jsonrpc": "2.0",
    "result": 10
}
```

## getbalance

返回 base58 地址的余额

#### 参数说明

`address`: base58 地址

#### 调用示例

请求：

```json
{
  "jsonrpc": "2.0",
  "method": "getbalance",
  "params": ["TA5uYzLU2vBvvfCMxyV2sdzc9kPqJzGZWq"],
  "id": 1
}
```

响应：

```json
{
   "desc":"SUCCESS",
   "error":0,
   "id":1,
   "jsonrpc":"2.0",
   "result":{
        "ont": "2500",
        "ong": "0"
       }
}
```

## getmerkleproof

返回对应交易的 merkle 证明。

#### 参数定义

`hash`: 交易哈希

#### 调用示例

请求：

```json
{
  "jsonrpc": "2.0",
  "method": "getmerkleproof",
  "params": ["0087217323d87284d21c3539f216dd030bf9da480372456d1fa02eec74c3226d"],
  "id": 1
}
```

响应：

```json
{
   "desc":"SUCCESS",
   "error":0,
   "id":1,
   "jsonrpc":"2.0",
   "result":{
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
   }
}
```

## getgasprice

返回 GAS 价格。


#### 调用示例

请求：

```json
{
  "jsonrpc": "2.0",
  "method": "getgasprice",
  "params": [],
  "id": 1
}
```

响应：

```json
{
   "desc":"SUCCESS",
   "error":0,
   "id":1,
   "jsonrpc":"2.0",
   "result":{
        "gasprice": 0,
        "height": 1
       }
}
```

## getallowance

返回允许从 from 转出到 to 账户的额度。

#### 参数说明

- `asset`: "ont" 或者 "ong"
- `from`: 转出账户 base58 地址
- `to`: 转入账户 base58 地址

#### 调用示例

请求：

```json
{
  "jsonrpc": "2.0",
  "method": "getallowance",
  "params": ["ont","from address","to address"],
  "id": 1
}
```

响应：

```json
{
   "desc":"SUCCESS",
   "error":0,
   "id":1,
   "jsonrpc":"2.0",
   "result": "10"
}
```

## getunboundong

返回可以提取的ong。

#### 参数定义

`address`：提取 ong 的账户地址。

#### 调用示例

请求：

```json
{
  "jsonrpc": "2.0",
  "method": "getunboundong",
  "params": ["address"],
  "id": 1
}
```

响应：

```json
{
   "desc":"SUCCESS",
   "error":0,
   "id":1,
   "jsonrpc":"2.0",
   "result": "204957950400000"
}
```

## getblocktxsbyheight

返回该高度对应的区块落账的所有交易的哈希。

#### 参数说明

`height`：区块高度

#### 调用示例

请求：

```json
{
  "jsonrpc": "2.0",
  "method": "getblocktxsbyheight",
  "params": [100],
  "id": 1
}
```

响应：

```json
{
   "desc":"SUCCESS",
   "error":0,
   "id":1,
   "jsonrpc":"2.0",
   "result": {
        "Hash": "ea5e5219d2f1591f4feef89885c3f38c83d3a3474a5622cf8cd3de1b93849603",
        "Height": 100,
        "Transactions": [
            "37e017cb9de93aa93ef817e82c555812a0a6d5c3f7d6c521c7808a5a77fc93c7"
        ]
    }
}
```

## getnetworkid

获取 network id。

#### 调用示例

请求:

```json
{
  "jsonrpc": "2.0",
  "method": "getnetworkid",
  "params": [],
  "id": 3
}
```

响应:

```json
{
  "desc":"SUCCESS",
  "error":0,
  "jsonrpc": "2.0",
  "id": 3,
  "result": 1
}
```

## getgrantong

获取 grant ong.

#### 调用示例

请求：

```json
{
  "jsonrpc": "2.0",
  "method": "getgrantong",
  "params": ["AKDFapcoUhewN9Kaj6XhHusurfHzUiZqUA"],
  "id": 3
}
```

响应：

```json
{
  "desc":"SUCCESS",
  "error":0,
  "jsonrpc": "2.0",
  "id": 3,
  "result": 4995625
}
```
