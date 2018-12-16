

### OntId Information

| Value     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    register OntId |   String|  register OntId |
|    add publicKey:xxxxx |   String|  add publicKey |
|    remove publicKey:xxxxx |   String|  remove publicKey |
|    add attribute:value1&value2 |   String| add attribute  |
|    update attribute:xxxx |   String|  update attribute |
|    remove attribute:xxxx |   String| remove attribute |
|    change recovery:xxxx |   String|  change recovery |
|    add recovery:xxxx |   String|  add recovery |


### DDO Attribute



| Key     | Value     |     Type |   Description   | 
| :--------------: | :--------:| :------: |:-----:|
|    Claim |    ContextDesc |   String|  description |
|    |    ClaimContext |   String|  claim context  |
|    |    IssuerOntId |   String| ontid of the issuer |
|    |    ClaimId |   String|  the hash of claim |
|   SelfDefined |    value |   String|  self defined DDO info |





### Query OntId list

```json
url：/api/v1/explorer/ontidlist/{amount}
method：GET
successResponse：
{
	"Action":"QueryOntIdList",
	"Version":"1.0",
	"Error":0,
	"Desc":"SUCCESS",
	"Result":[
		{
			"OntId":"did:ont:TA7aqop3BcYJpHtEEyfg1ucausfDETyTQA",
			"TxnHash":"09e599ecde6eec18608bdecd0cf0a54b02bc9d55239e1b1bd291558e5a6ef3fa",
			"Height":123,
			"TxnType":209,
			"TxnTime":1522213972,
			"Description":"register OntId",
			"Fee":"0.010000000"
		}
	]	
}
```

| RequestField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    amount|   int|  amount


| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    OntId |   String|  OntId |
|    TxnHash |   String|  transaction hash
|    Height |   int|  block height|
|    TxnTime |   int|  unix time of the block|
|    Description |   String|  description|
|    TxnType |   int|  208 or 209  |
|    Fee |   String|  fee  |




### Query OntId list by page

```json
url：/api/v1/explorer/ontidlist/{pagesize}/{pagenumber}
method：GET
successResponse：
{
	"Action":"QueryOntIdList",
	"Version":"1.0",
	"Error":0,
	"Desc":"SUCCESS",
	"Result":{
		"OntIdList":{
			[
				"OntId":"did:ont:TA8mpcKSzWQxesJ6bL2tP2qZtAnQdNy7Um",
				"TxnHash":"23797d23e9d1cc9bb9af8faf3c2abf73dc4f18b6cd1a840fca469bb9cc0d6e5b",
				"TxnType":209,
				"Height":123,
				"TxnTime":1522213966,
				"Description":"add attribute:claim",
				"Fee":"0.010000000"
			]
		},
		"Total":10
	}
}
```

| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    OntIdList.OntId|   String|  OntId |
|    OntIdList.TxnHash|   String|   |
|    OntIdList.Height|   int|    |
|    OntIdList.TxnTime|   int|    |
|    OntIdList.Description|   String|   |
|    OntIdList.TxnType|   int|    |
|    OntIdList.Fee |   String|    |
|    Total|   int|    |





### Query OntId

```json
url：/api/v1/explorer/ontid/{ontid}/{pagesize}/{pagenumber}
method：GET
successResponse：
{
	"Action":"QueryOntId",
	"Version":"1.0",
	"Error":0,
	"Desc":"SUCCESS",
	"Result":{
		"Ddo":{
			"Attributes":[
				{
					"Claim":{
						"ClaimId":"111ab2f56d106dac92e891b6f7fc4d9546fdf2eb94a364208fa65a9996b03ba0",
						"ClaimContext":"claim:github_authentication",
						"ContextDesc":"my github claim",
						"IssuerOntId":"did:ont:TKhyXw8o6Em5GjmJwiPT1oNXsy4p6fYZPB"
					}
				}
			],
			"OntId":"did:ont:TA7aqop3BcYJpHtEEyfg1ucausfDETyTQA",
			"Owners":[
				{
					"Type": "ECDSA",
					"Curve": "P-256",
					"Value": "120203cef1f2ff72b76cd777ca067dbdf655893671c261940312c800dcdf5c5772e449",
					"PublicKeyId": "did:ont:TA96Nqm9HRFKzudLjgH16Zfvdw3ixq8UGZ#keys-1"
				}
			]
		},
		"TxnList":[
			{
				"TxnHash":"df272d8bf471ed6f2caed051ab0a77691e7c24ad66bc1c460669fadc996f1b3f",
				"Height":123,
				"TxnType": 209,
				"TxnTime":1522213966,
				"Description":"add attribute:claim",
				"Fee":"0.010000000",
				"OntId": "did:ont:TA96Nqm9HRFKzudLjgH16Zfvdw3ixq8UGZ"
			}
		],
		"TxnTotal":10
	}
}
```

| RequestField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    ontid|   String|  ontid  |
|    pagesize|   int|  pagesiez.1-20  |
|    pagenumber|   int|  pagenumber. start from 1 |


| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    TxnTotal| int|    |
|    Ddo.Attributes|   list|  |
|    Ddo.OntId|   String|  OntId |
|    Ddo.Owners|   list|  |
|    Ddo.Owners.Type|   String|  |
|    Ddo.Owners.Value|   String|  |
|    TxnList.TxnHash|   String|   |
|    TxnList.Height|   int|    |
|    TxnList.TxnType|   int|    |
|    TxnList.Fee| String|    |
|    TxnList.OntId| String|  OntId  |
|    TxnList.TxnTime| int|    |
|    TxnList.Description|   String|   |


