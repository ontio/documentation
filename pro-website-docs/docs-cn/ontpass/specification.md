<h1 align="center">ONTPass 相关接口及技术参数</h1>

## 更多接口定义

### 查询授权请求状态

```json
Host：域名+/api/v1/ontpass/authrequesters
Method：GET /HTTP/1.1
Content-Type: application/json
RequestExample：
http://域名+/api/v1/ontpass/authrequesters?authID=123345667878780041

{
  "action": "queryAuthStat",
  "error": 0,
  "desc": "SUCCESS",
  "version": "1.0",
  "result": {
    "auth_id": "123345667878780008",
    "auth_status": true
  }
}
```


| Field_Name | Required |  Format | Description |
| :-----------------: | :----------------:| :------: | :------: |
|auth_id | yes | string 20-255 characters Length | 请求认证编码 |


| Field_Name  |  Format | Description |
| :-----------------: | :----------------: | :------: |
|version | String | 版本号，目前是1.0。|
|action | String | 固定值：AuthReq。|
|error | int | 错误码 |
|desc | String | 错误信息。成功即SUCCESS，其他即错误信息|
|result | Object | null表示处于Pending状态，认证结果未知 |
|auth_id | string  | 请求认证编码 |
|auth_flag | boolean  | 认证结果，true表示认证通过，false表示认证失败 |


### 查询用户认证数据

用户认证数据基于签发的可信声明模板，在ONT ID授权托管模式下，用户可以随时获取自己已经认证过的可信声明数据，数据被用户ONT ID进行加密，ONTPass并不可获取用户数据。

```json
Host：域名+/api/v1/ontpass/authrequesters
Method：GET /HTTP/1.1
Content-Type: application/json
RequestExample：
{
    "nounce":"123345667878780012",
    "auth_template":"authtemplate_kyc01",
    "ontid":"did:ont:AW6SJLdw6G3Ka2VnSxKapmRm6ee7qkjU9D",
    "signature":"111111111111111111111"
}

{
  "action": "queryMyClaims",
  "error": 0,
  "desc": "SUCCESS",
  "version": "1.0",
  "result": [
    {
      "claim_context": "claim:sfp_passport_authentication",
      "create_time": "2019-01-10T14:19:46.000+0000",
      "encrp_origdata": "",
      "issue_ontid": "did:ont:ARr6ApK24EU7nufND4s1SWpwULHBertpJb",
      "txnhash": ""
    }
  ]
}
```

| Field_Name | Required |  Format | Description |
| :-----------------: | :----------------:| :------: | :------: |
|nounce | yes | string 20-255 characters Length |需保证唯一性|
|ontid | yes | string | 用户ONT ID |
|auth_template | yes | string | 认证模板，默认：authtemplate_kyc01 | 
|signature | no | string | 用户签名 |


| Field_Name  |  Format | Description |
| :-----------------: | :----------------: | :------: |
|version | String | 版本号，目前是1.0。|
|action | String | 固定值：DocsSubmit。|
|error | int | 错误码 |
|desc | String | 错误信息。成功即SUCCESS，其他即错误信息|
|result | boolean | 对象列表|
|claim_context | String | CLaim模板 |
|encrp_origdata | String | 加密数据 |
|txnhash | String | 上链交易HASH |
|create_time | String | 生成时间 |
|issue_ontid | String | 发行方ONTID |
|auth_flag | String | 一个字符，状态：0-pending, 1-fail, 2-success |





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


## 签名及验签

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


## 示例DEMO

构造转账交易，使用身份ONT ID私钥进行签名验签等操作，可参考

[JAVA DEMO](https://github.com/ontio/documentation/blob/master/pro-website-docs/assets/Demo.java)

[TS DEMO](https://github.com/ontio/documentation/blob/master/pro-website-docs/assets/OntIdSignDemo.js)

[SDK开发者文档中心](https://dev-docs.ont.io/#/docs-en/SDKs/00-overview)




