---
title: 
keywords: sample homepage
sidebar: ont_doc_zh
permalink: claim_spec_zh.html
folder: doc_zh
---


[English](./claim_spec_en.html) / 中文

<h1 align="center">可信申明协议规范</h1>
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

[**附录A**](#A. 可信声明模板)小节包含可信声明的一个示例，展示了企业颁发的收入证明的声明模板。

### 1.1 可信声明签发流程

简单概括，颁发声明有三大步骤：

1. 接收者发起申请并提供数据，签发者构造可信声明；
2. 签发者在存证合约中进行存证，即在合约中登记该可信声明状态为*可用*；
3. 将可信声明以安全形式传输给接收者，即使用接收者的公钥将可信声明进行加密。

上述步骤对应可信声明工作流程中的第1 - 4步。


### 1.2 存证合约

可信声明存证合约提供存证服务，以及记录可用性信息，即是否被吊销等信息。

提供的接口主要是

- 声明存证

    ```
    bool Commit(byte[] claimId, byte[] committerOntId);
    ```

    在存证合约中，声明的唯一标识就是声明的ID，这个将被作为第一个参数；committerOntId就是存证人的ONT身份。

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
```
//吊销列表示例
    "Revocation": { 
            "Type": "RevocationList",
            "Id": "a35b2b3cx65373js8dd",
            "Time" : "2018-04-12 12:00:00"
        }
```

## 附录
### A. 可信声明模板

```json
{
    "Id":"ca4ab2f56d106dac92e891b6f7fc4d9546fdf2eb94a364208fa65a9996b03ba0",
    "Context":"https://example.com/salary/template/v1",
    "Content":{
        "IdNumber": "510806199002122991",
        "Name": "Bob Dylan",
        "JobTitle": "SoftwareEngineer",
        "MonthlySalary": 3000.00,
        "HireDate": "2017-03-20"
    },
    "Metadata":{
        "CreateTime":"2017-04-01T12:01:20Z",
        "Issuer":"did:ont:TRAtosUZHNSiLhzBdHacyxMX4Bg3cjWy3r",
        "Subject":"did:ont:SI59Js0zpNSiPOzBdB5cyxu80BO3cjGT70",
        "Expires":"2018-06-01",
        "Revocation": { 
            "Type": "Contract",
            "Addr": "8055b362904715fd84536e754868f4c8d27ca3f6"
        }
    },

    "Signature":{
        "PublicKeyId": "did:ont:TRAtosUZHNSiLhzBdHacyxMX4Bg3cjWy3r#keys-1",
    	"Format":"pgp",
    	"Algorithm":"ECDSAwithSHA256",
    	"Value":"rsjaenrxJm8qDmhtOHNBNOCOlvz/GC1c6CMnUb7KOb1jmHbMNGB63VXhtKflwSggyu1cVBK14/0t7qELqIrNmQ=="
    },

    "Proof":{
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



字段描述：

| Field     |     Type |   Description   | Necessary|
| :-------------- | :--------:| :------ |:------: |
|    Id|   String|  可信声明唯一标识  |Y|
|    Context|   String|  Content模板标识  |Y|
|    Content|   Object|  可信声明具体内容，key-value形式  |Y|
|    Metadata|   Object|  可信声明元数据  |Y|
|    Metadata.CreateTime|   String|  创建时间,格式：yyyy-MM-dd'T'HH:mm:ss'Z'  |Y|
|    Metadata.Issuer|   String|  可信声明颁发者ONTID  |Y|
|    Metadata.Subject|   String|  可信声明接收者ONTID  |Y|
|    Metadata.IssuerName|   String|  可信声明颁发者名称  |N|
|    Metadata.Expires|   String|  过期时间，格式：yyyy-MM-dd  |N|
|    Metadata.Revocation|   String|  声明吊销类型(吊销列表或利用存证合约吊销)  |N|
|    Signature|   Object |  签名信息  |Y|
|    Signature.PublicKeyId|   String |  签名公钥ID  |Y|
|    Signature.Format|   String |  签名格式  |Y|
|    Signature.Algorithm|   String |  签名算法  |Y|
|    Signature.Value|   String |  签名值  |Y|
|    Proof|   Object |  完整性证明  |Y|

详细说明：
- Id: 可信声明唯一标识，生成逻辑为对Context，Content，Metadata字段内容做Hash，保证了唯一性。
- Context: Content格式定义文档地址，目标文档定义了Content中每个(key,value)的含义，value的类型；
- Content: 可信声明具体内容。
- Metadata: 元数据，包含了签发时间，签发者和接收者身份标识等基本信息。
- Signature: 签名信息，是由声明签发者对Id，Context，Content，Metadata内容做的签名，可用于后续可信声明验证。
- Proof: 完整性证明，在Ontology中使用Merkle proof，可用于验证可信声明的存在性和完整性。

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