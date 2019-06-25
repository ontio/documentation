


## 1. ontology 节点如何连接 polaris 测试网

A : 启动时增加参数：```--networkid 2``` 。具体请参照```./ontology --help```

## 2. 转账手续费是什么

A: ontology 网络每次转账需要消耗 ONG( gas )，在主网需要 500+ 的 gasprice 的指定才会打包

```gasprice * gaslimit = ong  cost```

gaslimit 的最低值是 20000，gasprice 的最低值是 500，一般的交易情况都为最低值，也就是 0.01个ONG。如果合约过于复杂，gaslimit 的值可能会超过 20000 的最低值，gasprice 为用户自己设定，但不能低于最低。



## 3. ONT 解绑 ONG 问题

A:初始化时，所有的 ONG 会被发送到 ONT 合约地址中，随着时间的推移逐步的解绑 ONG 。解绑的 ONG 的地址确定且唯一。



## 4. 关于 ONT 和 ONG 精度问题  

A: ONT 为实际数量，不可分割。 ONG 精度为9，可分割。交易手续费使用  ONG 支付



## 5. 交易如果产生交易费用，交易费用也会对应一笔转账，怎么识别这笔转账呢？这笔转账的目标地址是固定地址吗？

A:交易总手续费在消息推送中由 gasConsumed 标识，在消息中为最后一个消息。且转到治理合约地址中：AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK，该地址唯一。

## 6. 特殊合约地址说明

A:

| Name     | Address(Hex)                             | Address(Base58)                    |
| -------- | ---------------------------------------- | ---------------------------------- |
| ONT      | 0100000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV |
| ONG      | 0200000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbvhfRZMHJ |
| 治理合约 | 0700000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK |


## 7. ONT 有区块链浏览器么
A：[https://explorer.ont.io/](https://explorer.ont.io/)

## 8. 什么是白名单启动方式
A: 为了避免同步到一些被污染或恶意节点的区块，可以使用白名单启动方式直接同步官方的种子节点，启动方式：
```./ontology --reservedfile=./peers.rsv --reservedonly```
白名单文件 peer.rsv 另附

## 9. 关于NEP-5 ont和主网 ONT 兑换
请于2018.10.1之前

1. 首先将 NEP-5 的 ONT 转到销毁地址: AFmseVrdL9f9oyCzZefL9tG6UbvhPbdYzM

2. 将下列信息以邮件形式发送到： xiaomin@ont.io;wengjunjie@ont.io;zhoupeiwen@ont.io

   交易所名称：

   兑换代币总量：

   转账交易 hash：

3. 我们将在一个工作日内将主网 ONT 和对应解绑的 ONG 发送到原转入地址，并邮件确认。

## 10. 关于换币产生的 ONG
1. 换币时发放的 ong 数量：是从 ontology 主网上线 到 nep-5 币打入销毁地址的时间内解绑的 ong ，不包括我们人工处理时间（最长24小时）产生的 ong 。
2. 给用户分配 ong：ong 转账同 ont 一样，会最少消耗 0.01ong 的手续费。
3. 当账户发生交易时，会按比例解绑 ong，可以通过接口进行提取，同样每次提取操作也会消耗 0.01ong 的手续费，所以不建议频繁提取

##11. ONG 的解绑规则是什么
可提取的 ong 数量 = 每秒解绑 ong 的数量 × ont 的持有时间 × 持有ont 的数量 / ont 的总量

每秒解绑 ong 的数量：按照 [5, 4, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] 逐年递减

ont 的持有时间：当前时间 - 上次 ont 变动时间

ont 总量：10亿

例如：账户 A 第一天持有100个 ont，第二天持有200个 ont，第三天持有300个 ont，可提取的ong数量为：

（24×60×60)×5×100/1000000000 + （24×60×60)×5×200/1000000000 

之后300个 ont 可提取的 ong 在下次账户变动时结算。

初次做 token swap 时，上次 ont 变动时间为2018.6.30  ontology主网上线时间。


