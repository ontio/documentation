

<h1 align="center">온톨로지 DAPP 개발 가이드</h1>
<p align="center" class="version">Version 1.0.0 </p>

이 강좌는 Ontology dApp API (dAPI)를 사용하여 dApp을 개발하는 방법입니다. 

요강:

[개발환경 설치] (#개발환경 설치)

[Ontology dAPI](#ontology-dapi)
+[dAPI 설치](#dapi-설치)
+ [dAPI 사례](#dapi-사례)
+ [dAPI 방법](#dapi-방법)
	+ [체인과 연동방법](#체인과 연동방법)
	+ [이체방법](#이체방법)
	+ [스마트 컨트랙트방법](# 스마트 컨트랙트방법)
	+ [데이터서명](#데이터서명)


[실행예시](#실행예시)

[귀하의dApp위해 스마트 컨트랙트쓰기](#귀하의dApp위해 스마트 컨트랙트쓰기)
+ [스마트 컨트랙트 컴파일하기](#스마트 컨트랙트 컴파일하기)
+ [스마트 컨트랙트 설치하기](#스마트 컨트랙트 설치하기)
+ [스마트 컨트랙트 테스트하기](#스마트 컨트랙트 테스트하기)



### 개발환경 설치

하기 소프트웨어가 설치되어 있는지 확인하십시오.


- [Node.js v6+ LTS with npm](https://nodejs.org/en/)

- [Cyano Wallet]( https://chrome.google.com/webstore/detail/ontology-web-wallet/dkdedlpgdmmkkfjabffeganieamfklkm)

- [Git](https://git-scm.com/)


### Ontology dAPI
#### dAPI 설치
dApp생성 시 Ontology dAPI는 Ontology체인과 호환하는 핵심 API 중 하나이며 이곳에서 소스코드를 다운로드 할 수 있습니다. [이곳](https://github.com/ontio/ontology-dapi). ```npm``` 을 통해 ```ontology-dapi```를 설치합니다. 


```
$ npm install ontology-dapi
```

#### dAPI 예시

dAPI예시를 생성할 때 먼저 ontology-dapi를 불러오고 클라이언트단을 등록해야 합니다

```typescript
import { client } from 'ontology-dapi';

client.registerClient({});
```

#### dAPI방법
dAPI예시 생성 완료 후 귀하의 dApp에서 dAPI방법을 호출할 수 있습니다. 
#####체인과 호환방법
```typescript
const network = await client.api.network.getNetwork();
const height = await client.api.network.getBlockHeight();
const block = await client.api.network.getBlock({ block: 1 });
const transaction = await client.api.network.getTransaction({txHash: '314e24e5bb0bd88852b2f13e673e5dcdfd53bdab909de8b9812644d6871bc05f'});
const balance = await client.api.network.getBalance({ address: 'AcyLq3tokVpkMBMLALVMWRdVJ83TTgBUwU' });
```
##### 이체방법
```
const result = await client.api.asset.makeTransfer({ recipient, asset, amount });
```
##### 스마트 컨트랙트 방법
```typescript
const result = await client.api.smartContract.invoke({contract,method,parameters,gasPrice,gasLimit,requireIdentity});
const result = await client.api.smartContract.invokeRead({ contract, method, parameters });
const result = await client.api.smartContract.deploy({code,name,version,author,email,description,needStorage,gasPrice,gasLimit});
```
##### 데이터서명

```
const message: string = values.message;
const signature: Signature = {
  data,
  publicKey
};
const result = await client.api.message.signMessage({ message });
const result = await client.api.message.verifyMessage({ message, signature });
```

모든 방법리스트는 문서에서 찾을 수 있습니다. [dAPI 규정](https://github.com/backslash47/OEPs/blob/oep-dapp-api/OEP-6/OEP-6.mediawiki). <br> 



### 실행예시

카피 [dAPI 예시](https://github.com/OntologyCommunityDevelopers/ontology-dapi-demo) ，dAPI가 어떠한 기능을 제공하는지 테스트할 수 있습니다. 

```
$ git clone https://github.com/OntologyCommunityDevelopers/ontology-dapi-demo.git

$ npm install

$ npm run start
```

실행에 성공하면 브라우저에서 사이트를 여세요.http://localhost:3000 

사이트를 연 후 Provider->GetProvider를 클릭하세요. 

![dApp Demo Provider](./lib/images/dappdemofirstscreen.png)
![dApp Demo Get Provider](./lib/images/dappdemoregisterprovider.png)

API호출을 통해 체인이 호환되었습니다. 예를 들어 Network->Get Block를 클릭하면 결과는 다음과 같습니다. 

![dApp Demo getBlock](./lib/images/dappdemonetworkblock.png)

이체 실행 예시는 Asset->Make Transfer를 클릭하면 Cyano Wallet가 확인창을 표시합니다. ```Confirm```를 클릭하여 트랜젝션을 확인합니다. 

![Cyano Wallet Confirm](./lib/images/demo.png)


### dApp를 위해 스마트 컨트랙트 쓰기

dApp백그라운드의 로직과 스토리지는 스마트 컨트랙트을 사용해야 하며 **SmartX**를 통해 스마트 컨트랙트을 편집하거나 디버깅할 수 있습니다.[SmartX](http://smartx.ont.io/)，[Smart Contract 강좌](https://github.com/ontio/documentation/tree/master/smart-contract-tutorial)

![SmartX Login](./lib/images/smartx.png)


#### 스마트 컨트랙트 컴파일 및 설치하기

**SmartX**는 Cyano Wallet을 사용하여 계약의 설치와 호출을 지원합니다. Cyano에 따라 테스트넷 계정을 생성했는지 확인하십시오.  

#### 스마트 컨트랙트 컴파일하기

**SmartX**을 이용한 계약 컴파일

![smart contract deploy and invoke](./lib/images/smartx-deploy.png)

#### 스마트 컨트랙트 설치하기

스마트 컨트랙트을 작성하고 컴파일 완료 후 스마트 컨트랙트을 설치하고 호출합니다. 만약 테스트넷 ONG가 없다면 
[테스트넷 ONG in Discord 신청이 필요합니다.](https://discordapp.com/channels/400884201773334540/453499298097922068)가 필요합니다. 


![Deploy](https://s1.ax1x.com/2018/09/03/PzhTCd.png)



![Invoke](https://s1.ax1x.com/2018/09/03/Pz5JO0.png) 

### 스마트 컨트랙트 테스트하기

테스트 프레임을 이용하여 스마트 컨트랙트을 테스트할 수 있습니다. 
[smart contract automated testing framework](https://github.com/lucas7788/pythontest)， 만약 프라이빗 체인에 설치해야 하면 최신버전의 Ontology를 다운로드 받아 실행하세요.    (https://github.com/ontio/ontology/releases).
```
$ ./ontology --testmode --gasprice 0

```
