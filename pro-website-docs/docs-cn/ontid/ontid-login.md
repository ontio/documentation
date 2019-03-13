# ONT ID 综合账户体系

ONT ID综合账户体系，为用户提供区块链综合账户，一站式数字身份登录授权、管理用户资产、支付、调用合约。

## 网站应用ONTID对接指南

### 1. 准备工作


网站应用ONTID登录是类似于OAuth2.0协议标准构建的ONTID授权登录系统。

在进行ONTID授权登录接入之前，在ONTID开放平台注册开发者ONTID，获得相应的ONTID和PrivateKey，申请微信登录且通过审核后，可开始接入流程。



### 2. 授权注册/登录流程说明


ONTID授权登录让ONTID用户使用ONTID身份安全登录第三方应用或网站，在ONTID用户授权登录已接入ONTID的第三方应用后，第三方可以获取到用户的接口调用凭证（access_token），通过access_token可以进行ONTID开放平台授权关系接口调用，从而可实现获取 ONTID 用户基本开放信息和帮助用户实现基础开放功能等。

ONTID授权登录模式整体流程为：


![ontid login](https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/ontid-login.png) 

1. 应用方到ONT ID后台注册其ontid
2. 获得ONT ID后台的公钥
3. 应用方前台重定向到通用的登录页面，url上参数带着应用方的ONTID和用于登录后重定向到应用方的redirect_uri。(注意使用encodeURIComponent)
4. 用户输入用户名密码或验证码的方式登录。这里为了防刷短信验证码，可以提供图片验证码校验。
5. 验证用户名是否已注册，若无，返回错误码；若已注册，验证密码或手机验证码是否正确，若不匹配，则返回错误码；登录成功后，ONTID后台生成JWT token（详细信息见下文，如果对安全级别要求高，可以使用应用方公钥加密JWT token），返回给前台。
6. ONTID 前台重定向到redirect_uri,url参数上附带着JWT token。redirect_uri的页面需要将JWT token发送到其后台。
7. 应用方后台验证 access_token 中的签名。验证通过后，获取JWT中用户信息，一般为简短的信息，如用户手机号，用户ONTID。应用方后台为该用户创建session（如果该用户在应用方后台没有账户，需要先创建账户，再创建session。这取决于应用方自己的业务需要。）返回信息到其前台页面，如sessionId。
8. 应用方通过 access_token 进行接口调用，获取用户基本数据资源或帮助用户实现基本操作。





#### JWT token 格式

JWT包含三个部分依次如下：
```
  Base64(Header).Base64(Payload).Base64(Signature)	 

```


每个部分都是Base64Url格式，以 ``` . ``` 隔开。
* Header:

{
  "alg": "ES256",
  "typ": "JWT"
}
上面代码中，```alg``` 属性表示签名的算法，默认是 HMAC SHA256（写成 HS256）；typ属性表示这个令牌（token）的类型（type），JWT 令牌统一写为JWT。

* Payload:
官方规定了7个字段，可选。我们选用以下几个必须字段：

  iss (issuer)：签发人。这里是ONTID后台的ONTID。
  
  exp (expiration time)：过期时间。实际上该字段并不能起限制作用。因为目前ONTID后台并没有对外提供资源服务，只是提供了通用的授权登录方式。应用方获取到token后给用户创建session，session的有效期是由应用方控制的。此处保留该字段，以后如果ONTID后台提供了其它资源服务，该字段可以有效保护用户的数据安全。
  
  aud (audience)：受众。这里是应用方的ONTID。
  
  iat (Issued At)：签发时间
  
  jti (JWT ID)：编号。ONTID后台保存的凭证。
  
除了以上字段，还有一些自定义字段用于存储用户信息。注意这些用户信息不能是敏感信息。

{
  "phone": "+86*1234567890",
  "ontid": "did:ont:Axxxxxxxxxxxxxxxxx",
  ......
}

* Signature:

Signature 部分是对前两部分的签名，防止数据篡改。

签名生成规则是:

1. Header 和 Payload按照字母序升序拼接成参数字符串，以&连接，比如：
Header : alg=ES256&typ=JWT
Payload: aud=应用方ONTID&exp=20190310&iat=20190301……

2. 将上述两个字符串转成base64url格式，用 . 连接，得到模板字符串。
3. 使用ONTID后台私钥和签名算法ES256对目标字符串签名。

应用方得到JWT token后，按照如上规则生成目标字符串并对签名进行验签。


### 3. 其他通用请求流程说明


ONTID通用请求，如支付和调用合约，整体流程为：

![ontid payment](https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/ontid-payment.png) 


1. 应用方后台发送请求到ONT ID后台，用于请求某个服务。比如支付请求。请求参数包含JWT token。ONT ID 后台验证token是否有效，验证后保存请求。以requestId作为索引。
2. 应用方前台重定向到通用支付页面，参数中带着requestId和应用方前台重定向的redirect_uri。
3. 用户确认请求，发送请求到ONTID后台
4. ONTID后台处理请求，通知结果到应用方后台。
5. 同时返回结果到ONT ID前台。
6. ONT ID前台重定向到redirect_uri

#### 调用合约

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

action：
params: 每种服务有对应的参数要求
token: 用户先登录获取token，才能继续请求通用服务。如果token过期，则返回相应错误码。
createTIme: 请求生成时间
paramsHash: 可作为免密操作的判断依据
appOntid: 应用方ONTID
signature: 对以上参数使用应用方私钥签名，传递到ONTID后台时会被校验。



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