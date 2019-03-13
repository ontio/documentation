


ONT ID 综合账户体系，为用户托管区块链综合账户，提供一站式数字身份登录授权、管理用户资产、支付、调用合约等服务。


## 准备工作


网站应用ONTID登录是类似于```OAuth2.0```协议标准构建的ONTID授权登录系统。

在进行 ONTID 授权登录接入之前，在 ONTID 开放平台注册开发者 ONTID ，获得相应的 ONTID 和```PrivateKey```，申请微信登录且通过审核后，可开始接入流程。



## 授权注册/登录


ONTID 授权登录是让用户使用ONTID身份安全登录第三方应用或网站，在 ONTID 用户授权登录已接入 ONTID 的第三方应用后，第三方可以获取到用户的接口调用凭证（```access_token```），通过 ```access_token``` 可以进行 ONTID 开放平台授权关系接口调用，从而可实现获取 ONTID 用户基本开放信息和其他接口。

ONTID 授权登录模式整体流程为：


![ontid login](https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/ontid-login.png) 

1. 应用方到 ONTID 后台注册其 ONTID
2. 获得 ONTID 后台的公钥
3. 应用方前台重定向到通用的登录页面，url上参数带着应用方的ONTID和用于登录后重定向到应用方的```redirect_uri```。(注意使用```encodeURIComponent```)
4. 用户输入用户名密码或验证码的方式登录。这里为了防刷短信验证码，可以提供图片验证码校验。
5. 验证用户名是否已注册，若无，返回错误码；若已注册，验证密码或手机验证码是否正确，若不匹配，则返回错误码；登录成功后，ONTID后台生成JWT token（详细信息见下文，如果对安全级别要求高，可以使用应用方公钥加密JWT token），返回给前台。
6. ONTID 前台重定向到```redirect_uri```,url参数上附带着```JWT token```。```redirect_uri```的页面需要将```JWT token```发送到其后台。
7. 应用方后台验证 ```access_token``` 中的签名。验证通过后，获取JWT中用户信息，一般为简短的信息，如用户手机号，用户ONTID。应用方后台为该用户创建session（如果该用户在应用方后台没有账户，需要先创建账户，再创建session。这取决于应用方自己的业务需要。）返回信息到其前台页面，如sessionId。
8. 应用方通过 ```access_token``` 进行接口调用，获取用户基本数据资源或帮助用户实现基本操作。





### JWT Token 格式说明

```JWT```包含三个部分：

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
上面代码中，```alg``` 属性表示签名的算法，默认是 ```HMAC SHA256```（写成 HS256）；typ属性表示这个令牌（token）的类型（type），```JWT token```统一写为JWT。

#### Payload

官方规定了7个字段，可选。我们选用以下几个必须字段：

  ```iss (issuer)```：签发人。这里是 ONTID 后台的 ONTID。
  
  ```exp (expiration time)```：```token``` 过期时间。
  
  ```aud (audience)```：受众。这里是应用方的ONTID。
  
  ```iat (Issued At)```：签发时间
  
  ```jti (JWT ID)```：编号。ONTID 后台保存的凭证。
  
除了以上字段，还有一些自定义字段用于存储用户信息。注意这些用户信息不能是敏感信息。

```
{
  "phone": "+86*1234567890",
  "ontid": "did:ont:Axxxxxxxxxxxxxxxxx",
  ......
}
```

#### Signature

```Signature``` 部分是对前两部分的签名，防止数据篡改。

签名生成规则是:

1. ```Header``` 和 ```Payload```按照字母序升序拼接成参数字符串，以&连接，比如：
Header : alg=ES256&typ=JWT
Payload: aud=应用方ONTID&exp=20190310&iat=20190301……

2. 将上述两个字符串转成base64url格式，用 . 连接，得到模板字符串。
3. 使用ONTID后台私钥和签名算法ES256对目标字符串签名。

应用方得到JWT token后，按照如上规则生成目标字符串并对签名进行验签。


## 支付、调用合约


