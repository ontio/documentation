

<!-- TOC -->

- [简介](#简介)
- [准备](#准备)
- [接口](#接口)
    - [Network](#network)
    - [Wallet](#wallet)
    - [Identity](#identity)
    - [IdentityManager](#identitymanager)
    - [ABI](#abi)
    - [Utils](#utils)
- [参与项目](#参与项目)
- [命名规范](#命名规范)
    - [概述](#概述)
    - [应该避免的名称](#应该避免的名称)
    - [命名约定](#命名约定)
    - [Python之父Guido推荐的规范](#python之父guido推荐的规范)
- [官网](#官网)
- [许可证](#许可证)

<!-- /TOC -->



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

**注意**：该包**尚未**经过安全审计，可能存在潜在的安全隐患。在生产环境中使用之前，务必采取诸如正确清理内存、安全存储私钥、测试交易接发功能的正确性等预防措施！


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

**注意**：该包**尚未**经过安全审计，可能存在潜在的安全隐患。在生产环境中使用之前，务必采取诸如正确清理内存、安全存储私钥、测试交易接发功能的正确性等预防措施！


### IdentityManager

This is an API set that allows you to manage your multiple identity in an wallet file.

|       | Main Function                      |
| :---: | :--------------------------------- |
| 1     | create_identity()                  |
| 2     | import_identity()                  |
| 3     | create_identity_from_private_key() |

**注意**：该包**尚未**经过安全审计，可能存在潜在的安全隐患。在生产环境中使用之前，务必采取诸如正确清理内存、安全存储私钥、测试交易接发功能的正确性等预防措施！


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

**注意**：该包**尚未**经过安全审计，可能存在潜在的安全隐患。在生产环境中使用之前，务必采取诸如正确清理内存、安全存储私钥、测试交易接发功能的正确性等预防措施！

### Utils

`Utils`包为`Ontology Dapps`和其他`Ontology-Python-Sdk`包提供工具类方法。

|       | Main Function       |
| :---: | :------------------ |
| 1     | get_random_hex_str()    |
| 2     | get_asset_address() |
| 3     | get_random_bytes()  |

## 参与项目

我可以为Ontology项目做贡献吗？

当然可以！请发起一个带有打开带有签名提交的拉取请求。我们非常感谢你您的帮助！

你还可以将补丁通过电子邮件的方式发送到开发人员邮件列表。请加入Ontology邮件列表或论坛，与我们讨论。

无论哪种方式，如果您不签署补丁，我们将不接受。这意味着在每次提交结束时添加一行`Signed-off-by：Name <email>`，表示你编写了代码并将其作为开源补丁传递。

另外，请写好git提交消息。一个好的提交消息如下所示：

标题行：在一行中解释提交（使用命令）

提交消息的主体是几行文本，更详细地解释事情，可能提供有关修复问题的一些背景等。

提交消息的主体可以是几个段落，请做正确的自动换行并保持列短于约74个字符左右。这样`git log`即使缩进也能很好地显示出来。

确保解释清楚你的解决方案以及为什么你正在做你正在做的事情，而不是描述你正在做的事情。审稿人和您未来的自己可以阅读补丁，但可能无法理解为什么要实施特定的解决方案。

> Reported-by: whoever-reported-it

> Signed-off-by: Your Name <youremail@yourhost.com>

## 命名规范

如果您想贡献，我们强烈建议您阅读 [Google Python Style Guide](https://github.com/google/styleguide/blob/gh-pages/pyguide.md).

### 概述

`module_name`,
`package_name`,
`ClassName`,
`method_name`,
`ExceptionName`,
`function_name`,
`GLOBAL_CONSTANT_NAME`,
`global_var_name`,
`instance_var_name`,
`function_parameter_name`,
`local_var_name`.

函数名，变量名和文件名应该是描述性的，如`eschew`这样的命名就是缩写。特别地，**不要使用项目之外的读者不明确或不熟悉的缩写**，也**不要通过删除单词中的字母来缩写**。

始终使用`.py`文件扩展名。

切勿使用短划线。

### 应该避免的名称

- 单字符名称, 除了计数器和迭代器。
- 包/模块名中的连字符（-）。
- 双下划线开头并结尾的名称（Python保留, 例如__init__）。

### 命名约定

- 所谓“`Internal`”表示仅模块内可用。或者, 在类内是保护或私有的.
- 用单下划线(`_`)开头表示模块变量或函数是`protected`的（使用`import * from`时不会包含）.
- 用双下划线(__)开头的实例变量或方法表示类内私有.
- 将相关的类和顶级函数放在同一个模块里。不像`Java`, 没必要限制一个类一个模块。
- 对类名使用大写字母开头的单词（如`CapWords`, 即`Pascal`风格）, 但是模块名应该用小写加下划线的方式(如`lower_with_under.py`)。尽管已经有很多现存的模块使用类似于`CapWords.py`这样的命名, 但现在已经不鼓励这样做, 因为如果模块名碰巧和类名一致, 这会让人困扰。


## 官网

* https://ont.io/

## 许可证

所有Ontology的库（即cmd目录之外的所有代码）遵循GNU Lesser General Public License v3.0许可，该许可证文件也包含在我们的存储库中。
