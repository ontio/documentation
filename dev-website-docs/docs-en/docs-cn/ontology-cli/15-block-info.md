## 查询信息

查询信息命令可以查询区块、交易以及交易执行等信息。使用./ontology info block --help 命令可以查看帮助信息。

### 查询区块信息

```
./ontology info block <height|blockHash>
```
可以通过区块高度或者区块Hash 查询区块信息。

### 查询交易信息

```
./ontology info tx <TxHash>
```
可以通过交易Hash查询交易信息。

### 查询交易执行信息

```
./ontology info status <TxHash>
```
可以通过交易Hash查询交易的执行信息，返回示例如下：

```
{
   "TxHash": "4c00674d96b1d3d2c8152b905cae6f87fff0ec8acf28ca3e7465aac59de814a1",
   "State": 1,
   "GasConsumed": 0,
   "Notify": [
      {
         "ContractAddress": "ff00000000000000000000000000000000000001",
         "States": [
            "transfer",
            "TA587BCw7HFwuUuzY1wg2HXCN7cHBPaXSe",
            "TA5gYXCSiUq9ejGCa54M3yoj9kfMv3ir4j",
            10
         ]
      }
   ]
}
```
其中，State表示交易执行结果，State的值为1，表示交易执行成功，State值为0时，表示执行失败。GasConsumed表示交易执行消耗的ONG。Notify表示交易执行时输出的Event log。不同的交易可能会输出不同的Event log。
