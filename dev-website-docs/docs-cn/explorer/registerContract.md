

## 1. 类型: 默认，OEP4 或 OEP5

	url：/api/v1/explorer/contract/registerContractInfo

```json
method：POST
input：
{
    "code": "6a55c36a54c3936a00527ac462c8ff6161616a53c36c7566",
    "abi": " {\"contractHash\": \"2a9cc8a5d0644283e7d7705abe5bbcb979c9bb03\"}",
    "name": "oep4Test",
    "project": "oep4Project",
    "contractHash": "2a9cc8a5d0644283e7d7705abe5bbcb979c9bb03",
    "type": "OEP4",
    "contactinfo": {
        "Website": "https://github.com/ontio"
    },
    "description": "contractsDescriptionTest",
    "logo": "https://luckynumber.one/index/img/logo.png"
   }

successResponse：
{
    "Action": "RegisterContractInfo",
    "Error": 0,
    "Desc": "SUCCESS",
    "Version": "1.0",
    "Result": true
}
```

| ResponseField     |     Type |   Description   |
| :--------------: | :--------:| :------: |
| contractHash|   String|    |
| name|   String|  |
| project|   String|  |
| abi|   String|    |
| code|   String|    |
| contactinfo|	String|	  |
| logo|	String|	  |
| description|	String|	  |
| type|	String|	  |



## 2. 类型: OEP8

	url：/api/v1/explorer/contract/registerContractInfo
```json
method：POST
input：
{
    "code": "6a55c36a54c3936a00527ac462c8ff6161616a53c36c7566",
    "abi": " {\"contractHash\": \"2a9cc8a5d0644283e7d7705abe5bbcb979c9bb03\"}",
    "name": "oep8Test",
    "project": "oep8Project",
    "contractHash": "2a9cc8a5d0644283e7d7705abe5bbcb979c9bb03",
    "type": "OEP8",
    "contactinfo": {
        "Website": "https://github.com/ontio"
    },
    "description": "contractsDescriptionTest",
    "logo": "https://luckynumber.one/index/img/logo.png",
    "tokenId": "01,02,03,04,05"
    }

successResponse：	
{
    "Action": "RegisterContractInfo",
    "Error": 0,
    "Desc": "SUCCESS",
    "Version": "1.0",
    "Result": true
}

```

| ResponseField     |     Type |   Description   |
| :--------------: | :--------:| :------: |
| contractHash|   String|    |
| name|   String|  |
| project|   String|  |
| abi|   String|    |
| code|   String|    |
| contactinfo|	String|	  |
| logo|	String|	  |
| description|	String|	  |
| type|	String|	  |
| tokenId|	String|	  |
