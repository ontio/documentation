English / [中文](README_cn.md)


<h1 align="center">Distributed Data eXchange Framework</h1>
<p align="center" class="version">Version 0.7.0 </p>

## Overview

The downsides of centralized data exchange include data caching, use of data without user authorization, and data copyright protection. Ontology proposes a Distributed Data Protocol (ONT Data). Based on the protocol ,we come up with distributed data exchange framework(DDXF) allows to customize data trading marketplaces with ensured data and financial security.With DDXF ,the developer of the ontology ecosystem will easily develop decentralized data application that meets the needs of various scenes and with various features.

DDXF uses blockchain , smart contract and a series of Smart Contracts,transaction SDK and cryptographic components, the application can be very convenient for the implementation of copyright protection, data sharing and other scene requirements.

Main functions of DDXF are as below：

* DataToken
* Data eXchange Smart Contract ,XSC for short
* SDKs for Data eXchange
* a series of cryptographic components ,e.g. digital watermarking technology

## what is DataToken

DToken (short for DataToken),which is the mapping of any asset or data in the reality to the digital assets of Ontology blockchain.For data or offchain assets to be traded, it is necessary to define Data eXchange smart contracts according to ontology contract asset specification, so as to facilitate chain transactions.

The DataToken includes metadata MetaData,  MetaData is a description of the data structure and constraints of the capitalized data. 

In the process of instantiating DToken, it will be used in combination with cryptographic components, such as digital watermarking, etc., for data transaction traceability and copyright tracking.

## Distributed Data management Protocol

Ontology proposes distributed data management protocol (ONT DATA), which defines a set of protocol specifications for data transactions between entities, and supports data collaboration, exchange and more functions among different entities .

To protect the equity of both parties in the transaction, a middleman acting as a “guarantor” is introduced into the transaction process of the agreement to ensure the settlement process is handled securely and smoothly. The intermediary is responsible for keeping the buyer's funds and transferring the funds to the seller or the buyer based on the final trading result. Since the middleman is responsible for the final settlement of the transaction it is fair and secure. It works on a distributed ledger contract with public and decentralized management features to ensure it can suitably play role of intermediary.

### Roles of Participants

* **Data requester**: Data agencies/businesses/individuals who want to buy data.
* **Data provider** Data agencies/business/individuals who want to sell data, both raw and processed. The data needs to meet local government laws and regulations.
* **User Agent**: Responsible for interacting with users to meet user authorization requirements for data transaction. User agents can be diversified (enterprise OA systems, internet platforms, or even simple SMS gateways), but they need to be fully implemented as defined in the application protocol framework's user license protocol.
* **Data owner**: The data subject, which can be institutions/businesses/individuals.
* **Decentralized Marketplace**: Decentralized Marketplace does not involve digital assets handling, only as a service institution, the main work includes: 1 run websites for visual data exchanging 2, the development of data exchange standards, for both parties and the transaction participants. There will be a lot of differences in data exchange standards in different industries, so there will be a variety of different stardards and rules of data exchanges.

> Note: In the point to point work mode(describes as following), the Decentralized Marketplace is not a necessary participant.

### Work mode

According to different scenarios, decentralized data exchanging are divided into two patterns ,point to point model and exchange participation model. DAPP developers can understand the following patterns and choose appropriate pattern for design and development.

> Note: In the process,Data requester, Data provider, and Data owner could be multiple participants.

#### Point to Point Model

In Point to Point Model, Decentralized Marketplace does not need to participate or participate lightly, for example, the exchange of credit reporting between credit reporting enterprises. This mode is more suitable for the scenarios in which the relationship between the buyer and the buyer is clear, exchange procedure is relatively simple, or exchange standard has been established. To use it, the transaction participants need to integrate or use SDK to implement the transaction process.

