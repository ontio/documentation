
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

4. 提交[认证请求](http://pro-docs.ont.io/#/docs-cn/ontpass/overview)到ONT Pass。这个请求需要认证需求方的签名，即用户的签名，也就需要用户输入密码。KYC dapp将获取签名的请求数据，用ONT ID后台提供的公钥加密，再发送给应用方后台，应用方后台然后附加上HMAC校验，转发给ONT ID账户体系后台。

5.  KYC dapp先将获取到的签名合并到请求数据中，发送给ONT Pass，触发认证请求。

6. 等待审核通过（测试环境一般10分钟内）

   ![cert](https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/kyc/certification.jpg)

### 2.2 授权

1. 应用方在需要用户授权的地方，通过url跳转到KYC dapp h5（在url后附上参数，通过用户ONT ID查询到加密后claim），显示授权页面。

2. 用户确认后，输入密码，发送授权信息到应用方后台（请求数据使用ONT ID 账户体系后台公钥加密），应用方后台转发请求数据到ONT ID后台，返回解密后的Claim。

3. 应用方验证Cliam。返回给KYC dapp验证结果，即授权结果。

   ![auth](https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/kyc/auth.jpg)


## 3. 应用方对接所需接口和链接

### 3.1 跳转到KYC dapp认证页面

```
url：host + /#/certHome?ontid={user's ONT ID}
```

### 3.2 跳转到KYC dapp授权页面

```
url: host + /#/authHome?userOntid={userOntid}&dappOntid={dappOntid}&dappName={dappName}&dappUrl={dappUrl}&callback={callback}&dappPk={dappPk}
```

`userOntid` User's ONT ID

`dappOntid` dApp's ONT ID

`dappName` dApp's name

`dappUrl` 授权成功后跳转回dapp的地址

`callback` dapp后台用来接收授权信息的回调地址。

`dappPk` 为保证传输用户信息的安全性，使用dapp的公钥和ECIES加密算法，对用户信息加密，把得到的密文信息传输给dapp后台，dapp后台用私钥解密出明文信息。

### 3.3 授权时KYC dapp h5 发送用户Claim到应用方后台回调

我们约定在授权时，应用方提供自己接受处理授权信息的回调地址。请求的参数和返回结果我们统一约定如下：

#### POST

```
url	: 由dapp传给KYC dapp
```

### REQUEST

| Field_Name  | Required | Format | Description             |
| ----------- | -------- | ------ | ----------------------- |
| nounce      | yes      | string | 需保证唯一性            |
| owner_claim | yes      | string | 用户Claim 的JSON string |
| owner_ontid | Yes      | String | 用户的ONT ID            |

### RESPONSE

| Field_Name | Format  | Description                                      |
| ---------- | ------- | ------------------------------------------------ |
| version    | String  | 版本号，目前是1.0。                              |
| action     | String  | 固定值：RequestAuthorizationCallback。           |
| desc       | String  | 错误信息。成功即SUCCESS，其他即错误信息          |
| result     | boolean | true：验证授权信息成功； false：验证授权信息失败 |

### 3.4 认证时转发获取签名请求

认证时，用户发送获取签名的请求，应用方直接转发请求到ONT ID账户体系后台。需要ONT ID后台提供接收该请求的 接口。

### POST

```
url: 由应用方传给KYC dapp
```

### REQUEST

| Field_Name | Required | Format | Description                                                  |
| ---------- | -------- | ------ | ------------------------------------------------------------ |
| nounce     | yes      | string | 需保证唯一性                                                 |
| message    | yes      | string | 使用ONT ID后台公钥加密的请求数据。格式是 “.”分隔的字符串。解密后内容为：{auth_id: 'xxxx', password: ''} |

### RESPONSE

| Field_Name | Format | Description                                |
| ---------- | ------ | ------------------------------------------ |
| version    | String | 版本号，目前是1.0。                        |
| action     | String | 固定值：RequestAuthorizationCallback。     |
| desc       | String | 错误信息。成功即SUCCESS，其他即错误信息    |
| result     | String | ONT  ID 使用用户私钥对解密出的数据做的签名 |

### 3.5 授权时转发授权信息

授权时，用户发送授权信息（使用ONT ID后台公钥加密的）给应用方后台。应用方转发给ONT ID后台解密，得到Claim，对Claim验证，验证成功，则授权成功。返回授权结果给KYC dapp。

### POST

```
url: 由应用方传给KYC dapp
```

### REQUEST

| Field_Name | Required | Format | Description                                                  |
| ---------- | -------- | ------ | ------------------------------------------------------------ |
| nounce     | yes      | string | 需保证唯一性                                                 |
| message    | yes      | string | 使用ONT ID后台公钥加密的请求数据。格式是 “.”分隔的字符串。解密后内容为：{enc_claim: 'xxxx', password: ''} |

### RESPONSE

| Field_Name | Format | Description                             |
| ---------- | ------ | --------------------------------------- |
| version    | String | 版本号，目前是1.0。                     |
| action     | String | 固定值：RequestAuthorizationCallback。  |
| desc       | String | 错误信息。成功即SUCCESS，其他即错误信息 |
| result     | String | 应用方后台验证授权Claim的结果。         |