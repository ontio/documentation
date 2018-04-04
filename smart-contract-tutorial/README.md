<h1 align="center">Ontology Smart Contract</h1>
<h4 align="center">Version V0.6.0 </h4>

## What is a smart contract?

A smart contract is a set of commitments that are defined in digital form, including the agreement on how contract participants shall fulfill these commitments. Blockchain technology gives us a decentralized, non-tamperable, highly reliable system in which smart contracts are extremely useful. Smart contracts are one of the most important characteristics of blockchain technology and the reason why blockchains can be called a “disruptive” technology. It is increasing the efficiency of our social structure day by day.

## Characteristics of Ontology smart contracts

Ontology smart contract have certainty, high-performance, and expandable features, it includes two modules: Interactive Service and Virtual Machine. Interactive Service provides interaction between virtual machine and blockchain ledger. Virtual Machine provides smart contract execution environment.

Interactive Service includes native service, NeoVM service, and WasmVM service. Native service provides special smart contract implementation in the underlying blockchain, which can be quickly and conveniently used. NeoVM service provides the API of NeoVM to communicate externally, it can enhance the invoke function of the smart contract. WasmVM service provides the API of WasmVM to communicate with the external virtual machine.

Virtual Machine includes NeoVM and WasmVM. NeoVM is a lightweight virtual machine，which has proven to perform well on public chains. WasmVM is a high-performance and universal virtual machine.

Ontology smart contract also support invoke in different contracts and virtual machines. Developers can easily use Ontology smart contracts to build projects.
## Write smart contracts in any language

The languages currently supported are:

C#, VB.Net, F#

Java, Kotlin

Python

C, C++

The languages that we plan to support include:

Rust

Golang

JavaScript

## How to make an effective smart contract?

![Workflow of smart contract](https://s1.ax1x.com/2018/03/24/9q9vx1.png)

First, you should choose a language to write your smart contract, let's suppose it's C#. Then you need to compile your code. Last, you can deploy your smart contract to the blockchain and invoke it. 

Do not worry, we have built a simple tool to help you with all these things. It's an [online IDE](http://dev.ont.io/#/) for Ontology smart contracts. You can write smart contract with popular languages, deploy, and invoke contracts easily. 

For more information, please check the [Smart Contract IDE user guide](/docs/en/ont sc ide user guide.md).

### Step 1 - Write & Compile  

We now support smart contracts that run in **NeoVM** and **WasmVM**.


* **For NeoVM**, we supply your Smart Contract IDE to help you write, compile, deploy, and invoke smart contracts. 
* **For WASMVM**, Please go to [>> Wasm Smart Contract](README_wasm.md).

First you should create a project and choose the language to write your smart contract.

![Select language](https://s1.ax1x.com/2018/03/24/9bxJYR.png)

Then you can see the main editor page. 

The left side is the file structure of your smart contract.

The right side is the operation panel.

The middle area is the editor and the logs output box.

![Compile contract](https://s1.ax1x.com/2018/04/04/CpIdpR.png)

#### Write smart contract

You can enjoy coding your smart contracts now. We also provide some useful contract templates for you to start writing easily.

You can check more specific examples here:

[ C# Smart Contract](docs/en/csharp.md)

[Python Smart Contract](docs/en/python.md)

#### Compile smart contract

After you have written your smart contract, you can click the **Compile** button on the right side to compile your code. 

If your code is correct, your smart contract will be compiled to the ABI and AVM file , and display on the right side.



### Step 2 - Deploy smart contract

Next, you can deploy the smart contract to the blockchain. This step costs a fee, so you have to select one of your local wallets with enough balance. Then click the **Deploy** button to deploy the contract.

Besides IDE, you can use ONT SDK to deploy the smart contract. Please check the SDKs for more detailed information.

[>> Java SDK](https://opendoc.ont.io/javasdk/en/chapter5/smartcontract.html)


![Deploy contract](https://s1.ax1x.com/2018/04/04/CpIcAe.png)


### Step 3 - Invoke smart contract

Last, you can run the method of your contract. This step costs a fee too. You can select the method and  input the params to invoke. The result will display on the right side.

![Invoke smart contract](https://s1.ax1x.com/2018/04/04/CpoCEF.png)

Besides IDE, you can use [>> Java SDK](https://opendoc.ont.io/javasdk/en/chapter5/smartcontract.html) to invoke a smart contract. Please check the SDKs for more detailed information. 









