


### Ontology Asset


| value     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    ont|   String|  ont|
|    ong|   String|  ong|
|    waitboundong|   String|  waitbound ong|
|    unboundong|   String|  unbound ong|



### Query transfer information by address

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
				"Balance": "7"
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
|    address|   String|  address  |
|    pagesize|   int|  pagesize.1-20  |
|    pagenumber|   int|  pagenumber. |



| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    AssetBalance.AssetName|   String|  |
|    AssetBalance.Balance|   String|  |
|    TxnList.TxnHash|   String|   |
|    TxnList.ConfirmFlag|   int| 1:succeed 2:failed  |
|    TxnList.Height|   int|    |
|    TxnList.TxnType|   int|  208 or 209  |
|    TxnList.TxnTime| int|    |
|    TxnList.Fee|   String|    |
|    TxnList.BlockIndex|   int| index in the block   |
|    TxnList.TransferList.FromAddress|   String|    |
|    TxnList.TransferList.ToAddress|   String|    |
|    TxnList.TransferList.Amount|   String|    |
|    TxnList.TransferList.AssetName|   String|   |





### Query transfer information by address and asset type

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
|    address|   String|    |
|    assetname|   String|   |
|    pagesize|   int|  pagesize. 1-20  |
|    pagenumber|   int|  pagenumber|



| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    AssetBalance.AssetName|   String|  |
|    AssetBalance.Balance|   String|  |
|    TxnList.TxnHash|   String|   |
|    TxnList.ConfirmFlag|   int|  state，1:succeed 2:failed |
|    TxnList.Height|   int|    |
|    TxnList.TxnType|   int|    |
|    TxnList.TxnTime| int|   |
|    TxnList.Fee|   String|    |
|    TxnList.BlockIndex|   int|    |
|    TxnList.TransferList.FromAddress|   String|    |
|    TxnList.TransferList.ToAddress|   String|    |
|    TxnList.TransferList.Amount|   String|    |
|    TxnList.TransferList.AssetName|   String|    |


> query ong，return waitboundong，unboundong



### Query transfer information by address and time

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
|    address|   String|    |
|    assetname|   String|    |
|    begintime|   int|   unix time |
|    endtime|   int| unix time  |



| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    AssetBalance.AssetName|   String|  |
|    AssetBalance.Balance|   String|  |
|    TxnList.TxnHash|   String|   |
|    TxnList.ConfirmFlag|   int|  |
|    TxnList.Height|   int|    |
|    TxnList.TxnType|   int|    |
|    TxnList.TxnTime| int|    |
|    TxnList.Fee|   String|    |
|    TxnList.BlockIndex|   int|    |
|    TxnList.TransferList.FromAddress|   String|    |
|    TxnList.TransferList.ToAddress|   String|    |
|    TxnList.TransferList.Amount|   String|    |
|    TxnList.TransferList.AssetName|   String|   |








### query all assets balance by address

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
		}
	]
}
```


| RequestField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    address|   String|    |



| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    AssetName|   String|  |
|    Balance|   String|  |






