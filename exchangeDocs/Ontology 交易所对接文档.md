# Ontology 交易所对接文档

ONT中有两种资产：原生资产和合约资产。原生资产如ont和ong。交易所对接时，主要处理这两种类型资产的充值、提现等操作。

本文档大纲如下：

[TOC]





​

​

​

## 1.部署Ontology同步节点

部署Ontology同步节点主要有两种方式：

### 从源码获取

克隆ontology仓库到 **$GOPATH/src/github.com/ontio** 目录

```
$ git clone https://github.com/ontio/ontology.git
```

或者

```
$ go get github.com/ontio/ontology
```

用第三方包管理工具glide拉取依赖库

```
$ cd $GOPATH/src/github.com/ontio/ontology
$ glide install
```

用make编译源码

```
$ make
```

成功编译后会生成两个可以执行程序

- `ontology`: 节点程序/以命令行方式提供的节点控制程序

### 直接从release获取

 [release page](https://github.com/ontio/ontology/releases)

### 服务器部署

1. #### 创建钱包

   - 通过CLI，创建节点运行所需的钱包文件 wallet.dat

     ```
     $ ./ontology-linux account add -d
     Use default setting '-t ecdsa -b 256 -s SHA256withECDSA' 
     	signature algorithm: ecdsa 
     	curve: P-256 
     	signature scheme: SHA256withECDSA 
     Password:
     Re-enter Password:

     Index: 1
     Label: 
     Address: TA4fG1ybsg6XHXp6qGymiubG4V1qN9rWRL
     Public key: 120203ac15db156e2af2c6f70b846de387e1dae0cc73a3a489e43db28b17ac7ae07e65
     Signature scheme: SHA256withECDSA

     Create account successfully.
     ```

     ​

   - 目录结构

     ```
        $ tree
        └── ontology
            ├── ontology
            └── wallet.dat
     ```


2. #### 启动节点

   由于同步节点只同步记账节点生成的区块，并不参与网络共识，因此可以通过--disableconsensus参数关闭网络共识模块

   ```./ontology --disableconsensus```

   节点启动默认是关闭websocket和rest端口的，需要开放上述端口，可以配置以下参数

   ```
   RESTFUL OPTIONS:
     --rest            Enable restful api server
     --restport value  Restful server listening port (default: 20334)
     
   WEB SOCKET OPTIONS:
     --ws            Enable websocket server
     --wsport value  Ws server listening port (default: 20335)
   ```

   ​

## 2. 使用CLI客户端

### 安全策略

强制要求：交易所必须使用白名单或防火墙以屏蔽外部服务器请求，否则会有重大安全隐患。

CLI 本身不提供远程开关钱包功能，打开钱包时也没有验证过程。因此，安全策略由交易所根据自身情况制定。由于钱包要一直保持打开状态以便处理用户的提现，因此，从安全角度考虑，钱包必须运行在独立的服务器上，并参考下表配置好端口防火墙。

|               | Mainnet default port |
| ------------- | -------------------- |
| Rest Port     | 20334                |
| Websorcket    | 20335                |
| Json RPC port | 20336                |
| Node port     | 20338                |

### CLI说明

#### 创建钱包

交易所需要创建一个在线钱包管理用户充值地址。钱包是用来存储账户（包含公钥和私钥）、合约地址等信息，是用户持有资产的最重要的凭证，一定要保管好钱包文件和钱包密码，不要丢失或泄露。 交易所不需要为每个地址创建一个钱包文件，通常一个钱包文件可以存储用户所有充值地址。也可以使用一个冷钱包（离线钱包）作为更安全的存储方式。

```
$ ./ontology account add -d
use default value for all options
Enter a password for encrypting the private key:
Re-enter password:

Create account successfully.
Address:  TA9TVuR4Ynn4VotfpExY5SaEy8a99obFPr
Public key: 120202a1cfbe3a0a04183d6c25ceff1e34957ace6e4899e4361c2e1a2bc3c817f90936
Signature scheme: SHA256withECDSA	
```

**ONT的公钥和私钥生成算法和NEO一致，同一个私钥对应的ONT和NEO的公钥地址是相同的。**

####  生成充值地址等

一个钱包可以存储多个地址，交易所需要为每个用户生成一个充值地址。

充值地址有两种生成方式：

- 用户第一次充值（ONT/ONG）时，程序动态创建 ONT 地址，优点：无需人工定期创建地址；缺点：不方便备份钱包。

  要动态创建地址，可以使用 Java SDK 的 实现，程序会返回创建的地址。参照 Java SDK  [随机创建账号](#随机创建账号)


- 交易所提前创建一批 ONT 地址，并在用户第一次充值（ONT/ONG）时，给用户分配一个 ONT 地址。优点：方便备份钱包；缺点：当地址不足时需要人工创建 ONT 地址。

  要批量创建地址，执行 CLI 的 ./ontology account add -n [n]  -w [wallet file]命令，-d 方括号为可选参数，默认值为 1 -w 为指定钱包文件，默认为wallet.dat。例如要一次创建100个地址:

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
Address: TA5JtcQC21fLtUy6Eacfkhg8pLEywTv82b
Public key: 120203eaa379d7ca8fdd9705854a72b36b831fb59e0c9cf8863e4bad177d2ad35b90a2
Signature scheme: SHA256withECDSA

Index: 2
Label: 
Address: TA6VB77YfWE7AayMijgzVkaewF8geagja1
Public key: 1202024ee20b5028dbff7d2ab3db47a48bad599cc04b1fb31ff605dc24412415b973ef
Signature scheme: SHA256withECDSA

Index: 3
Label: 
Address: TA5JpD5tTWyyPANxmzvXec1BXUYWpaaGBk
Public key: 120202b8e3f88081d99a88bf019380c27a8da301802157752ed1f8db27e3e108fae0ea
Signature scheme: SHA256withECDSA
....
```



## 3. 处理资产交易

### 交易所需要开发的交易对接程序

1. 使用CLI / API监控新区块
2. 根据交易信息完成用户充值
3. 存储交易所相关交易记录

### 用户充值

关于用户充值，交易所需要了解以下内容：

- 一般来讲，由于每个交易所的策略不同，交易所充值地址里的余额可能并不等于用户在交易所里的余额。

- Ontology 地址中包含 ONT 和 ONG 两种资产，交易所记录用户充值时需要判断充值资产的资产类型，以免把 ONT 和ONG 的充值弄混。

- Ontology钱包是一个全节点，要保持在线才能同步区块，可以通过CLI命令查看当前区块高度， 判断节点状态。

  ```
  $ ./ontology info curblockheight
  CurrentBlockHeight:2
  ```

  ​


- 交易所内的用户之间转账不需要通过区块链，而可以直接修改数据库中的用户余额进行，只有充值提现才上链。

例：

1. 用户向```TA8MoGmzS4T6g3T1CMGEVFiNGkZnn7ixw9```地址进行充值

2. 通过CLI ```./ontology info block <block number | block hash>```  监控区块信息：

   ```
   $ ./ontology info block 209304
   {
      "Hash": "cc92674c0efae4d64e0d974cf4eff78fa9297ca804595d82132afe372ffbc120",
      "Header": {
         "Version": 0,
         "PrevBlockHash": "1c27e93d0079ab701d3dce85edc22dc03c3d6ed58ac733829797a77e657fbead",
         "TransactionsRoot": "f4b39ac8f39e4eb92bbb8cc4f46b427bf68624a225c56fc0fa6310a6012538f0",
         "BlockRoot": "19a65b8fbedc9ebad41d4026e58bcc27a0bed396d95269a27cf1f725ad6a171e",
         "Timestamp": 1528195357,
         "Height": 209304,
         "ConsensusData": 5441406265160202485,
         "ConsensusPayload": "",
         "NextBookkeeper": "TAACeeRwwbHrEZZNCbqFQrNSutcsR3xkK3",
         "Bookkeepers": [
            "120202a76a434b18379e3bda651b7c04e972dadc4760d1156b5c86b3c4d27da48c91a1",
            "12020384d843c02ecef233d3dd3bc266ee0d1a67cf2a1666dc1b2fb455223efdee7452",
            "120203c43f136596ee666416fedb90cde1e0aee59a79ec18ab70e82b73dd297767eddf",
            "120203fab19438e18d8a5bebb6cd3ede7650539e024d7cc45c88b95ab13f8266ce9570"
         ],
         "SigData": [
            "01536b64896f2cd47af30721fad3640980f7ad06042859d75632871735e0fef7d1f404ab0b9904a3c6c67bc9f4887ad663bf7af9bd6239790ab5e1ec1cda7b0066",
            "018367431fb032992cb364df5cd1832c72de63d95d8901e1efadd4271773a4e634697cd33c07c3322dc83a79278112ff9b541e9373651ef96a9415bd547ee113ce",
            "0167b8192cd608bb9589057e87c8da18a32f7aa3664a0790d86d4bbccccd374ce7f092c3521f26ee40dcc91d7a2ad6c23f057f1408d5bf9ba8202165ea8a889653"
         ],
         "Hash": "cc92674c0efae4d64e0d974cf4eff78fa9297ca804595d82132afe372ffbc120"
      },
      "Transactions": [
         {
            "Version": 0,
            "Nonce": 1528195351,
            "GasPrice": 0,
            "GasLimit": 30000,
            "Payer": "0148cb3cb662b84b4bc59bd6e84bafe13b3c0c1f",
            "TxType": 209,
            "Payload": {
               "Code": "00000000000000000000000000000000000000000001087472616e736665722a010148cb3cb662b84b4bc59bd6e84bafe13b3c0c1f01bb163b9224d91160c8fbd65585d3a64c7b1a7f0a",
               "GasLimit": 0,
               "VmType": 255
            },
            "Attributes": [],
            "Sigs": [
               {
                  "PubKeys": [
                     "12020345ed8085fe96f4e816d5d8bda6d387f8df3ab1e52c88548e35315236732d6483"
                  ],
                  "M": 1,
                  "SigData": [
                     "01d2d2587d8c79d5aaef3b43a938a9d60c0eebc898a21df9fc089b2c891a3c553ee855c4f59a38c8f2d649aa1950a12444b39f795bbfbe5d9e69cd57765c7a5619"
                  ]
               }
            ],
            "Hash": "f4b39ac8f39e4eb92bbb8cc4f46b427bf68624a225c56fc0fa6310a6012538f0"
         }
      ]
   }

   ```

   3. 通过CLI ```./ontology info status```根据Transaction Hash 取得block中的所有Transaction信息

```
$ ./ontology info status f4b39ac8f39e4eb92bbb8cc4f46b427bf68624a225c56fc0fa6310a6012538f0
Transaction states:
{
   "TxHash": "f4b39ac8f39e4eb92bbb8cc4f46b427bf68624a225c56fc0fa6310a6012538f0",
   "State": 1,
   "GasConsumed": 0,
   "Notify": [
      {
         "ContractAddress": "0000000000000000000000000000000000000001",
         "States": [
            "transfer",
            "TA5zt4PrSzjWA7DaVHVw2nhxH5ZY9uQiGq",
            "TA8MoGmzS4T6g3T1CMGEVFiNGkZnn7ixw9",
            10
         ]
      }
   ]
}
```

判断“State” 为 1  代表交易成功，为 0 代表明确失败

解析“Notify"数组：

​     ContractAddress：合约地址	```0000000000000000000000000000000000000001``` 为ONT

​						        ```0000000000000000000000000000000000000002``` 为ONG

​     States：数组

​                第一个元素："transfer" 代表转账操作

​		第二个元素：为from 地址

​                第三个元素：为to 地址

​                第四个元素：为转账数量（**ONT为实际数量为整数，ONG为实际数量×10^9**）

只需过滤 to 地址为交易所为用户生成的充值地址，即可取得用户的充值记录

### 充值记录

同用户充值，交易所需要写代码监控每个区块的每个交易，在数据库中记录下所有充值提现交易。如果有充值交易就要修改数据库中的用户余额。



### 处理用户提现请求

关于用户提现，交易所需要完成以下操作：

1. 记录用户提现，修改用户账户余额。

2. 使用CLI命令对用户提现地址进行转账：

   ```
   $ ./ontology asset transfer --from TA5zt4PrSzjWA7DaVHVw2nhxH5ZY9uQiGq --to TA8MoGmzS4T6g3T1CMGEVFiNGkZnn7ixw9 --amount 100
   Password:
   Transfer ONT
     From:TA5zt4PrSzjWA7DaVHVw2nhxH5ZY9uQiGq
     To:TA8MoGmzS4T6g3T1CMGEVFiNGkZnn7ixw9
     Amount:100
     TxHash:9863485348031a333681d81e69bc93de66fe93dce3e17cd55a928025a23b512f

   Tip:
     Using './ontology info status 9863485348031a333681d81e69bc93de66fe93dce3e17cd55a928025a23b512f' to query transaction status

   ```

   命令的参数列表如下：

   --wallet, -w  
   wallet指定转出账户钱包路径，默认值为:"./wallet.dat"

   --gasprice  
   gasprice参数指定转账交易的gas price。交易的gas price不能小于接收节点交易池设置的最低gas price，否则交易会被拒绝。默认值为0。当交易池中有交易在排队等待打包进区块时，交易池会按照gas price有高到低排序，gas price高的交易会被优先处理。

   --gaslimit  
   gaslimit参数指定转账交易的gas limit。交易的gas limit不能小于接收节点交易池设置的最低gas limit，否则交易会被拒绝。gasprice * gaslimit 为账户实际支持的ONG 费用。 默认值为30000。

   --asset  
   asset参数指定转账的资产类型，ont表示ONT，ong表示ONG。默认值为ont。

   --from   
   from参数指定转出账户地址。

   --to  
   to参数指定转入账户地址。

   --amount   
   amount参数指定转账金额。注意：由于ONT的精度是1，因此如果输入的是个浮点值，那么小数部分的值会被丢弃；ONG的精度为9，因此超出9位的小数部分将会被丢

   ​

   确认交易结果：

   - 使用返回的交易hash直接查询：

     ```
     ./ontology info status 9863485348031a333681d81e69bc93de66fe93dce3e17cd55a928025a23b512f
     Transaction states:
     {
        "TxHash": "9863485348031a333681d81e69bc93de66fe93dce3e17cd55a928025a23b512f",
        "State": 1,
        "GasConsumed": 0,
        "Notify": [
           {
              "ContractAddress": "0000000000000000000000000000000000000001",
              "States": [
                 "transfer",
                 "TA5zt4PrSzjWA7DaVHVw2nhxH5ZY9uQiGq",
                 "TA8MoGmzS4T6g3T1CMGEVFiNGkZnn7ixw9",
                 100
              ]
           }
        ]
     }

     ```

     ​

   - 同”用户充值“，监控新区块中的交易并过滤出交易所地址向用户提现地址转账的成功交易

3. 从返回的 Json 格式交易详情中提取交易ID，记录在数据库中。

4. 等待区块链确认，确认后将提现记录标志为提现成功。

   类似充值时对区块链的监控，提现也一样，监控时若发现区块中的某个交易 ID 与提现记录中的交易 ID 相等，则该交易已经确认，即提现成功。

5. 如果交易始终没有得到确认，即通过交易hash查询不到对应的event log,则需要

   - 通过rpc/SDK接口查询交易是否在交易池中（参照[Java SDK:ONT和ONG转账](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/sdk_get_start.md#2-%E5%8E%9F%E7%94%9F%E8%B5%84%E4%BA%A7ont%E5%92%8Cong%E8%BD%AC%E8%B4%A6))，若在，需要等待共识节点打包出块后再查询

   - 若不在，则可认为该交易失败，需要重新进行转账操作。

   - 若该交易长时间没有被打包，可能是由于gas price过低。

     ​


## 4. 使用Java SDK

Java SDK 使用说明：[Java SDK 使用说明](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/sdk_get_start.md) 

### 账号管理

#### 不使用钱包管理：

##### 随机创建账号：

```java
com.github.ontio.account.Account acct = new com.github.ontio.account.Account(ontSdk.defaultSignScheme);
acct.serializePrivateKey();//私钥
acct.serializePublicKey();//公钥
acct.getAddressU160().toBase58();//base58地址
```

##### 根据私钥创建账号

```java
com.github.ontio.account.Account acct0 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey0), ontSdk.defaultSignScheme);
com.github.ontio.account.Account acct1 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey1), ontSdk.defaultSignScheme);
com.github.ontio.account.Account acct2 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey2), ontSdk.defaultSignScheme);

