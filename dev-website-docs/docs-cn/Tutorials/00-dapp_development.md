
本教程将指导你完成基于私有链的智能合约创建、部署、测试过程，并最终将其部署到本体主网。

使用的步骤是：

1. 在SmartX中创建和编辑智能合约（**不要在此步骤部署**）。
2. 下载并安装solo-chain。
3. 在谷歌浏览器中安装Cynao并将其连接到私链。
4. 在SmartX中部署智能合约，它将调用Cyano将合约部署到solo-chain。
5. 检查智能合约是否已成功部署在solo-chain。
6. 在SmartX中调用智能合约，它将使用Cyano调用solo-chain中的合约。
7. 检查solo-chain中的交易。
8. 使用SmartX和Cyano在主网上进行部署和调用（**仅在完成开发后执行此操作**）

需要以下工具：

- [SmartX](https://smartx.ont.io/) —— 我们的在线智能合约集成开发环境和调试器。
- [Solo-chain](https://github.com/punicasuite/solo-chain/releases) —— 是一个预先构建的私有链。
- [Cyano wallet](https://chrome.google.com/webstore/detail/cyano-wallet/dkdedlpgdmmkkfjabffeganieamfklkm?utm_source=chrome-ntp-icon) —— 是一个本体的谷歌 Chrome 浏览器插件。

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

Cyano钱包是与SmartX集成的谷歌 Chrome 扩展程序，允许开发人员在私有链或者本体测试网、主网上部署和调用智能合约。

安装 [Cyano 钱包](https://chrome.google.com/webstore/detail/cyano-wallet/dkdedlpgdmmkkfjabffeganieamfklkm?utm_source=chrome-ntp-icon)并点击屏幕右上角的⚙图标。

![Cyano settings cog](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/Cyano_settings_cog.jpg)

将网络切换至 **Private-Net** 并粘贴 solo-chain 中显示的IP地址到 Cyano 钱包 (一般情况下是 `127.0.0.1`)。

![Cyano settings page](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/Cyano_settings_page.jpg)

一旦 Cyano 成功连接到你的私有网络，屏幕右下角的连接图标将显示一个连接图标（如上所示）。

接下来，将私钥从 solo-chain 导入到 Cyano 钱包当中。

最后，发起交易并提取用于在部署和调用智能合约期间支付交易费用的 ONG。
<p><br>

## Deploy smart contract in SmartX

一旦你对你的智能合约感到满意，就可以使用SmartX将其部署到您的私人网络。SmartX将与Cyano钱包进行交互，以部署合约和支付交易费用。

选择在SmartX中部署，然后在信息字段（名称、作者等）中输入相应的详细信息。完成此操作后，选择 `deploy`。

![SmartX deploy](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/SmartX_deploy.jpg)
<p>

启动 Cyano 钱包，显示智能合约部署窗口，确保细节正确并选择 `confirm`。

![Cyano SC deploy](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/Cyano_SC_deploy.jpg)

输入你的 Cyano 钱包密码以部署你的智能合约。
<p><br>

## 检查智能合约是否已成功部署

你可以通过单击 solo-chain 中的 `Smart Contracts` 选项卡来验证智能合约是否已正确部署，该选项卡将显示您在SmartX中输入的合约哈希和信息。

![Solo-chain SC list](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/solo-chain_SC_list.jpg)
<p><br>

## 在SmartX调用智能合约

下一步是通过点击 `Run` 并选择任何方法（如果适用）来调用在SmartX中完成的智能合约。 在这个例子中，我们使用`Arith` 模板，因此我们将使用 `add` 方法将两个数字相加。

![SmartX invoke SC](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/SmartX_invoke_SC.jpg)

点击`run`后，Cyano 钱包将提示你智能合约调用，单击 `Confirm` 并输入密码即可完成。

![Cyano invoke SC](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/Cyano_invoke_SC.jpg)

调用的结果将显示在 SmartX 的日志窗口中。

![SmartX invoke SC results](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/SmartX_invoke_SC_result.jpg)
<p><br>

## 检查调用交易

你还可以使用 solo-chain 在`Transactions`选项卡中查找 `Invoke` 类型的交易来检查函数调用。

![Solo-chain invoke transaction](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/solo-chain_transaction_invoke.jpg)

单击 `Detail` 链接可获得更多详细信息。

![Solo-chain invoke transaction details](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/solo-chain_transaction_invoke_details.jpg)
<p><br>

## 部署到主网

完成上述步骤后，你可能希望将智能合约部署到本体主网。

要执行此操作，请在 Cyano 中选择右上角的⚙图标。

![Cyano settings cog](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/Cyano_settings_cog.jpg)

切换到主网并保存。

![Cyano settings mainnet](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/Cyano_settings_page_mainnet.jpg)

确保您在 Cyano 中设置了主网钱包，并且在继续操作之前需要足够的 gas 来部署合同。

最后，返回 SmartX 并按照与**在 SmartX 中部署智能合约**一节中所述步骤进行部署，确保 Cyano 显示它已连接到了主网。

你的智能合约现在被部署到了本体主网，你可以调用它就像**在 SmartX 中调用智能合约**一节中所述步骤进行调用。
