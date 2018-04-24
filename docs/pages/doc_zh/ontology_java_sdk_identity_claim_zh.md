---
title: 
keywords: sample homepage
sidebar: ont_doc_zh
permalink: ontology_java_sdk_identity_claim_zh.html
folder: doc_zh
---

[English](./ontology_java_sdk_identity_claim_en.html) / 中文

<h1 align="center"> Ontology Java SDK User Guide </h1>
<p align="center" class="version">Version 0.7.0 </p>

# 总体介绍

数字身份相关介绍可参考[ONT ID 身份标识协议及信任框架](https://github.com/ontio/ontology-DID)。

## 钱包文件及规范

钱包文件是一个Json格式的数据存储文件，可同时存储多个数字身份和多个数字资产账户。具体参考[钱包文件规范](Wallet_File_Specification.md)。

为了创建数字身份，您首先需要创建/打开一个钱包文件。


```
//如果不存在钱包文件，会自动创建钱包文件。
wm.openWalletFile("Demo3.json");
```
> 注：wm表示OntSdk实例，目前仅支持操作文件形式钱包文件，也可以扩展支持数据库或其他存储方式。



## 数字身份账户管理

* 1 数据结构说明

`ontid` 是代表身份的唯一的id
`label` 是用户给身份所取的名称。
`lock` 表明身份是否被用户锁定了。客户端不能更新被锁定的身份信息。默认值为false。
`controls` 是身份的所有控制对象ControlData的数组。
`extra` 是客户端开发者存储额外信息的字段。可以为null。
```
//Identity数据结构
public class Identity {
	public String label = "";
	public String ontid = "";
	public boolean isDefault = false;
	public boolean lock = false;
	public List<Control> controls = new ArrayList<Control>();
}

```

`algorithm`是用来加密的算法名称。
`parameters` 是加密算法所需参数。
`curve` 是椭圆曲线的名称。
`id` 是control的唯一标识。
`key` 是NEP-2格式的私钥。
```
public class Control {
    public String algorithm = "ECDSA";
    public Map parameters = new HashMap() ;
    public String id = "";
    public String key = "";
}
```

* 2 创建数字身份

ontsdk实例初始化

```
String url = "http://127.0.0.1:20384";
OntSdk wm = OntSdk.getInstance();
wm.setRpc(rpcUrl);
wm.setRestful(restUrl);
wm.setDefaultConnect(wm.getRestful());
wm.openWalletFile("InvokeSmartCodeDemo.json");
ontSdk.setCodeAddress("89ff0f39193ddaeeeab9de4873b549f71bbe809c");
```
> Note: ontid是由智能合约实现，所以需要设置ontid的智能合约codeAddress。

创建数字身份指的是产生一个Identity数据结构的身份信息，并写入到到钱包文件中。

```
Identity identity = ontSdk.getWalletMgr().createIdentity("passwordtest");
//创建的账号或身份只在内存中，如果要写入钱包文件，需调用写入接口
ontSdk.getWalletMgr().writeWallet();
```

* 3 向链上注册身份

只有向区块链链成功注册身份之后，该身份才可以真正使用。

```
ontSdk.getOntIdTx().sendRegister(identity,"passwordtest");
或
ontSdk.getOntIdTx().sendRegister("passwordtest");
```

链上注册成功后，对应此ONT ID的身份描述对象DDO将被存储在本体区块链上。关于DDO的信息可以从[ONT ID 身份标识协议及智能合约实现说明](https://git.ont.network/Ontology_Open_Platform/ontid/src/master/docs/en/ONTID_protocol_spec.md)详细了解。


* 4 导入账号或身份

当用户已经拥有了一个数字身份或者数字账户，SDK支持将其导入到钱包文件中。

> Note: 建议导入一个数字身份之前，建议查询链上身份，如果链上身份DDO不存在，表示此数字身份未在链上注册，请使用ontSdk.getOntIdTx().register(identity)把身份注册到链上。

```
Identity identity = ontSdk.getWalletMgr().importIdentity("6PYMpk8DjWzaEvneyaqxMBap9DuUPH72W6BsWWTtpWE4JJZkGq5ENtfYbT","passwordtest");
//写入钱包      
ontSdk.getWalletMgr().writeWallet();
```

* 5 查询链上身份

链上身份DDO信息，可以通过ONT ID进行查询。

```
//通过ONT ID获取DDO
String ddo = ontSdk.getOntIdTx().sendGetDDO(ontid,"passwordtest",ontid);

//返回DDO格式
{
	"OntId": "did:ont:AMs5NFdXPgCgC7Dci1FdFttvD42HELoLxG",
	"Attributes": {
		"attri0": {
			"Type": "String",
			"Value": "\"value0\""
		}
	},
	"Owners": [
		{
			"Value": "0392a4dbb2a44da81e0942cee1a62ff4298e04ed463b88911b97de19a1597fa83d"
		}
	]
}

```

* 6 移除身份
```
ontSdk.getWalletMgr().getWallet().removeIdentity(ontid);
//写入钱包
ontSdk.getWalletMgr().writeWallet();
```

* 7 设置默认账号或身份
```
//根据账户地址设置默认账户
ontSdk.getWalletMgr().getWallet().setDefaultAccount(address);
//根据identity索引设置默认identity
ontSdk.getWalletMgr().getWallet().setDefaultIdentity(index);
ontSdk.getWalletMgr().getWallet().setDefaultIdentity(ontid);
```

* 8 更新链上DDO属性

```
//更新一个属性
String sendUpdateAttribute(String ontid,String password,byte[] key,byte[] type,byte[] value)
```
| 参数      | 字段   | 类型  | 描述 |             说明 |
| ----- | ------- | ------ | ------------- | ----------- |
| 输入参数 | password| String | 发行者地址 | 必选，私钥解密的密码 |
|        | ontid    | String | 资产名称   | 必选，身份Id |
|        | key    | byte[]  | key       | 必选，key |
|        | type    | byte[] | 类型       |  必选，类型 |
|        | value   | byte[] | value     | 必选，值 |
| 输出参数 | txhash   | String  | 交易hash  | 交易hash是64位字符串 |

* 9 移除链上DDO属性

```
String hash = ontSdk.getOntIdTx().sendRemoveAttribute(did.ontid, "passwordtest", "attri".getBytes());
```
| 参数      | 字段   | 类型  | 描述 |             说明 |
| ----- | ------- | ------ | ------------- | ----------- |
| 输入参数 | password| String | 发行者地址 | 必选，私钥解密的密码 |
|        | ontid    | String | 资产名称   | 必选，身份Id |
|        | key    | byte[]  | key       | 必选，key |
| 输出参数 | txhash   | String  | 交易hash  | 交易hash是64位字符串 |


## 可信申明

### 1 数据结构和规范

* Claim 具有以下数据结构

```
{
  unsignedData : string,
  signedData : string,
  context : string,
  id : string,
  claim : {},
  metadata : Metadata,
  signature : Signature
}

```

`unsignedData` 是未被签名的声明对象的json格式字符串，声明对象包含Context, Id, Claim, Metadata这些字段。
`signedData` 是声明对象被签名后的json格式字符串，该json包含声明对象和签名对象。
`Context` 是声明模板的标识。
`Id` 是声明对象的标识。
`Claim` 是声明的内容。
`Metadata` 是声明对象的元数据。

* Metadata 具有以下数据结构

```
{
  createTime : datetime string
  issuer : string,
  subject : string,
  expires : datetime string
  revocation : string,
  crl : string
}

```
`createtime` 是声明的创建时间。
`issuer` 是声明的发布者。
`subject` 是声明的主语。
`expires` 是声明的过期时间。
`revocation` 是声明撤销方法。
`crl` 是声明撤销列表的链接。


* Signature 具有以下数据结构

```
{
    format : string,
    algorithm : string,
    value : string
}
format 是签名的格式。
algorithm 是签名的算法。
value 是计算后的签名值。
```

### 2 签发可信申明
根据用户输入内容构造声明对象，该声明对象里包含了签名后的数据。

```
Map<String, Object> map = new HashMap<String, Object>();
map.put("Issuer", dids.get(0).ontid);
map.put("Subject", dids.get(1).ontid);
String claim = ontSdk.getOntIdTx().createOntIdClaim(ontid,"passwordtest","claim:context",map,map);
System.out.println(claim);
```

> Note: Issuer可能有多把公钥，createOntIdClaim的参数ontid指定使用哪一把公钥。

### 3 验证可信申明

```
boolean b = ontSdk.getOntIdTx().verifyOntIdClaim(dids.get(0).ontid,"passwordtest",claim);

```


### 4 实例说明


```
//注册ontid
Identity ident = ontSdk.getOntIdTx().sendRegister("passwordtest");
String ontid = ident.ontid;
//更新属性
String attri = "attri";
Map recordMap = new HashMap();
recordMap.put("key0", "world0");
//recordMap.put("key1", i);
recordMap.put("keyNum", 1234589);
recordMap.put("key2", false);
String hash = ontSdk.getOntIdTx().sendUpdateAttribute(ontid,"passwordtest", attri.getBytes(), "Json".getBytes(), JSON.toJSONString(recordMap).getBytes());
```

> Note: 当不存在该属性时，调用sendUpdateAttribute方法，会增加相应的属性，当属性存在时，会更新相应属性，attri代表属性名称，"Json"是属性值得数据类型，recordMap表示属性的值。

Claim签发和验证：
```
Map<String, Object> map = new HashMap<String, Object>();
map.put("Issuer", dids.get(0).ontid);
map.put("Subject", dids.get(1).ontid);

//密码是签发人的秘密，钱包文件ontid中必须要有该签发人。
String claim = ontSdk.getOntIdTx().createOntIdClaim(ontid,"passwordtest","claim:context",map,map);
System.out.println(claim);
boolean b = ontSdk.getOntIdTx().verifyOntIdClaim(ontid,"passwordtest",claim);
```