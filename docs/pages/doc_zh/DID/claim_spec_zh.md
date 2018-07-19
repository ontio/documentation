---
title:
keywords: sample homepage
sidebar: DID_zh
permalink: claim_spec_zh.html
folder: doc_zh/DID
giturl: https://github.com/ontio/ontology-DID/blob/master/docs/cn/claim_spec_cn.md
---

[English](./claim_spec_en.html) / 中文

<h1 align="center">可信声明协议规范</h1>
<p align="center" class="version">Version 0.7.0 </p>

可信声明的整个工作流程如下图所示，包含三大部分，即

- 请求声明；
- 签发声明；
- 验证声明。

![claim workflow](./lib/images/claim_workflow.png)

## 1. 签发   
可信声明的颁发过程涉及两个角色，即签发者（Issuer）与接收者（Receipient）。
通常，一份可信声明应当包含声明内容、数字签名、区块链存证记录。更具体来说，

- 声明ID：能够唯一标识该声明；

- 声明内容：具体信息，如学位证明；

- 声明元数据
    - 创建时间： 声明创建的时间；
    - 签发者：签发者的Ont ID；
    - 接收者：接收者的Ont ID；
    - 过期时间：声明自动过期的时间；
    - 吊销机制:可以采用*吊销列表*，或者将吊销信息直接记录在*存证合约*中；

- 区块链证明

- 签名
    - 签发者公钥标识
    - 签名值

