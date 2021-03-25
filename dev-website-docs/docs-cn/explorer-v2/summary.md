

## 7.Summary APIs

### 7.1 Get blockchain,latest summary information

```java
url：/v2/summary/blockchain/latest-info, 
method：GET, 
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":{
		"block_height":12323, 
		"tx_count":52000, 
		"ontid_count":12, 
		"node_count":188, 
        "address_count":122, 
        "ontid_tx_count": 24188
    }
}

```

| ResponseField  | Type |              Description               |
| :------------: | :--: | :------------------------------------: |
|  block_height  | int  |      current latest block height       |
|    tx_count    | int  |    current latest transaction count    |
|  ontid_count   | int  |      current latest ONT ID count       |
|   node_count   | int  |       current latest node count        |
| address_count  | int  |         current address count          |
| ontid_tx_count | int  | current latest ontid transaction count |



### 7.2 Get blockchain,tps information

```java
url：/v2/summary/blockchain/tps, 
method：GET, 
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":{
	    "current_tps": "10.02", 
		"max_tps": 10000
	}
}

```

| ResponseField |  Type  | Description |
| :-----------: | :----: | :---------: |
|  current_tps  | String | current tps |
|    max_tps    | double |   max tps   |



### 7.3 Get blockchain,daily summary information

```java
url：/v2/summary/blockchain/daily?start_time=1556027861&end_time=1556087861, 
method：GET, 
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":{
    	"total": 3, 
        "records":[
              {
                  "time": 1543622400, 
                  "tx_count": 124, 
                  "block_count": 120, 
                  "active_address_count": 21, 
                  "new_address_count": 12, 
                  "ong_sum": "1204.003", 
                  "ont_sum": "342451", 
                  "active_ontid_count": 32, 
                  "new_ontid_count": 29, 
                  "ontid_total": 293, 
                  "address_total": 390
              }
           ]
    }
}

```

| Url RequestField | Type   | Description                |
| ---------------- | ------ | -------------------------- |
| type             | String | daily or weekly or monthly |
| start_time       | int    | start time. UNIX timestamp |
| end_time         | int    | end time. UNIX timestamp   |



|        ResponseField         |  Type  |           Description            |
| :--------------------------: | :----: | :------------------------------: |
|            total             |  int   |          total records           |
|         records.time         |  int   |          UNIX timestamp          |
|       records.tx_count       |  int   |        transaction count         |
|     records.block_count      |  int   |           block count            |
| records.active_address_count |  int   |       active address count       |
|  records.new_address_count   |  int   |        new address count         |
|       records.ong_sum        | String |             ong sum              |
|       records.ont_sum        | String |             ont sum              |
|  records.active_ontid_count  |  int   |        active ontid count        |
|   records.new_ontid_count    |  int   |         new ontid count          |
|     records.ontid_total      |  int   | total ONT ID volume as of today  |
|    records.address_total     |  int   | total address volume as of today |



### 7.4 Get contract daily summary information

```java
url：/v2/summary/contracts/{contract_hash}/daily?start_time=1556027861&end_time=1556087861, 
method：GET, 
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":{
    	"total": 3, 
        "records":[
              {
                  "time": 1543622400, 
                  "tx_count": 0, 
                  "active_address_count": 0, 
                  "new_address_count": 0, 
                  "ont_sum": "1244", 
                  "ong_sum": "324123.00345003"
              }
           ]
    }
}

```

| Url RequestField | Type   | Description                |
| ---------------- | ------ | -------------------------- |
| contract_hash    | String | contract hash              |
| start_time       | int    | start time. UNIX timestamp |
| end_time         | int    | end time. UNIX timestamp   |



|        ResponseField         |  Type  |     Description      |
| :--------------------------: | :----: | :------------------: |
|            total             |  int   |    total records     |
|         records.time         |  int   |    UNIX timestamp    |
|       records.tx_count       |  int   |  transaction count   |
| records.active_address_count |  int   | active address count |
|  records.new_address_count   |  int   |  new address count   |
|       records.ong_sum        | String |       ong sum        |
|       records.ont_sum        | String |       ont sum        |

