
## Preparation

ONT ID Open Platform provides a variety of application APIs that help third-party applications quickly integrate. At present, the open platform provides third-party login, KYC, identity authentication, data storage and so on, and will continue to come up with more functions.

For third-party applications, please follow the following steps to start the services you need:

* 1. Download ONTO APP[https://onto.app](https://onto.app).

* 2. Use ONTO to create an ONT ID, and need to verify your email address.

* 3. Visit [https://developer.ontid.pro](https://developer.ontid.pro) to apply for application integration.

> **Please Note：** At present, the open platform is still under test, you can apply for opening by openplatform@ont.io .


Note: make sure the login page is accessable before docking:

* ONT ID login page: main network [https://signin.ont.io/#/](https://signin.ont.io/#/), test network [http://139.219.136.188:10390/ ](http://139.219.136.188:10390/)

## Quick docking

Docking includes front-end docking and server docking. The front-end docking is mainly to dock the login and payment page, and the back-end docking is mainly to dock order request and order inquiry.

* Front-end demo of third-party application: [http://139.219.136.188:10391/#/](http://139.219.136.188:10391/#/), [source code](https://github.com/ontio-Ontid/ontid-app-demo)
* Example of a third-party application server: [app-server source code](https://github.com/ontio-ontid/ontid-app-server)

### Front-end docks login page

There are two ways to integrate the ONT ID login: the first is to jump to a specific URL and the second is to integrate a plugin - `plugin.js` in the page. Here is the way to dock quickly. The way the page integrates plugins is described below.

```
 http://139.219.136.188:10390/signin?params={value}
 value = window.encodeURIComponent(appontid + '&' + appname + '&' + callback_url + '&' + lang)
 ```


 ```lang``` is the language of page, en for English, and zh for Chinese.
 ```appontid``` is the ontid of the application.
 ```appname``` is the name of the application.

> After a user logs in successfully, a returned login information will be attached as a parameter to the application callback address `callback_url` and passed to the application.
>
> The returned information is processed by `encodeURIComponent(JSON.stringify(response))`. The application needs to reverse the operation to get the actual returned information. The structure of the returned information is as follows:
>
> ```json
> {
> "access_token": "",
> "ontid": "",
> }
> ```
>
> The application can get the ```access_token``` to query the user's information. 

## ONT ID authorization login

The ONT ID authorization login allows the user to securely log in to the third-party application or website by ONT ID. After the user of ONT ID authorizes the login to the third-party application that has accessed the ONT ID, the third party can get the user's interface call credentials (```access_token```) and then call the ONT ID related interface through the ```access_token``` .

The overall process of the ONT ID authorization login mode:

![ontid login](https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/ontid-login-en.jpg)

1. The application's front-end opens a new window to load the login page of the ONT ID.
2. The user enters the username and password to log in on the login page of the ONT ID.
3. The ONT ID development platform returns ```access_token``` with ```JWT token``` format.
4. ONT ID Open platform front-end closes the login page and returns ```JWT token``` to the front-end of the application.
5. The application front-end sends ```JWT token``` to the back-end of the application.
6. Applicant's background verification After the issuer of ```JWT token``` succeeds, the user information in ```refresh_token``` is obtained, which is generally non-sensitive information, such as user user ONT ID, mobile phone number.
7. The request header attaches the ```access_token``` to access the interface of ONT ID open platform.


### How to integrate ONT ID login

You can use the quick docking method, see above for details.

Here is the way to use the JS plugin.

1. The page imports the ```plugin.js```

   > Currently `plugin.js` is placed on [github](<https://github.com/ontio-ontid/ontid-app-demo/blob/master/public/plugin.js>), and we will put it later on the CDN.

2. Add a meta tag to the page and fill in the application's ONT ID. ```<meta name="ontid-signin-client_ontid" content="YOUR_CLIENT_ONT ID.apps.ontid.com">```

3. Add the Sign In button for ONT ID in the page. ``` <div class="ontid-signin" data-onsuccess="onSignIn"></div> ```

4. After the login is successful, trigger the callback onSignIn and send ```JWT token``` to the back-end of the applicaton.

```
    //get JWT token
    function onSignIn(result) {
      const {access_token, ontid} = result
      ...
       //sent to the  Website Application back end
        var xhr = new XMLHttpRequest();
        xhr.open('POST', 'https://yourbackend.example.com/tokensignin');
        xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
        xhr.onload = function() {
          console.log('Signed in as: ' + xhr.responseText);
        };
        xhr.send('idtoken=' + id_token);
    }
```

5. Application's back-end verifies ``` JWT token ```

## ONT ID associates authorization login of third-parties

Third-party authorization logins such as WeChat, QQ, and Facebook are very popular methods for quick login, which simplifies the process of user login.

We provide the function that can associate third-party authorization login. In short, when the user logs in by third-party account such as WeChat, QQ, and facebook, the ONT ID account is automatically associated.

Now supported: WeChat and Facebook. All major third-party accounts will be supported in the future, such as QQ, Weibo, Google, Twitter, etc.

![V9GyCT.md.png](https://github.com/ontio/documentation/blob/master/pro-website-docs/assets/ONT%20ID%20OAuth2%20Flow-en.png?raw=true)


### Access procedures

#### 1. The application puts a login button on the page.

Place login buttons of third parties for different needs.

#### 2. Add a click event for the login button

Click the login button to jump to the following link

```
${ontid_host}/oauthmiddle?dapp_ontid=${dapp_ontid}&oauth_type=${provider}&redirect_url=${redirect_url}&lang=${lang}`
```

`ontid_host` ONT ID front-end project address. Test environment: `http://139.219.136.188:10390`, the official environment: `http://onchain.com`.

`dapp_ontid` The application's ONT ID.

`provider` a authorized third party. The optional values: `wechat`, `facebook`.

`redirect_url` The callback address of the application. After the authorization login, it will be redirected to the callback address, and the user's `access_token` will be attached at the end.

`lang` The language of the page. The optional values: `en`, `zh`

### 3. Verify the access_token obtained from the callback address

`access_token` is in the `JWT` format. It contains the signature of the ONT ID back-end. It is necessary to send `access_token` to the application's back-end  for verification. After the verification, the login process is completed.

For details of `access_token`, please refer to [JWT Token Format Description](https://dev-docs.ont.io/#/docs-cn/dApp-Integration/08-ontid_integration?id=jwt-token-%e6%a0%bc%e5%bc%8f%e8%af%b4%e6%98%8e%ef%bc%9f)

For the way to verify `access_token`, please refer to [java example](<https://github.com/ontio-ontid/ontid-appserver/blob/master/src/main/java/com/github/ontid_demo/Util/MyJWTUtils.java>)

### demo and examples

[demo source code](<https://github.com/ontio-ontid/oauth-login-demo>)

Link: http://139.219.136.188:10392

> To experience WeChat login, please open the link in WeChat
>
> To experience other login methods, open the link in your browser

## Error code

| Code | Description |
| :----: | :----: |
| 00000 | SUCCESS, success |
| 61001 | PARAM_ERROR, parameter error |
| 61002 | ALREADY_EXIST, already exist |
| 61003 | NOT_FOUND, not found |
| 61004 | NOT_EXIST, do not exist
| 61005 | NOT_PERMISSION, permission error
| 61006 | NOT_REGISTRY, not registered
| 61007 | EXPIRES, expired
| 61008 | REVOKED, cancelled
| 61009 | SERIALIZE_ERROR, serialization error
| 61010 | TIME_EXCEEDED, time exceeded
| 62001 | VERIFY_FAIL, identity verification failed
| 62002 | CREATE_FAIL, creation failed
| 62003 | COMM_FAIL, communication exception
| 62004 | FILE_ERROR, file operation exception
| 62005 | DB_ERROR, database operation error
| 62006 | SIG_VERIFY_FAILED, the verification failed
| 63001 | INNER_ERROR, internal exception
| 63002 | EXCEPTION, exception
| 63003 | CODE_VERIFY_FAILED, device code verification failed
| 63004 | IDENTITY_VERIFY_FAILED, authentication failed


## Common problem

#### JWT Token Format Description

 ```JWT``` contains three parts:

```
  Base64(Header).Base64(Payload).Base64(Signature)
```

Each part is in the ```Base64Url``` format, separated by ``` . ```.

* **Header**
```
{
  "alg": "ES256",
  "typ": "JWT"
}
```

The ```alg``` attribute represents the signature algorithm. The default is ```HMAC SHA256``` (written as HS256), but we use ```ES256``` (```ECDSA``` is to use ``` P-256``` curve and ```SHA-256``` hash algorithm).

The ```typ``` attribute represents the type of this token, and ```JWT token``` is uniformly written as ```JWT```.

* **Payload**

Officially specified 7 fields, optional. We use the following required fields:

  ```iss (issuer)```: issuer. Here is the ONT ID of the ONT ID open platform.

  ```exp (expiration time)```:```token``` Expiration time.

  ```aud (audience)```: audience. Here is the application's ONT ID.

  ```iat (Issued At)```: issue time

  ```jti (JWT ID)```: number. The certificate saved by the ONT ID open platform.

> Note that in addition to the above fields, there are some customized fields for storing user information, which cannot be sensitive information.

`content` : 自定义的字段，用于保存用户信息。现在的内容如下：
> ```json
> "content":{"type":"access_token","ontid":"did:ont:AMxrSGHyxgnWS6qc1QjTNYeEaw3X3Dvzhf"}
> ```

* **Signature**

The ```Signature``` part is the signature of the first two parts to prevent data tampering.

The signature generation rules:

1. ```Header``` and ```Payload``` are spliced ​​into parameter strings in ascending alphabetical order, with &, such as:

```Header``` : alg=ES256&typ=JWT

```Payload```: aud=Applicator ONT ID&exp=20190310&iat=20190301...

2. Convert the above two strings into ```base64url``` format and connect with ```.``` to get the template string.
3. Sign the target string using the private key of ONT ID open platform and the signature algorithm ```ES256```.

After the application gets ```JWT token```, the target string is generated according to the above rules and finally the application checks the signature.

####  How to verify the signature of the access_token

Please refer to [java example](<https://github.com/ontio-ontid/ontid-app-server/blob/master/src/main/java/com/github/ontid_demo/util/MyJWTUtils.java>)
