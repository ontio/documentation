<h1 align="center">개발자 속성교육</h1> 

<p align="center" class="version">Version 1.0.0 </p> 

온톨로지는 차세대 고성능 퍼블릭 블록체인으로, 메인넷 오픈 후 많은 개발자들이 온톨로지의 기술커뮤니티에 참여해왔습니다. 문서는 개발자가 온톨로지 생태계에 진입하는 통로이며 완비된 문서체계는 개발자의 개발효율을 크게 향상시킵니다. 문서를 통해 개발자는 온톨로지생태계와 온톨로지 기술에 대해 정확히 이해 할 수 있습니다. 본 문서는 온톨로지 문서센터의 요약이며 문서센터의 각 구성요소를 대략 소개함으로써 개발자들이 속성으로 온톨로지기술 및 온톨로지 생태계를 숙달할 수 있도록 할 것입니다.   

* [온톨로지](#온톨로지)
     * [온톨로지란？](#온톨로지란)
     * [온톨로지획득방법？](#온톨로지획득방법)
     * [온톨로지노드소개](#온톨로지노드소개)
        * [동기화 노드](#동기화 노드)
        * [컨센서스](#컨센서스)
     * [온톨로지의 컨센서스 매커니즘](#온톨로지의 컨센서스 매커니즘)
     * [온톨로지네트워크에 연결](#온톨로지네트워크에 연결)
     * [온톨로지의 특수 기능](#온톨로지의 특수 기능)
        * [온톨로지DID](#온톨로지did)
        * [분산화 데이터트랜젝션](#분산화 데이터트랜젝션)
* [온톨로지와 호환하는 방법](#온톨로지와 호환하는 방법)
     * [온톨로지명령도구](#온톨로지명령도구)
     * [온톨로지 서명디바이스](#온톨로지 서명디바이스)
     * [온톨로지API](#온톨로지api)
* [온톨로지스마트 컨트랙트](#온톨로지스마트 컨트랙트)
     * [온톨로지스마트 컨트랙트 IDE——Smartx](#온톨로지스마트 컨트랙트 idesmartx)
     * [온톨로지스마트 컨트랙트 프로그래밍 방법](#온톨로지스마트 컨트랙트 프로그래밍 방법)
     * [계약의 설치 및 호출](#계약의 설치 및 호출)
     * [스마트 컨트랙트 권한관리](#스마트 컨트랙트 권한관리)
* [온톨로지사용](#온톨로지사용)
     * [환경설정](#환경설정)
     * [계약 프로그래밍, 설치 및 호출](#계약 프로그래밍, 설치 및 호출)

## 온톨로지

### 온톨로지란？

온톨로지의 특성은 [이곳](https://ontio.github.io/documentation/install_zh.html#특성)에 간략한 소개가 나와있습니다. 

### 온톨로지획득방법

현재 온톨로지의 모든 소스코드는 GitHub상의 오픈소스이며 유저는 자유롭게 [코드베이스](https://github.com/ontio/ontology)에서 소스코드를 다운받아 컴파일 후 설치 가능합니다. 또한 `curl https://dev.ont.io/ontology_install | sh `  명령을 통해 최신 ontology버전을 획득하거나, 각 버전의 [release버전](https://github.com/ontio/ontology/releases)를 직접 획득할 수 있습니다. 상세한 획득 및 설치방법은 [이곳](https://ontio.github.io/documentation/install_zh.html)을 참고하십시오. 


### 온톨로지노드 소개

온톨로지 획득 이후에 온톨로지에서 온톨로지 프로그램을 실행하여 온톨로지 네트워크에 연결할 수 있습니다. 하지만 이전에 먼저 현재 온톨로지 네트워크 중의 노드유형을 파악해야 합니다.  

온톨로지의 네트워크 노드유형은 합의노드와 동기화 노드가 있습니다:  

합의노드는 컨센서스에 참여하고 트랜젝션을 팩킹하여 블록을 생성합니다. 

동기화 노드는 최신 블록정보와 동기화되며 컨센서스에 참여하지 않습니다. 

#### 동기화 노드

동기화 노드는 메인넷 또는 온톨로지의 퍼블릭 테스트넷에 연결할 수 있습니다. 각각의 네트워크에 연결할 때 노드는 서로 다른 정보와 동기화되어 현재 목록에서 Chain과 Log두 개의 폴더를 생성합니다. Chain에서 모든 트랜젝션 데이터, 계정데이터 등등 동기화된 블록데이터를 저장합니다. Log에는 동기화 시 발생한 Log정보를 저장합니다.   


#### 합의노드

합의노드와 동기화 노드는 메인넷과 테스트넷에서 실행할 수 있고 실행과정에서 Chain과 Log폴더를 생성한다는 점에서는 비슷하지만 합의노드는 트랜젝션 정보를 팩킹하여 블록을 생성한다는 점이 다릅니다.  

### 온톨로지 합의매커니즘

온톨로지 네트워크 노드유형을 이해한 후에 온톨로지 네트워크의 합의매커니즘을 소개할 것입니다. 온톨로지는 DBFT와 VBFT컨센서스를 지원하고 있으며 현재 메인넷과 테스트넷에서는 VBFT컨센서스를 사용하고 있습니다. 

### 온톨로지 네트워크에 연결

현재 온톨로지 네트워크에 연결을 시도할 수 있습니다. 
[이곳](https://github.com/ontio/ontology/blob/master/README_CN.md#运行ontology)에서 온톨로지 네트워크에 연결하는 방법과 ontology테스트모드를 실행하는 방법을 자세히 소개하고 있습니다.  

### 온톨로지의 특수기능

#### 온톨로지 DID
 
Ontology DID（약칭ONT ID）는 W3C기반의 DID규정이며 탈중앙화 신원 확인 프로토콜입니다. 자세한 소개는 
[해당문서](https://ontio.github.io/documentation/ontology_DID_zh.html)를 참고하십시오.
 

#### 분산화 데이터 트랜젝션

현재 중앙화 데이터 거래소는 데이터캐시, 프라이버시 데이터가 유저의 수락을 받지 않고 데이터 라이선스가 보호되지 못하는 점 등의 문제점이 있습니다. 온톨로지에서는 분산화 테이터 관리 프로토콜인 ONT DATA와 해당 프로토콜을 기반으로 탈중앙화 데이터트랜잭션 프레임인 DDXF를 제안합니다. 더 자세한 내용은 [해당문서](https://ontio.github.io/documentation/DDXF_zh.html)를 참고하십시오. 


## 온톨로지와 호환 방법

### 온톨로지명령도구

온톨로지 네트워크를 구축하고 실행할 때 많은 명령줄 파라미터를 사용하게 될 수도 있습니다. 이 파라미터들에 관한 자세한 설명은 
[이곳](https://ontio.github.io/documentation/cli_user_guide_zh.html)에서 확인할 수 있습니다. 이 명령줄 파라미터들 또한 ontology실행프로그램을 통해 실행 가능하며 ontology CLI도구라고 통칭합니다. CLI는 온톨로지 네트워크의 대부분 기능을 실행 및 호출할 수 있으므로 온톨로지 네트워크의 최대 통로입니다. 문서 외에도 `./ontology –help`의 실행을 통해 명령줄 파라미터의 간략한 정보를 획득할 수 있습니다.  

### 온톨로지 서명디바이스

더 많은 수요를 만족시키고자 온톨로지에서는 서명디바이스라고 불리는 서비스를 제공합니다. 해당 서비스는 지정된 지갑을 사용하여 서비스에 전송된 트랜젝션에 대하여 서명을 진행합니다. 자세한 내용은 [해당문서](https://ontio.github.io/documentation/sigsvr_zh.html)를 참고하십시오. 


### 온톨로지 API


명령줄 외에, 온톨로지에서는 더욱 편리한 블록체인 호환 인터페이스를 제공합니다. 이 인터페이스는 API형식으로 제공되며 현재 온톨로지의 API는 [本体RPC API](https://ontio.github.io/documentation/rpc_api_zh.html)，
[온톨로지Restful API](https://ontio.github.io/documentation/restful_api_zh.html)，
[온톨로지Websocket API](https://ontio.github.io/documentation/websocket_api_zh.html)이상 3가지를 포함합니다.


## 온톨로지 스마트 컨트랙트

스마트 컨트랙트은 현재 블록체인에서 가장 중요한 기능이며 온톨로지 역시 자신만의 스마트 컨트랙트 체계를 가지고 있습니다. 자세한 내용은 [이곳](https://ontio.github.io/documentation/Introduction_of_Ontology_Smart_Contract_zh.html)을 참고하십시오. 


### 온톨로지 스마트 컨트랙트 IDE——Smartx

Smartx는 온톨로지에서 출시한 원스톱 스마트 컨트랙트 프로그래밍 도구이며 프로그래밍, 컴파일, 설치 및 디버깅 등 기능을 총망라하여 스마트 컨트랙트의 개발 효율을 극대화했습니다. Smartx의 사용방법은 [해당문서](https://ontio.github.io/documentation/SmartX_Tutorial_zh.html)를 참고하십시오.
  
### 스마트 컨트랙트 프로그래밍 방법

여기에서 [Hello World](https://ontio.github.io/documentation/The_Hello_World_Contract_zh.html) 를 예로 들어 간단한 스마트 컨트랙트 예시를 살펴보겠습니다. 스마트 컨트랙트 프로그래밍 과정에서 수많은 스마트 컨트랙트 API를 사용하게 되는데, 이 API들은 [이곳](https://apidoc.ont.io/smartcontract/)에서 볼 수 있습니다.

### 계약의 설치 및 호출

비록 smartx가 원스톱 설치호출 방식을 제공했다 하더라도 다른 방식으로도 계약을 설치 및 호출할 수 있습니다. 설치방법은 [해당문서](https://ontio.github.io/documentation/Smart_Contract_Deployment_zh.html) 를, 호출방법은 [해당문서](https://ontio.github.io/documentation/Smart_Contract_Invocation_zh.html)를 참고하십시오. 

### 스마트 컨트랙트의 권한관리

현재는 모든 유저가 스마트 컨트랙트 함수를 호출할 수 있는데, 이는 현실적 조건에 부합하지 않는 것입니다. 역할에 따른 권한관리의 기본 맥락은 모든 역할은 일부 함수를 호출할 수 있고 각각의 개체는 다양한 역할을 부여 받는 것입니다 (개체는 해당 ONT ID로 표시). [해당문서](https://ontio.github.io/documentation/ontology_java_sdk_auth_zh.html)에서 온톨로지 스마트 컨트랙트의 권한관리 방식에 관한 자세한 정보를 확인할 수 있습니다.  

## 온톨로지 사용

온톨로지에 대해 충분히 숙지한 후에 간단한 예시를 통해 온톨로지 네트워크에서 개발하는 방법에 대해 설명할 것입니다. 

### 환경설정

1. [온톨로지 네트워크에 연결] ](#온톨로지 네트워크에 연결)에서 서술한대로, 개별 컴퓨터의 환경에서의 테스트모델을 사용하시길 권장합니다. 물론 온톨로지 공용 테스트넷인 Polaris를 사용하셔도 좋습니다. 다음으로 개별 컴퓨터 환경의 테스트모드를 예시로 설명하겠습니다.  

2. 명령 `./ontology --rest --ws --localrpc --gaslimit 20000 --gasprice 0 --testmode --networkid 3`을 이용하여 테스트넷을 실행하고 대응하는 지갑 계정암호를 입력하십시오.

3. rest인터페이스를 이용하여 초기계정(solo모드에서의 기장인)의 잔액을 조회하십시오. 


  브라우저에`http://localhost:20334/api/v1/balance/APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh`를 입력합니다. 그 중 `localhost`는 노드ip이며 `20334`은 디폴트 rest인터페이스 입니다. 이 포트는 직접 지정할 수 있으며 명령은    
  `--rest --restport 20339`입니다. `api/v1/balance/`는 rest인터페이스의 url경로이며 후반의 `APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh`는 초기기장인의 주소입니다. 전체 URL은 잔액조회 rest인터페이스 호출방식을 구성합니다. 

   
   * 브라우저에서  `{"Action":"getbalance","Desc":"SUCCESS","Error":0,"Result":{"ont":"1000000000","ong":"0"},"Version":"1.0.0"}`로 반응하게 되면, 이것은 json서식의 반응 문자열입니다. 여기에서 해당 계정의 ont의 수량이 10억이고 ong는 0인 것을 볼 수 있습니다. 

   数量为十亿，ong数量为0。

4. 온톨로지 네트워크에서 거의 모든 동작에는 gas, 즉 ong가 소모됩니다. 이번 예시에서 실행할 때 `--gasprice 0`파라미터를 사용하고 gas소모 설정은 0이므로 후속 동작에서는 gas가 소모되지 않지만 gas지불은 가능합니다. 이 단계에서 계정에서 ong를 인출하는 법을 살펴보겠습니다. 

   * ong는 ont의 연료와 같은 존재이며 ONT에 따라 점차 배포됩니다. 하지만 수동으로 자신의 계정으로 인출해야 합니다. 
 
* `./ontology asset unboundong 1`을 이용하여 디폴트지갑의 첫 번째 계정의 인출 가능한 ONG수량을 조회합니다. `./ontology asset --help`를 통해 명령의 자세한 정보를 확인할 수 있습니다. 
   
       ```
       Unbound ONG:
       Account:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh
       ONG:0
       ```
   
   * 이때 인출 가능한 ong수량이 0인 이유는 해당 계정이 아직 ONG배포를 활성화하지 않았기 때문이며, 이체방식을 통해 활성화할 수 있습니다. 
   
   * `./ontology account add -d`를 사용하여 또 다른 ontology계정을 생성합니다. 주소는 `AGrJQhb7bZsy57MoQk6YDt3hDP7zRioHia`이며 `./ontology account list`로 디폴트지갑의 계정상황을 조회합니다.
   
       ```
       Index:1    Address:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh  Label: (default)
       Index:2    Address:AGrJQhb7bZsy57MoQk6YDt3hDP7zRioHia  Label:
       ```
   
   * `./ontology asset transfer --from 1 --to 2 --amount 100000000`명령을 사용하여 계정1에서 계정2로 1억개 ont를 이체합니다. 계정1의 암호를 입력하면 이체가 완료됩니다. 
   
       ```
       Transfer ONT
       From:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh
       To:AGrJQhb7bZsy57MoQk6YDt3hDP7zRioHia
       Amount:100000000
       TxHash:73a3d24b7dfd0d96b23f93fd38afe4638b70f921c278202443d0dd29a036236f
    
       Tip:
          Using './ontology info status 73a3d24b7dfd0d96b23f93fd38afe4638b70f921c278202443d0dd29a036236f' to query transaction status
       ```
   
   * 계정1과 계정2의 잔액을 조회합니다. 이번에는 명령줄을 사용하는 방식으로 조회하며 명령은 `./ontology asset balance 1`와 `./ontology asset balance 2`입니다. 
   
       ```
       BalanceOf:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh
       ONT:900000000
       ONG:0
       
       BalanceOf:AGrJQhb7bZsy57MoQk6YDt3hDP7zRioHia
       ONT:100000000
       ONG:0
       ```
   
   * 다시 `./ontology asset unboundong 1`을 사용하여 계정1의 인출 가능한 ong수량을 조회합니다. 이때 인출 가능한 수량이 0보다 큰 것을 (실제 실행과정에서 이 금액은 블록 높이와 이체한 금액의 영향을 받습니다) 확인할 수 있습니다.
   
       ```
       Unbound ONG:
       Account:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh
       ONG:5242930
       ```
   
   * `./ontology asset withdrawong 1`명령을 사용하여 계정1의 암호를 입력 후 계정1의 ong를 인출합니다. 
   
       ```
       Withdraw ONG:
       Account:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh
       Amount:5242930
       TxHash:6e10592e52cb7a3645eecd987c0161a8811f25ed5e183614d0e9cd9c58ab8a33
    
       Tip:
         Using './ontology info status 6e10592e52cb7a3645eecd987c0161a8811f25ed5e183614d0e9cd9c58ab8a33' to query transaction status
       ```
   
   * 명령줄의 방식으로 계정1의 잔액을 조회합니다. 이때 해당 계정에  ong가 생긴 것을 확인할 수 있습니다. 
   
       ```
       BalanceOf:APrkensMwPiaqg5rfz54Qa62hDWwtFAnkh
       ONT:900000000
       ONG:5242930
       ```
   
### 계약 프로그래밍, 설치 및 호출

1. [smartx](#온톨로지 스마트 컨트랙트idesmartx)을 열고 [HelloWorld예시](#스마트 컨트랙트 프로그래밍 방법)에 따라 Hello World스마트 컨트랙트을 프로그래밍 합니다. 호출 편리성을 위해 계약코드를 다음과 같은 형식으로 바꾸고 AVM바이트 코드로 변환하였습니다. 


    ```csharp
    using Neo.SmartContract.Framework.Services.Neo;
    using Neo.SmartContract.Framework;
    using System;
    using System.ComponentModel;
    
    namespace Neo.SmartContract
    {
        public class HelloWorld : Framework.SmartContract
        {
            public static object Main(string operation, params object[] args)
            {
                switch (operation)
                {
                    case "Hello":
                        Hello((string)args[0]);
                        return true;
                    default:
                        return false;
                }
            }
            public static void Hello(string msg)
            {
                Runtime.Notify(msg);
            }
        }
    }
    ```

    >설명: Hello 방법 중 Runtime.Notify가 전송한 파라미터는 체인상에 공지됩니다. 

2. 명령 `./ontology contract deploy --code hello.avm --name 'Hello' --version '1.0' --author 'ester' --email 'tester@test.com' --desc 'helloworld' --account 1 --gaslimit 100000000`를 사용하여 계약을 네트워크에 설치합니다. 계약설치명령에 관한 자세한 정보는 `./ontology contract deploy -h`를 사용하여 확인할 수 있습니다. 

    ```
    Deploy contract:
      Contract Address:362cb5608b3eca61d4846591ebb49688900fedd0
      TxHash:c49865b16009177ed4b06add97f7be1b0b1c246e4d4575c367e918da294d3287
    
    Tip:
      Using './ontology info status c49865b16009177ed4b06add97f7be1b0b1c246e4d4575c367e918da294d3287' to query transaction status
    ```

3. 브라우저에 `http://localhost:20334/api/v1/contract/362cb5608b3eca61d4846591ebb49688900fedd0`를 입력하고 rest인터페이스를 호출하여 계약정보를 조회합니다. 
  
    ```
    {"Action":"getcontract","Desc":"SUCCESS","Error":0,"Result":{"Code":"54c56b6c7...","NeedStorage":false,"Name":"Hello","CodeVersion":"1.0","Author":"ester","Email":
    "tester@test.com","Description":"helloworld"},"Version":"1.0.0"}
    ```

4. 명령 `./ontology contract invoke --address 362cb5608b3eca61d4846591ebb49688900fedd0 --params string:Hello,[string:tester] --gaslimit 200000`을 사용하여 설치된 계약을 호출합니다. 


    ```
    Invoke:d0ed0f908896b4eb916584d461ca3e8b60b52c36 Params:["Hello",["tester"]]
    Password:
      TxHash:2cc94de8c26fce3be233bef007ec3492043ffc304b79a02d9b612df96e950186
    
    Tip:
      Using './ontology info status 2cc94de8c26fce3be233bef007ec3492043ffc304b79a02d9b612df96e950186' to query transaction status
    ```

    >설명 : `--params string:Hello,[string:tester]`는 계약호출 전송을 지정하는 파라미터이며 여기에서는 각각 `string:Hello`和`[string:tester]`파라미터를 전송합니다. 이 파라미터는 계약코드 중의 MAin함수가 실행하는 파라미터에 전송됩니다. 

5. 가이드에 따라 명령`./ontology info status 2cc94de8c26fce3be233bef007ec3492043ffc304b79a02d9b612df96e950186`을 사용하여 트랜젝션 상황을 조회합니다. 

    ```
    Transaction states:
    {
       "TxHash": "2cc94de8c26fce3be233bef007ec3492043ffc304b79a02d9b612df96e950186",
       "State": 1,
       "GasConsumed": 0,
       "Notify": [
          {
             "ContractAddress": "362cb5608b3eca61d4846591ebb49688900fedd0",
             "States": [
                "746573746572"
             ]
          }
       ]
    }
    ```

6. 리턴된 결과 중 States는 계약호출이 공지한 msg정보이며 리턴결과는 16진수 문자열입니다. 코드변환기로 변환 후의 결과는 바로 ‘tester’이며 이는 바로 4번째 단계에서 전송한 두 번째 파라미터 입니다. 



