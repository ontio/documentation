
# 1. 获取通证信息

## 类型: oep4

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
		       "TotalSupply": 1000000000,
		       "Symbol": "MYT",
		       "Decimals": 8,
		       "Description": "30",
		       "Logo": "https://luckynumber.one/index/img/logo.png",
		       "ABI":"",
		       "Code": "013ec56b6a00527ac46a51527ac46a00c3046e616d659c640900658e076c7566616a00c30568656c6c6f9c6424006a51c3c0519e640700006c7566616a51c300c36a52527ac46a52c36551076c7566616a00.......",
		       "CreateTime":1516946305,
		       "UpdateTime":1516948340,
		       "ContactInfo":{
		           "email":"xx@onchain.com",
			   "twitter":"",
			   "github":""
			   ....
			   },
			"Addresscount": 1,
			"OntCount": "20.000000000",
			"OngCount": "2000.000000000"
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
| Addresscount|	int|	  |
| OntCount|	String|	  |
| OngCount|	String|	  |


## 类型: oep5

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
		       "ContractHash": "609cd49a9b15009ff2f3a1998f87b8212b8f6afb",
		       "Name": "name",
		       "Creator": "AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ",
		       "TxCount": 30,
		       "TotalSupply": 1000000000,
		       "Symbol": "MYT",
		       "Description": "30",
		       "Logo": "https://luckynumber.one/index/img/logo.png",
		       "ABI":"",
		       "Code": "013ec56b6a00527ac46a51527ac46a00c3046e616d659c640900658e076c7566616a00c30568656c6c6f9c6424006a51c3c0519e640700006c7566616a51c300c36a52527ac46a52c36551076c7566616a00.......",
		       "CreateTime":1516946305,
		       "UpdateTime":1516948340,
		       "ContactInfo":{
		           "email":"xx@onchain.com",
			   "twitter":"",
			   "github":""
			   ....
			   },
			"Addresscount": 1,
			"OntCount": "20.000000000",
			"OngCount": "2000.000000000"
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
| Creator|   String|    |
| ABI|   String|    |
| Code|   String|    |
| CreateTime	|	int|	  |
| UpdateTime|	int|	  |
| ContactInfo|	String|	  |
| Logo|	String|	  |
| Symbol|	String|	  |
| TotalSupply|	int|	  |
| Description|	String|	  |
| Addresscount|	int|	  |
| OntCount|	String|	  |
| OngCount|	String|	  |


## 类型: oep8

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
		       "ContractHash": "db80b875208f1f87b53c80a06a3288a1b2a0ea76",
		       "Name": "name",
		       "Creator": "AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ",
		       "TxCount": 30,
		       "TotalSupply": {
		           "01": "100002",
			   "02": "200000",
			   "03": "300000",
			   "04": "400000",
			   "05": "500000"
			},
		       "Symbol": {
		           "01": "TNF",
			   "02": "TNS",
			   "03": "TNH",
			   "04": "TNO",
			   "05": "TNI"
			},
			"TokenName": {
			    "01": "TokenNameFirst",
			    "02": "TokenNameSecond",
			    "03": "TokenNameThird",
			    "04": "TokenNameFourth",
			    "05": "TokenNameFifth"
			},
			"TokenId": {
			    "01": "01",
			    "02": "02",
			    "03": "03",
			    "04": "04",
			    "05": "05"
			},
		       "Description": "30",
		       "Logo": "https://luckynumber.one/index/img/logo.png",
		       "ABI":"",
		       "Code": "013ec56b6a00527ac46a51527ac46a00c3046e616d659c640900658e076c7566616a00c30568656c6c6f9c6424006a51c3c0519e640700006c7566616a51c300c36a52527ac46a52c36551076c7566616a00.......",
		       "CreateTime":1516946305,
		       "UpdateTime":1516948340,
		       "ContactInfo":{
		           "email":"xx@onchain.com",
			   "twitter":"",
			   "github":""
			   ....
			   },
			"Addresscount": 1,
			"OntCount": "20.000000000",
			"OngCount": "2000.000000000"
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
| Creator|   String|    |
| ABI|   String|    |
| Code|   String|    |
| CreateTime	|	int|	  |
| UpdateTime|	int|	  |
| ContactInfo|	String|	  |
| Logo|	String|	  |
| Symbol|	String|	  |
| TotalSupply|	String|	  |
| TokenName|	String|	  |
| TokenId|	String|	  |
| Description|	String|	  |
| Addresscount|	int|	  |
| OntCount|	String|	  |
| OngCount|	String|	  |



