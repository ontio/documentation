
## 快速开始

```go
package demo

import (
    ontology "github.com/ontio/ontology-go-sdk"
)

sdk := ontology.NewOntologySdk()
```

## 网络

`ontology-go-sdk` 提供了 `RPC`、`Restful` 以及 `WebSocket` 接口。

- `RPC` 接口

```go
sdk.NewRestClient().SetAddress("http://polaris1.ont.io:20334")
```

- `Restful` 接口

```go
sdk.NewRpcClient().SetAddress("http://polaris1.ont.io:20336")
```

- `WebSocket` 接口

```go
err := sdk.NewWebSocketClient().Connect("ws://polaris1.ont.io:20335")
if err != nil {
    fmt.Println(err)
}
```

### 网络编号

`GetNetworkId` 接口用于查询网络编号。

```go
netId, err := sdk.GetNetworkId()
if err != nil {
    fmt.Println(err)
} else {
    fmt.Println(netId)
}
```

### 节点版本

`GetVersion` 接口用于查询所连接节点的版本号。

```go
version, err := sdk.GetVersion()
if err != nil {
    fmt.Println(err)
} else {
    fmt.Println(version)
}
```

### Merkle 证明

`GetMerkleProof` 接口用于获取指定交易哈希所对应交易的 Merkle 证明。

```go
txHash := "65d3b2d3237743f21795e344563190ccbe50e9930520b8525142b075433fdd74"
merkleProof, err := sdk.GetMerkleProof(txHash)
if err != nil {
    fmt.Println(err)
} else {
    jsonMerkleProof, _ := json.Marshal(merkleProof)
    fmt.Println(string(jsonMerkleProof))
}
```

<div align="center"><img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/SDKs/merkle-tree.png" width="620px"></div>

<p class = "info">由于 <code>Merkle</code> 树的结构特征，通过使用默克尔证明技术，能够快速判断特定数据是否存在于默克尔树之中。</p>

### 区块高度

- `GetBlockHeightByTxHash` 接口用于查询指定交易哈希所对处区块的区块高度。

```go
txHash := "1ebde66ec3f309dad20a63f8929a779162a067c36ce7b00ffbe8f4cfc8050d79"
height, err := sdk.GetBlockHeightByTxHash(txHash)
if err != nil {
    fmt.Println(err)
} else {
    fmt.Println(height)
}
```

- `GetCurrentBlockHeight` 接口用于查询当前区块高度。

```go
height, err := sdk.GetCurrentBlockHeight()
if err != nil {
    fmt.Println(err)
} else {
    fmt.Println(height)
}
```

### 区块哈希

- `GetBlockHash` 接口用于查询指定块高度所对应区块的哈希值。

```go
hash, err = sdk.GetBlockHash(0)
if err != nil {
    fmt.Println(err)
} else {
    fmt.Println(hash)
}
```

- `GetCurrentBlockHash` 接口用于查询当前区块的哈希值。

```go
hash, err := sdk.GetCurrentBlockHash()
if err != nil {
    fmt.Println(err)
} else {
    fmt.Println(hash)
}
```

### 区块信息

- `GetBlockByHeight` 接口用于查询指定块高度所对应区块的信息。

```go
block, err := sdk.GetBlockByHeight(0)
if err != nil {
    fmt.Println(err)
} else {
    blockMarshal, _ := json.Marshal(block)
    fmt.Println(string(blockMarshal))
}
```

- `GetBlockByHash` 接口用于查询指定块哈希所对应区块的信息。

```go
block, err := sdk.GetBlockByHash(0)
if err != nil {
    fmt.Println(err)
} else {
    blockMarshal, _ := json.Marshal(block)
    fmt.Println(string(blockMarshal))
}
```

### 智能合约

- `GetSmartContract` 接口用于根据合约地址查询合约信息。

```go
ctrAddr := "1ddbb682743e9d9e2b71ff419e97a9358c5c4ee9"
contract, err := sdk.GetSmartContract(ctrAddr)
if err != nil {
    fmt.Println(err)
} else {
    jsonContract, _ := json.Marshal(contract)
    fmt.Println(string(jsonContract))
}
```

- `GetSmartContractEvent` 接口用于查询指定交易哈希所对应的合约事件。

```go
txHash := "65d3b2d3237743f21795e344563190ccbe50e9930520b8525142b075433fdd74"
event, err := sdk.GetSmartContractEvent(txHash)
if err != nil {
    fmt.Println(err)
} else {
    jsonEvent, _ := json.Marshal(event)
    fmt.Println(string(jsonEvent))
}
```

- `GetSmartContractEventByBlock` 接口用于查询指定块高所对应区块中的所有合约事件。

```go
eventLst, err := sdk.GetSmartContractEventByBlock(0)
if err != nil {
    fmt.Println(err)
} else {
    jsonEventLst, _ := json.Marshal(eventLst)
    fmt.Println(string(jsonEventLst))
}
```

