---
title: 
keywords: sample homepage
sidebar: SDKs_zh
permalink: ontology_wallet_file_specification_zh.html
folder: doc_zh
---

[English](./ontology_wallet_file_specification_en.html) / 中文

<h1 align="center">Wallet File Specification</h1>
<p align="center" class="version">Version 0.7.0 </p>

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
	"name": "mywallet",
	"version": "1.0",
	"scrypt": {
		"n": 16384,
		"p": 8,
		"r": 8,
		"dkLen" : 64
	},
	"defaultOntid": "did:ont:AMs5NFdXPgCgC7Dci1FdFttvD42HELoLxG",
    "defaultAccountAddress": "AMs5NFdXPgCgC7Dci1FdFttvD42HELoLxG",
    "createTime": "2018-03-14T03:12:30.862Z",
    "identitys": [
		{
			"controls": [{
				"algorithm": "ECDSA",
				"id": "",
				"key": "6PYT85poeK8XpuQhnroArEov64NfRsEeB4KiGD1YCoq5xU7sJrnXC92Vey", //加密后的私钥
				"parameters": {
				    "curve": "secp256r1"
				}
			}],
			"label": "",
			"lock": false,
			"ontid": "did:ont:AMs5NFdXPgCgC7Dci1FdFttvD42HELoLxG"  //ontid,身份id
		}
	],
	"accounts": [
		{
			"address": "AMs5NFdXPgCgC7Dci1FdFttvD42HELoLxG",
			"algorithm": "ECDSA",
			"contract": {
				"deployed": false,
				"parameters": ["Signature"],
				"script": "210392a4dbb2a44da81e0942cee1a62ff4298e04ed463b88911b97de19a1597fa83dac"
			},
			"key": "6PYT85poeK8XpuQhnroArEov64NfRsEeB4KiGD1YCoq5xU7sJrnXC92Vey", //加密后的私钥
			"label": "",
			"lock": false,
			"parameters": {
				 "curve": "secp256r1"
			}
		}
	]
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

```dkLen``` is the intended output length in octets of the derived key.

## Identity

Identity object has the following structure:

```
{
  "ontid": "did:ont:TQLASLtT6pWbThcSCYU1biVqhMnzhTgLFq",
  "label": "MyIdentity",
  "lock": false,
  "isDefault" : false,
  "controls": [],
  "extra": null
}
```

```ontid``` is the ontid of the identity.

```label``` is a label that the user has made to the identity.

```lock``` indicates whether the identity is locked by user. The client shouldn't update the infomation in a locked identity.

```isDefault``` indicates whether the identity is default.

```controls``` is an array of Controller objects which describe the details of each controller in the identity.

```extra``` is an object that is defined by the implementor of the client for storing extra data. This field can be null.

## Control

Control object has the following structure:
```
{
  "algorithm": "ECDSA",
  "parameters": {},
  "id": "1",
  "key": "6PYWB8m1bCnu5bQkRUKAwbZp2BHNvQ3BQRLbpLdTuizpyLkQPSZbtZfoxx",
}
```
```algorithm``` is the algorithms used in encryption system.

```parameters``` is the array of parameter objects used in encryption system.

```id``` is the identify of this control.

```key``` is the private key of the account in the NEP-2 format. This field can be null (for watch-only address or non-standard address).

## Parameter

Parameter object has the following structure:
```
{
  "curve":"secp256r1"
}
```
```curve``` is the name of the elliptic curve.

## Account

Account object has the following structure:
```
{
  "address": "TA78QdiA6DgqD5Jc5AX97GQ2fPuCt98kqr",
  "enc-alg": "aes-256-ctr",
  "key": "AI08vJjflG4BH2+n+Uus+t1mr1sVSA/KwGoaRt83wKU=",
  "hash": "sha256",
  "algorithm": "SM2",
  "parameters": {
  	"curve": "sm2p256v1"
  },
  "label": "",
  "publicKey": "131402a7491e289e13cdea16833ccc0dd320abf8a7e93ebc4ae3854403910f3ce27ffc",
  "signatureScheme": "SM3withSM2",
  "isDefault": true,
  "lock": false,
  "passwordHash": "a665a45920422f9d417e4867efdc4fb8a04a1f3fff1fa07e998e86f7f7a27ae3"
}
```
```address``` is the base58 encoded address of the account.

```enc-alg``` the algorithm to encrypt private key.

```hash``` the hash algorithm to hash password.

```passwordHash``` the value of password after hash operation.

```publicKey``` the public key.

```signatureScheme``` the signatureScheme used in signature.

```isDefault``` indicates whether the account is default.

```label``` is a label that the user has made to the account.

```lock``` indicates whether the account is locked by user. The client shouldn't spend the funds in a locked account.

```algorithm``` is the algorithms used in encryption system.

```parameters``` is the array of parameter objects used in encryption system.

```key``` is the private key of the account in the NEP-2 format. This field can be null (for watch-only address or non-standard address).

```extra``` is an object that is defined by the implementor of the client for storing extra data. This field can be null.

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
		"r": 8
	},
	"key":"x0U3gy7mQMpzCYXwlt/oWZerSGaCUimSMN2UiSd2aKs=",
	"prefix" : "6P27U3I4",
	"parameters": {
		 "curve": "secp256r1"
	}
}
```

```type``` used to distinguish between identity or account, **I** indicates this is an identity , **A** indicates this is an account.

```label``` the lable of identity or account

```algorithm``` the algorithm for key pair generation

```parameters``` the parameters of the key pair generation algorithm

```scrypt``` the parameters for scrypt.

```key``` the encrypted private key

```prefix``` do two sha256 operations on the address, and get the first 4 bytes of the result.
