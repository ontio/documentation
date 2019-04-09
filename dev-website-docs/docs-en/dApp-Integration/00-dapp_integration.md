
# DApp Integration instructions

This series of access documents mainly introduces how DApp calls DAPI in various scenarios to implement operations such as login and smart contract.

Unlike traditional apps, DApp does not have a centralized account management backend, and users have full control over their identities and assets, so DApps need to interact with each other in a variety of ways, in addition to building their own business logic through smart contracts. In order to reduce the difficulty of DApp development, we provide a rich DAPI or method for DApp and chain interaction, suitable for scenarios where DApp is used in all current mainstream devices.

The following scenarios are currently supported:

- [Open DApp in mobile wallet](https://dev-docs.ont.io/#/docs-en/dApp-Integration/01-DAppDocking-Wallet-Opens-DApp)
- [Use mobile wallet to scan code](https://dev-docs.ont.io/#/docs-en/dApp-Integration/02-DAppDocking-QRcode)
- [Use chrome plugin wallet](https://dev-docs.ont.io/#/docs-en/dApp-Integration/03-DAppDocking-use-chrome-extension-wallet)
- [Wake Up Mobile Wallet](https://dev-docs.ont.io/#/docs-en/dApp-Integration/06-DAppDocking-Wake-up)
- [Open DApp in desktop wallet](https://dev-docs.ont.io/#/docs-en/dApp-Integration/07-DAppDocking-use-desktop-wallet)


For the integration of DAPI-enabled wallets such as [Math Wallet](http://www.mathwallet.org/en/) and [Onion](http://onion.fun/), please refer to the corresponding docking document. For details of the agreement, please see [CEP1](https://github.com/ontio-cyano/CEPs/blob/master/CEPS/CEP1.mediawiki).

Demo wallet download address: http://101.132.193.149/files/app-debug.apk

## Wallet demo

Mobile version Cyano wallet source link address：[cyano-android](https://github.com/ontio-cyano/cyano-android),[cyano-ios](https://github.com/ontio-cyano/cyano-ios).

H5 DApp example source code: [mobile-dapp-demo](https://github.com/ontio-cyano/mobile-dapp-demo).


### Open DApp in the wallet

Open DApp in the wallet：http://101.132.193.149:5000/#/

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

### DApp Login

If the user identity needs to be verified, the DApp will send a message to the wallet to sign and then verify the signature.

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/01-open-dapp.png" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/03-login-pwd.png" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/04-logined.jpg" height="350" width="200">
</div>

### DApp Invoke SC

The calling contract process is:

1. Pre-execution contract after user signature
2. The user confirms and sends the transaction
3. Return the transaction hash to DApp

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/input-password.jpg" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/05-pre-exec-result.png" height="350" width="200">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/ios/06-dapp-recv-txhash.jpg" height="350" width="200">
</div>
