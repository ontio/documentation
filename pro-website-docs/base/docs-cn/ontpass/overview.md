<h1 align="center">ONTPass认证产品介绍 </h1>

## ONTPass能为你做什么？

如果您是一个应用平台或开发者，你需要基于ONT ID实名认证您的用户。

ONTPass基于ONTID及本体信任生态，是一个开放的、去中心化的认证平台，为人、财、物、事提供丰富的认证服务。本体信任生态已聚集了提供全球身份认证服务能力的信任锚，包括IdentityMind、CFCA、商汤科技、Shufti Pro等等，同时还支持邮箱、手机、社交媒体认证方式。详细[了解本体信任锚](https://info.ont.io/trust-anchor/en)。

ONTPass具有以下优势：

* 本体信任生态已经连接了全球的认证服务机构，覆盖218个国家的用户，支持多种证件类型；
* 基于本体区块链，所有认证动作和认证结果被区块链存证。
* 规范支持零知识证明等密码学算法，用户可以选择性出示自己的身份信息，最大限度保护用户隐私。

## 开始使用

本文用于指导认证需求方如何接入本体，并使用ONTPass提供的认证服务，流程中涉及到的参与方包括：

* 认证需求方（Requester）: 需要对人，物，事进行认证的DApp，机构或服务场景，是本体信任生态中认证服务的需求方。
* ONTPass：基于ONTID及本体信任生态，是一个开放的、去中心化的认证平台，为人、财、物、事提供丰富的认证服务。ONTPass协同用户和需求方进行数据交换，数据全程被加密，保护用户隐私数据。


### 了解和ONTPass的交互流程

![交互流程说明](http://assets.processon.com/chart_image/5a5fff53e4b0abe85d5e3e5f.png)


- 1：ONTPass提供了公开的认证服务集市，认证需求方可以到ONTPass平台浏览并选定自己需要的TrustAnchor及其认证服务。认证需求方确认所需的认证服务后，需要到ONTPass平台注册相关基本信息，包括ONT ID，基本简介，所需的认证服务及回调地址。
- 2：认证需求方根据TrustAnchor身份认证的要求，将用户数据提交到ONTPass ,ONTPass转交给TrustAnchor。
- 3.1：TrustAnchor对用户进行身份认证，完成可信声明签发。
- 3.2：可信声明基本信息链上存证。
- 4：TrustAnchor完成可信声明签发后，将可信声明用用户ONT ID对应的公钥进行端到端加密传输到ONTPass。
- 5：ONTPass根据回调地址将认证结果推送到认证需求方。
- 6：认证需求方在区块链上验证数据。

## 接入步骤

### Step 1: 发现认证服务

本体信任生态中的信任源TrustAnchor将认证服务和可信声明模板信息注册到ONTPass中，ONTPass对外提供认证服务集市。认证服务集市完全开放，认证需求方可以从ONTPass的认证服务集市选择自己需要的认证服务。

ONTPass目前已经对外开放的认证服务包括：

#### 全球身份认证服务  Global Identity Authentication Service

认证模板:

| Claim_Templete_Name | Claim_Description | 
| :-----------------: | :----------------:|
|claim:sfp_passport_authentication | 全球用户护照认证   |
|claim:sfp_idcard_authentication   | 全球用户身份证认证 |
|claim:sfp_dl_authentication       | 全球用户驾照认证   |


### Step 2: 确定收费模式

使用ONTPass需要支付一定的费用，ONTPass支持两种收费模式，您需要根据您的情况选择合适的支付方式。

* 模式一：即时支付模式

即时支付模式是完全开放并自治化，即每次认证请求都需要消耗ONG手续费，所以认证需求方在每次认证请求时都需要构造一笔ONG转账交易（收款地址和具体金额由各个TrustAnchor指定）。收到认证请求后由TrustAnchor先将交易发送到链上，交易发送成功后才会继续后续的身份认证流程。

认证需求方在每次认证请求时都需要构造一笔ONG转账交易（收款地址是**ATGJSGzm2poCB8N44BgrAccJcZ64MFf187**）。

每次认证费用：*1.2 ONG*

* 模式二：后付费模式

如果选择后付费模式，你需要联系[本体机构合作](https://info.ont.io/cooperation/zh)。


### Step 3:  ONTPass平台注册


**测试环境域名：https://api.ont.network**

认证需求方选定所需的TrustAnchor提供的认证服务后，需要到ONTPass平台注册相关信息，主要包括ONT ID，基本简介，所需认证服务及回调地址。只有在平台注册过的需求方才会收到后续的可信声明回调推送。

> 如何拥有自己的ONT ID并进行签名，可参考[附录DEMO](https://pro-docs.ont.io/#/docs-cn/ontpass/ontpass-auth?id=demo)


#### 认证需求方注册API

```json
Host：域名+/api/v1/ontpass/authrequesters
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
|    signature |   String|  需求方使用ONT ID私钥按照[签名规则](http://pro-docs.ont.io/#/docs-cn/ontpass/specification?id=%E7%AD%BE%E5%90%8D%E5%8F%8A%E9%AA%8C%E7%AD%BE)对请求内容的签名  |Y|


| ResponseField     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    version|   string|  版本号。目前是1.0|
|    action|   string|  Register|
|    error|   int|  错误码。可参考[错误码字典](http://pro-docs.ont.io/#/docs-cn/ontpass/ontpass-auth?id=%E9%94%99%E8%AF%AF%E7%A0%81%E5%AD%97%E5%85%B8)|
|    result|   Boolean|  true：注册成功  false：注册失败|


> 为保证数据传输安全性，需求方注册的回调接口必须是https+域名形式，同时需求方需保证注册的回调接口高可用性且接受ONTPass标准的https的post请求



### Step 4: 向ONTPass提交认证

需求方在ONTPass认证集市选定认证模板后，需向TrustAnchor提交认证数据。由TrustAnchor进行身份认证，可信声明签发，可信声明基本信息存证，并使用端到端加密传输可信声明到ONTPass。

* 首先提交数据到临时存储

```json
Host：域名+/api/v1/ontpass/authentication/doc
Method：POST /HTTP/1.1
Content-Type: application/json
RequestExample：
{
    "auth_id":"123345667878780052",
    "claim_template":"claim:sfp_passport_authentication",
    "country":"CN",
    "doc_type":"passport",
    "frontdoc":"data:image/jpeg;base64,/9j/4AAQSkZJRgABAQAAkACQAAD...",
    "backdoc":"data:image/jpeg;base64,/9j/4AAQSkZJRgABAQAAkACQAAD...",
    "owner_ontid":"did:ont:AJua7C6teoFUs2KhRecqbfbPwrF99kHHgj",
    "doc_id":"12345678"
}

{
  "action": "DocsSubmit",
  "error": 0,
  "desc": "SUCCESS",
  "version": "1.0",
  "result": true
}
```


| Field_Name | Required |  Format | Description |
| :-----------------: | :----------------:| :------: | :------: |
|auth_id | yes | string 20-255 characters Length | 请求认证编码，需保证唯一性。在后续认证过程中只做透传|
|owner_ontid | yes | string | 用户ONT ID |
|claim_template | yes | string | 认证模板 |
|create_ontid_tx | yes | string | 用户ONT ID上链交易 |
|country | yes | string 2 characters Length | 两位国家代码，参照ISO 3166-1 alpha-2编码标准。支持的国家及对应的国家编码可查询[认证支持国家列表](http://pro-docs.ont.io/#/docs-cn/ontpass/specification?id=%E8%AE%A4%E8%AF%81%E6%94%AF%E6%8C%81%E5%9B%BD%E5%AE%B6%E5%88%97%E8%A1%A8) |
|doc_type | yes | string  | 证件类型  护照 passport 身份证 id_card  驾照 driving_license|
|doc_id | no | string | 证件编号 |
|frontdoc | no | JPG, JPEG, PNG, PDF | 16MB 证件照正面的base64编码  |
|backdoc | no | JPG, JPEG, PNG, PDF | 16MB 证件照反面的base64编码  |


| Field_Name  |  Format | Description |
| :-----------------: | :----------------: | :------: |
|version | String | 版本号，目前是1.0。|
|action | String | 固定值：DocsSubmit。|
|error | int | 错误码 |
|desc | String | 错误信息。成功即SUCCESS，其他即错误信息|
|result | boolean | true：即提交成功  false：即提交失败|


* 提交认证请求

```json
Host：域名+/api/v1/ontpass/authentication
Method：POST /HTTP/1.1
Content-Type: application/json
RequestExample：
{
    "auth_id":"123345667878780052",
    "app_ontid":"did:ont:AcbVUAXkJSKy7g43KHW378pBwA48Ywbuuw",
    "app_signature":"111111111111111111111"
}

{
  "action": "AuthReq",
  "error": 0,
  "desc": "SUCCESS",
  "version": "1.0",
  "result": true
}
```

### Step 5: 获取认证结果

ONTPass会根据认证需求方之前注册的回调地址，将认证结果和签发的可信声明推送到需求方。

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

#### 错误码字典

| Field | Type | Description |
| :--- | :--- | :--- |
| 0 | int | SUCCESS. 成功 |
| 61001 | int | FAIL, param error. 参数错误 |
| 61002 | int | FAIL, ONTID not exist. ONTID不存在 |
| 62003 | int | FAIL, inner communicate fail. 内部通信异常 |
| 62006 | int | FAIL, verify signature fail. 验签失败 |
| 62007 | int | FAIL, txn toaddress error or amount insufficient. 交易收款地址错误或金额不足 |
| 62008 | int | FAIL, send transaction fail. 交易发送失败 |
| 63001 | int | FAIL, inner error. 内部异常 |



### DEMO

[JAVA DEMO](https://github.com/ontio/documentation/blob/master/pro-website-docs/assets/Demo.java)

[TS DEMO](https://github.com/ontio/documentation/blob/master/pro-website-docs/assets/OntIdSignDemo.js)

