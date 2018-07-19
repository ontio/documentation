---
title:
keywords: sample homepage
sidebar: SDKs_en
permalink: ontology_java_sdk_interface_en.html
folder: doc_en/SDKs
giturl: https://github.com/ontio/ontology-java-sdk/master/docs/en/interface.md
---

<h1 align="center">  Ontology Java SDK Interface</h1>

<p align="center" class="version">Version 1.0.0 </p>

English / [中文](./ontology_java_sdk_interface_zh.html)

## Overview

include：

* init 
* communication with block chain interface
* wallet manager 
* digit asset
* digit identity
* neo smart constract deploy and incoke
* Native smart constract invoke

### init ：

包括打开钱包文件和设置与链交互方式
 ```
     |                    Function                   |     Description            
 ----|-----------------------------------------------|------------------------
   1 | sdk.setRpc(rpcUrl)                            |   set rpc            
   2 | sdk.setRestful(restUrl)                       |   set restful
   3 | sdk.setWesocket(wsUrl, lock)                  |   set websocket
   4 | wm.setDefaultConnect(wm.getWebSocket());     |    set desualt
   5 | wm.openWalletFile("OntAssetDemo.json");        |   open wallet
 ```

### communication with block chain interface：

* 交互接口列表：
```

      |                     Main   Function                      |           Description            
 -----|----------------------------------------------------------|---------------------------------------------
    1 | ontSdk.getConnect().getGenerateBlockTime()               |  query  GenerateBlockTime    
    2 | ontSdk.getConnect().getNodeCount()                       |  query  node count
    3 | ontSdk.getConnect().getBlock(15)                         |  query  block
    4 | ontSdk.getConnect().getBlockJson(15)                     |  query   block   
    5 | ontSdk.getConnect().getBlockJson("txhash")               |  query  block    
    6 | ontSdk.getConnect().getBlock("txhash")                   |  query block     
    7 | ontSdk.getConnect().getBlockHeight()                     |  query height
    8 | ontSdk.getConnect().getTransaction("txhash")             |  query transaction                                     
    9 | ontSdk.getConnect().getStorage("contractaddress", key)   |  query storage
   10 | ontSdk.getConnect().getBalance("address")                |  query balance
   11 | ontSdk.getConnect().getContractJson("contractaddress")   |  query contract          
   12 | ontSdk.getConnect().getSmartCodeEvent(59)                |  query contract event
   13 | ontSdk.getConnect().getSmartCodeEvent("txhash")          |  query contract event
   14 | ontSdk.getConnect().getBlockHeightByTxHash("txhash")     |  query transaction block height
   15 | ontSdk.getConnect().getMerkleProof("txhash")             |  get merkle proof
   16 | ontSdk.getConnect().sendRawTransaction("txhexString")    |  send transaction
   17 | ontSdk.getConnect().sendRawTransaction(Transaction)      |  send transaction
   18 | ontSdk.getConnect().sendRawTransactionPreExec()          |  send prepare execution transaction
   19 | ontSdk.getConnect().getAllowance("ont","from","to")      |  query allowance
   20 | ontSdk.getConnect().getMemPoolTxCount()                  |  query memory pool transaction count
   21 | ontSdk.getConnect().getMemPoolTxState()                  |  query memory pool transaction state
```  

### wallet manager：

包括数字资产和数字身份管理
 
* 数字资产账户：

```  
     |                        Main   Function                                     |     Description            
 ----|----------------------------------------------------------------------------|------------------------ 
   1 | Account importAccount(String encryptedPrikey, String pwd,byte[] salt,String address)   |   import account
   2 | Account createAccount(String password)                                     |   create account
   3 | Account createAccountFromPriKey(String password, String prikey)            |   create with private key
   4 | AccountInfo createAccountInfo(String password)                             |   create with private key
   5 | AccountInfo createAccountInfoFromPriKey(String password, String prikey)    |   create with private key
   6 | AccountInfo getAccountInfo(String address, String password,byte[] salt)    |   get account info
   7 | List<Account> getAccounts()                                                |   get accounts
   8 | Account getAccount(String address)                                         |   get account
   9 | Account getDefaultAccount()                                                |   get default account
```  

