# Solution for offline judger

For detail and technology support, please contact Ontology dev team.

## 1. Enable offline judger for resources

仲裁包含四部分

- 仲裁方
- 仲裁方案
- 执行结果
- 仲裁合同本身

由资源需求者提出数据的仲裁，仲裁方根据Marketplace 提供的API 查询到所需仲裁的数据，根据签订的仲裁合同中的仲裁方案发布执行结果。



#### 仲裁执行

1. 通过marketplace 提供的 API 查询到所需仲裁的订单数据，仲裁方根据仲裁合约判定仲裁的成功和失败，并进行合约的上链操作

   通过 marketplace 提供的 [API](../../../framework/marketplace/restful-api.md#仲裁) 传递所需参数，并返回二维码字符串

   示例二维码

   ![a](../../res/ontid_qrcode.png)

   

   

   

   仲裁完成之后，资金会根据结果自动发送到双方（需求方和提供方）的钱包，双方亦可根据marketplace API 查询到订单状态（包含仲裁结果）

## 2. Enable offline judgement runtime

