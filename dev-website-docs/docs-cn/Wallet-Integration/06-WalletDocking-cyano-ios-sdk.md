# cyano-ios-sdk

cyano-ios-sdk 帮助 iOS webview和网页dapp之间通信。它对iOS webview进行了一些方法的封装。

> webview通信的方式是window.postmeaage()

- [WALLET](#如何使用)
- [ONTID](#ONTID) (<u>暂不支持</u>)
- [DEMO](#DEMO)
- [下载地址](#下载地址)

## 如何使用

- 将 CyanoRNWebView.framework 导入项目
- #import "RNJsWebView.h"

### 示例

#### 初始化

```
RNJsWebView * webView = [[RNJsWebView alloc]initWithFrame:CGRectZero];
[webView setURL:@""];
```

##### data

消息体data格式为json字符串

```
{
	"action": "login",
	"params": {
		"type": "account",
		"dappName": "My dapp",
		"message": "test message",
		"expired": "201812181000",
		"callback": ""
	}
}
```

##### message

对消息体 data 进行 decode 并 base64 加密,然后在拼接后的字符串首位再拼接上 ontprovider://ont.io?params= 作为网页端传来的原文数据

##### action: Login

```
[webView setLoginCallback:^(NSDictionary *callbackDic) {
    /*
     * TODO
     * 1.从 callbackDic 回调中解出 message
     * NSDictionary *params = callbackDic[@"params"];
     * NSString *message = params[@"message"];
     *
     * 2.将 message 转换成 hexString
     *
     * 3.弹出密码框,解出钱包account,对message进行签名，注意密码是base64EncodeString,并且耗时操作。
     *  （签名方法参考DEMO中TS SDK中signDataHex方法）
     *
     * 4.拼接返回结果，包括：action、version、error、desc、id、type、publicKey、address、
     *   message、signature
     * NSDictionary *result =@{@"type": @"account",
     *                         @"publicKey":钱包公钥,
     *                         @"address": 钱包地址,
     *                         @"message":message ,
     *                         @"signature":签名结果,
     *                         };
     * NSDictionary *callBackMessage =@{@"action":@"login",
     *                                  @"version": @"v1.0.0",
     *                                  @"error": @0,
     *                                  @"desc": @"SUCCESS",
     *                                  @"result":result,
     *                                  @"id":callbackDic[@"id"]
     *                                  };
     * [webView sendMessageToWeb:callBackMessage];
     */
}];
```

##### action: GetAccount

```
[webView setGetAccountCallback:^(NSDictionary *callbackDic) {
    /*
     * TODO
     * 1.发送钱包地址到webView
     * NSDictionary *callBackMessage =@{@"action":@"getAccount",
     *                                  @"version":@"v1.0.0",
     *                                  @"error":@0,
     *                                  @"desc":@"SUCCESS",
     *                                  @"result":钱包地址,
     *                                  @"id":callbackDic[@"id"]
     *                                  };
     * [webView sendMessageToWeb:callBackMessage];
     */
}];
```

##### action: Invoke

```
[webView setInvokeTransactionCallback:^(NSDictionary *callbackDic) {
    /* TODO
     * 1.弹出密码框，解出钱包明文私钥
     *
     * 2.将 callbackDic 转换成 jsonString 并以此构造交易（构造交易方法参考DEMO中TS SDK 中
     *   makeDappTransaction 方法）
     *
     * 3.预执行交易（预执行交易方法参考DEMO中TS SDK 中 checkTransaction 方法），并解析结果，注意耗时
     *   操作
     *
     * 4.将预知行结果解析出Notify结果，显示手续费，如果结果中包含ONT,ONG合约地址，需显示转账金额和收款
     *   地址，
     *
     * 5.用户确认后发送交易到链上
     *
     * 6.发送交易hash到webView
     * NSDictionary *callBackMessage = @{@"action":@"invoke",
     *                                 @"version": @"v1.0.0",
     *                                 @"error": @0,
     *                                 @"desc": @"SUCCESS",
     *                                 @"result":交易hash,
     *                                 @"id":callbackDic[@"id"]
     *                                 };
     * [webView sendMessageToWeb:callBackMessage];
     */
}];
```



##### action: InvokeRead

```
[webView setInvokeReadCallback:^(NSDictionary *callbackDic) {
    /* TODO
     * 1.将 callbackDic 转换成 jsonString 并以此构造交易（构造交易方法参考DEMO中TS SDK 中
     *   makeDappInvokeReadTransaction 方法）
     *
     * 2.预执行交易（预执行交易方法参考DEMO中TS SDK 中 checkTransaction 方法），并解析结果，注意耗时
     *   操作
     *
     * 3.将预知行结果解析出Notify结果，显示手续费，如果结果中包含ONT,ONG合约地址，需显示转账金额和收款
     *   地址，
     *
     * 4.用户确认后发送交易到链上
     *
     * 5.发送交易hash到webView
     * NSDictionary *callBackMessage = @{@"action":@"InvokeRead",
     *                                 @"version": @"v1.0.0",
     *                                 @"error": @0,
     *                                 @"desc": @"SUCCESS",
     *                                 @"result":交易hash,
     *                                 @"id":callbackDic[@"id"]
     *                                 };
     * [webView sendMessageToWeb:callBackMessage];
     */
}];
```



##### action: InvokePasswordFree

```
[webView setInvokePasswordFreeCallback:^(NSDictionary *callbackDic) {
    /* TODO
     * 1.第一次操作和action：Invoke相同，保存password，解出callbackDic[@"params"]并转换成
     *   jsonString 并保存
     *
     * 2.当第二次收到相同的 callbackDic[@"params"] 时候，将用保存的密码进行签名，预知行获取结果
     *
     * 3.预知行结果不用显示给用户确认
     *
     * 4.发送交易hash到webView
     * NSDictionary *callBackMessage = @{@"action":@"InvokePasswordFree",
     *                                 @"version": @"v1.0.0",
     *                                 @"error": @0,
     *                                 @"desc": @"SUCCESS",
     *                                 @"result":交易hash,
     *                                 @"id":callbackDic[@"id"]
     *                                 };
     * [webView sendMessageToWeb:callBackMessage];
     *
     * 注意:进入页面或者返回上一页面时,清除保存的密码等信息
}];
```

##### action: sendMessageToWeb

```
NSDictionary *params = @{@"action":@"",
                         @"version":@"v1.0.0",
                         @"error":@0,
                         @"desc":@"SUCCESS",
                         @"result":@""
                         };
[webView sendMessageToWeb:params];
```

## ONTID

- ONT ID 认证

```
[webView setAuthenticationCallback:^(NSDictionary * callbackDic) {
       NSDictionary * params = callbackDic[@"params"];
       NSString * subaction = params[@"subaction"];
       NSArray * allSubaction = @[@"getRegistryOntidTx",@"submit",@"getIdentity"];
       NSInteger index = [allSubaction indexOfObject:subaction];

       switch (index) {
       case 0:
       /* TODO
        * 1.发送保存的ONT_ID交易Hash到webView
        * NSDictionary *params = @{
        *                        @"action":@"authentication",
        *                        @"version":callbackDic[@"version"],
        *                        @"result":
        *                            @{
        *                                @"subaction":@"getRegistryOntidTx",
        *                                @"ontid":ontid,
        *                                @"registryOntidTx":ONT_ID交易Hash
        *                              },
        *                        @"id":callbackDic[@"id"],
        *                        @"error":@0,
        *                        @"desc":@"SUCCESS",
        *                        };
        *  [webView sendMessageToWeb:params];
        */
        break;
        case 1:
        /* TODO
         * 1.将H5返回的内容发到钱包后台
         * 2.将发送结果进行返回
         * NSDictionary *params = @{
         *                        @"action":@"authentication",
         *                        @"version":callbackDic[@"version"],
         *                        @"result":@1,
         *                        @"id":callbackDic[@"id"],
         *                        @"error":@0,
         *                        @"desc":@"SUCCESS",
         *                        };
         *  [webView sendMessageToWeb:params];
         */
         break;
         case 2:
         /* TODO
          * 1.发送ONT_ID到webView
          * NSDictionary *params = @{
          *                        @"action":@"authentication",
          *                        @"version":callbackDic[@"version"],
          *                        @"result":ontid,
          *                        @"id":callbackDic[@"id"],
          *                        @"error":@0,
          *                        @"desc":@"SUCCESS",
          *                        };
          *  [webView sendMessageToWeb:params];
          */
          break;
          default:
          break;
          }
}];
```

- ONT ID 授权

  ```
  [webView setAuthorizationCallback:^(NSDictionary *callbackDic) {
          NSDictionary * params = callbackDic[@"params"];
          NSString * subaction = params[@"subaction"];
          NSArray  * allSubaction = @[@"exportOntid",@"deleteOntid",@"decryptClaim",
                                      @"getAuthorizationInfo",@"requestAuthorization"];
          NSInteger index = [allSubaction indexOfObject:subaction];

          switch (index) {
          case 0:
          /* TODO
           * 1.弹出密码框，校验ONT ID的密码
           * 2.将身份导出成WIF格式
           */
           break;
           case 1:
           /* TODO
            * 1.弹出密码框，校验ONT ID的密码
            * 2.密码成功后删除本地ONT ID，关闭页面
            */
            break;
            case 2:
            /* TODO
             * 1.弹出密码框，校验ONT ID的密码
             * 2.解密，得到解密结果
             * 3.将结果进行返回
             * NSDictionary *params =   @{
             *                          @"action":@"authorization",
             *                          @"version":callbackDic[@"version"],
             *                          @"result":解密结果,
             *                          @"id":callbackDic[@"id"],
             *                          @"error":@0,
             *                          @"desc":@"SUCCESS",
             *                          };
             * [webView sendMessageToWeb:params];
             */
             break;
             case 3:
             /* TODO
             * 1.将保存数据中的subaction改成getAuthorizationInfo
             * 2.将结果进行返回
             * NSDictionary * resultDic = [[NSUserDefaults standardUserDefaults]
             *                            valueForKey:ONTIDAUTHINFO];
             * NSDictionary * resultParams = resultDic[@"params"];
             * NSMutableDictionary * resultParamsChange = [NSMutableDictionary
             *                            dictionaryWithDictionary:resultParams];
             * resultParamsChange[@"subaction"] = @"getAuthorizationInfo";
             * NSDictionary *params = @{
             *                        @"action":@"authorization",
             *                        @"version":callbackDic[@"version"],
             *                        @"result":resultParamsChange,
             *                        @"id":callbackDic[@"id"],
             *                        @"error":@0,
             *                        @"desc":@"SUCCESS",
             *                        };
             *  [webView sendMessageToWeb:params];
             */
             break;
             case 4:
             /* TODO
              * 1.保存收到的数据,并跳转到授权界面
              * [webView setURL:url];
              */
              break;
              default:
              break;
              }
  }];
  ```


## 如何使用

- 将 CyanoRNWebView.framework 导入项目

- # import "RNJsWebView.h"

##### 方式一:代码导入

- 使用pod导入三方库

```
pod 'MBProgressHUD', '~> 1.1.0'

pod 'Masonry', '~> 1.1.0'

pod 'IQKeyboardManager' ,'~> 6.0.6'
```

- 导入 Third 文件夹
- 导入 Tools 文件夹
- 导入  js 蓝色文件夹
- 导入 cyano.bundle

##### 方式二:静态库导入

- 导入  js 蓝色文件夹
- 导入 cyano.bundle

##### *注意事项:SDK未做相机权限的相关设置,使用前需先获取相机权限*

## 使用示例

启动ONT ID界面，ONT ID的私钥，密码和ONT 默认钱包 钱包一致，在进入界面之前需要检查是否已创建好钱包。

ONT ID只允许创建一个

```
NSString * ontIdString = [[NSUserDefaults standardUserDefaults] valueForKey:DEFAULTONTID];
if ([Common isBlankString:ontIdString]) {
    // 传入钱包字典
    NSString *jsonStr = [[NSUserDefaults standardUserDefaults] valueForKey:ASSET_ACCOUNT];
    if (!jsonStr) {
    [Common showToast:@"No Wallet"];
    return;
    }
    NSDictionary *dict = [Common dictionaryWithJsonString:jsonStr];
    ONTIdPreViewController * vc = [[ONTIdPreViewController alloc]init];
    vc.walletDic = dict;
    [self.navigationController pushViewController:vc animated:YES];
}else{
    ONTOAuthSDKViewController * vc= [[ONTOAuthSDKViewController alloc]init];
    [self.navigationController pushViewController:vc animated:YES];
}
```

##

## DEMO

#### [cyano-ios](https://github.com/ontio-cyano/cyano-ios.git)

## 下载地址

https://github.com/ontio-cyano/cyano-ios-sdk
