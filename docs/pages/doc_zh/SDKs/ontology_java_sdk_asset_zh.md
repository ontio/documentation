---
title:
keywords: sample homepage
sidebar: SDKs_zh
permalink: ontology_java_sdk_asset_zh.html
folder: doc_zh/SDKs
giturl: https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/asset.md
---

<h1 align="center"> 数字资产 </h1>

<p align="center" class="version">Version 1.0.0 </p>

[English](./ontology_java_sdk_asset_en.html) / 中文

## 钱包文件及规范

钱包文件是一个Json格式的数据存储文件，可同时存储多个数字身份和多个数字资产账户。具体参考[钱包文件规范](../en/Wallet_File_Specification.md)。

为了管理数字资产，您首先需要创建/打开一个钱包文件。

```java
//如果不存在钱包文件，会自动创建钱包文件。
OntSdk ontSdk = OntSdk.getInstance();
ontSdk.openWalletFile("Demo.json");
```
> 注：目前仅支持文件形式钱包文件，也可以扩展支持数据库或其他存储方式。

## 资产账户数据结构说明
`address` 是base58编码的账户地址。
`label` 是账户的名称。
`isDefault`表明账户是否是默认的账户。默认值为false。
`lock` 表明账户是否是被用户锁住的。客户端不能消费掉被锁的账户中的资金。
`algorithm` 是秘钥算法名称。
`parameters` 是加密算法所需参数。
`curve` 是椭圆曲线的名称。
`key` 是NEP-2格式的私钥。该字段可以为null（对于只读地址或非标准地址）。
`encAlg` 私钥加密的算法名称，固定为aes-256-ctr。
`salt` 私钥解密参数。
`extra` 是客户端存储额外信息的字段。该字段可以为null。
`signatureScheme` 是签名方案，用于交易签名。
`hash` hash算法，用于派生秘钥。


```java
public class Account {
    public String label = "";
    public String address = "";
    public boolean isDefault = false;
    public boolean lock = false;
    public String algorithm = "";
    public Map parameters = new HashMap() ;
    public String key = "";
    @JSONField(name = "enc-alg")
    public String encAlg = "aes-256-gcm";
    public String salt = "";
    public String hash = "sha256";
    public String signatureScheme = "SHA256withECDSA";
    public Object extra = null;
}
```

## 数字资产账户管理

以下举例说明如何管理钱包中的资产账户。

* 创建数字资产账号

```java
OntSdk ontSdk = OntSdk.getInstance();
Account acct = ontSdk.getWalletMgr().createAccount("password");
//创建的账号或身份只在内存中，如果要写入钱包文件，需调用写入接口
ontSdk.getWalletMgr().writeWallet();
```


* 移除数字资产账号

```java
ontSdk.getWalletMgr().getWallet().removeAccount(address);
//写入钱包
ontSdk.getWalletMgr().writeWallet();
```

* 设置默认数字资产账号

```java
ontSdk.getWalletMgr().getWallet().setDefaultAccount(index);
ontSdk.getWalletMgr().getWallet().setDefaultAccount("address");
```
> Note: index表示设置第index个account为默认账户，address表示设置该address对应的account为默认账户

## 原生数字资产接口


原生数字资产包括ONT和ONG。封装了构造交易、交易签名、发送交易。

#### 1. 转账
```java
String sendTransfer(Account sendAcct, String recvAddr, long amount, Account payerAcct, long gaslimit, long gasprice)
```
功能说明： 从发送方转移一定数量的资产到接收方账户

参数说明：

| 参数      | 字段   | 类型  | 描述 |             说明 |
| ----- | ------- | ------ | ------------- | ----------- |
| 输入参数 | sendAcct| Account | 发送方账户 | 必选 |
|        | recvAddr    | Account | 接收方地址   | 必选 |
|        | amount        | long | 转移的资产数量|必选|
|        | payerAcct| Account  |支付交易费用的账户 | 必选|
|        | gaslimit   | long | 声明发行者和申请者ontid | 必选 |
|        | gasprice   | long | gas价格 | 必选 |
| 输出参数 | 交易hash   | String  | 交易hash  |  |

#### 2. 授权转移资产
```java
String sendApprove(Account sendAcct, String recvAddr, long amount, Account payerAcct, long gaslimit, long gasprice)
```
功能说明： sendAddr账户允许recvAddr转移amount数量的资产

