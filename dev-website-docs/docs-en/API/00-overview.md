
The RPC interface, Restful interface, and WebSocket interface of the ontology node follow a set of public interface specifications.

By default, the Restful interface listens on port 20334, the Websocket interface listens on port 20335, and the RPC interface listens on port 20336.

## Use public nodes

Often, it is extremely inconvenient for developers to run their own nodes. Therefore, the ontology provides the `polaris` test network node and the main network node for developers to use, all supporting RPC, Restful, and WebSockek calls, and using the default port number.

> 10334 port of the first node of the polaris test network and the first node of the miannet network support HTTPS.

- `polaris` test network node
  - http://polaris1.ont.io
  - http://polaris2.ont.io
  - http://polaris3.ont.io
  - http://polaris4.ont.io
  - http://polaris5.ont.io

- main network node
  - http://dappnode1.ont.io
  - http://dappnode2.ont.io
  - http://dappnode3.ont.io
  - http://dappnode4.ont.io

If you want to develop on a `polaris` test network, you can apply for the required `ONT` and `ONG` [here](https://developer.ont.io/applyOng).

## Deploy personal nodes

According to the needs of developers, we also provide a way to [Running Node](https://dev-docs.ont.io/#/docs-en/OntologyCli/02-running-node).
