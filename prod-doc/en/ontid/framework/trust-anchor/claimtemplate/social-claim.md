## 社交媒体认证可信声明模板

#### 标准可信声明模板示例

**说明：标准可信声明由header，payload，signature，blockchain_proof四部分组成。组成格式为：header.payload.signature.blockchain_proof  针对自签的可信声明可以没有blockchain_proof**

#### Header 
```json
{
    "alg": "ONT-ES256",
    "typ": "JWT-X",
    "kid": "did:ont:TRAtosUZHNSiLhzBdHacyxMX4Bg3cjWy3r#keys-1"
}
```
#### Payload
```json
{
    "ver": "0.7.0",
    "iss": "did:ont:TRAtosUZHNSiLhzBdHacyxMX4Bg3cjWy3r",
    "sub": "did:ont:SI59Js0zpNSiPOzBdB5cyxu80BO3cjGT70",
    "iat": 1525465044,
    "exp": 1530735444,
    "jti":"4d9546fdf2eb94a364208fa65a9996b03ba0ca4ab2f56d106dac92e891b6f7fc",
    "@context":"https://example.com/template/v1",
    "clm":{
        "IdNumber": "510806199002122991",
        "Name": "Bob Dylan",
        "JobTitle": "SoftwareEngineer",
        "MonthlySalary": 3000.00,
        "HireDate": "2017-03-20"
    },
    "clm-rev":{ 
        "typ": "AttestContract",
        "addr": "8055b362904715fd84536e754868f4c8d27ca3f6"
    }
}
```
#### Signature

```
"e1231231231231231scsdcsdsddsadasdadas"
```

#### Blockchain proof    
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
}
```


字段说明：

| Field     |     Type |   Description   | Necessary|
| :--------------: | :--------:| :------: |:------: |
|    alg|   String|  指明使用的签名方案  |Y|
|    typ|   String|  格式类型, JWT或者JWT-X |Y|
|    kid|   String|  指明用于签名验证的公钥  |Y|
|    ver|   String|  指明可信声明版本  |Y|
|    iss|   String|  可信声明签发者的ONT ID |Y|
|    sub|   String|  可信声明接收者的ONT ID |Y|
|    iat|   int|  unix时间戳格式的创建时间  |Y|
|    exp|   int|  unix时间戳格式的过期时间 |N|
|    jti|   int|  可信声明的唯一标识符  |N|
|    @context|   String|  可信声明内容定义文档的uri，包含每个字段的含义和值的类型的定义  |N|
|    clm|   Object |  指明了可信声明内容  |Y|
|    clm-rev|   Object |  指明了可信声明吊销方式  |Y|
|    Type|   String |  固定值"MerkleProof"  |N|
|    TxnHash|   String |  存证交易hash值  |N|
|    ContractAddr|   String |  存证合约的地址  |N|
|    BlockHeight|   int |  存证交易对应的区块高度  |N|
|    MerkleRoot|   String|  该区块高度的区块对应的Merkle树根  |N|
|    Nodes|   list |  验证节点数组  |N|
|    Nodes.Direction|   String |  验证节点方向  |N|
|    Nodes.TargetHash|   String |  验证节点hash值  |N|



**说明**：可信声明主要分两种类型

- 自签名可信声明，该种声明不包含MerkleProof证明，Claim里没有blockchain_proof
- 第三方签名可信声明，该种声明包含了MerkleProof证明，Claim里有blockchain_proof

----------------------------------------------------------------------------------------------------------------------------------------

### 自签可信声明

这种可信声明没有blockchain_proof

### twitter认证可信声明模板


#### Payload

```json
{
    "ver": "0.7.0",
    "iss": "did:ont:TRAtosUZHNSiLhzBdHacyxMX4Bg3cjWy3r",
    "sub": "did:ont:SI59Js0zpNSiPOzBdB5cyxu80BO3cjGT70",
    "iat": 1525465044,
    "exp": 1530735444,
    "jti":"4d9546fdf2eb94a364208fa65a9996b03ba0ca4ab2f56d106dac92e891b6f7fc",
    "@context":"claim:twitter_authentication",
    "clm":{
	"Id": "424209562",
	"Name": "leewi9在上海",
	"Alias": "leewi9_shanghai",
	"Bio": "",
	"Avatar": "https://pbs.twimg.com/profile_images/627454413213315073/NDaMGG_a_normal.jpg",
	"Location": "",
	"WebSite": "",
	"HomePage": "https://twitter.com/leewi9_shanghai",
	"TwitterUrl": "https://twitter.com/leewi9_shanghai/status/968687917853036544",
	"TwitterCreateTime": "Wed Feb 28 03:22:51 +0000 2018",
    "IssuerName":"Ontology"
    },
    "clm-rev":{ 
        "typ": "AttestContract",
        "addr": "8055b362904715fd84536e754868f4c8d27ca3f6"
    }
}
```



可信声明具体内容clm对应字段说明：

| Field     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    Id|   String|  账户Id  |
|    Name|   String|  账户名称  |
|    Alias|   String|  账户别名  |
|    Bio|   String|  个人简介  |
|    Avatar|   String|  个人头像  |
|    Location|   String|  位置  |
|    WebSite|   String|  个人网站  |
|    HomePage|   String|  个人社媒主页  |
|    TwitterUrl|   String |  推文链接  |
|    TwitterCreateTime|   String |  推文发送时间  |
|    IssuerName|   String| 签发机构名称  |


### github认证可信声明模板


#### Payload
```json
{
    "ver": "0.7.0",
    "iss": "did:ont:TRAtosUZHNSiLhzBdHacyxMX4Bg3cjWy3r",
    "sub": "did:ont:SI59Js0zpNSiPOzBdB5cyxu80BO3cjGT70",
    "iat": 1525465044,
    "exp": 1530735444,
    "jti":"4d9546fdf2eb94a364208fa65a9996b03ba0ca4ab2f56d106dac92e891b6f7fc",
    "@context":"claim:github_authentication",
    "clm":{
	"Id": "10832544",
	"Name": "",
	"Company": "",
	"Alias": "leewi9",
	"Bio": "",
	"Avatar": "https://avatars2.githubusercontent.com/u/10832544?v=4",
	"Email": "leewi9@yahoo.com",
	"Location": "",
	"GistUrl": "https://gist.github.com/42298ebb0c44054c43f48e1afd763ff6",
	"GistCreateTime": "2018-02-28T03:24:48Z",
    "IssuerName":"Ontology"
    },
    "clm-rev":{ 
        "typ": "AttestContract",
        "addr": "8055b362904715fd84536e754868f4c8d27ca3f6"
    }
}
```

可信声明具体内容clm对应字段说明：

| Field     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    Id|   String|  账户Id  |
|    Name|   String|  账户名称  |
|    Company|   String|  账户绑定的公司  |
|    Alias|   String|  账户别名  |
|    Bio|   String|  个人简介  |
|    Avatar|   String|  个人头像  |
|    Email|   String|  账户绑定的邮箱  |
|    Location|   String|  位置  |
|    GistUrl|   String |  Gist文章链接  |
|    GistCreateTime|   String |  Gist文章发送时间  |
|    IssuerName|   String| 签发机构名称  |


----------------------------------------------------------------------------------------------------------------------------------

### 第三方签发可信声明

这种可信声明带有blockchain_proof

#### Blockchain proof    
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
}
```

