<h1 align="center">ONTPass认证服务接入指导</h1>

## 概述

本文用于指导认证需求方如何接入本体，并使用ONTPass提供的认证服务，流程中涉及到的参与方包括：

* 认证需求方（Requester）: 需要对人，物，事进行认证的DApp，机构或服务场景，是本体信任生态中认证服务的需求方。
* ONTPass：基于本体区块链的去中心化身份交易平台，ONTPass主要用于协同用户和需求方进行数据交换，数据全程被加密，ONTPass并不会触碰用户隐私数据。
* TrustAnchor：本体信任生态中的多信任源，能为现实中的人、物、事提供认证服务并能签发可信声明，背后既可以是连接了服务全球的身份认证服务供应商，也可以是社群或自信任源。


## 交互流程说明

![交互流程说明](https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/ontpass02.png)


- A0：ONTPass提供了公开的认证服务集市，认证需求方可以到ONTPass平台浏览并选定自己需要的TrustAnchor及其认证服务。
- A1：认证需求方确认所需的认证服务后，需要到ONTPass平台注册相关基本信息，包括ONT ID，基本简介，所需的认证服务及回调地址。
- A2：认证需求方根据TrustAnchor身份认证的要求，将用户数据提交到TrustAnchor。
- A3.1,A3.2：TrustAnchor对用户进行身份认证，完成可信声明签发，调用智能合约进行分润并做链上可信声明存证。
- A4：TrustAnchor完成可信声明签发后，将可信声明用用户ONT ID对应的公钥进行端到端加密传输到ONTPass。
- A5：ONTPass根据回调地址将签发的可信声明推送到认证需求方。


## 接入步骤

### 1.发现认证服务

本体信任生态中的信任源TrustAnchor会将基本简介，能提供的认证服务和可信声明模板信息注册到ONTPass中，ONTPass对外提供TrustAnchor认证服务集市。认证需求方可以从ONTPass的认证服务集市选择自己需要的认证服务。

<table>
<tr>
	<td>TA_OntId</td>
	<td>TA_Name</td>
	<td>TA_Description</td>
	<td>TA_Address</td>
	<td>Claim_Context</td>
	<td>Claim_Description</td>
	<td>PersonalKeyInfo</td>
	<td>Provider</td>
	<td>DocLink</td>
</tr>
<tr>
    <td rowspan="2">did：ont：ARr6ApK24EU7nu<br/>fND4s1SWpwULHBertpJb</td>
	<td rowspan="2">Ontology China Identity TrustAnchor</td>
    <td rowspan="2">Ontology China Identity TrustAnchor</td>
	<td rowspan="2">Adj7W5Z2hTxxxxxxxx</td>
    <td>claim:cfca_authentication</td>
	<td>中国公民实名身份认证</td>
	<td>姓名，身份证号</td>
	<td>CFCA</td>
	<td>https://www.trustasia.com/cfca?bdcpc&b_scene_zt=1</td>
</tr>
<tr>
    <td>claim:sensetime_authentication</td>
	<td>中国公民实名身份认证</td>
	<td>姓名，身份证号</td>
	<td>SenseTime</td>
	<td>https://www.sensetime.com/authentication/87</td>
</tr>
<tr>
    <td rowspan="6">did：ont：A8JnUAXkJS9LHn<br/>43KHW378pBwA48Ywbuuw<br/></td>
	<td rowspan="6">Ontology Global Identity TrustAnchor</td>
    <td rowspan="6">Ontology Global Identity TrustAnchor</td>
	<td rowspan="6">Adj7W5Z2hTxxxxxxxx</td>
    <td>claim:sfp_passport_authentication</td>
	<td>全球用户护照认证</td>
	<td><nobr>姓名，国籍，出生日期，证件号，签发日期，过期日期</nobr></td>
	<td>Shuftipro</td>
	<td>https://github.com/shuftipro/RESTful-API-v1.3</td>
</tr>
<tr>
    <td>claim:sfp_idcard_authentication</td>
	<td>全球用户身份证认证</td>
	<td><nobr>姓名，国籍，出生日期，证件号，签发日期，过期日期</nobr></td>
	<td>Shuftipro</td>
	<td>https://github.com/shuftipro/RESTful-API-v1.3</td>
