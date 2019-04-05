


### Overview

Before using [dAPI for chrome](https://github.com/ontio/ontology-dapi), install a wallet that implements the **DAPI provider** feature, such as [Cyano Wallet of Chrome](https://github.com/OntologyCommunityDevelopers/cyano-wallet).

DAPI is implemented using TypeScript and is also supported for use in JavaScript projects.

### Installation development environment

Please make sure to install the following software：

- [Node.js v6+ LTS with npm](https://nodejs.org/en/)

- [Cyano Wallet]( https://chrome.google.com/webstore/detail/ontology-web-wallet/dkdedlpgdmmkkfjabffeganieamfklkm)

- [Git](https://git-scm.com/)


### ontology DAPI
#### DAPI Installation
When creating a DApp, Ontology DAPI is one of the core APIs for interacting with the Ontology Chain, which can be downloaded from [here](https://github.com/ontio/ontology-dapi). Install ontology-DAPI via ```npm```:

```
$ npm install ontology-dapi
```

#### DAPI instance

When creating a DAPI instance, first import the library ontology-dapi and register the client as follows:

```typescript
import { client } from 'ontology-dapi';

client.registerClient({});
```

#### DAPI Method
Once the DAPI instance is created, you can call the DAPI method in your DApp.

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

##### Interaction method with chain
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

Can be used to authenticate the user when logging in.
```
const message: string = values.message;
const signature: Signature = {
  data,
  publicKey
};
const result = await client.api.message.signMessage({ message });
const result = await client.api.message.verifyMessage({ message, signature });
```

A list of all methods can be found in the [DAPI Specification](https://github.com/backslash47/OEPs/blob/oep-dapp-api/OEP-6/OEP-6.mediawiki).


### Running example

Copy [dAPI example](https://github.com/OntologyCommunityDevelopers/ontology-dapi-demo) to test what features DAPI provides.

```
$ git clone https://github.com/OntologyCommunityDevelopers/ontology-dapi-demo.git

$ npm install

$ npm run start
```

After the startup is successful, open the page in the browser. http://localhost:3000

After the page opens successfully, click Provider->GetProvider。

![dApp Demo Provider](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/dappdemofirstscreen.png)
![dApp Demo Get Provider](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/dappdemoregisterprovider.png)

It interacts with the chain through API calls. For example, click Network->Get Block and the results are as follows:

![dApp Demo getBlock](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/dappdemonetworkblock.png)

Run the transfer example, click Asset->Make Transfer, Cyano Wallet will pop up a confirmation box. Click ```Confirm``` to confirm the transaction.

![Cyano Wallet Confirm](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/demo.png)

#### How to fill in gaslimit and gasprice

Each transaction contains a gas limit and a gas price.

Gasprice will affect the time it takes for the transaction to be packaged. Currently, the minimum value of the main network and test network is 500.

Gaslimit Depending on the complexity of the contract execution, the minimum gaslimit value required for the call can be queried by pre-execution. The Native contract call gaslimit defaults to 20000. The deployment contract is based on the contract, and the gaslimit is generally more than 20000000.

#### Address Processing

The Chrome plug-in wallet Cyano wallet accepts only ByteArray types when processing incoming addresses. When debugging with [SmartX] (https://smartx.ont.io/#/), SmartX will automatically recognize the recognized address. The type is converted to a ByteArray type, so the call will not be a problem, but in the developer's own environment, if there is no type conversion, Cyano wallet will report an error.

The following is an example of getting a ByteArray format address in js:

```javascript
import {Crypto} from 'ontology-ts-sdk';
var address = new Crypto.Address(account).serialize() // 此处得到的 address 就是 ByteArray 格式
```
