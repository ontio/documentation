
## 1. 概述
手机钱包方集成 ```dAPI``` 实际上是集成 ```Provider-SDK```，```Provider-SDK``` 对 ```iOS/Android webview``` 进行了一些方法的封装，支持了网页 ```DAPP``` 和 ```iOS/Android webview``` 之间的通信。

![接入说明](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/provider-sdk.png)

## 2. 接入说明

根据你的操作系统，参考以下方法：

- Android 请参考 [ cyano-android-provider-sdk 接入文档](https://dev-docs.ont.io/#/docs-cn/cyano/02-mobile-provider?id=android-sdk)

- IOS 请参考 [ cyano-ios-provider-sdk 接入文档](https://dev-docs.ont.io/#/docs-cn/cyano/02-mobile-provider?id=ios-sdk)



## 3. ```dAPI``` 使用场景

移动端 ```dAPI``` 规范文档包括唤醒、扫码、和钱包中打开 ```H5 DAPP``` 三种场景。

对于已支持  ```dAPI``` 的钱包如 [麦子钱包 ](http://www.mathwallet.org/en/)，请参考对应的对接文档。关于协议详情请查看 [CEP1 ](https://github.com/ontio-cyano/CEPs/blob/master/CEPS/CEP1.mediawiki)。

 DAPP 场景接入文档：

* [钱包打开 ```DAPP``` 接入流程](https://dev-docs.ont.io/#/docs-cn/Wallet-Integration/04-WalletDocking-wallet-open-DApp)
* [扫码接入流程](https://dev-docs.ont.io/#/docs-cn/Wallet-Integration/03-WalletDocking-scan-qrcode)
* [唤醒接入流程](https://dev-docs.ont.io/#/docs-cn/Wallet-Integration/07-WalletDocking-wakeup)

参考钱包下载链接： [http://101.132.193.149/files/app-debug.apk](http://101.132.193.149/files/app-debug.apk)




### 场景1： 钱包中打开 ```DAPP```

![](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/scenario3-cn.png)

详细流程：

1. 在钱包中打开 ```DAPP```
2. 获取账户或身份信息
3. 登录 ```DAPP```
4. ```DAPP``` 调用智能合约

### 场景2： 钱包扫码

扫描登录：

![login-invoke](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/split-login-invoke-1-cn.png)

详细流程：

1. 钱包扫描 ```DAPP``` 方提供的二维码（ [登录二维码标准](#登录) ）
2.  ```Provider``` 获取到 ```callback url``` 和验证用的消息，让用户输入密码对对消息签名，调用 ```DAPP``` 方的回调地址
3. ```DAPP``` 后端验证签名（ [签名验证方法](#签名验证方法) ）后返回验证结果

扫描调用合约：

![login-invoke](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/split-login-invoke-2-cn.png)

详细流程：

1. 钱包扫描 ```DAPP``` 方提供的二维码（ [调用合约二维码标准](#调用合约) ）
2. 钱包构造交易，用户签名，预执行交易，用户确认，发送到链上，调用 ```DAPP``` 后端的回调地址发送交易  ```Hash``` 
3. ```DAPP``` 后端查询这笔合约交易事件

### 场景3： ```DAPP``` 唤醒钱包


 DAPP 发起登录请求：

![login-invoke](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/split-login-invoke-3-cn.png)

1. ```DAPP``` 唤醒钱包（[登录](#登录)）
2. 钱包获取到 ```callback url``` 和验证用的消息，让用户输入密码对消息签名，钱包调用 ```DAPP``` 后端的回调方法
3. ```DAPP``` 后端验证签名

DAPP 发起调用合约请求：

![login-invoke](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/split-login-invoke-4-cn.png)

1. ```DAPP``` 唤醒钱包（ [调用合约](#调用合约) ）
2. 钱包构造交易，用户输入密码，钱包预执行交易，待用户确认后，发送到链上，返回交易 ```Hash``` 给 ```callback``` 地址
3. ```DAPP``` 后端可以根据交易 ```Hash``` 到链上查询这笔合约交易事件


## 4. 场景1演示

移动版 ```Cyano``` 钱包源码链接地址 [ cyano-android ](https://github.com/ontio-cyano/cyano-android), [ cyano-ios ](https://github.com/ontio-cyano/cyano-ios)。

H5 DAPP 例子源码: [ mobile-dapp-demo ](https://github.com/ontio-cyano/mobile-dapp-demo)

### 4.1 在钱包中打开 ```DAPP```

在钱包中打开 ```DAPP```：[http://101.132.193.149:5000/#/](http://101.132.193.149:5000/#/)

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-dapps.jpg" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-private-dapp.jpg" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-open-dapp.png" height="350" width="200">
</div>

### 4.2 获取账号或身份信息

如果不需要验证用户身份， ```DAPP``` 将直接查询账号或身份信息。

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-open-dapp.png" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/02-getAccount.jpg" height="350" width="200">
</div>

### 4.3 登录 ```DAPP```

如果需要验证用户身份，```DAPP``` 将发消息给钱包签名，然后验证签名。

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-open-dapp.png" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/03-login-pwd.png" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/04-logined.jpg" height="350" width="200">
</div>

### 4.4 ```DAPP``` 调用合约

DAPP 调用合约流程为：

1. 用户签名后预执行合约
2. 用户确认并发送交易
3. 返回交易 ```Hash``` 给 ```DAPP```

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/input-password.jpg" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/05-pre-exec-result.png" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/06-dapp-recv-txhash.jpg" height="350" width="200">
</div>
