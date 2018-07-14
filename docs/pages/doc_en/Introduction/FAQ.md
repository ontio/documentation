---
title: 
keywords: sample homepage
sidebar: Introduction_en
permalink: FAQ_en.html
folder: doc_en
---



<h1 align="center">FAQ</h1>
<p align="center" class="version">Version 0.7.0 </p>



### Which programming language are you using?
We use Golang to develop the Ontology blockchain. Besides we use Python, Java, C++, and other languages to implement SDKs and applications. 


### Is signature verification really the bottleneck? I would have thought that the processing the smart contract bytecode through the VM engine and LevelDB storage IO would be where nodes spent most of their time.
Those all matter. Signature verification is an important part, and can be parallelized. Hardware acceleration is another method.

### Is there/will there be RPC API in typescript SDK for communicating with the node (like in neon-js)?
Yes. We support RESTful, WebSocket and RPC API.



### How do you generate ONG?
Now, On TestNet. ONG is not automatically assigned, if you transfer you ONT, you can receive approve ONG. you should invoke transferFrom function, then you can get your ONG.

### When I connect to TestNet, how do I apply for ONT to test transfer function? 
Developers can visit ontology official website to apply ONT for TestNet .  If  Developer use Smart Contract IDE ( smartx.ont.io ) to deploy smart contracts , IDE will  support enough ONT for deployment or invocation .


### Is a C# SDK being developed?
Currently the core team have support Java SDK and Typescript SDK. We encourage the community to develop SDKs for C#, Python, and so on.

### Is it 1:1 relationship between privatekey and ontid?  and 1:1 relationship between privatekey and accountAddress?
Yes.

### If I want to create a wallet to import multiple OntIDs and Accounts, I need to supply multiple private keys?
Yes.

### Is it possible to deploy the Ontology smart contract using C# with NeoVM in VS?
Yes, it is supported.

### Is there a doc list of all claim context templates? E.g. schema for claimData and metadata.
You can find more specific claim related docs in our GitHub documents. (https://github.com/ontio/ontology-DID/blob/master/docs/en/claim_spec.md)

### Am I free to add any attribute to claimData for example gender, address, profession?
As a claim issue , You are fee to define a new context template and add/delete any attribute in it. If you are a user , you can't change that but share it .


### Is metaData fixed for all context template? Are we allowed to create customized claim template scheme and give a unique name other than claim:standard0001? (not answered)
As a claim issue , You are fee to define a new context template and add/delete any attribute in it. If you are a user , you can't change that but share it .


### To transfer ONT from one account to another is it necessary to generate OP code with the VM and then use sendrawtransaction or is there a more simplistic approach?
Ontology transfer action is based on smart contract, so, it is necessary to generate OP code with the VM.Now we supply you SDKs(Java,golang,TypeScript ) to do that .  In the future( Q3 ), APP ONTO will be released to support  . 

### How to start to make a dApp? 
You are welcome to join community to make dApps .  We have established the blockchain infrastructure to support making dApps . We highly recommend you to visit https://github.com/ontio/documentation/blob/master/Ontology_Developer_Guide.md  to know more. 

### ONT supports multiple consensus algorithms. But I cannot see PoS, why?
Now we support dBFT and VBFT consensus algorithms. POS should be one of the consensuses to be supported in the future, and everyone is welcome to participate in the development of the consensus module.

### Trust anchors that provide authentication services will be rewarded with ONG?
We support a variety of ways to reward trust anchors. ONG is one of them. Specific details of incentives will be put forward soon.


### Ontology supports three SC contract types: native, Neo, and Wasm. Do all these three types need ONG  to start development?
Yes.

### Why is the NEP-5 smart contract not open source?
The ONT smart contract is made in C#, one reason is because we will very quickly change over to the ONT public chain, and there are also security considerations.

### How will ONT and ONG tokens be used for private blockchains in the Ontology ecosystem? Or are these tokens only for the public ONT core chain?
They will only be used for public/consortium chains

### Are there any smart contract example ?
You will find more examples here. https://github.com/ontio/documentation/tree/master/smart-contract-tutorial

### What is the difference between ONTID and a public key of our wallets? If an entity has a public key then why do we need ONTID? Why we cannot use our public keys as an our IDs?
ONTID is more than a key. It needs to support many complicated scenarios, such as multiple controllers, recovery of identity loss, (m,n)-threshold control, and so on. It is also needed to comply with W3C DID specifications. You can read more details at: https://github.com/ontio/ontology-DID/blob/master/docs/en/ONTID_protocol_spec.md.

### Is it possible to deploy the Ontology smart contract using C# with NeoVM in VS?
Yes, it is supported. Now you have the Ontology Java SDK or JS SDK to deploy it. The community development group are working on a C# SDK, you can find it here: https://github.com/OntologyCommunityDevelopers/ontology-csharp-sdk.

### Are there any docker images available for Ontology development?
Yes, the community development group have created one and it can be found here: https://github.com/OntologyCommunityDevelopers/ontology-privatenet-docker.

### Is there any plan of incentives/benefits for ONT developers?
Yes, you can read about it here: https://github.com/ontio/documentation/blob/master/EN/the-first-open-letter-to-the-ontology-technology-community.md.


### As I see on https://explorer.ont.io/transaction/ the failed transactions are also recorded on blockchain. How could we know if the transaction is failed or not from the data of the transaction?
Success or failure  of the transaction is decided by consensus, success or failure of smart contracts is determined by the execution, they both did not directly related.

### According to the code of OntInit method at https://github.com/ontio/ontology/blob/master/smartcontract/service/native/ont.go the distribution of total supply of 1,000,000,000 ONT was evenly distributed among the book-keepers at the time of OntInit. But in the first block the BookKeepers field is empty array. How would I know after ingesting this first block which addresses have the distributed ONT?
The current ONT distribution in the first block is just for test purpose. When in MainNet a specific address will be used.
If smart contract execute success, like transfer, you can receive notify.
If you want to know the ONT amount of an address, you can through RPC, it support get balance interface.
