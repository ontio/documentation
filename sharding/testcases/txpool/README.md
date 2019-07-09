
## Shard Transaction Pool

Shard node just processes transactions in the shard, and cross-shard transactions to the shard.
All other transactions in the shard network will be ignored by shard node.

There's only one transaction pool with shard node.  Its function keeps simliar with non-shard node.

### Test cases

* validate all transactions in shard
* drop all other transactions
* provide un-consensused transactions to consensus module
