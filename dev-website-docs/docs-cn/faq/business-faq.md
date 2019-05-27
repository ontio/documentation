

#### 1. 如何发币

1. 参考智能合约模板[合约模板](https://dev-docs.ont.io/#/docs-cn/smartcontract/02-template)



#### 2. 链改说明

游戏方链改：为每个用户创建一个区块链地址，与现有账户的绑定关系记录在数据库中，每个地址的私钥可以保存在数据库或使用我们的签名机托管。如果用户充值，就给用户打币，用户余额可以通过浏览器API接口查询到或调用合约接口查。

去中心化登录：如果游戏是H5，对接我们的dAPI，dAPI 已经在多款手机钱包和Chrome 插件钱包Cyano中支持。通过 dAPI 可以获取到用户当前使用的钱包的地址。通过 dAPI 可以发消息给钱包，用户用钱包对消息做签名，游戏方验证签名通过就认为用户登录成功。

去中心化支付：如果游戏是H5，根据 dAPI 协议用户通过钱包调用合约，游戏方后台需要通过同步合约数据知道用户的操作行为，包括转账信息。


#### 3. DAPP 对接 DAPI

1. 分别支持chrome 插件和移动版本dAPI

详细请参考[钱包对接指南](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/00-dapp_integration)

#### 4. 钱包对接

1. 支持 ONT/ONG 转账
2. 移动版本钱包支持 DAPI 协议
3. 支持 OEP4 资产

详细请参考[钱包对接指南](https://dev-docs.ont.io/#/docs-cn/Wallet-Integration/00-wallet_integration)


#### 5. 交易所对接

[交易所对接](https://dev-docs.ont.io/#/docs-cn/exchange-API/Ontology-%E4%BA%A4%E6%98%93%E6%89%80%E5%AF%B9%E6%8E%A5%E6%96%87%E6%A1%A3)


#### 6. DAPP Store 对接

[DAPP Store 对接指南](https://dev-docs.ont.io/#/docs-cn/dapps/overview)


#### 7. 游戏方对接步骤

对接步骤：
1. 对接dApi协议: [https://dev-docs.ont.io/#/docs-cn/dApp-Integration/01-DAppDocking-Wallet-Opens-DApp](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/01-DAppDocking-Wallet-Opens-DApp)
2. 通过getAccount获取钱包地址，invoke接口调用合约完成支付。测试钱包：[http://101.132.193.149/files/app-debug.apk](http://101.132.193.149/files/app-debug.apk)
3. 游戏方后台根据合约地址查询用户支付记录。[https://dev-docs.ont.io/#/docs-cn/explorer/contracts](https://dev-docs.ont.io/#/docs-cn/explorer/contracts)

资料：
1. dapp demo： [https://github.com/ontio-cyano/mobile-dapp-demo](https://github.com/ontio-cyano/mobile-dapp-demo)
2. 测试币申请：[https://developer.ont.io/applyOng](https://developer.ont.io/applyOng)
3. 智能合约开发 IDE ： [https://smartx.ont.io/#/](https://smartx.ont.io/#/)

合约开发：
1. 使用 smartx 开发合约: [https://dev-docs.ont.io/#/docs-cn/QuickGuide/00-dapp_development?id=%E5%90%88%E7%BA%A6%E5%BC%80%E5%8F%91](https://dev-docs.ont.io/#/docs-cn/QuickGuide/00-dapp_development?id=%E5%90%88%E7%BA%A6%E5%BC%80%E5%8F%91)
2. 参考合约模板支付 ONG 。[https://github.com/ONT-Avocados/python-template/blob/master/NativeAssetInvoke/native_asset_invoke_compiler2.0.py](https://github.com/ONT-Avocados/python-template/blob/master/NativeAssetInvoke/native_asset_invoke_compiler2.0.py)
3. 建议先在测试网测试，再在主网测试。