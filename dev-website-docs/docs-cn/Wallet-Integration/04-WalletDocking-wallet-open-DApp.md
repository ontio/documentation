

## 概述

本文用于指导钱包 APP 如何对接 ```Provider SDK``` 以支持本体的 dAPI 协议，对接 Provider SDK 可以参考对应的 [开源 Android 和 iOS 钱包](https://github.com/ontio-cyano)。

对接流程中涉及到的参与方包括：

* DAPP 方：对本体生态内的用户提供 ```DAPP``` ，是本体生态中重要的组成部分。
* Provider：支持 ```dApi``` 规范的钱包

> 已支持 dAPI 协议的钱包: [麦子钱包](http://www.mathwallet.org/en/)，[Banko](http://bankowallet.com/pc.html) 等

## 交互流程说明

交互流程中 DAPP 请求数据 ```URI scheme``` 是：```ontprovider://ont.io?param=Base64.encode(Uri.encode({the json data}.toString()))```，交互流程主要分三个步骤。

![login-invoke](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/scenario3-cn.png)



#### 第一步，钱包使用 Webview 打开 DAPP（使用 H5 开发）

 钱包 ```dApp Store``` 页面使用 ```Webview``` 打开 H5 DAPP

#### 第二步，DAPP 发起获取钱包地址信息请求

有两种获取方式:
* [通过 getAccount 协议获取账户信息](#查询钱包账号或身份信息)
* [通过 Login 协议获取账户信息](#登录)

#### 第三步，DAPP 发起调用合约请求

详细流程：
 1. DApp 请求 [调用合约](#调用合约)
 2. 钱包构造交易，弹出密码框让用户签名，用户输入密码
 3. 钱包预执行交易（[预执行交易](#预执行交易)）
 4. 钱包发送交易到链上
 3. 钱包返回交易Hash



## dAPI 协议介绍

dAPI 协议可扩展，现在支持的主要功能有：

* 查询 Provider 信息
* 查询钱包账号或身份信息
* 登录
* 消息签名
* 调用合约

### 查询 Provider 信息

DApp 发起查询 Provider 信息请求，数据如下，**URI 编码，Base64 编码**后发送请求：
```json

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

钱包返回 Provider 信息，**URI解码，Base64解码**后，获取到的数据如下：
```json
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

### 查询钱包账号或身份信息

DApp 发起查询账号或身份信息请求，数据如下，**URI 编码，Base64 编码**后发送请求：
```json

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

钱包返回账号或身份信息，**URI 解码，Base64 解码**后，获取到的数据如下：
```json
{
	"action": "getAccount", // or getIdentity
	"version": "v1.0.0",
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
	"error": 0,
	"desc": "SUCCESS",
	"result": "AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ"  // or  "did:ont:AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ"
}
```

### 登录

DApp 发起登录请求，数据如下，**URI 编码，Base64 编码**后发送请求：
```json
{
	"action": "login",
	"version": "v1.0.0",
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
	"params": {
		"type": "ontid or account",
		"dappName": "dapp Name",
		"dappIcon": "dapp Icon",
		"message": "helloworld"
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

钱包响应登录请求，**URI 解码，Base64 解码**后，获取到的数据如下：

返回成功内容：
```json
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



返回失败内容：

```json
{
  "action": "login",
  "version": "v1.0.0",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
  "error": 80001,
  "desc": "PARAMS ERROR",
  "result": 1
}
```


### 消息签名

跟登录协议一样，但 DApp 请求时不需要 DApp 名字和 icon。DApp 发起签名请求，数据如下，**URI 编码，Base64 编码**后发送请求：
```json
{
	"action": "signMessage",
	"version": "v1.0.0",
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
	"params": {
		"type": "ontid or account",
		"message": "helloworld"
	}
}
```

|字段|类型|定义|
| :---| :---| :---|
| action   |  string |  操作类型 |
| type   |  string |  定义是使用ontid登录设定为"ontid"，钱包地址登录设定为"account"，不填就默认是"account" |
| message   | string  | 随机生成，用于校验身份  |




### 调用合约

action 是 invoke: 走正常流程。

action 是 invokeRead: 是预执行交易，用户不需要签名，返回预执行结果给 DApp。

action 是 invokePasswordFree: 有些游戏会用到自动投注功能，比如每隔10秒投注一次，用户只需要输入一次密码。我们只信任固定的方法和参数，而不是信任整个合约的所有方法，所以输入密码后保存该交易的参数（是这个参数((InvokeCode)txs[0]).code），如果下次请求时是同样的数据就不需要再次输入密码，也不需要预执行。当用户离开当前DApp时，记得清空内存中的私钥和参数。



#### DAPP 发起调用合约请求
数据如下，**URI 编码，Base64 编码**后发送请求：

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


#### 钱包响应调用合约请求

**钱包先URI 解码，Base64 解码**：

1. 钱包构造交易
2. 用户签名
3. 预执行交易
4. 用户确认
5. 发送交易到链上
6. 返回交易 hash 给 DApp



* 返回交易成功给 DApp

```json
{
  "action": "invoke",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
  "error": 0,
  "desc": "SUCCESS",
  "result": "tx hash"
}
```

* 返回失败给 DApp

```json
{
  "action": "invoke",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
  "error": 80001,
  "desc": "SEND TX ERROR",
  "result": ""
}
```

##### 预执行交易

预执行交易返回的 ```Notify``` 结果可以查看用户在这笔交易中会花费多少 ONT/ONG 。需要连接到固定节点：主网：http://dappnode3.ont.io，测试网：http://polaris5.ont.io

> 需要遍历 Notify 做判断，因为该交易可能有多笔转账或其他事件，通过合约地址判断是 ONT 还是 ONG ，再判断 transfer 方法和转出方。

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


## dAPI Provider SDK 对接

dAPI Provider SDK 帮助 ```Android webview``` 和网页 ```DAPP``` 之间通信。它对 ```webview``` 进行了一些方法的封装。分别支持 ```Android```、```iOS```，详细请参考：
* [cyano-android-sdk](https://github.com/ontio-cyano/cyano-android-sdk)
* [cyano-ios-sdk](https://github.com/ontio-cyano/cyano-ios-sdk)

Android-sdk：

```java
//init
CyanoWebView cyanoWebView=new CyanoWebView(context);
cyanoWebView.loadUrl(url);

//Action handle
cyanoWebView.getNativeJsBridge().setHandleGetAccount(new NativeJsBridge.HandleGetAccount() {
            @Override
            public void handleAction(String data) {
              /* TODO
               * 1.发送钱包地址到webView
               * com.alibaba.fastjson.JSONObject reqJson = JSON.parseObject(data);
               * String action=reqJson.getString("action");
               * String version=reqJson.getString("version");
               * String id=reqJson.getString("id");
               * cyanoWebView.sendSuccessToWeb(action,version, id, 钱包地址);
               */
            }
	});

cyanoWebView.getNativeJsBridge().setHandleInvoke(new NativeJsBridge.HandleInvoke() {
            @Override
            public void handleAction(String data) {
              /* TODO
               * 1.弹出密码输入框，解出钱包 account，将 data 构建交易，对交易进行签名，预执行获取结果，注意耗时操作。
               *
               * 2.将预知行结果解析出 Notify 结果，显示手续费，如果结果中包含 ONT , ONG 合约地址，需显示转账金额和收款地址，
               *
               * 3.用户确认后发送交易到链上
               *
               * 4.发送交易 hash 到 webView
               * com.alibaba.fastjson.JSONObject reqJson = JSON.parseObject(data);
               * String action=reqJson.getString("action");
               * String version=reqJson.getString("version");
               * String id=reqJson.getString("id");
               * cyanoWebView.sendSuccessToWeb(action,version, id, 交易 hash);
               */
            }
	});

cyanoWebView.getNativeJsBridge().setHandleInvokeRead(new NativeJsBridge.HandleInvokeRead() {
        @Override
        public void handleAction(String data) {
               /* TODO
                * 1.将 data 构建交易，预执行获取结果，注意耗时操作。
                *
                * 2.发送预知行结果到 webView
                * com.alibaba.fastjson.JSONObject reqJson = JSON.parseObject(data);
                * String action=reqJson.getString("action");
                * String version=reqJson.getString("version");
                * String id=reqJson.getString("id");
                * cyanoWebView.sendSuccessToWeb(action,version, id, 预知行结果);
                */
        }
});


cyanoWebView.getNativeJsBridge().setHandleInvokePasswordFree(new NativeJsBridge.HandleInvokePasswordFree() {
        @Override
        public void handleAction(String data, String message) {
          /* TODO
           * 1.第一次操作和action：Invoke相同，同时保存password和message
           *
           * 2.当第二次收到相同的message时候，将用保存的密码进行签名，预知行获取结果
           *
           * 3.预知行结果不用显示给用户确认
           *
           * 4.发送交易hash到webView
           * com.alibaba.fastjson.JSONObject reqJson = JSON.parseObject(data);
           * String action=reqJson.getString("action");
           * String version=reqJson.getString("version");
           * String id=reqJson.getString("id");
           * cyanoWebView.sendSuccessToWeb(action,version, id, 交易hash);
           */
        }
});


//response
Map map = new HashMap<>();
map.put("action", "");
map.put("error", 0);
map.put("desc", "SUCCESS");
map.put("result", message);
cyanoWebView.sendBack(Base64.encodeToString(Uri.encode(JSON.toJSONString(map)).getBytes(), Base64.NO_WRAP));
```

iOS-sdk：

```
RNJsWebView * webView = [[RNJsWebView alloc]initWithFrame:CGRectZero];
[webView setURL:@""];
```



```


[webView setGetAccountCallback:^(NSDictionary *callbackDic) {

}];


[webView setInvokeTransactionCallback:^(NSDictionary *callbackDic) {

}];

[webView setInvokeReadCallback:^(NSDictionary *callbackDic) {

}];


NSDictionary *params = @{@"action":@"",
                         @"version":@"v1.0.0",
                         @"error":@0,
                         @"desc":@"SUCCESS",
                         @"result":@""
                         };
[webView sendMessageToWeb:params];
```

## 代码参考

##### 签名验证方法
* [java sdk 验签](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/interface.md#%E7%AD%BE%E5%90%8D%E9%AA%8C%E7%AD%BE)
* [ts sdk 验签](https://github.com/ontio/ontology-ts-sdk/blob/master/test/ecdsa.crypto.test.ts)

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
