

## 基础功能说明

对于 DAPP 开发者来说，需要基于本体链交互的功能大致有如下几种：

- [登录](登录) ：允许验证用户身份或直接查询账号或身份信息。

- [支付](支付) ： 通过调用智能合约处理交易中的支付业务，可以是 ```ONT/ONG``` 或其他 ```OEP``` 规范的通证。

- [智能合约开发](智能合约开发) ： 对于DApp而言，智能合约实现了其全部或部分业务逻辑。以游戏举例，可以实现购买，出售，租赁，或获取随机数等不同的业务及功能。详细业务逻辑参见智能合约。

- [资产上链（可选）](资产上链（可选）) ： 开发者可选择发布何种类型资产如 ```OEP4```，```OEP5```，```OEP8```。

对于不同情景下的开发者来说，可选择不同的接入方式进行DApp对接。我们提供了：

* 基于 ONT ID 开放平台的中心化方案
* 通过 DApi 接入的多个去中心化方案，包括在手机钱包内打开 DApp、或使用 Chrome 插件钱包等方法，允许 DApp 与链交互。
* 通过 SDK 接入的去中心化方案，比如基于 C# SDK 的 Unity 3D 游戏。

不同接入方式都可以实现登录，调用智能合约的功能，开发者可以选择其中一种进行 DApp 接入。本文针对来到本体公链开发DApp的开发者，提供了通用的DApp接入解决方案，让 DAPP 方可以快速将应用上链。

## 主要 DApp 功能介绍

DApp 与本体链产生交互时主要有以下功能：

### 登录

允许验证用户身份或直接查询账号/身份信息。

### 支付

通过调用智能合约实现 DApp 的支付功能。使用 ONG 支付的例子：

```
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

### 调用智能合约

对于DApp而言，智能合约实现了其全部或部分业务逻辑。以游戏举例，可以实现购买，出售，租赁，或获取随机数等不同的业务及功能。详细业务逻辑参见智能合约。

### 资产上链（可选）

资产上链并不是DApp开发必须的，但是有些DApp需要特定的链上资产来运行其内部逻辑。
根据对资产的需求不同，本体提供了OEP4，OEP5，OEP8这三种不同类型的链上资产类型。

[什么是OEP-4，OEP-5，OEP-8 ？](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/11-Q&A?id=_1-%E4%BB%80%E4%B9%88%E6%98%AFoep-4%EF%BC%8Coep-5%EF%BC%8Coep-8-%EF%BC%9F)

## 接入技术实现

为了实现上述的几种功能，我们提供了两种Dapp接入技术方案，两种接入方式都可以实现登录，调用智能合约等功能，开发者可以根据自身需求选择其中一种进行接入的开发

### ONT ID 开放平台（集成方案）


ONT ID 开放平台为第三方应用提供第三方登录、支付、智能合约执行、KYC等服务。

ONT ID 开放平台的优势在于，采用可信任的托管模式后，用户登录DApp将不再依赖于用户本地的钱包，大大扩展了DApp的使用范围。

- [ONT ID 开放平台集成](docs-cn/dApp-Integration/08-ontid_integration.md)

### DApi 集成（去中心化方案）


介绍了 DApp 如何在各种场景下调用 DApi，实现包括登录，调用智能合约等操作。

DApi 集成的优势在于，用户自己可以掌握自己所有的资产和信息，目前也可以较为便利地使用已经支持的钱包登录 DApp。

- [DApi 集成](docs-cn/dApp-Integration/09-dapi_integration.md)

### SDK 集成（去中心化方案）

介绍了 DApp 如何使用 SDK 实现与链交互，调用智能合约等操作。

- [Unity 3D 对接 C# SDK](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/12-unity_integration)
- [其他语言 SDK 使用](https://dev-docs.ont.io/#/docs-cn/SDKs/00-overview)