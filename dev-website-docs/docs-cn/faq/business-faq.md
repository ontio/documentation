

#### 如何发币

1. 参考智能合约模板[合约模板](https://dev-docs.ont.io/#/docs-cn/smartcontract/02-template)



#### 链改说明

游戏方链改：为每个用户创建一个区块链地址，与现有账户的绑定关系记录在数据库中，每个地址的私钥可以保存在数据库或使用我们的签名机托管。如果用户充值，就给用户打币，用户余额可以通过浏览器API接口查询到或调用合约接口查。

去中心化登录：如果游戏是H5，对接我们的dAPI，dAPI 已经在多款手机钱包和Chrome 插件钱包Cyano中支持。通过 dAPI 可以获取到用户当前使用的钱包的地址。通过 dAPI 可以发消息给钱包，用户用钱包对消息做签名，游戏方验证签名通过就认为用户登录成功。

去中心化支付：如果游戏是H5，根据 dAPI 协议用户通过钱包调用合约，游戏方后台需要通过同步合约数据知道用户的操作行为，包括转账信息。


#### DAPI 对接

1. 分别支持chrome 插件和移动版本dAPI

详细请参考[钱包对接指南](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/00-dapp_integration)

#### 钱包对接

1. 支持 ONT/ONG 转账
2. 移动版本钱包支持 DAPI 协议
3. 支持 OEP4 资产

详细请参考[钱包对接指南](https://dev-docs.ont.io/#/docs-cn/Wallet-Integration/00-wallet_integration)


#### 交易所对接

[交易所对接](https://dev-docs.ont.io/#/docs-cn/exchange-API/Ontology-%E4%BA%A4%E6%98%93%E6%89%80%E5%AF%B9%E6%8E%A5%E6%96%87%E6%A1%A3)


#### DAPP Store 对接

[DAPP Store 对接指南](https://dev-docs.ont.io/#/docs-cn/dapps/overview)