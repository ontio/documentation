

## 4.Address APIs

#### Asset Type

|     value      |  Type  |            Description            |
| :------------: | :----: | :-------------------------------: |
|   oep4\|OEP4   | String |            oep4 asset             |
|   oep5\|OEP5   | String |            oep5 asset             |
|   oep8\|OEP8   | String |            oep8 asset             |
| native\|NATIVE | String | ont, ong, waitbound ong, unbound ong |

#### Native Asset

|    value     |  Type  |  Description  |
| :----------: | :----: | :-----------: |
|     ont      | String |      ont      |
|     ong      | String |      ong      |
| waitboundong | String | waitbound ong |
|  unboundong  | String |  unbound ong  |



### 4.1 Get address balance by token type

```java
url：/v2/addresses/{address}/{token_type}/balances, 
method：GET, 
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":[
		{
			"balance": "138172.922008484", 
			"asset_name": "ong", 
			"asset_type":"native", 
            "contract_hash":""
		}, 
		{
			"balance": "14006.83021186", 
			"asset_name": "waitboundong", 
			"asset_type":"native", 
            "contract_hash":""
		}, 
		{
			"balance": "71472.14798338", 
			"asset_name": "unboundong", 
			"asset_type":"native", 
            "contract_hash":""
		}, 
		{
			"balance": "8637767", 
			"asset_name": "ont", 
			"asset_type":"native", 
            "contract_hash":""
		}, 
		{
			"asset_name": "pumpkin01", 
			"balance": "7", 
			"asset_type":"oep8", 
            "contract_hash":""
		}, 
		{
			"asset_name": "TNT", 
			"balance": "19888", 
			"asset_type":"oep4", 
            "contract_hash":""
		}, 
		{
			"asset_name": "HyperDragons:2", 
			"balance": "3", 
			"asset_type":"oep5", 
            "contract_hash":""
		}
	]
}

```

| URL Field  |  Type  |                         Description                          |
| :--------: | :----: | :----------------------------------------------------------: |
|  address   | String |                           address                            |
| token_type | String | oep4\|OEP4\|oep5\|OEP5\|oep8\|OEP8\|native\|NATIVE\|all\|ALL |



| ResponseField |  Type  |            Description            |
| :-----------: | :----: | :-------------------------------: |
|  asset_name   | String |            asset name             |
|    balance    | String |              balance              |
|  asset_type   | String | asset type：oep4, oep5, oep8, native |
| contract_hash | String |           contract hash           |



### 4.2 Get address balance by asset name

```java
url：/v2/addresses/{address}/balances?asset_name={assetName}, 
method：GET, 
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":[
		{
			"balance": "138172.922008484", 
			"asset_name": "ong", 
			"asset_type":"native", 
            "contract_hash":""
		}, 
		{
			"balance": "14006.83021186", 
			"asset_name": "waitboundong", 
			"asset_type":"native", 
            "contract_hash":""
		}, 
		{
			"balance": "71472.14798338", 
			"asset_name": "unboundong", 
			"asset_type":"native", 
            "contract_hash":""
		}, 
		{
			"balance": "8637767", 
			"asset_name": "ont", 
			"asset_type":"native", 
            "contract_hash":""
		}
	]
}

```

| URL Field |  Type  |                Description                 |
| :-------: | :----: | :----------------------------------------: |
|  address  | String |                  address                   |
| assetName | String | asset name.<br>ong, ont or oep token symbol |



| ResponseField |  Type  |            Description            |
| :-----------: | :----: | :-------------------------------: |
|  asset_name   | String |            asset name             |
|    balance    | String |              balance              |
|  asset_type   | String | asset type：oep4, oep5, oep8, native |
| contract_hash | String |           contract hash           |



### 4.3 Get address balance by contract hash

```java
url：/v2/addresses/{address}/balances?contract_hash={contractHash}, 
method：GET, 
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":[
		{
			"balance": "138172.922008484", 
			"asset_name": "ong", 
			"asset_type":"native", 
            "contract_hash":""
		}, 
		{
			"balance": "14006.83021186", 
			"asset_name": "waitboundong", 
			"asset_type":"native", 
            "contract_hash":""
		}, 
		{
			"balance": "71472.14798338", 
			"asset_name": "unboundong", 
			"asset_type":"native", 
            "contract_hash":""
		}, 
		{
			"balance": "8637767", 
			"asset_name": "ont", 
			"asset_type":"native", 
            "contract_hash":""
		}
	]
}

```

