
## Shard Smart Contract Management

From shard design, shard smart contracts are deployed on root shard, and processed on child shard.

Smart contract on shard support two mode:
* one-shard
* all-shard

For one-shard smart contract, it can only be processed by contract-owner configured shard.

For all-shard smart contract, it must be based on account-model, and derived from shard-asset system contract.  It can be processed by all shards.

All the above requires smart-contract configuration management.  Smart Contract Management is responsable to manage metadata of shard smart contracts.

### Test cases

* all smart contract deployed on root shard
* smart contract config management : change shard, change owner, freeze/unfreeze, upgrade/migration
* smart contract destruction
* all-shard contracts run on every shard
* one-shard contracts run on designated shard
* all-shard contracts can be locked by user-account
* smart-contract on different shard can not be inline-invoked
