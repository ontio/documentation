
## 스마트 컨트랙트이란?

스마트 컨트랙트는 1994년 Nick Szabo가 최조 제안한 개념입니다. 정보 제공방식으로 계약을 보급, 검증 또는 시행하도록 고안한 컴퓨터 프로토콜입니다. 스마트 컨트랙트는 제 3자 없이 트랜션가 가능하고, 이러한 트랜잭션는 추적이 가능하며 트랜잭션내역을 수정할 수 없습니다.

블록체인 기술의 탈중앙화, 조작불가, 신뢰성이라는 환경이 스마트 컨트랙트가 시장에서 유용하게 사용될 수 있고, 자리잡도록 도왔습니다.

## 온톨로지 스마트 컨트랙트의 특징은 무엇인가요?

온톨로지 스마트 컨트랙트는 다기능, 확장성, 고성능, 다국어, 교차계약, 교차가상머신 등 모든 기능을 하나의 시스템에 통합하였습니다. 또한, 온톨로지 스마트 컨트랙트는 여러 프로그래밍 언어를 지원하여 개발자가 새로운 프로그래밍 언어를 익힐 시간을 절약할 수 있도록 합니다. 현재까지 지원되는 언어는 C#, Python등으로 Java, C++, Rust, Go, and JavaScript를 포함한 다른 언어까지 지원할 것 입니다.

온톨로지 스마트 컨트랙트는 확실한 고성능의 확장기능 제공에 대화형 서비스와 버추얼 머신 두가지 모듈을 포함합니다. 대화형 서비스는 버추얼 머신와 블록체인 원장간의 상호작용을 제공합니다. 버추얼 머신는 스마트 컨트랙트의 실행환경을 제공합니다. 대화형 서비스는 기본 서비스와 NEO VM서비스를 포함합니다. 기본 서비는 기본 체인에 특수 스마트 컨트랙트 구현을 제공하며 신속하고 편리하게 사용할 수 있게합니다. NeoVM 서비스는 NeoVM의 API를 제공하여 외부에서 통신하므로 스마트 컨트랙트의 호출 기능을 향상시킬 수 있습니다.