# 2. 获取通证合约详情

## 类型: oep4

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
	       "Description": "contractsDescription",
	       "CreateTime": "2018-11-27T02:07:59.000+0000",
	       "TotalSupply": 1000000000,
	       "Symbol": "TNT",
	       "Decimals": 8,
	       "ABI": "",
	       "TxnList": [
	           {
		       "TxnTime": 1543304445,
		       "TxnType": 209,
		       "ConfirmFlag": 1,
		       "Fee": "0.010000000",
		       "TxnHash": "c265aef457cb3b9012f09d5ad5fb834468241744254133e8a95290e9a6df31cd",
		       "Height": 3130
		    }
		],
		"Code": "",
		"Name": "TNT coin",
		"Logo": "https://luckynumber.one/index/img/logo.png",
		"UpdateTime": 1544084016,
		"ContactInfo": "",
		"OntCount": "20.000000000",
		"OngCount": "2000.000000000",
		"Addresscount": 11
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
| UpdateTime|   int|    |
| Description|   String|    |
| Symbol|   String|    |
| ABI|   String|    |
| Code|   String|    |
| Name|   String|    |
| Logo|   String|    |
| OngCount|   String|    |
| ContactInfo|   String|    |
| OntCount|   String|    |
| Addresscount|   int|    |
| TxnHash|   String|    |
| TxnType|   int|  |
| TxnTime|   int|    |
| Height|   int|    |
| ConfirmFlag	|	int|	  |
| Fee|	String|	  |


## 类型: oep5

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
	       "Description": "contractsDescription",
	       "CreateTime": "2018-11-27T02:07:59.000+0000",
	       "TotalSupply": 1000000000,
	       "Symbol": "HD",
	       "ABI": "",
	       "TxnList": [
	           {
		       "TxnTime": 1543304445,
		       "TxnType": 209,
		       "ConfirmFlag": 1,
		       "Fee": "0.010000000",
		       "TxnHash": "c265aef457cb3b9012f09d5ad5fb834468241744254133e8a95290e9a6df31cd",
		       "Height": 3130
		    }
		],
		"Code": "",
		"Name": "TNT coin",
		"Logo": "https://luckynumber.one/index/img/logo.png",
		"UpdateTime": 1544084016,
		"ContactInfo": "",
		"OntCount": "20.000000000",
		"OngCount": "2000.000000000",
		"Addresscount": 11
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
| UpdateTime|   int|    |
| Description|   String|    |
| Symbol|   String|    |
| ABI|   String|    |
| Code|   String|    |
| Name|   String|    |
| Logo|   String|    |
| OngCount|   String|    |
| ContactInfo|   String|    |
| OntCount|   String|    |
| Addresscount|   int|    |
| TxnHash|   String|    |
| TxnType|   int|  |
| TxnTime|   int|    |
| Height|   int|    |
| ConfirmFlag	|	int|	  |
| Fee|	String|	  |



