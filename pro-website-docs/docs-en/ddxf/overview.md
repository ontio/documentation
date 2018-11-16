<h1 align="center">Decentralized Data Exchange Application Framework</h1>

## What is DDXF?

In light of the pain points of the current centralized data exchanges, such as data caching, private data use without user authorization, data copyright protection, etc., Ontology launched the decentralized data transaction framework, “DDXF”. Ontology ecosystem application developers can develop decentralized data transaction applications based on DDXF to meet different scenarios and features, and support communication/transactions between data transaction platforms.

Based on the Ontology blockchain and ONT ID protocols, DDXF implements decentralized transactions of digital assets through consistent bookkeeping, smart contracts, and cryptography. DDXF provides a series of smart contract templates, transaction modules, and cryptography modules. Applications can also easily implement the requirements of copyright control, contractual data sharing, etc.

## How to use DDXF

DDXF can help you quickly build a decentralized data exchange system. Simply integrate your system into the data transaction client DataRot and connect to a visual data trading market interface.

Start building your decentralized data trading platform with the [>> data trading client]().

## Understand how DXF works

![](http://on-img.com/chart_image/5b9b529de4b0fe81b63605f9.png)

The main players in the distributed data exchange protocol are:
* Data consumer: Institutions/enterprises/individuals who need to purchase data;

* Data provider: The organization/enterprise/individual providing the data, the data can be source data or processed data, and the data supply needs to fully meet the local government's laws and regulations;

* Data owner: The data subject can be an institution, enterprise, individual, etc.;

* Marketplace: Operates a visual data transaction page or community, develops data transaction and exchange standards in the industry, and facilitates efficient trading between buyers and sellers and trading participants. There will be significant differences in data exchange standards across industries, so there will be different types of decentralized data exchanges.

### Collaboratrion process

![](http://on-img.com/chart_image/5a54d944e4b01acda595f66d.png)

* Preparation

    1. Trading participants opens an ONT ID.
    
    2. Before the transaction request is initiated, the demander first deposits a sum of funds into the data transaction contract address.

* Transaction request, smart contract lock

    The data requester sends a data transaction request to the provider through the blockchain, and the request includes not limited to: transaction information, ONT ID, etc. At the same time, the XSC smart contract fund lock interface is invoked to lock the transaction costs necessary from the demander.

* User authorization

    After receiving the request from the demanding party, the user agent is accessed and authorization request initiated. At this time, the user agent can authenticate the identity of the demander through Ontology, and perform authorization processing according to the access policy provided by the data owner in advance. If the owner does not set an access policy, the user agent notifies them of the authorization. If the authorization is not obtained, the transaction is terminated.

* Upload data

    The data provider generates a one-time session key according to the symmetric-key algorithm supported by the requester, encrypts the data and data feature values of the transaction using the session key, and uploads the ciphertext to the third-party trusted storage (such as decentralized storage IPFS).

* Smart contract unlocking and distribution

    The data provider invokes the XSC smart contract asset unlocking interface, releases the locked funds, delivers the data assets and funds, and performs multi-party distribution according to the smart contract rules. The data asset DToken is pushed to the data receiver through event push.

* Receive data, transaction completed

    After receiving the notification of the smart contract event, the data requester obtains the DToken and obtains the data from the third-party trusted storage through DToken, and the transaction is completed.

## Simultaneous on-chain settlement of goods and funds

In order to ensure the rights and interests of trading participants, an intermediary as a “guarantor” is used in DDXF transaction processes to ensure the settlement process of goods and funds is handled simultaneously. The intermediary is responsible for keeping the buyer's funds and transferring the funds to the seller or returning them to the buyer based on the final transaction result.

DDXF designed a smart contract to implement this mechanism. This contract is used for locking and distributing funds. The contract accepts funds entered by the user account and locks them for a certain period of time. No one can use this money during the lock-in period. After the lock is over, the funds are distributed to other accounts according to the specified allocation rules.

This mechanism can achieve the following results:
* 1. The data demander proves that it has sufficient funds;
* 2. After the transaction is completed, the funds will be transferred to the data provider's account;
* 3. The data requester has the right to request a refund for the failed transaction;
* 4. A third party may be introduced for arbitration in a transaction.

**Process design**:

The entire process is divided into three phases, shown in this example:

* 1. The data demander, as the payer, sets the payee (the data provider) and other parameters, and transfers the funds. If a reviewer is set up, the data provider needs to confirm the reviewer information at this stage. At this stage, the data request can be canceled.
* 2. The data demander invokes the lockout interface, the funds are locked in the contract, and no one can touch the funds.
* 3. After the lockout period is over, the fund allocation phase begins. At this stage, the parties to receive payment are confirmed by either party, and the allocation of funds can be completed.









