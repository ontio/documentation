<h1 align="center">Global Identity Authentication Access Guide</h1>

## Overview

Ontology Global Identity TrustAnchor(ONTTA) is a comprehensive global identity trust source for Ontology Trust Ecosystem. It can authenticate passports, driver's licenses, ID card OCR certifications and issue corresponding verifiable claims to citizens in 200+ countries around the world. It provides multi-dimensional, high-accuracy and global identity authentication services for identity authentication requesters.

* TrustAnchor Name : Ontology Global Identity TrustAnchor
* TrustAnchor ONT ID :  did：ont：ANNmeSiQJVwq3z6KvKo3SSKGnoBqvwYcwt
* TrustAnchor Account Address : ATGJSGzm2poCB8N44BgrAccJcZ64MFf187
* Service List

| Claim_Templete_Name | Claim_Description |  DocLink |
| :-----------------: | :----------------:| :------: |
|claim:sfp_passport_authentication | Global User Passport Authentication   | http://pro-docs.ont.io/#/docs-cn/ontpass/ONTTA |
|claim:sfp_idcard_authentication   | Global User ID Authentication | http://pro-docs.ont.io/#/docs-cn/ontpass/ONTTA |
|claim:sfp_dl_authentication       | Global user license Authentication   | http://pro-docs.ont.io/#/docs-cn/ontpass/ONTTA |



## Charges

The instant payment mode is adopted, that is, each identity authentication request needs to consume ONG, so the authentication requester needs to establish an ONG transfer transaction for each authentication request.（The Payment Address is**ATGJSGzm2poCB8N44BgrAccJcZ64MFf187**）。

Cost per authentication：*1.2 ONG*

