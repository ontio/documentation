# Solution to offer claim

Tech document is way behind. For detail and technology support, please contact Ontology dev team.

## 1. Claim offering

1. Register on-chain domain to identify the credential service provider
   1. ONT ID ready
   2. Default payer ready
   3. Domain in ONS ready
2. Setup a trust anchor
   1. Use [`Ontology general trust anchor`](../../framework/trust-anchor/saas-tenant.md) or deploy a [new one](../../framework/trust-anchor/deployment.md) 
   2. Config claim template
3. Provide [claim service](../scenarios/trust-anchor/issue.md)
   - Log claim action on-chain if necessary
4. Enable [claim verification](../scenarios/trust-anchor/verify.md) (for client use only)
5. Done

