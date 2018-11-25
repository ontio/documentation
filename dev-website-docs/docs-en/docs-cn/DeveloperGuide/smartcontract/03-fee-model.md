<h1 align="center">Ontology 智能合约费用模型</h1>

## 1、费用模型

### GAS Limit
Gas limit是在执行智能合约的opcode过程中计步时使用，理论上智能合约越复杂，需要的gas limit的数量越高，ontology交易设定最低的Gas limit数量是20000

### GAS Price
Gas price是给执行opcode定价，gas price的价格越高，共识节点会优先打包该笔交易。

### Transaction Fee

交易费是gas limit 和 gas price乘积，实际的交易费分以下三种情形

- 执行opcode步数等于gas limit

 transaction fee =  gas price * gas limit

-  执行opcode步数大于gas limit

transaction fee =  gas price * gas limit 

交易失败，但gas不会退还

- 执行opcode步数小于gas limit
transaction fee =  gas price * (opcode实际消耗)

多余的gas 会退还，但最低消费是20000



**所有ONT,ONG的转账GAS LIMIT消费固定都是20000**




## 2、怎样设置Gas Fee

###  CLI

以ONT转账为例，使用Ontology CLI手动设置gas price 和 gas limit 参数，

\--gasprice  


\--gaslimit   


- 查询余额：

```
./ontology asset balance TA7FwLmuX6qMcWTgZtUxt6tjzFgfaBM5sz
```

![image](https://ws4.sinaimg.cn/large/006tKfTcgy1fs3ot3e084j30tc03q0tn.jpg)

- 转账：
```
./ontology asset transfer --from TA7FwLmuX6qMcWTgZtUxt6tjzFgfaBM5sz  --to TA7FwLmuX6qMcWTgZtUxt6tjzFgfaBM5sz  --amount 1000 --gasprice 5 --gaslimit 40000
```

![image](https://ws4.sinaimg.cn/large/006tKfTcgy1fs3ot31uq6j30sc03qaav.jpg)


可以看到，转账1000个ONT，gas price  = 5，gas limit = 40000，

最终消耗的gas =  1787019.99985 - 1787019.9997 = 0.00015

### SDK

目前使用Java SDK和Golang SDK都可以设置GAS LIMIT 和GAS PRICE

以JAVA SDK 转账为例

```
String sendTransfer(Account sendAcct, String recvAddr, long amount, Account payerAcct, long gaslimit, long gasprice)(Account sendAcct, String recvAddr, long amount, Account payerAcct, long gaslimit, long gasprice)
```

可以在**sendTransfer**函数参数调用指定gas价格

[JAVA SDK](https://github.com/ontio/ontology-java-sdk/tree/master/docs/cn)

[Golang SDK](https://github.com/ontio/ontology-go-sdk)