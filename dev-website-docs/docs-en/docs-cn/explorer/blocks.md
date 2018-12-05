

### 获取当前区块列表

```json
url：/api/v1/explorer/blocklist/{amount}
method：GET
successResponse：
{
	"Action":"QueryBlockList",
	"Version":"1.0",
	"Error":0,
	"Desc":"SUCCESS",
	"Result":[
		{
			"Hash":"63355f8e808e4572bab07c0748bd4182a562ee73401fc16c8108e4e56b264d2a",
			"Height":112,
			"TxnsRoot":"472af7d21a8315636021940933ec8d07a7a32fe21ba91075b4c0e0b1b4576531",
			"BookKeeper":"AL4CDqBikrj92pC3B747ZchYZAQf2fg1AC&AL4CDqBikrj92pC3B747ZchYZAQf2fg1AC",
			"NextBlock":"59192b3a12497793568f2394da91725cf382556b7a72e92f58e0a6f6cab6a70d",
			"ConsensusData":"12156079575032856115",
			"PrevBlock":"3865b98b84b3af895c946b23938a5dde127ad12d4268d92fbd63e642e91b00c8",
			"BlockSize":532,
			"BlockTime":1522205080,
			"TxnNum":12
		}
	]
}
```

| RequestField|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    amount|   int|  查询的区块数量  |


| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|   Hash|   String|  区块hash  |
|	Height|   int|  区块高度|
|	TxnsRoot|   String|  该区块内所有交易的merkleroot  |
|   BookKeeper|   String|  记账人,多个记账人以"&"分割  |
|   NextBlock|   String|  下一区块hash  |
|	ConsensusData	|	String|	共识数据  |
|	PrevBlock|	String|	上一区块hash  |
|	BlockSize|	int|	区块大小，单位：byte  |
|	BlockTime|	int|	区块时间戳，unix时间戳  |
|	TxnNum|	int|	交易数  |




### 分页获取区块列表

```json
url：/api/v1/explorer/blocklist/{pagesize}/{pagenumber}
method：GET
successResponse：
{
	"Action":"QueryBlockListByPage",
	"Version":"1.0",
	"Error":0,
	"Desc":"SUCCESS",
	"Result":{
		"BlockList":{
			[
				"Hash":"63355f8e808e4572bab07c0748bd4182a562ee73401fc16c8108e4e56b264d2a",
				"Height":112,
				"TxnsRoot":"472af7d21a8315636021940933ec8d07a7a32fe21ba91075b4c0e0b1b4576531",
				"BookKeeper":"AL4CDqBikrj92pC3B747ZchYZAQf2fg1AC&AL4CDqBikrj92pC3B747ZchYZAQf2fg1AC",
				"NextBlock":"59192b3a12497793568f2394da91725cf382556b7a72e92f58e0a6f6cab6a70d",
				"ConsensusData":"12156079575032856115",
				"PrevBlock":"3865b98b84b3af895c946b23938a5dde127ad12d4268d92fbd63e642e91b00c8",
				"BlockSize":532,
				"BlockTime":1522205080,
				"TxnNum":12
			]
		},
		"Total":23449
	}
}
```


| RequestField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    pagesize|   int|  每页数量  |
|    pagenumber|   int|  第几页，页数。从1开始|


| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|   BlockList.Hash|   String|  区块hash  |
|   BlockList.Height|   int|  区块高度|
|   BlockList.TxnsRoot|   String|  该区块内所有交易的merkleroot  |
|   BlockList.BookKeeper|   String|  记账人,多个记账人以"&"分割  |
|   BlockList.NextBlock|   String|  下一区块hash  |
|	BlockList.ConsensusData	|	String|	共识数据  |
|	BlockList.PrevBlock|	String|	上一区块hash  |
|	BlockList.BlockSize|	int|	区块大小，单位：byte  |
|	BlockList.BlockTime|	int|	区块时间戳，unix时间戳|
|	BlockList.TxnNum|	int|	交易数  |
|	Total|	int|	总的区块数量  |


### 根据区块高度或区块hash获取区块详情


```json
url：/api/v1/explorer/block/{param}
method：GET
successResponse：
{
	"Action":"QueryBlock",
	"Version":"1.0",
	"Error":0,
	"Desc":"SUCCESS",
	"Result":{
		"Hash":"63355f8e808e4572bab07c0748bd4182a562ee73401fc16c8108e4e56b264d2a",
		"Height":112,
		"TxnsRoot":"472af7d21a8315636021940933ec8d07a7a32fe21ba91075b4c0e0b1b4576531",
		"BookKeeper":"AL4CDqBikrj92pC3B747ZchYZAQf2fg1AC&AL4CDqBikrj92pC3B747ZchYZAQf2fg1AC",
		"NextBlock":"59192b3a12497793568f2394da91725cf382556b7a72e92f58e0a6f6cab6a70d",
		"ConsensusData":"12156079575032856115",
		"PrevBlock":"3865b98b84b3af895c946b23938a5dde127ad12d4268d92fbd63e642e91b00c8",
		"BlockSize":532,
		"BlockTime":1522205080,
		"TxnNum":12
		"TxnList":[
			{
				"TxnHash":"627f03aad7562ebf93b5bc2d2cd2f9ff8c446e447322f62d7e834f6f2f6f15e2",
				"TxnType":209,
				"Height": 112,
				"TxnTime":1522205080
			},
			{
				"TxnHash":"",
				"TxnType":209,
				"Height": 112,
				"TxnTime":1522205080
			}		
		]	
	}
}
```

| RequestField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    param|   String|  区块高度或区块hash  |



| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|   Hash|   String|  区块hash  |
|	Height|   int|  区块高度|
|	TxnsRoot|   String|  该区块内所有交易的merkleroot  |
|   BookKeeper|   String|  记账人,多个记账人以"&"分割    |
|   NextBlock|   String|  下一区块hash  |
|	ConsensusData	|	String|	共识数据  |
|	PrevBlock|	String|	上一区块hash  |
|	BlockSize|	int|	区块大小，单位：byte  |
|	BlockTime|	int|	区块时间戳，unix时间戳  |
|	TxnNum|	int|	该区块的交易数量  |
|	Txnlist.TxnHash|	String|	交易hash  |
|	Txnlist.TxnType|	int|	交易类型  |
|	Txnlistist.Height|	int |	交易区块高度  |
|	Txnlistist.TxnTime|	int |	交易时间戳，unix时间戳  |
