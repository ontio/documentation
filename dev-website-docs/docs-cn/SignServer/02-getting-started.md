# Getting Started

- [操作](#操作)
  - [配置](#配置)
  - [钱包数据目录](#钱包数据目录)
  - [IP地址权限控制](#IP地址权限控制)
  - [IP端口号](#IP端口号)
  - [ABI文件目录](#ABI文件目录)
  - [日志](#日志)
- [导入钱包数据](#导入钱包数据)

## 操作
如果仅使用默认参数的话，只需要执行下面的启动命令
```
./sigsvr
```
通过下面的链接访问:
```
http://localhost:20000/cli
```

## 配置
服务启动的时候会使用默认配置，但是你可以修改配置参数以适用于特定的项目。所有的配置参数都可以通过可选参数选项进行设置。如下：

```
./sigsvr --walletdir ./data/wallets --abi ./data/abi
```
可以使用下面详述的配置选项的任何组合。

### 钱包数据目录
服务会存储本地钱包的位置，默认的钱包文件位置是`$GOPATH/src/github.com/ontio/ontology/tools/wallet_data`. 如果你想改变钱包文件路径，可以使用`walletdir`参数设置。


例如:
```
./sigsvr --walletdir ./data/wallets
```

### IP地址访问控制

IP地址默认只供本地访问，通过`127.0.0.1`。如果你想提供外部访问，请使用`cliaddress`进行配置。

例如:
```
./sigsvr --cliaddress 0.0.0.0
```

### IP 端口号

服务的默认端口号是`20000`，如果你想更改端口号，请使用`cliport`参数配置。

例如:
```
./sigsvr --cliport 1337
```

### ABI 文件目录
服务会加载Ontology Native合约abi文件位置，abi文件位置默认是在`$GOPATH/src/github.com/ontio/ontology/tools/abi`，如果你想更改该路径，可以通过`abi`参数进行设置。

例如:
```
./sigsvr --abi ./data/abi
```

### 日志
提供不同级别的日志记录，默认的日志级别是Info (2). 可设置的日志级别如下.

0. Trace
1. Debug
2. Info (default)
3. Warn
4. Error
5. Fatal
6. Max Level

例如:
```
./sigsvr --loglevel 0
```

## 导入已经存在的钱包数据

你可能已经离线生成了钱包文件，想要导入到服务中。为了达到这个目的，你可以使用导入命令选项`wallet`来打入一个已经存在的钱包文件，该命令独立于服务配置选项，仅仅将钱包数据导入到服务，并没有真正的运行服务。

例如:
```
./sigsvr import --wallet ./wallet_2018-10-31-23-59-59.dat
```

这对于使用服务导出功能导出导入钱包非常有用。

