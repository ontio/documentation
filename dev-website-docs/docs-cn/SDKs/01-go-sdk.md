
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
}
```

### 节点版本

`GetVersion` 接口用于查询所连接节点的版本号。

```go
version, err := sdk.GetVersion()
if err != nil {
    fmt.Println(err)
}
```

### Merkle 证明

```go
txHash := "65d3b2d3237743f21795e344563190ccbe50e9930520b8525142b075433fdd74"
merkleProof, err := sdk.GetMerkleProof(txHash)
if err != nil {
    fmt.Println(err)
}
```

### 区块高度

- `GetBlockHeightByTxHash` 接口用于查询指定交易哈希所对处区块的区块高度。

```go
txHash := "1ebde66ec3f309dad20a63f8929a779162a067c36ce7b00ffbe8f4cfc8050d79"
height, err := sdk.GetBlockHeightByTxHash(txHash)
if err != nil {
    fmt.Println(err)
}
```

- `GetCurrentBlockHeight` 接口用于查询当前区块高度。

```go
height, err := sdk.GetCurrentBlockHeight()
if err != nil {
    fmt.Println(err)
}
```

### 区块哈希

- `GetBlockHash` 接口用于查询指定块高度所对应区块的哈希值。

```go
hash, err = sdk.GetBlockHash(0)
if err != nil {
    fmt.Println(err)
}
```

- `GetCurrentBlockHash` 接口用于查询当前区块的哈希值。

```go
hash, err := sdk.GetCurrentBlockHash()
if err != nil {
    fmt.Println(err)
}
```

### 区块信息

- `GetBlockByHeight` 接口用于查询指定块高度所对应区块的信息。

```go
block, err := sdk.GetBlockByHeight(0)
if err != nil {
    fmt.Println(err)
}
```

- `GetBlockByHash` 接口用于查询指定块哈希所对应区块的信息。

```go
block, err := sdk.GetBlockByHash(0)
if err != nil {
    fmt.Println(err)
}
```

### 智能合约

- `GetSmartContract` 接口用于根据合约地址查询合约信息。

```go
ctrAddr := "1ddbb682743e9d9e2b71ff419e97a9358c5c4ee9"
contract, err := sdk.GetSmartContract(ctrAddr)
if err != nil {
    fmt.Println(err)
}
```

- `GetSmartContractEvent` 接口用于查询指定交易哈希所对应的合约事件。

```go
txHash := "65d3b2d3237743f21795e344563190ccbe50e9930520b8525142b075433fdd74"
event, err := sdk.GetSmartContractEvent(txHash)
if err != nil {
    fmt.Println(err)
}
```

- `GetSmartContractEventByBlock` 接口用于查询指定块高所对应区块中的所有合约事件。

```go
eventLst, _ := sdk.GetSmartContractEventByBlock(0)
```

### 交易

- 执行交易

`SendTransaction` 接口用于将交易发送到所接入的本体区块链网络。

```go
wd, _ := os.Getwd()
walletFile := filepath.FromSlash(path.Join(wd, "wallet.dat"))
wallet, _ := sdk.OpenWallet(walletFile)
b58FromAddr := "Af1n2cZHhMZumNqKgw9sfCNoTWu9de4NDn"
b58ToAddr := "ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD"
fromAcct, _ := wallet.GetAccountByAddress(b58FromAddr, password)
fromAddr := fromAcct.Address
toAddr, _ := utils.AddressFromBase58(b58ToAddr)
tx, _ := sdk.Native.Ont.NewTransferTransaction(500, 20000, fromAddr, toAddr, 1)
_ = sdk.SignToTransaction(tx, fromAcct)
txHash, err := sdk.SendTransaction(tx)
if err != nil {
    fmt.Println(err)
}
```

- 预执行交易

`SendTransaction` 接口用于预执行交易，获取交易执行结果。

```go
wd, _ := os.Getwd()
walletFile := filepath.FromSlash(path.Join(wd, "wallet.dat"))
wallet, _ := sdk.OpenWallet(walletFile)
b58FromAddr := "Af1n2cZHhMZumNqKgw9sfCNoTWu9de4NDn"
b58ToAddr := "ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD"
fromAcct, _ := wallet.GetAccountByAddress(b58FromAddr, password)
fromAddr := fromAcct.Address
toAddr, _ := utils.AddressFromBase58(b58ToAddr)
tx, _ := sdk.Native.Ont.NewTransferTransaction(500, 20000, fromAddr, toAddr, 1)
_ = sdk.SignToTransaction(tx, fromAcct)
result, err := sdk.PreExecTransaction(tx)
if err != nil {
    fmt.Println(err)
}
```

### 交易池

- `GetMemPoolTxState` 接口用于查询指定交易在交易池中的状态。

```go
txHash := "65d3b2d3237743f21795e344563190ccbe50e9930520b8525142b075433fdd74"
state, _ := sdk.GetMemPoolTxState(txHash)
```

- `GetMemPoolTxCount` 接口用于查询交易池中的交易数。

```go
count, _ := sdk.GetMemPoolTxCount()
```

## 钱包

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
}
```

### 获取账户

- 根据 Base58 编码地址获取账户

```go
b58Addr := "ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD"
acct, err := wallet.GetAccountByAddress(b58Addr, password)
if err != nil {
    fmt.Println(err)
}
```

- 根据索引获取

```go
b58Addr := "ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD"
acct, err := wallet.GetAccountByIndex(1, password)
if err != nil {
    fmt.Println(err)
}
```

- 根据标签获取账户

```go
b58Addr := "ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD"
acct, err := wallet.GetAccountByLabel("acct1", password)
if err != nil {
    fmt.Println(err)
}
```

### 创建账户

- 创建默认账户

```go
acct, err := wallet.NewDefaultSettingAccount(password)
if err != nil {
    fmt.Println(err)
}
```

- 根据 `WIF` 创建账户

```go
acct, err := wallet.NewDefaultSettingAccount(password)
if err != nil {
    fmt.Println(err)
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
