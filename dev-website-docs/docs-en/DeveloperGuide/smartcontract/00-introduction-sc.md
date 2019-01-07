
## What is smart contract

The concept of “smart contract” was first introduced in 1994 by Nick Szabo, which is a computer protocol for contract dissemination, authentication and execution. Smart contract allows transactions to proceed between entities excluding third-party middlemen and these transactions are traceable and irreversible.

Blockchain technology gives us a decentralized, non-tamperable, highly reliable system in which smart contracts are extremely useful. Smart contracts are one of the most important features of blockchain technology and the reason why blockchains can be called a “disruptive” technology.

### Features of Ontology smart contract

Ontology Smart Contract possesses dynamic features, including high scalability, high performance, multilingual, cross-contracts, cross-virtual-machines, etc., all integrated into one system. Ontology Smart Contract supports multiple programming languages, which save time of learning a new programming language for developers. Currently, supported programming languages include C# and Python. The programming languages that will be supported in the future are Java, C++, Rust, Go, and JavaScript.

Ontology smart contract have certainty, high-performance, and expandable features. It includes two modules: Interactive Service and Virtual Machine. Interactive Service provides interaction between virtual machine and blockchain ledger. Virtual Machine provides smart contract execution environment. Interactive Service includes native service and NeoVM service. Native service provides special smart contract implementation in the blockchain, which can be quickly and conveniently used. NeoVM service provides the API of NeoVM to communicate externally, which can enhance the invoke function of the smart contract. 


![ontology smart contract architecture.png](https://raw.githubusercontent.com/ontio/ontology-smartcontract/master/smart-contract-tutorial/images/smartcontract_architecture.png)



### Contract Type

Ontology Smart Contract currently supports two types of contract: Native Contract and NeoVM Contract. The Native contract is a contract written directly on the underlying level of Ontology. It has high execution efficiency and is greatly optimized for common contracts. Its services include Oracle, DID, and rights management, and data exchanges will be implemented by Native contracts. The NeoVm contract is a contract that runs on the NeoVm virtual machine and you can write the corresponding contract code to implement it. The supported languages are: Java, C#, and Python. NeoVm has the features of lightweight, scalability, and high-performance. By combining the Interop Service layer, the interaction between the virtual machine and the ledger layer can be well established.


![ontology smart contract type.png](https://raw.githubusercontent.com/ontio/ontology-smartcontract/master/smart-contract-tutorial/images/smartcontract_type.png)


### Smart Contract Scheduling

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




## Ontology Smart Contract Fee Model

### 1. GAS Limit
The gas limit is used to perform step counting in the opcode process when executing a smart contract. In theory, the more complex the smart contract, the higher the amount of gas limit required, and the lowest number of Gas limit on the Ontology transaction is 30000.


### 2. GAS Price

The gas price is to price the opcode. The higher the gas price, the more priority the consensus node will package the transaction.

### 3. Transaction Fee

The transaction fee is the product of gas limit and gas price. The actual transaction fee is divided into the following three situations:

#### 3.1. The number of steps executing opcode equals to gas limit


**. transaction fee =  gas price * gas limit**

#### 3.2. The number of steps executing opcode greater than gas limit

**transaction fee =  gas price * gas limit**

The transaction failed but gas will not be refunded

#### 3.3. The number of steps executing opcode less than gas limit
**transaction fee =  gas price * (opcode实际消耗)**

Excess gas will be refunded

**GAS LIMIT fixed consumption is 20000 for all ONT, ONG transfer.**

### 4. How to set up Gas Fee

use Ontology CLI or SDK to manually set the gas price and gas limit parameters.

#### 4.1 CLI

Take ONT transfer as an example, use Ontology CLI to manually set the gas price and gas limit parameters.

\--gasprice


\--gaslimit

- Check balance：

```
./ontology asset balance TA7FwLmuX6qMcWTgZtUxt6tjzFgfaBM5sz
```

![image](https://ws4.sinaimg.cn/large/006tKfTcgy1fs3ot3e084j30tc03q0tn.jpg)

- Transfer：
```
./ontology asset transfer --from TA7FwLmuX6qMcWTgZtUxt6tjzFgfaBM5sz  --to TA7FwLmuX6qMcWTgZtUxt6tjzFgfaBM5sz  --amount 1000 --gasprice 5 --gaslimit 40000
```

![image](https://ws4.sinaimg.cn/large/006tKfTcgy1fs3ot31uq6j30sc03qaav.jpg)

You can see that the transfer amount = 1000 ONT, gas price = 5, gas limit = 40000

The final consumption of gas = 1787019.99985 - 1787019.9997 = 0.00015.


#### 4.2 SDK

GAS LIMIT and GAS PRICE can be set using the Java SDK and Golang SDK


Take a transfer process as an example (JAVA SDK):

```
String sendTransfer(Account sendAcct, String recvAddr, long amount, Account payerAcct, long gaslimit, long gasprice)(Account sendAcct, String recvAddr, long amount, Account payerAcct, long gaslimit, long gasprice)
```

You can set gas price when calling **sendTransfer**.

[JAVA SDK](https://github.com/ontio/ontology-java-sdk/tree/master/docs/cn)

[Golang SDK](https://github.com/ontio/ontology-go-sdk)


## DApp with smart contract

DApp is an abbreviated form for decentralized application. A DApp consists of back-end code that runs on a decentralized peer-to-peer network. A DApp can also have a user interface, created by front-end code that makes calls to the back-end. DApp do not require a central authority to function: they allow for direct interaction between users and providers.

![dapp](https://upload-images.jianshu.io/upload_images/150344-450fe6ab35cca843.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![app vs dapp.png](https://upload-images.jianshu.io/upload_images/150344-db176bdda1168c42.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

There are common features of Dapps:

*   **Open Source**. Ideally, it should be governed by autonomy and all changes must be decided by the consensus, or a majority, of its users. Its code base should be available for scrutiny.

*   **Decentralized**. All records of the application’s operation must be stored on a public and decentralized blockchain to avoid pitfalls of centralization.

*   **Incentivized**. Validators of the blockchain should be incentivized by rewarding them accordingly with cryptographic tokens.

*   **Protocol.** The application community must agree on a cryptographic algorithm to show proof of value. For example, Bitcoin uses [Proof of Work (PoW)](https://en.bitcoin.it/wiki/Proof_of_work) and Ethereum is currently using PoW with plans for a [hybrid PoW/Proof of Stake (PoS)](https://github.com/ethereum/wiki/wiki/Proof-of-Stake-FAQ)[5](https://blockgeeks.com/guides/dapps/#sdfootnote5sym) in the future.

