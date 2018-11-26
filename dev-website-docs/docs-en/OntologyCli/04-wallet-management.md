# Wallet Management

Wallet management commands can be used to add, view, modify, delete, and import an account.

You can run `./Ontology account --help` to view all of the wallet management command from the cli.

* [Encryption Algorithms](#encryption-algorithms)
* [Add Account](#add-account)
* [View Account](#view-account)
* [Modify Account](#modify-account)
* [Delete Account](#delete-account)
* [Import Account](#import-account)
	* [Import Account by WIF](#import-account-by-wif)

## Encryption Algorithms

Ontology supports multiple encryption algorithms, including ECDSA, SM2, and ED25519.

When using ECDSA encryption algorithm, it can support multiple key curves, such as: P-224, P-256, P-384, P-521; In addition, when using ECDSA encryption algorithm, you can also specify the signature scheme such as: SHA224withECDSA, SHA256withECDSA, SHA384withECDSA, SHA512withEdDSA, SHA3-224withECDSA, SHA3-256withECDSA, SHA3-384withECDSA, SHA3-512withECDSA, RIPEMD160withECDSA.

When using the SM2 encryption algorithm, the sm2p256v1 curve and SM3withSM2 signature algorithm will be used.

When using the ED25519 encryption algorithm, the 25519 curve and SHA512withEdDSA signature algorithm will be used.


### Add account

```
./Ontology account add --default
```

You can view the help information by ./Ontology account add --help.

Each wallet has a default account, which is generally the first account added. The default account cannot be deleted, you can modify the default account with `./Ontology account set` command.

*Parameters:*

#### `--type` or `-t`
The type parameter is used to set the encryption algorithm and supports the ecdsa, sm2, and ed25519 encryption algorithms.

#### `--bit-length` or `-b`
bit-length parameter is used to specify the key length. If ecdsa is the encryption algorithm, you can choose p-224, p-256, p-384 or p-521; if sm2 is the encryption algorithm, the default is sm2p256v1; if ed25519 is the encryption algorithm, the default is 25519.

#### `--signature-scheme` or `-s`
The signature-scheme parameter is used to specify the key signature scheme. For the ecdsa encryption algorithm, these signature schemes such as SHA224withECDSA, SHA256withECDSA, SHA384withECDSA, SHA512withEdDSA, SHA3-224withECDSA, SHA3-256withECDSA, SHA3-384withECDSA, SHA3-512withECDSA, RIPEMD160withECDSA are supported; For the sm2 encryption algorithm, SM3withSM2 signature scheme is used by default. If ed25519 is the encryption algorithm, the SHA512withEdDSA signature scheme is used by default.

#### `--default`
The default parameter uses the system's default key scheme. The default key scheme will use the ECDSA encryption algorithm with P-256 curve and SHA256withECDSA as the signature algorithm.

#### `--label`
Label is used to set labels for newly created accounts for easy and fast use of accounts. Note that duplicate label names cannot appear in the same wallet file. An account with no label is an empty string.

#### `--wallet`
The wallet parameter specifies the wallet file path. If the wallet file does not exist, a new wallet file will be automatically created.

#### `--number`
The number parameter specifies the number of accounts that need to be created. You can batch create accounts by number parameter. The default value is 1.

#### `--ontid`
The parameter is used to create ONT ID instead of account.


##  View Account

```
./Ontology account list
```

You can view all account information in your current wallet. such as:

```
$ ./Ontology account list
Index:1    Address:TA587BCw7HFwuUuzY1wg2HXCN7cHBPaXSe  Label: (default)
Index:2    Address:TA5gYXCSiUq9ejGCa54M3yoj9kfMv3ir4j  Label:
```

Among them, Index is the index of the account in the wallet and the index starts from 1. Address is the address of the account. Label is the label of the account, default indicates that the current account is the default account.
In Ontology CLI, you can find accounts by Index, Address, or a non-empty Label.

Use --v to view the details of the account.

You can view the help information via ./Ontology account list --help.


##  Modify Account

Using the modify account command to modify the account's label, reset the default account, modify the account's password. If the account is the key of the ECDSA encryption algorithm, you can also modify the key's signature scheme.

You can view the help information via ./Ontology account add --help.

*Parameters:*

#### `--as-default` or `-d`
The as-default parameter sets the account as the default account. A wallet only has one default account. After setting a new default account, the previous default account will automatically cancel the default account properties.

#### `--wallet` or `-w`
The wallet parameter specifies the wallet path. The default value is "./wallet.dat".

#### `--label` or `-l`
The label parameter is used to set a new label for the account. Note that a wallet file cannot have the same label.

#### `--change-passwd`
The change-passwd parameter is used to modify the account password.

#### `--signature-scheme` or `-s`
The signature-scheme parameter is used to modify the account signature scheme. If the account uses an ECDSA key, the following ECDSA-supported signature schemes can be modified: SHA224withECDSA, SHA256withECDSA, SHA384withECDSA, SHA512withEdDSA, SHA3-224withECDSA, SHA3-256withECDSA, SHA3-384withECDSA, SHA3-512withECDSA, RIPEMD160withECDSA.

**Set default account**

```
./Ontology account set -d <address|index|label>
```
**Edit account label**

```
./Ontology account set --label=XXX <address|index|label>
```
**Change account password**

```
./Ontology account set --changepasswd <address|index|label>
```

**Modify ECDSA key signature scheme**

```
./Ontology account set -s=SHA256withECDSA <address|index|label>
```


##  Delete Account

Unnecessary accounts in the wallet can be deleted and cannot be recovered after delete. Note: The default account cannot be deleted.

```
/Ontology account del <address|index|label>
```


##  Import Account

The import account command can import account of another wallet into the current wallet.
```
./Ontology account import -s=./source_wallet.dat
```

*Parameters:*

#### `--wallet` or `-w`
The wallet parameter specifies the current wallet path for saving the wallet-introduced account.

#### `--source` or `-s`
The source parameter specifies the imported wallet path.


### Import Account by WIF
Fill the WIF into a text file, and use the cmd below to import the key
```
./Ontology account import --wif --source key.txt
```