[**附录A**](#a-可信声明模板)小节包含可信声明的一个示例，展示了企业颁发的收入证明的声明模板。

### 1.1 可信声明签发流程

简单概括，颁发声明有三大步骤：

1. 接收者发起申请并提供数据，签发者构造可信声明；
2. 签发者在存证合约中进行存证，即在合约中登记该可信声明状态为*可用*；
3. 将可信声明以安全形式传输给接收者，即使用接收者的公钥将可信声明进行加密。

上述步骤对应可信声明工作流程中的第1 - 4步。

### 1.2 可信声明格式

我们使用JSON Web Token的扩展格式来表示一个可信声明，它可以在发行者和接收者之间传输。

可信声明基本结构由三部分组成：Header，Payload，Signature。我们应该尽可能的多重用JWT标准属性，在某些特殊情况下可以使用定制属性。

我们通过在最后附加区块链证明来扩展JWT格式，一个典型的可信声明被组织为**header.payload.signature.blockchain_proof**

	注意：blockchain_proof是可选的。某些情况下，可信声明可以不包含blockchain_proof

#### Header
Header部分定义了该可信声明的格式类型，使用的签名方案以及用于验证签名的公钥id
```
{
    "alg": "ES256",
    "typ": "JWT-X",
    "kid": "did:ont:TRAtosUZHNSiLhzBdHacyxMX4Bg3cjWy3r#keys-1"
}
```

- **alg** 指明使用的签名方案。支持的签名方案列表在[这里](##_Supported_signature_schemes).

-  **typ** 格式类型，可以是以下两种值
	- JWT:不包含区块链证明的可信声明
	- JWT-X:包含区块链证明的可信声明
	
	
- **kid** 指明用于签名验证的公钥。格式和ONT-ID 规范定义的一样：```<ONTID>#keys-<number>```

#### Payload
在Payload部分，可信声明id，content，metadata被编码为JSON对象。使用JWT规范中指定的一些名称，即 `jti`，`iss`，`sub`，`iat`，`exp`
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
-  **@context** 可信声明内容定义文档的uri，包含每个字段的含义和值的类型的定义
-  **clm** 指明了可信声明内容
-  **clm-rev** 指明了可信声明吊销方式。支持的方式在[附录C](#C-Revocation).


要签发一个可信声明，首先需要构造可信声明id、content和metadata的JSON对象，然后使用标准的JSON序列化方法对其进行序列化。最后，使用签发者的某个私钥对header和payload的二进制数据进行签名。例如上面的payload在序列化后看起来像这样：

	{"ver":"0.7.0","iss":"did:ont:TRAtosUZHNSiLhzBdHacyxMX4Bg3cjWy3r","sub":"did:ont:SI59Js0zpNSiPOzBdB5cyxu80BO3cjGT70","iat":1525465044,"exp":1530735444,"jti":"4d9546fdf2eb94a364208fa65a9996b03ba0ca4ab2f56d106dac92e891b6f7fc","@context":"https://example.com/template/v1","clm":{"Name":"Bob Dylan","Age":"22"},"clm-rev":{"Type":"Contract","Addr":"8055b362904715fd84536e754868f4c8d27ca3f6"}} 




#### Signature

在构造完Header和Payload部分后，根据JWS标准计算签名。详细的描述在 [RFC 7515 Section 5.1](https://tools.ietf.org/html/rfc7515#section-5.1)。简化的版本如下：

- 根据JWS规范对Header和Payload部分进行序列化，作为签名的输入
	
	sig := sign(Base64URL(header) || . || Base64URL(payload))


- 根据Header部分指定的特定签名方案来计算签名。

- 对签名进行编码
	
	signature := Base64URL(sig).


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
```

- **Type** 固定值"MerkleProof"
- **TxnHash** 将可信声明id存证在合约里的交易hash值
- **ContractAddr** 存证合约的地址
- **BlockHeight** 存证交易对应的区块高度
- **MerkleRoot** 该区块高度的区块对应的Merkle树根
- **Nodes** Merkle树证明的证明路径

MerkleProof按照以下格式编码
	
	BASE64URL(MerkleProof)

现在一个完整的可信声明就被创建好了
	
	BASE64URL(Header) || '.' || BASE64URL(Payload) || '.' || BASE64URL(Signature)  '.' || BASE64URL(MerkleProof) 





### 1.3 存证合约

可信声明存证合约提供存证服务即存证可信声明Id，签发者ONT身份，属主ONT身份等信息，以及记录可用性信息即是否被吊销等信息。

提供的接口主要是

- 声明存证

    ```
    bool Commit(byte[] claimId, byte[] committerOntId, byte[] ownerOntId);
    ```

    在存证合约中，声明的唯一标识就是声明的ID，这个将被作为第一个参数，committerOntId就是存证人的ONT身份，ownerOntId是可信声明属主的ONT身份。

    当且仅当该声明没有被存证过，且`Commit`函数是由committer调用，才能存证成功；否则，存证失败。

    存证成功后，该声明的状态就是*已存证*（committed）。

- 吊销声明
    ```
    bool Revoke(byte[] claimId, byte[] revokerOntId);
    ```
   当且仅当声明已被存证，且revokerOntId等于存证人的ONT身份时，才能成功吊销；否则，吊销失败。

- 存证查询接口
    ```
    byte[] GetStatus(byte[] claimId);
    ```
  返回声明的状态，包含两部分信息：
    - 状态：”未存证“， ”已存证“， ”存证被吊销“；
    - 存证人ONT ID。

## 2. 验证 

简单概括，验证声明有三大步骤，对应流程图第5 - 6步。

- 校验是否在区块链上；
- 验证签名，校验是否过期(可选)；
- 查看是否已经被吊销（可选）。

### 2.1 区块链存在性检验

简单来说，检验可信声明是否在区块链上，其实就是检验发布该可信声明的交易是否落账，在不同步完整区块链的情况下，我们可以采用检验交易的Merkle proof。

Merkle proof是一个数组，每个数组项包含两个元素（direction, hash）：
- `direction`：代表该数组项位于merkle tree的哪一个分支，有两个可能值：left 、right；
- `hash`：代表数据项的哈希值。

验证Merkle proof的算法（描述如下）

- Init: p <- proof.TxnHash
- For each element in proof.Nodes,  update p as
    - if e.Direction == "Left",  p <- H(e.TargetHash, p);
    - else, p <- H(p, e.TargetHash).
- Return true if p equals to proof.MerkleRoot. Otherwise, return false.

Merkle proof示例
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

除此之外，还需要检查声明存证状态，即调用地址为`proof.ContractAddr`的存证合约的查询接口`GetStatus()`，如果状态字段为”未存证“，则返回错误。


### 2.2 验证签名与过期时间

在验证签名时，需要根据公钥ID获取公钥值与公钥的当前状态，然后调用对应的验签算法进行验证。

公钥ID的格式是```<ONTID>#keys-<number>```，调用ONT ID智能合约的查询公钥状态接口```GetPublicKeyStatus(byte[] ontId, byte[] pkId)```会返回
- publicKey: 公钥值（hexstring）；
- status: 有两种可能值，```InUse```、```Revoked```。

签名验证的执行结果有三种：
 - 签名不合法；
 - 签名合法，公钥处于`Revoked`状态；
 - 签名有效。

过期时间的验证，验证当前时间是否已经超出过期时间。

过期时间的值由Metadata中Expires字段指定。该值可以为空。

### 2.3 吊销验证

目前有两种吊销模式，吊销列表和吊销查询接口。

已吊销查询接口为例，如果将吊销信息放在存证合约中，那么调用存证合约的查询接口`GetStatus`，当且仅当返回的状态字段是”已存证“，吊销验证才返回成功，若状态字段是”存证被吊销“，则返回验证失败。

吊销列表主要包括被吊销的可信声明的唯一标识符数据，以及吊销时间。


## 支持的签名方案

* ES224 - ECDSA with SHA224,
* ES256 - ECDSA with SHA256,
* ES384 - ECDSA with SHA384,
* ES512 - ECDSA with SHA512,
* ES3-224 - ECDSA with SHA3 224
* ES3-256 - ECDSA with SHA3 256
* ES3-384 - ECDSA with SHA3 384
* ES3-512 - ECDSA with SHA3 512
* ER160 - ECDSA with RIPEMD160
* SM - SM2 with SM3
* EDS512 - EDDSA with SHA256

## 附录
### A. 可信声明模板

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
TODO
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


### B. Content格式定义模板
可信声明的一个主要部分就是声明内容，而声明内容格式的定义是在另外一个JSON文件中，此文件中定义了每个属性的含义，以及对应的属性值的类型。

下面给出附录A中的Content的格式定义。
```json
{
    "Type": "claim:employment_authentication", 
    "IdNumber": {
        "Doc": "Unique number of certificate",
        "ValType": "String"
    }, 
    "Name": {
        "Doc": "The full name of certificate owner",
        "ValType": "String"
    },
    "JobTitle": {
        "Doc": "The job title of certificate owner",
        "ValType": "String"
    }, 
    "MonthlySalary": {
        "Doc": "The monthly salary of certificate owner",
        "ValType": "double"
    },
    "HireDate": {
        "Doc": "Hiring date",
        "ValType": "Time"
    }
}
```


### C 吊销

我们使用两种吊销机制

- 吊销列表


吊销列表需要包含被签发者吊销的可信声明唯一标识符，吊销时间。使用该机制，可信声明必须包含吊销列表的url，并且类型必须被指定为`RevocationList`。
```
    "clm-rev": {
        "type": "RevocationList",
        "url": "https://example.com/rev/1234"
    }
```

- 存证合约吊销
 吊销信息通过存证合约的`Revoke`函数被记录在存证合约里。为了确认一个可信声明是否已吊销，标准方法是调用`GetStatus`函数。更多信息，请参阅[1.3节](claim_spec.md#1.3-attest-contract)。
```
    "clm-rev": {
        "type": "AttestContract",
        "addr": "8055b362904715fd84536e754868f4c8d27ca3f6"
    }
```


### [更多可信声明模板示例](https://github.com/ontio/ontology-DID/blob/master/claimtemplate/cn/可信声明模板定义.md)
