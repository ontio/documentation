
android sdk 项目地址[ 链接 ](https://github.com/ontio-community/ontology-andriod-sdk)。

## 1. 与链交互

### 1.1 初始化

```
String ip = "http://polaris1.ont.io"; //test net
String ip = "http://dappnode1.ont.io"; //main net
String rpcUrl = ip + ":" + "20336";
OntSdk ontSdk = OntSdk.getInstance();
ontSdk.setRpc(rpcUrl);
ontSdk.setDefaultConnect(ontSdk.getRpc());

```

### 1.2 查询

#### 查询 Unbound ong

通过地址查询余额: `ONT` , `ONG` , `claimable ONG` and  `unbound ONG` .

测试网服务器  [https://polarisexplorer.ont.io](https://polarisexplorer.ont.io)

主网服务器 [https://explorer.ont.io](https://explorer.ont.io)

````
/api/v1/explorer/address/balance/{address}
method：GET
{
    "Action": "QueryAddressBalance",
    "Error": 0,
    "Desc": "SUCCESS",
    "Version": "1.0",
    "Result": [
        {
            "Balance": "138172.922008484",
            "AssetName": "ong"
        },
        {
            "Balance": "14006.83021186",
            "AssetName": "waitboundong"// This is the unbound ONG
        },
        {
            "Balance": "71472.14798338",
            "AssetName": "unboundong" // This is the claimable ONG
        },
        {
            "Balance": "8637767",
            "AssetName": "ont"
        }
    ]
}
````

#### 查询交易历史

查询交易历史.

````
url：/api/v1/explorer/address/{address}/{pagesize}/{pagenumber} or /api/v1/explorer/address/{address}/{assetname}/{pagesize}/{pagenumber}
method：GET
successResponse：
{
    "Action": "QueryAddressInfo",
    "Error": 0,
    "Desc": "SUCCESS",
    "Version": "1.0",
    "Result": {
        "AssetBalance": [
            {
                "Balance": "1.93199363",
                "AssetName": "ong"
            },
            {
                "Balance": "0.0020775",
                "AssetName": "waitboundong"
            },
            {
                "Balance": "0.0019375",
                "AssetName": "unboundong"
            },
            {
                "Balance": "1500",
                "AssetName": "ont"
            }
        ],
        "TxnList": [
            {
                "TxnTime": 1535894950,
                "TxnType": 209,
                "ConfirmFlag": 1,
                "Fee": "0.010000000",
                "TxnHash": "a8a75e3d44e5aff5de6dabcbee1492c89da1561e244da47327f178956b7c0015",
                "Height": 261617,
                "BlockIndex": 1,
                "TransferList": [
                    {
                        "FromAddress": "AUmzW4MYCtDakB59hFybV7aGFZVi2S7FLc",
                        "Amount": "1.000000000",
                        "ToAddress": "AUmzW4MYCtDakB59hFybV7aGFZVi2S7FLc",
                        "AssetName": "ont"
                    }
                ]
            },
            {
                "TxnTime": 1535310138,
                "TxnType": 209,
                "ConfirmFlag": 1,
                "Fee": "0.010000000",
                "TxnHash": "819a67b5c7c29fd234178ba9b901c6ed5af0734bafc76ffba6d1380cf2e07e8e",
                "Height": 218711,
                "BlockIndex": 1,
                "TransferList": [
                    {
                        "FromAddress": "AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV",
                        "Amount": "1.627527000",
                        "ToAddress": "AUmzW4MYCtDakB59hFybV7aGFZVi2S7FLc",
                        "AssetName": "ong"
                    }
                ]
            }
        ],
        "TxnTotal": 33
    }
}
````


### 1.3 其他接口


| No   |                    Main   Function                     |     Description      |
| ---- | :----------------------------------------------------: | :------------------: |
| 1    |           ontSdk.getConnect().getNodeCount()           |     node count     |
| 2    |            ontSdk.getConnect().getBlock(15)            |        get block        |
| 3    |          ontSdk.getConnect().getBlockJson(15)          |        get block in json        |
| 4    |       ontSdk.getConnect().getBlockJson("blockhash")       |        get block by blockhash       |
| 5    |         ontSdk.getConnect().getBlock("blockhash")         |        get block by blockhash       |
| 6    |          ontSdk.getConnect().getBlockHeight()          |     get Block Height     |
| 7    |      ontSdk.getConnect().getTransaction("txhash")      |       get Transaction       |
| 8    | ontSdk.getConnect().getStorage("contractaddress", key) |   get Storage   |
| 9   |       ontSdk.getConnect().getBalance("address")        |       get Balance       |
| 10   | ontSdk.getConnect().getContractJson("contractaddress") |     get Contract     |
| 11   |       ontSdk.getConnect().getSmartCodeEvent(59)        |   get SmartContract Event   |
| 12   |    ontSdk.getConnect().getSmartCodeEvent("txhash")     |   get SmartContract Event   |
| 13   |  ontSdk.getConnect().getBlockHeightByTxHash("txhash")  |   get Block Height of Tx Hash   |
| 14   |      ontSdk.getConnect().getMerkleProof("txhash")      |    get Merkle Proof    |
| 15   | ontSdk.getConnect().sendRawTransaction("txhexString")  |       send Raw Transaction       |
| 16   |  ontSdk.getConnect().sendRawTransaction(Transaction)   |       send Raw Transaction       |
| 17   |    ontSdk.getConnect().sendRawTransactionPreExec()     |    send RawTransaction PreExec    |
| 18   |  ontSdk.getConnect().getAllowance("ont","from","to")   |    get Allowance    |
| 19   |        ontSdk.getConnect().getMemPoolTxCount()         | getMemPoolTxCount |
| 20   |        ontSdk.getConnect().getMemPoolTxState("")         | getMemPoolTxState |


#### 1.3.1 查询 ONT/ONG 余额

```
ontSdk.getConnect().getBalance("AVcv8YBABi9m6vH7faq3t8jWNamDXYytU2");

ont：
System.out.println(ontSdk.nativevm().ont().queryName());
System.out.println(ontSdk.nativevm().ont().querySymbol());
System.out.println(ontSdk.nativevm().ont().queryDecimals());
System.out.println(ontSdk.nativevm().ont().queryTotalSupply());

ong：
System.out.println(ontSdk.nativevm().ong().queryName());
System.out.println(ontSdk.nativevm().ong().querySymbol());
System.out.println(ontSdk.nativevm().ong().queryDecimals());
System.out.println(ontSdk.nativevm().ong().queryTotalSupply());



```

#### 1.3.2 查询交易是否在交易池中

```
ontSdk.getConnect().getMemPoolTxState("d441a967315989116bf0afad498e4016f542c1e7f8605da943f07633996c24cc")


response in pool:

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

or not in pool

{
    "Action": "getmempooltxstate",
    "Desc": "UNKNOWN TRANSACTION",
    "Error": 44001,
    "Result": "",
    "Version": "1.0.0"
}

```

#### 1.3.3 查询交易是否成功

查询智能合约事件: 

```
ontSdk.getConnect().getSmartCodeEvent("d441a967315989116bf0afad498e4016f542c1e7f8605da943f07633996c24cc")


response:
{
    "Action": "getsmartcodeeventbyhash",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": {
        "TxHash": "20046da68ef6a91f6959caa798a5ac7660cc80cf4098921bc63604d93208a8ac",
        "State": 1,//表示交易执行成功
        "GasConsumed": 0,//表示交易手续费是0
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

通过块高查询智能合约

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


## 2. 账号




### 2.1 助记词和 keystore


用户可以使用 `menmonic` 代码创建帐户。 本体使用的 `BIP44` 路径是 “m / 44'/ 1024'/ 0'/ 0/0”。

Mnemonic code
```

//generate Mnemonic Code
String code = MnemonicCode.generateMnemonicCodesStr();

//get private keyfrom Mnemonic Code
byte[] prikey = MnemonicCode.getPrikeyFromMnemonicCodesStrBip44(code);
System.out.println(Helper.toHexString(prikey));

//create account
com.github.ontio.sdk.wallet.Account acct = ontSdk.getWalletMgr().createAccountFromPriKey("name",prikey,"password");

```

Keystore 是备份用户帐户的数据结构。它可以保存在 `QR` 码中。

用户可以使用手机扫描该 `QR` 码来读取数据并恢复帐户。 

您可以查看 [ Wallet Specification ](Wallet_Specification_en.md) 以查看更多信息。


```
//get keystore
Scrypt scrypt = new Scrypt();
com.github.ontio.sdk.wallet.Account account = OntSdk.getInstance().getWalletMgr().getWallet().getAccount("address");
//TODO change scrypt and account value

//export keystore
Map keystore = WalletQR.exportAccountQRCode(scrypt,account);
System.out.println(JSON.toJSONString(keystore));

//import keystore
String prikey2 = WalletQR.getPriKeyFromQrCode(JSON.toJSONString(keystore),"password");

//
Account acct2 = new Account(prikey2,SignatureScheme.SHA256WITHECDSA);
 ```

导入 keystore

 ```
 
String prikey2 = WalletQR.getPriKeyFromQrCode(JSON.toJSONString(keystore),"password");

 ```

### 2.2 随机创建账号


```
com.github.ontio.sdk.wallet.Account acct = ontSdk.getWalletMgr().createAccount("name","password");
ontSdk.getWalletMgr().writeWallet();
```

从钱包中删除帐户:

```

ontSdk.getWalletMgr().getWallet().removeAccount("")
ontSdk.getWalletMgr().writeWallet();

```

### 2.3 通过私钥创建账号


```
com.github.ontio.sdk.wallet.Account acct = ontSdk.getWalletMgr().createAccountFromPriKey("name",prikey,"password");
ontSdk.getWalletMgr().writeWallet();
```

### 2.4 通过 WIF 创建账号

```

byte[] prikey = com.github.ontio.account.Account.getPrivateKeyFromWIF("");
com.github.ontio.sdk.wallet.Account acct = ontSdk.getWalletMgr().createAccountFromPriKey("name",prikey,"password");
ontSdk.getWalletMgr().writeWallet();

```



### 2.5 地址

单签地址和多签地址

```

String privatekey0 = "c19f16785b8f3543bbaf5e1dbb5d398dfa6c85aaad54fc9d71203ce83e505c07";
String privatekey1 = "49855b16636e70f100cc5f4f42bc20a6535d7414fb8845e7310f8dd065a97221";
String privatekey2 = "1094e90dd7c4fdfd849c14798d725ac351ae0d924b29a279a9ffa77d5737bd96";

//
com.github.ontio.account.Account acct0 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey0), ontSdk.defaultSignScheme);
Address sender = acct0.getAddressU160();

com.github.ontio.sdk.wallet.Account acct = ontSdk.getWalletMgr().createAccountFromPriKey("name",prikey,"password");
acct.address

//base58 address decode
sender = Address.decodeBase58("AVcv8YBABi9m6vH7faq3t8jWNamDXYytU2")；

multi-signature address：
Address recvAddr = Address.addressFromMultiPubKeys(2, acct1.serializePublicKey(), acct2.serializePublicKey());


```

| 方法                  | 参数                      | 描述                       |
| :---------------------- | :------------------------ | :----------------------------- |
| addressFromMultiPubkeys | int m,byte\[\]... pubkeys | M,pubkey |



## 3. 数字资产



### 3.1 ONT 转账

example：[demo](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/OntDemo.java)

```
String hash = ontSdk.nativevm().ont().sendTransfer(acct0,"AUe2KKPnNMnM7hLHj6dEPJ4PA2m4pyJt2d",200,payerAcct,20000,500);

```
| 方法       | 参数                                                     | 描述                       |
| :----------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| sendTransfer | String sendTransfer(Account sendAcct, String recvAddr, long amount, Account payerAcct, long gaslimit, long gasprice) | sendAcct,recvAddr,amount,payer,gaslimit,gasprice |



### 3.2 ONG 转账

参考例子：[例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/OngDemo.java)



ONG 转账：

```
String hash = ontSdk.nativevm().ong().sendTransfer(acct0,"AUe2KKPnNMnM7hLHj6dEPJ4PA2m4pyJt2d",200,payerAcct,20000,500);

```
### 3.3 Oep4 转账

参考例子：[例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/Oep4Demo.java)



Oep4 转账：

```
String hash = ontSdk.nativevm().oep4().sendTransfer(acct0,"AUe2KKPnNMnM7hLHj6dEPJ4PA2m4pyJt2d",200,payerAcct,20000,500);

```


### 3.4 提取 ONG

1. 查询 `unboundOng`
2. 提取 `ONG`

```
query unboundOng:
String addr = acct0.getAddressU160().toBase58();
String ong = sdk.nativevm().ong().unboundOng(addr);

//withdrawOng
com.github.ontio.account.Account account = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey0), ontSdk.signatureScheme);
String hash = sdk.nativevm().ong().withdrawOng(account,toAddr,64000L,payerAcct,30000,500);

