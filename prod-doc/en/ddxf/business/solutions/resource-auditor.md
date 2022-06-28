# Solution for resource auditor

For detail and technology support, please contact Ontology dev team.

## 1. Enable resource auditor for resources

需求方生成数据的 dataid 之前，可根据具体情况选定数据认证方，认证方通过 marketplace 提供的 API 可查询到需要认证的数据，然后进行认证。数据认证也可通过Trust Anchor 进行签发Cliam认证（可选），认证之后，需求方可继续进行其他操作。



- 通过marketplace 提供的 [API](../../framework/resource-audit/readme.md) 查询到所需认证的订单数据，认证方判定数据认证的成功和失败API 参数

```js
  {
    orderId: 'orderId',
    isCer: true,
  }
```

​		提交 marketplace [API](../../framework/resource-audit) 进行数据的认证



- 通过 Trust Anchor 进行数据的认证

  具体可参照 [issue claim](../../../ontid/business/scenarios/trust-anchor/issue.md)

  认证成功之后，marketplace 会自动同步认证的数据

## 2. Enable resource audit runtime

