
## Overview

Currently, each mobile wallet App is an important entry point for DApp. We provide `cyano-bridge`. Once the dApp is installed, it can communicate with any wallet app that integrates `Provider-SDK` to implement chain operations by calling DAPI that is compatible with [CEP-1 standard](https://github.com/ontio-cyano/CEPs/blob/master/CEPS/CEP1.mediawiki) .

## Interaction Process of opening dApp in the wallet

### Login scenario
1. Open dApp in your wallet
2. The dApp sends a login request to the wallet, and the wallet returns the signed data.
3. dApp verification passed, login succeeded

### Call smart contract scenario
1. dApp initiates a request to call smart contract to the wallet (figure 4.1)
2. The wallet signs, pre-execute, sends the data to blockchain, and returns transaction hash to DApp (figure 4.2)

![](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/scenario3.png)


In addition, for DApp to work on both web and mobile versions, we provide examples that are compatible with both DAPIs:

* Mobile DAPI usage: [dapi for mobile](https://github.com/ontio-cyano/cyano-bridge)
* DAPI usage of Chrome plugin wallet [dapi for chrome](https://github.com/ontio/ontology-dapi)
* Code example for mobile and Chrome plugin DAPI: [dapi-universal](https://github.com/ontio-cyano/dapi-universal)

## Mobile DAPI Installation and Use

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

Currently you can get the latest version through `jsDelivr` and import the js file on the page to get started.

```html
<script src="https://cdn.jsdelivr.net/npm/cyanobridge/lib/browser.min.js"></script>
```

<p class = "info">It is recommended that users who introduce `cyano-bridge` on the CDN lock the version on the link address to avoid incompatibility updates for future `cyano-bridge` upgrade.</p> 

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

### Use

#### Get account or identity information

To obtain account or identity information, the mobile terminal can choose to fill in the optional DApp information.

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

To log in, a signed message is sent by the wallet and verified by the dApp.

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
const scriptHash = '8b344a43204e60750e7ccc8c1b708a67f88f2c43';
const operation = 'transferOng'
const args = [
   {
        "name": "arg0-id",
        "value": "String:hedgsg"
    }, {
        "name": "arg1-from",
        "value": "Address:AecaeSEBkt5GcBCxwz1F41TvdjX3dnKBkJ"
    }, {
        "name": "arg2-to",
        "value": "Address:AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ"
    }, {
        "name": "arg3-int",
        "value": 1
    }
]
const gasPrice = 500;
const gasLimit = 20000;
const payer = 'AecaeSEBkt5GcBCxwz1F41TvdjX3dnKBkJ'
const config = {
​    "login": true,
​    "message": "invoke smart contract test"
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

##### DApp Backend transaction event query
* [java sdk Transaction event query method](https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/basic.md)
* [ts sdk Transaction event query method](https://github.com/ontio/ontology-ts-sdk/blob/master/test/websocket.test.ts)

##### Wallet
* [cyano-android](https://github.com/ontio-cyano/cyano-android)
* [cyano-ios](https://github.com/ontio-cyano/cyano-ios)

##### dApi-mobile client sdk
* [cyano-bridge](https://github.com/ontio-cyano/cyano-bridge)

##### dApi-mobile provider sdk
* [cyano-android-sdk](https://github.com/ontio-cyano/cyano-android-sdk)
* [cyano-ios-sdk](https://github.com/ontio-cyano/cyano-ios-sdk)