参数说明：
       
| 参数      | 字段   | 类型  | 描述 |             说明 |
| ----- | ------- | ------ | ------------- | ----------- |
| 输入参数 | sendAcct| Account | 发送方账户 | 必选 |
|        | recvAddr    | Account | 接收方地址   | 必选 |
|        | amount        | long | 授权的资产数量|必选|
|        | payerAcct| Account  |支付交易费用的账户 | 必选|
|        | gaslimit   | long | 声明发行者和申请者ontid | 必选 |
|        | gasprice   | long | gas价格 | 必选 |
| 输出参数 | 交易hash   | String  | 交易hash  |  |

#### 3. TransferFrom

```java
String sendTransferFrom(Account sendAcct, String fromAddr, String toAddr, long amount, Account payerAcct, long gaslimit, long gasprice)
```
功能说明： sendAcct账户从fromAddr账户转移amount数量的资产到toAddr账户

参数说明：     
        
| 参数      | 字段   | 类型  | 描述 |             说明 |
| ----- | ------- | ------ | ------------- | ----------- |
| 输入参数 | sendAcct| Account | 发送方账户 | 必选 |
|        | fromAddr    | Account | 资产转出方地址   | 必选 |
|        | toAddr    | Account | 资产转入方地址   | 必选 |
|        | amount        | long | 转移的资产数量|必选|
|        | payerAcct| Account  |支付交易费用的账户 | 必选|
|        | gaslimit   | long | 声明发行者和申请者ontid | 必选 |
|        | gasprice   | long | gas价格 | 必选 |
| 输出参数 | 交易hash   | String  | 交易hash  |  |

#### 4. 查询余额

```java
long queryBalanceOf(String address)
```
功能说明： 查询账户address资产余额

参数说明：

```address```： 账户地址

返回值：账户余额

5. 查询Allowance
```java
long queryAllowance(String fromAddr,String toAddr)
```
功能说明： 查询fromAddr授权toAddr转移的数量

参数说明：

```fromAddr```: 授权转出方的账户地址

```toAddr```: 允许转入方的账户地址

返回值：授权转移的数量

#### 6. 查询资产名

```java
String queryName()
```
功能说明： 查询资产名信息

参数说明：

返回值：资产名称

#### 7. 查询资产Symbol

```java
String querySymbol()
```
功能说明： 查询资产Symbol信息

参数说明：

返回值：Symbol信息

#### 8. 查询资产的精确度

```java
long queryDecimals()
```
功能说明： 查询资产的精确度

参数说明：

返回值：精确度
            
#### 9. 查询资产的总供应量
```java
long queryTotalSupply()
```
功能说明： 查询资产的总供应量

参数说明：

返回值：总供应量


资产转移示例代码：

```java
//step1:获得ontSdk实例
OntSdk sdk = OntSdk.getInstance();
sdk.setRpc(url);
sdk.openWalletFile("OntAssetDemo.json");
//step2:获得ont实例
ont = sdk.nativevm().ont()
//step3:调用转账方法
com.github.ontio.account.Account account1 = new com.github.ontio.account.Account(privateKey,SignatureScheme.SHA256WITHECDSA);
ontSdk.nativevm().ont().sendTransfer(account1,"TA4pCAb4zUifHyxSx32dZRjTrnXtxEWKZr",10000,account1,ontSdk.DEFAULT_GAS_LIMIT,0);
```

## nep-5智能合约数字资产例子

nep-5文档：
>https://github.com/neo-project/proposals/blob/master/nep-5.mediawiki

数字资产模板:
>https://github.com/neo-project/examples/tree/master/ICO_Template


|方法名|输入参数|返回值|描述|
|:--|:--|:--|:--|
|sendInit    |boolean preExec|String|如果是true表示预执行以便测试是否已经初始化，如果是false初始化合约参数|
|sendTransfer|String sendAddr, String password, String recvAddr, int amount|String|转移资产|
|sendBalanceOf|String addr|String|获得账户余额|
|sendTotalSupply||String|获得总供应量|
|sendName||String|获取名字|
|sendDecimals||String|查询精度|
|sendSymbol||String|查询Token缩写|


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


查看如何部署和调用智能合约，详见[smartcontract](./ontology_java_sdk_smartcontract_zh.html)。