|  URL Field   |  Type  |  Description  |
| :----------: | :----: | :-----------: |
|   address    | String |    address    |
| contractHash | String | contract hash |



| ResponseField |  Type  |            Description            |
| :-----------: | :----: | :-------------------------------: |
|  asset_name   | String |            asset name             |
|    balance    | String |              balance              |
|  asset_type   | String | asset type：oep4, oep5, oep8, native |
| contract_hash | String |           contract Hash           |





### 4.4  Get transaction list by address and page

```java
url：/v2/addresses/{address}/transactions?page_size=10&page_number=1, 
method：GET, 
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":[
			{
				"tx_hash":"09e599ecde6ee....55239e1b1bd291558e5a6ef3fa", 
				"confirm_flag":1, 
				"tx_type":208, 
				"tx_time":1522207168, 
				"block_height":11, 
				"fee":"0.01", 
				"block_index":1, 
				"transfers": [
					{
                        "amount": "2.01", 
                        "from_address":"Aege6VvWEiKauFa2ngrtwdXt8FeGkWNPRH", 
                        "to_address":"ATUD7W6t6tLPGgd8H9tCN6Kwkb9WKFddch", 
                        "asset_name":"ont", 
                        "contract_hash":""
					}, 
                    {
                        "amount": "0.01", 
                        "from_address":"Aege6VvWEiKauFa2ngrtwdXt8FeGkWNPRH", 
                        "to_address":"ATUD7W6t6tLPGgd8H9tCN6Kwkb9WKFddch", 
                        "asset_name":"ong", 
                        "contract_hash":""
					}
				]
			}
		]
}

```

| Url RequestField | Type   | Description                                     |
| ---------------- | ------ | ----------------------------------------------- |
| address          | String | address                                         |
| page_size        | int    | number of records in one page (The page size is limited between 1 and 20) |
| page_number      | int    | number of the page (At least 1 or greater)              |



|      ResponseField      |  Type  |                     Description                     |
| :---------------------: | :----: | :-------------------------------------------------: |
|         tx_hash         | String |                  transaction hash                   |
|      confirm_flag       |  int   | transaction state on the blockchain, 1:success 0:failure |
|      block_height       |  int   |                    block height                     |
|         tx_type         |  int   |                   (208/209/210)                  |
|         tx_time         |  int   |            UNIX time of the transaction             |
|           fee           | String |                         fee                         |
|       block_index       |  int   |                 index in the block                  |
| transfers.from_address  | String |                    from_address                     |
|  transfers.to_address   | String |                     to_address                      |
|    transfers.amount     | String |                       amount                        |
|  transfers.asset_name   | String |                     asset name                      |
| transfers.contract_hash | String |                    contract hash                    |



### 4.5  Get transaction list by address and time

```java
url：/v2/addresses/{address}/transactions?begin_time=1556017050&end_time=1556017250, 
method：GET, 
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":[
			{
				"tx_hash":"09e599ecde6ee....55239e1b1bd291558e5a6ef3fa", 
				"confirm_flag":1, 
				"tx_type":208, 
				"tx_time":1522207168, 
				"block_height":11, 
				"fee":"0.01", 
				"block_index":1, 
				"transfers": [
					{
                        "amount": "2.01", 
                        "from_address":"Aege6VvWEiKauFa2ngrtwdXt8FeGkWNPRH", 
                        "to_address":"ATUD7W6t6tLPGgd8H9tCN6Kwkb9WKFddch", 
                        "asset_name":"ont", 
                        "contract_hash":""
					}, 
                    {
                        "amount": "0.01", 
                        "from_address":"Aege6VvWEiKauFa2ngrtwdXt8FeGkWNPRH", 
                        "to_address":"ATUD7W6t6tLPGgd8H9tCN6Kwkb9WKFddch", 
                        "asset_name":"ong", 
                        "contract_hash":""
					}
				]
			}
    ]
}

```

| Url RequestField | Type   | Description                                             |
| ---------------- | ------ | ------------------------------------------------------- |
| address          | String | address                                                 |
| end_time         | int    | unxi time                                               |
| begin_time       | int    | UNIX time.<br />The maximum time range is **one week**. |



