
## 简介

本体团队的官方 Python SDK 基于 Python 3.6 实现。目前，它支持钱包文件管理、数字身份管理、数字资产管理、智能合约的部署和调用、以及与本体区块链网络的通信。

## 快速开始

安装需要 `Python 3.6` 或更高版本的环境。

```shell
pip install ontology-python-sdk
```

## 接口

这里以列表的形式列出所支持的接口，更详细的信息可以点击[这里](https://apidoc.ont.io/pythonsdk/)访问我们的 API 文档。

### Network

这是一个用于与本体网络进行交互的API集合。

|       | Main Function                         |
| :---: | :------------------------------------ |
|   1   | get_version()                         |
|   2   | get_balance()                         |
|   3   | get_allowance()                       |
|   4   | get_gas_price()                       |
|   5   | get_network_id()                      |
|   6   | get_node_count()                      |
|   7   | get_block_count()                     |
|   8   | get_block_height()                    |
|   9   | get_block_by_hash()                   |
|  10   | get_block_by_height()                 |
|  11   | get_current_block_hash()              |
|  12   | get_block_hash_by_height()            |
|  13   | get_storage()                         |
|  14   | get_smart_contract()                  |
|  15   | get_smart_contract_event_by_tx_hash() |
|  16   | get_smart_contract_event_by_height()  |

### Wallet

这是一个用于操作钱包账户（以`AccountData`的形式）的API集合。

|       | Main Function    |
| :---: | :--------------- |
|   1   | add_account()    |
|   2   | remove_account() |

**注意**：该包**尚未**经过安全审计，可能存在潜在的安全隐患。在生产环境中使用之前，务必采取诸如正确清理内存、安全存储私钥、测试交易接发功能的正确性等预防措施！

### Account

这是一个
This is an API set that allows you to generate Ontology accounts and sign transactions and data.

|       | Main Function                      |
| :---: | :--------------------------------- |
|   1   | export_wif()                       |
|   2   | get_signature_scheme()             |
|   3   | get_public_key_bytes()             |
|   4   | get_private_key_bytes()            |
|   5   | get_public_key_hex()               |
|   6   | get_public_key_bytes()             |
|   7   | get_private_key_from_wif()         |
|   8   | get_gcm_decoded_private_key()      |
|   9   | export_gcm_encrypted_private_key() |
|  10   | get_address_hex()                  |
|  11   | get_address_hex_reverse()          |
|  12   | get_address_base58()               |
|  13   | generate_signature()               |

**注意**：该包**尚未**经过安全审计，可能存在潜在的安全隐患。在生产环境中使用之前，务必采取诸如正确清理内存、安全存储私钥、测试交易接发功能的正确性等预防措施！

### Identity

This is an API set that allows you to generate **Ontology Digital Identity.**

|       | Main Function                        |
| :---: | :----------------------------------- |
|   1   | parse_ddo()                          |
|   2   | send_get_ddo()                       |
|   3   | new_get_ddo_transaction()            |
|   4   | new_add_recovery_transaction()       |
|   5   | new_add_attribute_transaction()      |
|   6   | new_add_public_key_transaction()     |
|   7   | new_remove_public_key_transaction()  |
|   8   | new_registry_ont_id_transaction()    |
|   9   | new_remove_attribute_transaction()   |
|  10   | send_add_recovery_transaction()      |
|  11   | send_add_attribute_transaction()     |
|  12   | send_add_public_key_transaction()    |
|  13   | send_registry_ont_id_transaction()   |
|  14   | remove_public_key() |
|  15   | send_remove_attribute_transaction()  |
|  16   | send_add_public_key_by_recovery()    |
|  17   | sign_transaction()                   |
|  18   | add_sign_transaction()               |
|  19   | add_multi_sign_transaction()         |
|  20   | get_merkle_proof()                   |
|  21   | get_transaction_by_tx_hash()         |
|  22   | send_raw_transaction()               |
|  23   | send_raw_transaction_pre_exec()      |

**注意**：该包**尚未**经过安全审计，可能存在潜在的安全隐患。在生产环境中使用之前，务必采取诸如正确清理内存、安全存储私钥、测试交易接发功能的正确性等预防措施！

### AccountManager

This is an API set that allows you to manage your multiple account in an wallet file.

|       | Main Function                     |
| :---: | :-------------------------------- |
|   1   | import_account()                  |
|   2   | create_account()                  |
|   3   | create_account_from_private_key() |
|   4   | get_account()                     |
|   5   | get_accounts()                    |
|   6   | get_default_account()             |
|   7   | get_default_account_address()     |
|   8   | set_default_account_by_index()    |
|   9   | set_default_account_by_address()  |

**注意**：该包**尚未**经过安全审计，可能存在潜在的安全隐患。在生产环境中使用之前，务必采取诸如正确清理内存、安全存储私钥、测试交易接发功能的正确性等预防措施！

### IdentityManager

This is an API set that allows you to manage your multiple identity in an wallet file.

|       | Main Function                      |
| :---: | :--------------------------------- |
|   1   | create_identity()                  |
|   2   | import_identity()                  |
|   3   | create_identity_from_private_key() |

**注意**：该包**尚未**经过安全审计，可能存在潜在的安全隐患。在生产环境中使用之前，务必采取诸如正确清理内存、安全存储私钥、测试交易接发功能的正确性等预防措施！

### Asset

`Asset`包使你能够容易地处理Ontology原生数字资产（ONT，ONG）。

|       | Main Function                   |
| :---: | :------------------------------ |
|   1   | query_name()                    |
|   2   | query_symbol()                  |
|   3   | query_balance()                 |
|   4   | query_decimals()                |
|   5   | query_allowance()               |
|   6   | query_unbound_ong()             |
|   7   | get_asset_address()             |
|   8   | new_approve_transaction()       |
|   9   | new_transfer_transaction()      |
|  10   | new_transfer_from_transaction() |
|  11   | new_withdraw_ong_transaction()  |
|  12   | send_transfer()                 |
|  13   | send_approve()                  |
|  14   | send_transfer_from()            |
|  15   | send_withdraw_ong_transaction() |

### ABI

`ABI`包使你能够轻松地与已经部署的智能合约进行交互。

|       | Main Function      |
| :---: | :----------------- |
|   1   | get_function]()    |
|   2   | get_parameter()    |
|   3   | set_params_value() |

