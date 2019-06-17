

## 概述

本文用于指导钱包方如何接入扫码功能，提供扫码登陆，扫码调用智能合约等服务。
流程中涉及到的参与方包括：

* DApp 方：对本体链生态内的用户提供 ```dApp``` ，是本体生态中重要的组成部分。
* Provider：实现 ```dAPI mobile``` 规范的钱包

## 交互流程说明

应用方提供二维码，用户通过手机钱包扫码。

### 第一步，扫描登录

![login-invoke](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/split-login-invoke-1-cn.png)

详细流程：
1. 钱包扫描 ```DAPP``` 方提供的二维码（[登录二维码标准](#登录二维码标准)）
2. Provider 获取到 ```callback url``` 和验证用的消息，让用户输入密码对对消息签名，调用```DAPP``` 方的回调地址
3. ```DAPP``` 后端验证签名（[签名验证方法](#签名验证方法)）后返回验证结果

### 第二步，扫描调用合约

![login-invoke](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/split-login-invoke-2-cn.png)

详细流程：
1. 钱包扫描 ```DAPP``` 方提供的二维码（[调用合约二维码标准](#调用合约二维码标准)）
2. 钱包构造交易，用户签名，预执行交易，用户确认，发送到链上，调用 ```DAPP``` 后端的回调地址发送交易 ```Hash``` 
3. ```DAPP``` 后端查询这笔合约交易事件

## dAPI 协议介绍

扫码目前支持两个功能，登录和调用合约。

### 登录

通过钱包扫描做授权登录。钱包通过扫码获取登录参数，签名授权并发送给 DAPP 后端。

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
| action   |  string |  定义此二维码的功能，登录设定为 "Login"，调用智能合约设定为 "invoke" |
| id   |  string |  消息序列号，可选 |
| type   |  string |  定义是使用ontid登录设定为 "ontid"，钱包地址登录设定为 "account" |
| dappName   | string  | dapp名字 |
| dappIcon   | string  | dapp icon信息 |
| message   | string  | 随机生成，用于校验身份  |
| expire   | long  | 可选  |
| callback   | string  |  用户扫码签名后发送到DApp后端URL |

### DAPP 服务端的回调接口
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
| type   |  string |  定义是使用ontid登录设定为"ontid"，钱包地址登录设定为"account" |
| user | string | 用户做签名的账户，比如用户的ontid或者钱包地址 |
| message   | string  | 随机生成，用于校验身份  |
| publickey | string | 账户公钥 |
| signature  |  string |  用户签名 |

返回成功：

```json
{
  "action": "login",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
  "error": 0,
  "desc": "SUCCESS",
  "result": true
}
```

返回失败：

```json
{
  "action": "login",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
  "error": 80001,
  "desc": "PARAMS ERROR",
  "result": 1
}
```

### 调用合约

支付也是调用合约的一种，采用统一的协议标准。调用合约二维码标准：


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
| action      | string  | 操作类型，登录设定为"Login"，调用智能合约设定为"invoke" |
| qrcodeUrl         | string  | 二维码参数地址                                           |
| callback         | string  | 选填，返回交易hash给dApp服务端                                           |

根据二维码中 qrcodeUrl 链接，GET 的的数据如下：

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


钱包构造交易，用户签名，预执行交易，发送交易，POST 交易 hash 给 callback url 。

* 发送交易成功 POST 给回调地址

```json
{
  "action": "invoke",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
  "error": 0,
  "desc": "SUCCESS",
  "result": "tx hash"
}
```

* 发送交易失败 POST 给回调地址

```json
{
  "action": "invoke",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
  "error": 80001,
  "desc": "SEND TX ERROR",
  "result": 1
}
```

##### 预执行交易

预执行交易是可选的，主要作用是提醒用户该交易中包含的 ONT/ONG 转账数量。

预执行交易返回的 ```Notify``` 结果可以查看用户在这笔交易中会花费多少 ONT/ONG 。因为当前节点没升级，需要连接到固定节点预执行才会有返回 ```Notify``` 信息：主网：http://dappnode3.ont.io， 测试网：http://polaris5.ont.io

> 需要遍历 Notify 做判断，因为该交易可能有多笔转账事件或其他合约事件，如果是其他合约事件不需做处理，通过合约地址判断是 ONT 还是 ONG ，再判断 transfer 方法和转出方。建议 UI 显示转入转出方和 amount ，还有交易手续费大约 0.01 ONG 。
ONT:0100000000000000000000000000000000000000
ONG:0200000000000000000000000000000000000000

如果预执行成功，节点返回的结果是：
```json
{
    "Action": "sendrawtransaction",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": {
              	"Notify": [{
              		"States": ["transfer", "AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ", "AecaeSEBkt5GcBCxwz1F41TvdjX3dnKBkJ", 1],
              		"ContractAddress": "0100000000000000000000000000000000000000"
              	}],
              	"State": 1,
              	"Gas": 20000,
              	"Result": "01"
     },
    "Version": "1.0.0"
}
```

如果预执行失败，Error 的值> 0。


## 代码参考

##### 签名验证方法
* [java sdk验签](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/interface.md#%E7%AD%BE%E5%90%8D%E9%AA%8C%E7%AD%BE)
* [ts sdk验签](https://github.com/ontio/ontology-ts-sdk/blob/master/test/ecdsa.crypto.test.ts)

##### DAPP 后端查询交易事件
* [java sdk 交易事件查询方法](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/basic.md#%E4%B8%8E%E9%93%BE%E4%BA%A4%E4%BA%92%E6%8E%A5%E5%8F%A3)
* [ts sdk 交易事件查询方法](https://github.com/ontio/ontology-ts-sdk/blob/master/test/websocket.test.ts)

##### 钱包
* [cyano-android](https://github.com/ontio-cyano/cyano-android)
* [cyano-ios](https://github.com/ontio-cyano/cyano-ios)

##### dApi-mobile dapp sdk
* [cyano-bridge](https://github.com/ontio-cyano/cyano-bridge)

##### dApi-mobile provider sdk
* [cyano-android-sdk](https://github.com/ontio-cyano/cyano-android-sdk)
* [cyano-ios-sdk](https://github.com/ontio-cyano/cyano-ios-sdk)
