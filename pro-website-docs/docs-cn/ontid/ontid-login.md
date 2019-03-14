


ONT ID 开放平台，为用户托管区块链综合账户，提供一站式数字身份登录授权、管理用户资产、支付、调用合约等服务。


## 准备工作


网站应用 ONTID 登录是类似于```OAuth2.0```协议标准构建的 ONTID 授权登录系统。

在进行 ONTID 授权登录接入之前，应用方需要先在 ONTID 开放平台注册 ONTID ，获得相应的 ONTID 和```PrivateKey```，申请 ONTID 通过审核后，可开始接入流程。



## 注册/登录


ONTID 授权登录是让用户使用 ONTID 身份安全登录第三方应用或网站，在 ONTID 用户授权登录已接入 ONTID 的第三方应用后，第三方可以获取到用户的接口调用凭证（```access_token```），通过 ```access_token``` 可以进行 ONTID 相关接口调用。

ONTID 授权登录模式整体流程为：


![ontid login](https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/ontid-login.png) 


1. 应用方前台打开新窗口加载 ONTID 的登录页面。
2. 用户在 ONTID 的登录页面输入用户名密码登录。
3. ONTID 开发平台返回 ```access_token``` 和 ```refresh_token``` 的 ```JWT token```。
4. ONTID 开放平台前端关闭登录页面，返回```JWT token```给应用的前端。
5. 应用方前端发送 ```JWT token``` 给应用的后台。 
6. 应用放的后台验证 ```JWT token``` 的颁发者成功后，获取 ```refresh_token``` 中用户信息，一般为非敏感的信息，如用户用户 ONTID，手机号。
7. 根据```access_token``` 访问 ONTID 开放平台接口。

第三步返回的 ```JWT token``` 的数据格式：
 
```
 {
    "access_token" :  "JWT token",
    "refresh_token" : "JWT token",
 }
```
 
 | Param     |     Type |   Description   |
 | :--------------: | :--------:| :------: |
 |    access_token |   String | ```JWT token```，用户访问接口时 ```Header``` 需要填写 ```access_token``` |
 |    refresh_token |   String | ```JWT token```，刷新 ```access_token``` 时使用 |
 
 
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

```alg``` 属性表示签名的算法，默认是 ```HMAC SHA256```（写成 HS256）；

```typ``` 属性表示这个令牌（token）的类型，```JWT token```统一写为 ```JWT```。

#### Payload

官方规定了7个字段，可选。我们选用以下几个必须字段：

  ```iss (issuer)```：签发人。这里是 ONTID 开放平台的 ONTID。
  
  ```exp (expiration time)```：```token``` 过期时间。
  
  ```aud (audience)```：受众。这里是应用方的 ONTID。
  
  ```iat (Issued At)```：签发时间
  
  ```jti (JWT ID)```：编号。ONTID 开放平台保存的凭证。
  
> 注意除了以上字段，还有一些自定义字段用于存储用户信息，这些用户信息不能是敏感信息。只有 ```refresh_token``` 需要增加 ```content```：

```

  "content": {
      "phone": "+86*1234567890",
      "ontid": "did:ont:Axxxxxxxxxxxxxxxxx",
      ......
  }
  
```

#### Signature

```Signature``` 部分是对前两部分的签名，防止数据篡改。

签名生成规则是:

1. ```Header``` 和 ```Payload```按照字母序升序拼接成参数字符串，以&连接，比如：

```Header``` : alg=ES256&typ=JWT

```Payload```: aud=应用方ONTID&exp=20190310&iat=20190301……

2. 将上述两个字符串转成 ```base64url``` 格式，用 ```.``` 连接，得到模板字符串。
3. 使用 ONTID 开放平台私钥和签名算法```ES256```对目标字符串签名。

应用方得到```JWT token```后，按照如上规则生成目标字符串并对签名进行验签。



## 用户授权

有些接口需要用户授权，应用后台才有权限访问用户的数据。没有授权就能访问的是默认授权的接口。



