<h1 align="center">ONTPassONTPass Authentication Service Access Guide</h1>

## Overview

This tutorial will guide Requester to access the Ontology, and to use the authentication service provided by ONTPass. The participants involved in the process include:

* Requester: DApp, institution or service scenario that requires authentication of people, object or thing. Requester is the demand side of authentication service in the Ontology Trust Ecology.
* ONTPass: Based on ONTID and Ontology Trust Ecosystem, it is an open, decentralized authentication platform that provides rich authentication services for people, finances, objects, and things. ONTPass cooperates with users and requesters for data exchange, and data is encrypted and protected all the time to protect User's private data.
* TrustAnchor: Trust Anchor refers to the partner that provides certification services on  Ontology Trust Ecosystem. It may be government agencies, universities, banks, third-party certification service organizations (such as CA institutions), biometric technology companies, and so on.



## Understand the interaction process with ONTPass

![Interaction Process Description](https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/ontpass02.png)


- A0：ONTPass provides a public certification service market. Requester can browse and select the TrustAnchor Source and its authentication service they need on the ONTPass platform.
- A1：After the Requester confirms the  authentication service, it needs to register basic information to the ONTPass  platform. The information includes the ONT ID, basic introduction and callback address.
- A2：The authentication requester submits the user‘s data to the TrustAnchor Source according to the requirements of the TrustAnchor Source authentication.
- A3.1,A3.2：TrustAnchor authenticates the user and completes the issuance of the verifiable claim, which is stored on the basic information chain and the funds are delivered.
- A4：After the TrustAnchor Source issues the verifiable claim, the encrypted public key of the ONT ID, which corresponds to the verifiable claim user, is transmitted to the ONTPass end to end .
- A5：ONTPass pushes the verifiable claim to Requester according to the callback address.



## Access Step

### Step 1: iscovery Certification Service

TrustAnchor registers to the ONTPass the authentication service and verifiable claim template information to the ONTPass. The ONTPass provides the TrustAnchor authentication service market. Requester can select the certification service from the market.

The ONTPass authentication services that are currently open to the public include:

#### Global Identity Authentication Service

* TrustAnchor Name : Ontology Global Identity TrustAnchor
* TrustAnchor ONT ID :  did：ont：ANNmeSiQJVwq3z6KvKo3SSKGnoBqvwYcwt
* TrustAnchor Account Address : ATGJSGzm2poCB8N44BgrAccJcZ64MFf187
* Service list

| Claim_Templete_Name | Claim_Description |  DocLink |
| :-----------------: | :----------------:| :------: |
|claim:sfp_passport_authentication | Global User Passport Authenticatioin   | http://pro-docs.ont.io/#/docs-cn/ontpass/ONTTA |
|claim:sfp_idcard_authentication   | Global User ID Card Authentication | http://pro-docs.ont.io/#/docs-cn/ontpass/ONTTA |
|claim:sfp_dl_authentication       | Global User Driver License Authentication  | http://pro-docs.ont.io/#/docs-cn/ontpass/ONTTA |



### Step 2: Determine the charging mode

There is a fee for using ONTPass. ONTPass supports two charging modes. You need to choose the appropriate payment method according to your situation.

* Mode 1: Instant payment mode

The instant payment mode is completely open and autonomous, that is, each authentication request needs to consume the ONG fee, so the authentication requester needs to construct an ONG transfer transaction (The payment address and specific amount are specified by each TrustAnchor). After receiving the authentication request, TrustAnchor first sends the transaction to the chain, and the subsequent identity authentication process will continue after the transaction is successfully sent.

* Mode 2: Postpaid mode


