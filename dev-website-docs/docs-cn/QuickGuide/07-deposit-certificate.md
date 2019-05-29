
## 概述

某些特定类型的DApp可能有往链上存取数据的需求，本文档介绍了如何在链上进行数据存取操作。

链上数据的存储主要在于通过智能合约进行操作，以下是一个智能合约的例子,请在 Smartx 中调试，请参考 [调试指南](https://dev-docs.ont.io/#/docs-cn/QuickGuide/00-dapp_development?id=%E5%9C%A8-smartx-%E4%B8%AD%E5%88%9B%E5%BB%BA%EF%BC%8C%E7%BC%96%E8%AF%91%E5%92%8C%E9%83%A8%E7%BD%B2%E6%99%BA%E8%83%BD%E5%90%88%E7%BA%A6%E5%88%B0%E7%A7%81%E6%9C%89%E9%93%BE)

```
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