* 数字身份：
```  
     |                        Main   Function                                     |     Description            
 ----|----------------------------------------------------------------------------|------------------------ 
   1 | Identity importIdentity(String encryptedPrikey, String pwd,String address) |   
   2 | Identity createIdentity(String password)                                   |   
   3 | Identity createIdentityFromPriKey(String password, String prikey)          |   
   4 | IdentityInfo createIdentityInfo(String password)                           |   
   5 | IdentityInfo createIdentityInfoFromPriKey(String password, String prikey)  |   
   6 | IdentityInfo getIdentityInfo(String ontid, String password)                |     
   7 | List<Identity> getIdentitys()                                              |    
   8 | Identity getIdentity(String ontid)                                         |    
   9 | Identity getDefaultIdentity()                                              |   
  10 | Identity addOntIdController(String ontid, String key, String id)           |    
```        

助记词和keystore接口：

```  
     |                        Main   Function                                     |     Description            
 ----|----------------------------------------------------------------------------|------------------------ 
   1 | Map exportIdentityQRCode(Wallet walletFile, Identity identity)  |   
   2 | Map exportAccountQRCode(Wallet walletFile,Account account)                              |   
   3 | String getPriKeyFromQrCode(String qrcode,String password)          |   
   4 | String generateMnemonicCodesStr()                         |   
   5 | byte[] getSeedFromMnemonicCodesStr(String mnemonicCodesStr) |   
   6 | byte[] getPrikeyFromMnemonicCodesStrBip44(String mnemonicCodesStr)                |     
   7 | String encryptMnemonicCodesStr(String mnemonicCodesStr, String password, String address)    |    
   8 | decryptMnemonicCodesStr(String encryptedMnemonicCodesStr, String password,String address)     |    
```     

### digit asset：

1.native digit asset

2.Nep-5 smartconstract digit asset

* native digit asset：
ont:
```

      |                                         Main   Function                                                     |           Description            
 -----|-------------------------------------------------------------------------------------------------------------|---------------------------------------------
    1 | String sendTransfer(Account sendAcct, String recvAddr, long amount,Account payerAcct,long gaslimit,long gasprice)   |  transfer
    2 | long queryBalanceOf(String address)                                                       |  query Balance
    3 | long queryAllowance(String fromAddr,String toAddr)                                         |  query Allowance
    4 | String sendApprove(Account sendAcct, String recvAddr, long amount,Account payerAcct,long gaslimit,long gasprice)    |  Approve
    5 | String sendTransferFrom(Account sendAcct, String fromAddr, String toAddr,long amount,Account payerAcct,long gaslimit,long gasprice) |  TransferFrom
    6 | String queryName()                                                                          |  query Name
    7 | String querySymbol()                                                                        |  query Symbol
    8 | long queryDecimals()                                                                        |  query Decimals
    9 | long queryTotalSupply()                                                                     |  query TotalSupply
      
```
ong:
```

      |                                         Main   Function                                                     |           Description            
 -----|-------------------------------------------------------------------------------------------------------------|---------------------------------------------
    1 | String sendTransfer(Account sendAcct, String recvAddr, long amount,Account payerAcct,long gaslimit,long gasprice)   |  transfer
    2 | long queryBalanceOf(String address)                                                       |  get balance
    3 | long queryAllowance(String fromAddr,String toAddr)                                         |  get llowance
    4 | String sendApprove(Account sendAcct, String recvAddr, long amount,Account payerAcct,long gaslimit,long gasprice)    |  Approve
    5 | String sendTransferFrom(Account sendAcct, String fromAddr, String toAddr,long amount,Account payerAcct,long gaslimit,long gasprice) | TransferFrom
    6 | String queryName()                                                                          |  query name
    7 | String querySymbol()                                                                        |  query Symbol
    8 | long queryDecimals()                                                                        |  query Decimals
    9 | long queryTotalSupply()                                                                     |  query TotalSupply
   10 | String claimOng(Account sendAcct, String toAddr, long amount, Account payerAcct, long gaslimit, long gasprice)             |  claim ong
   11 | String unclaimOng(String address)                                                                           |  query unclaim ong
      
```   

* Nep-5 digit asset:

```  
      |                                         Main   Function                                       |           Description            
 -----|-----------------------------------------------------------------------------------------------|---------------------------------------------
    1 | void setContractAddress(String codeHash)                                                      | set contract address
    2 | String sendInit(Account acct, Account payerAcct,long gaslimit,long gasprice)                   |  init 
    3 | long sendInitGetGasLimit()                                                                     |  prepare execution init
    4 | String sendTransfer(Account acct, String recvAddr, long amount,Account payerAcct, long gaslimit,long gasprice)        |  transfer
    5 | long sendTransferGetGasLimit(Account acct, String recvAddr, long amount)                      |  prepare execution transfer                              
    6 | String queryBalanceOf(String addr)                                                            |  query balance
    7 | String queryTotalSupply()                                                                     |  query  TotalSupply
    8 | String queryName()                                                                            |  query name
    9 | String queryDecimals()                                                                        |  query decimals
   10 | String querySymbol()                                                                          |  query Symbol

```  

