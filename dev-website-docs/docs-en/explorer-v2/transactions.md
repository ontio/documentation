

## 2.Transaction APIs

#### Transaction type

| Value | Type | Description                  |
| ----- | ---- | ---------------------------- |
| 208   | int  | deploy smart contract        |
| 209   | int  | invoke neovm smart contract  |
| 210   | int  | invoke wasmvm smart contract |

#### Description

| Value                    | Type   | Description                                             |
| ------------------------ | ------ | ------------------------------------------------------------ |
| transfer                 | String | transfer                                                 |
| gasconsume               | String | consumed gas                                                 |
| ontId-                   | String | Ont ID                                                       |
| claimRecord-             | String | claim Record                                                 |
| auth                     | String | authorization                                                |
| {"NeedStorage":true, ...} | String | If the transaction type is 208, the filed content is the description of the contract |

#### Event Type

| Value | Type | Description     |
| ----- | ---- | --------------- |
| 0     | int  | others          |
| 1     | int  | deploy contract |
| 2     | int  | gas consumed    |
| 3     | int  | transfer        |
| 4     | int  | ONT ID          |
| 5     | int  | claim record    |
| 6     | int  | authorization   |



### 2.1 Get latest transaction list

```java
url: /v2/latest-transactions?count=10, 
method: GET, 
params: {
}, 
successResponse: {
    "code":0, 
    "msg":"SUCCESS", 
    "result":[
        {
            "tx_hash":"9762458cd30612509f7c...a010ccc7b347057eb5", 
            "tx_type":209, 
            "tx_time":1522210288, 
            "block_height":1212, 
            "confirm_flag":1, 
            "block_index":1, 
            "fee":"0.01"
        }
    ]
}
```



| Url RequestField | Type | Description                                 |
| ---------------- | ---- | ------------------------------------------- |
| count            | int  | number of latest transactions (count is limited between 1 and 50) |



| ResponseField |  Type  |                     Description                     |
| :-----------: | :----: | :-------------------------------------------------: |
|    tx_hash    | String |                  transaction hash                   |
|    tx_type    |  int   |         transaction type (208/209/210)              |
|    tx_time    |  int   |            UNIX time of the transaction             |
| block_height  |  int   |                    block height                     |
| confirm_flag  |  int   | transaction state on the blockchain, 0:failure 1:success |
|  block_index  |  int   |          The index of transactions within a block   |
|      fee      | String |                         fee                         |

### 2.2 Get transaction list by page

```java
url：/v2/transactions?page_size=10&page_number=1, 
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
        "total":23449
    }
}
```

| Url RequestField | Type | Description                                     |
| ---------------- | ---- | ----------------------------------------------- |
| page_size        | int  | number of records in one page (limited between 1 and 20)|
| page_number      | int  | page number (atleast 1 or greater)        |



| ResponseField |  Type  |                     Description                     |
| :-----------: | :----: | :-------------------------------------------------: |
|     total     |  int   |                 total transactions                  |
|    tx_hash    | String |                  transaction hash                   |
|    tx_type    |  int   |         transaction type (208/209/210)              |
|    tx_time    |  int   |            UNIX time of the transaction             |
| block_height  |  int   |                    block height                     |
| confirm_flag  |  int   | transaction state on the blockchain, 0:failure 1:success |
|  block_index  |  int   |          The index of transactions within a block         |
|      fee      | String |             transaction fee                         |



### 2.3 Get latest non-ontid transaction list

```java
url: /v2/latest-nonontid-transactions?count=10, 
method: GET, 
params: {
}, 
successResponse: {
    "code":0, 
    "msg":"SUCCESS", 
    "result":[
        {
            "tx_hash":"9762458cd30612509f7c...a010ccc7b347057eb5", 
            "tx_type":209, 
            "tx_time":1522210288, 
            "block_height":1212, 
            "confirm_flag":1, 
            "block_index":1, 
            "fee":"0.01"
        }
    ]
}
```



| Url RequestField | Type | Description                                         |
| ---------------- | ---- | --------------------------------------------------- |
| count            | int  | number of latest non-ontid transactions (limited between 1 and 50) |



