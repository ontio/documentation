---
title:
keywords: sample homepage
sidebar: SDKs_zh
permalink: Wallet_File_Specification_cn.html
folder: doc_zh/SDKs
giturl: https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/Wallet_File_Specification_cn.md
---

[English](./Wallet_File_Specification_en.html) / 中文

<h1 align="center"> 钱包规范 </h1>

<p align="center" class="version">Version 1.0.0 </p>



钱包规范描述了钱包数据结构及导出数字身份或资产账号二维码的数据结构。

## 1. 钱包文件结构

钱包文件数据以json格式存储，文件名后缀并无要求，钱包文件数据结构如下:

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
参数描述：

```name``` 钱包名.

```version``` 钱包版本号.

```scrypt``` SCrypt算法参数.

```defaultOntid``` 钱包中的默认Ontid.

```defaultAccountAddress``` 钱包中默认账户地址.

```createTime``` 钱包创建时间.

```identities``` 身份列表.

```accounts``` 账户列表.

```extra``` 备用参数.

一个真实的钱包数据如下:

```json
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

### 1.1 Scrypt参数

SCrypt算法参数，Scrypt数据结构:

```json
{
  "n": 16384,
  "r": 8,
  "p": 8,
  "dkLen" : 64
}
```

参数描述：

```n``` 内存消耗，必须是 2^N.

```r``` 参数.

```p``` SCrypt算法的并行参数.

```dkLen``` 派生key的长度.

### 1.2 数字身份

数字身份数据结构:
```json
{
  "ontid": "did:ont:TQLASLtT6pWbThcSCYU1biVqhMnzhTgLFq",
  "label": "MyIdentity",
  "lock": false,
  "isDefault" : false,
  "controls": []
}
```
参数描述：

```ontid``` 身份id.

```label``` 昵称.

```lock``` 是否锁住该身份.

```isDefault``` 是否是默认使用的身份.

```controls``` 控制人.

#### Control数据结构

Control是数字身份的控制人，里面包含控制人的加密后算法名，私钥，公钥，地址，salt等。

```json
{
  "algorithm": "ECDSA",
  "parameters": {},
  "id": "1",
  "key": "6PYWB8m1bCnu5bQkRUKAwbZp2BHNvQ3BQRLbpLdTuizpyLkQPSZbtZfoxx",
  "address": "AQkGLumU1tnyJBGV1ZUmD229iQf9KRTTDL",
  "salt": "Rv4v3a4U1zFEq28/"
}
```
参数描述：

```algorithm``` 签名算法名称.

```parameters``` 曲线参数.

```id``` 控制人id.

```key``` 加密后私钥.

```address```  base58地址.

```salt``` 16字节的盐，以base64格式存储.


#### Parameter数据结构

签名算法参数数据结构
```json
{
  "curve":"P-256"
}
```
参数描述：

```curve``` is the name of the elliptic curve.

### 1.3 Account


资产账户信息```Account``` 数据结构:


```json
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
参数描述：

```address``` base58 地址.

```enc-alg``` 私钥加密算法名称.

```salt``` 16字节的盐，以base64格式存储.

```publicKey``` 公钥

```signatureScheme``` 签名算法体系.

```isDefault``` 是否是默认账户.

```label``` 昵称.

```lock``` 是否加锁.

```algorithm``` 签名算法名称.

```parameters``` 签名算法参数.

```key``` 加密后私钥.



## 2. 二维码规范 

身份和账号二维码的作用是方便通过扫描导入身份或账号，二维码同时支持数字身份和资产账号规范. 

```json
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
参数描述：

```type``` 类型, **I** 代表身份 , **A** 代表账号.

```label``` 昵称.

```algorithm``` 签名算法名.

```parameters``` 签名算法参数.

```scrypt``` scrypt参数.

```key``` 加密后私钥.

```address```  地址.

```salt``` 16字节的盐，以base64格式存储.

