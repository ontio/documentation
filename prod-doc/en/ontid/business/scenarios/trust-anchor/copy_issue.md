# Trust anchor - issue claim

1. 可信声明的颁发过程涉及两个角色，即签发者（Issuer）与接收者（Receipient）。 通常，一份可信声明应当包含声明内容、数字签名、区块链存证记录。
2. 标准可信声明由header，payload，signature，blockchain_proof四部分组成，针对自签的可信声明可以没有blockchain_proof。组成格式：header.payload.signature.blockchain_proof。

[各类可信声明模版](../../../framework/trust-anchor/claimtemplate/)



### 可信声明签发流程(通用)



1. 接收者发起申请并提供数据，由TA向CA服务商验证数据

   ```
   api: /v1/claim/userdata
   method: post
   data: {
     id_card_number: 111111111111111111,
     name: 'ericyang',
     age: 18
   }
   
   注意: data为模拟数据，具体需要根据CA方需求来定义
   
   result: {
     is_true: true
   }
   
   'is_true': true 数据验证通过，false 数据验证未通过
   ```

   

2. 构造claim，并对其进行签名

   ##### Header

   Header部分定义了该可信声明的格式类型，使用的签名方案以及用于验证签名的公钥id

   ```
   {
       "alg": "ONT-ES256",
       "typ": "JWT-X",
       "kid": "did:ont:TRAtosUZHNSiLhzBdHacyxMX4Bg3cjWy3r#keys-1" // 指明用于签名验证的公钥
   }
   ```

   

| Field |  Type  |      Description       | Necessary |
| :---: | :----: | :--------------------: | :-------: |
|  typ  | String | 格式类型, JWT或者JWT-X |     Y     |
|  alg  | String |   指明使用的签名方案   |     Y     |
|  kid  | String | 指明用于签名验证的公钥 |     Y     |



##### Payload

​		Payload部分，可信声明id，content，metadata被编码为JSON对象。

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
        "Name": "ericyang",
        "Age": "18"
    },
    "clm-rev":{ 
        "typ": "AttestContract",
        "addr": "8055b362904715fd84536e754868f4c8d27ca3f6"
    }
}
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

1. 完整的可信声明

   ```
   BASE64URL(Header) || '.' || BASE64URL(Payload) || '.' || BASE64URL(Signature)  '.' || BASE64URL(Blockchain proof)
   ```

   

   

   - ES224 - ECDSA with SHA224,
   - ES256 - ECDSA with SHA256,
   - ES384 - ECDSA with SHA384,
   - ES512 - ECDSA with SHA512,
   - ES3-224 - ECDSA with SHA3 224
   - ES3-256 - ECDSA with SHA3 256
   - ES3-384 - ECDSA with SHA3 384
   - ES3-512 - ECDSA with SHA3 512
   - ER160 - ECDSA with RIPEMD160
   - SM - SM2 with SM3
   - EDS512 - EDDSA with SHA256

   ### 支持的签名方案

   

   

   

   ------

   

   - 声明存证

     ```
     bool Commit(byte[] claimId, byte[] committerOntId, byte[] ownerOntId);
     ```

     存证成功后，该声明的状态就是*已存证*（committed）。

     当且仅当该声明没有被存证过，且`Commit`函数是由committer调用，才能存证成功；否则，存证失败。

     在存证合约中，声明的唯一标识就是声明的ID，这个将被作为第一个参数，committerOntId就是存证人的ONT身份，ownerOntId是可信声明属主的ONT身份。

   - 吊销声明

     ```
     bool Revoke(byte[] claimId, byte[] revokerOntId);
     ```

     当且仅当声明已被存证，且revokerOntId等于存证人的ONT身份时，才能成功吊销；否则，吊销失败。

   - 存证查询接口

     ```
     byte[] GetStatus(byte[] claimId);
     ```

     - 状态：”未存证“， ”已存证“， ”存证被吊销“；
     - 存证人ONT ID。

     返回声明的状态，包含两部分信息：

   提供的接口主要是

   

   合约地址：729635b7135e9eab97daed4e0b48e9f18a71410d

   

   可信声明存证合约提供存证服务即存证可信声明Id，签发者ONT身份，属主ONT身份等信息，以及记录可用性信息即是否被吊销等信息。

   ### 存证合约

   

   

   ------



| Type             | String | 固定值"MerkleProof"              | N    |
| :--------------- | :----- | :------------------------------- | :--- |
| TxnHash          | String | 存证交易hash值                   | N    |
| ContractAddr     | String | 存证合约的地址                   | N    |
| BlockHeight      | int    | 存证交易对应的区块高度           | N    |
| MerkleRoot       | String | 该区块高度的区块对应的Merkle树根 | N    |
| Nodes            | list   | 验证节点数组                     | N    |
| Nodes.Direction  | String | 验证节点方向                     | N    |
| Nodes.TargetHash | String | 验证节点hash值                   | N    |



##### Blockchain proof



- 根据JWS规范对Header和Payload部分进行序列化，作为签名的输入

  sig := sign(Base64URL(header) || . || Base64URL(payload))

- 根据Header部分指定的特定签名方案来计算签名。

- 对签名进行编码

  signature := Base64URL(sig).

在构造完Header和Payload部分后，根据JWS标准计算签名。详细的描述在 [RFC 7515 Section 5.1](https://tools.ietf.org/html/rfc7515#section-5.1)。简化的版本如下：

##### Signature<div id="Inter-Page"></div>



要签发一个可信声明，首先需要构造可信声明id、content和metadata的JSON对象，然后使用标准的JSON序列化方法对其进行序列化。最后，使用签发者的某个私钥对header和payload的二进制数据进行签名。

| ver      | String | 指明可信声明版本                                             | Y    |
| :------- | :----- | :----------------------------------------------------------- | :--- |
| iss      | String | 可信声明签发者的ONT ID                                       | Y    |
| sub      | String | 可信声明接收者的ONT ID                                       | Y    |
| iat      | int    | unix时间戳格式的创建时间                                     | Y    |
| exp      | int    | unix时间戳格式的过期时间                                     | N    |
| jti      | int    | 可信声明的唯一标识符                                         | N    |
| @context | String | 可信声明内容定义文档的uri，包含每个字段的含义和值的类型的定义 | N    |
| clm      | Object | 指明了可信声明内容                                           | Y    |
| clm-rev  | Object | 指明了可信声明吊销方式                                       | Y    |
| Type     | String | 固定值"MerkleProof"                                          | N    |