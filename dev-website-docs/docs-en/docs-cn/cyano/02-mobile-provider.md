
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

同时，本体提供了实现了 `CEP-1` 移动端钱包：

- [Android](https://github.com/ontio-cyano/cyano-android)
- [IOS](https://github.com/ontio-cyano/cyano-ios)

### Android SDK

`cyano-android-sdk` 基于 [CEP1](https://github.com/ontio-cyano/CEPs/blob/master/CEPS/CEP1.mediawiki) 进行实现，对 Android WebView 进行了封装，用于帮助基于 WebView 进行开发的 Android 手机端 dApp 与实现了 `CEP1` 规范的钱包之间进行通信。

!> `WebView` 的通信方式为 `window.postmeaage()`

#### 导入项目

你可以从[这里](https://github.com/ontio-cyano/cyano-android-sdk)获取完整的项目代码，然后将 `cyano-android-sdk` 以模块的形式导入到你的项目中。

#### 初始化

在调用 `cyano-andorid-sdk` 所提供的方法之前，你需要对其进行初始化。

```java
CyanoWebView cyanoWebView = new CyanoWebView(context);  
cyanoWebView.loadUrl(url);
```

更详细的使用方法，你可以点击[这里](https://github.com/ontio-cyano/cyano-android)查看我们提供的示例程序 `cyano-android`，点击[这里](http://101.132.193.149/files/app-debug.apk)获取示例程序的安装包。

### IOS SDK

`cyano-ios-sdk` 基于 [CEP1](https://github.com/ontio-cyano/CEPs/blob/master/CEPS/CEP1.mediawiki) 进行实现，对 IOS WebView 进行了封装，用于帮助基于 WebView 进行开发的 IOS 手机端 dApp 与实现了 `CEP1` 规范的钱包之间进行通信。

!> `WebView` 的通信方式为 `window.postmeaage()`

#### 导入项目

你可以从[这里](https://github.com/ontio-cyano/cyano-ios-sdk)获取完整的项目代码，然后将 `cyano-ios-sdk` 以模块的形式导入到你的项目中。

#### 初始化

在调用 `cyano-ios-sdk` 所提供的方法之前，你需要对其进行初始化。

```Objective-C
RNJsWebView * webView = [[RNJsWebView alloc]initWithFrame:CGRectZero];
[webView setURL:@""];
```

更详细的使用方法，你可以点击[这里](https://github.com/ontio-cyano/cyano-ios)查看我们提供的示例程序 `cyano-ios`。
