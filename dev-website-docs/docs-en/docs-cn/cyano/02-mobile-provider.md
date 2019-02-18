
`cyano-mobile` 是 [CEP-1](https://github.com/ontio-cyano/CEPs/blob/master/CEPS/CEP1.mediawiki#scenario-3-provider-opens-dapp) 提案的一套标准实现，将电脑端的 dApi 扩展到了移动端，涵盖了移动端 dApp 的三个使用场景。

- 集成了 `dAPI-mobile` 的钱包通过二维码进行账户登陆、智能合约的调用。
- 集成了 `cyano-sdk` 的 dApp 唤醒集成了 `dAPI-mobile` 的钱包。
- 集成了 `dAPI-mobile` 的钱包打开内嵌的 dApp 并进行账户登陆、智能合约的调用。

在 `cyano-mobile` 中，dApp 的数据请求 URL 遵循 `CEP-1` 规范：

```java
import android.net.Uri;
import android.util.Base64;

import com.alibaba.fastjson.JSON;

String param = Base64.encodeToString(Uri.encode(JSON.toJSONString(map)).getBytes(), Base64.NO_WRAP).toString();
String url = "ontprovider://ont.io?param=".concat(param);
```

同时，本体提供了实现了 `CEP-1` 移动端钱包：

- [Android](https://github.com/ontio-cyano/cyano-android) 端移动钱包。
- [IOS](https://github.com/ontio-cyano/cyano-ios) 端移动钱包

### 交互流程

#### 登陆

对于一个集成了 `dAPI-mobile` 的钱包 `W`，dApp 通过钱包进行登陆的流程如下。

1. 集成了 `dAPI-mobile` 的钱包扫描 dApp 提供的二维码。
2. 集成了 `dAPI-mobile` 的钱包解析出回调 URL 与验证用的消息 `msg`。
3. 集成了 `dAPI-mobile` 的钱包对 `msg` 进行签名，调用登陆方法。
4. `dApp` 验证签名，根据验证结果进行登陆流程的处理。

#### 调用智能合约

对于一个集成了 `dAPI-mobile` 的钱包 `W`，其调用 dApp 所要求的智能合约流程如下。

1. 钱包 `W` 扫描 dApp 提供的二维码。
2. 钱包 `W` 解析出交易参数。
3. 钱包 `W` 根据交易参数构造交易。
4. 钱包 `W` 提示用户签名。
5. 钱包 `W` 预执行交易，并将预执行结果发送给用户进行确认。
6. 用户确认预执行结果后，钱包 `W` 将交易发送到链上，返回交易哈希 `TxHash`。
7. dApp 根据交易哈希查询交易。

### 技术规范

#### 查询 Provider

- 请求数据

```json
{
    "action": "getProvider",
    "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
    "version": "v1.0.0",
    "params": {
    }
}
```

- 响应数据

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

### 查询账户信息

- 请求数据

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

| 字段     | 类型   | 定义          |
| :------- | :----- | :------------ |
| action   | string | 操作类型      |
| dappName | string | dapp名字      |
| dappIcon | string | dapp icon信息 |

- 响应数据

```json
{
    "action": "getAccount",
    "version": "v1.0.0",
    "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
    "error": 0,
    "desc": "SUCCESS",
    "result": "AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ"
}
```

### 查询身份信息

- 请求数据

```json
{
    "action": "getIdentity",
    "version": "v1.0.0",
    "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
    "params": {
        "dappName": "dapp Name",
        "dappIcon": "dapp Icon"
    }
}
```

| 字段     | 类型   | 定义          |
| :------- | :----- | :------------ |
| action   | string | 操作类型      |
| dappName | string | dapp名字      |
| dappIcon | string | dapp icon信息 |

- 响应数据

```json
{
    "action": "getIdentity",
    "version": "v1.0.0",
    "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
    "error": 0,
    "desc": "SUCCESS",
    "result": "did:ont:AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ"
}
```

### 消息签名

- 请求数据

```json
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

| 字段    | 类型   | 定义                                                                                 |
| :------ | :----- | :----------------------------------------------------------------------------------- |
| action  | string | 操作类型                                                                             |
| type    | string | 定义是使用ontid登录设定为"ontid"，钱包地址登录设定为"account"，不填就默认是"account" |
| message | string | 随机生成，用于校验身份                                                               |


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


#### 登陆

##### 二维码

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
        "expire": 1546415363,
        "callback": "http://101.132.193.149:4027/blockchain/v1/common/test-onto-login"
    }
}
```

| 字段     | 类型   | 定义                                                              |
| :------- | :----- | :---------------------------------------------------------------- |
| action   | string | 定义此二维码的功能，登录设定为"Login"，调用智能合约设定为"invoke" |
| id       | string | 消息序列号，可选                                                  |
| type     | string | 定义是使用ontid登录设定为"ontid"，钱包地址登录设定为"account"     |
| dappName | string | dapp名字                                                          |
| dappIcon | string | dapp icon信息                                                     |
| message  | string | 随机生成，用于校验身份                                            |
| expire   | long   | 可选                                                              |
| callback | string | 用户扫码签名后发送到DApp后端URL                                   |

##### dApp

- `POST` 请求

- 请求数据

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

| 字段      | 类型   | 定义                                                          |
| :-------- | :----- | :------------------------------------------------------------ |
| action    | string | 操作类型                                                      |
| id        | string | 消息序列号，可选                                              |
| params    | string | 方法要求的参数                                                |
| type      | string | 定义是使用ontid登录设定为"ontid"，钱包地址登录设定为"account" |
| user      | string | 用户做签名的账户，比如用户的ontid或者钱包地址                 |
| message   | string | 随机生成，用于校验身份                                        |
| publickey | string | 账户公钥                                                      |
| signature | string | 用户签名                                                      |

- 响应数据

```json
{
  "action": "login",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
  "error": 0,
  "desc": "SUCCESS",
  "result": true
}
```

```json
{
  "action": "login",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
  "error": 80001,
  "desc": "PARAMS ERROR",
  "result": 1
}
```

#### 执行智能合约

##### 二维码

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

| 字段      | 类型   | 定义                                                    |
| :-------- | :----- | :------------------------------------------------------ |
| action    | string | 操作类型，登录设定为"Login"，调用智能合约设定为"invoke" |
| qrcodeUrl | string | 二维码参数地址                                          |
| callback  | string | 选填，返回交易hash给dApp服务端                          |

!> 当 `action` 字段为 `invoke` 时，为执行智能合约；当 `action` 字段为 `invokeRead` 时，为预执行智能合约；当 `action` 字段为 `action是invokePasswordFree` 时，为免密执行智能合约。

##### dApp

- `GET` 请求

- 请求数据

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

- 响应数据

```json
{
  "action": "invoke",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a", 
  "error": 0,
  "desc": "SUCCESS",
  "result": "tx hash"
}
```

```json
{
  "action": "invoke",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a", 
  "error": 80001,
  "desc": "SEND TX ERROR",
  "result": 1
}
```

### Android SDK

`cyano-android-sdk` 基于 [CEP1](https://github.com/ontio-cyano/CEPs/blob/master/CEPS/CEP1.mediawiki) 进行实现，对 Android WebView 进行了封装，用于帮助基于 WebView 进行开发的 Android 手机端 dApp 与实现了 `CEP1` 规范的钱包之间进行通信。

!> `WebView` 的通信方式为 `window.postmeaage()`

#### 导入项目

你可以从[这里](https://github.com/ontio-cyano/cyano-android-sdk)获取完整的项目代码，然后将 `cyano-android-sdk` 以模块的形式导入到你的项目中。

#### 初始化

在调用 `cyano-andorid-sdk` 所提供的方法之前，你需要对其进行初始化。

```java
CyanoWebView cyanoWebView = new CyanoWebView(context);  
cyanoWebView.loadUrl(url);
```

更详细的使用方法，你可以点击[这里](https://github.com/ontio-cyano/cyano-android)查看我们提供的示例程序 `cyano-android`，点击[这里](http://101.132.193.149/files/app-debug.apk)获取示例程序的安装包。

### IOS SDK

`cyano-ios-sdk` 基于 [CEP1](https://github.com/ontio-cyano/CEPs/blob/master/CEPS/CEP1.mediawiki) 进行实现，对 IOS WebView 进行了封装，用于帮助基于 WebView 进行开发的 IOS 手机端 dApp 与实现了 `CEP1` 规范的钱包之间进行通信。

!> `WebView` 的通信方式为 `window.postmeaage()`

#### 导入项目

你可以从[这里](https://github.com/ontio-cyano/cyano-ios-sdk)获取完整的项目代码，然后将 `cyano-ios-sdk` 以模块的形式导入到你的项目中。

#### 初始化

在调用 `cyano-ios-sdk` 所提供的方法之前，你需要对其进行初始化。

```Objective-C
RNJsWebView * webView = [[RNJsWebView alloc]initWithFrame:CGRectZero];
[webView setURL:@""];
```

更详细的使用方法，你可以点击[这里](https://github.com/ontio-cyano/cyano-ios)查看我们提供的示例程序 `cyano-ios`。
