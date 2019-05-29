


## 概述

本文用于指导dApp方如何唤醒钱包，及钱包如何返回信息。钱包实现请参考 [Cyano 开源钱包](https://github.com/ontio-cyano), 应用唤醒实现请参考 [Android 应用例子](https://github.com/ontio-cyano/android-app-demo),流程中涉及到的参与方包括：

* DAPP 方：对本体生态内的用户提供 ```DAPP```，是本体生态中重要的组成部分。
* Provider：实现 ```dAPI``` 规范的钱包

## 交互流程说明

DApp请求数据URI scheme：```ontprovider://ont.io?param=Base64.encode(Uri.encode({the json data}.toString()))```


### Login
- 1.1 ```DAPP``` 唤醒 Provider（[唤醒登陆请求](#唤醒登陆请求)）
- 1.2 Provider 获取到 ```callback url``` 和验证用的消息
- 2 对消息签名，调用回调方法（[钱包处理登录请求](#钱包处理登录请求)）
- 3 ```DAPP``` 后端验证签名（[DApp服务器返回数据](#DApp服务器返回数据)）后返回验证结果

### Invoke Smart contract
- 1 ```DAPP``` 唤醒 provider（[调用合约唤醒标准](#调用合约唤醒标准)）
- 2 Provider 构造交易，预执行交易，发送到链上，返回交易 ```Hash``` 给 ```callback``` 地址
- 3 DAPP 后端查询这笔合约交易（[DApp后端查询交易事件](#DApp后端查询交易事件)）

## 接入步骤


### 登陆接入步骤

#### 唤醒登陆请求
数据如下，**URI编码，Base64编码**后发送请求：

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
		"callback": "http://127.0.0.1:80/login/callback"
	}
}
```

|字段|类型|定义|
| :---| :---| :---|
| action   |  string |  操作类型 |
| type   |  string |  定义是使用ontid登录设定为"ontid"，钱包地址登录设定为"account" |
| dappName   | string  | dapp名字 |
| dappIcon   | string  | dapp icon信息 |
| message   | string  | 随机生成，用于校验身份  |
| callback   | string  |  用户扫码签名后发送到DApp后端URL |

### 钱包处理登录请求
**URI解码，Base64解码**后，对message做签名，POST如下内容给DApp服务器的callback地址

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
| params | string | 方法要求的参数 |
| type   |  string |  定义是使用ontid登录设定为"ontid"，钱包地址登录设定为"account" |
| user | string | 用户做签名的账户，比如用户的ontid或者钱包地址 |
| message   | string  | 随机生成，用于校验身份  |
| publickey | string | 账户公钥 |
| signature  |  string |  用户签名 |

#### DApp服务器返回数据
* 验证签名成功

```json
{
  "action": "login",
  "version": "v1.0.0",  
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",  
  "error": 0,
  "desc": "SUCCESS",
  "result": true
}
```

* 验证签名失败

```json
{
  "action": "login",
  "version": "v1.0.0",  
  "error": 80001,
  "desc": "PARAMS ERROR",
  "result": 1
}
```


### 调用合约唤醒标准
数据如下，**URI编码，Base64编码**后发送请求：

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
| action      | string  | 操作类型|
| qrcodeUrl         | string  | 二维码参数地址                                           |
| callback         | string  | 选填，返回交易hash给dApp服务端                                           |

根据二维码中qrcodeUrl链接，GET的的数据如下：

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


Provider 构造交易，用户签名，预执行交易，发送交易，POST 交易hash给callback url。

* 发送交易成功POST给callback

```json
{
  "action": "invoke",
  "version": "v1.0.0", 
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",  
  "error": 0,
  "desc": "SUCCESS",
  "result": "tx hash"
}
```

* 发送交易失败给callback

```json
{
  "action": "invoke",
  "error": 80001,
  "desc": "SEND TX ERROR",
  "result": 1
}
```

##### 预执行交易

预执行交易返回的Notify结果可以查看用户在这笔交易中会花费多少ONT/ONG。需要连接到固定节点：主网：http://dappnode3.ont.io，测试网：http://polaris5.ont.io

> 需要遍历Notify做判断，因为该交易可能有多笔转账或其他事件，通过合约地址判断是ONT还是ONG，再判断transfer方法和转出方。

```json

{
	"Notify": [{
		"States": ["transfer", "AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ", "AecaeSEBkt5GcBCxwz1F41TvdjX3dnKBkJ", 1],
		"ContractAddress": "0100000000000000000000000000000000000000"
	}],
	"State": 1,
	"Gas": 20000,
	"Result": "01"
}

```


## 代码参考

##### 签名验证方法
* [java sdk验签](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/interface.md#%E7%AD%BE%E5%90%8D%E9%AA%8C%E7%AD%BE)
* [ts sdk验签](https://github.com/ontio/ontology-ts-sdk/blob/master/test/message.test.ts)

##### DApp后端查询交易事件
* [java sdk 交易事件查询方法](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/basic.md#%E4%B8%8E%E9%93%BE%E4%BA%A4%E4%BA%92%E6%8E%A5%E5%8F%A3)
* [ts sdk 交易事件查询方法](https://github.com/ontio/ontology-ts-sdk/blob/master/test/websocket.test.ts)

##### 钱包
* [cyano-android](https://github.com/ontio-cyano/cyano-android)
* [cyano-ios](https://github.com/ontio-cyano/cyano-ios)

##### dApi-mobile client sdk
* [cyano-bridge](https://github.com/ontio-cyano/cyano-bridge)

##### dApi-mobile provider sdk
* [cyano-android-sdk](https://github.com/ontio-cyano/cyano-android-sdk)
* [cyano-ios-sdk](https://github.com/ontio-cyano/cyano-ios-sdk)
