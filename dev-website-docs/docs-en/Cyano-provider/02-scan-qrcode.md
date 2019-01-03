<h1 align="center">Scan QR code</h1>
<p align="center" class="version">Version 0.8.0 </p>

## Overview

This article is used to guide the DApp party how to access the Provider, and use the scan code to log in, scan the code to call smart contracts and other services.
The parties involved in the process include:

* DApp side: Providing dApp to users within the ONT ecosystem is an important part of the ontology ecosystem.
* Provider: wallet that implements the daApi mobile specification

## Interactive process description


<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/split-login-invoke.png" ><br><br>
</div>

### Login
- 1.1 Provider scans the QR code provided by dApp ([Login QR Code Standard](#Login-QR-Code-Standard))
- 1.2 Provider gets callback url and msg for verification
- 2 Sign the msg, call the login method ([DApp server login interface](#DApp-server-login-interface))
- 3 dApp backend verification signature ([Signature Verification Method](#Signature-Verification-Method)) returns the verification result

### Invoke Smart contract
- 1.1 provider scans the QR code provided by the dapp party ([Invoke smart contract QR code standard](#Invoke-smart-contract-QR-code-standard))
- 1.2 Using Provider Scan Code
- 2 Provider constructs transactions, user signatures, pre-executed transactions, user confirmation, sent to the chain, returns transaction hash
- 3 dApp backend query for this contract transaction ([query smart contract](#query-smart-contract))

## Usage

### Precondition
Before using, you need to contact [Ontology institutional cooperation](https://info.ont.io/cooperation/en)

### Login

#### Login QR Code Standard
Scan QR Code

```
{
	"action": "login",
	"version": "v1.0.0",
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

|parameter|type|description|
| :---| :---| :---|
| action   |  string | |
| type   |  string |  type is "ontid" or "account" |
| dappName   | string  | dapp name  |
| dappIcon   | string  | dapp icon |
| message   | string  |   |
| expire   | long  |   |
| callback   | string  |  |

### DApp server login interface
method: post 

```
{
	"action": "login",
	"version": "v1.0.0",
	"params": {
		"type": "ontid or account",
		"user": "did:ont:AUEKhXNsoAT27HJwwqFGbpRy8QLHUMBMPz",
		"message": "helloworld",
		"publickey": "0205c8fff4b1d21f4b2ec3b48cf88004e38402933d7e914b2a0eda0de15e73ba61",
		"signature": "01abd7ea9d79c857cd838cabbbaad3efb44a6fc4f5a5ef52ea8461d6c055b8a7cf324d1a58962988709705cefe40df5b26e88af3ca387ec5036ec7f5e6640a1754"
	}
}
```

|parameter|type|description|
| :---| :---| :---|
| action | string | action |
| params | string | params |
| type   |  string |  type is "ontid" or "account" |
| user | string |  |
| message   | string  |  |
| publickey | string |  |
| signature  |  string |   |

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


### Invoke smart contract QR code standard
Scan QR Code

```
{
	"action": "invoke",
	"version": "v1.0.0",
	"params": {
		"login": true,
		"callback": "http://101.132.193.149:4027/invoke/callback",		
		"qrcodeUrl": "http://101.132.193.149:4027/qrcode/AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ"
	}
}
```

|parameter|type|description|
| :---        | :---    | :---                                                              |
| action      | string  |  |
| qrcodeUrl         | string  |                                            |
| callback         | string  |                                           |

According to the qrcodeUrl link in the QR code, the data of the GET is as follows:

```
{
	"action": "invoke",
	"version": "v1.0.0",
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



Provider constructs transactions, user signatures, pre-executed transactions, sends transactions, POST transaction hashes to callback urls.

* Send the transaction successfully POST to the callback

```
{
  "action": "invoke",
  "error": 0,
  "desc": "SUCCESS",
  "result": "tx hash"
}
```

* Send transaction failed to callback

```
{
  "action": "invoke",
  "error": 8001,
  "desc": "SEND TX ERROR",
  "result": 1
}
```

##### Pre-executed transaction

The pre-execution transaction is optional and its main function is to remind the user of the number of ONT/ONG transfers included in the transaction.

The Notify result returned by the pre-execution transaction can see how many ONTs/ONGs the user will spend in the transaction. Because the current node is not upgraded, you need to connect to the fixed node pre-execution to return Notify information: main network: http://dappnode3.ont.io, test network: http://polaris5.ont.io

> Need to traverse Notify to make judgments, because the transaction may have multiple transfer events or other contract events. If other contract events do not need to be processed, the contract address is judged to be ONT or ONG, and then the transfer method and the transfer party are judged. It is recommended that the UI display the transfer to and from the export, and the transaction fee is approximately 0.01 ONG.
ONT: 0100000000000000000000000000000000000000
ONG: 0200000000000000000000000000000000000000

If the pre-execution is successful, the result returned by the node is:
```
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

Prepare execution fail, Error > 0。


## Code reference

##### Signature Verification Method
* [java sdk Verification](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/interface.md#%E7%AD%BE%E5%90%8D%E9%AA%8C%E7%AD%BE)
* [ts sdk Verification](https://github.com/ontio/ontology-ts-sdk/blob/master/test/message.test.ts)

##### query smart contract
* [java sdk query smart contract](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/basic.md#%E4%B8%8E%E9%93%BE%E4%BA%A4%E4%BA%92%E6%8E%A5%E5%8F%A3)
* [ts sdk query smart contract](https://github.com/ontio/ontology-ts-sdk/blob/master/test/websocket.test.ts)

##### wallet
* [cyano-android](https://github.com/ontio-cyano/cyano-android)
* [cyano-ios](https://github.com/ontio-cyano/cyano-ios)
* [WebViewActivity.java](https://github.com/ontio-cyano/cyano-android/blob/master/CyanoWallet/app/src/main/java/com/github/ont/cyanowallet/game/GameWebActivity.java)
* [DAppViewController.m](https://github.com/ontio-cyano/cyano-ios/blob/master/Cyano%20Wallet/Cyano%20Wallet/Classes/View/Discover/DAppViewController.m)

##### dApi-mobile client sdk
* [cyano-dapi-mobile](https://github.com/ontio-cyano/cyano-dapi-mobile)

##### dApi-mobile provider sdk
