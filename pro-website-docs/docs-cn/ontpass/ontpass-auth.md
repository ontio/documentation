[English](../en/thirdparty_kyc.md) / 中文

<h1 align="center">ONTPass认证服务接入指导</h1>
<p align="center" class="version">Version 0.8.0 </p>

## 概述

本文用于指导认证需求方如何接入本体，并使用ONTPass提供的认证服务，流程中涉及到的参与方包括：

* 认证需求方（Requester）: 需要对用户进行认证的DApp，机构或服务场景，是本体信任生态中认证服务的需求方。
* ONTPass：基于本体区块链的去中心化身份交易平台，ONTPass主要用于协同用户和需求方进行数据交换，数据全程被加密，ONTPass并不会触碰用户隐私数据。
* TrustAnchor：本体信任生态中的信任锚，为全球用户提供认证服务并能签发可信声明，背后连接了服务全球的身份认证服务供应商，能帮助用户实现身份认证。


## 交互流程说明

![交互流程说明](https://github.com/ontio/documentation/blob/master/pro-website-docs/ontpass02.png)


- A0：ONTPass提供了公开的认证服务集市，认证需求方可以到ONTPass平台浏览并选定自己需要的TrustAnchor及其认证服务。
- A1：认证需求方确认所需的认证服务后，需要到ONTPass平台注册相关基本信息，包括OntId，基本简介及回调地址。
- A2：认证需求方根据TrustAnchor身份认证所需要的数据，将用户数据提交到TrustAnchor。
- A3.1,A3.2：TrustAnchor对用户进行身份认证，签发可信声明并做链上可信声明存证。
- A4：TrustAnchor完成可信声明签发后，将可信声明用端到端加密传输到ONTPass。
- A5：ONTPass根据回调地址将TrustAnchor签发的可信声明推送到认证需求方。


## 接入步骤

### 1.发现认证服务

本体信任生态中的信任锚TrustAnchor会将自己能提供的认证服务和可信声明模板信息注册到ONTPass中，ONTPass对外提供TrustAnchor认证服务集市。认证需求方可以从ONTPass的认证服务集市选择自己需要的认证服务。

<table>
<tr>
	<td>TA_OntId</td>
	<td>TA_Description</td>
	<td>Claim_Context</td>
	<td>Claim_Description</td>
	<td>PersonalKeyInfo</td>
	<td>Provider</td>
	<td>DocLink</td>
</tr>
<tr>
    <td rowspan="2"> did:ont:ARr6ApK24EU7nu<br/>fND4s1SWpwULHBertpJb</td>
    <td rowspan="2">Ontology TrustAnchor</td>
    <td>claim:cfca_authentication</td>
	<td>中国公民实名身份认证</td>
	<td>姓名，身份证号</td>
	<td>CFCA</td>
	<td>https://github.com/shuftipro/RESTful-API-v1.3</td>
</tr>
<tr>
    <td>claim:sensetime_authentication</td>
	<td>中国公民实名身份认证</td>
	<td>姓名，身份证号</td>
	<td>SenseTime</td>
	<td>https://github.com/shuftipro/RESTful-API-v1.3</td>
</tr>
<tr>
    <td rowspan="6"> did:ont:AcbVUAXkJSKy7g<br/>43KHW378pBwA48Ywbuuw<br/></td>
    <td rowspan="6">Ontology TrustAnchor</td>
    <td>claim:sfp_passport_authentication</td>
	<td>全球用户护照认证</td>
	<td><nobr>姓名，国籍，出生日期，证件号,签发日期，过期日期</nobr></td>
	<td>Shuftipro</td>
	<td>https://github.com/shuftipro/RESTful-API-v1.3</td>
</tr>
<tr>
    <td>claim:sfp_idcard_authentication</td>
	<td>全球用户身份证认证</td>
	<td><nobr>姓名，国籍，出生日期，证件号,签发日期，过期日期</nobr></td>
	<td>Shuftipro</td>
	<td>https://github.com/shuftipro/RESTful-API-v1.3</td>
</tr>
<tr>
    <td>claim:sfp_dl_authentication</td>
	<td>全球用户驾照认证</td>
	<td><nobr>姓名，国籍，出生日期，证件号,签发日期，过期日期</nobr></td>
	<td>Shuftipro</td>
	<td>https://github.com/shuftipro/RESTful-API-v1.3</td>
</tr>
<tr>
    <td>claim:idm_passport_authentication</td>
	<td>全球用户护照认证</td>
	<td><nobr>姓名，国籍，证件号</nobr></td>
	<td>IdentityMind</td>
	<td>https://github.com/shuftipro/RESTful-API-v1.3</td>
</tr>
<tr>
    <td>claim:idm_idcard_authentication</td>
	<td>全球用户身份证认证</td>
	<td><nobr>姓名，国籍，证件号</nobr></td>
	<td>IdentityMind</td>
	<td>https://github.com/shuftipro/RESTful-API-v1.3</td>
</tr>
<tr>
    <td>claim:sfp_dl_authentication</td>
	<td>全球用户驾照认证</td>
	<td><nobr>姓名，国籍，证件号</nobr></td>
	<td>IdentityMind</td>
	<td>https://github.com/shuftipro/RESTful-API-v1.3</td>
</tr>
</table>



### 2. ONTPass平台注册

认证需求方选定所需的认证服务后，需要到ONTPass平台注册相关信息，主要包括OntId，基本简介及回调地址。


  如何拥有自己的OntId，可参考[附录]


#### 认证需求方注册API

```json
Host：https://app.ont.io/S1/api/v1/ontpass/authrequester
Method：POST /HTTP/1.1
Content-Type: application/json
RequestExample：
{
	"OntId":"did:ont:Assxxxxxxxxxxxxx",
	"Name":"COO",
	"Desc":"COO 区块链",
	"CallBackAddr":"https://coo.chain/user/authentication",
	"Signature":"AXFqy6w/xg+IFQBRZvucKXvTuIZaIxOS0pesuBj1IKHvw56DaFwWogIcr1B9zQ13nUM0w5g30KHNNVCTo14lHF0="
}

SuccessResponse：
{
	"Version":"0.8",
	"Action":"Register",
	"Error":0,
	"Desc":"SUCCESS",
	"Result":true
}
```


| RequestField     |     Type |   Description   | Necessary|
| :--------------: | :--------:| :------: |:----:|
|    OntId|   String|  认证需求方OntId  | Y|
|    Name|   String|  认证需求方名称  | Y|
|    Desc|   String| 认证需求方描述 |Y|
|    CallBackAddr|   String|  回调地址。满足https+域名，接收post回调请求来获取TrustAnchor签发完成的可信声明信息 | Y|
|    Signature|   String|  请求信息的签名。由认证需求方使用自己OntId的私钥按照标准的ECDSA算法签名。| Y|


| ResponseField     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    Result|   Boolean|  true：注册成功  false：注册失败|


> 注意：为保证数据传输安全性，需求方注册的回调接口必须是https+域名形式，同时场景方需保证注册的回调接口高可用性且接受ONTPass标准的https的post请求


### 3.获取用户可信声明

认证需求方向TrustAnchor提交认证数据，由TrustAnchor完成用户的身份信息认证并签发可信声明。当用户认证完成后，TrustAnchor会将可信声明发送到ONTPass。OntPass会根据认证需求方之前注册的回调地址，将签发完成的可信声明推送到需求方。


```json
Host：回调地址
Method：POST /HTTP/1.1
Content-Type: application/json

RequestExample：
{
	"OntPassOntId":"did:ont:AXZUn3r5yUk8o87wVm3tBZ31mp8FTaeqeZ",
	"Claims":[
		{
			"UserOntId":"did:ont:AXZUn3r5yUk8o87wVm3tBZ31mp8FTaeqeZ",
			"Context":"claim:cfca_authentication",
			"EncryOrigData":"eyJraWQiOiJkaWQ6b250OkFScjZBcEsyNEVVN251Zk5ENHMxU1dwd1VMSEJlcnRwSmIja2V5cy0xIiwidHlwIjoiSldULVgiLCJhbGciOiJPTlQtRVMyNTYifQ==.eyJjbG"
		}
	]	"Signature":"AXFqt7w/xg+IFQBRZvucKXvTuIZaIxOS0pesuBj1IKHvw56DaFwWogIcr1B9zQ13nUM0w5g30KHNNVCTo04lHF0="
}
```


| RequestField     |     Type |   Description   | Necessary|
| :--------------: | :--------:| :------: | :----: |
|    OntPassOntId|   String|  ONTPass平台的OntId  | Y|
|    Claims.UserOntId|   String|  用户OntId  | Y|
|    Claims.Context|   String|  用户可信声明模板标识  | Y|
|    Claims.EncryOrigData|   String|  加密后的可信声明 | Y|
|    Signature|   String|  ONTPass对请求信息的签名 | Y|




### 附录


#### 拥有自己的OntId

有了身份OntId相关信息后便可使用各种SDK进行签名验签等操作。

OntId签名验签等身份相关操作可参考附录[示例代码](https://github.com/ontio/ontology-DID/blob/master/docs/cn/thirdparty_kyc_cn.md#%E5%8F%82%E8%80%83%E4%BB%A3%E7%A0%81)或[SDKs开发文档](https://ontio.github.io/documentation/ontology_overview_sdks_en.html)

测试网OntId可由ONTPass平台免费代付完成上链注册，直接调用以下API即可完成测试网OntId注册。

```json
Host：https://app.ont.io/S1/api/v1/ontpass/thirdparty/ontid
Method：GET /HTTP/1.1
SuccessResponse：
{
  "Action": "RegisterTestNetOntId",
  "Error": 0,
  "Desc": "SUCCESS",
  "Version": "1.0",
  "Result": {
    "OntId": "did:ont:AVdPy51OzyK5MtYyxW4ggFmPCrWQU3VJF2",
    "Salt": "FODMSCkT9YDxyVQXQ61+Nw==",
    "Scrypt-N": 12386,
    "EncryptedPriKey": "a7BCMN9gupQfzfpeJgXJRK3OsO2LITu6xpet5tPyR65LvG4/n1bF+3m2Yy4efGGx",
    "Password": "123456",
	"PrivateKey":"5A5610287B5C6281C6030990D"
  }
}
```

| Param     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    OntId|   String | OntId |
|    Salt|   String | 盐，安全参数 |
|    Scrypt-N|   int | 加密参数。该参数与后续导入OntId操作相关 |
|    EncryptedPriKey|   String | 加密后的私钥 |
|    Password|   String | OntId私钥密码 |
|    PrivateKey|   String | 私钥 |


主网OntId，推荐使用Owallet客户端[https://onto.app](https://onto.app)创建。记住密码并导出keystore，keystore已包含salt，加密后的私钥，OntId等信息。

ONTO导出keystore示例：
```
{
  "scrypt" : {
    "r" : 8,
    "p" : 8,
    "n" : 4096,
    "dkLen" : 64
  },
  "address" : "AYMKcyx1EuY6o7qqMX17DCPbwmsFpQSoAx",
  "parameters" : {
    "curve" : "secp256r1"
  },
  "claimArray" : [
  	....
	....
  ],
  "label" : "xxx",
  "type" : "I",
  "algorithm" : "ECDSA",
  "key" : "rnE6WclHSS9tpHGp01KQOM10NzeZt4lvlOOOQC8ht9N0x7d1jkjccP9Ay3qQmStT",
  "salt" : "UyDgxiZs1StSBkqTmynRJg=="
}
```

| Param     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    scrypt.n|   int | 加密参数。该参数与后续导入OntId操作相关 |
|    key|   String | 加密后的私钥 |
|    salt|   String | 盐，安全参数 |
|    address|   String | OntId后缀地址。加上did:ont: 即完整的OntId |

若你已拥有数字资产账户且持有至少0.01个ONG，也可直接使用各种SDK自行自付创建OntId，获取OntId相关信息。



