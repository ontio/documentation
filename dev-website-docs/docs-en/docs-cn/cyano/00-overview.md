
`Cyano` 是一座连接未来的去中心化网络的桥梁，旨在使越来越多的人尽可能容易地使用本体。通过使用 `Cyano`，你能够马上使用本体上丰富的 dApp。更为重要的是，在这个过程中，你无需将你的私钥交给各种各样的 dApp，私钥将被保护在你的钱包之中。

`Cyano` 分为钱包端的 `Cyano Provider` 与 dApp 端的 `Cyano Provider SDK` 两部分。在技术实现上，钱包端通过集成 `Cyano Provider` 库来提供标准的 dApp 调用接口，dApp 端则通过集成 `Cyano Provider SDK` 来与支持 `Cyano Provider` 的各类钱包进行通信。

无论是电脑端还是移动端的，我们均提供了相应的 `Provider` 组件库供钱包集成。

- `Cyano Chrome Provider`：集成了 `cyano-chrome` 的浏览器钱包插件。
- `Cyano Mobile Provider`：集成了 `cyano-mobile` 的移动端钱包应用。
  - Android：通过集成 `cyano-android` 组件库来提供 `Provider` 实例，你可以点击[这里](https://github.com/ontio-cyano/cyano-android)访问在 GitHub 上的项目。
  - IOS：通过集成 `cyano-ios` 组件库来提供 `Provider` 实例，你可以点击[这里](https://github.com/ontio-cyano/cyano-ios)访问在 GitHub 上的项目。

对应地，我们提供了电脑端与移动端的 `Cyano Provider SDK` 供 dApp 使用。

- `Chrome Provider SDK`：供 Chrome 浏览器上的 dApp 与浏览器钱包插件进行通信。
- `Android Provider SDK`：供 Android 端的 dApp 与集成了 `cyano-mobile` 的移动端钱包应用进行通信，你可以点击[这里](https://github.com/ontio-cyano/cyano-android-sdk)访问在 GitHub 上的项目。
- `IOS Provider SDK`：供 IOS 端的 dApp 与集成了 `cyano-mobile` 的移动端钱包应用进行通信，你可以点击[这里](https://github.com/ontio-cyano/cyano-ios-sdk)访问在 GitHub 上的项目。
