

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
|    CurrentHeight|   int|  current block height  |
|    TxnCount|   int| total number of transactions  |
|    NodeCount|   int| total number of nodes |
|    OntIdCount|   int| total number of ontids |



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


# Query TPS Info

  url：/api/v1/explorer/summary/tps

	method：GET
  
  	successResponse：
	{
	    "Action": "QueryTps",
	    "Error": 0,
	    "Desc": "SUCCESS",
	    "Version": "1.0",
	    "Result": {
	        "CurrentTps": "10.02",
		"MaxTps": 10000
		}
	}


| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
| CurrentTps|   String|    |
| MaxTps|	int|	  |



# Query Summary Info

## type： daily or weekly or monthly

  url：/api/v1/explorer/summary/{type}/{starttime}/{endtime}

	method：GET
  
  	successResponse：
	{
	    "Action": "QuerySummary",
	    "Error": 0,
	    "Desc": "SUCCESS",
	    "Version": "1.0",
	    "Result": {
          "Total": 3,
          "SummaryList": [
              {
                  "TxnCount": 0,
                  "ActiveAddress": 0,
                  "BlockCount": 0,
                  "OngCount": "0.000000000",
                  "OntIdActiveCount": 0,
                  "OntIdNewCount": 0,
                  "NewAddress": 0,
                  "OntCount": "0.000000000",
                  "Time": "2018-07-02"
              },
            .......
           ]
      }
	}

| RequestField|     Type |   Description   | 
| :--------------: | :--------:| :------: |
| type|   String|     daily or weekly or monthly |
| starttime|   int|   dayTime(2018-06-30 00:00:00   : 1530288000)  |
| endtime|   int|     dayTime(2018-07-01 00:00:00   : 1530460800)  |



| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
| Total|   int|    |
| Time|	String|	  |
| TxnCount|   int|  |
| BlockCount|   int|    |
| ActiveAddress|   int|    |
| NewAddress|	int|	  
| OntCount|   String|    |
| OngCount|	String|	  |
| OntIdActiveCount|	int|	  |
| OntIdNewCount|	int|	  |


# Query Contract Info

## type： daily or weekly or monthly

  url：/api/v1/explorer/summary/contract/{contracthash}/{type}/{starttime}/{endtime}

	method：GET
  
  	successResponse：
	{
	    "Action": "QueryContract",
	    "Error": 0,
	    "Desc": "SUCCESS",
	    "Version": "1.0",
	    "Result": {
          "Total": 20,
          "OntCountSum": "0.000000000",
          "OngCountSum": "179923.466767857",
          "AddressSum": 7,
          "TxCountSum": 13,
          "SummaryList": [
              {
                  "Time": "2018-07-02",
                  "TxnCount": 0,
                  "ActiveAddress": 0,
                  "NewAddress": 0,
                  "OntCount": "0.000000000",
                  "OngCount": "0.000000000"
              },
            .......
           ]
      }
	}

| RequestField|     Type |   Description   | 
| :--------------: | :--------:| :------: |
| contracthash|   String|      |
| type|   String|     daily or weekly or monthly |
| starttime|   int|   dayTime(2018-06-30 00:00:00   : 1530288000)  |
| endtime|   int|     dayTime(2018-07-01 00:00:00   : 1530460800)  |



| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
| Total|   int|    |
| TxCountSum|	int|	total tx count of contract  |
| AddressSum|   int|   total address count of contract  |
| OntCountSum|   String|   total ont count of contract |
| OngCountSum|   String|  total ong count of contract  |
| Time|	String|	  
| TxnCount|	int|	  
| ActiveAddress|   int|    |
| NewAddress|	int|	  |
| OntCount|	String|	  |
| OngCount|	String|	  |


# Query Project Info

## type： daily or weekly or monthly

  url：/api/v1/explorer/summary/project/{project}/{type}/{starttime}/{endtime}

	method：GET
  
  	successResponse：
	{
	    "Action": "QueryProject",
	    "Error": 0,
	    "Desc": "SUCCESS",
	    "Version": "1.0",
	    "Result": {
          "Total": 20,
          "OntCountSum": "0.000000000",
          "OngCountSum": "110.000000000",
          "AddressSum": 7,
          "TxCountSum": 13,
          "SummaryList": [
              {
                  "Time": "2018-07-02",
                  "TxnCount": 0,
                  "ActiveAddress": 0,
                  "NewAddress": 0,
                  "OntCount": "0.000000000",
                  "OngCount": "0.000000000"
              },
            .......
           ]
      }
	}

| RequestField|     Type |   Description   | 
| :--------------: | :--------:| :------: |
| project|   String|   projectName   |
| type|   String|     daily or weekly or monthly |
| starttime|   int|   dayTime(2018-06-30 00:00:00   : 1530288000)  |
| endtime|   int|     dayTime(2018-07-01 00:00:00   : 1530460800)  |



| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
| Total|   int|      |
| TxCountSum  |	int  |	total tx count of project  |
| AddressSum  |   int    |   total address count of project |
| OntCountSum|   String  |  total ont count of project  |
| OngCountSum|   String  |    total ong count of project    |
| Time    |	String   |	     |
| TxnCount|	int   |	     |
| ActiveAddress|   int|      |
| NewAddress  |	int  |	  |
| OntCount|	String|	  |
| OngCount|	String|	  |
