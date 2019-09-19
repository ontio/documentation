# Solution for offline-judger

资源提供者和资源需求者在资源交易中都认可的链下纠纷仲裁者。链下产生的纠纷(如资源没有获取到)将由链下仲裁者进行裁定。

仲裁包含四部分

- 仲裁方
- 仲裁方案
- 执行结果
- 仲裁合同本身

由资源需求者提出数据的仲裁，仲裁方根据Marketplace 提供的API 查询到所需仲裁的数据，根据签订的仲裁合同中的仲裁方案发布执行结果。



#### 仲裁执行

1. 通过marketplace 提供的 API 查询到所需仲裁的订单数据，仲裁方根据仲裁合约判定仲裁的成功和失败，并进行合约的上链操作

   合约示例参数

   ```js
   {
     "argsList": [
     { "name": "orderId", 
      "value": "ByteArray:" + data.orderId // 订单数据的ID
     },
     { "name": "isWin", 
      "value": true // 判定结果 true or false
     }],
     "contractHash": "88da35324f1133aca1f3b728b27fa1f017e6fb8c",
     "method": "arbitrage"
   }
   ```

   传递SDK 所需 参数，通过  Singing-SDK 方法 获取生成二维码参数

   ```js
   let qrStr = singingSdk......
   ```

   

   示例二维码

   ![a](../../res/ontid_qrcode.png)

   仲裁完成之后，资金会根据结果自动发送到双方（需求方和提供方）的钱包，双方亦可根据marketplace API 查询到订单状态（包含仲裁结果）