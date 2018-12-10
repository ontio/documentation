<h1 align="center">全球身份认证接入指导</h1>

## 概述

Ontology Global Identity TrustAnchor(ONTTA)作为Ontology信任生态上的一个综合性的全球身份认证信任源，可对全球200+国家的公民进行护照，驾照，身份证OCR认证并签发对应的可信声明。为Ontology信任生态中的身份认证需求方提供了多维度、高准确性、全球化的身份认证服务。

* TrustAnchor Name : Ontology Global Identity TrustAnchor
* TrustAnchor ONT ID :  did：ont：ANNmeSiQJVwq3z6KvKo3SSKGnoBqvwYcwt
* TrustAnchor Account Address : ATGJSGzm2poCB8N44BgrAccJcZ64MFf187
* 服务列表

| Claim_Templete_Name | Claim_Description |  DocLink |
| :-----------------: | :----------------:| :------: |
|claim:sfp_passport_authentication | 全球用户护照认证   | http://pro-docs.ont.io/#/docs-cn/ontpass/ONTTA |
|claim:sfp_idcard_authentication   | 全球用户身份证认证 | http://pro-docs.ont.io/#/docs-cn/ontpass/ONTTA |
|claim:sfp_dl_authentication       | 全球用户驾照认证   | http://pro-docs.ont.io/#/docs-cn/ontpass/ONTTA |



## 收费标准

采用即时支付模式，即每次身份认证请求都需要消耗ONG手续费，所以认证需求方在每次认证请求时都需要构造一笔ONG转账交易（收款地址是**ATGJSGzm2poCB8N44BgrAccJcZ64MFf187**）。

每次认证费用：*1.2 ONG*

