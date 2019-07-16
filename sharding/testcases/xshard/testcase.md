# X-Shard Msg Test Case

* Tx state query
* X-Shard msg query
* X-Shard msg send
* X-Shard msg receive
* Shard tx generate
* Shard tx query

## Case 1, Tx state query

Each tx has a corresponding state, the state store at state db. Users could query txState by using source tx hash.

### Test Procedure

1. Send any tx to any shard;
2. Use tx hash to query tx state.

### Exception

The tx state display as follows:
```
type TxState struct {
	TxID           xshard_types.ShardTxID       // cross shard tx id: userTxHash+notify1+notify2...
	Shards         map[common.ShardID]ExecState // shards in this shard transaction, not include notification
	NumNotifies    uint32
	ShardNotifies  []*xshard_types.XShardNotify
	NextReqID      uint32
	InReqResp      map[common.ShardID][]*XShardTxReqResp // todo: request id may conflict
	PendingInReq   *xshard_types.XShardTxReq
	TotalInReq     uint32
	OutReqResp     []*XShardTxReqResp
	TxPayload      []byte
	PendingOutReq  *xshard_types.XShardTxReq
	PendingPrepare *xshard_types.XShardPrepareMsg
	ExecState      ExecState
	Result         []byte
	ResultErr      string
	LockedAddress  []common.Address
	LockedKeys     [][]byte
	WriteSet       *overlaydb.MemDB
	Notify         *event.ExecuteNotify
}
```

## Case 2, X-Shard msg query

Cross shard msg stored at state store. User could query it by using block height and shardId.

The block height means what height the msg generated at, and the shardId means that what shard the msg should be send to.

### Test Procedure

1. Invoke a tx that ```NotifyRemoteShard``` or ```InvokeRemoteShard```;
2. Query original shard x-shard msg by using different height and destination shard's id for req, prepare, commit msg;
3. Query shard tx at destination shard by using different height and original shard's id for resp, prepared msg;

### Exception

1. The different msg distributed in different block;
2. The query result returned by array format.

## Case 3, X-Shard msg send

X-Shard msg generated at block height ```h``` will be sent while block height ```h+1``` consensus complete. And in the consensus procedure, consensus node sign the msg.

### Test Procedure

1. Send a tx that shard A notify shard B;
2. Wait tx handled, record height ```h```;
3. Query ```h``` x-shard msg, listen shard B is received corresponding msg after shard A ```h``` block consensus complete.

### Exception

1. Block ```h``` at shard A contain this notify msg;
2. Shard B receive msg after the consensus complete, not before it.

## Case 4, X-Shard msg receive

Shard receive x-shard msg from p2p network. In the meantime, before block construct, shard fetch x-shard msg that target shardId is self from parent shard.

Shard use these msg to build shardTx, and package it to block.

Reference to [x-shard notify case 5](../xshard-notify/README.md#case-5-validation-of-cross-shard-message-queue)

## Case 5, Shard tx generate

After receive x-shard msg, msg will be used to generate shard tx. And the shard tx is also generated from parent shard msg that's target shard is self.

### Test Procedure

1. Insure parent shard ledger contains msg that's target shard is self;
2. Insure other shard send msg to self;
3. After block generated, query shard tx num and states.

### Exception

1. Shard tx is a mapping structure, key is sender shard id, value is tx array;
2. Shard tx states is success.

## Case 6, Shard tx query

Using ontology-cli and rpc/rest/ws interface to query shard tx states. Shard tx info is contained in block info, and also can be queried by using tx hash.

In the other, shard tx is derived from source transaction. So using the source tx hash as the param to query shard tx may be better.

### Test Procedure

1. Select one block that contains some shard tx, query its' info by ontology-cli, command is ```./ontology info block [height|hash]```;
2. Send a tx that invoke ```NotifyRemoteShard``` or ```InvokeRemoteShard```, and record its' hash;
3. Wait remote shard execute corresponding shard tx;
4. Using source tx hash to query shard tx info;

### Exception

1. Shard tx info is contained in block info;
2. The corresponding shard tx contract notification is displayed while using source tx hash to query.