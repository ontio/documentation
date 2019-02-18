

<h1 align="center">Wallet File Specification </h1>

<p align="center" class="version">Version 1.0.0 </p>





## 월렛

JSON형식의 월렛 파일의 기본 구조

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
```name``` 월렛 이름

```version``` 월렛 버전

```scrypt``` Scrypt 알고리즘 파라미터

```defaultOntid``` 월렛중의 기본 Ontid

```defaultAccountAddress``` 월렛중의 기본 계정주소

```createTime``` 월렛 생성 시간

```identities``` 신분목록

```accounts``` 계정목록

```extra``` 엑스트라 파라미터

진짜 월렛 데이터는 아래와 같습니다.

```
{
        "name": "com.github.ontio",
	"scrypt": {
		"dkLen": 64,
		"n": 16384,
		"p": 8,
		"r": 8
	},
	"version": "1.0"，
	"createTime": "2018-09-26T18:02:26Z",
	"defaultAccountAddress": "APyT9ZrjDsvq6cRWPaVq3Fu3zFjP33FUq4",
	"defaultOntid": "did:ont:AXFZPQivJK2NTxJDnE6vsrFfyyfnEQSqX6",
	"accounts": [{
		"address": "APyT9ZrjDsvq6cRWPaVq3Fu3zFjP33FUq4",
		"algorithm": "ECDSA",
		"enc-alg": "aes-256-gcm",
		"hash": "sha256",
		"isDefault": true,
		"key": "w29DODefaYPg2LKT9FW6/QziPAmVH7Q/NX9nobO3tteRRq2Tg3Hm72gNkyvJlg97",
		"label": "abaed057",
		"lock": false,
		"parameters": {
			"curve": "P-256"
		},
		"publicKey": "025a61aced9838fed2ffe0267ddcdd62159f51fcbc4fce7eb162d30d43da6fecc9",
		"salt": "dQ3ubLtvOQ4VEzN1l1aq8Q==",
		"signatureScheme": "SHA256withECDSA"
	}],
	"identities": [{
		"controls": [{
			"address": "AXFZPQivJK2NTxJDnE6vsrFfyyfnEQSqX6",
			"algorithm": "ECDSA",
			"enc-alg": "aes-256-gcm",
			"hash": "sha256",
			"id": "keys-1",
			"key": "oZ8kkH0MhKYNAIPA5WACsK93ghHqnTQU3oeC3bqPQ4KYRVXHOUwiLhgiWV+BIB9D",
			"parameters": {
				"curve": "secp256r1"
			},
			"publicKey": "02f866847298a7847c714c457dcc63122b946bd014b32e7c365a7bc89fefc2bdd8",
			"salt": "/OwXiTC9k3tzDN8bTigXew=="
		}],
		"isDefault": true,
		"label": "d6a5b3b3",
		"lock": false,
		"ontid": "did:ont:AXFZPQivJK2NTxJDnE6vsrFfyyfnEQSqX6"
	}]
	
}
```

## Scrypt 파라미터 

Scrypt 알고리즘 파라미터, Scrypt데이터 구조

```
{
  "n": 16384,
  "r": 8,
  "p": 8,
  "dkLen" : 64
}
```
```n``` 메모리 소비는 2^N이어야 합니다.

```r``` 매개변수

```p``` SCrypt알고리즘의 병행 파라미터

```dkLen``` key의 길이 생성

## ID

디지털 ID데이터 구조
```
{
  "ontid": "did:ont:TQLASLtT6pWbThcSCYU1biVqhMnzhTgLFq",
  "label": "MyIdentity",
  "lock": false,
  "isDefault" : false,
  "controls": []
}
```
```ontid``` 신분 id

```label``` 계정에 부여한 

```lock``` 신분 잠김/해지

```isDefault``` 기본 ID 여부확인

```controls``` 컨트롤러

## 컨트롤

Control의 기본 구조
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
```algorithm``` 암호화 시스템에서 사용되는 알고리즘

```parameters``` 암호화 시스템에서 사용되는 파라미터 객체의 배열

```id``` 컨트롤의 ID입니다.

```key``` NEP-2형식의 계정 프라이빗키입니다. 

```address```  base58 주소

```salt``` base64형식의 16바이트 솔트 값

## 파라미터

Parameter의 기본 구조
```
{
  "curve":"P-256"
}
```
```curve``` 타원 곡선의 이름
## Account

Account의 기본 구조
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
```address``` base58 주소

```enc-alg``` 프라이빗 키 암호화 알고리즘 이름

```salt``` 해독을 위한 솔트값

```publicKey``` 퍼블릭 키

```signatureScheme``` 시그니처에 사용되는 signatureScheme

```isDefault``` 기본 계정 여부 확인

```label``` 계정에 부여한 레이블

```lock``` 계정이 사용자에의해 잠겨있는지 여부 판단, 클라이언트는 잠긴 계정으로 자금 지출을 하면 안됩니다.

```algorithm``` 암호화 시스템에서 사용하는 알고리즘

```parameters``` 암호화 시스템에서 사용되는 파라미터 객체의 배열

```key``` NEP-2형식의 계정 프라이빗키입니다.



## QR Code 표준

ID와 계정을 위한 QR Code 표준

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

```type``` 유형, **I**는 신분을 대표하고, **A**는 계정을 대표

```label``` 신분 혹은 계정에 대한 레이블

```algorithm``` 키/페어 생성에 사용되는 알고리즘

```parameters``` 키/페어 알고리즘의 파라미터

```scrypt``` Scrypt파라미터

```key``` 암호화 후 프라이빗 키

```address```  주소

```salt``` base64 형식의 16바이트 솔트 값
