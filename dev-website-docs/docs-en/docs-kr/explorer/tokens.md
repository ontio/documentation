
# Get Token Contract

	url：/api/v1/explorer/oepcontract/{type}/{pagesize}/{pagenumber}
	method：GET
	successResponse：
	{
	   "Action": "QueryOEPContract",
	   "Error": 0,
	   "Desc": "SUCCESS",
	   "Version": "1.0",
	   "Result": {
	       "Total": 7,
	       "ContractList": [
	           {
		       "ContractHash": "16edbe366d1337eb510c2ff61099424c94aeef02",
		       "Name": "name",
		       "Creator": "AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ",
		       "TxCount": 30,
		       "OntCount"："10",
		       "OngCount": "10.98",
		       "TotalSupply": 1000000000,
		       "Symbol": "MYT",
		       "Decimals": 8,
		       "Description": "30",
		       "Logo": "",
		       "ABI":"",
		       "Code": "013ec56b6a00527ac46a51527ac46a00c3046e616d659c640900658e076c7566616a00c30568656c6c6f9c6424006a51c3c0519e640700006c7566616a51c300c36a52527ac46a52c36551076c7566616a00.......",
		       "CreateTime":1516946305,
		       "UpdateTime":1516948340,
		       "ContactInfo":{
		           "email":"xx@onchain.com",
			   "twitter":"",
			   "github":""
			   ....
			   }
			}
		   ]
		}
	}



| RequestField|     Type |   Description   | 
| :--------------: | :--------:| :------: |
| type|   String|  oep4 or oep8  |
| pagesize|   int|    |
| pagenumber|   int|    |



| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
| Total|   int|    |
| ContractHash|   String|    |
| Name|   String|  |
| TxCount|   int|    |
| OntCount|   String|    |
| OngCount|   String|    |
| Creator|   String|    |
| ABI|   String|    |
| Code|   String|    |
| CreateTime	|	int|	  |
| UpdateTime|	int|	  |
| ContactInfo|	String|	  |
| Logo|	String|	  |
| Symbol|	String|	  |
| TotalSupply|	int|	  |
| Decimals|	int|	  |
| Description|	String|	  |




# Get Token Contract Detail

	url：/api/v1/explorer/oepcontract/{type}/{contracthash}/{pagesize}/{pagenumber}
	method：GET
	successResponse：
	{
	   "Action": "QueryOEPContractByHash",
	   "Error": 0,
	   "Desc": "SUCCESS",
	   "Version": "1.0",
	   "Result": {
	       "Total": 7,
	       "Creator": "AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ",
	       "CreateTime": "2018-11-27T02:07:59.000+0000",
	       "TotalSupply": 1000000000,
	       "Decimals": 8,
	       "ContractList": [
	           {
		       "TxnTime": 1543304445,
		       "TxnType": 209,
		       "ConfirmFlag": 1,
		       "Fee": "0.010000000",
		       "TxnHash": "c265aef457cb3b9012f09d5ad5fb834468241744254133e8a95290e9a6df31cd",
		       "Height": 3130
		    }
		]
	   }
	}


| RequestField|     Type |   Description   | 
| :--------------: | :--------:| :------: |
| type|   String|  oep4 or oep8  |
| contracthash|   String|    |
| pagesize|   int|    |
| pagenumber|   int|    |


| ResponseField     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
| Total|   int|    |
| Creator|   String|    |
| CreateTime|   String|    |
| TotalSupply|   int|    |
| Decimals|   int|    |
| TxnHash|   String|    |
| TxnType|   int|  |
| TxnTime|   int|    |
| Height|   int|    |
| ConfirmFlag	|	int|	  |
| Fee|	String|	  |
