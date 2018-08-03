---
title:
keywords: sample homepage
sidebar: Dapp_en
permalink: auth_en.html
folder: doc_en/Dapp
giturl: https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/auth.md
---

<h1 align="center"> Authorization management </h1>

<p align="center" class="version">Version 1.0.0 </p>

English / [中文](./auth_zh.html)


At present, smart contracts can be called on by anyone, but this does not conform to the real requirements. The basic idea of the role-based authority management is that each role can call on certain functions and each entity can be given multiple roles (entities are identified by ONT ID).
If a smart contract needs to add an authority management function, then information such as roles allocated in the contract, roles’ callable function, and which entity does the role belong to etc. must be recorded. This can be a very elaborate process and can be managed by a system contract.

For details, please refer to
https://github.com/ontio/ontology-smartcontract/blob/master/smartcontract/native/auth/auth.md


*  Authority Contract Management

*  Usage Examples

*  Interface list

### Authority Contract Management

Auth contract is responsible for managing authority of an application contract. Contract administrator can transfer the authority, allocate functions for roles, revoke contract calling privileges, and can verify the validity of the contract call token through entity validation.

Auth contract implements a role-based authority management solution. Each role corresponds to some callable function. Administrator assigns a role to an ONT ID to make it possible to call functions under that role. At the same time, roles can be passed, which means A can pass a certain role delegation to B and appoint the delegation time, so that B can also call the corresponding functions in a certain period.

### Usage Examples

Ontology smart contract does not support initialization execution during employment, therefore, the contract administrator needs to hardcode it into contract code, where the contract administrator’s ONTID is defined as a constant in the contract. For more details please refer to the following contract example: Ontology smart contract can call VerifyToken function for authority verification. At the same time, for developers’ convenience to check if an ONTID has a role, Java-SDK also provides VerifyToken interface where one can check role allocations.

Use flow:
```
1. Deploy smart contract on-chain.
2. Call init methods in the smart contract. Use initContractAdmin method in the contract code to set up a pre-defined administrator ONT ID as the contract administration (please note: it is needed to register the administrator’s ONT ID on-chain).
3. Contract administrator designs the role required and binds it with the function in the smart contract. This step can call assignFuncsToRole interface in Java-SDK for settings.
4. Contract administrator allocates role to ONT ID, ONT ID that owns the role will have authority to call the corresponding function of the role. This step can call assignFuncsToRole interface in Java-SDK for settings.
5. ONT ID with role, before calling its corresponding function, can use VerifyToken Interface in Java-SDK to verify if ONTID has the right to call the corresponding function
```

Use the following examples to illustrate the use flow:

A.	Deploy smart contract on-chain
B.	Call init method in this contract

```
AbiInfo abiInfo = JSON.parseObject(abi,AbiInfo.class);
String name = "init";
AbiFunction function = abiInfo.getFunction(name);
function.setParamsValue();
String txhash = (String) sdk.neovm().sendTransaction(Helper.reverse(codeAddress),account,account,sdk.DEFAULT_GAS_LIMIT,0,function,false);
```

C.	Contract administrator designs role 1 and role 2, and binds role 1 and function foo1, as well as role2 and function foo2 and foo3.

```
String txhash = sdk.nativevm().auth().assignFuncsToRole(adminIdentity.ontid, password, adminIdentity.controls.get(0).getSalt(),
1, Helper.reverse(codeAddress), "role1", new String[]{"foo1"}, account, sdk.DEFAULT_GAS_LIMIT, 0);

String txhash = sdk.nativevm().auth().assignFuncsToRole(adminIdentity.ontid, password, adminIdentity.controls.get(0).getSalt(), 1,
Helper.reverse(codeAddress), "role2", new String[]{"foo2","foo3"}, account, sdk.DEFAULT_GAS_LIMIT, 0);

```

D.	Contract administrator will allocate role 1 to OntID1 and role 2 to OntID2, then OntID1 has the authority to call function foo1 and OntID2 has the authority to call function foo2 and foo3.
```
String txhash = sdk.nativevm().auth().assignOntIdsToRole(adminIdentity.ontid, password, adminIdentity.controls.get(0).getSalt(), 1,
Helper.reverse(codeAddress), "role1", new String[]{identity1.ontid}, account, sdk.DEFAULT_GAS_LIMIT, 0);

String txhash = sdk.nativevm().auth().assignOntIdsToRole(adminIdentity.ontid, password, adminIdentity.controls.get(0).getSalt(), 1,
Helper.reverse(codeAddress), "role2", new String[]{identity2.ontid}, account, sdk.DEFAULT_GAS_LIMIT, 0);

```

