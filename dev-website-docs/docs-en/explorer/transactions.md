

### Txn Type

| Value     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    208|   int|  deploy smart contract |
|    209|   int|  invoke smart contract|

### Description

| Value     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    transfer|   String|  transfer  |
|    gasconsume|   String|  gas consume  |
|    ontId- |   String|  OntId |
|    claimRecord- |   String|  claim Record  |
|    auth |   String|  auth  |




### Query transaction list by transaction amount

```json
url：/api/v1/explorer/transactionlist/{amount}
method：GET
successResponse：
{
	"Action":"QueryTransaction",
	"Version":"1.0",
	"Error":0,
	"Desc":"SUCCESS",
	"Result":[
		{
			"TxnHash":"9762458cd30612509f7cda589b7e1f7e59cb35d200eeb0a010ccc7b347057eb5",
            "TxnType":209,
            "TxnTime":1522210288,
            "Height":1212,
            "ConfirmFlag":1,
			"BlockIndex":1,
			"Fee":"0.010000000"
	    }
	]
}
```

| RequestField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    amount|   int|  amount  |

| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    TxnHash|   String|    |
|    TxnType|   int|  |
|    TxnTime|   int|    |
|    Height|   int|    |
|    BlockIndex|   int|  index in the block  |
|    ConfirmFlag|   int |   1:success. 0:fail|
|    Fee|   String |   |



### Query transaction list by page


```json
url：/api/v1/explorer/transactionlist/{pagesize}/{pagenumber}
method：GET
successResponse：
{
	"Action":"QueryTransaction",
	"Version":"1.0",
	"Error":0,
	"Desc":"SUCCESS",
	"Result":{
		"TxnList":{
			[
				"TxnHash":"9762458cd30612509f7cda589b7e1f7e59cb35d200eeb0a010ccc7b347057eb5",
	            "TxnType":209,
	            "TxnTime":1516946305,
	            "Height":1212,
	            "ConfirmFlag":1,
				"BlockIndex":1,
				"Fee":"0.010000000"
			]
		},
		"Total":12
	}
}
```

| RequestField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    pagesize|   int|  pagesieze. 1-20  |
|    pagenumber|   int| pagenumber. start from 1 |



| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    Txnlistist.TxnHash|   String|    |
|    Txnlistist.TxnType|   int|  |
|    Txnlistist.TxnTime|   int|    |
|    Txnlistist.Height|   int|    |
|    Txnlistist.BlockIndex|   int|    |
|    Txnlistist.ConfirmFlag|   int|   |
|    Txnlistist.Fee|   String |   |
|    Total|   int|   |



### Query transaction information by transaction hash 


```json
url：/api/v1/explorer/transaction/{txnhash}
method：GET
successResponse：
{
	"Action":"QueryTransaction",
	"Version":"1.0",
	"Error":0,
	"Desc":"SUCCESS",
	"Result":{
		"TxnHash":"9762458cd30612509f7cda589b7e1f7e59cb35d200eeb0a010ccc7b347057eb5",
		"TxnType":209,
		"TxnTime":1522207312,
		"Height":1212,
		"ConfirmFlag":1,
		"BlockIndex":1,
		"Fee":"0.010000000",
		"Description":"transfer",
		"Detail":{
		}
	}
}
```

| RequestField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    txnhash|   String|  transaction hash  |



| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    TxnHash|   String|    |
|    TxnType|   int|  |
|    TxnTime|   int|    |
|    Height|   int|    |
|    BlockIndex|   int|    |
|    Fee|   String |   |
|    ConfirmFlag|   int|   |
|    Description|   String|   |
|    Detail|   Object|  detail depends on Description |



**Detail：**


- Transfer Transaction

```json
successResponse：
{
	"Detail":{
		"TransferList": [
			{
				"Amount": "0.020000000",
				"FromAddress":"Aege6VvWEiKauFa2ngrtwdXt8FeGkWNPRH",
				"ToAddress":"ATUD7W6t6tLPGgd8H9tCN6Kwkb9WKFddch",
				"AssetName":"ont",
				"Description":"transfer"
			}
		]
	}
}
```


| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    TransferList.AssetName|   String|  |
|    TransferList.ToAddress|   String|  |
|    TransferList.FromAddress|   String|  |
|    TransferList.Amount|   String|  |
|    TransferList.Description|   String|  transfer|


- ontid transaction

```json
successResponse：
{
	"Detail":{
		"OntId":"did:ont:Ahctt129csbc612enxGTss6"
		"Description":"register OntId"
	}
}
```


| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    OntId|   String|  OntId|
|    Description|   String| |


