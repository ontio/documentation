
## 概述
钱包接入分成两个层次
- [资产功能集成](https://dev-docs.ont.io/#/docs-cn/Wallet-Integration/01-WalletDocking-asset-docking)
- [provider sdk集成](https://dev-docs.ont.io/#/docs-cn/Wallet-Integration/02-WalletDocking-provider-sdk-docking)

![wallet-integration](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/wallet-integration.png)

完成两层集成后，就可以进行场景使用接入


### 资产功能集成

资产功能集成是钱包集成的基础，钱包App集成ONT的SDK，配合公开的浏览器接口后就能实现数字资产操作，账号管理等功能，满足数量庞大的本体社区成员基本的资产管理需求。

![接入说明](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/sdk.png)

资产功能集成后，钱包可以提供以下功能：
-  与链交互
-  账号
-  数字资产
-  数字身份
-  节点质押

### provider sdk集成

资产功能集成完成后，钱包可以选择进行provider sdk集成，这是本体提供给钱包App的拓展选择，集成成功后，钱包App可以支持一系列的本体dApp，从而增加用户黏性，坐享本体生态中日益丰富的dApp带来的流量红利。

![接入说明](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/provider-sdk.png)

provider sdk集成完成后可以提供dApp使用多种应用场景的支持
- 扫码登录，转账，调用智能合约
- 钱包内打开，登录，转账，调用智能合约
- 网页版打开，登录，转账，调用智能合约

基本上涵盖了目前主流的dApp的应用场景需求，在本体生态中的dApp都将根据统一标准开发，这也就意味着，只要钱包App集成provider sdk后，就可以接入各种各样的本体dApp，而不是费时费力进行逐一对接，大大节约开发上线时间。
