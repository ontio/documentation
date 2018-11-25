# Asset Management

Asset management commands can check account balance, ONT/ONG transfers, extract ONG, and view unbound ONG.

* [Check Your Account Balance](#check-your-account-balance)
* [ONT/ONG Transfers](#ontong-transfers)
* [Authorize Transfer](#authorize-transfer)
* [View Authorized Transfer Balance](#view-authorized-transfer-balance)
* [Transferring Fund from Authorized Accounts](#transferring-fund-from-authorized-accounts)
* [View Unlocked ONG Balance](#view-unlocked-ong-balance)
* [Extract Unlocked ONG](#extract-unlocked-ong)

## Check Your Account Balance

```
./Ontology asset balance <address|index|label>
```

## ONT/ONG Transfers

```
./Ontology asset transfer --from=<address|index|label> --to=<address|index|label> --amount=XXX --asset=ont
```

*Parameters:*

#### `--wallet` or `-w`
Wallet specifies the transfer-out account wallet path. The default value is: "./wallet.dat".

#### `--gasprice`
Specifies the gas price of the transfer transaction. The gas price of the transaction cannot be less than the lowest gas price set by node's transaction pool, otherwise the transaction will be rejected. The default value is 500 (0 in testmode). When there are transactions that are queued for packing into the block in the transaction pool, the transaction pool will deal with transactions according to the gas price and transactions with high gas prices will be prioritized.

#### `--gaslimit`
Specifies the gas limit of the transfer transaction. The gas limit of the transaction cannot be less than the minimum gas limit set by the node's transaction pool, otherwise the transaction will be rejected. Gasprice * gaslimit is actual ONG costs. The default value is 20000.

#### `--asset`
Specifies the asset type of the transfer. ont indicates the ONT and ong indicates the ONG. The default value is ont.

#### `--from`
Specifies the transfer-out account address.

#### `--to`
Specifies the transfer-in account address.

#### `--amount`
Specifies the transfer amount.

Note: Since the precision of the ONT is 1, if the input is a floating-point value, then the value of the fractional part will be discarded; the precision of the ONG is 9, so the fractional part beyond 9 bits will be discarded.


## Authorize Transfer

A user may authorize others to transfer money from his account, and he can specify the transfer amount when authorizing the transfer.

```
./Ontology asset approve --from=<address|index|label> --to=<address|index|label> --amount=XXX --asset=ont
```

*Parameters:*

#### `--wallet` or `-w`
Specifies the transfer-out account wallet path. The default value is: "./wallet.dat".

#### `--gasprice`
Specifies the gas price of the transfer transaction. The gas price of the transaction cannot be less than the lowest gas price set by node's transaction pool, otherwise the transaction will be rejected. The default value is 500 (0 in testmode). When there are transactions that are queued for packing into the block in the transaction pool, the transaction pool will deal with transactions according to the gas price and transactions with high gas prices will be prioritized.

#### `--gaslimit`
Specifies the gas limit of the transfer transaction. The gas limit of the transaction cannot be less than the minimum gas limit set by the node's transaction pool, otherwise the transaction will be rejected. Gasprice * gaslimit is actual ONG costs. The default value is 20000.

#### `--asset`
Specifies the asset type of the transfer. ont indicates the ONT and ong indicates the ONG. The default value is ont.

#### `--from`
Specifies the transfer-out account address.

#### `--to`
Specifies the transfer-in account address.

#### `--amount`
Specifies the transfer amount.

Note: Since the precision of the ONT is 1, if the input is a floating-point value, then the value of the fractional part will be discarded; the precision of the ONG is 9, so the fractional part beyond 9 bits will be discarded.


## View Authorized Transfer Balance

After authorizing a user to transfer funds, the user can execute transfer operation within the authorized amount multiple times based on needs. The command of checking authorized transfer balances can see the untransferred balances.

```
./Ontology asset allowance --from=<address|index|label> --to=<address|index|label>
```

*Parameters:*

#### `--wallet` or `-w`
Specifies the transfer-out account wallet path. The default value is: "./wallet.dat".

#### `--asset`
Specifies the asset type of the transfer. ont indicates the ONT and ong indicates the ONG. The default value is ont.

#### `--from`
Specifies the transfer-out account address.

#### `--to`
Specifies the transfer-in account address.


## Transferring Funds from Authorized Accounts

After user authorization, the transfer can be made from the authorized account.

```
./Ontology asset transferfrom --from=<address|index|label> --to=<address|index|label> --sender=<address|index|label> --amount=XXX
```

*Parameters:*

#### `--wallet` or `-w`
Specifies the wallet path of authorized account. The default value is: "./wallet.dat".

#### `--gasprice`
Specifies the gas price of the transfer transaction. The gas price of the transaction cannot be less than the lowest gas price set by node's transaction pool, otherwise the transaction will be rejected. The default value is 500 (0 in testmode). When there are transactions that are queued for packing into the block in the transaction pool, the transaction pool will deal with transactions according to the gas price and transactions with high gas prices will be prioritized.

#### `--gaslimit`
Specifies the gas limit of the transfer transaction. The gas limit of the transaction cannot be less than the minimum gas limit set by the node's transaction pool, otherwise the transaction will be rejected. Gasprice * gaslimit is actual ONG costs. The default value is 20000.

#### `--asset`
Specifies the asset type of the transfer. ont indicates the ONT and ong indicates the ONG. The default value is ont.

#### `--from`
Specifies the transfer-out account address.

#### `--to`
Specifies the transfer-in account address.

#### `--sender`
Specifies the account address that actually operates the authorized transfer. If no sender parameter is specified, the sender parameter defaults to the value of the to parameter.

#### `--amount`
Specifies the transfer amount and the transfer amount cannot be greater than the authorized transfer balance. Otherwise, the transaction will be rejected.

Note: Since the precision of the ONT is 1, if the input is a floating-point value, then the value of the fractional part will be discarded; the precision of the ONG is 9, so the fractional part beyond 9 bits will be discarded.


## View Unbound ONG Balance

The ONG adopts the periodical unbinding policy to release the ONG bound to ONT. Use the following command to view the current account unbound ONG balance.

```
./Ontology asset unboundong <address|index|label>
```

## Extract Unbound ONG

Use the following command to extract all unbound ONG.

```
./Ontology asset withdrawong <address|index|label>
```

*Parameters:*

#### `--wallet` or `-w`
Specifies the wallet path of extracted account. The default value is: "./wallet.dat".

#### `--gasprice`
Specifies the gas price of the transfer transaction. The gas price of the transaction cannot be less than the lowest gas price set by node's transaction pool, otherwise the transaction will be rejected. The default value is 500 (0 in testmode). When there are transactions that are queued for packing into the block in the transaction pool, the transaction pool will deal with transactions according to the gas price and transactions with high gas prices will be prioritized.

#### `--gaslimit`
Specifies the gas limit of the transfer transaction. The gas limit of the transaction cannot be less than the minimum gas limit set by the node's transaction pool, otherwise the transaction will be rejected. Gasprice * gaslimit is actual ONG costs. The default value is 20000.
