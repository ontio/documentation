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
- A3.1,A3.2：TrustAnchor对用户进行身份认证，完成可信声明签发，可信声明基本信息链上存证，资金交割。
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
    <td rowspan="3">did:ont:ANNmeSiQJVwq3z6K<br/>vKo3SSKGnoBqvwYcwt<br/></td>
	<td rowspan="3">Ontology Global Identity TrustAnchor</td>
    <td rowspan="3">Ontology Global Identity TrustAnchor</td>
	<td rowspan="3">ATGJSGzm2poCB8N44BgrAccJcZ64MFf187</td>
    <td>claim:sfp_passport_authentication</td>
	<td>全球用户护照认证</td>
	<td><nobr>姓名，国籍，出生日期，证件号，签发日期，过期日期</nobr></td>
	<td>Shuftipro</td>
	<td>http://pro-docs.ont.io/#/docs-cn/ontpass/ONTTA</td>
</tr>
<tr>
    <td>claim:sfp_idcard_authentication</td>
	<td>全球用户身份证认证</td>
	<td><nobr>姓名，国籍，出生日期，证件号，签发日期，过期日期</nobr></td>
	<td>Shuftipro</td>
	<td>http://pro-docs.ont.io/#/docs-cn/ontpass/ONTTA</td>
</tr>
<tr>
    <td>claim:sfp_dl_authentication</td>
	<td>全球用户驾照认证</td>
	<td><nobr>姓名，国籍，出生日期，证件号，签发日期，过期日期</nobr></td>
	<td>Shuftipro</td>
	<td>http://pro-docs.ont.io/#/docs-cn/ontpass/ONTTA</td>
</tr>
</table>



### 2. ONTPass平台注册

认证需求方选定所需的TrustAnchor提供的认证服务后，需要到ONTPass平台注册相关信息，主要包括ONT ID，基本简介，所需认证服务及回调地址。只有在平台注册过的需求方才会收到后续的可信声明回调推送。

