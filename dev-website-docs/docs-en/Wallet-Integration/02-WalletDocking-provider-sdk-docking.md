
## Overview
Provider-SDK encapsulates some methods for iOS/Android webview, enabling communication between iOS/Android webview and web page DApp.

![Integration Description](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/provider_sdk_en.png)

## Integration Description

According to your operating system, refer to the following methods:

- Android Please refer to [cyano-android-provider-sdk access documentation](https://dev-docs.ont.io/#/docs-cn/cyano/02-mobile-provider?id=android-sdk)

- IOS Please refer to [cyano-ios-provider-sdk access documentation](https://dev-docs.ont.io/#/docs-cn/cyano/02-mobile-provider?id=ios-sdk)



## DApp usage scenarios

The mobile DAPI specification document includes three scenarios: wake up, scan code, and open H5 DApp in the wallet. For wallets that already support DAPI such as [Wheat Wallet](http://www.mathwallet.org/en/), [Onion](http://onion.fun/), please refer to the corresponding docking document. Please see for details of the agreement [CEP1](https://github.com/ontio-cyano/CEPs/blob/master/CEPS/CEP1.mediawiki).

DApp scene access documentation:
* [Wallet opens DApp access process](https://dev-docs.ont.io/#/docs-cn/Wallet-Integration/02-WalletDocking-wallet-open-DApp)
* [Scan code access process](https://dev-docs.ont.io/#/docs-cn/Wallet-Integration/03-WalletDocking-scan-qrcode)
* Wallet docking - wake-up access process (not supported at this time)
* Wallet docking - ONTID authentication and authorization (not supported at this time)

Reference wallet download link: http://101.132.193.149/files/app-debug.apk

## Scenes 1 and 2: Wake up, scan scenes


##### Login, call smart contract

![](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/split-login-invoke.png)

##### Call smart contract when not logged in

![](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/invoke-with-login.png)


## Scene 3: Open H5 DApp in the wallet

1. Open DApp in Provider
2. Get account or identity information
3. Log in to DApp
4. DApp calls smart contract

![](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/scenario3.png)

## Wallet Demo

Mobile version of Cyano wallet source link address [cyano-android] (https://github.com/ontio-cyano/cyano-android), [cyano-ios] (https://github.com/ontio-cyano/cyano- Ios).

H5 DApp example source code: [mobile-dapp-demo](https://github.com/ontio-cyano/mobile-dapp-demo)

### Open DApp in your wallet

Open DApp in the wallet: http://101.132.193.149:5000/#/

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-dapps.jpg" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-private-dapp.jpg" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-open-dapp.png" height="350" width="200">
</div>

### Get account or identity information

If you do not need to verify the user's identity, DApp will directly query the account or identity information.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-open-dapp.png" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/02-getAccount.jpg" height="350" width="200">
</div>

### Login DApp

If the user identity needs to be verified, the DApp will send a message to the wallet to sign and then verify the signature.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-open-dapp.png" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/03-login-pwd.png" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/04-logined.jpg" height="350" width="200">
</div>

### DApp calling contract

The DApp calling contract process is:

1. Pre-execution contract after user signature
2. The user confirms and sends the transaction
3. Return to the transaction hash to DApp

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/input-password.jpg" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/05-pre-exec-result.png" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/06-dapp-recv-txhash.jpg" height="350" width="200">
</div>
