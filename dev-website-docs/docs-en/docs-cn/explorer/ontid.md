## ONT ID APIs

### OntId操作描述字典

| Value     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    register OntId |   String|  注册OntId |
|    add publicKey:xxxxx |   String|  添加公钥，公钥值为xxxxx |
|    remove publicKey:xxxxx |   String|  删除公钥，公钥值为xxxxx |
|    add attribute:value1&value2 |   String|  添加属性，属性名为value1，若有多个属性以&分割  |
|    update attribute:xxxx |   String|  更新属性，属性名为xxxxx  |
|    remove attribute:xxxx |   String|  删除属性，属性名为xxxxx  |
|    change recovery:xxxx |   String|  修改恢复人信息，新的恢复人地址为xxxx  |
|    add recovery:xxxx |   String|  添加恢复人信息，新的恢复人地址为xxxx  |


### DDO Attribute字典



| Key     | Value     |     Type |   Description   | 
| :--------------: | :--------:| :------: |:-----:|
|    Claim |    ContextDesc |   String|  claim模板描述 |
|    |    ClaimContext |   String|  claim模板标识  |
|    |    IssuerOntId |   String| 颁发者ONTID |
|    |    ClaimId |   String|  claim的唯一标识 |
|   SelfDefined |    value |   String|  用户自定义的DDO信息 |





### 当前OntId基本信息列表

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
|    amount|   int|  查询的交易总数  |


| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    OntId |   String|  OntId |
|    TxnHash |   String|  交易hash |
|    Height |   int|  区块高度  |
|    TxnTime |   int|  区块时间，unix时间戳  |
|    Description |   String|  操作描述，具体参考**4.4.0 OntId操作描述字典**  |
|    TxnType |   int|  交易类型  |
|    Fee |   String|  交易手续费  |




### 分页查询OntId信息列表

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
|    OntIdList.TxnHash|   String|  交易hash |
|    OntIdList.Height|   int|  区块高度  |
|    OntIdList.TxnTime|   int|  区块时间，unix时间戳  |
|    OntIdList.Description|   String|  操作描述，具体参考**4.4.0 OntId操作描述字典**  |
|    OntIdList.TxnType|   int|  交易类型  |
|    OntIdList.Fee |   String|  交易手续费  |
|    Total|   int|  ontId相关的交易总数  |





### 分页查询某个OntId相关信息

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
|    pagesize|   int|  分页大小  |
|    pagenumber|   int|  页数，从1开始计数  |


| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    TxnTotal| int|  跟该OntId相关的总交易数量  |
|    Ddo.Attributes|   list|  DDO属性信息，里面是自定义信息,具体可参考**4.4.0 DDO Attribute字典**|
|    Ddo.OntId|   String|  OntId |
|    Ddo.Owners|   list|  OntId公钥列表|
|    Ddo.Owners.Type|   String|  OntId公钥类型|
|    Ddo.Owners.Value|   String|  OntId公钥值|
|    TxnList.TxnHash|   String|  交易hash |
|    TxnList.Height|   int|  区块高度  |
|    TxnList.TxnType|   int|  交易类型  |
|    TxnList.Fee| String|  交易手续费  |
|    TxnList.OntId| String|  OntId  |
|    TxnList.TxnTime| int|  区块时间，unix时间戳  |
|    TxnList.Description|   String|  操作描述，具体参考**4.4.0 OntId操作描述字典**  |


