<div align="center">
  <img src="https://raw.githubusercontent.com/punicasuite/solo-chain/master/image/icon.png" height="200" width="200">
  <h2 class="doc-title">Solo Chain</h2>
</div>

## Solo Chain Overview
Solo Chain is a desktop application for developers to quickly setup and manage their own private instance of the Ontology blockchain for rapid development. With Solo Chain, there are no dependencies to install, source code to compile, or Docker image to setup. It is packaged with [Electron](http://electronjs.org) and provides users with an intuitive GUI interface to setup and manage all aspects of their private Ontology blockchain instance.

The Solo Chain application allows you to:
- Start, Stop, and Restart your private instance.
- Provides all of the available RPC, REST, and WebSocket server interfaces present with the Ontology MainNet and TestNet
- Facilitates account to account asset transfers and claims
- Extremely detailed block, transaction, and event monitoring for debugging
- List of deployed smart contracts
- Verbose network activity logging
- Customizable network configurations, such as the ability to adjust the gas price

## Installation

### Download Release
You can download the latest release of Solo Chain for Windows and Mac in the [release section](https://github.com/punicasuite/solo-chain/releases).

### Build from Source
If you would like to compile the application yourself from the source repo, you are free to do that as well.
- Clone the repo `git clone git@github.com:punicasuite/solo-chain.git`
- Install dependencies `yarn install`
- Compile application `yarn build`
- Navigate to the `release` folder and open the appropriate desktop installer (dmg or exe)

#### Run for Development
To run Solo Chain on your local machine for development of Solo Chain:
- Clone the repo `git clone git@github.com:punicasuite/solo-chain.git`
- Install dependencies `yarn install`
- Run application `yarn dev`

This will install and compile all required dependencies and source code, and spin up a local server to host the local codebase at `localhost:9080`. As you make changes to the codebase in the ./src folder, the application will update without reloading.

## Getting Started
Upon opening the application, you will be presented with the first look at your private Ontology network.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/00-home.png" ><br><br>
</div>

Along the top, you will find the menu bar - where you can navigate to the different tabs of the application, as well as view the network settings.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/01-menu-bar.png" ><br><br>
</div>

Just below the menu bar, on the left hand side, you will find a bunch of useful information. This includes the server addresses to communicate with your private network, the current block height, and the gas price and limit, which are used to calculate the ONG network fee per transaction.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/02-server-addresses.png" ><br><br>
</div>

To the right you can find controls to stop and reboot your network instance. Pressing `Stop` will pause your network, but your data will be retained for when you click `Start` again. `Reboot` will clear out all of your data and restart the blockchain instance from a block height of 0.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/03-stop-reboot.png" ><br><br>
</div>

In the main part of the `Accounts` screen, you will see a list of pre-made accounts. The first will contain all the ONT in existence for your private network.

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

If you would like to see the details of any block, including all transactions processed in that block, click the `Detail` button on the right hand side of the block. A block detail modal will pop up with an interactive JSON of the information for that block.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/10-block-detail.png" ><br><br>
</div>

If you click the squares, you can expand and close the objects and arrays in the JSON.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/11-block-detail-open.png" ><br><br>
</div>

In the `Transactions` tab you can see all of the processed transactions - including which block they were executed in and its details.

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

Lastly, clicking on the gear icon in the top-right of the screen will open the settings page. Here we can configure the gas price of ONG required for network fees for our private network.

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
Contributors are welcome to `Solo Chain`. Before beginning, please take a look at our [contributing guidelines](https://github.com/punicasuite/solo-chain/blob/documentation/CONTRIBUTING.md). You can open an issue by [clicking here](https://github.com/punicasuite/solo-chain/issues/new).

If you have any issues getting setup, open an issue or reach out in the [Ontology Discord](https://discordapp.com/invite/4TQujHj).
