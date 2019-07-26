
## Cocos Creator

Cocos Creator 是以内容创作为核心，实现了脚本化、组件化和数据驱动的游戏开发工具，包括了 Cocos2d-x 引擎的 JavaScript 实现以及能让你更快速开发游戏所需要的各种图形界面工具。

<div align="center"><img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/dapp-integration/cocos-structure.jpg" width="440px"></div>

<p class="info">
Cocos2d-x 是一套成熟的开源跨平台游戏开发框架，提供了图形渲染、GUI、音频、网络、物理、用户输入等丰富的功能，被广泛应用于游戏开发及交互式应用的构建。其核心采用 C++ 编写，支持使用 C++、Lua 或 JavaScript 进行开发。
</p>

## 快速开始

如果你希望使用 Cocos Creator 开发基于本体网络的区块链游戏，你可以项目目录中引入桌面浏览器端所需的 `ontology-dapi` 以及移动手机端所需的 `cyano-bridge`。

<p class="warning">
由于桌面浏览器端的 <code>ontology-dapi</code> 无法在手机端使用。因此，如果你需要进行多端适配，请为桌面端和移动端创建不同的游戏场景，并在构建时分开构建。
</p>

### 桌面浏览器

`ontology-dapi` 是一个用于与 Chrome 钱包插件交互的轻量级 JavaScript 库。

```bash
$ npm install ontology-dapi -S
```

我们可以在游戏场景的脚本中以 ES6 模块的形式导入：

```bash
import { client } from 'ontology-dapi';
```

我们也可以在游戏场景的脚本中以 CommonJS/ES6 模块的形式导入：

```bash
var client = require('ontology-dapi').client;
```

在完成模块的导入后，我们只需要在场景的加载函数中与浏览器中的 Provide 实例注册即可：

```JavaScript
client.registerClient({});
```

### 手机端

`cyano-bridge` 是一个用于与移动钱包交互的 JavaScript 库。

```bash
$ npm install cyanobridge -S
```

我们可以在游戏场景的脚本中以 ES6 模块的形式导入：

```bash
import { client } from 'cyanobridge';
```

我们也可以在游戏场景的脚本中以 CommonJS/ES6 模块的形式导入：

```bash
var client = require('cyanobridge').client;
```

在完成模块的导入后，我们只需要在场景的加载函数中与浏览器中的 Provide 实例注册即可：

```JavaScript
client.registerClient();
```

## 示例项目

我们构建了一个名为 `bitcoin-catcher-box` 的开源项目，用于展示如何使用去中心化应用开发套件 Punica Suite 快速完成基于 Cocos2d-x 游戏引擎的区块链小游戏的开发。

### 在线体验

为了让你能够直观地感受区块链游戏，我们将该示例项目部署在了 GitHub pages 上。

#### 桌面浏览器

你可以在安装了 Cyano Wallet 的 Chrome 内核浏览器中访问部署在[这里](https://punica-box.github.io/bitcoin-catcher-box/)的游戏。

<div align="center"><img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/dapp-integration/game-in-chrome.png" width="800px"></div>

<p class="warning">
游戏的合约目前只部署在了 polaris 测试网上。因此，在体验之前，请将你的插件钱包或者移动端钱包切换到 polaris 测试网或者任何你已预先部署好合约的区块链网络。
</p>

#### 手机端

你可以在支持 `CEP-1` 的钱包中访问部署在[这里](https://punica-box.github.io/bitcoin-catcher-box/)的游戏，例如 Cyano Wallet、麦子钱包。

<div align="center"><img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/dapp-integration/game-in-onto.jpg" width="280px"></div>

<p class="warning">
游戏的合约目前只部署在了 polaris 测试网上。因此，在体验之前，请将你的插件钱包或者移动端钱包切换到 polaris 测试网或者任何你已预先部署好合约的区块链网络。
</p>

### 快速开始

1. 安装 Punica CLI

    ```bash
    $ pip3 install punica
    ```

2. 获取 `bitcoin-catcher-box`

    ```bash
    $ punica unbox bitcoin-catcher
    ```

3. 安装依赖

    ```bash
    $ npm install
    ```

4. 使用 Cocos Creator 打开项目。

<div align="center"><img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/dapp-integration/open-pj-in-cocos-creator.png" width="700px"></div>

### 文档

关于示例项目的更多信息，你可以点击[这里](https://punica-box.gitbook.io/docs/bitcoin-catcher-box)访问该项目的介绍文档。
