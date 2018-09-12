# Ontology 钱包开发文档

钱包开发分数字资产和数字身份两部分。

本文档大纲如下：

* [Ontology 钱包开发文档](#ontology-钱包开发文档)
    * [钱包开发说明](#钱包开发说明)
	* [SDK说明](#sdk说明)
	    * [与链交互接口](#与链交互接口)
	    	* [1. 初始化](#1-初始化)
        	* [2. 查询](#2-查询)
        		* [查询ONT，ONG余额](#查询ontong余额)
        		* [查询交易是否在交易池中](#查询交易是否在交易池中)
        		* [查询交易是否调用成功](#查询交易是否调用成功)
        	* [3. 其他与链交互接口列表：](#3-其他与链交互接口列表)
		* [账号管理](#账号管理)
			* [助记词和Keystore使用：](#助记词和keystore使用)
			* [不使用钱包管理：](#不使用钱包管理)
				* [随机创建账号：](#随机创建账号)
				* [根据私钥创建账号](#根据私钥创建账号)
			* [使用钱包管理：](#使用钱包管理)
		    * [地址生成](#地址生成)
		* [数字资产](#数字资产)
			* [1. ONT转账](#1-ont转账)
                * [ONT转账](#ont转账)
			* [2. ONG转账](#2-ong转账)
				* [ONG转账](#ong转账)
				* [提取ONG](#提取ong)
			* [3. 构造转账](#3-构造转账)
				* [构造转账交易并发送](#构造转账交易并发送)
            	* [多次签名](#多次签名)
            	* [一转多或多转多](#一转多或多转多)
        * [数字身份](#数字身份)
        	* [注册身份](#注册身份)
        	* [查询身份](#查询身份)
	* [部署Ontology同步节点](#部署ontology同步节点)


​
## 钱包开发说明

钱包开发分数字资产和数字身份两部分。

ONT中有两种资产：原生资产和合约资产。对接时主要涉及查询、转账、ONG提取等接口。

数字身份主要包括注册，更新属性，查询身份等功能。


## SDK说明

Java SDK 使用说明：[Java SDK 使用说明](https://github.com/ontio/ontology-java-sdk/blob/master/docs) 

Ts SDK 使用说明：[Ts SDK 使用说明](https://github.com/ontio/ontology-ts-sdk/tree/master/docs) 

Android SDK 使用说明：[Android SDK](https://github.com/ontio-community/ontology-andriod-sdk)

Go SDK 使用说明：[Go SDK](https://github.com/ontio/ontology-go-sdk) 

钱包规范：[钱包规范](https://github.com/ontio/documentation/blob/master/docs/pages/doc_zh/SDKs/ontology_wallet_file_specification_zh.md)

以下代码例子为Java sdk，android sdk 与 java sdk接口相同。

### 与链交互接口

#### 1. 初始化

```
String ip = "http://polaris1.ont.io"; //测试网
String ip = "http://dappnode1.ont.io"; //主网
String rpcUrl = ip + ":" + "20336";
OntSdk ontSdk = OntSdk.getInstance();
ontSdk.setRpc(rpcUrl);
ontSdk.setDefaultConnect(ontSdk.getRpc());

```

#### 2. 查询

##### 查询ONT，ONG余额

```
ontSdk.getConnect().getBalance("AVcv8YBABi9m6vH7faq3t8jWNamDXYytU2");

查ont信息：
System.out.println(ontSdk.nativevm().ont().queryName());
System.out.println(ontSdk.nativevm().ont().querySymbol());
System.out.println(ontSdk.nativevm().ont().queryDecimals());
System.out.println(ontSdk.nativevm().ont().queryTotalSupply());

查ong信息：
System.out.println(ontSdk.nativevm().ong().queryName());
System.out.println(ontSdk.nativevm().ong().querySymbol());
System.out.println(ontSdk.nativevm().ong().queryDecimals());
System.out.println(ontSdk.nativevm().ong().queryTotalSupply());



```

##### 查询交易是否在交易池中

```
ontSdk.getConnect().getMemPoolTxState("d441a967315989116bf0afad498e4016f542c1e7f8605da943f07633996c24cc")


response 交易池存在此交易:

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

或 交易池不存在此交易

{
    "Action": "getmempooltxstate",
    "Desc": "UNKNOWN TRANSACTION",
    "Error": 44001,
    "Result": "",
    "Version": "1.0.0"
}

```

##### 查询交易是否调用成功

查询智能合约推送内容

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

根据块高查询智能合约事件，返回有事件的交易

```
ontSdk.getConnect().getSmartCodeEvent(10)

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

#### 3. 其他与链交互接口列表：

| No   |                    Main   Function                     |     Description      |
| ---- | :----------------------------------------------------: | :------------------: |
| 1    |       ontSdk.getConnect().getGenerateBlockTime()       |   查询VBFT出块时间   |
| 2    |           ontSdk.getConnect().getNodeCount()           |     查询节点数量     |
| 3    |            ontSdk.getConnect().getBlock(15)            |        查询块        |
| 4    |          ontSdk.getConnect().getBlockJson(15)          |        查询块        |
| 5    |       ontSdk.getConnect().getBlockJson("txhash")       |        查询块        |
| 6    |         ontSdk.getConnect().getBlock("txhash")         |        查询块        |
| 7    |          ontSdk.getConnect().getBlockHeight()          |     查询当前块高     |
| 8    |      ontSdk.getConnect().getTransaction("txhash")      |       查询交易       |
| 9    | ontSdk.getConnect().getStorage("contractaddress", key) |   查询智能合约存储   |
| 10   |       ontSdk.getConnect().getBalance("address")        |       查询余额       |
| 11   | ontSdk.getConnect().getContractJson("contractaddress") |     查询智能合约     |
| 12   |       ontSdk.getConnect().getSmartCodeEvent(59)        |   查询智能合约事件   |
| 13   |    ontSdk.getConnect().getSmartCodeEvent("txhash")     |   查询智能合约事件   |
| 14   |  ontSdk.getConnect().getBlockHeightByTxHash("txhash")  |   查询交易所在高度   |
| 15   |      ontSdk.getConnect().getMerkleProof("txhash")      |    获取merkle证明    |
| 16   | ontSdk.getConnect().sendRawTransaction("txhexString")  |       发送交易       |
| 17   |  ontSdk.getConnect().sendRawTransaction(Transaction)   |       发送交易       |
| 18   |    ontSdk.getConnect().sendRawTransactionPreExec()     |    发送预执行交易    |
| 19   |  ontSdk.getConnect().getAllowance("ont","from","to")   |    查询允许使用值    |
| 20   |        ontSdk.getConnect().getMemPoolTxCount()         | 查询交易池中交易总量 |
| 21   |        ontSdk.getConnect().getMemPoolTxState()         | 查询交易池中交易状态 |

### 账号管理

#### 助记词和keystore使用：

##### 助记词和keystore接口

```

//生成助记词
String code = MnemonicCode.generateMnemonicCodesStr();

//根据助记词获取私钥
byte[] prikey = MnemonicCode.getPrikeyFromMnemonicCodesStrBip44(code);
System.out.println(Helper.toHexString(prikey));

//get keystore
Scrypt scrypt = new Scrypt();
com.github.ontio.sdk.wallet.Account account = new com.github.ontio.sdk.wallet.Account();
//TODO change scrypt and account value

//导出keystore
Map keystore = WalletQR.exportAccountQRCode(scrypt,account);
System.out.println(JSON.toJSONString(keystore));

//导入keystore
String prikey2 = WalletQR.getPriKeyFromQrCode(JSON.toJSONString(keystore),"password");

//生成账号
Account acct2 = new Account(prikey2,SignatureScheme.SHA256WITHECDSA);
 ```

 

#### 不使用钱包管理：

##### 随机创建账号：

```
com.github.ontio.account.Account acct = new com.github.ontio.account.Account(ontSdk.defaultSignScheme);
acct.serializePrivateKey();//私钥
acct.serializePublicKey();//公钥

acct.getAddressU160().toBase58();//base58地址
```

##### 根据私钥创建账号

```
com.github.ontio.account.Account acct0 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey0), ontSdk.defaultSignScheme);
com.github.ontio.account.Account acct1 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey1), ontSdk.defaultSignScheme);
com.github.ontio.account.Account acct2 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey2), ontSdk.defaultSignScheme);

```

##### 根据WIF格式私钥创建账号

```

byte[] prikey = com.github.ontio.account.Account.getPrivateKeyFromWIF("");
com.github.ontio.account.Account acct0 = new com.github.ontio.account.Account(prikey, ontSdk.defaultSignScheme);

```



             
#### 使用钱包管理：

钱包规范：[钱包规范](https://github.com/ontio/documentation/blob/master/docs/pages/doc_zh/SDKs/ontology_wallet_file_specification_zh.md)

参考例子：[例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/WalletDemo.java) 

```

#### 在钱包中批量创建账号:
ontSdk.getWalletMgr().createAccounts(10, "passwordtest");
ontSdk.getWalletMgr().writeWallet();

随机创建:
AccountInfo info0 = ontSdk.getWalletMgr().createAccountInfo("passwordtest");

通过私钥创建:
AccountInfo info = ontSdk.getWalletMgr().createAccountInfoFromPriKey("passwordtest","e467a2a9c9f56b012c71cf2270df42843a9d7ff181934068b4a62bcdd570e8be");

获取账号
com.github.ontio.account.Account acct0 = ontSdk.getWalletMgr().getAccount(info.addressBase58,"passwordtest");

```



#### 地址生成

包括单签地址和多签地址,生成方式与NEO地址相同。

```
单签地址生成：
String privatekey0 = "c19f16785b8f3543bbaf5e1dbb5d398dfa6c85aaad54fc9d71203ce83e505c07";
String privatekey1 = "49855b16636e70f100cc5f4f42bc20a6535d7414fb8845e7310f8dd065a97221";
String privatekey2 = "1094e90dd7c4fdfd849c14798d725ac351ae0d924b29a279a9ffa77d5737bd96";

//生成账号，获取地址
com.github.ontio.account.Account acct0 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey0), ontSdk.defaultSignScheme);
Address sender = acct0.getAddressU160();

//base58地址解码
sender = Address.decodeBase58("AVcv8YBABi9m6vH7faq3t8jWNamDXYytU2")；

多签地址生成：
Address recvAddr = Address.addressFromMultiPubKeys(2, acct1.serializePublicKey(), acct2.serializePublicKey());


```

| 方法名                  | 参数                      | 参数描述                       |
| :---------------------- | :------------------------ | :----------------------------- |
| addressFromMultiPubkeys | int m,byte\[\]... pubkeys | 最小验签个数(<=公钥个数)，公钥 |

### 数字资产





#### 1. ONT转账

参考例子：[例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/OntDemo.java)

##### ONT转账

```
String hash = ontSdk.nativevm().ont().sendTransfer(acct0,"AUe2KKPnNMnM7hLHj6dEPJ4PA2m4pyJt2d",200,payerAcct,20000,500);
```
| 方法名       | 参数                                                         | 参数描述                                                     |
| :----------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| sendTransfer | String sendTransfer(Account sendAcct, String recvAddr, long amount, Account payerAcct, long gaslimit, long gasprice) | 发送方账户，接收方地址，金额，网络费付款人账户，gaslimit，gasprice |



#### 2. ONG转账

参考例子：[例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/OngDemo.java)

##### ONG转账

接口与ONT类似：

```
ontSdk.nativevm().ong().sendTransfer(acct0,"AUe2KKPnNMnM7hLHj6dEPJ4PA2m4pyJt2d",200,payerAcct,20000,500);
```

##### 提取ONG

1. 查询是否有ONG可以提取
2. 创建账号
3. 构造交易
4. 签名
5. 发送提取ONG交易

```
查询未提取ong:
String addr = acct0.getAddressU160().toBase58();
String ong = sdk.nativevm().ong().unboundOng(addr);

//提取ong
com.github.ontio.account.Account account = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey0), ontSdk.signatureScheme);
String hash = sdk.nativevm().ong().withdrawOng(account,toAddr,64000L,payerAcct,30000,500);

```

| 方法名       | 参数                                                         | 参数描述                                                     |
| :----------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| withdrawOng | String claimer,String to,long amount,String payer,long gaslimit,long gasprice | ong提取者，提给谁，金额，网络付费人地址，gaslimit，gasprice |


### 数字身份

##### 注册身份

参考例子：[例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/NativeOntIdDemo.java)

```

Identity identity = ontSdk.getWalletMgr().createIdentity(password);
ontSdk.nativevm().ontId().sendRegister(identity,password,payerAcct,ontSdk.DEFAULT_GAS_LIMIT,0);
 
```

##### 查询身份

参考例子：[例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/NativeOntIdDemo.java)

```

String ddo2 = ontSdk.nativevm().ontId().sendGetDDO(identity.ontid);
 
```

### 3. 构造转账

参考例子：[例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/MakeTxWithoutWalletDemo.java)

##### 构造转账交易并发送

```
转出方与收款方地址：
Address sender = acct0.getAddressU160();
Address recvAddr = acct1;
//多签地址生成
//Address recvAddr = Address.addressFromMultiPubKeys(2, acct1.serializePublicKey(), acct2.serializePublicKey());

构造转账交易：
long amount = 1000;
Transaction tx = ontSdk.nativevm().ont().makeTransfer(sender.toBase58(),recvAddr.toBase58(), amount,sender.toBase58(),30000,0);


对交易做签名：
ontSdk.signTx(tx, new com.github.ontio.account.Account[][]{{acct0}});
//多签地址的签名方法：
ontSdk.signTx(tx, new com.github.ontio.account.Account[][]{{acct1, acct2}});
//如果转出方与网络费付款人不是同一个地址，需要添加网络费付款人的签名


发送交易：
ontSdk.getConnect().sendRawTransaction(tx.toHexString());


```



| 方法名       | 参数                                                         | 参数描述                                                     |
| :----------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| makeTransfer | String sender，String recvAddr,long amount,String payer,long gaslimit,long gasprice | 发送方地址，接收方地址，金额，网络费付款人地址，gaslimit，gasprice |
| makeTransfer | State\[\] states,String payer,long gaslimit,long gasprice    | 一笔交易包含多个转账。                                       |

##### 多次签名

如果转出方与网络费付款人不是同一个地址，需要添加网络费付款人的签名

```
1.添加单签签名
ontSdk.addSign(tx,acct0);

2.添加多签签名
ontSdk.addMultiSign(tx,2,new com.github.ontio.account.Account[]{acct0,acct1});

```



##### 一转多或多转多

1. 构造多个state的交易
2. 签名
3. 一笔交易上限为1024笔转账

```
Address sender1 = acct0.getAddressU160();
Address sender2 = Address.addressFromMultiPubKeys(2, acct1.serializePublicKey(), acct2.serializePublicKey());
int amount = 10;
int amount2 = 20;

State state = new State(sender1, recvAddr, amount);
State state2 = new State(sender2, recvAddr, amount2);
Transaction tx = ontSdk.nativevm().ont().makeTransfer(new State[]{state1,state2},sender1.toBase58(),30000,0);

//第一个转出方是单签地址，第二个转出方是多签地址：
ontSdk.signTx(tx, new com.github.ontio.account.Account[][]{{acct0}});
ontSdk.addMultiSign(tx,2,new com.github.ontio.account.Account[]{acct1, acct2});

```












## 部署Ontology同步节点

如果钱包直接发送交易到主网，而不是发送到钱包后台的同步节点，请忽略此步骤。

[如何部署Ontology同步节点](https://github.com/ontio/documentation/blob/master/exchangeDocs/Ontology%20交易所对接文档.md#1%E9%83%A8%E7%BD%B2ontology%E5%90%8C%E6%AD%A5%E8%8A%82%E7%82%B9)