### linkedin认证可信声明模板

**linkedin认证是由机构签发，所以包含MerkleProof**


#### Payload

```json
{
    "ver": "0.7.0",
    "iss": "did:ont:TRAtosUZHNSiLhzBdHacyxMX4Bg3cjWy3r",
    "sub": "did:ont:SI59Js0zpNSiPOzBdB5cyxu80BO3cjGT70",
    "iat": 1525465044,
    "exp": 1530735444,
    "jti":"4d9546fdf2eb94a364208fa65a9996b03ba0ca4ab2f56d106dac92e891b6f7fc",
    "@context":"claim:linkedin_authentication",
    "clm":{
	"Id": "yL5FdXB-um",
	"Name": "feng li",
	"FirstName": "feng",
	"LastName": "li",
	"Bio": "Blockchain App Developer",
	"Avatar": "https://media.licdn.com/mpr/mprx/0_-HOmp1u9zNCxbF3iKoYjplm9clNP53AiyuoAplgLHN8Cs56_YaaCtAdIJ0qS66rf1IpK19_gajZa",
	"HomePage": "https://www.linkedin.com/in/%E4%BA%9A%E5%B3%B0-%E6%9D%8E-b56b8b79",
    "IssuerName":"Ontology"
    },
    "clm-rev":{ 
        "typ": "AttestContract",
        "addr": "8055b362904715fd84536e754868f4c8d27ca3f6"
    }
}
```


可信声明具体内容clm对应字段说明：

| Field     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    Id|   String|  账户Id  |
|    Name|   String|  名称  |
|    FirstName|   String|  名  |
|    LastName|   String|  姓  |
|    Bio|   String|  个人简介  |
|    Avatar|   String|  个人头像  |
|    HomePage|   String|  社媒主页  |
|    IssuerName|   String| 签发机构名称  |


### facebook认证可信声明模板

**facebook认证是由机构签发，所以包含MerkleProof**

#### Payload

```json
{
    "ver": "0.7.0",
    "iss": "did:ont:TRAtosUZHNSiLhzBdHacyxMX4Bg3cjWy3r",
    "sub": "did:ont:SI59Js0zpNSiPOzBdB5cyxu80BO3cjGT70",
    "iat": 1525465044,
    "exp": 1530735444,
    "jti":"4d9546fdf2eb94a364208fa65a9996b03ba0ca4ab2f56d106dac92e891b6f7fc",
    "@context":"claim:github_authentication",
    "clm":{
	"Id": "1803639093262686",
	"Name": "lifeng",
	"FirstName": "feng",
	"LastName": "li",
	"Avatar": "https://graph.facebook.com/v2.3/1803639093262686/picture",
	"Gender": "male",
	"Locale": "zh_CN",
	"HomePage": "https://www.facebook.com/1803639093262686",
    "IssuerName":"Ontology"
    },
    "clm-rev":{ 
        "typ": "AttestContract",
        "addr": "8055b362904715fd84536e754868f4c8d27ca3f6"
    }
}
```


可信声明具体内容clm对应字段说明：

| Field     |     Type |   Description   | 
| :--------------: | :--------:| :------: |
|    Id|   String|  账户Id  |
|    Name|   String|  名称  |
|    FirstName|   String|  名  |
|    LastName|   String|  姓  |
|    Avatar|   String|  个人头像  |
|    Gender|   String|  性别  |
|    Locale|   String|  地区  |
|    HomePage|   String|  社媒主页  |
|    IssuerName|   String| 签发机构名称  |
