
## What is smart contract

The concept of “smart contract” was first introduced in 1994 by Nick Szabo, which is a computer protocol for contract dissemination, authentication and execution. Smart contract allows transactions to proceed between entities excluding third-party middlemen and these transactions are traceable and irreversible.

Blockchain technology gives us a decentralized, non-tamperable, highly reliable system in which smart contracts are extremely useful. Smart contracts are one of the most important features of blockchain technology and the reason why blockchains can be called a “disruptive” technology.

## Features of Ontology smart contract

Ontology Smart Contract possesses dynamic features, including high scalability, high performance, multilingual, cross-contracts, cross-virtual-machines, etc., all integrated into one system. Ontology Smart Contract supports multiple programming languages, which save time of learning a new programming language for developers. Currently, supported programming languages include C# and Python. The programming languages that will be supported in the future are Java, C++, Rust, Go, and JavaScript.

Ontology smart contract have certainty, high-performance, and expandable features. It includes two modules: Interactive Service and Virtual Machine. Interactive Service provides interaction between virtual machine and blockchain ledger. Virtual Machine provides smart contract execution environment. Interactive Service includes native service and NeoVM service. Native service provides special smart contract implementation in the blockchain, which can be quickly and conveniently used. NeoVM service provides the API of NeoVM to communicate externally, which can enhance the invoke function of the smart contract. 


![ontology smart contract architecture.png](https://raw.githubusercontent.com/ontio/ontology-smartcontract/master/smart-contract-tutorial/images/smartcontract_architecture.png)



## Contract Type

Ontology Smart Contract currently supports two types of contract: Native Contract and NeoVM Contract. The Native contract is a contract written directly on the underlying level of Ontology. It has high execution efficiency and is greatly optimized for common contracts. Its services include Oracle, DID, and rights management, and data exchanges will be implemented by Native contracts. The NeoVm contract is a contract that runs on the NeoVm virtual machine and you can write the corresponding contract code to implement it. The supported languages are: Java, C#, and Python. NeoVm has the features of lightweight, scalability, and high-performance. By combining the Interop Service layer, the interaction between the virtual machine and the ledger layer can be well established.


![ontology smart contract type.png](https://raw.githubusercontent.com/ontio/ontology-smartcontract/master/smart-contract-tutorial/images/smartcontract_type.png)


## Smart Contract Scheduling

VM Type

```
// Prefix of address
type VmType byte

const (
Native = VmType(0xFF)
NEOVM  = VmType(0x80)
WASMVM = VmType(0x90)
)

```

VMcode struct


```
type VmCode struct {
VmType VmType
Code   []byte
}

```

Invoke a transaction payload

```
// InvokeCode is an implementation of transaction payload for invoke smartcontract
type InvokeCode struct {
GasLimit common.Fixed64
Code     stypes.VmCode
}

```

The execution of Ontology smart contract requires input parameters and the corresponding virtual machine type. According to the different types of virtual machines, the scheduler will start the corresponding virtual machine for smart contract execution. During the execution, the contract uses AppCall command, including the needed parameters for contract operation, to trigger the smart contract scheduler. The scheduler will run the corresponding script in accordance with the imputed parameters until contract operation has been completed.


![process](http://upload-images.jianshu.io/upload_images/150344-ac402b1c8eb3aa9a.jpeg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

