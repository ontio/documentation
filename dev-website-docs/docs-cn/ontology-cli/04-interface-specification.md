
本体节点的 RPC 接口、Restful 接口、WebSocket 接口遵循着一套公开的接口规范。

默认情况下，Restful 接口监听在 20334 端口，Websocket 接口监听在 20335 端口，RPC 接口监听在 20336 端口。

## 使用公开节点

通常情况下，开发者自己运行节点是极为不便的。因此，本体提供了 `polaris` 测试网节点以及主网节点供开发者使用，它们均支持 RPC、 Restful 以及 WebSockek 调用，并使用默认的端口号。

- `polaris` 测试网节点
  - http://polaris1.ont.io
  - http://polaris2.ont.io
  - http://polaris3.ont.io
  - http://polaris4.ont.io
  - http://polaris5.ont.io

- 主网节点
  - http://dappnode1.ont.io
  - http://dappnode2.ont.io
  - http://dappnode3.ont.io
  - http://dappnode4.ont.io

如果你希望基于 `polaris` 测试网进行开发，你可以在[这里](https://developer.ont.io/applyOng)申请测试所需的 `ONT` 与 `ONG`。

## 部署个人节点

根据开发者需要，我们也提供了搭建节点的方法。

[节点部署](https://dev-docs.ont.io/#/docs-cn/ontology-cli/09-deploy-node)