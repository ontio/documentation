---
title: 
keywords: sample homepage
sidebar: ont_doc_zh
permalink: ontology_java_sdk_asset_zh.html
folder: doc_zh
---

[English](./ontology_java_sdk_asset_en.html) / 中文

<h1 align="center"> Ontology Java SDK User Guide </h1>
<p align="center" class="version">Version 0.7.0 </p>


# 数字资产

## 数据结构说明
`address` 是base58编码的账户地址。
`label` 是账户的名称。
`isDefault`表明账户是否是默认的账户。默认值为false。
`lock` 表明账户是否是被用户锁住的。客户端不能消费掉被锁的账户中的资金。
`algorithm` 是加密算法名称。
`parameters` 是加密算法所需参数。
`curve` 是椭圆曲线的名称。
`key` 是NEP-2格式的私钥。该字段可以为null（对于只读地址或非标准地址）。
`extra` 是客户端存储额外信息的字段。该字段可以为null。

```
public class Account {
    public String label = "";
    public String address = "";
    public boolean isDefault = false;
    public boolean lock = false;
    public String algorithm = "";
    public Map parameters = new HashMap() ;
    public String key = "";
    public Object extra = null;
}
```

## 数字资产账户管理

* 创建数字资产账号

```
String url = "http://127.0.0.1:20386";
OntSdk ontSdk = OntSdk.getInstance();
ontSdk.setRpcConnection(url);
ontSdk.openWalletFile("wallet.json");
Account acct = ontSdk.getWalletMgr().createAccount("password");
//创建的账号或身份只在内存中，如果要写入钱包文件，需调用写入接口
ontSdk.getWalletMgr().writeWallet();
```


* 移除数字资产账号

```
ontSdk.getWalletMgr().getWallet().removeAccount(address);
//写入钱包 
ontSdk.getWalletMgr().writeWallet();
```

* 设置默认数字资产账号

```
ontSdk.getWalletMgr().getWallet().setDefaultAccount(index);
ontSdk.getWalletMgr().getWallet().setDefaultAccount("address");
```
> Note: index表示设置第index个account为默认账户，address表示设置该address对应的account为默认账户

## 原生数字资产

* 使用SDK方法

我们建议您使用SDK封装的方法操作原生数字资产，比如 ONT Token等。

```
//step1:获得ontSdk实例
OntSdk wm = OntSdk.getInstance();
wm.setRpcConnection(url);
wm.openWalletFile("OntAssetDemo.json");
//step2:获得ontAssetTx实例
ontAssetTx = ontSdk.getOntAssetTx()
//step3:调用转账方法
ontAssetTx.sendTransfer(from,to,value)
ontSdk.getOntAssetTx().sendTransferToMany("ont",info1.address,"passwordtest",new String[]{info2.address,info3.address},new long[]{100L,200L});
ontSdk.getOntAssetTx().sendTransferFromMany("ont", new String[]{info1.address, info2.address}, new String[]{"passwordtest", "passwordtest"}, info3.address, new long[]{1L, 2L});
ontSdk.getOntAssetTx().sendOngTransferFrom(info1.address,"passwordtest",info2.address,100);
```


* 使用智能合约

您也可以使用智能合约操作原生数字资产。

ontology资产智能合约abi文件，abi文件是对智能合约函数接口的描述，通过abi文件可以清楚如何传参：

```
{
    "hash":"0xceab719b8baa2310f232ee0d277c061704541cfb",
    "entrypoint":"Main",
    "functions":
    [
        {
            "name":"Main",
            "parameters":
            [
                {
                    "name":"operation",
                    "type":"String"
                },
                {
                    "name":"args",
                    "type":"Array"
                }
            ],
            "returntype":"Any"
        },
        {
            "name":"Transfer",
            "parameters":
            [
                {
                    "name":"from",
                    "type":"ByteArray"
                },
                {
                    "name":"to",
                    "type":"ByteArray"
                },
                {
                    "name":"value",
                    "type":"Integer"
                }
            ],
            "returntype":"Boolean"
        },
        {
            "name":"BalanceOf",
            "parameters":
            [
                {
                    "name":"address",
                    "type":"ByteArray"
                }
            ],
            "returntype":"Integer"
        }
    ],
    "events":
    [
    ]
}
```

通过调用ontology资产智能合约进行转账操作

```
//step1:读取智能合约abi文件
InputStream is = new FileInputStream("C:\\NeoContract1.abi.json");
byte[] bys = new byte[is.available()];
is.read(bys);
is.close();
String abi = new String(bys);

//step2：解析abi文件
AbiInfo abiinfo = JSON.parseObject(abi, AbiInfo.class);

//step3：设置智能合约codeaddress
ontSdk.setCodeAddress(abiinfo.getHash());

//step4：选择函数，设置函数参数
AbiFunction func = abiinfo.getFunction("Transfer");
System.out.println(func.getParameters());
func.setParamsValue(from.getBytes(),to.getBytes(),value.getBytes());

//setp5：调用合约
String hash = ontSdk.getSmartcodeTx().sendInvokeSmartCodeWithSign("passwordtest",addr,func);
```

AbiInfo结构是怎样的？

```
public class AbiInfo {
    public String hash;
    public String entrypoint;
    public List<AbiFunction> functions;
    public List<AbiEvent> events;
}
public class AbiFunction {
    public String name;
    public String returntype;
    public List<Parameter> parameters;
}
public class Parameter {
    public String name;
    public String type;
    public String value;
}
```
## nep-5智能合约数字资产
nep-5文档：
>https://github.com/neo-project/proposals/blob/master/nep-5.mediawiki

