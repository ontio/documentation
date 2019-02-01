<div align="center">
<img src="https://avatars1.githubusercontent.com/u/43718245?s=400&amp;u=84eeb52003e5c32628fcc9cb23edd54d8596cf54&amp;v=4" height="200" width="200">
</div>

---

## 개요

 [Punica Box](https://punica.ont.io/boxes/) 는 개발자가 온톨로지 블록체인에서 프로그래밍의 기본 사항을 빨리 습득할 수 있도록 다양한 언어, dApp예제 및 템플릿을 제공합니다.


특징：
* ONT ID, OEP-4, OEP-5, etc등과 같은 다양한 dApp예제 제공.
* 개발자가 자신의 박스를 만들고 커뮤니티 저장소에 추가할 수 있습니다.
* 더 많은 개발 라이브러리를 dApp개발을 위해 만들 수 있습니다.
<p><br>

## Punica-Box사용하기

Punica-Box를 사용하려면 먼저 [Punica Python CLI](https://github.com/punicasuite/punica-python) 또는 [Punica TypeScript CLI](https://github.com/punicasuite/punica-ts)를 설치해야합니다. 설치 및 구성 (see [documentation](http://dev-docs.ont.io/#/docs-en/Punica/punica-cli)) 을 시작하면 punica-box가 다운로드됩니다.

이 튜토리얼 계정간에 전송할 수 있는 OEP4 token을 만들어 [Tutorialtoken-box](https://github.com/punica-box/tutorialtoken-box) 를 사용할 것 입니다.

Punica 프로젝트를 위해 새로운 디렉토리를 만들어주세요.

```shell
mkdir tutorialtoken
cd tutorialtoken
```

Tutorialtoken-box Box 다운로드:

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

The Tutorialtoken-box프로젝트 아래에 있는 `punica-config.json'문서의 네트워크 기본 설정값은 테스트넷입니다.

Example punica-config.json:
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
- 프로젝트의 루트 디렉토리에서 punica-cli를 실행하지 않는 경우 `-p` 또는 `--project` 옵션을 사용하여 dApp프로젝트 경로를 지정해야합니다.
<p><br>


#### 컴파일

`compile` 명령을 사용하여 Tutorialtoken-box 스마트 컨트랙트를 컴파일합니다.

```shell
punica compile
```

모든 것이 원활하게 진행되면 `contracts/build` 폴더에서 `avm` 및 `abi`파일을 찾을 수 있습니다.

```shell
contacts
    ├─build
    │      contract.avm
    │      contract_abi.json
```

자세한 사용방법은, `punica compile --help`를 사용해주세요.

```shell
punica compile --help
Usage: punica compile [OPTIONS] CONTRACT_NAME

  Compile the specified contracts to avm and abi file.

Options:
  --contracts Only compile the specified contract
  -h, --help  Show this message and exit.
```
**스마트 컨트랙트를 컴파일 한 후 배치 비용을 지불할 때 계정에 ONG가 충분한지 확인하세요.(다음단계 참조) 그렇지 않으면 배치가 실패됩니다. Tutorialtoken-box의 주소는 ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6입니다.**

**참고**: 프로젝트의 루트 디렉토리에서 punica-cli를 실행하지 않은 경우 `-p` 또는 `--project` 옵션을 사용하여 dApp프로젝트 경로를 지정해야합니다.
<p><br>

#### 배치

Tutotialtoken-box 스마트 컨트랙트를 선택한 네트워크에 배치하려면 다음을 실행해야합니다.

```shell
punica deploy
```

간단한 배치 프로세스는 다음과 같습니다.

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

자세한 사용방법은 `punica deploy --help`를 사용해주세요.

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

- 프로젝트의 루트 디렉토리에서 punica-cli를 실행하지 않는 경우, `-p` 또는 `--project` 옵션을 사용하여 dApp프로젝트 경로를 지정해야합니다.
-`contracts/build` 디렉토리에 여러 `avm` 파일이 있는 경우 배치할 컨트랙트를 지정하려면 `--avm` 옵션을 사용해야합니다.
- 다중 월렛 파일이 `wallet` 디렉토리에 있는 경우, `--wallet` 옵션으로 어떤 월렛을 사용할지 지정해야합니다. 지정하지 않을 경우 `wallet` 디렉토리에서 임의로 지정됩니다.
<p><br

#### 호출

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

To see a list of available functions for tutorialtoken-box  use:
```shell
punica invoke list
```

Tutorialtoken-box에서 `punica invoke list'를 실행할 때의 응답
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

자세한 사용방법은 `punica invoke --help`를 사용해주세요.

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

- 프로젝트의 루트 디렉토리에서 punica-cli를 실행하지 않는 경우 `-p` 또는 `--project` 옵션을 사용하여 dApp프로젝트 경로를 지정해야합니다.
- 다중 월렛 파일이 `wallet` 디렉토리에 있는 경우, `--wallet` 옵션으로 어떤 월렛을 사용할지 지정해야합니다. 지정하지 않을 경우 `wallet` 디렉토리에서 임의로 지정됩니다.
<p><br>

#### Scpm (시행전)

스마트 컨트랙트 패키지 관리자를 사용하여 punica boxes를 다운로드 및 커뮤니티 저장소에 게시할 수 있습니다. 

```shell
punica scpm
Usage: punica scpm [OPTIONS]

   smart contract package manager，support download and publish.

Options:
   -h, --help  Show this message and exit.
```
<p><br>
