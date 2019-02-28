
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

### RPC 接口

```go
sdk.NewRestClient().SetAddress("http://polaris1.ont.io:20334")
```

#### 查询当前块高

```go
height, _ := sdk.GetCurrentBlockHeight()
```

#### 查询当前块哈希

```go
hash, _ := sdk.GetCurrentBlockHash()
```

#### 查询指定高度的区块

```go
block, _ := sdk.GetBlockByHeight(0)
```

### Restful 接口

```go
sdk.NewRpcClient().SetAddress("http://polaris1.ont.io:20336")
```

#### 查询当前块高

```go
height, _ := sdk.GetCurrentBlockHeight()
```

#### 查询当前块哈希

```go
hash, _ := sdk.GetCurrentBlockHash()
```

#### 查询指定高度的区块

```go
block, _ := sdk.GetBlockByHeight(0)
```

### WebSocket 接口

```go
_ = sdk.NewWebSocketClient().Connect("ws://polaris1.ont.io:20335")
```

