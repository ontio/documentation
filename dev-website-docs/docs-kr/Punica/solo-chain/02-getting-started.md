
# Getting Started
Upon opening the application, you will be presented with the first look at your private Ontology network.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/00-home.png" ><br><br>
</div>

Along the top, you will find the menu bar, where you can navigate to the different tabs of the application along with viewing the network settings.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/01-menu-bar.png" ><br><br>
</div>

Just below the menu bar, on the left hand side you will find a bunch of useful information. Such as the server addresses to communicate with your private network, the current block height, and the gas price and limit which are used to calculate the ONG network fee per transaction.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/02-server-addresses.png" ><br><br>
</div>

To the right you can find controls to stop and reboot your network instance. Pressing `Stop` will pause your network, but your data will be retained for then you click `Start` again. `Reboot` will clear our all your data, and start the blockchain instance fresh.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/03-stop-reboot.png" ><br><br>
</div>

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/04-start.png" ><br><br>
</div>

In the main part of the `Accounts` screen, you will see a list of pre-made accounts. The first of which will contain all the ONT in existence for your private network.

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

If you would like to see the details of any block, including all transactions processed in that block, click the `Detail` button on the right hand side of the block you want to see. A block detail modal will pop up with a interactive JSON of the information about that block.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/10-block-detail.png" ><br><br>
</div>

If you click the squares, you can expand and contract the objects and arrays in the JSON.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/11-block-detail-open.png" ><br><br>
</div>

In the `Transactions` tab, you can see all of the processed transactions, including what block they were executed in, and it's details.

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

Lastly, clicking on the gear icon in the top right of the screen will bring up the settings screen. Here we can configure the gas price of ONG required for network fees for our private network.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/18-settings.png" ><br><br>
</div>
