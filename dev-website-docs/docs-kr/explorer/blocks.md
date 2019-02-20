

### 블록정보 얻기

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
			"BookKeeper":"AL4CDqBikrj92pC3B747ZchYZAQf2fg1AC&AL4CDqBikrj92pC3B747ZchYZAQf2fg1AC&AMvXn7U9S3Pq7hah16Euu7wX52UHtHyqNr",
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
|    amount|   int|   amount  |


| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|   Hash|   String|   block hash |
|	Height|   int|  block height |
|	TxnsRoot|   String|  the merkleroot of all transactions in the block  |
|   BookKeeper|   String|   keepers of this block,divided by & | 
|   NextBlock|   String|   next block hash |
|	ConsensusData	|	String|	consensus data  |
|	PrevBlock|	String|	previous block hash  |
|	BlockSize|	int|   size of this block, unit:byte  |
|	BlockTime|	int|	unix time of this block|
|	TxnNum|	int|	the number of transactions|




### 페이지에서 블록목록 받기

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
|    pagesize|   int|   pagesize. 1-20 |
|    pagenumber|   int| pagenumber. start from 1 |


| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|   BlockList.Hash|   String|  block hash  |
|   BlockList.Height|   int| block height  |
|   BlockList.TxnsRoot|   String|  the merkleroot of all transactions in the block   |
|   BlockList.BookKeeper|   String| keepers of this block,divided by &   |
|   BlockList.NextBlock|   String|  next block hash  |
|	BlockList.ConsensusData	|	String|	 consensus data |
|	BlockList.PrevBlock|	String|	  previous block hash |
|	BlockList.BlockSize|	int|	size of this block, unit:byte  |
|	BlockList.BlockTime|	int|	unix time of this block	|
|	BlockList.TxnNum|	int|	the number of transactions  |
|	Total|	int|total number of blocks  |


### 블록의 높이 혹은 블록의 해시값으로 블록 제부정보 가져오기


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
|    param|   String| block hash or block height   |



| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|   Hash|   String|   block hash  |
|	Height|   int| block height  |
|	TxnsRoot|   String|  the merkleroot of all transactions in the block  |
|   BookKeeper|   String|    keepers of this block,divided by &  |
|   NextBlock|   String|  next block hash |
|	ConsensusData	|	String|	 consensus data |
|	PrevBlock|	String|	previous block hash  |
|	BlockSize|	int|	size of this block, unit:byte  |
|	BlockTime|	int|	unix time of this block  |
|	TxnNum|	int|	the number of transactions   |
|	Txnlist.TxnHash|	String|	 transaction hash  |
|	Txnlist.TxnType|	int|	transaction type.208 or 209  |
|	Txnlistist.Height|	int |	block height  |
|	Txnlistist.TxnTime|	int |	unix time of the block  |
