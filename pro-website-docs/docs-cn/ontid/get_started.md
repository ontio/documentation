<h1 align="center">ONT ID 应用快速开发指南 </h1>

## 谁需要看这篇文档

我们假定您是一个移动端应用（以下简称：应用方），已经清楚ONT ID的概念，并且知道ONT ID能为您做什么。现在，您需要使用ONT ID为认证您的用户或者为你的用户管理数字身份，包括ONT ID创建、认证、管理、授权。

## 什么是 ONT ID Connector

ONT ID Connector是基于Android 和 iOS开发的集成组件，便于您的APP轻松集成，ONT ID Connector帮助您的应用实现ONT ID创建、认证、管理、授权。

## 1. 前置准备

ONTPass基于ONTID及本体信任生态，是一个开放的、去中心化认证服务平台，为您提供KYC（Know Your Customer）服务和多种用户认证服务。本体信任生态已聚集了提供全球身份认证服务能力的信任锚，包括IdentityMind、CFCA、商汤科技、Shufti Pro等等，同时还支持邮箱、手机、社交媒体认证方式。

您首选需要在ONTPass平台注册， 具体参考[>> ONTPass 认证需求方注册](https://pro-docs.ont.io/#/docs-cn/ontpass/ontpass-auth)

ONTPass支持两种收费模式，建议选择后付费模式。

* 模式一：即时支付模式

即时支付模式是完全开放并自治化，即每次认证请求都需要消耗ONG手续费，所以认证需求方在每次认证请求时都需要构造一笔ONG转账交易（收款地址和具体金额由各个TrustAnchor指定）。收到认证请求后由TrustAnchor先将交易发送到链上，交易发送成功后才会继续后续的身份认证流程。

* 模式二：后付费模式

如果选择后付费模式，你需要联系[本体机构合作](https://info.ont.io/cooperation/zh)。

## 2. 创建数字身份

* 标准ONT ID的创建流程

![](https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/register.png)

应用方需要保存好ONT ID和认证状态，ONT ID Connector可以定期和Server同步状态。 

* 典型的页面流程：

ONT ID Connector将引导用户输入ONT ID密码，并进行ONTPass的认证，让用户输入必要的认证信息。 

![输入密码](https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/ui-register.jpg) 


### 2.1 APP调用ONT ID Connnector

```
	{
		"action": "registerONTID",
		"version": "v1.0.0",
		"signature_service":"https://app/server/sign"
	}
```


### 2.2 应用server提供签名服务

应用server提供基于ONI ID私钥的签名服务，具体参考SDK。



### 2.3 收到认证结果

ONTPass会根据认证应用注册的回调地址，将认证结果和签发的可信声明推送到应用。**应用方应该记录ONT ID的认证状态和认证模板claim_context**

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
|    auth_flag |   Boolean|  认证结果 true：认证通过  false：认证未通过  |Y|
|    auth_id |   String|  需求方认证时传给TrustAnchor的认证编号  |Y|
|    claim_context |   String|  可信声明模板标识  |Y|
|    description|   String|  若认证失败，即失败原因。若认证成功，即可信声明描述 |Y|
|    encrp_origdata|   String|  加密后的可信声明 |Y|
|    ontid|   String|  ONTPass的ONT ID  |Y|
|    owner_ontid|   String|  用户的ONT ID   |Y|
|    ta_ontid|   String|  TrustAnchor的ONT ID   |Y|
|    txnhash |   String|  可信声明存证交易hash  |Y|
|    signature |   String|  ONTPass使用ONT ID私钥按照[签名规则](https://pro-docs.ont.io/#/docs-cn/ontpass/ontpass-auth?id=%E4%BD%BF%E7%94%A8ont-id%E7%AD%BE%E5%90%8D%E9%AA%8C%E7%AD%BE)对请求内容的签名  |Y|





## 3. 查询链上身份DDO

当链上成功注册一个ONT ID，链上将形成一个ONT ID对象，我们称之为DDO。查询DDO，最简单的办法是通过[本体区块链浏览器](https://explorer.ont.io)查询，或者您也可以通过SDK查询。

通过SDK查询的方式如下：

首先构建交易
````
import {OntidContract} from 'ontology-ts-sdk';
//we use identity's ONT ID to create the transaction
const tx = OntidContract.buildGetDDOTx(identity.ontid)
````

发送交易 查询交易不需要消耗gas，也就不需要指定payer和payer的签名。发送交易方法的第二个参数表示发送的是否是预执行的交易。预执行的交易只在接收到它的节点上运行，不需要等待共识。一般用来查询数据。
````
import {RestClient} from 'ontology-ts-sdk';
const rest = new RestClient();
rest.sendRawTransaction(tx, true).then(res => {
    console.log(res);
}
````

返回的结果如下：
````
{ Action: 'sendrawtransaction',
      Desc: 'SUCCESS',
      Error: 0,
      Result:
       { State: 1,
         Gas: 20000,
         Result: '26010000002103547c5abdbe66677ba7001cefd773f01a19c6360b15ee51c6db43911f046564fc0000' },
      Version: '1.0.0' }
````

Result 就是序列化后的DDO（ONT ID object） 我们可以通过反序列化得到详细数据。
````
const ddo = DDO.deserialize(response.Result.Result);
console.log(ddo);
````


## 4 ONT ID授权

ONT ID授权指的是把用户已经获得的认证，授权给某个DAPP场景方，比如在CandyBox场景中，用户需要将授权信息提供给Candy项目方，才可以获得Candy。 流程是这样的：

![](http://assets.processon.com/chart_image/5c20885ce4b0bcd70c453a32.png)


第一步，钱包应用需要通过页面跳转方式访问ONTPass授权服务：
https://api.ont.network/api/v1/ontpass/auth

```
	{
		"action":"auth",
		"version":"v1.0.0",
		"params":{
			"seqno":"0001",
			"user_ontid":"did:ont:Assxxxxxxxxxxxxx",
			"app_ontid":"did:ont:Assxxxxxxxxxxxxx",
			"to_ontid":"did:ont:Assxxxxxxxxxxxxx",
			"redirect_uri":"http://candybox.com/",
			"auth_templete":"authtemplate_kyc01"
		},
		"app_signature":"AXFqy6w/xg+IFQBRZvucKXvTuIZaIxOS0pesuBj1IKHvw56DaFwWogIcr1B9zQ13nUM0w5g30KHNNVCTo14lHF0=";
		"user_signature":"AXFqy6w/xg+IFQBRZvucKXvTuIZaIxOS0pesuBj1IKHvw56DaFwWogIcr1B9zQ13nUM0w5g30KHNNVCTo14lHF0=";
	}
```

| 参数         | 是否必须                                      | 说明                                     | 
| ------------ | ---------------------------------------- |  ------------------ |
| seqno        | 是                                 |  序列号，发起方自行管理，最大12位字符和数字，不重复 |
| user_ontid         | 是                                 |  场景方ONT ID |
| app_ontid         | 是                                 |  第三方应用ONT ID（钱包方） |
| to_ontid         | 是                                 |  场景方ONT ID |
| redirect_uri         | 是                                 |  场景方接受地址 |
| auth_templete         | 是                                 | 授权模板编号，用于明确授权方授权需求，具体参考ONTPass定义 |
| app_signature         | 是                                 |  应用方签名，对整个Param进行签名，使用from_ontid的私钥按照标准的ECDSA算法签名。  |
| user_signature         | 否                                 |  用户签名，可选项。  |


| redirect_uri         | 是                                 |  场景方接受地址 |
| auth_templete         | 是                                 | 授权模板编号，用于明确授权方授权需求，具体参考ONTPass定义 |
| app_signature         | 是                                 |  应用方签名，对整个Param进行签名，使用from_ontid的私钥按照标准的ECDSA算法签名。  |
| user_signature         | 否                                 |  用户签名，可选项。  |




## 5 ONT ID管理要求

钱包需要对ONT ID 提供管理功能，具体包括：

* **导入**，支持WIF 私钥和KeyStore两个方式导入；
* **查询**，生态合作伙伴钱包随时显示ONT ID的地址，并在输入密码的情况下，显示WIF私钥和 Keystore信息。 
* **管理**，生态合作伙伴钱包使用ONT ID Keystore存储规范存储，并随时可用用户使用；
