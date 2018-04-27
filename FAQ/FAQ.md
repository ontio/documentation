

<h1 align="center">FAQ</h1>
<p align="center" class="version">Version 0.7.0 </p>



### Which programming language/s do you use?
We use Golang to develop the Ontology blockchain. Besides Golang we use Python, Java, C++, and other languages to implement SDKs and applications. 


### Is signature verification really the bottleneck? I thought that the processing the smart contract bytecode through the VM engine and LevelDB storage IO would be where nodes spent most of their time.
Those all matter. Signature verification is an important part and can be parallelized. Hardware acceleration is another method.

### Is there/will there be a RPC API in typescript SDK for communicating with the node (like in neon-js)?
Yes. We support RESTful, WebSocket, and RPC API.



### How do you generate ONG?
Now, on TestNet, ONG is not automatically assigned. If you transfer your ONT, you can receive approve ONG. You should invoke the transferFrom function to get your ONG.

### When I connect to TestNet, how do I apply for ONT to test the transfer function? 
Developers can visit the Ontology official website to apply for TestNet ONT. If developers use Smart Contract IDE (http://smartx.ont.io) to deploy smart contracts, IDE will support enough ONT for deployment or invocation.


### Is a C# SDK being developed?
Currently the core team support Java SDK and Typescript SDK. We encourage the community to develop SDKs for C#, Python, and so on.

### Is there a 1:1 relationship between privatekey and ontid? And a 1:1 relationship between privatekey and accountAddress?
Yes.

### If I want to create a wallet to import multiple ONT IDs and accounts, do I need to supply multiple private keys?
Yes.

### Is it possible to deploy the Ontology smart contract using C# with NeoVM in VS?
Yes, it is supported.

### Is there a doc list of all claim context templates? E.g. Schema for claimData and metadata.
You can find more specific claim related docs in our GitHub documents (https://github.com/ontio/ontology-DID/blob/master/docs/en/claim_spec.md).

### Am I free to add any attribute to claimData, for example gender, address, and profession?
For claim issues you are free to define a new context template and add/delete any attribute in it. If you are a user, you can't change that but can share it.


### Is metaData fixed for all context template? Are we allowed to create customized claim template scheme and give a unique name other than claim:standard0001?
For claim issues you are free to define a new context template and add/delete any attribute in it. If you are a user, you can't change that but can share it.


### To transfer ONT from one account to another is it necessary to generate OP code with the VM and then use sendrawtransaction or is there a more simplistic approach?
The Ontology transfer action is based on a smart contract, so, it is necessary to generate the OP code with the VM. Now we supply you with SDKs (Java, Golang, TypeScript) to do that. In the future (Q3), the ONTO app will support this. 

### How to start to make a dApp? 
You are welcome to join our community to make dApps. We have established the blockchain infrastructure to support making dApps. We highly recommend you to visit https://github.com/ontio/documentation/blob/master/Ontology_Developer_Guide.md to learn more. 

### ONT supports multiple consensus algorithms but I cannot see PoS, why?
We currently support dBFT and VBFT consensus algorithms. POS will be one of the consensuses supported in the future. Everyone is welcome to participate in the development of the consensus module.

### Trust anchors that provide authentication services will be rewarded with ONG?
We support a variety of ways to reward trust anchors. ONG is one of them. Specific details of incentives will be put forward soon.


### Ontology supports three SC contract types: native, Neo, and Wasm. Do all these three types need ONG  to start development?
Yes.

### Why is the NEP-5 smart contract not open source?
The ONT smart contract is made in C#, one reason is because we will very quickly change over to the ONT public chain, and there are also security considerations.

### How will ONT and ONG tokens be used for private blockchains in the Ontology ecosystem? Or are these tokens only for the public ONT core chain?
They will only be used for public/consortium chains.

### Are there any smart contract examples?
You will find examples here: https://github.com/ontio/documentation/tree/master/smart-contract-tutorial.

### What is the difference between ONTID and a public key of our wallets? If an entity has a public key then why do we need ONTID? Why we cannot use our public keys as an our IDs?
ONTID is more than a key. It needs to support many complicated scenarios, such as multiple controllers, recovery of identity loss, (m,n)-threshold control, and so on. It is also needed to comply with W3C DID specifications. You can read more details at: https://github.com/ontio/ontology-DID/blob/master/docs/en/ONTID_protocol_spec.md.

### Is it possible to deploy the Ontology smart contract using C# with NeoVM in VS?
Yes, it is supported. Now you have the Ontology Java SDK or JS SDK to deploy it. The community development group are working on a C# SDK, you can find it here: https://github.com/OntologyCommunityDevelopers/ontology-csharp-sdk.

### Are there any docker images available for Ontology development?
Docker images are currently in the process.

### Is there any plan of incentives/benefits for Ontology developers?
Yes, you can read about it here: https://github.com/ontio/documentation/blob/master/EN/the-first-open-letter-to-the-ontology-technology-community.md.


### As I see on https://explorer.ont.io/transaction/ the failed transactions are also recorded on blockchain. How can we know if the transaction is failed or not from the transaction data?
Success or failure  of the transaction is decided by consensus, success or failure of smart contracts is determined by the execution, they are not both directly related.

### According to the code of OntInit method at https://github.com/ontio/ontology/blob/master/smartcontract/service/native/ont.go the distribution of total supply of 1,000,000,000 ONT was evenly distributed among the bookkeepers at the time of OntInit. However, in the first block the BookKeepers field is empty array. How would I know after ingesting this first block which addresses have the distributed ONT?
The current ONT distribution in the first block is just for test purposes. In MainNet a specific address will be used.
If smart contract execute successfully, like with transfer, you can receive a notification.
If you want to know the ONT amount of an address, you can through RPC, as it supports a getbalance interface.
