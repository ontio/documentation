<h1 align="center">Wallet Docking - The Docking Process for Wallet to Open DApp</h1>
<p align="center" class="version">Version 0.8.0 </p>

## Overview

This article is used to instruct dApp developer how to communicate with wallet and how wallet deals with the requests from dApp.
Participants involved in the process include:

* DApp developer: Providing DApps to users in ONT ecosystem, an important part of ecosystem.

* Provider: Wallet that implements the dApi mobile specification

## Interactive process description

URI scheme for DApp to request data：```ontprovider://ont.io?param=Base64.encode(Uri.encode({the json data}.toString()))```

![login-invoke](images/scenario3.png)

### Wallet opens a H5 dApp

- 1 Wallet opens a H5 dApp

### H5 DApp requests the info from Provider

- 1 DApp requests the info of Provider
- 2 Wallet returns the info of Provider

### H5 DApp requests account or identity info

- 1 DApp requests account or identity info
- 2 User accepts the request and returns the account or identity info


### Login
- 1 DApp requests a signature for message（[DApp requests login](#dapp-requests-login)）

- 2 Wallet user signs the message and returns the signature data（[Wallet responds to login request](#wallet-responds-to-login-requests)）

### Sign message


### Invoke a smart contract
- 1 DApp requests for invoking smart contracts（[DApp requests invoking a smart contract](#dapp-requests-invoking-a-smart-contract)）
- 2 Wallet builds a transaction and user signs it
- 3 Wallet pre-executes the transaction（[Pre-execute transaction](#pre-execute-transaction)）   
- 4 Wallet sends transaction
- 5 Wallet returns the transaction hash（[Wallet responds to contract request](#wallet-responds-to-contract-request)）



## The docking process for wallet and DApp

### Prerequisite
Before using it，you need to contact [the Ontology cooperation](https://info.ont.io/cooperation/en)


### dAPI Provider SDK使用

The dAPI Provider SDK helps communication between Android webview and dApp. It encapsulates some methods for webview. Support Android, iOS:
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
             
            }
	});
	
cyanoWebView.getNativeJsBridge().setHandleInvoke(new NativeJsBridge.HandleInvoke() {
            @Override
            public void handleAction(String data) {
               
            }
	});	

cyanoWebView.getNativeJsBridge().setHandleInvokeRead(new NativeJsBridge.HandleInvokeRead() {
        @Override
        public void handleAction(String data) {
           
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


```
RNJsWebView * webView = [[RNJsWebView alloc]initWithFrame:CGRectZero];
[webView setURL:@""];
```

iOS-sdk：

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


### The procedure for querying info of Provider

#### DApp initiates query request for Provider info

The data is as follows. Sending request after **URI encoding，Base64 encoding**：
```

{
	"action": "getProvider", 
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",	
	"version": "v1.0.0",
	"params": {
	}
}


```

|Field|Type|Description|
| :---| :---| :---|
| action   |  string |  Operational type |

#### Wallet returns the info of Provider

The data is as follows after **URI decoding，Base64 decoding**：
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

### The procedure for querying account or identity

#### DApp initiates a query for account or identity info

The data is as follows. Sending request after **URI encoding，Base64 encoding**：
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

|Field|Type|Description|
| :---| :---| :---|
| action   |  string |  Operational type |
| dappName   | string  | dapp name |
| dappIcon   | string  | dapp icon info |

#### Wallet returns account or identity info

The data is as follows after **URI decoding，Base64 decoding**：
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

### Login process

#### DApp requests login


The data is as follows. Sending request after **URI encoding，Base64 encoding**：
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

|Field|Type|Description|
| :---| :---| :---|
| action   |  string |  Operational type |
| type   |  string |  When login by ontid, setting as"ontid". When login by wallet address, setting as "account" |
| dappName   | string  | dapp name |
| dappIcon   | string  | dapp icon info |
| message   | string  | Random generated, it is used for verifying identity  |

#### Wallet responds to login request

The data is as follows after **URI decoding，Base64 decoding**：

* the returned data after sending successfully
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

|Field|Type|Description|
| :---| :---| :---|
| action | string | Operational type |
| result | string | Returned result |
| type   |  string |  When login by ontid, setting as"ontid". When login by wallet address, setting as "account" |
| user | string | The account for user signature such as user ontid or wallet address |
| message   | string  |Random generated, it is used for verifying identity  |
| publickey | string | Account public key |
| signature  |  string |  User signature |



* the returned data after failed sending

```
{
  "action": "login",
  "version": "v1.0.0",  
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a", 
  "error": 8001,
  "desc": "PARAMS ERROR",
  "result": 1
}
```


### The procedure for message signature

Same as login, but the DApp name and icon are not required.

The data is as follows. Sending request after **URI encoding，Base64 encoding**：

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


The data is as follows. Sending request after **URI encoding，Base64 encoding**：
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

|Field|Type|Description|
| :---| :---| :---|
| action   |  string |  Operational type |
| type   |  string |  When login by ontid, setting as"ontid". When login by wallet address, setting as "account", the default is "account" |
| message   | string  | Random generated, it is used for verifying identity  |


### The procedure for invoking a contract

If action is invoke, executing normal process.


If action is invokeRead, it is a pre-executing transaction and users do not need to sign the transaction. The result will be returned to DApp.

If action is invokePasswordFree, 
Some games use the automatic bet function, such as betting once every 10 seconds. For a better game experience, the user only needs to enter the password once. We only trust fixed methods and parameters, not all methods in the entire contract, so saving the parameters of the transaction after entering the password (this parameter is ((InvokeCode)txs[0]).code)). If the next request is the same data,  the system will not require the password and pre-execution again. Before leaving the current DApp, users need to remember to clear the private key and parameters in memory.

#### DApp requests invoking a smart contract

The data is as follows. Sending request after **URI encoding，Base64 encoding**：

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


#### Wallet responds to contract request

**Wallet is decoded by URI at first and then is decoded by Base64**：

1. Wallet builds transaction
2. User signs it
3. Pre-executing the transaction
4. User confirms
5. Sending the transaction to blockchain
6. Returning transaction hash to DApp



* the returned data after sending successfully

```
{
  "action": "invoke",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a", 
  "error": 0,
  "desc": "SUCCESS",
  "result": "tx hash"
}
```

* the returned data after a failed sending

```
{
  "action": "invoke",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",  
  "error": 80001,
  "desc": "SEND TX ERROR",
  "result": ""
}
```

##### Pre-execute transaction

Pre-executing a transaction is optional. The purpose is that reminding users the ONT/ONG transfer amount spent in this transaction. You need to connect to the fixed node to pre-execute before returning Notify information: MainNet: http://dappnode 3.ont.io, TestNet: http://polaris5.ont.io.


> Notify needs to be traversed to make a judgment, because the transaction may have multiple transfer events or other contract events. We determine whether it is ONT or ONG transfer through the contract address, and then determine the transfer method and the transferor. 


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

##### The method of verifying a signature
* [java sdk signature verification](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/interface.md#%E7%AD%BE%E5%90%8D%E9%AA%8C%E7%AD%BE)
* [ts sdk signature verification](https://github.com/ontio/ontology-ts-sdk/blob/master/test/message.test.ts)

##### The method of querying a contract
* [java sdk contract query](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/basic.md#%E4%B8%8E%E9%93%BE%E4%BA%A4%E4%BA%92%E6%8E%A5%E5%8F%A3)
* [ts sdk contract query](https://github.com/ontio/ontology-ts-sdk/blob/master/test/websocket.test.ts)

##### Wallet
* [cyano-android](https://github.com/ontio-cyano/cyano-android)
* [cyano-ios](https://github.com/ontio-cyano/cyano-ios)

##### dApi-mobile client sdk
* [cyano-bridge](https://github.com/ontio-cyano/cyano-dapi-mobile)

##### dApi-mobile provider sdk
* [cyano-android-sdk](https://github.com/ontio-cyano/cyano-android-sdk)
* [cyano-ios-sdk](https://github.com/ontio-cyano/cyano-ios-sdk)