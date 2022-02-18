# Ontology Exchange Docking Document

There are two kinds of assets in ONT: native assets and contract assets. Native assets are ONT and ONG. When docking with the exchange, it mainly processes deposit and withdrawal of these two assets.

The outline of this document is as follows:

* [Ontology Exchange Docking Document](#ontology-exchange-docking-document)
	* [1.Deploy Ontology Synchronization Node](#1deploy-ontology-synchronization-node)
		* [Get from source code](#get-from-source-code)
		* [Get from release](#get-from-release)
		* [Server deployment](#server-deployment)
			* [Create wallet(not mandatory for sync node)](#create-walletnot-mandatory-for-sync-node)
			* [Start up node](#start-up-node)
	* [2. Use CLI Client](#2-use-cli-client)
		* [Security policy](#security-policy)
		* [CLI instruction](#cli-instruction)
			* [Create wallet](#create-wallet)
			* [Generate deposit address](#generate-deposit-address)
	* [3. Process Asset Transactions](#3-process-asset-transactions)
		* [Transaction docking program the exchange needs to develop](#transaction-docking-program-the-exchange-needs-to-develop)
		* [User deposit](#user-deposit)
		* [Deposit record](#deposit-record)
		* [Process user withdrawal request](#process-user-withdrawal-request)
	* [4. Java SDK Tutorials](#4-java-sdk-tutorials)
		* [Account management](#account-management)
			* [Do not use wallet management](#do-not-use-wallet-management)
				* [Create account randomly](#create-account-randomly)
				* [Create account based on private key](#create-account-based-on-private-key)
			* [Use wallet management](#use-wallet-management)
		* [Address generation](#address-generation)
		* [ONT and ONG transfer](#ont-and-ong-transfer)
			* [1. Initialization](#1-initialization)
			* [2. Query](#2-query)
				* [Query ONT, ONG Balance](#query-ont-ong-balance)
				* [Query whether the transaction is in the transaction pool](#query-whether-the-transaction-is-in-the-transaction-pool)
				* [Query whether the transaction is successful](#query-whether-the-transaction-is-successful)
				* [The list of chain interaction interfaces](#the-list-of-chain-interaction-interfaces)
			* [3. ONT transfer](#3-ont-transfer)
				* [Construct transfer transaction and send](#construct-transfer-transaction-and-send)
				* [Multiple signatures](#multiple-signatures)
				* [One to multiple or multiple to multiple](#one-to-multiple-or-multiple-to-multiple)
				* [Use signature server to sign](#use-signature-server-to-sign)
			* [4. ONG transfer](#4-ong-transfer)
				* [ONG transfer](#ong-transfer)
				* [Withdraw ONG](#withdraw-ong)
	* [4. Distribute ONG to Users](#4-distribute-ong-to-users)
		* [What is ONG](#what-is-ong)
		* [Calculate the amount of ONG that can withdraw](#calculate-the-amount-of-ong-that-can-withdraw)
		* [Distribute ONG to users](#distribute-ong-to-users)
		* [Users withdraw ONG](#users-withdraw-ong)
	* [5. Signature service](#5-signature-service)
	* [6. OEP4 Token](#6-oep4-token)
	* [7. PAX token](#7-pax-token)
	* [Native contract address](#native-contract-address)
	* [FAQ](#faq)
	* [Mainnet update note](#mainnet-update-note)

## 1.Deploy Ontology Synchronization Node

There are two ways to deploy Ontology synchronization nodes:

### Get from source code

Clone ontology repository to  **$GOPATH/src/github.com/ontio** directory

```
$ git clone https://github.com/ontio/ontology.git
```

Or

```
$ go get github.com/ontio/ontology
```

Use the third-party package management tool glide to manage the dependent libraries

```
$ cd $GOPATH/src/github.com/ontio/ontology
$ glide install
```

Compile source code with make

```
$ make
```

An executable program will be generated after a successful compilation
(using ```make all``` command will generate sig server under 'tools' directory ）
- `ontology`: Node program/node control program provided by command line

### Get from release

 [release page](https://github.com/ontio/ontology/releases)

### Server deployment

1. #### Create wallet(not mandatory for sync node)

   - Create the wallet file - wallet.dat that is required for nodes running through the CLI

     ```
     $ ./ontology account add -d
     Use default setting '-t ecdsa -b 256 -s SHA256withECDSA' 
     	signature algorithm: ecdsa 
     	curve: P-256 
     	signature scheme: SHA256withECDSA 
     Password:
     Re-enter Password:

     Index: 1
     Label: 
     Address: AWVNFw74G8Sx9vcxGbmh4gT54ayuwb3bcm
     Public key: 02c17cd91acf618d497f65f1fc4f52de7952c8b2337883f898dda887953cd29dd7
     Signature scheme: SHA256withECDSA

     Create account successfully.
     ```

     

   - Directory Structure

     ```
        $ tree
        └── ontology
            ├── ontology
            └── wallet.dat
     ```


2. #### Start up node

   start up command:

   ```./ontology ```

   By default, the node startup will close the websocket and the rest port. If you want to open above-mentioned ports, you can configure the following parameters:

   ```
   RESTFUL OPTIONS:
     --rest            Enable restful api server
     --restport value  Restful server listening port (default: 20334)
     
   WEB SOCKET OPTIONS:
     --ws            Enable websocket server
     --wsport value  Ws server listening port (default: 20335)
   ```

   

## 2. Use CLI Client

### Security policy

Mandatory: The exchange must use a whitelist or firewall to block external server requests, otherwise there will be a serious security risk.

The CLI does not provide remote open/close wallet function and there is no verification process when opening the wallet. Therefore, the security policy needs to be set by the exchange based on its own situation. Since the wallet must remain open in order to process the users' withdrawal, from a security point of view, the wallet must be running on a separate server, and the exchange configures the firewall with reference to the following table.

|               | Mainnet default port |
| ------------- | -------------------- |
| Rest Port     | 20334                |
| Websorcket    | 20335                |
| Json RPC port | 20336                |
| Node port     | 20338                |

### CLI instruction

#### Create wallet

The exchange needs to create an online wallet to manage user deposit address. A wallet is used to store account (including public and private keys), contract address and other information, which is the most important certificate for users to hold assets. It is important to keep wallet files and wallet passwords safe and prevent them from loss or disclosure. The exchange does not need to create a wallet file for each address. Usually a wallet file can store all the user's deposit addresses. You can also use a cold wallet (offline wallet) as a more secure storage.

```
$ ./ontology account add -d
Use default setting '-t ecdsa -b 256 -s SHA256withECDSA' 
	signature algorithm: ecdsa 
	curve: P-256 
	signature scheme: SHA256withECDSA 
Password:
Re-enter Password:

Index: 1
Label: 
Address: AWVNFw74G8Sx9vcxGbmh4gT54ayuwb3bcm
Public key: 02c17cd91acf618d497f65f1fc4f52de7952c8b2337883f898dda887953cd29dd7
Signature scheme: SHA256withECDSA

Create account successfully.
```

**The public and private key generation algorithms of ONT are consistent with NEO. The public key addresses of ONT and NEO corresponding to the same private key are the same.**

####  Generate deposit address

**Note: ONT and ONG address is case-sensitive**

A wallet can store multiple addresses, and the exchange needs to generate a deposit address for each user.

There are two ways to generate deposit addresses:

- When the user first deposits (ONT/ONG), the program dynamically creates the ONT address. Advantages: No manual creation of addresses is required. Disadvantages: It is inconvenient to back up the wallet.

To create an address dynamically, you can use the Java SDK's implementation and the program will return the created address. Please refer to Java SDK [Create account randomly](#create-account-randomly)

- The exchange creates a batch of ONT addresses in advance and assigns the user an ONT address when the user deposits for the first time (ONT/ONG). Advantages: It is easy to back up wallet; disadvantages: Manually create ONT address when the address is insufficient.

  To create a batch of addresses, executing the ./ontology account add -n [n] -w [wallet file] command in the CLI. The -d bracket is an optional parameter and the default value is 1. -w specifies the wallet file and the default file is wallet.dat. For example, to create 100 addresses at one time:

```
$ ./ontology account add -n 100 -d -w wat.dat
Use default setting '-t ecdsa -b 256 -s SHA256withECDSA' 
	signature algorithm: ecdsa 
	curve: P-256 
	signature scheme: SHA256withECDSA 
Password:
Re-enter Password:

Index: 1
Label: 
Address: ATh1dt4pKZTASu45VeRChPi3iYmk8nYKJH
Public key: 03f8e59f0059d11dcec2902c44a9e7a2466adc9b25a61b1d94d2027d13f78ac45a
Signature scheme: SHA256withECDSA

Index: 2
Label: 
Address: AdYpqD8kn3NwBkkDktqfLfT8jJMCaD7BrB
Public key: 03e05424e711faa1591ee62a20648b45d8328f40c1ad5c479484501445fea62c50
Signature scheme: SHA256withECDSA

Index: 3
Label: 
Address: AY5hDhn2z8ND6F4JF9rQV1a4SDUT4aUr88
Public key: 03de554a6e3eea61aa9f78fa683ce9069ca8980a9f44b85eebe1d2c2e9a611875c
Signature scheme: SHA256withECDSA

....
```



## 3. Process Asset Transactions

### Transaction docking program the exchange needs to develop

1. Monitor new blocks using CLI/API
2. Complete user deposit according to the transaction information 
3. Store transaction records of exchanges

### User deposit

For user deposit, the exchange needs to understand the following:

- In general, due to the different strategies of each exchange, the balance in the exchange's deposit address may not equal to the user's balance in the exchange.

- Ontology address contains ONT and ONG assets. When processing the users' deposit, the exchange needs to judge the asset type so as not to mix up the ONT and ONG deposit.

- The Ontology wallet is a full node. To synchronize the blocks, the wallet needs to be online. You can view the current block height through the CLI command and judge the node status.


  ```
  $ ./ontology info curblockheight
  CurrentBlockHeight:2
  ```

- Transfers between users within the exchange do not need to go through the blockchain, so the exchange can directly modify the users' balance in the database. Only deposit and withdrawal need to go through the blockchain.

Example:

1. A user deposits tokens to the address - ```TA8MoGmzS4T6g3T1CMGEVFiNGkZnn7ixw9```

2. Monitor block information by CLI ```./ontology info block <block number | block hash>```  

   ```
   $ ./ontology info block 209304
   {
      "Hash": "83a70a5380532ededb4f3d65bcd4d3a8cd52f7f87bf1863d68bada59b95133d4",
      "Header": {
         "Version": 0,
         "PrevBlockHash": "e63ede75d1a1784c150edd537b2b5439cc3893be909d5e6970b7baa8b39a5437",
         "TransactionsRoot": "24ac1b3dbecedbac41413ef4578769dd858aab42ccb60b2918c879b129edbf5d",
         "BlockRoot": "8a03e9f3e9adb8abde5b129ba5f833a3555719ffbbf3dd97a931450620a6bbf0",
         "Timestamp": 1528959514,
         "Height": 3016,
         "ConsensusData": 8772979148630824583,
         "ConsensusPayload": "",
         "NextBookkeeper": "AQGN8sEz2dycryR5BxLCQCPYiqKPN5BMnx",
         "Bookkeepers": [
            "0217c25948722c14c1a6fa8e06b78691e722f4598585805671b0beaa7fd6c7662b"
         ],
         "SigData": [
            "a6faf7a3fe356e36977c249f858b8f0a11b719ae310470948e374b69cfb4c3f3d295ac3e81244ebbfc13a4ea94c3deee132ee9ef0caa745b4b6eaf21aeb92c40"
         ],
         "Hash": "83a70a5380532ededb4f3d65bcd4d3a8cd52f7f87bf1863d68bada59b95133d4"
      },
      "Transactions": [
         {
            "Version": 0,
            "Nonce": 4023588455,
            "GasPrice": 0,
            "GasLimit": 30000,
            "Payer": "f72c773b346d3cdf9672fcf9d1a9e0daababa270",
            "TxType": 209,
            "Payload": {
               "Code": "00c66b14e98f4998d837fcdd44a50561f7f32140c7c6c2606a7cc814dd803188dcc41329b6e9faa775a6085269b5db376a7cc808e8030000000000006a7cc86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65",
               "GasLimit": 0
            },
            "Attributes": [],
            "Sigs": [
               {
                  "PubKeys": [
                     "0217c25948722c14c1a6fa8e06b78691e722f4598585805671b0beaa7fd6c7662b"
                  ],
                  "M": 1,
                  "SigData": [
                     "0160ade36dc83fc79e8aee00ca2d7553bbef876a14b511bb68555247903732853134ecae9b9ce053c61b0fb65167e9745fdf7e85bd85861fde901430c3fd4de516"
                  ]
               },
               {
                  "PubKeys": [
                     "0250291da2e26b9f155e19d9a0aae1980124caa55760fcade32217fd93e8a0e750"
                  ],
                  "M": 1,
                  "SigData": [
                     "0106956ada8fb0fe2effe88215b39e607f7faa37f07428b5151a359868b03f701ff04b689bd9a96f5fb3272ee362d6176176f0a04959b953c0c85f220f1198d25f"
                  ]
               }
            ],
            "Hash": "bce10eb97c6cd122131e448ddf415bcd15aabbddd466e6850074c6c839a26596"
         },
         {
            "Version": 0,
            "Nonce": 238868671,
            "GasPrice": 0,
            "GasLimit": 30000,
            "Payer": "f72c773b346d3cdf9672fcf9d1a9e0daababa270",
            "TxType": 209,
            "Payload": {
               "Code": "00c66b14e98f4998d837fcdd44a50561f7f32140c7c6c2606a7cc814dd803188dcc41329b6e9faa775a6085269b5db376a7cc808b0040000000000006a7cc86c51c1087472616e736665721400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b65",
               "GasLimit": 0
            },
            "Attributes": [],
            "Sigs": [
               {
                  "PubKeys": [
                     "0217c25948722c14c1a6fa8e06b78691e722f4598585805671b0beaa7fd6c7662b"
                  ],
                  "M": 1,
                  "SigData": [
                     "0167697964e63236565e81ca35670b7b160fe4c5365bd437d54d467a63c83084f1988dc6c429d683a71ee590520a5c3ee1735657a485a9f549a4bbef76258db67b"
                  ]
               },
               {
                  "PubKeys": [
                     "0250291da2e26b9f155e19d9a0aae1980124caa55760fcade32217fd93e8a0e750"
                  ],
                  "M": 1,
                  "SigData": [
                     "01980eb20147a016b7ddf614107f4d178be3d7d66d56a5ecc56e80daa89bfed11b081f4a907c89338bbe1182d692307b2727d1227809f75c18662c5f3f9f0c43b4"
                  ]
               }
            ],
            "Hash": "10ccaf9188e249a7ff61aa68e429f9e5a916ca01bbeb55ccaec38588b1227518"
         }
      ]
   }
   ```


3. Get all transaction information in the block according to Transaction Hash by CLI  ```./ontology info status```

```
$ ./ontology info status bce10eb97c6cd122131e448ddf415bcd15aabbddd466e6850074c6c839a26596
Transaction states:
{
   "TxHash": "bce10eb97c6cd122131e448ddf415bcd15aabbddd466e6850074c6c839a26596",
   "State": 1,
   "GasConsumed": 0,
   "Notify": [
      {
         "ContractAddress": "0100000000000000000000000000000000000000",
         "States": [
            "transfer",
            "Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT",
            "Aby4Yw4tNEUN28cWY3cYK5Hk3t7opENq8q",
            1000
         ]
      }
   ]
}
```

"State" is 1 representing transaction success, and 0 representing the failure

Parse the "Notify" array:

​     ContractAddress: Contract address：	```0100000000000000000000000000000000000000```  is for ONT

​						        ```0200000000000000000000000000000000000000``` is for ONG

​     States：array

​                The first element: "transfer" represents a transfer operation

​		The second element: From address

​                The third element: To address

​                The fourth element: The transfer amounts （**The actual number of ONT is the number of ONT * 1, and the actual number of ONG is the number of ONG * 10^9**）

To obtain the user's deposit record, you can filter the to address that is generated by the exchange for users. 

### Deposit record

Same as user deposit, the exchange needs to write code to monitor all transactions in all blocks, and record all deposit and withdrawal transactions in the database. If there is a deposit transaction, the exchange needs to modify the corresponding user's balance in the database.



### Process user withdrawal request

With regard to user withdrawal, the exchange needs to complete the following operations:

1. Record user withdrawals and modify users' account balances.

2. Use the CLI command to transfer tokens to the user's withdrawal address:

```
   $ ./ontology asset transfer --from Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT --to AS3SCXw8GKTEeXpdwVw7EcC4rqSebFYpfb --amount 10 
   Password:
   Transfer ONT
     From:Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT
     To:AS3SCXw8GKTEeXpdwVw7EcC4rqSebFYpfb
     Amount:10
     TxHash:49a705f6beb6a15b92493db496f56e8bcddc95b803dac1e4a02b4579ce760b3f

   Tip:
     Using './ontology info status 49a705f6beb6a15b92493db496f56e8bcddc95b803dac1e4a02b4579ce760b3f' to query transaction status

```

  The list of parameters for the command is as follows:

   --wallet, -w  
   Wallet specifies the wallet path of transfer-out account. The default value is: "./wallet.dat".

   --gasprice  
   The total ONG cost of a transaction  is the gaslimit * Gasprice
   The gasprice parameter specifies the gas price of the transfer transaction. The gas price of the transaction cannot be less than the lowest gas price set by node's transaction pool, otherwise the transaction will be rejected. The default value is 0. When there are transactions that are queued for packing into the block in the transaction pool, the transaction pool will deal with transactions according to the gas price and transactions with high gas prices will be prioritized. 

   --gaslimit  
   The gas limit is called the limit because it's the maximum amount of units of gas you are willing to spend on a transaction. 
   However, the actual gas cost is determined by the number of steps or APIs executed by the VM, assuming the following two conditions:  
      1. gaslimit>= actual cost, the transaction will be executed successfully, and return the unconsumed gas;  
         2. Gaslimt< actual cost, the transaction will fail to execute and consume the gas that the VM has already executed;  

        The minimum gas limit allowed for trading is 30,000. Transactions below this amount will not be packaged.
           Gaslimit can be calculate by transaction pre-execution. (Of course by different execution context, such as time, this is not a definite value).  
           In order to make the use of ONT/ONG simpler, all methods of ONT/ONG are set to the lowest gas limit, ie, 30000 gas.

   --asset  
   The asset parameter specifies the asset type of the transfer. Ont indicates the ONT and ong indicates the ONG. The default value is ONT.

   --from   
   The from parameter specifies the transfer-out account address.

   --to  
   The to parameter specifies the transfer-in account address.

   --amount   
   The amount parameter specifies the transfer amount. Note: Since the precision of the ONT is 1, if the input is a floating-point value, then the value of the fractional part will be discarded; the precision of the ONG is 9, so the fractional part beyond 9 bits will be discarded.


   Confirm the transaction result:

   - Use the returned transaction hash to query directly:

   ```
     $ ./ontology info status 49a705f6beb6a15b92493db496f56e8bcddc95b803dac1e4a02b4579ce760b3f
     Transaction states:
     {
        "TxHash": "49a705f6beb6a15b92493db496f56e8bcddc95b803dac1e4a02b4579ce760b3f",
        "State": 1,
        "GasConsumed": 0,
        "Notify": [
           {
              "ContractAddress": "0100000000000000000000000000000000000000",
              "States": [
                 "transfer",
                 "Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT",
                 "AS3SCXw8GKTEeXpdwVw7EcC4rqSebFYpfb",
                 10
              ]
           }
        ]
     }
    
   ```

​     

   - Same as ”user deposit“, monitor transactions in new blocks and filter out successful transactions which are from exchange addresses to user's withdrawal addresses

3. Extract the transaction ID from the returned transaction details of Json format and record it in the database.

4. Wait for the blockchain confirmation. After confirmation, marking the withdrawal record as successful withdrawal.

   Similar to monitoring the blockchain during deposit, the withdrawal process is also the same. If a certain transaction ID in the block is found to be equal to the transaction ID in the withdrawal record during monitoring, the transaction is confirmed and the withdrawal is successful.

5. If the transaction is not confirmed all the time, that is, the corresponding event log cannot be queried through the transaction hash, then

   - Check if the transaction is in the transaction pool via RPC/SDK interface（refer to[Java SDK:ONT and ONG transfer](https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/sdk_get_start.md#2-%E5%8E%9F%E7%94%9F%E8%B5%84%E4%BA%A7ont%E5%92%8Cong%E8%BD%AC%E8%B4%A6))，if it exists，you needs to wait for the consensus node to pack and then query

   - If not, the transaction can be considered as failure and the transfer operation needs to be executed again.


   - If the transaction is not packaged for a long time, it may be due to the gas price being too low.

     

## 4. Java SDK Tutorials

Java SDK Tutorials: [Java SDK Tutorials](https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/sdk_get_start.md) 

### Account management

#### Do not use wallet management

##### Create account randomly

```java
com.github.ontio.account.Account acct = new com.github.ontio.account.Account(ontSdk.defaultSignScheme);
acct.serializePrivateKey();//Private key
acct.serializePublicKey();//Public key
acct.getAddressU160().toBase58();//base58 address
```

##### Create account based on private key

```java
com.github.ontio.account.Account acct0 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey0), ontSdk.defaultSignScheme);
com.github.ontio.account.Account acct1 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey1), ontSdk.defaultSignScheme);
com.github.ontio.account.Account acct2 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey2), ontSdk.defaultSignScheme);

```

#### Use wallet management

[Example](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/WalletDemo.java) 

```java

#### Create a batch of account in the wallet
ontSdk.getWalletMgr().createAccounts(10, "passwordtest");
ontSdk.getWalletMgr().writeWallet();

Create account randomly
AccountInfo info0 = ontSdk.getWalletMgr().createAccountInfo("passwordtest");

Create account based on private key
AccountInfo info = ontSdk.getWalletMgr().createAccountInfoFromPriKey("passwordtest","e467a2a9c9f56b012c71cf2270df42843a9d7ff181934068b4a62bcdd570e8be");

Get account
com.github.ontio.account.Account acct0 = ontSdk.getWalletMgr().getAccount(info.addressBase58,"passwordtest");

```

### Address generation

The address includes single-signature address and multi-signature address, and the generation method is the same as the NEO address.

```
single-signature address generation
String privatekey0 = "c19f16785b8f3543bbaf5e1dbb5d398dfa6c85aaad54fc9d71203ce83e505c07";
String privatekey1 = "49855b16636e70f100cc5f4f42bc20a6535d7414fb8845e7310f8dd065a97221";
String privatekey2 = "1094e90dd7c4fdfd849c14798d725ac351ae0d924b29a279a9ffa77d5737bd96";

//Generate account and get address
com.github.ontio.account.Account acct0 = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey0), ontSdk.defaultSignScheme);
Address sender = acct0.getAddressU160();

//base58 address decode
sender = Address.decodeBase58("AVcv8YBABi9m6vH7faq3t8jWNamDXYytU2")；

//multi-signature address generation
Address recvAddr = Address.addressFromMultiPubKeys(2, acct1.serializePublicKey(), acct2.serializePublicKey());


```

| Method Name             | Parameter                 | Parameter Description                                        |
| :---------------------- | :------------------------ | :----------------------------------------------------------- |
| addressFromMultiPubkeys | int m,byte\[\]... pubkeys | The minimum number of signatures (<=the number of public keys)，public key |


### ONT and ONG transfer

Example：[Example](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/MakeTxWithoutWalletDemo.java)

#### 1. Initialization

```
String ip = "http://polaris1.ont.io";
String rpcUrl = ip + ":" + "20336";
OntSdk ontSdk = OntSdk.getInstance();
ontSdk.setRpc(rpcUrl);
ontSdk.setDefaultConnect(ontSdk.getRpc());

```

#### 2. Query

##### Query ONT, ONG Balance

```
ontSdk.getConnect().getBalance("AVcv8YBABi9m6vH7faq3t8jWNamDXYytU2");

View ONT information:
System.out.println(ontSdk.nativevm().ont().queryName());
System.out.println(ontSdk.nativevm().ont().querySymbol());
System.out.println(ontSdk.nativevm().ont().queryDecimals());
System.out.println(ontSdk.nativevm().ont().queryTotalSupply());

View ONG information:
System.out.println(ontSdk.nativevm().ong().queryName());
System.out.println(ontSdk.nativevm().ong().querySymbol());
System.out.println(ontSdk.nativevm().ong().queryDecimals());
System.out.println(ontSdk.nativevm().ong().queryTotalSupply());

```

##### Query whether the transaction is in the transaction pool

```
ontSdk.getConnect().getMemPoolTxState("d441a967315989116bf0afad498e4016f542c1e7f8605da943f07633996c24cc")


response:transaction is in the tx pool

{
    "Action": "getmempooltxstate",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": {
        "State":[
            {
              "Type":1,
              "Height":744,
              "ErrCode":0
            },
            {
              "Type":0,
              "Height":0,
              "ErrCode":0
            }
       ]
    },
    "Version": "1.0.0"
}

Or transaction is Not in the tx pool:

{
    "Action": "getmempooltxstate",
    "Desc": "UNKNOWN TRANSACTION",
    "Error": 44001,
    "Result": "",
    "Version": "1.0.0"
}


```

##### Query whether the transaction is successful

Query pushing content of a smart contract

```
ontSdk.getConnect().getSmartCodeEvent("d441a967315989116bf0afad498e4016f542c1e7f8605da943f07633996c24cc")


response:
{
    "Action": "getsmartcodeeventbyhash",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": {
        "TxHash": "20046da68ef6a91f6959caa798a5ac7660cc80cf4098921bc63604d93208a8ac",
        "State": 1,
        "GasConsumed": 0,
        "Notify": [
            {
                "ContractAddress": "0100000000000000000000000000000000000000",
                "States": [
                    "transfer",
                    "Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT",
                    "AS3SCXw8GKTEeXpdwVw7EcC4rqSebFYpfb",
                    1000000000
                ]
            }
        ]
    },
    "Version": "1.0.0"
}

```

You can use the block height to query a smart contract event, and the event transaction detail will be returned.

```
ontSdk.getConnect().getSmartCodeEvent(10)

response:
{
    "Action": "getsmartcodeeventbyhash",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": [
                             {
                                  "TxHash": "7e8c19fdd4f9ba67f95659833e336eac37116f74ea8bf7be4541ada05b13503e",
                                  "State": 1,
                                  "GasConsumed": 0,
                                  "Notify": [
                                      {
                                          "ContractAddress": "0200000000000000000000000000000000000000",
                                          "States": [
                                              "transfer",
                                              "AFmseVrdL9f9oyCzZefL9tG6UbvhPbdYzM",
                                              "AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV",
                                              1000000000000000000
                                          ]
                                      }
                                  ]
                              },
                              {
                                  "TxHash": "fc82cd363271729367098fbabcfd0c02cf6ded1e535700d04658b596d53cf07d",
                                  "State": 1,
                                  "GasConsumed": 0,
                                  "Notify": [
                                      {
                                          "ContractAddress": "0200000000000000000000000000000000000000",
                                          "States": [
                                              "transfer",
                                              "AFmseVrdL9f9oyCzZefL9tG6UbvhPbdYzM",
                                              "AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV",
                                              1000000000000000000
                                          ]
                                      }
                                  ]
                              }
     ],
    "Version": "1.0.0"
}

```

##### The list of chain interaction interfaces

| No   |                    Main   Function                     |                      Description                       |
| ---- | :----------------------------------------------------: | :----------------------------------------------------: |
| 1    |       ontSdk.getConnect().getGenerateBlockTime()       |               Query VBFT block-out time                |
| 2    |           ontSdk.getConnect().getNodeCount()           |               Query the number of nodes                |
| 3    |            ontSdk.getConnect().getBlock(15)            |                    Query block info                    |
| 4    |          ontSdk.getConnect().getBlockJson(15)          |                    Query block info                    |
| 5    |       ontSdk.getConnect().getBlockJson("txhash")       |                    Query block info                    |
| 6    |         ontSdk.getConnect().getBlock("txhash")         |                    Query block info                    |
| 7    |          ontSdk.getConnect().getBlockHeight()          |               Query current block height               |
| 8    |      ontSdk.getConnect().getTransaction("txhash")      |                   Query transaction                    |
| 9    | ontSdk.getConnect().getStorage("contractaddress", key) |              Query smart contract storage              |
| 10   |       ontSdk.getConnect().getBalance("address")        |                     Query balance                      |
| 11   | ontSdk.getConnect().getContractJson("contractaddress") |                  Query smart contract                  |
| 12   |       ontSdk.getConnect().getSmartCodeEvent(59)        |         Query the event in the smart contract          |
| 13   |    ontSdk.getConnect().getSmartCodeEvent("txhash")     |         Query the event in the smart contract          |
| 14   |  ontSdk.getConnect().getBlockHeightByTxHash("txhash")  |       Query the block height by transaction hash       |
| 15   |      ontSdk.getConnect().getMerkleProof("txhash")      |                    Get merkle proof                    |
| 16   | ontSdk.getConnect().sendRawTransaction("txhexString")  |                    Send transaction                    |
| 17   |  ontSdk.getConnect().sendRawTransaction(Transaction)   |                    Send transaction                    |
| 18   |    ontSdk.getConnect().sendRawTransactionPreExec()     |            Send a pre-execution transaction            |
| 19   |  ontSdk.getConnect().getAllowance("ont","from","to")   |                  Query Allowed Values                  |
| 20   |        ontSdk.getConnect().getMemPoolTxCount()         | Query total transaction volumn in the transaction pool |
| 21   |        ontSdk.getConnect().getMemPoolTxState()         |    Query transaction status in the transaction pool    |

#### 3. ONT transfer

##### Construct transfer transaction and send

```
// Transferee and payee address
Address sender = acct0.getAddressU160();
Address recvAddr = acct1;

// Multiple address generation
//Address recvAddr = Address.addressFromMultiPubKeys(2, acct1.serializePublicKey(), acct2.serializePublicKey());

// Construct a transfer transaction
long amount = 1000;
Transaction tx = ontSdk.nativevm().ont().makeTransfer(sender.toBase58(),recvAddr.toBase58(), amount,sender.toBase58(),30000,0);

// Sign a transaction
ontSdk.signTx(tx, new com.github.ontio.account.Account[][]{{acct0}});
//Signature scheme of multiple address
ontSdk.signTx(tx, new com.github.ontio.account.Account[][]{{acct1, acct2}});
//If the addresses of the transferee and the payer who pay the network fee are different, the payer’s signature needs to be added.

// Send a transaction
ontSdk.getConnect().sendRawTransaction(tx.toHexString());


```

| Method Name  | Parameter                                                    | Parameter Description                                        |
| :----------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| makeTransfer | String sender，String recvAddr,long amount,String payer,long gaslimit,long gasprice | sender address, receiver address, amount, network fee payer address, gaslimit, gasprice |
| makeTransfer | State\[\] states,String payer,long gaslimit,long gasprice    | A transaction contains multiple transfers                    |

##### Multiple signatures 

If the addresses of the transferee and the payer who pay the network fee are different, the payer’s signature needs to be added.

```
// 1.Add single signature 
ontSdk.addSign(tx,acct0);

// 2.Add multiple signatures 
ontSdk.addMultiSign(tx,2,new com.github.ontio.account.Account[]{acct0,acct1});

```


##### One to multiple or multiple to multiple

1. Construct a transaction with multiple states
2. Signature
3. A transaction includes 1024 transfers at most

```
Address sender1 = acct0.getAddressU160();
Address sender2 = Address.addressFromMultiPubKeys(2, acct1.serializePublicKey(), acct2.serializePublicKey());
int amount = 10;
int amount2 = 20;

State state = new State(sender1, recvAddr, amount);
State state2 = new State(sender2, recvAddr, amount2);
Transaction tx = ontSdk.nativevm().ont().makeTransfer(new State[]{state1,state2},sender1.toBase58(),30000,0);

//The first transferee is a single-signature address, and the second transferee is a multiple-signature address
ontSdk.signTx(tx, new com.github.ontio.account.Account[][]{{acct0}});
ontSdk.addMultiSign(tx,2,new com.github.ontio.account.Account[]{acct1, acct2});

```

##### Use signature server to sign

- **Construct transaction and sign**

1. Construct a transaction, serialize a transaction, send a transaction to the signature server
2. The signature server receives the transaction, deserializes, checks the transaction, and adds the signature
3. Send transaction

```
//Send serialized transaction to signature server
Transaction tx = ontSdk.nativevm().ont().makeTransfer(sender.toBase58(),recvAddr.toBase58(), amount,sender.toBase58(),30000,0);
String txHex = tx.toHexString();

//The receiver deserializes the transaction and signs it
Transaction txRx = Transaction.deserializeFrom(Helper.hexToBytes(txHex));
//View transfer content in the transaction
System.out.println(Transfers.deserializeFrom(Contract.deserializeFrom(txRx.code).args).json());

//Sign
ontSdk.addSign(txRx,acct0);
```

- **Sign data**

[Example](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/SignatureDemo.java) 

```
com.github.ontio.account.Account acct = new com.github.ontio.account.Account(ontSdk.defaultSignScheme);

byte[] data = "12345".getBytes();
byte[] signature = ontSdk.signatureData(acct, data);

System.out.println(ontSdk.verifySignature(acct.serializePublicKey(), data, signature));

```



#### 4. ONG transfer

##### ONG transfer

The interface is similar to ONT:

```
ontSdk.nativevm().ong().makeTransfer...
```

##### Withdraw ONG

1. Check the balance of ONG
2. Create account
3. Construct transaction
4. Signature
5. Send transaction that withdraw ONG

```
//Query non-withdrawal ONG
String addr = acct0.getAddressU160().toBase58();
String ong = sdk.nativevm().ong().unboundOng(addr);

//Claim ong，withdraw ONG
com.github.ontio.account.Account account = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey0), ontSdk.signatureScheme);
String hash = sdk.nativevm().ong().withdrawOng(account,toAddr,64000L,payerAcct,30000,500);

```

| Method Name  | Parameter                                                    | Parameter Description                                        |
| :----------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| makeClaimOng | String claimer,String to,long amount,String payer,long gaslimit,long gasprice | claimer，who to send，amount, network payer address，gaslimit，gasprice |

## 4. Distribute ONG to Users

**NOTE: the following section unavailable since ontology 2.0 update on July 7th 2020**

The exchange can choose whether to distribute the ONG to users. The ONG is used to pay for the Ontology blockchain bookkeeping fees, network fees, and other service fees.

### What is ONG

The total number of ONG is 1 billion with a precision of 9. When the ONT transfer transaction occurs, the unlocked ONG will be authorized by the ONT contract to the transfer sender and receiver. The ONG quantity that the ONT holder can obtain is the percentage of the total amount of ONT owned by the ONT holder. If the transfer transaction has not been triggered, the ONG authorized to the ONT holder will be accumulated and will be issued at the time of the next transfer transaction. This part of the ONG needs to be manually withdrew into wallet address.

### Calculate the amount of ONG that can withdraw

The number of unlocked ONGs is determined by the time interval. The unlock rule is as follows: Unlocking ONG once every second. The number of unlocked ONG is not constant and the unlocked number is determined by ontology unlocked distribution curve. Ontology unlocked distribution curve interval is [5, 4, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]. Approximately every 31536000 blocks, the unlocked value of ONG will be changed. After about 18 years, all ONGs will be unlocked.

**ONG locked list**
![ong](https://s15.postimg.cc/bwnan7anv/image.png)

### Distribute ONG to users

View locked ONG Balances via the CLI：```./ontology asset unboundong <address|index|label>```

```
$ ./ontology asset unboundong 1
Unclaim Ong:
  Account:Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT
  ONG:23698.8755104

```

Withdraw unlocked ONG via CLI：```./ontology asset withdrawong <address|index|label>```

--wallet, -w  
Wallet specifies the wallet path of withdrawal account. The default value is: "./wallet.dat".

--gasprice  
The gasprice parameter specifies the gas price of the transfer transaction. The gas price of the transaction cannot be less than the lowest gas price set by node's transaction pool, otherwise the transaction will be rejected. The default value is 0. When there are transactions that are queued for packing into the block in the transaction pool, the transaction pool will deal with transactions according to the gas price and transactions with high gas prices will be prioritized. 

--gaslimit  
The gaslimit parameter specifies the gas limit of the transfer transaction. The gas limit of the transaction cannot be less than the minimum gas limit set by the node's transaction pool, otherwise the transaction will be rejected. Gasprice * gaslimit is actual ONG costs. The default value is 30000.

```
$ ./ontology asset withdrawong 1
Password:
Claim Ong:
  Account:Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT
  Amount:23698.8755104
  TxHash:c696033f1589a88c7b849dbd2ad0c13a9ca695c3220e4f846f9b1096d0972b80

Tip:
  Using './ontology info status c696033f1589a88c7b849dbd2ad0c13a9ca695c3220e4f846f9b1096d0972b80' to query transaction status

```

Same as user deposit，you can use ```./ontology info status c696033f1589a88c7b849dbd2ad0c13a9ca695c3220e4f846f9b1096d0972b80``` to query the result of the ONG withdrawal.

Example:

Assuming that all addresses of the exchange are in one wallet, the following figure shows the process and calculation formula about how an exchange distributes ONG to a user A:

![ong](./images/ong_en.png)

### Users withdraw ONG

The process of withdrawing the ONG is the same as the process of withdrawing the ONT, just specify the asset parameter as ong:

```
$ ./ontology asset transfer --from Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT --to AS3SCXw8GKTEeXpdwVw7EcC4rqSebFYpfb --amount 10 --asset ong
Password:
Transfer ONG
  From:Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT
  To:AS3SCXw8GKTEeXpdwVw7EcC4rqSebFYpfb
  Amount:10
  TxHash:76b19689042d255f3dac2aaf1b30c86fd83c5abfc983d80b8c64fdcc86f33f5e

Tip:
  Using './ontology info status 76b19689042d255f3dac2aaf1b30c86fd83c5abfc983d80b8c64fdcc86f33f5e' to query transaction status

```

Use Java SDK to withdraw ONG，please refer to[Java SDK:ONG transfer](https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/sdk_get_start.md#24-ong%E8%BD%AC%E8%B4%A6)

## 5. Signature service
When your system doesn't support the SDKs and CLI, you can use the sign server to make and sign transactions:

[Ontology Signature Server Tutorials](https://github.com/ontio/ontology/blob/master/docs/specifications/sigsvr.md)

## 6. OEP4 Token

OEP4 is ontology token protocol : [OEP-4 instruction](https://github.com/ontio/OEPs/blob/master/OEPS/OEP-4.mediawiki)

Use Java SDK:

1. Set OEP4 contract hash to sdk:

   ```
   OntSdk wm = OntSdk.getInstance();
           wm.setRpc(rpcUrl);
           wm.setRestful(restUrl);
           wm.setDefaultConnect(wm.getRestful());
           wm.neovm().oep4().setContractAddress("55e02438c938f6f4eb15a9cb315b26d0169b7fd7");
   ```

   

2. transfer

   ```
   String txhash = ontSdk.neovm().oep4().sendTransfer(account,  //from
   acct.getAddressU160().toBase58(),             //to
   1000,                                         //amount
   account,                                      //payer
   20000,											//gaslimit					
   500);                                         //gasprice    
   ```

   

3. monitor contract events

   ```
   Object result = ontSdk.getConnect().getSmartCodeEvent(height)
   ```

   the result is:

   ```
   [  
      {  
         "GasConsumed":0,
         "Notify":[  
            {  
               "States":[  
                  "7472616e73666572",
                  "e98f4998d837fcdd44a50561f7f32140c7c6c260",
                  "9d1ce056ac1eb29d73104b3e3c7dfc793c879918",
                  "00a0724e1809"
               ],
               "ContractAddress":"75a5cdc00164266a1ba859da785e31cd914ddbd0"
            }
         ],
         "TxHash":"be0430a6d01404350f4f7a724fabea5e5c3c939668e03979362c5bb6fad68fea",
         "State":1
      }
   ]
   ```

   familiar with ONT and ONG:

   "State":1 means the transaction is succeed

   "ContractAddress":"75a5cdc00164266a1ba859da785e31cd914ddbd0"  is the OEP4 contract hash

   "States":[  
                  "7472616e73666572",                                                      //method
                  "e98f4998d837fcdd44a50561f7f32140c7c6c260",       //from
                  "9d1ce056ac1eb29d73104b3e3c7dfc793c879918",     //to
                  "00a0724e1809"                                                                  //amount
               ]

   For a standard OEP4 contract transfer , the event notify should contains "tranfer",from address, to address and amount fields, currently all the OEP4 contracts is Neovm contract, so we need to do decode the fields like below:

   method:

   ```
   byte[] bs =Helper.hexToBytes("7472616e73666572");
   String s = new String(bs); //s is "transfer"
   ```

   from address:

   ```
   Address from = Address.parse("e98f4998d837fcdd44a50561f7f32140c7c6c260");
   System.out.println("from is " + from.toBase58());
   ```

   to address:

   ```
    Address to = Address.parse("70a2ababdae0a9d1f9fc7296df3c6d343b772cf7");
    System.out.println("to is " + to.toBase58());
   ```

   amount:

   ```
   BigInteger amount = Helper.BigIntFromNeoBytes(Helper.hexToBytes("00a0724e1809"));
   System.out.println("amount is " + amount);
   ```

   ***Note*** amount value is contains the "decimal"，you can get it by

   ```
   ontSdk.neovm().oep4().queryDecimals()
   ```

   for the sig server solution, please refer to the [sigserver guide](https://github.com/ontio/documentation/blob/master/exchangeDocs/Sigsvr_Exchange_Guide.md#6-oep4-tokens-transfer)

   ## 7. PAX token
   Pax is an OEP4 Protocol stable token issued by [Paxos](https://www.paxos.com/pax/) on ontology，same with other OEP4 token , you just need to change the contractAddress to：6bbc07bae862db0d7867e4e5b1a13c663e2b4bc8 即可。
   
   [browser](https://explorer.ont.io/contract/6bbc07bae862db0d7867e4e5b1a13c663e2b4bc8/10/1)


## Native contract address

| Name                         | Address(Hex)                             | Address(Base58)                    |
| ---------------------------- | ---------------------------------------- | ---------------------------------- |
| ONT Token                    | 0100000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV |
| ONG Token                    | 0200000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbvhfRZMHJ |
| ONT ID                       | 0300000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6Ubvho7BUwN |
| Global Params                | 0400000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbvhrUqmc2 |
| Oracle                       | 0500000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbvhzQYRMK |
| Authorization Manager(Auth)  | 0600000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6Ubvi9BuggV |
| Governance                   | 0700000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK |
| DDXF(Decentralized Exchange) | 0800000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbviKTaSnK |

## FAQ
[FAQ](https://github.com/ontio/documentation/blob/master/exchangeDocs/ONT%2BExchange%2BDocking%2BFAQ.md)

## Mainnet update note
please refer to the following note to check whether you need to upgrade your sdk version or not:
[Update note](https://github.com/ontio/documentation/blob/master/exchangeDocs/Ontology%20mainnet%20update%20note.md)



### Decimal ONT / ONG

please refer to [Ontology_Decimal&EVM_update](./Ontology_Decimal&EVM_update.md)

