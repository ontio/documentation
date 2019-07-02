

## 1. 概述

IDEA Ontology 智能合约开发插件支持:

1. python 合约编译 (.py)
2. 合约部署 t (TestNet / MainNet / PrivateNet)
3. 合约调用 (Exec / PreExec)
4. 合约 Debug (Step through / Breakpoints / Variables Preview)

## 2. 插件安装

该插件可以在市场搜索或手动下载安装，`Debug` 功能是可选的，如果需要合约 `Debug` ，要额外安装 `Ontdev` 程序。

### 2.1 不安装 Debug 功能

该插件可以在市场搜索或手动下载安装，点击 **Project settings**:

<img width="450" src="https://raw.githubusercontent.com/punicasuite/pycharm-plugin-for-ontology/master/doc/imgs/settings.png" />


### 2.2 安装 Debug 功能

1. 先安装 `Node.js`, 可以通过 [Official Installation Package](https://nodejs.org/en/) 或 [Node Version Manager](https://github.com/creationix/nvm) 安装.

2. 通过命令行 `npm install -g ontdev` 安装 `Ontdev` 

3. 下载 [releases](https://github.com/punicasuite/pycharm-plugin-for-ontology/releases) 版本并安装 `jar` 文件.

   1. 在 **Settings/Preferences** 选择 **Plugins**
  
   2. 在 **Plugins** 对话框, 点击 <img width="16" src="https://www.jetbrains.com/help/img/idea/2018.3/icons.general.gearPlain.svg@2x.png" /> 然后点击 **Install Plugin from Disk..**
   
      <img width="450" src="https://raw.githubusercontent.com/punicasuite/pycharm-plugin-for-ontology/master/doc/imgs/install-1.png" />

## 3. 工具使用

提供的数据转换工具，支持以下类型转换:

* String <=> Hex string

* Address <=> Script hash

* Number <=> Hex string

* Byte array <=> Hex string

* 大小端转换

可以在 **Tools -> Ontology Tools** 里找到转换工具:

<img width="450" src="https://raw.githubusercontent.com/punicasuite/pycharm-plugin-for-ontology/master/doc/imgs/tools.png" />