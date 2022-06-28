# Solution for web-app

Tech document is way behind. For detail and technology support, please contact Ontology dev team.

## 1. Enable self-sovereign account to buy in more stakeholders

1. Register on-chain domain to identify the web-app
   1. ONT ID ready
   2. Default payer ready
   3. Domain in ONS ready
2. Setup a signing server
   1. Use [`Ontology general signing server`](../../framework/signing-server/saas-tenant.md) or deploy a [new one](../../framework/signing-server/deployment.md) 
   2. Config web-app actions with signing server one by one
3. Use signing SDK in web-app
   1. Map account in web-app with ONT ID
   2. [optional] enable ONS on sub-domain for account
4. Register new actions to be record on-chain
5. Enable registration and login with signing SDK
   1. [register](../scenarios/web-app/register.md)
   2. [login](../scenarios/web-app/login.md)
   3. [on-chain actions](../scenarios/web-app/action.md)
6. Done

### 1.1 Workaround for centralized identities

1. Register on-chain domain to identify the web-app
2. Have `root key` ready for "delegated ONT IDs"
3. Enable [actions](../scenarios/web-app/centralized-id.md) with signing SDK
   1. register 
      1. Generate `ONT ID` for end users after the `root key`
      2. Map `ONT ID` with user account
      3. Sign with `root key`  and publish to Ontology mainnet for on-chain registration, if necessary
   2. login
      1. Common login
      2. Query `ONT ID` with user account
      3. Sign with `root key`  and publish to Ontology mainnet for on-chain login, if necessary
   3. on-chain actions
      1. Query `ONT ID` with user account
      2. Sign with `root key`  and publish to Ontology mainnet for on-chain action
4. Done

## 2. Enable qualification filtering on customer registration

1. Use claim system (trust anchor) SDK in server side
2. Create claim template to use
3. Add claim query on the first step of user registration, enable [claim verification](../scenarios/web-app/verify-claim.md)
   1. claim verificaton passed, 
   2. move on to the next step
4. Done

## 3. Share high value customers with lower cost over network

1. Define the cost model of customer acquisition and publish
   - [>>> Learn more.](../../../ddxf/business/solutions/mp/id.md)
2. Generate claim template and forward to claim store
3. Wait for new customers to give a try
4. Done

## 4. A new business to offer credential of qualified users

[>>> Learn more.](./claim.md)

