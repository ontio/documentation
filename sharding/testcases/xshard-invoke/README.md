
# Cross Shard Invocation

Cross shard invocation is to support synchronous cross-shard transaction.
It can support cross shard atomic transaction.

The atomicity is based on verifiable cross-shard message queue and 2PC protocol. Please reference sharding paper for details.

## Test cases

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

### Case 1, cross shard REQ

Use the [example code](https://github.com/qiluge/ontology-xshard-contract/blob/master/xshardcall/xshardcaller.py#L61) to ```InvokeRemoteShard```, and you can also construct cross-shard request by manual code.

#### Test Procedure

1. Invoke example contract method, waited tx handled, record handled block height ```h```;
2. Use ```h``` to generate key to query x-shard request at state store.

#### Exception

The request can be read, and decode it as follows:
```
type ShardMsgHeader struct {
	ShardTxID     ShardTxID
	SourceShardID common.ShardID
	TargetShardID common.ShardID
	SourceTxHash  common.Uint256
}
type XShardTxReq struct {
	ShardMsgHeader
	IdxInTx  uint64
	Contract common.Address
	Payer    common.Address
	Fee      uint64
	GasPrice uint64
	Method   string
	Args     []byte
}
```

### Case 2, cross shard RSP

After case 1, the target shard received the request and handle it. The handled result is x-shard response msg. Similarly with x-shard request. the response msg also store at state store.

#### Test Procedure

1. After shard receive x-shard req, wait it handled, record this block height ```h```;
2. Use ```h``` to generate key to query x-shard request at state store.

#### Exception

The response could be read and decode it as follows:
```
type XShardTxRsp struct {
	ShardMsgHeader
	IdxInTx uint64
	FeeUsed uint64
	Error   bool
	Result  []byte
}
```

### Case 3, cross shard Tx pending state management

When the source tx invoke remote shard, the tx state is pending in fact, but while you query its' states, the chain return err until the ```InvokeRemoteShard``` is normal ended.

#### Test Procedure
1. After case 1, query source tx at original shard;
2. After case 2, wait x-shard invoke ended, query source tx at original shard.

#### Exception

Source tx states is err firstly, and then changing to normal after the x-shard invoke result return.

### Case 4, 2PC commit protocol

After original shard receive resp msg, the 2pc protocol start to run. If resp has no err, the normal protocol processes start up, that is prepare->prepared->commit.
And if resp has err, the err handle processes start up, that is original send abort msg to destination shard to drop x-shard invoke result.

#### Test Procedure

1. After case 2, if resp contains error, original shard will sent abort msg to destination shard;
2. Wait abort msg handled, record block height ```h1``` at destination shard;
3. After case 2, if resp contains no error, original shard will sent prepare msg to destination shard;
4. Wait prepare msg handled, record block height ```h2``` at destination shard;
5. Destination shard sent prepared msg to original shard, wait it handled, record height ```h3``` at original shard;
6. Original shard sent commit msg to destination shard, wait it handled, record height ```h4``` at destination shard;

#### Exception

1. Use ```h1``` to query msg, and decode it as follows:
```
type XShardAbortMsg struct {
	ShardMsgHeader
}
```

2. Use ```h2, h3, h4``` to query msg, and decode it as follows:
```
type XShardPrepareMsg struct {
	ShardMsgHeader
}

type XShardPreparedMsg struct {
	ShardMsgHeader
}

type XShardCommitMsg struct {
	ShardMsgHeader
}
```

### Case 5, smart contract locking on committing

In the time of 2pc protocol running, the involved contract has been locked except OEP-9 and system contract.

You can query locked contract by using height of block generated in these time.

#### Test Procedure

1. In case 4, query locked contracts of height ```h1, h2, h3, h4```.

#### Exception

The caller and callee contract has locked, and listed in locked contracts.

### Case 6, smart contract should not be invoked when its locked

Locking smart contract means that contract cannot be invoked, the result of invoked these contract transaction is error.

#### Test Procedure

1. After case 2, invoke caller contract and callee contract separately at shard 1 and shard 2;
2. Wait the transactions handled.

#### Exception

The states of these transaction has failed.

### Case 7, shard-asset contract is locked based on user account

In the 2pc protocol, OEP-9 contract locks only account address, not contract address. The reason is that OEP-9 contract will be locked frequently and there will decrease operating efficiency if locking contract address straightly.

Add one line code that invoke OEP-9 contract at [example code](https://github.com/qiluge/ontology-xshard-contract/blob/master/xshardcall/xshardcaller.py#L61) to test this case.

#### Test Procedure

1. Invoke the contract;
2. Wait 2pc commit;
3. In the waiting time, query locked contracts and locked keys.

#### Exception

The locked contract addresses does not contain OEP-9 contract address, but the locked keys contain the account address byte array.

### Case 8, remote-Invoke triggered by remote notification

If remote notification trigger the remote-invoke, the notification will also experience a complete remote invoke procedure.

The pre-condition is that shard A notify shard B, shard B invoke shard C.

#### Test Procedure

1. Invoke contract at shard A, wait tx handled;
2. Wait notify shard Tx at shard B handled;
3. Wait invoke shard Tx at shard C handled;
4. Query source tx and two shard tx states.

#### Exception

1. Source tx state is success, and notify shard tx and invoke shard tx state is success;
2. Notify shard tx could be queried by using source tx hash, invoke shard tx could be queried by using notify shard tx hash.

### Case 9, no data commit if transaction is aborted

In the time of ```InvokeRemoteShard```, if remote tx failed, the resp msg carried err to return to original shard. In this case, the temporary change at original shard will be dropped.
And then, send a abort msg to destination shard, the shard will also drop the temporary change after receive the abort msg.

#### Test Procedure

1. Insure remote shard execution will be failed;
2. Invoke at current shard, wait tx handled;
3. Wait shard tx handled at destination shard and sent resp msg to original shard;
4. Wait original shard handled resp msg and sent abort msg to destination shard;
5. Wait abort msg handled at destination shard;
6. Query source tx and these shard tx states.

#### Exception

1. Source tx state is failed, these shard tx state is success;
2. The ```invokeCount``` at destination shard does not changed.

### Case 10, cross shard Tx commit once and only once

In the 2pc protocol, the shard tx will execute twice, but the ledger change commit only once.

#### Test Procedure

1. Query ```invokeCount``` at shard 2 and record it as ```c1```;
2. Invoke contract method ```xshardInvoke```, wait tx handled;
3. Query ```invokeCount``` at shard 2 and record it as ```c2```.

#### Exception

c2-c1 = 1.

### Case 11, cross shard Tx pending state is not visible to other transactions

In the procedure of ```InvokeRemoteShard```, each tx is run at a sandy-box context, and these context is independent of each other.

#### Test Procedure

1. Execute two shard tx at shard A, these tx read ```invokeCount``` and increase it;
2. Query these shard tx state;
3. Query ```invokeCount``` at shard A.

#### Exception

1. Tx states are success;
2. ```invokeCount``` increase 2.