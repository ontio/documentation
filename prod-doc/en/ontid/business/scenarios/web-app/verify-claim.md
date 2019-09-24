# Web-app - verify claim

1. 根据Singing-SDK 方法 得到二维码参数，通过 ontoAuth Signing server 扫码签名

   * 需要先注册 [获取可信声明](../web-app/action.md) 的Action Name

     ```json
     {
        "domain": "on.ont",
        "enableONS": true,
        "defaultPayer": "AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV",
        "actions": [{
              "type": "claimQuery",
              "onchainRec": false
           },
           {
              "type": "...",
              "onchainRec": false
           },
           {
              "type": "...",
              "onchainRec": true,
              "payer": "AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV",
              "qrcodeUrl": "",
              "callback": ""
           }
        ]
     }
     ```

   * 通过 Singing-SDK [方法](../../../framework/signing-server/sdk/java/javadoc/[README.md](README.md))获取二维码协议参数

     ![a](../../../res/queryClaim.png?lastModify=1568624986)

   2. 签名之后，ontoAuth 调用接口把本地存储的claim发送到web-app[接口及参数说明](../../../framework/trust-anchor/restful-api.md#credential_id)

   * web-app会向TA验证公钥, 并且会向[链上查询](../../../framework/trust-anchor/smart-contract-api.md)claim状态，返回结果

   ```
   {
       "action": "claimCallback",
       "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
       "error": 0,
       "desc": "SUCCESS", // 最终结果
       "version": "v1"
   }
   ```

   至此验证流程完毕

   