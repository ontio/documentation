# ONT ID托管设计概要和接口

## 设计背景

### 扩展应用场景
基础的ONT ID是基于密码学公私钥体系设计的非中心化账户体系。在更多的实际运用场景中，我们要求ONT ID的开通和管理需要扩展嵌入到各种场景，同时包括PC端、移动端等各种渠道，我们需要一个更完善、更接地气的综合账户体系，综合账户体系支持把数字身份、数字资产、中心账户一并管理和管理。为便于理解，以下列举部分非常典型和具体的场景应用： 
* 在AAPP Store PC端应用中，用户需要在PC页面中及时开通ONT ID；
* 在各种营销活动中，移动端H5页面随处需要开通ONT ID;
* 在一些移动端钱包中，可以支持用户使用WIF私钥导入创建ONTID；
* 在CandyBox应用中，ONT ID可以关联各种Candy，这些Candy是以中心化账户系统管理；
* 更多场景......

### 强化用户标志
同时，我们需要让用户对ONT ID更方便管理且更有辨识度，互联网用户将不必记忆自己复杂的WIF私钥或者Keystore , ONT ID将关联用户手机或者和第三方账户体系关联。 用户非常容易记忆和管理。

### 统一应用标准
以上的扩展应用方案，我们仍旧需要纳入ONT ID标准体系，便于用户在跨应用、跨终端使用。 比如，用户在AAPP Store中开通的ONT ID，仍旧可以导入到ONTO或者麦子钱包中去管理其资产和数据。

### 目标
ONT ID快速开通模式应用在H5或嵌入页面式的应用场景中，在这类场景中，用户的特点是无任何区块链背景知识，没有密钥管理经验；同时页面在微信/Facebook等社媒中传播，没有任何私钥管理的基础设施（没有集成CyanoMobile）。

