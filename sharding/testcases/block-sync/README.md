
## Block Syncing in Shard

For shard, there'll be multiple ledgers, root-ledger and shard-ledgers.
to keep syncing of their ledgers, shard nodes will start multiple block-syncers, one syncer per ledger.

* Root Syncer : syncing for root ledger
* Shard Syncer : syncing for shard ledger

Because there's dependency between shard-ledger and root-ledger, there's dependency among their syncers.

When shard-syncer failed <code>Add-Block</code> with <code>ErrNoParentBlock</code>, shard syncer should stop and wait until root-syncer catched up.

### Test cases

Testcases of BlockSyncing includes at least:

* Root-Ledger block syncing
* Shard-Ledger block syncing
* Starting Root-ledger syncer on node starting
* Starting Shard-ledger syncer after shard-actived
* process sync-request from shard consensus, to wait root-syncer
* process sync-request from shard-syncer, to wait root-syncer

