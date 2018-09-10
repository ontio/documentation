English / [中文](./ontology_dapp_dev_tutorial_zh.html)

<h1 align="center">Ontology dApp development tutorial</h1>
<p align="center" class="version">Version 1.0.0 </p>

This tutorial will guide you through the process of building your first dApp and is meant for those with a basic knowledge of the Ontology ecosystem, smart contracts and HTML/JavaScript, but who are new to building dApps.<p>

In this tutorial we will be covering:

[Setting up the development environment](#setup-dev)

[Creating a project](#create-proj)

[Writing the smart contract](#write-SC)

[Compiling and deploying/invoking the smart contract](#deploy-SC)

[Testing the smart contract](#test-SC)

[Interacting with the dapp in a browser](#interact-dapp) <p>



### Setting up the development environment

There are a few technical requirements before we start. Please ensure you have the following installed and configured for use in your development environment.

* [Node.js v6+ LTS and npm](https://nodejs.org/en/)

* [Git](https://git-scm.com/)<p>


### Creating a project

#### dAPI Installation
Next, download the Ontology dAPI SDK [here](https://github.com/ontio/ontology-dapi) and install using:

```
npm install ontology-dapi
```

#### dAPI Import and registration

Import and register the dAPI using:
```
import { client } from 'ontology-dapi';

client.registerClient({});
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
const result = await client.api.asset.makeTransfer({ recipient, asset, amount });
```

##### Example Smart Contract methods
```
const result = await client.api.smartContract.invoke({contract,method,parameters,gasPrice,gasLimit,requireIdentity});
const result = await client.api.smartContract.invokeRead({ contract, method, parameters });
const result = await client.api.smartContract.deploy({code,name,version,author,email,description,needStorage,gasPrice,gasLimit});
```

A full list of methods can be found in the [OEP-6 document](https://github.com/backslash47/OEPs/blob/oep-dapp-api/OEP-6/OEP-6.mediawiki) and an example is located in the [dAPI demo](https://github.com/OntologyCommunityDevelopers/ontology-dapi-demo)
<p><br>



### Writing a smart contract for your dApp


To support our dApp we will write a smart contract that acts as the back-end logic and storage. We use Ontology's [SmartX](http://smartx.ont.io/) tool for this. 


![SmartX Login](../docs/lib/images/smartx.png)


#### Compiling and deploying/invoking the smart contract

SmartX uses [Cyano Wallet]( https://chrome.google.com/webstore/detail/ontology-web-wallet/dkdedlpgdmmkkfjabffeganieamfklkm) to help with compiling, deploying and invoking the smart contract. Please make sure you have installed Cyano and created an account in it.

#### Compiling the smart contract

Use Smartx to Compiling smart contract.

![smart contract deploy and invoke](../docs/lib/images/smartx-deploy.png)

#### Deploy/invoke smart contract

Now that we have written our smart contract, the next steps are to deploy and invoke it. Deploying and Invoking requires Testnet ONG.  If you dont have any already, please [request testnet ONG in Discord](https://discordapp.com/channels/400884201773334540/453499298097922068)



![Deploy](https://s1.ax1x.com/2018/09/03/PzhTCd.png)

<p>

![Invoke](https://s1.ax1x.com/2018/09/03/Pz5JO0.png) <p>

### Testing the smart contract

In order to test the smart contract, you can use the [smart contract automated testing framework](https://github.com/lucas7788/pythontest) or deploy your own Ontology privatenet running in testmode by downloading the latest [Ontology release](https://github.com/ontio/ontology/releases) and starting it as below.
```
./ontology --testmode --gasprice 0

```


### Interacting with the dApp in a browser

Now we're ready to use our dapp!

### Installing and configuring Cyano Wallet


![Cyano Wallet](../docs/lib/images/cyano-wallet.png)

The easiest way to interact with our dapp in a browser is through Cyano Wallet, a browser extension for Chrome.[Cyano Wallet](https://github.com/OntologyCommunityDevelopers/cyano-wallet)


## 7. Using the dapp


### 7.1 Start the local web server of demo:

```
npm run start

```

The dev server will launch and automatically open a new browser tab containing your dapp.


### 7.2 transfer or invoke smartcontract

To use the dapp, click the ```make``` button.

### 7.3 approve the transaction on Cyano Wallet

You'll be automatically prompted to approve the transaction by Cyano Wallet. Click Confirm to approve the transaction.

![Cyano Wallet Confirm](../docs/lib/images/demo.png)

### 7.4 check transaction

In Cyano Wallet, you'll see the transaction listed:
