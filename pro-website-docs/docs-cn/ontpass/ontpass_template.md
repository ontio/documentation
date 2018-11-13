[English](../en/thirdparty_kyc.md) / 中文

<h1 align="center">ONTPass 认证服务索引 </h1>
<p align="center" class="version">Version 0.9.0 </p>


本文注册登记了所有在ONTPass上提供认证服务的可信声明定义，为认证需求方提供技术接入指导。

* ONTPass：基于本体区块链的去中心化身份交易平台，ONTPass主要用于协同用户和需求方进行数据交换，数据全程被加密，ONTPass并不会触碰用户隐私数据。
* TrustAnchor：信任锚Trust Anchor是指在本体生态上提供认证服务的合作方，其可能是政府机关、大学、银行、第三方认证服务机构（比如CA机构）、生物识别科技公司等等。


## 已注册可信声明

| 可信声明标识     |     说明 |   签发者   | 
| :--------------: | :--------:| :------: |
|    claim:email_authentication|   个人邮箱认证可信声明|  ONTO  |
|    claim:mobile_authentication|   个人手机认证可信声明|  ONTO  |
|    claim:cfca_authentication|   中国公民实名认证可信声明|  CFCA |
|    claim:sensetime_authentication|   中国公民实名认证可信声明|  商汤SenseTime |
|    claim:idm_passport_authentication|   全球用户个人护照认证可信声明|  IdentityMind |
|    claim:idm_idcard_authentication|    全球用户个人身份证件认证可信声明|  IdentityMind |
|    claim:idm_dl_authentication|    全球用户个人驾照认证可信声明|  IdentityMind |
|    claim:github_authentication|   Github社媒认证可信声明|  Github |
|    claim:twitter_authentication|   Twitter社媒认证可信声明|  Twitter |
|    claim:linkedin_authentication|   Linkedin社媒认证可信声明| Linkedin |
|    claim:facebook_authentication|   Facebook社媒认证可信声明|  Facebook |


## 标准认证模板


| 认证模板类型 | 认证模板标识 | 认证模板描述 | 认证模板对应的可信声明模板标识 | 授权逻辑规则 |
| :--------: | :--------:|:---------:|:--------: | :--------:|
| 社交媒体认证    |   authtemplate_social01 |  有关用户各种社交媒体的基本信息认证  | claim:github_authentication<br><br>claim:twitter_authentication<br><br>claim:facebook_auuthentication<br><br>claim:linkedin_authentication    |   任选其一 |
| 联系信息认证    |   authtemplate_contact01 |  有关全球用户的邮箱信息认证  | claim:email_authentication |   必选 |
| 联系信息认证    |   authtemplate_contact02 |  有关全球用户的手机号信息认证  | claim:mobile_authentication |   必选 |
| kyc认证    |   authtemplate_kyc01 |  有关全球用户基本个人信息的认证  | claim:idm_passport_authentication<br><br>claim:idm_idcard_authentication<br><br>claim:idm_dl_authentication |   任选其一 |
| kyc认证    |   authtemplate_kyc02 |  有关中国用户的实名信息认证  | claim:cfca_authentication |   必选 |




## 附录：

### 可信声明规范

可信声明使用JSON Web Token的扩展格式来表示，基本结构由三部分组成：Header，Payload，Signature。我们通过在最后附加区块链证明Blockchain_Proof来扩展JWT格式，一个典型的完整可信声明被组织为

	Header.Payload.Signature.Blockchain_Proof


**Header**
Header部分定义了该可信声明的格式类型，使用的签名方案以及用于验证签名的公钥id

```
{
    "alg": "ES256",
    "typ": "JWT-X",
    "kid": "did:ont:TRAtosUZHNSiLhzBdHacyxMX4Bg3cjWy3r#keys-1"
}
```


**Payload**

Payload部分定义了可信声明的基本信息及TrustAnchor认证的内容

```
{
    "ver": "0.7.0",
    "iss": "did:ont:TRAtosUZHNSiLhzBdHacyxMX4Bg3cjWy3r",
    "sub": "did:ont:SI59Js0zpNSiPOzBdB5cyxu80BO3cjGT70",
    "iat": 1525465044,
    "exp": 1530735444,
    "jti":"4d9546fdf2eb94a364208fa65a9996b03ba0ca4ab2f56d106dac92e891b6f7fc",
    "@context":"https://example.com/template/v1",
    "clm":{
        "Name": "Bob Dylan",
        "Age": "22"
    },
    "clm-rev":{ 
        "typ": "AttestContract",
        "addr": "8055b362904715fd84536e754868f4c8d27ca3f6"
    }
}
```

- **ver** 指明可信声明版本
-  **iss** 可信声明签发者的ONT ID
-  **sub** 可信声明接收者的ONT ID
-  **iat** unix时间戳格式的创建时间
-  **exp** unix时间戳格式的过期时间
-  **jti** 可信声明的唯一标识符
-  **@context** 可信声明模板标识
-  **clm** 指明了TrustAnchor认证的可信声明内容
-  **clm-rev** 指明了可信声明吊销方式。


**Signature**

