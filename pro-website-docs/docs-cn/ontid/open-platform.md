
ONT ID 开放平台为第三方应用提供第三方登录、支付、智能合约执行、KYC等服务，请按照以下步骤开始应用集成。


## 准备工作


网站应用 ONTID 登录是类似于```OAuth2.0```协议标准构建的 ONTID 授权登录系统。

在进行 ONTID 授权登录接入之前，应用方需要先在 ONTID 开放平台注册 ONTID ，获得相应的 ONTID 和 ```PrivateKey```，申请 ONTID 通过审核后，可开始接入流程。



## 第三方登录


ONTID 授权登录是让用户使用 ONTID 身份安全登录第三方应用或网站，在 ONTID 用户授权登录已接入 ONTID 的第三方应用后，第三方可以获取到用户的接口调用凭证（```access_token```），通过 ```access_token``` 可以进行 ONTID 相关接口调用。

ONTID 授权登录模式整体流程为：


![ontid login](https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/ontid-login.png) 


1. 应用方前台打开新窗口加载 ONTID 的登录页面。
2. 用户在 ONTID 的登录页面输入用户名密码登录。
3. ONTID 开发平台返回 ```access_token``` 和 ```refresh_token``` 的 ```JWT token```。
4. ONTID 开放平台前端关闭登录页面，返回```JWT token```给应用的前端。
5. 应用方前端发送 ```JWT token``` 给应用的后台。 
6. 应用方的后台验证 ```JWT token``` 的颁发者成功后，获取 ```refresh_token``` 中用户信息，一般为非敏感的信息，如用户用户 ONTID，手机号。
7. 根据```access_token``` 访问 ONTID 开放平台接口。

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
       "phone": "86*1234567890",
       "ontid": "did:ont:Axxxxxxxxxxxxxxxxx",
       ......
   }
   
```
 
 | Param     |     Type |   Description   |
 | :--------------: | :--------:| :------: |
 |    access_token |   String | ```JWT token```，用户访问接口时 ```Header``` 需要填写 ```access_token``` |
 |    refresh_token |   String | ```JWT token```，刷新 ```access_token``` 时使用 |
 
 

### JWT Token 格式说明

 ```JWT``` 包含三个部分：

```
  Base64(Header).Base64(Payload).Base64(Signature)	 
```


每个部分都是```Base64Url```格式，以 ``` . ``` 隔开。

#### Header
```
{
  "alg": "ES256",
  "typ": "JWT"
}
```

```alg``` 属性表示签名的算法，默认是 ```HMAC SHA256```（写成 HS256）, 但我们使用 ```ES256``` (```ECDSA``` 使用 ```P-256``` 曲线和 ```SHA-256``` hash 算法)。

```typ``` 属性表示这个令牌（token）的类型，```JWT token```统一写为 ```JWT```。

#### Payload

官方规定了7个字段，可选。我们选用以下几个必须字段：

  ```iss (issuer)```：签发人。这里是 ONTID 开放平台的 ONTID。
  
  ```exp (expiration time)```：```token``` 过期时间。
  
  ```aud (audience)```：受众。这里是应用方的 ONTID。
  
  ```iat (Issued At)```：签发时间
  
  ```jti (JWT ID)```：编号。ONTID 开放平台保存的凭证。
  
> 注意除了以上字段，还有一些自定义字段用于存储用户信息，这些用户信息不能是敏感信息。

#### Signature

```Signature``` 部分是对前两部分的签名，防止数据篡改。

签名生成规则是:

1. ```Header``` 和 ```Payload```按照字母序升序拼接成参数字符串，以&连接，比如：

```Header``` : alg=ES256&typ=JWT

```Payload```: aud=应用方ONTID&exp=20190310&iat=20190301……

2. 将上述两个字符串转成 ```base64url``` 格式，用 ```.``` 连接，得到模板字符串。
3. 使用 ONTID 开放平台私钥和签名算法```ES256```对目标字符串签名。

应用方得到```JWT token```后，按照如上规则生成目标字符串并对签名进行验签。



### 应用方对接流程


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

以下接口 ``` Header``` 都需要添加```access_token``` 才能访问。

#### 查询 ontid 账户信息

```
url：/api/v1/ontid/info

method：POST

{  
}
```

返回：

```
{
    action: "getInfo",
    error: 0,
    desc: "SUCCESS",
    result: {
        wallet: [
            {
                address: "ASqT8qw2TMXCcTLQtpmbhTrpPhWDj8qCRV",
                ont: 0,
                ong: 0
            }
        ],
        phone: "86*15951496186",
        publicKey: "03f4c1212a5f726aca1c6877070b7d017cf5927ef7be9083b0ef5619e1b3ffbfed",
        ontid: "did:ont:AMxrSGHyxgnWS6qc1QjTNYeEaw3X3Dvzhf"
    },
    version: "v1"
}
```

| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    action|   String|  动作标志  |
|    version|   String|  版本号  |
|    error|   int|  错误码  |
|    desc|   String|  成功为SUCCESS，失败为错误描述  |
|    result|   String| 	结果  |
|    result.phone|   String| 	用户的手机号  |
|    result.publicKey|   String| 	用户的公钥  |
|    result.ontid|   String| 	用户的ontid  |
|    result.wallet|   String| 	用户的钱包  |
|    wallet.address|   String| 	用户的钱包地址  |
|    wallet.ont|   String| 	钱包的ont余额  |
|    wallet.ong|   String| 	钱包的ong余额  |



## 支付/调用合约接口


ONTID通用请求，如支付和调用合约，整体流程为：

![ontid payment](https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/ontid-payment.png) 


1. 应用方后台发送支付请求到 ONT ID 开放平台。ONT ID 开放平台返回 ```orderid``` 作为流水号。
2. 应用方前台打开支付页面，参数中带着 ```orderid``` 和应用方前台的重定向地址 ```redirect_uri```。
3. 用户确认请求，发送请求到 ONTID 开放平台。
4. ONTID 开放平台处理请求，通知结果到应用方后台。
5. 同时返回结果到ONT ID前台。
6. ONT ID前台重定向到```redirect_uri```


### 调用合约的数据格式

```
url：/api/v1/provider/request/order

