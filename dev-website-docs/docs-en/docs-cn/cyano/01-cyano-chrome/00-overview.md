
### 简介

`cyano wallet` 是一款基于 `Chrome` 浏览器开发的钱包插件，集成了 `cyano-chrome` 组件库，你可以通过点击[这里](https://chrome.google.com/webstore/detail/cyano-wallet/dkdedlpgdmmkkfjabffeganieamfklkm)从 Chrome 网上应用店中获取该插件，或者点击[这里](https://github.com/OntologyCommunityDevelopers/cyano-wallet/releases)从 Github 上下载安装包。当钱包插件安装完成后，你可点击[这里](https://dapp.review/explore/ont)体验基于 Chrome 浏览器的 dApp。

!> 出于安全考虑，请将你的资产在冷钱包与热钱包中进行适当的分配。

- 账户管理
  - 创建账户
  - 导入导出 `keystore` 文件。
  - 通过十六进制私钥创建账户。
  - 通过 `WIF` 格式的私钥创建账户。
  - 通过助记词恢复账户。
- 身份管理
  - 创建身份。
  - 通过十六进制私钥创建身份。
  - 通过 `WIF` 格式的私钥创建身份。
- 资产管理
  - ONT
  - ONG
  - OEP-4 Token
- 网络管理
  - 主网
  - `polaris` 测试网
  - 私有网络
  - 本地节点
- 连接硬件钱包  
  - Ledger
  - Trezor
- 可信合约管理

!> 在创建身份的过程中需要在链上进行注册，因此你需要确保你的钱包账户中至少拥有 0.01 个 ONG。

### 常见问题

- 我在 `cyano wallet` 中导入了我的钱包账户，但为什么账户余额不对？
  
  首先，你需要在左下角查看你的钱包插件是否接入了正确的网络。如果接入的网络不正确，你可以通过点击右上角的 ⚙️ 图标进行修改。其次，你需要确定你的钱包插件是否已正确接入到了节点，你可以将鼠标移动到右下角的图标查看是否显示为 `Connected`。

- 如何查看我的钱包身份列表？

  你可以点击右上角的 🎫 图标切换到身份列表。

- 如何查看我的钱包账户列表？

  你可以点击右上角的 💲 图标从身份列表切换到钱包列表。

- 如何切换我的账户/身份？

  你可以点击右上角的 ⇄ 图标进行切换。