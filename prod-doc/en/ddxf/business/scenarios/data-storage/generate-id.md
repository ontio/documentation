# Generate data identifier for data and resource(s)

通过 MP 提供的 [API](../../../framework/data-storage/restful-api.md#注册dataId) 或者 MP-SDK 方法为数据生成DataId，通过Onto Auth 扫码签名进行上链操作，API 或 SDK 方法会返回生成二维码参数

示例二维码

![a](../../../res/ontid_qrcode.png)

再通过 marketplace 提供的 [API](../../../framework/data-storage/restful-api.md#查询注册的dataId及结果) 接口或 SDK 方法，查询是否成功，成功之后，平台方需自己进行 dataid 与 数据资源的绑定