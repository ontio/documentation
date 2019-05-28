
<iframe frameborder="0" src="https://v.qq.com/txp/iframe/player.html?vid=u0797zd38y1" allowFullScreen="true" width="100%" height="360"></iframe>

`Cyano` 是一座连接未来的去中心化网络的桥梁，旨在使越来越多的人尽可能容易地使用本体。

通过使用 `Cyano`，你能够马上使用本体上丰富的 dApp。更为重要的是，在这个过程中，你无需将你的私钥交给各种各样的 dApp，私钥将被保护在你的钱包之中。

`Cyano` 分为钱包端的 `Provider SDK` 与 dApp 端的 `dAPI` 两部分。

在技术实现上，钱包端通过集成 `Provider SDK` 来提供标准化的 `Provider` 实例供 dApp 调用，dApp 端则通过集成 `dAPI` 来与 `Provider` 实例进行通信。

无论是电脑端还是移动端的，我们均提供了相应的 `Provider SDK` 供钱包集成。

<iframe frameborder="0" src="https://v.qq.com/txp/iframe/player.html?vid=l0797rr9g9a" allowFullScreen="true" width="100%" height="360"></iframe>

- `Chrome Provider`：集成了 `cyano-chrome` 的浏览器钱包插件。
- `Mobile Provider`：集成了 `cyano-mobile` 的移动端钱包应用。

对于 `Mobile Provider`，我们为主流的操作系统提供了相应的 SDK，并保持了方法上的一致性。

- `cyano-android-sdk`：用于为 Android 端的移动钱包提供 `Provider` 实例，你可以点击[这里](https://github.com/ontio-cyano/cyano-android-sdk)访问在 GitHub 上的项目。
- `cyano-ios-sdk`：用于为 IOS 端的移动钱包提供 `Provider` 实例，你可以点击[这里](https://github.com/ontio-cyano/cyano-ios-sdk)访问在 GitHub 上的项目。

对应地，我们提供了电脑端与移动端的 `dAPI` 供 dApp 与 `Provider` 实例之间进行通信。

- `ontology-dapi`：供电脑端的 dApp 与 Chrome 浏览器钱包插件进行通信，你可以点击[这里](https://github.com/ontio/ontology-dapi)访问在 GitHub 上的项目。
- `cyano-bridge`：供移动端的 dApp 与集成了 `cyano-mobile` 的移动端钱包应用进行通信，你可以点击[这里](https://github.com/ontio-cyano/cyano-bridge)访问在 GitHub 上的项目。
