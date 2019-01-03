
<h1 align="center">钱包打开H5 DApp接入流程</h1>
<p align="center" class="version">Version 0.8.0 </p>

## 概述

本文用于指导dApp方如何与钱包通信，及钱包如何处理dApp的请求。
流程中涉及到的参与方包括：

* Dapp方：对ONT生态内的用户提供Dapp，是本体生态中重要的组成部分。
* Provider：实现dApi mobile规范的钱包

## 交互流程说明

DApp请求数据URI scheme：```ontprovider://ont.io?param=Base64.encode(Uri.encode({the json data}.toString()))```

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/scenario3.png" ><br><br>
</div>

### 钱包打开H5 DApp

- 1 钱包打开H5 DApp

### H5 DApp向获取Provider信息

- 1 DApp请求Provider信息
- 2 钱包返回Provider信息

### H5 DApp向获取账户或身份信息

- 1 DApp请求账户或身份信息
- 2 用户接受请求，返回账户或身份信息


### 登录Login
- 1 DApp请求对message做签名（[DApp发起登录请求](#DApp发起登录请求)）
- 2 钱包用户对message做签名，返回签名数据（[钱包响应登录请求](#钱包响应登录请求)）

### 消息签名signMessage


### 调用合约Invoke Smart contract
- 1 DApp请求调用合约（[DApp发起调用合约请求](#DApp发起调用合约请求)）
- 2 钱包构造交易，用户签名
- 3 钱包预执行交易（[预执行交易](#预执行交易)）   
- 4 钱包发送交易
- 3 钱包返回交易Hash（[钱包响应调用合约请求](#钱包响应调用合约请求)）



## 钱包和DApp接入步骤

### 前提条件
使用前，你需要联系[本体机构合作](https://info.ont.io/cooperation/en)


### 查询Provider信息步骤

#### DApp发起查询Provider信息请求

数据如下，**URI编码，Base64编码**后发送请求：
```

{
	"action": "getProvider", 
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",	
	"version": "v1.0.0",
	"params": {
	}
}


```

|字段|类型|定义|
| :---| :---| :---|
| action   |  string |  操作类型 |

#### 钱包返回Provider信息

**URI解码，Base64解码**后，获取到的数据如下：
```
{
	"action": "getProvider", 
	"version": "v1.0.0",
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",	
	"error": 0,
	"desc": "SUCCESS",
	"result": {
	    "provider": "cyano walllet",
	    "version": "1.0.0"
	}
}
```

### 查询账号或身份信息步骤

#### DApp发起查询账号或身份信息请求

数据如下，**URI编码，Base64编码**后发送请求：
```

{
	"action": "getAccount", // or getIdentity
	"version": "v1.0.0",
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",	
	"params": {
		"dappName": "dapp Name",
		"dappIcon": "dapp Icon"
	}
}


```

|字段|类型|定义|
| :---| :---| :---|
| action   |  string |  操作类型 |
| dappName   | string  | dapp名字 |
| dappIcon   | string  | dapp icon信息 |

#### 钱包返回账号或身份信息

**URI解码，Base64解码**后，获取到的数据如下：
```
{
	"action": "getAccount", // or getIdentity
	"version": "v1.0.0",
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",	
	"error": 0,
	"desc": "SUCCESS",
	"result": "AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ"  // or  "did:ont:AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ"
}
```

### 登陆步骤

#### DApp发起登录请求


数据如下，**URI编码，Base64编码**后发送请求：
```
{
	"action": "login",
	"version": "v1.0.0",
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",	
	"params": {
		"type": "ontid or account",
		"dappName": "dapp Name",
		"dappIcon": "dapp Icon",
		"message": "helloworld",
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

#### 钱包响应登录请求

**URI解码，Base64解码**后，获取到的数据如下：

* 返回成功内容
```
{
	"action": "login",
	"version": "v1.0.0",
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",	
	"error": 0,
    "desc": "SUCCESS",
	"result": {
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
| result | string | 返回结果 |
| type   |  string |  定义是使用ontid登录设定为"ontid"，钱包地址登录设定为"account" |
| user | string | 用户做签名的账户，比如用户的ontid或者钱包地址 |
| message   | string  | 随机生成，用于校验身份  |
| publickey | string | 账户公钥 |
| signature  |  string |  用户签名 |



* 返回失败内容

```
{
  "action": "login",
  "version": "v1.0.0",  
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a", 
  "error": 80001,
  "desc": "PARAMS ERROR",
  "result": 1
}
```


### 消息签名步骤

跟login一样，但DApp请求时不需要DApp名字和icon。

数据如下，**URI编码，Base64编码**后发送请求：

```
{
	"action": "signMessage",
	"version": "v1.0.0",
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",	
	"params": {
		"type": "ontid or account",
		"message": "helloworld",
	}
}
```
#### DApp发起签名请求


数据如下，**URI编码，Base64编码**后发送请求：
```
{
	"action": "signMessage",
	"version": "v1.0.0",
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",	
	"params": {
		"type": "ontid or account",
		"message": "helloworld",
	}
}
```

|字段|类型|定义|
| :---| :---| :---|
| action   |  string |  操作类型 |
| type   |  string |  定义是使用ontid登录设定为"ontid"，钱包地址登录设定为"account"，不填就默认是"account" |
| message   | string  | 随机生成，用于校验身份  |




### 调用合约步骤

action是invoke: 走正常流程。

action是invokeRead: 是预执行交易，用户不需要签名，返回预执行结果给DApp。

action是invokePasswordFree: 有些游戏会用到自动投注功能，比如每隔10秒投注一次，用户只需要输入一次密码。我们只信任固定的方法和参数，而不是信任整个合约的所有方法，所以输入密码后保存该交易的参数（是这个参数((InvokeCode)txs[0]).code），如果下次请求时是同样的数据就不需要再次输入密码，也不需要预执行。当用户离开当前DApp时，记得清空内存中的私钥和参数。



#### DApp发起调用合约请求

数据如下，**URI编码，Base64编码**后发送请求：

```
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


#### 钱包响应调用合约请求

**钱包先URI解码，Base64解码**：

1. 钱包构造交易
2. 用户签名
3. 预执行交易
4. 用户确认
5. 发送交易到链上
6. 返回交易hash给DApp



* 返回交易成功给DApp

```
{
  "action": "invoke",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a", 
  "error": 0,
  "desc": "SUCCESS",
  "result": "tx hash"
}
```

* 返回失败给DApp

```
{
  "action": "invoke",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",  
  "error": 80001,
  "desc": "SEND TX ERROR",
  "result": ""
}
```

##### 预执行交易

预执行交易返回的Notify结果可以查看用户在这笔交易中会花费多少ONT/ONG。需要连接到固定节点：主网：http://dappnode3.ont.io，测试网：http://polaris5.ont.io

> 需要遍历Notify做判断，因为该交易可能有多笔转账或其他事件，通过合约地址判断是ONT还是ONG，再判断transfer方法和转出方。

```

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

##### 合约查询方法
* [java sdk 合约查询](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/basic.md#%E4%B8%8E%E9%93%BE%E4%BA%A4%E4%BA%92%E6%8E%A5%E5%8F%A3)
* [ts sdk 合约查询](https://github.com/ontio/ontology-ts-sdk/blob/master/test/websocket.test.ts)

##### 钱包
* [cyano-android](https://github.com/ontio-cyano/cyano-android)
* [cyano-ios](https://github.com/ontio-cyano/cyano-ios)

##### dApi-mobile client sdk
* [cyano-bridge](https://github.com/ontio-cyano/cyano-bridge)

##### dApi-mobile provider sdk
* [cyano-android-sdk](https://github.com/ontio-cyano/cyano-android-sdk)
* [cyano-ios-sdk](https://github.com/ontio-cyano/cyano-ios-sdk)