### 交易

- 执行交易

`SendTransaction` 接口用于将交易发送到所接入的本体区块链网络。

```go
wallet, err := sdk.OpenWallet(walletFile)
if err != nil {
    fmt.Println(err)
}
fromAcct, _ := wallet.GetAccountByAddress("Af1n2cZHhMZumNqKgw9sfCNoTWu9de4NDn", password)
fromAddr := fromAcct.Address
toAddr, _ := utils.AddressFromBase58("ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD")
tx, _ := sdk.Native.Ont.NewTransferTransaction(500, 20000, fromAddr, toAddr, 1)
_ = sdk.SignToTransaction(tx, fromAcct)
txHash, err := sdk.SendTransaction(tx)
if err != nil {
    fmt.Println(err)
} else {
    fmt.Println(txHash)
}
```

- 预执行交易

`SendTransaction` 接口用于预执行交易，获取交易执行结果。

```go
wallet, err := sdk.OpenWallet(walletFile)
if err != nil {
    fmt.Println(err)
}
fromAcct, _ := wallet.GetAccountByAddress("Af1n2cZHhMZumNqKgw9sfCNoTWu9de4NDn", password)
fromAddr := fromAcct.Address
toAddr, _ := utils.AddressFromBase58("ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD")
tx, _ := sdk.Native.Ont.NewTransferTransaction(500, 20000, fromAddr, toAddr, 1)
_ = sdk.SignToTransaction(tx, fromAcct)
result, err := sdk.PreExecTransaction(tx)
if err != nil {
    fmt.Println(err)
} else {
    fmt.Println(result)
}
```

### 交易池

- `GetMemPoolTxState` 接口用于查询指定交易在交易池中的状态。

```go
txHash := "65d3b2d3237743f21795e344563190ccbe50e9930520b8525142b075433fdd74"
state, err := sdk.GetMemPoolTxState(txHash)
if err != nil {
    fmt.Println(err)
} else {
    fmt.Println(state)
}
```

- `GetMemPoolTxCount` 接口用于查询交易池中的交易数。

```go
count, err := sdk.GetMemPoolTxCount()
if err != nil {
    fmt.Println(err)
} else {
    fmt.Println(count)
}
```

## 钱包

<p class = "info">GO SDK中的OpenWallet方法只能打开已经存在的钱包，如果该文件路径下没有.dat文件，将会报错</p>

```go
import (
    "fmt"
    "os"
    "path"
    "path/filepath"
)

wd, err := os.Getwd()
walletFile := filepath.FromSlash(path.Join(wd, "wallet.dat"))
wallet, err := sdk.OpenWallet(walletFile)
if err != nil {
    fmt.Println(err)
} else {
    fmt.Println(wallet.GetAccountCount())
}
```

### 获取账户

- 根据 Base58 编码地址获取账户

```go
b58Addr := "ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD"
acct, err := wallet.GetAccountByAddress(b58Addr, password)
if err != nil {
    fmt.Println(err)
} else {
    fmt.Println(acct.Address.ToBase58())
}
```

- 根据索引获取

```go
b58Addr := "ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD"
acct, err := wallet.GetAccountByIndex(1, password)
if err != nil {
    fmt.Println(err)
} else {
    fmt.Println(acct.Address.ToBase58())
}
```

- 根据标签获取账户

```go
b58Addr := "ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD"
acct, err := wallet.GetAccountByLabel("acct1", password)
if err != nil {
    fmt.Println(err)
} else {
    fmt.Println(acct.Address.ToBase58())
}
```

### 创建账户

- 创建随机账户

```go
acct, err := wallet.NewDefaultSettingAccount(password)
if err != nil {
    fmt.Println(err)
} else {
    fmt.Println(acct.Address.ToBase58())
}
```

- 根据 `WIF` 创建账户

```go
wif := []byte("L1eCFtiZH2ZU6KjTR9MR14wfTEHnGGGoxSuRB2TUXRqoGwa7NAjN")
acct, err := wallet.NewAccountFromWIF(wif, password)
if err != nil {
    fmt.Println(err)
} else {
    fmt.Println(acct.Address.ToBase58())
}
```

!> <code>WIF（Wallet Import Format）</code> 是将明文私钥以 <code>Base58</code> 校验和编码格式显示的钱包导入格式。<code>WIF</code> 和私钥可以互转，因此也理解为是另一种形式的明文私钥。任何具有 <code>WIF</code> 的人，就能控制该 <code>WIF</code> 所对应的钱包账户。

### 删除账户

```go
b58Addr := "AHPVRC5biRZfHRcYFLHfRPfgmbFdCzYQWq"
err = wallet.DeleteAccount(b58Addr)
if err != nil {
    fmt.Println(err)
}
```