![](http://on-img.com/chart_image/5a54d944e4b01acda595f66d.png)


* Preparations

    1 All transaction participants register ONT ID.

    2 Before the transaction request is initiated, the requester first deposits funds to the contract address.

* Transaction request & Locking position

    The requester sends a data transaction request to the provider through Ontology blockchain.The request includes but is not limited to transaction information and ONT ID information.At the same time, funds lock interface of XSC is called to lock the required transaction costs.

* User Authorization

    After receiving the request from the requester, the data provider accesses the User Agent and initiates an authorization request. At this point the User Agent can authenticate the identity of the requester on demand via Ontology, and perform authorization according to the access control policies provided in advance by the Owner. If the Owner does not set an access control policy, the User Agent notifies the Owner for authorization. If the authorization request is rejected, the transaction should be terminated.
 
* Uploading data

    The data provider generates a one-time session key according to the symmetric-key algorithm supported by the requester, uses it to encrypt the data and data characteristic values of the transaction, and sends the ciphertext to an intermediate storage system, e.g. IPFS.

* Unlocking position & Profit Distribution

    The data provider called XSC smart contract assets unlock interface, trigger the release of the lock funds for settlement and profit distribution according to the contract rules .DToken is sent to the requester through the event pushing.

* Receiving data 

    After receiving the notification of the smart contract event, The requester then gets the ciphertext from the intermediate storage, decrypts it with the session key, calculates and verifies the characteristics of the plaintext.

Now ,transaction is done!

#### Exchange Participation Model

In many cases, the participation of the marketplace can effectively define the data exchange standard and the interface standard with all the participants, making data transaction participants more convenient and quick. In this mode, the collaboration process is as follows:



![](http://on-img.com/chart_image/5a56fe50e4b05a8ff2f8e716.png)



## Getting Started with DDXF

### 1 Preparations

* Register ONT ID

* Open Digital Asset Account
     
    In most data transactions, entity data or offchain assets will be digitalized into Token, requiring all participants to open digital asset accounts to facilitate transaction and settlement.

We provide a variety of SDK for registration,  here:
    
[>> JAVA SDK](https://github.com/ontio/ontology-java-sdk) 
 
[>> TS SDK](https://github.com/ontio/ontology-ts-sdk)  

### 2 Register DataToken

Ontology official or third party marketplaces will provide standardized intelligent contract template, data requester, data provider or data marketplace itself chooses template to customize.

DataToken deployment, distribution, transfer and other operations, can refer to our smart contract , access to [>> smart contract tutorial](https://github.com/ontio/documentation/tree/master/smart-contract-tutorial), to learn how to use smart contract.
    


### 3 Develop and Deploy XSC
   
The use of smart contracts as a trust intermediary for data transactions has many advantages, such as transparency, undeniability, and untampering. But the writing of smart contracts requires relatively experienced developers, and even the reviewers are required to participate in the review. Fortunately, officials will define some general intelligent contract templates based on some typical data trading scenarios that can be used directly.

XSC contracts need to record user authorization reference, transaction price,distribution rules and so on. This information is generally specified by the marketplace. In a typical data transaction smart contract template, the following parameters and functions need to be explicitly designed and defined.


**Parameters**
```json
    {
        "deposit_address": "aefd726ac55f14cc0a4acdf3b1",
        "price_at_ont": "0.1",
        "price_at_ong": "0.5"
    }
```

**Lock position**

This function is called by the data requester, can also be invoked by an marketplace.
```
bool Lock(byte[] serial_no,  byte[33] user_ontid,  byte[33] buyer_ontid, int amount, byte[] buyer_sig);
```

**Unlocking position & Profit Distribution**

After the function is successful, the asset delivery will be completed. One hand, the locked amount will be settled. On the one hand, the DataToken is also delivered to the requester. This function is usually invoked by the data provider, or by the multiple parties involved in the joint signature determination.

```
bool Confirm(byte[] serial_no, byte[33] buyer, byte[33] user, byte[33] issuer, int seller_bounty, int issuer_bounty, byte[] buyer_sig
```

This is a Smart Contract,access to [>> smart contract tutorial](https://github.com/ontio/documentation/tree/master/smart-contract-tutorial), to learn how to use smart contract.

At the same time, DDXF has prepared the basic smart contract templates for you to use, click the [>> DXC sample template](./demo/dex-sc-csharp/dex.cs) to get it.

### 4 Start Transaction

If the above has been completed, it is now possible to start real data transactions.

Since the main functions are based on smart contract , SDK can be used to operate smart contract transactions as long as the developer has completed the second and third steps.

