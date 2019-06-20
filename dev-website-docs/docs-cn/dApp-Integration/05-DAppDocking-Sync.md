

本章节会介绍如何将链上数据同步到应用本地的数据库。

当 ```DAPP``` 需要查询链上数据（比如交易记录等）时，可以通过公开的 [浏览器 API](https://dev-docs.ont.io/#/docs-cn/explorer/overview) 进行一些查询频率低、查询量少的 ```DAPP```查询，而对一些高频次查询需求的 ```DAPP```，通过浏览器接口查询的方式无法满足其业务需求，从而本体推出了同步链上数据到应用本地数据库的方法。

> 请注意，同步链上数据到本地数据库对于 DAPP 开发者不是一个必选项，请开发者在衡量自身应用具体需求后做出判断。

## 1. 连接本体节点

可以连接本体公共节点或启动同步节点。

### 1.1 连接公共节点
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

### 1.2 运行自己的节点

开发者也可以自己运行同步节点，请参考 [本体节点部署](http://dev-docs.ont.io/#/docs-cn/ontology-cli/09-deploy-node?id=%E9%83%A8%E7%BD%B2%E5%90%8C%E6%AD%A5%E8%8A%82%E7%82%B9)

## 2. 运行同步程序

同步是将节点上所有区块、交易、合约事件保存到数据库，供应用查询，[Explorer](https://explorer.ont.io) 就是典型的同步程序。项目方可以选择性同步自己关注的数据，比如自己部署的合约事件。


### 2.1 同步所有区块信息

部分 ```DAPP``` 需要同步所有的区块信息，比较典型的就是本体的浏览器，有类似需求的开发者可以参考 [本体浏览器的区块同步程序](https://github.com/ontio/ontology-explorer/tree/master/back-end-projects/OntSynHandler)。

- 根据快高获取块，通过链 [getblk_by_height](https://dev-docs.ont.io/#/docs-cn/ontology-cli/06-restful-specification?id=getblk_by_height) 接口得到的返回值示例：
```json
http://polaris1.ont.io:20334/api/v1/block/details/height/909220

{
	"Action": "getblockbyheight",
	"Desc": "SUCCESS",
	"Error": 0,
	"Result": {
		"Hash": "02f723a83eae05238481bc8b7d315cbbcd4326ccb53df6e1de35b19c496868ee",
		"Size": 1392,
		"Header": {
			"Version": 0,
			"PrevBlockHash": "b0243bd78e7368c8bed33a9e66b4a8c0a2f98fbcf18457a018f027b69ab1f7fc",
			"TransactionsRoot": "7f89aaf1ca48a8cff46493f1ca75f91fabe1ec14b8acd3ffd32acd722d398b4e",
			"BlockRoot": "e6440680fc91be58c5d41298c992cb6cd04c365a00bf6dce216ce085ce0e75cd",
			"Timestamp": 1551427384,
			"Height": 909220,
			"ConsensusData": 12174009838538082583,
			"ConsensusPayload": "7b226c6561646572223a312c227672665f76616c7565223a224249526839547a4f4e526e71766444566b565a6753624e6e533871336465344b4b59786a52686174713864394b6d3974316f7279654f426b727170502f4b6f4474674135647061492f313649536c4b643556784e4d444d3d222c227672665f70726f6f66223a222f6e7a554a54766f7959676d594a544570574938326958454b497a6c7247707870753067767239784a6231784c646c344442435831796d7372703941796f495256372f35626f2f4c572b2b36336937665553747378513d3d222c226c6173745f636f6e6669675f626c6f636b5f6e756d223a3930383432342c226e65775f636861696e5f636f6e666967223a6e756c6c7d",
			"NextBookkeeper": "AFmseVrdL9f9oyCzZefL9tG6UbvhPbdYzM",
			"Bookkeepers": ["037c9e6c6a446b6b296f89b722cbf686b81e0a122444ef05f0f87096777663284b", "03aa4d52b200fd91ca12deff46505c4608a0f66d28d9ae68a342c8a8c1266de0f9", "0205bc592aa9121428c4144fcd669ece1fa73fee440616c75624967f83fb881050", "030a34dcb075d144df1f65757b85acaf053395bb47b019970607d2d1cdd222525c", "020cc76feb375d6ea8ec9ff653bab18b6bbc815610cecc76e702b43d356f885835", "03dff4c63267ae5e23da44ace1bc47d0da1eb8d36fd71181dcccf0e872cb7b31fa"],
			"SigData": ["ded9f22792bfc4aa1e471fe05cfc68af2cd5204fd1664f3151648910f51cc531f8dc9c301ee450538e84ffa8a77b5c8141e37caab4917eb7b8c6eb11e8e1b387", "ac5b1710b50d1d35b7948d2e19a22e5f7eecbe210f09551275ca273d09ea15e1aa5198d052ef913cf51b3855955f0f89caf174ca4ffac4451d27b29dc64626e7", "121d213cf49f7c7a706e9098d2ed9ae53ead4fe41774fdccd7186fd47fffa13f60dea875794fe9bbcf5fd729a1294cc835b34ef42ae8544425b15bedca0d8e93", "8053c1fbf81f3d3c01925ad3160dec9c4751203da9a31c22448de4aa18c38d07f99e0cbb7066bb83de6e7d46720184e541bcad8e9fdd2ec18cd8cbd83f0c335c", "ffc94ae16e0ff54a922f970b3226b5e2267a1b783ff990799f536dd3f0713782c9e43d372fcd3b4596f922a222db4e3bf3fe2b84e62c3ef580ff02d46491a61a", "cf52208439275256dfe3f97af4fab5a1b6c69661d5b885f6623337a4dfc729cb6b425fe8e009fccb115e7b4626f4176806ffd323a96d4aa0866a0459cf02917a"],
			"Hash": "02f723a83eae05238481bc8b7d315cbbcd4326ccb53df6e1de35b19c496868ee"
		},
		"Transactions": [{
			"Version": 0,
			"Nonce": 1551427383,
			"GasPrice": 500,
			"GasLimit": 20000000,
			"Payer": "Af1n2cZHhMZumNqKgw9sfCNoTWu9de4NDn",
			"TxType": 209,
			"Payload": {
				"Code": "016414aa57ed4be4a318fb4b88b6a25d662f7e073743aa14feec06b79ed299ea06fcb94abac41aaf3ead765853c15a14feec06b79ed299ea06fcb94abac41aaf3ead76581446b1a18af6b7c9f8a4602f9f73eeb3030f0c29b753c152c151c10e7472616e736665725f6d756c746967bed9a5a68557381d0598cfcbfb16c03334a791ca"
			},
			"Attributes": [],
			"Sigs": [{
				"PubKeys": ["02e8e84be09b87985e7f9dfa74298f6bb7f70f85515afca7e041fe964334e4b6c1"],
				"M": 1,
				"SigData": ["dd0edcbb49e77bfec7fb5dbaaeafcb309dcd2b3db940dc27a33f5738872bd25684fcbd1da140d7ec483fa2eedb9e0c520619076e45e5f43383eeef55ca36d759"]
			}, {
				"PubKeys": ["03d0fdb54acba3f81db3a6e16fa02e7ea3678bd205eb4ed2f1cfa8ab5e5d45633e"],
				"M": 1,
				"SigData": ["df6c95816a56eab350800be3ccc3a9a7794b565a47b49f53b6351a19c5e1dd8d980d32a04a97f8e933a11683b7e1fcc50fd8f91695ab0189468a7c0a5a518156"]
			}],
			"Hash": "7f89aaf1ca48a8cff46493f1ca75f91fabe1ec14b8acd3ffd32acd722d398b4e",
			"Height": 0
		}]
	},
	"Version": "1.0.0"
}
```
### 2.2 只同步具体合约相关的 Event

大部分 ```DAPP``` 只需要同步自己的合约中产生的 ```Event``` 即可，不需要同步所有区块的信息。

具体的同步程序应该根据应用的具体业务需求编写，在这里我们为开发者提供了一个只同步自身合约信息的 [示例](https://github.com/lucas7788/wontologyserver/blob/master/src/main/java/com/github/ontio/asyncService/BlkSyncService.java)。

- 开发者在合约中自定义 ```Notify``` 的内容。示例:
```python
Notify(["params1", "params2", "params3"])
```

- 根据快高查合约事件，通过链 [getSmartCodeEvent](https://dev-docs.ont.io/#/docs-cn/ontology-cli/06-restful-specification?id=getsc_event_by_height) 接口得到的返回值示例：


```json

http://polaris1.ont.io:20334/api/v1/smartcode/event/transactions/909220
 
{
	"Action": "getsmartcodeeventbyheight",
	"Desc": "SUCCESS",
	"Error": 0,
	"Result": [{
		"TxHash": "7f89aaf1ca48a8cff46493f1ca75f91fabe1ec14b8acd3ffd32acd722d398b4e",
		"State": 1,
		"GasConsumed": 10000000,
		"Notify": [{
			"ContractAddress": "ca91a73433c016fbcbcf98051d385785a6a5d9be",
			"States": ["7472616e736665725f6d756c7469", [
				["46b1a18af6b7c9f8a4602f9f73eeb3030f0c29b7", "feec06b79ed299ea06fcb94abac41aaf3ead7658", "0a"],
				["feec06b79ed299ea06fcb94abac41aaf3ead7658", "aa57ed4be4a318fb4b88b6a25d662f7e073743aa", "64"]
			]]
		}, {
			"ContractAddress": "0200000000000000000000000000000000000000",
			"States": ["transfer", "Af1n2cZHhMZumNqKgw9sfCNoTWu9de4NDn", "AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK", 10000000]
		}]
	}],
	"Version": "1.0.0"
}
```

  - 数组 ExecuteNotify 的数据结构是

```go
type ExecuteNotify struct {
	TxHash      common.Uint256   //交易hash
	State       byte             //1表示交易执行成功，0表示失败
	GasConsumed uint64
	Notify      []*NotifyEventInfo
}
```

 - NotifyEventInfo 的数据结构是

```go
type NotifyEventInfo struct {
	ContractAddress common.Address  //合约地址
	States          interface{}     //notify内容
}
```

-  监听特定合约事件示例

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
