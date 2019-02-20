本体为DApp开发提供了一站式的解决方案，帮助开发者快速上手DApp开发。

DApp开发主要分为两个部分：智能合约开发和dApi的调用。

一般DApp的核心逻辑都是在智能合约中完成，本体提供了多个工具，帮助开发者快速开发和部署合约，或者从其它链上迁移合约。本体还为dapp开发提供了与合约交互的接口规范--dApi，这样，用户可以安全，方便地使用dapp，不用担心丢失私钥；dapp开发者可以只专注于dapp的业务逻辑开发。

## 一. 合约开发

本教程将指导你完成基于私有链的智能合约创建、部署、测试过程，并最终将其部署到本体主网。

> 您也可以直接在SmartX上基于本体测试网完成合约的部署和测试，这样就不需要安装和使用solo-chain。
>
> 您可以从[这里](https://developer.ont.io/applyOng)申请本体测试网token。

使用的步骤是：

1. 下载并安装solo-chain。
2. 在谷歌浏览器中安装Cynao并将其连接到私链。
3. 在SmartX中创建，编辑和部署智能合约，它将调用Cyano将合约部署到solo-chain。
4. 检查智能合约是否已成功部署在solo-chain。
5. 在SmartX中调用智能合约，它将使用Cyano调用solo-chain中的合约。
6. 检查solo-chain中的交易。
7. 使用SmartX和Cyano在主网上进行部署和调用（**仅在完成开发后执行此操作**）

![Smart Contract Develop](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/SCdevelop.jpg)

需要以下工具：

- [SmartX](https://smartx.ont.io/) —— 我们的在线智能合约集成开发环境和调试器。
- [Solo-chain](https://github.com/punicasuite/solo-chain/releases) —— 是一个预先构建的私有链。
- [Cyano wallet](https://chrome.google.com/webstore/detail/cyano-wallet/dkdedlpgdmmkkfjabffeganieamfklkm?utm_source=chrome-ntp-icon) —— 是一个本体的谷歌 Chrome 浏览器插件。


### 1. 下载并安装 solo-chain

Solo-chain 是一个预构建的本体私链，它包含许多与网络交互和监视网络的工具。

下载安装[Solo-chain](https://github.com/punicasuite/solo-chain/releases)并验证它是否按预期工作。你可以通过检查正在生成的区块和发起交易来执行此操作。

请记录下控制面板中显示的IP地址以供日后使用。

![Solo-chain dashboard](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/solo-chain_interface.jpg)

<p><br>

### 2. 在Chrome浏览器中安装Cyano钱包

Cyano钱包是与SmartX集成的谷歌 Chrome 扩展程序，允许开发人员在私有链或者本体测试网、主网上部署和调用智能合约。

安装 [Cyano 钱包](https://chrome.google.com/webstore/detail/cyano-wallet/dkdedlpgdmmkkfjabffeganieamfklkm?utm_source=chrome-ntp-icon)并点击屏幕右上角的⚙图标。

![Cyano settings cog](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/Cyano_settings_cog.jpg)

将网络切换至 **Private-Net** 并粘贴 solo-chain 中显示的IP地址到 Cyano 钱包 (一般情况下是 `127.0.0.1`)。

![Cyano settings page](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/Cyano_settings_page.jpg)

一旦 Cyano 成功连接到你的私有网络，屏幕右下角的连接图标将显示一个连接图标（如上所示）。

接下来，将私钥从 solo-chain 导入到 Cyano 钱包当中。

最后，发起交易并提取用于在部署和调用智能合约期间支付交易费用的 ONG。
<p><br>

### 3. 在SmartX中创建，编译和部署智能合约到私有链

我们将使用[SmartX](https://smartx.ont.io/)开发、编译和测试我们的智能合约。关于智能合约的开发，请参考我们的[相关教程](http://dev-docs.ont.io/#/docs-cn/smartcontract/01-started)。

创建你的智能合约。
![New](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/newSC.jpg)

![Create](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/createSC.jpg)


编译你的智能合约。

![Compile](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/SmartX_compile.jpg)


一旦你对你的智能合约感到满意，就可以使用SmartX将其部署到您的私人网络。SmartX将与Cyano钱包进行交互，以部署合约和支付交易费用。

选择在SmartX中部署，然后在信息字段（名称、作者等）中输入相应的详细信息。完成此操作后，选择 `deploy`。

![SmartX deploy](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/SmartX_deploy.jpg)
<p>

启动 Cyano 钱包，显示智能合约部署窗口，确保细节正确并选择 `confirm`。

![Cyano SC deploy](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/Cyano_SC_deploy.jpg)

输入你的 Cyano 钱包密码以部署你的智能合约。
<p><br>

### 4. 检查智能合约是否已成功部署

你可以通过单击 solo-chain 中的 `Smart Contracts` 选项卡来验证智能合约是否已正确部署，该选项卡将显示您在SmartX中输入的合约哈希和信息。

![Solo-chain SC list](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/solo-chain_SC_list.jpg)
<p><br>

### 5. 在SmartX调用智能合约

下一步是通过点击 `Run` 并选择任何方法（如果适用）来调用在SmartX中完成的智能合约。 在这个例子中，我们使用`Arith` 模板，因此我们将使用 `add` 方法将两个数字相加。

![SmartX invoke SC](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/SmartX_invoke_SC.jpg)

点击`run`后，Cyano 钱包将提示你智能合约调用，单击 `Confirm` 并输入密码即可完成。

![Cyano invoke SC](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/Cyano_invoke_SC.jpg)

调用的结果将显示在 SmartX 的日志窗口中。

![SmartX invoke SC results](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/SmartX_invoke_SC_result.jpg)
<p><br>

### 6. 检查调用交易

你还可以使用 solo-chain 在`Transactions`选项卡中查找 `Invoke` 类型的交易来检查函数调用。

![Solo-chain invoke transaction](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/solo-chain_transaction_invoke.jpg)

单击 `Detail` 链接可获得更多详细信息。

![Solo-chain invoke transaction details](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/solo-chain_transaction_invoke_details.jpg)
<p><br>

### 7. 部署到主网

完成上述步骤后，你可能希望将智能合约部署到本体主网。

要执行此操作，请在 Cyano 中选择右上角的⚙图标。

![Cyano settings cog](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/Cyano_settings_cog.jpg)

切换到主网并保存。

![Cyano settings mainnet](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/Cyano_settings_page_mainnet.jpg)

确保您在 Cyano 中设置了主网钱包，并且在继续操作之前需要足够的 gas 来部署合同。

最后，返回 SmartX 并按照与**在 SmartX 中部署智能合约**一节中所述步骤进行部署，确保 Cyano 显示它已连接到了主网。

你的智能合约现在被部署到了本体主网，你可以调用它就像**在 SmartX 中调用智能合约**一节中所述步骤进行调用。

## 二. 使用dApi

dApi支持[Web环境](https://github.com/ontio-cyano/cyano-bridge)（仅支持Chrome浏览器）和[移动版](https://github.com/ontio/ontology-dapi)（已实现dApi接口的钱包）。

移动版dApi只提供几个重要dapi接口，查询区块交易等相关的接口可以直接调用区块链浏览器的api接口查询, 详细情况见[explorer api](http://dev-docs.ont.io/#/docs-en/explorer/overview) 。而Chrome插件钱包的dApi接口比较全。

>目前两种环境中dApi代码不能通用。兼容的方式可以参考：[dapi-universal](https://github.com/ontio-cyano/dapi-universal)

下面会介绍dapp下开发中常见的几种接口：登录，查询合约接口，调用合约方法。

![dapi develop](https://raw.githubusercontent.com/ontio/documentation/master/docs/lib/images/dapidevelop.jpg)

### 1. 安装dApi

首先需要安装dApi。

#### Chrome版

```
npm install ontology-dapi
```

#### 移动版

```
npm install cyanobridge
```

### 2. 初始化

在调用dApi接口之前需要初始化。

#### Chrome版

```
import {client} from 'ontology-dapi'
client.registerClient({})
```

#### 移动版
```
import { client } from 'cyanobridge'
client.registerClient();

```

### 3. 登录

DApp中的登录可以有两种实现：

1. 直接通过dapi获取用户的账户地址或身份（ONT ID），如果有则认为已登录dApp。
2. dapp后台生成一个字符串，发送给前端，前端调用dapi对该字符串签名，并返回给后端，后端验证通过后，可以认为登录成功，接下来后台可以给用户颁发session，或者颁发access token，这取决于dapp自己业务逻辑。

#### 3.1 获取账号或身份信息

获取账号或身份信息，移动端可以可以选择填dapp信息也可以不填写。

##### 移动版

```
import { client } from 'cyanobridge'

const params = {
    dappName: 'My dapp',
    dappIcon: '' // some url points to the dapp icon
}

try {
    const res = await client.api.asset.getAccount(params);
    const res = await client.api.identity.getIdentity(params);
    console.log(res)
} catch(err) {
    console.log(err)
}

```

##### Chrome版

```
account = await client.api.asset.getAccount()
res = await client.api.identity.getIdentity();
```

#### 3.2 数据签名

##### 移动版

```
const params = {
    type: 'account',// account or identity that will sign the message
    dappName: 'My dapp', // dapp's name
    dappIcon: 'http://mydapp.com/icon.png', // some url that points to the dapp's icon
    message: 'test message', // message sent from dapp that will be signed by native client
    expired: new Date('2019-01-01').getTime(), // expired date of login
    callback: '' // callback url of dapp
}
let res;
try {
    res = await client.api.message.login(params);
    console.log(res)
}catch(err) {
    console.log(err)
}
```

##### Chrome版

```
const result = await client.api.message.signMessage({ message });

```

### 4. 合约调用

合约调用主要分为两种：预执行和执行。预执行一般是用来调用合约的查询接口，执行是直接调用合约的方法。比如有一个摇骰子的游戏，通过调用执行，调用合约中摇骰子的具体方法；通过调用预执行，查询摇骰子的结果。


#### 4.1 执行

##### 移动版

```
const scriptHash = 'cd948340ffcf11d4f5494140c93885583110f3e9';
const operation = 'test'
const args = [
    {
        type: 'String',
        value: 'helloworld'
    }
]
const gasPrice = 500;
const gasLimit = 20000;
const payer = 'AecaeSEBkt5GcBCxwz1F41TvdjX3dnKBkJ'
const config = {
    "login": true,
    "message": "invoke smart contract test",
    "qrcodeUrl": "" ,
    "callback": ""
}
const params = {
          scriptHash,
          operation,
          args,
          gasPrice,
          gasLimit,
          payer,
          config
        }
try {
   const res = await client.api.smartContract.invoke(params);
   } catch(err) {
    console.log(err)
}

```

##### Chrome版
````
const scriptHash = '16edbe366d1337eb510c2ff61099424c94aeef02';
const gasLimit = 30000;
const gasPrice = 500;
const operation = 'test'

const args = [
   {
	name: "msg",
	type: "String",
	value: "hello world"
   }
]
 params = {
            scriptHash,
            operation,
            args,
            gasPrice,
            gasLimit
}
await client.api.smartContract.invoke(params)

​```
````