method：POST

{
   "app_token" :  "JWT token: Base64(Header).Base64(Payload).Base64(Signature)",
   "user": "did:ont:AcrgWfbSPxMR1BNxtenRCCGpspamMWhLuL"
}

```
返回：

```

{
  "action" : "requestOrder",
  "error" : 0,
  "desc" : "SUCCESS",
  "result" : {
    "invoke_token" : "eyJ0eXAiOiJKV1QiLCJhbGciOiJFUzI1NiJ9.eyJhdWQiOiJkaWQ6b250OkFOUzlKbm9FUjVXcWNFNzVqSGVZWkF1U1dSdlRqUDY5V0giLCJpc3MiOiJkaWQ6b250OkFhdlJRcVhlOVByYVY1dFlnQnF2VjRiVXE4TFNzdmpjV1MiLCJleHAiOjE1NTM5NTkwMjAsImlhdCI6MTU1Mzg3MjYyMCwianRpIjoiYzkyZjNiMTdkN2E2NGZjZjg2MGI5M2I4ODgwMjVkNTMiLCJjb250ZW50Ijp7InR5cGUiOiJhY2Nlc3NfdG9rZW4iLCJvbnRpZCI6ImRpZDpvbnQ6QU5TOUpub0VSNVdxY0U3NWpIZVlaQXVTV1J2VGpQNjlXSCJ9fQ.MDFiYTllM2VkZjRhNjE2ODM1NjZjYThkMWVkM2UwNWUxNTg5MDEzMjEwYTFlOGU2ZDdiYmYxYjc0NTRmOGFlNzExMDQxZDUwMDExZWFkNDIwMmY3NDYyMTMyNGNlYjQ5NTA4NDM0YzRjOTI5Y2NmZTcyNzRmYTcxYTg2MzNkNTMzMw",
    "orderId" : "9892bcb698bb4cbd812c8b466d8ad432"
  },
  "version" : "v1"
}

```

#### Payload 里的字段

包含调用合约的参数和应用方的信息。

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
        "name": "",
        "logo":"",
        "message": "",
        "ontid": "",
        "callback": "",
        "nonce": "123456781234"
     }
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
|    app.callback |   String | 调用合约成功的回调地址 |
|    app.nonce |   long | 随机数，保证每次请求的数据不一样,16位 |
|    exp |   long | 时间戳，该token的有效时间 |





## 查询接口

```app_token``` 是应用方签发的，里面包含应用方 ontid 和签名，类似与支付请求。

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

### 根据订单号查询订单详情

```text
url： /api/v1/provider/query/order

method：POST

{
    "app_token" :  "JWT token: Base64(Header).Base64(Payload).Base64(Signature)",
    "orderId":"a24d06ec89c3ce0c845eb719697d7843464f287e19a8c7e3d3ef614378e610b2"
}
```



返回：

```
{
    action: "queryOrder",
    error: 0,
    desc: "SUCCESS",
    result: {
        note: null,
        wallet: "ASqT8qw2TMXCcTLQtpmbhTrpPhWDj8qCRV",
        txHash: "5b7fd0f390bd5cfa9dc5df2014712f7312857b1e303a367bb60100ac0e7d5fcf",
        orderId: "2ce54ba2db47b01a64d09b1ba1a848161f06361525bbd99b49c3ccf214c3259b",
        createTime: 1554992710000,
        appInfo: {
            name: "test",
            logo: "www.baidu.com",
            callback: "http://139.219.136.188:11111/ontid/payment/callback",
            message: "这是一个测试内容",
            nonce: "1ee1bdd6d50c433cb7429c0779c45384",
            ontid: "did:ont:AaqWLmN3LNqu8QFpuSnoK3QM4g5KC2ZSTC"
        },
        state: 6,
        event: null,
        user: "did:ont:AMxrSGHyxgnWS6qc1QjTNYeEaw3X3Dvzhf"
    },
    version: "v1"
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

```text
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
    action: "queryOrderRange",
    error: 0,
    desc: "SUCCESS",
    result: [
        {
            wallet: "ASqT8qw2TMXCcTLQtpmbhTrpPhWDj8qCRV",
            txHash: null,
            orderId: "532de576f7ba4c194e71c3994a452688b8d474760e844c3cf6d00f76c0a02fe9",
            createTime: 1555039410000,
            state: 0,
            user: "did:ont:AMxrSGHyxgnWS6qc1QjTNYeEaw3X3Dvzhf"
        }
     ],
    version: "v1"
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


## 对接文档

请参考 [对接指南](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/08-ontid_integration)。
