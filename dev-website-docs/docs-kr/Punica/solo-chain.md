<div align="center">
  <img src="https://raw.githubusercontent.com/punicasuite/solo-chain/master/image/icon.png" height="200" width="200"><br><br>
</div>

---

## Solo Chain 개요
온톨로지의 프라이빗넷 블록체인. 이 데이스탑 애플리케이션을 사용하면 개발자가 쉽고 빠르게 개발을 할 수 있습니다. 설치에 의존할 필요 없이 직접 컴파일을 할 수 있습니다. Docker을 기반으로 설치할 수 있습니다. Solo chain을 Electron과 함께 제공되면 사용자가 브라이빗 온톨로지 블록체인 인스턴스의 모든 측면을 설정 및 관리할 수 있는 직관적인 GUI인터페이스를 사용자에게 제공됩니다.

Solo chain애플리케이션을 사용하면 다음을 수행할 수 있습니다.
- 실행중에 개인 인스턴스를 시작, 중지 및 다시시작
- Ontology 메인넷 및 테스트 넷에 있는 사용 가능한 모든 RPC, REST 및 Websocket 서버 인터페이스 제공
- 신속한 테스트 환경 설정을 위해 자산거래 및 클레임을 계정화할 수 있습니다
- 직접적이고 편리한 디버깅을 위한 디테일한 블록, 트랜잭션 및 이벤트 모니터링
- 배포 된 스마트 컨트랙트 전체 목록
- 자세한 네트워크 활동 로깅
- 사용자 정의가 가능한 네트워크 구성

