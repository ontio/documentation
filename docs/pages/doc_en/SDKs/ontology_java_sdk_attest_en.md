---
title:
keywords: sample homepage
sidebar: SDKs_en
permalink: ontology_java_sdk_attest_en.html
folder: doc_en/SDKs
giturl: https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/attest.md
---

<h1 align="center"> Attest Attestation </h1>

<p align="center" class="version">Version 1.0.0 </p>

English / [中文](./ontology_java_sdk_attest_zh.html)


The attest contract of verifiable claim provides the attest service and the records availability information, that is, whether it has been revoked.

## Step


* 1. SDK init


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

* 2. Create claim

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

> Note: createOntIdClaim interface details please see the digital identity ontid document https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/identity_claim.md


The specification of the following interface document is: https://github.com/kunxian-xia/ontology-DID/blob/master/docs/en/claim_spec.md.


* 3. String sendCommit (String issuerOntid, String password,byte[] salt, String subjectOntid, String claimId, Account payerAcct, long gaslimit, long gasprice)

        Function description: Save data to the chain

        Parameter description：

        issuerOntid：Issuer ONT ID

        subjectOntid: Subject ONT ID

        password: Identity password

        claimId: Trusted claims claim uniqueness mark, i.e. Jti field in Claim

        payerAcct: Payment transaction account

        gaslimit: Gas limit

        gasprice: Gas price

        return value: Transaction hash


Example

```
String[] claims = claim.split("\\.");
JSONObject payload = JSONObject.parseObject(new String(Base64.getDecoder().decode(claims[1].getBytes())));
ontSdk.neovm().claimRecord().sendCommit(ontid,password,payload.getString("jti"),0)
```


* 4. String sendGetStatus(String claimId)

        Function description: Query status of trusted claim

        Parameter description:

        claimId: Trusted claims claim uniqueness mark, i.e. Jti field in Claim

        return value：There are two parts: In the first part, the status of the claim: "Not attested", "Attested", "Attest has been revoked"; the second part is the certificate's ONT ID.

Example
```
String getstatusRes2 = ontSdk.neovm().claimRecord().sendGetStatus(payload.getString("jti"));
```


* 5. String sendRevoke(String issuerOntid,String password,byte[] salt,String claimId,Account payerAcct,long gaslimit,long gas)

        Function description:Repeal of a trust claim

        Parameter description:

        issuerOntid: Issuer ONT ID

        password: Attester's ONT ID password

        claimId: Trusted claims claim uniqueness mark, i.e. Jti field in Claim

        payerAcct: Payment transaction account

        gaslimit: Gas limit

        gasprice: Gas price

        return value：This function will return true if and only if the claim is attested, and the revokerOntId is equal to the attester's ONT identity; Otherwise, it will return false.
