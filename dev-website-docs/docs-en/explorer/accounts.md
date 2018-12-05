## Account APIs


### Ontology资产名称字典

Ontology资产名称字典

| value     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    ont|   String|  ont资产|
|    ong|   String|  ong资产|
|    waitboundong|   String|  等待提取ong资产|
|    unboundong|   String|  未提取ong资产|
|    pumpkin01|   String|  oep8资产，redpumpkin红南瓜|
|    pumpkin02|   String|  oep8资产，orangepumpkin橘南瓜|
|    pumpkin03|   String|  oep8资产，yellowpumpkin黄南瓜|
|    pumpkin04|   String|  oep8资产，greenpumpkin绿南瓜|
|    pumpkin05|   String|  oep8资产，indigopumpkin靛南瓜|
|    pumpkin06|   String|  oep8资产，bluepumpkin蓝南瓜|
|    pumpkin07|   String|  oep8资产，purplepumpkin紫南瓜|
|    pumpkin08|   String|  oep8资产，goldenpumpkin金南瓜|




### 分页查询某个地址的所有转账交易信息

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
		"TxnTotal":20,
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
|    pagesize|   int|  分页大小  |
|    pagenumber|   int|  页数，从1开始计数  |



| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    AssetBalance.AssetName|   String|  资产名称，具体可参考**资产名称字典**|
|    AssetBalance.Balance|   String|  该资产的账户余额|
|    TxnTotal|   int|  交易总数 |
|    TxnList.TxnHash|   String|  交易hash |
|    TxnList.ConfirmFlag|   int|  交易状态，1:交易成功 2:交易失败 |
|    TxnList.Height|   int|  区块高度  |
|    TxnList.TxnType|   int|  交易类型  |
|    TxnList.TxnTime| int|  交易时间，unix时间戳  |
|    TxnList.Fee|   String|  手续费  |
|    TxnList.BlockIndex|   int|  该交易在该区块中的索引  |
|    TxnList.TransferList.FromAddress|   String|  转出账户地址  |
|    TxnList.TransferList.ToAddress|   String|  转入账户地址  |
|    TxnList.TransferList.Amount|   String|  交易金额  |
|    TxnList.TransferList.AssetName|   String|  交易资产名称，具体可参考**0资产名称字典**  |

说明：

- 若查询地址与TxnList.TransferList.FromAddress字段的地址一样，则说明是一笔资产转出交易。Amount即转出金额。
- 若查询地址与TxnList.TransferList.ToAddress字段的地址一样，则说明是一笔资产转入交易，Amount即转入金额。



### 分页查询某个地址的某种资产的所有转账交易信息

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
		"TxnTotal":20,
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
|    assetname|   String|  资产名称，具体可参考**0资产名称字典**  |
|    pagesize|   int|  分页大小  |
|    pagenumber|   int|  页数，从1开始计数  |



| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    AssetBalance.AssetName|   String|  资产名称|
|    AssetBalance.Balance|   String|  该资产的账户余额|
|    TxnTotal|   int|  交易总数 |
|    TxnList.TxnHash|   String|  交易hash |
|    TxnList.ConfirmFlag|   int|  交易状态，1:交易成功 2:交易失败 |
|    TxnList.Height|   int|  区块高度  |
|    TxnList.TxnType|   int|  交易类型  |
|    TxnList.TxnTime| int|  交易时间，unix时间戳  |
|    TxnList.Fee|   String|  手续费  |
|    TxnList.BlockIndex|   int|  该交易在该区块中的索引  |
|    TxnList.TransferList.FromAddress|   String|  转出账户地址  |
|    TxnList.TransferList.ToAddress|   String|  转入账户地址  |
|    TxnList.TransferList.Amount|   String|  交易金额  |
|    TxnList.TransferList.AssetName|   String|  交易资产名称，具体可参考**0资产名称字典**  |


说明：

- 若查询地址与TxnList.TransferList.FromAddress字段的地址一样，则说明是一笔资产转出交易。Amount即转出金额。
- 若查询地址与TxnList.TransferList.ToAddress字段的地址一样，则说明是一笔资产转入交易，Amount即转入金额。



