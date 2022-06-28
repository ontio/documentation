# Marketplace - smart contract api

# 交易合约

## 1. 概述

**术语**：

- `RP `

  资源提供者

- `RC`

  资源需求者

- `RA`

  资源认证方

- `OJ`

  链下仲裁者

- `MP`

  market place
  
  


## 2. 相关合约

- MaketPlace交易合约

  该本合约是Market place主合约，涉及到交易从挂单到成交所有阶段

- market place手续费规则合约

  目前以交易额的5%收取，保留升级接口

- OJ仲裁费规则合约

  目前以交易额的5%收取，保留升级接口

- RP挂单抵押金额规则合约

  目前以交易金额的20%收取保证金，保留升级接口



## 3. 接口

#### 3.1 AuthOrder

参数：

- `dataId`
  
- `index`

- `symbol`

- `name`

- `authAmount`

    授权marketplace生成token的数量，例如authAmount=10，即最多生成10个data token

- `price`

  单个token的价格，以ONG标价

- `transferCount`

- `accessCount`

- `expireTime`

- `makerTokenHash`
	 	Maker 抵押的data token合约hash

- `makerReceiveAddress`

  RP收款钱包地址
  
- `mpReceiveAddress`

    MP收款钱包地址
   
- `OJList`

  仲裁者地址（wallet address）列表，至少有一个OJ

调用成功后，合约会生成唯一的Auth ID

### 3.2 cancelAuth

本接口供`RC`调用，RC取消生成dataToken的授权

调用成功后，authId失效，RP无法通过authId购买商品

参数：

- `authId`

  


### 3.3 takeOrder

参数：

- `authId`

  `3.1`接口生成的auth id

- `takerReceiveAddress`

  RC的钱包地址
  
- `tokenAmount`

  RP购买token的数量，RP购买成功后，对应authId的authAmount会扣减相应数量

- `OJ`

  由`RC`选择的唯一的OJ

### 3.4 applyArbitrage

`RC`申请仲裁，RC需要抵押仲裁费到合约

参数：

- `orderId`

- `arbitrageFee`

  仲裁费数量，该数量应该和**3.1**RP挂单的仲裁费相同，否则交易失败



### 3.5 arbitrage

`OJ`对指定一笔交易发起线下仲裁，得出结论后，调用本接口最终裁定。

调用本接口代表订单结束，订单分润一并完成

参数：

- `orderId`

- `winOrLoss`

   挑战是否成功

- `makerReceiveAmount`

   RC仲裁后收到的ONG数量

- `takerReceiveAmount`

  RP仲裁后收到的ONG数量
  
   

**注意：makerReceiveAmount + takerReceiveAmount = 总交易额(ONG)  + RC已抵押的抵押费**

### 3.6 confirm

本接口可以在订单`expire time`之后由任意人调用，若在此之前，只有`RC`可以调用

订单一经确认，不可更改，订单分润一并完成。

- `orderId`



