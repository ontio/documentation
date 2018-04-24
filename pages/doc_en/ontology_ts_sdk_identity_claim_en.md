---
title: 
keywords: sample homepage
sidebar: ont_doc_en
permalink: ontology_ts_sdk_identity_claim_en.html
folder: doc_en
---

English / [中文](./ontology_ts_sdk_identity_claim_zh.html)

<h1 align="center">Identity and Claim </h1>
<p align="center" class="version">Version 0.7.0 </p>



### 1.1 Generate identity

ONT ID is a decentralized identity that managed users’ various digital identity authentications.Identity is one of the core classes exposed from ONT SDK, which contains the ONT ID that represent the identity.

> For more information about identity, see [ONT TS SDK]()

You can use SDK to create a digital identity. During the process, SDK will generate a ONT ID base on user's private key.

> For ONT ID specifications, see [ONT ID Generation Specifications](./ONTID_protocol_spec.md/#1.1_ONT_ID生成).

The method needs parameters as follows:

**privateKey** user's private key. Can use the SDK to generate the private key safely.

**password** the password to encrypt and decrypt the private key.

**algorithmObj** describes the algorithm used to generate identity, has following structure ：

```
{
  algorithm: string // algorithm's name
  parameters: {}    // algorithm's parameters
}
```

```
import {Identity} from 'Ont'
var identity = new Identity()
identity.create(privateKey, password)
console.log(identity.ontid)
```

### 1.2 Register ONT ID to the blockchain

After the identity is created the user needs to send the ONT ID to the blockchain to make it a truly decentralized identity.

Sending ONT IDs to the blockchain is the same process as sending transactions. The transaction object can be constructed by calling the methods provided by the SDK.

A typical scenario is to create a transaction object by transferring the ONT ID just created and the user’s private key.

The private key transferred here has two roles:

1. Sign the transaction;

2.The user’s ONT ID is bound to the public key corresponding to the user’s private key. The user can then add other public keys to the ONT ID.

````
var param = buildRegisterOntidTx(ontid, privateKey)
````

This method returns the serialized parameters of the transaction object. Next is sending the parameter, this can be sent via WebSocket or a http request. 

````
//TxSender is a utility class for sending transactions
var txSender = new TxSender(ONT_NETWORK.TEST)

//define the callback function to handle received messages
const callback = function(res, socket) {
    if(res.Action === 'Notify' && res.Result == 0 ) {
    	//close the socket after confirming that the tx is committed in the blockchain
        socket.close()
    }
}

//send the transaction
txSender.sendTxWithSocket( param, callback )
````

The ONT ID creation process is completed when the push message we have defined in the callback function is processed successfully. Next, you can manager users’ verifiable claims through ONT ID.

For detailed information about the data returned by the blockchain, see [ONT ID Smart Contract Design and Related Documents](./ONTID_protocol_spec.md/#g._事件推送).

## Issuing a verifiable claim

Users can have several types of identities. For example, users with an ID card issued by the China Ministry of Public Security all have the identity “Chinese National”. Users can present their ID cards in certain scenarios to declare their identity; the ID card is the Ministry of Public Security’s citizenship certification.

For example, a student who graduates from a university can obtain the status of a graduate of the university. This status can be proved by a diploma issued by the school to students. Now there is a new way to authenticate the identity of this university graduate through blockchain technology, by binding a verifiable claim (a trusted statement) to the user’s ONT ID. Similarly, users can obtain different verifiable claims from multiple different organizations and/or platforms.

> The owner of an ONT ID can issue a verifiable claim to himself or others.

> Government agencies, universities, banks, third-party authentication service agencies (such as CA), biometrics technology companies, etc., can serve as trusted institutions and be added to the Ontology ecosystem as partners. If you think you could be a certification service partner, please see the [Certification Service Partner Assessment Standard](./verification_provider_specification.md).

We use a digital diploma issued by China’s Fudan University as an example to illustrate how users can obtain a third-party claim.

Suppose Alice is a student at Fudan University and applies to the school for a digital graduation certificate. After the school verifies Alice’s identity, it invokes the SDK’s API to generate a trusted statement that contains Alice’s graduation information and the signature of the school, which was made with the school’s private key.

````
var claim = SDK.signClaim(context, claimData, issuer, subject, privateKey)
````

This  method is described as follows:

**context** marks a claim template.

**claimData** is the specific content of the user claim, the value is a JSON object. Here is the information on Alice’s graduation certificate:

````
{
    "degree" : "bachelor",
    "year" : "2017",
    ......
}
````

**issuer** is the ONT ID of the issuer of the claim (in this case Fudan University).

**subject** the ONT ID of the claim recipient (in this case Alice).

**privateKey** is the issuer’s private key.

The claim object returned by this method looks like this:

````
{
    .....
}
````

For claim object specification, see [claim specifications]().

The next step is to send to the blockchain for attestation. After successful recording to the blockchain a claim will be sent. The claim format is:
[claim complete certification]()。

First you need to construct the transaction to send. The parameters needed are:

**path** is the key name where the claim information is stored on the blockchain. The value is the ID in the claim object. This is the hash of serialization of a claim object.

**value** is the claim information that needs to be stored to the chain. The value is the following JSON structure:

````
{
    Context : string, //Definition of the Claim template
    Ontid : string //Signer’s ONT ID
}
````

**ontid** is the transaction sender’s ONT ID and the ONT ID of the claim issuer.

**privateKey** is the transaction sender’s private key and the private key of the claim issuer.

````
var param = SDK.buildClaimTx(path, value, ontid, privateKey)
````

Next, build a tool to send transactions and a recall method for monitoring information.

To recall information, after the claim is recorded to the blockchain the claim complete certification will be recalled. This complete certification will be added to the previously constructed claim object and users receive a complete third-party certification statement object. After this, users can provide the statement in a scenario where needed.

````
//connect to a fullnode of the ONTology testnet
var txSender = new TxSender(ONT_NETWORK.TEST)
const callback = function(res, socket) {
    let res 
    if(typeof event.data === 'string') {
    res = JSON.parse(event.data)
    //parse the event message returned by a full node
    //test if the tx is committed in the blockchain by checking the blockchain’s height 
    if(res.Result.BlockHeight) {
      socket.close()
    }
}
txSender.sendTxWithSocket(param, callback)
````

The certification is like the following:

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

## Verifiable claim verification

In the above section we illustrated how to obtain an identity claim granted by a third party which can presented when needed. At the same time, these statements can be verified through an SDK to verify their authenticity and that they have not been tampered with.

The process of verifying a verifiable claim is illustrated with the example of Alice seeking employment.

When Alice applies for company B she provides a digital diploma certificate issued by Fudan University. The certificate is a JSON file that conforms to the claim format. Company B can verify the statement by calling on the ONT SDK. The method logic is to first obtain the DDO information of the issuer through the issuer field in the claim, obtain the issuer’s public key from the DDO information, then remove the signature of the claim to access the content, and verify the signature value with the public key and signature.

The input parameter for this method is the claim JSON string, and the result is Promise. In recalling Promise verification results are processed.

````
Core.verifyClaim(claim).then((result) => {
    //result contains whether the verification passed
    if(result){
        //verification passed
    } else {
        //verification failed to pass
    }
})
````