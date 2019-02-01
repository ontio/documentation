
* [Generate Multi-Signature Address](#generate-multi-signature-address)
* [Multi-Signature To Transaction](#multi-signature-to-transaction)

## Generate Multi-Signature Address

Generating a multi-signature address need public keys and the signature number at least.

```
./ontology multisigaddr --pubkey=03c0c30f11c7fc1396e8595bf2e339d553d728ea6f21ae831e8ab704ca14fe8a56,02b2b9fb60a0add9ef6715ffbac8bc7e81cb47cd06c157c19e6a858859c0158231 -m=1
```
Return example:

```
Pub key list:
Index 1 Address:AaCe8nVkMRABnp5YgEjYZ9E5KYCxks2uce PubKey:02b2b9fb60a0add9ef6715ffbac8bc7e81cb47cd06c157c19e6a858859c0158231
Index 2 Address:ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48 PubKey:03c0c30f11c7fc1396e8595bf2e339d553d728ea6f21ae831e8ab704ca14fe8a56

MultiSigAddress:Ae4cxJiubmgueAVtNbjpmm2AGNgdKP6Ea7
```

*Parameters:*

#### `--pubkey`
The public keys to be included in the multisig address. Multiple addresses are separated by commas. The max number of public key support by Ontology is 16 at present.

You can retrieve your account public keys with the command: `./ontology account list -v`

#### `-m`
Specifies the minimum number of signatures required for a transaction to be accepted for this address. Default value is 1.


## Multi-Signature Sign Transaction

Multi-Signature transactions need multiple accounts to sign a transaction, one at a time one. The signed output by one signer, will serve as the input of the following signer, until number of signatures equals at least the value of `m` (specified at time of multisig account creation).


```
./ontology multisigtx --account=ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48 --pubkey=03c0c30f11c7fc1396e8595bf2e339d553d728ea6f21ae831e8ab704ca14fe8a56,02b2b9fb60a0add9ef6715ffbac8bc7e81cb47cd06c157c19e6a858859c0158231 -m=1 00d1045f875bf401000000000000204e000000000000f47d92d27d02b93d21f8af16c9f05a99d128dd5a6e00c66b6a14f47d92d27d02b93d21f8af16c9f05a99d128dd5ac86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a5ac86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
```

Return example:

```
RawTx after multi signed:
00d1045f875bf401000000000000204e000000000000f47d92d27d02b93d21f8af16c9f05a99d128dd5a6e00c66b6a14f47d92d27d02b93d21f8af16c9f05a99d128dd5ac86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a5ac86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65000141409dd2a46277f96566b9e9b4fc354be90b61776c58125cfbf36e770b1b1d50a16febad4bfadfc966fa575e90acf3b8308d7a0f637260b31321cb7ef6f741364d0e47512102b2b9fb60a0add9ef6715ffbac8bc7e81cb47cd06c157c19e6a858859c01582312103c0c30f11c7fc1396e8595bf2e339d553d728ea6f21ae831e8ab704ca14fe8a5652ae
```

*Parameters:*

#### `--pubkey`
The public keys to be included in the multisig address. Multiple addresses are separated by commas. The max number of public key support by Ontology is 16 at present.

You can retrieve your account public keys with the command: `./ontology account list -v`

#### `-m`
Specifies the minimum number of signatures required for a transaction to be accepted for this address. Default value is 1.

#### `--wallet` or `-w`
Specifies the wallet path of authorized account. The default value is: "./wallet.dat".

#### `--account` or `-a`
Specifies signature account, if not specified, the default account of wallet will be used.

#### `--send`
Specifies whether send transaction to Ontology after signed.

#### `--prepare`
Specifies whether prepare execute transaction, without send to Ontology.

#### `--rpcport`
Specifies the port number to which the RPC server is bound. The default is 20336.
