##  소개

디지털원과 관련된 정보는 [ONT ID신원표시 프로토콜 및 신뢰프레임]을 참고하세요.(https://github.com/ontio/ontology-DID)。

## 지갑문서 및 규정

지갑문서는 Json형식의 데이터 저장 문서이며 동시에 다수의 디지털신원과 다수의 디지털자산 계정을 저장할 수 있습니다. 상세한 내용은 [지갑문서규정]을 참고하세요.

디지털신원을 생성하기 위해 먼저 지갑문서를 생성 후 실행해야 합니다.

```java
//지갑문서가 없으면 자동으로 설치됩니다.
OntSdk ontSdk = OntSdk.getInstance();
ontSdk.openWalletFile("Demo3.json");
```
> 비고: 현재는 문서형식의 지갑문서만 지원하고 데이터베이스 또는 기타 저장방식으로도 확장 가능합니다.  



## 디지털신원 데이터구조

**Identity데이터구조 설명**

`ontid`는 신원을 나타내는 유일한 id입니다.
`label`은 유저가 신원에 부여하는 명칭입니다. 
`lock`은 신원이 유저에 의해 홀딩 되었는지를 의미합니다. 클라이언트단에서는 홀딩된 신원정보를 업데이트 할 수 없습니다. 디폴트 값은 false입니다. 
`controls`은 신원의 모든 컨트롤 대상인 ControlData의 배열입니다. 
`extra`는 클라이언트단의 개발자가 별도 저장한 정보 필드입니다. Null로 표기할 수 있습니다. 

```
//Identity데이터구조
public class Identity {
	public String label = "";
	public String ontid = "";
	public boolean isDefault = false;
	public boolean lock = false;
	public List<Control> controls = new ArrayList<Control>();
	public  Object extra = null;
}
```

`algorithm`는 암호화 알고리즘 명칭에 사용됩니다. 
`parameters`는 암호알고리즘에 필요한 파라미터입니다. 
`curve`는 타원곡선의 명칭입니다. 
`id`는 control의 유일한 표시입니다. 
`key`는 NEP-2서식의 프라이빗키입니다. 

```
public class Control {
    public String algorithm = "ECDSA";
    public Map parameters = new HashMap() ;
    public String id = "";
    public String key = "";
    public String salt = "";
    public String hash = "sha256";
    @JSONField(name = "enc-alg")
    public String encAlg = "aes-256-gcm";
    public String address = "";
}
```

## 디지털신원 인터페이스


### 1. 신원 등록

디지털신원 생성은 1개의 Identity데이터구조의 신원정보가 생성되고 지갑문서에 기록되는 것입니다. 

```
Identity identity = ontSdk.getConnect().createIdentity("passwordtest");
//생성된 계정 또는 신원은 메모리에만 저장되므로 지갑문서에 기록하려면 기록인터페이스를 호출해야 합니다. 
ontSdk.getWalletMgr().writeWallet();
```

**체인상에서의 신원 등록**

블록체인 체인에 성공적으로 등록되어야만 해당 신원을 사용할 수 있습니다. 

두 가지 방식으로 체인상에 신원을 등록할 수 있습니다.  

방법1, 등록자가 트랜젝션 비용지불계정 주소를 지정합니다. 

```
Identity identity = ontSdk.getWalletMgr().createIdentity(password);
ontSdk.nativevm().ontId().sendRegister(identity2,password,payerAcct,gaslimit,gasprice);
```


방법2. 구성한 트랜젝션을 서버에 전송하면 서버에서 트랜젝션비용 계정 서명을 처리합니다.  


```
Identity identity = ontSdk.getWalletMgr().createIdentity(password);
Transaction tx = ontSdk.nativevm().ontId().makeRegister(identity.ontid,password,payerAcc.address,ontSdk.DEFAULT_GAS_LIMIT,0);
ontSdk.signTx(tx,identity.ontid,password);
ontSdk.getConnect().sendRawTransaction(tx);
```

체인상 등록이 완료되면 해당 ONT ID에 대응되는 신원의 서술 대상인 DDO가 온톨로지 블록체인에 저장됩니다. 

DDO에 관련한 정보는 [ONT TD신원표시 프로토콜]에서 확인하세요.https://github.com/ontio/ontology-DID/blob/master/README_cn.md)


### 2. 신원관리

**신원 불러오기**

유저가 디지털신원 또는 디지털계정을 가지고 있으면 SDK는 이를 지갑문서로 불러옵니다.  

> Note: 디지털신원을 불러오기 전에 먼저 체인상 신원을 조회하는 것을 권장합니다. 만약 체인상 신원DDO가 존재하지 않는다면 해당 디지털신면이 체인상 등록되지 않은 것이므로, 상기 디지털신원 등록방식을 통해 신원을 체인상 등록하십시오. 


```java
Identity identity = ontSdk.getWalletMgr().importIdentity(encriptPrivateKey,password,salt,address);
//지갑에 기록       
ontSdk.getWalletMgr().writeWallet();
```


파라미터 설명 
encriptPrivateKey: 암호화 후의 프라이빗키
password：암호화 프라이빗키 사용암호
salt: 프라이빗키 해독용 파라미터
address: 계정주소 base58 코드

**신원삭제**

```java
ontSdk.getWalletMgr().getWallet().removeIdentity(ontid);
//지갑에 기록
ontSdk.getWalletMgr().writeWallet();
```

**디폴트계정 및 신원 설치**

```java
//계정주소에 따라 디폴트계정을 설치합니다.
ontSdk.getWalletMgr().getWallet().setDefaultAccount(address);
//identity색인에 따라 디폴트 identity를 설치합니다. 
ontSdk.getWalletMgr().getWallet().setDefaultIdentity(index);
ontSdk.getWalletMgr().getWallet().setDefaultIdentity(ontid);
```

### 3. 체인상 신원정보 조회

체인상 신원DDO정보는 ONT ID를 통해 조회 가능합니다. 

```json
//ONT ID를 통해 DDO획득
String ddo = ontSdk.nativevm().ontId().sendGetDDO(ontid);

//DDO서식으로 돌아가기
{
	"Attributes": [{
		"Type": "String",
		"Value": "value1",
		"Key": "key1"
	}],
	"OntId": "did:ont:TA5UqF8iPqecMdBzTdzzANVeY8HW1krrgy",
	"Recovery": "TA6AhqudP1dcLknEXmFinHPugDdudDnMJZ",
	"Owners": [{
		"Type": "ECDSA",
		"Curve": "P256",
		"Value": "12020346f8c238c9e4deaf6110e8f5967cf973f53b778ed183f4a6e7571acd51ddf80e",
		"PubKeyId": "did:ont:TA5UqF8iPqecMdBzTdzzANVeY8HW1krrgy#keys-1"
	}, {
		"Type": "ECDSA",
		"Curve": "P256",
		"Value": "1202022fabd733d7d7d7009125bfde3cb0afe274769c78fd653079ecd5954ae9f52644",
		"PubKeyId": "did:ont:TA5UqF8iPqecMdBzTdzzANVeY8HW1krrgy#keys-2"
	}]
}

```



### 4. 신원속성

#### 4.1 체인상DDO속성 업데이트
방법1. 트랜젝션 비용지불 계정을 지정합니다. 

```java
//속성을 추가 또는 업데이트합니다. 
String sendAddAttributes(String ontid, String password,byte[] salt， Attribute[] attributes,Account payerAcct,long gaslimit,long gasprice)
```


| 파라이터      | 필드   | 유형  | 서술 |             설명 |
| -----    | ------- | ------ | ------------- | ----------- |
| 输入파라이터   | password| String | 디지털 신원 암호 | 필수，프라이빗키 해독 암호 |
|           |salt     | byte[] |  |    필수  |
|           | ontid    | String | 디지털신원id  | 필수，신원Id |
|           | attributes | Attribute[]| 속성배열  | 필수 |
|           | payerAcct    | Account | 트랜젝션비용 지불인 계정      |  필수， |
|           | gaslimit      | long | gaslimit     | 필수 |
|           | gasprice      | long | gas가격     | 필수 |
| 파라이터 송출   | txhash   | String  | 트랜잭션hash  | 트랜잭션hash는64자리 문자 |



방법2. 구성된 트랜젝션을 서버에 전송하면 서버에서 트랜젝션 비용계정 서명을 처리합니다
```java
Transaction makeAddAttributes(String ontid, String password, byte[] salt,Attribute[] attributes,String payer,
                                          long gaslimit,long gasprice)
```

코드예시
```java
Transaction tx = ontSdk.nativevm().ontId().makeAddAttributes(ontid,password,salt,attributes,payer,gaslimit,0);
ontSdk.signTx(tx,identity.ontid,password);
ontSdk.getConnect().sendRawTransaction(tx);
```

#### 4.2 체인상 DDO속성 제거

방법1. 

```
String sendRemoveAttribute(String ontid,String password,byte[] salt,String path,Account payerAcct,long gaslimit,long gasprice)
```


| 파라이터      | 필드   | 유형  | 서술 |             설명 |
| ----- | ------- | ------ | ------------- | ----------- |
| 파라이터송출 | password| String | 디지털신원 암호 | 필수 |
|        | salt| byte[] |  | required |
|        | ontid    | String | 디지털 신원ID   | 필수，신원Id |
|        | path    | byte[]  | path       | 필수，path |
|        | payer    | String  | payer       | 필수，payer |
|        | payerpassword | String  | 트랜젝션비용 지불계정 주소  | 필수 |
|        | gas   | long | 지불한 트랜젝션비용    | 필수 |
| 파라이터송출 | txhash   | String  | 트랜잭션hash  | 트랜젝션hash는 64자리 문자열 |


방법2. 구성된 트랜젝션을 서버에 전송하면 서버에서 트랜젝션 비용계정 서명을 처리합니다. 
```
Transaction makeRemoveAttribute(String ontid,String password,salt,String path,String payer,long gaslimit,long gasprice)
```

예시코드：
```
Transaction tx = ontSdk.nativevm().ontId().makeRemoveAttribute(ontid,password,salt,path,payer,gaslimit,0);
ontSdk.signTx(tx,identity.ontid,password);
ontSdk.getConnect().sendRawTransaction(tx);
```

### 5. 신원 퍼블릭키

신원 하나는 여러 관리자를 가질 수 있으며 신원의 퍼블릭키는 관리자의 퍼블릭키 리스트 입니다.  
#### 5.1 퍼블릭키 추가

방법1

```java
String sendAddPubKey(String ontid, String password,byte[] salt, String newpubkey,Account payerAcct,long gaslimit,long gasprice)
```


| 파라이터      | 필드   | 유형  | 서술 |             설명 |
| ----- | ------- | ------ | ------------- | ----------- |
| 파라이터입력 | password| String | 디지털신원 암호 | 필수 |
|        | salt| byte[] |  | required |
|        | ontid    | String | 디지털신원ID   | 필수，신원Id |
|        | newpubkey| String  |퍼블릭키       | 필수， newpubkey|
|        | payerAcct    | Account  | Payment transaction account  | 필수，payer |
|        | gaslimit   | long | gaslimit     | 필수 |
|        | gasprice   | long | gas가격     | 필수 |
| 파라이터송출 | txhash   | String  | 트랜잭션hash  | 트랜젝션hash는 64자리 문자열 |


방법2. 구성된 트랜젝션을 서버에 전송하면 서버에서 트랜젝션 비용계정 서명을 처리합니다. 

```java
Transaction makeAddPubKey(String ontid,String password,byte[] salt,String newpubkey,String payer,long gaslimit,long gasprice)
```
파라미터에 관한 설명은 방법1sendAddPubKey를 참고하십시오. 

코드예시
```java
Transaction tx = ontSdk.nativevm().ontId().makeAddPubKey(ontid,password,byte[] salt,newpubkey,payer,gaslimit,gasprice);
ontSdk.signTx(tx,identity.ontid,password);
ontSdk.getConnect().sendRawTransaction(tx);
```

방법3. recovery매커니즘
recovery는 ontid에 퍼블릭키를 추가할 수 있습니다. 
```java
String sendAddPubKey(String ontid,String recoveryAddr, String password, byte[] salt,String newpubkey,Account payerAcct,long gaslimit,long gasprice)
```

| 파라이터      | 필드   | 유형  | 서술 |             명 |
| ----- | ------- | ------ | ------------- | ----------- |
| 파라미터입력 | ontid    | String | 디지털신원 암호   | 필수, 프라이빗키 해독 암호 |
|        | recoveryAddr| String | recovery주소 | 필수 |
|        | password| String | recovery암호 | 필수 |
|        | salt| byte[] |  | required |
|        | newpubkey| String  |퍼블릭키       | 필수， newpubkey|
|        | payer    | String  | payer       | 필수，payer |
|        | payerpwd | String  | 트랜젝션비용 지불계정 주소  | 필수 |
|        | gaslimit   | long | gaslimit     | 필수 |
|        | gasprice   | long | gas가격     | 필수 |
| 파라이터송출 | txhash   | String  | 트랜잭션hash  | 트랜젝션hash는 64자리 문자열 |


방법4 (recovery매커니즘)

```java
Transaction makeAddPubKey(String ontid,String recoveryAddr,String password,byte[] salt,String newpubkey,
                                          String payer,long gaslimit,long gasprice)
```

파라미터에 관한 설명은 방법3을 참고하십시오. 


#### 5.2 퍼블릭키 삭제

방법1. 퍼블릭키 삭제

```java
String sendRemovePubKey(String ontid, String password,byte[] salt, String removePubkey,Account payerAcct,long gaslimit,long gasprice)
```


| 파라이터      | 필드   | 유형  | 서술 |             설명 |
| ----- | ------- | ------ | ------------- | ----------- |
| 파라이터입력 | password| String | 디지털신원 암호 | 필수 |
|        | salt| byte[] |  | required |
|        | ontid    | String | 디지털신원ID  | 필수，신원Id |
|        | removePubkey| String  |퍼블릭키       | 필수， removePubkey|
|        | payer    | String  | payer       | 필수，payer |
|        | payerpassword | String  | 트랜젝션비용 지불계정 주소  | 필수 |
|        | gas   | long | 지불한 트랜젝션 비용     | 필수 |
| 파라이터송출 | txhash   | String  | 트랜잭션hash  | 트랜젝션hash는 64자리 문자열 |


방법3. 구성된 트랜젝션을 서버에 전송하면 서버에서 트랜젝션 비용계정 서명을 처리합니다. 

```java
Transaction tx = ontSdk.nativevm().ontId().makeRemovePubKey(ontid,password,salt,removePubkey,payer,gas);
ontSdk.signTx(tx,identity.ontid.replace(Common.didont,""),password,salt);
ontSdk.getConnect().sendRawTransaction(tx);
```

방법3. 리커버리 매커니즘
```java
String sendRemovePubKey(String ontid, String recoveryAddr,String password, byte[] salt,String removePubkey,Account payerAcct,long gaslimit,long gasprice)
```

| 파라이터      | 필드   | 유형  | 서술 |             설명 |
| ----- | ------- | ------ | ------------- | ----------- |
| 파라이터입력 | ontid    | String | 디지털신원ID   | 필수，신원Id |
|        | recoveryAddr| String | recovery주소 | 필수 |
|        | password| String | recovery암호 | 필수 |
|        | salt| byte[] |  | required |
|        | newpubkey| String  |퍼블릭키       | 필수， newpubkey|
|        | payerAcct    | Account  | Payment transaction account | 필수，payer |
|        | gaslimit   | long | gaslimit     | 필수 |
|        | gasprice   | long | gas가격     | 필수 |
| 파라이터송출 | txhash   | String  | 트랜잭션hash  | 트랜젝션hash는 64자리 문자열 |


방법4 (recovery매커니즘)
```java
Transaction makeRemovePubKey(String ontid,String recoveryAddr, String password,byte[] salt, String removePubkey,String payer,
                                          long gaslimit,long gasprice)
```

파라미터에 관한 설명은 방법3을 참고하십시오.

### 6. 신원 리커버리

ontid에서 관리자가 프라이빗키를 분실했을 경우 신원 리커버리는 새로운 관리자를 설정할 수 있습니다. 
#### 6.1 리커버리 추가

방법1

```java
String sendAddRecovery(String ontid, String password,byte[] salt, String recoveryAddr,Account payerAcct,long gaslimit,long gasprice)
```

| 파라이터      | 필드   | 유형  | 서술 |             설명 |
| ----- | ------- | ------ | ------------- | ----------- |
| 파라이터입력 | password| String | 디지털신원 암호 | 필수 |
|        | salt| byte[] | | required |
|        | ontid    | String | 디지털신원ID   | 필수，신원Id |
|        | recoveryAddr| String  |recovery계정주소 | 필수，recovery|
|        | payerAcct    | Account  | payerAcct  | 필수，payer |
|        | gaslimit   | long | gaslimit     | 필수 |
|        | gasprice   | long | gas가격     | 필수 |
| 파라이터송출 | txhash   | String  | 트랜잭션hash  | 트랜젝션hash는 64자리 문자열 |


방법3. 구성된 트랜젝션을 서버에 전송하면 서버에서 트랜젝션비용 계정서명을 처리합니다. 
```
Transaction makeAddRecovery(String ontid, String password,byte[] salt, String recoveryAddr,String payer,long gaslimit,long gasprice)
```

예시
```
Transaction tx = ontSdk.nativevm().ontId().makeAddRecovery(ontid,password,salt,recovery,payer,gas);
ontSdk.signTx(tx,identity.ontid.replace(Common.didont,""),password,salt);
ontSdk.getConnect().sendRawTransaction(tx);
```

#### 6.2 수정recovery

방법1
```
String sendChangeRecovery(String ontid, String newRecovery, String oldRecovery, String password,,byte[] salt,long gaslimit,long gasprice)
```

| 파라이터      | 필드   | 유형  | 서술 |             설명 |
| ----- | ------- | ------ | ------------- | ----------- |
| 파라이터입력 |ontid    | String | 디지털신원ID   | 필수，신원Id |
|        | newRecovery| String  |newRecovery계정주소 | 필수，newRecovery|
|        | oldRecovery| String  |oldRecovery계정주소 | 필수，oldRecovery|
|        | oldRecovery password | String  | oldRecovery password  | 필수 |
|        | password| String | 디지털신원 암호 | 필수 |
|        | salt| byte[] | | required |
|        | gaslimit   | long | gaslimit     | 필수 |
|        | gasprice   | long | gasprice     | 필수 |
| 파라이터송출 | txhash   | String  | 래hash  | 트랜젝션hash는 64자리 문자열 |


방법2
```
Transaction makeChangeRecovery(String ontid, String newRecovery, String oldRecovery, String password,byte[] salt,long gaslimit,long gasprice)
```

파라미터에 관한 설명은 상기 방법1을 참고하십시오. 
