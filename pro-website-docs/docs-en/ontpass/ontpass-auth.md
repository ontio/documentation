<h1 align="center">ONTPass Authentication Service Access Guide</h1>

## Overview

This tutorial will guide the service requester to access Ontology and use the authentication services provided by ONTPass. The participants involved in the process include:

* Requester: dApps, institutions, or services which requires authentication of people, objects, or things. The requester is the demand side of authentication services in the Ontology trust ecosystem.
* ONTPass: A decentralized identity transaction platform based on the Ontology blockchain. ONTPass is mainly used to exchange data between users and the Requester. The data is encrypted at all times, and ONTPass does not touch the user's private data.
* TrustAnchor Sources: The multiple trust sources in the Ontology trust ecosystem. They can provide authentication services for people, objects, and things in the real world and issue verifiable claims. It can be connected to identity authentication service providers worldwide, or it can be a self-trust source.


## Interaction Process Description


![Interaction Process Description](https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/ontpass02.png)


- A0: ONTPass provides a public certification service market. The Requester can browse and select the TrustAnchor Source and authentication service they need on the ONTPass platform.
- A1: After the Requester confirms the  authentication service, it needs to register basic information to the ONTPass  platform. The information includes the ONT ID, basic introduction, and callback address.
- A2: The authentication requester submits user data to the TrustAnchor Source according to the requirements of the TrustAnchor Source authentication.
- A3.1, A3.2：The TrustAnchor Source authenticates the user, issues the verifiable claim, and invokes the smart contract to distribute the profit and attest the verifiable claim on the blockchain.
- A4: After the TrustAnchor Source issues the verifiable claim, the encrypted public key of the ONT ID, which corresponds to the verifiable claim user, is transmitted to ONTPass.
- A5: ONTPass pushes the verifiable claim to Requester according to the callback address.


## Access Steps

### 1. Discovery Certification Service

TrustAnchor Source registers to the authentication service and verifiable claim template information to ONTPass. ONTPass provides the TrustAnchor Source authentication service market. The Requester can then select the certification service from the market.

<table>
<tr>
	<td>TAS_OntId</td>
	<td>TAS_Description</td>
	<td>Claim_Context</td>
	<td>Claim_Description</td>
	<td>PersonalKeyInfo</td>
	<td>Provider</td>
	<td>DocLink</td>
</tr>
<tr>
    <td rowspan="2">did:ont:ARr6ApK24EU7nu<br/>fND4s1SWpwULHBertpJb</td>
    <td rowspan="2">Ontology China Identity TrustAnchor Source</td>
    <td>claim:cfca_authentication</td>
	<td>Chinese Citizen Real-name Authentication</td>
	<td>Name, ID Card Number</td>
	<td>CFCA</td>
	<td>https://www.trustasia.com/cfca?bdcpc&b_scene_zt=1</td>
</tr>
<tr>
    <td>claim:sensetime_authentication</td>
	<td>Chinese Citizen Real-name Authentication</td>
	<td>Name, ID Card Number</td>
	<td>SenseTime</td>
	<td>https://www.sensetime.com/authentication/87</td>
</tr>
<tr>
    <td rowspan="6">did:ont:AcbVUAXkJSKy7g<br/>43KHW378pBwA48Ywbuuw<br/></td>
    <td rowspan="6">Ontology Global Identity TrustAnchor Source</td>
    <td>claim:sfp_passport_authentication</td>
	<td>Global User Passport Certification</td>
	<td><nobr>Name, Nationality, Date of Birth, Document Number, Date of Issue, Expiration Date</nobr></td>
	<td>ShuftiPro</td>
	<td>https://github.com/shuftipro/RESTful-API-v1.3</td>
</tr>
<tr>
    <td>claim:sfp_idcard_authentication</td>
	<td>Global User ID Certification</td>
	<td><nobr>Name, Nationality, Date of Birth, Document Number, Date of Issue, Expiration Date</nobr></td>
	<td>ShuftiPro</td>
	<td>https://github.com/shuftipro/RESTful-API-v1.3</td>
</tr>
<tr>
    <td>claim:sfp_dl_authentication</td>
	<td>Global User License Certification</td>
	<td><nobr>Name, Nationality, Date of Birth, Document Number, Date of Issue, Expiration Date</nobr></td>
	<td>ShuftiPro</td>
	<td>https://github.com/shuftipro/RESTful-API-v1.3</td>
</tr>
<tr>
    <td>claim:idm_passport_authentication</td>
	<td>Global User Passport Certification</td>
	<td><nobr>Name, Nationality, Document Number</nobr></td>
	<td>IdentityMind</td>
	<td>https://identitymindglobal.com/identity-link-api/</td>
