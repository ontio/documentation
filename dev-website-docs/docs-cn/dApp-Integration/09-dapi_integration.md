
# DApi 接入说明

本系列接入文档主要介绍 DApp 如何在各种场景下调用 DAPI，实现包括登录，调用智能合约等操作。

与传统 App 不同，DApp 没有一个中心化的账号管理后台，用户完全掌控自身的身份和资产，所以 DApp 除了通过智能合约构建自己的业务逻辑，也需要通过各种方式和链进行交互。为了降低 DApp 开发难度，我们提供了丰富的 DAPI 或方法用于 DApp 与链交互，适用于当前所有主流设备中使用 DApp 的场景。

目前支持以下场景：
- [DApp 调用 Chrome 插件钱包](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/03-DAppDocking-use-chrome-extension-wallet)
- [手机钱包内打开 DApp](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/01-DAppDocking-Wallet-Opens-DApp)
- [手机钱包扫码 DApp](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/02-DAppDocking-QRcode)
- [应用唤醒手机钱包](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/06-DAppDocking-Wake-up)

目前已支持 DAPI 的钱包如 [麦子钱包](http://www.mathwallet.org/en/)、[Banko](http://bankowallet.com/pc.html) ，已支持 DAPI 的 DAPPs： [https://github.com/ontio-community/dapp-store](https://github.com/ontio-community/dapp-store)。

协议详情请查看 [CEP1](https://github.com/ontio-cyano/CEPs/blob/master/CEPS/CEP1.mediawiki)。

参考 ```Android``` 钱包下载地址：[http://101.132.193.149/files/app-debug.apk](http://101.132.193.149/files/app-debug.apk)


## 钱包演示

这里主要介绍一下最主流的在手机钱包中打开 DApp的流程和基本功能演示，具体对接详情文档请参考 [在手机钱包中打开 DApp](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/01-DAppDocking-Wallet-Opens-DApp)：

* 移动版 Cyano 钱包源码链接地址：[cyano-android](https://github.com/ontio-cyano/cyano-android) ，[cyano-ios](https://github.com/ontio-cyano/cyano-ios)
* 移动版 Cyano 安卓钱包下载地址：[cyano wallet](http://101.132.193.149/files/app-debug.apk)
* H5 DApp 例子源码：[mobile-dapp-demo](https://github.com/ontio-cyano/mobile-dapp-demo)
* H5 DApp例子链接：http://101.132.193.149:5000/#/

### 在钱包中打开 DApp

在钱包中打开DApp：http://101.132.193.149:5000/#/

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-dapps.jpg" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-private-dapp.jpg" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-open-dapp.png" height="350" width="200">
</div>

### 获取账号或身份信息

如果不需要验证用户身份，DApp 将直接查询账号或身份信息。

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-open-dapp.png" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/02-getAccount.jpg" height="350" width="200">
</div>

### 登录 DApp

如果需要验证用户身份，DApp 将发消息给钱包签名，然后验证签名。

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-open-dapp.png" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/03-login-pwd.png" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/04-logined.jpg" height="350" width="200">
</div>

### DApp 调用合约

DApp 调用合约流程为：

1. 用户签名后预执行合约
2. 用户确认并发送交易
3. 返回交易 hash 给 DApp

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/input-password.jpg" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/05-pre-exec-result.png" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/06-dapp-recv-txhash.jpg" height="350" width="200">
</div>
