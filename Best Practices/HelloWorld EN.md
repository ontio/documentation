# HelloWorld on Ontology

This text will demonstrate the deployment and execution of HelloWorld contract in  testmode.

* [HelloWorld on ontology](#helloworld-on-ontology)  
   * * 1. Download Ontology and use Ontology to create a default account.
     * 2. Start testmode
     * 3. Develop HelloWorld contract via SmartX
     * 4. Deploy contract
     * 5. Deployed contract information query
     * 6. Contract method invocation
     * 7. Query the event that invokes the transaction

### 1. Download Ontology and use Ontology to create a default account
Linux and Mac users can download via curl https://dev.ont.io/ontology_install | sh , or you can download from [here](https://github.com/ontio/ontology/releases). 

Create an account:

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

### 2. Start testmode
Use command`./ontology --testmode  --rest` to start, below is what you will see after you start:

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

### 3. Use SmartX HelloWorld contract
1. Open [SmartX](http://smartx.ont.io), write a HelloWorld smart contract according to `HelloWorld示例`, you can directly use template code and compile into AVM bytecode,

Download AVM bytecode, name it as `hello.avm` :

  ![](https://github.com/ontio/documentation/blob/master/Best%20Practices/pic/1.png)
  ![](https://github.com/ontio/documentation/blob/master/Best%20Practices/pic/2.png)
  ![](https://github.com/ontio/documentation/blob/master/Best%20Practices/pic/3.png)
  ![](https://github.com/ontio/documentation/blob/master/Best%20Practices/pic/4.png)

### 4. Contract deployment
Use command `./ontology contract deploy --code hello.avm --name 'Hello' --version '1.0' --author 'ester' --email 'tester@test.com' --desc 'helloWorld' --account 1 --gaslimit 100000000` to deploy contract on the network. Details for contract deployment command can be acquired by using `./ontology contract deploy -h`;

    ```
    Deploy contract:
      Contract Address:362cb5608b3eca61d4846591ebb49688900fedd0
      TxHash:c49865b16009177ed4b06add97f7be1b0b1c246e4d4575c367e918da294d3287
    
    Tip:
      Using './ontology info status c49865b16009177ed4b06add97f7be1b0b1c246e4d4575c367e918da294d3287' to query transaction status
    ```
    
### 5. Query deployed contract information
Enter `http://localhost:20334/api/v1/contract/362cb5608b3eca61d4846591ebb49688900fedd0` in the explorer and invoke rest interface to query contract information:
    ```
    {"Action":"getcontract","Desc":"SUCCESS","Error":0,"Result":{"Code":"54c56b6c7...","NeedStorage":false,"Name":"Hello","CodeVersion":"1.0","Author":"ester","Email":
    "tester@test.com","Description":"helloWorld"},"Version":"1.0.0"}
    ```
    
### 6. Contract invocation method
Use command `./ontology contract invoke --address 362cb5608b3eca61d4846591ebb49688900fedd0 --params string:Hello,[string:tester] --gaslimit 200000` to invoke deployed contract:

    ```
    Invoke:d0ed0f908896b4eb916584d461ca3e8b60b52c36 Params:["Hello",["tester"]]
    Password:
      TxHash:2cc94de8c26fce3be233bef007ec3492043ffc304b79a02d9b612df96e950186
    
    Tip:
      Using './ontology info status 2cc94de8c26fce3be233bef007ec3492043ffc304b79a02d9b612df96e950186' to query transaction status
    ```
    
    >Instruction：`--params string:Hello,[string:tester]`specify parameter passed in invocation contract. Here passed two parameters, which are`string:Hello` and `[string:tester]`, these parameters are the paremeters passed to Main function of contract code for execution.

### 7. Query events that invoke transaction
Use command `./ontology info status 2cc94de8c26fce3be233bef007ec3492043ffc304b79a02d9b612df96e950186` according to tips to check transaction status:

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

In return results, States is the msg information of invoked contract notification, the return value is a hexadecimal string, use compiler to transform, the result is exactly `tester`, which is the second parameter we passed in step four.
