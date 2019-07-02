


## 1. Ontology 资产名称字典


| value     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    ont|   String|  ont 资产|
|    ong|   String|  ong 资产|
|    waitboundong|   String|  等待提取 ong 资产|
|    unboundong|   String|  未提取 ong 资产|
|    YLTK|oep4资产| oep4|
|    HP|oep4资产| oep4|
|    DICE|oep4资产| oep4|
|    SONT|oep4资产| oep4|
|    LCY|oep4资产| oep4|
|    SPKZ|oep4资产| oep4|
|    YLTK|oep4资产| oep4|
|    CNYL|oep4资产| oep4|
|    SEED|oep4资产| oep4|
|    ALV|oep4资产| oep4|
|    PAX|oep4资产| oep4|

## 2. 分页查询某个地址的所有转账交易信息

```json
url：/api/v1/explorer/address/{address}/{pagesize}/{pagenumber}
method：GET
successResponse：
{
	"Action":"QueryAddressInfo",
	"Version":"1.0",
	"Error":0,
	"Desc":"SUCCESS",
	"Result":{
		"AssetBalance":[
			{
				"AssetName":"ont",
				"Balance":"123.2"
			},
			{
				"AssetName":"ong",
				"Balance":"1232"
			},
			{
				"AssetName": "waitboundong",
				"Balance": "14006.83021186"
			},
			{
				"AssetName": "unboundong",
				"Balance": "71472.14798338"
			},
			{
				"AssetName": "pumpkin01",
				"Balance": "7",
				"AssertType": "OEP8"
			},
			{
				"AssetName": "HyperDragons",
				"Balance": "3",
				"AssertType": "OEP5"
			},
			{
				"AssetName": "TNT",
				"Balance": "58829",
				"AssertType": "OEP4"
			}
		],
		"TxnList":[
			{
				"TxnHash":"09e599ecde6eec18608bdecd0cf0a54b02bc9d55239e1b1bd291558e5a6ef3fa",
				"ConfirmFlag":1,
				"TxnType":208,
				"TxnTime":1522207168,
				"Height":11,
				"Fee":"0.010000000",
				"BlockIndex":1,
				"TransferList": [
					{
						"Amount": "100.000000000",
						"FromAddress":"A15NzM9iE3VT9X8SGk5h3dii6GPFQh2vme",
						"ToAddress":"AA8fwY3wWhit3bnsAKRdoiCsKqp2qr4VBx",
						"AssetName":"ont"
					}
				]
			}
		]
	}
}
```


| RequestField     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    address|   String|  账户地址  |
|    pagesize|   int|  分页大小(当前限制最大值为 20 )  |
|    pagenumber|   int|  页数，从 1 开始计数  |



| ResponseField     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    AssetBalance.AssetName|   String|  资产名称，具体可参考**资产名称字典**|
|    AssetBalance.Balance|   String|  该资产的账户余额|
|    AssetBalance.AssertType|   String|  该资产的类型|
|    TxnList.TxnHash|   String|  交易 hash |
|    TxnList.ConfirmFlag|   int|  交易状态，1:交易成功 2:交易失败 |
|    TxnList.Height|   int|  区块高度  |
|    TxnList.TxnType|   int|  交易类型  |
|    TxnList.TxnTime| int|  交易时间，unix 时间戳  |
|    TxnList.Fee|   String|  手续费  |
|    TxnList.BlockIndex|   int|  该交易在该区块中的索引  |
|    TxnList.TransferList.FromAddress|   String|  转出账户地址  |
|    TxnList.TransferList.ToAddress|   String|  转入账户地址  |
|    TxnList.TransferList.Amount|   String|  交易金额  |
|    TxnList.TransferList.AssetName|   String|  交易资产名称，具体可参考**资产名称字典**  |





## 3. 分页查询某个地址的某种资产的所有转账交易信息

```json
url：/api/v1/explorer/address/{address}/{assetname}/{pagesize}/{pagenumber}
method：GET
successResponse：
{
	"Action":"QueryAddressInfo",
	"Version":"1.0",
	"Error":0,
	"Desc":"SUCCESS",
	"Result":{
		"AssetBalance":[
			{
				"AssetName":"ont",
				"Balance":"123.200000000"
			}
		],
		"TxnList":[
			{
				"TxnHash":"09e599ecde6eec18608bdecd0cf0a54b02bc9d55239e1b1bd291558e5a6ef3fa",
				"ConfirmFlag":1,
				"TxnType":208,
				"TxnTime":1522207168,
				"Height":11,
				"Fee":"0.010000000",
				"BlockIndex":1,
				"TransferList": [
					{
						"Amount": "100.000000000",
						"FromAddress": "AA5NzM9iE3VT9X8SGk5h3dii6GPFQh2vme",
						"ToAddress":"AA8fwY3wWhit3bnsAKRdoiCsKqp2qr4VBx",
						"AssetName":"ont"
					}
				]
			}
		]
	}
}
```