</tr>
<tr>
    <td>claim:sfp_dl_authentication</td>
	<td>全球用户驾照认证</td>
	<td><nobr>姓名，国籍，出生日期，证件号，签发日期，过期日期</nobr></td>
	<td>Shuftipro</td>
	<td>https://github.com/shuftipro/RESTful-API-v1.3</td>
</tr>
<tr>
    <td>claim:idm_passport_authentication</td>
	<td>全球用户护照认证</td>
	<td><nobr>姓名，国籍，证件号</nobr></td>
	<td>IdentityMind</td>
	<td>https://identitymindglobal.com/identity-link-api/</td>
</tr>
<tr>
    <td>claim:idm_idcard_authentication</td>
	<td>全球用户身份证认证</td>
	<td><nobr>姓名，国籍，证件号</nobr></td>
	<td>IdentityMind</td>
	<td>https://identitymindglobal.com/identity-link-api/</td>
</tr>
<tr>
    <td>claim:sfp_dl_authentication</td>
	<td>全球用户驾照认证</td>
	<td><nobr>姓名，国籍，证件号</nobr></td>
	<td>IdentityMind</td>
	<td>https://identitymindglobal.com/identity-link-api/</td>
</tr>
</table>



### 2. ONTPass平台注册

认证需求方选定所需的TrustAnchor提供的认证服务后，需要到ONTPass平台注册相关信息，主要包括ONT ID，基本简介，所需认证服务及回调地址。只有在平台注册过的需求方才会收到后续的可信声明回调推送。

