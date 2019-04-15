## Overview

This document describes how to synchronize data on a chain to an application-local database.

When the dApp needs to query the data on the chain (such as transaction records, etc.), it can be queried through the public [explorer api](https://dev-docs.ont.io/#/docs-en/explorer/overview). The method is applicable to some dApps with a small query frequency and a small amount of queries. For some high-frequency query dApps, the query through the browser interface cannot meet the business requirements, so we have introduced the data on the synchronization chain to the application. The method of the database.

Specific steps are as follows:
- Connect to the ontology node
- Run the sync program

![Data-Sync](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/Sync.png)

Please note that synchronizing the data on the chain to the local database is a non-essential option for the dApp developer, and the developer is required to make a judgment after measuring the specific needs of the application.

## Connecting the ontology node

### Connecting public nodes
Often, it is extremely inconvenient for developers to run their own nodes. Therefore, the ontology provides the `polaris` test network node and the main network node for developers to use, all supporting RPC, Restful, and WebSockek calls, and using the default port number.

- `polaris` test network node
  - http://polaris1.ont.io
  - http://polaris2.ont.io
  - http://polaris3.ont.io
  - http://polaris4.ont.io
  - http://polaris5.ont.io

- Primary network node
  - http://dappnode1.ont.io
  - http://dappnode2.ont.io
  - http://dappnode3.ont.io
  - http://dappnode4.ont.io

> The first node of the polaris test network and the 10334 port of the first node of the primary network support HTTPS.

If you want to develop based on the `polaris` test network, you can apply for the required `ONT` and `ONG` in [here](https://developer.ont.io/applyOng).

### Running your own node

Developers can also run nodes themselves and synchronize them as follows

[Ontology node deployment](https://dev-docs.ont.io/#/docs-en/OntologyCli/02-running-node)

## Running the synchronization program

### Only synchronize specific contract related events

Some DApps only need to correlate the events generated in their own contracts, and do not need to synchronize the information of all blocks.

The specific synchronization program should be written according to the specific business needs of the application. Here we provide an example for developers to synchronize their own contract information:
- [A game sync block](https://github.com/lucas7788/ontologyplayer/blob/master/src/main/java/com/github/ontio/thread/BlockSyncThread.java)

### Synchronize all block information

Some DApps need to synchronize all the block information. The typical one is the explorer of the ontology. Developers with similar requirements can refer to the block synchronization program of the ontology browser.

- [Ontology explorer background blockchain information synchronization](https://github.com/ontio/ontology-explorer/tree/master/back-end-projects/OntSynHandler)

### Only synchronize specific contract related events

The developer customizes the contents of Notify in the contract.
Example:
```
Notify(["params1", "params2", "params3"])
```

The return value of the chain getSmartCodeEvent interface is ExecuteNotify

The data structure of the array ExecuteNotify is
```
Type ExecuteNotify struct {
TxHash common.Uint256 //transaction hash
State byte //1 indicates successful transaction execution, 0 indicates failure
GasConsumed uint64
Notify []*NotifyEventInfo
}
```
The data structure of NotifyEventInfo is

```
Type NotifyEventInfo struct {
ContractAddress common.Address //Contract address
States interface{} //notify content
}
```

Example
```
{
  "ContractAddress": "a671e2cd7a7d5e7111d211aaa628c469e59fa301",
  "States": ["params1", "params2", "params3"]
}
```

The sample code for listening to a specific contract event is as follows
```java
Public void run() {

    Try{

        While (true) {
            / / Query the current block height on the chain
            Int remoteBlockHieght = getRemoteBlockHeight();
            Logger.info("######remote blockheight:{}", remoteBlockHieght);
            / / Query the height of the block in the database has been synchronized
            Int dbBlockHeight = blkHeightMapper.selectDBHeight();
            Logger.info("######db blockheight:{}", dbBlockHeight);
            dbBlockHeight = dbBlockHeight +1;
            / / If the block height in the database is greater than or equal to the latest block height on the chain, wait for the next block to resynchronize
            If (dbBlockHeight >= remoteBlockHieght) {
                //TODO
            }
            / / Query all events in the block corresponding to the height according to the block height, event is a JSONArray object, the data type of each element is ExecuteNotify
            Object event = sdk.getConnect().getSmartCodeEvent(dbBlockHeight);
            If (event != null) {
              For(Object obj : (JSONArray)event){
                  / / Filter the event of successful transaction
                  If (obj.get("State") ==1) {
                    For(Object notify: obj.get("Notify")) {
                        / / Filter the events we listened to
                        If(notify.getString("ContractAddress") == contractAddress) {
                             //TODO
                        }
                    }
                  }
              }
            }
            / / Update the block height in the database
            blkHeightMapper.update(dbBlockHeight);

        }
    }catch (Exception e) {
        Logger.error("Exception occured,Synchronization thread can't work,error ...", e);
    }

}
```