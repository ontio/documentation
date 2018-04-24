---
title: 
keywords: sample homepage
sidebar: ont_doc_zh
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

```createTime``` is the createTime of this wallet, in UTC format.

```identities``` is an array of Identity objects which describe the details of each Identity in the wallet.

```accounts``` is an array of Account objects which describe the details of each account in the wallet.

```extra``` is an object that is defined by the implementor of the client for storing extra data. This field can be null.

Here is an example as below:

```
{
	"name": "mywallet",
	"version": "1.0",
	"scrypt": {
		"n": 16384,
		"p": 8,
		"r": 8
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
  "p": 8
}
```
```n``` is a parameter that defines the CPU/memory cost. Must be a value 2^N.

```r``` is a tuning parameter.

```p``` is a tuning parameter (parallelization parameter). A large value of p can increase computational cost of SCrypt without increasing the memory usage.

## Identity

Identity object has the following structure:
```
{
  "ontid": "did:ont:TQLASLtT6pWbThcSCYU1biVqhMnzhTgLFq",
  "label": "MyIdentity",
  "lock": false,
  "controls": [],
  "extra": null
}
```
```ontid``` is the ontid of the identity.

```label``` is a label that the user has made to the identity.

```lock``` indicates whether the identity is locked by user. The client shouldn't update the infomation in a locked identity.

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
```algorithm``` is the algorithm used in encryption system.

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
  "address": "AQLASLtT6pWbThcSCYU1biVqhMnzhTgLFq",
  "label": "MyAddress",
  "lock": false,
  "algorithm": "ECDSA",
  "parameters": {},
  "key": "6PYWB8m1bCnu5bQkRUKAwbZp2BHNvQ3BQRLbpLdTuizpyLkQPSZbtZfoxx",
  "contract": {},
  "extra": null
}
```
```address``` is the base58 encoded address of the account.

```label``` is a label that the user has made to the account.

```lock``` indicates whether the account is locked by the user. The client shouldn't spend the funds in a locked account.

```algorithm``` is the algorithm used in encryption system.

```parameters``` is the array of parameter objects used in encryption system.

```key``` is the private key of the account in the NEP-2 format. This field can be null (for watch-only address or non-standard address).

```contract``` is a Contract object which describes the details of the contract. This field can be null (for watch-only addresses).

```extra``` is an object that is defined by the implementor of the client for storing extra data. This field can be null.

## Contract

Contract object has the following structure:
```
{
  "script": "21036dc4bf8f0405dcf5d12a38487b359cb4bd693357a387d74fc438ffc7757948b0ac",
  "parameters": [],
  "deployed": false
}
```

```script``` is the script code of the contract. This field can be null if the contract has been deployed to the blockchain.

```parameters``` is an array of Parameter objects which describe the details of each parameter in the contract function.

```deployed``` indicates whether the contract has been deployed to the blockchain.

## QR Code Specification 

This is a QR Code Specification for both indentity and account. 

```
{
	"type":"I",
	"label": "MyIdentity",
	"algorithm": "ECDSA",
	"key":"6PYT85poeK8XpuQhnroArEov64NfRsEeB4KiGD1YCoq5xU7sJrnXC92Vey",
	"parameters": {
		 "curve": "secp256r1"
	}
}
```

```type``` is used to distinguish between indentity or account, **I** indicates this is an indentity , **A** indicates this is an account.