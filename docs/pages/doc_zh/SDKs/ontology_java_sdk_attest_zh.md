---
title:
keywords: sample homepage
sidebar: SDKs_zh
permalink: ontology_java_sdk_attest_zh.html
folder: doc_zh/SDKs
giturl: https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/attest.md
---

<h1 align="center"> 可信声明及存证 </h1>

<p align="center" class="version">Version 1.0.0 </p>

[English](./ontology_java_sdk_attest_en.html) / 中文




##  1. 可信声明

可验证声明用来证明实体的某些属性。

可信声明存证合约提供了可信声明的存证服务。即存证可信声明Id，签发者ONT身份，属主ONT身份等信息，以及记录可用性信息即是否被吊销等信息。

可信声明规范说明文档请参考：[可信声明规范](https://github.com/ontio/ontology-DID/blob/master/docs/cn/claim_spec_cn.md)


### 1.1 数据结构和规范

具体标准请参考https://github.com/kunxian-xia/ontology-DID/blob/master/docs/en/claim_spec.md

java-sdk采用JSON Web Token的格式表示claim以便于在声明发行者和申请者之间进行传递，jwt格式包含三部分header,payload,signature.

* Claim 具有以下数据结构

```java
class Claim{
  header : Header
  payload : Payload
  signature : byte[]
}
```


```java
class Header {
    public String Alg = "ONT-ES256";
    public String Typ = "JWT-X";
    public String Kid;
    }
```

字段说明
`alg` 使用的签名框架
`typ` 可以是下面两个值中的一个
     JWT: 表示区块链证明不包含在claim中
     JWT-X: 表示区块链证明是claim中的一部分
`kid` 用于签名的公钥

```java
class Payload {
    public String Ver;
    public String Iss;
    public String Sub;
    public long Iat;
    public long Exp;
    public String Jti;
    @JSONField(name = "@context")
    public String Context;
    public Map<String, Object> ClmMap = new HashMap<String, Object>();
    public Map<String, Object> ClmRevMap = new HashMap<String, Object>();
    }
```

`ver` Claim版本号
`iss` 发行方的ontid
`sub` 申请方的ontid
`iat` 创建时间
`exp` 超期时间
`jti` claim的唯一标志
`@context` 指定声明内容定义文档URI，其定义了每个字段的含义和值得类型
`clm` 包含claim内容的对象
`clm-rev` 定义个claim 的撤销机制，

### 1.2 创建可信声明

根据用户输入内容构造声明对象，该声明对象里包含了签名后的数据。
创建claim：
* 1.查询链上是否存在Issuer的DDO
* 2.签名者的公钥必须在DDO的Owners中存在
* 3.claimId 是对claim中删除Signature、Id、Proof的数据转byte数组，做一次sha256，再转hexstring
* 4.对要签名的json数据转成Map对key做排序。
* 5.Signature中Value值：claim 删除Signature、Proof后转byte数组, 做两次sha256得到的byte数组。

```java
Map<String, Object> map = new HashMap<String, Object>();
map.put("Issuer", dids.get(0).ontid);
map.put("Subject", dids.get(1).ontid);
Map clmRevMap = new HashMap();
clmRevMap.put("typ","AttestContract");
clmRevMap.put("addr",dids.get(1).ontid.replace(Common.didont,""));
String claim = ontSdk.nativevm().ontId().createOntIdClaim(dids.get(0).ontid,password,salt, "claim:context", map, map,clmRevMap,System.currentTimeMillis()/1000 +100000);
```

**createOntIdClaim**

```java
String createOntIdClaim(String signerOntid, String password,byte[] salt, String context, Map<String, Object> claimMap, Map metaData,Map clmRevMap,long expire)
```


 功能说明： 创建可信声明

| 参数      | 字段   | 类型  | 描述 |             说明 |
| ----- | ------- | ------ | ------------- | ----------- |
| 输入参数 | signerOntid| String | 签名者ontid | 必选 |
|        | password    | String | 签名者密码   | 必选 |
|        | salt        | byte[] | 解密需要的参数|必选|
|        | context| String  |指定声明内容定义文档URI，其定义了每个字段的含义和值得类型 | 必选|
|        | claimMap| Map  |声明的内容 | 必选|
|        | metaData   | Map | 声明发行者和申请者ontid | 必选 |
|        | clmRevMap   | Map | claim的撤回机制 | 必选 |
|        | expire   | long | 声明过期时间     | 必选 |
| 输出参数 | claim   | String  | 可信声明  |  |

   

### 1.3 验证可信声明

验证claim步骤：
* 1.查询链上是否存在Metadata中Issuer的DDO
* 2.Owner是否存在Sgnature中的PublicKeyId
* 3.对要验签的json数据转成Map对key做排序。
* 4.删除Signature做验签（根据PublicKeyId的id值查找到公钥,签名是Signature中Value做base64解码）
```java
boolean b = ontSdk.nativevm().ontId().verifyOntIdClaim(claim);
```

**verifyOntIdClaim**

```java
boolean verifyOntIdClaim(String claim)
```

功能说明： 验证可信声明

| 参数      | 字段   | 类型  | 描述 |             说明 |
| ----- | ------- | ------ | ------------- | ----------- |
| 输入参数 | claim| String | 可信声明 | 必选 |
| 输出参数 | true或false   | boolean  |   |  |




## 2. 可信声明存证合约使用步骤

该合约提供存储、吊销、查询状态等功能。

### 2.1. 初始化SDK

使用存证合约之前先初始化，并设置合约地址。

```java
String ip = "http://127.0.0.1";
String restUrl = ip + ":" + "20334";
String rpcUrl = ip + ":" + "20336";
String wsUrl = ip + ":" + "20335";
OntSdk wm = OntSdk.getInstance();
wm.setRpc(rpcUrl);
wm.setRestful(restUrl);
wm.setDefaultConnect(wm.getRestful());
wm.openWalletFile("RecordTxDemo.json");
wm.setCodeAddress("803ca638069742da4b6871fe3d7f78718eeee78a");
```

> Note: codeAddress是存证合约地址。

    
    
###  2.2 将可信申明保存到链上 

**sendCommit**

```java
String sendCommit(String issuerOntid, String password,byte[] salt, String subjectOntid, String claimId, Account payerAcct, long gaslimit, long gasprice)
```

功能说明： 将数据保存到链上，声明存证，当且仅当该声明没有被存证过，且Commit函数是由committer调用，才能存证成功；否则，存证失败。存证成功后，该声明的状态就是已存证（committed）。

参数说明：

| 参数      | 字段   | 类型  | 描述 |             说明 |
| ----- | ------- | ------ | ------------- | ----------- |
| 输入参数 | issuerOntid| String | 可信申明签发者数字身份ontid | 必选 |
| 输入参数 | password| String | 数字身份密码 | 必选 |
| 输入参数 | subjectOntid| String | 可信申明申请者ontid | 必选 |
| 输入参数 | claimId| String | 可信申明claim唯一性标志，即Claim里面的Jti字段 | 必选 |
| 输入参数 | payerAcct| String | 交易费用支付者账号 | 必选 |
| 输入参数 | gaslimit| String | gaslimit | 必选 |
| 输入参数 | gasprice| String | gasprice | 必选 |
| 输出参数 | 交易hash   | boolean  |   |  |



示例代码

```java
String[] claims = claim.split("\\.");
JSONObject payload = JSONObject.parseObject(new String(Base64.getDecoder().decode(claims[1].getBytes())));
String commitHash = ontSdk.neovm().claimRecord().sendCommit(dids.get(0).ontid,password,dids.get(1).ontid,payload.getString("jti"),account1,ontSdk.DEFAULT_GAS_LIMIT,0)
```

###  2.3. 查询可信申明的状态

**sendGetStatus**

```
String sendGetStatus(String claimId)
```

功能说明：查询可信申明的状态


参数说明：

```claimId```： 可信申明claim唯一性标志，即Claim里面的Jti字段

返回值：有两部分: 第一部分，claim的状态："Not attested", "Attested", "Attest has been revoked";第二部分是存证者的ontid


示例代码

```java
String getstatusRes2 = ontSdk.neovm().claimRecord().sendGetStatus(payload.getString("jti"));
```


###  2.4. 撤销可信申明


**sendRevoke**

```java
String sendRevoke(String issuerOntid,String password,byte[] salt,String claimId,Account payerAcct,long gaslimit,long gas)
```

功能说明：撤销可信申明


| 参数      | 字段   | 类型  | 描述 |             说明 |
| ----- | ------- | ------ | ------------- | ----------- |
| 输入参数 | issuerOntid| String | 可信申明签发者数字身份ontid | 必选 |
| 输入参数 | password| String | 数字身份密码 | 必选 |
| 输入参数 | salt| String | issuer的salt | 必选 |
| 输入参数 | claimId| String | 可信申明claim唯一性标志，即Claim里面的Jti字段 | 必选 |
| 输入参数 | payerAcct| String | 交易费用支付者账号 | 必选 |
| 输入参数 | gaslimit| String | gaslimit | 必选 |
| 输入参数 | gasprice| String | gasprice | 必选 |
| 输出参数 | 交易hash   | boolean  |   |  |


示例代码

```java
String revokeHash = ontSdk.neovm().claimRecord().sendRevoke(dids.get(0).ontid,password,salt,payload.getString("jti"),account1,ontSdk.DEFAULT_GAS_LIMIT,0);
```
