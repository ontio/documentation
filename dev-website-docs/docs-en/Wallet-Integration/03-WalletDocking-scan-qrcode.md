

## Overview

This article is used to guide the DApp party how to access the Provider, and use the scan code to log in, scan the code to call smart contracts and other services.
The parties involved in the process include:

* DApp side: Providing dApp to users within the ONT ecosystem is an important part of the ontology ecosystem.
* Provider: Wallet that implements the daApi mobile specification

## Interaction Process Description

![login-invoke](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/split-login-invoke.png)

### Login
- 1.1 Provider scans the QR code provided by dApp ([Login QR code standard](#Login-QR-code-standard)
- 1.2 Provider gets callback url and msg for authentication
- 2 Sign the msg and call the login method ([DApp server login interface](#DApp-server-login-interface))
- 3 dApp back verification signature ([Signature verification method] (#Signature-verification-method)) returns the verification result

### Invoke Smart contract
- 1.1 provider scans the QR code provided by dapp ([Calling contract QR code standard](#Calling-contract-QR-code-standard)
- 1.2 Using Provider Scan Code
- 2 Provider constructs the transaction, user signature, pre-executed transaction, user confirmation, send to the chain, return transaction hash to DApp backend
- 3 dApp backend query transaction ([DApp Backend query transaction event](#DApp-Backend-query-transaction-event)

## Integration Step

### Precondition
Before using, you need to contact[Contact Us](https://ont.io/#/contactUs)

### Login Integration Step

#### Login QR code standard
Scan code acquisition

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
		"ishex": false
		"expire": 1546415363, // QR Code expire time
		"callback": "http://101.132.193.149:4027/blockchain/v1/common/test-onto-login"
	}
}
```

|Field|Type|Definition|
| :---| :---| :---|
| action | string | Define the function of this QR code, set the login to "Login", and set the smart contract to "invoke" |
| id | string | message sequence number, optional |
| type | string | definition is set to "ontid" with ontid login, "account" for wallet address login |
| dappName | string | dapp name |
| dappIcon | string | dapp icon information |
| message | string | Randomly generated for verifying identity |
| ishex | bool | hex message |
| expire | long | Optional |
Callback | string | User scans the signature and sends it to the DApp backend URL |

### DApp server login interface
method: post

```
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

|Field|Type|Definition|
| :---| :---| :---|
| action | string | operation type |
| id | string | message sequence number, optional |
| params | string | parameters required by the method |
| type | string | definition is set to "ontid" with ontid login, "account" for wallet address login |
User | string | The account the user is signing, such as the user's ontid or wallet address |
| message | string | Randomly generated for verifying identity |
Publickey | string | account public key |
| signature | string | User Signature |

#### Response
* Success

```
{
  "action": "login",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
  "error": 0,
  "desc": "SUCCESS",
  "result": true
}
```

* Failed

```
{
  "action": "login",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
  "error": 80001,
  "desc": "PARAMS ERROR",
  "result": 1
}
```


### Calling contract QR code standard
Scan code acquisition

```
{
	"action": "invoke",
	"version": "v1.0.0",
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
	"params": {
		"login": true,
		"callback": "http://101.132.193.149:4027/invoke/callback",
	    "expire": 1546415363, // QR Code expire time
		"qrcodeUrl": "http://101.132.193.149:4027/qrcode/AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ"
	}
}
```

|Field|Type|Definition|
| :--- | :--- | :--- |
|Action | string | operation type, login is set to "Login", call smart contract is set to "invoke" |
|qrcodeUrl | string | QR code parameter address |
|callback | string | Optional, return transaction hash to dApp server |
|expire | long | Optional, QR Code expire time |

According to the qrcodeUrl link in the QR code, the data of GET is as follows:

```
{
	"action": "invoke",
	"version": "v1.0.0",
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
	"params": {
		"invokeConfig": {
			"contractHash": "16edbe366d1337eb510c2ff61099424c94aeef02", //smartcontract hash
			"functions": [{
				"operation": "method name", // invoke method in smartcontract
				"args": [{
					"name": "arg0-list", //type is Array
					"value": [true, 100, "Long:100000000000", "Address:AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ", "ByteArray:aabb", "String:hello", [true, 100], {
						"key": 6
					}]
				}, {
					"name": "arg1-map", //type is Map
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
                },{
                    "name": "arg2-ByteArray", //type is ByteArray
                    "value": "ByteArray:aabbcc"
                },{
                    "name": "arg2-int", //type is int or long
                    "value": 100
                },{
					"name": "arg2-str",  // type is string
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


Provider constructs a transaction, user signature, pre-executed transaction, send transaction, POST transaction hash to callback url.

* Send the transaction successfully POST to callback

```
{
  "action": "invoke",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
  "error": 0,
  "desc": "SUCCESS",
  "result": "tx hash"
}
```

* Send transaction failed to callback

```
{
  "action": "invoke",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
  "error": 80001,
  "desc": "SEND TX ERROR",
  "result": 1
}
```

##### Pre-executed trading

The pre-execution transaction is optional and its main function is to remind the user of the number of ONT/ONG transfers included in the transaction.

The Notify result returned by the pre-execution transaction can see how much ONT/ONG the user will spend in the transaction. Because the current node is not upgraded, you need to connect to the fixed node for pre-execution to return Notify information: main network: http://dappnode3.ont.io, test network: http://polaris5.ont.io

> Need to traverse Notify to make judgments, because the transaction may have multiple transfer events or other contract events. If other contract events do not need to be processed, the contract address is judged to be ONT or ONG, and then the transfer method and the transfer party are judged. It is recommended that the UI display the transfer to and from the transfer, and the transaction fee is approximately 0.01 ONG.

ONT:0100000000000000000000000000000000000000
ONG:0200000000000000000000000000000000000000

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

If pre-execution fails, the value of Error > 0.


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