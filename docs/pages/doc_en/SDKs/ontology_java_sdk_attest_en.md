---
title:
keywords: sample homepage
sidebar: SDKs_en
permalink: ontology_java_sdk_attest_en.html
folder: doc_en/SDKs
giturl: https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/attest.md
---

<h1 align="center">Claim and Attestation </h1>

<p align="center" class="version">Version 1.0.0 </p>

English / [中文](./ontology_java_sdk_attest_zh.html)




## Verifiable claim

### Data structure specification

```
class Claim{
  header : Header
  payload : Payload
  signature : byte[]
}
```

```
class Header {
    public String Alg = "ONT-ES256";
    public String Typ = "JWT-X";
    public String Kid;
    }
```

`alg` attribute specifies the signature scheme to use
`typ` attribute can take one of the two values:

    * JWT: This corresponds to the case that blockchain proof is not contained in the claim
    * JWT-X: This corresponds to the case that blockchain proof is a part of the claim

`kid`  attribute refers to the public key used for signature verification. It has the form <ontID>#keys-<id> as defined in ONT ID specification.


```
class Payload {
    public String Ver;
    public String Iss;
    public String Sub;
    public long Iat;
    public long Exp;
    public String Jti;
    @JSONField(name = "@context")
    public String Context;
    public Map<String, Object> ClmMap = new HashMap<String, Object>();
    public Map<String, Object> ClmRevMap = new HashMap<String, Object>();
    }
```

`ver` attribute specifies the version of the claim specification it follows

`iss` attribute refers to the ONT ID of the issuer

`sub` attribute refers to the ONT ID of the recipient

`iat` attribute marks the time the claim was created and has the unix timestamp format

`exp` attribute marks the expiration time of the claim and has the the unix timestamp format

`jti` attribute specifies the unique identifier of the verifiable claim

`@context` attribute specifies the uri of the claim content definition document which defines the meaning of each field and the type of the value

`clm` attribute is an object which contains the claim content

`clm-rev` attribute is an object which defines the revocation mechanism the claim uses <p><br>



### Sign and issue verifiable claim
A verifiable claim is constructed based on user input, which contains signed data.

**createOntIdClaim**

| Parameter      | Field   | Type  | Description |            Remarks |
| ----- | ------- | ------ | ------------- | ----------- |
| Input parameter | signerOntid| String | ONT ID | Required |
|        | password    | String | ONT ID password   | Required |
|        | salt        | byte[] | Private key decryption parameters |Required|
|        | context| String  |Attribute specifies the URI of claim content definition document which defines the meaning of each field and the type of the value | Required|
|        | claimMap| Map  |Content of claim | Required|
|        | metaData   | Map | Claim issuer and subject's ONT ID | Required |
|        | clmRevMap   | Map | Attribute is an object which defines the revocation mechanism the claim use | Required |
|        | expire   | long | Attribute marks the expiration time of the claim and has the format of unix timestamp     | required |
| Output parameter| claim   | String  |   |  |

Refer to: https://github.com/kunxian-xia/ontology-DID/blob/master/docs/en/claim_spec.md

##### Example of creating an onit claim    
```
String createOntIdClaim (String signerOntid, String password,byte[] salt, String context, Map<String, Object> claimMap, Map metaData,Map clmRevMap,long expire)
```

```
Map<String, Object> map = new HashMap<String, Object>();
map.put("Issuer", dids.get(0).ontid);
map.put("Subject", dids.get(1).ontid);
Map clmRevMap = new HashMap();
clmRevMap.put("typ","AttestContract");
clmRevMap.put("addr",dids.get(1).ontid.replace(Common.didont,""));
String claim = ontSdk.nativevm().ontId().createOntIdClaim(dids.get(0).ontid,password,salt, "claim:context", map, map,clmRevMap,System.currentTimeMillis()/1000 +100000);
```
Note: The issuer may have multiple public keys. The parameter ontid of createOntIdClaim specifies which public key to use. <p> <br>


### Verify verifiable claim

**verifyOntIdClaim**

| Parameter      | Field   | Type  | Description |            Remarks |
| ----- | ------- | ------ | ------------- | ----------- |
| Input parameter | claim| String | Trusted claim | Required |
| Output parameter | true or false   | boolean  |   |  |
  
 
```
boolean verifyOntIdClaim (string claim)
```