> 如何拥有自己的ONT ID并进行签名，可参考[附录](https://pro-docs.ont.io/#/docs-cn/ontpass/ontpass-auth?id=%E9%99%84%E5%BD%95)


#### 认证需求方注册API

```json
Host：https://app.ont.io/S1/api/v1/ontpass/authrequesters
Method：POST /HTTP/1.1
Content-Type: application/json
RequestExample：
{
	"callback_addr": "https://xxx",
	"description": "coinwallet",
	"name": "coinwallet",
	"ontid": "did:ont:AXXxiWCuJXmuPGnsBji4cqWqV1VrKx8nkM",
	"ta_info": [
		{
			"claim_contexts": [
				"claim:cfca_authentication",
				"claim:sensetime_authentication"
			],
			"ontid": "did:ont:AXXxiWCuJXmuPGnsBji4cqWqV1VrKx8nkM"
		}
	],
	"signature":"AQp2ka0OJG5K7jlnaV8jwWneye7knHWTNN+D3yUly="
}

SuccessResponse：
{
	"version":"1.0",
	"action":"Register",
	"error":0,
	"desc":"SUCCESS",
	"result":true
}
```


| RequestField     |     Type |   Description   | Necessary|
| :--------------: | :--------:| :------: |:----:|
|    callback_addr |   String|  可信声明回调地址  | Y|
|    description |   String|  请求方的描述  | N|
|    name|   String|  请求方的名称 |N|
|    ontid|   String|  请求方的ONT ID  | Y|
|    ta_info.claim_contexts |   list|  选定所需的TrustAnchor的可信声明模板列表    | Y|
|    ta_info.ontid |   String|  选定所需的TrustAnchor的ONT ID    | Y|
|    signature |   String|  请求方使用ONT ID私钥按照[签名规则]()对请求内容的签名  |Y|


| ResponseField     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    result|   Boolean|  true：注册成功  false：注册失败|


> 为保证数据传输安全性，需求方注册的回调接口必须是https+域名形式，同时需求方需保证注册的回调接口高可用性且接受ONTPass标准的https的post请求



### 3.向TrustAnchor提交认证

认证需求方根据第一步选定的TrustAnchor认证服务的认证需求，向TrustAnchor提交认证数据。由TrustAnchor进行身份认证，签发可信声明并使用端到端加密，并完成智能合约调用进行资产分润和可信声明基本信息存证。


### 4.获取用户可信声明

当TrustAnchor完成用户认证后，会将认证结果及签发的信声明发送到ONTPass。ONTPass会根据认证需求方之前注册的回调地址，将认证结果和签发的可信声明推送到需求方。信息回调时ONTPass平台会带上自己的ONT ID对应的签名，认证需求方可进行验签，验证回调请求的可信性及未篡改性。

```json
Host：回调地址
Method：POST /HTTP/1.1
Content-Type: application/json
RequestExample：
{
	"auth_flag":true,
	"auth_id":"xxxxxxxxxxx",
	"claim_context":"claim:cfca_authentication",
    "encrp_origdata":"header.payload.signature.blockchain_proof",
	"ontid":"did:ont:AEnB1v4zRzepHY344g2K1eiZqdskhwGuN3",
	"owner_ontid":"did:ont:A9Kn1v4zRzepHY344g2K1eiZqdskhnh2Jv",
	"ta_ontid":"did:ont:A7wB7v4zRzepHY344g2K1eiZqdskhwHu9J",
	"txnhash":"836764a693000d2ca89ea7187af6d40c0a10c31b202b0551f63c6bc1be53fc5b"
	"signature":"AQp2ka0OJWTNN+D3yUlydyjpLpS/GJp6cFt9+wWeT25dBdGYSaErxVDpM1hnbC6Pog="
}
```


| RequestField     |     Type |   Description   | Necessary|
| :--------------: | :--------:| :------: |:----:|
|    auth_flag |   Boolean|  TrustAnchor认证结果 true：认证通过  false：认证未通过  |Y|
|    auth_id |   String|  请求方认证时传给TrustAnchor的认证编号  |Y|
|    claim_context |   String|  可信声明模板标识  |Y|
|    encrp_origdata|   String|  加密后的可信声明 |Y|
|    ontid|   String|  ONTPass的ONT ID  |Y|
|    owner_ontid|   String|  用户的ONT ID   |Y|
|    ta_ontid|   String|  TrustAnchor的ONT ID   |Y|
|    txnhash |   String|  可信声明存证交易hash  |Y|
|    signature |   String|  ONTPass使用ONT ID私钥按照[签名规则]()对请求内容的签名  |Y|




### 附录

#### 拥有自己的ONT ID

**如何拥有测试网ONT ID？**

测试网ONT ID可由ONTPass平台免费代付完成上链注册，直接调用以下API即可完成测试网ONT ID注册并获取相关信息。

```json
Host：https://app.ont.io/S1/api/v1/ontpass/thirdparty/ontid
Method：GET /HTTP/1.1
SuccessResponse：
{
	"ontId": "did:ont:AVdPy51OzyK5MtYyxW4ggFmPCrWQU3VJF2",
	"salt": "FODMSCkT9YDxyVQXQ61+Nw==",
	"scrypt_n": 12386,
	"encrypted_prikey": "a7BCMN9gupQfzfpeJgXJRK3OsO2LITu6xpet5tPyR65LvG4/n1bF+3m2Yy4efGGx",
	"password": "123456",
	"privatekey":"5A5610287B5C6281C6030990D"
}
```

| Param     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    ontId|   String | ONT ID |
|    salt|   String | 盐，安全参数 |
|    scrypt_n|   int | 加密参数。该参数与后续导入ONT ID操作相关 |
|    encrypted_prikey|   String | 加密后的私钥 |
|    password|   String | ONT ID私钥密码 |
|    privatekey|   String | 私钥 |


**如何拥有主网ONT ID？**

- 若你已拥有数字资产账户且在主网上持有至少0.01个ONG，可直接使用各种SDK自行自付创建ONT ID，获取ONT ID相关信息。

- 可使用ONTO客户端[https://onto.app](https://onto.app)创建。记住密码并导出keystore，keystore已包含salt，加密后的私钥，ONT ID等信息。

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
|    scrypt.n|   int | 加密参数。该参数与后续导入ONT ID操作相关 |
|    key|   String | 加密后的私钥 |
|    salt|   String | 盐，安全参数 |
|    address|   String | ONT ID后缀地址。加上did：ont： 即完整的ONT ID |


#### 使用ONT ID签名验签

有了身份ONT ID相关信息后便可进行签名验签操作，可参考[JAVA DEMO](https://github.com/ontio/documentation/blob/master/pro-website-docs/assets/OntIdSignDemo.java)，[TS DEMO](https://github.com/ontio/documentation/blob/master/pro-website-docs/assets/OntIdSignDemo.js)或[SDK开发者文档中心](https://dev-docs.ont.io/#/docs-en/SDKs/00-overview)