|      ResponseField      |  Type  |                    Description                     |
| :---------------------: | :----: | :------------------------------------------------: |
|         tx_hash         | String |                  transaction hash                  |
|      confirm_flag       |  int   | transaction state on the blockchain,1:success 0:failure |
|      block_height       |  int   |                    block height                    |
|         tx_type         |  int   |                     208 or 209                     |
|         tx_time         |  int   |            UNIX time of the transaction            |
|           fee           | String |                        fee                         |
|       block_index       |  int   |                 index in the block                 |
| transfers.from_address  | String |                    from_address                    |
|  transfers.to_address   | String |                     to_address                     |
|    transfers.amount     | String |                       amount                       |
|  transfers.asset_name   | String |                     asset name                     |
| transfers.contract_hash | String |                   contract hash                    |



### 4.6  Get transaction list by address and asset name and page

```java
url：/v2/addresses/{address}/{asset_name}/transactions?page_size=10&page_number=1, 
method：GET, 
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":[
			{
				"tx_hash":"09e599ecde6ee....55239e1b1bd291558e5a6ef3fa", 
				"confirm_flag":1, 
				"tx_type":208, 
				"tx_time":1522207168, 
				"block_height":11, 
				"fee":"0.01", 
				"block_index":1, 
				"transfers": [
					{
                        "amount": "2.01", 
                        "from_address":"Aege6VvWEiKauFa2ngrtwdXt8FeGkWNPRH", 
                        "to_address":"ATUD7W6t6tLPGgd8H9tCN6Kwkb9WKFddch", 
                        "asset_name":"ont", 
                        "contract_hash":""
					}
				]
			}
    	]
}

```

| Url RequestField | Type   | Description                                     |
| ---------------- | ------ | ----------------------------------------------- |
| address          | String | address                                         |
| asset_name       | String | asset name                                      |
| page_size        | int    | number of records in one page (The page size is limited between 1 and 20) |
| page_number      | int    | number of the page (At least 1 or greater)              |



|      ResponseField      |  Type  |                    Description                     |
| :---------------------: | :----: | :------------------------------------------------: |
|         tx_hash         | String |                  transaction hash                  |
|      confirm_flag       |  int   | transaction state on the blockchain,1:success 0:failure |
|      block_height       |  int   |                    block height                    |
|         tx_type         |  int   |                     208 or 209                     |
|         tx_time         |  int   |            UNIX time of the transaction            |
|           fee           | String |                        fee                         |
|       block_index       |  int   |                 index in the block                 |
| transfers.from_address  | String |                    from_address                    |
|  transfers.to_address   | String |                     to_address                     |
|    transfers.amount     | String |                       amount                       |
|  transfers.asset_name   | String |                     asset name                     |
| transfers.contract_hash | String |                   contract hash                    |



### 4.7  Get transaction list by address and asset name and time

```java
url：/v2/addresses/{address}/{asset_name}/transactions?begin_time=1556017050&end_time=1556017250, 
method：GET, 
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":[
			{
				"tx_hash":"09e599ecde6ee....55239e1b1bd291558e5a6ef3fa", 
				"confirm_flag":1, 
				"tx_type":208, 
				"tx_time":1522207168, 
				"block_height":11, 
				"fee":"0.01", 
				"block_index":1, 
				"transfers": [
					{
                        "amount": "2.01", 
                        "from_address":"Aege6VvWEiKauFa2ngrtwdXt8FeGkWNPRH", 
                        "to_address":"ATUD7W6t6tLPGgd8H9tCN6Kwkb9WKFddch", 
                        "asset_name":"ont", 
                        "contract_hash":""
					}
				]
			}
    ]
}

```

| Url RequestField | Type   | Description                                            |
| ---------------- | ------ | ------------------------------------------------------ |
| address          | String | address                                                |
| asset_name       | String | asset name                                             |
| begin_time       | int    | UNIX time                                              |
| end_time         | int    | unxi time<br />The maximum time range is **one week**. |



|      ResponseField      |  Type  |                    Description                     |
| :---------------------: | :----: | :------------------------------------------------: |
|         tx_hash         | String |                  transaction hash                  |
|      confirm_flag       |  int   | transaction state on the blockchain,1:success 0:failure |
|      block_height       |  int   |                    block height                    |
|         tx_type         |  int   |                     208 or 209                     |
|         tx_time         |  int   |            UNIX time of the transaction            |
|           fee           | String |                        fee                         |
|       block_index       |  int   |                 index in the block                 |
| transfers.from_address  | String |                    from_address                    |
|  transfers.to_address   | String |                     to_address                     |
|    transfers.amount     | String |                       amount                       |
|  transfers.asset_name   | String |                     asset name                     |
| transfers.contract_hash | String |                   contract hash                    |