E.	As ONTID1’s role is allocated by contract administrator, its authority level default is 2, which means ONTID1 can transfer its authority delegation to another ONTIDX, the delegation interface Java-SDK is delegate, more details can be referred from the following interface information. When delegating authority, it is required to have the appointed principal’s authority level and delegation time. If the level of the delegate is 2, then the principal’s level can only be 1.
```
sdk.nativevm().auth().delegate(identity1.ontid,password,identity1.controls.get(0).getSalt(),1,Helper.reverse(codeAddress),
identityX.ontid,"role1",60*5,1,account,sdk.DEFAULT_GAS_LIMIT,0);
```
F.	Verify if an ONTID has the authority to call a certain function via VerifyToken interface.
```
String result = sdk.nativevm().auth().verifyToken(identityX.ontid, password, identityX.controls.get(0).getSalt(), 1, Helper.reverse(codeAddress), "foo1");

Returned Value: “01” means has authority, “00” means no authority.
```

G.	If the principal’s authority time has not finished, the delegate can revoke the authority that is delegated to others.
```
sdk.nativevm().auth().withdraw(identity1.ontid,password,identity1.controls.get(0).getSalt(),1,Helper.reverse(codeAddress),identityX.ontid,"role1",account,sdk.DEFAULT_GAS_LIMIT,0);
```

H.	Contract administrator can pass his or her administration authority to other ONTID.
```
String txhash = sdk.nativevm().auth().sendTransfer(adminIdentity.ontid,password,adminIdentity.controls.get(0).getSalt(),1,Helper.reverse(codeAddress),adminIdentity.ontid,
account,sdk.DEFAULT_GAS_LIMIT,0);
```

Ontology contract example:
```
using Neo.SmartContract.Framework;
using Neo.SmartContract.Framework.Services.Neo;
using Neo.SmartContract.Framework.Services.System;
using System;
using System.ComponentModel;
using System.Numerics;

namespace Example
{
    public class AppContract : SmartContract
    {
        public struct initContractAdminParam
        {
            public byte[] adminOntID;
        }

        public struct verifyTokenParam
        {
            public byte[] contractAddr; // Contract Address
            public byte[] calllerOntID; // ontId Caller’s ONTID
            public string funcName;     // Function Name
            public int keyNo;           // Which number of public key of Caller’s ONTID is used?
        }

        //the admin ONT ID of this contract must be hardcoded.
        public static readonly byte[] adminOntID = "did:ont:AazEvfQPcQ2GEFFPLF1ZLwQ7K5jDn81hve".AsByteArray();

        public static Object Main(string operation,object[] args)
        {
            if (operation == "init") return init();

            if (operation == "foo")
            {
                //we need to check if the caller is authorized to invoke foo
                if (!verifyToken(operation, args)) return "no auth";

                return foo();
            }
            if (operation == "foo2")
            {
                //we need to check if the caller is authorized to invoke foo
                if (!verifyToken(operation, args)) return "no auth";

                return foo2();
            }
            if (operation == "foo3")
            {
                //we need to check if the caller is authorized to invoke foo
                if (!verifyToken(operation, args)) return "no auth";

                return foo3();
            }

            return "over";
        }

        public static string foo()
        {
            return "A";
        }
        public static string foo2()
        {
            return "B";
        }
        public static string foo3()
        {
            return "C";
        }

        //this method is a must-defined method if you want to use native auth contract.
        public static bool init()
        {
            byte[] authContractAddr = {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x06 };
            byte[] ret = Native.Invoke(0, authContractAddr, "initContractAdmin", adminOntID);
            return ret[0] == 1;
        }

        internal static bool verifyToken(string operation, object[] args)
        {
            verifyTokenParam param = new verifyTokenParam{};
            param.contractAddr = ExecutionEngine.ExecutingScriptHash;
            param.funcName = operation;
            param.calllerOntID = (byte[])args[0];
            param.keyNo = (int)args[1];

            byte[] authContractAddr = {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x06 };
            byte[] ret = Native.Invoke(0, authContractAddr, "verifyToken", param);
            return ret[0] == 1;
        }
    }
}
```


### Interface list

Java-SDK has encapsulated the call interface for authority contract. The authority can be managed through Java-SDK.

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
||gaslimit|Gaslimit|
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
||gaslimit|Gaslimit|
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
||gaslimit|Gaslimit|
||gasprice|Gas price|
|Return value instruction|Transaction hash||

4. String delegate(String ontid,String password,salt,String contractAddr,String toOntId,String role,long period,long level,long keyNo,Account payerAcct,long gaslimit,long gasprice)

Role owner can assign a role to other people, from is the ONT ID for assigner, to is the ONT ID for the assignee/delegate, role is the assigned role, period parameter specifies the term time of delegation by second.


Delegate can assign its role to more people, level parameter specifies the depth of the delegate level, for instance,

 Level = 1：Delegate cannot assign its role. The current realization only supports this case.

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
||gaslimit|Gaslimit|
||gasprice|Gas price|
|Return value instruction|Transaction hash||

5. String withdraw(String initiatorOntid,String password,byte[] salt,String contractAddr,String delegate, String role,long keyNo,Account payerAcct,long gaslimit,long gasprice)

Role owners can revoke the role delegation in advance. InitiatorOntid is the initiator, delegate is role delegate, initiator revokes the role delegated to the delegate in advance.

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
||gaslimit|Gaslimit|
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
||gaslimit|Gaslimit|
||gasprice|Gas price|
|Return value instruction|Transaction hash||
