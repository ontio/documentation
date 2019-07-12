
## Cross Shard Invocation

Cross shard invocation is to support synchronous cross-shard transaction.
It can support cross shard atomic transaction.

The atomicity is based on verifiable cross-shard message queue and 2PC protocol. Please reference sharding paper for details.

### Test cases

* cross shard REQ
* cross shard RSP
* cross shard Tx pending state management
* 2PC commit protocol
* smart contract locking on committing
* smart contract should not be invoked when its locked
* shard-asset contract is locked based on user account
* remote-Invoke triggered by remote notification
* no data commit if transaction is aborted
* cross shard Tx commit once and only once
* cross shard Tx pending state is not visible to other transactions

