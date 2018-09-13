---
title:
keywords: sample homepage
sidebar: SDKs_en
permalink: Wallet_File_Specification_en.html
folder: doc_en/SDKs
giturl: https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/Wallet_File_Specification_en.md
---

English / [中文](./Wallet_File_Specification_cn.html)


<h1 align="center">Wallet File Specification </h1>

<p align="center" class="version">Version 1.0.0 </p>





## Wallet

A wallet file in JSON format has the following basic structure:

```
{
  "name": "MyWallet",
  "version": "1.0",
  "scrypt": {},
  "defaultOntid": "did:ont:TJNxJe2Ty8eSCjCDxDPwiS78NRAn8XPTFL",
  "defaultAccountAddress": "TJNxJe2Ty8eSCjCDxDPwiS78NRAn8XPTFL",
  "createTime": "2018-03-14T03:12:30.862Z",
  "identities": [],
  "accounts": [],
  "extra": null
}
```
```name``` is a label that the user has given to the wallet file.

```version``` is currently fixed at 1.0 and will be used for functional upgrades in the future.

```scrypt``` is a ScryptParameters object which describe the parameters of SCrypt algorithm used for encrypting and decrypting the private keys in the wallet.

```defaultOntid``` indicates the default identity in this wallet.

```defaultAccountAddress``` indicates the default digital asset account's address in this wallet.

```createTime``` is the time this wallet was created, in UTC format.

```identities``` is an array of identity objects which describe the details of each identity in the wallet.

```accounts``` is an array of account objects which describe the details of each account in the wallet.

```extra``` is an object that is defined by the implementor of the client for storing extra data. This field can be null.

Here is an example as below:

```
{
	"name": "mickey",
	"defaultOntid": "",
	"defaultAccountAddress": "",
	"createTime": "2018-06-30T08:52:01.519Z",
	"version": "1.0",
	"scrypt": {
		"n": 4096,
		"r": 8,
		"p": 8,
		"dkLen": 64
	},
	"identities": [{
		"ontid": "did:ont:ATcHA9eYKyve8M74CB4p6Ssx7kwXjmREUa",
		"label": "mickey",
		"lock": false,
		"controls": [{
			"id": "1",
			"algorithm": "ECDSA",
			"parameters": {
				"curve": "P-256"
			},
			"key": "M+PnrYLVDrU0gkSzj0FAsvqCYv+HWEEUMDSyKSJACzJhZVglFU9tkfQKlLby5UCY",
			"address": "ATcHA9eYKyve8M74CB4p6Ssx7kwXjmREUa",
			"salt": "wwa12j4K0SyDP23+UDJNtA==",
			"enc-alg": "aes-256-gcm"
		}]
	}],
	"accounts": [{
		"address": "AJQLNWy9X6qdeEFrSH6UzgEjadSsRiYDCS",
		"label": "mickey",
		"lock": false,
		"algorithm": "ECDSA",
		"parameters": {
			"curve": "P-256"
		},
		"key": "qFbemAbu7fEjOJzAZZhGkmzp2YNxdSCuK7xyvhBAnUBX/FmAj2Ns84Y7frh6hfQv",
		"enc-alg": "aes-256-gcm",
		"salt": "u+SiqpRk17b0vIPesh4xXA==",
		"isDefault": false,
		"publicKey": "037fb6dfc9420e1d8275d9133d6d69fe64e8e3567241e7583234b9efa8b2ce7ae1",
		"signatureScheme": "SHA256withECDSA"
	}],
	"extra": null
}
```

## ScryptParameters

ScryptParameters object has the following structure:

```
{
  "n": 16384,
  "r": 8,
  "p": 8,
  "dkLen" : 64
}
```
```n``` is a parameter that defines the CPU/memory cost. Must be a value 2^N.

```r``` is a tuning parameter.

```p``` is a tuning parameter (parallelization parameter). A large value of p can increase computational cost of SCrypt without increasing the memory usage.

```dkLen``` is intended output length in octets of the derived key.

## Identity

