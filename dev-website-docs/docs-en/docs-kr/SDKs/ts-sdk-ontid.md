
# Identity
Identity has the following structure:

```
{
    "ontid": "did:ont:ATcHA9eYKyve8M74CB4p6Ssx7kwXjmREUa",
    "label": "mickey",
    "lock": false,
    "controls": [{
        "id": "1",
        "algorithm": "ECDSA",
        "parameters": {
            "curve": "P-256"
        },
        "key": "M+PnrYLVDrU0gkSzj0FAsvqCYv+HWEEUMDSyKSJACzJhZVglFU9tkfQKlLby5UCY",
        "address": "ATcHA9eYKyve8M74CB4p6Ssx7kwXjmREUa",
        "salt": "wwa12j4K0SyDP23+UDJNtA==",
        "enc-alg": "aes-256-gcm"
    }]
}
```
`ontid` ONT ID 

`label` Name of the identity

`lock` Decides if the identity is locked

`controls` The control data of identity

`id` ID of the control data

`algorithm` The keypair generation algorithm used in the identity

`parameters` The parameters used in keypair generation algorithm

`curve` The elliptic curve used in the algorithm

`key` The encrypted private key

`address` Used to encrypt and decrypt the private key

`salt` Used to encrypt and decrypt the private key

`enc-alg` The algorithm used to encrypt the private key. Now is 'aes-256-gcm'.

## 1.1 Generate identity

ONT ID is a decentralized identity that manages various digital identity authentications of a user. Identity is one of the core categories exposed from ONT SDK containing the ONT ID, which represents identity.

> For more information, see [ONT TS SDK]().

You can use SDK to create a digital identity. During the process, SDK will generate an ONT ID base on a user's private key.

