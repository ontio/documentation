
<h1 align="center">Ontology Smart Contract Fee Model</h1>

## 1. GAS Limit
The gas limit is used to perform step counting in the opcode process when executing a smart contract. In theory, the more complex the smart contract, the higher the amount of gas limit required, and the lowest number of Gas limit on the Ontology transaction is 30000.


## 2. GAS Price

The gas price is to price the opcode. The higher the gas price, the more priority the consensus node will package the transaction.

## 3. Transaction Fee

The transaction fee is the product of gas limit and gas price. The actual transaction fee is divided into the following three situations:

### 1. The number of steps executing opcode equals to gas limit


**. transaction fee =  gas price * gas limit**

### 2. The number of steps executing opcode greater than gas limit

**transaction fee =  gas price * gas limit**

The transaction failed but gas will not be refunded

### 3. The number of steps executing opcode less than gas limit
**transaction fee =  gas price * (opcode实际消耗)**

Excess gas will be refunded

**GAS LIMIT fixed consumption is 20000 for all ONT, ONG transfer.**

## 2. How to set up Gas Fee

## CLI

Take ONT transfer as an example, use Ontology CLI to manually set the gas price and gas limit parameters.

\--gasprice


\--gaslimit

- Check balance：

```
./ontology asset balance TA7FwLmuX6qMcWTgZtUxt6tjzFgfaBM5sz
```

![image](https://ws4.sinaimg.cn/large/006tKfTcgy1fs3ot3e084j30tc03q0tn.jpg)

- Transfer：
```
./ontology asset transfer --from TA7FwLmuX6qMcWTgZtUxt6tjzFgfaBM5sz  --to TA7FwLmuX6qMcWTgZtUxt6tjzFgfaBM5sz  --amount 1000 --gasprice 5 --gaslimit 40000
```

![image](https://ws4.sinaimg.cn/large/006tKfTcgy1fs3ot31uq6j30sc03qaav.jpg)

You can see that the transfer amount = 1000 ONT, gas price = 5, gas limit = 40000

The final consumption of gas = 1787019.99985 - 1787019.9997 = 0.00015.


### SDK

GAS LIMIT and GAS PRICE can be set using the Java SDK and Golang SDK


Take a transfer process as an example (JAVA SDK):

```
String sendTransfer(Account sendAcct, String recvAddr, long amount, Account payerAcct, long gaslimit, long gasprice)(Account sendAcct, String recvAddr, long amount, Account payerAcct, long gaslimit, long gasprice)
```

You can set gas price when calling **sendTransfer**.

[JAVA SDK](https://github.com/ontio/ontology-java-sdk/tree/master/docs/cn)

[Golang SDK](https://github.com/ontio/ontology-go-sdk)








