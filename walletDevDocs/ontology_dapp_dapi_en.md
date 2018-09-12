English / [中文](./ontology_dapp_dapi_zh.html)

<h1 align="center">Ontology dAPI</h1>
<p align="center" class="version">Version 1.0.0 </p>

# Abstract

This proposal has two major parts:

* A Javascript API is proposed for dApps development. This dAPI allows dApps to communicate with Ontology blockchain and make requests for transfers, ONT ID registration and others, without requiring users to trust the dApp itself. The issue of trust is shifted to the dAPI provider.

* A Communication protocol is proposed for dAPI provider development. This allows multiple Wallet implementators to offer the same unified service to users of dApps and prevent fragmentation of dApp development.

# Motivation

Currently a dApp will use one of the SDKs (Typescript, Java, Python, ...) to communicate with Ontology network. This setup has three main disadvantages:

1. User of the dApp will have to trust the dApp developer with his private keys and that information about transfers mediated through the dApp are legitimate.

2. Although the SDKs are very powerful, they are hard to use. A more streamlined API will allow developers to focus on the application itself.

3. Hard to implement integration to external signing mechanism (e.g.: Ledger, Trezor)

# Specification

This proposal makes use of the following functions and definitions:

* **SDK**, a software development kit implementing low level communication with the network and providing high level interface for dApps.

* **dApp**, an application with decentralised characteristics running in web environment. The application uses Ontology network for value transfers, contracts enforcing and identification between participants.

* **dAPI**, the API for dApps this OEP is proposing.

* **dAPI provider**, an implementation of the dAPI in the form of web browser plugin or other means, where a user interaction with the provider can be injected into api call workflow (e.g.: confirming transfer).

* **Notify event**, an event broadcasted from smart contract execution.

* **NEOVM**, a lightweight virtual machine for execution of Neo/Ontology smart contracts.

# Implementation

https://apidoc.ont.io/dapi/