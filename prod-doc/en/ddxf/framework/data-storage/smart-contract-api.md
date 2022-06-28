# DToken - smart contract api

# eshop类型的 Data Token设计接口

## 1. Overview

本文档是关于data  Token的设计文档，主要参考[OEP-8](https://github.com/ontio/OEPs/blob/master/OEPS/OEP-8.mediawiki)标准



## 2. Method


### 2.1 createToken

```python
def createToken(account:address， dataId:string, ontId:string, index:int, symbol:string, name:string, amount:int, transferCount:int, accessCount:int, expireTime:int)
```



- `account`

  生成data token的接收地址，此地址必然已绑定在传入的ONT ID下

- `dataId`

   已注册的dataId

- `ontid`

  控制人ONT ID

- `index`

  控制人ONT ID index

- `symbol`

- `name` 

- `amount`

  生成data token的数量，每个data token 有唯一的token id，数量递增
  
  例如，当前最大的token id是100，amount 是10，则10个token 的token id
  
  是101-110
  
- `transferCount`

   token可以流转的次数，初始大于0

   每transfer一次，次数减1

- `accessCount`

   token可以访问数据的次数，初始大于0

   每访问数据一次，可使用次数减1

- `expireTime`

   token的过期时间，如果为0，则意味不设置过期时间，如果大于0，则该该字段必须当前当前时间
   
   超过过期时间之后，token失效，无法流转
   
   

**tokenId:dataId:data = N:1:1**



### 2.2 consumeToken

```python
def consumeToken(tokenId:string)
```

- `tokenId`

调用成功后，token的访问次数减1

### 2.3 getTransferCount

```python
def getTransferCount(tokenId:string)
```

- `tokenId`

查询token可以转账的次数

### 2.4 getAccessCount

```python
def getAccessCount(tokenId:string)
```

- `tokenId`

查询token可以访问数据的次数

### 2.5 getExpireTime

```python
def getExpireTime(tokenId:string)
```

- `tokenId`

查询token的过期时间

### 2.6 name

```python
def name(tokenId:string)
```
- `tokenId`

  查询token名称

### 2.7 symbol
```python
def symbol(tokenid:string)
```
- `tokenId`

  查询token符号

### 2.8 totalSupply

```python
def totalSupply()
```

查询已发行的token总量

### 2.9 transfer

```python
def transfer(from:address, to:address, tokenId:string)
```

- `from`

- `to`

- `tokenId`

  

### 2.10 transferMulti
```python
def transferMulti(args:array)
```
- `args`

  args是**2.5 Transfer**接口的参数数组

  

### 2.11 approve
```python
def approve(owner:address, spender:address, tokenId:string)
```
- `owner`
- `spender`
- `tokenId`

  

本接口由`owner`调用，允许`spendner`消费指定`tokenId` 的token

### 2.12 transferFrom
```python
def transferFrom(from:address, to:address, tokenId:string)
```
- `from`

- `to`

- `tokenId`

  

调用人`from`账户的的token支付给接收人`to`账户，此接口的调用人必须被`from`账户`approve`相应的权限

### 2.12 approveMulti
```python
def approveMulti(args:array)
```
- `args`

  args是**2.7 approve**接口的参数数组

  

### 2.13 transferFromMulti
```python
def transferFromMulti(args:array)
```
- `args`

  args是**2.8 transferFrom**接口的参数数组




# data类型的  Data Token设计接口

## 1. Overview

本文档是关于data  Token的设计文档，主要参考[OEP-8](https://github.com/ontio/OEPs/blob/master/OEPS/OEP-8.mediawiki)标准



## 2. Method


### 2.1 mintToken

```python
def mintToken(account:address， dataId:string, ontId:string, symbol:string, name:string, amount:int, transferCount:int, accessCount:int, expireTime:int)
```

**本接口 只提供给MarketPlace合约调用，个人账户无法调用**

- `account`

  生成data token的接收地址，此地址必然已绑定在传入的ONT ID下

- `dataId`

   已注册的dataId

- `ontid`

  控制人ONT ID

- `symbol`

- `name` 

- `amount`

  生成data token的数量，每个data token 有唯一的token id，数量递增
  
  例如，当前最大的token id是100，amount 是10，则10个token 的token id
  
  是101-110
  
- `transferCount`

   token可以流转的次数，初始大于0

   每transfer一次，次数减1

- `accessCount`

   token可以访问数据的次数，初始大于0

   每访问数据一次，可使用次数减1

- `expireTime`

   token的过期时间，如果为0，则意味不设置过期时间，如果大于0，则该该字段必须当前当前时间
   
   超过过期时间之后，token失效，无法流转
   
   

**tokenId:dataId:data = N:1:1**



### 2.2 consumeToken

```python
def consumeToken(tokenId:string)
```

- `tokenId`

调用成功后，token的访问次数减1

### 2.3 getTransferCount

```python
def getTransferCount(tokenId:string)
```

- `tokenId`

查询token可以转账的次数

### 2.4 getAccessCount

```python
def getAccessCount(tokenId:string)
```

- `tokenId`

查询token可以访问数据的次数

### 2.5 getExpireTime

```python
def getExpireTime(tokenId:string)
```

- `tokenId`

查询token的过期时间

### 2.6 name

```python
def name(tokenId:string)
```
- `tokenId`

  查询token名称

### 2.7 symbol
```python
def symbol(tokenid:string)
```
- `tokenId`

  查询token符号

### 2.8 totalSupply

```python
def totalSupply()
```

查询已发行的token总量

### 2.9 transfer

```python
def transfer(from:address, to:address, tokenId:string)
```

- `from`

- `to`

- `tokenId`

  

### 2.10 transferMulti
```python
def transferMulti(args:array)
```
- `args`

  args是**2.5 Transfer**接口的参数数组

  

### 2.11 approve
```python
def approve(owner:address, spender:address, tokenId:string)
```
- `owner`
- `spender`
- `tokenId`

  

本接口由`owner`调用，允许`spendner`消费指定`tokenId` 的token

### 2.12 transferFrom
```python
def transferFrom(from:address, to:address, tokenId:string)
```
- `from`

- `to`

- `tokenId`

  

调用人`from`账户的的token支付给接收人`to`账户，此接口的调用人必须被`from`账户`approve`相应的权限

### 2.12 approveMulti
```python
def approveMulti(args:array)
```
- `args`

  args是**2.7 approve**接口的参数数组

  

### 2.13 transferFromMulti
```python
def transferFromMulti(args:array)
```
- `args`

  args是**2.8 transferFrom**接口的参数数组