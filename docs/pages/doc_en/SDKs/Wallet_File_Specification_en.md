---
title:
keywords: sample homepage
sidebar: SDKs_en
permalink: Wallet_File_Specification_en.html
folder: doc_en/SDKs
giturl: https://github.com/ontio/ontology-ts-sdk/blob/master/docs/en/Wallet_File_Specification.md
---

<h1 align="center">Wallet File Specification</h1>

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
```name``` is a label that the user has made to the wallet file.

```version``` is currently fixed at 1.0 and will be used for functional upgrades in the future.

```scrypt``` is a ScryptParameters object which describe the parameters of SCrypt algorithm used for encrypting and decrypting the private keys in the wallet.

```defaultOntid``` indicates the default identity in this wallet.

```defaultAccountAddress``` indicates the default digital assert account's address in this wallet.

```createTime``` is the createTime of this wallet,in UTC format.

```identities``` is an array of Identity objects which describe the details of each Identity in the wallet.

```accounts``` is an array of Account objects which describe the details of each account in the wallet.

```extra``` is an object that is defined by the implementor of the client for storing extra data. This field can be null.

Here is an example as below.

```
{
    "name": "mickey",
    "createTime": "2018-07-24T12:03:27Z",
    "defaultAccountAddress": "ATiHVFmvyUh2ULvg7Hr7LtdZC7v7NZGneF",
    "defaultOntid": "did:ont:AQibRo1HUY9XQb9xgk714AcpYfUMRZEqCJ",
    "version": "1.0",
	"accounts": [{
		"address": "ATiHVFmvyUh2ULvg7Hr7LtdZC7v7NZGneF",
		"algorithm": "ECDSA",
		"enc-alg": "aes-256-gcm",
		"hash": "sha256",
		"isDefault": true,
		"key": "09UafwhKPdpjJY3+YpRxk+Iah67k9Mtld774moPhKCroyD+AENGz/X4B6p43c9KF",
		"label": "9a9ba80c",
		"lock": false,
		"parameters": {
			"curve": "P-256"
		},
		"publicKey": "02799d9ee00408dc4352222d2dfc0e99964a8d691ea5d6324849dff5b3ee8e606e",
		"salt": "ZiWM7dQQL4Zz3wrnyt6csw==",
		"signatureScheme": "SHA256withECDSA"
	}],
	"identities": [{
		"controls": [{
			"address": "AQibRo1HUY9XQb9xgk714AcpYfUMRZEqCJ",
			"algorithm": "ECDSA",
			"enc-alg": "aes-256-gcm",
			"hash": "sha256",
			"id": "keys-1",
			"key": "VHFz9sfwarrMF6oUCZzDJNT4rIQHamJCXud8mC1LaUNFKK1FfjSAVWIVqqamngBS",
			"parameters": {
				"curve": "secp256r1"
			},
			"publicKey": "02580de64f61b3ba6e3513f152110d9f38c5c42cfc558bfdbe9b23a38713ef2389",
			"salt": "CR3vqQBFOSKniIlxqFWbmA=="
		}],
		"isDefault": true,
		"label": "0f4def16",
		"lock": false,
		"ontid": "did:ont:AazEvfQPcQ2GEFFPLF1ZLwQ7K5jDn81hve"
	}],
	"scrypt": {
		"dkLen": 64,
		"n": 16384,
		"p": 8,
		"r": 8
	}
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

```dkLen``` Intended output length in octets of the derived key.

## Identity

Identity object has the following structure:
```
{
  "ontid": "did:ont:AazEvfQPcQ2GEFFPLF1ZLwQ7K5jDn81hve",
  "label": "MyIdentity",
  "lock": false,
  "isDefault" : false,
  "controls": []
}
```
```ontid``` is the ontid of the identity.

```label``` is a label that the user has made to the identity.

```lock``` indicates whether the identity is locked by user. The client shouldn't update the infomation in a locked identity.

```isDefault``` indicates whether the identity is default.

```controls``` is an array of Controller objects which describe the details of each controller in the identity.

## Control

Control object has the following structure:
```
{
    "address": "AQibRo1HUY9XQb9xgk714AcpYfUMRZEqCJ",
    "algorithm": "ECDSA",
    "enc-alg": "aes-256-gcm",
    "hash": "sha256",
    "id": "keys-1",
    "key": "VHFz9sfwarrMF6oUCZzDJNT4rIQHamJCXud8mC1LaUNFKK1FfjSAVWIVqqamngBS",
    "parameters": {
        "curve": "secp256r1"
    },
    "publicKey": "02580de64f61b3ba6e3513f152110d9f38c5c42cfc558bfdbe9b23a38713ef2389",
    "salt": "CR3vqQBFOSKniIlxqFWbmA=="
}
```
```algorithm``` is the algorithms used in encryption system.

```parameters``` is the array of parameter objects used in encryption system.

```id``` is the identify index of this control.

```key``` is the private key of the account in the NEP-2 format. This field can be null (for watch-only address or non-standard address).

```address```  address in base58 format.

```salt``` 16 bytes salt value in base64 format.

```publicKey``` publicKey.

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
    "address": "ATiHVFmvyUh2ULvg7Hr7LtdZC7v7NZGneF",
    "algorithm": "ECDSA",
    "enc-alg": "aes-256-gcm",
    "hash": "sha256",
    "isDefault": true,
    "key": "09UafwhKPdpjJY3+YpRxk+Iah67k9Mtld774moPhKCroyD+AENGz/X4B6p43c9KF",
    "label": "9a9ba80c",
    "lock": false,
    "parameters": {
        "curve": "P-256"
    },
    "publicKey": "02799d9ee00408dc4352222d2dfc0e99964a8d691ea5d6324849dff5b3ee8e606e",
    "salt": "ZiWM7dQQL4Zz3wrnyt6csw==",
    "signatureScheme": "SHA256withECDSA"
}
```
```address``` is the base58 encoded address of the account.

```enc-alg``` the algorithm to encrypt private key.

```salt``` salt value for decryption.

```publicKey``` the public key.

```signatureScheme``` the signatureScheme used in signature.

```isDefault``` indicates whether the account is default.

```label``` is a label that the user has made to the account.

```lock``` indicates whether the account is locked by user. The client shouldn't spend the funds in a locked account.

```algorithm``` is the algorithms used in encryption system.

```parameters``` is the array of parameter objects used in encryption system.

```key``` is the private key of the account in the NEP-2 format. This field can be null (for watch-only address or non-standard address).

```publicKey``` publicKey.


## QR Code Specification 

This is QR Code Specification for both identity and account. 

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

```type``` used to distinguish between identity or account, **I** indicates this is an identity , **A** indicates this is an account.

```label``` the lable of identity or account

```algorithm``` the algorithm for key pair generation

```parameters``` the parameters of the key pair generation algorithm

```scrypt``` the parameters for scrypt.

```key``` the encrypted private key

```address```  address in base58 format.

```salt``` 16 bytes salt in base64 format.

