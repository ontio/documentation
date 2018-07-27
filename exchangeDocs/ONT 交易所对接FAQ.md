# ONT 交易所对接FAQ

## Q：ontology 节点如何连接 polaris 测试网

A : 启动时增加参数：```--networkid 2``` 。具体请参照```./ontology --help```



## Q:转账手续费是什么

A: ontology网络每次转账需要消耗ONG(gas)，在主网需要500+的gasprice的指定才会打包

```gasprice * gaslimit = ong  cost```

gaslimit的最低值是20000，gasprice的最低值是500，一般的交易情况都为最低值，也就是0.01个ONG。如果合约过于复杂，gaslimit的值可能会超过20000的最低值，gasprice为用户自己设定，但不能低于最低。



## Q:ONT解绑ONG问题

A:初始化时，所有的ONG会被发送到ONT合约地址中，随着时间的推移逐步的解绑ONG。解绑的ONG的地址确定且唯一。



## Q:关于ONT和ONG精度问题

A:ONT精度为1，不可分割。ONG精度为9，可分割。交易手续费使用ONG支付



## Q:交易如果产生交易费用，交易费用也会对应一笔转账，怎么识别这笔转账呢？这笔转账的目标地址是固定地址吗？

A:交易总手续费在消息推送中由gasConsumed标识，在消息中为最后一个消息。且转到治理合约地址中：AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK，该地址唯一。

## Q:特殊合约地址说明

A:

| Name     | Address(Hex)                             | Address(Base58)                    |
| -------- | ---------------------------------------- | ---------------------------------- |
| ONT      | 0100000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV |
| ONG      | 0200000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbvhfRZMHJ |
| 治理合约 | 0700000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK |


## Q: ONT有区块链浏览器么
A：[https://explorer.ont.io/](https://explorer.ont.io/)

## Q: 什么是白名单启动方式
A: 为了避免同步到一些被污染或恶意节点的区块，可以使用白名单启动方式直接同步官方的种子节点，启动方式：
```./ontology --reservedfile=./peers.rsv --reservedonly```
白名单文件peer.rsv另附

## Q: 关于NEP-5 ont和主网ONT兑换
请于2018.10.1之前

1. 首先将NEP-5的ONT 转到销毁地址:AFmseVrdL9f9oyCzZefL9tG6UbvhPbdYzM

2. 将下列信息以邮件形式发送到xiaomin@ont.io;wengjunjie@ont.io;zhoupeiwen@ont.io

   交易所名称：

   兑换代币总量：

   转账交易hash：

3. 我们将在一个工作日内将主网ONT和对应解绑的ONG发送到原转入地址，并邮件确认。

## Q: 关于换币产生的ONG
1. 换币时发放的ong数量：是从ontology 主网上线 到nep-5币打入销毁地址的时间内解绑的ong，不包括我们人工处理时间（最长24小时）产生的ong。
2. 给用户分配ong：ong转账同ont一样，会最少消耗0.01ong的手续费。
3. 当账户发生交易时，会按比例解绑ong，可以通过接口进行提取，同样每次提取操作也会消耗0.01ong的手续费，所以不建议频繁提取

## Q:ong的解绑规则是什么
可提取的ong数量 = 每秒解绑ong的数量 × ont的持有时间 × 持有ont的数量 / ont的总量

每秒解绑ong的数量：按照 [5, 4, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] 逐年递减

ont的持有时间：当前时间 - 上次ont变动时间

ont总量：10亿

例如：账户A 第一天持有100个ont，第二天持有200个ont，第三天持有300个ont，可提取的ong数量为：

（24×60×60)×5×100/1000000000 + （24×60×60)×5×200/1000000000 

之后300个ont可提取的ong在下次账户变动时结算。

初次做token swap时，上次ont变动时间为2018.6.30  ontology主网上线时间。


