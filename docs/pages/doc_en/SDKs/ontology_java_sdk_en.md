---
title:
keywords: sample homepage
sidebar: SDKs_en
permalink: ontology_java_sdk_en.html
folder: doc_en/SDKs
giturl: https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/README.md
---

<h1 align="center"> Ontology Java SDK User Guide </h1>

<p align="center" class="version">Version 1.0.0 </p>

English / [中文](./ontology_java_sdk_zh.html)

## Overview

This official Ontology Java SDK is a comprehensive Java library for the Ontology blockchain. This SDK supports multiple functions including native wallet management, digital identity management, digital asset management, smart contract deployment and invocation and node communication. This SDK will continue to be updated with new features.

## Main functions

- [Getting Started](./ontology_java_sdk_get_start_en.html)
- [Interface](./ontology_java_sdk_interface_en.html)
- [Basic operation of blockchain nodes](./ontology_java_sdk_basic_en.html)
- [Wallet file specification](https://github.com/ontio/documentation/blob/master/docs/pages/doc_en/SDKs/Wallet_File_Specification_en.md)
- [Digital identity and verifable claim management](./ontology_java_sdk_identity_claim_en.html)
- [Digital assets](./ontology_java_sdk_asset_en.html)
- [Digital Attestment](./ontology_java_sdk_attest_en.html)
- [Authorization management](./ontology_java_sdk_auth_en.html)
- [Smart contract deployment and invocation](./ontology_java_sdk_smartcontract_en.html)
- [Error codes](errorcode.md)
- [API reference](https://apidoc.ont.io/javasdk/)


## Code structure:

The SDK is broken down into the following key areas:

* account: Account operations, e.g. public/private key generation
* common: Common interface
* core: Core layer, including smart contract, transaction and signature
* crypto: Relevant to crytography, e.g. ECC/SM
* io: IO operations
* network: Interfacing with the restful, RPC or websocket interfaces of the chain.
* sdk: Underlying encapsulation, info management, communications management, UTXO management, wallet file management, exception class.
* ontsdk class: Provide manager and transaction use cases and there are two types of managers: 
	* walletMgr: Manages digital identities and digital asset accounts. Transactions sent to the blockchain need to be digitally signed with the user's private key. 
	* connManager: Manages blockchain communications system. Any transactions and query needs to be processed by connManager.

## Installation Environment

Please configure JDK 8 and above.

> **Note:** As the length of the key used in the Java SDK is greater than 128 and due to the restrictions of JAVA security policy files, it is necessary to download local_policy.jar and US_export_policy.jar from the official website to replace the two jar files in ${java_home}/jre/lib/security in JRE directory.

Download URL：

>http://www.oracle.com/technetwork/java/javase/downloads/jce8-download-2133166.html


### Build

```
$ mvn clean install
```

### Preparations

Ensure you have access to an Ontology Blockchain (mainnet, testnet or privaenet) and access via RPC ports is available. 


