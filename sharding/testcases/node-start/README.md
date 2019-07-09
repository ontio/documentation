
## Shard Node

In non-shard mode, Ontology node has only one ledger, network module only support one chain.

In shard mode, when node started, it need to initialize multiple ledgers and chains.


### Test cases

* initialize root ledger
* start root ledger syncing
* validate shard ledger with root ledger
* validate pending-Tx-store
* start shard ledger syncing
* start txpool and consensus for shard

