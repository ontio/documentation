# cyano-android-sdk
cyano-android-sdk 帮助Android webview和网页dapp之间通信。它对Android webview进行了一些方法的封装。
>webview通信的方式是window.postmeaage()

* [WALLET](#WALLET)
* ONTID (暂不支持)
    * [如何使用](#ONTID_如何使用)
    * [快速集成](#ONTID_快速集成)
* [DEMO](#demo)
* [DEMO 下载地址](#DEMO_下载地址)

# 集成
将工程当作module导入到项目中

[数据格式请参照CEP1文档](https://github.com/ontio-cyano/CEPs/blob/master/CEPS/CEP1.mediawiki)

## WALLET

* 初始化

```
	CyanoWebView cyanoWebView=new CyanoWebView(context);
	cyanoWebView.loadUrl(url);
```


* action：login

```
	cyanoWebView.getNativeJsBridge().setHandleLogin(new NativeJsBridge.HandleLogin() {
            @Override
            public void handleAction(String data) {
            /* TODO
            * 1. params参数中解析出message
            * com.alibaba.fastjson.JSONObject reqJson = JSON.parseObject(data);
            * String message=reqJson.getJSONObject("params").getString("message");
            *
            * 2.弹出密码框,解出钱包account,对message进行签名，注意耗时操作。
            *
            * 3. 拼接返回结果，包括：publicKey、type、user message signature
            *  JSONObject result = new JSONObject();
            *   result.put("publickey", 钱包公钥);
            *   result.put("type", "account");
            *   result.put("user", 钱包地址);
            *   result.put("message", message);
            *   result.put("signature", 签名结果);
            *
            * 4.发送返回结果到webView
            * String action=reqJson.getString("action");
            * String version=reqJson.getString("version");
            * String id=reqJson.getString("id");
            * cyanoWebView.sendSuccessToWeb(action,version, id, result);
            */
            }
	});
```


* action：Invoke
```
	cyanoWebView.getNativeJsBridge().setHandleInvoke(new NativeJsBridge.HandleInvoke() {
            @Override
            public void handleAction(String data) {
              /* TODO
               * 1.弹出密码输入框，解出钱包account，将data构建交易，对交易进行签名，预执行获取结果，注意耗时操作。
               *
               * 2.将预知行结果解析出Notify结果，显示手续费，如果结果中包含ONT,ONG合约地址，需显示转账金额和收款地址，
               *
               * 3.用户确认后发送交易到链上
               *
               * 4.发送交易hash到webView
               * com.alibaba.fastjson.JSONObject reqJson = JSON.parseObject(data);
               * String action=reqJson.getString("action");
               * String version=reqJson.getString("version");
               * String id=reqJson.getString("id");
               * cyanoWebView.sendSuccessToWeb(action,version, id, 交易hash);
               */
            }
	});
```

* action：GetAccount
```
	cyanoWebView.getNativeJsBridge().setHandleGetAccount(new NativeJsBridge.HandleGetAccount() {
            @Override
            public void handleAction(String data) {
              /* TODO
               * 1.发送钱包地址到webView
               * com.alibaba.fastjson.JSONObject reqJson = JSON.parseObject(data);
               * String action=reqJson.getString("action");
               * String version=reqJson.getString("version");
               * String id=reqJson.getString("id");
               * cyanoWebView.sendSuccessToWeb(action,version, id, 钱包地址);
               */
            }
	});
```

* action：InvokeRead
```
	cyanoWebView.getNativeJsBridge().setHandleInvokeRead(new NativeJsBridge.HandleInvokeRead() {
            @Override
            public void handleAction(String data) {
              /* TODO
               * 1.将data构建交易，预执行获取结果，注意耗时操作。
               *
               * 2.发送预知行结果到webView
               * com.alibaba.fastjson.JSONObject reqJson = JSON.parseObject(data);
               * String action=reqJson.getString("action");
               * String version=reqJson.getString("version");
               * String id=reqJson.getString("id");
               * cyanoWebView.sendSuccessToWeb(action,version, id, 预知行结果);
               */
            }
	});
```

* action：InvokePasswordFree
```
	cyanoWebView.getNativeJsBridge().setHandleInvokePasswordFree(new NativeJsBridge.HandleInvokePasswordFree() {
            @Override
            public void handleAction(String data, String message) {
              /* TODO
               * 1.第一次操作和action：Invoke相同，同时保存password和message
               *
               * 2.当第二次收到相同的message时候，将用保存的密码进行签名，预知行获取结果
               *
               * 3.预知行结果不用显示给用户确认
               *
               * 4.发送交易hash到webView
               * com.alibaba.fastjson.JSONObject reqJson = JSON.parseObject(data);
               * String action=reqJson.getString("action");
               * String version=reqJson.getString("version");
               * String id=reqJson.getString("id");
               * cyanoWebView.sendSuccessToWeb(action,version, id, 交易hash);
               */
            }
	});
```
* 失败返回结果


```
	/*
	* 需要错误返回时调用
	*/
	cyanoWebView.sendFailToWeb(action,error,version,id,result);

    action：请求的action

    version：请求的version

    id：请求的id

    error：错误码

    result：处理后的结果
```

[错误码](https://github.com/ontio-cyano/CEPs/blob/master/CEP1.mediawiki#Error_code)

## ONTID_如何使用

* ONT ID认证

```
  mWebView.getNativeJsBridge().setAuthentication(new NativeJsBridge.HandleAuthentication() {
            @Override
            public void handleAction(String data) {
                JSONObject jsonObject = JSON.parseObject(data);
                String subAction = jsonObject.getJSONObject("params").getString("subaction");
                switch (subAction) {
                    case "getIdentity":
              /* TODO
               * 1.发送ONT_ID到webView
               * com.alibaba.fastjson.JSONObject reqJson = JSON.parseObject(data);
               * String action=reqJson.getString("action");
               * String version=reqJson.getString("version");
               * String id=reqJson.getString("id");
               * cyanoWebView.sendSuccessToWeb(action,version, id, ONT_ID);
               */
                        break;
                    case "submit":
              /* TODO
               * 1.将H5返回的内容发到钱包后台
               * 2.将发送结果进行返回
               * com.alibaba.fastjson.JSONObject reqJson = JSON.parseObject(data);
               * String action=reqJson.getString("action");
               * String version=reqJson.getString("version");
               * String id=reqJson.getString("id");
               * cyanoWebView.sendSuccessToWeb(action,version, id, true);
               */
                        break;
                    case "getRegistryOntidTx":
              /* TODO
               * 1.发送保存的ONT_ID交易到webView
               * com.alibaba.fastjson.JSONObject reqJson = JSON.parseObject(data);
               * String action=reqJson.getString("action");
               * String version=reqJson.getString("version");
               * String id=reqJson.getString("id");
               * cyanoWebView.sendSuccessToWeb(action,version, id, ONT_ID交易内容);
               */
                        break;
                    default:
                }
            }
        });
```

* ONT ID授权

```

        mWebView.getNativeJsBridge().setAuthorization(new NativeJsBridge.HandleAuthorization() {
            @Override
            public void handleAction(String data) {
                JSONObject jsonObject = JSON.parseObject(data);
                String subAction = jsonObject.getJSONObject("params").getString("subaction");
                switch (subAction) {
                    case "requestAuthorization":
              /* TODO
               * 1.保存收到的数据,并跳转到授权界面
               * mWebView.loadUrl(Constant.CYANO_AUTH_URL);
               */
                        break;
                    case "getAuthorizationInfo":
              /* TODO
               * 1.将保存数据中的subaction改成getAuthorizationInfo
               *
               * 2.将结果进行返回
               * com.alibaba.fastjson.JSONObject reqJson = JSON.parseObject(data);
               * String action=reqJson.getString("action");
               * String version=reqJson.getString("version");
               * String id=reqJson.getString("id");
               * cyanoWebView.sendSuccessToWeb(action,version, id, 保存的数据);
               */
                        break;
                    case "decryptClaim":
               /* TODO
               * 1.弹出密码框，处理加密的数据
               *  JSONArray parse = jsonObject.getJSONObject("params").getJSONArray("message");
               * String[] datas = new String[parse.size()];
               * for (int i = 0; i < parse.size(); i++) {
                    datas[i] = parse.getString(i);
               * }
               *
               * 2.解密，得到解密结果
               *
               * 2.将结果进行返回
               * com.alibaba.fastjson.JSONObject reqJson = JSON.parseObject(data);
               * String action=reqJson.getString("action");
               * String version=reqJson.getString("version");
               * String id=reqJson.getString("id");
               * cyanoWebView.sendSuccessToWeb(action,version, id, 解密结果);
               */
                        break;
                    case "deleteOntid":
              /* TODO
               * 1.弹出密码框，校验ONT ID的密码
               *
               * 2.密码成功后删除本地ONT ID，关闭页面
               */
                        break;
                    default:
                }
            }
        });
```

## ONTID_快速集成
我们已经对ONT ID相关处理进行了封装，如果对页面没有定制话需求可以直接使用

* 添加权限

```
    <uses-permission android:name="android.permission.SYSTEM_ALERT_WINDOW" />
    <uses-permission android:name="android.permission.SYSTEM_OVERLAY_WINDOW" />
    <uses-permission android:name="android.permission.INTERNET" />
    <uses-permission android:name="android.permission.VIBRATE" />
    <uses-permission android:name="android.permission.CAMERA" />
    <uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE" />
    <uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
    <uses-permission android:name="android.permission.REQUEST_INSTALL_PACKAGES" />
```

* 注册activity

```
    <activity android:name="com.github.ont.connector.ontid.CreateOntIdActivity" />
    <activity android:name="com.github.ont.connector.ontid.ImportOntIdActivity" />
    <activity android:name="com.github.ont.connector.ontid.OntIdWebActivity" />
    <activity android:name="com.github.ont.connector.ontid.TestFrameActivity" />
    <activity android:name="com.github.ont.connector.ontid.ExportOntIdActivity" />
```

* 添加ONT lib

将repositories的文件夹复制到工程中

在工程最外部的build.gradle添加
```
allprojects {
    repositories {
        flatDir {
            dirs '../repositories'
        }
    }
}
```

如果钱包需要集成，在对应build.gradle文件中添加
```
  implementation(name: 'ontolib-release', ext: 'aar')
```

* 照片选择

在[build.gradle](https://github.com/ontio-cyano/cyano-android-sdk/blob/master/cyano_lib/build.gradle)修改图片选择库，当前使用得是matisse图片选择器

在[com.github.ont.connector.update.ImageUtil](https://github.com/ontio-cyano/cyano-android-sdk/blob/master/cyano_lib/src/main/java/com/github/ont/connector/update/ImageUtil.java)文件中修改对应的图片处理

* 网络请求

在[build.gradle](https://github.com/ontio-cyano/cyano-android-sdk/blob/master/cyano_lib/build.gradle)修改网络框架，当前使用得是okhttp框架

在[com.github.ont.connector.update.NetUtil](https://github.com/ontio-cyano/cyano-android-sdk/blob/master/cyano_lib/src/main/java/com/github/ont/connector/update/NetUtil.java)文件中修改对应的网络请求

* 设置wallet file的存储路径

修改[Constant](https://github.com/ontio-cyano/cyano-android-sdk/blob/master/cyano_lib/src/main/java/com/github/ont/cyano/Constant.java)的WALLET_FILE字段，让ont sdk存储wallet file路径一致

* 设置服务器的接收地址

修改[Constant](https://github.com/ontio-cyano/cyano-android-sdk/blob/master/cyano_lib/src/main/java/com/github/ont/cyano/Constant.java)的WALLET_RECEIVER_URL字段，认证后会返回[authenticationId](https://github.com/ontio-cyano/integration-docs/blob/master/%E9%92%B1%E5%8C%85%E5%AF%B9%E6%8E%A5-OntId%E8%AE%A4%E8%AF%81.md),需要提交到钱包服务器.

* 启动

启动ONT ID界面，ONT ID的私钥，密码和ONT 默认钱包 钱包一致，在进入界面之前需要检查是否已创建好钱包。

ONT ID只允许创建一个

```
        String defaultAccountAddress = OntSdk.getInstance().getWalletMgr().getWallet().getDefaultAccountAddress();

        if (TextUtils.isEmpty(defaultAccountAddress)) {
        //TODO 未创建钱包的处理
        } else {
                    Intent intent = new Intent(baseActivity, TestFrameActivity.class);
                    startActivity(intent);
        }
```

## DEMO
[cyano-android](https://github.com/ontio-cyano/cyano-android)

## DEMO_下载地址
[点我下载](http://101.132.193.149/files/app-debug.apk)

## 版本
0.0.1
