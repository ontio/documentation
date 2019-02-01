
<div align="center">
<img src="https://avatars1.githubusercontent.com/u/43718245?s=400&amp;u=84eeb52003e5c32628fcc9cb23edd54d8596cf54&amp;v=4" height="200" width="200">
</div>

---

## 概述

[Punica Box](https://github.com/punica-box/)是dApp模板或案例，可以通过Punica-Cli下载和发布Box。目前已经提供的Box请查看网页[punica box](https://github.com/punica-box/)



特点：
* 提供了多种语言版本的dApp例子。如Ontid，OEP-4，OEP-5,OEP-8等。
* 将提供更多的开发者辅助库。
* 开发者可以发布Punica-Box
* 由社区贡献，方便与Punica-Cli一起使用。


## 开始使用

如果你还没下载Punica Cli，请先下载，才能进行Punica Box的相关操作。

### 创建工程文件夹:

```shell
mkdir tutorialtoken
cd tutorialtoken
```
### 通过```unbox```命令下载对应的box:

```shell
punica unbox tutorialtoken
```

> 注意: 也可以通过 ```punica init``` 命令创建空的项目.


### 如果下载成功，文件夹结构类似这样:

- `contracts/`: 智能合约文件夹.
- `src/`: aApp源码文件夹.
- `test/`: 测试文件夹，可以是智能合约或dApp的测试代码.
- `wallet/`: 钱包文件夹.

