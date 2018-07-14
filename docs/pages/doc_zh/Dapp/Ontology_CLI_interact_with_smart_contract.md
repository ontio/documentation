---
sidebar : Dapp_zh
permalink : Ontology_CLI_interact_with_smart_contract_zh.html
folder : doc_zh
---



<h1 align="center">Ontology CLI 与智能合约交互</h1>
<p align="center" class="version">Version V1.0.0 </p>


- [使用Ontology CLI与链交互](#使用ontology-cli与链交互)
    - [Ontology CLI概览](#ontology-cli概览)
    - [账户管理](#账户管理)
        - [命令概览](#命令概览)
        - [添加账户](#添加账户)
        - [显示账户](#显示账户)
    - [信息获取](#信息获取)
        - [命令概览](#命令概览-1)
        - [区块信息获取](#区块信息获取)
            - [通过块高度查询区块信息](#通过块高度查询区块信息)
            - [通过块哈希查询区块信息](#通过块哈希查询区块信息)
        - [交易信息获取](#交易信息获取)
        - [当前块高获取](#当前块高获取)
    - [资产处理](#资产处理)
        - [命令概览](#命令概览-2)
        - [提取ONG](#提取ong)
        - [转账示例](#转账示例)
            - [命令概览](#命令概览-3)
            - [ONT转账](#ont转账)
            - [ONG转账](#ong转账)
        - [授权转账](#授权转账)
    - [智能合约](#智能合约)
        - [命令概览](#命令概览-4)
        - [智能合约的部署](#智能合约的部署)
        - [智能合约的执行](#智能合约的执行)
            - [按合约地址执行](#按合约地址执行)
            - [按字节码执行](#按字节码执行)
    - [区块导出与导入](#区块导出与导入)
        - [命令概览](#命令概览-5)
        - [区块导出](#区块导出)
        - [区块导入](#区块导入)

## 使用Ontology CLI与链交互

教程所用的Ontology CLI版本为0.9，你可通过`./ontology --help`命令查看当前所使用的Ontology CLI版本。

```
$./ontology --help
VERSION:
  0.9
```

### Ontology CLI概览

- **启动Ontology CLI**

```
$./ontology
```

- **获取帮助**

```
$./ontology --help
```

### 账户管理

节点运行需要钱包文件`.dat`，在第一次启动Ontology CLI的时候，我们需要首先创建钱包文件。否则，将会得到如下提示：

```
$ ./ontology
 [INFO ] GID 1, Config init success
 [ERROR] GID 1, initWallet error:Cannot find wallet file:./wallet.dat. Please create wallet first
```

一个钱包文件`.dat`的内容如下所示：

```
{
    "name":"MyWallet",
    "version":"1.1",
    "scrypt":{
        "p":8,
        "n":16384,
        "r":8,
        "dkLen":64
    },
    "accounts":[
        {
            "address":"AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs",
            "enc-alg":"aes-256-gcm",
            "key":"94SPzRl5PHi8qJayofpGvpioS9zSDCnIZBfpyWI4GXedSgTFpFFAnpyqmPM38Q+z",
            "algorithm":"ECDSA",
            "salt":"HkBRKvpiONzICBFCFrUuHw==",
            "parameters":{
                "curve":"P-256"
            },
            "label":"",
            "publicKey":"032cf2191a24c6bee28abbee0c4b5265dc841394f2794c1fb18e52ffb2c9d7c9c6",
            "signatureScheme":"SHA256withECDSA",
            "isDefault":true,
            "lock":false
        }
    ]
}
```

#### 命令概览

如下所示，`ontology account`命令用于对账户进行添加、查看、修改、删除、导入等操作，以及多重签名地址的生成。

```
$ ./ontology account --help

NAME:
	ontology account - Wallet management commands can be used to add, view, modify, delete, import account, and so on.
   
USAGE:
	ontology account command [command options] [arguments...]

COMMANDS:
    add           Add a new account
    list          List existing accounts
    set           Modify an account
    del           Delete an account
    import        Import accounts of wallet to another
    export        Export accounts to a specified wallet file
    multisigaddr  Gen multi-signature address

OPTIONS:
	--help, -h  show help                    
```

#### 添加账户

通过`./ontology account add`命令可以完成添加账户的操作，该命令所支持的参数如下所示。

```
$ ./ontology account add --help

USAGE:
	ontology account add [command options] [sub-command options]

DESCRIPTION:
	Add a new account to wallet.
  
ACCOUNT OPTIONS:
	--number <quantity>, -n <quantity>
	  Specifies the <quantity> of account to create. (default: 1)
	  
	--type <key-type>, -t <key-type>            
	  Specifies the <key-type> by signature algorithm.
	
	--bit-length <bit-length>, -b <bit-length>
	  Specifies the <bit-length> of key
	
	--signature-scheme <scheme>, -s <scheme>
	  Specifies the signature scheme <scheme>
	
	--default, -d
	  Use default settings to create a new account (equal to '-t ecdsa -b 256 -s SHA256withECDSA')
	
	--label <label>, -l <label>
	  Use <label> for newly created accounts for easy and fast use of accounts. 
	  Note that duplicate label names cannot appear in the same wallet file. 
	  An account with no label is an empty string.
	
	--wallet <filename>, -w <filename>
	  Use <filename> as the wallet (default: "./wallet.dat")
```

- **创建账户**

```
$ ./ontology account add

Select a signature algorithm from the following:

  1  ECDSA
  2  SM2
  3  Ed25519

[default is 1]: 1
ecdsa is selected. 

Select a curve from the following:

    | NAME  | KEY LENGTH (bits)
 ---|-------|------------------
  1 | P-224 | 224
  2 | P-256 | 256
  3 | P-384 | 384
  4 | P-521 | 521

This determines the length of the private key [default is 2]: 2
scheme P-256 is selected.

Select a signature scheme from the following:

  1  SHA224withECDSA
  2  SHA256withECDSA
  3  SHA384withECDSA
  4  SHA512withECDSA
  5  SHA3-224withECDSA
  6  SHA3-256withECDSA
  7  SHA3-384withECDSA
  8  SHA3-512withECDSA
  9  RIPEMD160withECDSA

This can be changed later [default is 2]: 2
scheme SHA256withECDSA is selected.
Password:
Re-enter Password:

Index: 3
Label: 
Address: AQZ7siPVMSK2wmPrcFuaH5moCK9CcnSamW
Public key: 0267711482fe11a3313db449982b383c1cf2637636f1096625d20fb40568b5aaec
Signature scheme: SHA256withECDSA

Create account successfully.
```


- **使用默认设置生成账户**

```
$ ./ontology account add -d
Use default setting '-t ecdsa -b 256 -s SHA256withECDSA' 
	signature algorithm: ecdsa 
	curve: P-256 
	signature scheme: SHA256withECDSA 
Password:
Re-enter Password:

Index: 2
Label: 
Address: AXqduY2hhW8DbDphFz6nTiBA5SUaDHqndB
Public key: 033d172e68b20ef34c602af415cc3f4e77d8c6d0f5ac2223c3c8cd7ce85036bbec
Signature scheme: SHA256withECDSA

Create account successfully.
```

- **批量生成账户**

```
$ ./ontology account add -n 3 -d -w wallet.dat
Use default setting '-t ecdsa -b 256 -s SHA256withECDSA' 
	signature algorithm: ecdsa 
	curve: P-256 
	signature scheme: SHA256withECDSA 
Password:
Re-enter Password:

Index: 1
Label: 
Address: AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
Public key: 032cf2191a24c6bee28abbee0c4b5265dc841394f2794c1fb18e52ffb2c9d7c9c6
Signature scheme: SHA256withECDSA

Index: 2
Label: 
Address: AZk95PorAAUFGZUUQbozUHgVADQ5LFj1WJ
Public key: 02dca3145b351386aba4464862a470b97a8b64ef077dbe370831b74791d02efe50
Signature scheme: SHA256withECDSA

Index: 3
Label: 
Address: AGrHMXjj14iiyGzHfmz2nrCKveHSeEzs2E
Public key: 033ec2635d84d0b0c5e932bbb9c5aa61b0d79b32e42979d5694c1efb54dcd86293
Signature scheme: SHA256withECDSA

Create account successfully.
```

#### 显示账户

`./ontology account list`命令用于显示当前钱包文件中所存有的账户，其示例如下所示。

```
$ ./ontology account list
Index:1    Address:AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs  Label: (default)
Index:2    Address:AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g  Label:
```


### 信息获取

#### 命令概览

```
$ ./ontology info

USAGE:
	ontology info command [command options] [arguments...]


Description:
	
	Query information command can query information such as blocks, transactions, and transaction executions. 

COMMANDS:
	
	tx              Display transaction information
	block           Display block information
	status          Display transaction status
	curblockheight  Display the current block height

OPTIONS:
	
	--help, -h  show help
```

#### 区块信息获取

##### 通过块高度查询区块信息

```
$ ./ontology info block 1
{
   "Hash": "312fcb5739620956999c138a6d4b60682c9e9c9cff1ca37776ed77257c1ca86c",
   "Header": {
      "Version": 0,
      "PrevBlockHash": "1a9a9f5ab90dd537fb53e8f74b7519b14cea05cde95b1da33a0971a630b4040a",
      "TransactionsRoot": "0000000000000000000000000000000000000000000000000000000000000000",
      "BlockRoot": "8e927cf85381ad80ca8b267070939fd57695b4ef9b9fc5ea63e73dc716d9e45d",
      "Timestamp": 1529908576,
      "Height": 1,
      "ConsensusData": 11154013587666973726,
      "ConsensusPayload": "",
      "NextBookkeeper": "AJmM4TYyBxiQqsKZfvfCg5z66TjGx9x29P",
      "Bookkeepers": [
         "0315a692b695bc9e08dbede48ff61f52d98ad3b4cb13eb31ba2d32bf1da8e570b9"
      ],
      "SigData": [
         "43f4e406558ff79f4fd1beac9a2cb0e50f6bf839a59ada1c98ee4fcfa9ad26d4109f2f9d8c414551fc582470273bf18bf820f773520fa6083ded5ba84f36f936"
      ],
      "Hash": "312fcb5739620956999c138a6d4b60682c9e9c9cff1ca37776ed77257c1ca86c"
   },
   "Transactions": []
}
```

##### 通过块哈希查询区块信息

```
$ ./ontology info block 312fcb5739620956999c138a6d4b60682c9e9c9cff1ca37776ed77257c1ca86c
{
   "Hash": "312fcb5739620956999c138a6d4b60682c9e9c9cff1ca37776ed77257c1ca86c",
   "Header": {
      "Version": 0,
      "PrevBlockHash": "1a9a9f5ab90dd537fb53e8f74b7519b14cea05cde95b1da33a0971a630b4040a",
      "TransactionsRoot": "0000000000000000000000000000000000000000000000000000000000000000",
      "BlockRoot": "8e927cf85381ad80ca8b267070939fd57695b4ef9b9fc5ea63e73dc716d9e45d",
      "Timestamp": 1529908576,
      "Height": 1,
      "ConsensusData": 11154013587666973726,
      "ConsensusPayload": "",
      "NextBookkeeper": "AJmM4TYyBxiQqsKZfvfCg5z66TjGx9x29P",
      "Bookkeepers": [
         "0315a692b695bc9e08dbede48ff61f52d98ad3b4cb13eb31ba2d32bf1da8e570b9"
      ],
      "SigData": [
         "43f4e406558ff79f4fd1beac9a2cb0e50f6bf839a59ada1c98ee4fcfa9ad26d4109f2f9d8c414551fc582470273bf18bf820f773520fa6083ded5ba84f36f936"
      ],
      "Hash": "312fcb5739620956999c138a6d4b60682c9e9c9cff1ca37776ed77257c1ca86c"
   },
   "Transactions": []
}
```

#### 交易信息获取

```
$ ./ontology info status 93768ba53a6e55fe9d228163e39d85f3b7992feab2346053e5012ebba48b48f9
Transaction states:
{
   "TxHash": "93768ba53a6e55fe9d228163e39d85f3b7992feab2346053e5012ebba48b48f9",
   "State": 1,
   "GasConsumed": 0,
   "Notify": [
      {
         "ContractAddress": "0100000000000000000000000000000000000000",
         "States": [
            "transfer",
            "AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs",
            "AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g",
            10
         ]
      }
   ]
}
```

#### 当前块高获取

```
$ ./ontology info curblockheight
CurrentBlockHeight:5467
```

### 资产处理

教程所用到的示例账户如下所示：

```
$ ontology account list
Index:1    Address:AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs  Label: (default)
Index:2    Address:AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g  Label:
```


#### 命令概览

```
$ ./ontology asset help

Description:
   ontology asset - Handle assets

USAGE:
  ontology asset [options] command [command options] [arguments...]
  
VERSION:
  0.9
  
COMMANDS:
  transfer      Transfer ont or ong to another account
  approve       Approve another user can transfer asset
  transferfrom  Using to transfer asset after approve
  balance       Show balance of ont and ong of specified account
  allowance     Show approve balance of ont or ong of specified account
  unboundong    Show the balance of unbound ONG
  withdrawong   Withdraw ONG
  help, h       Shows a list of commands or help for one command
  
MISC OPTIONS:
  --help, -h  show help
```

#### 提取ONG

- **查询账户余额**

```
$ ./ontology asset balance AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
BalanceOf:AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
  ONT:1000000000
  ONG:0
```

- **查询未提取ONG**

```
./ontology asset unboundong AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
Unbound ONG:
  Account:AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
  ONG:7914590
```

```
$ ./ontology asset unboundong AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g
Unbound ONG:
  Account:AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g
  ONG:0
```

- **提取ONG**

```
$ ./ontology asset withdrawong AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
Password:
Withdraw ONG:
  Account:AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
  Amount:7914590
  TxHash:0ca17f47ebb4127b26cafeadabd21d96353c5c00e0392f44a573d6b7d3c0fcdd

Tip:
  Using './ontology info status 0ca17f47ebb4127b26cafeadabd21d96353c5c00e0392f44a573d6b7d3c0fcdd' to query transaction status
```

- **查询交易状态**

```
$ ./ontology info status 0ca17f47ebb4127b26cafeadabd21d96353c5c00e0392f44a573d6b7d3c0fcdd
Transaction states:
{
   "TxHash": "0ca17f47ebb4127b26cafeadabd21d96353c5c00e0392f44a573d6b7d3c0fcdd",
   "State": 1,
   "GasConsumed": 0,
   "Notify": [
      {
         "ContractAddress": "0200000000000000000000000000000000000000",
         "States": [
            "transfer",
            "AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV",
            "AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs",
            7914590000000000
         ]
      }
   ]
}
```

- **查询账户余额**

```
$ ./ontology asset balance AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
BalanceOf:AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
  ONT:1000000000
  ONG:7914590
```


#### 转账示例

##### 命令概览

```
USAGE:
	ontology asset transfer [command options]  

DESCRIPTION:
	Transfer ont or ong to another account. If from address does not specified, using default account
  
ACCOUNT OPTIONS:
	--wallet <filename>, -w <filename>  
	Use <filename> as the wallet (default: "./wallet.dat")

TXPOOL OPTIONS:

	--gasprice value  
	Using to specifies the gas price of transaction. 
	The gas price of the transaction cannot be less than the lowest gas price set by node's transaction pool, otherwise the transaction will be rejected. 
	When there are transactions that are queued for packing into the block in the transaction pool, the transaction pool will deal with transactions according to the gas price and transactions with high gas prices will be prioritized (default: 0)
 
	--gaslimit value  
	Using to specifies the gas limit of the transaction. 
	The gas limit of the transaction cannot be less than the minimum gas limit set by the node's transaction pool, otherwise the transaction will be rejected. 
	Gasprice * gaslimit is actual ONG costs. (default: 20000)

RPC OPTIONS:
	--rpcport value  Json rpc server listening port (default: 20336)

TRANSACTION OPTIONS:
	--asset <ont|ong>             Using to specifies the transfer asset <ont|ong> (default: "ont")
	--from <address|label|index>  Using to specifies the transfer-out account <address|label|index>
	--to <address|label|index>    Using to specifies the transfer-in account <address|label|index>
	--amount value                Using to specifies the transfer amount
```

##### ONT转账

- **查询账户余额**

```
$ ./ontology asset balance AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
BalanceOf:AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
  ONT:1000000000
  ONG:7914590
```

```
$ ./ontology asset balance AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g
BalanceOf:AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g
  ONT:0
  ONG:0
```


- **执行转账**

```
$ ./ontology asset transfer --asset ONT --from AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs --to AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g  --amount 10 --gaslimit 20000
Password:
Transfer ONT
  From:AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
  To:AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g
  Amount:10
  TxHash:93768ba53a6e55fe9d228163e39d85f3b7992feab2346053e5012ebba48b48f9

Tip:
  Using './ontology info status 93768ba53a6e55fe9d228163e39d85f3b7992feab2346053e5012ebba48b48f9' to query transaction status
```

- **查询交易结果**

```
$ ./ontology info status 93768ba53a6e55fe9d228163e39d85f3b7992feab2346053e5012ebba48b48f9
Transaction states:
{
   "TxHash": "93768ba53a6e55fe9d228163e39d85f3b7992feab2346053e5012ebba48b48f9",
   "State": 1,
   "GasConsumed": 0,
   "Notify": [
      {
         "ContractAddress": "0100000000000000000000000000000000000000",
         "States": [
            "transfer",
            "AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs",
            "AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g",
            10
         ]
      }
   ]
}
```

- **查询账户余额**

```
$ ./ontology asset balance AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
BalanceOf:AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
  ONT:999999990
  ONG:7914590
```

```
$ ./ontology asset balance AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g
BalanceOf:AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g
  ONT:10
  ONG:0
```

##### ONG转账

- **查询账户余额**

```
$ ./ontology asset balance AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
BalanceOf:AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
  ONT:999999990
  ONG:7914590
```

```
$ ./ontology asset balance AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g
BalanceOf:AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g
  ONT:10
  ONG:0
```

- **转账执行**

```
$ ./ontology asset transfer --asset ONG --from AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs --to AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g  --amount 10 --gaslimit 20000
Password:
Transfer ONG
  From:AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
  To:AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g
  Amount:10
  TxHash:84d7e8c98d224212f260e0034e36735ec935021818dca1b654522196be0eb624

Tip:
  Using './ontology info status 84d7e8c98d224212f260e0034e36735ec935021818dca1b654522196be0eb624' to query transaction status
```

- **查询交易结果**

```
$ ./ontology info status 84d7e8c98d224212f260e0034e36735ec935021818dca1b654522196be0eb624
Transaction states:
{
   "TxHash": "84d7e8c98d224212f260e0034e36735ec935021818dca1b654522196be0eb624",
   "State": 1,
   "GasConsumed": 0,
   "Notify": [
      {
         "ContractAddress": "0200000000000000000000000000000000000000",
         "States": [
            "transfer",
            "AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs",
            "AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g",
            10000000000
         ]
      }
   ]
}
```

- **查询账户余额**

```
$ ./ontology asset balance AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
BalanceOf:AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
  ONT:999999990
  ONG:7914580
```

```
$ ./ontology asset balance AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g
BalanceOf:AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g
  ONT:10
  ONG:10
```

#### 授权转账

- **查询账户余额**

```
$ ./ontology asset balance AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
BalanceOf:AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
  ONT:999999990
  ONG:7914580
```

```
$ ./ontology asset balance AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g
BalanceOf:AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g
  ONT:10
  ONG:10
```

- **授权转账**

```
$ ./ontology asset approve --from AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs --to AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g --amount 1.000000002  --asset ONG
Password:
Approve:
  Asset:ONG
  From:AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
  To:AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g
  Amount:1.000000002
  TxHash:219d2d3473ca0e2b9c96b938121e36e74c5fc55496142f64eb4cac9f75d3231a

Tip:
  Using './ontology info status 219d2d3473ca0e2b9c96b938121e36e74c5fc55496142f64eb4cac9f75d3231a' to query transaction status
```

- **查询交易结果**

```
$ ./ontology info status 219d2d3473ca0e2b9c96b938121e36e74c5fc55496142f64eb4cac9f75d3231a
Transaction states:
{
   "TxHash": "219d2d3473ca0e2b9c96b938121e36e74c5fc55496142f64eb4cac9f75d3231a",
   "State": 1,
   "GasConsumed": 0,
   "Notify": []
}
```

- **查询授权转账余额**

```
$ ./ontology asset allowance --from AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs --to AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g --asset ONG
Allowance:ONG
  From:AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
  To:AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g
  Balance:1.000000002
```

- **从授权账户中转账**

```
$ ./ontology asset transferfrom -from AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs --to AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g --sender AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g --amount 1.000000001 --asset ONG
Password:
Transfer from:
  Asset:ONG
  Sender:AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g
  From:AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
  To:AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g
  Amount:1.000000001
  TxHash:6dad38a2961d012ca235aa2e6b6f52157bc8710b0df60a8e6d56f9d8a83b1e68

Tip:
  Using './ontology info status 6dad38a2961d012ca235aa2e6b6f52157bc8710b0df60a8e6d56f9d8a83b1e68' to query transaction status
```

- **查询交易结果**

```
$ ./ontology info status 6dad38a2961d012ca235aa2e6b6f52157bc8710b0df60a8e6d56f9d8a83b1e68
Transaction states:
{
   "TxHash": "6dad38a2961d012ca235aa2e6b6f52157bc8710b0df60a8e6d56f9d8a83b1e68",
   "State": 1,
   "GasConsumed": 0,
   "Notify": [
      {
         "ContractAddress": "0200000000000000000000000000000000000000",
         "States": [
            "transfer",
            "AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs",
            "AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g",
            1000000001
         ]
      }
   ]
}
```

- **查询授权转账余额**

```
$ ./ontology asset allowance --from AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs --to AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g --asset ONG
Allowance:ONG
  From:AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
  To:AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g
  Balance:0.000000001
```

- **查询账户余额**

```
$ ./ontology asset balance AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
BalanceOf:AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs
  ONT:999999990
  ONG:7914578.999999999
```

```
$ ./ontology asset balance AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g
BalanceOf:AaG9jUSBTWXjeUzR3LBDiPBUPrGUbSKu3g
  ONT:10
  ONG:11.000000001
```

### 智能合约

示例智能合约如下：

```
using Neo.SmartContract.Framework.Services.Neo;
using Neo.SmartContract.Framework;
using System;
using System.ComponentModel;

namespace Neo.SmartContract
{
    public class HelloWorld : Framework.SmartContract
    {
        public static object Main(string operation, params object[] args)
        {
            switch (operation)
            {
                case "Hello":
                    Hello((string)args[0]);
                    return true;
                default:
                    return false;
            }
        }
        public static void Hello(string msg)
        {
            Runtime.Log(msg);
        }
    }
}
```

#### 命令概览

```
$ ./ontology contract help
NAME:
	ontology contract - Deploy or invoke smart contract

	Ontology CLI is an Ontology node command line Client for starting and managing Ontology nodes,
  managing user wallets, sending transactions, deploying and invoking contract, and so on.

USAGE:
	ontology contract [options] command [command options]  
  
VERSION:
	v0.9.4-17-g4c96
  
COMMANDS:
	deploy      Deploy a smart contract to ontolgoy
	invoke      Invoke smart contract
	invokeCode  Invoke smart contract by code
	help, h     Shows a list of commands or help for one command
  
MISC OPTIONS:
	--help, -h  show help
```

#### 智能合约的部署

- **部署参数概览**

```
$ ./ontology contract deploy help

USAGE:
	ontology contract deploy [command options]  
ACCOUNT OPTIONS:
	--wallet <filename>, -w <filename>                         
	Use <filename> as the wallet (default: "./wallet.dat")

	--account <address|label|index>, -a <address|label|index>
	Using to specify the account <address|label|index> when the Ontology node starts. If the account is null, it uses the wallet default account

TXPOOL OPTIONS:
	--gasprice value  
	Using to specifies the gas price of transaction. The gas price of the transaction cannot be less than the lowest gas price set by node's transaction pool, otherwise the transaction will be rejected. When there are transactions that are queued for packing into the block in the transaction pool, the transaction pool will deal with transactions according to the gas price and transactions with high gas prices will be prioritized (default: 0)

	--gaslimit value
	Using to specifies the gas limit of the transaction. The gas limit of the transaction cannot be less than the minimum gas limit set by the node's transaction pool, otherwise the transaction will be rejected. Gasprice * gaslimit is actual ONG costs. (default: 20000)

RPC OPTIONS:
  --rpcport value
  Json rpc server listening port (default: 20336)

CONTRACT OPTIONS:
  --needstore         Is need use storage in contract
  --code <path>       File path of contract code <path>
  --name <name>       Specifies contract name to <name>
  --version <ver>     Specifies contract version to <ver>
  --author <address>  Set <address> as the contract owner
  --email <email>     Set <email> owner's email address
  --desc <text>       Set <text> as the description of the contract
  --prepare, -p       Prepare deploy contract without commit to ledger
```

- **部署示例**

- 在[SmartX](http://smartx.ont.io/)上编译后得到**NVM字节码**

```
54c56b6c766b00527ac46c766b51527ac4616c766b00c36c766b52527ac46c766b52c30548656c6c6f87630600621a006c766b51c300c36165230061516c766b53527ac4620e00006c766b53527ac46203006c766b53c3616c756651c56b6c766b00527ac4616c766b00c361681253797374656d2e52756e74696d652e4c6f6761616c7566
```

- 将`MVN字节码`保存到本地

- 利用`--code`参数指定保存到本地的`MVN字节码`路径

```
$ ./ontology contract deploy --name=Hello --code=/home/user/Desktop/Hello.avm --author=AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs --desc=example --email=hello@ontology.com --needstore --gaslimit=100000000
Password:
Deploy contract:
  Contract Address:79102ef95cf75cab8e7f9a583c9d2b2b16fbce70
  TxHash:ae76366e743be69b546a3552c30152024f1b5d539b74aa1f12e06bbff98e8bc8

Tip:
  Using './ontology info status ae76366e743be69b546a3552c30152024f1b5d539b74aa1f12e06bbff98e8bc8' to query transaction status
```

- 通过交易哈希值查询合约部署状态

```
$ ./ontology info status ae76366e743be69b546a3552c30152024f1b5d539b74aa1f12e06bbff98e8bc8
Transaction states:
{
   "TxHash": "ae76366e743be69b546a3552c30152024f1b5d539b74aa1f12e06bbff98e8bc8",
   "State": 1,
   "GasConsumed": 0,
   "Notify": []
}
```

其中，`"State"`为`1`表明合约已经成功部署。

- 查看合约详细信息

```
$ ./ontology info tx ae76366e743be69b546a3552c30152024f1b5d539b74aa1f12e06bbff98e8bc8
{
   "Version": 0,
   "Nonce": 1530326262,
   "GasPrice": 0,
   "GasLimit": 100000000,
   "Payer": "AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs",
   "TxType": 208,
   "Payload": {
      "Code": "54c56b6c766b00527ac46c766b51527ac4616c766b00c36c766b52527ac46c766b52c30548656c6c6f87630600621a006c766b51c300c36165230061516c766b53527ac4620e00006c766b53527ac46203006c766b53c3616c756651c56b6c766b00527ac4616c766b00c361681253797374656d2e52756e74696d652e4c6f6761616c7566",
      "NeedStorage": true,
      "Name": "Hello",
      "CodeVersion": "",
      "Author": "AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs",
      "Email": "hello@ontology.com",
      "Description": "example"
   },
   "Attributes": [],
   "Sigs": [
      {
         "PubKeys": [
            "032cf2191a24c6bee28abbee0c4b5265dc841394f2794c1fb18e52ffb2c9d7c9c6"
         ],
         "M": 1,
         "SigData": [
            "98fbef0e3e2c4433b13fd255df7a96c473ad75d0ed202bc980ae987688324ac4d8728dc1f4d5c273fbac6a3bb84e1e1ed803fc01d9bfe981fb256704c39f2307"
         ]
      }
   ],
   "Hash": "ae76366e743be69b546a3552c30152024f1b5d539b74aa1f12e06bbff98e8bc8"
}
```

#### 智能合约的执行

##### 按合约地址执行

- **命令概览**

```
USAGE:
	ontology contract invokeCode [command options]  

ACCOUNT OPTIONS:	
	--wallet <filename>, -w <filename>                         
	Use <filename> as the wallet (default: "./wallet.dat")

	--account <address|label|index>, -a <address|label|index>  
	Using to specify the account <address|label|index> when the Ontology node starts. 
	If the account is null, it uses the wallet default account

TXPOOL OPTIONS:
	--gasprice value
	Using to specifies the gas price of transaction. 
	The gas price of the transaction cannot be less than the lowest gas price set by node's transaction pool, otherwise the transaction will be rejected. 
	When there are transactions that are queued for packing into the block in the transaction pool, the transaction pool will deal with transactions according to the gas price and transactions with high gas prices will be prioritized (default: 0)

	--gaslimit value  
	Using to specifies the gas limit of the transaction. 
	The gas limit of the transaction cannot be less than the minimum gas limit set by the node's transaction pool, otherwise the transaction will be rejected. Gasprice * gaslimit is actual ONG costs. (default: 20000)

RPC OPTIONS:
	--rpcport value  
	Json rpc server listening port (default: 20336)

CONTRACT OPTIONS:
	--code <path>  
	File path of contract code <path>
	
	--prepare, -p  
	Prepare invoke contract without commit to ledger
```

- **预执行智能合约**

通过智能合约的预执行，可以获得当前合约执行所需要的`Gaslimit`,从而为智能合约的实际执行设置`Gaslimit`设置提供参考，避免由于**ONG**余额不足造成的执行失败。

```
$ ./ontology contract invoke --address 79102ef95cf75cab8e7f9a583c9d2b2b16fbce70 --params string:Hello,[string:Hello] --prepare --return bool
Invoke:70cefb162b2b9d3c589a7f8eab5cf75cf92e1079 Params:["Hello",["Hello"]]
Contract invoke successfully
  Gaslimit:20000
  Return:true
```

- **执行智能合约**

```
$ ./ontology contract invoke --address 79102ef95cf75cab8e7f9a583c9d2b2b16fbce70 --params string:Hello,[string:Hello] --gaslimit 20000
Invoke:70cefb162b2b9d3c589a7f8eab5cf75cf92e1079 Params:["Hello",["Hello"]]
Password:
  TxHash:1d033ebeec3a833c0cc31ce9d78876d3464d60d8816be6d143582cb5d7409610

Tip:
  Using './ontology info status 1d033ebeec3a833c0cc31ce9d78876d3464d60d8816be6d143582cb5d7409610' to query transaction status
```

- **通过交易哈希值查询合约执行状态**

```
$ ./ontology info status 1d033ebeec3a833c0cc31ce9d78876d3464d60d8816be6d143582cb5d7409610
Transaction states:
{
   "TxHash": "1d033ebeec3a833c0cc31ce9d78876d3464d60d8816be6d143582cb5d7409610",
   "State": 1,
   "GasConsumed": 0,
   "Notify": []
}
```

##### 按字节码执行

```
using Neo.SmartContract.Framework.Services.Neo;
using Neo.SmartContract.Framework;
using System;
using System.ComponentModel;

namespace Neo.SmartContract
{
    public class HelloWorld : Framework.SmartContract
    {
        public static object Main()
        {
            string operation = "Hello";
            Hello(operation);
            return true;
       
        }
        public static void Hello(string msg)
        {
            Runtime.Log(msg);
        }
    }
}
```

- **预执行智能合约**

```
$ ./ontology contract invokeCode --code "/home/wdx7266/Desktop/Hello World.avm" --prepare
Contract pre-invoke successfully
Gas consumed:20000
Return:01 (raw value)
```

- **部署智能合约**

```
$ ./ontology contract deploy --name="Hello World" --code="/home/wdx7266/Desktop/Hello World.avm" --author=AKFMnJT1u5pyPhzGRuauD1KkyUvqjQsmGs --desc=example --email=hello@ontology.com --needstore --gaslimit=20000
Password:
Deploy contract:
  Contract Address:72f52a2202b63891f92f9f5c756d9b7b63dd04aa
  TxHash:cf1a628e74a190d9471cde8571e607348af43c17557759f9e109bd72b83a9d1e

Tip:
  Using './ontology info status cf1a628e74a190d9471cde8571e607348af43c17557759f9e109bd72b83a9d1e' to query transaction status
```

- **查询合约部署状态**

```
$ ./ontology info status 23d8f080b4cca62c9966503c1696b6709f626fd89c5ee2106ec251e18c03abbb
Transaction states:
{
   "TxHash": "23d8f080b4cca62c9966503c1696b6709f626fd89c5ee2106ec251e18c03abbb",
   "State": 1,
   "GasConsumed": 0,
   "Notify": []
}
```


- **执行智能合约**

```
$ ./ontology contract invokeCode --code "/home/wdx7266/Desktop/Hello World.avm" --gaslimit 20000
Password:
TxHash:7a457e0a9856d8b9c3c69a5098820299a21d70f33acc3d08c8ec1c9790f20025

Tip:
  Using './ontology info status 7a457e0a9856d8b9c3c69a5098820299a21d70f33acc3d08c8ec1c9790f20025' to query transaction status
```

- **查询合约执行状态**

```
$ ./ontology info status 7a457e0a9856d8b9c3c69a5098820299a21d70f33acc3d08c8ec1c9790f20025
Transaction states:
{
   "TxHash": "7a457e0a9856d8b9c3c69a5098820299a21d70f33acc3d08c8ec1c9790f20025",
   "State": 1,
   "GasConsumed": 0,
   "Notify": []
}
```

### 区块导出与导入


#### 命令概览

```
USAGE:
	ontology export [command options] [arguments...]
RPC OPTIONS:
	--rpcport value
	Json rpc server listening port (default: 20336)

EXPORT OPTIONS:
	--file value     
	Path of export file (default: "./blocks.dat")

	--height value   
	Using to specifies the height of the exported block.
	When height of the local node's current block is greater than the height required for export, the greater part will not be exported.
	Height is equal to 0, which means exporting all the blocks of the current node. (default: 0)

	--speed <h|m|l>
	Export block speed, <h|m|l> h for high speed, m for middle speed and l for low speed (default: "m")
```


#### 区块导出

```
$ ./ontology export
Start export.
Block(362/362) [====================================================================] 100%    1s
Export blocks successfully.
Total blocks:363
Export file:./blocks.dat
```

#### 区块导入

```
$ ./ontology import
[INFO ] GID 1, Config init success
[INFO ] GID 1, deploy contract address:0239dcf9b4a46f15c5f23f20d52fac916a0bac0d
[INFO ] GID 1, deploy contract address:08b6dcfed2aace9190a44ae34a320e42c04b46ac
[INFO ] GID 1, deploy contract address:7a2f84e3b94d20da1a8592116c0103c28c5e457e
[INFO ] GID 1, deploy contract address:6815cbe7b4dbad4d2d09ae035141b5254a002f79
[INFO ] GID 1, deploy contract address:24a15c6aed092dfaa711c4974caf1e9d307bf4b5
[INFO ] GID 1, deploy contract address:4d6934f0a524a084bb20cff4cdbea236760bb4a3
[INFO ] GID 1, GenesisBlock init success. GenesisBlock hash:b5380192526717ecc7bb8086d8754444f6e8e423fecf4ea1f39e55a779d7bef7

[INFO ] GID 1, Ledger init success
[INFO ] GID 1, getGasPriceLimitConfig: gasPrice 0, configure 0
[INFO ] GID 1, TxPool init success
[INFO ] GID 1, init peer ID to 4161297767523662910
……
```