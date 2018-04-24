---
title: 
keywords: sample homepage
sidebar: ont_doc_en
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

See [**Appendix A**](#A. Verifiable claim template) section for an example of verifiable claim that shows an empolyee's salary certificate issued by a company.

### 1.1 Verifiable claim issuance process

To summarize briefly, there are three major steps in issuing a claim:

1. The recipient initiates an application and provides data, and the issuer constructs a verifiable claim;
2. The issuer keeps the attest in the attest contract, that is, set the status of the verifiable claim as *available*;
3. Transmit the verifiable claim to the Recipient in a secure method, that is, the verifiable claim is encrypted by the recipient's public key.

The above steps correspond to steps 1 - 4 in the workflow of the verifiable claim.


### 1.2 Attest contract

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

- Init: p <- proof.TxnHash
- For each element in proof.Nodes,  update p as
    - if e.Direction == "Left",  p <- H(e.TargetHash, p);
    - else, p <- H(p, e.TargetHash).
- Return true if p equals to proof.MerkleRoot. Otherwise, return false.

An example of Merkle proof 
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

In addition, it is also necessary to verify the status of the claim attest, that is, to call the inquiry interface `GetStatus()` of the attest contract with the address  `proof.ContractAddr`. If the status is "not attested," an error would be returned.


### 2.2 Signature verification and expiration time

When verifying the signature, you need to use the public key ID to get the public key value and the current status of the public key, and then call the corresponding verification algorithm to verify.

The format of public key ID is ```<ONTID>#keys-<number>```，which calls the interface of ONT ID smart contract that inquiry the status of the public key```GetPublicKeyStatus(byte[] ontId, byte[] pkId)```, it returns

- publicKey: Public key value (hexstring);
- status: There are two possible values，```InUse```, ```Revoked```.

There are three results of signature verification:
 - The signature is invalid;
 - The signature is valid and the public key is in the status of <code>Revoked</code>;
 - Signature is valid.
  

Verification of the expiration time: Verify whether the timeout period has expired.


### 2.3 Revoke verification 

Currently, there are two revocation modes, revocation list and revocation inquiry interface.

Using the revocation inquiry interface as an example, if the revocation information is placed in the attest contract, when calling the inquiry interface  `GetStatus` of attest contract, revocation verification will return "success" if and only if the returned status field is "attested". It will return "fail" if the status field is "attest has been revoked."

The revocation list mainly includes the unique identifier of the revoked verifiable claim and the revocation time.

## Appendix
### A. Verifiable claim template

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



Field description:

| Field     |     Type |   Description   | Necessary|
| :-------------- | :--------:| :------ |:------: |
|    Id|   String|  Unique identifier of verifiable claim  |Y|
|    Context|   String|  Content template identifier  |Y|
|    Content|   Object|  Content of verifiable claim，key-value form  |Y|
|    Metadata|   Object|  Metadata of verifiable claim  |Y|
|    Metadata.CreateTime|   String|  Created time, format：yyyy-MM-dd'T'HH:mm:ss'Z'  |Y|
|    Metadata.Issuer|   String|  The ONT ID of verifiable claim issuer |Y|
|    Metadata.Subject|   String|  The ONT ID of verifiable claim Recipient  |Y|
|    Metadata.IssuerName|   String|  Verifiable claim issuer name  |N|
|    Metadata.Expires|   String|  Expiration time, format：yyyy-MM-dd  |N|
|    Metadata.Revocation|   String|  Declaration of the revocation type(revocation list or revocation with a attest contract)  |N|
|    Signature|   Object |  Signature information  |Y|
|    Signature.PublicKeyId|   String |  The ID of a signature public key  |Y|
|    Signature.Format|   String |  Signature format  |Y|
|    Signature.Algorithm|   String |  Signature algorithm  |Y|
|    Signature.Value|   String |  Signature value  |Y|
|    Proof|   Object |  Integrity proof  |Y|


Detailed description:
- Id: The unique identifier of the verifiable claim. The generating logic is to do Hash for the contents of the Context, Content, and Metadata fields to ensure uniqueness.
- Context: The Content format defines the document address, the target document defines the meaning of each (key, value) in the Content, and the type of the value;
- Content: The contents of the verifiable claim.
- Metadata: Metadata, which contains basic information such as issuing time, issuer and recipient identity.
- Signature: Signature information is the signature of the issuer to the content of Id, Context, Content, Metadata, which can be used for verification of the subsequent verifiable claim.
- Proof: Proof of integrity that verify the existence and integrity of a verifiable claim by Merkle proof in Ontology.

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