```



#### 使用钱包管理：

[例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/WalletDemo.java) 

```java

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



### 地址生成

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

### ONT和ONG转账

参考例子：[例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/MakeTxWithoutWalletDemo.java)

#### 1. 初始化

```
String ip = "http://polaris1.ont.io";
String rpcUrl = ip + ":" + "20336";
OntSdk ontSdk = OntSdk.getInstance();
ontSdk.setRpc(rpcUrl);
ontSdk.setDefaultConnect(wm.getRpc());

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
                "ContractAddress": "ff00000000000000000000000000000000000001",
                "States": [
                    "transfer",
                    "T9yD14Nj9j7xAB4dbGeiX9h8unkKHxuWwb",
                    "TA4WVfUB1ipHL8s3PRSYgeV1HhAU3KcKTq",
                    1000000000
                ]
            }
        ]
    },
    "Version": "1.0.0"
}

```

根据块高查询智能合约事件，返回有事件的交易hash

```
ontSdk.getConnect().getSmartCodeEvent(10)

response:
{
    "Action": "getsmartcodeeventbyheight",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": [
        "20046da68ef6a91f6959caa798a5ac7660cc80cf4098921bc63604d93208a8ac",
        "38e88c4f3e566737d45f25acbbfeaaebd226cc71aef16ba266c55bf6f8333966",
        "724c6f7645e489e9405e6a9745e89a27c13e3a8563b71e71197fc80fe94023ab",
        "923320009925c6468a483e5dad2989f590d21a9f8bc1230b8fc31e7459da32c8"
    ],
    "Version": "1.0.0"
}

```

