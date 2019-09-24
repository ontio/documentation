# Web-app - centralized identity

1. Generate `root key` for "delegated ONT IDs"
   1. // TODO：api in signing SDK
2. Enable actions with signing SDK
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
3. Hand centralized `ONT ID` back to the identity owner
   1. change the  `Owner` of `ONT ID` DDO from web-app to the end user
      1. [add user key](../../../framework/spec/ontid.md#addKey)
      2. [remove web-app key](../../../framework/spec/ontid.md#removeKey)

