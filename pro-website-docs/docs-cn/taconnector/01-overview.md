
## 什么是信任锚

信任锚Trust Anchor是指在本体生态上提供认证服务的合作方，其可能是政府机关、大学、银行、第三方认证服务机构（比如CA机构）、生物识别科技公司等等，这些企业为本体ONT ID的持有者（Owner）提供多维度的认证，并第一时间通过Ontology BlockChain来记录认证行为和认证结果HASH，从而为用户认证需求方/场景方提供了标准化、可信的认证方式。

## 如何使用 Trust Anchor Connector

Trust Anchor Connector(简称TAConnector)是一个技术接入组件，帮助信任锚快速接入本体信任生态。

## 工作原理

 ![](http://assets.processon.com/chart_image/5a92d69de4b0874437cfe5f3.png)

## 准入规则

作为本体信任锚，除了技术接入以外，需要遵守包括不限于以下条款：

- 信任锚如果没有相应资质或用户许可，不可留存任何用户数据。
- 信任锚在其官方网站上公布将作为本体的身份识别、认证服务提供者（Verify Provider），并指定其注册的OntID。
- 信任锚应保证其用户信息准确性与真实性。本体团队对信任锚提交的用户信息的真实性不承担责任。因用户信息虚假、不完整，而导致有关法律文件的效力瑕疵，本体团队不承担责任，有关责任由信任锚自行向其用户或第三人承担。
- 信任锚具备身份识别、认证管理配置能力，原则性要求如下，指标性要求可以由甲方根据具体服务要求来具体指定。
- 具有身份识别、认证需要的硬件和网络设施；
- 具有一定的安全防护标准；
- 部署身份识别、认证管理软件，本体将开源标准软件代码；
- 基于身份识别、认证的管理流程，信任锚将提供包括不限于以下的可信申明服务
  - 可信申明的颁发；
  - 可信申明的吊销；
  - 以官方域名 URL 对外开放可信申明验证服务。

## 收费机制

TrustAnchor默认使用ONG作为计费方式，也可以使用法定货币作为计费方式，收费信息将登记到ONTPass。



## 对接ONTPass平台

#### Request Header

`TrustAnchor`请求`ONTPass`服务时需要进行身份鉴权，目前使用HMAC校验，鉴权信息需保存在http请求头的`Authorization`里，格式为`hmac: hmac值`。`TrustAnchor`注册时`ONTPass`会返回一对`appId`和`appKey`，用于后续身份鉴权，`TrustAnchor`需保存好该信息，防止泄露。

#### HTTP Codes

| Http code | Http message | Description                  |
| --------- | ------------ | ---------------------------- |
| 200       | OK           | 成功                         |
| 400       | Bad Request  | 参数缺失或错误               |
| 401       | Unauthorized | header缺失鉴权信息或鉴权失败 |
| 404       | Not found    | 资源未发现                   |
| 500       | Server Error | 内部异常                     |

#### Response body

```javascript
{
    "msg":"Register",
	"code":0,
	"result":{}
}
```

| ResponseField | Type   | Description              | Necessary |
| ------------- | ------ | ------------------------ | --------- |
| msg           | String | 描述                     | Y         |
| code          | int    | 错误码。0:成功 其他:异常 | Y         |
| result        | Object | 返回内容                 | Y         |



### 1.TrustAnchor注册API

`TrustAnchor`接入`ONTPass`时需要注册自己的基本信息及提供的认证服务信息，`ONTPass`会展示各个`TrustAnchor`提供的认证服务信息，供认证需求方在进行认证时选择。

- TA注册完后默认为待审核状态，后台审核成功后才能查询到。

```javascript
Host：域名+/v1/trustanchors
Method：POST /HTTP/1.1
Content-Type: application/json
RequestExample：
{
    "logo":"http://authentication-sd/pic/logo.png",
	"description": "coinwallet",
	"name": "coinwallet",
	"contact_info":"{\"website\":\"\",\"phone\":\"121221\"}",
	"ontid": "did:ont:AXXxiWCuJXmuPGnsBji4cqWqV1VrKx8nkM",
    "address":"AXXxiWCuJXmuPGnsBji4cqWqV1VrKx8nkM",
    "request_endpoint":"https://auth.com/v1/kyc",
    "auth_info":[
        {
            "claim_context":"claim:sfp_idcard_authentication",
            "claim_description":"shuftipro身份证认证可信声明",
            "claim_price":"0.3"
        }
    ]
}

SuccessResponse：
{
	"msg":"",
	"code":0,
	"result":true
}
```

>为保证数据传输安全性，TrustAnchor注册的认证接口必须是https+域名形式，同时TrustAnchor需保证注册的认证接口高可用性且接受ONTPass标准的https的post请求



| RequestField            | Type    | Description                                         | Necessary |
| ----------------------- | ------- | --------------------------------------------------- | --------- |
| description             | String  | TrustAnchor的描述                                   | Y         |
| name                    | String  | TrustAnchor的名称                                   | Y         |
| ontid                   | String  | TrustAnchor的ONT ID                                 | Y         |
| address                 | Striing | 收款地址                                            | Y         |
| request_endpoint        | String  | 认证请求的接口url定义                               | Y         |
| logo                    | String  | logo的url地址                                       | Y         |
| contact_info            | String  | 联系信息。json格式字符串                            | Y         |
| auth_info.claim_context | String  | 可信声明模板标识                                    | Y         |
| auth_info.description   | String  | 可信声明描述                                        | Y         |
| auth_info.price         | String  | 对应的认证费用，单位ong。月结模式的话走线下对账模式 | Y         |

### 2.TrustAnchor信息更新 API

`TrustAnchor`可以调用该API更新原来注册的信息。

- 需要使用`hmac`做身份鉴权

```javascript
Host：域名+/v1/trustanchors/{ontid}
Method：PUT /HTTP/1.1
Content-Type: application/json
RequestExample：
{
    "logo":"http://authentication-sd/pic/logo.png",
	"description": "coinwallet",
	"name": "coinwallet",
	"contact_info":{"website":"","phone":"121221"},
    "request_endpoint":"https://auth.com/v2/kyc",    
    "auth_info":[
        {
            "claim_context":"claim:sfp_idcard_authentication",
            "claim_description":"shuftipro身份证认证可信声明",
            "claim_price":"0.2"
        }
    ]
}

SuccessResponse：
{
	"msg":"",
	"code":0,
	"result":true
}
```



| UrlRequestField | Type   | Description         | Necessary |
| --------------- | ------ | ------------------- | --------- |
| ontid           | String | TrustAnchor的ONT ID | Y         |



| RequestField            | Type   | Description                                         | Necessary |
| ----------------------- | ------ | --------------------------------------------------- | --------- |
| description             | String | TrustAnchor的描述                                   | Y         |
| name                    | String | TrustAnchor的名称                                   | Y         |
| logo                    | String | logo                                                | Y         |
| contact_info            | String | 联系信息                                            | Y         |
| auth_info.claim_context | String | 可信声明模板标识                                    | Y         |
| auth_info.description   | String | 可信声明描述                                        | Y         |
| auth_info.price         | String | 对应的认证费用，单位ong。月结模式的话走线下对账模式 | Y         |



### 3.TrustAnchor信息查询 API

可以调用该API查询`ONTPass`平台注册并审核通过的`TrustAnchor`信息

```javascript
Host：域名+/v1/trustanchors
Method：GET /HTTP/1.1
Content-Type: application/json
RequestExample：

SuccessResponse：
{
	"msg":"",
	"code":0,
	"result":[
        {
            "ontid": "did:ont:AXXxiWCuJXmuPGnsBji4cqWqV1VrKx1111",
            "description": "coinwallet",
            "name": "coinwallet",
            "address": "1212",
            "contact_info": "{\"website\":\"\",\"phone\":\"121221\"}",
            "logo": "11",
            "auth_info": [
                {
                    "claim_context": "claim:11_idcard_authentication",
                    "ontid": "did:ont:AXXxiWCuJXmuPGnsBji4cqWqV1VrKx1111",
                    "claim_description": "shuftipro身份证认证可信声明",
                    "claim_price": 0.3
                }
            ]
        }
    ]
}
```



| ResponseField           | Type    | Description             | Necessary |
| ----------------------- | ------- | ----------------------- | --------- |
| description             | String  | TrustAnchor的描述       | Y         |
| name                    | String  | TrustAnchor的名称       | Y         |
| ontid                   | String  | TrustAnchor的ONT ID     | Y         |
| address                 | Striing | 收款地址                | N         |
| logo                    | String  | logo                    | Y         |
| contact_info            | String  | 联系信息                | Y         |
| auth_info.claim_context | String  | 可信声明模板标识        | Y         |
| auth_info.description   | String  | 可信声明描述            | Y         |
| auth_info.price         | String  | 对应的认证费用，单位ong | Y         |
| auth_info.ontid         | String  | TrustAnchor的ONT ID     | Y         |



### 4.TrustAnchor认证结果回调

`TrustAnchor`完成kyc认证后，需要将kyc认证结果通过该接口使用Http请求回调给`ONTPass`

- 需要进行Hmac身份鉴权

```java
Host：域名+/v1/trustanchors/kyc-result
Method：POST /HTTP/1.1
Content-Type: application/json
RequestExample：
{
	"auth_flag":true,
	"ta_ontid":"did:ont:AEnB1v4zRzepHY344g2K1eiZqdskhwGuN3",
    "claim_context":"claim:sfp_passport_authentication",    
    "encrp_origdata":"eyJraWQiOiJkaWQ6b250OkFQYzh....7bJuxky33SBWdKl4Xg=",
    "tx_hash":"d97b479f69a86a52ccf846e1df2fb301137d828c952bfe9d15db3d197d97ju79",
    "description":"",
    "message_key":"dFsT7I5reQIt_did:ont:AMw4LnBZ9qsbo8dizRME4e9nTiCNtRdubd"
}

SuccessResponse：
{
	"msg":"",
	"code":0,
	"result":true
}

```



| ResponseFiled  | Type    | Description                                                  |
| -------------- | ------- | ------------------------------------------------------------ |
| auth_flag      | boolean | 认证结果  true：认证通过   false：认证未通过                 |
| ta_ontid       | string  | Trustanchor的ONT ID                                          |
| claim_context  | string  | 可信声明模板                                                 |
| encrp_origdata | string  | 用户可信声明。若认证失败，则为空字符串                       |
| tx_hash        | string  | 存证交易hash。若认证失败，则为空字符串                       |
| description    | string  | 描述。认证失败为失败原因                                     |
| message_key    | string  | message_key。由认证时ONTPass传入，认证完成后回调需要传入该值 |



### 错误码字典

| Field | Type | Description                                                  |
| :---- | :--- | :----------------------------------------------------------- |
| 0     | int  | SUCCESS. 成功                                                |
| 61001 | int  | FAIL, param error. 参数错误                                  |
| 61002 | int  | FAIL, already exist. 已存在                                  |
| 61003 | int  | FAIL, not found. 未找到                                      |
| 61012 | int  | claim context already exist. 可信声明模板已存在              |
| 61013 | int  | claim context not found. 可信声明模板不存在                  |
| 61014 | int  | trustanchor not match the claim context. Trustanchor和可信声明模板不匹配 |
| 61015 | int  | country not match claim context.国家与认证模板不匹配         |
| 62001 | int  | authentication request time exceed limit.认证请求次数超限    |
| 62003 | int  | FAIL, communication fail.通信异常                            |
| 62007 | int  | FAIL, need authorization header.需要身份认证Header           |
| 62008 | int  | FAIL, authorization fail.身份认证失败                        |
| 63001 | int  | FAIL, inner error.内部异常                                   |



## HMAC校验

### 说明

#### 什么是 HMAC Authentication？

HMAC Authentication 是在客户端和服务端共享一个秘密，然后客户端通过哈希函数散列发送的内容加上秘密，服务端使用同样的方法对内容和秘密进行散列，然后对比结果，如果相同则可以相信客户端是可信的。

客户端流程：

首先服务器需要提供给客户端 APP Id 和 APP Key。

1. 构造需要哈希的 data ，包括（APP Id, HTTP method, request URI, request time stamp, nonce, and Base 64 string representation of the request payload）
2. 客户端使用哈希函数（SHA256）来生成一个签名。
3. 签名会被放在 Authorization header，设置一个 schema（hmac:ont:）。请求头的key 是 Authorization， value 是hmac:ont:APPId:Signature:Nonce:Timestamp。
4. 客户端发送数据和 Authorization header。

> request time stamp 需要使用 `UNIX time`，这样服务器和客户端在不同的时区也没问题。nonce 是一个随机值，可以和 request time stamp 一起用来防止[重放攻击](https://en.wikipedia.org/wiki/Replay_attack)

> Base 64 string representation of the request payload ：用 MD5 先hash一遍请求的payload，再把 hash 后的内容转成 Base 64 string



#### 客户端发送数据伪代码

首先要构造 http 协议头部的 `Authorization` 参数的方法

``` C#
function GenerateAlgorithm (payload) => {
  if(!payload) {
      requestContentBase64String = null;
  } else {
      requestContentBase64String = base64(MD5(payload))
  }

  // 按照一定的顺序构造需要签名的字符串
  rawData =  appId + requestHttpMethod + requestUri + requestTimeStamp + nonce + requestContentBase64String

  // 使用约定好的算法哈希需要签名的内容，哈希后的内容需要转成 Base64String
  HmacSHA256.initHmac(secret, length)
  signature = base64(HmacSHA256.ComputeHash(rawData))

  // 构造 http 协议头部的 Authorization 参数，注意 schema 是约定好的hmac，各个参数用 : 分割，花括号是C#的 String Format语法，{0} 表示占据第0个位置。
  header = string.Format("hmac:ont:{0}:{1}:{2}:{3}", APPId, signature, nonce, requestTimeStamp)
}
```

构造好后发送请求

``` js
// 发送 http 或者 https 的请求到服务器
client.send(header, payload)
```



### Demo

#### java

- 签名

  ```java
      public static void main(String[] args){
          String appId = "6Xj8aS01";
          String appKey = "R3VUd0JWu2wEcAgYruBBEDC8HkUMMs==";
          //http request method
          String method = "POST";
          //http request uri
          String requestUri = "/v1/kyc-data";
          //http request body
          JSONObject obj = new JSONObject();
          obj.put("auth_id","6666666666666666666666666");
          obj.put("ar_ontid","did:ont:A9JG4rRMXgCNQCwFKCe1v9fx7mQPhXg9N");
          obj.put("ta_ontid","did:ont:AH87GYANf6XHnBL64hT3RBfnQJbpNCR0L");
          obj.put("owner_ontid","did:ont:AMw95nBZ9qsbo8dizRME4e9nTiCNtRdu");
          obj.put("claim_context","claim:sfp_passport_authentication");
          obj.put("country","AU");
          obj.put("name","");
          obj.put("doc_type","passport");
          obj.put("doc_id","");
          String str = "123123";
          obj.put("front_doc",str);
          obj.put("back_doc","");
  
          try {
              String bodyStr = obj.toJSONString();
              String bodyMD5Base64Str = encode(MD5Encode(bodyStr));
              System.out.println("bodyMD5Base64Str:" + bodyMD5Base64Str);
  
              String nonce = encode(UUID.randomUUID().toString().getBytes(StandardCharsets.UTF_8));
              Long tsLong = System.currentTimeMillis() / 1000L;
              String requestTimeStamp = tsLong.toString();
              //make rawdata
              String rawData = appId + method + requestUri + requestTimeStamp + nonce + bodyMD5Base64Str;
              //signature
              String signature = encode(sha256_HMAC(rawData, appKey));
              //make hmac schema
              String hmacData = String.format("ont:%s:%s:%s:%s", appId, signature, nonce, requestTimeStamp);
              System.out.println("hmac:" + hmacData);
          }catch (Exception e){
              e.printStackTrace();
          }
      }
  
      public static byte[] sha256_HMAC(String message,
                                       String secret) throws Exception {
          Mac sha256_HMAC = Mac.getInstance("HmacSHA256");
          SecretKeySpec secret_key = new SecretKeySpec(secret.getBytes(StandardCharsets.UTF_8), "HmacSHA256");
          sha256_HMAC.init(secret_key);
          return sha256_HMAC.doFinal(message.getBytes(StandardCharsets.UTF_8));
      }
  
      public static byte[] MD5Encode(String origin) throws Exception{
          try {
              MessageDigest md = MessageDigest.getInstance("MD5");
              byte[] rs = md.digest(origin.getBytes("utf-8"));
              return rs;
          } catch (Exception e) {
              e.printStackTrace();
              throw e;
          }
      }
  
      public static String encode(byte[] src) throws UnsupportedEncodingException {
          byte[] encodeBytes = Base64.getEncoder().encode(src);
          return new String(encodeBytes);
      }
  ```

- 验签

  ```java
      public static void main(String[] args){
  
          String appId = "6Xj8aSGC";
          String appKey = "R3VUd0JWu2wEcAgYruBBEDC8HkUMwQ==";
          //http request method
          String method = "POST";
          //http request uri
          String requestUri = "/v1/kyc-data";
          String hmacData = "ont:6Xj8aSGC:/j9j0oQOJNgodJBmt2LVcVcGH7UOr5BdK6n3MHnF2JE=:YTQxNjMyMDMtYTBhYi00YmYxLTlhOWItNWEwOGJlMzJmZGMy:1563257304";
          String bodyMD5Base64Str = "e3b+nSiakg+3/CjKe51y1w==";
          String appkey = "R3VUd0JWu2wEcAgYruBBEDC8HkUMwQ==";
  
          try {
              verify(hmacData, method, requestUri, bodyMD5Base64Str, appKey);
          } catch (Exception e) {
              e.printStackTrace();
          }
      }
  
      public static void verify(String hmacData,
                         String method,
                         String requestUri,
                         String bodyMD5Base64Str,
                         String AppSecret) throws Exception {
  
          String[] hmacDataArray = hmacData.split(":");
          if (hmacDataArray.length != 5) {
              throw new Exception("length size incorrect.");
          }
  
          // parse header
          String tag = hmacDataArray[0];
          String appId = hmacDataArray[1];
          String signature = hmacDataArray[2];
          String nonce = hmacDataArray[3];
          String requestTimeStamp = hmacDataArray[4];
  
          // verify schema
          if (!tag.equals("ont")) {
              throw new Exception("tag incorrect.");
          }
  
          // verify expire time
          long expireDate = Long.parseLong(requestTimeStamp) * 1000 + 86400000;  // 86400000ms = 24h
          if (new Date(expireDate).before(new Date())) {
              throw new Exception("expired.");
          }
  
          // make rawdata
          String rawData = appId + method + requestUri + requestTimeStamp + nonce + bodyMD5Base64Str;
          //signature
          String localSignature = Base64ConvertUtil.encode(sha256_HMAC(rawData, AppSecret));
          if (!localSignature.equals(signature)) {
              throw new Exception("verify failed.");
          } else {
              System.out.println("verify success!");
          }
      }
  
      public static byte[] sha256_HMAC(String message,
                                       String secret) throws Exception {
          Mac sha256_HMAC = Mac.getInstance("HmacSHA256");
          SecretKeySpec secret_key = new SecretKeySpec(secret.getBytes(StandardCharsets.UTF_8), "HmacSHA256");
          sha256_HMAC.init(secret_key);
          return sha256_HMAC.doFinal(message.getBytes(StandardCharsets.UTF_8));
      }
  ```

  

  

