# Solution for marketplace

For detail and technology support, please contact Ontology dev team.

## 1. Enable marketplace for resources

1. Register on-chain domain to identify the marketplace
   1. ONT ID ready
   2. Default payer ready
   3. Domain in ONS ready
2. Setup a marketplace
   1. Use [`Ontology general marketplace server`](../../framework/marketplace/saas-tenant.md) or deploy a [new one](../../framework/marketplace/deployment.md)
   2. Config marketplace 
3. Use marketplace SDK in web-app
   1. Link to [data storage provider](./data-storage.md)
   2. Enable [`ONT ID`](../../../ontid/business/solutions/web-app/README.md)
4. Choose marketplace [`resource auditors`](./resource-auditor.md) and [`offline judgers`](./resource-judger.md)

## 2. Enable marketplace runtime

1. Enable marketplace for end users
   1. [Resource preparing](../scenarios/resource-preparing.md)
      1. call [resource-data mapping and upload](../scenarios/data-storage/upload.md) in `data storage provider`
      2. get claim from [resource auditor](./resource-auditor.md)
      3. [generate data identifier](../scenarios/data-storage/generate-id.md) for data in `data storage provider`
   2. [Resource publish](../scenarios/resource-publish.md)
      1. choose pay-as-you-go or pre-order model
         - [pay-as-you-go](../scenarios/marketplace/pay-as-you-go.md)
            1. register marketplace to the off-chain data in `data storage provider`
         - [pre-order](../scenarios/marketplace/pre-order.md)
            1. generate DToken to access/transfer/... off-chain data in `data storage provider`
      2. [publish resource](../scenarios/marketplace/publish.md) to marketplace
   3. [Resource transaction](../scenarios/resource-transaction.md)
      1. DToken transfer or DToken/utility-token [exchange](../scenarios/marketplace/exchange.md)
   4. [Resource incentive share](../scenarios/resource-incentive-share.md)
      1. [share](../scenarios/marketplace/share.md) on transactions after certain challenge period
   5. [Transaction evaluation](../scenarios/tx-evaluation.md)
      1. [evaluate](../scenarios/marketplace/evaluate.md)

## 3. Enable reputation score 

- inside marketplace
- cross marketplace
