

This tutorial is designed to demonstrate an overview of creating dApps by using the Ontology dApp API (dAPI). It also contains the information on the tools required and as well as an example dApp.

The document is broken down into the following sections:

[Overview](#overview)

[Setting up the development environment](#setting-up-the-development-environment)

[Architecture](#Architecture)

[Ontology dAPI Overview](#ontology-dapi-overview)
+ [dAPI Installation](#dapi-installation)
+ [dAPI Instantiation](#dapi-instantiation)
+ [Example dAPI methods](#example-dapi-methods)
	+ [Example blockchain methods](#example-blockchain-methods)
	+ [Example asset methods](#example-asset-methods)
	+ [Example Smart Contract methods](#example-smart-contract-methods)
	+ [Example Message methods](#example-message-methods)

[Running the demo project](#running-the-demo-project)

[Writing a smart contract for your dApp](#writing-a-smart-contract-for-your-dapp)
+ [Compiling your smart contract](#compiling-your-smart-contract)
+ [Deploying your smart contract](#deploying-your-smart-contract)
+ [Testing your smart contract](#testing-your-smart-contract)


## Overview

It is necessary to have installed suitable **dAPI provider** . Reference implementation is [Cyano Wallet of Chrome](https://github.com/ontio/cyano-wallet)





## Setting up the Development Environment

Please ensure you have the following installed and configured in order to setup the development environment.

- [Node.js v6+ LTS with npm](https://nodejs.org/en/)

- [Cyano Wallet]( https://chrome.google.com/webstore/detail/ontology-web-wallet/dkdedlpgdmmkkfjabffeganieamfklkm)

- [Git](https://git-scm.com/)

### Architecture

![architecture](https://raw.githubusercontent.com/ontio-community/bounty-program-report/master/image/dapi.png)

## dAPI Usage
#### dAPI Installation
The Ontology dAPI is the core API used to interface with the Ontology blockhain when creating a dApp and the repository can be found [here](https://github.com/ontio/ontology-dapi). First you must install the npm package using: 

```
$ npm install @ont-dev/ontology-dapi
```

#### dAPI Instantiation

To use the dAPI in your project, you need to import the library and then register as a client.
Import and register the dAPI using:
```
import { client, provider } from '@ont-dev/ontology-dapi';

client.registerClient({
        extension: provider.ExtensionType.Cyano
  })
```

#### Example dAPI methods
Once imported and registered, use the provided dAPI methods in your dApp (see below).
##### Example blockchain methods
```
const network = await client.api.network.getNetwork();
const height = await client.api.network.getBlockHeight();
const block = await client.api.network.getBlock({ block: 1 });
const transaction = await client.api.network.getTransaction({txHash: '314e24e5bb0bd88852b2f13e673e5dcdfd53bdab909de8b9812644d6871bc05f'});
const balance = await client.api.network.getBalance({ address: 'AcyLq3tokVpkMBMLALVMWRdVJ83TTgBUwU' });
```
##### Example asset methods

```
const result = await client.api.asset.makeTransfer({ recipient, asset, amount });
```

##### Example Smart Contract Methods

```
const result = await client.api.smartContract.invoke({contract,method,parameters,gasPrice,gasLimit,requireIdentity});
const result = await client.api.smartContract.invokeRead({ contract, method, parameters });
const result = await client.api.smartContract.deploy({code,name,version,author,email,description,needStorage,gasPrice,gasLimit});
```
##### Example Message Methods

```
const message: string = values.message;
const signature: Signature = {
  data,
  publicKey
};
const result = await client.api.message.signMessage({ message });
const result = await client.api.message.verifyMessage({ message, signature });
```

A full list of methods can be found in the [dAPI Specification document](https://github.com/backslash47/OEPs/blob/oep-dapp-api/OEP-6/OEP-6.mediawiki). <p><br> 


### Running the Demo Project

Clone the [dAPI demo](https://github.com/ontio/ontology-dapi-demo) which we will use to demonstrate functionality.

```
$ git clone https://github.com/ontio/ontology-dapi-demo.git

$ npm install

$ npm run start
```

This will start the demo which can be accessed using the Google Chrome browser at http://localhost:3000

Accessing this, select Provider->GetProvider.

![dApp Demo Provider](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/dappdemofirstscreen.png)
![dApp Demo Get Provider](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/dappdemoregisterprovider.png)

This will allow us to communicate with the Ontology Blockchain and make API calls.  For example, selecting Network->Get Block results in the following:

![dApp Demo getBlock](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/dappdemonetworkblock.png)

You can also initiate a transfer by selecting Asset->Make Transfer where you'll be automatically prompted to approve the transaction by Cyano Wallet. Click Confirm to approve the transaction.

![Cyano Wallet Confirm](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/demo.png)

#### How to set gaslimit and gasprice

Each transaction contains a gas limit and a gas price. Gasprice will affect the time it takes for the transaction to be packaged. Currently, the minimum value of the main network and test network is 500.

The gaslimit is based on the complexity of the contract execution and can be queried by pre-execution.  The Native contract calls gaslimit by default is 20000. The deployment contract is based on the contract, and the gaslimit is generally more than 20000000.

### Writing a smart contract for your dApp


To support your dApp you will likely want to write a smart contract that acts as the back-end logic and storage. We use Ontology's [SmartX](http://smartx.ont.io/) tool for this. SmartX includes several template Smart Contracts to assist in development and further information can be found in the [Smart Contract Tutorial](https://github.com/ontio/documentation/tree/master/smart-contract-tutorial)


![SmartX Login](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/smartx.png)


#### Compiling and deploying your smart contract

SmartX uses Cyano Wallet to help with compiling, deploying and invoking the smart contract. Please make sure you have installed Cyano and created a Testnet account in it.

#### Compiling your smart contract

Use Smartx to compile the smart contract.

![smart contract deploy and invoke](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/smartx-deploy.png)

#### Deploying your Smart Contract

Now that we have written our smart contract, the next steps are to deploy and invoke it. Deploying and invoking requires Testnet ONG.  If you dont have any at the moment, please [request testnet ONG in Discord](https://discordapp.com/channels/400884201773334540/453499298097922068)

![Deploy](https://s1.ax1x.com/2018/09/03/PzhTCd.png)



![Invoke](https://s1.ax1x.com/2018/09/03/Pz5JO0.png) 

### Testing Smart Contract

In order to test the smart contract, you can use the [smart contract automated testing framework](https://github.com/ontio-community/ontology-sctf) or deploy your own Ontology privatenet running in testmode by downloading the latest [Ontology release](https://github.com/ontio/ontology/releases) and starting it as below.
```
$ ./ontology --testmode --gasprice 0

```