## 支付/调用合约接口


ONTID通用请求，如支付和调用合约，整体流程为：

![ontid payment](https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/ontid-payment.png) 


1. 应用方后台发送支付请求到 ONT ID 开放平台。请求的头部包含 ```access_token```。ONT ID 开放平台验证 ```access_token``` 是否有效，返回 ```requestId``` 作为流水号。
2. 应用方前台打开支付页面，参数中带着 ```requestId``` 和应用方前台的重定向地址 ```redirect_uri```。
3. 用户确认请求，发送请求到 ONTID 开放平台。
4. ONTID 开放平台处理请求，通知结果到应用方后台。
5. 同时返回结果到ONT ID前台。
6. ONT ID前台重定向到```redirect_uri```

### 调用合约的数据格式

数据格式：

```
url：/api/v1/ontid/invoke

method：POST

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
            "createtime": 1552541388,
            "expire": 1552543312,
            "nonce": 5434536
        },
        "signature": ""
}
```



| Param     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    invokeConfig |   String | Parameter configuration of the invokation contract |
|    invokeConfig.contractHash |   String | contract hash |
|    invokeConfig.functions |   List | The function list that calls the contract, currently only supports one |
|    invokeConfig.payer |   String | Network fee payer |
|    invokeConfig.gasLimit |   int | Gas consumed to execute the contract |
|    invokeConfig.gasPrice |   int | Fixed value 500 |
|    signature|   String | The application uses the private key to sign parameters other than signature, which are verified when passed to the ONTID open platform. |


ONT/ONG transfer ```invokeConfig``` parameter filling example :
```
{
	"invokeConfig": {
		"contractHash": "0100000000000000000000000000000000000000", // ONG: 0200000000000000000000000000000000000000
		"functions": [{
			"operation": "transfer",
			"args": [{
					"name": "arg0-from",
					"value": "Address:AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ"
				}, {
					"name": "arg1-to",
					"value": "Address:AecaeSEBkt5GcBCxwz1F41TvdjX3dnKBkJ"
				},
				{
					"name": "arg2-amount",
					"value": 10000
				}
			]
		}],
		"payer": "AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ",
		"gasLimit": 20000,
		"gasPrice": 500
	}
}

```

## Other interface

The following interfaces ``` Header``` need to add ```access_token``` to access.


### Query asset balance


```
url：/api/v1/ontid/getbalance

method：POST

{
   	"ontid":"did:ont:AcrgWfbSPxMR1BNxtenRCCGpspamMWhLuL"
}
```
| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    ontid|   String|  ontid  |

Response：

```
{
    "action":"getbalance",
    "version":"1.0",
    "error":0,
    "desc":"SUCCESS",
    "result": {
       "ont": "100",
       "ong": "10000000000"
    }
}
```

| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    action|   String|  action  |
|    version|   String|  version  |
|    error|   int|  error code  |
|    desc|   String|  error desc |
|    result|   String| 	result  |


### Error Code


| Code     |     desc   |  
| :----: | :----: | 
| 00000	|	SUCCESS |
| 61001	|	PARAM_ERROR |
| 61002	|	ALREADY_EXIST |
| 61003	|	NOT_FOUND |
| 61004	|	NOT_EXIST
| 61005	|	NOT_PERMISSION
| 61006	|	NOT_REGISTRY
| 61007	|	EXPIRES
| 61008	|	REVOKED
| 61009	|	SERIALIZE_ERROR
| 61010	|	TIME_EXCEEDED
| 62001	|	VERIFY_FAIL
| 62002	|	CREATE_FAIL
| 62003	|	COMM_FAIL
| 62004	|	FILE_ERROR
| 62005	|	DB_ERROR
| 62006	|	SIG_VERIFY_FAILED
| 63001	|	INNER_ERROR
| 63002	|	EXCEPTION
| 63003	|	CODE_VERIFY_FAILED
| 63004	|	IDENTITY_VERIFY_FAILED


