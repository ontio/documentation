---
title: 
keywords: sample homepage
sidebar: ont_doc_en
permalink: index.html
---


English / [中文](./first_open_letter_zh.html)


<h1 align="center">The First Open Letter to the Ontology Technology Community </h1>
<p align="center" class="version">By Ontology | Updated 2018/03/30</p>

Ontology will open source the first batch of projects this month, and with this the technical community will begin. Here the Ontology team has prepared the first open letter to the technical community, which describes the project structure for the first stage of Ontology, as well as the Ontology team's outlook on public chain design and future strategic direction. At the same time, this letter also invites the technical community to together invest in the development of blockchain.

## Ontology

The Ontology blockchain framework includes a complete distributed ledger system, a P2P network protocol, a modular consensus protocol set, a modular smart contract mechanism, and more.

## Ontology DID (Distributed Identity Framework)

ONT ID is a decentralized identity protocol based on W3C DID specification. The agreement supports collaborative services such as distributed and multi-factor confirmation, identification, and certification for people, organizations, objects, and content. ONT ID establishes a cryptography-based digital identity for each entity, allowing data authorization and authority autonomy. It makes identity and data assets that users can truly control.

## ONTO

ONTO is an Ontology-based integrated client product, blockchain search engine, and blockchain system entry. ONTO will help users realize comprehensive functions including digital identity management, digital asset management, and distributed data exchange. ONTO maps digital identities to real world identities. Users can use this product to build their own digital identities and comprehensive personal profiles, and also ensure privacy protection through cryptographic algorithms. ONTO can manage digital assets securely and reliably, and apply them to various scenarios. At the same time, ONTO establishes a reliable and controllable data transaction system for users through authorization systems and encrypted algorithms. In the future, ONTO-based digital identity and digital assets will further support various social situations and collaboration needs.

## Ontology WASM

A WASM virtual machine written in Go language.

## Ontology Java SDK

Ontology Java SDK is a comprehensive SDK which currently supports: local wallet management, digital identity management, digital asset management, smart contract deployment and invocation, and node communication. In the future it will also support richer features and applications.

## Ontology TS SDK

Ontology TypeScript SDK (supports JavaScript), features are synchronized with the Java SDK.

## Ontology Crypto

Various cryptography basic function modules.

## Ontology EventBus

The Ontology Event Bus module can be used to support the functional service coordination of the underlying blockchain or other basic modules.

## Ontology FPGA

FPGA implementation of computation-intensive logic.

## Ontology DDXF

Decentralized data exchange framework. DDXF supports peer-to-peer trust in a decentralized model with blockchain and smart contract technology. At the same time, DDXF provides a series of cryptographic components. Upper-level applications can easily implement scenarios such as copyright control and contractual data sharing. Ontology application developers can develop applications based on DDXF that meet the needs of various subdivided scenarios and their own decentralization data transaction applications.

## Ontology Oracle

The oracle functionality supports access to third party trusted data for blockchain systems.

## Ontology OEPs

Several types of technological development or improvement proposals.

For the specific content of each project you can refer to related documents on GitHub. In addition to introducing the first batch of open source projects, we also want to communicate with the technical community about our research and reflections on public chain design and technology development, and work with the technical community to promote the development of the public chain infrastructure.

# Reflecting on Public Chain Design

## Account system

Blockchain account systems mainly have two categorical directions: the asset-based account system (such as UTXO) and the user-based account system (such as the account balance type). Each have their advantages of which we will not elaborate on here. In many projects led by our team before the UTXO system has been stable. In the first edition, we have used the account balance type of smart contract assets to implement ONT/ONG-related management. This is because we considered several key points, including that contract assets can better coordinate with other smart contracts. In addition, when combined with the Ontology's DID system, the user account system model is more natural and smooth in integration. Of course, the UTXO module function remains in the Ontology blockchain framework, so that different types of account systems can be freely selected according to specific requirements amongst the different business chains in the Ontology chain network.

## Consensus

