<div align="center">
  <img src="https://raw.githubusercontent.com/punicasuite/solo-chain/master/image/icon.png" height="200" width="200"><br><br>
</div>

---

## Solo Chain Overview
A self contained one click private network for the Ontology blockchain. This desktop application makes it easy for developers to quickly setup and manage their own private instance of the Ontology blockchain for rapid development. There are no dependencies to install, source code to compile, or even Docker to setup. Solo chain is packaged with Electron, and provides users with an intuitive GUI interface to setup and mange all aspects of their private Ontology blockchain instance.

The Solo chain application allows you to:
- Start, Stop, and Restart your private instance on the fly.
- Provides all available RPC, REST, and Websocket server interfaces exactly as is present with the Ontology main net and test net
- Facilitates account to account asset transfers and claims, for quick test environment setup
- Extremely detailed block, transaction, and event monitoring for direct and convenient debugging
- Full listings for deployed smart contracts
- Verbose network activity logging
- Customizable network configurations

## Installation
- [Download the latest release](https://github.com/punicasuite/solo-chain/releases) version of the Solo chain application for your appropriate development environment (Windows, Mac)
- Install the application to your desktop computer
- IMPORTANT! Run the application "Run as administrator"

If you would like to compile the application yourself from the source repo, you are free to do that as well.
- Clone down the github repo `git clone git@github.com:punicasuite/solo-chain.git`
- Install dependencies `yarn install`
- Compile installer `yarn build`
- Navigate to the `release` folder and open the appropriate desktop installer (dmg or exe)



## Getting Started
Upon opening the application as "Run as administrator", you will be presented with the first look at your private Ontology network.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/00-home.png" ><br><br>
</div>

Along the top, you will find the menu bar, where you can navigate to the different tabs of the application along with viewing the network settings.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/01-menu-bar.png" ><br><br>
</div>

Just below the menu bar, on the left hand side you will find a bunch of useful information. Such as the server addresses to communicate with your private network, the current block height, and the gas price and limit which are used to calculate the ONG network fee per transaction.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/02-server-addresses.png" ><br><br>
</div>

To the right you can find controls to stop and reboot your network instance. Pressing `Stop` will pause your network, but your data will be retained for then you click `Start` again. `Reboot` will clear our all your data, and start the blockchain instance fresh.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/03-stop-reboot.png" ><br><br>
</div>

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/04-start.png" ><br><br>
</div>

In the main part of the `Accounts` screen, you will see a list of pre-made accounts. The first of which will contain all the ONT in existence for your private network.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/05-starting-account.png" ><br><br>
</div>

Upon clicking the `Transfer` button on that account, a modal will appear, where you can send ONT to the second account in the list. Just fill out the transfer details, and click `OK`.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/06-transfer.png" ><br><br>
</div>

Shortly after sending, you should see the balances in the accounts update. Only after sending will you be able to claim ONG. So on the first account, click `Redeem ONG`, and you should shortly receive the ONG for that account.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/07-claim.png" ><br><br>
</div>

On the right side of the account line item, you will see a key icon. Upon clicking this, you will see a modal with the private key for this account. You will need these later when starting to build your applications, as they will serve as your credentials for sending transaction to the network.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/08-pk.png" ><br><br>
</div>

Moving onto the next tab, if you click on the `Blocks` item in the menu bar at the top, you will be presented with the blocks information screen.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/09-blocks.png" ><br><br>
</div>

If you would like to see the details of any block, including all transactions processed in that block, click the `Detail` button on the right hand side of the block you want to see. A block detail modal will pop up with a interactive JSON of the information about that block.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/10-block-detail.png" ><br><br>
</div>

If you click the squares, you can expand and contract the objects and arrays in the JSON.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/11-block-detail-open.png" ><br><br>
</div>

In the `Transactions` tab, you can see all of the processed transactions, including what block they were executed in, and it's details.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/12-transactions.png" ><br><br>
</div>

Clicking on the `Detail` button on the right hand side will bring up a modal with all the details for that transaction in an interactive JSON format. Here you can see everything from who signed the transaction, to who paid the network fee, and much more.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/13-tx-details.png" ><br><br>
</div>

In the `Events` tab, you can view a list of all the notification events emitted as a result of transactions being processed.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/14-events.png" ><br><br>
</div>

For example, drilling into the details of the following event, we can see it was emitted from the `transfer` operation that we executed when claiming our ONG. This can be an extremely useful tool when debugging your smart contracts, as you can create these custom notification events to be broadcast yourself.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/15-transfer-event.png" ><br><br>
</div>

In the `Smart Contracts` tab, you can find a full listing of all contracts that have been deployed to your network. This will be useful for managing your new development contract hash addresses as new versions are deployed.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/16-smart-contracts.png" ><br><br>
</div>

In the `Logs` tab, you can view the full and complete transcript of everything that is happening within your private network behind the scenes.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/17-logs.png" ><br><br>
</div>

Lastly, clicking on the gear icon in the top right of the screen will bring up the settings screen. Here we can configure the gas price of ONG required for network fees for our private network.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/18-settings.png" ><br><br>
</div>

## Usage
Once you have your Solo Chain instance up and running, you will want to connect with it from one of the various development SDKs.

- [RPC](#rpc)
- [Restful API](#restful-api)
- [WebSockets](#websockets)

- [Cyano Wallet](#cyano-wallet)

### RPC
In order to broadcast transactions to your private network via RPC, simply set the RPC address to reference the value found in your Solo Chain app.

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
In order to broadcast transactions to your private network via Restful API, simply set the API address to reference the value found in your Solo Chain app.

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
In order to broadcast transactions to your private network via WebSockets, simply set the socket address to reference the value found in your Solo Chain app.

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
