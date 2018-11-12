<div align="center"><img src="https://raw.githubusercontent.com/punicasuite/solo-chain/master/image/icon.png" height="200" width="200"></div>

# Solo-chain

## 概览

Solo-chain是一键式区块链，是一个基于本体进行dApp开发的私有链。

Solo-chain基于本体区块链的[发布版本](https://github.com/ontio/ontology/releases)进行开发，在测试模式下运行。

## 安装

你可以从此存储库的[发布页面](https://github.com/punicasuite/solo-chain/releases)下载适用于所在平台的自包含预构建二进制文件。

## 快速开始

当启动Solo chain时，屏幕将显示测试模式下节点的一些详细信息，并列出多个帐户及其私钥。

共有六个页面：

- 帐户页面显示生成的帐户及其余额，并且可以转移ONT/ONG并取出ONG。
- 区块页面显示区块链中的块及其详细信息。
- 交易页面列出了区块链中发生的所有交易。
- 事件页面显示了智能合约事件。
- 智能合约页面显示了已部署的智能合约。
- 日志页面显示了测试节点的日志。

### 如何基于源码构建？

#### 构建步骤

``` bash
# install dependencies
npm install

# serve with hot reload at localhost:9080
npm run dev

# build electron application for production
npm run build
```

## 入门

<div align="center"><img src="https://raw.githubusercontent.com/punicasuite/solo-chain/master/image/solo_chain.png" ></div>

Solo-chain是一个预构建的本体私链，它包含了许多交互和监视工具。

你可以通过检查生成的区块和初始化一笔交易来，验证下载安装的[Solo-chain](https://github.com/punicasuite/solo-chain/)是否正在按照预期工作。

请记下控制面板中显示的IP地址以供日后使用。
