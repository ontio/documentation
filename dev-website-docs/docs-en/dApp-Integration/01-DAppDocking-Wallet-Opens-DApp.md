
## Overview

Currently, each mobile version of the Wallet App is an important entry point for DApp. We provide `cyano-bridge`. Once the DApp is installed, it can be called by calling [CEP-1](https://github.com/ontio-cyano /CEPs/blob/master/CEPS/CEP1.mediawiki) The standard DAPI communicates with any wallet app that integrates `Provider-SDK` to implement chain operations.

## Open DApp interaction process in the wallet

### Login scenario
1. Open DApp in your wallet
2. The DApp sends a login request to the wallet, and the wallet returns the signature data.
3. DApp verification passed, login succeeded

### Call smart contract scene
1. DApp initiates a smart contract request to the wallet (4.1 in the figure)
2. Wallet signature, pre-execution, send to chain, return transaction hash to DApp (4.2 in the figure)

![](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/scenario3.png)


In addition, in order to satisfy DApp for both web and mobile versions, we provide examples that are compatible with both DAPIs:

* Mobile DAPI usage: [dapi for mobile](https://github.com/ontio-cyano/cyano-bridge)
* DAPI usage of Chrome plugin wallet [dapi for chrome](https://github.com/ontio/ontology-dapi)
* Code example for mobile and Chrome plugin DAPI: [dapi-universal](https://github.com/ontio-cyano/dapi-universal)

## Mobile DAPI installation and use

### installation

You can choose one of the following installation methods:

- npm installation
- CDN


#### npm installation

Install using `npm`:

```shell
npm install cyanobridge
```

#### CDN

Currently you can get the latest version of the resource through `jsDelivr` and import the js file on the page to get started.

```html
<script src="https://cdn.jsdelivr.net/npm/cyanobridge/lib/browser.min.js"></script>
```

<p class = "info">It is recommended that users who introduce `cyano-bridge` on the CDN lock the version on the link address to avoid future incompatibility updates for the `cyano-bridge` upgrade.</p> 

### Import

#### CommonJS

```javascript
var client = require('cyanobridge').client
```

#### ES6 Module

```javascript
import { client } from 'cyanobridge'
```

#### Web require

Import the `browser.js` file in the `./lib` folder:

```html
<script src="./lib/browser.js"></script>

var client = CyanoMobile.client;
```

### initialization

Need to be initialized before use：

```javascript
import { client } from 'cyanobridge'

client.registerClient();
```

### use

#### Get account or identity information

To obtain account or identity information, the mobile terminal can choose to fill in DApp information or not.。

```
import { client } from 'cyanobridge'

const params = {
​    dappName: 'My dapp',
​    dappIcon: '' // some url points to the dapp icon
}

try {
​    const res = await client.api.asset.getAccount(params);
    const res = await client.api.identity.getIdentity(params);
​    console.log(res)
} catch(err) {
​    console.log(err)
}

```


#### Login

The login is signed by the wallet party and the DApp verifies the signature.

```
const params = {
​    type: 'account',// account or identity that will sign the message
​    dappName: 'My dapp', // dapp's name
​    dappIcon: 'http://mydapp.com/icon.png', // some url that points to the dapp's icon
​    message: 'test message', // message sent from dapp that will be signed by native client
​    expired: new Date('2019-01-01').getTime(), // expired date of login
​    callback: '' // callback url of dapp
}
let res;
try {
​    res = await client.api.message.login(params);
​    console.log(res)
}catch(err) {
​    console.log(err)
}
```

#### Invoke contract


```
const scriptHash = 'cd948340ffcf11d4f5494140c93885583110f3e9';
const operation = 'test'
const args = [
​    {
​        type: 'String',
​        value: 'helloworld'
​    }
]
const gasPrice = 500;
const gasLimit = 20000;
const payer = 'AecaeSEBkt5GcBCxwz1F41TvdjX3dnKBkJ'
const config = {
​    "login": true,
​    "message": "invoke smart contract test",
​    "qrcodeUrl": "" ,
    "callback": ""
}
const params = {
          scriptHash,
          operation,
          args,
          gasPrice,
          gasLimit,
          payer,
          config
        }
try {
   const res = await client.api.smartContract.invoke(params);
   } catch(err) {
​    console.log(err)
}

```

## Code reference

##### Signature verification method
* [java sdk Signature check](https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/interface.md#verify-signature)
* [ts sdk Signature check](https://github.com/ontio/ontology-ts-sdk/blob/master/test/ecdsa.crypto.test.ts)

##### DApp Backend query transaction event
* [java sdk Transaction event query method](https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/basic.md)
* [ts sdk Transaction event query method](https://github.com/ontio/ontology-ts-sdk/blob/master/test/websocket.test.ts)

##### wallet
* [cyano-android](https://github.com/ontio-cyano/cyano-android)
* [cyano-ios](https://github.com/ontio-cyano/cyano-ios)

##### dApi-mobile client sdk
* [cyano-bridge](https://github.com/ontio-cyano/cyano-bridge)

##### dApi-mobile provider sdk
* [cyano-android-sdk](https://github.com/ontio-cyano/cyano-android-sdk)
* [cyano-ios-sdk](https://github.com/ontio-cyano/cyano-ios-sdk)
