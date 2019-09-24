# Marketplace - RESTful api

* 1. [RESTful api](#RESTful api)
	* 1.1. [上架](#上架)
	* 1.2. [购买](#购买)
	* 1.3. [确认](#确认)
	* 1.4. [申诉](#申诉)
	* 1.5. [仲裁](#仲裁)
	* 1.6. [查询交易结果及返回的参数](#查询交易结果及返回的参数)
	

## RESTful api

###  上架
```
url：/api/v1/order/auth
method：POST
```

请求：

```json
{
	"dataId": "did:ont:ANYEUuWmPFrHM8XPYLJf2Z1PGAKSyBJ2G9",
	"symbol": "symbol",
	"name": "name",
	"amount": 100,
	"price": 10,
	"transferCount": 10,
	"accessCount": 10,
	"expireTime": 0,
	"makerReceiveAddress": "ARCESVnP8Lbf6S7FuTei3smA35EQYog4LR",
	"mpReceiveAddress": "AR9NDnK3iMSZodbENnt7eX5TJ2s27fnHra",
	"OJList": ["AR9NDnK3iMSZodbENnt7eX5TJ2s27fnHra"]
}
```

| Field Name | Type | Description |
|---|---|---|
|dataId|String|为数据生成的dataId|
|symbol|String|token的symbol|
|name|String|token的name|
|amount|int|授权生成token的数量|
|price|String|单价|
|transferCount|int|token的可流转次数|
|accessCount|int|token的可访问次数|
|expireTime|int|token的过期时间，0为永久有效|
|makerReceiveAddress|String|卖家收款地址|
|mpReceiveAddress|String|平台收款地址|
|ojList|List|仲裁者列表|

响应：

```json
{
	"action": "authOrder",
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
| result | Obj | 授权订单的交易hex，将result内容生成二维码，并让ONT Auth扫码|
| version   | String | 版本号                        |


###  购买
```
url：/api/v1/order/take
method：POST
```

请求：

```json
{
	"authId": "b1f929778f7aaa9aed007e61eda05253dc0fef1c",
	"takerReceiveAddress": "AMZvjuJNxD21uVgJ5c8VDdGUiT4TudtLFU",
	"tokenAmount": 1,
    "oj": "AJYEUcQi9jp157QXNWpKybwkCVSTuTNsh1"
}
```

| Field Name | Type | Description |
|---|---|---|
|authId|String|authOrder操作后在链上生成的id|
|takerReceiveAddress|String|买家付款及收取token地址|
|tokenAmount|int|购买的token数量|
|oj|String|选取的仲裁方|


响应：

```json
{
	"action": "takeOrder",
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
| result | Obj | 下单的交易hex，将result内容生成二维码，并让ONT Auth扫码|
| version   | String | 版本号                        |


###  确认
```
url：/api/v1/order/confirm
method：POST
```

请求：

```json
{
	"orderId": "2d8042e7d50a3e012ad3231a90f06b8615318319"
}
```

| Field Name | Type | Description |
|---|---|---|
|orderId|String|takeOrder操作后在链上生成的id|


响应：

```json
{
	"action": "confirm",
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
| result | Obj | 确认订单的交易hex，将result内容生成二维码，并让ONT Auth扫码|
| version   | String | 版本号                        |


###  申诉
```
url：/api/v1/order/apply
method：POST
```

请求：

```json
{
	"orderId": "2d8042e7d50a3e012ad3231a90f06b8615318319"
}
```

| Field Name | Type | Description |
|---|---|---|
|orderId|String|takeOrder操作后在链上生成的id|


响应：

```json
{
	"action": "apply",
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
| result | Obj | 申诉的交易hex，将result内容生成二维码，并让ONT Auth扫码|
| version   | String | 版本号                        |


###  仲裁
```
url：/api/v1/order/arbitrage
method：POST
```

请求：

```json
{
	"orderId": "2d8042e7d50a3e012ad3231a90f06b8615318319",
	"isWin": true,
	"makerReceiveAmount": 50000000,
	"takerReceiveAmount": 1150000000
}
```

| Field Name | Type | Description |
|---|---|---|
|orderId|String|takeOrder操作后在链上生成的id|
|isWin|boolean|仲裁判断结果，true为买家赢，false为卖家赢|
|makerReceiveAmount|long|卖家收款金额|
|takerReceiveAmount|long|买家收款金额|


响应：

```json
{
	"action": "arbitrage",
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
| result | Obj | 仲裁的交易hex，将result内容生成二维码，并让ONT Auth扫码|
| version   | String | 版本号                        |


###  查询交易结果及返回的参数

```
url：/api/v1/order/result/{id}
method：Get
```

请求：
| Field Name | Type | Description |
|---|---|---|
|id          |String|调用`上架`，`购买等`交易接口，返回result中的id     |

响应：

```json
{
    "action": "actionResult",
    "error": 0,
    "desc": "SUCCESS",
    "result": {
        "result": "1",
        "authId": "b1f929778f7aaa9aed007e61eda05253dc0fef1c",
        "orderId": "2d8042e7d50a3e012ad3231a90f06b8615318319",
        "tokenId": [1,10]
    },
    "version": "v1"
}
```
| Field Name | Type | Description |
| :-- | :-- | :-- |
| action    | String | 动作标志                      |
| error     | int    | 错误码                        |
| desc      | String | 成功为SUCCESS，失败为错误描述 |
| result    | String | 成功返回"1"，失败返回"0",没有查到链上信息返回null|
| authId    | String | 上架后生成的授权id（只有调用上架接口才会返回）              |
| orderId   | String | 购买后生成的订单id（只有调用购买接口才会返回）              |
| tokenId   | List   | 购买后生成的tokenId（只有调用购买接口才会返回）,第一个元素表示起始token，第二个元素表示结束token |
| version   | String | 版本号                        |