
## 概述
手机钱包方集成dAPI 实际上是集成 Provider-SDK，Provider-SDK 对 iOS/Android webview 进行了一些方法的封装，支持了网页 DApp 和 iOS/Android webview 之间的通信。

![接入说明](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/provider-sdk.png)

## 接入说明

根据你的操作系统，参考以下方法：

- Android 请参考 [cyano-android-provider-sdk接入文档](https://dev-docs.ont.io/#/docs-cn/cyano/02-mobile-provider?id=android-sdk)

- IOS 请参考 [cyano-ios-provider-sdk接入文档](https://dev-docs.ont.io/#/docs-cn/cyano/02-mobile-provider?id=ios-sdk)



## DApp 使用场景

移动端 DAPI 规范文档包括唤醒、扫码、和钱包中打开 H5 DApp 三种场景。对于已支持 DAPI 的钱包如 [麦子钱包](http://www.mathwallet.org/en/)，请参考对应的对接文档。关于协议详情请查看 [CEP1](https://github.com/ontio-cyano/CEPs/blob/master/CEPS/CEP1.mediawiki)。

DApp 场景接入文档：
* [钱包打开 DApp 接入流程](https://dev-docs.ont.io/#/docs-cn/Wallet-Integration/04-WalletDocking-wallet-open-DApp)
* [扫码接入流程](https://dev-docs.ont.io/#/docs-cn/Wallet-Integration/03-WalletDocking-scan-qrcode)
* [唤醒接入流程](https://dev-docs.ont.io/#/docs-cn/Wallet-Integration/07-WalletDocking-wakeup)

参考钱包下载链接： http://101.132.193.149/files/app-debug.apk

## 场景1和2： 唤醒、扫码场景


##### 登录、调用智能合约

![](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/split-login-invoke.png)

##### 未登录时调用智能合约

![](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/invoke-with-login.png)


## 场景3： 钱包中打开 H5 DApp

1. 在 Provider 中打开 DApp
2. 获取账户或身份信息
3. 登录 DApp
4. DApp 调用智能合约

![](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/scenario3.png)

## 钱包演示

移动版 Cyano 钱包源码链接地址 [cyano-android](https://github.com/ontio-cyano/cyano-android),[cyano-ios](https://github.com/ontio-cyano/cyano-ios)。

H5 DApp 例子源码: [mobile-dapp-demo](https://github.com/ontio-cyano/mobile-dapp-demo)

### 在钱包中打开 DApp

钱包中打开 DApp：http://101.132.193.149:5000/#/

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
