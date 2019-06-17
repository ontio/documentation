
## 概述

本文档介绍了如何同步链上数据到应用本地的数据库。

当 ```DAPP``` 需要查询链上数据（比如交易记录等），可以通过公开的 [浏览器 API](https://dev-docs.ont.io/#/docs-cn/explorer/overview) 进行查询，这种方式适用于一些查询频率，查询量不大的 ```DAPP```，对一些高频次查询需求的 ```DAPP```，通过浏览器接口查询的方式就无法满足其业务需求，所以我们推出了同步链上数据到应用本地数据库的方法。

> 请注意，同步链上数据到本地数据库对于dApp开发者是一个非必选项，请开发者在衡量自身应用具体需求后做出判断。

## 连接本体节点

### 连接公用节点
通常情况下，开发者自己运行节点是极为不便的。因此，本体提供了 `polaris` 测试网节点以及主网节点供开发者使用，它们均支持 ```RPC```、 ```Restful``` 以及 ```WebSocket``` 调用，并使用默认的端口号。

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

> polaris 测试网第一个节点和主网第一个节点的10334端口支持 HTTPS。

如果你希望基于 `polaris` 测试网进行开发，你可以在 [这里](https://developer.ont.io/applyOng) 申请测试所需的 `ONT` 与 `ONG`。

### 运行自己的节点

开发者也可以自己运行节点并进行同步，方法如下

[本体节点部署](http://dev-docs.ont.io/#/docs-cn/ontology-cli/09-deploy-node?id=%E9%83%A8%E7%BD%B2%E5%90%8C%E6%AD%A5%E8%8A%82%E7%82%B9)

## 运行同步程序

### 只同步具体合约相关的 Event

部分 ```DAPP``` 只需要关系自己的合约中产生的 ```Event``` 即可，不需要同步所有区块的信息。

具体的同步程序应该根据应用的具体业务需求编写，在这里我们为开发者提供了一个只同步自身合约信息的示例:
- [某游戏同步区块](https://github.com/lucas7788/ontologyplayer/blob/master/src/main/java/com/github/ontio/thread/BlockSyncThread.java)

### 同步所有区块信息

部分 ```DAPP``` 需要同步所有的区块信息，比较典型的就是本体的浏览器，有类似需求的开发者可以参考本体浏览器的区块同步程序。

- [本体浏览器后台区块链信息同步](https://github.com/ontio/ontology-explorer/tree/master/back-end-projects/OntSynHandler)

### 只同步具体合约相关的 Event

开发者在合约中自定义 ```Notify``` 的内容.
示例:
```python
Notify(["params1", "params2", "params3"])
```

链 getSmartCodeEvent 接口得到的返回值是 ExecuteNotify

数组 ExecuteNotify 的数据结构是

```go
type ExecuteNotify struct {
	TxHash      common.Uint256   //交易hash
	State       byte             //1表示交易执行成功，0表示失败
	GasConsumed uint64
	Notify      []*NotifyEventInfo
}
```
NotifyEventInfo 的数据结构是

```go
type NotifyEventInfo struct {
	ContractAddress common.Address  //合约地址
	States          interface{}     //notify内容
}
```

示例
```json
{
  "ContractAddress":"a671e2cd7a7d5e7111d211aaa628c469e59fa301",
  "States":["params1", "params2", "params3"]
}
```

监听特定合约事件示例代码如下
```java
public void run() {

    try{

        while (true) {
            //查询链上当前区块高度
            int remoteBlockHieght = getRemoteBlockHeight();
            logger.info("######remote blockheight:{}", remoteBlockHieght);
            //查询数据库中已经同步的区块高度
            int dbBlockHeight = blkHeightMapper.selectDBHeight();
            logger.info("######db blockheight:{}", dbBlockHeight);
            dbBlockHeight = dbBlockHeight +1;
            //如果数据库中的区块高度大于或等于链上最新的区块高度，就等待出下一个块再同步
            if (dbBlockHeight >= remoteBlockHieght) {
                //TODO
            }
            //根据区块高度查询该高度对应的区块中所有的事件,event是一个JSONArray对象, 每个元素的数据类型是ExecuteNotify
            Object event = sdk.getConnect().getSmartCodeEvent(dbBlockHeight);
            if (event != null) {
              for(Object obj : (JSONArray)event){
                  //过滤交易成功的事件
                  if (obj.get("State") ==1) {
                    for(Object notify: obj.get("Notify")) {
                        //过滤我们监听的事件
                        if(notify.getString("ContractAddress") == contractAddress) {
                             //TODO
                        }
                    }
                  }
              }
            }
            //更新数据库中的区块高度
            blkHeightMapper.update(dbBlockHeight);

        }
    }catch (Exception e) {
        logger.error("Exception occured，Synchronization thread can't work,error ...", e);
    }

}
```
