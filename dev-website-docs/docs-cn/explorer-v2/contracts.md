

## 5.Contract APIs

### 5.1 Get contract lsit

```java
url：/v2/contracts?page_size=10&page_number=1, 
method：GET, 
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":{
        "records":[
            {
                "contract_hash": "16edbe366d...99424c94aeef02", 
                "name": "name", 
                "logo":"", 
                "description": "is a decentralized, tru.....", 
                "creator": "AFmseVrdL9f9oyCzZefL9tG6UbvhPbdYzM", 
                "create_time":1516946305, 
                "update_time":1516948340, 
                "contact_info":"{\"website\":\"www.test.cn\", \"github\":\"github.com\"}", 
                "ont_sum": "2123", 
                "ong_sum": "1233123123.002", 
                "address_count": 122, 
                "tx_count": 30, 
                "token_sum":{\"Ht\":\"124\"}", 
                "category":"oep", 
                "type":"oep4", 
                "dapp_name":""
            }
        ], 
        "total":12
    }
}

```

| Url RequestField | Type | Description                                     |
| ---------------- | ---- | ----------------------------------------------- |
| page_size        | int  | number of records in one page (The page size is limited between 1 and 20) |
| page_number      | int  | number of the page (At least 1 or greater)              |

| ResponseField |  Type  |              Description               |
| :-----------: | :----: | :------------------------------------: |
| contract_hash | String |             contract hash              |
|     name      | String |             contract name              |
|  create_time  |  int   |              create time               |
|  update_time  |  int   |              update time               |
| contact_info  | String | contact information.JSON format string |
|     logo      | String |                logo url                |
|  description  | String |          contract description          |
|    creator    | String |            creator address             |
|    ong_sum    | String |               total ong                |
|    ont_sum    | String |               total ont                |
| address_count |  int   |             total address              |
|   tx_count    |  int   |           total transaction            |
|   token_sum   | String |     total token.JSON format string     |
|   category    | String |                category                |
|     type      | String |          oep4, oep5, oep8, other          |
|   dapp_name   | String |               dapp name                |
|     total     |  int   |             total contract             |



### 5.2 Get contract detail by contract_hash

```java
url：/v2/contracts/{contract_hash}, 
method：GET, 
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":{
        "contract_hash": "16edbe366d...99424c94aeef02", 
        "name": "name", 
        "abi":"25a80bbc...5381", 
        "code": "013ec56b6...006a5", 
        "source_code":"", 
        "create_time":1516946305, 
        "update_time":1516948340, 
        "contact_info":"{\"website\":\"www.test.cn\", \"github\":\"github.com\"}", 
        "logo":"", 
        "description": "LuckyNumber is a decentralized, tru.....", 
        "creator": "AFmseVrdL9f9oyCzZefL9tG6UbvhPbdYzM", 
        "ont_sum": "2123", 
        "ong_sum": "1233123123", 
        "address_count": 122, 
        "tx_count": 30, 
        "token_sum":{\"Ht\":\"124\"}", 
        "category":"oep", 
        "type":"oep5", 
        "dapp_name":""
    }
}

```

| Url RequestField | Type   | Description   |
| ---------------- | ------ | ------------- |
| contract_hash    | String | contract hash |

| ResponseField |  Type  |              Description               |
| :-----------: | :----: | :------------------------------------: |
| contract_hash | String |             contract hash              |
|     name      | String |             contract name              |
|  create_time  |  int   |              create time               |
|  update_time  |  int   |              update time               |
| contact_info  | String | contact information.JSON format string |
|     logo      | String |                logo url                |
|  description  | String |          contract description          |
|    creator    | String |            creator address             |
|    ong_sum    | String |               total ong                |
|    ont_sum    | String |               total ont                |
| address_count |  int   |             total address              |
|   tx_count    |  int   |           total transaction            |
|   token_sum   | String |     total token.JSON format string     |
|     type      | String |         oep4, oep5, oep8, others          |
|      abi      | String |              contract abi              |
|     code      | String |             contract code              |
|  source_code  | String |          contract source code          |
|   category    | String |                category                |
|   dapp_name   | String |               dapp name                |



### 5.3 Get contract transaction list by contracthash

