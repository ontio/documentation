# Solution for resource-auditor

具有一定权威性的第三方，拥有自己的资源质量认证体系，根据该体系可以给资源或者资源提供者提供一定方式的认证增强资源或者资源提供者的可信度。认证根据不同的模式可以收取或者不收取认证费用。与没有经过认证的资源相比，经过认证的资源会拥有更多的潜在买家以及可能获得更高的报酬。



#### 数据认证

需求方生成数据的 dataid 之前，可根据具体情况选定数据认证方，认证方通过 marketplace 提供的 API 可查询到需要认证的数据，然后进行认证。数据认证也可通过Trust Anchor 进行签发Cliam认证（可选），认证之后，需求方可继续进行其他操作。

1. 通过marketplace 提供的 [API]() 查询到所需认证的订单数据，认证方判定数据认证的成功和失败

   API 参数

   ```js
   {
     orderId: 'orderId',
     isCer: true,
   }
   ```

   提交 marketplace [API]() 进行数据的认证

   

2.  通过 Trust Anchor 进行数据的认证

   具体可参照 [issue claim](../../../ontid/business/scenarios/trust-anchor/issue.md)

   认证成功之后，marketplace 会自动同步认证的数据



