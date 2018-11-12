<h1 align="center"> 지갑규정 </h1>

<p align="center" class="version">Version 1.0.0 </p>



지갑규정은 지갑 데이터구조 및 디지털신분 불러오기 또는 자산계정 QR코드의 데이터구조를 서술합니다. 

## 1. 지갑문서 구조

지갑문서 데이터는 json서식으로 저장되며 문서 이름에는 규칙이 없습니다. 지갑문서 데이터구조는 다음과 같습니다. 

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
파라미터 서술:

```name```은 지갑이름 입니다.
 
```version```은 지갑버전 번호입니다.
 
```scrypt```는 SCrypt알고리즘 파라미터 입니다. 

```defaultOntid```는 지갑의 디폴트Ontid입니다. 
  
```defaultAccountAddress```는 지갑의 디폴트계정 주소입니다. 

```createTime```은 지갑 생성시간입니다. 

```identities```은 신분 리스트입니다. 

```accounts```는 계정 리스트입니다. 

```extra```는 백업 파라미터입니다. 

실제 지갑 데이터는 다음과 같습니다.

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

### 1.1 Scrypt파라미터

SCrypt알고리즘 파라미터, Scrypt데이터 구조:

```json
{
  "n": 16384,
  "r": 8,
  "p": 8,
  "dkLen" : 64
}
```

파라미터 서술:

```n```은 메모리 소모량이며 2^N여야 합니다.

```r```은 파라미터입니다. 

```p```는 SCrypt알고리즘의 병렬파라미터 입니다.  

```dkLen```은 파생key의 길이입니다. 

### 1.2 디지털신분

디지털신분 데이터구조:
```json
{
  "ontid": "did:ont:TQLASLtT6pWbThcSCYU1biVqhMnzhTgLFq",
  "label": "MyIdentity",
  "lock": false,
  "isDefault" : false,
  "controls": []
}
```
파라미터 서술:

```ontid```는 신분id입니다. 

```label```은 닉네임입니다. 

```lock```은 해당신분의 락킹 여부를 뜻 합니다 

```isDefault```는 디폴트의 신분사용 여부를 뜻합니다.

```controls```는 관리자입니다. 

#### Control데이터구조

Control은 데이터신분의 관리자이며 내부에는 관리자의 암호화된 알고리즘 명과 프라이빗키, 퍼블릭키, 주소, salt등이 포함되어 있습니다. 

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
파라미터 서술:

```algorithm```은 서명알고리즘 명칭입니다. 

```parameters```은 곡선 파라미터 입니다. 

```id```는 관리자id입니다. 

```key```는 암호화된 프라이빗키 입니다. 

```address```는 base58주소입니다. 

```salt```는 16바이트의 솔트이며 base64서식으로 저장됩니다. 

#### Parameter데이터구조

서명알고리즘 파라미터 데이터구조
```json
{
  "curve":"P-256"
}
```
파라미터 서술:

```curve``` is the name of the elliptic curve.

### 1.3 Account


자산계정정보```Account```데이터구조:


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
파라미터 서술:

```address```는 base58주소입니다. 

```enc-alg```는 프라이빗키 암호알고리즘 명칭입니다. 

```salt```는 16바이트의 솔트이며 base64서식으로 저장됩니다. 

```publicKey```는 퍼블릭키 입니다.
 
```signatureScheme```는 서명알고리즘 체계입니다. 

```isDefault```는 디폴트계정 여부를 뜻 합니다. 

```label```는 닉네임입니다. 

```lock```는 락킹 여부를 뜻 합니다.
 
```algorithm```은 서명알고리즘 명칭입니다. 

```parameters```은 서명알고리즘 파라미터 입니다.
 
```key```는 암호화된 프라이빗키 입니다. 


## 2. QR코드 규정

신분과 계정QR코드의 역할은 스캔을 통해 편리하게 신분과 계정을 불러오는 것이며, QR코드는 디지털신분과 자산계정 규정을 모두 지원합니다.  

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
파라미터 서술:

```type```은 유형이며 **I**는 신분을, **A** 는 계정을 의미합니다. 
 
```label```은 닉네임입니다. 

```algorithm```은 서명알고리즘 명칭입니다. 

```parameters```는 서명알고리즘 파라미터 입니다. 

```scrypt```는 scrypt파라미터 입니다. 

```key```는 암호화된 프라이빗키 입니다. 

```address```는 주소입니다. 

```salt```는 16바이트 솔트이며 base64서식으로 저장됩니다. 


