
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

#### 查询当前区块信息

- 当前区块高度

```go
package demo

import ontology "github.com/ontio/ontology-go-sdk"

height, _ := sdk.GetCurrentBlockHeight()
```

- 当前区块哈希

```go
package demo

import ontology "github.com/ontio/ontology-go-sdk"

hash, _ := sdk.GetCurrentBlockHash()
```

#### 查询区块信息

- 指定块高

```go
package demo

import ontology "github.com/ontio/ontology-go-sdk"

block, _ := sdk.GetBlockByHeight(0)
```

- 指定块哈希

```go
package demo

import ontology "github.com/ontio/ontology-go-sdk"

block, _ := sdk.GetBlockByHash(0)
```

#### 查询区块哈希

`GetBlockHash` 接口用于查询指定高度的区块哈希值。

```go
package demo

import ontology "github.com/ontio/ontology-go-sdk"

hash, _ = sdk.GetBlockHash(0)
```
