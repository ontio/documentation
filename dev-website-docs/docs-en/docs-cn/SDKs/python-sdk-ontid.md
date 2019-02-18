
## 简介

Ontology-Python-SDK是一个基于`Python3.6`实现的综合性SDK。目前，它支持本地钱包管理、数字身份管理、数字资产管理、智能合约的部署和调用、OEP4智能合约的调用以及与Ontology区块链的通信。并且，未来它还将支持更多功能和应用。

## 准备

安装需要`Python 3.6`或更高版本的环境。

```bash
pip install ontology-python-sdk
```

## 接口

更多信息可浏览[Ontology-Python-SDK API 文档](https://apidoc.ont.io/pythonsdk/).

### Network

这是一个用于与Ontology节点进行交互的API集合。

|       | Main Function                         |
| :---: | :------------------------------------ |
| 1     | get_version()                         |
| 2     | get_balance()                         |
| 3     | get_allowance()                       |
| 4     | get_gas_price()                       |
| 5     | get_network_id()                      |
| 6     | get_node_count()                      |
| 7     | get_block_count()                     |
| 8     | get_block_by_hash()                   |
| 9     | get_block_by_height()                 |
| 10    | get_current_block_hash()              |
| 11    | get_block_hash_by_height()            |
| 12    | get_storage()                         |
| 13    | get_smart_contract()                  |
| 14    | get_smart_contract_event_by_tx_hash() |
| 15    | get_smart_contract_event_by_height()  |

### Wallet

这是一个用于操作钱包账户（以`AccountData`的形式）的API集合。

|       | Main Function    |
| :---: | :--------------- |
| 1     | add_account()    |
| 2     | remove_account() |

!> 该包**尚未**经过安全审计，可能存在潜在的安全隐患。在生产环境中使用之前，务必采取诸如正确清理内存、安全存储私钥、测试交易接发功能的正确性等预防措施！


### Identity

This is an API set that allows you to generate **Ontology Digital Identity.**

|       | Main Function                        |
| :---: | :----------------------------------- |
| 1     | parse_ddo()                          |
| 2     | send_get_ddo()                       |
| 3     | new_get_ddo_transaction()            |
| 4     | new_add_recovery_transaction()       |
| 5     | new_add_attribute_transaction()      |
| 6     | new_add_public_key_transaction()     |
| 7     | new_remove_public_key_transaction()  |
| 8     | new_registry_ont_id_transaction()    |
| 9     | new_remove_attribute_transaction()   |
| 10    | send_add_recovery_transaction()      |
| 11    | send_add_attribute_transaction()     |
| 12    | send_add_public_key_transaction()    |
| 13    | send_registry_ont_id_transaction()   |
| 14    | send_remove_public_key_transaction() |
| 15    | send_remove_attribute_transaction()  |
| 16    | send_add_public_key_by_recovery()    |
| 17    | sign_transaction()                   |
| 18    | add_sign_transaction()               |
| 19    | add_multi_sign_transaction()         |
| 20    | get_merkle_proof()                   |
| 21    | get_raw_transaction()                |
| 22    | send_raw_transaction()               |
| 23    | send_raw_transaction_pre_exec()      |

!> 该包**尚未**经过安全审计，可能存在潜在的安全隐患。在生产环境中使用之前，务必采取诸如正确清理内存、安全存储私钥、测试交易接发功能的正确性等预防措施！


### IdentityManager

This is an API set that allows you to manage your multiple identity in an wallet file.

|       | Main Function                      |
| :---: | :--------------------------------- |
| 1     | create_identity()                  |
| 2     | import_identity()                  |
| 3     | create_identity_from_private_key() |

!> 该包**尚未**经过安全审计，可能存在潜在的安全隐患。在生产环境中使用之前，务必采取诸如正确清理内存、安全存储私钥、测试交易接发功能的正确性等预防措施！


### ABI

`ABI`包使你能够轻松地与已经部署的智能合约进行交互。

|       | Main Function      |
| :---: | :----------------- |
| 1     | get_function]()    |
| 2     | get_parameter()    |
| 3     | set_params_value() |

### OEP4

`OEP4`包使你能够轻松地与已经部署的Ontology OEP4智能合约进行交互。

|       | Main Function      |
| :---: | :----------------- |
| 1     | init()             |
| 2     | get_name()         |
| 3     | get_symbol()       |
| 4     | get_decimal()      |
| 5     | get_total_supply() |
| 6     | approve()          |
| 7     | allowance()        |
| 8     | balance_of()       |
| 9     | transfer()         |
| 10    | transfer_multi()   |
| 11    | transfer_from()    |

!> 该包**尚未**经过安全审计，可能存在潜在的安全隐患。在生产环境中使用之前，务必采取诸如正确清理内存、安全存储私钥、测试交易接发功能的正确性等预防措施！

### Utils

`Utils`包为`Ontology Dapps`和其他`Ontology-Python-Sdk`包提供工具类方法。

|       | Main Function       |
| :---: | :------------------ |
| 1     | get_random_hex_str()    |
| 2     | get_asset_address() |
| 3     | get_random_bytes()  |