> 如何拥有自己的ONT ID并进行签名，可参考[附录DEMO](https://pro-docs.ont.io/#/docs-cn/ontpass/ontpass-auth?id=demo)


#### 认证需求方注册API

```json
Host：https://api.ont.network/api/v1/ontpass/authrequesters
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
|    description |   String|  需求方的描述  | Y|
|    name|   String|  需求方的名称 |Y|
|    ontid|   String|  需求方的ONT ID  | Y|
|    ta_info.claim_contexts |   list|  选定所需的TrustAnchor的可信声明模板列表    | Y|
|    ta_info.ontid |   String|  选定所需的TrustAnchor的ONT ID    | Y|
|    signature |   String|  需求方使用ONT ID私钥按照[签名规则](https://pro-docs.ont.io/#/docs-cn/ontpass/ontpass-auth?id=%E4%BD%BF%E7%94%A8ont-id%E7%AD%BE%E5%90%8D%E9%AA%8C%E7%AD%BE)对请求内容的签名  |Y|


| ResponseField     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    result|   Boolean|  true：注册成功  false：注册失败|


> 为保证数据传输安全性，需求方注册的回调接口必须是https+域名形式，同时需求方需保证注册的回调接口高可用性且接受ONTPass标准的https的post请求



### 3.向TrustAnchor提交认证

需求方在ONTPass认证集市选定TrustAnchor的认证服务后，需向TrustAnchor提交认证数据。由TrustAnchor进行身份认证，可信声明签发，可信声明基本信息存证，资产交割，并使用端到端加密传输可信声明到ONTPass。

[查看ONTPass平台已登记的TrustAnchor信任源](http://pro-docs.ont.io/#/docs-cn/ontpass/ONTTA)


### 4.获取用户可信声明

当TrustAnchor完成用户认证后，会将认证结果及签发的信声明发送到ONTPass。ONTPass会根据认证需求方之前注册的回调地址，将认证结果和签发的可信声明推送到需求方。

信息回调时ONTPass平台会带上自己的ONT ID对应的签名，认证需求方可进行验签，验证回调请求的可信性及未篡改性。

```json
Host：回调地址
Method：POST /HTTP/1.1
Content-Type: application/json
RequestExample：
{
	"auth_flag":true,
	"auth_id":"xxxxxxxxxxx",
	"claim_context":"claim:sfp_passport_authentication",
	"description":"shuftipro passport authentication ",
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
|    auth_id |   String|  需求方认证时传给TrustAnchor的认证编号  |Y|
|    claim_context |   String|  可信声明模板标识  |Y|
|    description|   String|  若认证失败，即失败原因。若认证成功，即可信声明描述 |Y|
|    encrp_origdata|   String|  加密后的可信声明 |Y|
|    ontid|   String|  ONTPass的ONT ID  |Y|
|    owner_ontid|   String|  用户的ONT ID   |Y|
|    ta_ontid|   String|  TrustAnchor的ONT ID   |Y|
|    txnhash |   String|  可信声明存证交易hash  |Y|
|    signature |   String|  ONTPass使用ONT ID私钥按照[签名规则](https://pro-docs.ont.io/#/docs-cn/ontpass/ontpass-auth?id=%E4%BD%BF%E7%94%A8ont-id%E7%AD%BE%E5%90%8D%E9%AA%8C%E7%AD%BE)对请求内容的签名  |Y|




### 附录

#### 拥有自己的ONT ID

在Ontology上注册ONT ID需要消耗ONG手续费。首先需要你拥有数字资产账户，且账户里至少有0.01个ONG，然后使用该资产账户为注册ONT ID进行手续费代付，完成ONT ID链上注册。

> 如何创建数字资产账户，使用资产账户创建ONT ID，获取ONT ID相关信息并进行签名。可参考[附录DEMO](https://pro-docs.ont.io/#/docs-cn/ontpass/ontpass-auth?id=demo)或[SDK开发者文档中心](https://dev-docs.ont.io/#/docs-en/SDKs/00-overview)


> 测试网ONG可到Ontology开发者中心直接申请：[测试网ONG申请入口](https://developer.ont.io/applyOng)

#### 使用ONT ID签名验签

**签名规则：**

HTTP Post请求体里的JSON对象需要按照key的字母升序排序，然后序列化为标准的JSON格式字符串，再对该请求内容字符串进行签名，最后再把签名以signature为key添加到请求体里的JSON对象中。

以注册请求为例：
POST请求的JSON对象按照key升序排序后为
```
{
	"callback_addr": "https://xxx",
	"description": "coinwallet",
	"name": "coinwallet",
	"ontid": "did:ont:AXXxiWCuJXmuPGnsBji4cqWqV1VrKx8nkM",
	"ta_info": [
		{
			"claim_contexts": [
				"claim:sensetime_authentication"
			],
			"ontid": "did:ont:AXXxiWCuJXmuPGnsBji4cqWqV1VrKx8nkM"
		}
	]
}
```
转换成标准JSON格式字符串：

	{"callback_addr":"https://xxx","description":"coinwallet","name":"coinwallet","ontid":"did:ont:AXXxiWCuJXmuPGnsBji4cqWqV1VrKx8nkM","ta_info":[{"claim_contexts":["claim:sensetime_authentication"],"ontid":"did:ont:AXXxiWCuJXmuPGnsBji4cqWqV1VrKx8nkM"}]}

再对该JSON格式字符串进行签名(签名验签操作，可参考[附录DEMO]()或[SDK开发者文档中心](https://dev-docs.ont.io/#/docs-en/SDKs/00-overview))，得到签名值sigvalue后，以signature为key添加到Post请求体的JSON对象中

最终认证Post请求体的JSON对象为：
```
{
	"callback_addr": "https://xxx",
	"description": "coinwallet",
	"name": "coinwallet",
	"ontid": "did:ont:AXXxiWCuJXmuPGnsBji4cqWqV1VrKx8nkM",
	"ta_info": [
		{
			"claim_contexts": [
				"claim:sensetime_authentication"
			],
			"ontid": "did:ont:AXXxiWCuJXmuPGnsBji4cqWqV1VrKx8nkM"
		}
	],
	"signature":"sigvalue"
}
```



### DEMO

[JAVA DEMO](https://github.com/ontio/documentation/blob/master/pro-website-docs/assets/Demo.java)

[TS DEMO](https://github.com/ontio/documentation/blob/master/pro-website-docs/assets/OntIdSignDemo.js)


