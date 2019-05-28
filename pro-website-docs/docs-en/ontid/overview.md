
## What is ONT ID?

ONT ID is a decentralized identity protocol, which establishes a cryptographic identity for each user, company, item and any other entity. ONT ID is based on W3c DID protocol specification and ontology blockchain technology. It is not restricted by any centralized organization and is completely controlled by users themselves. For users ONT ID has the following usages:

* Single Sign On

Use ONT ID as your sole access point to the blockchain world.

* Multi-source authentication

Using Ontology’s trust partners you can access identity verification services that cover nearly 200 countries and regions, as well as use your qualifications, reputation, and credit to manage your own personal profile.These data are encrypted and hosted in ONT ID accounts. Authentication and authorization are completely controlled by users themselves.

* Self-controll your data

Privacy protection is ensured by cryptographic algorithms and your key for encryption can be self-managed or entrusted with a third party. All data access must obtain your authorization.

* More blockchain functions

You can also use ONT ID for more blockchain transactions, such as attestation, payment and smart contract transactions.


## Get started

ONT ID Open Platform provides a variety of application APIs that help third-party applications quickly integrate. At present, the open platform provides login, KYC, identity authentication, data storage and so on, and will continue to come up with more functions.

For third-party applications, please follow the following steps to start the services you need:

* 1. Download ONTO APP[https://onto.app](https://onto.app).

* 2. Use ONTO to create an ONT ID, and need to verify your email address.

* 3. Visit [https://developer.ontid.pro](https://developer.ontid.pro) to apply for application integration.

> **Please Note：** At present, the open platform is still under test, you can apply for opening by openplatform@ont.io .

After the approval, the access process can be started. Optional application services:

* If you are a dAPP，want to integrate third-party Login，[Here](https://pro-docs.ont.io/#/docs-cn/ontid/thirdparty_login)；

* If you are a financial applition，need to KYC your customers，[Here](https://pro-docs.ont.io/#/docs-cn/onto/ONTO_login)；

* If you want to use blockchain attestation，[Here]()；

* If you are a verification service provider，join Ontology trust ecosystem and supply ONT ID users with verification service,[Here](https://pro-docs.ont.io/#/docs-cn/taconnector/01-overview)；


## Work principles

Before using ONT ID, you can first get an idea of how ONT ID works.

The following roles will be present throughout the use of ONT ID:

* **Recipient** The owner of the ONT ID, they can accept verifiable claims issued by verifiers, or issue verifiable claims to others.

* **Claim issuer** This can be any ONT ID holder in the Ontology ecosystem, including Ontology trust anchors (partners providing the certification service), which may be government agencies, universities, banks, or third-party certification services (such as CA), biometric technology companies, and so on. These companies provide multi-dimensional authentication for ONT ID owners and record authentication activity and result hash, thereby reaching service demands of the user while using a standardized, trusted way to authenticate.

* **Claim verifier** Receives the user's verifiable claim and verifies the case, such as with an employer who needs to verify the interviewer's identity information/education/industry skills.

* **Developer** Provide various application development services for different users and scenarios using the ONT ID protocol and interface.

![](https://github.com/ontio/ontology-DID/raw/master/images/claim_workflow.png)



## Understanding the ONT ID protocol

The ONT ID protocol system consists of two parts: the Ontology DID and the verifiable claim protocol.

Ontology DID is a decentralized identity protocol based on [W3C](https://www.w3.org/2017/vc/WG/) [DID](https://w3c-ccg.github.io/did-spec/) specification. Ontology's ONT ID creates and manage on-chain identities using this protocol. [>> Read more about the ONT ID protocol](https://github.com/ontio/ontology-DID/blob/master/docs/cn/ONTID_protocol_spec_cn.md)

A verifiable claim is a statement made by an entity of certain attributes of another entity (including itself). It includes the entity's own digital signature to prove the authenticity of these attributes, which can be used by other entities for verification purposes. The verifiable claim protocol details the procedures and specifications for the issuance, storage, verification, and so on of the statement. The Ontology verifiable claim protocol establishes a decentralized trust model and a distributed trust delivery system, and introduces cryptographic techniques such as the C-L signature algorithm and sigma protocol to assure privacy protection of verifiable claims.
[>> Read more about the verifiable claim protocol](https://github.com/ontio/ontology-DID/blob/master/docs/en/claim_spec.md)



## Why do we need to decentralize your identity?

On March 18th, 2018, US social media giant Facebook revealed that user information data of  more than 50 million users was leaked. On March 27th, Facebook CEO Zuckerberg published an article in a number of newspapers, publicly apologizing, admitting that they had hurt the trust of users. He said Facebook have a responsibility to protect your information, and if they can’t, they don't deserve it. They violated trust and are sorry that they didn't do more at the time. Of course, this scandal was only a concentrated outbreak of the problem. For the general public, Zuckerberg’s apology is merely an emotional expression. What is actually needed is to protect user data privacy through legal and technical methods, and to protect a healthy public domain network environment.

![](https://github.com/ontio/ontology-DID/raw/master/images/ontid.jpg)
<p align="center">
<b>Presentation from Ontology community[1]</b>
</p>

## Citations

- [1] "Ontology Trust Network" by https://twitter.com/musuko_crypto