ONTID通用请求，如支付和调用合约，整体流程为：

![ontid payment](https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/ontid-payment.png) 


1. 应用方后台发送请求到ONT ID后台，用于请求某个服务。比如支付请求。请求参数包含```JWT token```。ONT ID 后台验证token是否有效，验证后保存请求。以```requestId```作为索引。
2. 应用方前台重定向到通用支付页面，参数中带着```requestId```和应用方前台重定向的```redirect_uri```。
3. 用户确认请求，发送请求到ONTID后台
4. ONTID后台处理请求，通知结果到应用方后台。
5. 同时返回结果到ONT ID前台。
6. ONT ID前台重定向到```redirect_uri```

### 调用合约

数据格式：

```

{
	"action": "invoke",
	"version": "v1.0.0",
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",	
	"params": {
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
            "callback": ""
        },
        "signature": ""
	}
}
```



| Param     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    action|   String | 通用服务类别，比如支付payment，授权authorization等 |
|    params|   String | 每种服务有对应的参数要求 |
|    invokeConfig |   String | 调用合约的参数 |
|    invokeConfig.contractHash |   String | 合约hash |
|    invokeConfig.functions |   List | 调用合约的函数，目前只支持一个 |
|    invokeConfig.payer |   String | 网络费付款人 |
|    invokeConfig.gasLimit |   int | 执行合约需要消耗的gas |
|    invokeConfig.gasPrice |   int | 目前是固定值500 |
|    signature|   String | 对params内除signature以外参数应用方用私钥签名，传递到ONTID后台时会被校验。 |


ONT/ONG转账```invokeConfig```参数填写例子：
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

## 接口说明

### 导出
1. 提交ontid和密码
2. 返回所需要的结果
```text
导出 keystore
url：/api/v1/ontid/export/keystore 

导出 wif
url：/api/v1/ontid/export/wif 

导出 手机号
url：/api/v1/ontid/export/phone 

method：POST
```

请求：
```json
{
   	"ontid":"did:ont:AcrgWfbSPxMR1BNxtenRCCGpspamMWhLuL",
   	"password":"12345678"
}
```
| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    ontid|   String|  ontid  |
|    password|   String|  ontid密码  |

返回：
```json
{
	"action":"export",
	"version":"1.0",
	"error":0,
	"desc":"SUCCESS",
	"result": "请求的对应值"
}
```

| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    action|   String|  动作标志  |
|    version|   String|  版本号  |
|    error|   int|  错误码  |
|    desc|   String|  成功为SUCCESS，失败为错误描述  |
|    result|   String|  keystore请求返回keystore，wif请求返回wif,phone请求返回phone，失败返回""  |

