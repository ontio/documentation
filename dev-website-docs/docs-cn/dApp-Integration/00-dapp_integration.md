
# DApp 接入说明

本系列接入文档主要介绍了目前提供的两种DApp接入方式，两种接入方式都可以实现登录，调用智能合约的功能，开发者可以选择其中一种进行DApp接入。

- [ONT ID 开放平台接入](docs-cn/dApp-Integration/08-ontid_integration.md)
- [DApi 接入](docs-cn/dApp-Integration/09-dapi_integration.md)


## ONT ID 开放平台接入

ONT ID 开放平台为第三方应用提供第三方登录、支付、智能合约执行、KYC等服务。

网站应用 ONTID 登录是类似于 `OAuth2.0` 协议标准构建的 ONTID 授权登录系统。

在进行 ONTID 授权登录接入之前，应用方需要先在 ONTID 开放平台注册 ONTID ，获得相应的 ONTID 和 `PrivateKey`，申请 ONTID 通过审核后，可开始接入流程。

ONT ID 开放平台的优势在于，采用可信任的托管模式后，用户登录DApp将不再依赖于用户本地的钱包，大大扩展了DApp的使用范围。

## DApi 接入

介绍了 DApp 如何在各种场景下调用 DApi，实现包括登录，调用智能合约等操作。

与传统 App 不同，DApp 没有一个中心化的账号管理后台，用户完全掌控自身的身份和资产，所以 DApp 除了通过智能合约构建自己的业务逻辑，也需要通过各种方式和链进行交互。为了降低 DApp 开发难度，我们提供了丰富的 DAPI 或方法用于DApp 与链交互，适用于当前所有主流设备中使用 DApp 的场景。

DApi 接入的优势在于，去中心化程度更高，用户可以较为便利地使用已有的钱包登录DApp。