### 数据安全
+ [HMAC校验](#HMAC校验)

三方使用我们注册服务需加上HMAC校验

+ [接口加密](#接口加密)

我们在项目中所有接口使用到RSA，AES128，以及MD5，用以保证客户端(Client)和服务端(Server)之间的通信安全。

+ [数据库加密](#数据库加密)

## ONTID综合账户管理接口
注意： 需要添加HMAC认证方案。
管理接口如下：
+ 注册ONT ID
    + [手机注册](#手机注册)
    + [keystore注册](#keystore注册)
+ 登录ONT ID
    + [手机验证码登录](#手机验证码登录)
    + [手机密码登录](#手机密码登录)
+ [导出](#导出)
+ 修改
    + [修改手机号](#修改手机号)
    + [修改密码](#修改密码)
+ [校验密码](#校验密码)
+ [获取验证码](#获取验证码)
+ [解密claim](#解密claim)
+ [获取注册交易](#获取注册交易)


### 手机注册
1. [获取验证码](#获取验证码)
2. 提交号码，验证码，密码
3. 返回ontid
```text
url：/api/v1/ontid/register/phone
method：POST
```

请求：
```json
{
	"number":"+86*15821703553",
	"verifyCode": "123456",
	"password":"123456"
}
```
| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    number|   String|  手机号码  |
|    verifyCode|   String|  手机验证码  |
|    password|   String|  设置密码  |

返回：
```json
{
	"action":"register",
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

### keystore注册
1. [获取验证码](#获取验证码)
2. 提交号码，验证码，keystore，keystore对应的密码
3. 返回ontid（该ontid和keystore的ontid一致）
```text
url：/api/v1/ontid/binding 
method：POST
```

请求：
```json
{
	"phone":"+86*15821703553",
	"verifyCode":"123456",
	"keystore":"keystore",
	"password":"123456"
}
```
| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    phone|   String|  手机号码  |
|    verifyCode|   String|  手机验证码  |
|    keystore|   String|  keystore  |
|    password|   String|  设置密码  |

返回：
```json
{
	"action":"binding",
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

### 手机验证码登录
1. [获取验证码](#获取验证码)
2. 提交号码，验证码
3. 返回ontid（该ontid和keystore的ontid一致）
```text
url：/api/v1/ontid/login/phone
method：POST
```

请求：
```json
{
	"phone":"+86*15821703553",
	"verifyCode": "123456"
}
```
| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    phone|   String|  手机号码  |
|    verifyCode|   String|  手机验证码  |

返回：
```json
{
	"action":"login",
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

### 手机密码登录
1. 提交号码，密码
2. 返回ontid
```text
url：/api/v1/ontid/login/password
method：POST
```

请求：
```json
{
    "phone":"+86*15821703553",
    "password": "123456"
}
```
| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    phone|   String|  手机号码  |
|    password|   String|  用户密码  |

返回：
```json
{
    "action":"login",
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
    "newPhone": "+86*15821703552",
    "verifyCode": "123456",
    "oldPhone":"+86*15821703553",
    "password":"123456"
}
```
| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    phone|   String|  手机号码  |
|    verifyCode|   String|  手机验证码  |

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
1. [获取验证码](#获取验证码)
2. 提交号码，旧密码，新的密码
3. 返回ontid（该ontid和原来的不一致）
```text
url：/api/v1/ontid/edit/password
method：POST
```

请求：
```json
{
    "phone":"+86*15821703553",
    "oldPassword":"123456",
    "newPassword":"12345678"
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

### 校验密码
1. 提交ontid和密码
2. 返回所需要的结果
```text
url：/api/v1/ontid/verify

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
    "action":"verify",
    "version":"1.0",
    "error":0,
    "desc":"SUCCESS",
    "result": true
}
```

| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    action|   String|  动作标志  |
|    version|   String|  版本号  |
|    error|   int|  错误码  |
|    desc|   String|  成功为SUCCESS，失败为错误描述  |
|    result|   bool| 成功返回true，失败返回false  |

### 获取验证码
```text
url : /api/v1/ontid/getcode/phone
method:POST
```

请求：
```json
{
    "number":"+86*15821703553"
}
```
| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    number|   String|  手机号码  |

返回：
```json
{
    "action":"getVerifyCode",
    "version":"1.0",
    "error":0,
    "desc":"SUCCESS",
    "result": true
}
```

| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    action|   String|  动作标志  |
|    version|   String|  版本号  |
|    error|   int|  错误码  |
|    desc|   String|  成功为SUCCESS，失败为错误描述  |
|    result|   bool|  发送结果（成功，失败）  |

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

### 获取注册交易
1. 通过ONT ID 和密码获取ONT ID交易内容
2. 返回所需要的结果
```text
url：/api/v1/ontid/gettx/register/ontid

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
    "action":"getTx",
    "version":"1.0",
    "error":0,
    "desc":"SUCCESS",
    "result": "交易内容"
}
```

| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    action|   String|  动作标志  |
|    version|   String|  版本号  |
|    error|   int|  错误码  |
|    desc|   String|  成功为SUCCESS，失败为错误描述  |
|    result|   String| 	交易内容  |

### HMAC校验
获取手机验证码接口我们加上了HMAC校验功能

用户需要提前在我们平台上注册

1. 前端处理

获取当前时间（秒为单位）得到字符串 requestTimeStamp

UUID随机得到字符串 nonce

对整个body进行MD5加密再转Base64获得字符串requestContentBase64String

拼接需要加密的内容
method:"POST"
> String rawData = AppId + method + requestPath + requestTimeStamp + nonce + requestContentBase64String;

用AppSecret对内容进行HMACSha256加密再转Base64得到字符串signature

拼接结果：
> ont:AppId:signature:nonce:requestTimeStamp
 
java示例：
 ```text
    private static String AppId = "";
    private static String AppSecret = "";
    
    String requestContentBase64String = "";
    byte[] payload = this.getBody();
    byte[] md5 = MD5Utils.MD5Encode(payload);
    requestContentBase64String = toBase64String(md5);
    
    Long tsLong = System.currentTimeMillis() / 1000;
    String requestTimeStamp = tsLong.toString();
                
    UUID uuid = UUID.randomUUID();
    String nonce = toBase64String(uuid.toString().getBytes());           
    
    String rawData = AppId + method + requestPath + requestTimeStamp + nonce + requestContentBase64String;
    String signature = toBase64String(HMACSha256.sha256_HMAC(rawData, AppSecret));
    String header = String.format("ont:%s:%s:%s:%s", AppId, signature, nonce, requestTimeStamp);
    //请求头
    headers.put("Authorization", header);
```
2. 后台HMAC校验

### 接口加密
 我们在项目中使用到RSA，AES128，以及MD5，用以保证客户端(Client)和服务端(Server)之间的通信安全。
1. RSA——非对称加密，会产生公钥和私钥，公钥在客户端，私钥在服务端。公钥用于加密，私钥用于解密。
2. AES——对称加密，直接使用给定的秘钥加密，使用给定的秘钥解密。(加密解密使用相同的秘钥)

> 客户端上传数据加密 ==> 服务器获取数据解密 ==> 服务器返回数据加密 ==> 客户端获取数据解密

+ 客户端上传数据加密 A
1. 客户端随机产生一个16位的字符串，用以之后AES加密的秘钥，AESKey。
2. 使用RSA对AESKey进行公钥加密，RSAKey。
3. 重要的接口需要加签处理。
4. 将明文的要上传的数据包(字典/Map)转为Json字符串，使用AESKey加密，得到JsonAESEncryptedData。
5. 封装为{key : RSAKey, value : JsonAESEncryptedData}的字典上传服务器，服务器只需要通过key和value，然后解析，获取数据即可。

+ 服务器获取数据解密 B
1. 获取到RSAKey后用服务器私钥解密，获取到AESKey
2. 获取到JsonAESEncriptedData，使用AESKey解密，得到明文的客户端上传上来的数据
3. 如果客户端进行了加签处理，此处需要验签，以保证数据在网络传输过程中是否被篡改

+ 服务器返回数据加密 C
1. 将要返回给客户端的数据(字典/Map)转成Json字符串，用AESKey加密处理
2. 如需要可以加签处理
3. 封装数据{data : value}的形式返回给客户端

+ 客户端获取数据解密 D
1. 客户端获取到数据后通过key为data得到服务器返回的已经加密的数据AESEncryptedResponseData
2. 对AESEncryptedResponseData使用AESKey进行解密，得到明文服务器返回的数据。

+ 加签处理(数据发起方都可以加签，此处是客户端)
1. 我们一般取其中的关键字段(别人可能修改的字段)，比如此时step，和time及memberId，都比较敏感。
2. 在上文的A中的第二步之后，获取step，time，memberId，拼接成一个字符串(顺序和服务器约定好)，然后使用md5加密，采用base64编码(编码格式和服务约定)。得到signData
3. 然后将获取到的signData以key-value的形式保存到原来明文的数据包中，然后进行A的第三步

+ 验签处理(数据接受方都可以验签，此处服务端)
1. 如上，到B的第三步，此时已经得到了客户端上传的明文数据
2. 按照喝客户端约定的字段拼接，将得到的step，time，memberId拼接后，使用同样的md5_base64处理，然后比较数据包中的签名sign是否和客户端当时的签名一致。
3. 如果一致，接受数据。不一致，抛弃数据，终止本次操作

> 假设加签之后的数据包被截获，然后解密成功，得到明文的数据包。但是签名md5加密是无法解密的(单向加密)。此时即时修改了step，然后post到服务器，服务器通过修改后的step，time，memberId得到的字符串经过md5加密后，一定会与客户端的签名不一致。从而数据被抛弃。

流程图描述上文

![流程图](%E6%8E%A5%E5%8F%A3%E5%8A%A0%E5%AF%86%E6%B5%81%E7%A8%8B%E5%9B%BE.jpg)

### 数据库加密
我们不会保存用户的密码，在数据库中存放的是密码的hash，校验数据是根据密码hash是否一致来判断。
