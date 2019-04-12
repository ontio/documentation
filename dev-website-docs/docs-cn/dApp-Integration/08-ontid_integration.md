
# ONT ID 开放平台 接入说明

ONT ID 开放平台为第三方应用提供第三方登录、支付、智能合约执行、KYC等服务，请按照以下步骤开始应用集成。


## 准备工作


在进行 ONTID 授权登录接入之前，应用方需要先在 ONTID 开放平台注册 ONTID ，获得相应的 ONTID 和 ```PrivateKey```，申请 ONTID 通过审核后，可开始接入流程。

对接前请确保登录和支付页面能正常访问：

* ONTID 登录页面： 主网 [https://signin.ont.io/#/](https://signin.ont.io/#/)，测试网 [http://139.219.136.188:10390/](http://139.219.136.188:10390/)

* ONTID 支付页面：主网  [https://pay.ont.io/#/](https://pay.ont.io/#/)，测试网  [http://139.219.136.188:10390/transaction](http://139.219.136.188:10390/transaction)




## 快速对接


应用方对接包括前端对接和服务器对接。前端对接主要是对接登录和支付页面，后台对接主要是对接发起订单请求和订单查询。


* 第三方应用前端演示： [http://139.219.136.188:10391/#/](http://139.219.136.188:10391/#/)，[源码](https://github.com/ontio-ontid/ontid-app-demo)
* 第三方应用服务器例子： [app-server 源码](https://github.com/ontio-ontid/ontid-app-server)

### 前端对接登录页面
 
 
 ```
 http://139.219.136.188:10390/signin?params={value}
 value = window.encodeURIComponent(appontid + '&' + appname + '&' + lang)
```
 

 ```lang``` 是可选的参数默认是en，en表示英文，zh表示中文。
 ```appontid``` 是应用方的 ontid。
 ```appname``` 是应用方的 名字。

> 用户登录成功后，应用方得到 ```access_token```可以查询用户的信息，应用方需要保存用户的资产地址信息，支付时候需要使用

### 应用方服务器发起支付订单请求

应用方发起请求中含有``` app_token``` 和``` user```，``` app_token``` 里的 ``` Payload``` 需要包含应用方信息和调用合约参数，``` user```是用户的 ontid。



```
url：/api/v1/ontid/request/order

method：POST

{
   "app_token" :  "JWT token: Base64(Header).Base64(Payload).Base64(Signature)",
   "user": "did:ont:AcrgWfbSPxMR1BNxtenRCCGpspamMWhLuL"
}
```

请求数据中```Payload```的应用方信息和调用合约参数填写例子： 

```

{
	"invokeConfig": {
		"contractHash": "0100000000000000000000000000000000000000", // ONG: 0200000000000000000000000000000000000000
		"functions": [{
			"operation": "transfer",
			"args": [{
					"name": "arg0-from",
					"value": "Address:AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ"   //用户资产地址
				}, {
					"name": "arg1-to",
					"value": "Address:AecaeSEBkt5GcBCxwz1F41TvdjX3dnKBkJ"   //应用方收款地址
				},
				{
					"name": "arg2-amount",
					"value": 10000
				}
			]
		}],
		"payer": "AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ",    //用户资产地址，用于付手续费
		"gasLimit": 20000,  //根据合约复杂度填写，预执行可以查询该值，最小是20000
		"gasPrice": 500    //固定值
	},
	"app": {
        "name": "", // String，必填项，应用方名称
        "logo":"", // String，可选项，应用方logo的url。
        "message": "", // String，必填项，用于页面上显示支付/调用合约的目的，不能超过30个字符
        "ontid": "", // String，必填项，应用方的ONT ID
        "callback":"",// String，可选项，交易成功后通知应用方
        "nonce": "123456" // String，不能重复
    }
}

```

应用方服务器可以通过``` callback ```确认用户支付成功，也可以通过合约 hash 到[链上查询合约事件](https://dev-docs.ont.io/#/docs-cn/ontology-cli/06-restful-specification?id=getsmtcode_evts)。



### 前端对接支付页面

```  
  http://139.219.136.188:10390/transaction?params={value}
  value = window.encodeURIComponent(orderid + & + invoke_token + & + callback_url + & + lang)
  
```

 ```lang``` 是可选的参数默认是en，en表示英文，zh表示中文。
 ```invoke_token``` 是应用方服务器发起支付订单请求，开发平台返回的 invoke_token。
 ```orderid``` 是应用方服务器发起支付订单请求，开发平台返回的 orderid。
 ```callback_url``` 是应用方的前端页面。

> 支付成功后，应用方前端会收到交易 hash ，服务器需要保存交易 hash，通过交易 hash 可以查询交易状态或到[链上查询合约事件](https://dev-docs.ont.io/#/docs-cn/ontology-cli/06-restful-specification?id=getsmtcode_evts)。



### 应用方服务器查询订单


 ```app_token``` 是应用方签发的，里面包含应用方 ontid 和签名，类似与支付请求，Payload 里的字段：

 ```text
 {
     "app": {
         "ontid": ""
      }
     "exp":1555041974000
 }
 ```
 
根据订单号查询
```
url： /api/v1/provider/query/order

method：POST

{
    "app_token" :  "JWT token: Base64(Header).Base64(Payload).Base64(Signature)",
    "orderId":"a24d06ec89c3ce0c845eb719697d7843464f287e19a8c7e3d3ef614378e610b2"
}
```

查询订单历史记录
```
url： /api/v1/provider/query/order/range

method：POST

{
    "app_token" :  "JWT token: Base64(Header).Base64(Payload).Base64(Signature)",
    "currentPage": 1,
    "size":10
}

```

> ```app_token``` 是应用方签发的，里面包含应用方 ontid 和签名，类似与支付请求。

### 智能合约

如果应用方需要统计交易量，可以把 ONT/ONG 转账封装在合约里，请参考智能合约模板[native_asset_invoke_compiler2.0](https://github.com/ONT-Avocados/python-template/blob/master/NativeAssetInvoke/native_asset_invoke_compiler2.0.py)。

## 第三方登录对接


ONTID 授权登录是让用户使用 ONTID 身份安全登录第三方应用或网站，在 ONTID 用户授权登录已接入 ONTID 的第三方应用后，第三方可以获取到用户的接口调用凭证（```access_token```），通过 ```access_token``` 可以进行 ONTID 相关接口调用。

ONTID 授权登录模式整体流程为：


![ontid login](https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/ontid-login.png) 


1. 应用方前台打开新窗口加载 ONTID 的登录页面。
2. 用户在 ONTID 的登录页面输入用户名密码登录。
3. ONTID 开发平台返回 ```access_token``` 和 ```refresh_token``` 的 ```JWT token```。
4. ONTID 开放平台前端关闭登录页面，返回```JWT token```给应用的前端。
5. 应用方前端发送 ```JWT token``` 给应用的后台。 
6. 应用方的后台验证 ```JWT token``` 的颁发者成功后，获取 ```refresh_token``` 中用户信息，一般为非敏感的信息，如用户用户 ONTID，手机号。
7. 请求头部携带着```access_token```去访问 ONTID 开放平台接口。

第三步返回的 ```JWT token``` 的数据采用应用方公钥加密，解密后的数据格式为：

```
 {
    "access_token" :  "JWT token",
    "refresh_token" : "JWT token"
 }
```

>  ```JWT token``` 的值里的Payload需要增加 ```content```字段：

```
 
   "content": {
       "type": "refresh_token", // or access_token
       "phone": "+86*1234567890",
       "ontid": "did:ont:Axxxxxxxxxxxxxxxxx",
       ......
   }
   
```

| Param     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    access_token |   String | ```JWT token```，用户访问接口时 ```Header``` 需要填写 ```access_token``` |
|    refresh_token |   String | ```JWT token```，刷新 ```access_token``` 时使用 |

 



### 如何集成ONT ID登录


1. 页面引入```OntidSignIn.js```
2. 页面添加 meta 标签，填写应用方的ONT ID。```<meta name="ontid-signin-client_ontid" content="YOUR_CLIENT_ONTID.apps.ontid.com">```
3. 页面添加 ONTID 的Sign In 按钮。``` <div class="ontid-signin" data-onsuccess="onSignIn"></div> ```
4. 在登录成功后，触发回调onSignIn,发送 ```JWT token``` 到应用方后台。

```
    // 获取JWT token
    function onSignIn(googleUser) {
      var token = ontidUser.getAuthResponse().token;
      ...
    }
    //页面发送JWT token到应用方后台
    var xhr = new XMLHttpRequest();
    xhr.open('POST', 'https://yourbackend.example.com/tokensignin');
    xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
    xhr.onload = function() {
      console.log('Signed in as: ' + xhr.responseText);
    };
    xhr.send('idtoken=' + id_token);
```
5. 应用方后台验证 ``` JWT token ```





### 应用方查询用户 ontid 账户信息

使用前需先登录 ONTID ，有``` access_token ```才能调用查询接口，应用方需要保存用户的 ONTID 和对应的资产地址，支付功能需要使用用户的资产地址。

```
url：/api/v1/ontid/info

headers.set("access_token", token);
method：POST

{
}
```

| Field_Name|     Type |   Description   |
| :--------------: | :--------:| :------: |
|    ontid|   String|  ontid  |

返回：

```
{
	"wallet": [{
		"address": "ASm1sUJQDCgNzfjd9FuA5JGLBJLeXiQd1W",
		"ont": 0,
		"ong": 949999500
	}],
	"phone": "86*15821703553",
	"publicKey": "032f70df4ab7baf182c779ca7ab6b5b92e349170b2c3a76df3a6bda66ca627ff61"
}
```

| Field_Name|     Type |   Description   |
| :--------------: | :--------:| :------: |
|    action|   String|  动作标志  |
|    version|   String|  版本号  |
|    error|   int|  错误码  |
|    desc|   String|  成功为SUCCESS，失败为错误描述  |
|    result|   String| 	结果  |


## 支付或调用合约对接


ONTID通用请求，如支付和调用合约，整体流程为：

![ontid payment](https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/ontid-payment.png) 


1. 应用方后台发送支付请求到 ONT ID 开放平台。ONT ID 开放平台返回 ```orderid``` 作为流水号。
2. 应用方前台打开支付页面，参数中带着 ```orderid``` 和应用方前台的重定向地址 ```redirect_uri```。
3. 用户确认请求，发送请求到 ONTID 开放平台。
4. ONTID 开放平台处理请求，通知结果到应用方后台。
5. 同时返回结果到ONT ID前台。
6. ONT ID前台重定向到```redirect_uri```


### 应用方对接流程

1. 用户使用ONT ID登录第三方应用并传递`access_token`给应用后台。

2. 第三方应用后台发送创建订单请求到ONT ID开发平台后台，得到订单号`orderid`和`invoke_token`

```
url：/api/v1/ontid/request/order

method：POST

{
   "app_token" :  "JWT token: Base64(Header).Base64(Payload).Base64(Signature)",
   "user": "did:ont:AcrgWfbSPxMR1BNxtenRCCGpspamMWhLuL"
}

// data 需要使用应用方的ONT ID进行签名
// user 是用户的ONT ID
```
返回：

```

{
  "action" : "requestOrder",
  "error" : 0,
  "desc" : "SUCCESS",
  "result" : {
    "invoke_token" : "eyJ0eXAiOiJKV1QiLCJhbGciOiJFUzI1NiJ9.eyJhdWQiOiJkaWQ6b250OkFOUzlKbm9FUjVXcWNFNzVqSGVZWkF1U1dSdlRqUDY5V0giLCJpc3MiOiJkaWQ6b250OkFhdlJRcVhlOVByYVY1dFlnQnF2VjRiVXE4TFNzdmpjV1MiLCJleHAiOjE1NTM5NTkwMjAsImlhdCI6MTU1Mzg3MjYyMCwianRpIjoiYzkyZjNiMTdkN2E2NGZjZjg2MGI5M2I4ODgwMjVkNTMiLCJjb250ZW50Ijp7InR5cGUiOiJhY2Nlc3NfdG9rZW4iLCJvbnRpZCI6ImRpZDpvbnQ6QU5TOUpub0VSNVdxY0U3NWpIZVlaQXVTV1J2VGpQNjlXSCJ9fQ.MDFiYTllM2VkZjRhNjE2ODM1NjZjYThkMWVkM2UwNWUxNTg5MDEzMjEwYTFlOGU2ZDdiYmYxYjc0NTRmOGFlNzExMDQxZDUwMDExZWFkNDIwMmY3NDYyMTMyNGNlYjQ5NTA4NDM0YzRjOTI5Y2NmZTcyNzRmYTcxYTg2MzNkNTMzMw",
    "orderid" : "9892bcb698bb4cbd812c8b466d8ad432"
  },
  "version" : "v1"
}

```

3. 第三方应用跳转至通用的支付/调用合约页面，需要在url上附带参数如下：

   ```
   host + /transaction?orderid={orderid}&invoke_token={invoke_token}&callback_url={callback_url}
   ```

   其中，callback_url是支付/调用合约完成后，返回到应用方的回调地址。

4. 用户确认后输入ONT ID密码，交易发送上链，返回到第三方应用。

> 具体案例可以参考[官方示例](https://github.com/ontio-ontid/ontid-app-demo)



#### 订单请求 app_token 说明

``` app_token ``` 是应用方签发的，ONTID 开发平台验证通过才能访问接口。

Payload 里的字段包含调用合约的参数和应用方的信息，例如：

```
{
		"invokeConfig": { 
			"contractHash": "16edbe366d1337eb510c2ff61099424c94aeef02",
			"functions": [{
				"operation": "method name",
				"args": [{
					"name": "arg0-list",
					"value": [true, 100, "Long:100000000000", "Address:AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ", "ByteArray:aabb", "String:hello", [true, 100], {
						"key": 6
					}]
				}, {
					"name": "arg1-map",
					"value": {
						"key": "String:hello",
						"key1": "ByteArray:aabb",
						"key2": "Long:100000000000",
						"key3": true,
						"key4": 100,
						"key5": [100],
						"key6": {
							"key": 6
						}
					}
				}, {
					"name": "arg2-str",
					"value": "String:test"
				}]
			}],
			"payer": "AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ",
			"gasLimit": 20000,
			"gasPrice": 500
		},
        "app": {
            "name": "", // String，必填项，应用方名称
            "logo":"", // String，可选项，应用方logo的url。
            "message": "", // String，必填项，用于页面上显示支付/调用合约的目的，不能超过30个字符
            "ontid": "", // String，必填项，应用方的ONT ID
            "callback":"",// String，可选项，交易成功后通知应用方
            "nonce": "123456" // String，不能重复
        },
        "exp":1555041974000
}
```



| Param     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    invokeConfig |   String | 调用合约的参数 |
|    invokeConfig.contractHash |   String | 合约hash |
|    invokeConfig.functions |   List | 调用合约的函数，目前只支持一个 |
|    invokeConfig.payer |   String | 网络费付款人 |
|    invokeConfig.gasLimit |   int | 执行合约需要消耗的gas |
|    invokeConfig.gasPrice |   int | 目前是固定值500 |
|    app.ontid |   String | 应用方 ontid |
|    app.name |   String | 应用方 name |
|    app.logo |   String | 应用方 logo |
|    app.message |   String | 用于页面上显示支付/调用合约的目的，不能超过30个字符 |
|    app.nonce |   long |  |
|    exp |   long | 时间戳，该token的有效时间 |



## 查询接口对接


 ```app_token``` 是应用方签发的，里面包含应用方 ontid 和签名，类似与支付请求，Payload 里的字段：

 ```text
 {
     "app": {
         "ontid": ""
      }
     "exp":1555041974000
 }
 ```
 
 | Param     |     Type |   Description   |
 | :--------------: | :--------:| :------: |
 |    app.ontid |   String | 应用方 ontid |
 |    exp |   long | 时间戳，该token的有效时间 |
 

### 根据订单号查询订单
```
url： /api/v1/provider/query/order

method：POST

{
    "app_token" :  "JWT token: Base64(Header).Base64(Payload).Base64(Signature)",
    "orderId":"a24d06ec89c3ce0c845eb719697d7843464f287e19a8c7e3d3ef614378e610b2"
}
```

| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    app_token|   String|  应用方 app_token  |
|    orderId|   String|  订单号  |

返回：

```
{
  "action" : "queryOrder",
  "error" : 0,
  "desc" : "SUCCESS",
  "result" : {
    "note" : null,
    "wallet" : "ASm1sUJQDCgNzfjd9FuA5JGLBJLeXiQd1W",
    "tx" : "3a9594a26b84bfce8c7e44f9257fd09dadf303ea789fc4692123bcc7a679433d",
    "orderId" : "a24d06ec89c3ce0c845eb719697d7843464f287e19a8c7e3d3ef614378e610b2",
    "appInfo" : {
      "name" : "baidu",
      "logo" : "https://www.baidu.com/s?wd=%E4%BB%8A%E6%97%A5%E6%96%B0%E9%B2%9C%E4%BA%8B&tn=SE_Pclogo_6ysd4c7a&sa=ire_dl_gh_logo&rsv_dl=igh_logo_pc",
      "callback" : "http://127.0.0.1:1111/ontid/payment/callback",
      "language" : "cn",
      "message" : "baidu yixia",
      "nonce" : "cd4c4c0d-340e-4d31-8d4b-9fdc6b2939b7",
      "ontid" : "did:ont:AHcXzSaujd35gMaWsCv1R2Xd2w4Y43qdB8"
    },
    "state" : 5,
    "event" : "{\"GasConsumed\":10000000,\"Notify\":[{\"States\":[\"transfer\",\"ASm1sUJQDCgNzfjd9FuA5JGLBJLeXiQd1W\",\"AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ\",100],\"ContractAddress\":\"0200000000000000000000000000000000000000\"},{\"States\":[\"transfer\",\"ASm1sUJQDCgNzfjd9FuA5JGLBJLeXiQd1W\",\"AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK\",10000000],\"ContractAddress\":\"0200000000000000000000000000000000000000\"}],\"TxHash\":\"3a9594a26b84bfce8c7e44f9257fd09dadf303ea789fc4692123bcc7a679433d\",\"State\":1}",
    "user" : "did:ont:AJ6gC7r6Rb3ac4Zh7J4D69sSAps5bGZRTf"
  },
  "version" : "v1"
}
```


| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    action|   String|  动作标志  |
|    version|   String|  版本号  |
|    error|   int|  错误码  |
|    desc|   String|  成功为SUCCESS，失败为错误描述  |
|    result|   String| 	结果  |
|    result.note|   String| 	备注，失败情况的描述  |
|    result.wallet|   String| 	付款的地址  |
|    result.txHash|   String| 	该笔交易hash  |
|    result.orderId|   String| 	订单号  |
|    result.createTime|   String| 	订单创建时间  |
|    result.appInfo|   String| 	订单详情，跟之前构建订单内容一致  |
|    result.state|   String| 	0-初始，1-准备发送;2-发送成功;3-发送失败;4-交易成功;5-交易失败;6-订单过期  |
|    result.event|   String| 	该笔交易的smart event  |
|    result.user|   String| 	用户ontid  |

### 查询订单列表

```
url： /api/v1/provider/query/order/range

method：POST

{
    "app_token" :  "JWT token: Base64(Header).Base64(Payload).Base64(Signature)",
    "currentPage": 1,
    "size":10
}

```

返回：
```
{
  "action" : "queryOrderRange",
  "error" : 0,
  "desc" : "SUCCESS",
  "result" : [ {
    "wallet" : "ASm1sUJQDCgNzfjd9FuA5JGLBJLeXiQd1W",
    "txHash" : "3a9594a26b84bfce8c7e44f9257fd09dadf303ea789fc4692123bcc7a679433d",
    "orderId" : "a24d06ec89c3ce0c845eb719697d7843464f287e19a8c7e3d3ef614378e610b2",
    "createTime" : 1554986210000,
    "state" : 5,
    "user" : "did:ont:AJ6gC7r6Rb3ac4Zh7J4D69sSAps5bGZRTf"
  } ],
  "version" : "v1"
}
```

| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    action|   String|  动作标志  |
|    version|   String|  版本号  |
|    error|   int|  错误码  |
|    desc|   String|  成功为SUCCESS，失败为错误描述  |
|    result|   String| 	结果  |
|    result.wallet|   String| 	付款的地址  |
|    result.txHash|   String| 	该笔交易hash  |
|    result.orderId|   String| 	订单号  |
|    result.createTime|   String| 	订单创建时间  |
|    result.state|   String| 	0-初始，1-准备发送;2-发送成功;3-发送失败;4-交易成功;5-交易失败;6-订单过期  |
|    result.user|   String| 	用户ontid  |



## 错误码


| 代码     |     说明   |
| :----: | :----: |
| 00000	|	SUCCESS,成功 |
| 61001	|	PARAM_ERROR,参数错误 |
| 61002	|	ALREADY_EXIST,已存在 |
| 61003	|	NOT_FOUND,未找到 |
| 61004	|	NOT_EXIST,不存在
| 61005	|	NOT_PERMISSION,权限错误
| 61006	|	NOT_REGISTRY,未注册
| 61007	|	EXPIRES,已过期
| 61008	|	REVOKED,已注销
| 61009	|	SERIALIZE_ERROR,序列化错误
| 61010	|	TIME_EXCEEDED,次数超限
| 62001	|	VERIFY_FAIL,身份校验失败
| 62002	|	CREATE_FAIL,创建失败
| 62003	|	COMM_FAIL,通信异常
| 62004	|	FILE_ERROR,文件操作异常
| 62005	|	DB_ERROR,数据库操作错误
| 62006	|	SIG_VERIFY_FAILED,验签失败
| 63001	|	INNER_ERROR,内部异常
| 63002	|	EXCEPTION,异常
| 63003	|	CODE_VERIFY_FAILED,设备码校验失败
| 63004	|	IDENTITY_VERIFY_FAILED,身份认证失败






## 常见问题

#### JWT Token 格式说明？



 ```JWT``` 包含三个部分：

```
  Base64(Header).Base64(Payload).Base64(Signature)	 
```


每个部分都是```Base64Url```格式，以 ``` . ``` 隔开。

* **Header**
```
{
  "alg": "ES256",
  "typ": "JWT"
}
```

```alg``` 属性表示签名的算法，默认是 ```HMAC SHA256```（写成 HS256）, 但我们使用 ```ES256``` (```ECDSA``` 使用 ```P-256``` 曲线和 ```SHA-256``` hash 算法)。

```typ``` 属性表示这个令牌（token）的类型，```JWT token```统一写为 ```JWT```。

* **Payload**

官方规定了7个字段，可选。我们选用以下几个必须字段：

  ```iss (issuer)```：签发人。这里是 ONTID 开放平台的 ONTID。

  ```exp (expiration time)```：```token``` 过期时间。

  ```aud (audience)```：受众。这里是应用方的 ONTID。

  ```iat (Issued At)```：签发时间

  ```jti (JWT ID)```：编号。ONTID 开放平台保存的凭证。

> 注意除了以上字段，还有一些自定义字段用于存储用户信息，这些用户信息不能是敏感信息。

* **Signature**

```Signature``` 部分是对前两部分的签名，防止数据篡改。

签名生成规则是:

1. ```Header``` 和 ```Payload```按照字母序升序拼接成参数字符串，以&连接，比如：

```Header``` : alg=ES256&typ=JWT

```Payload```: aud=应用方ONTID&exp=20190310&iat=20190301……

2. 将上述两个字符串转成 ```base64url``` 格式，用 ```.``` 连接，得到模板字符串。
3. 使用 ONTID 开放平台私钥和签名算法```ES256```对目标字符串签名。

应用方得到```JWT token```后，按照如上规则生成目标字符串并对签名进行验签。