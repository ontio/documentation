
## Chain Manager in Shard

Similiar as ledgers, there're multiple chains in shard node, root-chain and shard-chain.

On node starting, chainmgr is responsible to starting root-chain and shard-chain, 
including initializing their ledger, starting their block-syncer and starting consensus if necessary.

When node started, it's possible that shard has not been activated.  
In this case, chainmgr is responsible for listening <code>Shard Events</code> from <code>shard-mgmt contract</code>, starting shard consensus on necessary.

### Test cases

Testcases of Chainmgr includes:

* initialize shard ledgers
* start syncers
* start shard consensus if necessary

