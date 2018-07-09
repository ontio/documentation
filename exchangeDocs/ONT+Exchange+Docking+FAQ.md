# ONT exchange FAQ

## Q：How does the Ontology node connect to the polaris TestNet?

A: Add parameter when starting: ```--networkid 2``` . For details, please refer to ```./ontology --help```


## Q: What is the transfer fee?

A: The Ontology network needs to consume ONG (gas) every transfer transaction, and only transactions with gasprice greater than 500 will be packaged on the MainNet.

```gasprice * gaslimit = ong  cost```


The lowest value of gaslimit is 20000, and the lowest value of gasprice is 500. So in general situations, the lowest transaction cost is 0.01 ONG. If the contract is too complicated, the value of gaslimit may exceed the minimum value - 20,000. The gasprice is set by the user and it should be greater than the lowest value.


## Q: How does ONT gradually unlock ONG?

A: At initialization, all ONG will be sent to a ONT contract address, and the ONG will be gradually unlocked over time. The address of the unlocked ONG is fixed and unique.

## Q: The issue about the precision of ONT and ONG

A: The ONT has a precision of 1, which is indivisible. The ONG has a precision of 9, which is separable. A transaction fee is paid by ONG.


## Q: If a transaction generates transaction cost, the transaction fee will also correspond to a transfer transaction. How to identify this transfer transaction? Is the destination address for the transfer a fixed address?

A: The total transaction fee is identified by **gasConsumed** in the message push and it must be the last message. The fee will be transferred to the governance contract address: AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK, and the address is unique.


## Q: Special contract address description

A:

| Name     | Address(Hex)                             | Address(Base58)                    |
| -------- | ---------------------------------------- | ---------------------------------- |
| ONT      | 0100000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV |
| ONG      | 0200000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbvhfRZMHJ |
| Governance Contract | 0700000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK |

## Q: Where is the ONT blockchain explorer?
A:[https://explorer.ont.io/](https://explorer.ont.io/)


## Q: What's the "White list startup"
A: In order to avoid syncing to some contaminated or malicious nodes, you can use the whitelist startup method to directly synchronize the official seed nodes. Command:
``` ./ontology --reservedfile=./peers.rsv --reservedonly``` 
We will provide the white list file peers.rsv in another place




