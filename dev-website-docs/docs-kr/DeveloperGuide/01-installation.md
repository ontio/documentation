


[![GoDoc](https://godoc.org/github.com/ontio/ontology?status.svg)](https://godoc.org/github.com/ontio/ontology)




<!-- TOC -->

- [Build development environment](#build-development-environment)
- [Get Ontology](#get-ontology)
    - [Get from release](#get-from-release)
    - [Get from source code](#get-from-source-code)
- [Run Ontology](#run-ontology)
    - [MainNet sync node](#mainnet-sync-node)
    - [Public test network Polaris sync node (TestNet)](#public-test-network-polaris-sync-node-testnet)
    - [Testmode](#testmode)
    - [Run in docker](#run-in-docker)
- [Some examples](#some-examples)
    - [ONT transfer sample](#ont-transfer-sample)
    - [Query transfer status sample](#query-transfer-status-sample)
    - [Query account balance sample](#query-account-balance-sample)

<!-- /TOC -->

## 개발 환경 구축
온톨로지를 구축하기 위한 요구 사항은 다음과 같습니다.

- Golang 1.9 버전 이상
- Glide (타사 패키지 관리 도구)
- 제대로 구성된 Go 언어 환경
- Golang 지원 운영 체제

## 온톨로지 얻기

### release를 통해 얻기
- ` curl https://dev.ont.io/ontology_install | sh `명령을 사용하여 최신 버전의 온톨로지 얻기.

- [release page](https://github.com/ontio/ontology/releases)에서 다른 버전도 다운로드할 수 있습니다.
.

### 소스코드로 얻기

온톨로지 저장소를 적절한$GOPATH/src/github.com/ontio 디렉토리에 복제하세요.

```
$ git clone https://github.com/ontio/ontology.git
```
혹은
```
$ go get github.com/ontio/ontology
```
타사 관리 도구 glide를 사용하여 저장소로 가지고 오기

```
$ cd $GOPATH/src/github.com/ontio/ontology
$ glide install
```

make로 소스코드 컴파일하기

```
$ make all
```

성공적으로 컴파일 시킨 후 2개의 실행가능한 프로그램이 보일 것 이다.

- `ontology`: 노드 제어를위한 노드 프로그램 / 명령행 프로그램.
- `tools/sigsvr`: (선택 사항) Ontology Signature Server - sigsvr은 몇 가지 특별한 요구 사항에 대한 트랜잭션 서명을위한 RPC 서버입니다. 자세한 문서는[here](https://github.com/ontio/documentation/blob/master/docs/pages/doc_en/Ontology/sigsvr_en.md)에서 찾을 수 있습니다.

## 온톨로지 운행

온톨로지를 4가지 모드로 실행할 수 있습니다.

1) MainNet (./ontology)
2) TestNet (./ontology --networkid 2)
3) Testmode (./ontology --testmode)
4) Docker

예 : Windows (64 비트)의 경우 명령 프롬프트를 사용하여 Ontology 릴리스를 설치 한 디렉토리로 이동 한 다음 `start ontology-windows-amd64.exe --networkid 2`를 입력하면 TestNet에 동기화됩니다. 도움말 명령은 `ontology-windows-amd64.exe --networkid 2 help`입니다.

### MainNet 동기화 노드

온톨로지 직접 실행

   ```
	./ontology
   ```
온톨로지 메인넷에 연결한다

### 퍼블릭 테스트 네트워크 Polaris동기화 노드(테스트넷)

온톨로지 직접 실행

   ```
	./ontology --networkid 2
   ```
   
온톨로지 테스트 넷 연결

### 테스트 모드

호스트에 디렉토리를 작성하고 디렉토리에 다음 파일을 저장하세요.
- 노드 프로그램 `ontology`
- 월렛 파일 `wallet.dat` (`wallet.dat` 는 `./ontology account add -d`에 의해 생성될 수 있습니다)

`$ ./ontology --testmode` 은 단일 호스트 테스트넷을 실행할 수 있습니다.

다음은 싱글 호스트 구성의 예입니다.:

- 디렉토리 구조

    ```shell
    $ tree
    └── ontology
        ├── ontology
        └── wallet.dat
    ```

### 도커에서 실행하기

사용자의 컴퓨터에 도커가 있는지 확인하세요.

1. 토커 이미지 만들기

    - 소스 코드의 루트 디렉토리에서 `make docker`make docker를 실행하면 docker에서 온톨로지 이미지가 생성됩니다.

2. 온톨로지 이미지 실행

    - `docker run ontio/ontology` 을 사용하여 온톨로지를 실행하세요.

    - 이미지가 실행되는 동안 대화형 키보드 입력을 허용해야하는 경우 `docker run -ti ontio/ontology` 명령을 사용하여 이미지를 시작할 수 있습니다.

    - 런타임에 이미지로 생성 된 데이터를 유지해야하는 경우 docker의 데이터 지속성 기능 (예 : 볼륨)을 참조 할 수 있습니다.

    - I온톨로지 파라미터를 추가해야하는 경우 `docker run ontio/ontology` such as `docker run ontio/ontology --networkid 2`와 같은 `docker run ontio/ontology`를 실행 한 후 해당 파라미터를 직접 추가 할 수 있습니다. 온톨로지 명령행 파라미터는 여기를 참조하십시오.
     The parameters of ontology command line refer to [here](./docs/specifications/cli_user_guide.md).

## 예제들

### ONT 거래 예제
 -- from: transfer from； -- to: transfer to； -- amount: ONT amount；
```shell
 ./ontology asset transfer  --from=ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48 --to=AaCe8nVkMRABnp5YgEjYZ9E5KYCxks2uce --amount=10
```
거래를 성공하면 다음과 같이 결과가 표시됩니다.

```shell
Transfer ONT
  From:ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48
  To:AaCe8nVkMRABnp5YgEjYZ9E5KYCxks2uce
  Amount:10
  TxHash:437bff5dee9a1894ad421d55b8c70a2b7f34c574de0225046531e32faa1f94ce
```
TxHash는 전송 트랜잭션 해시이며 TxHash로 전송 결과를 쿼리 할 수 있습니다. 블록 시간으로 인해 블록이 생성되고 추가되기 전에 전송 트랜잭션이 실행되지 않습니다.

ONG를 전송하려면 --asset = ong 플래그를 추가하세요.

ONT는 정수이고 소수 자릿수는없는 반면 ONG는 9 자릿수입니다. 자세한 정보는 [ONG에 대해 알아야 할 모든 것](https://medium.com/ontologynetwork/everything-you-need-to-know-about-ong-582ed216b870)을 클릭 후 읽어주세요.

```shell
./ontology asset transfer --from=ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48 --to=ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48 --amount=95.479777254 --asset=ong
```
성공적인 거래 후 결과는 아래와 같이 나타납니다.

```shell
Transfer ONG
  From:ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48
  To:AaCe8nVkMRABnp5YgEjYZ9E5KYCxks2uce
  Amount:95.479777254
  TxHash:e4245d83607e6644c360b6007045017b5c5d89d9f0f5a9c3b37801018f789cc3
```

계정 주소를 사용할 때 인덱스 혹은 계정 레이블을 사용할 수 있습니다. 인덱스는 월렛에 있는 특정 계정의 일련 번호입니다. 인덱스는 1에서 시작하고 레이블은 월렛의 유니크한 별명입니다.

```shell
./ontology asset transfer --from=1 --to=2 --amount=10
```

### 쿼리 거래 상태 샘플

```shell
./ontology info status <TxHash>
```

예제:

```shell
./ontology info status 10dede8b57ce0b272b4d51ab282aaf0988a4005e980d25bd49685005cc76ba7f
```

거래:

```shell
Transaction:transfer success
From:AXkDGfr9thEqWmCKpTtQYaazJRwQzH48eC
To:AYiToLDT2yZuNs3PZieXcdTpyC5VWQmfaN
Amount:10
```

### 쿼리 잔액 샘플

```shell
./ontology asset balance <address|index|label>
```

예제:

```shell
./ontology asset balance ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48
```

혹은

```shell
./ontology asset balance 1
```
결과:
```shell
BalanceOf:ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48
  ONT:989979697
  ONG:28165900
```

더 많은 예제를 보고싶으시다면 [CLI User Guide](https://ontio.github.io/documentation/cli_user_guide_en.html)에 .


