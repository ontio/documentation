
## Shard Network

Shard Network is a multi-layered network, or multiple sub-network.
Each peer in shard has to be in multiple network, root network and shard network.

Some peer may participant with multiple shard.  They will be in multiple sub-network, and in each sub-network, they will have different neighbors.

For sharding, transactions in one shard should only be broadcasted in the given sub-network.
Cross-shard transactions should be relayed to target shard sub-network.

### Test cases

Testcase of shard network includes:

* peer keep alive in shard subnetwork
* transaction broadcasting in shard subnetwork
* syncing/consensus message broadcasting in shard network
* cross-shard transaction relays
* network isolation
