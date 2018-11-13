本教程将指导你完成基于私有链的智能合约创建、部署、测试过程，并最终将其部署到本体主网。

使用的步骤是：

1.在SmartX中创建和编辑智能合约（**不要在此步骤部署**）。
2.下载并安装solo-chain。
3.在谷歌浏览器中安装Cynao并将其连接到私链。
4.在SmartX中部署智能合约，它将调用Cyano将合约部署到solo-chain。
5.检查智能合约是否已成功部署在solo-chain。
6.在SmartX中调用智能合约，它将使用Cyano调用solo-chain中的合约。
7.检查solo-chain中的交易。
8.使用SmartX和Cyano在主网上进行部署和调用（**仅在完成开发后执行此操作**）

需要以下工具：

- [SmartX](https://smartx.ont.io/) —— 我们的在线智能合约集成开发环境和调试器。
- [Solo-chain](https://github.com/punicasuite/solo-chain/releases) —— 一个预先构建的私有链。
- [Cyano wallet](https://chrome.google.com/webstore/detail/cyano-wallet/dkdedlpgdmmkkfjabffeganieamfklkm?utm_source=chrome-ntp-icon) —— 一个本体的谷歌 Chrome 浏览器插件。

## 在SmartX中创建并编译智能合约

我们将使用[SmartX](https://smartx.ont.io/)开发、编译和测试我们的智能合约。如果你不熟悉SmartX，请阅读[SmartX教程](https://ontio.github.io/documentation/SmartX_Tutorial_en.html)，它将指导你完成该工具的使用。

编译你的智能合约但**不要部署它**。

![Compile](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/SmartX_compile.jpg)

<p><br>

## 下载并安装 solo-chain

Solo-chain 是一个预构建的本体私链，它包含许多与网络交互和监视网络的工具。

下载安装[Solo-chain](https://github.com/punicasuite/solo-chain/releases)并验证它是否按预期工作。你可以通过检查正在生成的区块和发起交易来执行此操作。

请记录下控制面板中显示的IP地址以供日后使用。

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
