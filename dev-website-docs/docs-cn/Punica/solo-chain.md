
<div align="center"><img src="https://raw.githubusercontent.com/punicasuite/solo-chain/master/image/icon.png" height="200" width="200"></div>

---

## 概述

本体的一键式（私有）区块链。借助于该桌面应用程序，开发人员可以轻松快速地设置和管理他们自己的本体区块链私有实例，快速进行dApp的开发。Solo Chain 通过 Electron 进行打包，为用户提供了一个设置和管理其私有本体区块链实例的直观图形用户界面。

Solo Chain 应用程序提供了以下功能：

- 快速开始、停止和重启私有区块链实例。
- 提供与本体主网和测试网一样的RPC、REST和Websocket服务器接口。
- 便捷的帐户与帐户之间的资产转移和领取，能够快速进行测试环境的设置。
- 提供了详细的区块、交易和事件信息，可以方便地进行调试。
- 以列表的形式完整地显示所有已部署的智能合约。
- 详细的网络活动记录。
- 可定制的网络配置。


## 安装

- [下载](https://github.com/punicasuite/solo-chain/releases)适用于所在平台(Windows, Mac)的最新安装包。
- 将应用程序安装到桌面计算机。

如果您想基于源代码库自己编译应用程序。

- 从Github上克隆项目库：`git clone git@github.com:punicasuite/solo-chain.git`
- 安装依赖项`yarn install`
- 编译安装程序`yarn build`
- 跳转到`release`文件夹并打开相应的桌面安装程序（dmg或exe）


## 开始使用

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

移动到下一个选项卡，如果单击顶部菜单栏中的`Blocks`选项，将能看到区块信息。

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/solo-chain/09-blocks.png" ><br><br>
</div>

如果你想查看区块的详细信息（包括区块中所处理的所有交易），请单击想要查看区块右侧的`Detail`按钮。在弹出的区块详细信息窗口中，区块信息以JSON格式显示。

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


## 贡献

如果您碰巧发现任何问题，或者对 Solo Chain 的后续功能有任何想法，请到 [Github 项目库](https://github.com/punicasuite/solo-chain) 中提出，这将帮助我们创造一个更好的 Solo Chain。

### 开发步骤

如果要以开发者模式下运行 Solo Chain，你可以：

- 从GitGub获取完整的源码 `git clone git@github.com：punicasuite/solo-chain.git`
- 安装依赖项 `yarn install`
- 编译安装程序 `yarn dev`

这将安装并编译所有必需的依赖项和源代码，并启在 `localhost：9080` 启动服务。当你对 `./src` 文件夹中的代码库进行更改时，应用程序将以热重载的方式进行刷新。

如果你在安装时遇到任何问题，都可以在 Github 的 issue 中提出，或者直接在 Discord 上联系。

### 贡献指南

请打开带有签名的拉取请求。感谢您的帮助！您还可以将代码作为电子邮件发送到开发人员邮件列表。欢迎您加入本体邮件列表或开发人员论坛。

如果您想为此项目贡献代码，请提供详细的提交信息。格式如下：

标题行：在一行中解释提交（使用命令）。

提交消息的主体是几行文本，更详细地解释事情，可能提供有关修复问题的一些背景，等等。

提交消息的主体可以是几个段落，请做正确的自动换行并保持列短于约74个字符左右。这样 `git log` 即使缩进也能很好地显示出来。

解释你的解决方案以及为什么你做你正在做的事情，而不是描述你正在做的事情。确保评审者和你未来都可以阅读补丁，并理解为什么要实施特定的解决方案。

报告者：名字 签署者：名字 邮箱（Reported-by: whoever-reported-it Signed-off-by: Your Name youremail@yourhost.com）