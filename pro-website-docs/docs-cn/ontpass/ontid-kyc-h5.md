
# 认证设计概要和接口

此文档为h5版本kyc dapp的流程设计和接口定义。（区别于之前依赖于Cyano provider的kyc dapp）

##  1. 认证商选择

为适应ontid宣传推广，会有不同的web环境，能够支持的方案是选择Shufti Pro.

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

4. 等待审核通过（测试环境一般10分钟内）

   [![kRqsu6.md.jpg](https://s2.ax1x.com/2019/02/21/kRqsu6.md.jpg)](https://imgchr.com/i/kRqsu6)

### 2.2 授权

1. 应用方在需要用户授权的地方，通过url跳转到KYC dapp h5（在url后附上参数，通过用户ONT ID查询到加密后claim），显示授权页面

2. 用户确认后，输入密码，发送请求到ONT ID后端进行解密

3. ONT ID后端验证密码正确后，通过托管的私钥解密claim，返回到KYC dapp h5

4. KYC dapp h5 发送授权信息到应用方后台后， 返回授权成功页面，用户可以点击返回到应用方。应用方调用自己后台接口获取授权结果。（需要应用方自行实现接收授权信息接口和验证授权接口）

   ![kRq2Ue.jpg](https://s2.ax1x.com/2019/02/21/kRq2Ue.jpg)

## 3. 接口定义

### 3.1 获取注册ONT ID交易

通过ONT ID 获取ONT ID交易内容

#### POST

```
url: /api/v1/ontid/gettx/register/ontid
```

### REQUEST

| Field_Name    | Required | Format                          | Description                            |
| ------------- | -------- | ------------------------------- | -------------------------------------- |
| ontid        | yes      | string | 手机号码（例如："+86*15821703553"）        |


### RESPONS

| Field_Name | Format | Description                                                  |
| ---------- | ------ | ------------------------------------------------------------ |
| version    | String | 版本号，目前是1.0。                                          |
| action     | String | 固定值：getTx。                                           |
| error      | int    | 错误码                                                       |
| desc       | String | 错误信息。成功即SUCCESS，其他即错误信息                      |
| result     | String  | 交易内容 |


### 3.2 请求ONT ID账户系统后台解密认证Claim

通过Onid和密码解密claim

#### POST

```
url: /api/v1/ontid/decrypt/claim
```

### REQUEST

| Field_Name    | Required | Format                          | Description                            |
| ------------- | -------- | ------------------------------- | -------------------------------------- |
| ontid        | yes      | string 20-255 characters Length | ontid（例如："did:ont:AcrgWfbSPxMR1BNxtenRCCGpspamMWhLuL"）        |
| password        | yes      | string 20-255 characters Length | 密码        |
| message        | yes      | JSONArray 3 Length | 加密后的数据        |


### RESPONSE

| Field_Name | Format | Description                                                  |
| ---------- | ------ | ------------------------------------------------------------ |
| version    | String | 版本号，目前是1.0。                                          |
| action     | String | 固定值：decrypt。                                           |
| error      | int    | 错误码                                                       |
| desc       | String | 错误信息。成功即SUCCESS，其他即错误信息                      |
| result     | String  | 解密后的内容 |

### 3.3 提交认证信息

调用ONT Pass接口https://documenter.getpostman.com/view/4781757/RznFoHaC#d7ddb4e7-150f-4b9a-a461-0c890fc2a5ed ，提交到ONT Pass后台审核。

（ONT Pass现在还需要在调用[Authentication Request](https://documenter.getpostman.com/view/4781757/RznFoHaC#5951d0a6-66a9-4234-b8a5-63e32b3189ec) 后触发认证的审核，可商定去掉该接口）

### 3.4 查询认证状态

应用方从ONTPass后台查询认证。

#### POST

```
url: /api/v1/ontpass/myclaims
```

### REQUEST

| Field_Name    | Required | Format                          | Description                            |
| ------------- | -------- | ------------------------------- | -------------------------------------- |
| nounce        | yes      | string 20-255 characters Length | 需保证唯一性                           |
| ontid         | yes      | string                          | 用户ONT ID                             |
| auth_template | yes      | string                          | 认证模板，默认：authtemplate_kyc01     |
| signature     | no       | string                          | 用户签名（值不能为空，可填任意字符串） |

### RESPONSE

| Field_Name | Format | Description                                                  |
| ---------- | ------ | ------------------------------------------------------------ |
| version    | String | 版本号，目前是1.0。                                          |
| action     | String | 固定值：MyClaims。                                           |
| error      | int    | 错误码                                                       |
| desc       | String | 错误信息。成功即SUCCESS，其他即错误信息                      |
| result     | Array  | 对象列表,每个对象字段见下表。如果数组为空，表示该ONT ID没有做认证；如果数组不为空，取数组第一个元素判断认证结果。 |

| Field_Name     | Format | Description                                  |
| -------------- | ------ | -------------------------------------------- |
| claim_context  | String | CLaim模板                                    |
| encrp_origdata | String | 加密数据                                     |
| txnhash        | String | 上链交易HASH                                 |
| create_time    | String | 生成时间                                     |
| issue_ontid    | String | 发行方ONTID                                  |
| auth_flag      | String | 一个字符，状态：0-pending, 1-fail, 2-success |

### 3.5 请求授权

应用方请求用户授权认证信息。

### POST

```
url: /api/vi/ontid/authorizationrequest
```

### REQUEST

| Field_Name     | Required | Format                          | Description                                     |
| -------------- | -------- | ------------------------------- | ----------------------------------------------- |
| nounce         | yes      | string 20-255 characters Length | 需保证唯一性                                    |
| owern_ontid    | yes      | string                          | 用户ONT ID                                      |
| dapp_ontid     | Yes      | String                          | dapp ONT ID                                     |
| encrp_origdata | String   | string                          | 加密数据                                        |
| password       | Yes      | string                          | 用户密码                                        |
| callback       | yes      | string                          | 应用方用来接收用户Claim，处理授权的后台回调地址 |

### RESPONSE

| Field_Name | Format  | Description                                                  |
| ---------- | ------- | ------------------------------------------------------------ |
| version    | String  | 版本号，目前是1.0。                                          |
| action     | String  | 固定值：RequestAuthorization。                               |
| error      | int     | 错误码                                                       |
| desc       | String  | 错误信息。成功即SUCCESS，其他即错误信息                      |
| result     | boolean | true：即请求成功，用户认证Claim已发送到callback； false：即请求失败 |

### 3.6 KYC dapp h5 发送用户Claim到应用方后台回调

#### POST

```
url	: /api/v1/ontid/sendclaimback
```

### REQUEST

| Field_Name  | Required | Format                          | Description             |
| ----------- | -------- | ------------------------------- | ----------------------- |
| nounce      | yes      | string 20-255 characters Length | 需保证唯一性            |
| owner_claim | yes      | string                          | 用户Claim 的JSON string |
| owner_ontid | Yes      | String                          | 用户的ONT ID            |

### RESPONSE

| Field_Name | Format  | Description                                                  |
| ---------- | ------- | ------------------------------------------------------------ |
| version    | String  | 版本号，目前是1.0。                                          |
| action     | String  | 固定值：RequestAuthorizationCallback。                       |
| desc       | String  | 错误信息。成功即SUCCESS，其他即错误信息                      |
| result     | boolean | true：即请求成功，用户认证Claim已发送到callback； false：即请求失败 |

