# Transactions

With the Ontology CLI you are able to construct various different types of transactions to sign and broadcast the the network.

* [Build Transaction](#build-transaction)
	* [Build Transfer Transaction](#build-transfer-transaction)
	* [Build Authorize Transfer](#build-authorize-transfer)
	* [Build Transfer From Authorize Account Transaction](#build-transfer-from-authorize-account-transaction)
	* [Build Withdraw ONG Transaction](#build-withdraw-ong-transaction)
* [Sign To Transaction](#sign-to-transaction)
* [Send Transaction](#send-transaction)
* [Show Transaction Infomation](#show-transaction-infomation)

## Build Transaction

Building a transaction will format the transaction attributes into a raw data format to be signed and broadcast to the Ontology network.

### Build Transfer Transaction

```
./ontology buildtx transfer --asset=ONT --from=ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48 --to=AaCe8nVkMRABnp5YgEjYZ9E5KYCxks2uce --amount=10
```

Return example:

```
Transfer raw tx:
00d1d376865bf401000000000000204e0000000000006a987e044e01e3b71f9bb60df57ab0458215ef0f6e00c66b6a146a987e044e01e3b71f9bb60df57ab0458215ef0fc86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a5ac86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
```

*Parameters:*

#### `--wallet` or `-w`
Wallet specifies the transfer-out account wallet path. The default value is: "./wallet.dat".

#### `--gasprice`
The gasprice parameter specifies the gas price of the transfer transaction. The gas price of the transaction cannot be less than the lowest gas price set by node's transaction pool, otherwise the transaction will be rejected. The default value is 500 (0 in testmode). When there are transactions that are queued for packing into the block in the transaction pool, the transaction pool will deal with transactions according to the gas price and transactions with high gas prices will be prioritized.

#### `--gaslimit`
The gaslimit parameter specifies the gas limit of the transfer transaction. The gas limit of the transaction cannot be less than the minimum gas limit set by the node's transaction pool, otherwise the transaction will be rejected. Gasprice * gaslimit is actual ONG costs. The default value is 20000.

#### `--asset`
The asset parameter specifies the asset type of the transfer. Ont indicates the ONT and ong indicates the ONG. The default value is ont.

#### `--from`
The from parameter specifies the transfer-out account address.

#### `--to`
The to parameter specifies the transfer-in account address.

#### `--amount`
The amount parameter specifies the transfer amount. Note: Since the precision of the ONT is 1, if the input is a floating-point value, then the value of the fractional part will be discarded; the precision of the ONG is 9, so the fractional part beyond 9 bits will be discarded.

#### `--payer`
payer parameter specifies the transaction fee payer. If don't specifies, using signer account default.


### Build Authorize Transfer

```
./ontology buildtx approve --from=ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48 --to=AaCe8nVkMRABnp5YgEjYZ9E5KYCxks2uce --amount=10
```
Return example:

```
Approve raw tx:
00d12178865bf401000000000000204e0000000000006a987e044e01e3b71f9bb60df57ab0458215ef0f6b00c66b6a146a987e044e01e3b71f9bb60df57ab0458215ef0fc86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a5ac86c07617070726f76651400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
```

*Parameters:*

#### `--wallet` or `-w`
Wallet specifies the transfer-out account wallet path. The default value is: "./wallet.dat".

#### `--gasprice`
The gasprice parameter specifies the gas price of the transfer transaction. The gas price of the transaction cannot be less than the lowest gas price set by node's transaction pool, otherwise the transaction will be rejected. The default value is 500 (0 in testmode). When there are transactions that are queued for packing into the block in the transaction pool, the transaction pool will deal with transactions according to the gas price and transactions with high gas prices will be prioritized.

#### `--gaslimit`
The gaslimit parameter specifies the gas limit of the transfer transaction. The gas limit of the transaction cannot be less than the minimum gas limit set by the node's transaction pool, otherwise the transaction will be rejected. Gasprice * gaslimit is actual ONG costs. The default value is 20000.

#### `--asset`
The asset parameter specifies the asset type of the transfer. Ont indicates the ONT and ong indicates the ONG. The default value is ont.

#### `--from`
The from parameter specifies the transfer-out account address.

#### `--to`
The to parameter specifies the transfer-in account address.

#### `--amount`
The amount parameter specifies the transfer amount. Note: Since the precision of the ONT is 1, if the input is a floating-point value, then the value of the fractional part will be discarded; the precision of the ONG is 9, so the fractional part beyond 9 bits will be discarded.

#### `--payer`
payer parameter specifies the transaction fee payer. If don't specifies, using signer account default.


### Build Transfer From Authorize Account Transaction

```
./ontology buildtx transferfrom --sender=AMFrW7hrSRw1Azz6hQohni8BdStZDvectW --from=Aaxjf7utmjSstmTD1LjtYfhZ3CoWaxC7Tt --to=AMFrW7hrSRw1Azz6hQohni8BdStZDvectW --amount=10
```

Return example:

```
00d10754875bf401000000000000204e0000000000003c2352095b7428debfd1c1519f5a8f45a474a4218700c66b6a143c2352095b7428debfd1c1519f5a8f45a474a421c86a14d2784bddeac73d20124f20f4fa9528f3365a4dd4c86a143c2352095b7428debfd1c1519f5a8f45a474a421c86a5ac86c0c7472616e7366657246726f6d1400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
```

*Parameters:*

#### `--wallet` or `-w`
Wallet specifies the wallet path of authorized account. The default value is: "./wallet.dat".

#### `--gasprice`
The gasprice parameter specifies the gas price of the transfer transaction. The gas price of the transaction cannot be less than the lowest gas price set by node's transaction pool, otherwise the transaction will be rejected. The default value is 500 (0 in testmode). When there are transactions that are queued for packing into the block in the transaction pool, the transaction pool will deal with transactions according to the gas price and transactions with high gas prices will be prioritized.

#### `--gaslimit`
The gaslimit parameter specifies the gas limit of the transfer transaction. The gas limit of the transaction cannot be less than the minimum gas limit set by the node's transaction pool, otherwise the transaction will be rejected. Gasprice * gaslimit is actual ONG costs. The default value is 20000.

#### `--asset`
The asset parameter specifies the asset type of the transfer. Ont indicates the ONT and ong indicates the ONG. The default value is ont.

#### `--from`
The from parameter specifies the transfer-out account address.

#### `--to`
The to parameter specifies the transfer-in account address.

#### `--sender`
The sender parameter specifies the account address that actually operates the authorized transfer. If no sender parameter is specified, the sender parameter defaults to the value of the to parameter.

#### `--amount`
The amount parameter specifies the transfer amount and the transfer amount cannot be greater than the authorized transfer balance. Otherwise, the transaction will be rejected. Note: Since the precision of the ONT is 1, if the input is a floating-point value, then the value of the fractional part will be discarded; the precision of the ONG is 9, so the fractional part beyond 9 bits will be discarded.

#### `--payer`
payer parameter specifies the transaction fee payer. If don't specifies, using signer account default.


### Build Withdraw ONG Transaction

```
./ontology buildtx withdrawong ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48
```

Return example:

```
Withdraw account:ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48
Receive account:ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48
Withdraw ONG amount:2321499191858975
Withdraw raw tx:
00d11b56875bf401000000000000204e0000000000006a987e044e01e3b71f9bb60df57ab0458215ef0f8e00c66b6a146a987e044e01e3b71f9bb60df57ab0458215ef0fc86a140000000000000000000000000000000000000001c86a146a987e044e01e3b71f9bb60df57ab0458215ef0fc86a071f57ad26643f08c86c0c7472616e7366657246726f6d1400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
```

*Parameters:*

#### `--wallet` or `-w`
Wallet specifies the wallet path of authorized account. The default value is: "./wallet.dat".

#### `--gasprice`
The gasprice parameter specifies the gas price of the transfer transaction. The gas price of the transaction cannot be less than the lowest gas price set by node's transaction pool, otherwise the transaction will be rejected. The default value is 500 (0 in testmode). When there are transactions that are queued for packing into the block in the transaction pool, the transaction pool will deal with transactions according to the gas price and transactions with high gas prices will be prioritized.

#### `--gaslimit`
The gaslimit parameter specifies the gas limit of the transfer transaction. The gas limit of the transaction cannot be less than the minimum gas limit set by the node's transaction pool, otherwise the transaction will be rejected. Gasprice * gaslimit is actual ONG costs. The default value is 20000.

#### `--amount`
The amount parameter specifies the transfer amount and the transfer amount cannot be greater than the authorized transfer balance. Otherwise, the transaction will be rejected. Note: Since the precision of the ONT is 1, if the input is a floating-point value, then the value of the fractional part will be discarded; the precision of the ONG is 9, so the fractional part beyond 9 bits will be discarded.
If don't specifies withdraw all unbound ONG as default.

#### `--receive`
receive params specifies the ONG receive account. If don't specifies, using withdraw account default.

#### `--payer`
payer parameter specifies the transaction fee payer. If don't specifies, using signer account default.

#### `--rpcport`
The rpcport parameter specifies the port number to which the RPC server is bound. The default is 20336.


## Sign Transaction

The transaction build by buildtx command, should be signed before send to Ontology.

Note: if the payer of the transaction fee is different than the sender, both accounts must sign to the transaction.

```
./ontology sigtx --account=ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48 00d11b56875bf401000000000000204e0000000000006a987e044e01e3b71f9bb60df57ab0458215ef0f8e00c66b6a146a987e044e01e3b71f9bb60df57ab0458215ef0fc86a140000000000000000000000000000000000000001c86a146a987e044e01e3b71f9bb60df57ab0458215ef0fc86a071f57ad26643f08c86c0c7472616e7366657246726f6d1400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
```

Return example:

```
RawTx after signed:
00d11b56875bf401000000000000204e0000000000006a987e044e01e3b71f9bb60df57ab0458215ef0f8e00c66b6a146a987e044e01e3b71f9bb60df57ab0458215ef0fc86a140000000000000000000000000000000000000001c86a146a987e044e01e3b71f9bb60df57ab0458215ef0fc86a071f57ad26643f08c86c0c7472616e7366657246726f6d1400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b65000141407331b7ba2a7708187ad4cb14146d2080185e42f0a39d572f58d25fa2e20f3066711b64f2b91d958683f7bfb904badeb0d6bc733506e665028a2c2968b77d5958232103c0c30f11c7fc1396e8595bf2e339d553d728ea6f21ae831e8ab704ca14fe8a56ac
```

*Parameters:*

#### `--wallet` or `-w`
Wallet specifies the wallet path of authorized account. The default value is: "./wallet.dat".

#### `--account` or `-a`
account parameter specifies signature account, if not specified, the default account of wallet will be used.

#### `--send`
--send parameter specifies whether send transaction to Ontology after signed.

#### `--prepare`
prepare parameter specifies whether prepare execute transaction, without send to Ontology.

#### `--rpcport`
The rpcport parameter specifies the port number to which the RPC server is bound. The default is 20336.


## Send Transaction

The transaction after being signed can be sent to Ontology via sendtx command.

```
./ontology sendtx 00d17c61875bf401000000000000204e0000000000006a987e044e01e3b71f9bb60df57ab0458215ef0f6e00c66b6a146a987e044e01e3b71f9bb60df57ab0458215ef0fc86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a5ac86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65000141409f32f1fd170d174959da26cb9df8f4a15049d255ed3953d92870d5739c4e8b8158ec3bde1e9ae9b4d9621b09311b5e49ed91dcbc64d3b5f74cf011eaa616c403232103c0c30f11c7fc1396e8595bf2e339d553d728ea6f21ae831e8ab704ca14fe8a56ac
```

Return example:

```
  TxHash:f8ea91da985af249e808913b6398150079cdfb02273146e4eb69c43947a42db2

Tip:
  Using './ontology info status f8ea91da985af249e808913b6398150079cdfb02273146e4eb69c43947a42db2' to query transaction status.
```

*Parameters:*

#### `--rpcport`
The rpcport parameter specifies the port number to which the RPC server is bound. The default is 20336.

#### `--prepare`
prepare parameter specifies whether prepare execute transaction, without send to Ontology.


If prepare option is set, the following will be returned instead:

```
Prepare execute transaction success.
Gas limit:20000
Result:01
```

## 12. Show Transaction Infomation

The information of transaction field can be show via showtx command.

Example:

```
./ontology showtx 00d1045f875bf401000000000000204e000000000000f47d92d27d02b93d21f8af16c9f05a99d128dd5a6e00c66b6a14f47d92d27d02b93d21f8af16c9f05a99d128dd5ac86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a5ac86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65000141409dd2a46277f96566b9e9b4fc354be90b61776c58125cfbf36e770b1b1d50a16febad4bfadfc966fa575e90acf3b8308d7a0f637260b31321cb7ef6f741364d0e47512102b2b9fb60a0add9ef6715ffbac8bc7e81cb47cd06c157c19e6a858859c01582312103c0c30f11c7fc1396e8595bf2e339d553d728ea6f21ae831e8ab704ca14fe8a5652ae
```
Return:

```
{
   "Version": 0,
   "Nonce": 1535598340,
   "GasPrice": 500,
   "GasLimit": 20000,
   "Payer": "Ae4cxJiubmgueAVtNbjpmm2AGNgdKP6Ea7",
   "TxType": 209,
   "Payload": {
      "Code": "00c66b6a14f47d92d27d02b93d21f8af16c9f05a99d128dd5ac86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a5ac86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65",
      "GasLimit": 0
   },
   "Attributes": [],
   "Sigs": [
      {
         "PubKeys": [
            "02b2b9fb60a0add9ef6715ffbac8bc7e81cb47cd06c157c19e6a858859c0158231",
            "03c0c30f11c7fc1396e8595bf2e339d553d728ea6f21ae831e8ab704ca14fe8a56"
         ],
         "M": 1,
         "SigData": [
            "9dd2a46277f96566b9e9b4fc354be90b61776c58125cfbf36e770b1b1d50a16febad4bfadfc966fa575e90acf3b8308d7a0f637260b31321cb7ef6f741364d0e"
         ]
      }
   ],
   "Hash": "34559b63187d7ddf5a17ac7a2dabb8fcaa1bea6676eba78a174d038ff3c66f15",
   "Height": 0
}
```
