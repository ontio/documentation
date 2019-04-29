

This article is used to instruct DApp developer how to access Provider, login by scanning, and call a service of smart contract by scanning.

Participants involved in the process include:

* DApp developer: Providing dApps to users in ONT ecosystem, an important part of ecosystem.

* Provider: Wallet that implements the daApi mobile specification

## Interactive process description

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/split-login-invoke.png" ><br><br>
</div>

### Login
- 1.1 Provider scan the QRcode provided by DApp developer [Standard of login QRcode](#standard-of-login-qrcode)
- 1.2 Provider gets callback URL and msg for verification
- 2 Sign the msg and call the login method（[Login interface of DApp server](#login-interface-of-dapp-server)）
- 3 DApp backend verifies signature（[The method of verifying signature](#the-method-of-verifying-signature)）and then return result of verification.

### Invoke a smart contract
- 1.1 Provider scan the QRcode provided by DApp developer [Standard of invoking contract QRcode](#standard-of-invoking-contract-qrcode)
- 1.2 Use Provider to scan 
- 2 Provider builds a transaction and user signs it. Then Provider pre-executes the transaction and user confirms. Provider sends it to the blockchain, and a transaction hash wil be returned.
- 3 DApp backend queries the contract transaction（[The method of querying a contract](#the-method-of-querying-a-contract)）

## Docking for Wallet

### Prerequisite
Before using it，you need to contact [the Ontology cooperation](https://info.ont.io/cooperation/en)

### The process of login docking

#### Standard of login QRcode
Getting by scanning

```
{
	"action": "login",
    "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",  	
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

|Field|Type|Description|
| :---| :---| :---|
| action   |  string |  Define the function of QRcode, set login as "Login" and invoking a smart contract as "invoke" |
| type   |  string |  When login by ontid, setting as"ontid". When login by wallet address, setting as "account" |
| dappName   | string  | DApp name |
| dappIcon   | string  | dApp icon info |
| message   | string  | Random generated, it is used for verifying identity  |
| expire   | long  | Optional  |
| callback   | string  |  After user signs by scanning, the url sent to dApp backend|

### Login interface of DApp server
method: post 

```
{
	"action": "login",
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",  
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

|Field|Type|Description|
| :---| :---| :---|
| action | string | Operational type，login is set as "login" and  invoking a smart contract is set as "invoke" |
| params | string | params required by methods |
| type   |  string |  When login by ontid, setting as"ontid". When login by wallet address, setting as "account" |
| user | string | The account used for sign transactions |
| message   | string  | Random generated, it is used for verifying identity  |
| publickey | string | The public key of an account |
| signature  |  string |  User signature |

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


### Standard of invoking contract QRcode

getting by scanning

```
{
	"action": "invoke",
    "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",  	
	"version": "v1.0.0",
	"params": {
		"login": true,
		"callback": "http://101.132.193.149:4027/invoke/callback",		
		"qrcodeUrl": "http://101.132.193.149:4027/qrcode/AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ"
	}
}
```

|Field|Type|Description|
| :---        | :---    | :---                                                              |
| action      | string  | Operational type，login is set as "login" and  invoking a smart contract is set as "invoke" |
| qrcodeUrl         | string  | The address of QRcode params                                           |
| callback         | string  | Optional，it returns the contract hash to DApp server                                          |

According to the qrcodeUrl in the QRcode, the data is as follows.

```
{
	"action": "invoke",
    "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",  	
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


Provider builds a transaction and user signs it. Then Provider pre-executes the transaction and user confirms. Next, Provider sends it to the blockchain, and a transaction hash wil be returned. Finally, it posts transaction hash to callback url.

* Send transaction successfully and post it to callback

```
{
  "action": "invoke",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",    
  "error": 0,
  "desc": "SUCCESS",
  "result": "tx hash"
}
```

* Fail to send transaction and post it to callback

```
{
  "action": "invoke",
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",    
  "error": 80001,
  "desc": "SEND TX ERROR",
  "result": 1
}
```

##### Pre-execute a transaction

Pre-executing a transaction is optional. The purpose is that reminding users the ONT/ONG transfer amount spent in this transaction.

The Notify result returned from the pre-executed transaction can see how much ONT/ONG the user will spend on the transaction. Because the current node is not upgraded, you need to connect to the fixed node to pre-execute before returning Notify information: MainNet: http://dappnode 3.ont.io, TestNet: http://polaris5.ont.io.

> Notify needs to be traversed to make a judgment, because the transaction may have multiple transfer events or other contract events. If other contract events do not need to be processed, we determine whether ONT or ONG transfer through the contract address, and then determine the transfer method and the transferor. It is suggested that the UI display the amount and the transfer, and the transaction fee is about 0.01 ONG.

ONT:0100000000000000000000000000000000000000
ONG:0200000000000000000000000000000000000000

If pre-execute successfully，the result returned by node is：
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

If pre-execute failed，the value of error would be large than 0.


## Code reference

##### The method of verifying a signature
* [java sdk signature verification](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/interface.md#%E7%AD%BE%E5%90%8D%E9%AA%8C%E7%AD%BE)
* [ts sdk signature verification](https://github.com/ontio/ontology-ts-sdk/blob/master/test/ecdsa.crypto.test.ts)

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