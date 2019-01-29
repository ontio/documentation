
本体客户端 `Ontology-CLI` 提供了区块导入模块，能够将存有区块数据的压缩文件导入到本地节点，可以在命令行中通过 `import` 命令使用。

- `--datadir` 用于指定区块数据存储目录
- `--config` 用于指定当前节点创世区块配置文件的路径（默认使用主网的创世块配置）
- `--disableeventlog` 用于关闭导入区块时生成合约日志功能
- `--networkid` 用于指定需要导入的网路ID（默认为主网的网络编号）
- `--endheight` 用于指定导入区块数据的目标区块高度（默认导入所有的区块）
- `--importfile` 用于指定导入文件的路径（默认为 `./OntBlocks.dat`）

> **注意**：出于安全考虑，请确保导入的区块数据文件的来源是可信的。

```shell
./ontology import --importfile=./OntBlocks.dat
```

你也可以通过 `--help` 选项获取帮助信息。

```shell
ontology import --help
```
