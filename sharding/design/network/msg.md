## Msgs


### Handshake

  * version
    * Version
    * Services
    * TimeStamp
    * SyncPort
    * HttpInfoPort
    * ConsPort
    * Cap
    * Nonce
    * StartHeight
    * Relay
    * IsConsensus
    * SoftVersion
    * ShardHeights  map[uint64]*HeightInfo

  * verAck
    * IsConsensus

### PeerAlive

  * ping
    * Height map[uint64]*HeightInfo

  * pong
    * Height map[uint64]*HeightInfo

### Sync
  * blockHeadersReq
    * Len
    * ShardID
    * HashStart Uint256
    * HashEnd Uint256

  * blockHeadersRsp
    * BlkHdr []*Header

  * blockReq
    * HeaderHashCount
    * HashStart Uint256
    * HashStop Uint256

  * blockRsp
    * Blk *Block
    * MerkleRoot

### Consensus
  * InvPayload
    * InvType
    * Blk
    * ShardID

### Transaction
  * Transaction
    * Txn  *Transaction

### Routing
  * AddressReq
  
  * AddressRsp
    * NodeAddrs []PeerAddr
