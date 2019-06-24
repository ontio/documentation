## Sharding Network Design


Requirements:

* Multiple SubNetwork
  * Consensus
  * Shard
  * Auto-configured SubNetwork
      * Candidate <--> Consensus
* NeighTable for Root and Shard
* Block Propagation (from consensus to sync)
* Tx Propagation (from sync to consensus)
* Shard-Tx Propagation (cross shard subnet)
* Consensus-Msg relay
  * Consensus Network
* Node discovery
  * Find peer with peer-pk
* Connection Management
  * per-peer connection
  * connection should be shared with multi-subnet
* Memory Management
  * msg throttling
* Security
  * Randomized PeerID
* NAT
* Performance vs Msg-Duplication


### Role of Peer

from role:

* Consensus
* Sync

from shard:

* shard ID

### SubNetwork

SubNetwork for each role of Peer.

Function requirements of SubNetwork:

* subnet = (shardId, role), role = (consensus, sync)
* In-subnet broadcasting
* Cross-subnet msg broadcasting
* open subnet vs. contract-managed subnet

### Routing

associated with subnet.

* Gossip-based routing
* NeighTable
* Discovery
  * Contract-managed member
  * open subnet

### ConnectionMgmt

Support for all subnets.

* peer handshake
* subnet join/leave protocol
* 

### Message

* Handshake
  * version
  * verAck
* PeerAlive
  * ping
  * pong
* Sync
  * blockHeadersReq
  * blockHeadersRsp
  * blockReq
  * blockRsp
* Consensus
  * InvPayload
* Transaction
  * Transaction
* Routing
  * AddressReq
  * AddressRsp

