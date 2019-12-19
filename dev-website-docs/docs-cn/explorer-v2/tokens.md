

## 6.Token APIs

#### Vm_Category Type

| value |  Type  | Description |
| :---: | :----: | :---------: |
| neovm | String |   neo vm    |
| wasmv | String |   wasm vm   |

#### 

### 6.1 Get token list by token type

```java
url：/v2/tokens/{token_type}?page_size=10&page_number=1, 
method：GET, 
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":{
        "records":[
            {
                "contract_hash": "16edbe366d1337eb...4c94aeef02", 
                "creator": "AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ", 
                "description": "30", 
                "logo": "", 
                "create_time":1516946305, 
                "update_time":1516948340, 
                "contact_info":"{\"website\":\"www.test.cn\", \"github\":\"github.com\"}", 
                "total_supply": 1000000000, 
                "name": "name", 
                "symbol": "MYT", 
                "decimals": 8, 
                "address_count": 1, 
                "tx_count": 30, 
                "vm_category":"neovm"
            }
        ], 
        "total":12
    }
}

```

| Url RequestField | Type   | Description                                     |
| ---------------- | ------ | ----------------------------------------------- |
| token_type       | String | oep4, oep5, oep8                                  |
| page_size        | int    | number of records in one page (The page size is limited between 1 and 20) |
| page_number      | int    | number of the page (At least 1 or greater)              |

| ResponseField |  Type  |                         Description                          |
| :-----------: | :----: | :----------------------------------------------------------: |
| contract_hash | String |                        contract hash                         |
|     name      | String |                        contract name                         |
|    creator    | String |                       creator address                        |
|  description  | String |                     contract description                     |
|     logo      | String |                           logo url                           |
|  create_time  |  int   |                         create time                          |
|  update_time  |  int   |                         update time                          |
| contact_info  | String |            contact information.JSON format string            |
| total_supply  |  int   |                  total supply of the token                   |
|    symbol     | String |                     symbol of the token                      |
|   decimals    |  int   | decimals of the token. If the token type is oep5, response not have this param |
| address_count |  int   |                        total address                         |
|   tx_count    |  int   |                      total transaction                       |
|  vm_category  | String |                       neovm  or wasmvm                       |
|     total     |  int   |                        total contract                        |

##### Oep8 token

If the param `token_type` == **oep8**, then the result is:

```java
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":{
        "records":[
            {
                "contract_hash": "16edbe366d1337eb...4c94aeef02", 
                "name": "name", 
                "creator": "AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ", 
                "description": "test contract", 
                "logo": "", 
                "create_time":1516946305, 
                "update_time":1516948340, 
                "contact_info":"{\"website\":\"www.tst.cn\", \"github\":\"github.com\"}", , 
                "total_supply": {
                	"01":"1002", 
                	"02":"899", 
                	"03":"321"
                }, 
                "symbol": {
                	"01":"TNA", 
                	"02":"TNB", 
                	"03":"TNC"
                }, 
                "token_name":{
                	"01":"TokenNameFrist", 
                	"02":"TokenNameSecond", 
                	"03":"TokenNameThird"
                }, 
                "token_id":{
                	"01":"01", 
                	"02":"02", 
                	"03":"03"
                }
                "address_count": 1, 
                "tx_count": 30, 
                "vm_category":"neovm"
            }
        ], 
        "total":12
    }
}


```





### 6.2 Get token detail by token type and contracthash

```java
url：/v2/tokens/{token_type}/{contract_hash}, 
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
        "description": "oep4 token", 
        "creator": "AFmseVrdL9f9oyC....G6UbvhPbdYzM", 
        "ont_sum": "2123.000000000", 
        "ong_sum": "1233123123.000000000", 
        "address_count": 122, 
        "tx_count": 30, 
        "token_sum":{\"Ht\":\"124\"}", 
        "category":"oep", 
        "type":"oep4", 
        "total_supply": 1000000000, 
        "symbol": "MYT", 
        "decimals": 8, 
        "vm_category":""
    }
}

```

| Url RequestField | Type   | Description    |
| ---------------- | ------ | -------------- |
| token_type       | String | oep4, oep5, oep8 |
| contract_hash    | String | contract_hash  |

| ResponseField |  Type  |                         Description                          |
| :-----------: | :----: | :----------------------------------------------------------: |
| contract_hash | String |                        contract hash                         |
|     name      | String |                        contract name                         |
|  create_time  |  int   |                         create time                          |
|  update_time  |  int   |                         update time                          |
| contact_info  | String |            contact information.JSON format string            |
|     logo      | String |                           logo url                           |
|  description  | String |                     contract description                     |
|    creator    | String |                       creator address                        |
|    ong_sum    | String |                          total ong                           |
|    ont_sum    | String |                          total ont                           |
| address_count |  int   |                        total address                         |
|   tx_count    |  int   |                      total transaction                       |
|   token_sum   | String |                total token.JSON format string                |
|     type      | String |                    oep4, oep5, oep8, others                     |
|      abi      | String |                         contract abi                         |
|     code      | String |                        contract code                         |
|  source_code  | String |                     contract source code                     |
|   category    | String |                           category                           |
| total_supply  |  int   |                  total supply of the token                   |
|    symbol     | String |                     symbol of the token                      |
|   decimals    |  int   | decimals of the token. If the token type is oep5, response not have this param |
|  vm_category  | String |                       neovm or wasmvm                        |



##### Oep8 token

If the param `token_type` == **oep8**, then the result is:

```java
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
        "ont_sum": "2123.000000000", 
        "ong_sum": "1233123123.000000000", 
        "address_count": 122, 
        "tx_count": 30, 
        "token_sum":{\"Ht\":\"124\"}", 
        "category":"oep", 
        "type":"oep8", 
        "total_supply": {
            "01":"1002", 
            "02":"899", 
            "03":"321"
        }, 
        "symbol": {
            "01":"TNA", 
            "02":"TNB", 
            "03":"TNC"
        }, 
        "token_name":{
            "01":"TokenNameFrist", 
            "02":"TokenNameSecond", 
            "03":"TokenNameThird"
        }, 
        "token_id":{
            "01":"01", 
            "02":"02", 
            "03":"03"
        }
    }
}


```



### 6.3 Get oep8 token transaction list by token name

```java
url：/v2/tokens/oep8/{contract_hash}/{token_name}/transactions?page_size=10&page_number=1, 
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
                "fee":"0.01", 
    		}
    	], 
    	"total":20
    }
}

```

| Url RequestField | Type   | Description                                     |
| ---------------- | ------ | ----------------------------------------------- |
| contract_hash    | String | oep8 token contract hash                        |
| token_name       | String | oep8 token name                                 |
| page_size        | int    | number of records in one page (The page size is limited between 1 and 20) |
| page_number      | int    | number of the page (At least 1 or greater)              |

|    ResponseField     |  Type  |                     Description                     |
| :------------------: | :----: | :-------------------------------------------------: |
|   records.tx_hash    | String |                  transaction hash                   |
|   records.tx_type    |  int   |             transaction type (208/209)             |
|   records.tx_time    |  int   |            UNIX time of the transaction             |
| records.block_height |  int   |                    block height                     |
| records.confirm_flag |  int   | transaction state on the blockchain, 0:failure 1:success |
| records.block_index  |  int   |          The index of transactions within a block         |
|     records.fee      | String |                         fee                         |
|        total         |  int   |                        total                        |



