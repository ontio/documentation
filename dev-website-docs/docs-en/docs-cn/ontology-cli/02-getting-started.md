
当你安装好本体的客户端后，便可以使用以下命令进行一些常用操作。

**查看客户端版本**

```shell
ontology -v
```

**查看帮助信息**

```shell
ontology help
```

**连接到主网**

```shell
ontology
```

或者

```shell
ontology --networkid 1
```

**连接到测试网**

```shell
ontology --networkid 2
```

**启动测试模式**

```shell
ontology --networkid 3
```

或者

```shell
ontology --testmode
```

> **注意**： 
>
> - 第一次启动测试模式之前，需要创建钱包文件。
>
>   ```shell
>   .\ontology account add -d
>   ```
>
> - 在测试模式下，节点独立运行，默认的 `gasprice` 为 0。