### 修改手机号
1. 新的手机[获取验证码](#获取验证码)
2. 提交新手机号码，验证码，旧手机号码和密码
3. 返回ontid（该ontid和keystore的ontid一致）
```text
url：/api/v1/ontid/edit/phone 
method：POST
```

请求：
```json
{
    "newPhone": "86*15821703552",
    "verifyCode": "123456",
    "oldPhone":"86*15821703553",
    "password":"12345678"
}
```
| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    newPhone|   String|  新的手机号码  |
|    verifyCode|   String|  新的手机的验证码  |
|    oldPhone|   String|  旧的手机号码  |
|    password|   String|  原来的密码  |

返回：
```json
{
    "action":"edit",
    "version":"1.0",
    "error":0,
    "desc":"SUCCESS",
    "result": "did:ont:AcrgWfbSPxMR1BNxtenRCCGpspamMWhLuL"
}
```

| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    action|   String|  动作标志  |
|    version|   String|  版本号  |
|    error|   int|  错误码  |
|    desc|   String|  成功为SUCCESS，失败为错误描述  |
|    result|   String|  成功返回ontid，失败返回""  |

### 修改密码
1. 提交号码，旧密码，新的密码
2. 返回ontid
```text
url：/api/v1/ontid/edit/password
method：POST
```

请求：
```json
{
    "phone":"86*15821703553",
    "oldPassword":"12345678",
    "newPassword":"12345679"
}
```
| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    phone|   String|  手机号码  |
|    oldPassword|   String|  旧密码  |
|    newPassword|   String|  新密码  |

返回：
```json
{
    "action":"edit",
    "version":"1.0",
    "error":0,
    "desc":"SUCCESS",
    "result": "did:ont:AcrgWfbSPxMR1BNxtenRCCGpspamMWhLuL"
}
```

| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    action|   String|  动作标志  |
|    version|   String|  版本号  |
|    error|   int|  错误码  |
|    desc|   String|  成功为SUCCESS，失败为错误描述  |
|    result|   String|  成功返回ontid，失败返回""  |


### 解密claim
1. 通过Onid和密码解密claim
2. 返回所需要的结果
```text
url：/api/v1/ontid/decrypt/claim

method：POST
```

请求：
```json
{
   	"ontid":"did:ont:AcrgWfbSPxMR1BNxtenRCCGpspamMWhLuL",
   	"password":"12345678",
   	"message": ["","",""]
}
```
| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    ontid|   String|  ontid  |
|    password|   String|  ontid密码  |
|    message|   JSONArray|  加密后的数据  |

返回：
```json
{
    "action":"decrypt",
    "version":"1.0",
    "error":0,
    "desc":"SUCCESS",
    "result": "解密后的内容"
}
```

| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    action|   String|  动作标志  |
|    version|   String|  版本号  |
|    error|   int|  错误码  |
|    desc|   String|  成功为SUCCESS，失败为错误描述  |
|    result|   String| 	解密后的内容  |


### 错误码


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


### 接口测试
我们建议前端数据RSA公钥加密，发给后台加上HMAC签名获取数据

测试数据：
```text
private static String AppId = "mdgDyjj4";

private static String AppSecret = "cOLo1W+NlZy9wUzWuMARUg==";

private static String pubRSAKey="MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCdyNjEizEPw7cudl/wY2UFg9ghNj/jR04iC8H3W+SWL/GMCnOz/9XDfC3u84Tvt1KgFqWIZIwkgNJlMTXHedSXIMX91jU0mGIHiUcmRmgr56Jb1B5C13tD+UTA4ii63WKmD+AEvxejxSphuyZ2MILlNqIIuL71gklSkYkTbXsXGQIDAQAB";

private static String testNet="http://139.219.136.188:10330"

private static String aes.iv="6889f892a17e4371"
```
举例：
前端请求
转发
```text
url：/api/v1/ontid/test/forwardRequest

method：POST
```

```text
{
    "url":"/api/v1/ontid/gettx/register/ontid",
    "secure":"eewK+BL+iBja2n2l57ffdQrdB/zdsJGOPTJFD86IsLm1D/UBh9DKmCQjjP9d7tLrmAkgI62ewLwLRMzPoqs8JblUcDDGsQbG2wEdHUN5wvEoUgHbRQaTpGvIqQoL2FFSPqxFaYn4uh1RjhrcjgxHDh0JqJG3wyyHUV+vzymJJBw=",
    "data":"FK/1h1QVJzJLnQyKR5mCpf56IOsldpRqXvX6PZooccNnkoH3KserF2eDDGBRw6NDEg5h9VhRt8TkAqTYIZgQLg=="
}
```
| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    url|   String|  动作标志  |
|    secure|   String|  RSA公钥加密后的数据  |
|    data|   String|  AES使用随机生成的对请求body进行加密的数据  |

如不需要，可以自己定制后台的逻辑处理
```text
header
"Content-Type", "application/ontid.manage.api.v1+json"
"Secure-Key",前端发来的secure数据
"Authorization":HMAC处理后的结果

body
{"data":"FK/1h1QVJzJLnQyKR5mCpf56IOsldpRqXvX6PZooccNnkoH3KserF2eDDGBRw6NDEg5h9VhRt8TkAqTYIZgQLg=="}

去掉空格和换行
请求对应的服务器地址+url
```