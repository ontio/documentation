

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


### Get daily info

```json
url：/api/v1/explorer/daily/info/{starttime}/{endtime}
method：GET
successResponse：
{
	"Action": "QueryDailyInfo",
	"Error": 0,
	"Desc": "SUCCESS",
	"Version": "1.0",
	"Result": [
		{
			"TxnCount": 155,
			"AddressCount": 4,
			"BlockCount": 414,
			"OntIdCount": 0,
			"Time": "2018-12-06"
		},
		{
			"TxnCount": 233,
			"AddressCount": 16,
			"BlockCount": 12,
			"OntIdCount": 12,
			"Time": "2018-12-07"
		}
	]
}
```

| RequestField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    starttime|   int| 开始时间，unix时间戳   |
|    endtime|   int| 截止时间，unix时间戳   |


| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    Time|   string|   format:yyyy-MM-dd |
|    TxnCount|   int|  |
|    AddressCount|   int|  |
|    BlockCount|   int|  |
|    OntIdCount|   int|  |

