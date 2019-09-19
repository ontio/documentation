# Solution for resource-provider

拥有资源的实体，并将资源开放给市场，以资源通过 某种定价体系换取一定的报酬(例如, ONG 或其它某种资源)。此类实体有很多种类，比如数据所有者、算力拥有者、数据收集平台以及具有一定权限的数据托管方，可以称为提供资源的卖家。



#### 准备工作

1. Onto Auth App
2. 注册ontid以及ONS，并通过合约绑定ontid及ONS
   * ontid 可进行Trust Anchor Claim 认证（可选）
3. 通过ONS登陆Marketplace web-app



#### 资源发布

1. 提供资源的具体信息，包括资源的元信息，以及数据的认证方、数据的价格（ONG）等，通过marketplace提供的存储方案进行存储，当然也可以自定义存储方案

   ##### 元数据模板

   ```json
   {
     @context: "http://schema.org",
     @type: Dataset,
     identifier: did:ont:xxxx....,
     name: sample data,
     description: "Just a sample for structured data", 
     keywords: "sample, structured",
     publisher: {
       @type: Person,
       identifier: did:ont:yyyy....,
       name: My Name,
       ...
     },
     datePublished: 2019-01-01T00:00:00Z,
     creator: {...},
     version: 1,
     expires: 2020-02-01T00:00:00Z,
     license: "http://example.license.com/v1",
     ...
   }
   ```

   ##### 示例数据模板

   ```json
   {
     certifier: "did:ont:AMz77J4iuHGmAdw7P9g1CZ7SoL996AdyxC",
     coin: "ONG",
     data:"a",
     dataId: "",
     desc: "test1",
     img: "",
     keywords: ["test1"],
     name: "test1",
     dataSource: "test1",
     ontid: "did:ont:ALfPq6XV9Pa6oDKENunPvwxxaMX8tBiJhA",
     price: 1,
     metadata: {
         @context: "http://schema.org",
         @type: Dataset,
         identifier: 'did:ont:xxxx....',
         name: sample data,
         description: "Just a sample for structured data", 
         keywords: "sample, structured",
         publisher: {
         @type: Person,
         identifier: 'did:ont:yyyy',
         name: My Name,
       },
       datePublished: 2019-01-01T00:00:00Z,
       creator: {...},
     version: 1,
     expires: 2020-02-01T00:00:00Z,
     license: "http://example.license.com/v1"
     }
   }
   ```

   

   数据认证通过后，为数据注册生成DataId，并通过Onto Auth 扫码签名进行上链操作

   通过  Singing-SDK 方法 获取生成二维码参数

   ```js
   let qrStr = singingSdk......
   ```

   

   ​	示例二维码

![a](../../res/ontid_qrcode.png)



2. 为生成Token提供基本字段和数据，比如生成Token数量，调用DToken合约，通过Onto Auth 扫码签名进行上链操作（eshop 模式适用）

   生成Token 所需字段，可参考[合约字段]()

   ```js
   {
     dataId: "did:ont:aaaaaaa", // 数据的ontid
     ontid: ontid, // RP的ontid
     pubKey: 1,
     contractVo: {
       argsList: [{
         name: "account",
         value: "Address:aaaaaaa" // 钱包地址
       }, {
         name: "dataId",
         value: "String:" + dataId // 数据的ontid
       }, {
         name: "ontid",
         value: "String:" + ontid	// RP的ontid
       }, {
         name: "index",
         value: 1
       }, {
         name: "symbol",
         value: "String:aaa"
       }, {
         name: "name",
         value: "String:aaa"
       }, {
         name: "amount",  // Token生成数量
         value: 12
       }, {
         name: 'transferCount',
         value: 12
       }, {
         name: 'accessCount',
         value: 12
       }, {
         name: 'expireTime',
         value: 16121212		// Token 的过期时间
       }],
       contractHash: "06633f64506fbf7fd4b65b422224905d362d1f55",	// 合约哈希
       method: "createTokenWithController",	// 合约方法
     }
   }
   ```

   传递参数，并通过  Singing-SDK 方法 获取生成二维码参数

   ```js
   let qrStr = singingSdk......
   ```

   示例二维码

   ![a](../../res/ontid_qrcode.png)





​		DataId与Token绑定之后，选择上传Token的数量等，进行数据的上传操作

3. 最后确认上传数据到Marketplace

   选择仲裁方，及上架的过期时间等字段，eshop模式下要填写上传的Token数量

   传递参数，并通过  Singing-SDK 方法 获取生成二维码参数

   ```js
   let qrStr = singingSdk......
   ```

   ![a](../../res/ontid_qrcode.png)

   完成之后，可在marketplace中查看上传的数据



#### 收款

1. 三种情况下，需求方可进行收款操作

   * 需求方在挑战期内未进行收货操作

   * 需求方已收货

   * 仲裁之后判定需求方失败

     

   ```js
   {
     argsList: [
     { name: "orderId", 
     value: "ByteArray:" + orderId // 订单ID
     }],
     contractHash: "88da35324f1133aca1f3b728b27fa1f017e6fb8c", // 合约哈希
     method: "confirm"
   }
   ```

   传递参数，并通过  Singing-SDK 方法 获取生成二维码参数

   ```js
   let qrStr = singingSdk......
   ```

   ![a](../../res/ontid_qrcode.png)

   通过之后完成收款操作