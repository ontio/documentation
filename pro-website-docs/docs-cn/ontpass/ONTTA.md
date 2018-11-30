<h1 align="center">ONTTA认证服务对接指导</h1>

## 概述

ONTTA作为Ontology信任生态上的一个综合性的全球身份认证信任源，可对全球200+国家的公民进行护照，驾照，身份证OCR认证并签发对应的可信声明。为Ontology信任生态中的身份认证需求方提供了多维度、高准确性、全球化的身份认证服务。

提供的认证服务包括：

- 护照OCR认证
- 驾照OCR认证
- 身份证OCR认证

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
</tr>
<tr>
    <td>claim:sfp_idcard_authentication</td>
	<td>全球用户身份证认证</td>
	<td><nobr>姓名，国籍，出生日期，证件号，签发日期，过期日期</nobr></td>
	<td>Shuftipro</td>
</tr>
<tr>
    <td>claim:sfp_dl_authentication</td>
	<td>全球用户驾照认证</td>
	<td><nobr>姓名，国籍，出生日期，证件号，签发日期，过期日期</nobr></td>
	<td>Shuftipro</td>
</tr>
</table>


## 认证模式

现在身份认证是**单笔小额付费**模式，即每次身份认证请求都需要消耗ONG手续费，所以认证需求方在每次认证请求时都需要构造一笔ONG转账交易（收款地址是**ATGJSGzm2poCB8N44BgrAccJcZ64MFf187**，金额即每次身份认证的手续费）。收到认证请求后由TrustAnchor先将交易发送到链上，交易发送成功后才会继续后续的身份认证流程。

