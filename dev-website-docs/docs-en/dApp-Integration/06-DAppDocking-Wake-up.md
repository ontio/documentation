


A specially adapted wallet app can support wake-up feature by other mobile apps. This document will introduce features such as logging in through apps that can wake up wallet and calling smart contract (including payment).

## Description

##### dApp
Decentralized application

##### dApp Backend
Mainly provides the following features:
- Corresponding dApp operations, generating corresponding login parameters or parameters of calling smart contracts.
- Synchronizing information on the chain and get results of login or calling smart contracts

##### Smart Contract
Ontology Smart Contract is a complete system that combines versatility, lightweight, high availability, concurrency, multi-language, cross-contract, and cross-virtual machine.

For dApps, smart contracts implement all or part of their business logic

##### Provider
Providing signatures, pre-executing transactions, and executing transactions, etc. to interact with the chain. In the current document, it only refers to the two wallets currently supported.
- ONTO [download](https://onto.app)
- Cyano [download](http://101.132.193.149/files/app-debug.apk)

##### Demo
We provide a demo app that wakes up a specific wallet for reference. [wake up demo](https://github.com/ontio-cyano/android-app-demo)

## Development

DApp development requires two processes in the wake-up feature:
- Login
- Calling smart contract

The login process does not need to be explained at length. The process of calling smart contract can realize various business logics of dApps according to different methods of calling different contracts. Take gaming dApps, they can support different businesses such as purchase, sale and lease.

### Login

The login process is shown below

![wakeup-login](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/wakeupLogin.png)

1. dApp sends login information created by dApp backend service to specific Provider (wallet)
2. The Provider signs the login information and transmits the relevant data to the return address set in the previous login information.
3. The dApp backend verifies the signature, and the dApp login success is notified after verification.

#### Login Data

When the dApp needs to log in, it gets the login data from the dApp backend and sends it to a specific Provider.

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


1. The dApp sends the login information created by dApp backend service to a specific Provider (wallet), for example:
```
    String data = "{\"action\":\"login\",\"id\":\"10ba038e-48da-487b-96e8-8d3b99b6d18a\",\"version\":\"v1.0.0\",\"params\":{\"type\":\"ontid or account\",\"dappName\":\"dapp Name\",\"dappIcon\":\"dapp Icon\",\"message\":\"helloworld\",\"expire\":1546415363,\"callback\":\"http://127.0.0.1:80/login/callback\"}}"; //此处就是将之前的登录数据拼接后的状态。

    String sendData = Base64.encodeToString(Uri.encode(data).getBytes(), Base64.NO_WRAP);
    Intent intent = new Intent("android.intent.action.VIEW");
    intent.setData(Uri.parse("ontprovider://ont.io?param=" + sendData ));
    intent.addCategory("android.intent.category.DEFAULT");
    startActivity(intent);
```

2. The Provider signs the login information and transmits the relevant data to the return address set in the previous login information. This step does not require the dApp developer to execute.

3. The dApp backend verifies the signature, and the dApp login success is notified after verification.

Signature verification method:
* [java sdk Signature verification](https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/interface.md#verify-signature)
* [ts sdk Signature verification](https://github.com/ontio/ontology-ts-sdk/blob/master/test/ecdsa.crypto.test.ts)


### Calling contract

Contract calling process is shown below

![wakeup-login](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/wakeupInvoke.png)

1. Create contract calling data and send the data to a specific Provider
2. Provider signs and pre-executes the contract, and finally send it to the chain (this step does not require dApp development)
3. Provider sends the transaction hash to the dApp backend
4. The dApp backend search the contract execution results from the chain
5. The dApp backend feeds the results back to the dApp and presents it to users.

#### Contract calling data

Contract calling data example
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
1. The dApp backend puts the transaction data in the qrcodeUrl link. For details, please refer to [Cyano QR Code](https://github.com/ontio-cyano/CEPs/blob/master/CEPS/CEP1.mediawiki#Invoke_a_Smart_Contract-2)

 Splicing the data and starting the transaction, for example:

```
    String data="{\"action\":\"invoke\",\"version\":\"v1.0.0\",\"id\":\"10ba038e-48da-487b-96e8-8d3b99b6d18a\",\"params\":{\"login\":true,\"qrcodeUrl\":\"http://101.132.193.149:4027/qrcode/AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ\",\"message\":\"will pay 1 ONT in this transaction\",\"callback\":\"http://101.132.193.149:4027/invoke/callback\"}}";


    String sendData = Base64.encodeToString(Uri.encode(data).getBytes(), Base64.NO_WRAP);
    Intent intent = new Intent("android.intent.action.VIEW");
    intent.setData(Uri.parse("ontprovider://ont.io?param=" + sendData ));
    intent.addCategory("android.intent.category.DEFAULT");
    startActivity(intent);
```

2. Provider signs and pre-execute the contract, and finally send the data to the chain (this step does not require DApp development)
3. The Provider sends the transaction hash to the dApp backend. This step is implemented according to the actual condition of the dApp.
4. The dApp backend checks contract execution results from the chain
    * [java sdk Transaction event query method](https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/basic.md)
    * [ts sdk Transaction event query method](https://github.com/ontio/ontology-ts-sdk/blob/master/test/websocket.test.ts)
5. The dApp backend feeds the results back to the dApp and presents it to users. This step is implemented according to the actual condition of the dApp.
