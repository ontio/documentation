
## 1. 概述

本文用于指导 ```DAPP``` 如何接入 ```dAPI``` 扫描协议，让用户能够用手机钱包实现扫码登陆，扫码调用智能合约等服务。

流程中涉及到的参与方包括：

* ```DAPP``` 方：为本体生态内的用户提供 ```DAPP``` 是本体生态中重要的组成部分。
* ```Provider```方：实现 ```dAPI mobile``` 规范的钱包


### 基本概念

介绍去中心化应用程序和去中心化手机钱包的职责。

#### ①去中心化应用程序

#####  DAPP 

-  ```DAPP``` 后台主要提供以下功能：

 - ```DAPP``` 操作，生成相应的登录参数或者调用智能合约的参数。
 - 同步链上信息，获取登录或调用智能合约的结果。

#### ②去中心化手机钱包的职责

##### Provider
- 提供签名，预执行交易，执行交易等与链交互职责。

> 当前描述仅针对目前支持的两个钱包：

> - ONTO [下载](https://onto.app)
> - Cyano [下载](http://101.132.193.149/files/app-debug.apk)

#### ③演示
此处提供了两个唤醒特定钱包的  ```Demo app``` 供您参考：

* [唤醒演示](https://github.com/ontio-cyano/android-app-demo)

* [Unity 游戏演示](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/12-unity_integration)

## 2. 交互流程

下面简单介绍登录和调用智能合约完成支付流程两部分。

### 登录

![login-invoke](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/split-login-invoke-1-cn.png)

1. ```DAPP``` 方提供二维码（[登录](#登录)）
2. ```DAPP``` 服务端登录方法（[DAPP 服务端登录接口](#DAPP-服务端登录接口)）
3. ```DAPP``` 后端验证签名（[签名验证方法](#签名验证方法)）后返回验证结果

### 调用智能合约

![login-invoke](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/split-login-invoke-2-cn.png)

1. ```DAPP``` 方提供二维码（[调用合约](#调用合约)）
2. ```Provider``` 构造交易、用户签名、预执行交易、用户确认、发送到链上，最后返回交易 ```hash``` 给 ```DAPP``` 后端
3. ```DAPP``` 后端到链上查询这笔合约交易事件

## 3. dAPI 协议使用

 dAPI 协议目前支持登录和调用合约。

### 3.1 登录
二维码标准：

```json
{
	"action": "login",
	"version": "v1.0.0",
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
	"params": {
		"type": "ontid or account",
		"dappName": "dapp Name",
		"dappIcon": "dapp Icon",
		"message": "helloworld",
		"expire": 1546415363, // QR Code expire time
		"callback": "http://101.132.193.149:4027/blockchain/v1/common/test-onto-login"
	}
}
```

|字段|类型|定义|
| :---| :---| :---|
| action   |  string | 定义此二维码的功能，登录设定为 `Login`，调用智能合约设定为 `invoke` |
| id   |  string |  消息序列号，可选 |
| type   |  string | 使用 ontid 登录设定为 `ontid`，钱包地址登录设定为 `account` |
| dappName   | string  | DAPP 名字 |
| dappIcon   | string  | DAPP icon 信息 |
| message   | string  | 随机生成，用于校验身份  |
| expire   | long  | 可选  |
| callback   | string  | 用户扫码签名后发送到 DAPP 后端 URL |

### 3.2 DAPP 服务端登录接口
method: post

```json
{
	"action": "login",
	"version": "v1.0.0",
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
	"params": {
		"type": "ontid or account",
		"user": "did:ont:AUEKhXNsoAT27HJwwqFGbpRy8QLHUMBMPz",
		"message": "helloworld",
		"publickey": "0205c8fff4b1d21f4b2ec3b48cf88004e38402933d7e914b2a0eda0de15e73ba61",
		"signature": "01abd7ea9d79c857cd838cabbbaad3efb44a6fc4f5a5ef52ea8461d6c055b8a7cf324d1a58962988709705cefe40df5b26e88af3ca387ec5036ec7f5e6640a1754"
	}
}
```

|字段|类型|定义|
| :---| :---| :---|
| action | string | 操作类型 |
| id   |  string |  消息序列号，可选 |
| params | string | 方法要求的参数 |
| type   |  string | ontid 登录设定为 `ontid`，钱包地址登录设定为 `account` |
| user | string | 用户做签名的账户，比如用户的 ontid 或者钱包地址 |
| message   | string  | 随机生成，用于校验身份  |
| publickey | string | 账户公钥 |
| signature  |  string |  用户签名 |

成功响应：

```json
{
  "action": "login",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
  "error": 0,
  "desc": "SUCCESS",
  "result": true
}
```

失败响应：

```json
{
  "action": "login",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
  "error": 80001,
  "desc": "PARAMS ERROR",
  "result": 1
}
```


### 3.3 调用合约

支付也是调用合约的子功能，调用合约二维码标准：

```json
{
	"action": "invoke",
	"version": "v1.0.0",
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
	"params": {
		"login": true,
		"callback": "http://101.132.193.149:4027/invoke/callback",
		"qrcodeUrl": "http://101.132.193.149:4027/qrcode/AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ"
	}
}
```

|字段|类型|定义|
| :---        | :---    | :---                                                              |
| action      | string  | 操作类型，登录设定为 `Login`，调用智能合约设定为 `invoke`. |
| qrcodeUrl         | string  | 二维码参数地址                                           |
| callback         | string  | 可选，返回交易 hash 给 `DAPP` 服务端                         |

根据二维码中 `qrcodeUrl` 链接，GET 的数据如下：

```json
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
		}
	}
}
```

> base58 地址如 AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ 可以填 ```%address```，钱包会把 ```%address``` 改成钱包的资产地址。如果参数里有 `%ontid` 钱包会改成钱包的 `ontid` 地址。

<p class = "info">调用合约时，如果二维码里 payer 没填写，就由钱包填写。如果二维码里 payer 有填写，钱包要验证是否与钱包的资产地址一致。</p>

Provider 构造交易，进行用户签名、预执行交易、发送交易，最后 POST 交易 hash 给 callback url。

发送交易成功，POST 给 callback：

```json
{
  "action": "invoke",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
  "error": 0,
  "desc": "SUCCESS",
  "result": "tx hash"
}
```

发送交易失败，POST 给 callback：

```json
{
  "action": "invoke",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
  "error": 80001,
  "desc": "SEND TX ERROR",
  "result": 1
}
```


## 4. 代码参考

##### 签名验证方法
* [java sdk验签](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/interface.md#%E7%AD%BE%E5%90%8D%E9%AA%8C%E7%AD%BE)
* [ts sdk验签](https://github.com/ontio/ontology-ts-sdk/blob/master/test/ecdsa.crypto.test.ts)

##### DAPP 后端查询交易事件
* [java sdk 交易事件查询方法](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/basic.md#%E4%B8%8E%E9%93%BE%E4%BA%A4%E4%BA%92%E6%8E%A5%E5%8F%A3)
* [ts sdk 交易事件查询方法](https://github.com/ontio/ontology-ts-sdk/blob/master/test/websocket.test.ts)

##### 钱包
* [cyano-android](https://github.com/ontio-cyano/cyano-android)
* [cyano-ios](https://github.com/ontio-cyano/cyano-ios)

##### dAPI-mobile client sdk
* [cyano-bridge](https://github.com/ontio-cyano/cyano-bridge)

##### dAPI-mobile provider sdk
* [cyano-android-sdk](https://github.com/ontio-cyano/cyano-android-sdk)
* [cyano-ios-sdk](https://github.com/ontio-cyano/cyano-ios-sdk)
