

Ontology Cli支持导出本地节点的区块数据到一个压缩文件中，生成的压缩文件可以再导入其它Ontology节点中。出于安全考虑，导入的区块数据文件请确保是从可信的来源获取的。

--rpcport
rpcport 参数用于指定Ontology节点的rpc端口号，默认值为20336。

--exportfile
exportfile 参数指定导出的文件路径。默认值为：./OntBlocks.dat

--startheight
startheight 参数指定导出区块的起始高度。默认值为0。

--endheight
endheight 参数用于指定导出区块的终止高度。默认值为0，表示导出所有区块。

--speed
speed 参数指定导出速度。分别用h表示high，m表示middle，l表示low。默认值为m。

区块导出

```
./ontology export
```