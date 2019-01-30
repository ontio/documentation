
本体客户端 `Ontology-CLI` 提供了区块导出模块，能够将本地节点的区块数据导出到一个压缩文件之中，可以在命令行中通过 `export` 命令使用。

- `--exportfile`：指定导出文件的路径（默认为 `./OntBlocks.dat`）
- `--startheight`：指定导出区块的起始高度（默认为 `0`）
- `--endheight`：指定导出区块的终止高度（默认值为 `0`，表示导出所有区块）
- `--speed`：指定导出速度，`h` 表示快速导出，`m` 表示正常导出，`l` 表示慢速导出（默认值为`m`）

```shell
$ ontology export
Start export.
Block(3653/3652) [====================================================================] 100%   10s
Export blocks successfully.
StartBlockHeight:0
EndBlockHeight:3652
Export file:./OntBlocks_0_3652.dat
```

你也可以通过 `--help` 选项获取帮助信息。

```shell
ontology export --help
```