> For ONT ID specifications, see [ONT ID Generation Specifications](./ONTID_protocol_spec.md/#1.1_ONT_ID生成).

The method needs the following parameters:

**privateKey** User's private key, using the SDK to generate the private key safely.

**password** The password is used for encrypting and decrypting the private key.

**label** Name of the identity.

**params** Optional scrypt params used to encrypt the private key.

```
import {Identity, Crypto} from 'ontology-ts-sdk';
//generate a random private key
const privateKey = Crypto.PrivateKey.random();

var identity = Identity.create(privateKey, password, label)
console.log(identity.ontid)
```

## 1.2 Register ONT ID to the blockchain

After the identity is created, the user needs to send the ONT ID to the blockchain to make it a truly decentralized identity.

Sending ONT IDs to the blockchain requires sending specific transactions. The transaction object can be done by calling the methods provided by the SDK.

### Create Transaction

````typescript
import {OntidContract} from 'ontology-ts-sdk';
import {TransactionBuilder} from 'ontology-ts-sdk'

//suppose we already got a identity
const did = identity.ontid;
//we need the public key, which can be generate from private key
const pk = privateKey.getPublicKey();
const gasPrice = '0';
const gasLimit = '20000;
const tx = OntidContract.buildRegisterOntidTx(did, pk, gasPrice, gasLimit);

````
### Sign Transaction With Payer
The transaction also needs signatures from the payer.

```typescript
import {TransactionBuilder} from 'ontology-ts-sdk'
//we also need an account to pay for the gas
//supporse we have an account and the privateKey
tx.payer = account.address
// First, we need sign transaction with the private key of the ONT ID.
TransactionBuilder.signTransaction(tx, privateKey);
//Then sign the transaction with payer's account
//we already got transaction created before,add the signature.
TransactionBuilder.addSign(tx, privateKeyOfAccount)
```

### Send Transaction
We can use RESTful API, RPC API and WebSocket API to send transactions to the blockchain.
We can set the URL of the node that we want to send transaction to. You can run in testnet, mainnet, or even as a local node. It will in testnet by default.

A notice will pop up when we use the WebSocket API.

```typescript
import {RestClient, CONST} from 'ontology-ts-sdk'

const rest = new RestClient(CONST.TEST_ONT_URL.REST_URL);
rest.sendRawTransaction(tx.serialize()).then(res => {
	console.log(res)
})
```
The response will look like: 

````
{ Action: 'sendrawtransaction',
  Desc: 'SUCCESS',
  Error: 0,
  Result: 'dfc598649e0f3d9ff94486a80020a2775e1d474b843255f8680a3ac862c58741',
  Version: '1.0.0' }
````
Now the transaction is sent to the blockchain. Then we can check if the ONT ID is registered on the chain by querying the DDO( Description object of ONT ID). This info is stored on the chain.

## 1.3 Query DDO
We also send the specific transaction to query the DDO.

### Create transaction
```typescript
import {OntidContract} from 'ontology-ts-sdk';
//we use identity's ONT ID to create the transaction
const tx = OntidContract.buildGetDDOTx(identity.ontid)

```
### Send transaction
There is no need to pay transaction gas if the transaction is a query, and there is no need to sign this kind of transaction - we can send it directly.

```typescript
import {RestClient} from 'ontology-ts-sdk';
const rest = new RestClient();
rest.sendRawTransaction(tx, true).then(res => {
	console.log(res);
})
```

RestClient.sendRawTransaction(hexData, preExec). The second parameter decides if it is a pre-execute transaction, which will be executed on the blockchain node and do not have to wait for the consensus. We use pre-execute transaction to query the data. For more info please check the TS SDK API as a reference.

The response will look like:

```
{ Action: 'sendrawtransaction',
      Desc: 'SUCCESS',
      Error: 0,
      Result:
       { State: 1,
         Gas: 20000,
         Result: '26010000002103547c5abdbe66677ba7001cefd773f01a19c6360b15ee51c6db43911f046564fc0000' },
      Version: '1.0.0' }
``` 
`Result` of the response is a hex encoded DDO object. You can deserialize a DDO object from it.
Now the ONT ID is registered to the blockchain successfully.


## 2 Issuing a verifiable claim

A user can have several types of identities. For example, a user with an ID card issued by the China Ministry of Public Security will all have the identity as "Chinese National". A user can present his ID card in certain scenarios to declare his identity; the ID card is the Ministry of Public Security's citizenship certification.

For example, a student who graduates from a university wants to obtain the status of the diploma from the university. This status can be received by issuing the diploma issued from the school to the student. Now there is a new way to authenticate the identity of this university graduate through blockchain technology, by binding a verifiable claim (a trusted statement) to the user's ONT ID. Similarly, users can obtain different verifiable claims from multiple different organizations and/or platforms.

Owner of an ONT ID can issue a verifiable claim to himself or others.

Government agencies, universities, banks, third-party authentication service agencies (such as CA), biometrics technology companies and etc., can serve as trusted institutions and join the Ontology ecosystem as partners. If you think you could be a certification service partner, please visit [Certification Service Partner Assessment Standard](./verification_provider_specification.md).

We use a digital diploma issued by China's Fudan University as an example to illustrate how users can obtain a third-party claim.

Suppose Alice is a student from Fudan University and wants to apply a digital graduation certificate from the school. After the school verifies Alice's identity, it invokes the SDK's API to generate a trusted statement that contains Alice's graduation information with the signature by using school's private key.

### 2.1 Construct a claim

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

These attributes of claim are described as follows:

**signature** The signature of the claim. It can be null or undefiend at the beginning.

**useProof** Decides if the claim will be used as a proof.

**messageId** String value.

**issuer** Issuser's ONT ID.

**subject** Subject's ONT ID.

**issueAt** Timestamp of when the claim is created.

**version** Version of the claim.

**context** The online location of the claim template.

**content** The content of the claim.


For claim object specification, see [claim specifications]().

### 2.2 Attest Claim
The issuer should attest the claim the the blockchain.

The parameters are as below:

**url** Websocket endpoint of Ontology node

**privateKey** Private key to sign the transaction

**gasPrice** gasPrice

**gasLimit** gasLimit

**payer** payer

````
const url = 'http://polaris1.ont.io:20335';
const gasPrice = '500';
const gasLimit = '20000';
const payer = new Address('AMLn5W7rz1sYd1hGpuQUfsnmUuUco22pM8');
const privateKey = new PrivateKey('44fd06de5a6529f3563aad874fb6c8240....')
const result = await claim.attest(url, gasPrice, gasLimit, payer, privateKey);
````
The result is a promised boolean value. If it's true then the claim has been attested successfully.

### 2.3 Revoke Claim
The issuer can also issuer the claim.

The parameters are as below:

**url** Websocket endpoint of Ontology node

**privateKey** Private key to sign the transaction

**gasPrice** gasPrice

**gasLimit** gasLimit

**payer** payer

````
const url = 'http://polaris1.ont.io:20335';
const gasPrice = '500';
const gasLimit = '20000';
const payer = new Address('AMLn5W7rz1sYd1hGpuQUfsnmUuUco22pM8');
const privateKey = new PrivateKey('44fd06de5a6529f3563aad874fb6c8240....')
const result = await claim.revoke(url, gasPrice, gasLimit, payer, privateKey);
````
The result is promised boolean value. If it's true then the claim has been revoked successfully.


### 2.4 Verifiable claim verification

In the above section we illustrated how to obtain an identity claim granted by a third party which can be presented when needed. At the same time, these statements can be verified through an SDK to verify the authenticity.

The process of verifying a verifiable claim is illustrated with the example of Alice seeking employment.

When Alice applies for company B she provides a digital diploma certificate issued by Fudan University. The certificate is a JSON file that match to the claim format. Company B can verify the statement by calling on the ONT SDK. Anyone who wants to verify the claim can query the status of the claim from blockchain.

The parameters are as below:

**url** Restful endpoint of Ontology node.

````
const url = 'http://polaris1.ont.io:20335';
const result = await claim.getStatus(url);

````
If the claim is attested and the issuer is correct, the returned result will be true.