#### 其他与链交互接口列表：

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

#### 3. ONT转账

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

#### 使用签名机签名

- **构造交易并签名**

1. 构造交易，序列化交易，发送交易给签名机
2. 签名机接收到交易，反序列化，检查交易，添加签名
3. 发送交易

```
序列化交易发送给签名机：
Transaction tx = ontSdk.nativevm().ont().makeTransfer(sender.toBase58(),recvAddr.toBase58(), amount,sender.toBase58(),30000,0);
String txHex = tx.toHexString();

接收方反序列化交易并签名：

Transaction txRx = Transaction.deserializeFrom(Helper.hexToBytes(txHex));
//查看交易中转账内容
System.out.println(Transfers.deserializeFrom(Contract.deserializeFrom(txRx.code).args).json());

签名：
ontSdk.addSign(txRx,acct0);
```

- **对数据做签名**

[例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/SignatureDemo.java) 

```
com.github.ontio.account.Account acct = new com.github.ontio.account.Account(ontSdk.defaultSignScheme);

byte[] data = "12345".getBytes();
byte[] signature = ontSdk.signatureData(acct, data);

System.out.println(ontSdk.verifySignature(acct.serializePublicKey(), data, signature));

```



#### 4. ONG转账

##### ONG转账

接口与ONT类似：

