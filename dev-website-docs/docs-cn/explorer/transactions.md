

* TxnType 交易类型字典

| Value     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    208|   int|  部署智能合约交易  |
|    209|   int|  调用智能合约交易  |

* Description 交易描述字典

| Value     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    transfer|   String|  资产转账交易  |
|    gasconsume|   String|  手续费交易  |
|    ontId- |   String|  OntId 相关动作交易  |
|    claimRecord- |   String|  存证动作交易  |
|    auth |   String|  权限交易  |




## 1. 获取当前最新交易基本信息列表

```json
url：/api/v1/explorer/transactionlist/{amount}
method：GET
successResponse：
{
	"Action":"QueryTransaction",
	"Version":"1.0",
	"Error":0,
	"Desc":"SUCCESS",
	"Result":[
		{
			"TxnHash":"9762458cd30612509f7cda589b7e1f7e59cb35d200eeb0a010ccc7b347057eb5",
            "TxnType":209,
            "TxnTime":1522210288,
            "Height":1212,
            "ConfirmFlag":1,
			"BlockIndex":1,
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
|    TxnHash|   String|  交易 hash  |
|    TxnType|   int|  交易类型|
|    TxnTime|   int|  交易时间戳，unix 时间戳  |
|    Height|   int|  区块高度  |
|    BlockIndex|   int|  交易在该区块的索引  |
|    ConfirmFlag|   int |  确认标识 1:交易成功 2:交易失败 |
|    Fee|   String |  手续费 |



## 2. 根据分页获取交易基本信息列表


```json
url：/api/v1/explorer/transactionlist/{pagesize}/{pagenumber}
method：GET
successResponse：
{
	"Action":"QueryTransaction",
	"Version":"1.0",
	"Error":0,
	"Desc":"SUCCESS",
	"Result":{
		"TxnList":{
			[
				"TxnHash":"9762458cd30612509f7cda589b7e1f7e59cb35d200eeb0a010ccc7b347057eb5",
	            "TxnType":209,
	            "TxnTime":1516946305,
	            "Height":1212,
	            "ConfirmFlag":1,
				"BlockIndex":1,
				"Fee":"0.010000000"
			]
		},
		"Total":12
	}
}
```

| RequestField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    pagesize|   int|  每页数量  |
|    pagenumber|   int|  页数|



| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    Txnlistist.TxnHash|   String|  交易 hash  |
|    Txnlistist.TxnType|   int|  交易类型|
|    Txnlistist.TxnTime|   int|  交易时间戳，unix 时间戳  |
|    Txnlistist.Height|   int|  区块高度  |
|    Txnlistist.BlockIndex|   int|  交易在该区块的索引  |
|    Txnlistist.ConfirmFlag|   int|  确认标识 1:交易成功 2:交易失败 |
|    Txnlistist.Fee|   String |  手续费 |
|    Total|   int|  总的交易数量 |



## 3. 根据交易 hash 获取交易详细信息


```json
url：/api/v1/explorer/transaction/{txnhash}
method：GET
successResponse：
{
	"Action":"QueryTransaction",
	"Version":"1.0",
	"Error":0,
	"Desc":"SUCCESS",
	"Result":{
		"TxnHash":"9762458cd30612509f7cda589b7e1f7e59cb35d200eeb0a010ccc7b347057eb5",
		"TxnType":209,
		"TxnTime":1522207312,
		"Height":1212,
		"ConfirmFlag":1,
		"BlockIndex":1,
		"Fee":"0.010000000",
		"Description":"transfer",
		"Detail":{
		}
	}
}
```

| RequestField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    txnhash|   String|  交易 hash  |



| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    TxnHash|   String|  交易 hash  |
|    TxnType|   int|  交易类型|
|    TxnTime|   int|  交易时间戳，unix 时间戳  |
|    Height|   int|  区块高度  |
|    BlockIndex|   int|  交易在该区块的索引  |
|    Fee|   String |  手续费 |
|    ConfirmFlag|   int|  确认标识 1:交易成功 2:交易失败 |
|    Description|   String|  交易描述 ，具体参考**交易描述字典** |
|    Detail|   Object|  交易详情，根据不同的交易类型，该字段内的内容会不一样，需根据交易描述做判断。详细字段参考以下说明 |



**Detail字段内容：**


- 转账交易

```json
successResponse：
{
	"Detail":{
		"TransferList": [
			{
				"Amount": "0.020000000",
				"FromAddress":"Aege6VvWEiKauFa2ngrtwdXt8FeGkWNPRH",
				"ToAddress":"ATUD7W6t6tLPGgd8H9tCN6Kwkb9WKFddch",
				"AssetName":"ont",
				"Description":"transfer"
			}
		]
	}
}
```


| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    TransferList.AssetName|   String|  资产名称,具体可参考**资产名称字典**|
|    TransferList.ToAddress|   String|  交易转入地址|
|    TransferList.FromAddress|   String|  交易转出地址|
|    TransferList.Amount|   String|  交易金额|
|    TransferList.Description|   String|  transfer|


- ontid 相关交易

```json
successResponse：
{
	"Detail":{
		"OntId":"did:ont:Ahctt129csbc612enxGTss6"
		"Description":"register OntId"
	}
}
```


| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    OntId|   String|  OntId|
|    Description|   String|  OntId 操作描述，具体字段参考 **OntId 操作描述字典**|


