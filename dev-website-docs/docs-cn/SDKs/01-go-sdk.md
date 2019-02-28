
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
_ = sdk.NewWebSocketClient().Connect("ws://polaris1.ont.io:20335")
```

### 网络编号

`GetNetworkId` 接口用于查询网络编号。

```go
netId, _ := sdk.GetNetworkId()
```

### 节点版本

`GetVersion` 接口用于查询所连接节点的版本号。

```go
version, _ := sdk.GetVersion()
```

### Merkle 证明

```go
txHash := "65d3b2d3237743f21795e344563190ccbe50e9930520b8525142b075433fdd74"
merkleProof, _ := sdk.GetMerkleProof(txHash)
```

### 区块高度

- `GetBlockHeightByTxHash` 接口用于查询指定交易哈希所对处区块的区块高度。

```go
txHash := "1ebde66ec3f309dad20a63f8929a779162a067c36ce7b00ffbe8f4cfc8050d79"
height, _ := sdk.GetBlockHeightByTxHash(txHash)
```

- `GetCurrentBlockHeight` 接口用于查询当前区块高度。

```go
height, _ := sdk.GetCurrentBlockHeight()
```

### 区块哈希

- `GetBlockHash` 接口用于查询指定块高度所对应区块的哈希值。

```go
hash, _ = sdk.GetBlockHash(0)
```

- `GetCurrentBlockHash` 接口用于查询当前区块的哈希值。

```go
hash, _ := sdk.GetCurrentBlockHash()
```

### 区块信息

- `GetBlockByHeight` 接口用于查询指定块高度所对应区块的信息。

```go
block, _ := sdk.GetBlockByHeight(0)
```

- `GetBlockByHash` 接口用于查询指定块哈希所对应区块的信息。

```go
block, _ := sdk.GetBlockByHash(0)
```

### 智能合约

- `GetSmartContract` 接口用于根据合约地址查询合约信息。

```go
ctrAddr := "1ddbb682743e9d9e2b71ff419e97a9358c5c4ee9"
contract, _ := sdk.GetSmartContract(ctrAddr)
```

- `GetSmartContractEvent` 接口用于查询指定交易哈希所对应的合约事件。

```go
txHash := "65d3b2d3237743f21795e344563190ccbe50e9930520b8525142b075433fdd74"
event, _ := sdk.GetSmartContractEvent(txHash)
```

- `GetSmartContractEventByBlock` 接口用于查询指定块高所对应区块中的所有合约事件。

```go
eventLst, _ := sdk.GetSmartContractEventByBlock(0)
```

### 交易



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
    "os"
    "path"
    "path/filepath"
)

wd, _ := os.Getwd()
walletFile := filepath.FromSlash(path.Join(wd, "wallet.dat"))
wallet, _ := sdk.OpenWallet(walletFile)
```

### 获取账户

- 根据 Base58 编码地址获取账户

```go
b58Addr := "ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD"
acct, _ := wallet.GetAccountByAddress(b58Addr, password)
```

- 根据索引获取

```go
b58Addr := "ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD"
acct, _ := wallet.GetAccountByIndex(1, password)
```

- 根据标签获取账户

```go
b58Addr := "ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD"
acct, _ := wallet.GetAccountByLabel("acct1", password)
```
