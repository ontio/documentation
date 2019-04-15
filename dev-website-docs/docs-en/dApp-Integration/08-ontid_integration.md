


The ONTID open platform is a custodian ONTID service for users of Ontology blockchain and provides one-stop digital identity login authorization, user assets management, payment, and contract invocation.


## Preparation

ONTID Login for website applications is the ONTID authorization login system that is similar to OAuth2.0 protocol standards.

Before the ONTID authorized login integration, the website application registers the ONTID on the ONTID open platform and obtains the corresponding ONTID and ```PrivateKey```. After the application for ONTID is approved, it can start the access process.

## Sign-In with Ontology

ONTID authorization login is to allow users to securely login to third-party applications or websites using ONTID.

After a ONTID user authorizes the login to the third-party application, the third party can obtain the user's interface call credentials (```access_token```), which is used to access the ONTID open platform.

The ONTID authorization login process is:


![ontid login](https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/ontid-login-en.jpg) 



1. The website application's front end opens the ONTID login page.
2. The user enters the username and password on the login page of the ONTID.
3. The ONTID open platform returns ```access_token```, ```refresh_token``` and ```JWT token``.
4. The ONTID open platform front end closes the login page and returns ```JWT token``` to the front end of the application.
5. The website application's front end sends ```JWT token``` to its backend.
6. After backend verifies the issuer of ```JWT token``` successfully, the user information in ```refresh_token``` is obtained, which is generally non-sensitive information, such as user's ONTID and mobile phone number.
7. Access the ONTID open platform interface using ```access_token```.

The data of ```JWT token``` is encrypted with the public key of the website application, and the data format after decryption is as follows:
 
```
 {
    "access_token" :  "JWT token",
    "refresh_token" : "JWT token"
 }
```
> Payload in ```JWT token``` needs to add ```content```:
  
```
  
    "content": {
        "type": "refresh_token", // or access_token
        "phone": "+86*1234567890",
        "ontid": "did:ont:Axxxxxxxxxxxxxxxxx",
        ......
    }
    
```
   
 | Param     |     Type |   Description   |
 | :--------------: | :--------:| :------: |
 |    access_token |   String | ```JWT token```, ```Header```  need to fill ```access_token``` when the user accesses the interface |
 |    refresh_token |   String | ```JWT token``` that is used when refreshing ```access_token``` |
 
 

### JWT Token 

 ```JWT``` contains three parts:

```
  Base64(Header).Base64(Payload).Base64(Signature)	 
```


Each part is based on the ```Base64Url``` format, separated by ``` . ```.

#### Header
```
{
  "alg": "ES256",
  "typ": "JWT"
}
```


The ```alg``` attribute represents the signature algorithm. The default is ```HMAC SHA256``` (written as HS256), but we use ```ES256``` (```ECDSA``` using ```P-256``` curve and ```SHA-256``` hash algorithm); 

The ```typ``` attribute indicates the type of the token, regarding ```JWT token``` as ```JWT``.

#### Payload

Officially specified 7 fields, optional. We use the following required fields:

  ```iss (issuer)```: issuer. Here is the ONTID of the ONTID open platform.
  
  ```exp (expiration time)```: ```token``` Expiration time.
  
  ```aud (audience)```: Audience. Here is the application's ONTID.
  
  ```iat (Issued At)```: Issuing time
  
  ```jti (JWT ID)```: id. The certificate saved by the ONTID open platform.
  
> In addition to the above fields, there are some custom fields for storing user information, which cannot be sensitive information. 

#### Signature

```Signature```: It is the signature to the first two parts to prevent data tampering.

The signature generation rules are:

1. ```Header``` and ```Payload``` Splicing into parameter strings in ascending alphabetical order, with & to connect, for example:

```Header``` : alg=ES256&typ=JWT

```Payload```: aud=Website Application ONTID&exp=20190310&iat=20190301......

2. Convert the above two strings into the ```base64url``` format and use ```.``` to connect to get the template string.
3. The target string is signed by the private key of ONTID open platform and the signature algorithm ```ES256```.

After the website application gets ```JWT token```, generate the target string and verify the signature according to the above rules.



### Application integration guide


1. Import ```OntidSignIn.js``` in page.
2. Add a meta tag to the page and fill application's ONTID.```<meta name="ontid-signin-client_ontid" content="YOUR_CLIENT_ONTID.apps.ontid.com">```
3. Adds the `Sign In` button in page.``` <div class="ontid-signin" data-onsuccess="onSignIn"></div> ```
4. After the login is successful, the callback onSignIn is triggered, and the ```JWT token``` will be sent to the website application backend.

