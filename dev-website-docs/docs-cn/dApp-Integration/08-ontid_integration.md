

ONT ID 开放平台为第三方应用提供第三方登录、支付、智能合约执行、KYC等服务，请按照以下步骤开始应用集成。


## 准备工作


在进行 ONTID 授权登录接入之前，应用方需要先在 ONTID 开放平台注册 ONTID ，获得相应的 ONTID 和 ```PrivateKey```，申请 ONTID 通过审核后，可开始接入流程。也可以向我们工作人员申请测试网的 ONTID 和 ```PrivateKey```。

对接前请确保登录和支付页面能正常访问：

* ONTID 登录页面：主网 [https://signin.ont.io/#/](https://signin.ont.io/#/)，测试网 [http://139.219.136.188:10390/](http://139.219.136.188:10390/)




## 快速对接


对接包括前端对接和服务器对接。前端对接主要是对接登录和支付页面，后台对接主要是对接发起订单请求和订单查询。


* 第三方应用前端演示： [http://139.219.136.188:10391/#/](http://139.219.136.188:10391/#/)，[源码](https://github.com/ontio-ontid/ontid-app-demo)
* 第三方应用服务器例子： [app-server 源码](https://github.com/ontio-ontid/ontid-app-server)

### 前端对接登录页面

ONT ID 登录集成有两种方式：通过跳转到特定URL，和页面集成插件`plugin.js`。这里介绍的是快速对接的方式。页面集成插件的方式见下文。


 ```
 http://139.219.136.188:10390/signin?params={value}
 value = window.encodeURIComponent(appontid + '&' + appname + '&' + callback_url + '&' + lang)
 ```

 ```lang``` 是设定页面的语言，en表示英文，zh表示中文。
 ```appontid``` 是应用方的 ontid。
 ```appname``` 是应用方的 名字。

> 用户登录成功后，登录的返回信息会作为参数附在应用方回调地址`callback_url`后，传递给应用方。
>
> 返回信息是经过`encodeURIComponent(JSON.stringify(response))`处理的。应用方需要逆向操作得到实际的返回信息。返回信息的结构如下：
>
> ```json
> {
>   "access_token": "",
>   "ontid": "",
>   "refresh_token":  ""
> }
> ```
>
> 应用方得到 ```access_token```可以查询用户的信息，应用方需要保存用户的资产地址信息，支付时候需要使用

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
    "ontid": "did:ont:AcrgWfbSPxMR1BNxtenRCCGpspamMWhLuL",
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

您可以使用快速对接的方式，详情见上文。

这里介绍的是使用js插件的方式。


1. 页面引入```plugin.js```

   > 目前`plugin.js`放在[github](<https://github.com/ontio-ontid/ontid-app-demo/blob/master/public/plugin.js>)上，以后我们会放到CDN上。

2. 页面添加 meta 标签，填写应用方的ONT ID。```<meta name="ontid-signin-client_ontid" content="YOUR_CLIENT_ONTID.apps.ontid.com">```

3. 页面添加 ONTID 的Sign In 按钮。``` <div class="ontid-signin" data-onsuccess="onSignIn"></div> ```

4. 在登录成功后，触发回调onSignIn,发送 ```JWT token``` 到应用方后台。

```
    //get JWT token
    function onSignIn(result) {
      const {access_token, ontid, refresh_token} = result
      ...
       //sent to the  Website Application back end
        var xhr = new XMLHttpRequest();
        xhr.open('POST', 'https://yourbackend.example.com/tokensignin');
        xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
        xhr.onload = function() {
          console.log('Signed in as: ' + xhr.responseText);
        };
        xhr.send('idtoken=' + id_token);
    }
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
|    result|   String| 	结果返回：  |



## 使用ONT ID接入第三方平台授权登录

### 什么是ONT ID第三方授权登录？

第三方授权登录是非常流行的快速登录应用的方式，能简易用户的注册登录流程。

各种主流的社交应用都开放了这个功能，方便应用方集成。

为了免除应用方需要重复繁琐地接入不同的第三方，并且帮助应用方导流不同的ONT ID用户。我们提供了ONT ID第三方授权登录。

现在已经支持：微信，Facebook。

以后将支持更多第三方，如：QQ，微博，Google，Twitter等。

### 接入流程

[![V9GyCT.md.png](https://s2.ax1x.com/2019/05/22/V9GyCT.md.png)](https://imgchr.com/i/V9GyCT)

### 准备工作

应用方需要先到ONT ID开放平台注册ONT ID。需要提供应用的名称，logo图片等信息。

### 接入步骤

#### 1. 应用方在页面上放置登录按钮。

根据需要放置不同第三方的登录按钮。

#### 2. 添加登录按钮的点击事件

登录按钮点击后跳转到以下链接

```
${ontid_host}/oauthmiddle?dapp_ontid=${dapp_ontid}&oauth_type=${provider}&redirect_url=${redirect_url}&lang=${lang}`
```

`ontid_host` ONT ID 前端项目地址。测试环境：`http://139.219.136.188:10390`，  正式环境：`http://onchain.com`。

`dapp_ontid` 应用方的ONT ID。

`provider` 授权的第三方。可选的值有：`wechat`, `facebook`

`redirect_url` 应用方的回调地址。授权登录后会重定向到该回调地址，并在后面附上用户的`access_token`

`lang` 页面的语言。可选的值有：`en`, `zh`

### 3. 验证回调地址得到的access_token

`access_token`是`JWT`格式的。包含ONT ID后台的签名。 需要将`access_token`发送到应用方后台验证。验证通过后，登录流程完成。

关于`access_token`的具体内容，请参考[JWT Token 格式说明？](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/08-ontid_integration?id=jwt-token-%e6%a0%bc%e5%bc%8f%e8%af%b4%e6%98%8e%ef%bc%9f)

关于验证`access_token`的方式，请参考[java示例](<https://github.com/ontio-ontid/ontid-app-server/blob/master/src/main/java/com/github/ontid_demo/util/MyJWTUtils.java>)

### demo与示例

[demo源码](<https://github.com/ontio-ontid/oauth-login-demo>)

链接：http://139.219.136.188:10392

> 要体验微信登录，请在微信客户端内打开该链接
>
> 要体验其它登录方式，请在浏览器中打开该链接



## 后台错误码


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