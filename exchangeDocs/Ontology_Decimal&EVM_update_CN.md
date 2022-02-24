# Ontology Decimal&EVM Upgrade Guide

## 1. 背景

为了更好的支持在Ontology 上的DApp应用，Ontology 已经支持EVM虚拟机，仍然使用ONG 做为手续费代币，同时，将ONT的精度扩大为9，ONG的精度扩大为18 。



## 2. 升级流程

### 2.1 Ontology 节点升级

Ontology 主网将于区块高度 **[13920000]** 进行升级，请在**务必**该高度前完成本地的同步节点的升级（并请确保在本体主网的共识节点已经完成升级之后）。

Ontology Release 链接：**[https://github.com/ontio/ontology/releases/tag/v2.3.5]**



### 2.2 处理升级后ONT / ONG的精度的入金事件（必须）

ONT / ONG 在发生转账交易后，系统产生对应的event log在升级后会发生变化，需要监控的程序作出修改：

#### 2.2.1 对于ONT

合约地址为："0100000000000000000000000000000000000000"

**NOTE**

“States”数组的长度可能为4 或 5

当转账的ONT数量为整数时，和旧版本的事件一致：

States[0]: "transfer" （固定）

States[1]: from address

States[2]: to address

States[3]: amount(整数，精度为0)

例如：转账1个ONT

```
{
    "ContractAddress": "0100000000000000000000000000000000000000",
        "States": [
        "transfer",
        "AdeTj6K9UUmz5yfyc8SLX7mJSmCqDKK6yT",
        "AdeTj6K9UUmz5yfyc8SLX7mJSmCqDKK6yT",
        1
    ]
},
```



当转账的ONT数量包含小数时：

States[0]: "transfer" （固定）

States[1]: from address

States[2]: to address

States[3]: amount(整数部分，精度为0)

States[4]: amount(小数部分，精度为9)

例如：转账1.052999999个ONT

```
{
    "ContractAddress": "0100000000000000000000000000000000000000",
        "States": [
        "transfer",
        "AdeTj6K9UUmz5yfyc8SLX7mJSmCqDKK6yT",
        "AdeTj6K9UUmz5yfyc8SLX7mJSmCqDKK6yT",
        1,
        52999999
    ]
}
```



#### 2.2.2 对于ONG

合约地址为：”0200000000000000000000000000000000000000“

同样类似与ONT，“States”数组的长度可能为4 或 5

当转账的ONG数量大于等于0.000000001时（10^-9)，和旧版本的事件一致：

States[0]: "transfer" （固定）

States[1]: from address

States[2]: to address

States[3]: amount(整数，精度为9)

例如：转账0.000000001ONG

```
{
    "ContractAddress": "0200000000000000000000000000000000000000",
    "States": [
        "transfer",
        "AdeTj6K9UUmz5yfyc8SLX7mJSmCqDKK6yT",
        "AdeTj6K9UUmz5yfyc8SLX7mJSmCqDKK6yT",
        1
    ]
}
```

当转账的ONG数量小于0.000000001或包含小于0.000000001的部分时（10^-9)

States[0]: "transfer" （固定）

States[1]: from address

States[2]: to address

States[3]: amount(大于0.000000001部分，精度为9)

States[4]: amount(小于0.000000001部分，精度为9)

例如：转账 0.00000000105 ONG

```
{
"ContractAddress": "0200000000000000000000000000000000000000",
    "States": [
        "transfer",
        "AdeTj6K9UUmz5yfyc8SLX7mJSmCqDKK6yT",
        "AdeTj6K9UUmz5yfyc8SLX7mJSmCqDKK6yT",
        1,
        50000000
    ]
}
```



### 2.3 调用tranferV2支持ONT/ONG的新精度出金（可选）

旧版本的ONT  的transfer方法只支持整数数量的转账，ONG的transfer方法只支持精度为9（最小0.000000001）数量的转账。

**如果出金的策略不变，则可以继续使用原来的逻辑和代码**。

如果需要支持ONT的9位精度和ONG的18位精度的出金，则需要作出下列修改：

#### 2.3.1 使用SDK

如果使用SDK，请更新到最新的版本：

Golang:https://github.com/ontio/ontology-go-sdk

参考：

https://github.com/ontio/ontology-go-sdk/blob/6117f13ebd6b6411b5ee765eeee71b0fb5fc97ec/ont_sdk_v2_test.go



Java:https://github.com/ontio/ontology-java-sdk

参考：

https://github.com/ontio/ontology-java-sdk/blob/c8e2da6d3a4b18dd6235b4ed81f47199856bbd59/src/test/java/com/github/ontio/smartcontract/nativevm/OntV2Test.java

https://github.com/ontio/ontology-java-sdk/blob/c8e2da6d3a4b18dd6235b4ed81f47199856bbd59/src/test/java/com/github/ontio/smartcontract/nativevm/OngV2Test.java



TypeScript:https://github.com/ontio/ontology-ts-sdk

参考：

https://github.com/ontio/ontology-ts-sdk/blob/master/test/integration/v2/transfer.test.ts



#### 2.3.2 使用签名机：

参考：https://github.com/ontio/documentation/blob/master/exchangeDocs/sigsvr_CN.md

1. 使用SDK构造V2交易并等到交易个raw hex。
2. 调用签名机的sigrawtx对交易签名，得到签名后的交易hex。
3. 调用节点的sendrawtx广播交易。

或：

1. 直接调用签名机的sigtransfertxV2构造交易并签名。
2. 调用节点的sendrawtx广播交易。