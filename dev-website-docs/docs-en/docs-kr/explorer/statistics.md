

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



### Get daily information

```json
url：/api/v1/explorer/daily/info/{starttime}/{endtime}
method：GET
successResponse：
{
	"Action":"QueryDailyInfo",
	"Version":"1.0",
	"Error":0,
	"Desc":"SUCCESS",
	"Result":[
		{
			"TxnCount": 1202,
			"BlockCount": 1180,
			"OntIdCount": 789,
			"Time": "2018-11-02"
		},
		{
			"TxnCount": 1002,
			"BlockCount": 902,
			"OntIdCount": 489,
			"Time": "2018-11-01"
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
|    TxnCount|   int|  该日交易总量  |
|    BlockCount|   int| 该日区块总量 |
|    OntIdCount|   int| 该日ONT ID总量 |
|    Time|   string | 日期，格式：yyyy-MM-dd |


