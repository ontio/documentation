<h1 align="center">ONTO Connector服务接入标准 </h1>
<p align="center" class="version">Version 0.8.0 </p>

## 概述

本文用于指导dapp方如何接入ONTO connector，并使用扫码登陆，扫码调用智能合约等服务。
流程中涉及到的参与方包括：

* Dapp方：对ONT生态内的用户提供Dapp，是本体生态中重要的组成部分。
* ONTO：综合客户端产品[https://onto.app](https://onto.app)，连接了服务全球的身份认证服务供应商，并帮助用户实现认证和自主管理数据。

## 交互流程说明

<img src="https://github.com/ontio/documentation/blob/master/pro-website-docs/assets/split-login-invoke.png" style="max-width:1000px"/>

### Login
- 1.1 使用ONTO作为provider扫描dapp方提供的二维码（[登陆二维码标准](#登陆二维码标准)）
- 1.2 ONTO获取到callback url和验证用的msg
- 2 对msg签名，调用登陆方法（[登陆接口](#登陆接口)）
- 3 dapp后端验证签名（[签名验证方法](#签名验证方法)）后返回验证结果

### Invoke SC
- 1.1 使用ONTO作为provider扫描dapp方提供的二维码（[调用合约二维码标准](#调用合约二维码标准)）
- 1.2 使用ONTO扫码
- 1.3 ONTO获得构造后的交易
- 2 ONTO验证签名，添加自己的签名，发送到链上
- 3 dapp后端查询这笔合约交易（[合约查询方法](#合约查询方法)）

## 接入步骤

### 前提条件
要使用ONTO connector，你需要联系[本体机构合作](https://info.ont.io/cooperation/en)

### 登陆接入步骤

#### 登陆二维码标准
扫码获取

```
{
	"action": "login",
  "params": {
    "type": "ontid", // or account
    "method": "post",
    "message": "HgigFdfwf",
    "url": "http://127.0.0.1:80/login/callback"
  }
}
```

|字段|类型|定义|
| :---| :---| :---|
| action   |  string |  定义此二维码的功能，登录设定为"Login"，调用智能合约设定为"invoke" |
| type   |  string |  定义是使用ontid登录设定为"ontid"，钱包地址登录设定为"account" |
| method   | string  | post  |
| message   | string  | 随机生成，用于校验身份  |
| url   | string  |  用户扫码签名后发送的URL |

### 登陆接口
method: post

```
{
  "action": "login",
  "params": {
    "user":"did:ont:Akdjhskgfhlsdhgklfdhkjghf",
    "message": "HgigFdfwf",
    "publickey":"1be23hm1vbehj12g127814gk23bnvb213i7ugcb3rfdhb98",
    "signature":"hfksjhdsjkhfjkdhsjkhfdwakjl,hfgkjasedhfjklhsgdkjhfjk",
  }
}
```

|字段|类型|定义|
| :---| :---| :---|
| action | string | 定义此二维码的功能，登录设定为"login"，调用智能合约设定为"invoke" |
| params | string | 方法要求的参数 |
| user | string | 用户做签名的账户，比如用户的ontid或者钱包地址 |
| message   | string  | 随机生成，用于校验身份  |
| publickey | string | 账户公钥 |
| signature  |  string |  用户签名 |

#### Response
* Success

```
{
  "action": "login",
  "error": 0,
  "desc": "SUCCESS",
  "result": true
}
```

* Failed

```
{
  "action": "login",
  "error": 8001,
  "desc": "PARAMS ERROR",
  "result": 1
}
```


### 调用合约二维码标准
扫码获取

```
{
	"action": "invoke",
  "params": {
      "login_statu": true,
      "method": "post",
      "url": "http://127.0.0.1:80/rawtransaction/txhash", //optional: get signedTx from DApp backend
      "signedTx": "00d000000000000000000000000000000000000000000000000000000000000000000000000000000000140000000000000000000000000000000000000004010b506172616d436f6e66696703312e300d4f6e746f6c6f6779205465616d0e636f6e74616374406f6e742e696f2b436861696e20476c6f62616c20456e7669726f6e6d656e74205661726961626c6573204d616e61676572200000"
  }
}
```

|字段|类型|定义|
| :---        | :---    | :---                                                              |
| ----------- | ------- | ----------------------------------------------------------------- |
| action      | string  | 定义此二维码的功能，登录设定为"Login"，调用智能合约设定为"invoke" |
| login_statu | boolean |                                                                   |
| method      | string  | post                                                              |
| url         | string  | 用户扫码签名后发送的URL                                           |
| signedTx    | string  | dapp后台根据用户钱包构建的调用智能合约交易                        |



##### 签名验证方法
* [java sdk验签](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/interface.md#%E7%AD%BE%E5%90%8D%E9%AA%8C%E7%AD%BE)
* [ts sdk验签](https://github.com/ontio/ontology-ts-sdk/blob/master/test/message.test.ts)

##### 合约查询方法
* [java sdk 合约查询](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/basic.md#%E4%B8%8E%E9%93%BE%E4%BA%A4%E4%BA%92%E6%8E%A5%E5%8F%A3)
* [ts sdk 合约查询](https://github.com/ontio/ontology-ts-sdk/blob/master/test/websocket.test.ts)