### digit identity：

1.Register, AddPubKey,AddAttribute,AddRecovery

2.claim create and verify

3.claim record

* ontid：
```
      |                                         Main   Function                                                     |           Description            
 -----|-------------------------------------------------------------------------------------------------------------|---------------------------------------------
    1 | String getContractAddress()                                                                                                                             |  get contract address 
    2 | Identity sendRegister(Identity ident, String password,byte[] salt,Account payerAcct,long gaslimit,long gasprice)                                         |  register ontid
    3 | Identity sendRegisterPreExec(Identity ident, String password,byte[] salt,Account payerAcct,long gaslimit,long gasprice)                                  |  prepare execution registryontid
    4 | Identity sendRegisterWithAttrs(Identity ident, String password,byte[] salt,Attribute[] attributes,Account payerAcct,long gaslimit,long gasprice)         |  register ontid with add attribute
    5 | String sendAddPubKey(String ontid, String password,byte[] salt, String newpubkey,Account payerAcct,long gaslimit,long gasprice)                          |  add pubkey
    6 | String sendAddPubKey(String ontid,String recoveryOntid, String password,byte[] salt, String newpubkey,Account payerAcct,long gaslimit,long gasprice)      |  add pubkey
    7 | String sendGetPublicKeys(String ontid)                                                                                                                  |  add pubkey
    8 | String sendRemovePubKey(String ontid, String password,byte[] salt, String removePubkey,Account payerAcct,long gaslimit,long gasprice)                    |  remove pubkey
    9 | String sendRemovePubKey(String ontid, String recoveryOntid,String password,byte[] salt, String removePubkey,Account payerAcct,long gaslimit,long gasprice)|  remove pubkey
   10 | String sendGetKeyState(String ontid,int index)                                                                                                          |  get pubkey status
   11 | String sendAddAttributes(String ontid, String password,byte[] salt, Attribute[] attributes,Account payerAcct,long gaslimit,long gasprice)                |  add attribute
   12 | String sendGetAttributes(String ontid)                                                                                                                  |  query attribute
   13 | String sendRemoveAttribute(String ontid,String password,byte[] salt,String path,Account payerAcct,long gaslimit,long gasprice)                           |  remove attribute
   14 | String sendAddRecovery(String ontid, String password,byte[] salt, String recoveryOntid,Account payerAcct,long gaslimit,long gasprice)                     |  add Recovery
   15 | String sendChangeRecovery(String ontid, String newRecovery, String oldRecovery, String password,byte[] salt,Account payerAcct, long gaslimit,long gasprice)                            |  change Recovery
   16 | String sendGetDDO(String ontid)                                                                                                                         |  get DDO
   
```

* make tansaction：

 ```  
     |                                           Make Transaction  Function                                                |     Description            
 ----|---------------------------------------------------------------------------------------------------------------------|------------------------ 
   1 | Transaction makeRegister(String ontid,String password,byte[] salt,String payer,long gaslimit,long gasprice)                                              |
   2 | Transaction makeRegisterWithAttrs(String ontid, String password,byte[] salt, Attribute[] attributes, String payer, long gaslimit, long gasprice)         |
   3 | Transaction makeAddPubKey(String ontid,String password,byte[] salt,String newpubkey,String payer,long gaslimit,long gasprice)                            |
   4 | Transaction makeAddPubKey(String ontid,String recoveryAddr,String password,byte[] salt,String newpubkey,String payer,long gaslimit,long gasprice)        |
   5 | Transaction makeRemovePubKey(String ontid, String password,byte[] salt, String removePubkey,String payer,long gaslimit,long gasprice)                    |
   6 | Transaction makeRemovePubKey(String ontid,String recoveryAddr, String password, byte[] salt,String removePubkey,String payer,long gaslimit,long gasprice)|
   7 | Transaction makeAddAttributes(String ontid, String password,byte[] salt, Attribute[] attributes,String payer,long gaslimit,long gasprice)                |
   8 | Transaction makeRemoveAttribute(String ontid,String password,byte[] salt,String path,String payer,long gaslimit,long gasprice)                           |
   9 | Transaction makeAddRecovery(String ontid, String password,byte[] salt, String recoveryAddr,String payer,long gaslimit,long gasprice)                     |
  ```
  