```
    //get JWT token
    function onSignIn(googleUser) {
      var token = ontidUser.getAuthResponse().token;
      ...
    }
    //sent to the  Website Application back end
    var xhr = new XMLHttpRequest();
    xhr.open('POST', 'https://yourbackend.example.com/tokensignin');
    xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
    xhr.onload = function() {
      console.log('Signed in as: ' + xhr.responseText);
    };
    xhr.send('idtoken=' + id_token);
```
5. Website application backend verifies ``` JWT token ```


## User authorization

Some interfaces require the user to authorize the website application backend to access the user's data. The default authorized interface is accessible without authorization.



## Payment/invoke contract interface


The ONTID Payment process is:

![ontid payment](https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/ontid-payment-en.png) 


1. The application sends a payment request to the ONT ID open platform. The ONT ID open platform returns ```orderid``` as the serial number.
2. The application opens the payment page with the parameter ```orderid``` and the redirect address ```redirect_uri``` of the application's frontend.
3. The user confirms the request and sends a request to the ONTID open platform.
4. The ONTID open platform processes the request and notifies the result to the application.
5. Return the result to the ONTID frontend at the same time.
6. The ONTID frontend is redirected to ```redirect_uri```

### The data format of invoking a smart contract

```
url：/api/v1/ontid/request/order

method：POST

{
   "data" :  "JWT token: Base64(Header).Base64(Payload).Base64(Signature)",
   "user": "did:ont:AcrgWfbSPxMR1BNxtenRCCGpspamMWhLuL"
}

```

Response:

```

{
  "action" : "requestOrder",
  "error" : 0,
  "desc" : "SUCCESS",
  "result" : {
    "invoke_token" : "eyJ0eXAiOiJKV1QiLCJhbGciOiJFUzI1NiJ9.eyJhdWQiOiJkaWQ6b250OkFOUzlKbm9FUjVXcWNFNzVqSGVZWkF1U1dSdlRqUDY5V0giLCJpc3MiOiJkaWQ6b250OkFhdlJRcVhlOVByYVY1dFlnQnF2VjRiVXE4TFNzdmpjV1MiLCJleHAiOjE1NTM5NTkwMjAsImlhdCI6MTU1Mzg3MjYyMCwianRpIjoiYzkyZjNiMTdkN2E2NGZjZjg2MGI5M2I4ODgwMjVkNTMiLCJjb250ZW50Ijp7InR5cGUiOiJhY2Nlc3NfdG9rZW4iLCJvbnRpZCI6ImRpZDpvbnQ6QU5TOUpub0VSNVdxY0U3NWpIZVlaQXVTV1J2VGpQNjlXSCJ9fQ.MDFiYTllM2VkZjRhNjE2ODM1NjZjYThkMWVkM2UwNWUxNTg5MDEzMjEwYTFlOGU2ZDdiYmYxYjc0NTRmOGFlNzExMDQxZDUwMDExZWFkNDIwMmY3NDYyMTMyNGNlYjQ5NTA4NDM0YzRjOTI5Y2NmZTcyNzRmYTcxYTg2MzNkNTMzMw",
    "orderid" : "9892bcb698bb4cbd812c8b466d8ad432"
  },
  "version" : "v1"
}

```

#### Claims in Payload

```

{
		"invokeConfig": {
			"contractHash": "16edbe366d1337eb510c2ff61099424c94aeef02",
			"functions": [{
				"operation": "method name",
				"args": [{
					"name": "arg0-list",
					"value": [true, 100, "Long:100000000000", "Address:AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ", "ByteArray:aabb", "String:hello", [true, 100], {
						"key": 6
					}]
				}, {
					"name": "arg1-map",
					"value": {
						"key": "String:hello",
						"key1": "ByteArray:aabb",
						"key2": "Long:100000000000",
						"key3": true,
						"key4": 100,
						"key5": [100],
						"key6": {
							"key": 6
						}
					}
				}, {
					"name": "arg2-str",
					"value": "String:test"
				}]
			}],
			"payer": "AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ",
			"gasLimit": 20000,
			"gasPrice": 500
		},
        "app": {
            "name": "",
            "logo":"",
            "message": "",
            "ontid": "",
            "callback": "",
            "nonce": "123456"
        },
        "exp":1555041974000
}
```


| Param     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    invokeConfig |   String | Parameter configuration of invoking a contract |
|    invokeConfig.contractHash |   String | contract hash |
|    invokeConfig.functions |   List | The function list that calls the contract, currently only supports one function |
|    invokeConfig.payer |   String | Network fee payer |
|    invokeConfig.gasLimit |   int | Gas consumed to execute a contract |
|    invokeConfig.gasPrice |   int | Fixed value 500 |
|    app.ontid |   String | The application ontid |
|    app.callback |   String | callback  url |
|    app.nonce |   long | nonce |
|    exp |   long | expire |




