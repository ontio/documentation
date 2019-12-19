

## 3.ONT ID APIs

#### ONT ID description

|              Value               |  Type  |   Description    |
| :------------------------------: | :----: | :--------------: |
|          register OntId          | String |  register OntId  |
|       add publicKey:xxxxx        | String |  add publicKey   |
|      remove publicKey:xxxxx      | String | remove publicKey |
|   add attribute:value1&value2    | String |  add attribute   |
|      update attribute:xxxx       | String | update attribute |
|      remove attribute:xxxx       | String | remove attribute |
|       change recovery:xxxx       | String | change recovery  |
|        add recovery:xxxx         | String |   add recovery   |
| create new claim: claimId:xxxxxx | String |   create claim   |

#### DDO Attribute

| Key         | Value        | Type   | Description           |
| ----------- | ------------ | ------ | --------------------- |
| Claim       | ContextDesc  | String | description           |
|             | ClaimContext | String | claim context         |
|             | IssuerOntId  | String | ONT ID of the issuer  |
|             | ClaimId      | String | hash of the claim     |
| SelfDefined | value        | String | user defined DDO info |



### 3.1 Get latest ONT ID  list

```java
url：/v2/latest-ontids?count=10, 
method：GET, 
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":[
        {
            "ontid":"did:ont:TA7aqop3BcYJpHtEEyfg1ucausfDETyTQA", 
            "description":"register OntId", 
            "tx_hash":"9762458cd30612509f7c...a010ccc7b347057eb5", 
            "tx_type":209, 
            "tx_time":1522210288, 
            "block_height":1212, 
            "fee":"0.01"
        }
    ]
}

```

| Url RequestField | Type | Description                          |
| ---------------- | ---- | ------------------------------------ |
| count            | int  | number of latest ontids (limited between 1 and 50) |



| ResponseField |  Type  |                  Description                  |
| :-----------: | :----: | :-------------------------------------------: |
|     ontid     | String |                    ONT ID                     |
|    tx_hash    | String |               transaction hash                |
| block_height  |  int   |                 block height                  |
|    tx_time    |  int   |         UNIX time of the transaction          |
|  description  | String | transaction description for given **ONT ID** |
|    tx_type    |  int   |                      209                      |
|      fee      | String |                      fee                      |



### 3.2 Get  ONT ID  list by page

```java
url：/v2/ontids?page_size=10&page_number=1, 
method：GET, 
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":{
    	"records":[
            {
                "ontid":"did:ont:TA7aqop3BcYJpHtEEyfg1ucausfDETyTQA", 
                "description":"register OntId", 
                "tx_hash":"9762458cd30612509f7c...a010ccc7b347057eb5", 
                "tx_type":209, 
                "tx_time":1522210288, 
                "block_height":1212, 
                "fee":"0.01"
            }
    	], 
    	"total":100
    }
}

```

| Url RequestField | Type | Description                                     |
| ---------------- | ---- | ----------------------------------------------- |
| page_size        | int  | number of records in one page (The page size is limited between 1 and 20) |
| page_number      | int  | number of the page (At least 1 or greater)              |



| ResponseField |  Type  |                  Description                  |
| :-----------: | :----: | :-------------------------------------------: |
|     total     |  int   |                 total ONT ID                  |
|     ontid     | String |                    ONT ID                     |
|    tx_hash    | String |               transaction hash                |
| block_height  |  int   |                 block height                  |
|    tx_time    |  int   |         UNIX time of the transaction          |
|  description  | String | transaction description for given **ONT ID** |
|    tx_type    |  int   |                      209                      |
|      fee      | String |                      fee                      |



### 3.3 Get ONT ID transaction list by page

```java
url：/v2/ontids/{ontid}/transactions?page_size=10&page_number=1, 
method：GET, 
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":{
		"records":[
			{
				"tx_hash":"df272d8bf471ed...669fadc996f1b3f", 
				"block_height":123, 
				"tx_type": 209, 
				"tx_time":1522213966, 
				"description":"add attribute:claim", 
				"fee":"0.01", 
				"ontid": "did:ont:TA96Nqm9HRFKzudLjgH16Zfvdw3ixq8UGZ"
			}
		], 
		"total":10
    }
}

```

| RequestField |  Type  |                   Description                   |
| :----------: | :----: | :---------------------------------------------: |
|    ontid     | String |                     ONT ID                      |
|  page_size   |  int   | number of records in one page (The page size is limited between 1 and 20) |
| page_number  |  int   |       number of the page (At least 1 or greater)        |

| ResponseField |  Type  |                 Description                  |
| :-----------: | :----: | :------------------------------------------: |
|    tx_hash    | String |               transaction hash               |
| block_height  |  int   |                 block height                 |
|    tx_type    |  int   |                     209                      |
|      fee      | String |                     fee                      |
|     ontid     | String |                    ONT ID                    |
|    tx_time    |  int   |         UNIX time of the transaction         |
|  description  | String | transaction description for given **ONT ID** |
|     total     |  int   |       total transactions of the ONT ID       |

### 3.3 Get ONT ID ddo

```java
url：/v2/ontids/{ontid}/ddo, 
method：GET, 
successResponse：{
    "code":0, 
    "msg":"SUCCESS", 
    "result":{
        "Attributes":[
            {
                "Claim":{
                    "ClaimId":"111ab2f56d106da...8fa65a9996b03ba0", 
                    "ClaimContext":"claim:github_authentication", 
                    "ContextDesc":"my github claim", 
                    "IssuerOntId":"did:ont:TKhyXw8o...sy4p6fYZPB"
                }
            }
        ], 
        "OntId":"did:ont:TA7aqop3B...ausfDETyTQA", 
        "Owners":[
            {
                "Type": "ECDSA", 
                "Curve": "P-256", 
                "Value": "120203cef1f2ff7...4031dcdf5c5772e449", 
                "PublicKeyId": "did:ont:TA96Nq...vdw3ixq8UGZ#keys-1"
            }
        ]
    }
}

```

| RequestField |  Type  | Description |
| :----------: | :----: | :---------: |
|    ontid     | String |   ONT ID    |

| ResponseField |  Type  |       Description       |
| :-----------: | :----: | :---------------------: |
|  Attributes   |  list  | Attribute of the ONT ID |
|     OntId     | String |         ONT ID          |
|  Owners.Type  | String |          ECDSA          |
| Owners.Curve  | String |          P-256          |
| Owners.Value  | String | publickey in HEX string |

