

### Get summary

```json
url：/api/v1/explorer/summary
method：GET
successResponse：
{
	"Action":"QuerySummaryInfo",
	"Version":"1.0",
	"Error":0,
	"Desc":"SUCCESS",
	"Result":{
		"CurrentHeight":12323,
		"TxnCount":52000,
		"NodeCount":12,
		"OntIdCount":188
	}
}
```

| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    CurrentHeight|   int|    |
|    TxnCount|   int|  |
|    NodeCount|   int|  |
|    OntIdCount|   int|  |



### Query generate block time

```json
url：/api/v1/explorer/block/generatetime/{amount}
method：GET
successResponse：
{
	"Action":"QueryBlockGenerateTime",
	"Version":"1.0",
	"Error":0,
	"Desc":"SUCCESS",
	"Result":[
		{
			"Height":1,
			"GenerateTime":6
		}
	]
}
```

| RequestField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    amount|   int|    |

| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    Height|   int|    |
|    GenerateTime|   int|  |

