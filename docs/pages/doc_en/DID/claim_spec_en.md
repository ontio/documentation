---
sidebar: DID_en
permalink: claim_spec_en.html
folder: doc_en
---

English / [中文](./claim_spec_zh.html)

<h1 align="center">Verifiable Claim Protocol</h1>
<p align="center" class="version">Version 0.7.0 </p>

The entire workflow of the verifiable claim is shown in the figure below. It contains three major parts:

- Request claim;
- Issue claim;
- Verify claim.

![claim workflow](./lib/images/claim_workflow.png)

## 1. Issue 
The issuance process of a verifiable claim involves two roles, the issuer and the recipient.

In general, a verifiable claim should include the contents of the claim, digital signatures, and blockchain attest records. More specifically,

- Claim ID: Uniquely identifies the claim;

- Claim content: Specific information such as a degree certificate;

- Claim metadata
    - Created time: The time the claim was created;
    - Issuer: Ont ID of the issuer;
    - Recipient：Ont ID of the recipient；
    - Expiration time: The time when the claim expires automatically;
    - Revocation mechanism: Use the *revocation list* or record the revocation information directly in *attest contract*;

- Blockchain proof

- Signature
    - The Public key ID of a issuer 
    - Signature value

See [**Appendix A**](#a-verifiable-claim-template) section for an example of verifiable claim that shows an empolyee's salary certificate issued by a company.

### 1.1 Verifiable claim issuance process

To summarize briefly, there are three major steps in issuing a claim:

1. The recipient initiates an application and provides data, and the issuer constructs a verifiable claim;
2. The issuer keeps the attest in the attest contract, that is, set the status of the verifiable claim as *attested*;
3. Transmit the verifiable claim to the Recipient in a secure method, that is, the verifiable claim is encrypted by the recipient's public key.

The above steps correspond to steps 1 - 4 in the workflow of the verifiable claim.

### 1.2 The format of a verifiable claim

We will use an extension of the [JSON Web Token](https://tools.ietf.org/html/rfc7519) format to represent a verifiable claim which is transferred between issuer and recipient. 

Basic structure of the token consists of three parts: Header, Payload and Signature. The standard JWT attributes are reused as much as possible and in special cases custom attributes are defined.

We augment the JWT format by appending the blockchain proof in the end,  a typical verifiable claim is organized as 
` header . payload . signature . blockchain_proof`.
> Note: blockchain_proof is optional. In some cases, Claim not include blockchain_proof.

#### Header
The header part defines the type of the format, the signature scheme employed and id of the public key used to verify the signature. 
```json
{
    "alg": "ES256",
    "typ": "JWT-X",
    "kid": "did:ont:TRAtosUZHNSiLhzBdHacyxMX4Bg3cjWy3r#keys-1"
}
```
- **alg** attribute specifies the signature scheme to use. A list of supported values can be found [here](#supported-signature-schemes).
- **typ** attribute can take one of the two values
    - JWT: This corresponds to the case that blockchain proof is not contained in the claim.
    - JWT-X: This corresponds to the case that blockchain proof is a part of the claim. 
- **kid** attribute refers to the public key used for signature verification. It has the form `<ontID>#keys-<id>` as defined in ONT ID specification.

#### Payload

The claim id, claim content and claim metadata are encoded as a JSON object that is used as the payload part. And  will use some of registered claim names specified in the JWT spec, namely `jti`, `iss`, `sub`, `iat`, `exp`. 
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

- **ver** attribute specifies the version of the claim spec it follows. 
- **iss** attribute refers to the ONT ID of the issuer.
- **sub** attribute refers to the ONT ID of the recipient. 
- **iat** attribute marks the time the claim was created and has the format of unix timestamp.
- **exp** attribute marks the expiration time of the claim and has the format of unix timestamp.
- **jti** attribute specifies the unique identifier of the verifiable claim. 
- **@context** attribute specifies the uri of claim content definition document which  defines the meaning of each field and the type of the value;
- **clm** attribute is an object which contains the claim content.
- **clm-rev** attribute is an object which defines the revocation mechanism the claim use. A list of supported mechanism is listed in the [Appendix C](#c-revocation).


To issue a claim, first construct the JSON object that represents the claim id, content and metadata, then use the standard JSON serialization method to serialize it. Finally, use one of the issuer's private keys to sign the binary data of the header and payload. For example, after serialization, the above payload will look like 
```
{"ver":"0.7.0","iss":"did:ont:TRAtosUZHNSiLhzBdHacyxMX4Bg3cjWy3r","sub":"did:ont:SI59Js0zpNSiPOzBdB5cyxu80BO3cjGT70","iat":1525465044,"exp":1530735444,"jti":"4d9546fdf2eb94a364208fa65a9996b03ba0ca4ab2f56d106dac92e891b6f7fc","@context":"https://example.com/template/v1","clm":{"Name":"Bob Dylan","Age":"22"},"clm-rev":{"Type":"Contract","Addr":"8055b362904715fd84536e754868f4c8d27ca3f6"}}
```

#### Signature

After constructing Header and Payload of the request, Signature part is computed according to JWS standard. Full description can be found in [RFC 7515 Section 5.1](https://tools.ietf.org/html/rfc7515#section-5.1). The simplified version is as follows:

* Compute the signing input as serialization of Header and Payload according to JWS specification. 
```
sig := sign(Base64URL(header) || . || Base64URL(payload))
```

* Compute the JWS Signature in the manner defined for the particular signature scheme being used over the signing input.

* Encode the signature
```
signature := Base64URL(sig).
```


#### Blockchain proof

```json
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
- **Type** attribute is always "MerkleProof".
- **TxnHash** attribute refers to the hash of the transaction that attests the claim id in the attest contract. 
- **ContractAddr** attribute refers to the address of the attest contract.
- **BlockHeight** attribute refers to the height of block which contains the attest transaction.
- **MerkleRoot** attribute refers to the root of Merkle tree when the tree size equals to BlockHeight.
- **Nodes** attribute refers to the inclusion proof of block in the Merkle tree.

Encode the MerkleProof as below:
```
BASE64URL(MerkleProof)
```

Now a complete verifiable claim is created:
```
 BASE64URL(Header) || '.' || BASE64URL(Payload) || '.' || BASE64URL(Signature)  '.' || BASE64URL(MerkleProof) 
 ```

### 1.3 Attest contract

The attest contract of verifiable claim  provides the attest service and the record availability information, that is, whether it has been revoked.

The interfaces provided are mainly

- Commit attest

    ```
    bool Commit(byte[] claimId, byte[] committerOntId);
    ```

    In the attest contract, the unique identifier of a claim is the claim ID. It is the first parameter; The committerOntId is the ONT identity of the attester.
    
    This function will return `true` if and only if the claim is not attested, and the function is called by the committer; Otherwise, it will return `false`.

    After the attestation is done, the status of the claim will be *attested*.

- Revoke claim
    ```
    bool Revoke(byte[] claimId, byte[] revokerOntId);
    ```
    This function will return true if and only if the claim is *attested*, and the revokerOntId is equal to the attester's ONT identity; Otherwise, it will return false.

- Attest inquiry interface
    ```
    byte[] GetStatus(byte[] claimId);
    ```
  Returns the status of the claim that contains two parts of information:
    - Status: "Not attested", "Attested", "Attest has been revoked";
    - ONT ID of the attester.

## 2. Verification

To summarize briefly, there are three major steps in verifying a claim, corresponding to the steps 5 - 6 in the workflow.

- Check whether it is in the blockchain;
- Verify the signature and verify whether it has expired;
- Check whether it has been revoked (optional).


### 2.1 Blockchain existence verification

To summarize briefly，we need to verify whether a verifiable claim is in the blockchain. In the case that the entire blockchain is not synchronized, we can use the Merkle proof to verify the transaction.

Merkle proof is an array, and each array item contains two elements (direction, hash):
- `direction`: represents which branch of the Merkle tree the array item is in. There are two possible values: left, right;
- `hash`: represents the hash value of the data item.

The  algorithm that verifies the Merkle proof (described below)

1. Check if transaction is included in block indexed by `proof.BlockHeight`. If not, return `false`.
2. p <- GetBlockHash(`proof.BlockHeight`).
3. For each element in `proof.Nodes`, update p as
    - if e.Direction == "Left",  p <- H(e.TargetHash, p);
    - else, p <- H(p, e.TargetHash).
4. Return `true` if p equals to `proof.MerkleRoot`. Otherwise, return false.

In addition, it is also necessary to verify the status of the claim attest, that is, to call the inquiry interface `GetStatus()` of the attest contract with the address  `proof.ContractAddr`. If the status is "not attested," an error would be returned.


### 2.2 Signature verification and expiration time

When verifying the signature, you need to use the public key ID to get the public key value and the current status of the public key, and then call the corresponding verification algorithm to verify.

The format of public key ID is ```<ONTID>#keys-<number>```，which calls the interface of ONT ID smart contract that inquiry the status of the public key `GetPublicKeyStatus(byte[] ontId, byte[] pkId)`, it returns

- publicKey: Public key value (hexstring);
- status: There are two possible values: `InUse`, `Revoked`.

There are three results of signature verification:
 - The signature is invalid;
 - The signature is valid and the public key is in the status of <code>Revoked</code>;
 - Signature is valid.
  

Verification of the expiration time: Verify whether the timeout period has expired.


### 2.3 Revoke verification 

Currently, there are two revocation modes, revocation list and revocation inquiry interface.

Using the revocation inquiry interface as an example, if the revocation information is placed in the attest contract, when calling the inquiry interface  `GetStatus` of attest contract, revocation verification will return "success" if and only if the returned status field is "attested". It will return "fail" if the status field is "attest has been revoked."

The revocation list mainly includes the unique identifier of the revoked verifiable claim and the revocation time.

## Supported signature schemes

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

## Appendix
### A. Verifiable claim template

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


### B. Content format definition template
A major part of a verifiable claim is the content of the claim, and the definition of the claim content format is in another JSON file, which defines the meaning of each attribute and the type of the corresponding attribute value.

The format definition of Content in Appendix A is given below.
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

### C. Revocation
Two revocation mechanisms can be used. 
- Revocation list
       
    The list contains the claims revoked by issuer which specifies           the id of revoked claim, the time of revocation. To use this mechanism, the claim must contain the url of the list, and the type must be `RevocationList`.   
    ```json
    "clm-rev": {
        "type": "RevocationList",
        "url": "https://example.com/rev/1234"
    }
    ```

- Revocation with attest contract
        
    The revocation information is recorded in the attest contract via the `Revoke` function. To find out if a claim has been revoked, the standard approach is to invoke the `GetStatus` function. Please refer to [section 1.3](#13-attest-contract) for more information.

    ```json
    "clm-rev": {
        "type": "AttestContract",
        "addr": "8055b362904715fd84536e754868f4c8d27ca3f6"
    }
    ```

### [More claim template examples](https://github.com/ontio/ontology-DID/blob/master/claimtemplate/en/ClaimTemplate_definition.md)