
## Overview

This article is aimed to guide dApps to integrate with the Provider, and to scan QR code to log in and scan invoke smart contracts and other services.
Participants involved in the process include:

* dApp developer: Providing dApps to users in the ONT ecosystem and is an important part of the Ontology ecosystem.
* Provider: Wallet that implements the DAPI mobile specification

## Interactive process description

![login-invoke](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/split-login-invoke.png)

### Login
1. dApp provides QR code ([Login QR code standard](#Login-QR-code-standard))
2. dApp server login interface ([DApp Server login interface](#DApp-Server-login-interface))
3. Return the verification result after dApp backend signature verification ([Signature verification method](#Signature-verification-method))

### Invoke SC
1. dApp provides QR code ([Call contract QR code standard](#Call-contract-QR-code-standard)
2. Provider constructs the transaction, user signature, pre-executed transaction, user confirmation, send to the chain, and finally return the transaction hash to the dApp backend
3. dApp backend query transaction event ([dApp Backend query transaction event](#dapp-backend-transaction-event-query))

## Integration step

### Precondition

Before use, you need to contact Ontology [Contact Us](https://ont.io/#/contactUs)。

### Login QR code standard
Scan QR code to acquire

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

|Field|Type|definition|
| :---| :---| :---|
| action   |  string | Define the function of this QR code, set the login to `Login`, and set the smart contract to `invoke`. |
| id   |  string |  Message serial number, optional |
| type   |  string | Use ontid login to set to `ontid`, wallet address login to `account` |
| dappName   | string  | dapp name |
| dappIcon   | string  | Dapp icon info |
| message   | string  | Randomly generated for verifying identity  |
| expire   | long  | optional  |
| callback   | string  | The user scans the signature and sends it to the DApp backend URL. |

### DApp Server login interface
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

|Field|Type|definition|
| :---| :---| :---|
| action | string | operation type |
| id | string | message serial number, optional |
| params | string | parameters required by the method |
| type | string | ontid login is set to `ontid`, wallet address login is set to `account` |
User | string | The account for user signature, such as the user's ontid or wallet address |
| message | string | Randomly generated for verifying identity |
Publickey | string | account public key |
| signature | string | User Signature |

#### Response
Success：

```json
{
  "action": "login",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
  "error": 0,
  "desc": "SUCCESS",
  "result": true
}
```

Failure：

```json
{
  "action": "login",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
  "error": 80001,
  "desc": "PARAMS ERROR",
  "result": 1
}
```


### Call contract QR code standard
Scan QR code to acquire

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

|Field|Type|Definition|
| :--- | :--- | :--- |
Action | string | Operation type, login set to `Login`, call smart contract set to `invoke`. |
qrcodeUrl | string | QR code parameter address |
Callback | string | Optional, return transaction hash to DApp server |

According to the qrcodeUrl link in the QR code, the GET data is as follows:

```json
{
	"action": "invoke",
	"version": "v1.0.0",
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
	"params": {
		"expire": 1546415363, //qrcode expire time
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
<p class = "info">When the contract is called, if the payer is not filled in the QR code, it will be filled in by the wallet. If the payer is filled in the QR code, the wallet should verify that it matches the wallet's asset address.</p>

The Provider constructs the transaction, performs user signatures, pre-executes transactions, sends transactions, and finally POST the transaction hash to the callback url.

Transaction successfully sent, POST to callback:

```
{
  "action": "invoke",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
  "error": 0,
  "desc": "SUCCESS",
  "result": "tx hash"
}
```

Transaction not sent, POST to callback:

```
{
  "action": "invoke",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
  "error": 80001,
  "desc": "SEND TX ERROR",
  "result": 1
}
```

## Code reference

##### Signature verification method
* [java sdk Signature verification](https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/interface.md#verify-signature)
* [ts sdk Signature verification](https://github.com/ontio/ontology-ts-sdk/blob/master/test/ecdsa.crypto.test.ts)

##### DApp Backend transaction event query
* [java sdk Transaction event query method](https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/basic.md)
* [ts sdk Transaction event query method](https://github.com/ontio/ontology-ts-sdk/blob/master/test/websocket.test.ts)

##### Wallet
* [cyano-android](https://github.com/ontio-cyano/cyano-android)
* [cyano-ios](https://github.com/ontio-cyano/cyano-ios)

##### dApi-mobile client sdk
* [cyano-bridge](https://github.com/ontio-cyano/cyano-bridge)

##### dApi-mobile provider sdk
* [cyano-android-sdk](https://github.com/ontio-cyano/cyano-android-sdk)
* [cyano-ios-sdk](https://github.com/ontio-cyano/cyano-ios-sdk)