
## Cross Shard Notification

Cross Shard Notification is to support smart contract in shard to invoke smart contract in another shard asynchronously.

Because it is asynchronous, transaction in another shard will be another transaction, and smart contract A which triggered the notification will not be able to get its result.

Cross-Shard notification is based on verifiable cross-shard message queue.
If two cross-shard notification created by one block, and they have same target shard, target shard will process the two notifications in same order with source shard.

### Test cases

* root -> shard notification
* shard -> root notification
* shard -> shard notification
* relay of cross-shard notification message
* validation of cross-shard message queue
* no cross-shard notification if its parent transaction failed or aborted
