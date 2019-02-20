
# 시작하기

- [조작](#operation)
  - [구성](#configuration)
  - [월렛 데이터 디렉토리](#wallet-data-directory)
  - [IP 주소 엑세스 제어](#ip-address-access-control)
  - [IP 포트 번호](#ip-port-number)
  - [ABI 파일 디렉토리](#abi-file-directory)
  - [로그](#logging)
- [월렛 데이터 가져오기](#importing-existing-wallet-data)

## 조작
기본 옵션으로 서비스를 빠르게 실행시키려면 명령을 실행하기만 하면 됩니다.
```
./sigsvr
```
이 서비스는 다음에서 이용할 수 있습니다.
```
http://localhost:20000/cli
```

## 구성
이 서비스는 기본옵션으로 사전 구성되어 제공되지만 특정 프로젝트에 맞게 조정할 수 있습니다. 모든 구성은 옵션 파라미터를 통해 이루어집니다. 
예:

```
./sigsvr --walletdir ./data/wallets --abi ./data/abi
```
아래에는 자세히 설명된 구성 옵션의 조합을 사용할 수 있습니다.

### 월렛 데이터 디렉토리
서비스는 로컬 월렛 위치에 저장됩니다. 기본으로 설정된 월렛 파일의 위치는 `$GOPATH/src/github.com/ontio/ontology/tools/wallet_data`입니다. 월렛 파일의 위치를 변경하려면 `walletdir` 파라미터 설정을 사용하세요.

예제:
```
./sigsvr --walletdir ./data/wallets
```

### IP 주소 엑세스 제어
서비스에 엑세스 할 수 있는 IP주소입니다. 로컬 컴퓨터에서만 엑세스 할 수 있도록 설정된 기본 값은 `127.0.0.1`입니다. 이외의 서비스를 외부에서 엑세스 할 수 있게 하기 위해서 `cliaddress`파라미터를 사용하세요.

예제:
```
./sigsvr --cliaddress 0.0.0.0
```

### IP 포트 번호
서비스를 사용할 수 있는 포트번호입니다. 기본으로 설정된 포트 번호는 `20000`입니다. 위치를 변경하려면 `cliport`파라미터를 사용하세요.

예제:
```
./sigsvr --cliport 1337
```

### ABI 파일 디렉토리
Ontology Native 스마트 컨트랙트 ABI파일 위치가 나타납니다. 기본으로 설정된 ABI 파일 위치는 `$GOPATH/src/github.com/ontio/ontology/tools/abi`입니다. 위치를 변경하려면 `abi` 파라미터를 사용하세요.

예제:
```
./sigsvr --abi ./data/abi
```

### 로그
다양한 수준의 서비스로 로깅이 가능합니다. 기본으로 설정된 값은 Info (2)이지만 사용할 수 있는 로깅 수준은 7가지 입니다.

0. Trace
1. Debug
2. Info (default)
3. Warn
4. Error
5. Fatal
6. Max Level

예제:
```
./sigsvr --loglevel 0
```

## 월렛 데이터 가져오기
사용자는 오프라인에서 생성된 월렛 파일을 서비스로 가져오려 할 수 있습니다. 이를 수행하기 위해서는 import 명령을 `wallet` 옵션과 함께 사용하여 이미 존재하는 월렛 파일을 가져올 수 있습니다. 이 서비스는 서비스 구성 옵션과는 별개로 월렛 데이터를 서비스로 가져오고 실제 서비스는 실행하지 않습니다.
예제:
```
./sigsvr import --wallet ./wallet_2018-10-31-23-59-59.dat
```

이는 서비스 내보내기 기능을 사용하여 월렛을 가져오는데 유용합니다.