##### Example of verifying an ontid claim
```
boolean b = ontSdk.nativevm().ontId().verifyOntIdClaim(claim);
```

##### Example of claim issuance and verification:

```
Map<String, Object> map = new HashMap<String, Object>();
map.put("Issuer", dids.get(0).ontid);
map.put("Subject", dids.get(1).ontid);

Map clmRevMap = new HashMap();
clmRevMap.put("typ","AttestContract");
clmRevMap.put("addr",dids.get(1).ontid.replace(Common.didont,""));

String claim = ontSdk.nativevm().ontId().createOntIdClaim(dids.get(0).ontid,password,salt, "claim:context", map, map,clmRevMap,System.currentTimeMillis()/1000 +100000);
boolean b = ontSdk.nativevm().ontId().verifyOntIdClaim(claim);
```

----

## Attestation Example

The attest contract of a verifiable claim provides the attest service and records availability information, that is, whether it has been revoked.


#### SDK init


```
String ip = "http://127.0.0.1";
String restUrl = ip + ":" + "20334";
String rpcUrl = ip + ":" + "20336";
String wsUrl = ip + ":" + "20335";
OntSdk wm = OntSdk.getInstance();
wm.setRpc(rpcUrl);
wm.setRestful(restUrl);
wm.setDefaultConnect(wm.getRestful());
wm.openWalletFile("RecordTxDemo.json");
```

Note: codeAddress is the address of the record contract.

#### Create claim

```
Map<String, Object> map = new HashMap<String, Object>();
map.put("Issuer", dids.get(0).ontid);
map.put("Subject", dids.get(1).ontid);

Map clmRevMap = new HashMap();
clmRevMap.put("typ","AttestContract");
clmRevMap.put("addr",dids.get(1).ontid.replace(Common.didont,""));

String claim = ontSdk.nativevm().ontId().createOntIdClaim(dids.get(0).ontid,password,dids.get(0).controls.get(0).getSalt(), "claim:context", map, map,
clmRevMap,System.currentTimeMillis()/1000 +100000);
```

Note: For createOntIdClaim interface details please see the digital identity ontid document https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/identity_claim.md


The specification of the following interface document is: https://github.com/kunxian-xia/ontology-DID/blob/master/docs/en/claim_spec.md.

<p><br>

#### Storage Claim

**sendCommit**
```
String sendCommit (String issuerOntid, String password,byte[] salt, String subjectOntid, String claimId, Account payerAcct, long gaslimit, long gasprice)
```
	Function description: Save data to the chain

	Parameters:
			issuerOntid:  Issuer ONT ID
			subjectOntid:  Subject ONT ID
			password: Identity password
			claimId: Trusted claims claim uniqueness mark, i.e. Jti field in Claim
			payerAcct: Payment transaction account
			gaslimit: Gas limit
			gasprice: Gas price
	return value: Transaction hash


##### Example

```
String[] claims = claim.split("\\.");
JSONObject payload = JSONObject.parseObject(new String(Base64.getDecoder().decode(claims[1].getBytes())));
ontSdk.neovm().claimRecord().sendCommit(ontid,password,payload.getString("jti"),0)
```


### Get Status

**sendGetStatus**
```
 String sendGetStatus(String claimId)
```
	Function description: Query status of trusted claim

	Parameters:
			claimId: Trusted claims claim uniqueness mark, i.e. Jti field in Claim
	
	return value： 
			Part 1: Status of the claim: "Not attested", "Attested", "Attest has been revoked"
			Part 2: The certificate's ONT ID.

##### Example
```
String getstatusRes2 = ontSdk.neovm().claimRecord().sendGetStatus(payload.getString("jti"));
```


### Revoke

**sendRevoke**
```
String sendRevoke(String issuerOntid,String password,byte[] salt,String claimId,Account payerAcct,long gaslimit,long gas)
```
	Function description:Repeal of a trust claim

	Parameters:
			issuerOntid: Issuer ONT ID
			password: Attester's ONT ID password
			claimId: Trusted claims claim uniqueness mark, i.e. Jti field in Claim
			payerAcct: Payment transaction account
			gaslimit: Gas limit
			gasprice: Gas price
	
	return value： This function will return true if and only if the claim is attested, and the revokerOntId is equal to the attester's ONT identity; Otherwise, it will return false.