在构造完Header和Payload部分后，签名根据JWS标准来计算。

- 根据JWS规范对Header和Payload部分进行序列化，作为签名的输入
	
	sig := sign(Base64URL(header) || . || Base64URL(payload))


- 根据Header部分指定的特定签名方案来计算签名。

- 对签名进行编码
	
	signature := Base64URL(sig).


**Blockchain Proof**

签发者会将该可信声明进行区块链存证，并根据存证交易获取到区块链证明merkleproof

```
{
    "Type":"MerkleProof",
    "TxnHash":"c89e76ee58ae6ad99cfab829d3bf5bd7e5b9af3e5b38713c9d76ef2dcba2c8e0",
    "ContractAddr": "8055b362904715fd84536e754868f4c8d27ca3f6",
    "BlockHeight":10,
    "MerkleRoot":"bfc2ac895685fbb01e22c61462f15f2a6e3544835731a43ae0cba82255a9f904",
    "Nodes":[{
    	"Direction":"Right",
        "TargetHash":"2fa49b6440104c2de900699d31506845d244cc0c8c36a2fffb019ee7c0c6e2f6"
    }, {
        "Direction":"Left",
        "TargetHash":"fc4990f9758a310e054d166da842dab1ecd15ad9f8f0122ec71946f20ae964a4"
    }]
}
```

- **Type** 固定值"MerkleProof"
- **TxnHash** 将可信声明id存证在合约里的交易hash值
- **ContractAddr** 存证合约的地址
- **BlockHeight** 存证交易对应的区块高度
- **MerkleRoot** 该区块高度的区块对应的Merkle树根
- **Nodes** Merkle树证明的证明路径


**可信声明传输**

传输时参考JWT规范使用base64编码后的格式。场景方获取到的可信声明也按照如下格式组织：

	BASE64URL(Header) || '.' || BASE64URL(Payload) || '.' || BASE64URL(Signature)  '.' || BASE64URL(blockchain_proof) 

**可信声明示例**

下面是一个不带merkleproof的个人邮箱证明可信声明示例
	
	eyJraWQiOiJkaWQ6b250OkFScjZBcEsyNEVVN251Zk5ENHMxU1dwd1VMSEJlcnRwSmIja2V5cy0xIiwidHlwIjoiSldULVgiLCJhbGciOiJPTlQtRVMyNTYifQ==.eyJjbG0tcmV2Ijp7InR5cCI6IkF0dGVzdENvbnRyYWN0IiwiYWRkciI6IjgwNTViMzYyOTA0NzE1ZmQ4NDUzNmU3NTQ4NjhmNGM4ZDI3Y2EzZjYifSwic3ViIjoiZGlkOm9udDpBVTFvTHBLMTRFQjdudTdORDRzMTJXcHdVUUhCT3J0MU5oIiwidmVyIjoidjEuMCIsImNsbSI6eyJJc3N1ZXJOYW1lIjoiaG90bWFpbCIsIkVtYWlsIjoiMTgydGVzdEBob3RtYWlsLmNvbSJ9LCJpc3MiOiJkaWQ6b250OkFScjZBcEsyNEVVN251Zk5ENHMxU1dwd1VMSEJlcnRwSmIiLCJleHAiOjE1NzA3ODQ1MjUsImlhdCI6MTUzOTI0ODUyNywiQGNvbnRleHQiOiJjbGFpbTplbWFpbF9hdXRoZW50aWNhdGlvbiIsImp0aSI6Ijc4YjNjZDYzMTdiNTI0MjAyNjdmMWI0M2VhOWMyYTk5NDhmNTY4YzMwNzBlMGQ5MDljMjY0ODRjMGE4YzE2YjkifQ==.AQCIG9ugLuqxBwU2ujISsA84QSItvH5gDmJzescmv+LogE8DjEt7UWjWscssshZWTKUr0UO9eLIg9yf0jva344U=


先按照'.'分割，再对每部分用标准base64解码后获取到的信息应该如下：

header：
	
	{"kid":"did:ont:ARr6ApK24EU7nufND4s1SWpwULHBertpJb#keys-1","typ":"JWT-X","alg":"ONT-ES256"}


payload：
	
	{"clm-rev":{"typ":"AttestContract","addr":"8055b362904715fd84536e754868f4c8d27ca3f6"},"sub":"did:ont:AU1oLpK14EB7nu7ND4s12WpwUQHBOrt1Nh","ver":"v1.0","clm":{"IssuerName":"hotmail","Email":"182test@hotmail.com"},"iss":"did:ont:ARr6ApK24EU7nufND4s1SWpwULHBertpJb","exp":1570784525,"iat":1539248527,"@context":"claim:email_authentication","jti":"78b3cd6317b52420267f1b43ea9c2a9948f568c3070e0d909c26484c0a8c16b9"}

signature：
	
	AQCIG9ugLuqxBwU2ujISsA84QSItvH5gDmJzescmv+LogE8DjEt7UWjWscssshZWTKUr0UO9eLIg9yf0jva344U=



有关可信声明的详细定义及规范可参考：[可信声明协议规范](https://ontio.github.io/documentation/claim_spec_en.html)

