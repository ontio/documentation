
# 数字身份与可信声明

## 1.1 创建身份

ONT ID是一个去中心化的身份标识，能够管理用户的各种数字身份认证。数字身份(Identity)是ONT SDK导出的一个核心类，该类包含代表身份的ONT ID属性。

> 关于数字身份的具体信息请查阅[ONT TS SDk]() 中相关内容。

可以通过SDK来创建一个身份。创建身份的过程中会基于用户的私钥生成ONT ID。

> 关于ONT ID 的规范参见[ONT ID生成规范](./ONTID_protocol_spec.md/#1.1_ONT_ID生成)

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

## 1.2 将ONT ID登记到链上

身份创建完成后，还需要将身份的ONT ID注册到链上，身份才算真正地创建完成。

发送ONT ID上链是需要发送交易的过程。可以通过调用SDK提供的方法构造交易对象。

一种比较典型的场景是通过传递刚刚创建的ONT ID和用户的私钥来构造交易对象。

### 构建交易
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

该方法返回的是交易对象序列化好的参数，接下来是发送该参数。可以通过websocket或者http请求的方式发送。这里我们以websocket为例，这样能够监听链上推送回来的消息，来确认ONT ID是否上链成功。

### 添加交易Payer的签名
发送ONT ID上链的交易需要消耗手续费，我们需要给交易指定一个Payer，并添加Payer的签名。

````
import {TransactionBuilder} from 'ontology-ts-sdk'
//we also need an account to pay for the gas
//supporse we have an account and the privateKey
tx.payer = account.address
//Then sign the transaction with payer's account
//we already got transaction created before,add the signature.
TransactionBuilder.addSign(tx, privateKeyOfAccount)
````

### 发送交易
我们多种发送交易的方式，如Websocket, Restful和RPC。这里以Restful的方式为例。我们可以指定交易发送到的节点，如果不指定，默认发送到测试网。

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

如果结果返回状态成功，表明ONT ID上链成功。我们可以通过查询接口查询链上ONT ID的相关信息。

### 1.3 查询DDO

###构建交易

````
import {OntidContract} from 'ontology-ts-sdk';
//we use identity's ONT ID to create the transaction
const tx = OntidContract.buildGetDDOTx(identity.ontid)
````
###发送交易
查询交易不需要消耗gas，也就不需要指定payer和payer的签名。发送交易方法的第二个参数表示发送的是否是预执行的交易。预执行的交易只在接收到它的节点上运行，不需要等待共识。一般用来查询数据。
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
**Result** 就是序列化后的DDO（ONT ID object）
我们可以通过反序列化得到详细数据。

````
const ddo = DDO.deserialize(response.Result.Result);
console.log(ddo);
````

## 2. 签发可信声明

用户可能会有多种不同的身份。比如拥有公安部颁发的身份证的用户，都拥有中国公民这种身份，用户可以在生活中的某些场景中，出示自己的身份证，来声明自己的这种身份；身份证就是公安部对我们公民身份的认证。

再比如某所大学毕业的学生，可以获得该大学的毕业生的身份。这个身份可以通过学校给学生颁发的毕业证来证明。现在，还有一种新的方式来认证这种某大学毕业生的身份。这就是通过区块链技术，将某种可信声明同用户的ONT ID绑定起来。同样地，用户可以向多个不同的机构或平台获取不同的可信声明。

> 任何一个ONT ID的所有者（Owner）均可以向自己或他人签发可信声明。 

> 政府机关、大学、银行、第三方认证服务机构（比如CA机构）、生物识别科技公司等等可作为现实信任机构，可以作为特定的合作方，加入到在本体生态中。
如果你可能成为认证服务合作方，请参见[认证服务合作方接入标准](./verification_provider_specification.md)。

我们以中国复旦大学颁发数字毕业证书来举例，说明如何获取第三方授予用户的的身份声明。

假设Alice是复旦大学的学生，向学校申请毕业证的数字证明。学校验证确认了Alice的身份后，通过调用SDK的api生成一份可信声明，该声明包含Alice的毕业信息，和用学校的私钥对声明做的签名。

### 构建可信声明

````
import {Claim} from 'ontology-ts-sdk';

const signature = null;
const useProof = false;
const claim = new Claim({
	messageId: '1',
	issuer: 'did:ont:AJTMXN8LQEFv3yg8cYKWGWPbkz9KEB36EM',
	subject: 'did:ont:AUEKhXNsoAT27HJwwqFGbpRy8QLHUMBMPz',
	issueAt: 1525800823
}, signature, useProof);

claim.version = '0.7.0';
claim.context = 'https://example.com/template/v1';
claim.content = {
	Name: 'Alice',
	Age: '22',
	......
};

````

可信声明的属性如下：

**signature** 可信声明的签名。用来验证可信声明。在初始化时可以为空。

**useProof** 指定声明序列化的规范为JWT或者JWT-X.改值为true表明使用JWT-X.

**messageId** 声明的ID

**issuer** 声明签发者的ONT ID.

**subject** 声明接收者的ONT ID.

**issueAt** 创建声明时的时间。以时间戳表示。

**version** 声明的版本。

**context** 声明的模板在线保存的url。

**content** 声明的内容。JSON格式。

## 在链上存证可信声明
声明的签发者可以将声明存证到链上。
方法的参数如下:

**url** 发送交易到的节点的websocket url

**privateKey** 签发者的私钥。用来签名交易。

**gasPrice** 交易的gas price

**gasLimit** 交易的gas limit

**payer** 交易gas的payer

````
const url = 'http://polaris1.ont.io:20335';
const gasPrice = '500';
const gasLimit = '20000';
const payer = new Address('AMLn5W7rz1sYd1hGpuQUfsnmUuUco22pM8');
const privateKey = new PrivateKey('44fd06de5a6529f3563aad874fb6c8240....')
const result = await claim.attest(url, gasPrice, gasLimit, payer, privateKey);
````
返回结果为true表明声明存证成功。

### 2.3 撤销声明
声明的签发者可以撤销可信声明。
方法的参数如下：
**url** 发送交易到的节点的websocket url

**privateKey** 签发者的私钥。用来签名交易。

**gasPrice** 交易的gas price

**gasLimit** 交易的gas limit

**payer** 交易gas的payer

````
const url = 'http://polaris1.ont.io:20335';
const gasPrice = '500';
const gasLimit = '20000';
const payer = new Address('AMLn5W7rz1sYd1hGpuQUfsnmUuUco22pM8');
const privateKey = new PrivateKey('44fd06de5a6529f3563aad874fb6c8240....')
const result = await claim.revoke(url, gasPrice, gasLimit, payer, privateKey);
````
返回结果为true表明撤销声明成功。

### 2.4 验证可信声明

在上面一节我们举例说明了如何获取第三方授予的身份声明，用户在需要的时候可以出示这些声明。同时，这些声明可以通过SDK提供的方法来验证是否是真实的、未篡改的。

我们以Alice同学求职的情况为例说明验证可信声明的过程。

Alice向公司B求职时，提供了复旦大学授予的数字毕业证书，该证书是一份符合claim声明格式的JSON文件。公司B可以通过调用ONT SDK的方法来验证该声明。任何需要验证声明的用户都可以调用相关方法，查询声明在链上的状态，验证声明。

方法的参数如下：
**url** 节点的Restful接口url

````
const url = 'http://polaris1.ont.io:20335';
const result = await claim.getStatus(url);

````
如果声明的状态为“已存证”且声明签发者也正确，则表明声明通过验证。