```

| 函数      | 参数                      | 描述                       |
| :----------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| withdrawOng | String claimer,String to,long amount,String payer,long gaslimit,long gasprice | from,to,amount,payer,gaslimit,gasprice |




## 3.5 构造转账

参考例子：[例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/MakeTxWithoutWalletDemo.java)

#### 3.5.1 转账

```

Address sender = acct0.getAddressU160();
Address payer = acct1.getAddressU160();
Address recvAddr = acct1;

//Address recvAddr = Address.addressFromMultiPubKeys(2, acct1.serializePublicKey(), acct2.serializePublicKey());


long amount = 1000;
Transaction tx = ontSdk.nativevm().ont().makeTransfer(sender.toBase58(),recvAddr.toBase58(), amount,payer.toBase58(),30000,0);


ontSdk.signTx(tx, new com.github.ontio.account.Account[][]{{acct0}});//sender
ontSdk.addSign(tx,new com.github.ontio.account.Account[][]{{acct1}});//payer

ontSdk.getConnect().sendRawTransaction(tx.toHexString());


```



| 函数      | 参数                      | 描述                       |
| :----------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| makeTransfer | String sender，String recvAddr,long amount,String payer,long gaslimit,long gasprice | sender,to,amount,payer,gaslimit,gasprice |
| makeTransfer | State\[\] states,String payer,long gaslimit,long gasprice    | multi state                                   |

#### 3.5.2 签名

如果转出方和网络费付款人不是同一个人，两者都需要签名.

```
1.add Sign
ontSdk.addSign(tx,acct0);