### 根据时间范围查询某个地址的某种资产的所有转账交易信息

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
		"TxnTotal":20,
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
|    assetname|   String|  资产名称，具体可参考**0资产名称字典**  |
|    begintime|   int|  开始时间，unix时间戳  |
|    endtime|   int|  结束时间，unix时间戳  |



| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    AssetBalance.AssetName|   String|  资产名称|
|    AssetBalance.Balance|   String|  该资产的账户余额|
|    TxnTotal|   int|  交易总数 |
|    TxnList.TxnHash|   String|  交易hash |
|    TxnList.ConfirmFlag|   int|  交易状态，1:交易成功 2:交易失败 |
|    TxnList.Height|   int|  区块高度  |
|    TxnList.TxnType|   int|  交易类型  |
|    TxnList.TxnTime| int|  交易时间，unix时间戳  |
|    TxnList.Fee|   String|  手续费  |
|    TxnList.BlockIndex|   int|  该交易在该区块中的索引  |
|    TxnList.TransferList.FromAddress|   String|  转出账户地址  |
|    TxnList.TransferList.ToAddress|   String|  转入账户地址  |
|    TxnList.TransferList.Amount|   String|  交易金额  |
|    TxnList.TransferList.AssetName|   String|  交易资产名称，具体可参考**0资产名称字典**  |




### 根据截止时间及分页查询某个地址的某种资产的所有转账交易信息

```json
url：/api/v1/explorer/address/timeandpage/{address}/{assetname/{sum}/{endtime}
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
		"TxnTotal":20,
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
|    assetname|   String|  资产名称，具体可参考**0资产名称字典**  |
|    sum|   int|  查询数量  |
|    endtime|   int|  结束时间，unix时间戳  |



| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    AssetBalance.AssetName|   String|  资产名称|
|    AssetBalance.Balance|   String|  该资产的账户余额|
|    TxnTotal|   int|  交易总数 |
|    TxnList.TxnHash|   String|  交易hash |
|    TxnList.ConfirmFlag|   int|  交易状态，1:交易成功 2:交易失败 |
|    TxnList.Height|   int|  区块高度  |
|    TxnList.TxnType|   int|  交易类型  |
|    TxnList.TxnTime| int|  交易时间，unix时间戳  |
|    TxnList.Fee|   String|  手续费  |
|    TxnList.BlockIndex|   int|  该交易在该区块中的索引  |
|    TxnList.TransferList.FromAddress|   String|  转出账户地址  |
|    TxnList.TransferList.ToAddress|   String|  转入账户地址  |
|    TxnList.TransferList.Amount|   String|  交易金额  |
|    TxnList.TransferList.AssetName|   String|  交易资产名称，具体可参考**0资产名称字典**  |



### 根据开始时间查询某个地址的某种资产的所有转账交易信息

```json
url：/api/v1/explorer/address/time/{address}/{assetname}/{begintime}
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
		"TxnTotal":20,
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
|    assetname|   String|  资产名称，具体可参考**0资产名称字典**  |
|    begintime|   int|  开始时间，unix时间戳  |



| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    AssetBalance.AssetName|   String|  资产名称|
|    AssetBalance.Balance|   String|  该资产的账户余额|
|    TxnTotal|   int|  交易总数 |
|    TxnList.TxnHash|   String|  交易hash |
|    TxnList.ConfirmFlag|   int|  交易状态，1:交易成功 2:交易失败 |
|    TxnList.Height|   int|  区块高度  |
|    TxnList.TxnType|   int|  交易类型  |
|    TxnList.TxnTime| int|  交易时间，unix时间戳  |
|    TxnList.Fee|   String|  手续费  |
|    TxnList.BlockIndex|   int|  该交易在该区块中的索引  |
|    TxnList.TransferList.FromAddress|   String|  转出账户地址  |
|    TxnList.TransferList.ToAddress|   String|  转入账户地址  |
|    TxnList.TransferList.Amount|   String|  交易金额  |
|    TxnList.TransferList.AssetName|   String|  交易资产名称，具体可参考**0资产名称字典**  |




### 查询某个地址的原生资产余额

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
|    address|   String|  账户地址  |



| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    AssetName|   String|  资产名称|
|    Balance|   String|  该资产的账户余额|






