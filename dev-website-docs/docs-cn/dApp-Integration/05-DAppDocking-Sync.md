
## 概述

本文档介绍了如何同步链上数据到应用本地的数据库。

当dApp需要查询链上数据（比如交易记录等），可以通过公开的[浏览器接口](https://dev-docs.ont.io/#/docs-cn/explorer/overview) 进行查询，这种方式适用于一些查询频率，查询量不大的dApp，对一些高频次查询需求的dApp，通过浏览器接口查询的方式就无法满足其业务需求，所以我们推出了同步链上数据到应用本地数据库的方法。

具体步骤如下：
- 连接到本体节点
- 运行同步程序

![Data-Sync](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/Sync.png)

请注意，同步链上数据到本地数据库对于dApp开发者是一个非必选项，请开发者在衡量自身应用具体需求后做出判断。

## 连接本体节点

### 连接公用节点
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

### 运行自己的节点

开发者也可以自己运行节点并进行同步，方法如下

[本体节点部署](http://dev-docs.ont.io/#/docs-cn/ontology-cli/09-deploy-node?id=%E9%83%A8%E7%BD%B2%E5%90%8C%E6%AD%A5%E8%8A%82%E7%82%B9)

## 运行同步程序

### 只同步具体合约相关的Event

部分dApp只需要关系自己的合约中产生的Event即可，不需要同步所有区块的信息。

具体的同步程序应该根据应用的具体业务需求编写，在这里我们为开发者提供了一个只同步自身合约信息的示例:
- [某游戏同步区块](https://github.com/lucas7788/ontologyplayer/blob/master/src/main/java/com/github/ontio/thread/BlockSyncThread.java)

### 同步所有区块信息

部分dApp需要同步所有的区块信息，比较典型的就是本体的浏览器，有类似需求的开发者可以参考本体浏览器的区块同步程序。

- [本体浏览器后台区块链信息同步](https://github.com/ontio/ontology-explorer/tree/master/back-end-projects/OntSynHandler)

### 只同步具体合约相关的Event

部分dApp只需要关注和本身智能合约相关的Event，那就不需要同步所有区块信息，下面给出了一个范例作为参考：

```java
    public void run() {
        logger.info("========{}.run=======", CLASS_NAME);

        try{
            //初始化node列表
            initNodeRpcList();
            int oneBlockTryTime = 1;
            while (true) {

                int remoteBlockHieght = getRemoteBlockHeight();
                logger.info("######remote blockheight:{}", remoteBlockHieght);

                int dbBlockHeight = blkHeightMapper.selectDBHeight();
                logger.info("######db blockheight:{}", dbBlockHeight);
                dbBlockHeight = dbBlockHeight +1;
                //wait for generating block
                if (dbBlockHeight >= remoteBlockHieght) {
                    logger.info("+++++++++wait for block+++++++++");
                    try {
                        Thread.sleep(configParam.BLOCK_INTERVAL);
                    } catch (InterruptedException e) {
                        logger.error("error...", e);
                        e.printStackTrace();
                    }
                    oneBlockTryTime++;
                    if (oneBlockTryTime >= configParam.NODE_WAITFORBLOCKTIME_MAX) {
                        switchNode();
                        oneBlockTryTime = 1;
                    }
                    continue;
                }

                oneBlockTryTime = 1;
                Object event = ConstantParam.ONT_SDKSERVICE.getConnect().getSmartCodeEvent(dbBlockHeight);
                if (event != null) {
                    List eventList = new ArrayList();
                    for(Object obj : (JSONArray)event){
                        if ((Integer) ((JSONObject)obj).get("State") == 1  && ((JSONObject)obj).get("Notify") != null){
                            JSONArray notifyArray = (JSONArray) ((JSONObject)obj).get("Notify");
                            for(Object notify : notifyArray){
                                String contractAddr = ((JSONObject)notify).getString("ContractAddress");
                                if(ConstantParam.CODEHASH_LIST.contains(contractAddr)) {
                                    if(((JSONArray)((JSONObject)notify).get("States")).size() !=0){
                                        logger.info("event: "+ event);
                                        eventList.add(obj);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    if(eventList.size() != 0) {
                        Object block = ConstantParam.ONT_SDKSERVICE.getConnect().getBlock(dbBlockHeight);
                        blkSyncService.handleEventList(eventList, ((Block) block).timestamp);
                    }
                }

                blkHeightMapper.update(dbBlockHeight);

            }
        }catch (Exception e) {
            logger.error("Exception occured，Synchronization thread can't work,error ...", e);
        }

    }
```
