
# Punica-Cli

## 개요

Punica-Cli는 개발자가 전체 SDK 없이도 스마트 컨트랙트를 컴파일, 배치 및 호출 할 수 있도록 설계된 명령행 인터페이스입니다. 현재 Punica-Cli에서는 [Punica Python CLI](https://github.com/punicasuite/punica-python) 와 [Punica TypeScript CLI](https://github.com/punicasuite/punica-ts) 두 가지 언어가 제공됩니다.

### 특징:
* 지능형 스마트 컨트랙트 컴파일, 배치, 호출 및 테스팅 지원
* Python과 TypeScript 프로그래밍 언어 지원
* Punica-Box를 통한 dApp 템플릿 다운로드
* 스마트 컨트랙트 포장 관리 도구
* 월렛 파일 관리 지원
<p><br>

## 설치

```shell
pip3 install punica
```
```
npm install punica-ts -g
```
또는 
```shell
python setup.py install
```
**참고: Python을 사용할 경우, [Python v3.7](https://www.python.org/downloads/release/python-370/) 이상이 설치되어있는지 확인하세요.**
<p><br>


## 사용가능한 명령

```shell
punica
Usage: punica [OPTIONS] COMMAND [ARGS]...

Options:
  -p, --project PATH  Specify a punica project directory.
  -v, --version       Show the version and exit.
  -h, --help          Show this message and exit.

Commands:
  compile  Compile the specified contracts to avm and...
  deploy   Deploys the specified contracts to specified...
  init     Initialize new and empty Ontology DApp...
  invoke   Invoke the function list in default-config or...
  node     Ontology Blockchain private net in test mode.
  scpm     Smart contract package manager，support...
  smartx   Ontology smart contract IDE,SmartX...
  test     Unit test with specified smart contract
  unbox    Download a Punica Box, a pre-built Ontology...
  wallet   Manager your ontid, account, asset.
```

## 시작하기


### 새 프로젝트 초기화

스마트 컨트랙트 없이 `init` 명령을 사용하여 새로운 Punica프로젝트를 만들 수 있습니다.

```shell
punica init
```

작업이 완료되면 다음 항목이 포함된 프로젝트 구조가 생성됩니다.

- `contracts/`: 스마트 컨트랙트를 위한 디렉토리
- `src/`: 소스 파일을 위한 디렉토리
- `test/`: 애플리케이션 및 계약 테스트를 위한 테스트 파일 디렉토리
- `wallet/`: 저장된 온톨로지 월렛 파일의 디렉토리

자세한 사용방법은 `punica init --help`를 사용해주세요.
```shell
punica init --help
Usage: punica init [OPTIONS]

  Initialize new and empty Ontology DApp project.

Options:
  -h, --help  Show this message and exit.
```

**참고**: 프로젝트의 루트 디렉토리를 punica-cli에서 실행하지 않는다면, `-p` 또는 `--project` 옵션을 이용하여 dApp 프로젝트 경로를 지정해야합니다.
<p><br>

### Punica-Box 프로젝트 사용하기

시작하기 전에 Punica Boxes의 dApps 및 프로젝트 템플릿 예제가 프로젝트 시작에 도움이 될 것 입니다.

튜토리얼에는 계정간의 거래를 할 수 있는 OEP4 토큰을 만드는 [Tutorialtoken-box](https://github.com/punica-box/tutorialtoken-box) 전체를 사용합니다.

새로운 Punica 프로젝트를 위해 새로운 디렉토리를 생성하세요.

```shell
mkdir tutorialtoken
cd tutorialtoken
```

Tutorialtoken-box Box를 다운로드 ("unbox")하세요:

```shell
punica unbox tutorialtoken
```

자세한 사용방법은 `punica unbox --help`를 사용해주세요.
```shell
punica unbox --help
Usage: punica unbox [OPTIONS] BOX_NAME

  Download a Punica Box, a pre-built Ontology DApp project.

Options:
  -h, --help  Show this message and exit.
```

#### Punica-Cli가 사용하는 네트워크 구성

The Tutorialtoken-box프로젝트 아래에 있는 `punica-config.json'문서의 네트워크 기본 설정값은 테스트넷입니다.파일의 DefaultNet 설정을 변경하여 Punica-Cli가 사용할 네트워크를 설정할 수 있습니다.

punica-config.json 예제:
```json
{
  "networks": {
    "testNet": {
      "host": "http://polaris3.ont.io",
      "port": 20336
    },
    "mainNet": {
      "host": "http://dappnode1.ont.io",
      "port": 20336
    },
    "privateNet": {
      "host": "http://127.0.0.1",
      "port": 20336
    }
  },
  "defaultNet":"testNet"
}
```

**참고**:
- `punica unbox <box-name>` 명령을 사용하여 다른 [Punica Boxes](http://punica.ont.io/boxes/)를 다운로드 할 수 있습니다.
- 프로젝트의 루트 디렉토리에서 punica-cli를 실행하지 않을 때, `-p` 또는 `--project` 옵션을 이용하여 dApp 프로젝트 경로를 지정해야합니다.
<p><br>


### 컴파일링

`compile` 명령을 사용하여 Tutorialtoken-box 스마트 컨트랙트를 컴파일 할 수 있습니다.

```shell
punica compile
```

모든 것이 원활하게 진행되면 계약/빌드 폴더에서 `avm` 과 `abi` 파일을 `contracts/build` 폴더에서 찾을 수 있습니다.

```shell
contacts
    ├─build
    │      contract.avm
    │      contract_abi.json
```
자세한 사용방법은 `punica compile --help` 를 사용해주세요.

```shell
punica compile --help
Usage: punica compile [OPTIONS] CONTRACT_NAME

  Compile the specified contracts to avm and abi file.

Options:
  --contracts Only compile the specified contract
  -h, --help  Show this message and exit.
```
**스마트 컨트랙트 컴파일 후 배치 비용 지불시, 계정에 ONG가 충분한지 확인해야합니다(다음 단계 참조), 그렇지 않을경우 배치에 실패하게됩니다. Tutorialtoken-box 주소는 ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6**

**참조**: 프로젝트의 루트 디렉토리에서 punica-cli 를 실행하지 않는 경우, `-p` 또는 `--project` 옵션을 이용하여 dApp 프로젝트 경로를 지정해야합니다.
<p><br>

### 배치

Tutotialtoken-box 스마트 컨트랙트를 선택한 네트워크에 배치하려면 다음을 실행하세요.

```shell
punica deploy
```

배치 단계를 간단히 보면 아래와 같습니다.

```shell
Using network 'testNet'.

Running deployment: oep4.avm
	Deploying...
	... 0x0131c56b6a00527ac46a51527ac46a00c3044e616d659c6409006593096c7566
	Deploy to: 0xf9f47e6a80482eb1c8831789f46dbc5a4f606222
Deploy successful to network...
	... 0xc08a440a7f93cc7229fee15b55455fac51ec15153753303bd252c710547ecb62
Enjoy your contract:)
```

자세한 사용방법은 `punica deploy --help` 를 사용해주세요.

```shell
punica deploy --help
Usage: punica deploy [OPTIONS]

  Deploys the specified contracts to specified chain.

Options:
  --network TEXT   Specify which network the contract will be deployed.
  --avm TEXT       Specify which avm file will be deployed.
  --wallet TEXT    Specify which wallet file will be used.
  -h, --help       Show this message and exit.
```

**참고**:

- 프로젝트의 루트 디렉토리에서 punica-cli 를 실행하지 않는 경우, `-p` 또는 `--project` 옵션을 이용하여 dApp 프로젝트 경로를 지정해야합니다.
- 여러개의 `avm` 파일이 `contracts/build` 디렉토리에 있다면, 배치할 계약서를 지정하기위해 `--avm` 옵션을 사용하여야 합니다.
- 다중 월렛이 `wallet` 디렉토리에 있다면, `--wallet` 옵션을 사용하여 사용할 월렛을 지정해야합니다. 지정하지 않을경우 월렛 파일이 `wallet` 디렉토리 파일에 자동 배치됩니다.
<p><br>

### 호출

스마트 컨트랙트를 설정하려면 특정 기능을 호출하기 전에 `punica invoke` 명령을 실행해야합니다.

```shell
punica invoke
```

출력:
```shell
Running invocation: oep4.json
Using network 'testNet'.

Unlock default payer account...
	Unlock account: ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6
    Please input account password: 
	Unlock successful...
Invoking Name...
	Invoke successful...
		... Invoke result: 546f6b656e4e616d65
Invoking Symbol......
```

Tutorialtoken-box의 `default-config.json` 파일에는 스마트 컨트랙트 기능을 정의하는 'invokeConfig' 섹션이 있습니다.

```json
"invokeConfig":{
    "abi": "oep4_token_abi.json",
    "defaultPayer": "ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6",
    "gasPrice": 0,
    "gasLimit": 21000000,
    "functions": [
        {   
	    "name": "Name",
            "params": {},
            "signers": {},
            "preExec": true
        },
	{
            "name": "Symbol",
            "params": {},
            "signers": {},
            "preExec": true
        },
	{
            "name": "Decimal",
            "params": {},
            "signers": {},
            "preExec": true
        },
        {
	    "name": "TotalSupply",
            "params": {},
            "signers": {},
            "preExec": true
        },
        {
	    "name":"BalanceOf",
            "params": {
                "account": "ByteArray:ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6"
            },
            "signers": {},
            "preExec": true
        },
        {
	    "name": "Transfer",
            "params": {
                "from_acct": "ByteArray:ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6",
                "to_acct": "ByteArray:AazEvfQPcQ2GEFFPLF1ZLwQ7K5jDn81hve",
                "amount": 1
            },
            "signers": {
                "m": 1,
                "signer": ["ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6"]
            },
            "preExec": false
        },
        {
	    "name": "TransferMulti",
            "params": {
                "args": [
                    {
                        "from": "ByteArray:ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6",
                        "to": "ByteArray:AazEvfQPcQ2GEFFPLF1ZLwQ7K5jDn81hve",
                        "amount": 1
                    },
                    {
                        "from": "ByteArray:AazEvfQPcQ2GEFFPLF1ZLwQ7K5jDn81hve",
                        "to": "ByteArray:Ad4H6AB3iY7gBGNukgBLgLiB6p3v627gz1",
                        "amount": 2
                    }
                ]
            },
            "signers": {
                "m": 1,
                "signer": ["ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6", "AazEvfQPcQ2GEFFPLF1ZLwQ7K5jDn81hve"]
            },
            "payer": "ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6",
            "preExec": false
        },
        {
	    "name": "Allowance",
            "params": {
                "owner": "ByteArray:ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6",
                "spender": "ByteArray:AazEvfQPcQ2GEFFPLF1ZLwQ7K5jDn81hve"
            },
            "signers": {
                "m": 1,
                "signer": ["ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6"]
            },
            "preExec": false
        },
        {
	    "name": "TransferFrom",
            "params": {
                "sender": "ByteArray:AazEvfQPcQ2GEFFPLF1ZLwQ7K5jDn81hve",
                "from_acct": "ByteArray:ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6",
                "to_acct": "ByteArray:Ad4H6AB3iY7gBGNukgBLgLiB6p3v627gz1",
                "amount": 1
            },
            "signers": {
                "m": 1,
                "signer": ["ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6"]
            },
            "preExec": false
        },
        {
	    "name": "Init",
            "params": {},
            "signers": {},
            "preExec": true
        }
    ]
}
```

사용 가능한 기능 목록을 보려면:
```shell
punica invoke list
```

Tutorialtoken-box에서 `punica invoke list' 를 실행할 때의 응답
```shell
All Functions:
         Init
         Name
         Symbol
         Decimal
         TotalSupply
         BalanceOf
         Transfer
         TransferMulti
         Allowance
         TransferFrom
```

자세한 사용방법은 `punica invoke --help`를 사용해주세요

```shell
punica invoke --help
Usage: punica invoke [OPTIONS]

  Invoke the function list in punica-config.

Options:
  --network TEXT   Specify which network the contract will be deployed.
  --wallet TEXT    Specify which wallet file will be used.
  --functions Text Specify which function will be used.
  -h, --help       Show this message and exit.
```

**참고**:

- 프로젝트의 루트 디렉토리에서 punica-cli 를 실행하지 않는 경우, `-p` 또는 `--project` 옵션을 이용하여 dApp 프로젝트 경로를 지정해야합니다.
- 다중 월렛이 `wallet` 디렉토리에 있다면, `--wallet` 옵션을 사용하여 사용할 월렛을 지정해야합니다. 지정하지 않을경우 월렛 파일이 `wallet` 디렉토리 파일에 자동 배치됩니다.
<p><br>

### 노드

미리 만들어진 Ontology private-net Solo-chain의 다운로드 링크를 보여줍니다.

자세한 사용방법은 `punica node --help'를 사용해주세요.
```shell
punica node --help
Usage: punica node [OPTIONS]

   Ontology Blockchain private net in test mode. please download from
   https://github.com/punicasuite/solo-chain/releases

Options:
   -h, --help  Show this message and exit.
```
<p><br>

### Scpm (시행전)

스마트 컨트랙트 패키지 관리를 사용하면 커뮤니티 저장소에 다운로드 및 게제할 수 있습니다.

```shell
punica scpm
Usage: punica scpm [OPTIONS]

   smart contract package manager，support download and publish.

Options:
   -h, --help  Show this message and exit.
```
<p><br>

### Smartx (시행전)

SmartX 는 온톨로지 온라인 스마트 컨트랙트 IDE 및 디버거입니다.

```shell
punica smartx

Please go to Smartx for debugging smart contracts:
http://smartx.ont.io/#/
```
<p><br>

### 단위 테스트

테스트 기능을 사용하면 테스트 파일을 사용하여 스마트 컨트랙트에 대해 자동화된 테스트를 실행할 수 있습니다.

자세한 사용방법은 `punica test --help' 를 사용해주세요.
```shell
punica test -h
Usage: punica test [OPTIONS] COMMAND [ARGS]...

  Unit test with specified smart contract

Options:
  --file TEXT  Specify which test file will be used.
  -h, --help   Show this message and exit.

Commands:
  template  generate test template file
```
<p><br>

### 월렛

계정 또는 OntID 추가, 리스트, 삭제 및 거래와 같은 기능으로 월렛을 관리할 수 있습니다.

예제:
```shell
punica wallet account list
Account:
        ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6
        AazEvfQPcQ2GEFFPLF1ZLwQ7K5jDn81hve
        Ad4H6AB3iY7gBGNukgBLgLiB6p3v627gz1
        ARLvwmvJ38stT9MKD78YtpDak3MENZkoxF
```

자세한 사용방법은 `punica wallet --help' 를 사용해주세요.
```shell
punica wallet --help
Usage: punica wallet [OPTIONS] COMMAND [ARGS]...

   Manager your asset, ontid, account.

Options:
   -h, --help  Show this message and exit.

Commands:
   account  Manage your account.
   asset    Manage your asset, transfer, balance,...
   ontid    Manage your ont_id, list or add.

```
