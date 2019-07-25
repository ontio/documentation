# SHARD CONSENSUS USE VBFT


### sharding consensus mode same as the root chain consensus,but there are some differences in make proposal,endorser and commiter stage.

## consensus process

### 1、Proposal

#### 1、build cross shard msg to blockProposalMsg
#### 2、build shardTx to blockProposalMsg
#### 3、check current parent height,set block parent height
#### 4、sig cross shard msg hash

#### In make proposal stage,you should check is need change consensus,get new chainconfig.

##### 1、get shard commit dpos height from shard ledger
##### 2、if height > last consensus height or current block height - height > maxblockchangeview then get current chainconfig from shard ledger.
##### 3、use new chainfig as next round consensus config info.
##### 4、if this change consensus is periodic switch,then need create new shard gov system tx

#### TestCase

#### 1、get cross shard msg from shardNoify,need check CrossMsgHash is nil
```
type ExecuteResult struct {
	WriteSet    *overlaydb.MemDB
	Hash        common.Uint256
	MerkleRoot  common.Uint256
	Notify      []*event.ExecuteNotify
	ShardNotify []xshard_types.CommonShardMsg
}

type Block struct {
	Block               *types.Block
	EmptyBlock          *types.Block
	Info                *vconfig.VbftBlockInfo
	PrevBlockMerkleRoot common.Uint256
	CrossMsgHash        *types.CrossShardMsgHash
}

type CrossShardMsgHash struct {
	ShardMsgHashs []common.Uint256
	SigData       map[uint32][]byte
}

```
#### 2、check shardTxs is nil
```

type Block struct {
	Header       *Header
	ShardTxs     map[common.ShardID][]*CrossShardTxInfos
	Transactions []*Transaction
}
```

#### 3、check block parent height

#### 4、check CrossShardMsgHash len(SigData) == 0

### 2、Other Consensus Node Verify Proposal

#### 1、compare proposal block parent height with current parent height. if proposal block parent height > current parent height,send p2p req sync proposal block parrent height,util get new block parrent.
#### 2、verify porposal cross shard msg root hash

### 3、 Endorser

#### 1、endorser node need sig cross shard msg hash
#### 2、consensus node receive other endorser node cross shard msg sig,save the msg to block pool

#### TestCase 

#### 1、check cross shard msg sigData > 1
#### 2、check receive cross shard msg from other endorser node


### 4、Commiter 

#### 1、commiter node sig cross shard msg
#### 2、consensus node receve other commiter node cross shard msg sig
#### 3、check total cross shard msg hash sig > (2/3)*len(consenusNode number)

### TestCase

#### 1、check cross shard msg sigData > 1
#### 2、check total cross shard msg hash sig > 2/3

### 5、SealBlock 

#### 1、save block to chainstore
#### 2、save cross shard msg to cross shard db by key hashRoot
#### 3、p2p send to cross shard msg to target shard

### TestCase 

#### 1、check cross shard msg sigData number
#### 2、check hashRoot consistency
#### 3、check cross shard db has save the cross shard msg
#### 4、check p2p send succ

