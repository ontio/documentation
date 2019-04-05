
<h1 align="center">Open the dApp access process inside the wallet</h1>
<p align="center" class="version">Version 0.8.0 </p>

## Overview

This article is used to guide how the dApp party communicates with the wallet and how the wallet handles the dApp request.
The parties involved in the process include:

* Dapp side: Providing Dapp to users within the ONT ecosystem is an important part of the ontology ecosystem.
* Provider: Wallet that implements the dApi mobile specification

## Interaction Process Description

DApp request data URI scheme: ```ontprovider://ont.io?param=Base64.encode(Uri.encode({the json data}.toString()))```

![login-invoke](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/scenario3.png)

### Wallet open H5 DApp

- 1 wallet open H5 DApp

### H5 DApp Get Provider Information

- 1 DApp Request Provider Information
- 2 wallet returns Provider information

### H5 DApp Get account or identity information

- 1 DApp request account or identity information
- 2 User accepts request, returns account or identity information


### Login
- 1 DApp requests signature of message ([DApp initiates a login request](#DApp-initiates-a-login-request)
- 2 The wallet user signs the message and returns the signature data ([Wallet responding to login request](#Wallet-responding-to-login-request))

### signMessage


### Invoke Smart contract
- 1 DApp request call contract ([DApp initiates a call contract request](#DApp-initiates-a-call-contract-request)
- 2 wallet construction transaction, user signature
- 3 wallet pre-executed transactions ([Pre-executed trading](#Pre-executed-trading))
- 4 wallet to send transactions
- 3 Wallet return call request [Wallet response call contract request](#Wallet-response-call-contract-request)



## Wallet and DApp Access Steps

### Prerequisites
Before using, you need to contact [institutional cooperation] (https://info.ont.io/cooperation/en)


## dAPI Provider SDK use

The dAPI Provider SDK helps communication between Android webview and web dapp. It encapsulates some methods for webview. Support Android, iOS, please refer to:

* [cyano-android-sdk](https://github.com/ontio-cyano/cyano-android-sdk)
* [cyano-ios-sdk](https://github.com/ontio-cyano/cyano-ios-sdk)

Android-sdk：

```
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
                * 1. Pop-up password input box, solve the wallet account, build data transaction,   sign the transaction, pre-execute the result, pay attention to time-consuming operation.
                *
                * 2. Parsing the predicted line result out of the Notify result, showing the handling fee. If the result includes the ONT, ONG contract address, the transfer amount and the receiving address must be displayed.
                *
                * 3. After the user confirms, send the transaction to the chain.
                *
                * 4. Send the transaction hash to the webView
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
                * 1. Build data to build transactions, pre-execute the results, pay attention to time-consuming operations.
                 *
                 * 2. Send the predicted line result to webView
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
* 1. The first operation is the same as action: Invoke, while saving password and message
            *
            * 2. When the same message is received the second time, it will be signed with the saved password, and the prediction line will get the result.
            *
            * 3. Predictive line results do not need to be displayed to the user for confirmation
            *
            * 4. Send transaction hash to webView
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

### Query Provider Information Steps

#### DApp Initiate Query Provider Information Request

The data is as follows, ** URI encoding, Base64 encoding ** send request:
```

{
	"action": "getProvider",
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
	"version": "v1.0.0",
	"params": {
	}
}


```

|Field|Type|Definition|
| :---| :---| :---|
| action | string | operation type |

#### Wallet returns Provider information

** URI decoding, Base64 decoding **, the obtained data is as follows:
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

### Query account or identity information steps

#### DApp initiates a query account or identity information request

The data is as follows, **URI encoding, Base64 encoding** after sending the request:
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

|Field|Type|Definition|
| :---| :---| :---|
| action | string | operation type |
| dappName | string | dapp name |
| dappIcon | string | dapp icon information |

#### Wallet returns account or identity information

**URI decoding, Base64 decoding**, the obtained data is as follows:
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

### Login step

#### DApp initiates a login request


The data is as follows, **URI encoding, Base64 encoding** after sending the request:
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

|Field|Type|Definition|
| :---| :---| :---|
| action | string | operation type |
| type | string | definition is set to "ontid" with ontid login, "account" for wallet address login |
| dappName | string | dapp name |
| dappIcon | string | dapp icon information |
| message | string | Randomly generated for verifying identity |

#### Wallet responding to login request

**URI decoding, Base64 decoding**, the obtained data is as follows:

* Return successful content
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

|Field|Type|Definition|
| :---| :---| :---|
| action | string | operation type |
| result | string | return result |
| type | string | definition is set to "ontid" with ontid login, "account" for wallet address login |
User | string | The account the user is signing, such as the user's ontid or wallet address |
| message | string | Randomly generated for verifying identity |
Publickey | string | account public key |
| signature | string | User Signature |



* Return failed content
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


### Message Signing Step

Same as login, but the DApp name does not require a DApp name and icon.

The data is as follows, **URI encoding, Base64 encoding** after sending the request:

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
#### DApp initiates a signature request


The data is as follows, **URI encoding, Base64 encoding** after sending the request:
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

|Field|Type|Definition|
| :---| :---| :---|
| action | string | operation type |
| type | string | definition is set to "ontid" with ontid login, "account" for wallet address login, "account" if not filled
| message | string | Randomly generated for verifying identity |



### Calling contract steps

Action is invoke: Going through the normal process.

Action is invokeRead: is a pre-executed transaction, the user does not need to sign, return the pre-execution result to the DApp.

Action is invokePasswordFree: Some games use automatic betting, such as betting every 10 seconds, the user only needs to enter the password once. We only trust fixed methods and parameters, not all methods that trust the entire contract, so save the parameters of the transaction after entering the password (this parameter ((InvokeCode)txs[0]).code)), if the next request is The same data does not require a password to be entered again, nor does it require pre-execution. When the user leaves the current DApp, remember to clear the private key and parameters in memory.



#### DApp initiates a call contract request

The data is as follows, **URI encoding, Base64 encoding** after sending the request:

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


#### Wallet response call contract request

** wallet first URI decoding, Base64 decoding**:

Wallet construction transaction
2. User signature
3. Pre-executed trading
4. User confirmation
5. Send the transaction to the chain
6. Return to the transaction hash to DApp



* Return the transaction to DApp

```
{
  "action": "invoke",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
  "error": 0,
  "desc": "SUCCESS",
  "result": "tx hash"
}
```

* Return failed to DApp

```
{
  "action": "invoke",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
  "error": 80001,
  "desc": "SEND TX ERROR",
  "result": ""
}
```

##### Pre-executed trading

The Notify result returned by the pre-execution transaction can see how much ONT/ONG the user will spend in the transaction. Need to connect to the fixed node: main network: http://dappnode3.ont.io, test network: http://polaris5.ont.io

> Need to traverse Notify to make a judgment, because the transaction may have multiple transfers or other events, determine whether it is ONT or ONG through the contract address, and then determine the transfer method and the transfer party.

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



## Code reference

##### Signature verification method
* [java sdk Signature check](https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/interface.md#verify-signature)
* [ts sdk Signature check](https://github.com/ontio/ontology-ts-sdk/blob/master/test/ecdsa.crypto.test.ts)

##### DApp Backend query transaction event
* [java sdk Transaction event query method](https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/basic.md)
* [ts sdk Transaction event query method](https://github.com/ontio/ontology-ts-sdk/blob/master/test/websocket.test.ts)

##### wallet
* [cyano-android](https://github.com/ontio-cyano/cyano-android)
* [cyano-ios](https://github.com/ontio-cyano/cyano-ios)

##### dApi-mobile client sdk
* [cyano-bridge](https://github.com/ontio-cyano/cyano-bridge)

##### dApi-mobile provider sdk
* [cyano-android-sdk](https://github.com/ontio-cyano/cyano-android-sdk)
* [cyano-ios-sdk](https://github.com/ontio-cyano/cyano-ios-sdk)