Consensus is a core mechanism of blockchain. In the history of blockchain development, consensus algorithms such as PoW/PoS/BFT have played separate roles in their respective application scenarios. In the first stage of Ontology, combining the business features of the stage, Ontology will be based on the BFT consensus model. In the framework of the first phase, a stable version of the dBFT module is included and there is a new consensus algorithm module, VBFT, which is a new consensus algorithm module that combines PoS, VRF (Verifiable Random Function), and BFT. TestNet will be tested primarily with VBFT. VBFT can support the scale expansion of consensus groups and guarantee the randomness and fairness of consensus partitioner selection with VRF, and at the same time BFT can achieve state finality more quickly. Ontology will be the first project to integrate VRF into a public chain.

At the same time, the Ontology blockchain framework will add several types of consensus modules to support the customization requirements of different service chains in the chain network. In addition to the consensus of the BFT series, the team has also implemented PoW-based consensus modules, which will be gradually added to open source libraries. There is also a Solo consensus module that facilitates development testing.

Cross-chain consensus is an important direction in the development of consensus mechanisms. The Ontology team has done a lot of research and thinking on this part, which will be laid out in the subsequent cross-chain section.

## Smart contracts

Smart contracts are an important module at the underlying level of the blockchain. Ontology implements a modular smart contract mechanism that can flexibly support different smart contract components.

## NeoVM in Golang

Ontology implements a version of NeoVM written completely in Go language. Smart contract development can support multiple languages such as C#, Java, Python, and JS, and brings in a new smart contract development IDE. In the future the Ontology team will continue to collaborate with the NEO team to jointly promote the development of NeoVM and the technical ecosystem development.

## Ontology WASM

The Go language version of the WASM virtual machine will fully implement the WASM technical specifications and based on application scenarios will be continuously optimized, and to meet requirements, smart contract migration and implementation based on WASM business logic is used. Supported smart contract programming languages include C/C++, RUST, Go, and so on.

## High-performance

Performance is a problem that blockchain 3.0 is committed to solving. Ontology realizes optimization in all aspects through framework and algorithm design. Overall performance has already been greatly improved and it can provide industry-leading performance indicators. Ontology’s BFT series of consensus algorithms (dBFT, VBFT) have achieved high performance of thousands of TPS without concurrent commission or sharding. However, the pursuit of high-performance is ongoing. Therefore, Ontology will also conduct continuous exploration and performance improvement in several major directions.

## Concurrent commission processing

Concurrent optimization of the blockchain framework can be carried out at multiple levels, such as the business layer, transaction layer, and ledger layer. The difficultly lies in how to better integrate with businesses and make reasonable grouping and concurrent commission processing of transactions. Here, Ontology combines the account system and smart contract dependency analysis, and performs corresponding partitioning and concurrent commission processing on transactions in the chain. In many processing-intensive scenarios, the concurrent commission performs better. In addition, through introducing Event Bus, various modules in the transaction processing flow can carry out microservices, achieve multi-level fine-grained concurrent commission, and flexibly improve performance.

## Scalability
Sharding, sidechains, and state-channels are technologies where a lot of scalability discussion happens in the blockchain field. The Ontology team has also put a lot of research, thought, and design into these areas. Through research and program analysis, despite in-depth discussions from experts, it is still at too much of an exploratory stage to tentatively judge scalability solutions that can support generic services. In some sharding application practices there have been technological breakthroughs in storage and transaction shards, but there are still many challenges in the core areas of state sharding. In addition, if sharding and status-channel schemes are applied to public chains, there will be challenges to the established economic incentive models, which could affect operations.

After in-depth research and discussion amongst the Ontology team about design, we have chosen to give priority to the development of sub-chains, side-chains, and storage sharding. In the future full introduction of state sharding schemes on public chains will require more design attempts and mechanisms for trial operation. Ontology will also adopt a pragmatic attitude in the development of sharding, and gradually test a variety of comparative solutions in TestNet. At the same time, the Ontology team will also actively conduct design and research, followed up with periodical trials.

(PS: The first complete description of the sharding concept was brought about by the Ethereum team. Many different projects are now ahead of Ethereum in advancing sharding. Many people think that Ethereum appears to be falling behind. However, after in-depth research and discussion, we believe that in applying sharding to the study of large-scale public chains, the Ethereum team have taken the most in-depth considerations in all aspects. The Ethereum team also believes that public chain sharding application still needs more in-depth research and experimentation.)

## FPGA

