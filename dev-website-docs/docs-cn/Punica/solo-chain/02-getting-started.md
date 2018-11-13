# 快速开始

当启动Solo Chain后，你将看到类似的界面。

<div align="center"><img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/00-home.png"><br><br></div>

在顶部菜单栏，你可以在其中导航栏中找到应用程序的不同选项卡以及查看网络的设置。

<div align="center"><img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/01-menu-bar.png"><br><br></div>

在菜单栏的左下侧，你可以看到许多有用的信息。例如与你的私有区块链网络通信的服务器地址、当前的块高度以及用于计算每笔交易所需费用的 gas price 和 gas limit。

<div align="center"><img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/02-server-addresses.png"><br><br></div>

在右侧，你可以找到停止和重新启动网络实例的按钮。点击`Stop`将暂停你的网络（数据将被保留），然后你可以再次单击`Start`。`Reboot`将清除所有数据并启动新的区块链实例。

<div align="center"><img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/03-stop-reboot.png"><br><br></div>

<div align="center"><img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/04-start.png"><br><br></div>

在`Account`界面的主要部分，你将看到预先创建的帐户列表。第一个账户将包含你的私有区块链网络中的所有ONT。

<div align="center"><img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/05-starting-account.png" ><br><br></div>

单击该帐户上的`Transfer`按钮后，你可以在显示的窗口中将ONT发送到账户列表中的第二个帐户。只需填写详细的转账信息，然后单击`OK`。

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/06-transfer.png" ><br><br>
</div>

发送后不久，你应该会看到帐户中的余额更新。只有在发送后你才可以申请ONG。因此，在第一个帐户上，单击`Redeem ONG`，你很快就会收到该帐户的ONG。

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/07-claim.png" ><br><br>
</div>

在帐户项的右侧，有一个🔑图标。单击此按钮后，你看到帐户的私钥。在构建自己的应用程序时可能会需要这些私钥来签署交易。

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

如果单击方块，则可以在JSON中展开和收缩对象和数组。

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/11-block-detail-open.png" ><br><br>
</div>

在`Transactions`选项卡中，你可以看到所有已处理的交易，包括它们在哪个块中执行，以及它的详细信息。

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/12-transactions.png" ><br><br>
</div>

单击右侧的 `Detail` 按钮将以JSON格式显示包含在该交易中的所有详细信息。在这里，你可以看到签署交易的账户、支付网络费用账户等等。

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/13-tx-details.png" ><br><br>
</div>

在 `Events` 选项卡中，你可以查看交易中发出的所有通知事件。

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/14-events.png" ><br><br>
</div>

例如，深入研究下面事件的细节，我们可以看到它是在领取我们的ONG时执行的 `transfer` 操作时发出。在调试智能合约时，这可能是一个非常有用的工具，因为你可以创建自定义的 `Notify` 事件进行广播。

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/15-transfer-event.png" ><br><br>
</div>

在`Smart Contracts`选项卡中，你可以找到部署在所处网络中的所有合约的完整列表。在部署新版本时，这对于管理新的开发合约哈希地址非常有用。

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/16-smart-contracts.png" ><br><br>
</div>

在`Logs`选项卡中，你可以看到私有网络的完整日志记录。

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/17-logs.png" ><br><br>
</div>

最后，单击屏幕右上角的齿轮图标将显示设置屏幕窗口。在这里，我们可以为我们的私有网络配置 gas price。

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/18-settings.png" ><br><br>
</div>
