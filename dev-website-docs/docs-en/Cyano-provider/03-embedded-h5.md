<h1 align="center">Wallet opens H5 DApp</h1>
<p align="center" class="version">Version 0.8.0 </p>

## Overview

This article is used to guide how the dApp party communicates with the wallet and how the wallet handles the dApp request.
The parties involved in the process include:

* Dapp side: Providing Dapp to users within the ONT ecosystem is an important part of the ontology ecosystem.
* Provider: wallet that implements the dApi mobile specification

## Interactive process description

DApp request data URI scheme：```ontprovider://ont.io?param=Base64.encode(Uri.encode({the json data}.toString()))```


<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/scenario3.png" ><br><br>
</div>

### Wallet opens H5 DApp

- 1 Wallet opens H5 DApp

### H5 DApp get Provider information

- 1 DApp request Provider information
- 2 wallet returns Provider information

### H5 DApp get account or identity information

- 1 DApp request account or identity information
- 2 User accepts request, returns account or identity information


### Login
- 1 DApp requests to sign the message ([DApp initiates login request](#DApp-initiates-login-request))
- 2 The wallet user signs the message and returns the signature data ([wallet response login request](#wallet-response-login-request))

### signMessage


### Invoke Smart contract
- 1 DApp request to call contract ([DApp initiates invoke smart contract request](#DApp-initiates-invoke-smart-contract-request))
- 2 wallet construction transaction, user signature
- 3 Wallet pre-executed transactions ([Pre-execution transaction](#Pre-execution-transaction))
- 4 wallet to send transactions
- 3 Wallet returns transaction Hash ([wallet response call contract request](#wallet-response-call-contract-request))



## Usage

### Precondition
Before using, you need to contact [Ontology institutional cooperation](https://info.ont.io/cooperation/en)


### get Provider information

#### DApp initiates query Provider information request

The data is as follows, **URI encoding, Base64 encoding** then send request：
```

{
	"action": "getProvider", 
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",		
	"version": "v1.0.0",
	"params": {
	}
}


```

|parameter|type|description|
| :---| :---| :---|
| action   |  string |   |

#### wallet response login request

**URI decoding, Base64 decoding**, the obtained data is as follows:
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

### Query account or identity information

#### DApp initiates query account or identity information request

The data is as follows, **URI encoding, Base64 encoding** then send request:
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

|parameter|type|description|
| :---| :---| :---|
| action   |  string |   |
| dappName   | string  | dapp name |
| dappIcon   | string  | dapp icon |

#### Wallet return account or identity information

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

### Login

#### DApp initiates a login request


The data is as follows, **URI encoding, Base64 encoding** then send request:
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

|parameter|type|description|
| :---| :---| :---|
| action   |  string |   |
| type   |  string |  type is "ontid" or "account" |
| dappName   | string  | dapp name |
| dappIcon   | string  | dapp icon |
| message   | string  |   |

#### Wallet responds to login request

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

|parameter|type|description|
| :---| :---| :---|
| action | string |  |
| result | string |  |
| type   |  string |  "ontid" or "account" |
| user | string |  |
| message   | string  |   |
| publickey | string | |
| signature  |  string |   |



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


### Message signature

Same as login, but the DApp name does not require a DApp name and icon.

The data is as follows, **URI encoding, Base64 encoding** then send request:

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


The data is as follows, **URI encoding, Base64 encoding** then send request:
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

|parameter|type|description|
| :---| :---| :---|
| action   |  string |   |
| type   |  string |  "ontid" or "account" |
| message   | string  |   |



### Invoke smart contract 

The action is invoke: Take the normal process.

The action is invokeRead: is a pre-executed transaction, the user does not need to sign, and returns the pre-execution result to the DApp.

The action is invokePasswordFree: Some games use the automatic bet function, such as betting once every 10 seconds, the user only needs to enter the password once. We only trust fixed methods and parameters, not all methods that trust the entire contract, so save the parameters of the transaction after entering the password (this parameter ((InvokeCode)txs[0]).code)), if the next request is The same data does not require a password to be entered again, nor does it require pre-execution. When the user leaves the current DApp, remember to clear the private key and parameters in memory.

#### DApp initiates a call contract request

The data is as follows, **URI encoding, Base64 encoding** send request:

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





#### Wallet response invoke smart contract request

**wallet first URI decoding, Base64 decoding**:

Wallet construction transaction
2. User signature
3. Pre-executed trading
4. User confirmation
5. Send the transaction to the chain
6. Return the trade hash to the DApp


* Return success to DApp

```
{
  "action": "invoke",
  "version": "v1.0.0",  
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",	 
  "error": 0,
  "desc": "SUCCESS",
  "result": "tx hash"
}
```

* Return failure to DApp

```
{
  "action": "invoke",
  "version": "v1.0.0",  
  "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",	  
  "error": 80001,
  "desc": "SEND TX ERROR",
  "result": ""
}
```

##### Pre-executed transaction

The Notify result returned by the pre-execution transaction can see how many ONTs/ONGs the user will spend in the transaction. Need to connect to the fixed node: main network: http://dappnode3.ont.io, test network: http://polaris5.ont.io

> Need to traverse Notify to make a judgment, because the transaction may have multiple transfers or other events, judge whether it is ONT or ONG through the contract address, and then judge the transfer method and the transfer party.

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

##### Signature Verification Method
* [java sdk Verification](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/interface.md#%E7%AD%BE%E5%90%8D%E9%AA%8C%E7%AD%BE)
* [ts sdk Verification](https://github.com/ontio/ontology-ts-sdk/blob/master/test/message.test.ts)

##### query smart contract
* [java sdk query smart contract](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/basic.md#%E4%B8%8E%E9%93%BE%E4%BA%A4%E4%BA%92%E6%8E%A5%E5%8F%A3)
* [ts sdk query smart contract](https://github.com/ontio/ontology-ts-sdk/blob/master/test/websocket.test.ts)

##### wallet
* [cyano-android](https://github.com/ontio-cyano/cyano-android)
* [cyano-ios](https://github.com/ontio-cyano/cyano-ios)

##### dApi-mobile client sdk
* [cyano-bridge](https://github.com/ontio-cyano/cyano-bridge)

##### dApi-mobile provider sdk
* [cyano-android-sdk](https://github.com/ontio-cyano/cyano-android-sdk)
* [cyano-ios-sdk](https://github.com/ontio-cyano/cyano-ios-sdk)