nep-5智能合约模板：

```
using Neo.SmartContract.Framework;
using Neo.SmartContract.Framework.Services.Neo;
using Neo.SmartContract.Framework.Services.System;
using System;
using System.ComponentModel;
using System.Numerics;

namespace Nep5Template
{
    public class Nep5Template : SmartContract
    {
        //Token Settings
        public static string Name() => "Nep5Template Token";
        public static string Symbol() => "TMP";
        public static readonly byte[] community = "AXK2KtCfcJnSMyRzSwTuwTKgNrtx5aXfFX".ToScriptHash();
        public static byte Decimals() => 8;
        private const ulong factor = 100000000; //decided by Decimals()

        //ICO Settings
        private const ulong totalAmount = 1000000000 * factor;
        private const ulong communityCap = 1000000000 * factor;

        [DisplayName("transfer")]
        public static event Action<byte[], byte[], BigInteger> Transferred;

        public static Object Main(string operation, params object[] args)
        {
            if (Runtime.Trigger == TriggerType.Application)
            {
                if (operation == "init") return Init();
                if (operation == "totalSupply") return TotalSupply();
                if (operation == "name") return Name();
                if (operation == "symbol") return Symbol();
                if (operation == "transfer")
                {
                    if (args.Length != 3) return false;
                    byte[] from = (byte[])args[0];
                    byte[] to = (byte[])args[1];
                    BigInteger value = (BigInteger)args[2];
                    return Transfer(from, to, value);
                }
                if (operation == "balanceOf")
                {
                    if (args.Length != 1) return 0;
                    byte[] account = (byte[])args[0];
                    return BalanceOf(account);
                }
                if (operation == "decimals") return Decimals();
            }
            return false;
        }

        // 初始化参数
        public static bool Init()
        {
            byte[] total_supply = Storage.Get(Storage.CurrentContext, "totalSupply");
            if (total_supply.Length != 0) return false;

            Storage.Put(Storage.CurrentContext, community, communityCap);
            Transferred(null, community, communityCap);

            Storage.Put(Storage.CurrentContext, "totalSupply", totalAmount);
            return true;
        }

        // get the total token supply
        // 获取已发行token总量
        public static BigInteger TotalSupply()
        {
            Runtime.CheckSig(new byte[1]{ 1 },  new byte[]{2},new byte[]{ 3});
            return Storage.Get(Storage.CurrentContext, "totalSupply").AsBigInteger();
        }

        // function that is always called when someone wants to transfer tokens.
        // 流转token调用
        public static bool Transfer(byte[] from, byte[] to, BigInteger value)
        {
            if (value <= 0) return false;
            if (!Runtime.CheckWitness(from)) return false;
            if (from == to) return true;
            BigInteger from_value = Storage.Get(Storage.CurrentContext, from).AsBigInteger();
            if (from_value < value) return false;
            if (from_value == value)
                Storage.Delete(Storage.CurrentContext, from);
            else
                Storage.Put(Storage.CurrentContext, from, from_value - value);
            BigInteger to_value = Storage.Get(Storage.CurrentContext, to).AsBigInteger();
            Storage.Put(Storage.CurrentContext, to, to_value + value);
            Transferred(from, to, value);
            return true;
        }

        // get the account balance of another account with address
        // 根据地址获取token的余额
        public static BigInteger BalanceOf(byte[] address)
        {
            return Storage.Get(Storage.CurrentContext, address).AsBigInteger();
        }
    }
}
```
部署合约：
```
  InputStream is = new FileInputStream("C:\\smartcontract.avm");//
  byte[] bys = new byte[is.available()];
  is.read(bys);
  is.close();
  String code = Helper.toHexString(bys);
  System.out.println("Code:" + Helper.toHexString(bys));
  System.out.println("CodeAddress:" + Helper.getCodeAddress(code, VmType.NEOVM.value()));

  ontSdk.setCodeAddress(Helper.getCodeAddress(code, VmType.NEOVM.value()));
  Transaction tx = ontSdk.getSmartcodeTx().makeDeployCodeTransaction(code, true, "name", "v1.0", "author", "email", "desc", VmType.NEOVM.value());
```
调用合约：
```
  AbiInfo abiinfo = JSON.parseObject(nep5abi, AbiInfo.class);
  //选个智能合约方法
  AbiFunction func = abiinfo.getFunction("Transfer");
  func.name = func.name.toLowerCase();
  //设置方法的参数
  func.setParamsValue(Address.decodeBase58(sendAddr).toArray(),Address.decodeBase58(recvAddr).toArray(),amount);
  Transaction tx = sdk.getSmartcodeTx().invokeTransaction(sendAddr,password,func,VmType.NEOVM.value());
  //签名
  sdk.signTx(tx, sendAddr, password);
  boolean b = sdk.getConnectMgr().sendRawTransaction(tx.toHexString());
```

## 说明

* codeAddress是什么？

```
是智能合约的唯一标识。在这里代表资产合约的codeAddress。
```

* invoke时为什么要传入账号和密码？

```
调用智能合约时需要用户签名，钱包中保存的是加密后的用户私钥，需要密码才能解密获取私钥。
```

* 查询资产操作时，智能合约预执行是怎么回事，如何使用？

```
如智能合约get相关操作，从智能合约存储空间里读取数据，无需走节点共识，只在该节点执行即可返回结果。
发送交易时调用预执行接口
String result = (String) sdk.getConnectMgr().sendRawTransactionPreExec(txHex);
```

* 想查看转账时的推送结果？


请查看智能合约采用websocket连接调用合约方法，详见[smartcontract](smartcontract.md)。

