

* Native 合约 API： 有关本体网络中使用的 ```Native``` 合约 API，请参考 [Native Contract API](https://github.com/ontio/ontology/blob/master/docs/specifications/native_contract/paramapi.md)。
* Python 合约 API： 有关本体网络中使用的 ```Python``` 合约 ```API``` 和示例，请参考 [API doc](https://apidoc.ont.io/smartcontract/)。


为了方便开发者快速开始智能合约编写，我们提供了众多实用的合约模板。我们推出了 1.0 和 2.0 两个版本的编译器，今后将以 2.0 作为主流，请各位优先参考 2.0 版本的模板。

### 基础合约模板

ONG 转账 和存储是合约里较基础的功能。

#### 合约里支持 ONG 转账

```python
OntCversion = '2.0.0'
from ontology.interop.Ontology.Native import Invoke
from ontology.builtins import state
from ontology.interop.System.Runtime import Notify
from ontology.interop.System.ExecutionEngine import GetExecutingScriptHash
from ontology.interop.Ontology.Runtime import Base58ToAddress,AddressToBase58


# ONG Big endian Script Hash: 0x0200000000000000000000000000000000000000
OngContract = Base58ToAddress("AFmseVrdL9f9oyCzZefL9tG6UbvhfRZMHJ")


def Main(operation, args):
    if operation == "transferOng":
        if len(args) != 3:
            return False
        return transferOng(args[0], args[1], args[2])

    return False

def transferOng(from_base58, to_base58,  ong_amount):
    from_acct = Base58ToAddress(from_base58)
    to_acct = Base58ToAddress(to_base58)
    param = state(from_acct, to_acct, ong_amount)
    res = Invoke(0, OngContract, "transfer", [param])
    if res and res == b'\x01':
        Notify([True,from_base58, to_base58,  ong_amount])
        return True
    else:
        Notify([False,from_base58, to_base58,  ong_amount])
        return False
```

#### 链上数据的存储

某些特定类型的 ```DAPP``` 可能有往链上存取数据的需求，本文档介绍了如何在链上进行数据存取操作。

链上数据的存储主要在于通过智能合约进行操作，以下是一个智能合约的例子,请在 ```SmartX``` 中调试，请参考 [调试指南](https://dev-docs.ont.io/#/docs-cn/QuickGuide/00-dapp_development?id=%E5%9C%A8-smartx-%E4%B8%AD%E5%88%9B%E5%BB%BA%EF%BC%8C%E7%BC%96%E8%AF%91%E5%92%8C%E9%83%A8%E7%BD%B2%E6%99%BA%E8%83%BD%E5%90%88%E7%BA%A6%E5%88%B0%E7%A7%81%E6%9C%89%E9%93%BE)

```python
OntCversion = '2.0.0'
"""
Contract Record
"""
from ontology.interop.System.Storage import GetContext, Get, Put
from ontology.interop.System.Runtime import CheckWitness, Notify
from ontology.interop.Ontology.Runtime import Base58ToAddress

# set the owner codeAddr to your base58 codeAddr (starting with a captical A)
Owner = Base58ToAddress('APa7uMYqdqpFK2chwwmeE7SrQAWZukuGbX')

def Main(operation, args):
    if operation == "putRecord":
        assert (len(args) == 2)
        key = args[0]
        value = args[1]
        return putRecord(key, value)
    if operation == "getRecord":
        assert (len(args) == 1)
        key = args[0]
        return getRecord(key)
    return False


def putRecord(key, value):
    assert (_isOwner())
    Put(GetContext(), key, value)
    Notify(["putRecord", key, value])
    return True

def getRecord(key):
    return Get(GetContext(), key)

def _isOwner():
    return CheckWitness(Owner)
```


### 编译器 2.0 的合约模板

| # | 智能合约                         |        语言      |   描述   |
| -----| ---------------------------------------- | ---------------- | ---------------- |
| 1| [Oep4](https://github.com/ONT-Avocados/python-template/blob/master/OEP4Sample/OEP4Sample_compiler2.0.py) |    Python     |    Oep4  |
| 2| [Oep5](https://github.com/ONT-Avocados/python-template/blob/master/OEP5Sample/OEP5Sample_compiler2.0.py) |  Python   |  Oep5   |
| 3| [Oep8](https://github.com/ONT-Avocados/python-template/blob/master/OEP8Sample/OEP8Sample_compiler2.0.py) |  Python   |  Oep8   |
| 4| [Invoke Oep4](https://github.com/ONT-Avocados/python-template/blob/master/Static_Call_Oep4/static_call_Oep4_compiler2.0.py) |  Python  | 在智能合约中调用 Oep4 方法 |
| 5| [Storage example](https://github.com/ONT-Avocados/python-template/blob/master/Storage_Example/storage_example_compiler2.0.py) |   Python  |   Storage 示例  |
| 6| [Struct example](https://github.com/ONT-Avocados/python-template/blob/master/Struct_Example/struct_example_compiler2.0.py) |   Python  | Struct 示例  |
| 7| [Invoke native in sc](https://github.com/ONT-Avocados/python-template/blob/master/NativeAssetInvoke/native_asset_invoke_compiler2.0.py) | Python | 在智能合约中调用 native |
| 8| [Migrate Contract](https://github.com/ONT-Avocados/python-template/blob/master/MigrateDestruct/migrate_destroyWithinContract_compiler2.0.py) | Python | 迁移合约 |
| 9| [Event test](https://github.com/ONT-Avocados/python-template/blob/master/EventTest/event_test_compiler2.0.py) | Python|   Event 测试  |
|10| [Smart contract libs](https://github.com/ONT-Avocados/python-template/tree/master/libs) | Python|  合约 libs    |

> 2.0编译版本中，`from boa.builtins import concat,ToScriptHash` 由于方法重复已经被取消，请使用`from ontology.interop.Ontology.Runtime import Base58ToAddress`

### 编译器 1.0 的合约模板

| # | 智能合约                         |        语言      |   描述   |
| -----| ---------------------------------------- | ---------------- | ---------------- |
| 1| [Oep4](https://github.com/ONT-Avocados/python-template/blob/master/OEP4Sample/OEP4Sample.py) |    Python     |    Oep4  |
| 2| [Oep5](https://github.com/ONT-Avocados/python-template/blob/master/OEP5Sample/OEP5Sample.py) |  Python   |  Oep5   |
| 3| [Oep8](https://github.com/ONT-Avocados/python-template/blob/master/OEP8Sample/OEP8Sample.py) |  Python   |  Oep8   |
| 4| [Invoke Oep4](https://github.com/ONT-Avocados/python-template/blob/master/Static_Call_Oep4/static_call_Oep4.py) |  Python  | 在智能合约中调用 Oep4 方法 |
| 5| [Storage example](https://github.com/ONT-Avocados/python-template/blob/master/Storage_Example/storage_example.py) |   Python  |   Storage 示例  |
| 6| [Struct example](https://github.com/ONT-Avocados/python-template/blob/master/Struct_Example/struct_example.py) |   Python  | Struct 示例  |
| 7| [Invoke native in sc](https://github.com/ONT-Avocados/python-template/blob/master/NativeAssetInvoke/native_asset_invoke.py) | Python | 在智能合约中调用 native |
| 8| [Migrate Contract](https://github.com/ONT-Avocados/python-template/blob/master/MigrateDestruct/migrate_destroyWithinContract.py) | Python | 迁移合约 |
| 9| [Event test](https://github.com/ONT-Avocados/python-template/blob/master/EventTest/event_test.py) | Python|   Event 测试  |
|10| [Smart contract libs](https://github.com/ONT-Avocados/python-template/tree/master/libs) | Python|  合约 libs    |

> 在主网发行合约后如果需要在浏览器中显示，请提交 [申请表](https://docs.google.com/forms/d/e/1FAIpQLSdszQp1BbviS83psIZUZYMKoNkn0e4zcYxrVqM6v5Qbmzby3g/viewform?vc=0&c=0&w=1)
>
> 在测试网发行合约后如果需要在浏览器中显示，请发邮件到 sulingxiao@onchain.com

### 项目

| # | 智能合约                             |        语言      |   描述   |
| -----| ---------------------------------------- | ---------------- | ---------------- |
| 1| [Spokkz](https://github.com/Spuul/spokkz-ontology-smart-contracts/blob/master/contracts/contracts/SpokkzCoin.py) |    Python     |      |
| 2| [Muzika](https://github.com/MuzikaFoundation/ontology-smart-contract/blob/master/contracts/contracts/MuzikaCoin.py) |    Python     |      |
| 3| [Pumpkin](https://github.com/skyinglyh1/CollectPumpkin/blob/master/collectPumpkin.py) |    Python     |      |
