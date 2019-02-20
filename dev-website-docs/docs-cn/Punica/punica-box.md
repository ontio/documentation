

## 概述

[Punica Box](https://github.com/punica-box/) 提供多种语言版本的dApp 模板或案例，如 Ontid、OEP-4、OEP-5、OEP-8 等。开发者可以通过Punica-Cli 下载和发布 Box。目前已经提供的 Box 可查看 [punica box](https://github.com/punica-box/)。未来将提供更多的开发者辅助库。


## 开始使用

开始 Punica Box 相关操作之前，请确认你已经下载 Punica Cli。

### 创建工程文件夹

使用以下命令：

```shell
mkdir tutorialtoken
cd tutorialtoken
```
### 下载 box

使用 `unbox` 命令下载对应的 box:

```shell
punica unbox tutorialtoken
```

<p class="info">也可以通过 ```punica init``` 命令创建空的项目.</p>

如果下载成功，文件夹结构类似这样:

- `contracts/`: 智能合约文件夹
- `src/`: aApp源码文件夹
- `test/`: 测试文件夹，可以是智能合约或dApp的测试代码
- `wallet/`: 钱包文件夹