</tr>
<tr>
    <td>claim:idm_idcard_authentication</td>
	<td>Global User ID Certification</td>
	<td><nobr>Name, Nationality, Document Number</nobr></td>
	<td>IdentityMind</td>
	<td>https://identitymindglobal.com/identity-link-api/</td>
</tr>
<tr>
    <td>claim:sfp_dl_authentication</td>
	<td>Global User License Certification</td>
	<td><nobr>Name, Nationality, Document Number</nobr></td>
	<td>IdentityMind</td>
	<td>https://identitymindglobal.com/identity-link-api/</td>
</tr>
</table>



### 2. ONTPass Platform Registion

After selecting the authentication service, Requester needs to register relevant information to the ONTPass platform. The information includes the ONT ID, basic introduction, and callback address. Only the registered Requester ONT ID will receive the subsequent verifiable claim callback.

  For how to have your own ONT ID and sign it, please refer to the [Appendix]().


#### Request Registers API

```json
Host：https://app.ont.io/S1/api/v1/ontpass/authrequester
Method：POST /HTTP/1.1
Content-Type: application/json
RequestExample：
{
	"OntId":"did:ont:AHq7ApK24H97nufND4s1SWpwULHBertoik",
	"Name":"COO",
	"Desc":"COO BlockChain",
	"CallBackAddr":"https://coo.chain/user/authentication",
	"Signature":"AXF1y6w/xg+IFQBRZvucKXvBYIZaIxOS0pesuBj12KHvw56DaFwWogIcr1B9zQ13nUM0w5g30KHNNVCTo14lHF0="
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
|    OntId|   String|  Requester ONT ID  | Y|
|    Name|   String|  Name of Requester  | Y|
|    Desc|   String| Description of Requester |Y|
|    CallBackAddr|   String|  Callback Address, which meets https+ domain name, and receives post callback request to get verifiable claim information. | Y|
|    Signature|   String|  The Requester uses the private key of its own ONT ID to sign based on the standard ECDSA algorithm.| Y|


| ResponseField     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    Result|   Boolean|  True: Register Success, false: Register Failure|


> Note: In order to ensure data transmission security, the callback interface must be in the form of https+domain name, and Requester must ensure that the registered callback interface is highly available and accepts the https post request that meets the ONTPass standard.


### 3. Submit Certification to TrustAnchor Source

Requester submits the certification data according to the certification requirements of the TrustAnchor Source authentication service selected in the first step. TrustAnchor Source conducts the Identity Authentication, issues end-to-end encrypted verifiable claim, and invokes the smart contract for asset distribution and basic information attestation.


### 4. Get Verifiable Claim

After TrustAnchor Source completes the user's information authentication and issues a verifiable claim, the verifiable claim is sent to ONTPass. ONTPass pushes the signed verifiable claim to Requester based on the callback address previously registered by Requester.


```json
Host：Callback Address
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
|    OntPassOntId|   String|  ONT ID of ONTPass Platform  | Y|
|    Claims.UserOntId|   String|  ONT ID of User  | Y|
|    Claims.Context|   String|  User verifiable claim template identifier  | Y|
|    Claims.EncryOrigData|   String|  Encrypted verifiable claim | Y|
|    Signature|   String|  ONTPass signs for requested information | Y|




### Appendix


#### How to have your own ONT ID and sign it

A TestNet ONT ID can be registered on-chain for free using ONTPass. TestNet ONT ID registration can be completed by directly calling the following API:

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
|    OntId|   String | ONT ID |
|    Salt|   String | Salt, safety parameter |
|    Scrypt-N|   int | Encrypted parameter. This parameter is related to the subsequent import of the ONT ID operation. |
|    EncryptedPriKey|   String | Encrypted private key |
|    Password|   String | ONT ID private key password |
|    PrivateKey|   String | Private key |

It is recommended that MainNet ONT ID be registered from the [ONTO Client](https://onto.app). Please remember your password and export the keystore for backup. The keystore includes salt, encrypted private key, ONT ID, and other information.

An example of a keystore:
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
|    scrypt.n|   int | Encrypted parameter. This parameter is related to the subsequent import of the ONT ID operation.|
|    key|   String | Encrypted private key |
|    salt|   String | Salt, safety parameter  |
|    address|   String | ONT ID suffix address. Plus did:ont: makes the full ONT ID. |

If you already have a digital asset account and hold at least 0.01 ONG, you can also use various SDKs to create an ONT ID and obtain relevent information.

You can also use SDKs for signature verification and other operations using ONT ID.

You can also take a look at identity-related operations such as ONT ID signature verification [sample code](https://github.com/ontio/ontology-DID/blob/master/docs/cn/thirdparty_kyc_cn.md#%E5%8F%82%E8%80%83%E4%BB%A3%E7%A0%81) or [SDK development documentation](https://ontio.github.io/documentation/ontology_overview_sdks_en.html).

