# Solution for resource-consumer

资源提供者的交易对手方，是需要某种资源的实体，从资源提供者中获取资源的(部分)所有权或者使用权，并为此支付一定的报酬(例如 ONG)。



#### 准备工作

1. Onto Auth App
2. 注册ontid以及ONS，并通过合约绑定ontid及ONS
   - ontid 可进行Trust Anchor Claim 认证（可选）
3. 通过ONS登陆Marketplace web-app



#### 购买操作流程

1. 选择需要购买的数据，进行下单操作

   选择仲裁方以及购买Token的数量（eshop模式需要）

   [合约所需参数]()

   ```js
    {
      argsList: [
      { name: "orderId", "value": 
       "ByteArray:" + this.orderData.orderId  // 订单ID
      },
      { name: "takerReceiveAddress", 
       "value": "Address:" + this.address // 付款地址
      },
      { name: "txFeeTokenHash", 
       "value": "ByteArray:0000000000000000000000000000000000000002"  // 币种哈希
      },
      { name: "txFeeAmount", 
       "value": this.orderData.price * Math.pow(10, 9) * 0.1 // 所需费用
      },
      { name: "OJ", 
       "value": "Address:" + this.OJlist.substring(8)  // 仲裁方ontid
      }
      ],
      contractHash: "88da35324f1133aca1f3b728b27fa1f017e6fb8c", // 合约地址
      method: "takeOrder"
    }
   ```

   传递SDK 所需 参数，通过  Singing-SDK 方法 获取生成二维码参数

   ```js
   let qrStr = singingSdk......
   ```

   示例二维码

   ![a](../../res/ontid_qrcode.png)

   



2. 通过marketplace 提供的[API]() 可查到自己所买的数据订单

   凭借Token 查看数据元信息

   示例合约参数

   ```js
   {
     argsList: [
     { name: 'tokenId', 
      value: data.tokenId // Token 
     }
     ],
     contractHash: "06633f64506fbf7fd4b65b422224905d362d1f55", // 合约哈希
     method: "consumeToken"
   }
   ```

   传递SDK 所需 参数，通过  Singing-SDK 方法 获取生成二维码参数

   ```js
   let qrStr = singingSdk......
   ```

   示例二维码

   ![a](../../res/ontid_qrcode.png)



3. 若数据不符，需求方可进行申请仲裁操作

   示例合约参数

   ```js
   {
     argsList: [
       { name: "orderId", 
        value: "ByteArray:" + data.orderId }, // 订单ID
       { name: "arbitrageFee", 
        value: data.price * 0.05 // 仲裁费用
       }
     ],
     contractHash: "88da35324f1133aca1f3b728b27fa1f017e6fb8c",
     method: "applyArbitrage"
   }
   ```

   传递SDK 所需 参数，通过  Singing-SDK 方法 获取生成二维码参数

   ```js
   let qrStr = singingSdk......
   ```

   示例二维码

   ![a](../../res/ontid_qrcode.png)

   完成之后，等待仲裁结果，[仲裁细节]()



4. 数据符合，需求方可进行收货操作

   示例合约参数

   ```js
   {
     argsList: [
     { name: "orderId", 
      value: "ByteArray:" + data.orderId // 订单ID
     }],
     contractHash: "88da35324f1133aca1f3b728b27fa1f017e6fb8c",
     method: "confirm"
   }
   ```

   传递SDK 所需 参数，通过  Singing-SDK 方法 获取生成二维码参数

   ```js
   let qrStr = singingSdk......
   ```

   示例二维码

   ![a](../../res/ontid_qrcode.png)

   确认之后，至此购买流程结束