| ResponseField |  Type  |                     Description                     |
| :-----------: | :----: | :-------------------------------------------------: |
|    tx_hash    | String |                  transaction hash                   |
|    tx_type    |  int   |            transaction type (209/210)               |
|    tx_time    |  int   |            UNIX time of the transaction             |
| block_height  |  int   |                    block height                     |
| confirm_flag  |  int   | transaction state on the blockchain, 0:failure 1:success|
|  block_index  |  int   |          The index of transactions within a block         |
|      fee      | String |             transaction fee                         |

### 2.4 Get non-ontid transaction list by page

```java
url：/v2/nonontid-transactions?page_size=1&page_number=10, 
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
        "total":23449
    }
}
```

| Url RequestField | Type | Description                                     |
| ---------------- | ---- | ----------------------------------------------- |
| page_size        | int  | number of records in one page (limited between 1 and 20) |
| page_number      | int  | page number (atleast 1 or greater)             |




| ResponseField |  Type  |                     Description                     |
| :-----------: | :----: | :-------------------------------------------------: |
|     total     |  int   |                 total transactions                  |
|    tx_hash    | String |                  transaction hash                   |
|    tx_type    |  int   |         transaction type (208/209/210)              |
|    tx_time    |  int   |            UNIX time of the transaction             |
| block_height  |  int   |                    block height                     |
| confirm_flag  |  int   | transaction state on the blockchain, 0:failure 1:success |
|  block_index  |  int   |          The index of transactions within a block         |
|      fee      | String |                         fee                         |



### 2.5 Get transaction detail by txhash

```java
url：/v2/transactions/{tx_hash}, 
method：GET, 
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":{
        "tx_hash":"000004c9903c338...ee5505e171e6d752dbd", 
        "tx_type":209, 
        "tx_time":1522210288, 
        "block_height":1212, 
        "confirm_flag":1, 
        "block_index":1, 
        "fee":"0.01", 
        "description":"transfer", 
        "event_type":3, 
        "detail":{
        
        }
    }
}

```

| Url RequestField | Type   | Description      |
| ---------------- | ------ | ---------------- |
| tx_hash          | String | transaction hash |



| ResponseField |  Type  |                     Description                     |
| :-----------: | :----: | :-------------------------------------------------: |
|    tx_hash    | String |                  transaction hash                   |
|    tx_type    |  int   |         transaction type (208/209/210)          |
|    tx_time    |  int   |            UNIX time of the transaction             |
| block_height  |  int   |                    block height                     |
| confirm_flag  |  int   | transaction state on the blockchain, 0:failure 1:success |
|  block_index  |  int   |          The index of transactions within a block         |
|      fee      | String |                         fee                         |
|  description  | String |        transaction description for given **ONT ID**         |
|  event_type   |  int   |         event type reference        |
|    detail     | Object |                 transaction detail                  |

**`detail` field:**

- Deploy smart contract transaction

Smart contract detail in **description** filed

  ```java
  {
  	"detail":{}
  }
  
  ```

- Transfer transaction

```java
{
	"detail":{
		"transfers": [
			{
				"amount": "0.02", 
				"from_address":"Aege6VvWEiKauFa2ngrtwdXt8FeGkWNPRH", 
				"to_address":"ATUD7W6t6tLPGgd8H9tCN6Kwkb9WKFddch", 
				"asset_name":"ont",
				"contract_hash":"9762458cd30612509f7c...",
				"description":"transfer"
			}
		]
	}
}

```

|     ResponseField      |  Type  |             Description              |
| :--------------------: | :----: | :----------------------------------: |
|  transfers.asset_name  | String |              asset name              |
|  transfers.to_address  | String |               toaddres               |
| transfers.from_address | String |             fromaddress              |
|    transfers.amount    | String |                amount                |
| transfers.description  | String | transfer reference |
| transfers.contract_hash | String | contract hash |

- ONT ID transaction

```json
{
	"detail":{
		"ontid":"did:ont:Ahctt129csbc612enxGTss6", 
		"description":"register OntId"
	}
}

```

| ResponseField |  Type  |           Description            |
| :-----------: | :----: | :------------------------------: |
|     ontid     | String |              OntId               |
|  description  | String | transaction description for given **ONT ID** |


