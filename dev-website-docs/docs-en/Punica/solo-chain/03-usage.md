
# Usage
Once you have your Solo Chain instance up and running, you will want to connect with it from one of the various development SDKs.

- [RPC](#rpc)
- [Restful API](#restful-api)
- [WebSockets](#websockets)

- [Cyano Wallet](#cyano-wallet)

## RPC
In order to broadcast transactions to your private network via RPC, simply set the RPC address to reference the value found in your Solo Chain app.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/rpc-server.png" ><br><br>
</div>

### Python SDK

```
from ontology.ont_sdk import OntologySdk

rpc_address = 'http://127.0.0.1:20336'
sdk = OntologySdk()
sdk.rpc.set_address(rpc_address)
```

### Go SDK

```
import ontology_go_sdk

ontSdk = NewOntologySdk()
ontSdk.NewRpcClient().SetAddress("http://127.0.0.1:20336")
```

### Typescript SDK

```
import { RestClient } from 'ontology-ts-sdk';

const rpcClient = new RpcClient('http://127.0.0.1:20336');
const res = await rpcClient.sendRawTransaction(tx.serialize(), true);
```

### Java SDK

```
import com.github.ontio.OntSdk;

OntSdk ontSdk = OntSdk.getInstance();
ontSdk.setRpc('http://127.0.0.1:20336');
ontSdk.setDefaultConnect(ontSdk.getRpc());
```

## Restful API
In order to broadcast transactions to your private network via Restful API, simply set the API address to reference the value found in your Solo Chain app.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/rest-server.png" ><br><br>
</div>

### Typescript SDK

```
import { RestClient } from 'ontology-ts-sdk';

const restClient = new RestClient('http://127.0.0.1:20334');
const res = await restClient.sendRawTransaction(tx.serialize());
```

### Java SDK

```
import com.github.ontio.OntSdk;

OntSdk ontSdk = OntSdk.getInstance();
ontSdk.setRestful('http://127.0.0.1:20334');
ontSdk.setDefaultConnect(ontSdk.getRestful());
```

## Websockets
In order to broadcast transactions to your private network via WebSockets, simply set the socket address to reference the value found in your Solo Chain app.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/websockets.png" ><br><br>
</div>

### Typescript SDK

```
import { WebsocketClient } from 'ontology-ts-sdk';

const socketClient = new WebsocketClient('http://127.0.0.1:20335', true, false);
const result = await client.sendRawTransaction(tx.serialize(), false, true);
```

### Java SDK

```
import com.github.ontio.OntSdk;

OntSdk ontSdk = OntSdk.getInstance();
ontSdk.setWesocket('http://127.0.0.1:20335', lock);
ontSdk.setDefaultConnect(ontSdk.getWebSocket());
```

## Cyano Wallet
To point your Cyano Wallet at your private network, navigate to the setting screen by clicking the gear icon on the top right of the home screen.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/cyano-home.png" ><br><br>
</div>

Once on the settings screen, select `PRIVATE-NET` from the `Net` dropdown, and set the `private node api/address` to `127.0.0.1` if not already set.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/cyano-settings.png" ><br><br>
</div>
