

--datadir
datadir 参数用于指定区块数据存储目录

--config
config 参数用于指定当前Ontology节点创世区块配置文件的路径。如果不指定，将使用Ontolog主网的创世块配置。

--disableeventlog
disableeventlog 参数用于关闭导入区块时生成合约日志功能。

--networkid
networkid 参数用于指定需要导入的网路ID。默认值为主网networkid。

--endheight
endheight 参数指定导入的目标区块高度。如果importheight指定的区块高度小于区块文件的最大高度时，只导入到importheight指定的高度，剩余的区块会停止导入。默认值为0，表示导入所有的区块。

--importfile
importfile 参数用于指定导入文件的路径。默认值为"./OntBlocks.dat"。

导入区块

```
./ontology import --importfile=./OntBlocks.dat
```