> 备注：如何构造转账交易可参考[附录DEMO](http://pro-docs.ont.io/#/docs-cn/ontpass/ONTTA?id=%E7%A4%BA%E4%BE%8Bdemo)或[SDK开发者文档中心](https://dev-docs.ont.io/#/docs-en/SDKs/00-overview)

## 认证请求示例

```json
Host：https://api.ont.network/api/v1/ontta/ocr/authentication
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
    "action": "OcrApply",
    "error": 0,
    "desc": "SUCCESS",
    "version": "1.0",
    "result": true
}
```

### RequestField

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

	请求方的ONT ID，使用该ONT ID对请求内容进行签名。


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
### ResponseField

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
| 0 | int | SUCCESS. 成功 |
| 61001 | int | FAIL, param error. 参数错误 |
| 62003 | int | FAIL, inner communicate fail. 内部通信异常 |
| 62006 | int | FAIL, verify signature fail. 验签失败 |
| 62007 | int | FAIL, txn toaddress error or amount insufficient. 交易收款地址错误或金额不足 |
| 62008 | int | FAIL, send transaction fail. 交易发送失败 |
| 63001 | int | FAIL, inner error. 内部异常 |



## 认证支持国家列表


Country Name       | Country Code
---------          | -----------
Afghanistan|AF
Aland Islands|AX
Albania|AL
Algeria|DZ
American Samoa|AS
Andorra|AD
Angola|AO
Anguilla|AI
Antarctica|AQ
Antigua and Barbuda|AG
Argentina|AR
Armenia|AM
Aruba|AW
Australia|AU
Austria|AT
Azerbaijan|AZ
Bahamas|BS
Bahrain|BH
Bangladesh|BD
Barbados|BB
Belarus|BY
Belgium|BE
Belize|BZ
Benin|BJ
Bermuda|BM
Bhutan|BT
Bolivia|BO
Bosnia and Herzegovina|BA
Botswana|BW
Bouvet Island|BV
Brazil|BR
British Indian Ocean Territory|IO
Brunei|BN
Bulgaria|BG
Burkina Faso|BF
Burma (Myanmar)|MM
Burundi|BI
Cambodia|KH
Cameroon|CM
Canada|CA
Cape Verde|CV
Cayman Islands|KY
Central African Republic|CF
Chad|TD
Chile|CL
China|CN
Christmas Island|CX
Cocos (Keeling) Islands|CC
Colombia|CO
Comoros|KM
Congo, Dem. Republic|CD
Congo, Republic|CG
Cook Islands|CK
Costa Rica|CR
Croatia|HR
Cuba|CU
Cyprus|CY
Czech Republic|CZ
Denmark|DK
Djibouti|DJ
Dominica|DM
Dominican Republic|DO
East Timor|TL
Ecuador|EC
Egypt|EG
El Salvador|SV
Equatorial Guinea|GQ
Eritrea|ER
Estonia|EE
Ethiopia|ET
Falkland Islands|FK
Faroe Islands|FO
Fiji|FJ
Finland|FI
France|FR
French Guiana|GF
French Polynesia|PF
French Southern Territories|TF
Gabon|GA
Gambia|GM
Georgia|GE
Germany|DE
Ghana|GH
Gibraltar|GI
Greece|GR
Greenland|GL
Grenada|GD
Guadeloupe|GP
Guam|GU
Guatemala|GT
Guernsey|GG
Guinea|GN
Guinea-Bissau|GW
Guyana|GY
Haiti|HT
Heard Island and McDonald Islands|HM
Honduras|HN
HongKong|HK
Hungary|HU
Iceland|IS
India|IN
Indonesia|ID
Iran|IR
Iraq|IQ
Ireland|IE
Israel|IL
Italy|IT
Ivory Coast|CI
Jamaica|JM
Japan|JP
Jersey|JE
Jordan|JO
Kazakhstan|KZ
Kenya|KE
Kiribati|KI
Korea, Dem. Republic of|KP
Kuwait|KW
Kyrgyzstan|KG
Laos|LA
Latvia|LV
Lebanon|LB
Lesotho|LS
Liberia|LR
Libya|LY
Liechtenstein|LI
Lithuania|LT
Luxemburg|LU
Macau|MO
Macedonia|MK
Madagascar|MG
Malawi|MW
Malaysia|MY
Maldives|MV
Mali|ML
Malta|MT
Man Island|IM
Marshall Islands|MH
Martinique|MQ
Mauritania|MR
Mauritius|MU
Mayotte|YT
Mexico|MX
Micronesia|FM
Moldova|MD
Monaco|MC
Mongolia|MN
Montenegro|ME
Montserrat|MS
Morocco|MA
Mozambique|MZ
Namibia|NA
Nauru|NR
Nepal|NP
Netherlands|NL
Netherlands Antilles|AN
New Caledonia|NC
New Zealand|NZ
Nicaragua|NI
Niger|NE
Nigeria|NG
Niue|NU
Norfolk Island|NF
Northern Mariana Islands|MP
Norway|NO
Oman|OM
Pakistan|PK
Palau|PW
Palestinian Territories|PS
Panama|PA
Papua New Guinea|PG
Paraguay|PY
Peru|PE
Philippines|PH
Pitcairn|PN
Poland|PL
Portugal|PT
Puerto Rico|PR
Qatar|QA
Reunion Island|RE
Romania|RO
Russian Federation|RU
Rwanda|RW
Saint Barthelemy|BL
Saint Kitts and Nevis|KN
Saint Lucia|LC
Saint Martin|MF
Saint Pierre and Miquelon|PM
Saint Vincent and the Grenadines|VC
Samoa|WS
San Marino|SM
Saudi Arabia|SA
Senegal|SN
Serbia|RS
Seychelles|SC
Sierra Leone|SL
Singapore|SG
Slovakia|SK
Slovenia|SI
Solomon Islands|SB
Somalia|SO
South Africa|ZA
South Georgia and the South Sandwich Islands|GS
South Korea|KR
Spain|ES
Sri Lanka|LK
Sudan|SD
Suriname|SR
Svalbard and Jan Mayen|SJ
Swaziland|SZ
Sweden|SE
Switzerland|CH
Syria|SY
São Tomé and Príncipe|ST
Taiwan|TW
Tajikistan|TJ
Tanzania|TZ
Thailand|TH
Togo|TG
Tokelau|TK
Tonga|TO
Trinidad and Tobago|TT
Tunisia|TN
Turkey|TR
Turkmenistan|TM
Turks and Caicos Islands|TC
Tuvalu|TV
Uganda|UG
Ukraine|UA
United Arab Emirates|AE
United Kingdom|GB
United States|US
Uruguay|UY
Uzbekistan|UZ
Vanuatu|VU
Vatican City State|VA
Venezuela|VE
Vietnam|VN
Virgin Islands (British)|VG
Virgin Islands (U.S.)|VI
Wallis and Futuna|WF
Western Sahara|EH
Yemen|YE
Zambia|ZM
Zimbabwe|ZW

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
		"IssuerName":"ONTTA"
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