Identity object has the following structure:
```
{
  "ontid": "did:ont:TQLASLtT6pWbThcSCYU1biVqhMnzhTgLFq",
  "label": "MyIdentity",
  "lock": false,
  "isDefault" : false,
  "controls": []
}
```
```ontid``` is the ontid of the identity.

```label``` is a label that the user has given to the identity.

```lock``` indicates whether the identity is locked by the user - the client shouldn't update the infomation in a locked identity.

```isDefault``` indicates whether the identity is the default identity.

```controls``` is an array of Control objects which describes the details of each controller in the identity.

## Control

Control object has the following structure:
```
{
  "algorithm": "ECDSA",
  "parameters": {},
  "id": "1",
  "key": "6PYWB8m1bCnu5bQkRUKAwbZp2BHNvQ3BQRLbpLdTuizpyLkQPSZbtZfoxx",
  "address": "AQkGLumU1tnyJBGV1ZUmD229iQf9KRTTDL",
  "salt": "Rv4v3a4U1zFEq28/"
}
```
```algorithm``` is the algorithm used in the encryption system.

```parameters``` is an array of parameter objects used in the encryption system.

```id``` is the identity of this control.

```key``` is the private key of the account in the NEP-2 format. This field can be null (for watch-only addresses or non-standard addresses).

```address```  address in base58 format.

```salt``` 16 byte salt value in base64 format.

## Parameter

Parameter object has the following structure:
```
{
  "curve":"P-256"
}
```
```curve``` is the name of the elliptic curve.

## Account

Account object has the following structure:
```
{
    "address": "AadQ5xRwrSsFTGzKfLHc1brzykdnf7phhD",
    "label": "a6575fd9",
    "lock": false,
    "algorithm": "ECDSA",
    "parameters": {
    	"curve": "P-256"
     },
    "key": "NyfxXX+xKDG2agrDy3espqX7N0k3MysTgqx5FxJGI8bkklZQO6+6BSluyBRvEsOx",
    "enc-alg": "aes-256-gcm",
    "salt": "MHct5XIedi86rQILJFi9lA==",
    "isDefault": false,
    "publicKey": "03e897f5a1ea306270e3e1e539c9065b6905e2430aae7f4802e1114f01634d7235",
    "signatureScheme": "SHA256withECDSA"
}
```
```address``` is the base58 encoded address of the account.

```enc-alg``` is the algorithm used to encrypt the private key.

```salt``` is the salt value for decryption.

```publicKey``` is the public key.

```signatureScheme``` is the signatureScheme used in signature.

```isDefault``` indicates whether the account is the default account.

```label``` is a label that the user has given to the account.

```lock``` indicates whether the account is locked by the user - the client shouldn't spend the funds in a locked account.

```algorithm``` is the algorithms used in the encryption system.

```parameters``` is an array of parameter objects used in encryption system.

```key``` is the private key of the account in the NEP-2 format. This field can be null (for watch-only addresses or non-standard addresses).



## QR Code Specification 

This QR Code Specification is for both identities and accounts. 

```
{
	"type":"I",
	"label": "MyIdentity",
	"algorithm": "ECDSA",
	"scrypt": {
		"n": 4096,
		"p": 8,
		"r": 8,
		"dkLen": 64
	},
	"key":"x0U3gy7mQMpzCYXwlt/oWZerSGaCUimSMN2UiSd2aKs=",
	"address" : "AQkGLumU1tnyJBGV1ZUmD229iQf9KRTTDL",
	"salt" : "Rv4v3a4U1zFEq28/",
	"parameters": {
		 "curve": "P-256"
	}
}
```

```type``` is used to distinguish between identity or account, **I** indicates this is an identity , **A** indicates this is an account.

```label``` is the label for the  identity or account.

```algorithm``` is the algorithm used for key/pair generation.

```parameters``` is the parameters of the key/pair generation algorithm.

```scrypt``` is an ScryptParameters object which describes the parameters of the SCrypt algorithm used for encrypting and decrypting the private keys in the wallet.

```key``` is the encrypted private key.

```address```  is the address in base58 format.

```salt``` 16 byte salt in base64 format.

