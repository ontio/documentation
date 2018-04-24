---
title: 
keywords: sample homepage
sidebar: ont_doc_zh
permalink: ontology_ts_sdk_identity_claim_zh.html
folder: doc_zh
---


[English](./ontology_ts_sdk_identity_claim_en.html) / 中文

<h1 align="center">数字身份与可信声明</h1>
<p align="center" class="version">Version 0.7.0 </p>

## 1.1 创建身份

ONT ID是一个去中心化的身份标识，能够管理用户的各种数字身份认证。数字身份(Identity)是ONT SDK导出的一个核心类，该类包含代表身份的ONT ID属性。

> 关于数字身份的具体信息请查阅[ONT TS SDk]() 中相关内容。

可以通过SDK来创建一个身份。创建身份的过程中会基于用户的私钥生成ONT ID。

> 关于ONT ID 的规范参见[ONT ID生成规范](./ONTID_protocol_spec.md/#1.1_ONT_ID生成)

创建身份需要提供的参数如下：

**privateKey** 用户的私钥。可以通过SDK提供的方法安全地生成私钥。

**password** 用来加密和解密私钥的密码。

**algorithmObj** 用来生成身份的算法对象。该值是可选参数，结构如下：

```
{
  algorithm: string // 算法名称
  parameters: {}    // 算法参数
}
```

```
import {Identity} from 'Ont'
var identity = new Identity()
identity.create(privateKey, password)
console.log(identity.ontid)
```

### 1.2 将ONT ID登记到链上

身份创建完成后，还需要将身份的ONT ID注册到链上，身份才算真正地创建完成。

发送ONT ID上链是需要发送交易的过程。可以通过调用SDK提供的方法构造交易对象。

一种比较典型的场景是通过传递刚刚创建的ONT ID和用户的私钥来构造交易对象。

这里传递的私钥有两个作用：

1.对构造的交易进行签名；

2.将用户的ONT ID绑定到用户的私钥对应的公钥上。用户之后还可以在ONT ID上添加其它的公钥。

````
var param = buildRegisterOntidTx(ontid, privateKey)
````

该方法返回的是交易对象序列化好的参数，接下来是发送该参数。可以通过websocket或者http请求的方式发送。这里我们以websocket为例，这样能够监听链上推送回来的消息，来确认ONT ID是否上链成功。

````
//构造发送交易的工具类，这里连接的是测试节点。
var txSender = new TxSender(ONT_NETWORK.TEST)

//构造回调函数，处理接收到的消息
const callback = function(res, socket) {
    if(res.Action === 'Notify' && res.Result == 0 ) {
    	//确认上链成功，关闭socket
        socket.close()
    }
}

//发送交易
txSender.sendTxWithSocket( param, callback )
````

当我们定义的回调函数里处理得到上链成功的推送消息时，ONT ID创建过程才真正完成。接下来就可以通过ONT ID来管理用户的各项可信声明了。

关于链上推送返回的具体信息，可以参见[ONT ID智能合约的设计与调用相关文档](./ONTID_protocol_spec.md/#g._事件推送)。

## 2. 签发可信声明

用户可能会有多种不同的身份。比如拥有公安部颁发的身份证的用户，都拥有中国公民这种身份，用户可以在生活中的某些场景中，出示自己的身份证，来声明自己的这种身份；身份证就是公安部对我们公民身份的认证。

再比如某所大学毕业的学生，可以获得该大学的毕业生的身份。这个身份可以通过学校给学生颁发的毕业证来证明。现在，还有一种新的方式来认证这种某大学毕业生的身份。这就是通过区块链技术，将某种可信声明同用户的ONT ID绑定起来。同样地，用户可以向多个不同的机构或平台获取不同的可信声明。

> 任何一个ONT ID的所有者（Owner）均可以向自己或他人签发可信声明。 

> 政府机关、大学、银行、第三方认证服务机构（比如CA机构）、生物识别科技公司等等可作为现实信任机构，可以作为特定的合作方，加入到在本体生态中。
如果你可能成为认证服务合作方，请参见[认证服务合作方接入标准](./verification_provider_specification.md)。

我们以中国复旦大学颁发数字毕业证书来举例，说明如何获取第三方授予用户的的身份声明。

假设Alice是复旦大学的学生，向学校申请毕业证的数字证明。学校验证确认了Alice的身份后，通过调用SDK的api生成一份可信声明，该声明包含Alice的毕业信息，和用学校的私钥对声明做的签名。

````
var claim = SDK.signClaim(context, claimData, issuer, subject, privateKey)
````

该方法的参数说明如下：

**context** 是一种声明模板的标识。

**claimData** 是用户声明的具体内容，该值是JSON对象。在这里就是Alice毕业证上的信息，如：

````
{
    "degree" : "bachelor",
    "year" : "2017",
    ......
}
````

**issuer** 是声明的签发者（这里是复旦大学）的ONT ID。

**subject** 是声明接收者（这里是Alice）的ONT ID。表示将该声明绑定到Alice的ONT ID上。

**privateKey** 声明签发者的私钥。用来对声明做签名。

该方法返回的声明对象，内容类似于：

````
{
    .....
}
````

关于声明对象的具体规范，详见[claim的规范]()。

接下来需要发送交易到链上用于存证。上链成功后，会返回该声明上链的完整性证明。该证明的具体格式参见

[claim完整性证明]()。

首先需要构造要发送的交易。需要传递的参数

**path** 是声明信息存储在链上的键名。该值为声明对象中的Id。这是一个对声明对象内容做hash运算后的值。

**value** 是需要存储在链上的声明信息。该值为如下的JSON结构：

````
{
    Context : string, //声明模板的标识，
    Ontid : string //声明签发者的ONT ID
}
````

**ontid** 交易发送者ONT ID，即声明签发者的ONT ID。

**privateKey** 交易发送者私钥，即声明签发者的私钥。

````
var param = SDK.buildClaimTx(path, value, ontid, privateKey)
````

接下来构建发送交易的工具类和监听消息的回调方法。

在回调方法中，声明上链成功后会返回声明的完整性证明。将该完整性证明添加到之前构建的声明对象中，用户就得到完整的第三方认证的声明对象。之后，用户就可以在有需要的场景中，提供该声明。

````
//这里以测试节点为例
var txSender = new TxSender(ONT_NETWORK.TEST)
const callback = function(res, socket) {
    let res 
    if(typeof event.data === 'string') {
    res = JSON.parse(event.data)
    //解析后台推送的Event通知
    //通过简单的判断区块高度，得知上链成功，
    if(res.Result.BlockHeight) {
      socket.close()
    }
}
txSender.sendTxWithSocket(param, callback)
````

证明的内容类似如下：

````
{
    "Proof" : {
        "Type" : "MerkleProof",
        "TxnHash" : "aaa",
        "BlockHeight" : "1000",
        "MerkleRoot" : "aaaaaaa",
        "Nodes" : [
            {"Direction" : "Right", "TargetHash" : "aaaa"},
            {"Direction" : "Left", "TargetHash" : "bbbbb"}
        ]
    }
}
````

## 3. 验证可信声明

在上面一节我们举例说明了如何获取第三方授予的身份声明，用户在需要的时候可以出示这些声明。同时，这些声明可以通过SDK提供的方法来验证是否是真实的、未篡改的。

我们以Alice同学求职的情况为例说明验证可信声明的过程。

Alice向公司B求职时，提供了复旦大学授予的数字毕业证书，该证书是一份符合claim声明格式的JSON文件。公司B可以通过调用ONT SDK的方法来验证该声明。该方法的内部实现逻辑是首先通过声明中的**Issuer** 字段，获取声明签发者的DDO信息，从DDO信息中得到签发者的公钥，然后将声明对象中去掉签名后的内容，同公钥和签名值进行验签。验证通过，则表明声明是真实有效的。

该方法的输入参数是claim声明的JSON字符串，返回结果是Promise。在Promise的回调方法中处理验证结果。

````
Core.verifyClaim(claim).then((result) => {
    //result就是验证结果
    if(result){
        //验证通过
    } else {
        //验证不通过
    }
})
````