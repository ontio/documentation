


The ONTID open platform is a custodian ONTID service for users of Ontology blockchain and provides one-stop digital identity login authorization, user assets management, payment, and contract invocation.


## Preparation

ONTID Login for website applications is the ONTID authorization login system that is similar to OAuth2.0 protocol standards.

Before the ONTID authorized login integration, the website application registers the ONTID on the ONTID open platform and obtains the corresponding ONTID and ```PrivateKey```. After the application for ONTID is approved, it can start the access process.

## Authorization Login

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

The data format of ```JWT token``` :
 
```
 {
    "access_token" :  "JWT token",
    "refresh_token" : "JWT token",
 }
```
 
 | Param     |     Type |   Description   |
 | :--------------: | :--------:| :------: |
 |    access_token |   String | ```JWT token```, ```Header```  need to fill ```access_token``` when the user accesses the interface |
 |    refresh_token |   String | ```JWT token``` that is used when refreshing ```access_token``` |
 
 
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


The ```alg``` attribute represents the signature algorithm. The default is ```HMAC SHA256``` (written as HS256); 

The ```typ``` attribute indicates the type of the token, regarding ```JWT token``` as ```JWT``.

#### Payload

Officially specified 7 fields, optional. We use the following required fields:

  ```iss (issuer)```: issuer. Here is the ONTID of the ONTID open platform.
  
  ```exp (expiration time)```: ```token``` Expiration time.
  
  ```aud (audience)```: Audience. Here is the application's ONTID.
  
  ```iat (Issued At)```: Issuing time
  
  ```jti (JWT ID)```: id. The certificate saved by the ONTID open platform.
  
> In addition to the above fields, there are some custom fields for storing user information, which cannot be sensitive information. Only ```refresh_token``` needs to add ```content```：

```

  "content": {
      "phone": "+86*1234567890",
      "ontid": "did:ont:Axxxxxxxxxxxxxxxxx",
      ......
  }
  
```

#### Signature

```Signature```: It is the signature to the first two parts to prevent data tampering.

The signature generation rules are:

1. ```Header``` and ```Payload``` Splicing into parameter strings in ascending alphabetical order, with & to connect, for example:

```Header``` : alg=ES256&typ=JWT

```Payload```: aud=Website Application ONTID&exp=20190310&iat=20190301......

2. Convert the above two strings into the ```base64url``` format and use ```.``` to connect to get the template string.
3. The target string is signed by the private key of ONTID open platform and the signature algorithm ```ES256```.

After the website application gets ```JWT token```, generate the target string and verify the signature according to the above rules.



## User authorization

Some interfaces require the user to authorize the website application backend to access the user's data. The default authorized interface is accessible without authorization.



## Payment/invoke contract interface


The ONTID Payment process is:

![ontid payment](https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/ontid-payment-en.png) 


1. The application sends a payment request to the ONT ID open platform. The header of the request contains ```access_token```. The ONT ID open platform verifies if the ```access_token``` is valid and returns ```requestId``` as the serial number.
2. The application opens the payment page with the parameter ```requestId``` and the redirect address ```redirect_uri``` of the application's frontend.
3. The user confirms the request and sends a request to the ONTID open platform.
4. The ONTID open platform processes the request and notifies the result to the application.
5. Return the result to the ONTID frontend at the same time.
6. The ONTID frontend is redirected to ```redirect_uri```

### The data format of invoking a smart contract



```
url：/api/v1/ontid/invoke

method：POST

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
            "createtime": 1552541388,
            "expire": 1552543312,
            "nonce": 5434536
        },
        "signature": ""
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
|    signature|   String | The application uses its private key to sign all parameters other than the signature, which will be verified when passed to the ONTID open platform. |


ONT/ONG transfer ```invokeConfig``` parameter filling example :
```
{
	"invokeConfig": {
		"contractHash": "0100000000000000000000000000000000000000", // ONG: 0200000000000000000000000000000000000000
		"functions": [{
			"operation": "transfer",
			"args": [{
					"name": "arg0-from",
					"value": "Address:AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ"
				}, {
					"name": "arg1-to",
					"value": "Address:AecaeSEBkt5GcBCxwz1F41TvdjX3dnKBkJ"
				},
				{
					"name": "arg2-amount",
					"value": 10000
				}
			]
		}],
		"payer": "AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ",
		"gasLimit": 20000,
		"gasPrice": 500
	}
}

```

## Other interface

The following interfaces ``` Header``` need to add ```access_token``` to access.


### Query asset balance


```
url：/api/v1/ontid/getbalance

method：POST

{
   	"ontid":"did:ont:AcrgWfbSPxMR1BNxtenRCCGpspamMWhLuL"
}
```
| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    ontid|   String|  ontid  |

Response：

```
{
    "action":"getbalance",
    "version":"1.0",
    "error":0,
    "desc":"SUCCESS",
    "result": {
       "ont": "100",
       "ong": "10000000000"
    }
}
```

| Field_Name|     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    action|   String|  action  |
|    version|   String|  version  |
|    error|   int|  error code  |
|    desc|   String|  error desc |
|    result|   String| 	result  |


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


## Examples

Website Application： ```http://172.168.3.47:81/#/```

ONTID Login： ```http://172.168.3.47/#/signIn```