```
ontSdk.nativevm().ong().makeTransfer...
```

##### 提取ONG

1. 查询是否有ONG可以提取
2. 创建账号
3. 构造交易
4. 签名
5. 发送提取ONG交易

```
查询未提取ong:
String claimer = acct0.getAddressU160().toBase58();
sdk.nativevm().ong().unclaimOng(claimer);

//claim ong，提取ong
com.github.ontio.account.Account acct0 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey0), ontSdk.signatureScheme);

Transaction tx = sdk.nativevm().ong().makeClaimOng(claimer,claimer,10,claimer,30000,0);
sdk.signTx(tx, new com.github.ontio.account.Account[][]{{acct0}});

ontSdk.getConnect().sendRawTransaction(tx.toHexString());
```

| 方法名       | 参数                                                         | 参数描述                                                     |
| :----------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| makeClaimOng | String claimer,String to,long amount,String payer,long gaslimit,long gasprice | claim提取者，提给谁，金额，网络付费人地址，gaslimit，gasprice |



## 5. 给用户分发ONG

交易所可以选择是否给用户分发ONG， ONG用于支付Ontology区块链的记账费用和网络等附加服务费。

### 什么是ONG

ONG对应ONT总量为10亿，精度为9。当ONT转账交易发生时，解绑的ONG将会由ONT合约授权给转账发起人和接收人，而ONT持有者所能获得的ONG的数量是由ONT持有者的占ONT总量的百分比决定，若转账交易一直不被触发，则授权给ONT持有者的ONG将会被累加，在下一次转账交易发生时，一次性发放，这部分的ONG需要手动提取到自己的钱包地址中。

