


This tutorial will guide you through the process of creating a smart contract, deploying it to your private-net, testing and finally deploying it to the Ontology Mainnet. 

The steps used will be:

1. Create/edit smartcontract in SmartX (**do not deploy at this step**)
2. Download and install solo-chain
3. Install Cynao in Google Chrome and use private-net which will connnect to solo-chain
4. Deploy smartcontract in SmartX which will use Cyano to deploy to solo-chain
5. Check the smartcontract has deployed successfully on the solo-chain
6. Invoke smartcontract in SmartX  which will use Cyano to invoke on solo-chain
7. Check transction on solo-chain
8. Deploy/Invoke to Mainnet using SmartX and Cyano (**only do this when you have completed development**)


The following tools will be needed:

* [SmartX](https://smartx.ont.io/) - our online smart contract IDE and debugger
* [Solo-chain](https://github.com/punicasuite/solo-chain/releases) - a prebuilt private-net for development
* [Cyano wallet](https://chrome.google.com/webstore/detail/cyano-wallet/dkdedlpgdmmkkfjabffeganieamfklkm?utm_source=chrome-ntp-icon) - an Ontology Google Chrome extension wallet
<p><br>


## Create and compile your smart contract in SmartX

We will develop, compile and test our smart contract using the [SmartX](https://smartx.ont.io/) tool. If you are new to SmartX, please read over the [SmartX Tutorial](https://dev-docs.ont.io/#/docs-en/smartcontract/01-started) which will guide you thorugh the process of using the tool.

Create a new project in the language of your choice and use one of the templates (we will be using Arith) to work with if you don't have your own smart contract.

Compile your smart contract but **do not deploy it yet**.

![Compile](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/SmartX_compile.jpg)


<p><br>

## Download and install solo-chain

Solo-chain is a pre-built Ontology private-net which includes a number of tools to interact with and monitor the network.

Download and install [Solo-chain](https://github.com/punicasuite/solo-chain/releases) and verify it is working as expected.  You can do this by checking that blocks are being generated and/or initiating a transaction.  

Please make note of the IP address shown in the dashboard for later use.

![Solo-chain dashboard](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/solo-chain_interface.jpg)

<p><br>

## Install Cyano

Cyano wallet is a Google Chrome extension that is integrated with SmartX and allows developers to deploy/invoke smart contracts either on a private-net or the Ontology mainnet.

Install [Cyano wallet](https://chrome.google.com/webstore/detail/cyano-wallet/dkdedlpgdmmkkfjabffeganieamfklkm?utm_source=chrome-ntp-icon) and click on the settings cog in the top right hand corner of the first screen.

![Cyano settings cog](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/Cyano_settings_cog.jpg)

Change the network to **Private-Net** and put the IP address shown in the solo-chain interface in Cyano (typically 127.0.0.1).

![Cyano settings page](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/Cyano_settings_page.jpg)

Once Cyano is successfully connected to your private-net, the connection icon in the bottom right hand side of the screen will show a connected icon (as above).

Next, import the private key of the main address from your solo-chain into Cyano.

Finally, initiate a transaction and claim your ONG which will be used to pay for transaction fees during deployment/invocation.
<p><br>

## Deploy smart contract in SmartX

Once you are satisfied with your smart contract, you can use SmartX to deploy it to your private-net.  SmartX will interact with Cyano wallet in order to deploy and pay the transaction fee(s).

Select Deploy in SmartX and enter the appropriate details in the information fields (Name, Author, etc).  Once this has been done, select deploy.

![SmartX deploy](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/SmartX_deploy.jpg)

<p>
Cyano wallet will be launched and the smart contract deploy screen will be shown.  Ensure the details are correct and select confirm.  

![Cyano SC deploy](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/Cyano_SC_deploy.jpg)

Enter your Cyano wallet password to deploy your smart contract.
<p><br>

## Check the smart contract has deployed successfully

You can verify the smart contract has been deployed correctly by clicking the Smart Contract icon in solo-chain which will show you the contract hash and information you entered in SmartX.

![Solo-chain SC list](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/solo-chain_SC_list.jpg)
<p><br>

## Invoke smart contract in SmartX

The next step is to invoke your smart contract which is done in SmartX by selecting Run and selecting any methods (if applicable).  In this example we are using the 'Arith' template so we will be using the add method to add two numbers together.

![SmartX invoke SC](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/SmartX_invoke_SC.jpg)

Once you click on Run, Cyano wallet will prompt you to invoke the smart contract which can be done by clicking confirm and entering your password.

![Cyano invoke SC](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/Cyano_invoke_SC.jpg)

The results of the invocation will be displayed in the log window of SmartX.

![SmartX invoke SC results](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/SmartX_invoke_SC_result.jpg)
<p><br>


## Check invocation transction

You can also use solo-chain to check the invoke function by selecting the Transactions tab and looking for a transaction type of Invoke.

![Solo-chain invoke transaction](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/solo-chain_transaction_invoke.jpg)

More detailed information is available by clicking on the Detail link.

![Solo-chain invoke transaction details](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/solo-chain_transaction_invoke_details.jpg)
<p><br>


## Deploy to Mainnet 

Once you have completed the above steps, you may wish to deploy your smart contract to the Ontology Mainnet for general purpose use.

To do this, in Cyano select the settings cog in the top right hand corner.

![Cyano settings cog](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/Cyano_settings_cog.jpg)

Change to network to Main-Net and click Save.

![Cyano settings mainnet](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/Cyano_settings_page_mainnet.jpg)

Ensure you have a Main-net wallet setup in Cyano with sufficient gas to deploy the contract before proceeding.

Finally, return to SmartX and follow the same process as you did in the **Deploy smart contract in SmartX** section ensuring that Cyano shows it is connected to Main-net.

Your smart contract will now be deployed to the Ontology Main-net and you can invoke it as you did in the **Invoke smartcontract in SmartX** section.