If you choose post-paid mode, you need to contact [Ontology
Institutional cooperation](https://info.ont.io/cooperation/zh).


### Step 3:  ONTPass Platform Registion

After Requester selects the authentication service provided by the TrustAnchor in need, it needs to register the relevant information on the ONTPass platform, including the ONT ID, basic introduction,  authentication service in need, and callback address. Only  registered Requested on the platform will receive the subsequent verifiable claim callback.

> Please refer to [Appendix] for the method to have your own ONT ID
[AppendixDEMO](https://pro-docs.ont.io/#/docs-cn/ontpass/ontpass-auth?id=demo)


#### Requester Registers API

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
|    callback_addr |   String|  verifiable claim callback address  | Y|
|    description |   String|  Requester discription  | Y|
|    name|   String|  Requester's name |Y|
|    ontid|   String|  Requestes's ONT ID  | Y|
|    ta_info.claim_contexts |   list|  Select the list of verifiable claims templates for the TrustAnchor in need   | Y|
|    ta_info.ontid |   String|  Select the required TrustAnchor's ONT ID    | Y|
|    signature |   String|  The Requester uses the ONT ID private key to sign the requested content according to [Signature rule](https://pro-docs.ont.io/#/docs-cn/ontpass/ontpass-auth?id=%E4%BD%BF%E7%94%A8ont-id%E7%AD%BE%E5%90%8D%E9%AA%8C%E7%AD%BE)  |Y|


| ResponseField     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    result|   Boolean|  true：egister Success  false：Register Failure|


> In order to ensure data transmission's security, the callback interface must be in the form of https+domain name, and Requester must ensure that the registered callback interface is highly available and accepts the https post request that meets the ONTPass standard.



### Step 4: Submit Certification to TrustAnchor Source

After Requester selects the TrustAnchor authentication service in the ONTPass certification market, it needs to submit the authentication data to TrustAnchor. TrustAnchor then authenticates the identity, issues the verifiable claim, deposits basic information of the verifiable claim, and passes it to ONTPass through end-to-end encrypted transmission


- [Access Global Identity Authentication](http://pro-docs.ont.io/#/docs-cn/ontpass/ONTTA)


### Step 5: Get certification results

After TrustAnchor completes the user's information authentication and issues a verifialbe claim, the verifiable claim is sent to ONTPass. ONTPass pushes the signed verifialbe claim to Requester based on the callback address previously registered by Requester.


When the information is called back, the ONTPass platform will bring the signature corresponding to its own ONT ID. Requester can verify the signature, as well as the credibility and the non-tamperable features of the callback request.

```json
Host：callback address
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
|    auth_flag |   Boolean|  TrustAnchor authentication results true：authentication passed false：authentication failed  |Y|
|    auth_id |   String|  The authentication number passed to TrustAnchor when Requester is authenticated.  |Y|
|    claim_context |   String|  Verifiable claim template identifier  |Y|
|    description|   String|  The reason for the failure if the authentication fails; The description of verifiable claim, if the authentication is successful|Y|
|    encrp_origdata|   String|  encrypted verifiable claim |Y|
|    ontid|   String|  ONTPass's ONT ID  |Y|
|    owner_ontid|   String|  User's ONT ID   |Y|
|    ta_ontid|   String|  TrustAnchor's ONT ID   |Y|
|    txnhash |   String|  Hash of verifiable claim deposit transaction |Y|
|    signature |   String|  ONTPass uses ONT ID priviate key to sign the requested content[Signature Rules](https://pro-docs.ont.io/#/docs-cn/ontpass/ontpass-auth?id=%E4%BD%BF%E7%94%A8ont-id%E7%AD%BE%E5%90%8D%E9%AA%8C%E7%AD%BE) |Y|




### Appendix

#### Error Code Dictionary

| Field | Type | Description |
| :--- | :--- | :--- |
| 0 | long | SUCCESS. success |
| 61001 | long | FAIL, param error. parameter error |
| 61002 | long | FAIL, already exist. already exist |
| 61003 | long | FAIL, not found. not found|
| 62003 | long | FAIL, communication fail. Internal communication failure |
| 62006 | long | FAIL, FAIL, verify signature fail. signature verification failure |
| 63001 | long | FAIL, inner error. inner error |


#### Get your own ONT ID

Registering an ONT ID on Ontology requires an ONG fee. First, you need to have a digital asset account, and there are at least 0.01 ONGs in the account. Then use the account to pay the fee for registering ONT ID and complete the registration on the ONT ID chain.

> Please refer to [Appendix DEMO](https://pro-docs.ont.io/#/docs-cn/ontpass/ontpass-auth?id=demo) or [SDK developer documentation center](https://dev-docs.ont.io/#/docs-en/SDKs/00-overview)for method to create a digital asset account, to use the account to create an ONT ID, to obtain information about the ONT ID, and to do the signature


> TestNet ONG can be applied from Ontology Developer Center：[TestNet ONG Applicaiotn Gateway ](https://developer.ont.io/applyOng)

#### Use ONT ID to sign and verify a signature

**Signature Rules：**

The JSON object in the HTTP Post request body needs to be sorted in ascending alphabetical order of the key, then serialized into a standard JSON format string, then the request content string is signed, and finally the signature is added to the request body with the signature as the key. 

Take a registration request as an example：
After the JSON object of POST Request is sorted in ascending key order.
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
Convert it to standard JSON format string：

	{"callback_addr":"https://xxx","description":"coinwallet","name":"coinwallet","ontid":"did:ont:AXXxiWCuJXmuPGnsBji4cqWqV1VrKx8nkM","ta_info":[{"claim_contexts":["claim:sensetime_authentication"],"ontid":"did:ont:AXXxiWCuJXmuPGnsBji4cqWqV1VrKx8nkM"}]}

Then Sign the JSON format string(For Signer's Operation，please refer to[Appendix DEMO]() or [SDK deverloper documentation center](https://dev-docs.ont.io/#/docs-en/SDKs/00-overview))，after getting sigvalue，add the signature as the key to the JSON object of the Post request body.

Finally Authentication Post Body Object is：
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
