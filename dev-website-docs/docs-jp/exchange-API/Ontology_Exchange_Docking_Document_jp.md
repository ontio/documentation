# Ontology取引所ドッキングに関するドキュメント

ONTには2種類のアセットがあり、ネイティブアセットとコントラクトアセットに分けられます。ネイティブアセットはONTとONGです。取引とドッキングする場合、この2種類のアセットの入金と送金を処理します。

このドキュメントの概要は下記のようになっております。

* [Ontology取引所ドッキングに関するドキュメント](#Ontology取引所ドッキングに関するドキュメント)
	* [1.Ontology同期化ノードの配備](#1.Ontology同期化ノードの配備)
		* [ソースコードから取得](#ソースコードから取得)
		* [リリースから取得](#リリースから取得)
		* [サーバー配備](#サーバー配備)
			* [財布を作る(同期化ノードは必須ではない)](#財布を作る(同期化ノードは必須ではない))
			* [起動ノード](#起動ノード)
	* [2.CLIクライアントの利用](#2.CLIクライアントの利用)
		* [セキュリティポリシー](#セキュリティポリシー)
		* [CLI 命令](#CLI 命令)
			* [財布を作る](#財布を作る)
			* [入金アドレス生成](#入金アドレス生成)
	* [3.資産取引の処理](#3.資産取引の処理)
		* [取引所が開発する必要がある取引のドッキングプログラム](#取引所が開発する必要がある取引のドッキングプログラム)
		* [ユーザーの入金](#ユーザーの入金)
		* [入金のレコード](#入金のレコード)
		* [引き出しの処理](#引き出しの処理)
	* [4.Java SDKチュートリアル](#4.Java-SDKチュートリアル)
		* [アカウント管理](#アカウント管理)
			* [財布管理を利用しないでください](#財布管理を利用しないでください)
				* [ランダムにアカウントを作成](#ランダムにアカウントを作成)
				* [秘密鍵に基づいたアカウントを作成](#秘密鍵に基づいたアカウントを作成)
			* [財布管理を利用](#財布管理を利用)
		* [アドレス生成](#アドレス生成)
		* [ONTとONGの振替 ](#ONTとONGの振替)
			* [1.初期化](#1.初期化)
			* [2.お問い合わせ](#2.お問い合わせ)
				* [ONTとONGの残高に関するお問い合わせ](#ONTとONGの残高に関するお問い合わせ)
				* [取引は既に取引プールに入ったかに関するお問い合わせ](#取引は既に取引プールに入ったかに関するお問い合わせ)
				* [取引が成功したかに関するお問い合わせ](#取引が成功したかに関するお問い合わせ)
				* [チェーンの相互作用インターフェースに関するリスト](#チェーンの相互作用インターフェースに関するリスト)
			* [3.ONT振替](#3.ONT振替)
				* [振替の取引を生成してから発送する](#振替の取引を生成してから発送する)
				* [複数の署名](#複数の署名)
				* [1対複数もしくは複数対複数](#1対複数もしくは複数対複数)
				* [署名サーバー経由でサイン](#署名サーバー経由でサイン)
			* [4.ONG振替](#4.ONG振替)
				* [ONG振替](#ONG振替)
				* [ONG出金](#ONG出金)
	* [4.ユーザーへのONG分配](#4.ユーザーへのONG分配)
		* [ONGとは](#ONGとは)
		* [引出せるONG数量の計算](#引出せるONG数量の計算)
		* [ユーザーへのONG分配](#ユーザーへのONG分配)
		* [ONGの引き出し](#ONGの引き出し)
	* [5.サインサービス](#5.サインサービス)
	* [6.OEP4トークン](#6.OEP4トークン)
	* [7.PAXトークン](#7.PAXトークン)
	* [ネイティブコントラクトアドレス](#ネイティブコントラクトアドレス)
	* [FAQ](#FAQ)
	* [メインネット更新ノート](#メインネット更新ノート)

## 1.Ontology同期化ノードの配備

Ontology同期化ノードの配備には2つの方法があります。

### ソースコードから取得

Ontologyのリポジトリを **$GOPATH/src/github.com/ontio** にそのままにコピーする

```
$ git clone https://github.com/ontio/ontology.git
```

もしくは

```
$ go get github.com/ontio/ontology
```

第三者機関のパッケージ管理ツールを利用し、依存ライブラリを管理する

```
$ cd $GOPATH/src/github.com/ontio/ontology
$ glide install
```

makeを利用してそーそコードをコンパイルする

```
$ make
```

コンパイル成功した後に実行可能なプログラムが生成されます
（```make all``` コマンドを使用すると、 'tools'ディレクトリの下にsigサーバーが生成されます）

- `ontology`: コマンドラインで提供されるノードプログラム/ノード制御プログラム

### リリースから取得

 [リリースページ](https://github.com/ontio/ontology/releases)

### サーバー配備

1. #### 財布を作る(同期化ノードは必須ではない)

   - 財布ファイルを作成する - CLIを通して実行するノードに必要なwallet.datの作成

     ```
     $ ./ontology account add -d
     Use default setting '-t ecdsa -b 256 -s SHA256withECDSA' 
     	signature algorithm: ecdsa 
     	curve: P-256 
     	signature scheme: SHA256withECDSA 
     Password:
     Re-enter Password:

     Index: 1
     Label: 
     Address: AWVNFw74G8Sx9vcxGbmh4gT54ayuwb3bcm
     Public key: 02c17cd91acf618d497f65f1fc4f52de7952c8b2337883f898dda887953cd29dd7
     Signature scheme: SHA256withECDSA

     Create account successfully.
     ```

     

   - ディレクトリ構造

     ```
        $ tree
        └── ontology
            ├── ontology
            └── wallet.dat
     ```


2. #### 起動ノード

   起動コマンド:

   ```./ontology ```

   デフォルト設定では、ノード起動したら、websocketと残りのポートが閉じられます。上記のポートをオーペンしたい場合、次のパラメーターを設定してください。 

   ```
   RESTFUL OPTIONS:
     --rest            Enable restful api server
     --restport value  Restful server listening port (default: 20334)
     
   WEB SOCKET OPTIONS:
     --ws            Enable websocket server
     --wsport value  Ws server listening port (default: 20335)
   ```

   

## 2.CLIクライアントの利用

### セキュリティポリシー

必須条件:ホワイトリストまたはファイアウォールを利用して外部サーバーのリクエストをブロックする状況で取引が行われます。そうしない場合、セキュリティリスクは非常に高いです。 

CLIは遠隔操作で財布の起動・閉じる機能を提供していないです。財布起動した際に検証プロセスはありません。したがって、セキュリティポリシーは取引の各状況に基づいて設定する必要があります。引き出しの処理は財布起動したままで操作できるので、財布は単独なサーバーで実行する必要があります。取引所のファイアウォールの設定は下記の表をご参照ください。

|               | メインネット　デフォルト　ポート |
| ------------- | -------------------------------- |
| Rest Port     | 20334                            |
| Websorcket    | 20335                            |
| Json RPC port | 20336                            |
| Node port     | 20338                            |

### CLI 命令

#### 財布を作る

ユーザーの入金アドレスを管理するために取引所はオンラインの財布を作成する必要があります。財布にはアカウント（公開鍵と秘密鍵）、コントラクトアドレスとその他の情報を保存しています。財布はユーザーが資産の保有者であることの一番重要な証明です。財布のファイルとパスワードの紛失と漏えいを防ぎ、安全に保管することが大事です。取引所はアドレスごとに財布のファイルを生成する必要がありません。通常、財布のファイルには全部の入金アドレスを保存できます。コールド財布（オフライン財布）はより安全なストレージとして使われます。

```
$ ./ontology account add -d
Use default setting '-t ecdsa -b 256 -s SHA256withECDSA' 
	signature algorithm: ecdsa 
	curve: P-256 
	signature scheme: SHA256withECDSA 
Password:
Re-enter Password:

Index: 1
Label: 
Address: AWVNFw74G8Sx9vcxGbmh4gT54ayuwb3bcm
Public key: 02c17cd91acf618d497f65f1fc4f52de7952c8b2337883f898dda887953cd29dd7
Signature scheme: SHA256withECDSA

Create account successfully.
```

**ONTの公開鍵と秘密鍵の生成アルゴリズムはNEOと一致しています。同じ秘密鍵に対応するONTとNEOの公開鍵のアドレスは同じです。**

####  入金アドレス生成

**注意: ONTとONGのアドレスは大文字と小文字が区別されます**

一つの財布は複数のアドレスを保存できます。取引所は各ユーザーの入金アドレスを生成する必要があります。

入金アドレスの生成方法は二つある:

- ユーザーが初めて(ONT/ONG)を入金する際にプログラムが動的にONTアドレスを生成します。 優位性: アドレスを手動に生成する必要がありません。短所: 財布のバックアップは不便です。

アドレスを動的に作成するにはJava SDKが使われます。プログラムは作成されたアドレスを取り戻します。Java SDK [ランダムにアカウントを作る](#create-account-randomly)をご参照ください。

- 取引所は事前にONTアドレスのバッチを作成します。ユーザーが初めて (ONT/ONG)を入金する際にONTアドレスが分配されます。優位性 :財布はバックアップしやすいです。 短所:アドレスが不足している場合、手動にONTアドレスを作成します。 

  アドレスのバッチを生成するにはCLIで ./ontology account add -n [n] -w [wallet file] のコマンドを実行します。-dブラケットは選択可能なパラメーター で、デフォルト値は１となっています。. -w は財布のファイルを指定し、デフォルトのファイルはwallet.datです。例えば、一回で100のアドレスを作成する場合 :

```
$ ./ontology account add -n 100 -d -w wat.dat
Use default setting '-t ecdsa -b 256 -s SHA256withECDSA' 
	signature algorithm: ecdsa 
	curve: P-256 
	signature scheme: SHA256withECDSA 
Password:
Re-enter Password:

Index: 1
Label: 
Address: ATh1dt4pKZTASu45VeRChPi3iYmk8nYKJH
Public key: 03f8e59f0059d11dcec2902c44a9e7a2466adc9b25a61b1d94d2027d13f78ac45a
Signature scheme: SHA256withECDSA

Index: 2
Label: 
Address: AdYpqD8kn3NwBkkDktqfLfT8jJMCaD7BrB
Public key: 03e05424e711faa1591ee62a20648b45d8328f40c1ad5c479484501445fea62c50
Signature scheme: SHA256withECDSA

Index: 3
Label: 
Address: AY5hDhn2z8ND6F4JF9rQV1a4SDUT4aUr88
Public key: 03de554a6e3eea61aa9f78fa683ce9069ca8980a9f44b85eebe1d2c2e9a611875c
Signature scheme: SHA256withECDSA

....
```



## 3.資産取引の処理

### 取引所が開発する必要がある取引のドッキングプログラム

1. CLI/APIを利用し、新しいブロックをモニタリングする
2. 取引情報に基づいてユーザーの入金を完成させる
3. 取引記録の保存

### ユーザーの入金

ユーザーの入金に対し、下記のことを理解する必要があります。

- 通常、取引ごとのストラテジーが異なるので取引所の入金アドレスの残高とユーザーの残高は一致していない可能性があります。
- OntologyのアドレスはONTとONGのアセットが含まれます。ユーザーの入金を処理する際、ONTとONG入金を混同しないように取引所はアセットのタイプを判断する必要があります。
- Ontologyの財布は完全なコードです。ブロックを同期化するには財布はオンラインでなければなりません。CLIコマンドを使って現時点のブロックの高さの確認とノードの状態の判断ができます。


  ```
  $ ./ontology info curblockheight
  CurrentBlockHeight:2
  ```

- 取引所内部の振替はブロックチェーンを経由しなくても大丈夫です。したがって、取引所はデータベースにあるユーザーの残高を直接に変更できます。入金と引き出しだけはブロックチェーンを経由します。

例えば:

1. ユーザーはトークンをアドレスに入金する - ```TA8MoGmzS4T6g3T1CMGEVFiNGkZnn7ixw9```

2. CLIによるブロック情報のモニタリング```./ontology info block <block number | block hash>```  

   ```
   $ ./ontology info block 209304
   {
      "Hash": "83a70a5380532ededb4f3d65bcd4d3a8cd52f7f87bf1863d68bada59b95133d4",
      "Header": {
         "Version": 0,
         "PrevBlockHash": "e63ede75d1a1784c150edd537b2b5439cc3893be909d5e6970b7baa8b39a5437",
         "TransactionsRoot": "24ac1b3dbecedbac41413ef4578769dd858aab42ccb60b2918c879b129edbf5d",
         "BlockRoot": "8a03e9f3e9adb8abde5b129ba5f833a3555719ffbbf3dd97a931450620a6bbf0",
         "Timestamp": 1528959514,
         "Height": 3016,
         "ConsensusData": 8772979148630824583,
         "ConsensusPayload": "",
         "NextBookkeeper": "AQGN8sEz2dycryR5BxLCQCPYiqKPN5BMnx",
         "Bookkeepers": [
            "0217c25948722c14c1a6fa8e06b78691e722f4598585805671b0beaa7fd6c7662b"
         ],
         "SigData": [
            "a6faf7a3fe356e36977c249f858b8f0a11b719ae310470948e374b69cfb4c3f3d295ac3e81244ebbfc13a4ea94c3deee132ee9ef0caa745b4b6eaf21aeb92c40"
         ],
         "Hash": "83a70a5380532ededb4f3d65bcd4d3a8cd52f7f87bf1863d68bada59b95133d4"
      },
      "Transactions": [
         {
            "Version": 0,
            "Nonce": 4023588455,
            "GasPrice": 0,
            "GasLimit": 30000,
            "Payer": "f72c773b346d3cdf9672fcf9d1a9e0daababa270",
            "TxType": 209,
            "Payload": {
               "Code": "00c66b14e98f4998d837fcdd44a50561f7f32140c7c6c2606a7cc814dd803188dcc41329b6e9faa775a6085269b5db376a7cc808e8030000000000006a7cc86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65",
               "GasLimit": 0
            },
            "Attributes": [],
            "Sigs": [
               {
                  "PubKeys": [
                     "0217c25948722c14c1a6fa8e06b78691e722f4598585805671b0beaa7fd6c7662b"
                  ],
                  "M": 1,
                  "SigData": [
                     "0160ade36dc83fc79e8aee00ca2d7553bbef876a14b511bb68555247903732853134ecae9b9ce053c61b0fb65167e9745fdf7e85bd85861fde901430c3fd4de516"
                  ]
               },
               {
                  "PubKeys": [
                     "0250291da2e26b9f155e19d9a0aae1980124caa55760fcade32217fd93e8a0e750"
                  ],
                  "M": 1,
                  "SigData": [
                     "0106956ada8fb0fe2effe88215b39e607f7faa37f07428b5151a359868b03f701ff04b689bd9a96f5fb3272ee362d6176176f0a04959b953c0c85f220f1198d25f"
                  ]
               }
            ],
            "Hash": "bce10eb97c6cd122131e448ddf415bcd15aabbddd466e6850074c6c839a26596"
         },
         {
            "Version": 0,
            "Nonce": 238868671,
            "GasPrice": 0,
            "GasLimit": 30000,
            "Payer": "f72c773b346d3cdf9672fcf9d1a9e0daababa270",
            "TxType": 209,
            "Payload": {
               "Code": "00c66b14e98f4998d837fcdd44a50561f7f32140c7c6c2606a7cc814dd803188dcc41329b6e9faa775a6085269b5db376a7cc808b0040000000000006a7cc86c51c1087472616e736665721400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b65",
               "GasLimit": 0
            },
            "Attributes": [],
            "Sigs": [
               {
                  "PubKeys": [
                     "0217c25948722c14c1a6fa8e06b78691e722f4598585805671b0beaa7fd6c7662b"
                  ],
                  "M": 1,
                  "SigData": [
                     "0167697964e63236565e81ca35670b7b160fe4c5365bd437d54d467a63c83084f1988dc6c429d683a71ee590520a5c3ee1735657a485a9f549a4bbef76258db67b"
                  ]
               },
               {
                  "PubKeys": [
                     "0250291da2e26b9f155e19d9a0aae1980124caa55760fcade32217fd93e8a0e750"
                  ],
                  "M": 1,
                  "SigData": [
                     "01980eb20147a016b7ddf614107f4d178be3d7d66d56a5ecc56e80daa89bfed11b081f4a907c89338bbe1182d692307b2727d1227809f75c18662c5f3f9f0c43b4"
                  ]
               }
            ],
            "Hash": "10ccaf9188e249a7ff61aa68e429f9e5a916ca01bbeb55ccaec38588b1227518"
         }
      ]
   }
   ```


3. CLIによる取引ハッシュに基づいてブロック内のすべての取引情報を取得します。 ```./ontology info status```

```
$ ./ontology info status bce10eb97c6cd122131e448ddf415bcd15aabbddd466e6850074c6c839a26596
Transaction states:
{
   "TxHash": "bce10eb97c6cd122131e448ddf415bcd15aabbddd466e6850074c6c839a26596",
   "State": 1,
   "GasConsumed": 0,
   "Notify": [
      {
         "ContractAddress": "0100000000000000000000000000000000000000",
         "States": [
            "transfer",
            "Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT",
            "Aby4Yw4tNEUN28cWY3cYK5Hk3t7opENq8q",
            1000
         ]
      }
   ]
}
```

"State"  1は取引成功、0は失敗。

 "Notify" 配列を解析する:

​     ContractAddress: Contract address：	```0100000000000000000000000000000000000000```  is for ONT

​						        ```0200000000000000000000000000000000000000``` is for ONG

​     States：array

​                一つ目の要素: "transfer" は振替の操作を意味する

​		二つ目の要素: 差出先（From address）

​                三つ目の要素: 発送先（To address）

​                四つ目の要素: 振替数量（**ONTの実際の数量はONT数量 * 1。ONGの実際の数量はONG数量* 10^9**）

入金記録を取得するには取引所がユーザーのために生成したアドレスをフィルタリングすることができます。

### 入金のレコード

ユーザーの入金と同じように取引所はすべてのブロック内の全部の取引をモニタリングするコードを作成します。データベース内のすべての入金と引き出しを記録する必要があります。入金の取引がある場合、取引所はデータベースに対応するユーザーの残高を変更します。



### 引き出しの処理

ユーザーの引き出しを処理するには、次の操作を完成する必要があります。

1. ユーザーの引き出し数量を記録し、残高を変更させる。

2. CLIコマンドを使用して、トークンをユーザーの引き出しアドレスに振替します。

```
   $ ./ontology asset transfer --from Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT --to AS3SCXw8GKTEeXpdwVw7EcC4rqSebFYpfb --amount 10 
   Password:
   Transfer ONT
     From:Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT
     To:AS3SCXw8GKTEeXpdwVw7EcC4rqSebFYpfb
     Amount:10
     TxHash:49a705f6beb6a15b92493db496f56e8bcddc95b803dac1e4a02b4579ce760b3f

   Tip:
     Using './ontology info status 49a705f6beb6a15b92493db496f56e8bcddc95b803dac1e4a02b4579ce760b3f' to query transaction status

```

  このコマンドにあるパラメーターのリスト:

   --wallet, -w  
  財布は振替アカウントの財布パスを指定します。デフォルト値は"./wallet.dat"です。

   --gasprice  
   取引の総計ONGコストは gaslimit * Gasprice
   gaspriceパラメーターはgasの価格を指定します。gasの価格はノードの取引プールで設定された最低価格より低くすることができません。そうしないと、取引が拒否されます。デフォルト値は0です。取引プールにはブロックにパッキング待ちの取引がある場合、gasの価格にしたがって取引を処理し、gasの価格が高い取引は優先されます。

   --gaslimit  
   gasの制限は取引に使うgas単位の最大量であるので制限と呼ばれます。
   しかし、実際のgasコストはVMによって実行されるステップの数、もしくはAPIの数によって決められます。次の二つの条件を想定します。

      1. gaslimit>= 実際のコスト。取引成功。消耗されていないgasを取り戻します;  
            2. Gaslimt< 実際のコスト。取引失敗。VMが実行したgasが消耗されます;  
               　gas取引の最小限は30,000です。この数値より低い取引はパッキングされないです。
           Gaslimitは取引の事前実行によって計算できます。 (もちろん、時間などが異なる実行コンテキストであるために明確な数値ではない)。  
           ONT/ONGの利用を簡素化にするために、ONT/ONGのすべての方法を最低のgas制限に設定し、つまり30000 gasです。

   --asset  
  アセットのパラメーター は振替する資産のタイプを指定します。OntはONTを代表し、ongはONGを代表します。デフォルト値はONTです。

   --from   
   この fromのパラメーターは差出先のアカウントのアドレスを指します。 

   --to  
   このtoのパラメーターは振替先のアカウントのアドレスを指します。 

   --amount   
   この amountのパラメーターは振替数量を指します。注意: ONT精度は１であるので、インプットは浮動小数点である場合、小数部分の値は破棄されます。ONG精度は9であるので、9ビットを超える小数部分は破棄されます。


  取引の結果を確認する:

   - 取り戻した取引のハッシュを利用し、直接クエリする:

   ```
     $ ./ontology info status 49a705f6beb6a15b92493db496f56e8bcddc95b803dac1e4a02b4579ce760b3f
     Transaction states:
     {
        "TxHash": "49a705f6beb6a15b92493db496f56e8bcddc95b803dac1e4a02b4579ce760b3f",
        "State": 1,
        "GasConsumed": 0,
        "Notify": [
           {
              "ContractAddress": "0100000000000000000000000000000000000000",
              "States": [
                 "transfer",
                 "Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT",
                 "AS3SCXw8GKTEeXpdwVw7EcC4rqSebFYpfb",
                 10
              ]
           }
        ]
     }
    
   ```

​     

   - 「ユーザーの入金」と同じように新しいブロックの取引をモニタリングし、取引アドレスからユーザーの引き出し先のせいこうした取引を除外します。

3. Json形式で返された取引の詳細から取引IDを抽出し、データベースに記録します。

4. ブロックチェーンの確認を待ちます。確認した後、引き出し記録に引き出し成功の印をつけます。

   入金中のブロックチェーンを監視すると同じように引き出しのプロセスも監視されています。モニタリング中の際に、ブロック内の特定な取引IDは引き出し記録にある取引IDと同じである場合、この取引が確認され、引き出しも成功します。

5. 取引が長時間で確認されていなかったのは対応するイベントログが取引を通じて取引ハッシュの確認ができません。そうした場合の解決策は：

   - 取引がRPC／SDKインターフェース経由で取引プールにあるかどうかを確認します。（refer to[Java SDK:ONT and ONG transfer](https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/sdk_get_start.md#2-%E5%8E%9F%E7%94%9F%E8%B5%84%E4%BA%A7ont%E5%92%8Cong%E8%BD%AC%E8%B4%A6))。存在する場合、コンセンサスノードをパックしてから確認する必要があります。

   - 存在しない場合、取引が失敗し、振替のオペレーションをもう一度実行する必要があります。


   - 取引は長時間でパッキングされていない場合、gas価格は低すぎるかもしれない。

     

## 4.Java SDKチュートリアル

Java SDK チュートリアル: [Java SDK Tutorials](https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/sdk_get_start.md) 

### アカウント管理

#### 財布管理を利用しないでください

##### ランダムにアカウントを作成

```java
com.github.ontio.account.Account acct = new com.github.ontio.account.Account(ontSdk.defaultSignScheme);
acct.serializePrivateKey();//Private key
acct.serializePublicKey();//Public key
acct.getAddressU160().toBase58();//base58 address
```

##### 秘密鍵に基づいたアカウントを作成

```java
com.github.ontio.account.Account acct0 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey0), ontSdk.defaultSignScheme);
com.github.ontio.account.Account acct1 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey1), ontSdk.defaultSignScheme);
com.github.ontio.account.Account acct2 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey2), ontSdk.defaultSignScheme);

```

#### 財布管理を利用

[例を挙げると](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/WalletDemo.java) 

```java

#### Create a batch of account in the wallet
ontSdk.getWalletMgr().createAccounts(10, "passwordtest");
ontSdk.getWalletMgr().writeWallet();

Create account randomly
AccountInfo info0 = ontSdk.getWalletMgr().createAccountInfo("passwordtest");

Create account based on private key
AccountInfo info = ontSdk.getWalletMgr().createAccountInfoFromPriKey("passwordtest","e467a2a9c9f56b012c71cf2270df42843a9d7ff181934068b4a62bcdd570e8be");

Get account
com.github.ontio.account.Account acct0 = ontSdk.getWalletMgr().getAccount(info.addressBase58,"passwordtest");

```

### アドレス生成

このアドレスにはシングルサインのアドレスと複数サインのアドレスが含まれます。作成方法はNEOアドレスと同じです。

```
single-signature address generation
String privatekey0 = "c19f16785b8f3543bbaf5e1dbb5d398dfa6c85aaad54fc9d71203ce83e505c07";
String privatekey1 = "49855b16636e70f100cc5f4f42bc20a6535d7414fb8845e7310f8dd065a97221";
String privatekey2 = "1094e90dd7c4fdfd849c14798d725ac351ae0d924b29a279a9ffa77d5737bd96";

//Generate account and get address
com.github.ontio.account.Account acct0 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey0), ontSdk.defaultSignScheme);
Address sender = acct0.getAddressU160();

//base58 address decode
sender = Address.decodeBase58("AVcv8YBABi9m6vH7faq3t8jWNamDXYytU2")；

//multi-signature address generation
Address recvAddr = Address.addressFromMultiPubKeys(2, acct1.serializePublicKey(), acct2.serializePublicKey());


```

| 方法                    | パラメーター              | パラメーターの説明                                           |
| :---------------------- | :------------------------ | :----------------------------------------------------------- |
| addressFromMultiPubkeys | int m,byte\[\]... pubkeys | The minimum number of signatures (<=the number of public keys)，public key |


### ONTとONGの振替

例えば：[Example](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/MakeTxWithoutWalletDemo.java)

#### 1.初期化

```
String ip = "http://polaris1.ont.io";
String rpcUrl = ip + ":" + "20336";
OntSdk ontSdk = OntSdk.getInstance();
ontSdk.setRpc(rpcUrl);
ontSdk.setDefaultConnect(ontSdk.getRpc());

```

#### 2.お問い合わせ

##### ONTとONGの残高に関するお問い合わせ

```
ontSdk.getConnect().getBalance("AVcv8YBABi9m6vH7faq3t8jWNamDXYytU2");

View ONT information:
System.out.println(ontSdk.nativevm().ont().queryName());
System.out.println(ontSdk.nativevm().ont().querySymbol());
System.out.println(ontSdk.nativevm().ont().queryDecimals());
System.out.println(ontSdk.nativevm().ont().queryTotalSupply());

View ONG information:
System.out.println(ontSdk.nativevm().ong().queryName());
System.out.println(ontSdk.nativevm().ong().querySymbol());
System.out.println(ontSdk.nativevm().ong().queryDecimals());
System.out.println(ontSdk.nativevm().ong().queryTotalSupply());

```

##### 取引は既に取引プールに入ったかに関するお問い合わせ

```
ontSdk.getConnect().getMemPoolTxState("d441a967315989116bf0afad498e4016f542c1e7f8605da943f07633996c24cc")


response:transaction is in the tx pool

{
    "Action": "getmempooltxstate",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": {
        "State":[
            {
              "Type":1,
              "Height":744,
              "ErrCode":0
            },
            {
              "Type":0,
              "Height":0,
              "ErrCode":0
            }
       ]
    },
    "Version": "1.0.0"
}

Or transaction is Not in the tx pool:

{
    "Action": "getmempooltxstate",
    "Desc": "UNKNOWN TRANSACTION",
    "Error": 44001,
    "Result": "",
    "Version": "1.0.0"
}


```

##### 取引が成功したかに関するお問い合わせ

スマートコントラクトのコンテンツをプッシュするか

```
ontSdk.getConnect().getSmartCodeEvent("d441a967315989116bf0afad498e4016f542c1e7f8605da943f07633996c24cc")


response:
{
    "Action": "getsmartcodeeventbyhash",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": {
        "TxHash": "20046da68ef6a91f6959caa798a5ac7660cc80cf4098921bc63604d93208a8ac",
        "State": 1,
        "GasConsumed": 0,
        "Notify": [
            {
                "ContractAddress": "0100000000000000000000000000000000000000",
                "States": [
                    "transfer",
                    "Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT",
                    "AS3SCXw8GKTEeXpdwVw7EcC4rqSebFYpfb",
                    1000000000
                ]
            }
        ]
    },
    "Version": "1.0.0"
}

```

ブロックの高さ（ block height）を利用してスマートコントラクトイベントを確認することができます。イベント取引の詳細が返されます。

```
ontSdk.getConnect().getSmartCodeEvent(10)

response:
{
    "Action": "getsmartcodeeventbyhash",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": [
                             {
                                  "TxHash": "7e8c19fdd4f9ba67f95659833e336eac37116f74ea8bf7be4541ada05b13503e",
                                  "State": 1,
                                  "GasConsumed": 0,
                                  "Notify": [
                                      {
                                          "ContractAddress": "0200000000000000000000000000000000000000",
                                          "States": [
                                              "transfer",
                                              "AFmseVrdL9f9oyCzZefL9tG6UbvhPbdYzM",
                                              "AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV",
                                              1000000000000000000
                                          ]
                                      }
                                  ]
                              },
                              {
                                  "TxHash": "fc82cd363271729367098fbabcfd0c02cf6ded1e535700d04658b596d53cf07d",
                                  "State": 1,
                                  "GasConsumed": 0,
                                  "Notify": [
                                      {
                                          "ContractAddress": "0200000000000000000000000000000000000000",
                                          "States": [
                                              "transfer",
                                              "AFmseVrdL9f9oyCzZefL9tG6UbvhPbdYzM",
                                              "AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV",
                                              1000000000000000000
                                          ]
                                      }
                                  ]
                              }
     ],
    "Version": "1.0.0"
}

```

##### チェーンの相互作用インターフェースに関するリスト

| No   |                    Main   Function                     |                      Description                       |
| ---- | :----------------------------------------------------: | :----------------------------------------------------: |
| 1    |       ontSdk.getConnect().getGenerateBlockTime()       |               Query VBFT block-out time                |
| 2    |           ontSdk.getConnect().getNodeCount()           |               Query the number of nodes                |
| 3    |            ontSdk.getConnect().getBlock(15)            |                    Query block info                    |
| 4    |          ontSdk.getConnect().getBlockJson(15)          |                    Query block info                    |
| 5    |       ontSdk.getConnect().getBlockJson("txhash")       |                    Query block info                    |
| 6    |         ontSdk.getConnect().getBlock("txhash")         |                    Query block info                    |
| 7    |          ontSdk.getConnect().getBlockHeight()          |               Query current block height               |
| 8    |      ontSdk.getConnect().getTransaction("txhash")      |                   Query transaction                    |
| 9    | ontSdk.getConnect().getStorage("contractaddress", key) |              Query smart contract storage              |
| 10   |       ontSdk.getConnect().getBalance("address")        |                     Query balance                      |
| 11   | ontSdk.getConnect().getContractJson("contractaddress") |                  Query smart contract                  |
| 12   |       ontSdk.getConnect().getSmartCodeEvent(59)        |         Query the event in the smart contract          |
| 13   |    ontSdk.getConnect().getSmartCodeEvent("txhash")     |         Query the event in the smart contract          |
| 14   |  ontSdk.getConnect().getBlockHeightByTxHash("txhash")  |       Query the block height by transaction hash       |
| 15   |      ontSdk.getConnect().getMerkleProof("txhash")      |                    Get merkle proof                    |
| 16   | ontSdk.getConnect().sendRawTransaction("txhexString")  |                    Send transaction                    |
| 17   |  ontSdk.getConnect().sendRawTransaction(Transaction)   |                    Send transaction                    |
| 18   |    ontSdk.getConnect().sendRawTransactionPreExec()     |            Send a pre-execution transaction            |
| 19   |  ontSdk.getConnect().getAllowance("ont","from","to")   |                  Query Allowed Values                  |
| 20   |        ontSdk.getConnect().getMemPoolTxCount()         | Query total transaction volumn in the transaction pool |
| 21   |        ontSdk.getConnect().getMemPoolTxState()         |    Query transaction status in the transaction pool    |

#### 3.ONT振替

##### 振替の取引を生成してから発送する

```
// Transferee and payee address
Address sender = acct0.getAddressU160();
Address recvAddr = acct1;

// Multiple address generation
//Address recvAddr = Address.addressFromMultiPubKeys(2, acct1.serializePublicKey(), acct2.serializePublicKey());

// Construct a transfer transaction
long amount = 1000;
Transaction tx = ontSdk.nativevm().ont().makeTransfer(sender.toBase58(),recvAddr.toBase58(), amount,sender.toBase58(),30000,0);

// Sign a transaction
ontSdk.signTx(tx, new com.github.ontio.account.Account[][]{{acct0}});
//Signature scheme of multiple address
ontSdk.signTx(tx, new com.github.ontio.account.Account[][]{{acct1, acct2}});
//If the addresses of the transferee and the payer who pay the network fee are different, the payer’s signature needs to be added.

// Send a transaction
ontSdk.getConnect().sendRawTransaction(tx.toHexString());


```

| 方法         | パラメーター                                                 | パラメーターの説明                                           |
| :----------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| makeTransfer | String sender，String recvAddr,long amount,String payer,long gaslimit,long gasprice | sender address, receiver address, amount, network fee payer address, gaslimit, gasprice |
| makeTransfer | State\[\] states,String payer,long gaslimit,long gasprice    | A transaction contains multiple transfers                    |

##### 複数の署名

ネット料金の支払人と振替先のアドレスが異なる場合、支払人のサインを追加する必要があります。

```
// 1.Add single signature 
ontSdk.addSign(tx,acct0);

// 2.Add multiple signatures 
ontSdk.addMultiSign(tx,2,new com.github.ontio.account.Account[]{acct0,acct1});

```


##### 1対複数もしくは複数対複数

1. 複数の状態を持つ取引を作成する
2. サイン
3. 一回の取引は最大で1024

```
Address sender1 = acct0.getAddressU160();
Address sender2 = Address.addressFromMultiPubKeys(2, acct1.serializePublicKey(), acct2.serializePublicKey());
int amount = 10;
int amount2 = 20;

State state = new State(sender1, recvAddr, amount);
State state2 = new State(sender2, recvAddr, amount2);
Transaction tx = ontSdk.nativevm().ont().makeTransfer(new State[]{state1,state2},sender1.toBase58(),30000,0);

//The first transferee is a single-signature address, and the second transferee is a multiple-signature address
ontSdk.signTx(tx, new com.github.ontio.account.Account[][]{{acct0}});
ontSdk.addMultiSign(tx,2,new com.github.ontio.account.Account[]{acct1, acct2});

```

##### 署名サーバー経由でサイン

- **振替の取引を生成してからサインする**

1. 取引を生成し、取引をシリアル化、署名サーバーに取引を発送する
2. 署名サーバーは取引を受信し、デシリアライズし、取引を確認してからサインを追加する
3. 取引を発送する

```
//Send serialized transaction to signature server
Transaction tx = ontSdk.nativevm().ont().makeTransfer(sender.toBase58(),recvAddr.toBase58(), amount,sender.toBase58(),30000,0);
String txHex = tx.toHexString();

//The receiver deserializes the transaction and signs it
Transaction txRx = Transaction.deserializeFrom(Helper.hexToBytes(txHex));
//View transfer content in the transaction
System.out.println(Transfers.deserializeFrom(Contract.deserializeFrom(txRx.code).args).json());

//Sign
ontSdk.addSign(txRx,acct0);
```

- **サインデータ**

[例を挙げると](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/SignatureDemo.java) 

```
com.github.ontio.account.Account acct = new com.github.ontio.account.Account(ontSdk.defaultSignScheme);

byte[] data = "12345".getBytes();
byte[] signature = ontSdk.signatureData(acct, data);

System.out.println(ontSdk.verifySignature(acct.serializePublicKey(), data, signature));

```



#### 4.ONG振替

##### ONG振替

インターフェースはONTに類似:

```
ontSdk.nativevm().ong().makeTransfer...
```

##### ONG出金

1. ONGの残高を確認する
2. アカウントを作る
3. 取引を生成する
4. サイン
5. 取引を発送し、ONGを引き出す

```
//Query non-withdrawal ONG
String addr = acct0.getAddressU160().toBase58();
String ong = sdk.nativevm().ong().unboundOng(addr);

//Claim ong，withdraw ONG
com.github.ontio.account.Account account = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey0), ontSdk.signatureScheme);
String hash = sdk.nativevm().ong().withdrawOng(account,toAddr,64000L,payerAcct,30000,500);

```

| 方法         | パラメーター                                                 | パラメーターの説明                                           |
| :----------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| makeClaimOng | String claimer,String to,long amount,String payer,long gaslimit,long gasprice | claimer，who to send，amount, network payer address，gaslimit，gasprice |


## 4.ユーザーへのONG分配

取引所はONGをユーザーに配布するかどうかを選択できます。ONGはOntologyのブロックチェーンの簿記費用、ネットワーク料金とほかのサービス料金を支払います。

### ONGとは

ONGは総計10億で精度は９です。ONT振替取引が発生する場合、ロックが解除されたONGはONTコントラクトによって振替の差出人と受信者に許可されます。 ONT保有者が取得できるONG数量は所有するONTの合計額の割合です。 振替の取引が発効されていない場合、ONT所有者に許可されたONGがたまって今度の振替の取引の時点で配布されます。 このONGの部分は財布アドレスに手動で引き出す必要があります。

### 引出せるONG数量の計算

ロック解除されたONGの数は時間間隔によって決められます。ロック解除ルールは下記のようになります。1秒ごとにONGのロックが解除されます。 ロック解除されたONGの数は一定ではなく、ロック解除された数はOntologyのロック解除の分布曲線によって確定されます。 Ontologyのロック解除の分布曲線の間隔は[5、4、3、3、2、2、2、2、1、1、1、1、1、1、1、1、1、1、1]です。 約31536000ブロックごとにロック解除されたONGの値が変更されます。 約18年後、すべてのONGはロック解除されます。

**ONGロックリスト**
![ong](https://s15.postimg.cc/bwnan7anv/image.png)

### ユーザーへのONG分配

CLIを通してブロックされたONGの残高確認：```./ontology asset unboundong <address|index|label>```

```
$ ./ontology asset unboundong 1
Unclaim Ong:
  Account:Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT
  ONG:23698.8755104

```

CLIを通してブロックされていないONGの引き出し：```./ontology asset withdrawong <address|index|label>```

--wallet, -w  
財布は振替アカウントの財布パスを指定します。デフォルト値は"./wallet.dat"です。

--gasprice  
  gaspriceパラメーターはgasの価格を指定します。gasの価格はノードの取引プールで設定された最低価格より低くすることができません。そうしないと、取引が拒否されます。デフォルト値は0です。取引プールにはブロックにパッキング待ちの取引がある場合、gasの価格にしたがって取引を処理し、gasの価格が高い取引は優先されます。

--gaslimit  
このgaslimitのパラメーターは取引のgasの制限を指します。取引のgasの制限はノードの取引ぷーぷるにある 最低のgasの制限より低くすることができません。そうしないと、取引lが拒否されます。Gasprice * gaslimitは実際のONGコストです。デフォルト値は30,000です。

```
$ ./ontology asset withdrawong 1
Password:
Claim Ong:
  Account:Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT
  Amount:23698.8755104
  TxHash:c696033f1589a88c7b849dbd2ad0c13a9ca695c3220e4f846f9b1096d0972b80

Tip:
  Using './ontology info status c696033f1589a88c7b849dbd2ad0c13a9ca695c3220e4f846f9b1096d0972b80' to query transaction status

```

入金と同じようにONG出金の結果の確認は下記のことも利用できる ```./ontology info status c696033f1589a88c7b849dbd2ad0c13a9ca695c3220e4f846f9b1096d0972b80``` 

例えば:

取引所のすべてのアドレスは一つの財布にあると仮定すれば、次の図は取引所がユーザーAにONGの配布方法に関するプロセスと計算式を表しています。

![ong](./images/ong_en.png)

### ONGの引き出し

ONGの引き出しのプロセスはONTのと同じです。アセットのパラメーターをongに設定:

```
$ ./ontology asset transfer --from Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT --to AS3SCXw8GKTEeXpdwVw7EcC4rqSebFYpfb --amount 10 --asset ong
Password:
Transfer ONG
  From:Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT
  To:AS3SCXw8GKTEeXpdwVw7EcC4rqSebFYpfb
  Amount:10
  TxHash:76b19689042d255f3dac2aaf1b30c86fd83c5abfc983d80b8c64fdcc86f33f5e

Tip:
  Using './ontology info status 76b19689042d255f3dac2aaf1b30c86fd83c5abfc983d80b8c64fdcc86f33f5e' to query transaction status

```

 Java SDKを利用してONGを引き出しには 下記のことをご参照ください。[Java SDK:ONG transfer](https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/sdk_get_start.md#24-ong%E8%BD%AC%E8%B4%A6)

## 5.サインサービス
システムがSDKとCLIをサポートしていない場合、サインサーバーを利用し、取引を生成およびサインできます。

[Ontology Signature Server Tutorials](https://github.com/ontio/ontology/blob/master/docs/specifications/sigsvr.md)

## 6.OEP4トークン

OEP4はOntologyのトークンプロトコル : [OEP-4 instruction](https://github.com/ontio/OEPs/blob/master/OEPS/OEP-4.mediawiki)

Java SDKを利用:

1. OEP4コントラクトハッシュをsdkに設定:

   ```
   OntSdk wm = OntSdk.getInstance();
           wm.setRpc(rpcUrl);
           wm.setRestful(restUrl);
           wm.setDefaultConnect(wm.getRestful());
           wm.neovm().oep4().setContractAddress("55e02438c938f6f4eb15a9cb315b26d0169b7fd7");
   ```

   

2. 振替

   ```
   String txhash = ontSdk.neovm().oep4().sendTransfer(account,  //from
   acct.getAddressU160().toBase58(),             //to
   1000,                                         //amount
   account,                                      //payer
   20000,											//gaslimit					
   500);                                         //gasprice    
   ```

   

3. モニターコントラクトのイベント

   ```
   Object result = ontSdk.getConnect().getSmartCodeEvent(height)
   ```

   結果は次のように:

   ```
   [  
      {  
         "GasConsumed":0,
         "Notify":[  
            {  
               "States":[  
                  "7472616e73666572",
                  "e98f4998d837fcdd44a50561f7f32140c7c6c260",
                  "9d1ce056ac1eb29d73104b3e3c7dfc793c879918",
                  "00a0724e1809"
               ],
               "ContractAddress":"75a5cdc00164266a1ba859da785e31cd914ddbd0"
            }
         ],
         "TxHash":"be0430a6d01404350f4f7a724fabea5e5c3c939668e03979362c5bb6fad68fea",
         "State":1
      }
   ]
   ```

   ONTとONGに精通:

   "State":1 は取引成功を表す

   "ContractAddress":"75a5cdc00164266a1ba859da785e31cd914ddbd0"  はOEP4コントラクトハッシュ 

   "States":[  
                  "7472616e73666572",                                                      //method
                  "e98f4998d837fcdd44a50561f7f32140c7c6c260",       //from
                  "9d1ce056ac1eb29d73104b3e3c7dfc793c879918",     //to
                  "00a0724e1809"                                                                  //amount
               ]

   標準OEP4コントラクトを振替する場合、イベント通知には「振替」の差出先、発送先、数量が含まれます。現在、すべてのOEP4コントラクトはNeovmコントラクトであるので下記のようなフィールドをデコードすることが必要です。 

   方法:

   ```
   byte[] bs =Helper.hexToBytes("7472616e73666572");
   String s = new String(bs); //s is "transfer"
   ```

   差出先:

   ```
   Address from = Address.parse("e98f4998d837fcdd44a50561f7f32140c7c6c260");
   System.out.println("from is " + from.toBase58());
   ```

   振替先:

   ```
    Address to = Address.parse("70a2ababdae0a9d1f9fc7296df3c6d343b772cf7");
    System.out.println("to is " + to.toBase58());
   ```

   数量:

   ```
   BigInteger amount = Helper.BigIntFromNeoBytes(Helper.hexToBytes("00a0724e1809"));
   System.out.println("amount is " + amount);
   ```

   ***注意*** 数量値には「小数」が含まれます。下記の式で算出できます。

   ```
   ontSdk.neovm().oep4().queryDecimals()
   ```

   サーバーのソリューションについては[sigserverガイドをご参照ください。](https://github.com/ontio/documentation/blob/master/exchangeDocs/Sigsvr_Exchange_Guide.md#6-oep4-tokens-transfer)

   ## 7.PAXトークン
   PaxはOntologyで [Paxos](https://www.paxos.com/pax/) の保証によって発行されたOEP4プロトコル安定トークンです。ほかのOEP4　トークンと同じです。コントラクトアドレスを下記のアドレスに変更することが必要です。アドレス：6bbc07bae862db0d7867e4e5b1a13c663e2b4bc8。
   
   [browser](https://explorer.ont.io/contract/6bbc07bae862db0d7867e4e5b1a13c663e2b4bc8/10/1)


## ネイティブコントラクトアドレス

| 名称                         | アドレス(Hex)                            | アドレス(Base58)                   |
| ---------------------------- | ---------------------------------------- | ---------------------------------- |
| ONT Token                    | 0100000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV |
| ONG Token                    | 0200000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbvhfRZMHJ |
| ONT ID                       | 0300000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6Ubvho7BUwN |
| Global Params                | 0400000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbvhrUqmc2 |
| Oracle                       | 0500000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbvhzQYRMK |
| Authorization Manager(Auth)  | 0600000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6Ubvi9BuggV |
| Governance                   | 0700000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK |
| DDXF(Decentralized Exchange) | 0800000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbviKTaSnK |

## FAQ
[FAQ](https://github.com/ontio/documentation/blob/master/exchangeDocs/ONT%2BExchange%2BDocking%2BFAQ.md)

## メインネット更新ノート
SDKバージョンのアップデート状況の確認は下記のノートをご参照ください。
[更新ノート](https://github.com/ontio/documentation/blob/master/exchangeDocs/Ontology%20mainnet%20update%20note.md)