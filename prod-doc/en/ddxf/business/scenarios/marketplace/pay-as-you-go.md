# Pay as you go mode of marketplace

- RP 预上传数据之后，需要生成 Dataid 实现与数据的绑定
- RP 上传数据（填写生成 Token 所需参数）
  - [可参照](../../solutions/marketplace.md)
- RC 在平台方执行购买操作，同时会包含 Token 的生成，此时 Token 所有权即归 RC 所有
  - [可参照](../resource-publish.md)
- RC 可凭借此 Token 访问资源的元数据
- 购买操作完成时，交易费用均按照流程已分配完成
  - [可参照](../../../framework/marketplace/smart-contract-api.md)

