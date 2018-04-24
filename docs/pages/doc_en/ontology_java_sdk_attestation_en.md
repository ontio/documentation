---
title: 
keywords: sample homepage
sidebar: ont_doc_en
permalink: ontology_java_sdk_attestation_en.html
folder: doc_en
---

English / [中文](./ontology_java_sdk_attestation_zh.html)

<h1 align="center"> Ontology Java SDK User Guide </h1>
<p align="center" class="version">Version 0.7.0 </p>

# Attest Attestation

## Step


* 1. SDK init


```
String ip = "http://127.0.0.1";
String restUrl = ip + ":" + "20384";
String rpcUrl = ip + ":" + "20386";
String wsUrl = ip + ":" + "20385";
OntSdk wm = OntSdk.getInstance();
wm.setRpc(rpcUrl);
wm.setRestful(restUrl);
wm.setDefaultConnect(wm.getRestful());
wm.openWalletFile("RecordTxDemo.json");
wm.setCodeAddress("803ca638069742da4b6871fe3d7f78718eeee78a");
```

> Note: codeAddress is the address of the record contract。


* 2. attest data onto the blockchain


```
String res = ontSdk.getRecordTx().sendPut("TA9WXpq7GNAc2D6gX9NZtCdybRq8ehGUxw","passwordtest","key","value");
```

> Note: The key represents the key of the data value stored in the chain, which can later be stored according to the key.


* 3. Get data from the chain by the key


```
String res = ontSdk.getRecordTx().sendGet("TA9WXpq7GNAc2D6gX9NZtCdybRq8ehGUxw","passwordtest","key");
```


* 4. description of response


```
{"Data":{"Algrithem":"SM2","Hash":"","Text":"value","Signature":""},"CAkey":"","SeqNo":"","Timestamp":0}
```
> Note: Algrithem:encryption algorithm name，Hash:record hash，Text:stored value，Signature:signing the record hash，CAkey:initiator identity flag，SeqNo:transaction serial number，Timestamp:external time stamp