> Note：method to construct a transfer transaction[AppendixDEMO](http://pro-docs.ont.io/#/docs-cn/ontpass/ONTTA?id=%E7%A4%BA%E4%BE%8Bdemo)or[SDK developer document center](https://dev-docs.ont.io/#/docs-en/SDKs/00-overview)

## Authentication Request Example

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

	Requesting an authentication code requires uniqueness. Only pass-through is carried out in the subsequent certification process.


* ### backdoc

	Required: **Yes**
	
	Type: **string**
	
	Format: **JPG, JPEG, PNG, PDF**
	
	Maximum: **16MB**

	The base 64 code of backside certification photo


* ### country

	Required: **Yes**
	
	Type: **string**
	
	Length: **2 characters**

	Two digits country code，refer to ISO 3166-1 alpha-2 Code Standard。Supported countries and corresponding country codes can be queried through[List of authentication supported countries](http://pro-docs.ont.io/#/docs-cn/ontpass/ONTTA?id=%E8%AE%A4%E8%AF%81%E6%94%AF%E6%8C%81%E5%9B%BD%E5%AE%B6%E5%88%97%E8%A1%A8)


* ### doc_type

	Required: **Yes**
	
	Type: **string**
	
	Supported Types: **passport，id_card，driving_license**

	Certification Type  Passport:passport ID Card:id_card  Driving License:driving_license


* ### frontdoc

	Required: **Yes**
	
	Type: **string**
	
	Image Format: **JPG, JPEG, PNG, PDF**
	
	Maximum: **16MB**

	The base 64 code of frontside certification photo


* ### ontid

	Required: **Yes**
	
	Type: **string**

	Requester's ONT ID.You should use this ONT ID to signature.


* ### owner_ontid

	Required: **Yes**
	
	Type: **string**

	User's ONT ID.


* ### txn_body

	Required: **Yes**
	
	Type: **string**

	Constructed transfer transation body.


* ### txn_body

	Required: **Yes**
	
	Type: **string**

	Constructed transfer transaction hash。


* ### signature

	Required: **Yes**
	
	Type: **string**

	The requester uses the ONT ID private key to sign the requested content according to[Signature Rules](http://pro-docs.ont.io/#/docs-cn/ontpass/ONTTA?id=%E7%AD%BE%E5%90%8D%E5%8F%8A%E9%AA%8C%E7%AD%BE).

--------------------------------------------------------
### ResponseField

* ### version

	Type: **string**

	Version Number，Currently 1.0


* ### action

	Type: **string**

	Constant：AuthApply


* ### error

	Type: **long**

	Error code. Refer to [Error code dictionary](http://pro-docs.ont.io/#/docs-cn/ontpass/ONTTA?id=%E9%94%99%E8%AF%AF%E7%A0%81%E5%AD%97%E5%85%B8)


* ### desc

	Type: **string**

	Error message. Success is SUCCESS. Others are error messages.


* ### result

	Type: **boolean**

	true：Submitted successfully  false：Submition Failure


## Error code dictionary


| Field | Type | Description |
| :--- | :--- | :--- |
| 0 | int | SUCCESS. Success |
| 61001 | int | FAIL, param error. Parameter error |
| 61002 | int | FAIL, ONTID not exist. |
| 62003 | int | FAIL, inner communicate fail. Inner communicate failure |
| 62006 | int | FAIL, verify signature fail.  Verify signature failure|
| 62007 | int | FAIL, txn toaddress error or amount insufficient. Transaction error |
| 62008 | int | FAIL, send transaction fail. transaction-sending failure |
| 63001 | int | FAIL, inner error. Inner error |



## List of authentication supported countries


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

## Verifiable claim template

Following Ontology standard verifiable claim format：

	base64(Header)'.'base64(Payload)'.'base64(Signature)'.'base64(MerkleProof)

Format of Authentication Information clm in Payload is as follows：

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
|    Nationality |   String|  Two digits country code，refer to ISO 3166-1 alpha-2 code standard  |
|    Name |   String|  name  |
|    BirthDay|   String|  date of birth, format：yyyy-mm-dd|
|    IssueDate|   String|  issue date。format：yyyy-mm-dd |
|    ExpirationDate |   String|  expiration date。format：yyyy-mm-dd    |
|    IDDocNumber|   String|  Certification Number    |
|    IssuerName |   String|  ONTTA  |


## Appendix

### Signature and verification

To ensure that the request is not tampered and verifiable, each time the authentication requester initiates the authentication, the private key corresponding to the own ONT ID needs to be used to sign the request content, and the TrustAnchor will check the authentication request data.

**Signature Rule：**


The JSON object in the HTTP Post request body needs to be sorted in ascending alphabetical order of the key, then serialized into a standard JSON format string, then the request content string is signed, and finally the signature is added to the request body's JSON object with the signature as the key.

Use some OCR certification request as example：

The JSON object requested by the POST is sorted in ascending order of the key, and the JSON is:
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
Convert to standard JSON format string：

	{"auth_id":"1233211233211233211123312","backdoc":"image/png;base64,iVBORw0KGgoAAAANSUhmJM5WHUcAeKwnHAcY...","country":"CN","doc_type":"passport","frontdoc":"image/png;base64,iVBORw0KGgoAAAAADAFBMAAAAAAAAAAAAAAA...","ontid":"did:ont:AcbVUAXkJSKy7g43KHW378pBwA48Ywbuuw","owner_ontid":"did:ont:AcbVUAXkJSKy7g43KHW378pBwA48Ywbuuw","txn_body":"000005f77103a51c9eb625618fab20a8486fc03b1184...1dee3be19909583","txn_hash":"5f77103a51ef21c912625618fab20a8486fc03b118410b5101dee3be19909583"}

Then sign the JSON format string, obtain the signature value (sigvalue), and add it to the JSON object of the Post request body with the signature as the key.

The JSON object that finally authenticates the Post request body is：
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


### Example DEMO

For Construct transfer transaction, Apply ONT ID private key for signature, and so on, please refer to
[JAVA DEMO](https://github.com/ontio/documentation/blob/master/pro-website-docs/assets/Demo.java)

[TS DEMO](https://github.com/ontio/documentation/blob/master/pro-website-docs/assets/OntIdSignDemo.js)

[SDK developer documentation center](https://dev-docs.ont.io/#/docs-en/SDKs/00-overview)