## 설치
- 모든 플랫폼(Windows, Mac)의 Solo chain 애플리케이션 [최신 버전을 다운로드하세요](https://github.com/punicasuite/solo-chain/releases).
- 애플리케이션을 데스크탑에 설치하세요
- 중요! 애플리케이션을 실행할 시 "관리자 권한으로 실행"해주세요.

소스 저장소에서 사용자의 애플리케이션을 컴파일 시키려면, 이렇게 수행할 수 있습니다.
- github Clone 클론 저장소 `git clone git@github.com:punicasuite/solo-chain.git`
- 의존성 다운로드 s `yarn install`
- 컴파일 다운로드 `yarn build`
- `release` 폴더로 옮긴 뒤 해당하는 데스크탑 애플리케이션(dmg 혹은 exe)을 열어주세요.



## 시작하기
"관리자 권한으로 실행"하면, 아래와 같이 보입니다. 온톨로지 브라이빗넷이 보입니다.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/00-home.png" ><br><br>
</div>

맨 위에는 메뉴바가 나타나 있으며 애플리케이션의 여러 탭으로 이동하여 네트워크 설정을 확인 할 수 있습니다.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/01-menu-bar.png" ><br><br>
</div>

메뉴 바로 아래 좌측 상단에 여러 정보들을 확인해볼 수 있습니다. 브라이빗 네트워크와 통신하는 서버 주소, 현재 블록높이, 매 트랙잭션시 생기는 ONG네트워크 요금을 계산하는데 사용되는 가스 가격 및 한도.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/02-server-addresses.png" ><br><br>
</div>

우측 상단에 네트워크 인스턴스 중지 및 재부팅 할 수 있는 컨트롤을 찾을 수 있습니다. 중지 버튼을 클릭하면 일시중지 되지만 다시시작을 클릭하면 데이터는 유지된 상태로 시작됩니다. 재부팅을 클릭하면 모든 데이터가 지워지고 새로운 블록체인 인스턴스가 시작됩니다.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/03-stop-reboot.png" ><br><br>
</div>

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/04-start.png" ><br><br>
</div>

화면의 주요 부분에는 미리 만들어진 계정 목록이 표시됩니다. 첫 번째는 프라이빗넷을 위해 존재하는 모든 ONT를 포함하고 있습니다.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/05-starting-account.png" ><br><br>
</div>

해당 계정의 `Transfer`을 클릭하면 두 번째 계정으로 ONT를 보낼 수 있는 페이지가 형성됩니다. 송금 정보를 입력하고 `OK`를 눌러주세요.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/06-transfer.png" ><br><br>
</div>

전송 후 잔액 내역이 업데이트된 것을 확인해 볼 수 있습니다. 전송 후에만 ONG를 클레임할 수 있습니다. 첫 거래 후 `Redeem ONG`를 눌러주세요.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/07-claim.png" ><br><br>
</div>

계정 항목의 오른쪽에 키 아이콘을  본 계정의 프라이빗 키가 보이는 페이지가 표시됩니다. 차후 애플리케이션을 만들떄 필요한 정보이자 트랜젝션이 네트워크로 전송되는데 꼭 필요한 증명으로 사용되기도 합니다.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/08-pk.png" ><br><br>
</div>

다음 탭으로 이동한 후 메뉴바에 있는 `Blocks` 항목을 클릭하면 블록과 관련된 정보들이 보이는 모든 화면이 나타납니다.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/09-blocks.png" ><br><br>
</div>

해당 블록에서 처리된 모든 거래 및 블록의 세부 사항을 확인해보고 싶으시다면 메뉴바에 있는 `Detail`을 클릭해주세요. 블록과 관련된 모든 정보가 대화형 JSON으로 팝업됩니다.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/10-block-detail.png" ><br><br>
</div>

사각형 모양을 클릭하면 JSON에서 객체와 배열을 확장 및 축소할 수 있습니다.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/11-block-detail-open.png" ><br><br>
</div>

메뉴바의 `Transactions`에서 처리된 모든 거래와 실행된 블록을 포함한 모든 내역을 확인할 수 있습니다.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/12-transactions.png" ><br><br>
</div>

우측에 위치한 `Detail` 을 클릭하면 대화형 JSON형식으로 트랜잭션의 모든 세부정보가 표시되면 서명한 사람, 네트워크 수수료지불한 사람 등 모든 것을 확인할 수 있습니다.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/13-tx-details.png" ><br><br>
</div>

`Events` 에서는 처리중인 거래의 결과로 생성된 모든 알림 이벤트의 목록을 확인할 수 있습니다.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/14-events.png" ><br><br>
</div>

예를 들어, 다음 이벤트의 디테일을  확인해봅시다. 우리의 ONG를 소유를 주장할 때 실행한 전송 작업에서 발생했음을 알 수 있습니다. 스마트 컨트랙트를 디버깅할 때 아주 유용하게 사용되는 툴으로 이러한 식으로 사용자가 직접 지정하여 이벤트 알림을 만들어 브로드 캐스트할 수 있습니다.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/15-transfer-event.png" ><br><br>
</div>

`Smart Contracts`에서는 네트워크에 배치된 모든 컨트랙트의 목록을 확인해 볼 수 있습니다. 또한 새 버전이 배포되면 새로운 개발 계약 해시 주소를 관리하는데 유용합니다. 

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/16-smart-contracts.png" ><br><br>
</div>

`Logs`에서는 프라이빗 네트워크에서 발생한 모든 전체 내용을 확인할 수 있습니다.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/17-logs.png" ><br><br>
</div>

마지막으로 우측 상단에 있는 톱니바퀴 모양의 아이콘을 클릭하면 설정화면으로 넘어갑니다. 여기에서는 프라이빗넷에서 필요한 ONG가스 가격을 구성할 수 있습니다.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/18-settings.png" ><br><br>
</div>

## Usage
Once you have your Solo Chain 인스턴스를 실행하면 다양한 개발 SDK중에서 하나의 인스턴스로 연결하려고 합니다.

- [RPC](#rpc)
- [Restful API](#restful-api)
- [WebSockets](#websockets)

- [Cyano Wallet](#cyano-wallet)

### RPC
RPC를 통한 프라이빗넷 트랜잭션을 브로드 캐스트하기 위해서는 Solo Chain app에 있는 값을 참조하도록 RPC주소를 설정하면 됩니다.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/rpc-server.png" ><br><br>
</div>

#### Python SDK

```
from ontology.ont_sdk import OntologySdk

rpc_address = 'http://127.0.0.1:20336'
sdk = OntologySdk()
sdk.rpc.set_address(rpc_address)
```

#### Go SDK

```
import ontology_go_sdk

ontSdk = NewOntologySdk()
ontSdk.NewRpcClient().SetAddress("http://127.0.0.1:20336")
```

#### Typescript SDK

```
import { RestClient } from 'ontology-ts-sdk';

const rpcClient = new RpcClient('http://127.0.0.1:20336');
const res = await rpcClient.sendRawTransaction(tx.serialize(), true);
```

#### Java SDK

```
import com.github.ontio.OntSdk;

OntSdk ontSdk = OntSdk.getInstance();
ontSdk.setRpc('http://127.0.0.1:20336');
ontSdk.setDefaultConnect(ontSdk.getRpc());
```

### Restful API
Restful API를 통한 프라이빗넷 트랜잭션을 브로드 캐스트하기 위해서는 Solo Chain app에 있는 값을 참조하도록 API주소를 설정하면 됩니다.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/rest-server.png" ><br><br>
</div>

#### Typescript SDK

```
import { RestClient } from 'ontology-ts-sdk';

const restClient = new RestClient('http://127.0.0.1:20334');
const res = await restClient.sendRawTransaction(tx.serialize());
```

#### Java SDK

```
import com.github.ontio.OntSdk;

OntSdk ontSdk = OntSdk.getInstance();
ontSdk.setRestful('http://127.0.0.1:20334');
ontSdk.setDefaultConnect(ontSdk.getRestful());
```

### Websockets
WebSockets을 통한 프라이빗넷 트랜잭션을 브로드 캐스트하기 위해서는 Solo Chain app에 있는 값을 참조하도록 socket주소를 설정하면 됩니다.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/websockets.png" ><br><br>
</div>

#### Typescript SDK

```
import { WebsocketClient } from 'ontology-ts-sdk';

const socketClient = new WebsocketClient('http://127.0.0.1:20335', true, false);
const result = await client.sendRawTransaction(tx.serialize(), false, true);
```

#### Java SDK

```
import com.github.ontio.OntSdk;

OntSdk ontSdk = OntSdk.getInstance();
ontSdk.setWesocket('http://127.0.0.1:20335', lock);
ontSdk.setDefaultConnect(ontSdk.getWebSocket());
```

### Cyano Wallet
To point your Cyano Wallet at your private network, navigate to the setting screen by clicking the gear icon on the top right of the home screen.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/cyano-home.png" ><br><br>
</div>

Once on the settings screen, select `PRIVATE-NET` from the `Net` dropdown, and set the `private node api/address` to `127.0.0.1` if not already set.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/cyano-settings.png" ><br><br>
</div>



## Contributing
If you happen to find any issues, or have any cool ideas for the next amazing feature for Solo chain, please head over to the [Github](https://github.com/punicasuite/solo-chain) repo, and help us make Solo chain even better.

### Development Setup
To get Solo chain up and running on your local machine for development on Solo chain, you can:
- Clone down the github repo `git clone git@github.com:punicasuite/solo-chain.git`
- Install dependencies `yarn install`
- Compile installer `yarn dev`

This will install and compile all required dependencies and source code, and spin up a local server to host the local codebase at `localhost:9080`. As you make changes to the codebase in the `./src` folder, the application will update with hot reloading.

If you have any issues getting setup, please reach out in the Github issues, or directly on Discord.

### Contribution Guidelines

Please open a pull request with signed-off commits. We appreciate your help! You can also send your codes as emails to the developer mailing list. You're welcomed to join the Ontology mailing list or developer forum.

Please provide detailed submission information when you want to contribute code for this project. The format is as follows:

Header line: explain the commit in one line (use the imperative).

Body of commit message is a few lines of text, explaining things in more detail, possibly giving some background about the issue being fixed, etc.

The body of the commit message can be several paragraphs, and please do proper word-wrap and keep columns shorter than about 74 characters or so. That way "git log" will show things nicely even when it's indented.

Make sure you explain your solution and why you're doing what you're doing, as opposed to describing what you're doing. Reviewers and your future self can read the patch, but might not understand why a particular solution was implemented.

Reported-by: whoever-reported-it Signed-off-by: Your Name youremail@yourhost.com
