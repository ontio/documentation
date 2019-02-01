
# Info

The `info` command can query information such as blocks, transactions, and transaction executions.

You can use the `./Ontology info --help` command to view help information.

* [Block Information](#query-block-information)
* [Transaction Information](#query-transaction-information)
* [Transaction Execution Information](#query-transaction-execution-information)


## Block Information
Block information can be queried by block height or block hash.

```
./Ontology info block <height|blockHash>
```

## Transaction Information
You can query transaction information by transaction hash.

```
./Ontology info tx <TxHash>
```

## Transaction Execution Information
You can query the transaction execution information through the transaction hash.

```
./Ontology info status <TxHash>
```
Example response:

```
{
   "TxHash": "4c00674d96b1d3d2c8152b905cae6f87fff0ec8acf28ca3e7465aac59de814a1",
   "State": 1,
   "GasConsumed": 0,
   "Notify": [
      {
         "ContractAddress": "ff00000000000000000000000000000000000001",
         "States": [
            "transfer",
            "TA587BCw7HFwuUuzY1wg2HXCN7cHBPaXSe",
            "TA5gYXCSiUq9ejGCa54M3yoj9kfMv3ir4j",
            10
         ]
      }
   ]
}
```

`State` represents the result of the transaction execution.

	1: successful
	0: failure

`GasConsumed` indicates the ONG consumed by the transaction execution.

`Notify` represents the Event log output when the transaction is executed. Different transactions may output different event logs.
