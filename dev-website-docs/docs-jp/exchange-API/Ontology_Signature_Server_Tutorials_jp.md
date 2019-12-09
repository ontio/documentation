# Ontology署名サーバーのチュートリアル

Ontology 署名サーバー - sigsvrは、トランザクションに署名するためのrpcサーバーです。署名サーバーは127.0.0.1アドレスにバインドされ、ローカルマシンから送信された署名要求のみをサポートします。

* [Ontology署名サーバーのチュートリアル](#Ontology署名サーバーのチュートリアル)
	* [1.署名サービスの起動](#1.署名サービスの起動)
		* [署名サービスの起動のパラメーター](#署名サービスの起動のパラメーター)
	* [2.署名サービス方法](#2.署名サービス方法)
		* [2.1署名サービスの呼び出し方法](#2.1署名サービスの呼び出し方法)
		* [2.2生の取引の署名](#2.2生の取引の署名)
		* [2.3生の取引の複数署名](#2.3生の取引の複数署名)
		* [2.4取引転送の署名](#2.4取引転送の署名)
		* [2.5ネイティブコントラクト呼び出し署名](#2.5ネイティブコントラクト呼び出し署名)
		* [2.6Neovm契約により呼び出された署名](#2.6Neovm契約により呼び出された署名)

## 1.署名サービスの起動

### 署名サービスの起動のパラメーター

--loglevel   
loglevel パラメータを使用して、sigsvr出力のログレベルを設定します。sigsvrは7種類のログレベルをサポートしています- 0:Debug 1:Info 2:Warn 3:Error 4:Fatal 5:Trace 6:MaxLevel。ログレベルは低いから高いになり、出力ログの量は高いから低いになります。既定値は1です。つまり、レベル1以上のログのみが出力されます。


--wallet, -w   
wallet パラメーターは、sigsvrの起動時に財布ファイルのパスを指定します。既定値は "./wallet.dat" です。

--account, -a   
account パラメータは、 sigsvr が始まるときにアカウントアドレスを指定します。account が null の場合は、既定アカウントを使用します。

--cliport  
署名サーバーがバインドされているポート番号。既定値は20000です。

## 2.署名サービス方法

署名サービスは現在、生の取引に対して単一の署名と複数の署名、
ONT / ONG転送取引と署名、ネイティブコントラクト呼び出し署名できる取引、Neovm契約により呼び出された署名できる取引をサポートしています。

### 2.1署名サービスの呼び出し方法

署名サービスはjson rpcサーバーであり、POSTメソッドを採用しています。 要求されたサービスパスは次のとおりです。

```
http://localhost:20000/cli
```
リクエスト構造

```
{
	"qid":"XXX",    //Request ID， the same response will bring the same qid
	"method":"XXX", //Requested method name
	"params":{
		//The request parameters of the specific method, which are filled in according to the calling request method
	}
}
```
レスポンス構造:

```
{
    "qid": "XXX",   //Request ID
    "method": "XXX",//Requested method name
    "result": {     //Response result
        "signed_tx": "XXX"  //The transaction after signature
    },
    "error_code": 0,//Error code，zero represents success, non-zero represents failure
    "error_info": ""//Error description
}
```

エラーコード：

エラーコード  | エラー説明
--------|-----------
1001 | Invalid http method
1002 | Invalid http request
1003 |  Invalid request parameter
1004 | Unsupported method
1005 | Account is locked
1006 | Invalid transactions
1007 | ABI is not found
1008 | ABI is not matched
9999 | Unknown error

### 2.2生の取引の署名

方法名：sigrawtx

リクエストパラメータ:

```
{
    "raw_tx":"XXX"      //Unsigned Transaction
}
```
レスポンス結果:

```
{
    "signed_tx":"XXX"   //Signed Transaction
}
```
例:

リクエスト:
```
{
	"qid":"1",
	"method":"sigrawtx",
	"params":{
		"raw_tx":"00d14150175b000000000000000000000000000000000000000000000000000000000000000000000000ff4a0000ff00000000000000000000000000000000000001087472616e736665722a0101d4054faaf30a43841335a2fbc4e8400f1c44540163d551fe47ba12ec6524b67734796daaf87f7d0a0000"
	}
}
```
レスポンス:

```
{
    "qid": "1",
    "method": "sigrawtx",
    "result": {
        "signed_tx": "00d14150175b00000000000000000000000000000000011e68f7bf0aaba1f18213639591f932556eb674ff4a0000ff00000000000000000000000000000000000001087472616e736665722a0101d4054faaf30a43841335a2fbc4e8400f1c44540163d551fe47ba12ec6524b67734796daaf87f7d0a000101231202026940ba3dba0a385c44e4a187af75a34e281b96200430db2cbc688a907e5fb54501014101d3998581639ff873f4e63936ae63d6ccd56d0f756545ba985951073f293b07507e2f1a342654c8ad28d092dd6d8250a0b29f5c00c7866df3c4df1cff8f00c6bb"
    },
    "error_code": 0,
    "error_info": ""
}
```

### 2.3生の取引の複数署名

秘密鍵はさまざまな人々の手にあるため、マルチ署名方式は複数回呼び出す必要があります。

方法名：sigmutilrawtx  

リクエストパラメータ:
```
{
    "raw_tx":"XXX", //Unsigned Transaction
    "m":xxx         //The minimum number of signatures required for multiple signatures
    "pub_keys":[
        //Public key list of signature
    ]
}
```
レスポンス結果:

```
{
    "signed_tx":"XXX" //Signed Transaction
}
```
例:

リクエスト:

```
{
	"qid":"1",
	"method":"sigmutilrawtx",
	"params":{
		"raw_tx":"00d12454175b000000000000000000000000000000000000000000000000000000000000000000000000ff4a0000ff00000000000000000000000000000000000001087472616e736665722a01024ce71f6cc6c0819191e9ec9419928b183d6570012fb5cfb78c651669fac98d8f62b5143ab091e70a0000",
		"m":2,
		"pub_keys":[
		    "1202039b196d5ed74a4d771ade78752734957346597b31384c3047c1946ce96211c2a7",
		    "120203428daa06375b8dd40a5fc249f1d8032e578b5ebb5c62368fc6c5206d8798a966"
		]
	}
}
```

レスポンス:

```
{
    "qid": "1",
    "method": "sigmutilrawtx",
    "result": {
        "signed_tx": "00d12454175b00000000000000000000000000000000024ce71f6cc6c0819191e9ec9419928b183d6570ff4a0000ff00000000000000000000000000000000000001087472616e736665722a01024ce71f6cc6c0819191e9ec9419928b183d6570012fb5cfb78c651669fac98d8f62b5143ab091e70a000102231202039b196d5ed74a4d771ade78752734957346597b31384c3047c1946ce96211c2a723120203428daa06375b8dd40a5fc249f1d8032e578b5ebb5c62368fc6c5206d8798a9660201410166ec86a849e011e4c18d11d64ca0afbeaebf8a4c975be1eab4dcb8795abef5c908647294822ddaadaf2e4ae2432c9c8d143ceba8fa6355d6dfe59f846ac5a41a"
    },
    "error_code": 0,
    "error_info": ""
}
```
### 2.4取引転送の署名


転送取引の署名プロセスを簡素化するために、転送取引構造関数が提供されています。 転送する場合、転送パラメータのみを提供する必要があります。

方法名：sigtransfertx  
リクエストパラメータ:
```
{
	"gas_price":XXX,  //gasprice 
	"gas_limit":XXX,  //gaslimit
	"asset":"ont",    //asset: ont or ong
	"from":"XXX",     //Payment account
	"to":"XXX",       //Receipt address
	"amount":XXX      //transfer amount. Note that since the precision of ong is 9, it is necessary to multiply the actual transfer amount by 1000000000 when making ong transfer.
}
```
レスポンス結果:

```
{
    "signed_tx":XXX     //Signed Transaction
}
```

例:

リクエスト:
```
{
	"qid":"t",
	"method":"sigtransfertx",
	"params":{
		"gas_price":0,
		"gas_limit":30000,
		"asset":"ont",
		"from":"TADPWFL3yHoHeNN3Bx1RUCrrXjU35EmeXp",
		"to":"TA5gYXCSiUq9ejGCa54M3yoj9kfMv3ir4j",
		"amount":10
	}
}
```

レスポンス:

```
{
    "qid": "t",
    "method": "sigtransfertx",
    "result": {
        "signed_tx": "00d1184a175b000000000000000050c3000000000000011e68f7bf0aaba1f18213639591f932556eb674ff4a0000ff00000000000000000000000000000000000001087472616e736665722a0102ae97551187192cdae14052c503b5e64b32013d01397cafa8cc71ae9e555e439fc0f0a5ded12a2a0a000101231202026940ba3dba0a385c44e4a187af75a34e281b96200430db2cbc688a907e5fb545010141016a0097dbe272fd61384d95aaeb02e9460e18078c9f4cd524d67ba431033b10d20de72d1bc819bf6e71c6c17116f4a7a9dfc9b395738893425d684faa30efea9c"
    },
    "error_code": 0,
    "error_info": ""
}
```

### 2.5ネイティブコントラクト呼び出し署名
ネイティブコントラクト呼び出し取引は、ABIに従って構築および署名されます。


注意：
sigsvrが起動すると、現在のディレクトリの「./cmd/abi/native」の下にあるネイティブコントラクトabiが検索されます。
ネイティブディレクトリにこのコントラクトのabiがない場合、1007エラーが返されます。



方法名：signativeinvoketx  

リクエストパラメータ:

```
{
    "gas_price":XXX,    //gasprice
    "gas_limit":XXX,    //gaslimit
    "address":"XXX",    //The address that invokes native contract
    "method":"XXX",     //The method that invokes native contract
    "version":0,        //The version that invokes native contract
    "params":[
        //The parameters of the Native contract are constructed according to the ABI of calling method. All values ​​are string type.
    ]
}
```
レスポンス結果:
```
{
    "signed_tx":XXX     //Signed Transaction
}
```


例としての ont 転送取引：

リクエスト:

```
{
	"Qid":"t",
	"Method":"signativeinvoketx",
	"Params":{
		"gas_price":0,
		"gas_limit":50000,
		"address":"ff00000000000000000000000000000000000001",
		"method":"transfer",
		"version":0,
		"params":[
			[
				[
				"TA587BCw7HFwuUuzY1wg2HXCN7cHBPaXSe",
				"TA5gYXCSiUq9ejGCa54M3yoj9kfMv3ir4j",
				"1000"
				]
			]
		]
	}
}
```
レスポンス:

```
{
    "qid": "1",
    "method": "signativeinvoketx",
    "result": {
        "signed_tx": "00d1a55b175b00000000000000003075000000000000011e68f7bf0aaba1f18213639591f932556eb674ff4c0000ff00000000000000000000000000000000000001087472616e736665722c01011e68f7bf0aaba1f18213639591f932556eb67401397cafa8cc71ae9e555e439fc0f0a5ded12a2afde803000101231202026940ba3dba0a385c44e4a187af75a34e281b96200430db2cbc688a907e5fb545010141013eaf77601c847c4244b5b5a1b22153d6231c29853838b8a963c34834987f86cb6f63a8e5b454899457ee0be56eec16339efdbc4876649c72f313f04c5fa2ba11"
    },
    "error_code": 0,
    "error_info": ""
}
```

### 2.6Neovm契約により呼び出された署名

Neovmパラメータコントラクトは、配列、バイト配列、文字列、整数、およびブール型をサポートします。 パラメーターを作成する場合、パラメーターのタイプとパラメーター値を指定する必要があります。 パラメーター値は文字列型を使用します。 配列はオブジェクトの配列であり、Neovmがサポートするパラメーターのすべてのタイプと数量をサポートします。

方法名：signeovminvoketx  

リクエストパラメータ:
```
{
    "gas_price":XXX,    //gasprice
    "gas_limit":XXX,    //gaslimit
    "address":"XXX",    //The address that invokes NeoVM contract
    "params":[
        //The parameters of the Native contract. All values ​​are string type.
    ]
}
```
レスポンス結果:
```
{
    "signed_tx":XXX     //Signed Transaction
}
```

例:

リクエスト:

```
{
	"qid": "t",
	"method": "signeovminvoketx",
	"params": {
		"gas_price": 0,
		"gas_limit": 50000,
		"address": "8074775331499ebc81ff785e299d406f55224a4c",
		"version": 0,
		"params": [
			{
				"type": "string",
				"value": "Time"
			},
			{
				"type": "array",
				"value": [
					{
						"type": "string",
						"value": ""
					}
				]
			}
		]
	}
}
```
レスポンス:

```
{
    "qid": "t",
    "method": "signeovminvoketx",
    "result": {
        "signed_tx": "00d18f5e175b000000000000000050c3000000000000011e68f7bf0aaba1f18213639591f932556eb67480216700008074775331499ebc81ff785e299d406f55224a4c00080051c10454696d65000101231202026940ba3dba0a385c44e4a187af75a34e281b96200430db2cbc688a907e5fb54501014101b93bef619b4d7900b57f91e1810b268f9e10eb39fd563f23ce01323cde6273518000dc77d2d2231bc39428f1fa35d294990676015dbf6b4dfd2e6c9856034cc1"
    },
    "error_code": 0,
    "error_info": ""
}
```