## 类型: oep8（添加通证名字）

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
	       "Description": "contractsDescription",
	       "CreateTime": 1544411015,
	       "TotalSupply": {
	           "01": "100002",
		   "02": "200000",
		   "03": "300000",
		   "04": "400000",
		   "05": "500000"
		},
		"Symbol": {
		   "01": "TNF",
		   "02": "TNS",
		   "03": "TNH",
		   "04": "TNO",
		   "05": "TNI"
		},
		"TokenName": {
		   "01": "TokenNameFirst",
		   "02": "TokenNameSecond",
		   "03": "TokenNameThird",
		   "04": "TokenNameFourth",
		   "05": "TokenNameFifth"
		},
		"TokenId": {
		   "01": "01",
		   "02": "02",
		   "03": "03",
		   "04": "04",
		   "05": "05"
		},
	       "ABI": "",
	       "TxnList": [
	           {
		       "TxnTime": 1543304445,
		       "TxnType": 209,
		       "ConfirmFlag": 1,
		       "Fee": "0.010000000",
		       "TxnHash": "c265aef457cb3b9012f09d5ad5fb834468241744254133e8a95290e9a6df31cd",
		       "Height": 3130,
		       "TokenName": "TokenNameThird"
		    }
		],
		"Code": "",
		"Name": "TNT coin",
		"Logo": "https://luckynumber.one/index/img/logo.png",
		"UpdateTime": 1544084016,
		"ContactInfo": "",
		"OntCount": "20.000000000",
		"OngCount": "2000.000000000",
		"Addresscount": 11
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
| CreateTime|   int|    |
| UpdateTime|   int|    |
| Description|   String|    |
| TotalSupply|   String|    |
| Symbol|   String|    |
| TokenName|	String|	  |
| TokenId|	String|	  |
| ABI|   String|    |
| Code|   String|    |
| Name|   String|    |
| Logo|   String|    |
| ContactInfo|   String|    |
| Addresscount|   int|    |
| OngCount|   String|    |
| OntCount|   String|    |
| TxnHash|   String|    |
| TxnType|   int|  |
| TxnTime|   int|    |
| Height|   int|    |
| ConfirmFlag	|	int|	  |
| Fee|	String|	  |
| TokenName|	String|	  |





## 类型: oep8(添加通证名字)

	url：/api/v1/explorer/oepcontract/{type}/{contracthash}/{tokenname}/{pagesize}/{pagenumber}
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
	       "Description": "contractsDescription",
	       "CreateTime": 1544411015,
	       "TotalSupply": "100002",
	       "Symbol": "TNF",
	       "TokenName": "TokenNameFirst",
	       "TokenId": "01",
	       "ABI": "",
	       "TxnList": [
	           {
		       "TxnTime": 1543304445,
		       "TxnType": 209,
		       "ConfirmFlag": 1,
		       "Fee": "0.010000000",
		       "TxnHash": "c265aef457cb3b9012f09d5ad5fb834468241744254133e8a95290e9a6df31cd",
		       "Height": 3130,
		       "TokenName": "TokenNameFirst"
		    }
		],
		"Code": "",
		"Name": "TNT coin",
		"Logo": "https://luckynumber.one/index/img/logo.png",
		"UpdateTime": 1544084016,
		"ContactInfo": "",
		"OntCount": "20.000000000",
		"OngCount": "2000.000000000",
		"Addresscount": 11
	   }
	}


| RequestField|     Type |   Description   |
| :--------------: | :--------:| :------: |
| type|   String|  oep8  |
| tokenname|   String| TokenNameFirst  |
| contracthash|   String|    |
| pagesize|   int|    |
| pagenumber|   int|    |


| ResponseField     |     Type |   Description   |
| :--------------: | :--------:| :------: |
| Total|   int|    |
| Creator|   String|    |
| CreateTime|   int|    |
| UpdateTime|   int|    |
| Description|   String|    |
| TotalSupply|   String|    |
| Symbol|   String|    |
| TokenName|   String|    |
| TokenId|   String|    |
| ABI|   String|    |
| Code|   String|    |
| Name|   String|    |
| Logo|   String|    |
| ContactInfo|   String|    |
| Addresscount|   int|    |
| OngCount|   String|    |
| OntCount|   String|    |
| TxnHash|   String|    |
| TxnType|   int|  |
| TxnTime|   int|    |
| Height|   int|    |
| ConfirmFlag	|	int|	  |
| Fee|	String|	  |
| TokenName|	String|	  |
