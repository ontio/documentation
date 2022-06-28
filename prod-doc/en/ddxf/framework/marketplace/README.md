# Marketplace

## Roles and components

角色定义遵从 GREP 描述。

1. 资源准备
   1. 资源信息化（信息化安全存储）
   2. 资源数据特征抽取
2. 资源（marketplace）发布
   1. 资源审核
   2. 资源交换元数据对齐
   3. 交易合约确定
   4. 违约保证金缴纳
3. 交易
   1. 需求确认，资源加工工作流预设
   2. 资源整合和撮合，生成交易
      1. 用户委托和数据特征撮合
      2. 合约订单生成
   3. 执行交易
      1. 合约工作流驱动，数据加工、资源交换和数据交互
4. 即时结算和纠纷仲裁

在实际使用过程中，根据交易特征和资源类型设计专属市场，根据实际情况对功能组件进行组合，实现资源市场的搭建。

## Host resource exchange

1. [Deploy a marketplace](./deployment.md)
   - Use [`Ontology general marketplace`](./saas-tenant.md) (SaaS) to run your own marketplace
2. [Marketplace RESTful api](./restful-api.md)
   - [Smart contract api](./smart-contract-api.md) for marketplace
3. [Marketplace SDK - java](./sdk/java/javadoc/README.md)
4. Choose [scenarios](../../business/scenarios/README.md) to for the marketplace
5. Follow the workflow of the marketplace