2.add MultiSign if address is MultiSign address
ontSdk.addMultiSign(tx,2,new com.github.ontio.account.Account[]{acct0,acct1});

```



#### 3.5.3 一转多多转多

1. 构造多个 `state`
2. 签名

```
Address sender1 = acct0.getAddressU160();
Address sender2 = Address.addressFromMultiPubKeys(2, acct1.serializePublicKey(), acct2.serializePublicKey());
int amount = 10;
int amount2 = 20;

State state = new State(sender1, recvAddr, amount);
State state2 = new State(sender2, recvAddr, amount2);
Transaction tx = ontSdk.nativevm().ont().makeTransfer(new State[]{state1,state2},sender1.toBase58(),30000,0);

//signature：
ontSdk.signTx(tx, new com.github.ontio.account.Account[][]{{acct0}});
ontSdk.addMultiSign(tx,2,new com.github.ontio.account.Account[]{acct1, acct2});

```



## 4. 数字身份

#### 4.1 注册

参考例子：[例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/NativeOntIdDemo.java)

```

Identity identity = ontSdk.getWalletMgr().createIdentity(password);
ontSdk.nativevm().ontId().sendRegister(identity,password,payerAcct,ontSdk.DEFAULT_GAS_LIMIT,0);
 
```

#### 4.2 查询身份

参考例子：[例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/NativeOntIdDemo.java)

```