如何构造转账交易可参考[附录DEMO](http://pro-docs.ont.io/#/docs-cn/ontpass/ONTTA?id=%E7%A4%BA%E4%BE%8Bdemo)或[SDK开发者文档中心](https://dev-docs.ont.io/#/docs-en/SDKs/00-overview)

## 认证请求示例

```json
Host：/api/v1/trustanchor/ocr/authentication
Method：POST /HTTP/1.1
Content-Type: application/json
RequestExample:
{
	"auth_id":"xxxxxxxxx",
	"backdoc":"image/png;base64,iVBORw0KGgoAAAANSUhmJlglqxaRSiRX/sIyvoGKIRmJM5WHUcAeKwnHAcY...",
	"country":"CN",
	"doc_type":"passport",
	"frontdoc":"image/png;base64,iVBORw0KGgoAAAAADAFBMVEVHcEwAAAAAAAAAAAAAAAAAAA...",
	"ontid":"did:ont:AcbVUAXkJSKy7g43KHW378pBwA48Ywbuuw",
	"owner_ontid":"did:ont:AcbVUAXkJSKy7g43KHW378pBwA48Ywbuuw",
	"txn_body":"",
	"txn_hash":"",
	"signature":""
}
SuccessResponse：
{
    "action": "ShuftiproApply",
    "error": 0,
    "desc": "SUCCESS",
    "version": "1.0",
    "result": true
}
```

## RequestField

* ### auth_id

	Required: **Yes**
	
	Type: **string**
	
	Minimum: **20 characters**
	
	Maximum: **255 characters**

	请求认证编码，需保证唯一性。在后续认证过程中只做透传。


* ### backdoc

	Required: **Yes**
	
	Type: **string**
	
	Format: **JPG, JPEG, PNG, PDF**
	
	Maximum: **16MB**

	证件照反面的base64编码。


* ### country

	Required: **Yes**
	
	Type: **string**
	
	Length: **2 characters**

	两位国家代码，参照ISO 3166-1 alpha-2编码标准。支持的国家及对应的国家编码可查询[认证支持国家列表](http://pro-docs.ont.io/#/docs-cn/ontpass/ONTTA?id=%E8%AE%A4%E8%AF%81%E6%94%AF%E6%8C%81%E5%9B%BD%E5%AE%B6%E5%88%97%E8%A1%A8)


* ### doc_type

	Required: **Yes**
	
	Type: **string**
	
	Supported Types: **passport，id_card，driving_license**

	证件类型  护照:passport 身份证:id_card  驾照:driving_license


* ### frontdoc

	Required: **Yes**
	
	Type: **string**
	
	Image Format: **JPG, JPEG, PNG, PDF**
	
	Maximum: **16MB**

	证件照正面的base64编码。


* ### ontid

	Required: **Yes**
	
	Type: **string**

	请求方的ONT ID。


* ### owner_ontid

	Required: **Yes**
	
	Type: **string**

	用户的ONT ID。


* ### txn_body

	Required: **Yes**
	
	Type: **string**

	构造好的转账交易体。


* ### txn_body

	Required: **Yes**
	
	Type: **string**

	构造好的转账交易hash。


* ### signature

	Required: **Yes**
	
	Type: **string**

	请求方使用ONT ID私钥按照[签名规则](http://pro-docs.ont.io/#/docs-cn/ontpass/ONTTA?id=%E7%AD%BE%E5%90%8D%E5%8F%8A%E9%AA%8C%E7%AD%BE)对请求内容的签名。

--------------------------------------------------------
## ResponseField

* ### version

	Type: **string**

	版本号，目前是1.0。


* ### action

	Type: **string**

	固定值：AuthApply


* ### error

	Type: **long**

	错误码。具体可参照[错误码字典](http://pro-docs.ont.io/#/docs-cn/ontpass/ONTTA?id=%E9%94%99%E8%AF%AF%E7%A0%81%E5%AD%97%E5%85%B8)


* ### desc

	Type: **string**

	错误信息。成功即SUCCESS，其他即错误信息


* ### result

	Type: **boolean**

	true：即提交成功  false：即提交失败


## 错误码字典


| Field | Type | Description |
| :--- | :--- | :--- |
| 0 | long | SUCCESS. 成功 |
| 61001 | long | FAIL, param error. 参数错误 |
| 62003 | long | FAIL, communication fail. 内部通信异常 |
| 62006 | long | FAIL, verify signature fail. 验签失败 |
| 62007 | long | FAIL, transaction error. 交易异常 |
| 62008 | long | FAIL, send transaction fail. 交易发送失败 |
| 63001 | long | FAIL, inner error. 内部异常 |



## 认证支持国家列表


Country Name       | Language Code
---------          | -----------
Afrikaans | AF
Albanian | SQ
Amharic | AM
Arabic | AR
Armenian | HY
Azerbaijani | AZ
Basque | EU
Belarusian | BE
Bengali | BN
Bosnian | BS
Bulgarian | BG
Burmese | MY
Catalan | CA
Chichewa | NY
Chinese | ZH
Corsican | CO
Croatian | HR
Czech | CS
Danish | DA
Dutch | NL
English | EN
Esperanto | EO
Estonian | ET
Filipino | TL
Finnish | FI
French | FR
Frisian | FY
Galician | GL
Georgian | KA
German | DE
Greek (modern) | EL
Gujarati | GU
Haitian, Haitian Creole | HT
Hausa | HA
Hebrew (modern) | HE
Hindi | HI
Hungarian | HU
Indonesian | ID
Irish | GA
Igbo | IG
Icelandic | IS
Italian | IT
Japanese | JA
Javanese | JV
Kannada | KN
Kazakh | KK
Khmer | KM
Kirghiz, Kyrgyz | KY
Korean | KO
Kurdish | KU
Latin | LA
Luxembourgish, Letzeburgesch | LB
Lao | LO
Lithuanian | LT
Latvian | LV
Macedonian | MK
Malagasy | MG
Malay | MS
Malayalam | ML
Maltese | MT
Maori | MI
Marathi | MR
Mongolian | MN
Nepali | NE
Norwegian | NO
Punjabi | PA
Persian | FA
Polish | PL
Pashto | PS
Portuguese | PT
Romanian | RO
Russian | RU
Sindhi | SD
Samoan | SM
Serbian | SR
Scottish Gaelic | GD
Shona | SN
Sinhala | SI
Slovak | SK
Slovenian | SL
Somali | SO
Sesotho | ST
Spanish | ES
Sundanese | SU
Swahili | SW
Swedish | SV
Tamil | TA
Telugu | TE
Tajik | TG
Thai | TH
Turkish | TR
Ukrainian | UK
Urdu | UR
Uzbek | UZ
Vietnamese | VI
Welsh | CY
Xhosa | XH
Yiddish | YI
Yoruba | YO
Zulu | ZU


## 签发的可信声明模板

遵循Ontology标准的可信声明规范格式：

	base64(Header)'.'base64(Payload)'.'base64(Signature)'.'base64(MerkleProof)

Payload里认证信息clm格式如下：

```
{
	"clm":{
		"Nationality": "US",
		"Name":"john smith",
		"BirthDay":"1990-01-01",
		"IssueDate":"2000-01-01",
		"ExpirationDate":"2020-01-01",
		"IDDocNumber":"510807199001012551",
		"IssuerName":"Shuftipro"
	}
}

```
| Field     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    Nationality |   String|  两位国家代码，参照ISO 3166-1 alpha-2编码标准  |
|    Name |   String|  姓名  |
|    BirthDay|   String|  出生日期。格式：yyyy-mm-dd|
|    IssueDate|   String|  证件签发日期。格式：yyyy-mm-dd |
|    ExpirationDate |   String|  证件过期日期。格式：yyyy-mm-dd    |
|    IDDocNumber|   String|  证件号    |
|    IssuerName |   String|  ONTTA  |


## 附录

### 签名及验签

为保证请求的不可篡改性，可验证性，每次认证需求方发起认证时都需要使用自己的ONT ID对应的私钥对请求内容进行签名，TrustAnchor会对每次认证请求数据进行验签。

**签名规则：**

HTTP Post请求体里的JSON对象需要按照key的字母升序排序，然后序列化为标准的JSON格式字符串，再对该请求内容字符串进行签名，最后再把签名以signature为key添加到请求体里的JSON对象中。

以某次OCR认证请求为例：
POST请求的JSON对象按照key升序排序后的JSON为
```
{
	"auth_id":"1233211233211233211123312",
	"backdoc":"image/png;base64,iVBORw0KGgoAAAANSUhmJM5WHUcAeKwnHAcY...",
	"country":"CN",
	"doc_type":"passport",
	"frontdoc":"image/png;base64,iVBORw0KGgoAAAAADAFBMAAAAAAAAAAAAAAA...",
    	"ontid":"did:ont:AcbVUAXkJSKy7g43KHW378pBwA48Ywbuuw",
	"owner_ontid":"did:ont:AcbVUAXkJSKy7g43KHW378pBwA48Ywbuuw",
	"txn_body":"000005f77103a51c9eb625618fab20a8486fc03b1184...1dee3be19909583",
	"txn_hash":"5f77103a51ef21c912625618fab20a8486fc03b118410b5101dee3be19909583"
}
```
转换成标准JSON格式字符串：

	{"auth_id":"1233211233211233211123312","backdoc":"image/png;base64,iVBORw0KGgoAAAANSUhmJM5WHUcAeKwnHAcY...","country":"CN","doc_type":"passport","frontdoc":"image/png;base64,iVBORw0KGgoAAAAADAFBMAAAAAAAAAAAAAAA...","ontid":"did:ont:AcbVUAXkJSKy7g43KHW378pBwA48Ywbuuw","owner_ontid":"did:ont:AcbVUAXkJSKy7g43KHW378pBwA48Ywbuuw","txn_body":"000005f77103a51c9eb625618fab20a8486fc03b1184...1dee3be19909583","txn_hash":"5f77103a51ef21c912625618fab20a8486fc03b118410b5101dee3be19909583"}

再对该JSON格式字符串进行签名，得到签名值sigvalue后，以signature为key添加到Post请求体的JSON对象中

最终认证Post请求体的JSON对象为：
```
{
	"auth_id":"1233211233211233211123312",
	"backdoc":"image/png;base64,iVBORw0KGgoAAAANSUhmJM5WHUcAeKwnHAcY...",
	"country":"CN",
	"doc_type":"passport",
	"frontdoc":"image/png;base64,iVBORw0KGgoAAAAADAFBMAAAAAAAAAAAAAAA...",
    	"ontid":"did:ont:AcbVUAXkJSKy7g43KHW378pBwA48Ywbuuw",
	"owner_ontid":"did:ont:AcbVUAXkJSKy7g43KHW378pBwA48Ywbuuw",
	"txn_body":"000005f77103a51c9eb625618fab20a8486fc03b1184...1dee3be19909583",
	"txn_hash":"5f77103a51ef21c912625618fab20a8486fc03b118410b5101dee3be19909583",
	"signature":"sigvalue"
}
```


### 示例DEMO

构造转账交易，使用身份ONT ID私钥进行签名验签等操作，可参考

[JAVA DEMO](https://github.com/ontio/documentation/blob/master/pro-website-docs/assets/Demo.java)

[TS DEMO](https://github.com/ontio/documentation/blob/master/pro-website-docs/assets/OntIdSignDemo.js)

[SDK开发者文档中心](https://dev-docs.ont.io/#/docs-en/SDKs/00-overview)





