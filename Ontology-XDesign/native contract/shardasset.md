# Shard Asset

## 功能

提供可以在root和shard之间流通的资产的底层实现，用户部署的所有可以跨分片流通的资产必须基于该合约进行扩展，否则不允许跨分片流通。

## 设计【暂时只支持OEP-4】

1. 使用assetId管理跨分片资产，每种在ShardAsset合约里注册的跨分片资产都会被分配给一个assetId。assetId与资产合约的地址绑定，合约升级时，会使用新的地址与旧的id绑定，这样跨分片资产不会受到资产合约升级的影响。

2. 使用notify的方式进行跨分片通信。

3. 跨分片资产转移只能从root到分片，从分片到root，不能从分片到分片；

4. root上记录各个分片上各个资产的总量；

5. 跨分片资产转移的过程如下：

    用户调用xshardtransfer后，合约会将用户转移的资产在该分片上销毁，然后分配一个transferId，记录下该transfer的状态；接着通知目标分片，目标分片收到通知后，在自己的分片上增发给用户相应的数量，同时记录下该transfer已经收到；最后目标分片通知回原始分片该transfer已经成功了，原始分片收到之后记录该transfer已经完成。
    
    当中间出现失败情况时，用户可以通过使用transferId重试调用transfer的方式重试发送，这个重试过程并不会造成资产的二次增发和销毁，因为原始分片和目标分片都记录了transferId的状态，重试过程实际上只是notify之类的通信重试。
    
    ![img](../img/shardasset-xshardtransfer.png)

6. 跨分片转移ONG的过程与其他资产相类似，但有如下区别：
    1. 初始化不在shardasset合约里注册，而是在每一个分片启动时，调用ong合约新增的一个方法shardInit初始化，这个方法会将所有的ONG转入到shardasset合约里，这意味着shardasset在分片一开始就拥有着所有的ONG；
    
    2. 跨分片转移时，ONG并不销毁，而是从用户地址转入到shardasset合约，目标分片接收时，也不是增发，而是从shardasset转出到用户地址；

## 实现

shard asset 合约有如下方法：

```
    INIT = "ope4ShardAssetInit" // shard asset init

    REGISTER = "oep4Register" // asset register
    MIGRATE  = "oep4Migrate" // asset contract migrate

    NAME           = "oep4Name"
    SYMBOL         = "oep4Symbol"
    DECIMALS       = "oep4Decimals"
    TOTAL_SUPPLY   = "oep4TotalSupply" // query total supply at shard
    SHARD_SUPPLY   = "oep4ShardSupply" // query shard supply at root
    WHOLE_SUPPLY   = "oep4WholeSupply" // sum supply at all shard, only can be invoked at root
    BALANCE_OF     = "oep4BalanceOf"
    TRANSFER       = "oep4Transfer"
    TRANSFER_MULTI = "oep4TransferMulti"
    APPROVE        = "oep4Approve"
    TRANSFER_FROM  = "oep4TransferFrom"
    ALLOWANCE      = "oep4Allowance"
    ASSET_ID       = "oep4AssetId" // query asset id

    XSHARD_TRANSFER       = "oep4XShardTransfer" // xshard transfer asset
    XSHARD_TRANFSER_RETRY = "oep4XShardTransferRetry" // retry xshard trasnfer
    
    ONG_XSHARD_TRANSFER       = "ongXShardTransfer" // xshard transfer ong
    ONG_XSHARD_TRANSFER_RETRY = "ongXShardTransferRetry" // retry xhsard transfer success

    // call by shardsysmsg contract
    XSHARD_TRANSFER_SUCC = "oep4XShardTransferSuccess" // xshard transfer success
    SHARD_RECEIVE_ASSET  = "oep4ShardReceive" // shard receive asset at xshard transfer
    ONG_XSHARD_RECEIVE   = "ongXShardReceive" // shard receive ong at xshard transfer
```
