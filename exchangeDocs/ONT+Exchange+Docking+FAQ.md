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

## Q: How to swap NEP-5 ONT token

Before 2018.10.1 ,please

1. Transfer you NEP-5 ONT token to our destroy address :AFmseVrdL9f9oyCzZefL9tG6UbvhPbdYzM

2. Send email to : xiaomin@ont.io;wengjunjie@ont.io;zhoupeiwen@ont.io with following form:

   Exchange Name:

   Token swap amount:

   Transfer transaction hash:

3. We will send mainnet ONT back to the original address within a working day,  and send the confirm email.

## Q: How about the ong produced by token swap

1. The amount of ongs issued during the token swap: It is the unbounded ong from the ontology mainnet launched to the time when the nep-5 coin is transfered to the destruction address, excluding our manual processing time (up to 24 hours).

2. Assigning users to ong:ong transfer is the same as ont, and will consume at least 0.01 ong.

3. When withdraw ongs, the same processing fee will be consumed for each extraction operation, so it is not recommended to extract frequently.

## Q: What's the ONG unbounding rule
withdrawable ONG amount = [unbounded ong amount per second] × [holding time of ONT] × [holding ONT amount] / [ONT total supply]

[unbounded ong amount per second] will reduced by  [5, 4, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]  every year.

[holding time of ONT] :current time - last ONT account changed time

[ONT total supply]:1000000000

For Example:Account A holding 100 ONTs on day 1,200 ONTs on day 2, 300 ONTs on day 3, so he can withdraw ONGs:

（24×60×60)×5×100/1000000000 + （24×60×60)×5×200/1000000000

The other 300 ONTs will calculated on next account ONTs changed.

The first account ONT changed time is Ontology mainnet launched time on 2018/6/30.