![ontology smart contract architecture.png](https://raw.githubusercontent.com/ontio/ontology-smartcontract/master/smart-contract-tutorial/images/smartcontract_architecture.png)



## 컨트랙트 유형

온톨로지 스마트 컨트랙트는 네이티브 계약과 NeoVm 계약 두 종류로 나뉩니다. 네이티브 계약은 온톨로지 기반에서 직접 작성한 계약으로 일반적인 계약처럼 계약 코드를 작성할 필요가 없으며 실행 효율성이 높아 보통계약에 대해 최적화 되어있습니다. Oracle, DID, 관리 권한, 데이터 거래소 모두 네이트브 계약 서비스로 포함되어있습니다. NeoVm계약은 NeoVm가상 시스템에서 실행되는 계약으로 해당 계약 코드를 직접 작성해야합니다. 현재까지 지원되는 언어는 Java, C #, Python입니다. NeoVm은 자체적으로 가볍고 확장 가능한 고성능 기능을 가지고 있어  Interop 서비스계층과의 결합을 통해 버추얼 머신과 원장간의 상호 작용을 원활하게 연결할 수 있습니다.


![ontology smart contract type.png](https://raw.githubusercontent.com/ontio/ontology-smartcontract/master/smart-contract-tutorial/images/smartcontract_type.png)


## 계약관리

가상머신 유형

```
// Prefix of address
type VmType byte

const (
Native = VmType(0xFF)
NEOVM  = VmType(0x80)
WASMVM = VmType(0x90)
)

```

가상머신 코드 구조



```
type VmCode struct {
VmType VmType
Code   []byte
}

```

transaction payload사용

```
// InvokeCode is an implementation of transaction payload for invoke smartcontract
type InvokeCode struct {
GasLimit common.Fixed64
Code     stypes.VmCode
}

```

온톨로지 스마트 컨트랙트를 실행하려면 계약을 실행하는 스크립트와 버추얼 머신이 필요합니다. 스마트 컨트랙트 스케줄러는 버추얼 머신의 유형에 따라 다른 컨트랙트를 실행합니다. 진행 과정에서 컨트랙트는 AppCall명령(컨트랙트 운영의 필수 파라미터 포함)을 호출하여 스마트 컨트랙트 스케줄러를 움직이게 합니다. 스케줄러는 입력된 파라미터에 따라 해당 버추얼머신 스크립트를 컨트랙트가 완성될 때까지 실행하도록 합니다.

![process](http://upload-images.jianshu.io/upload_images/150344-ac402b1c8eb3aa9a.jpeg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)




## 지불 모델

### 1. GAS Limit
Gas limit은 스마트 컨트랙트를 실행할 때 pcode 프로세스 단계에서 계산을 실행하는데 사용됩니다. 이론상으로는 스마트 컨트랙트에서 더욱 복잡한 계산이 진행될수록 Gas limit이 더 높아지고 가장 적은 Gas limit은 30000입니다.


### 2. GAS 가격

Gas 가격은 opcode으로 가격이 측정됩니다. Gas 가격이 높을수록 컨센서스 노드가 거래를 우선적으로 처리할 우선순위가 높아집니다.

### 3. Transaction Fee

거래비용은 Gas limit과 Gas 가격의 곱입니다. 실제 거래비용는 다음과 같은 3가지 상황으로 나뉩니다. 


#### 3.1. opcode를 실행하는 단계의 수는 gas limit과 같습니다.


**. transaction fee =  gas price * gas limit**

#### 3.2. opcode를 실행하는 단계의 수는 gas limit과 같습니다.

**transaction fee =  gas price * gas limit**

거래가 실패해도 가스는 환불되지 않습니다.

#### 3.3. The number of steps executing opcode를 실행하는 단계의 수는 Gas limit보다 적습니다.
**transaction fee =  gas price * (opcode use)**

초과 gas는 환불됩니다.

**GAS LIMIT의 고정 소비량은 모든 ONT, ONG거래의 20000입니다.**

### 4. Gas 요금 설정 방법

Ontology CLI 혹은 SDK를 사용하여 수동으로 gas 가격 및 gas limit 파라미터를 설정합니다.

#### 4.1 CLI

ONT거래를 예로 들어 Ontology CLI를 사용하여 수동으로 gas 가격 및 gas limit 파라미터를 설정하세요.

\--gasprice


\--gaslimit

- 잔금 확인：

```
./ontology asset balance TA7FwLmuX6qMcWTgZtUxt6tjzFgfaBM5sz
```

![image](https://ws4.sinaimg.cn/large/006tKfTcgy1fs3ot3e084j30tc03q0tn.jpg)

- 거래：
```
./ontology asset transfer --from TA7FwLmuX6qMcWTgZtUxt6tjzFgfaBM5sz  --to TA7FwLmuX6qMcWTgZtUxt6tjzFgfaBM5sz  --amount 1000 --gasprice 5 --gaslimit 40000
```

![image](https://ws4.sinaimg.cn/large/006tKfTcgy1fs3ot31uq6j30sc03qaav.jpg)

거래 금액= 1000 ONT, gas price = 5, gas limit = 40000

최종 gas 소비량 = 1787019.99985 - 1787019.9997 = 0.00015.


#### 4.2 SDK

GAS LIMIT 과 GAS PRICE는 Java SDK와 Golang SDK를 사용하여 설정할 수 있습니다.


전송 과정을 예로 들어봅시다 (JAVA SDK):

```
String sendTransfer(Account sendAcct, String recvAddr, long amount, Account payerAcct, long gaslimit, long gasprice)(Account sendAcct, String recvAddr, long amount, Account payerAcct, long gaslimit, long gasprice)
```

You can set gas price when calling **sendTransfer**.

[JAVA SDK](https://github.com/ontio/ontology-java-sdk/tree/master/docs/cn)

[Golang SDK](https://github.com/ontio/ontology-go-sdk)


## DApp

dApp은 탈중앙화 애플리케이션의 축약형입니다. dApp은 탈중앙화 peer-to-peer 네트워크에서 실행되는 백 엔드 코드로 구성됩니다. dApp에는 백 엔드에 대한 호출을 생성하는 프로트 엔드 코드로 생성된 사용자 인터페이스가 있을 수도 있습니다. 또한 dApp은 중앙화 권한을 필요로 하지 않으며 사용자와 공급자 간의 직접적인 상호작용을 허용합니다.

![dapp](https://upload-images.jianshu.io/upload_images/150344-450fe6ab35cca843.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![app vs dapp.png](https://upload-images.jianshu.io/upload_images/150344-db176bdda1168c42.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

dApp이 가지고 있는 공통 기능:

*   **오픈 소스**. 이상적으로는 자율성에 의해 관리 되어야 하고 모든 변경은 사용자의 컨센서스(또는 다수)에 의해 결정되어야 합니다. 코드 베이스는 정밀 조사가 가능해야 합니다.

*   **탈중앙화**. 애플리케이션의 모든 작업 기록은 중앙 집중화를 피하기 위해 퍼블릭 탈중앙화 블록체인 위에 저장되어야 합니다.

*   **인센티브**. 암호화 토큰을 사용하여 블록체인 인증자를 보상해야 합니다.

*   **프로토콜** 애플리케이션 커뮤니티는 가치 증명을 위해 암호화 알고리즘에 동의해야 합니다. 예를 들어, 비트코인은 [Proof of Work (PoW)](https://en.bitcoin.it/wiki/Proof_of_work)를 사용하고 있으며, 이더리움은 [hybrid PoW/Proof of Stake (PoS)](https://github.com/ethereum/wiki/wiki/Proof-of-Stake-FAQ)[5](https://blockgeeks.com/guides/dapps/#sdfootnote5sym) 계획을 가진 PoW를 사용하고 있습니다.