```java
url：/v2/contracts/{contract_type}/{contract_hash}/transactions?page_size=10&page_number=1, 
method：GET, 
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":{
    	"records":[
    		{
                "tx_hash":"9762458cd30612509f7c...a010ccc7b347057eb5", 
                "tx_type":209, 
                "tx_time":1522210288, 
                "block_height":1212, 
                "confirm_flag":1, 
                "block_index":1, 
                "fee":"0.01"
    		}
    	], 
    	"total":20
    }
}

```

| Url RequestField | Type   | Description                                     |
| ---------------- | ------ | ----------------------------------------------- |
| page_size        | int    | number of records in one page (The page size is limited between 1 and 20) |
| page_number      | int    | number of the page (At least 1 or greater)              |
| contract_type    | String | oep4, oep5, oep8, other                            |
| contract_hash    | String | contract_hash                                   |

|    ResponseField     |  Type  |                     Description                     |
| :------------------: | :----: | :-------------------------------------------------: |
|   records.tx_hash    | String |                  transaction hash                   |
|   records.tx_type    |  int   |         transaction type (208/209/210)          |
|   records.tx_time    |  int   |            UNIX time of the transaction             |
| records.block_height |  int   |                    block height                     |
| records.confirm_flag |  int   | transaction state on the blockchain, 0:failure 1:success |
| records.block_index  |  int   |          The index of transactions within a block         |
|       txs.fee        | String |                         fee                         |
|        total         |  int   |                        total                        |



#### HyperDragon Oep5 Contract

Response two more parameters：

- asset_name：asset name
- json_url：json data

```java
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":{
    	"txs":[
    		{
                "tx_hash":"9762458cd30612509f7c...a010ccc7b347057eb5", 
                "tx_type":209, 
                "tx_time":1522210288, 
                "block_height":1212, 
                "confirm_flag":1, 
                "block_index":1, 
                "fee":"0.01", 
                "asset_name":"HyperDragons: 1360", 
                "json_url":"{\"image\":\"https://hyd-go-res.alfakingdom.com/normal/1360.svg\", \"name\":\"dragon#1360\"}"   //如果asset_name没有找到对应的json描述，该字段不返回
    		}
    	], 
    	"total":20
    }
}

```





### 5.4 Get contract transaction list by contracthash

```java
url：/v2/contracts/{contract_hash}/transactions?page_size=10&page_number=1, 
method：GET, 
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":{
    	"records":[
    		{
                "tx_hash":"9762458cd30612509f7c...a010ccc7b347057eb5", 
                "tx_type":209, 
                "tx_time":1522210288, 
                "block_height":1212, 
                "confirm_flag":1, 
                "block_index":1, 
                "fee":"0.01"
    		}
    	], 
    	"total":20
    }
}

```

| Url RequestField | Type   | Description                                     |
| ---------------- | ------ | ----------------------------------------------- |
| page_size        | int    | number of records in one page (The page size is limited between 1 and 20) |
| page_number      | int    | number of the page (At least 1 or greater)              |
| contract_type    | String | oep4, oep5, oep8, other                            |
| contract_hash    | String | contract_hash                                   |

|    ResponseField     |  Type  |                     Description                     |
| :------------------: | :----: | :-------------------------------------------------: |
|   records.tx_hash    | String |                  transaction hash                   |
|   records.tx_type    |  int   |         transaction type (208/209/210)          |
|   records.tx_time    |  int   |            UNIX time of the transaction             |
| records.block_height |  int   |                    block height                     |
| records.confirm_flag |  int   | transaction state on the blockchain, 0:failure 1:success |
| records.block_index  |  int   |          The index of transactions within a block         |
|       txs.fee        | String |                         fee                         |
|        total         |  int   |                        total                        |



#### Hyperdragon OEP5 contract

Two extra fields in response:

- asset_name：Name of the asset
- json_url: JSON string of the dragon logo and name. If the `asset_name` doesn't have a corresponding JSON description, this field will not be returned

```java
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":{
    	"txs":[
    		{
                "tx_hash":"9762458cd30612509f7c...a010ccc7b347057eb5", 
                "tx_type":209, 
                "tx_time":1522210288, 
                "block_height":1212, 
                "confirm_flag":1, 
                "block_index":1, 
                "fee":"0.01", 
                "asset_name":"HyperDragons: 1360", 
                "json_url":"{\"image\":\"https://hyd-go-res.alfakingdom.com/normal/1360.svg\", \"name\":\"dragon#1360\"}"   //If the `asset_name` doesn't have a corresponding JSON description, this field will not be returned
    		}
    	], 
    	"total":20
    }
}

```





