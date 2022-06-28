


### Overview

Before using [dAPI for chrome](https://github.com/ontio/ontology-dapi), please install a wallet that has the **DAPI provider** feature, such as [Cyano Wallet of Chrome](https://github.com/ontio/cyano-wallet).

DAPI is implemented using TypeScript and can also be used for JavaScript projects.

### Installation development environment

Please make sure the following softwares are installed：

- [Node.js v6+ LTS with npm](https://nodejs.org/en/)

- [Cyano Wallet]( https://chrome.google.com/webstore/detail/ontology-web-wallet/dkdedlpgdmmkkfjabffeganieamfklkm)

- [Git](https://git-scm.com/)


### Ontology DAPI
#### DAPI Installation
When creating a dApp, Ontology DAPI is one of the core APIs for interacting with the Ontology blockchain, and the source code can be downloaded [here](https://github.com/ontio/ontology-dapi). Install Ontology-DAPI via ```npm```:

```
$ npm install @ont-dev/ontology-dapi
```

#### DAPI example

When creating a DAPI example, first import ontology-dapi and register as follows:

```typescript
import { client, provider } from '@ont-dev/ontology-dapi';

client.registerClient({
        extension: provider.ExtensionType.Cyano
  })
```

#### DAPI method
Once the DAPI example is created, you can call the DAPI method in your dApp.

##### Get account or identity information

```
account = await client.api.asset.getAccount()
res = await client.api.identity.getIdentity();
```


##### Smart contract method
```typescript
const result = await client.api.smartContract.invoke({contract,method,parameters,gasPrice,gasLimit,requireIdentity});
const result = await client.api.smartContract.invokeRead({ contract, method, parameters });
const result = await client.api.smartContract.deploy({code,name,version,author,email,description,needStorage,gasPrice,gasLimit});
```

##### Interaction method with blockchain
```typescript
const network = await client.api.network.getNetwork();
const height = await client.api.network.getBlockHeight();
const block = await client.api.network.getBlock({ block: 1 });
const transaction = await client.api.network.getTransaction({txHash: '314e24e5bb0bd88852b2f13e673e5dcdfd53bdab909de8b9812644d6871bc05f'});
const balance = await client.api.network.getBalance({ address: 'AcyLq3tokVpkMBMLALVMWRdVJ83TTgBUwU' });
```
##### Transfer method
```
const result = await client.api.asset.makeTransfer({ recipient, asset, amount });
```

##### Data signature

Can be used to verify user identity when logging in.
```
const message: string = values.message;
const signature: Signature = {
  data,
  publicKey
};
const result = await client.api.message.signMessage({ message });
const result = await client.api.message.verifyMessage({ message, signature });
```

A list of all the methods can be found in the [DAPI Specification](https://github.com/backslash47/OEPs/blob/oep-dapp-api/OEP-6/OEP-6.mediawiki).


### Running example

Copy [dAPI example](https://github.com/ontio/ontology-dapi-demo) and test what features DAPI provides.

```
$ git clone https://github.com/ontio/ontology-dapi-demo.git

$ npm install

$ npm run start
```

After , open the page http://localhost:3000 in the browser. 

Once the page is opened, click Provider->GetProvider。

![dApp Demo Provider](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/dappdemofirstscreen.png)
![dApp Demo Get Provider](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/dappdemoregisterprovider.png)

It interacts with the chain by calling API. For example, click Network->Get Block and the results are as follows:

![dApp Demo getBlock](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/dappdemonetworkblock.png)

Run the transfer example, click Asset->Make Transfer, Cyano Wallet will pop up a confirmation box. Click ```Confirm``` to confirm the transaction.

![Cyano Wallet Confirm](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/demo.png)

#### How to fill in gaslimit and gasprice

Each transaction contains a gas limit and a gas price.

Gasprice will affect the time it takes for the transaction to be packaged. Currently, the minimum value of both the mainnet and test network is 500.

Gaslimit depends on the complexity of the contract execution, the minimum gaslimit value required for the call can be queried by pre-execution. The default Native contract call gaslimit is 20000. The deployment contract is based on the contract, and the gaslimit is generally more than 20000000.

#### Address Processing

The Chrome plug-in wallet Cyano Wallet accepts only ByteArray type when processing incoming addresses. When debugging with [SmartX](https://smartx.ont.io/#/), SmartX will automatically convert the recognized address types to ByteArray type, so the call will not be a problem, but in the developer's own environment, if there is no type conversion, then Cyano wallet will report an error.

The following is an example of getting an address in ByteArray format in js:

```javascript
import {Crypto} from 'ontology-ts-sdk';
var address = new Crypto.Address(account).serialize() // The address obtained here is the ByteArray format.
```
