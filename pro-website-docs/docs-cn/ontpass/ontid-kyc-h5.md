
# KYC dapp h5对接

此文档为h5版本kyc dapp的对接文档。

##  1. 认证商选择

为了适应dapp会有不同的web环境，选择**Shufti Pro**作为认证商。

## 2. 认证和授权流程

流程中涉及到的多方如下：

- ONT ID账户体系前端和后端，以下简称ONT ID 前端和ONT ID 后端
- ONT Pass
- KYC dapp h5（包含认证和授权功能，可以在h5和钱包中打开）
- 场景方dapp（比如Candybox）

### 2.1 认证

1. 用户在ONT ID前端，使用手机号（或邮箱）注册ONT ID，ONT ID后台创建好注册ONT ID的交易并签名,并保存在数据库中

2. 在应用场景中触发认证请求，重定向到KYC dapp h5（在url后附上用户ONT ID），如果该ONT ID已认证，则显示ONT ID信息，如果未认证，走认证流程

3. KYC dapp调用ONT ID后端接口获取注册ONTID的交易，上传认证信息到ONT Pass（ONT Pass在审核通过后发送上链交易）；

4. 提交[认证请求](http://pro-docs.ont.io/#/docs-cn/ontpass/overview)到ONT Pass。这个请求需要认证需求方的签名，即应用方的签名。KYC dapp发送相关数据给应用方后台，应用方后台添加上自己签名后，提交认证请求到ONT Pass，返回结果给KYC dapp。

5.  KYC dapp显示等待审核页面。

   ![cert](https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/kyc/certification.jpg)

### 2.2 授权

1. 应用方在需要用户授权的地方，通过url跳转到KYC dapp h5（在url后附上参数，通过用户ONT ID查询到加密后claim），显示授权页面。

2. 用户确认后，输入密码，发送授权信息到应用方后台（请求数据使用ONT ID 账户体系后台公钥加密），应用方后台转发请求数据到ONT ID后台，得到解密后的Claim。

3. 应用方验证Claim，然后把验证结果，即授权结果，返回给KYC dapp，KYC dapp根据授权结果显示认证成功或失败。

   ![auth](https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/kyc/auth.jpg)


## 3. 应用方对接所需接口和链接

> KYC dapp url后可附带参数控制多语言，默认语言是英文。
>
> lang=en 语言为英文
>
> lang=zh 语言为中文

### 3.1 跳转到KYC dapp认证页面

```
url：host + /#/mgmtHome?ontid={ontid}&forwardCallback={transmitCallback}&requestAuthenticationCallback={requestAuthenticationCallback}
```

`ontid` User's ONT  ID

`forwardCallback` 应用方后台用于转发请求的回调地址

`requestAuthenticationCallback` 应用方后台用于提交认证请求的回调地址

### 3.2 跳转到KYC dapp授权页面

```
url: host + /#/authHome?userOntid={userOntid}&dappOntid={dappOntid}&dappName={dappName}&dappUrl={dappUrl}&callback={callback}
```

`userOntid` User's ONT ID

`dappOntid` dApp's ONT ID

`dappName` dApp's name

`dappUrl` 授权成功后跳转回dapp的地址

`callback` dapp后台用来接收授权信息的回调地址。

## 4. 应用方需要提供的接口

### 4.1 转发KYC dapp的请求

ONT ID后台的访问需要通过HMAC校验。KYC dapp不能直接访问ONT ID后台接口，所以需要通过应用方提供的接口转发请求。

应用方收到请求后，转发请求到ONT ID后台。需要对转发请求做HMAC处理。转发的地址是参数中的targetUrl。

### POST

```
url: 由应用方传给KYC dapp(比如http://host+ /forwardRequest)
```

### REQUEST

| Field_Name | Required | Format | Description                            |
| ---------- | -------- | ------ | -------------------------------------- |
| message    | Yes      | String | 需要转发的接口（ONT ID后台提供的接口） |
| data       | Yes      | String | 使用RSA/AES加密后的参数                |
| action     | Yes      | String | 固定值。ForwardRequest                 |

### RESPONSE

| Field_Name | Format | Description                             |
| ---------- | ------ | --------------------------------------- |
| version    | String | 版本号，目前是1.0。                     |
| action     | String | 固定值：TransmitRequest。               |
| desc       | String | 错误信息。成功即SUCCESS，其他即错误信息 |
| result     | String | ONT ID后台返回的结果                    |

### 4.2 处理授权请求回调

授权时，用户发送授权信息（使用ONT ID后台公钥加密的）给应用方后台。应用方转发给ONT ID后台解密，得到Claim，对Claim验证，验证成功，则授权成功。返回授权结果给KYC dapp。

### POST

```
url: 由应用方传给KYC dapp(比如http://host + /handleAuth)
```

### REQUEST

| Field_Name | Required | Format | Description                                                  |
| ---------- | -------- | ------ | ------------------------------------------------------------ |
| targetUrl  | yes      | String | ONT ID 后台用来解密数据的接口                                |
| data       | yes      | string | 使用ONT ID后台公钥加密的请求数据。解密后内容为：                    {message: 'xxxx', password: '', ontid: 'did:ont:Axxxxxxx'} |
| action     | yes      | string | 固定值。HandleAuthorization                                  |

### RESPONSE

| Field_Name | Format | Description                             |
| ---------- | ------ | --------------------------------------- |
| version    | String | 版本号，目前是1.0。                     |
| action     | String | 固定值：RequestAuthorizationCallback。  |
| desc       | String | 错误信息。成功即SUCCESS，其他即错误信息 |
| result     | String | 应用方后台验证授权Claim的结果。         |

### 4.3 应用方提交认证请求

> 目前测试环境，由KYC dapp提交认证请求；生产环境由应用方后台提交认证请求。

应用方后台对认证数据签名，并发送认证请求到ONT Pass。

### POST

由应用方传递给KYC dapp.例如：

```
https://host + /sendAuthenticationRequestCallback
```

### REQUEST

| Field_Name | Required | Format | Description |
| ---------- | -------- | ------ | ----------- |
| auth_id    | yes      | String | 认证的id    |

### RESPONSE

| Field_Name | Format | Description                                 |
| ---------- | ------ | ------------------------------------------- |
| version    | String | 版本号，目前是1.0。                         |
| action     | String | 固定值：RequestAuthenticationCallback       |
| desc       | String | 错误信息。成功即SUCCESS，其他即错误信息     |
| result     | String | 提交的结果。true：提交成功；false：提交失败 |

KYC dapp发送给应用方后台的数据如下：

```
{
    auth_id: '' // 代表一次认证的唯一id
}
```

应用方后台构造数据如下：

```
{
    auth_id: '',
    app_ontid: ''
}
```

应用方对构造的数据签名，并将得到的签名添加到上一步构造的数据中，如下：

```
{
    auth_id: '',
    app_ontid: '',
    app_signature: ''
}
```

应用方后台发送上面的数据到ONT Pass，提交认证请求。请求具体内容见[文档](https://documenter.getpostman.com/view/4781757/RznFoHaC#5951d0a6-66a9-4234-b8a5-63e32b3189ec)。返回给KYC dapp结果。

## 5. ONT ID后台需要提供的接口

> 注意：ONT ID接口接收的参数都是RSA/AES加密的。以下为接口说明中参数为解密后的参数。

### 5.1 获取注册ONTID的交易

通过ONT ID 获取ONT ID交易内容

#### POST

```
url: /api/v1/ontid/gettx/register/ontid
```

### REQUEST

| Field_Name | Required | Format | Description  |
| ---------- | -------- | ------ | ------------ |
| ontid      | yes      | string | 用户的ONT ID |


### RESPONS

| Field_Name | Format | Description                             |
| ---------- | ------ | --------------------------------------- |
| version    | String | 版本号，目前是1.0。                     |
| action     | String | 固定值：getTx。                         |
| error      | int    | 错误码                                  |
| desc       | String | 错误信息。成功即SUCCESS，其他即错误信息 |
| result     | String | 交易内容                                |

### 5.2 解密Claim

通过Onid和密码解密claim

#### POST

```
url: /api/v1/ontid/decrypt/claim
```

### REQUEST

| Field_Name | Required | Format                          | Description                                                 |
| ---------- | -------- | ------------------------------- | ----------------------------------------------------------- |
| ontid      | yes      | string 20-255 characters Length | ontid（例如："did:ont:AcrgWfbSPxMR1BNxtenRCCGpspamMWhLuL"） |
| password   | yes      | string 20-255 characters Length | 密码                                                        |
| message    | yes      | JSONArray 3 Length              | 加密后的数据                                                |


### RESPONSE

| Field_Name | Format | Description                             |
| ---------- | ------ | --------------------------------------- |
| version    | String | 版本号，目前是1.0。                     |
| action     | String | 固定值：decrypt。                       |
| error      | int    | 错误码                                  |
| desc       | String | 错误信息。成功即SUCCESS，其他即错误信息 |
| result     | String | 解密后的内容                            |