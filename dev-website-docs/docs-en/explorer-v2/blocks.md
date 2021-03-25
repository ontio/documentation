

## 1. Block APIs

### 1.1 Get latest block list

```java
url: /v2/latest-blocks?count=10, 
method: GET, 
params: {
}, 
successResponse: {
    "code":0, 
    "msg":"SUCCESS", 
    "result":[
        {
            "block_hash":"63355f8e80...6c8108e4e56b264d2a", 
            "block_height":112, 
            "txs_root":"472af7d21a83156...75b4c0e0b1b4576531", 
            "bookkeepers":"AMvXn7U9...HyqNr&AL4CDqBikrj...ZAQf2fg1AC", 
            "consensus_data":"12156079575032856115", 
            "block_size":532, 
            "block_time":1522205080, 
            "tx_count":12
        }
    ]
}
```

| Url RequestField | Type | Description                           |
| ---------------- | ---- | ------------------------------------- |
| count            | int  | number of latest blocks. (limited between 1 and 50) |


| ResponseField  | Type   | Description                                     |
| -------------- | ------ | ----------------------------------------------- |
| block_hash     | String | block hash                                      |
| block_height   | int    | block height                                    |
| txs_root       | String | the merkleroot of all transactions in the block |
| bookkeepers    | String | keepers of this block, divided by `&`            |
| consensus_data | String | consensus data                                  |
| block_size     | int    | size of this block, unit:bytes                   |
| block_time     | int    | UNIX time of this block                         |
| tx_count       | int    | the number of transactions in this block        |



### 1.2 Get block list by page

```java
url：/v2/blocks?page_size=1&page_number=10, 
method：GET, 
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":{
        "records":[
            {
                "block_hash":"63355f8e80...6c8108e4e56b264d2a", 
                "block_height":112, 
                "txs_root":"472af7d21a83156...75b4c0e0b1b4576531", 
                "bookkeepers":"AMvXn7U9...HyqNr&AL4CDqBikrj...ZAQf2fg1AC", 
                "consensus_data":"12156079575032856115", 
                "block_size":532, 
                "block_time":1522205080, 
                "tx_count":12
            }
        ], 
        "total":23449
    }
}
```

| Url RequestField | Type | Description                                     |
| ---------------- | ---- | ----------------------------------------------- |
| page_size        | int  | number of records in one page (The page size is limited between 1 and 20) |
| page_number      | int  | number of the page (At least 1 or greater)              |

| ResponseField  | Type   | Description                                     |
| -------------- | ------ | ----------------------------------------------- |
| total          | int    | total blocks                                    |
| block_hash     | String | block hash                                      |
| block_height   | int    | block height                                    |
| txs_root       | String | the merkleroot of all transactions in the block |
| bookkeepers    | String | keepers of this block, divided by `&`            |
| consensus_data | String | consensus data                                  |
| block_size     | int    | size of this block, unit:bytes                   |
| block_time     | int    | UNIX time of this block                         |
| tx_count       | int    | the number of transactions in this block        |



### 1.3 Get block detail by height or hash

```java
url：/v2/blocks/{param}
method：GET
successResponse：
{
	"code":0, 
	"msg":"SUCCESS", 
	"result":{
        "block_hash":"63355f8e80...6c8108e4e56b264d2a", 
        "block_height":112, 
        "txs_root":"472af7d21a83156...75b4c0e0b1b4576531", 
        "bookkeepers":"AL4CDqBikr...Qf2fg1AC&AL...g1AC", 
        "consensus_data":"12156079575032856115", 
        "block_size":532, 
        "block_time":1522205080, 
        "tx_count":12, 
        "txs":[
        	{
        		"tx_hash":"000062c6fe4...9a1c33721", 
        		"tx_type":209, 
        		"tx_time":1522205080, 
        		"confirm_flag":1
        	}
        ]
	}
}
```

| Url Field | Type   | Description                |
| --------- | ------ | -------------------------- |
| param     | String | block height or block hash |



| ResponseField    | Type   | Description                                        |
| ---------------- | ------ | -------------------------------------------------- |
| block_hash       | String | block hash                                         |
| block_height     | int    | block height                                       |
| txs_root         | String | the merkleroot of all transactions in the block    |
| bookkeepers      | String | keepers of this block, divided by `&`               |
| consensus_data   | String | consensus data                                     |
| block_size       | int    | size of this block, unit:bytes                      |
| block_time       | int    | UNIX time of this block                            |
| tx_count         | int    | the number of transactions in this block           |
| txs.tx_hash      | String | transaction hash                                   |
| txs.tx_type      | int    | transaction type (208/209/210)                 |
| txs.confirm_flag | int    | transaction state on the blockchain, 1:succees 0:failure |
| txs.tx_time      | int    | UNIX time of the transaction                       |

### 1.4 Get latest blocks

```java
url：/v2/blocks/generate-time?count=10, 
method：GET, 
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":[
		{
			"block_height":1, 
			"generate_time":6
		}, 
		{
			"block_height":2, 
			"generate_time":1
		}
	]
}
```

| RequestField | Type |         Description         |
| :----------: | :--: | :-------------------------: |
|    count     | int  | number of the latest blocks |

| ResponseField | Type |              Description              |
| :-----------: | :--: | :-----------------------------------: |
| block_height  | int  |             block height              |
| generate_time | int  | time of block generation，unit:seconds |
