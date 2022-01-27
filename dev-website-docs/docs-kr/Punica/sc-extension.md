

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-community/bounty-program-report/master/image/sc-vscode-exten.png" height="200" width="200">
</div>

---

## 개요

Visual Studio Code는 소스코드 편집기의 단순성과 IntelliSense code 완성 및 디버깅과 같은 개발자 도구를 결합한 것 입니다.

먼저 [VSCode](https://code.visualstudio.com/)를 다운로드 하였는지 확인해주세요. 이 확장 기능은 온톨로지 블록체인에 대한 스마트 컨트랙트 개발 및 테스트를 지원합니다. **VSCode를 추천할 때 `pylint`를 비활성화시키세요.**

<div align="center">
<img src="https://raw.githubusercontent.com/ontio-community/bounty-program-report/master/image/vscode.png" >
</div>  

**특징:**
1. 컴파일: VSCode는 Python 스마트 컨트랙트(.py) 및 CSharp 스마트 컨트랙트(.cs)를 지원합니다.
2. 배치: 스마트 컨트랙트를 MainNet / TestNet/ PrivateNet에 배치합니다.
3. 호출: 스마트 컨트랙트를 실행하거나 사전실행합니다.
4. 디버그: 디버그 절차(StepIn, StepOut, Next, Continue, Stop, Restart), breakpoints 설정, 변수 미리보기, 설정 및 상태 저장소 조작을 지원합니다.

## 시작하기


### 1. 확장 기능 설정

이 확장 프로그램은 다음과 같은 설정을 제공합니다.

- `ontology.network.type`: 배치 및 호출에서 사용할 네트워크를 지원합니다.
- `ontology.network.private`: PrivateNet 주소는 http://host:port 형식에 있습니다.
- `ontology.wallet`: 배치 및 호출중에 사용되는 월렛 파일 (경로에서 \${workspaceFolder} 사용가능)
- `ontology.payer`: 기본 지불자 주소 (월렛 파일에서 찾기)
- `ontology.deploy.gasLimit`: 배치하는 동안 사용되는 가스 한도
- `ontology.deploy.gasPrice`: 배치하는 동안 사용되는 가스 가격
- `ontology.invoke.gasLimit`: 호출하는 동안 사용되는 가스 한도
- `ontology.invoke.gasPrice`: 호출하는 동안 사용되는 가스 가격

이러한 설정은 왼쪽 하단의 기어 박스 아이콘을 클릭하여 표준 VSCode 설정에서 변경할 수 있습니다.

![Settings 1](https://raw.githubusercontent.com/ontio/vscode-ext-ontology/master/img/settings1.png)
![Settings 2](https://raw.githubusercontent.com/ontio/vscode-ext-ontology/master/img/settings2.png)


### 2. Ontology extension 사용가이드

확장기능 마켓으로 이동한 후,  **VSCode Extension for Ontology extension**를 설치합니다. .py 혹은 .cs 파일을 VS Code에서 열어줍니다. 확장기능이 활성화 되었고, 이 확장이 전체 스마트 컨트랙트 개발 프로세스를 향상시킵니다.

#### 2.1 컴파일

스마트 컨트랙트를 컴파일하려면 .py 또는 .cs file을 컨트랙트 메뉴에서 표시하세요.

![Compile](https://raw.githubusercontent.com/ontio/vscode-ext-ontology/master/img/compile.png)

`Compile smart contract`를 누릅니다. 편집 결과에 대한 알림은 알림으로 표시됩니다. 컴파일은 .avm file의 컴파일 된 코드와 _abi.json file의 스마트 컨트랙트 설명 파일을 빌드 폴더에 생성합니다.

#### 2.2 배치

스마트 컨트랙트를 배치하려면 컴파일 된 .avm file에 컨트랙트 메뉴를 표시합니다.

![Deploy 1](https://raw.githubusercontent.com/ontio/vscode-ext-ontology/master/img/deploy1.png)

`Deploy smart contract`를 클릭하세요. 설명 양식이 있는 새 패널이 표시됩니다. 필요한 정보를 입력하고 배치를 누릅니다. 편집 결과에 대한 알림은 알림으로 표시됩니다.

#### 2.3 호출 및 디버그

스마트 컨트랙트에서 메소드를 호출하려면 \_abi.json file을 엽니다. 스마트 컨트랙트 방식의 새 패널이 표시됩니다.

![Invoke 1](https://raw.githubusercontent.com/ontio/vscode-ext-ontology/master/img/invoke1.png)

호출 양식을 표시하기 위해 메소드 중 하나를 더블클릭해주세요. 파라미터를 채우고 호출 버튼을 클릭해주세요.

![Invoke 2](https://raw.githubusercontent.com/ontio/vscode-ext-ontology/master/img/invoke2b.png)
![Invoke 3](https://raw.githubusercontent.com/ontio/vscode-ext-ontology/master/img/invoke3b.png)

호출 진행에 대한 알림을 받은 후 호출 결과는 새 패널에 표시됩니다.

![Invoke 4](https://raw.githubusercontent.com/ontio/vscode-ext-ontology/master/img/invoke4.png)

호출 대신 스마트 컨트랙트를 디버그를 진행하려면 디버그 버튼을 누릅니다. StepIn, StepOut, Next, Continue, Restart, Stop 및 breakpoints 와 같은 VScode의 표준 디버그 기능을 파라미터 미리보기 및 설정과 함께 사용할 수 있습니다.



### 3. Extension author

- **Matus Zamborsky** - _Initial work_ - [Backslash47](https://github.com/backslash47)





