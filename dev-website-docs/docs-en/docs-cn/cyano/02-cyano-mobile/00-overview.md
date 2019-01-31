
`cyano-mobile` 是 [CEP-1](https://github.com/ontio-cyano/CEPs/blob/master/CEPS/CEP1.mediawiki#scenario-3-provider-opens-dapp) 提案的一套标准实现，将电脑端的 dApi 扩展到了移动端，涵盖了移动端 dApp 的三个使用场景。

- 集成了 `dApi-mobile` 的钱包通过二维码进行账户登陆、智能合约的调用。
- 集成了 `cyano-sdk` 的 dApp 唤醒集成了 `dApi-mobile` 的钱包。
- 集成了 `dApi-mobile` 的钱包打开内嵌的 dApp 并进行账户登陆、智能合约的调用。

在 `cyano-mobile` 中，dApp 的数据请求 URL 遵循 `CEP-1` 规范：

```java
import android.net.Uri;
import android.util.Base64;

import com.alibaba.fastjson.JSON;

String param = Base64.encodeToString(Uri.encode(JSON.toJSONString(map)).getBytes(), Base64.NO_WRAP).toString();
String url = "ontprovider://ont.io?param=".concat(param);
```

同时，本体团队提供了实现了 `CEP-1` 移动端钱包：

- [Android](https://github.com/ontio-cyano/cyano-android)
- [IOS](https://github.com/ontio-cyano/cyano-ios)

如果你想要将你的 dApp 接入到使用了 `dApi-mobile` 的钱包，你可以查看我们的 SDK 接入文档。

- [Android](https://dev-docs.ont.io/#/docs-cn/cyano/01-cyano-android-sdk)
- [IOS](https://dev-docs.ont.io/#/docs-cn/cyano/02-cyano-ios-sdk.md)
