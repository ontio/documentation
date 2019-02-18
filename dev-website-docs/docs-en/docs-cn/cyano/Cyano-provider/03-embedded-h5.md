
本文用于指导dApp方如何与钱包通信，及钱包如何处理dApp的请求。
流程中涉及到的参与方包括：

* DApp方：对ONT生态内的用户提供Dapp，是本体生态中重要的组成部分。
* Provider：实现dApi mobile规范的钱包

## 交互流程说明

DApp请求数据URI scheme：```ontprovider://ont.io?param=Base64.encode(Uri.encode({the json data}.toString()))```

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-cyano/integration-docs/master/images/scenario3.png" ><br><br>
</div>

### 钱包打开H5 DApp

- 1 钱包打开H5 DApp

### H5 DApp向获取Provider信息

- 1 DApp请求Provider信息
- 2 钱包返回Provider信息

### H5 DApp向获取账户或身份信息

- 1 DApp请求账户或身份信息
- 2 用户接受请求，返回账户或身份信息


### 登录Login
- 1 DApp请求对message做签名（[DApp发起登录请求](#DApp发起登录请求)）
- 2 钱包用户对message做签名，返回签名数据（[钱包响应登录请求](#钱包响应登录请求)）

### 消息签名signMessage
- 1 DApp请求对message做签名
- 2 钱包用户对message做签名

### 调用合约Invoke Smart contract
- 1 DApp请求调用合约（[DApp发起调用合约请求](#DApp发起调用合约请求)）
- 2 钱包构造交易，用户签名
- 3 钱包预执行交易（[预执行交易](#预执行交易)）   
- 4 钱包发送交易
- 3 钱包返回交易Hash（[钱包响应调用合约请求](#钱包响应调用合约请求)）



## 钱包和DApp接入步骤

### 前提条件
使用前，你需要联系[本体机构合作](https://info.ont.io/cooperation/en)

```

