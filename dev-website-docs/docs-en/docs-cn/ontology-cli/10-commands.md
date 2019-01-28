
本体客户端  `Ontology CLI` 支持的命令行参数如下表所示，你可以在需要的时候使用 `help` 命令在终端中查看。

```shell
ontology help
```

|     命令     |               描述               |
| :----------: | :------------------------------: |
|   account    |             账户管理             |
|     info     |           获取链上信息           |
|    asset     |             资产管理             |
|   contract   |        部署与调用智能合约        |
|    import    |       从文件中导入区块数据       |
|    export    |       将区块数据导出到文件       |
|   buildtx    |             构造交易             |
|    sigtx     |             签署交易             |
| multisigaddr |           生成多签地址           |
|  multisigtx  |           签署多签交易           |
|    sendtx    |        发送序列化后的交易        |
|    showtx    | 以 JSON 格式显示序列化交易的信息 |
|   help, h    |           显示帮助信息           |

具体命令的使用介绍，你可以参考如下章节：

- [`account` 命令的使用介绍](docs-cn/ontology-cli/13-wallet-manager.md)