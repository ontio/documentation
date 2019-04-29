
# Sigsvr plus rpc for exchanges
This article mainly covers creating wallet and account, motinoring deposits and signing for withdrawal through sigsvr and rpc.
- [Sigsvr plus rpc for exchanges](#sigsvr-plus-rpc-for-exchanges)
    - [1. Prepation to run ontology and synchronize ontology node](#1-prepation-to-run-ontology-and-synchronize-ontology-node)
    - [2. Server Side](#2-server-side)
        - [2.1 Create Wallet through Cli](#21-create-wallet-through-cli)
            - [2.1.1 Notes about Cli](#211-notes-about-cli)
        - [2.2 Create account and export wallet file through Sigsvr](#22-create-account-and-export-wallet-file-through-sigsvr)
            - [2.2.1 Postman](#221-postman)
            - [2.2.2 Start Sigsvr](#222-start-sigsvr)
        - [2.2.3 Post through Postman](#223-post-through-postman)
        - [2.2.4 Export wallet file](#224-export-wallet-file)
        - [2.2.5 Signature server method introduction](#225-signature-server-method-introduction)
    - [3. Start ontology node](#3-start-ontology-node)
    - [4. Process the asset transaction](#4-process-the-asset-transaction)
        - [4.1 Sign for withdrawal](#41-sign-for-withdrawal)
            - [4.1.1 Construct transaction through post method 1](#411-construct-transaction-through-post-method-1)
            - [4.1.2 Construct transaction through post method 2](#412-construct-transaction-through-post-method-2)
            - [4.1.3 Asset option](#413-asset-option)
        - [4.2 Monitor the deposit](#42-monitor-the-deposit)
            - [4.2.1 Get current block height](#421-get-current-block-height)
                - [4.2.1.1 Through Cli](#4211-through-cli)
                - [4.2.1.2 Getblockcount through Post](#4212-getblockcount-through-post)
            - [4.2.2 Monitor block info](#422-monitor-block-info)
                - [4.2.2.1 Through Cli](#4221-through-cli)
                - [4.2.2.2 Getblock through post](#4222-getblock-through-post)
            - [4.2.3 Get the transaction execution info](#423-get-the-transaction-execution-info)
                - [4.2.3.1 Through Cli](#4231-through-cli)
                - [4.2.3.2 Getrawtransaction through post](#4232-getrawtransaction-through-post)
    - [5. Unbound Ong and withdraw](#5-unbound-ong-and-withdraw)
        - [5.1 Check unbound ong](#51-check-unbound-ong)
            - [5.1.1 Through Cli](#511-through-cli)
            - [5.1.2 Getunboundong through post](#512-getunboundong-through-post)
        - [5.2 Withdraw ong](#52-withdraw-ong)
            - [5.2.1 Through Cli](#521-through-cli)
            - [5.2.2 Withdrawong through post](#522-withdrawong-through-post)




## 1. Prepation to run ontology and synchronize ontology node 

To run ontology, you can get it from [the source](https://github.com/ontio/ontology/blob/master/README.md)
Or, get it from [the release page](https://github.com/ontio/ontology/releases).

## 2. Server Side

### 2.1 Create Wallet through Cli

Use ontology Cli to Create Wallet and add account based on your need. For more info about how to use ontology cli, please go to [Cli Instruction](https://github.com/ontio/ontology/blob/master/docs/specifications/cli_user_guide.md).

```
C:\Go_WorkSpace\src\github.com\ontio\ontology (master -> origin)
λ ontology account add -d
Use default setting '-t ecdsa -b 256 -s SHA256withECDSA'
        signature algorithm: ecdsa
        curve: P-256
        signature scheme: SHA256withECDSA
Password:
Re-enter Password:
Index:3
Label:
Address:AUPd1sZDcdgCy8dKwsvTvT4gjDdtB3w57w
Public key:02dac6dd6595edf1c3679a3fc16fe80d434e511263452c16adb82f35a82d2a469c
Signature scheme:SHA256withECDSA
Create account successfully.
```
```
ontology account add --default
```

#### 2.1.1 Notes about Cli

The exchange needs to create online wallet to manage the users' account. The wallet file contains info about account (including public key and private key), contract hash script and so on. It's most important for exchanges to validate their users. Please make sure the wallet file and password are safe and confidential. The exchange can use one wallet file to store all the users account info, or use the hard wallet (offline wallet) to make it safer.

There are two methods to create the accounts.
One way is to automatically create accounts for users. The first time when one user wants to deposit ONT/ONG, you can program to automatically create account for him.
Another way is to create plenty of ONT address (accounts), then allocate one address to one user when this user wants to deposit for the first time. To create some accounts in advance, run ```./ontology account add -n [n] -w [wallet file] ```command.

-d is optional, the default value is 1

-w is the designated wallet file, the default is wallet.dat

-n is the number of accounts(address) you want to create.

For example
```
ontology account add -n 10 -d -w wat.dat
```

### 2.2 Create account and export wallet file through Sigsvr

#### 2.2.1 Postman
Prepare [Postman](https://www.getpostman.com), and install it.
Set the method as "POST", set the url as "http://127.0.0.1:20000/cli"

#### 2.2.2 Start Sigsvr
```
./sigsvr
```

### 2.2.3 Post through Postman
```
{
	"qid":"t",
	"method":"createaccount",
	"pwd":"XXXX",     //the password of the newly created account
	"params":{}
}
```
Then you can see the account was created
```
2018/09/07 11:37:30.774727 [INFO ] GID 38, [CreateAccount]{"address":"AJdh41doGw1Ty79baVG9Xdari34zkP2FCS","enc-alg":"aes-256-gcm","key":"JCvluLJ8J/SOChZtM3GvWFvyyNS37Yo3X7wV4lFIAQmimjAhC+2TEuflrVI7zR+e","algorithm":"ECDSA","salt":"jj99HOalCPW8T9nOTOQdcA==","parameters":{"curve":"P-256"},"label":"","publicKey":"0356aa6706c089eb045a9d0b123f581a5ccebbf61e85c462d57a2952b34c7a84be","signatureScheme":"SHA256withECDSA","isDefault":false,"lock":false}
2018/09/07 11:37:30.776665 [INFO ] GID 38, [CliRpcResponse]{"qid":"t","method":"createaccount","result":{"account":"AJdh41doGw1Ty79baVG9Xdari34zkP2FCS"},"error_code":0,"error_info":""}
```
### 2.2.4 Export wallet file

Through Postman post: 
```
{
	"qid":"t",
	"method":"exportaccount",
	"pwd":"111111",
	"params":{	"wallet_path":"$GOPATH$src/github.com/ontio/ontology/sigsvr_wallet"     // the designated wallet path
	}
}
```
Then the wallet file will be exported.

### 2.2.5 Signature server method introduction

Currently, Sigsvr supports signing for data, normal transaction, multiSig transaction, construction of Native contract invoking, construction of NeoVM contract invoking.

Signature server is one json formatted rpc server. It can be used by posting messages. 

The posted server path should be set as 
http://localhost:20000/cli.

The post structure should be
```
{
    "qid":"XXX",    //request ID，the answer will have the same ID
    "method":"XXX", //the request method name
    "account":"XXX",//signature account
    "pwd":"XXX",    //account unlocking password
    "params":{
        //Request parameters should be consistent with the method name
    }
}
```
The answer structure is 
```
{
    "qid": "XXX",   //request ID
    "method": "XXX",//request method name
    "result": {     //answering result
        "signed_tx": "XXX"  //tx after signature
    },
    "error_code": 0,//Error code, zero (0) means success，nonzeor means failure
    "error_info": ""//error description
}
```
## 3. Start ontology node
Here we start in testmode, for testnet or mainnet, refer to [run-ontology](https://github.com/ontio/ontology/blob/master/README.md#run-ontology)
```
C:\Go_WorkSpace\src\github.com\ontio\ontology (master -> origin)
λ ontology --testmode --gasprice=0
```


## 4. Process the asset transaction

### 4.1 Sign for withdrawal 

#### 4.1.1 Construct transaction through post method 1

In "sigtransfertx" method, the transaction payer account is the signing account by default. If it's needed to designate other account as payer, you can use "payer" parameter. Note that if you designate the payer account, "sigrawtx" will be used to sign the result of posting "sigtransfertx" method. We will give the details in 4.1.2
```
{
    "qid":"t",
    "method":"sigtransfertx",
    "account":"AdXadq2bYykdbopzHNqYymtvw2eQmnoMRs",
    "pwd":"111111",
    "params":{
    	"gas_price":0,
    	"gas_limit":20000,
    	"asset":"ont",
    	"from":"AdXadq2bYykdbopzHNqYymtvw2eQmnoMRs",
    	"to":"AeV2sjPqd3HPg4yE1EJm1HSy62xDYYZ3ps",
    	"amount":"10"
    }
}
```
Then we will get the signed_tx.
```
{
    "qid": "t",
    "method": "sigtransfertx",
    "result": {
        "signed_tx": "00d1cbf8915b0000000000000000204e000000000000ee9ebe462361fd252ebf81504bcaa75bdb1eed7e6e00c66b6a14ee9ebe462361fd252ebf81504bcaa75bdb1eed7ec86a14f91b8663ad7c5729c365e37ccfcec379ab6afce6c86a5ac86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65000141400a1b898fe16ae20d25bd50a189170b3670e097761f85cad6a438d59a7c2d660f070284a9655c94f352ff39f289094ddf5c742f3f14125b0a68bd3ba8a695afd3232102bc256745a6c3e20117b5214f12b2132f863b0087730f42dc3fbd12a1c3847d67ac"
    },
    "error_code": 0,
    "error_info": ""
}
```
Then, in ontology cli, run the following. Note that signed_tx should be the above returned result.
```
./ontology sendtx "signed_tx"
```
The transaction will be broadcast.


#### 4.1.2 Construct transaction through post method 2
We set the "payer" not equal to "from".
```
{
    "qid":"t",
    "method":"sigtransfertx",
    "account":"AeV2sjPqd3HPg4yE1EJm1HSy62xDYYZ3ps",
    "pwd":"111111",
    "params":{
    	"gas_price":0,
    	"gas_limit":20000,
    	"asset":"ont",
    	"from":"AeV2sjPqd3HPg4yE1EJm1HSy62xDYYZ3ps",
    	"to":"AUPd1sZDcdgCy8dKwsvTvT4gjDdtB3w57w",
    	"amount":"3",
    	"payer":"AdXadq2bYykdbopzHNqYymtvw2eQmnoMRs"
    }
}
```
We get 
```
{
    "qid": "t",
    "method": "sigtransfertx",
    "result": {
        "signed_tx": "00d11a06925b0000000000000000204e000000000000ee9ebe462361fd252ebf81504bcaa75bdb1eed7e6e00c66b6a14f91b8663ad7c5729c365e37ccfcec379ab6afce6c86a148a644531653e932afc8c40ed2f6fcd6b39e54bfec86a53c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b650001414005c16c9dbd723b77d16b21c9a677053db2434c298b30e83e0b502b8ffba745a3975e4da1b951c49e3574a6d5ef812da690baa1964c4bac1abe46e96ba849cbb7232103b82aaa9682aca3d147c4d8daa06553d2184b313863ff0071b99f56d51457a3ceac"
    },
    "error_code": 0,
    "error_info": ""
}
```
Then Post to get the tx signed by account "AdXadq2bYykdbopzHNqYymtvw2eQmnoMRs".
```
{
    "qid":"t",
    "method":"sigrawtx",
    "account":"AdXadq2bYykdbopzHNqYymtvw2eQmnoMRs",
    "pwd":"111111",
    "params":{
    	"raw_tx":"00d11a06925b0000000000000000204e000000000000ee9ebe462361fd252ebf81504bcaa75bdb1eed7e6e00c66b6a14f91b8663ad7c5729c365e37ccfcec379ab6afce6c86a148a644531653e932afc8c40ed2f6fcd6b39e54bfec86a53c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b650001414005c16c9dbd723b77d16b21c9a677053db2434c298b30e83e0b502b8ffba745a3975e4da1b951c49e3574a6d5ef812da690baa1964c4bac1abe46e96ba849cbb7232103b82aaa9682aca3d147c4d8daa06553d2184b313863ff0071b99f56d51457a3ceac"
    }
}
```
The returned result is
```
{
    "qid": "t",
    "method": "sigrawtx",
    "result": {
        "signed_tx": "00d11a06925b0000000000000000204e000000000000ee9ebe462361fd252ebf81504bcaa75bdb1eed7e6e00c66b6a14f91b8663ad7c5729c365e37ccfcec379ab6afce6c86a148a644531653e932afc8c40ed2f6fcd6b39e54bfec86a53c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b650002414005c16c9dbd723b77d16b21c9a677053db2434c298b30e83e0b502b8ffba745a3975e4da1b951c49e3574a6d5ef812da690baa1964c4bac1abe46e96ba849cbb7232103b82aaa9682aca3d147c4d8daa06553d2184b313863ff0071b99f56d51457a3ceac4140d294c403ed5852285760b224b2c84da4c1694e5062e07665fe60325f39f9f24c14fe99c50c2d651c0ec93a91b06e46b51b3ce9661afc9497fabe6221a66535ce232102bc256745a6c3e20117b5214f12b2132f863b0087730f42dc3fbd12a1c3847d67ac"
    },
    "error_code": 0,
    "error_info": ""
}
```
Then go to ontology cli, and run the following. Note that signed_tx should be the above returned result.
```
./ontology sendtx "signed_tx" 
```
#### 4.1.3 Asset option

You can set the "asset" parameters as "ont" or "ong"


### 4.2 Monitor the deposit

Set the postman url as http://127.0.0.1:20336.

#### 4.2.1 Get current block height

##### 4.2.1.1 Through Cli

In ontology cli, run ./ontology info curblockheight.
```
C:\Go_WorkSpace\src\github.com\ontio\ontology (master -> origin)
λ ontology info curblockheight
CurrentBlockHeight:1972
```
##### 4.2.1.2 Getblockcount through Post

method: "getblockcount", params: null, return: blockheight

Post 
```
{
  "jsonrpc": "2.0",
  "method": "getblockcount",
  "params": [],
  "id": 1
}
```
You will get 
```
{
    "desc": "SUCCESS",
    "error": 0,
    "id": 1,
    "jsonrpc": "2.0",
    "result": 1972
}
```

#### 4.2.2 Monitor block info

##### 4.2.2.1 Through Cli

In ontology cli, run 
```
./ontology info block <block number | block hash>

C:\Go_WorkSpace\src\github.com\ontio\ontology (master -> origin)
λ ontology info block 1972
{
    "Hash": "f5b8188802c44701de722b7fa8aa0c59211052e93fc256957c5c300398ca7865",
    "Size": 499,
    "Header": {
        "Version": 0,
        "PrevBlockHash": "07721261e49a9bc752c8bfd4e60b23a3a935076758aaef5ebb4441e2e15773c9",
        "TransactionsRoot": "34fd01ebfcd21d2b805149a225f319ccffdfc0489c28da23638522fcff651567",
        "BlockRoot": "4692dec9b8c3aef693b2f5d02d27e06b14fa3cbd616bcdf844ef358b4367b452",
        "Timestamp": 1536299652,
        "Height": 1972,
        "ConsensusData": 11057278166103331997,
        "ConsensusPayload": "",
        "NextBookkeeper": "AdXadq2bYykdbopzHNqYymtvw2eQmnoMRs",
        "Bookkeepers": [
            "02bc256745a6c3e20117b5214f12b2132f863b0087730f42dc3fbd12a1c3847d67"
        ],
        "SigData": [
            "78d0a67ca7d7451cf5688be97b1ee014f831d55089af9c241832f2b811c44c35ef1a05eba0143169e3c244c6c4a31994c7bb4ea0e1b73ec8df2dd23dd008520c"
        ],
        "Hash": "f5b8188802c44701de722b7fa8aa0c59211052e93fc256957c5c300398ca7865"
    },
    "Transactions": [
        {
            "Version": 0,
            "Nonce": 1536299650,
            "GasPrice": 0,
            "GasLimit": 20000,
            "Payer": "AdXadq2bYykdbopzHNqYymtvw2eQmnoMRs",
            "TxType": 209,
            "Payload": {
            "Code": "00c66b6a14ee9ebe462361fd252ebf81504bcaa75bdb1eed7ec86a14f91b8663ad7c5729c365e37ccfcec379ab6afce6c86a51c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65",
            "GasLimit": 0
            },
            "Attributes": [],
            "Sigs": [
            {
                "PubKeys": [
                    "02bc256745a6c3e20117b5214f12b2132f863b0087730f42dc3fbd12a1c3847d67"
                ],
                "M": 1,
                "SigData": [
                    "a360394db961ee468ea7c9cc1f5361e9a8434ad9e88d0a37e08c866067cf7c1bcf6f83f93a68ad1f705b00a3d08f6d9da979fa7cebb7b072038572052b0a6a1e"
                ]
            }
            ],
            "Hash": "34fd01ebfcd21d2b805149a225f319ccffdfc0489c28da23638522fcff651567",
            "Height": 0
        }
    ]
}
```
##### 4.2.2.2 Getblock through post

method: "getblock", params: hash/height, return: block info.
```
{
  "jsonrpc": "2.0",
  "method": "getblock",
  "params": ["f5b8188802c44701de722b7fa8aa0c59211052e93fc256957c5c300398ca7865", 1],
  "id": 1
}
```
or
```
{
  "jsonrpc": "2.0",
  "method": "getblock",
  "params": [1972, 1],
  "id": 1
}
```
Here, 1 in "params" list is the verbose parameter. By default verbose=0, the serialized hex string info is returned. then we have to use SDK to deserialize it in order to get the block detailed info. When we set verbose=1, the json style understandable block info will be returned.
You will get
```
{
    "desc": "SUCCESS",
    "error": 0,
    "id": 1,
    "jsonrpc": "2.0",
    "result": {
        "Hash": "f5b8188802c44701de722b7fa8aa0c59211052e93fc256957c5c300398ca7865",
        "Size": 499,
        "Header": {
            "Version": 0,
            "PrevBlockHash": "07721261e49a9bc752c8bfd4e60b23a3a935076758aaef5ebb4441e2e15773c9",
            "TransactionsRoot": "34fd01ebfcd21d2b805149a225f319ccffdfc0489c28da23638522fcff651567",
            "BlockRoot": "4692dec9b8c3aef693b2f5d02d27e06b14fa3cbd616bcdf844ef358b4367b452",
            "Timestamp": 1536299652,
            "Height": 1972,
            "ConsensusData": 11057278166103331997,
            "ConsensusPayload": "",
            "NextBookkeeper": "AdXadq2bYykdbopzHNqYymtvw2eQmnoMRs",
            "Bookkeepers": [
                "02bc256745a6c3e20117b5214f12b2132f863b0087730f42dc3fbd12a1c3847d67"
            ],
            "SigData": [
                "78d0a67ca7d7451cf5688be97b1ee014f831d55089af9c241832f2b811c44c35ef1a05eba0143169e3c244c6c4a31994c7bb4ea0e1b73ec8df2dd23dd008520c"
            ],
            "Hash": "f5b8188802c44701de722b7fa8aa0c59211052e93fc256957c5c300398ca7865"
        },
        "Transactions": [
            {
                "Version": 0,
                "Nonce": 1536299650,
                "GasPrice": 0,
                "GasLimit": 20000,
                "Payer": "AdXadq2bYykdbopzHNqYymtvw2eQmnoMRs",
                "TxType": 209,
                "Payload": {
                    "Code": "00c66b6a14ee9ebe462361fd252ebf81504bcaa75bdb1eed7ec86a14f91b8663ad7c5729c365e37ccfcec379ab6afce6c86a51c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65",
                    "GasLimit": 0
                },
                "Attributes": [],
                "Sigs": [
                    {
                        "PubKeys": [
                            "02bc256745a6c3e20117b5214f12b2132f863b0087730f42dc3fbd12a1c3847d67"
                        ],
                        "M": 1,
                        "SigData": [
                            "a360394db961ee468ea7c9cc1f5361e9a8434ad9e88d0a37e08c866067cf7c1bcf6f83f93a68ad1f705b00a3d08f6d9da979fa7cebb7b072038572052b0a6a1e"
                        ]
                    }
                ],
                "Hash": "34fd01ebfcd21d2b805149a225f319ccffdfc0489c28da23638522fcff651567",
                "Height": 0
            }
        ]
    }
}
```
#### 4.2.3 Get the transaction execution info

##### 4.2.3.1 Through Cli

In cli, run 
```
./ontology info status <TxHash>
```
You will get
```
C:\Go_WorkSpace\src\github.com\ontio\ontology (master -> origin)
λ ontology info status 34fd01ebfcd21d2b805149a225f319ccffdfc0489c28da23638522fcff651567
Transaction states:
{
   "TxHash": "34fd01ebfcd21d2b805149a225f319ccffdfc0489c28da23638522fcff651567",
   "State": 1,
   "GasConsumed": 0,
   "Notify": [
      {
         "ContractAddress": "0100000000000000000000000000000000000000",
         "States": [
            "transfer",
            "AdXadq2bYykdbopzHNqYymtvw2eQmnoMRs",
            "AeV2sjPqd3HPg4yE1EJm1HSy62xDYYZ3ps",
            1
         ]
      }
   ]
}
```
Explanation:
```
"TxHash": the transaction hash.
"State" = 1: Success, "State" = 0: Failure.
"GasConsumed": the consumed gas for this transaction.
Notify:
	ContractAddress: 
		0100000000000000000000000000000000000000<=>ONT, 
		0200000000000000000000000000000000000000<=>ONG.
	States:
		1st element: "transfer"--invoked method
		2nd element: from address
		3rd element: to address
		4th element: amount (for Ont, it's integer, for ont, it's [ong amount to be transferred]X10^9 )
```
What you need to do is to filter the "to address". When it's detected that "to address" is one of your users account address, then it can be recorded that that user has deposited some ong/ont to his account.

##### 4.2.3.2 Getrawtransaction through post

method:"getrawtransaction", params: txhash, return: transaction detailed info. 

Post
```
{
  "jsonrpc": "2.0",
  "method": "getrawtransaction",
  "params": ["34fd01ebfcd21d2b805149a225f319ccffdfc0489c28da23638522fcff651567"],
  "id": 1
}
```
You will get
```
{
    "desc": "SUCCESS",
    "error": 0,
    "id": 1,
    "jsonrpc": "2.0",
    "result": "00d18212925b0000000000000000204e000000000000ee9ebe462361fd252ebf81504bcaa75bdb1eed7e6e00c66b6a14ee9ebe462361fd252ebf81504bcaa75bdb1eed7ec86a14f91b8663ad7c5729c365e37ccfcec379ab6afce6c86a51c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b6500014140a360394db961ee468ea7c9cc1f5361e9a8434ad9e88d0a37e08c866067cf7c1bcf6f83f93a68ad1f705b00a3d08f6d9da979fa7cebb7b072038572052b0a6a1e232102bc256745a6c3e20117b5214f12b2132f863b0087730f42dc3fbd12a1c3847d67ac"
}
```

## 5. Unbound Ong and withdraw

### 5.1 Check unbound ong

#### 5.1.1 Through Cli

In cli, 
```
./ontology asset unboundong <address|index|label> 
```
#### 5.1.2 Getunboundong through post

method: "getunboundong", params: address, return: 
```
{
  "jsonrpc": "2.0",
  "method": "getunboundong",
  "params": ["AdXadq2bYykdbopzHNqYymtvw2eQmnoMRs"],
  "id": 1
}
```
You will get
```
{
    "desc": "SUCCESS",
    "error": 0,
    "id": 1,
    "jsonrpc": "2.0",
    "result": "50429999676900"
}
```
### 5.2 Withdraw ong

#### 5.2.1 Through Cli

In cli, 
```
./ontology asset withdrawong <address|index|label>
```
#### 5.2.2  Withdrawong through post
```
{
    "Qid":"t",
    "Method":"signativeinvoketx",
    "account":"AdXadq2bYykdbopzHNqYymtvw2eQmnoMRs",
    "pwd":"111111",
    "Params":{
    	"gas_price":0,
    	"gas_limit":20000,
    	"address":"0200000000000000000000000000000000000000",
    	"method":"transferFrom",
    	"version":0,
    	"payer":"AdXadq2bYykdbopzHNqYymtvw2eQmnoMRs",
    	"params":[
    			"AdXadq2bYykdbopzHNqYymtvw2eQmnoMRs",
    			"AFxSzt7GAW8Ys4PUhN5x6UkmMBgmVU6BWz",
    			"AdXadq2bYykdbopzHNqYymtvw2eQmnoMRs",
    			"1000"
    	]
    }
}
```
Explanation
```
"account": signing account
"pwd": password
In params:
	1st address -- sender:  
	2nd address -- base58 address of ONG contract big endian script hash
	3rd address -- the address to receive the withdrawal ong
	4th value   -- the value of ong (actual ong = value/10^9)
```
Then you will get
```
{
    "qid": "t",
    "method": "signativeinvoketx",
    "result": {
        "signed_tx": "00d12331925b0000000000000000204e000000000000ee9ebe462361fd252ebf81504bcaa75bdb1eed7e8900c66b6a14ee9ebe462361fd252ebf81504bcaa75bdb1eed7ec86a140000000000000000000000000000000000000001c86a14ee9ebe462361fd252ebf81504bcaa75bdb1eed7ec86a02e803c86c0c7472616e7366657246726f6d1400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b6500014140670a9224264d51c52d1a6e7590040cb9315b4235da23722b5e5b8035eb43c6388633c31b9e4f7688777ef3fa3d2bac759b9c0e809752a7983288f4a980f84dea232102bc256745a6c3e20117b5214f12b2132f863b0087730f42dc3fbd12a1c3847d67ac"
    },
    "error_code": 0,
    "error_info": ""
}
```
Then go to cli, run 
```
./ontology sendtx "signed_tx"
```
Then check you ong balance.
