

## 概述

进行特殊适配的钱包 App 可以支持被手机内其他 App 唤醒，本文将介绍在 App 内如何通过唤醒钱包 App 实现登录，调用智能合约（包括付款）等功能。

### 基本概念

##### DApp
去中心化应用程序

##### DApp 后台
主要提供以下功能：
- DApp 操作，生成相应的登录参数或者调用智能合约的参数。
- 同步链上信息，获取登录或调用智能合约的结果

##### Provider
提供签名，预执行交易，执行交易等与链交互。本文档描述针对目前支持的两个钱包：
- ONTO [下载](https://onto.app)
- Cyano [下载](http://101.132.193.149/files/app-debug.apk)

##### demo
我们提供了一个唤醒特定钱包的Demo app 供参考：[唤醒demo](https://github.com/ontio-cyano/android-app-demo)

## 交互流程

DApp 开发要实现唤醒功能中的两种流程：
- 登录
- 调用智能合约

登录流程不用过多解释，调用智能合约这个流程可以根据调用不同合约不同方法，实现 DApp 的各种业务逻辑，以游戏为例，可以实现购买，出售，租赁等不同的业务。

### 登录

登录流程如下图所示：

![wakeup-login](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/wakeupLogin.png)

1. DApp 将 DApp 后台服务构建的登录信息发送给特定的 Provider （钱包）
2. Provider 对登录信息进行签名，将相关的数据传输到之前登录信息中设定好的回传地址
3. DApp 后台验证签名，通过后通知 DApp 登录成功。

#### 登录数据

当 DApp 需要登录的时候，就从 DApp 后台获取登录数据，发送给特定的 Provider

登录数据示例：
```json
{
	"action": "login",
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
	"version": "v1.0.0",
	"params": {
		"type": "ontid or account",
		"dappName": "dapp Name",
		"dappIcon": "dapp Icon",
		"message": "helloworld",
		"expire": 1546415363,
		"callback": "http://127.0.0.1:80/login/callback"
	}
}
```

#### 具体实施流程

1. 判断本地是否安装Cyano App，例如:

   ```
    public static boolean checkInstallCynoApp(Context context) {
           final PackageManager packageManager = context.getPackageManager();// 获取packagemanager
           List<PackageInfo> pinfo = packageManager.getInstalledPackages(0);// 获取所有已安装程序的包信息
           if (pinfo != null) {
               for (int i = 0; i < pinfo.size(); i++) {
                   String pn = pinfo.get(i).packageName.toLowerCase(Locale.ENGLISH);
                   if (pn.equals("com.github.ont.cyanowallet")) {
                       return true;
                   }
               }
           }
           return false;
       }
   ```

2. DApp 将 DApp 后台服务构建的登录信息发送给特定的 Provider （钱包），例如：

   ```
       String data = "{\"action\":\"login\",\"id\":\"10ba038e-48da-487b-96e8-8d3b99b6d18a\",\"version\":\"v1.0.0\",\"params\":{\"type\":\"ontid or account\",\"dappName\":\"dapp Name\",\"dappIcon\":\"dapp Icon\",\"message\":\"helloworld\",\"expire\":1546415363,\"callback\":\"http://127.0.0.1:80/login/callback\"}}"; //此处就是将之前的登录数据拼接后的状态。
   
       String sendData = Base64.encodeToString(Uri.encode(data).getBytes(), Base64.NO_WRAP);
       Intent intent = new Intent("android.intent.action.VIEW");
       intent.setData(Uri.parse("ontprovider://ont.io?param=" + sendData ));
       intent.addCategory("android.intent.category.DEFAULT");
       startActivity(intent);
   ```

3. Provider 对登录信息进行签名，将相关的数据传输到之前登录信息中设定好的回传地址，此步操作不需要DApp 开发者执行。

4. DApp 后台验证签名，通过后通知 DApp 登录成功。

签名验证方法：
* [java sdk验签](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/interface.md#%E7%AD%BE%E5%90%8D%E9%AA%8C%E7%AD%BE)
* [ts sdk验签](https://github.com/ontio/ontology-ts-sdk/blob/master/test/ecdsa.crypto.test.ts)


### 调用合约

调用合约流程如下图所示：

![wakeup-login](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/wakeupInvoke.png)

1. 构建调用合约数据给特定 Provider
2. Provider 签名，预执行，并最终发送到链上（本步骤无需 DApp 开发）
3. Provider 将交易 hash 发给 DApp 后台
4. DApp 后台从链上查询合约执行结果
5. DApp 后台将结果反馈给 DApp，呈献给用户

#### 调用合约数据

调用合约数据示例：
```
{
	"action": "invoke",
	"version": "v1.0.0",
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
	"params": {
		"login": true,
		"qrcodeUrl": "http://101.132.193.149:4027/qrcode/AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ",
		"message": "will pay 1 ONT in this transaction",
		"callback": "http://101.132.193.149:4027/invoke/callback"
	}
}
```
#### 具体实施流程

1. 检查是否安装特定 Provider ，参考 [登录](#登录)

2. DApp 后台将交易内容放在 qrcodeUrl 链接中，具体操作请参考 [Cyano二维码](https://github.com/ontio-cyano/CEPs/blob/master/CEPS/CEP1.mediawiki#Invoke_a_Smart_Contract-2)

   拼接传递内容，启动交易，例如：

   ```
       String data="{\"action\":\"invoke\",\"version\":\"v1.0.0\",\"id\":\"10ba038e-48da-487b-96e8-8d3b99b6d18a\",\"params\":{\"login\":true,\"qrcodeUrl\":\"http://101.132.193.149:4027/qrcode/AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ\",\"message\":\"will pay 1 ONT in this transaction\",\"callback\":\"http://101.132.193.149:4027/invoke/callback\"}}";
   
   
       String sendData = Base64.encodeToString(Uri.encode(data).getBytes(), Base64.NO_WRAP);
       Intent intent = new Intent("android.intent.action.VIEW");
       intent.setData(Uri.parse("ontprovider://ont.io?param=" + sendData ));
       intent.addCategory("android.intent.category.DEFAULT");
       startActivity(intent);
   ```

3. Provider 签名，预执行，最终发送到链上（本步骤无需 DApp 开发）

4. Provider 将交易 hash 发给DApp 后台（本步骤视 DApp 具体情况实现）。

5. DApp 后台从链上查询合约执行结果：

   - [java sdk 交易事件查询方法](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/basic.md#%E4%B8%8E%E9%93%BE%E4%BA%A4%E4%BA%92%E6%8E%A5%E5%8F%A3)
   - [ts sdk 交易事件查询方法](https://github.com/ontio/ontology-ts-sdk/blob/master/test/websocket.test.ts)

6. DApp 后台将结果反馈给 DApp，呈献给用户（本步视 DApp 具体情况实现）。