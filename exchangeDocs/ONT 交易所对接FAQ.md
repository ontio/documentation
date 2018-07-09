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