## Query interface



```app_token``` is issued by Application.

```text
{
    "app": {
        "ontid": ""
    }
    "exp":1555041974000
}
```

| Param     |     Type |   Description   |
| :--------------: | :--------:| :------: |
|    app.ontid |   String |  |
|    exp |   long |  |

### Query Order

```text
url： /api/v1/provider/query/order

method：POST

{
    "app_token" :  "JWT token: Base64(Header).Base64(Payload).Base64(Signature)",
    "orderId":"a24d06ec89c3ce0c845eb719697d7843464f287e19a8c7e3d3ef614378e610b2"
}
```



response：

```
{
    action: "queryOrder",
    error: 0,
    desc: "SUCCESS",
    result: {
        note: null,
        wallet: "ASqT8qw2TMXCcTLQtpmbhTrpPhWDj8qCRV",
        txHash: "5b7fd0f390bd5cfa9dc5df2014712f7312857b1e303a367bb60100ac0e7d5fcf",
        orderId: "2ce54ba2db47b01a64d09b1ba1a848161f06361525bbd99b49c3ccf214c3259b",
        createTime: 1554992710000,
        appInfo: {
            name: "test",
            logo: "www.ont.io",
            callback: "http://139.219.136.188:11111/ontid/payment/callback",
            message: "test",
            nonce: "1ee1bdd6d50c433cb7429c0779c45384",
            ontid: "did:ont:AaqWLmN3LNqu8QFpuSnoK3QM4g5KC2ZSTC"
        },
        state: 6,
        event: null,
        user: "did:ont:AMxrSGHyxgnWS6qc1QjTNYeEaw3X3Dvzhf"
    },
    version: "v1"
}
```

| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    action|   String|    |
|    version|   String|    |
|    error|   int|    |
|    desc|   String|    |
|    result|   String| 	  |
|    result.note|   String| 	  |
|    result.wallet|   String| 	  |
|    result.txHash|   String| 	  |
|    result.orderId|   String| 	  |
|    result.createTime|   String| 	  |
|    result.appInfo|   String| 	 |
|    result.state|   String| 	0-init，1-ready;2-send success;3-send fail;4-tx success;5-tx fail;6-expire   |
|    result.event|   String| 	sc event  |
|    result.user|   String| 	user ontid  |

### Query order list

```text
url： /api/v1/provider/query/order/range

method：POST

{
    "app_token" :  "JWT token: Base64(Header).Base64(Payload).Base64(Signature)",
     "currentPage": 1,
     "size":10
}
```

response：

```
{
    action: "queryOrderRange",
    error: 0,
    desc: "SUCCESS",
    result: [
        {
            wallet: "ASqT8qw2TMXCcTLQtpmbhTrpPhWDj8qCRV",
            txHash: null,
            orderId: "532de576f7ba4c194e71c3994a452688b8d474760e844c3cf6d00f76c0a02fe9",
            createTime: 1555039410000,
            state: 0,
            user: "did:ont:AMxrSGHyxgnWS6qc1QjTNYeEaw3X3Dvzhf"
        }
     ],
    version: "v1"
}
```

| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    action|   String|    |
|    version|   String|    |
|    error|   int|    |
|    desc|   String|    |
|    result|   String| 	  |
|    result.wallet|   String| 	  |
|    result.txHash|   String| 	  |
|    result.orderId|   String| 	  |
|    result.createTime|   String| 	  |
|    result.state|   String| 	0-init，1-ready;2-send success;3-send fail;4-tx success;5-tx fail;6-expire  |
|    result.user|   String| 	user ontid  |



### Error Code


| Code     |     desc   |  
| :----: | :----: | 
| 00000	|	SUCCESS |
| 61001	|	PARAM_ERROR |
| 61002	|	ALREADY_EXIST |
| 61003	|	NOT_FOUND |
| 61004	|	NOT_EXIST
| 61005	|	NOT_PERMISSION
| 61006	|	NOT_REGISTRY
| 61007	|	EXPIRES
| 61008	|	REVOKED
| 61009	|	SERIALIZE_ERROR
| 61010	|	TIME_EXCEEDED
| 62001	|	VERIFY_FAIL
| 62002	|	CREATE_FAIL
| 62003	|	COMM_FAIL
| 62004	|	FILE_ERROR
| 62005	|	DB_ERROR
| 62006	|	SIG_VERIFY_FAILED
| 63001	|	INNER_ERROR
| 63002	|	EXCEPTION
| 63003	|	CODE_VERIFY_FAILED
| 63004	|	IDENTITY_VERIFY_FAILED
