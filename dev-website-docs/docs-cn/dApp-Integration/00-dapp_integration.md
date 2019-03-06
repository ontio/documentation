
# dApp接入说明

本系列接入文档主要介绍了DApp如何在各种场景下调用dApi，实现包括登录，调用智能合约等操作

DApp和传统App不同之处在于DApp没有一个中心化的账号管理后台，用户完全掌控自身的身份和资产，所以Dapp除了通过智能合约构建自己的业务逻辑，也需要通过各种方式和链进行交互。为了降低DApp开发难度，我们提供了非常丰富的DApp与链交互的dApi或方法，适用于当前所有主流设备中使用DApp的场景。

目前有唤醒、扫码、钱包中打开H5 DApp、桌面钱包中打开H5 DApp、chrome插件钱包五种场景。已支持dAPI的钱包 [麦子钱包](http://www.mathwallet.org/en/)、[Onion](http://onion.fun/) ,对接请参考对应的对接文档。协议详情请看 [CEP1](https://github.com/ontio-cyano/CEPs/blob/master/CEPS/CEP1.mediawiki)。

参考钱包下载链接： http://101.132.193.149/files/app-debug.apk

当前场景：
- [在手机钱包内打开DApp](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/01-DAppDocking-Wallet-Opens-DApp)
- [DApp支持手机钱包扫码](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/02-DAppDocking-QRcode)
- [DApp支持chrome插件钱包](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/03-DAppDocking-use-chrome-extension-wallet)
- [DApp唤醒手机钱包](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/06-DAppDocking-Wake-up)
- [桌面钱包内打开DApp](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/07-DAppDocking-use-desktop-wallet)


## 钱包演示

移动版Cyano钱包源码链接地址[cyano-android](https://github.com/ontio-cyano/cyano-android),[cyano-ios](https://github.com/ontio-cyano/cyano-ios)。

H5 DApp例子源码: [mobile-dapp-demo](https://github.com/ontio-cyano/mobile-dapp-demo)

### 钱包中打开 DApp

钱包中打开DApp：http://101.132.193.149:5000/#/

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-dapps.jpg" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-private-dapp.jpg" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-open-dapp.png" height="350" width="200">
</div>

### Get account or get identity

DApp登录如果不需要验证用户身份，直接查询账号或身份信息：

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-open-dapp.png" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/02-getAccount.jpg" height="350" width="200">
</div>

### Login DApp

DApp登录如果需要验证用户身份: DApp发消息到给钱包签名，DApp验证签名。

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-open-dapp.png" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/03-login-pwd.png" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/04-logined.jpg" height="350" width="200">
</div>

### DApp Invoke smart contract

DApp调用合约，用户签名后预执行合约，用户确认并发送交易，返回交易hash给DAPP。

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/input-password.jpg" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/05-pre-exec-result.png" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/06-dapp-recv-txhash.jpg" height="350" width="200">
</div>
