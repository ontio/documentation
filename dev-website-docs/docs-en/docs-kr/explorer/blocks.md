

### Get Bolck List

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
|    amount|   int|    |


| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|   Hash|   String|    |
|	Height|   int|  |
|	TxnsRoot|   String|    |
|   BookKeeper|   String|    |
|   NextBlock|   String|    |
|	ConsensusData	|	String|	  |
|	PrevBlock|	String|	  |
|	BlockSize|	int|	  |
|	BlockTime|	int|	  |
|	TxnNum|	int|	  |




### Get block list by page

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
|    pagesize|   int|    |
|    pagenumber|   int| |


| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|   BlockList.Hash|   String|    |
|   BlockList.Height|   int|  |
|   BlockList.TxnsRoot|   String|    |
|   BlockList.BookKeeper|   String|    |
|   BlockList.NextBlock|   String|    |
|	BlockList.ConsensusData	|	String|	  |
|	BlockList.PrevBlock|	String|	  |
|	BlockList.BlockSize|	int|	  |
|	BlockList.BlockTime|	int|	|
|	BlockList.TxnNum|	int|	  |
|	Total|	int|	  |


### Query Block by height or hash


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
|    param|   String|    |



| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|   Hash|   String|    |
|	Height|   int|  |
|	TxnsRoot|   String|    |
|   BookKeeper|   String|      |
|   NextBlock|   String|   |
|	ConsensusData	|	String|	  |
|	PrevBlock|	String|	  |
|	BlockSize|	int|	  |
|	BlockTime|	int|	  |
|	TxnNum|	int|	  |
|	Txnlist.TxnHash|	String|	  |
|	Txnlist.TxnType|	int|	  |
|	Txnlistist.Height|	int |	  |
|	Txnlistist.TxnTime|	int |	  |
