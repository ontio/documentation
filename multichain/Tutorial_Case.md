<h1 align="center">跨链使用教程 </h1>



## 测试网环境

本体多链测试网包含一条主链和侧链，两条链之间可以完成跨链业务

|               | 主链         | 侧链         |
| ------------- | ------------ | ------------ |
| **ip**        | 138.91.6.125 | 138.91.6.193 |
| **rest port** | 20334        | 20334        |
| **ws port**   | 20335        | 20335        |
| **rpc port**  | 20336        | 20336        |
| **chain ID**  | 0            | 1            |





## 资产转移

### 通过工具转移，前往下载 [multichain-transfer ](https://github.com/siovanus/multichain-transfer)

其中`config.json`文件如下：

```json
{
  "ChainID": 0,
  "JsonRpcAddress":"http://138.91.6.125:20336",
  "GasPrice":500,
  "GasLimit":20000
}
```

- `ChainID`是链的 ID
- `JsonRpcAddress`是此条链的 ip 地址和 rpc 端口

可以通过在命令行执行`./main -h`查看帮助

![帮助](https://i.loli.net/2019/05/09/5cd3b61d366ea.png)

- --fee 表示矿工费
- --chain-id 表示目标链的链ID
- --amount 表示要转移ong的数量（精度为9）
- --wallet 后面需要指定`wallet.dat`文件的路径，默认为当前路径

<br/>
<br/>

先确定我们处于主链还是侧链，即`config.json`中的指定

![1557370123328](https://i.loli.net/2019/05/09/5cd3b7580a1e5.png)

<br/>
<br/>

运行命令行，执行：```./main --fee 10000000000 --chain-id 1 --amount 150000000000```

![1557369575080](https://i.loli.net/2019/05/09/5cd3b8ab32f52.png)

<br/>
<br/>

`config.json`当中指定了我们当前处于主链，执行跨链交易时，指定了`--chain-id 1` ,`--fee 10000000000`,`--amount 150000000000`，即向id为1的侧链转账150个 `ong`，并扣除当前所处链的费用 10

<br/>

我们可以在 `Cyano` 钱包上，查看余额是否到账，在此之前，我们在 `Cyano` 先导入`wallet.dat`文件，并确保处于我们所想查看的网络上

例如，我们想查看刚刚的侧链 id 为1，资产是否到账，我们可以通过更改`Net`和`Private node ip/address`。由于侧链id为1的 ip 为`138.91.6.193`，因此我们在Cyano中更改即可

![1557370547287](https://i.loli.net/2019/05/09/5cd3b7a625342.png)

<br/>
<br/>
更改之后，我们可以查看到，刚刚所转账的已经到账

![1557369792351](https://i.loli.net/2019/05/09/5cd3b7b97e770.png)
<br/>
<br/>

若想主链向其他侧链，或侧链向主链转账，同理
<br/>
<br/>
<br/>

### 跨链合约使用，前往下载[OEP4合约模板](https://github.com/siovanus/multiChainContract/tree/master/OEP4-template)

我们可以使用 [samrtx](https://smartx.ont.io) 部署和运行智能合约



#### 部署智能合约

部署智能合约A到主链 id 0上，我们先确保Cyano处于主链网络上，即更改`Net`和`Private node ip/address`

owner 为智能合约的管理人，我们更改为自己的地址即可

![1557371595430](https://i.loli.net/2019/05/09/5cd3b7d726f23.png)
<br/>
<br/>

部署完成之后，调用 init 方法，初始化10亿 token 给 owner 地址

![1557371725480](https://i.loli.net/2019/05/09/5cd3b7e710158.png)
<br/>

此外我们还需要执行 setdestination 函数来设置对方子链OEP4跨链合约的地址
![](https://i.loli.net/2019/05/15/5cdb84eae51e337089.png)
<br/>

另外 `destination_contract`是合约 hash 的反序，可以在 smartx 上试用工具栏下的`Hex String (Big-endian/Little-endian)`方法返回反序后的值
![1557372908086](https://i.loli.net/2019/05/09/5cd3b7f80449d.png)
<br/>

<br/>
<br/>

部署智能合约B到侧链id 1上，同上原理，更换 Cyano为侧链 ip，在smartx上部署，部署完成后也需要执行 init，初始化10亿token给该智能合约B的地址
<br/>
<br/>
<br/>

#### 运行合约

**1. 调用合约的lock函数进行跨链转账**
<br/>
在此之前，主链往侧链转账需注意, Cyano需处于主链网络上，lock函数中，指定`to chain_id`为侧链id
<br/>
在一切准备就绪后，接下来，我们执行 lock 函数

![1557373167083](https://i.loli.net/2019/05/09/5cd3b80af311b.png)
<br/>

点击运行之后，会调用 Cyano进行签名。执行成功后，可以在 smartx 左侧的 Logs中查看到结果和交易 hash
<br/>
<br/>

**2. 验证侧链是否到账**
<br/>
在此之前，我们需要在Cyano上添加OEP4 Token的地址，此地址即为B合约部署在侧链的合约地址

![1557373896613](https://i.loli.net/2019/05/09/5cd3b81d3cb5e.png)

![1557373988646](https://i.loli.net/2019/05/09/5cd3b8300e019.png)

<br/>

<br/>



之后，需要切换Cyano网络到侧链上，例，我们刚刚像侧链id为1的转账，Cyano中切换为138.91.6.193的侧链网络

![1557373499176](https://i.loli.net/2019/05/09/5cd3b83e93f3e.png)

<br/>

可以查看到已经到账的 OEP4 token

![1557374056829](https://i.loli.net/2019/05/09/5cd3b84f9b0c4.png)
<br/>



侧链向主链转账，原理同上
