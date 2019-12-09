# 取引所のSigsvr plus rpc
この記事では、主にsigsvrおよびrpcによる財布とアカウントの作成、入金の監視、引き出しの署名について説明します。



* [取引所のSigsvr plus rpc](#取引所のSigsvr-plus-rpc)
	* [1.ontologyを実行する準備とontologyノードの同期](#1.ontologyを実行する準備とontologyノードの同期)
	* [2.サーバ側](#2.サーバ側)
		* [2.1Cliを使用して財布の作成](#2.1Cliを使用して財布の作成)
			* [2.1.1Cliについての注意事項](#2.1.1Cliについての注意事項)
		* [2.2アカウントを作成し、Sigsvrを通じてWalletファイルをエクスポート](#2.2アカウントを作成し、Sigsvrを通じてWalletファイルをエクスポート)
			* [2.2.1Postman](#2.2.1Postman)
			* [2.2.2 Sigsvrを起動](#2.2.2 Sigsvrを起動)
		* [2.2.3PostmanによるPost](#2.2.3PostmanによるPost)
		* [2.2.4財布ファイルをエクスポートする](#2.2.4財布ファイルをエクスポートする)
		* [2.2.5署名サーバー方式の紹介](#2.2.5署名サーバー方式の紹介)
	* [3.ontologyノードを開始](#3.ontologyノードを開始)
	* [4.資産取引を処理](#4.資産取引を処理)
		* [4.1引き出しの署名](#4.1引き出しの署名)
			* [4.1.1postメソッド1を使用して取引を構築](#4.1.1postメソッド1を使用して取引を構築)
			* [4.1.2postメソッド2を使用して取引を構築](#4.1.2postメソッド2を使用して取引を構築)
			* [4.1.3マルチ振替の取引を構築](#4.1.3マルチ振替の取引を構築)
			* [4.1.4資産オプション](#4.1.4資産オプション)
		* [4.2入金の監視](#4.2入金の監視)
			* [4.2.1現在のブロックの高さを取得](#4.2.1現在のブロックの高さを取得)
				* [4.2.1.1Cliによる](#4.2.1.1Cliによる)
				* [4.2.1.2PostによるGetblockcount](#4.2.1.2PostによるGetblockcount)
			* [4.2.2ブロック情報の監視](#4.2.2ブロック情報の監視)
				* [4.2.2.1Cliによる](#4.2.2.1Cliによる)
				* [4.2.2.2postによるGetblock](#4.2.2.2postによるGetblock)
			* [4.2.3取引実行情報を取得](#4.2.3取引実行情報を取得)
				* [4.2.3.1Cliによる](#4.2.3.1Cliによる)
				* [4.2.3.2postによるGetrawtransaction](#4.2.3.2postによるGetrawtransaction)
	* [5.アンバインドのONGと出金](#5.アンバインドのONGと出金)
		* [5.1アンバインドのONGを確認](#5.1アンバインドのONGを確認)
			* [5.1.1Cliによる](#5.1.1Cliによる)
			* [5.1.2postによるGetunboundong](#5.1.2postによるGetunboundong)
		* [5.2ONG出金](#5.2ONG出金)
			* [5.2.1Cliによる](#5.2.1Cliによる)
			* [5.2.2postによるONG出金](#5.2.2postによるONG出金)
	* [6.OEP4トークン振替](#6.OEP4トークン振替)
		* [6.1振替](#6.1振替)



## 1.ontologyを実行する準備とontologyノードの同期


ontologyを実行するには、[ソース](https://github.com/ontio/ontology/blob/master/README.md)から取得するか、[リリースページ](https://github.com/ontio/ontology/releases)から取得します。

## 2.サーバ側

### 2.1Cliを使用して財布の作成

ontologyCliを使用して財布を作成し、必要に応じてアカウントを追加します。 ontology Cli使用方法の詳細については、[Cliの説明](https://github.com/ontio/ontology/blob/master/docs/specifications/cli_user_guide.md)をご覧ください。

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

#### 2.1.1Cliについての注意事項


取引所は、ユーザーのアカウントを管理するためにオンライン財布を作成する必要があります。 財布ファイルには、アカウント（公開キーと秘密キーを含む）、契約ハッシュスクリプトなどに関する情報が含まれています。 取引所がユーザーを検証することは最も重要です。 財布ファイルとパスワードが安全かつ機密であることを確認してください。 交換では、1つの財布ファイルを使用してすべてのユーザーアカウント情報を保存するか、ハード財布（オフライン財布）を使用して安全性を高めることができます。

アカウントを作成するには2つの方法があります。
1つの方法は、ユーザーのアカウントを自動的に作成することです。 1人のユーザーが初めてONT / ONGをデポジットする場合、そのユーザーのアカウントを自動的に作成するようにプログラムできます。
もう1つの方法は、十分なONTアドレス（アカウント）を作成し、このユーザーが初めてデポジットしたいときに1人のユーザーに1つのアドレスを割り当てることです。 いくつかのアカウントを事前に作成するには、このコマンドを実行します。`` `./ontology account add -n [n] -w [wallet file]` ``



-d はオプションで、既定値は1です。

-w は指定された財布ファイルです。既定値はwallet.datです。

-nは、作成するアカウント（アドレス）の数です。

例
```
ontology account add -n 10 -d -w wat.dat
```

### 2.2アカウントを作成し、Sigsvrを通じてWalletファイルをエクスポート

#### 2.2.1Postman

[Postman](https://www.getpostman.com) を準備し、インストールします。 メソッドを「POST」に設定し、url を "http://127.0.0.1:20000/cli" に設定します


#### 2.2.2 Sigsvrを起動
```
./sigsvr
```

### 2.2.3PostmanによるPost

```
{
	"qid":"t",
	"method":"createaccount",
	"pwd":"XXXX",     //the password of the newly created account
	"params":{}
}
```
その後、アカウントが作成されたことを確認できますd
```
2018/09/07 11:37:30.774727 [INFO ] GID 38, [CreateAccount]{"address":"AJdh41doGw1Ty79baVG9Xdari34zkP2FCS","enc-alg":"aes-256-gcm","key":"JCvluLJ8J/SOChZtM3GvWFvyyNS37Yo3X7wV4lFIAQmimjAhC+2TEuflrVI7zR+e","algorithm":"ECDSA","salt":"jj99HOalCPW8T9nOTOQdcA==","parameters":{"curve":"P-256"},"label":"","publicKey":"0356aa6706c089eb045a9d0b123f581a5ccebbf61e85c462d57a2952b34c7a84be","signatureScheme":"SHA256withECDSA","isDefault":false,"lock":false}
2018/09/07 11:37:30.776665 [INFO ] GID 38, [CliRpcResponse]{"qid":"t","method":"createaccount","result":{"account":"AJdh41doGw1Ty79baVG9Xdari34zkP2FCS"},"error_code":0,"error_info":""}
```
### 2.2.4財布ファイルをエクスポートする

PostmanによるPost: 
```
{
	"qid":"t",
	"method":"exportaccount",
	"pwd":"111111",
	"params":{	"wallet_path":"$GOPATH$src/github.com/ontio/ontology/sigsvr_wallet"     // the designated wallet path
	}
}
```
その後、財布ファイルがエクスポートされます。

### 2.2.5署名サーバー方式の紹介

現在、Sigsvrは、データの署名、通常の取引、multiSig取引、ネイティブコントラクト呼び出し署名できる取引、Neovm契約により呼び出された署名できる取引をサポートしています。

署名サーバーは、1つのjson形式のrpcサーバーです。 メッセージを送信することで使用できます。

投稿されたサーバーのパスは次のように設定する必要があります。
http://localhost:20000/cli.

post構造は
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
答えの構造は
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
## 3.ontologyノードを開始


ここではテストモードで開始します。テストネットまたはメインネットについては、「[run-ontology](https://github.com/ontio/ontology/blob/master/README.md#run-ontology)」を参照してください。

```
C:\Go_WorkSpace\src\github.com\ontio\ontology (master -> origin)
λ ontology --testmode --gasprice=0
```


## 4.資産取引を処理

### 4.1引き出しの署名

#### 4.1.1postメソッド1を使用して取引を構築

「sigtransfertx」メソッドでは、取引支払いアカウントはデフォルトで署名アカウントです。 他のアカウントを支払人として指定する必要がある場合は、「payer」パラメーターを使用できます。 支払人アカウントを指定する場合、「sigrawtx」を使用して「sigtransfertx」メソッドのpost結果に署名することに注意してください。 詳細は4.1.2で説明します。


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
次に、signed_txを取得します。
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


次に、オントロジーCLIで、次を実行します。 signed_txが上記の結果であることに注意してください。

```
./ontology sendtx "signed_tx"
```

取引は散布されるでしょう。

#### 4.1.2postメソッド2を使用して取引を構築
「from」と等しくない「payer」を設定します。
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
返された結果
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

次に、「Post」してアカウント「AdXadq2bYykdbopzHNqYymtvw2eQmnoMRs」によって署名された tx を取得します。


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
返される結果は
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

次に、ontology Cliを使用して、次を実行します。 signed_txが上記の結果であることに注意してください。

```
./ontology sendtx "signed_tx" 
```
#### 4.1.3マルチ振替の取引を構築

ont　取引に複数の振替を配置するには、次のパラメーターを使用する必要があります。

```
{
    "Qid":"t",
    "Method":"signativeinvoketx",
    "account":"Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT",
    "pwd":"xxxxx",
    "Params":{
    	"gas_price":500,
    	"gas_limit":20000,
    	"address":"0100000000000000000000000000000000000000",
    	"method":"transfer",
    	"version":0,
    	"payer":"Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT",
    	"params":[
    		    [
    			[
    			"Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT",
    			"AS3SCXw8GKTEeXpdwVw7EcC4rqSebFYpfb",
    			"1000"
    			],
    			[
    			"Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT",
    			"AK98G45DhmPXg4TFPG1KjftvkEaHbU8SHM",
    			"1000"
    			]
    		     ]
    	]
    }
}
```
返された結果は
```
{"qid":"t","method":"signativeinvoketx","result":{"signed_tx":"00d11104175cf401000000000000204e000000000000e98f4998d837fcdd44a50561f7f32140c7c6c260a700c66b6a14e98f4998d837fcdd44a50561f7f32140c7c6c260c86a1470a2ababdae0a9d1f9fc7296df3c6d343b772cf7c86a02e803c86c00c66b6a14e98f4998d837fcdd44a50561f7f32140c7c6c260c86a1424ed4f965d3a5a76f5d0e87633c0b76941fc8827c86a02e803c86c52c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b6500014140aeaa1c95c2c0bc3071d8d5896e6f7b359522efc7edbf8bcc991cb2d57adee1db8e598b25a0ef52f60f4c589ef05b0bfa7cbe906059b54abd6286cc043c975f8723210217c25948722c14c1a6fa8e06b78691e722f4598585805671b0beaa7fd6c7662bac"},"error_code":0,"error_info":""}
```


その後、署名済みの取引を以前と同様にオontology に送信できます。
"address":"0100000000000000000000000000000000000000" はONT用です
"address":"0200000000000000000000000000000000000000" はONG用です。

***注：ont取引で最大500件の振替を追加できます***


#### 4.1.4資産オプション



「asset」パラメータを「ont」または「ong」として設定できます。

### 4.2入金の監視



postman　の url を http://127.0.0.1:20336 に設定します。
#### 4.2.1現在のブロックの高さを取得

##### 4.2.1.1Cliによる

ontology cli で、 `./ontology info curblockheight` を実行します。

```
C:\Go_WorkSpace\src\github.com\ontio\ontology (master -> origin)
λ ontology info curblockheight
CurrentBlockHeight:1972
```
##### 4.2.1.2PostによるGetblockcount

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
返された結果
```
{
    "desc": "SUCCESS",
    "error": 0,
    "id": 1,
    "jsonrpc": "2.0",
    "result": 1972
}
```

#### 4.2.2ブロック情報の監視

##### 4.2.2.1Cliによる

ontology cli で、これを実行します。
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
##### 4.2.2.2postによるGetblock

method: "getblock", params: hash/height, return: block info.
```
{
  "jsonrpc": "2.0",
  "method": "getblock",
  "params": ["f5b8188802c44701de722b7fa8aa0c59211052e93fc256957c5c300398ca7865", 1],
  "id": 1
}
```
または
```
{
  "jsonrpc": "2.0",
  "method": "getblock",
  "params": [1972, 1],
  "id": 1
}
```
ここで、「params」リストの「1」は冗長パラメータです。 デフォルトではverbose = 0で、シリアル化された16進文字列情報が返されます。 ブロックの詳細情報を取得するには、SDKを使用してデシリアライズする必要があります。 verbose = 1を設定すると、jsonスタイルの理解可能なブロック情報が返されます。

返された結果は
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
#### 4.2.3取引実行情報を取得

##### 4.2.3.1Cliによる

ontology cli で、これを実行します。
```
./ontology info status <TxHash>
```
返された結果
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
説明:
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

何をする必要がある「to address」フィルタリングすることです。「to address」がユーザーアカウントのアドレスの1つであることが検出された場合、そのユーザーが自分のアカウントにong / ontを預けたことが記録されます。

##### 4.2.3.2postによるGetrawtransaction

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
返された結果
```
{
    "desc": "SUCCESS",
    "error": 0,
    "id": 1,
    "jsonrpc": "2.0",
    "result": "00d18212925b0000000000000000204e000000000000ee9ebe462361fd252ebf81504bcaa75bdb1eed7e6e00c66b6a14ee9ebe462361fd252ebf81504bcaa75bdb1eed7ec86a14f91b8663ad7c5729c365e37ccfcec379ab6afce6c86a51c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b6500014140a360394db961ee468ea7c9cc1f5361e9a8434ad9e88d0a37e08c866067cf7c1bcf6f83f93a68ad1f705b00a3d08f6d9da979fa7cebb7b072038572052b0a6a1e232102bc256745a6c3e20117b5214f12b2132f863b0087730f42dc3fbd12a1c3847d67ac"
}
```

## 5.アンバインドのONGと出金

### 5.1アンバインドのONGを確認
#### 5.1.1Cliによる

ontology cli で、これを実行します。
```
./ontology asset unboundong <address|index|label> 
```
#### 5.1.2postによるGetunboundong

method: "getunboundong", params: address, return: 
```
{
  "jsonrpc": "2.0",
  "method": "getunboundong",
  "params": ["AdXadq2bYykdbopzHNqYymtvw2eQmnoMRs"],
  "id": 1
}
```
返された結果
```
{
    "desc": "SUCCESS",
    "error": 0,
    "id": 1,
    "jsonrpc": "2.0",
    "result": "50429999676900"
}
```
### 5.2ONG出金

#### 5.2.1Cliによる

ontology cli で、これを実行します。
```
./ontology asset withdrawong <address|index|label>
```
#### 5.2.2postによるONG出金

[例](https://github.com/ontio/ontology/blob/master/docs/specifications/sigsvr.md#example2-constructing-withdraw-ong-transaction)を参照してください。

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
    			"AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV",
    			"AdXadq2bYykdbopzHNqYymtvw2eQmnoMRs",
    			"1000"
    	]
    }
}
```
説明
```
"account": signing account
"pwd": password
In params:
	1st address -- sender:  
	2nd address -- base58 address of ONT contract big endian script hash
	3rd address -- the address to receive the withdrawal ong
	4th value   -- the value of ong (actual ong = value/10^9)
```
返された結果
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
ontology cli で、これを実行します。
```
./ontology sendtx "signed_tx"
```
次に、ONG残高を確認します。

## 6.OEP4トークン振替
### 6.1振替
方法名: signeovminvoketx
リクエスト:
```
{
	"Qid":"t",
	"Method":"signeovminvoketx",
	"account":"Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuB",	 
	"pwd":"123456",
	"Params":{
		"gas_price":500,
		"gas_limit":20000,
		"address":"75a5cdc00164266a1ba859da785e31cd914ddbd0",
		"payer":"Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuB",
		"version":0,
		"params": [
    		{
    			"type": "string",
    			"value": "transfer"
    		},
    		{
    			"type": "array",
    			"value": [
    				{
    					"type": "ByteArray",
    					"value": "e98f4998d837fcdd44a50561f7f32140c7c6c260"
    				},
    				{
    					"type": "ByteArray",
    					"value": "70a2ababdae0a9d1f9fc7296df3c6d343b772cf7"
    				},
    				{
    					"type": "int",
    					"value": "100"
    				}
    			]
    		}
    	]
	}
}
```

***注***：addressパラメータは「ByteArray」形式である必要があります