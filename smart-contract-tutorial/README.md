<h1 align="center">Ontology Smart Contract</h1>
<h4 align="center">Version V0.6.0 </h4>

## What is a smart contract?

A smart contract is a set of commitments that are defined in digital form, including the agreement on how contract participants shall fulfill these commitments. Blockchain technology gives us a decentralized, non-tampering, highly reliable system in which smart contracts are extremely useful. Smart contracts is one of the most important characteristics of blockchain technologies and the reason why blockchains can be called disruptive technology. It is increasing the efficiency of our social structure by each passing day.

## Characteristics of Ontology smart contracts

Ontology smart contract have certainty, high performance and expansibility features, it includes two modules: Interactive Service and Virtual Machine. Interactive Service provides interaction between virtual machine and blockchain ledger. Virtual Machine provides smart contract execution environment.

Interactive Service includes native service, neovm service and wasmvm service. native service provides special smart contract implementation in blockchain of the underlying, they can be quick and convenient used. neovm service provides api of neovm communicates with the outside, it can enhance the invoke function of smart contract. wasmvm service provides api of wasmvm communicates with the outside virtual machine.

Virtual Machine includes neovm and wasmvm, neovm is a lightweight virtual machine，the characteristics of it have been some public blockchain proved very well. wasmvm is high performance and universal virtual machine.

Ontology smart contract also support invoke in different contracts and virtual machine, developers can easily use Ontology smart contract to build the project.
## Write smart contracts in any language

The languages that are currently supported are:

C#, VB.Net, F#

Java, Kotlin

Python

C, C++

The languages that we plan to support include:

Rust

Golang

JavaScript

## How to make a effective smart contract?

![Workflow of smart contract](https://s1.ax1x.com/2018/03/24/9q9vx1.png)

There are few things as below.

First, you should choose a language to write your smart contract, lets's suppose it's C#. Then you need to compile your code. At last, you can deploy your smart contract to the blockchain and invoke it. 

Don't worry, we have built a simple tool to help you with all these things. It's a [online IDE]() for Ontology smart contract. You can write smart contract with popular languages on it, and deploy ,invoke contracts easily. 

For more information, please check the [Smart Contract IDE user guide]().

### Step1 - Write & Compile 

We now support smart contracts that run in **NEOVM** and **WASMVM**.


* **For NeoVM**, We supply you Smart Contract IDE to help your write, compile,deploy and invoke smart contracts. 
* **For WASMVM**, Please enter  [>> Wasm Smart Contract](README_wasm.md).

Firstly , you should create a project, and you can choose the language to write smart contract as you want.

![Select language](https://s1.ax1x.com/2018/03/24/9bxJYR.png)

Then you can see the main editor page. 

The left side is the file structure of your smart contract.

The right side is the operation panel.

The middle area is the editor and the logs output box.

![](https://s1.ax1x.com/2018/03/24/9bzj2t.md.png)

#### Write smart contract

You can enjoy coding your smart contracts now. We also provide some userful contract templates for you to  start writing easily.

You can check more specific examples here:

[ C# Smart Contract](docs/en/csharp.md)

[Python Smart Contract](docs/en/python.md)

#### Compile smart contract

After you have written your smart contract, you can click the **Compile** button on the right side to compile your code. 

If your code is correct, your smart contract will be compiled to the ABI and AVM file , and display on the right side.



### Step2 -  Deploy smart contract

Next, you can deploy the smart contract to the blockchain. This step costs some fee so you have to select one of your local wallet with enough balance. Then click the **Deploy** button to deploy the contract.

Besides IDE, you can use ONT SDK to deploy smart contract. Please check the sdks to see more detailed information.

[>> Java SDK](https://opendoc.ont.io/javasdk/en/chapter5/smartcontract.html)


![](https://s1.ax1x.com/2018/03/24/9qp10S.png)


### Step3 - Invoke smart contract

Last, you can run the method of your contract. The step costs some fee, too. You can select the method and  input the params to invoke. The result will display on the right side.

![Invoke smart contract](https://s1.ax1x.com/2018/03/24/9qpLct.png)

Besides IDE, you can use [>> Java SDK](https://opendoc.ont.io/javasdk/en/chapter5/smartcontract.html) to invoke smart contract. Please check the sdks to see more detailed information. 









