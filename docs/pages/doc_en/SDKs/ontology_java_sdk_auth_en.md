---
title:
keywords: sample homepage
sidebar: SDKs_en
permalink: ontology_java_sdk_auth_en.html
folder: doc_en/SDKs
giturl: https://github.com/ontio/ontology-java-sdk/master/docs/en/auth.md
---

<h1 align="center"> Authorization management </h1>

<p align="center" class="version">Version 1.0.0 </p>

English / [中文](./auth_zh.html)


Currently, the function of smart contract can be called by anyone, which obviously does not meet the actual requirements. The basic idea of ​​role-based authorization management is that each role can call a partial function, and each entity can be assigned multiple roles (the entity is identified by its ONT ID).

If the smart contract needs to add the authorization management function, it must record the roles assigned by the contract, the functions that the role can call, which entity has this role, and so on. This work is tedious and can be managed by a system contract.

For details, please refer to 
https://github.com/ontio/ontology-smartcontract/blob/master/smartcontract/native/auth/auth.md


*  Management of authorization management contract

* Interface list

### Management of authorization management contract

The Auth contract is responsible for managing the function call authorizations of the application contract. The functions include that the contract administrator can transfer the contract management authorization, the contract administrator can assign the function to the role, the contract administrator can bind the role to the entity identity, the entity with the contract function call authorization can delegate its authorization to others, the contract administrator can recall the contract call authorization, and the entity verifies the validity of the contract call token.

Interface list

1. String sendTransfer(String adminOntId, String password, byte[] salt, String contractAddr, String newAdminOntID, long keyNo, Account payerAcct, long gaslimit, long gasprice)

|Instruction||Description|
|:--|:--|:--|
|Function instruction|Contract administrator transfers contract management authorization|This function must be called by the contract administrator and we use the public key with the number keyNo in the adminOntID to verify the validity of transaction signature. |
|Parameter instruction|Field|Description|
||adminOntId|Contract administrator's ontid|
||password|Contract administrator's password|
||salt|Private key decryption parameters|
||contractAddr|Contract address|
||newAdminOntID|New administrator|
||keyNo|Contract administrator's public key KeyNo|
||payerAcct|Paid account|
||gaslimit|Gas price|
||gasprice|Gas price|
|Return value instruction|Transaction hash||
    

2. String assignFuncsToRole(String adminOntID,String password,byte[] salt,String contractAddr,String role,String[] funcName,long keyNo,Account payerAcct,long gaslimit,long gasprice)

|instruction||Description|
|:--|:--|:--|
|Function instruction|Assign a function to a role|This function must be called by the contract administrator, and it will automatically bind all functions to the role. if it is already binded, the binding procedure will skip automatically, and return true in the end.|
|Parameter instruction|Field|Description|
||adminOntId|Contract administrator's ontid|
||password|Contract administrator's password|
||salt|Private key decryption parameters|
||contractAddr|Contract address|
||role|Role|
||funcName|Function name|
||keyNo|Contract administrator's KeyNo|
||payerAcct|Paid account|
||gaslimit|Gas price|
||gasprice|Gas price|
|Return value instruction|Transaction hash||
    
    

3. String assignOntIDsToRole(String adminOntId,String password,salt,String contractAddr,String role,String[] ontIDs,long keyNo,Account payerAcct,long gaslimit,long gasprice)

|instruction||Description|
|:--|:--|:--|
|Function instruction|Bind a role to an entity|This function must be called by the contract administrator. The ONT ID in the ontIDs array is assigned the role and finally returns true. In the current implementation, the level of the permission token is equal to 2 by default.|
|Parameter instruction|Field|Description|
||adminOntId|Contract administrator's ontid|
||password|Contract administrator password|
||salt|Private key decryption parameters|
||contractAddr|Contract address|
||role|Role|
||ontIDs|ontid array|
||keyNo|Contract administrator's public key KeyNo|
||payerAcct|Paid account|
||gaslimit|Gas price|
||gasprice|Gas price|
|Return value instruction|Transaction hash||

4. String delegate(String ontid,String password,salt,String contractAddr,String toOntId,String role,long period,long level,long keyNo,Account payerAcct,long gaslimit,long gasprice)

The role owner can delegate the role to others. "from:" is the ONT ID of the transferor, "to" is the ONT ID of the delegator, "role" is the role of delegator, and the "period" parameter specifies the duration of the delegation. (use second as the unit).


The delegator can delegate his role to other people too, and the parameter level specifies the depth of the delegation level. E.g,

level = 1: The delegator cannot delegate his role to others; the current implementation only supports this situation.

|instruction||Description|
|:--|:--|:--|
|Function instruction|Delegate contract call authorization to others||
|Parameter instruction|Field|Description|
||ontid|The ontid of a function call authorization in the contract|
||password|ontid password|
||salt|Private key decryption parameters|
||contractAddr|Contract address|
||toOntId|The ontid that receives contract call authorization|
||role|Role|
||period|Use second as the unit|
||keyNo|The KeyNo of ontid public key|
||payerAcct|Paid account|
||gaslimit|Gas price|
||gasprice|Gas price|
|Return value instruction|Transaction hash||

5. String withdraw(String initiatorOntid,String password,byte[] salt,String contractAddr,String delegate, String role,long keyNo,Account payerAcct,long gaslimit,long gasprice)

The role owner can withdraw the role delegation in advance. initiator is the initiator, delegate is the role delegator, and the initiator can withdraw the role from the delegator in advance.

|instruction||Description|
|:--|:--|:--|
|Function instruction|Revocate contract call authorization（use with delegate function）||
|Parameter instruction|Field|Description|
||initiatorOntid|Transfer contract call authorization to other's ontid|
||password|ontid password|
||salt|Private key decryption parameters|
||contractAddr|Contract address|
||delegate|Delegator's ontid|
||role|Role|
||keyNo|ontid public key KeyNo|
||payerAcct|Paid account|
||gaslimit|Gas price|
||gasprice|Gas price|
|Return value instruction|Transaction hash||

6. String verifyToken(String ontid,String password,byte[] salt,String contractAddr,String funcName,long keyNo,Account payerAcct,long gaslimit,long gasprice)

|instruction||Description|
|:--|:--|:--|
|Function instruction|Verify the validity of contract call token||
|Parameter instruction|Field|Description|
||ontid|ontid that should be verified|
||password|ontid password|
||salt|Private key decryption parameters|
||contractAddr|Contract address|
||funcName|Function name|
||keyNo|ontid public key KeyNo|
||payerAcct|Paid account|
||gaslimit|Gas price|
||gasprice|Gas price|
|Return value instruction|Transaction hash||
