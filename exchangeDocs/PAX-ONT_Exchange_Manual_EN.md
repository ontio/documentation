# PAX to PAXO Manual



## 1. Background

`PAX is` a `ERC-20` stable coin issued on ethereum blockchain. now, `PAX` is bring to the` Ontology `blockchain.

 `Ontology offical`  deploy a smart contract to recycling the `PAX` `ERC-20` token, the `PAX` token holder transfer `PAX` to the recycle smart  contract，Ontology then deploy a monitoring server to monitor the recycle contract，any `PAX` to `PAXO` transactions, the program will  and transfer same number of `PAXO`  to the holder's `ONT` wallet address  on the `Ontology` chain.

The `PAX`and`PAXO` **1 to 1** anchor

## 2. PAX->PAXO steps

Below steps are demonstrated through `Remix`. In  real scenario, you need to use  ehtereum client to invoke smart contract on ethereum.

### 2.1. PAX ERC-20 Token smart contract compile

`PAX` ERC-20 token source code：[Pax Contract](https://github.com/paxosglobal/pax-contracts)

Need to compile `PAXImplementation.sol` on `REMIX`, choose solidity compiler version `0.4.24`

After compile success，In the upper right corner **Run** option, select the `PAXImplementation`

Enter the `PAX` Token contract in the **At Address** input box:`0x8e870d67f660d95d5be530380d0ec0bd388289e1`



![](./images/pax01.png)

as shown below



![](./images/pax02.png)



### 2.2. Approve PAX token to recycle contract

`PAX` smat contract address: `0x8e870d67f660d95d5be530380d0ec0bd388289e1`

invoke function: `approve`

Parameters:

- ：**_spender**： `address`，default is the recycle smart contract address:`0x0628ba39a124b772fae5edd52d2aa330e0f1078a`

- ：_**value**: `bigint`，PAX token decimals is 18，if you want approve 1 PAX token，the value should be 1000000000000000000



![](./images/pax03.png)



### 2.3. transfer PAX to recycle contract

The `PAX` recycle contract address：`0x0628ba39a124b772fae5edd52d2aa330e0f1078a`

Invoke function：`PAXTOOEP4`

Parameters:

- **_ont_base58_address**： `string`,PAX token holder `ONT` wallet address

- **_value**：`bigint`，the number of `PAXO` you need to convert

  

![](./images/pax04.png)



After convert is successful, the holder's `PAX` will be  reduced, and the holder's `PAXO` balance will increase in same amount.

`PAXO`的 smart contract address is 6bbc07bae862db0d7867e4e5b1a13c663e2b4bc8`

Can query  `PAXO` balance on [ontology explorer](https://explorer.ont.io/)



