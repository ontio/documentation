

钱包接入可分为两个层次：
- [资产功能集成](https://dev-docs.ont.io/#/docs-cn/Wallet-Integration/01-WalletDocking-asset-docking)
- [provider sdk 集成](https://dev-docs.ont.io/#/docs-cn/Wallet-Integration/02-WalletDocking-provider-sdk-docking)

![wallet-integration](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/wallet-integration.png)

完成两层集成后，就可以进行场景使用接入。

你可以使用测试网和主网测试是否接入成功。

### 资产功能集成

资产功能集成是钱包集成的基础，钱包 App 集成 ONT 的 SDK，配合公开的浏览器接口就能实现数字资产操作，账号管理等功能，满足数量庞大的本体社区成员基本的资产管理需求。

![接入说明](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/sdk.png)

资产功能集成后，钱包可以提供以下功能：
-  与链交互
-  账号
-  数字资产
-  数字身份
-  节点质押

### provider sdk 集成

资产功能集成完成后，可以选择对钱包进行 provider sdk 集成。由于本体生态中的 DApp 都将根据统一标准开发，钱包 App 集成 provider sdk 后就可以接入各种各样的本体 DApp ，无需逐一对接，大大节约开发上线时间。

![接入说明](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/provider-sdk.png)

钱包完成 provider sdk 集成后，支持以下主流的 DApp 应用场景：
- 扫码登录，转账，调用智能合约
- 钱包内打开，登录，转账，调用智能合约
- 网页版打开，登录，转账，调用智能合约

### 测试 DApp 链接
完成集成后，可以在钱包内打开以下链接，测试是否成功完成了接入：

测试网 DAPP：
`http://101.132.193.149:5000/#/`

主网 DAPP：
`https://ont.bet/`