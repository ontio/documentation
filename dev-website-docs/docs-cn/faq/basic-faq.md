

## 测试网币申请

ONT/ONG 申请链接： [https://developer.ont.io/applyOng](https://developer.ont.io/applyOng) 

OEP4/OEP5/OEP8 币申请： 联系对接人员，或根据[合约模板](https://dev-docs.ont.io/#/docs-cn/smartcontract/02-template)自己部署合约测试。


## 公共节点地址

polaris 测试网节点: http://polaris1.ont.io, http://polaris2.ont.io, http://polaris3.ont.io, http://polaris4.ont.io, http://polaris5.ont.io

主网节点: http://dappnode1.ont.io, http://dappnode2.ont.io, http://dappnode3.ont.io, http://dappnode4.ont.io


## 浏览器

浏览器地址：[https://explorer.ont.io/](https://explorer.ont.io/)

浏览器 API ：[https://dev-docs.ont.io/#/docs-cn/explorer/overview](https://dev-docs.ont.io/#/docs-cn/explorer/overview)

浏览器 API 功能：根据地址查余额和交易记录，查所合约信息，根据合约地址查交易记录，查询统计数据等。

## ONG 的解绑规则是什么
可提取的ong数量 = 每秒解绑ong的数量 × ont的持有时间 × 持有ont的数量 / ont的总量

每秒解绑ong的数量：按照 [5, 4, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] 逐年递减

ont的持有时间：当前时间 - 上次ont变动时间

ont总量：10亿

例如：账户A 第一天持有100个ont，第二天持有200个ont，第三天持有300个ont，可提取的ong数量为：

（24×60×60)×5×100/1000000000 + （24×60×60)×5×200/1000000000 

之后300个ont可提取的ong在下次账户变动时结算。

初次做token swap时，上次ont变动时间为2018.6.30  ontology主网上线时间。

## 关于 ONT 和 ONG 精度问题

ONT为实际数量，不可分割。ONG精度为9，可分割。交易手续费使用ONG支付


## 转账手续费是什么

ontology网络每次转账需要消耗ONG(gas)，在主网需要500+的gasprice的指定才会打包

```gasprice * gaslimit = ong  cost```

gaslimit的最低值是20000，gasprice的最低值是500，一般的交易情况都为最低值，也就是0.01个ONG。如果合约过于复杂，gaslimit的值可能会超过20000的最低值，gasprice为用户自己设定，但不能低于最低。


## 签名机

提供私钥托管的服务，可以通过简单 API， 支持：创建账户，导出钱包，构造交易，交易签名，多签地址签名等。

## 钱包

Chrome 插件钱包： [https://dev-docs.ont.io/#/docs-cn/cyano/01-chrome-wallet](https://dev-docs.ont.io/#/docs-cn/cyano/01-chrome-wallet)

移动端钱包 ONTO ： [https://onto.app](https://onto.app) 

移动端钱包 Cyano（测试版）：[http://101.132.193.149/files/app-debug.apk](http://101.132.193.149/files/app-debug.apk) ， [源码](https://github.com/ontio-cyano)

桌面钱包 Owallet ：[https://github.com/ontio/OWallet/releases](https://github.com/ontio/OWallet/releases)

其他支持本体的钱包：目前大约支持20款钱包

## DAPP 相关

已经上线的 DAPP： [https://dapp.ont.io/](https://dapp.ont.io/)

DAPP 激励计划 ： [https://dapp.ont.io/support](https://dapp.ont.io/support)

开发指导： [https://dev-docs.ont.io/#/docs-cn/QuickGuide/00-dapp_development](https://dev-docs.ont.io/#/docs-cn/QuickGuide/00-dapp_development)


## API 接口

1. 节点接口： [RPC、Restful、Websocket](https://dev-docs.ont.io/#/docs-cn/ontology-cli/04-interface-specification)
2. 浏览器 API ：[https://dev-docs.ont.io/#/docs-cn/explorer/overview](https://dev-docs.ont.io/#/docs-cn/explorer/overview)

查询合约事件：[https://dev-docs.ont.io/#/docs-cn/ontology-cli/06-restful-specification?id=getsmtcode_evts](https://dev-docs.ont.io/#/docs-cn/ontology-cli/06-restful-specification?id=getsmtcode_evts)

## dAPI 使用

这个链接里有dAPI对接文档，测试钱包，演示DAPP。[https://github.com/ontio-cyano/integration-docs/blob/master/README_CN.md](https://github.com/ontio-cyano/integration-docs/blob/master/README_CN.md)

如何调用 dAPI 参考 [https://github.com/ontio-cyano/dapi-universal/blob/master/DApiUtil.tsx](https://github.com/ontio-cyano/dapi-universal/blob/master/DApiUtil.tsx)

## 如何创建地址？

通过私钥创建账户，账户的公钥计算出地址，地址是 Base58 格式。合约的地址是 Hex 格式，它跟 Base58 可以互转。
```java
com.github.ontio.account.Account acct2 = new com.github.ontio.account.Account(Helper.hexToBytes(privKey),ontSdk.defaultSignScheme);
System.out.println(acct2.getAddressU160().toBase58());

```

## 如何计算一个交易的手续费？如何查询一笔交易的手续费？

GAS price 是给执行 opcode 定价，执行 opcode 步数等于 GAS limit，交易手续费 = GAS Price * GAS limit 。

预执行，返回的数据如下：
```json
{
	"Notify": [{
		"States": ["transfer", "AQmTJnojgMJXTWDE8rL5R5SRKLHr9TZmPR", "AazEvfQPcQ2GEFFPLF1ZLwQ7K5jDn81hve", 10],
		"ContractAddress": "0200000000000000000000000000000000000000"
	}],
	"State": 1,
	"Gas": 20000,
	"Result": "01"
}

```
其中```Gas``` 就是该交易需要花费的 gasLimit，GAS price 目前固定值是 500。在主网上花费的手续费是500 * 20000 = 0.01 ONG。

执行交易返回的结果：
```json
{
    "Action": "getsmartcodeeventbyhash",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": {
        "TxHash": "c843a017f5630d9b874fba968574dbb91d4d65058efc3a094587fa5a50f9fc00",
        "State": 1,  //执行成功
        "GasConsumed": 10000000, //gas消耗
        "Notify": [
            {
                "ContractAddress": "0200000000000000000000000000000000000000", //转账的合约地址
                "States": [
                    "transfer",
                    "AQmTJnojgMJXTWDE8rL5R5SRKLHr9TZmPR",
                    "AazEvfQPcQ2GEFFPLF1ZLwQ7K5jDn81hve",
                    10
                ]
            },
            {   //付手续费的合约事件
                "ContractAddress": "0200000000000000000000000000000000000000",  // ONG 合约
                "States": [
                    "transfer",
                    "AQmTJnojgMJXTWDE8rL5R5SRKLHr9TZmPR",   //付款人 payer的地址
                    "AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK",  //手续费付给生态治理的统一收款地址
                    10000000
                ]
            }
        ]
    },
    "Version": "1.0.0"
}

```


## 获取交易池交易数量的返回信息，这种情况怎么区分转账是否成功呢？


GET http://dappnode1.ont.io:20334/api/v1/mempool/txcount

```json

{
    "Action": "getmempooltxcount",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": [
        6, //已验证通过的交易数
        2  //未开始验证的交易数
    ],
    "Version": "1.0.0"
}

```
交易池中还未落账的交易总数 = 已验证 + 未验证。通过查询 Hash 查询交易或查询合约事件能查到信息说明转账成功。一般发交易后2 - 20秒之前会落账。


## 什么是助记词？

助记词是私钥的另一种表现形式。最早是由 BIP39 提案提出, 其目的是为了帮助用户记忆复杂的私钥字符串。助记词一般由12、15、18、21个单词构成, 这些单词都取自一个固定词库, 其生成顺序也是按照一定算法而来。

任何人得到了你的助记词, 在钱包中输入助记词并设置一个密码（不用输入原密码），就能进入钱包并拥有这个钱包的掌控权，可以轻而易举地夺走你的数字资产。

所以在创建钱包后，一定要完成助记词备份，而且助记词只能备份一次，备份后，在钱包中再也不会显示，牢记在备份时一定要抄写下来，保存好！

## 什么是Keystore?

Keystore是允许你以加密的方式存储私钥。你自定义的密码加密私钥，起到了对ONT ID和钱包的保护作用。

一定要记住Keystore 的密码, 一旦忘记密码, 你就会失去了Keystore 的使用权, 同时ONTO无法帮你找回密码。

因此一定要妥善保管好 Keystore 以及密码。


##  什么是明文私钥？什么是WIF私钥？
         
明文私钥是随机生成的，用来解锁对应钱包的一串字符。交易场景下, 私钥用于生成交易所必须的签名，以证明资产的所有权。任何人得到了你的明文私钥, 在钱包中输入明文私钥并设置一个密码（不用输入原密码），就能进入钱包并拥有这个钱包的掌控权，可以轻而易举地夺走你的数字资产。因此，妥善保存好你的明文私钥。

WIF（Wallet Import Format）是将明文私钥以Base58校验和编码格式显示的钱包导入格式。WIF和私钥可以互转，因此也理解为是另一种形式的明文私钥。任何人得到了你的WIF, 在钱包中输入WIF并设置一个密码（不用输入原密码），就能进入钱包并拥有这个钱包的掌控权，可以轻而易举地夺走你的数字资产。因此，妥善保存好你的WIF。


## Unity 游戏方如何对接？

请参考对接文档，[Unity SDK 对接](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/12-unity_integration)


## 如何唤醒 ONTO/Cyano 钱包支付？

如果是 Unity 游戏请参考： [https://github.com/ontio-community/unity-demo](https://github.com/ontio-community/unity-demo)

如果是 手机应用请参考：[android-app-demo](https://github.com/ontio-cyano/android-app-demo),[ios-app-demo](https://github.com/ontio-cyano/ios-app-demo)


## 游戏如何对接支付 ONG？

部署合约：

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
        assert(len(args) == 4)
        return transferOng(args[0], args[1], args[2], args[3])

    return False

def transferOng(id,from_acct, to_acct,  ong_amount):
    param = state(from_acct, to_acct, ongAmount)
    res = Invoke(0, OngContract, "transfer", [param])
    if res and res == b'\x01':
        Notify([True,id,AddressToBase58(from_acct), AddressToBase58(to_acct),  ong_amount])
        return True
    else:
        Notify([False,id,AddressToBase58(from_acct), AddressToBase58(to_acct),  ong_amount])
        return False
```

转账函数```transferOng(id,from_acct, to_acct,  ong_amount)``` 第一个参数是订单的id编号，转入方和转出方。

转账成功的合约事件，如果金额不足的失败合约事件里没有转账信息：
```json

{
	"TxHash": "8e15edb68de87bc4c4bd25dd79e6cbda6721a4459d44544817610aaacc4d3e8e",  //交易hash
	"State": 1, //代表合约执行成功
	"GasConsumed": 10000000,  消耗的gas是0.01 ong
	"Notify": [{
			"ContractAddress": "0200000000000000000000000000000000000000",  //这个就是合约里的转账，这个合约就是ong
			"States": [
				"transfer",
				"APa7uMYqdqpFK2chwwmeE7SrQAWZukuGbX",  //转出方
				"AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ",  //转入方
				"1000                                  //金额 1000，
			]
		},
		{
			"ContractAddress": "2cfa6e5519b94059fa0558d7f24406069c5ae5b9",  你的合约地址
			"States": [
				"01",    //代表转账成功
				"31",   //代表你的订单id号
				"41506137754d5971647170464b32636877776d65453753725141575a756b75476258", //转出方地址，解析成base58地址： System.out.println(new String(Helper.hexToBytes("41506137754d5971647170464b32636877776d65453753725141575a756b75476258")));
				"41557235515566654241447136424d593654703579754d73554e47707344376e4c5a",  //接收方地址 
				"e803"                                                                    //转账金额1000的hex小端值
			]
		},
		{
			"ContractAddress": "0200000000000000000000000000000000000000",     //手续费接收地址
			"States": [
				"transfer",
				"APa7uMYqdqpFK2chwwmeE7SrQAWZukuGbX",
				"AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK",   //固定的收手续费地址
				10000000           //你的合约固定消耗0.01 ong
			]
		}
	]
}


```

## 转账如何用Base58地址而不是ByteArray？

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