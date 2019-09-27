# Data Storage Service Provider - RESTful api

* 1. [RESTful api](#RESTful api)
	* 1.1. [注册dataId](#注册dataId)
	* 1.2. [ONT Auth发送注册dataId交易](#ONT Auth发送注册dataId交易)
	* 1.3. [查询注册的dataId及结果](#查询注册的dataId及结果)

	**以下接口eshop类型场景适用**
	* 1.4. [生成tokenId](#生成tokenId)
	* 1.5. [ONT Auth发送生成tokenId交易](#ONT Auth发送生成tokenId交易)
	* 1.6. [查询生成的tokenId及结果](#查询生成的tokenId及结果)
	

## RESTful api

###  注册dataId

```
url：/api/v1/data/dataId
method：POST
```

请求：

```json
{
	"ontid": "did:ont:ARCESVnP8Lbf6S7FuTei3smA35EQYog4LR"
}
```

| Field Name | Type | Description |
|---|---|---|
|ontid|String|用户ontid|

响应：

```json
{
	"action": "createDataId",
	"error": 0,
	"desc": "SUCCESS",
	"result": {
		"action": "signMessage",
		"version": "v1.0.0",
		"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
		"params": {
			"type": "ontid",
			"message": "7d7c4f01e0fa3c3203424644697b8d2266f337fb25b3ae89bc9575194a5d5ce7",
			"ishex": true,
			"callback": "http://101.132.193.149:4027/api/v1/data/invoke"
		}
	},
	"version": "v1"
}
```

| Field Name | Type | Description |
| :-- | :-- | :-- |
| action | String | 动作标志 |
| error | int | 错误码 |
| desc | String | 成功为SUCCESS，失败为错误描述 |
| result | Obj | 注册dataId的交易hex，将result内容生成二维码，并让ONT Auth扫码|
| version   | String | 版本号                        |


###  ONT Auth发送注册dataId交易

```
url：/back/invoke
method：Post
```
请求
````json
{
	"action": "signMessage",
	"id": "string",
	"params": {
		"type": "ontid",
		"user": "did:ont:AUEKhXNsoAT27HJwwqFGbpRy8QLHUMBMPz",
		"message": "7d7c4f01e0fa3c3203424644697b8d2266f337fb25b3ae89bc9575194a5d5ce7",
		"publickey": "0205c8fff4b1d21f4b2ec3b48cf88004e38402933d7e914b2a0eda0de15e73ba61",
		"signature": "01abd7ea9d79c857cd838cabbbaad3efb44a6fc4f5a5ef52ea8461d6c055b8a7cf324d1a58962988709705cefe40df5b26e88af3ca387ec5036ec7f5e6640a1754"
	},
	"version": "v1"
}
````
| Field Name | Type | Description |
|---|---|---|
|message|String|签名的内容|
|publickey|String|ontid公钥|
|signature|String|签名数据|

响应：

```json
{
	"action": "createDataId",
	"error": 0,
	"desc": "SUCCESS",
	"result": "SUCCESS",
	"version": "v1"
}
```

| Field Name | Type | Description |
| :-- | :-- | :-- |
| action | String | 动作标志 |
| error | int | 错误码 |
| desc | String | 成功为SUCCESS，失败为错误描述 |
| result | Obj | 返回结果，失败为""|
| version   | String | 版本号                        |


###  查询注册的dataId及结果

```
url：/back/result/{id}
method：Get
```

请求：
| Field Name | Type | Description |
|---|---|---|
|id          |String|注册dataId返回的记录id     |

响应：

```json
{
    "action": "registerDataIdResult",
    "error": 0,
    "desc": "SUCCESS",
    "result": {
        "dataId": "did:ont:ANYEUuWmPFrHM8XPYLJf2Z1PGAKSyBJ2G9",
        "result": "1"
    },
    "version": "v1"
}
```
| Field Name | Type | Description |
| :-- | :-- | :-- |
| action    | String | 动作标志                      |
| error     | int    | 错误码                        |
| desc      | String | 成功为SUCCESS，失败为错误描述 |
| dataId    | String | 注册生成的dataId              |
| result    | String | 成功返回"1"，失败返回"0",没有查到链上信息返回null|
| version   | String | 版本号                        |


**以下接口eshop类型场景适用**
###  生成tokenId

```
url：/api/v1/data/tokenId/register
method：POST
```

请求：

```json
{
	"address": "ARCESVnP8Lbf6S7FuTei3smA35EQYog4LR",
	"dataId": "did:ont:ANYEUuWmPFrHM8XPYLJf2Z1PGAKSyBJ2G9",
	"ontid": "did:ont:ARCESVnP8Lbf6S7FuTei3smA35EQYog4LR",
	"index": 1,
	"symbol": "symbol",
	"name": "name",
	"amount": 100,
	"transferCount": 10,
	"accessCount": 10,
	"expireTime": 0
}
```

| Field Name | Type | Description |
|---|---|---|
|address|String|生成data token的接收地址|
|dataId|String|已注册的dataId|
|ontid|String|dataId的控制人ONT ID|
|index|int|控制人ONT ID index|
|symbol|String|token的symbol|
|name|String|token的name|
|amount|int|生成token的数量|
|transferCount|int|token的可流转次数|
|accessCount|int|token的可访问次数|
|expireTime|int|token的过期时间|

响应：

```json
{
	"action": "createTokenId",
	"error": 0,
	"desc": "SUCCESS",
	"result": {
		"action": "signMessage",
		"version": "v1.0.0",
		"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
		"params": {
			"type": "ontid",
			"message": "7d7c4f01e0fa3c3203424644697b8d2266f337fb25b3ae89bc9575194a5d5ce7",
			"ishex": true,
			"callback": "http://101.132.193.149:4027/api/v1/data/invoke"
		}
	},
	"version": "v1"
}
```

| Field Name | Type | Description |
| :-- | :-- | :-- |
| action | String | 动作标志 |
| error | int | 错误码 |
| desc | String | 成功为SUCCESS，失败为错误描述 |
| result | Obj | 生成dataToken的交易hex，将result内容生成二维码，并让ONT Auth扫码|
| version   | String | 版本号                        |


###  ONT Auth发送生成tokenId交易

```
url：/back/invoke
method：Post
```
请求
````json
{
	"action": "signMessage",
	"id": "string",
	"params": {
		"type": "ontid",
		"user": "did:ont:AUEKhXNsoAT27HJwwqFGbpRy8QLHUMBMPz",
		"message": "7d7c4f01e0fa3c3203424644697b8d2266f337fb25b3ae89bc9575194a5d5ce7",
		"publickey": "0205c8fff4b1d21f4b2ec3b48cf88004e38402933d7e914b2a0eda0de15e73ba61",
		"signature": "01abd7ea9d79c857cd838cabbbaad3efb44a6fc4f5a5ef52ea8461d6c055b8a7cf324d1a58962988709705cefe40df5b26e88af3ca387ec5036ec7f5e6640a1754"
	},
	"version": "v1"
}
````
| Field Name | Type | Description |
|---|---|---|
|message|String|签名的内容|
|publickey|String|ontid公钥|
|signature|String|签名数据|

响应：

```json
{
	"action": "createTokenId",
	"error": 0,
	"desc": "SUCCESS",
	"result": "SUCCESS",
	"version": "v1"
}
```

| Field Name | Type | Description |
| :-- | :-- | :-- |
| action | String | 动作标志 |
| error | int | 错误码 |
| desc | String | 成功为SUCCESS，失败为错误描述 |
| result | Obj | 返回结果，失败为""|
| version   | String | 版本号                        |


###  查询生成的tokenId及结果

```
url：/back/result/{id}
method：Get
```

请求：
| Field Name | Type | Description |
|---|---|---|
|id          |String|生成tokenId返回的记录id     |

响应：

```json
{
    "action": "createTokenIdResult",
    "error": 0,
    "desc": "SUCCESS",
    "result": {
        "tokenId": [1,50],
        "result": "1"
    },
    "version": "v1"
}
```
| Field Name | Type | Description |
| :-- | :-- | :-- |
| action    | String | 动作标志                      |
| error     | int    | 错误码                        |
| desc      | String | 成功为SUCCESS，失败为错误描述 |
| tokenId   | List   | 生成的tokenId,第一个元素表示起始id，第二个元素表示结束id|
| result    | String | 成功返回"1"，失败返回"0",没有查到链上信息返回null|
| version   | String | 版本号                        |