With hardware acceleration, compute-intensive business logic will give a great performance boost. Ontology has researched and contrasted hardware acceleration techniques, and focusing on GPU and FPGA solutions, has finally decided to use FPGA in the first phase. In the first stage of FPGA development, we first support the core signature verification function, including ECC (Elliptic Curve Digital Signature Algorithm) and SM series verification, both of which support China national cryptographic standards. In the medium and long-term there will be further support for generalized, computation-intensive business logic with FPGAs for faster computing performance. FPGA implementation will help some of the high-performance service chains in the Ontology chain network or introduce a super node mechanism to help the main chain.

## Cross-chain

Cross-chain is a hot topic in current technological development, with many people discussing and comparing various cross-chain protocols. Our thinking on cross-chain is that cross-chain is not a general-purpose business supported by only one common protocol, but a protocol group with various levels and scenarios of collaboration. It is also difficult for cross-chain services to solve all application scenarios through a single protocol. Based on this understanding, we have already made several preliminary hierarchical divisions across chains:

* Business-layer cross-chain: Such as mapping the account system between chains, the exchange of data, etc. Cross-chain business collaboration can be loosely coupled at the business later. In this layer of Ontology, the DID protocol and distributed data exchange protocols are used to support cross-chain collaboration, and the business-level collaboration protocol is continuously enhanced according to business requirements.

* Asset/transaction-layer cross-chain: This involves the cross-chain exchange of digital assets or the cooperation of cross-chain transactions. This layer of cross-chain can also be accomplished using many different protocols. This part of Ontology will first implement a cross-chain asset exchange and transaction collaboration protocol that does not depend on third parties. This is also NEOX's core protocol. At the same time Ontology will track and research all types of cross-chain protocols that have been verified in practice, maintain compatibility with other cross-chain protocols, and expand choice to Ontology users.

* Consensus-layer cross-chain: There is a need for cross-chain for consensus mechanisms, for mutual understanding of consensus processes and integration of consensus processes. Only with this can we have a deeper cross-chain mechanism. In the second stage there will be testing and experimentation of consensus-layer cross-chain protocols.

In Ontology's chain network, cross-chain is not completed by a single protocol, but instead performed at different levels, combined with specific business requirements, using different protocol groups.

## Stable Value Measurement System

Blockchain brings value to traditional business systems. To better serve other business systems, we need to define a relatively stable cost measurement system for blockchain services. Due to the uniqueness of blockchain systems, how to achieve a stable cost measurement system is a challenge that all blockchain systems currently face. In this respect, Ontology has already started exploring stable service cost measures based on its own dual token mechanism. At the same time, we are also investigating various existing stable value measurement design mechanisms, because at present, there has not been a stable operation that has been proven successful. Ontology will further track this part of the research and design, and conduct joint research and cooperation with the community and third party cooperation teams, and later conduct experiments on the test network at an appropriate time.

## Platform governance technology solution

As blockchain is a technology product with human management, blockchain platforms are likely to encounter problems beyond straightforward defects and design faults. Blockchain solutions need to acknowledge these problems and join to formulate a framework for finding and addressing problems. This framework includes addressing network abnormalities, suggestions for solutions, escalating issues, quick coordination with stakeholders, and rapid deployment of corrections to the network.

Unexpected events may also cause economic loss. How to further reduce, avoid, and recover losses is something Ontology is continuing to explore and study.

## Trust collaboration platform

When blockchain platforms are used to support physical applications, having support from the technology alone is far from enough. In addition to trust based in technology, it is necessary to further integrate legal systems, communities, etc., from the real world to make a more comprehensive trust so that blockchain can be better integrated into business processes. Ontology refers to this layer of the platform as the "distributed trust collaboration platform".

The distributed trust collaboration platform consists of a series of universal modules that support the integration of the digital world and entity services, such as distributed identity management frameworks, distributed data exchange protocols, distributed community frameworks, and distributed reputation evaluation services. In the first stage, Ontology will first introduce two common modules: the distributed identity management framework (ONT ID) and the Ontology distributed data exchange protocol (ONT DDXF).

## Distributed identity management framework (ONT ID)

ONT ID is a decentralized identity protocol based on the W3C DID specification. The agreement supports collaborative services such as distributed and multi-factor confirmation, identification, and certification for people, organizations, objects, and content. ONT ID establishes a cryptography-based digital identity for each subject, allowing data authorization and authority autonomy, making identity and data truly assets that users can control themselves. ONT ID itself does not collect entity data but is a connector for authentication and data information.