### 计算可提取的ONG总量

ONG解绑的数量由时间区间决定，解绑规则如下：每一秒钟解绑一次ONG，解绑的ONG数量并不是一直恒定的不变，而是按照本体解绑分布曲线呈现递减式解绑，本体解绑分布曲线区间为[5, 4, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]，大约经过每31536000个时间区间块后，按照本体解绑分布曲线，ONG的解绑值将会发生一次变更，大约经过约18年后，全部ONG将会解绑完毕。

**ONG解绑列表**
![ong](https://s15.postimg.cc/bwnan7anv/image.png)

### 给用户分发ONG

通过CLI查看未解绑ONG余额：```./ontology asset unboundong <address|index|label>```

```
$ ./ontology asset unboundong 1
Unclaim Ong:
  Account:TA5zt4PrSzjWA7DaVHVw2nhxH5ZY9uQiGq
  ONG:23698.8755104

```

通过CLI提取解绑的ONG：```./ontology asset withdrawong <address|index|label>```

--wallet, -w  
wallet指定提取账户的钱包路径，默认值为:"./wallet.dat"

--gasprice  
gasprice参数指定转账交易的gas price。交易的gas price不能小于接收节点交易池设置的最低gas price，否则交易会被拒绝。默认值为0。当交易池中有交易在排队等待打包进区块时，交易池会按照gas price有高到低排序，gas price高的交易会被优先处理。

--gaslimit  
gaslimit参数指定转账交易的gas limit。交易的gas limit不能小于接收节点交易池设置的最低gas limit，否则交易会被拒绝。gasprice * gaslimit 为账户实际支持的ONG 费用。 默认值为30000。

```
$ ./ontology asset withdrawong 1
Password:
Claim Ong:
  Account:TA5zt4PrSzjWA7DaVHVw2nhxH5ZY9uQiGq
  Amount:23698.8755104
  TxHash:c696033f1589a88c7b849dbd2ad0c13a9ca695c3220e4f846f9b1096d0972b80

Tip:
  Using './ontology info status c696033f1589a88c7b849dbd2ad0c13a9ca695c3220e4f846f9b1096d0972b80' to query transaction status

```

同”用户充值“，可根据```./ontology info status c696033f1589a88c7b849dbd2ad0c13a9ca695c3220e4f846f9b1096d0972b80```

查询提取ONG交易的结果。

例如：

假设交易所的所有地址都在一个钱包里，下图显示了交易所向某用户 A 分发 GAS 的流程和计算公式：

![ong](./images/ong1.png)

### 用户提取ONG

用户提取ONG的流程和提取ONT的流程一致，只需指定asset 参数为ong即可：

```
$ ./ontology asset transfer --asset ong --from TA5zt4PrSzjWA7DaVHVw2nhxH5ZY9uQiGq --to TA8MoGmzS4T6g3T1CMGEVFiNGkZnn7ixw9 --amount 100
Password:
Transfer ONG
  From:TA5zt4PrSzjWA7DaVHVw2nhxH5ZY9uQiGq
  To:TA8MoGmzS4T6g3T1CMGEVFiNGkZnn7ixw9
  Amount:100
  TxHash:a77f84040700f0a68d0ce401f6eae5786744b56061c1888b5848f4dc46648b4f

Tip:
  Using './ontology info status a77f84040700f0a68d0ce401f6eae5786744b56061c1888b5848f4dc46648b4f' to query transaction status

```

使用Java SDK 提取ONG，请参照[Java SDK:ONG转账](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/sdk_get_start.md#24-ong%E8%BD%AC%E8%B4%A6)

## 5. 签名服务

[Ontology 签名服务器使用说明](./Ontology+签名服务器使用说明.md)