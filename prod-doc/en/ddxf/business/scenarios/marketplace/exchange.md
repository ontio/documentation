# DToken-utility token exchange

#### 生成Token

eshop 模式下，正式上传数据之前，为生成Token提供基本字段和数据，比如生成Token数量，调用DToken合约，通过Onto Auth 扫码签名进行上链操作

可参考[合约字段](../../../framework/data-storage/smart-contract-api.md)

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

通过  marketplace 提供的 [API](../../../framework/data-storage/restful-api.md#生成tokenId) 或 SDK 方法获取二维码参数

示例二维码

![a](../../../res/ontid_qrcode.png)

再通过 [API](../../../framework/data-storage/restful-api.md#查询生成的tokenId及结果) 查询生成结果

DataId与Token绑定之后，选择上传Token的数量等，正式进行数据的上传操作



#### Token 及数据资源的购买

RC 选择需要购买的数据，仲裁方以及购买Token的数量，进行下单操作，data模式下，会在购买时生成对应的Token，购买完成后 Token 的所有权归 RC 所有。