String ddo2 = ontSdk.nativevm().ontId().sendGetDDO(identity.ontid);
 
```

#### 4.3 身份 keystore

导出助记词

```
//export keystore
Scrypt scrypt = new Scrypt();
com.github.ontio.sdk.wallet.Identity identity = OntSdk.getInstance().getWalletMgr().getWallet().getIdentity("ontid");
Map keystore = WalletQR.exportIdentityQRCode(scrypt,identity);
System.out.println(JSON.toJSONString(keystore));


 ```

导入助记词

 ```
 
String prikey2 = WalletQR.getPriKeyFromQrCode(JSON.toJSONString(keystore),"password");

 ```


## 5. 节点质押

### 5.1 注册候选节点

注册候选节点：

````

//@param ontid {string} User's ONT ID
//@param peerPubkey {string} Peer's public key
//@param keyNo {int} Id of public key.Usually set as 1.
//@param payerAcct {Address} User's address to pay fee
//@param initPos {long} Number of ONT to pay for register

String peerPubkey = Helper.toHexString(account8.serializePublicKey());
String txhash = sdk.nativevm().governance().registerCandidate(account,peerPubkey,initPos,identity.ontid,password,identity.controls.get(0).getSalt(),keyNo,payerAcct,gasLimit,gasPrice);

````

### 5.2 取消注册

取消注册：

```
String peerPubkey = Helper.toHexString(account8.serializePublicKey());
String txhash = sdk.nativevm().governance().unRegisterCandidate(account,peerPubkey,payerAcct,gasLimit,gasPrice);

```

### 5.3 提取 

提取 `ONT`:

```

String[] peerPubkeys = new String[]{"03e1e09221c9f513df76273f3cec0d033ee6056b159300d7b1072fc7020eadccbb"};
String txhash = sdk.nativevm().governance().withdraw(account,peerPubkeys,new long[]{9999},payerAcct,gasLimit,gasPrice);

```

### 5.4 退出质押

退出质押:

```
String[] peerPubkeys = new String[]{"03e1e09221c9f513df76273f3cec0d033ee6056b159300d7b1072fc7020eadccbb"};
String txhash = sdk.nativevm().governance().quitNode(account,peerPubkey,payerAcct,gasLimit,gasPrice);

```







