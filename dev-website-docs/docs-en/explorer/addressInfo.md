 # Query Address Info


  url：/api/v1/explorer/address/queryaddressinfo/{address}

	method：GET

  	successResponse：
	{
	    "Action": "QueryAddressInfoForExcel",
	    "Error": 0,
	    "Desc": "SUCCESS",
	    "Version": "1.0",
	    "Result": {
           "TxnList": [
               {
                    "TxnTime": "2018-11-27 16:56:14",
                    "FromAddress": "AWiuedTEi9UVJkeAKEkwaescV29oFYSdg7",
                    "ConfirmFlag": 1,
                    "Fee": "0.0123155",
                    "Amount": "0.01",
                    "TxnHash": "e3c112d4de3c28e3b7efed16f4e95d96f19f7863c5c2286b5762ae508afc2432",
                    "AssetName": "TNT",
                    "ToAddress": "AHdVYY3oCPho1JmwYYmaPYUTXLsZXMAYL3"
            },
            .......
           ]
      }
	}

| ResponseField     |     Type |   Description   |
| :--------------: | :--------:| :------: |
| TxnTime|   int|    |
| FromAddress|   String|  |
| ConfirmFlag|   int|    |
| Fee|   String|    |
| Amount|	String|	  |
| TxnHash|	String|	  |
| AssetName|	String|	  |
| ToAddress|	String|	  |