### OEP4

`OEP4`包使你能够轻松地与已经部署的Ontology OEP4智能合约进行交互。

|       | Main Function      |
| :---: | :----------------- |
|   1   | init()             |
|   2   | get_name()         |
|   3   | get_symbol()       |
|   4   | get_decimal()      |
|   5   | get_total_supply() |
|   6   | approve()          |
|   7   | allowance()        |
|   8   | balance_of()       |
|   9   | transfer()         |
|  10   | transfer_multi()   |
|  11   | transfer_from()    |

**注意**：该包**尚未**经过安全审计，可能存在潜在的安全隐患。在生产环境中使用之前，务必采取诸如正确清理内存、安全存储私钥、测试交易接发功能的正确性等预防措施！

### Utils

`Utils`包为`Ontology Dapps`和其他`Ontology-Python-Sdk`包提供工具类方法。

|       | Main Function        |
| :---: | :------------------- |
|   1   | get_random_hex_str() |
|   2   | get_asset_address()  |
|   3   | get_random_bytes()   |

### 签名机

在使用签名机对交易进行签名时，其流程如下。

1. SDK 构造交易，将序列化后的交易发送给签名机。
2. 签名机收到交易，将交易反序列化。
3. 签名机完成交易的检查后，添加签名并发送交易。

<section class = "warning">
在使用签名机之前，请确保已经启动了签名机服务。
  <ul>
    <li>运行 go 程序。</li>
    <pre v-pre="" data-lang="shell"><code class="lang-shell">go run .\sigsvr.go</code></pre>
    <li>运行编译后的二进制应用程序。</li>
    <pre v-pre="" data-lang="shell"><code class="lang-shell">.\sigsvr</code></pre>
  </ul>
</section>

#### 连接签名机

```python
from ontology.ont_sdk import OntologySdk

sdk = OntologySdk()
sdk.service.sig_svr.connect_to_localhost()
```

#### 创建账户

```python
sdk.service.sig_svr.create_account('password')
```

#### 导出账户

```python
sdk.service.sig_svr.export_account()
```

#### 数据签名

```python
msg = '48656c6c6f2c20776f726c64'
b58_address = 'Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT'
sdk.service.sig_svr.sig_data(msg, b58_address, 'password')
```
