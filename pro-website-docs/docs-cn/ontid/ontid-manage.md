
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
3. ONTID 开发平台返回 ```access_token``` 的 ```JWT token```。
4. ONTID 开放平台前端关闭登录页面，返回```JWT token```给应用的前端。
5. 应用方前端发送 ```JWT token``` 给应用的后台。 
6. 应用方的后台验证 ```JWT token``` 。
7. 根据```access_token``` 访问 ONTID 开放平台接口。

第三步返回的 ```JWT token``` 的数据采用应用方公钥加密，解密后的数据格式为：
 
```
 {
    "ontid": "did:ont:AcrgWfbSPxMR1BNxtenRCCGpspamMWhLuL",
    "access_token" :  "JWT token",
 }
```
 
>  ```JWT token``` 的值里的Payload需要增加 ```content```字段：
 
```
 
   "content": {
       "type": "access_token", 
       "ontid": "did:ont:Axxxxxxxxxxxxxxxxx",
     }
   
```
 
 | Param     |     Type |   Description   |
 | :--------------: | :--------:| :------: |
 |    access_token |   String | ```JWT token```，用户访问接口时 ```Header``` 需要填写 ```Authorization : access_token``` |

 
 

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

#### 应用方平台注册

应用方需要先联系我们，我们将会提供appId和appSecret用于后台请求
```text
{
    "code"=0,
    "msg"="SUCCESS",
    "result"={    
        "platform_public_key"="026d3557e55fffe7bc5a9a8fc0c7361bc48590c17bf4d0d345e3f354bb64a0452a",
        "dapp_public_key"="03d355ac923efadbc7e6f2f07b49536a25a7f817498409593b51f5d532152c3bfa",
        "app_id"="did:ont:ANqiHycikgyzkfz36faP5ymXLVg1uovhXh", 
        "app_secret"="TG9lbFpWSKaGwbwdXrPjCUbNXLi/HA=="
                }
}
```
| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    code|   int|  错误码  |
|    msg|   String|  成功为SUCCESS，失败为错误描述  |
|    result|   String| 	结果  |
|    result.platform_public_key|   String| 	平台的公钥，用于验签  |
|    result.dapp_public_key|   String| 	dapp的公钥  |
|    result.app_id|   String| 	dapp的app id  |
|    result.app_secret|   String| 	dapp的app secret  |


#### 对接流程
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

#### HTTP-Header

| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
| Authorization | String | 放jwt_token，做身份认证和权限控制  |
| Hmac          | String    | 放请求内容的hmac值，防止重放和篡改 |

#### Hmac

当DApp在平台注册时，同时分配`appid`和`appsecret`，`appid`现在就是`ontid`。客户端和服务端按照下面同样的生成规则和逻辑，生成HMAC和验证HMAC。通过nonce和requestTimeStamp判断是否重放，通过验证signature验证数据是否被篡改。

``` java
if(requestHttpMethod == POST || requestHttpMethod == PUT ){
    payload = request.body;
}else if(requestHttpMethod == GET){
    payload = request.uriparam;// url?之后的值,如果没有，用""代替
}

function GenerateAlgorithm (payload) => {
  requestContentBase64String = base64(MD5(payload))

  // 按照一定的顺序构造需要签名的字符串
  rawData =  appId + requestHttpMethod + requestUri + requestTimeStamp + nonce + requestContentBase64String

  // 使用约定好的算法哈希需要签名的内容，哈希后的内容需要转成 Base64String
  HmacSHA256.initHmac(appsecret, length)
  signature = base64(HmacSHA256.ComputeHash(rawData))

  // 构造 http 协议头部的 Authorization 参数，注意 schema 是约定好的 ont，各个参数用 , 分割，花括号是C#的 String Format语法，{0} 表示占据第0个位置。
  header = string.Format("ont,{0},{1},{2},{3}", APPId, signature, nonce, requestTimeStamp)
}
```
#### 查询 ontid 账户信息

```
url：/v1/dapps/users/info

method：GET

```

返回：

```
  "Response": {
          "code": 0,
          "msg": "string",
          "result": {
              "user_phone":"",
              "user_public_key":""
              "user_ontid":""
        }
    }
```

| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    code|   int|  错误码  |
|    msg|   String|  成功为SUCCESS，失败为错误描述  |
|    result|   String| 	结果  |
|    result.user_phone|   String| 	用户的手机号  |
|    result.user_public_key|   String| 	用户的公钥  |
|    result.user_ontid|   String| 	用户的ontid  |



## 支付/调用合约接口
参考[cynao](https://dev-docs.ont.io/#/docs-en/Cyano/Cyano-provider/02-scan-qrcode)

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
| 61011	|	VERIFY_CODE_FREQUENT,验证码请求过于频繁
| 61012	|	VERIFY_CODE_ERROR,验证码错误
| 61013	|	VERIFY_CODE_EXPIRES,验证码已过期
| 61024	|	INVALID_PASSWORD,密码错误
| 61030	|	ONTID_LOCKED,ONT ID 已经锁住
| 61031	|	DECODE_ERROR,解密失败
| 61032	|	ENCODE_ERROR,加密失败
| 61033	|	GEETEST_ERROR,Gee校验失败
| 61034	|	TRANSACTION_PARAM_ERROR,交易参数错误
| 61035	|	ORDER_NOT_EXIST,订单不存在
| 61036	|	ORDER_EXPIRED,订单已过期
| 61037	|	ACCOUNT_NOT_EXIST,钱包不存在
| 61038	|	QUERY_BALANCE_FAIL,查询余额失败
| 61039	|	TRANSACTION_PAYER_ERROR,交易付款人错误
| 61040	|	REPEATED_REQUESTS_ERROR,重复的请求
| 61041	|	DDO_NOT_EXIST,DDO不存在
| 61042	|	DEVELOPER_NOT_EXIST,developer不存在
| 61042	|	DEVELOPER_NOT_EXIST,developer不存在
| 61043	|	ONTID_NOT_EXIST,ONT ID不存在
| 61044	|	PASSWORD_NOT_EXIST,密码不存在
| 61045	|	PUBLIC_KEY_NOT_EXIST,公钥不存在
| 61046	|	PRE_TRANSACTION_FAIL,预执行失败
| 62001	|	VERIFY_FAIL,身份校验失败	
| 62002	|	CREATE_FAIL,创建失败	
| 62003	|	COMM_FAIL,通信异常	
| 62007	|	COMM_SMS_FAIL,SMS通信异常
| 62008	|	COMM_NET_FAIL,网络通信异常
| 62009	|	VERIFY_PROVIDE_FAILED,三方身份校验失败
| 62004	|	FILE_ERROR,文件操作异常	
| 62005	|	DB_ERROR,数据库操作错误
| 62006	|	SIG_VERIFY_FAILED,验签失败	
| 62015	|	TOKEN_TYPE_ERROR,token类型错误
| 63001	|	INNER_ERROR,内部异常	
| 63002	|	EXCEPTION,异常	
| 63003	|	CODE_VERIFY_FAILED,设备码校验失败	


## 对接文档

请参考 [对接指南](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/08-ontid_integration)。
