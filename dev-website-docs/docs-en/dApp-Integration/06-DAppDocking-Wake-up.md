


A specially adapted wallet app can support wake-up by other apps in the phone. This document will introduce features such as smart contract (including payment) if you log in through the Wakeup Wall App in the app.

## Description

##### DApp
Decentralized application

##### DApp Background
Mainly provides the following features:
- Corresponding DApp operations, generating corresponding login parameters or calling parameters of smart contracts.
- Synchronize information on the chain to get results of logging in or calling smart contracts

##### Smart Contract
Ontology Smart Contract is a complete system that combines versatility, lightweight, high availability, concurrency, multi-language, cross-contract, and cross-virtual machine.

For DApp, smart contracts implement all or part of their business logic

##### Provider
Provide signatures, pre-execute transactions, execute transactions, etc. to interact with the chain, in the current document refers to the two wallets currently supported.
- ONTO [download](https://onto.app)
- Cyano [download](http://101.132.193.149/files/app-debug.apk)

##### demo
We provide a Demo app that wakes up a specific wallet for reference. [wake up demo](https://github.com/ontio-cyano/android-app-demo)

## Development

DApp development requires two processes in the wake-up function:
- log in
- Call smart contract

The login process does not need to be explained too much. The process of calling the smart contract can realize various business logics of DApp according to different methods of calling different contracts. With the game example, it can realize different businesses such as purchase, sale and lease.

### log in

The login process is shown below

![wakeup-login](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/wakeupLogin.png)

1. DApp sends login information built by DApp background service to specific Provider (wallet)
2. The Provider signs the login information and transmits the relevant data to the return address set in the previous login information.
3. The DApp background verification signature is passed, and the DApp login is notified after the success.

#### Login Data

When the DApp needs to log in, it gets the login data from the DApp background and sends it to the specific Provider.

Login data example:
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

##### Specific implementation process

0. Determine if the Cyano App is installed locally, for example:
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


1. The DApp sends the login information built by the DApp backend service to a specific Provider (wallet), for example:
```
    String data = "{\"action\":\"login\",\"id\":\"10ba038e-48da-487b-96e8-8d3b99b6d18a\",\"version\":\"v1.0.0\",\"params\":{\"type\":\"ontid or account\",\"dappName\":\"dapp Name\",\"dappIcon\":\"dapp Icon\",\"message\":\"helloworld\",\"expire\":1546415363,\"callback\":\"http://127.0.0.1:80/login/callback\"}}"; //此处就是将之前的登录数据拼接后的状态。

    String sendData = Base64.encodeToString(Uri.encode(data).getBytes(), Base64.NO_WRAP);
    Intent intent = new Intent("android.intent.action.VIEW");
    intent.setData(Uri.parse("ontprovider://ont.io?param=" + sendData ));
    intent.addCategory("android.intent.category.DEFAULT");
    startActivity(intent);
```

2. The Provider signs the login information and transmits the relevant data to the return address set in the previous login information. This step does not require the DApp developer to execute.

3. The DApp background verification signature is passed, and the DApp login is notified after the success.

Signature verification method:
* [java sdk Signature check](https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/interface.md#verify-signature)
* [ts sdk Signature check](https://github.com/ontio/ontology-ts-sdk/blob/master/test/ecdsa.crypto.test.ts)


### Calling the contract

Call the contract process as shown below

![wakeup-login](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/wakeupInvoke.png)

1. Build call contract data to a specific Provider
2. Provider signature, pre-execution, and finally sent to the chain (this step does not require DApp development)
3. Provider sends the transaction hash to the DApp background
4. DApp background Query contract execution results from the chain
5. The DApp backend feeds the results back to the DApp and presents it to the user.

#### Calling contract data

Call contract data example
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
##### Specific implementation process

0. Check if a specific Provider is installed, refer to [Login] (#Login)
1. The DApp background puts the transaction content in the qrcodeUrl link. For details, please refer to [Cyano QR Code](https://github.com/ontio-cyano/CEPs/blob/master/CEPS/CEP1.mediawiki#Invoke_a_Smart_Contract-2)

 Splicing the content and starting the transaction, for example:

```
    String data="{\"action\":\"invoke\",\"version\":\"v1.0.0\",\"id\":\"10ba038e-48da-487b-96e8-8d3b99b6d18a\",\"params\":{\"login\":true,\"qrcodeUrl\":\"http://101.132.193.149:4027/qrcode/AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ\",\"message\":\"will pay 1 ONT in this transaction\",\"callback\":\"http://101.132.193.149:4027/invoke/callback\"}}";


    String sendData = Base64.encodeToString(Uri.encode(data).getBytes(), Base64.NO_WRAP);
    Intent intent = new Intent("android.intent.action.VIEW");
    intent.setData(Uri.parse("ontprovider://ont.io?param=" + sendData ));
    intent.addCategory("android.intent.category.DEFAULT");
    startActivity(intent);
```

2. Provider signature, pre-execution, and finally sent to the chain (this step does not require DApp development)
3. The Provider sends the transaction hash to the DApp background. This step is implemented according to the DApp specific situation.
4. DApp background Query contract execution results from the chain
    * [java sdk Transaction event query method](https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/basic.md)
    * [ts sdk Transaction event query method](https://github.com/ontio/ontology-ts-sdk/blob/master/test/websocket.test.ts)
5. The DApp background feeds the results back to the DApp and presents it to the user. This step is implemented according to the specific situation of the DApp.
