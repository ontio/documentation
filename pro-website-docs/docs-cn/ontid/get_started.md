<h1 align="center">ONT ID 应用快速开发指南 </h1>

我们假定您已经清楚ONT ID的概念，并且知道ONT ID能为您做什么。现在，您需要使用ONT ID为认证您的用户或者为你的用户管理数字身份，可以参照这篇文档着手搭建。

我们支持使用多种SDK或RPC方式来应用ONT ID ，我们以Typescript SDK为例，说明如何进行快速开发。本文档中以下的示例代码都以Node环境为例。

## 环境准备

请参考[Ontology TS SDk的安装指南](https://github.com/ontio/ontology-ts-sdk)，安装好环境。

## 创建数字身份

### 2.1 创建身份

ONT ID是一个去中心化的身份标识，能够管理用户的各种数字身份认证。数字身份(Identity)是ONT SDK导出的一个核心类，该类包含代表身份的ONT ID属性。

> 如需要了解数字身份更详细的信息，请查阅[ONT ID Protocol Specifiction](https://github.com/ontio/ontology-DID/blob/master/docs/cn/ONTID_protocol_spec_cn.md)。

你可以通过SDK来创建一个身份。创建身份的过程中会基于用户的私钥生成ONT ID。

创建身份需要提供的参数如下：

**privateKey** 用户的私钥。可以通过SDK提供的方法安全地生成私钥。

**password** 用来加密和解密私钥的密码。

**label** 身份的名称

**params** 用来加密私钥的算法参数。可选参数。默认值如下：

```
{
    cost: 4096,
    blockSize: 8,
    parallel: 8,
    size: 64
}
```

```
import {Identity, Crypto} from 'ontology-ts-sdk';
//generate a random private key
const privateKey = Crypto.PrivateKey.random();

var identity = Identity.create(privateKey, password, label)
console.log(identity.ontid)
```

### 2.2 将ONT ID登记到链上

身份创建完成后，还需要将身份的ONT ID注册到链上，身份才算真正地创建完成。

发送ONT ID上链是需要发送交易的过程。可以通过调用SDK提供的方法构造交易对象。

一种比较典型的场景是通过传递刚刚创建的ONT ID和用户的私钥来构造交易对象。

这里传递的私钥有两个作用：

1.对构造的交易进行签名；

2.将用户的ONT ID绑定到用户的私钥对应的公钥上。用户之后还可以在ONT ID上添加其它的公钥。

````
import {OntidContract} from 'ontology-ts-sdk';
import {TransactionBuilder} from 'ontology-ts-sdk'

//suppose we already got a identity
const did = identity.ontid;
//we need the public key, which can be generate from private key
const pk = privateKey.getPublicKey();
const gasPrice = '0';
const gasLimit = '20000;
const tx = OntidContract.buildRegisterOntidTx(did, pk, gasPrice, gasLimit);
Transaction.signTransaction(tx, privateKey);
````

发送ONT ID上链的交易需要消耗手续费，我们需要给交易指定一个支付人Payer，并添加Payer的签名。支付人可以是用户本人，也可以是dApp应用为用户支付。

````
import {TransactionBuilder} from 'ontology-ts-sdk'
//we also need an account to pay for the gas
//supporse we have an account and the privateKey
tx.payer = account.address
//Then sign the transaction with payer's account
//we already got transaction created before,add the signature.
TransactionBuilder.addSign(tx, privateKeyOfAccount)
````

现在可以发送交易到链上。我们多种发送交易的方式，如Websocket, Restful和RPC。这里以Restful的方式为例。我们可以指定交易发送到的节点，如果不指定，默认发送到测试网。

````
import {RestClient, CONST} from 'ontology-ts-sdk'

const rest = new RestClient(CONST.TEST_ONT_URL.REST_URL);
rest.sendRawTransaction(tx.serialize()).then(res => {
    console.log(res)
})
````
返回结果如下：

````
{ Action: 'sendrawtransaction',
  Desc: 'SUCCESS',
  Error: 0,
  Result: 'dfc598649e0f3d9ff94486a80020a2775e1d474b843255f8680a3ac862c58741',
  Version: '1.0.0' }
````

如果结果返回状态成功（Error是0），表明ONT ID上链成功。我们可以查询链上ONT ID的相关信息。

当我们定义的回调函数里处理得到上链成功的推送消息时，ONT ID创建过程才真正完成。接下来就可以通过ONT ID就可以使用了。


## 3. 查询链上身份DDO

当链上成功注册一个ONT ID，链上将形成一个ONT ID对象，我们称之为DDO。查询DDO，最简单的办法是通过[本体区块链浏览器](https://explorer.ont.io)查询，或者您也可以通过SDK查询。

通过SDK查询的方式如下：

首先构建交易
````
import {OntidContract} from 'ontology-ts-sdk';
//we use identity's ONT ID to create the transaction
const tx = OntidContract.buildGetDDOTx(identity.ontid)
````

发送交易 查询交易不需要消耗gas，也就不需要指定payer和payer的签名。发送交易方法的第二个参数表示发送的是否是预执行的交易。预执行的交易只在接收到它的节点上运行，不需要等待共识。一般用来查询数据。
````
import {RestClient} from 'ontology-ts-sdk';
const rest = new RestClient();
rest.sendRawTransaction(tx, true).then(res => {
    console.log(res);
}
````

返回的结果如下：
````
{ Action: 'sendrawtransaction',
      Desc: 'SUCCESS',
      Error: 0,
      Result:
       { State: 1,
         Gas: 20000,
         Result: '26010000002103547c5abdbe66677ba7001cefd773f01a19c6360b15ee51c6db43911f046564fc0000' },
      Version: '1.0.0' }
````

Result 就是序列化后的DDO（ONT ID object） 我们可以通过反序列化得到详细数据。
````
const ddo = DDO.deserialize(response.Result.Result);
console.log(ddo);
````
## 4. 认证用户并获取Claim

ONTPass基于ONTID及本体信任生态，是一个开放的、去中心化认证服务平台，为您提供KYC（Know Your Customer）服务和多种用户认证服务。本体信任生态已聚集了提供全球身份认证服务能力的信任锚，包括IdentityMind、CFCA、商汤科技、Shufti Pro等等，同时还支持邮箱、手机、社交媒体认证方式。

[>> 通过ONTPass认证用户](https://github.com/ontio/documentation/blob/master/pro-website-docs/docs-cn/ontpass/ontpass_getstarted.md)


## 5. 验证可信声明

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

## 6. 为用户制作可信声明

您的平台也可以为用户制作可信声明。

> 任何一个ONT ID的所有者（Owner）均可以向自己或他人签发可信声明。 

> 政府机关、大学、银行、第三方认证服务机构（比如CA机构）、生物识别科技公司等等可作为现实信任机构，可以作为特定的合作方，加入到在本体生态中。
如果你可能成为认证服务合作方，请具体了解[信任锚]()。

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

关于声明对象的具体规范，详见[claim的规范](https://github.com/ontio/ontology-DID/blob/master/docs/cn/claim_spec_cn.md)。

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