## Distributed data exchange protocol (ONT DDXF)

Considering the pain points brought by centralized data exchange, such as data caching, unauthorized data use, and data copyright protection, Ontology proposes a distributed data management protocol, ONT Data, which is based on the distributed data exchange protocol. DDXF supports peer-to-peer trust in the decentralized model with blockchain and smart contract technology. At the same time, DDXF provides a series of cryptographic components. Upper-level applications can easily implement scenarios such as copyright control and contractual data sharing. Ontology application developers can develop applications based on DDXF that meet the needs of various subdivided scenarios and their own decentralized data transaction applications.

## Application layer products

Ontology focuses on the underlying infrastructure, providing basic services for several types of applications in different industries. Therefore, in the application layer Ontology will focus on partner applications from various industries.

In addition to the underlying blockchain layer and upper distributed trust collaboration platform, Ontology will also provide a series of general-purpose application services at the application layer. The most basic services are a series of APIs that can support different industry use. Ontology-based APIs can quickly integrate Ontology blockchain services and integrate Ontology's group of blockchain services to develop several types of customized business scenarios and business applications. In addition, Ontology will also provide some common application services. In the first stage, an integrated client platform (ONTO) integrates the versatility of asset management, entity identity management, and data collaboration management.

In addition, Ontology TSE will be launched in the next phase. It can quickly retrieve the human, financial, material, business, and numerous services in Ontology in one portal, as well as provide fast and automatic verification of search results and related services.

In the follow-up the Ontology team and partners will continue to launch a variety of service layer applications, and welcome the technical community to together build more distributed applications.

## Technical community construction

The technical community is the core strength of public-chain projects. Ontology has set aside a 10% ONT token allocation as incentive for the technical community. This is the largest proportion reserved for a technical community in any public chain project. With the first Ontology open source projects released on GitHub, the technical community will be officially launched. No matter where you are in the world, you can participate in the technology community in a variety of ways. In the first stage, you can participate in the following ways:

* Individual technical contributions

Individual technology participants can select projects that interest them to participate in, make new enhancement proposals (OEP), implement code, participate in testing, and many other ways. Individuals can also apply for new projects. The Ontology Foundation will give various levels of support according to different levels of contribution.

* Technical community groups

Developers can organize different technical community groups based on their preference in technology direction to carry out larger-scale distributed technical collaborations. They can set a name for their group, develop their own group charter, select executive committees, evaluate and filter projects, set up their own GitHub, and so on. The Ontology Foundation will evaluate and support development plans of different technical community groups. (We have already received some name suggestions for technical community groups, such as "Athens Academy", "Olympia Mountain", etc.)

* Organizational technical contributors

Institutions can cooperate with Ontology to conduct technology research related to their own business, and jointly conduct research on underlying product technologies and common business modules. Both parties can collaborate on technology, funding, resources, and other aspects in a flexible manner.

## Open Blockchain Foundation plans

Ontology has joined the Open Blockchain Foundation fund initiated by NEO. This non-profit technology research fund is focused on the fields of blockchain, security, and cryptography. It will cooperate with universities and research teams around the world to carry out relevant cutting-edge technologies. The research and results will be open to the whole of society. It will also serve as a force for the development of blockchain-related technology.

# Conclusion

Blockchain has had a huge impact in its short history and has already achieved many phases of results. As one of the earliest technical teams to invest in the blockchain field, we must also acknowledge that blockchain is still without perfection, as it faces many problems in technology, ecosystem, and other mechanisms that need to be explored to support mainstream industries. Therefore, at this stage, industry collaboration is far more important than competition. Ontology will continuously cooperate with industry peers and technology communities in the spirit of open source and open cooperation in order to advance the development of blockchain technology and the industry.

Despite the numerous challenges facing blockchain, we have in the past several years explored, practiced, and thought deeply on the fields of technology and applications, and have recognized that blockchain brings about social collaboration in finance, business, organizations, and populations. It reduces costs, increases efficiency, and even changes values of existing models.

The future has come, and it is being distributed for all.

The Ontology Team

Ontology GitHub: https://github.com/ontio/

Ontology Discord: https://discord.gg/4TQujHj/ 