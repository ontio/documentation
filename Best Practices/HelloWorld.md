# HelloWorld on ontology

本文将演示在testmode下，部署一本helloWorld合约，并做执行。

* [HelloWorld on ontology](#helloworld-on-ontology)  
		* [1. 下载ontology并使用ontology创建一个默认账户](#1-下载ontology并使用ontology创建一个默认账户)  
		* [2. 启动testmode](#2-启动testmode)  
		* [3. 通过smartx开发HelloWorld 合约](#3通过smartx开发helloworld-合约)  
		* [4. 部署合约](#4部署合约)  
		* [5. 查询已部署合约信息](#5查询已部署合约信息)  
		* [6. 调用合约方法](#6调用合约方法)  
		* [7. 查询调用交易的事件](#7查询调用交易的事件)  

### 1. 下载ontology并使用ontology创建一个默认账户
  ./ontology account add -d
    Use default setting '-t ecdsa -b 256 -s SHA256withECDSA'
            signature algorithm: ecdsa
            curve: P-256
            signature scheme: SHA256withECDSA
    Password:
    Re-enter Password:

    Index: 1
    Label:
    Address: your address
    Public key: your public key
    Signature scheme: SHA256withECDSA

    Create account successfully.

### 2. 启动testmode
  使用命令`./ontology --testmode  --rest`启动，启动之后大概是这样的
```
    λ ./ontology --testmode --rest
    2018/07/20 15:46:42.918576 [INFO ] GID 1, Config init success
    Password:
    2018/07/20 15:46:45.658436 [INFO ] GID 1, Using account:your public key
    2018/07/20 15:46:45.660443 [INFO ] GID 1, Account init success
    2018/07/20 15:46:46.050346 [INFO ] GID 1, deploy contract address:0239dcf9b4a46f15c5f23f20d52fac916a0bac0d
    2018/07/20 15:46:46.053336 [INFO ] GID 1, deploy contract address:08b6dcfed2aace9190a44ae34a320e42c04b46ac
    2018/07/20 15:46:46.054337 [INFO ] GID 1, deploy contract address:7a2f84e3b94d20da1a8592116c0103c28c5e457e
    2018/07/20 15:46:46.056331 [INFO ] GID 1, deploy contract address:6815cbe7b4dbad4d2d09ae035141b5254a002f79
    2018/07/20 15:46:46.057327 [INFO ] GID 1, deploy contract address:24a15c6aed092dfaa711c4974caf1e9d307bf4b5
    2018/07/20 15:46:46.058325 [INFO ] GID 1, deploy contract address:4d6934f0a524a084bb20cff4cdbea236760bb4a3
    2018/07/20 15:46:46.165447 [INFO ] GID 1, GenesisBlock init success. GenesisBlock hash:00a3691ce01ba51962fd18c770ecb7c7400adf323d59f1190867b4e16f51d7e3

    2018/07/20 15:46:46.167440 [INFO ] GID 1, Ledger init success
    2018/07/20 15:46:46.168464 [INFO ] GID 1, tx pool: the current local gas price is 0
```
   
### 3.通过smartx开发HelloWorld 合约
1. 打开[smartx](http://smartx.ont.io)，按照`HelloWorld示例`编写一个Hello World智能合约，可以直接使用template代码，然后编译成AVM字节码，
将AVM字节码下载下来，命名为`hello.avm`：
![](https://github.com/luodanwg/documentation/blob/master/Best%20Practices/1.png)
![](https://github.com/luodanwg/documentation/blob/master/Best%20Practices/2.png)
![](https://github.com/luodanwg/documentation/blob/master/Best%20Practices/3.png)
![](https://github.com/luodanwg/documentation/blob/master/Best%20Practices/4.png)

    >说明：Hello方法中，Runtime.Notify将传入的参数在链上做一个通知。

### 4.部署合约
使用命令`./ontology contract deploy --code hello.avm --name 'Hello' --version '1.0' --author 'ester' --email 'tester@test.com' --desc 'helloWorld' --account 1 --gaslimit 100000000`将
合约部署到网络上，部署合约命令的详细信息可以使用`./ontology contract deploy -h`获取；

    ```
    Deploy contract:
      Contract Address:362cb5608b3eca61d4846591ebb49688900fedd0
      TxHash:c49865b16009177ed4b06add97f7be1b0b1c246e4d4575c367e918da294d3287
    
    Tip:
      Using './ontology info status c49865b16009177ed4b06add97f7be1b0b1c246e4d4575c367e918da294d3287' to query transaction status
    ```
### 5.查询已部署合约信息
在浏览器中输入`http://localhost:20334/api/v1/contract/362cb5608b3eca61d4846591ebb49688900fedd0`，调用rest接口查询合约信息：
    
    ```
    {"Action":"getcontract","Desc":"SUCCESS","Error":0,"Result":{"Code":"54c56b6c7...","NeedStorage":false,"Name":"Hello","CodeVersion":"1.0","Author":"ester","Email":
    "tester@test.com","Description":"helloWorld"},"Version":"1.0.0"}
    ```
### 6.调用合约方法
使用命令`./ontology contract invoke --address 362cb5608b3eca61d4846591ebb49688900fedd0 --params string:Hello,[string:tester] --gaslimit 200000`调用部署的合约：

    ```
    Invoke:d0ed0f908896b4eb916584d461ca3e8b60b52c36 Params:["Hello",["tester"]]
    Password:
      TxHash:2cc94de8c26fce3be233bef007ec3492043ffc304b79a02d9b612df96e950186
    
    Tip:
      Using './ontology info status 2cc94de8c26fce3be233bef007ec3492043ffc304b79a02d9b612df96e950186' to query transaction status
    ```

    >说明：`--params string:Hello,[string:tester]`指定调用合约传入的参数，这里传入了两个参数，分别是`string:Hello`和`[string:tester]`，这些参数即是传入到合约代码中Main函数执行的参数。

### 7.查询调用交易的事件
根据提示使用命令`./ontology info status 2cc94de8c26fce3be233bef007ec3492043ffc304b79a02d9b612df96e950186`查询交易情况：

    ```
    Transaction states:
    {
       "TxHash": "2cc94de8c26fce3be233bef007ec3492043ffc304b79a02d9b612df96e950186",
       "State": 1,
       "GasConsumed": 0,
       "Notify": [
          {
             "ContractAddress": "362cb5608b3eca61d4846591ebb49688900fedd0",
             "States": [
                "746573746572"
             ]
          }
       ]
    }
    ```

返回的结果中，States即为调用合约通知的msg信息，返回的是一个十六进制字符串，使用编码转换器转化后，得到的结果正是`tester`，即我们在第四步中传入的第二个参数。