| RequestField     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    address|   String|  账户地址  |
|    assetname|   String|  资产名称，具体可参考**资产名称字典**  |
|    pagesize|   int|  分页大小  |
|    pagenumber|   int|  页数，从1开始计数  |



| ResponseField     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    AssetBalance.AssetName|   String|  资产名称|
|    AssetBalance.Balance|   String|  该资产的账户余额|
|    TxnList.TxnHash|   String|  交易 hash |
|    TxnList.ConfirmFlag|   int|  交易状态，1:交易成功 2:交易失败 |
|    TxnList.Height|   int|  区块高度  |
|    TxnList.TxnType|   int|  交易类型  |
|    TxnList.TxnTime| int|  交易时间，unix 时间戳  |
|    TxnList.Fee|   String|  手续费  |
|    TxnList.BlockIndex|   int|  该交易在该区块中的索引  |
|    TxnList.TransferList.FromAddress|   String|  转出账户地址  |
|    TxnList.TransferList.ToAddress|   String|  转入账户地址  |
|    TxnList.TransferList.Amount|   String|  交易金额  |
|    TxnList.TransferList.AssetName|   String|  交易资产名称，具体可参考**资产名称字典**  |


> 查询 `ong` 资产，会同时返回 `waitboundong` ，`unboundong`



## 4. 根据时间范围查询某个地址的某种资产的所有转账交易信息

```json
url：/api/v1/explorer/address/time/{address}/{assetname}/{begintime}/{endtime}
method：GET
successResponse：
{
	"Action":"QueryAddressInfo",
	"Version":"1.0",
	"Error":0,
	"Desc":"SUCCESS",
	"Result":{
		"AssetBalance":[
			{
				"AssetName":"ong",
				"Balance":"1232"
			},
			{
				"AssetName": "waitboundong",
				"Balance": "14006.83021186"
			},
			{
				"AssetName": "unboundong",
				"Balance": "71472.14798338"
			}
		],
		"TxnList":[
			{
				"TxnHash":"09e599ecde6eec18608bdecd0cf0a54b02bc9d55239e1b1bd291558e5a6ef3fa",
				"ConfirmFlag":1,
				"TxnType":208,
				"TxnTime":1522207168,
				"Height":11,
				"Fee":"0.010000000",
				"BlockIndex":1,
				"TransferList": [
					{
						"Amount": "100.000000000",
						"FromAddress": "AA5NzM9iE3VT9X8SGk5h3dii6GPFQh2vme",
						"ToAddress":"AA8fwY3wWhit3bnsAKRdoiCsKqp2qr4VBx",
						"AssetName":"ong",
					}
				]
			}
		]
	}
}
```


| RequestField     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    address|   String|  账户地址  |
|    assetname|   String|  资产名称，具体可参考**资产名称字典**  |
|    begintime|   int|  开始时间，unix 时间戳  |
|    endtime|   int|  结束时间，unix 时间戳  |



| ResponseField     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    AssetBalance.AssetName|   String|  资产名称|
|    AssetBalance.Balance|   String|  该资产的账户余额|
|    TxnList.TxnHash|   String|  交易 hash |
|    TxnList.ConfirmFlag|   int|  交易状态，1:交易成功 2:交易失败 |
|    TxnList.Height|   int|  区块高度  |
|    TxnList.TxnType|   int|  交易类型  |
|    TxnList.TxnTime| int|  交易时间，unix 时间戳  |
|    TxnList.Fee|   String|  手续费  |
|    TxnList.BlockIndex|   int|  该交易在该区块中的索引  |
|    TxnList.TransferList.FromAddress|   String|  转出账户地址  |
|    TxnList.TransferList.ToAddress|   String|  转入账户地址  |
|    TxnList.TransferList.Amount|   String|  交易金额  |
|    TxnList.TransferList.AssetName|   String|  交易资产名称，具体可参考**资产名称字典**  |








## 5. 查询某个地址的资产余额

```json
url：/api/v1/explorer/address/balance/{address}
method：GET
successResponse：
{
	"Action": "QueryAddressBalance",
	"Error": 0,
	"Desc": "SUCCESS",
	"Version": "1.0",
	"Result": [
		{
			"Balance": "138172.922008484",
			"AssetName": "ong"
		},
		{
			"Balance": "14006.83021186",
			"AssetName": "waitboundong"
		},
		{
			"Balance": "71472.14798338",
			"AssetName": "unboundong"
		},
		{
			"Balance": "8637767",
			"AssetName": "ont"
		},
		{
			"AssetName": "pumpkin01",
			"Balance": "7",
			"AssertType": "OEP8"
		},
		{
			"AssetName": "HyperDragons",
			"Balance": "3",
			"AssertType": "OEP5"
		},
		{
			"AssetName": "TNT",
			"Balance": "58829",
			"AssertType": "OEP4"
		}
	]
}
```


| RequestField     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    address|   String|  账户地址  |



| ResponseField     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    AssetName|   String|  资产名称|
|    Balance|   String|  该资产的账户余额|
|    AssetBalance.AssertType|   String|  该资产的类型|
