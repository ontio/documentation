## 6. Block Import and Export

Ontology CLI supports exporting the local node's block data to a compressed file. The generated compressed file can be imported into the Ontology node. For security reasons, the imported block data file must be obtained from a trusted source.

* [Export Blocks](#export-blocks)
* [Import Blocks](#import-blocks)

### Export Blocks

```
./Ontology export
```

*Parameters:*

--rpcport
Specifies the port number to which the RPC server is bound. The default is 20336.

--exportfile
Specifies the exported file path. The default value is: ./OntBlocks.dat.

--startheight
Specifies the start height of the exported block. Default value is 0.

--endheight
Specifies the end height of the exported block. When height of the local node's current block is greater than the end height required for export, the greater part will not be exported. Height is equal to 0, which means exporting all the blocks of the current node. The default value is 0.

--speed
Specifies the export speed. Respectively, h denotes high, m denotes middle, and l denotes low. The default value is m.


### 6.2 Import Blocks

```
./ontology import --importfile=./OntBlocks.dat
```

*Parameters:*

--datadir
Specifies the storage path of the block data. The default value is "./Chain".

--networkid
Used to specify the network ID. Default value is 1, means MainNet network ID.

--config
Specifies the file path of the genesis block for the current Ontology node. Default value is main net config.

--disableeventlog
Disable the event log output when the smart contract is executed to improve the node transaction execution performance. The Ontology node enables the event log output function by default.

--endheight
Specifies the end height of the imported block. If the block height specified by --endheight is less than the maximum height of the block file, it will only be imported to the height specified by --endheight and the rest blocks will stop importing. The default value is 0, which means import all the blocks.

--importfile
The path to the import file when importing blocks. The default value is "./OntBlocks.dat".
