


本系列接入文档主要介绍 ```DAPP``` 如何在各种场景下调用 ```dAPI```，实现包括登录，调用智能合约等操作。

与传统 ```APP``` 不同，```DAPP``` 没有一个中心化的账号管理后台，用户完全掌控自身的身份和资产，所以 ```DAPP``` 除了通过智能合约构建自己的业务逻辑，也需要通过各种方式和链进行交互。为了降低 ```DAPP``` 开发难度，我们提供了丰富的 ```dAPI``` 方法用于 ```DAPP``` 与链交互，目前的技术已经适用于在所有主流设备中使用 ```DAPP``` 的场景。

- 目前支持以下场景：
 - [DApp 调用 Chrome 插件钱包](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/03-DAppDocking-use-chrome-extension-wallet)
 - [手机钱包内打开 DApp](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/01-DAppDocking-Wallet-Opens-DApp)
 - [手机钱包扫码 DApp](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/02-DAppDocking-QRcode)
 - [应用唤醒手机钱包](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/06-DAppDocking-Wake-up)

- 目前已支持 ```dAPI``` 协议的钱包有：
 -  [麦子钱包](http://www.mathwallet.org/en/)
 - [Banko](http://bankowallet.com/pc.html) 

- 目前已支持 dAPI 的 DAPPs： 
 - [https://github.com/ontio-community/dapp-store](https://github.com/ontio-community/dapp-store)。

协议详情请查看 [CEP1](https://github.com/ontio-cyano/CEPs/blob/master/CEPS/CEP1.mediawiki)。调试使用 ```Android``` 钱包，下载地址：[http://101.132.193.149/files/app-debug.apk](http://101.132.193.149/files/app-debug.apk)


## 钱包演示

下面主要介绍一下最主流的在手机钱包中打开 ```DAPP``` 的流程和基本功能演示，具体对接详情文档请参考 [在手机钱包中打开 DAPP](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/01-DAppDocking-Wallet-Opens-DApp)：

* 移动版 ```Cyano``` 钱包源码链接地址：[cyano-android](https://github.com/ontio-cyano/cyano-android) ，[Cyano-ios](https://github.com/ontio-cyano/cyano-ios)
* 移动版 ```Cyano``` 安卓钱包下载地址：[http://101.132.193.149/files/app-debug.apk](http://101.132.193.149/files/app-debug.apk)
* H5 DAPP 例子源码：[mobile-dapp-demo](https://github.com/ontio-cyano/mobile-dapp-demo)
* H5 DAPP 例子链接：[http://101.132.193.149:5000/#/](http://101.132.193.149:5000/#/)

### 1. 在钱包中打开 DAPP

在钱包中打开 ```DAPP```：[http://101.132.193.149:5000/#/](http://101.132.193.149:5000/#/)

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-dapps.jpg" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-private-dapp.jpg" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-open-dapp.png" height="350" width="200">
</div>

### 2. 获取账号或身份信息

如果不需要验证用户身份，```DAPP``` 将直接查询账号或身份信息。

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-open-dapp.png" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/02-getAccount.jpg" height="350" width="200">
</div>

### 3. 登录 DAPP

如果需要验证用户身份，```DAPP``` 将发消息给钱包进行签名，然后验证签名。

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-open-dapp.png" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/03-login-pwd.png" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/04-logined.jpg" height="350" width="200">
</div>

### 4. DAPP 调用合约

#### DAPP 调用合约流程为：

1. 用户签名后预执行合约
2. 用户确认并发送交易
3. 返回交易 ```Hash``` 给 ```DAPP```

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/input-password.jpg" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/05-pre-exec-result.png" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/06-dapp-recv-txhash.jpg" height="350" width="200">
</div>