* Claim：
  
 ```
     |                                           Claim Function                                                                      |     Description            
 ----|-------------------------------------------------------------------------------------------------------------------------------|------------------------
   1 | public Object getMerkleProof(String txhash)                                                                                   |   
   2 | boolean verifyMerkleProof(String claim)                                                                                       |                 
   3 | String createOntIdClaim(String signerOntid, String pwd,byte[] salt, String context, Map claimMap, Map metaData,Map clmRevMap,long expire) |
   4 | boolean verifyOntIdClaim(String claim)                                                                                        |   
  
 ```
 
* Claim record：
  
 ```
     |                                            Function                                                         |     Description
 ----|-------------------------------------------------------------------------------------------------------------|------------------------
   1 | String sendCommit(String issuerOntid,String pwd,byte[] salt,String subjectOntid,String claimId,Account payerAcct,long gaslimit,long gasprice)  |
   2 | String sendRevoke(String issuerOntid,String password,byte[] salt,String claimId,Account payerAcct,long gaslimit,long gasprice)                 |
   3 | String sendGetStatus(String claimId)                                                                                               |   
  
 ```
 
 ### neo smart contract deploy and invoke
 
 deploy and invoke
  ```
      |                                            Function                                                                                                                             |     Description            
  ----|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------
    1 | DeployCode makeDeployCodeTransaction(String code, boolean needStorage, String name, String version, String author, String email, String desp, byte vmtype,String payer,long gaslimit,long gasprice)|   deploy
    2 | InvokeCode makeInvokeCodeTransaction(String codeAddr,String method,byte[] params, byte vmtype, String payer,long gaslimit,long gasprice)                                                           |   invoke
   
  ```

 ### Native smart contract invoke

 #### auth manager contract

* auth manager：
 ```
       |                                            Function                                                                                                                               |     Description
   ----|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------
     1 | String sendTransfer(String adminOntId,String password,byte[] salt,String contractAddr, String newAdminOntID,int key,Account payerAcct,long gaslimit,long gasprice)                 |
     2 | String assignFuncsToRole(String adminOntID,String password,byte[] salt,String contractAddr,String role,String[] funcName,int key,Account payerAcct, long gaslimit,long gasprice)    |
     3 | String assignOntIDsToRole(String adminOntId,String password,byte[] salt,String contractAddr,String role,String[] ontIDs, int key,Account payerAcct, long gaslimit,long gasprice)    |
     4 | String delegate(String ontid,String password,byte[] salt,String contractAddr,String toOntId,String role,int period,int level,int key,Account payerAcct, long gaslimit,long gasprice)|
     5 | String withdraw(String initiatorOntid,String password,byte[] salt,String contractAddr,String delegate, String role,int key,Account payerAcct, long gaslimit,long gasprice)          |
 ```

 * make transaction：
```
       |                                            Function                                                                                                                               |     Description
   ----|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------
     1 | Transaction makeTransfer(String adminOntID,String contractAddr, String newAdminOntID,int key,String payer,long gaslimit,long gasprice)                    |   
     2 | Transaction makeAssignFuncsToRole(String adminOntID,String contractAddr,String role,String[] funcName,int key,String payer,long gaslimit,long gasprice)   |   
     3 | Transaction makeAssignOntIDsToRole(String adminOntId,String contractAddr,String role,String[] ontIDs, int key,String payer,long gaslimit,long gasprice)   |   
     4 | Transaction makeDelegate(String ontid,String contractAddr,String toAddr,String role,int period,int level,int key,String payer,long gaslimit,long gasprice)|   
     5 | Transaction makeWithDraw(String ontid,String contractAddr,String delegate, String role,int key,String payer,long gaslimit,long gasprice)                  |   
 ```
 
  #### Governance contract
  
   ```
         |                                            Function                                                                                                                               |     Description
     ----|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------
       1 | String registerCandidate(Account account, String peerPubkey, long initPos, String ontid,String ontidpwd,byte[] salt,  long keyNo, Account payerAcct, long gaslimit, long gasprice)                |
       2 | String unRegisterCandidate(Account account, String peerPubkey,Account payerAcct, long gaslimit, long gasprice)   |
       3 | String withdrawOng(Account account,Account payerAcct,long gaslimit,long gasprice)    |
       4 | String getPeerInfo(String peerPubkey) |
       5 | String getPeerInfoAll()       |
       6 | VoteInfo getVoteInfo(String peerPubkey,Address addr)       |
       7 | String withdraw(Account account,String peerPubkey[],long[] withdrawList,Account payerAcct,long gaslimit,long gasprice)
       8 | String quitNode(Account account,String peerPubkey,Account payerAcct,long gaslimit,long gasprice)
   ```
