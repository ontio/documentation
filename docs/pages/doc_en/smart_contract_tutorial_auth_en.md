---
title: 
keywords: sample homepage
sidebar: ont_doc_en
permalink: smart_contract_tutorial_auth_en.html
folder: doc_en
---


English / [中文](./smart_contract_tutorial_auth_zh.html)

<h1 align="center"> Ontology Java SDK User Guide </h1>
<p align="center" class="version">Version 1.0.0 </p>

# Authority Management

- [Authority Management](#authority-management)
    - [Authority Contract Management](#authority-contract-management)
        - [Usage Examples](#usage-examples)
        - [Interface List](#interface-list)

At present, smart contracts can be called on by anyone, but this does not conform to the real requirements. The basic idea of the role-based authority management is that each role can call on certain functions and each entity can be given multiple roles (entities are identified by ONT ID).

If a smart contract needs to add an authority management function, then information such as roles allocated in the contract, roles callable function, and which entity does the role belong to and etc. must be recorded. This can be a very elaborate process and can be managed by a system contract. 

For further details, please refer to:
https://github.com/ontio/ontology-smartcontract/blob/master/smartcontract/native/auth/auth.md

* Authority Contract Management
* Usage Examples
* Interface List
 
## Authority Contract Management

`Auth` contract is responsible for managing authority of an application contract. Contract administrator can transfer the authority, allocate functions for roles, revoke contract calling privileges, and can verify the validity of the contract call token through entity validation.

Auth contract implements a role-based authority management solution. Each role corresponds to some callable function. Administrator assigns a role to an ONT ID to make it possible to call functions under that role. At the same time, roles can be passed, which means A can pass a certain role delegation to B and appoint the delegation time, so that B can also call the corresponding functions in a certain period of time.

### Usage Examples

OntologyONT IDOntologyverifyTokenOntIDJava-SDKverifyToken
Ontology smart contract does not support initialization execution during employment, therefore, the contract administrator needs to hardcode it into contract code, where the contract administrators ONTID is defined as a constant in the contract. For more details please refer to the following contract example: Ontology smart contract can call VerifyToken function for authority verification. At the same time, for developers convenience to check if an ONTID has a role, Java-SDK also provides VerifyToken interface where one can check role allocations. 

Use flow:

> 1. Deploy smart contract on-chain.

> 2. initinitContractAdminONT ID:ONT ID
Call init methods in the smart contract. Use initContractAdmin method in the contract code to set up a pre-defined administrator ONT ID as the contract administration (please note: it is needed to register the administrators ONT ID on-chain).

> 3. Java-SDKassignFuncsToRole
Contract administrator designs the role required and binds it with the function in the smart contract. This step can call assignFuncsToRole interface in Java-SDK for settings.

> 4. ONT IDONT IDJava-SDKassignOntIDsToRole
Contract administrator allocates role to ONT ID, ONT ID that owns the role will have authority to call the corresponding function of the role. This step can call assignFuncsToRole interface in Java-SDK for settings.

> 5. ONT IDJava-SDKverifyTokenontid
ONT ID with role, before calling its corresponding function, can use VerifyToken Interface in Java-SDK to verify if ONTID has the right to call the corresponding function

Use the following examples to illustrate the use flow:

1. Deploy smart contract on-chain

2. initCall init method in this contract

```
AbiInfo abiInfo = JSON.parseObject(abi,AbiInfo.class);
String name = "init";
AbiFunction function = abiInfo.getFunction(name);
function.setParamsValue();
String txhash = (String) sdk.neovm().sendTransaction(Helper.reverse(codeAddress),account,account,sdk.DEFAULT_GAS_LIMIT,0,function,false);
```

3. Contract administrator designs role 1 and role 2, and binds role 1 and function foo1, as well as role2 and function foo2 and foo3.
Contract administrator designs role 1 and role 2, and binds role 1 and function foo1, as well as role2 and function foo2 and foo3.

```
String txhash = sdk.nativevm().auth().assignFuncsToRole(adminIdentity.ontid, password, adminIdentity.controls.get(0).getSalt(),
1, Helper.reverse(codeAddress), "role1", new String[]{"foo1"}, account, sdk.DEFAULT_GAS_LIMIT, 0);

String txhash = sdk.nativevm().auth().assignFuncsToRole(adminIdentity.ontid, password, adminIdentity.controls.get(0).getSalt(), 1,
Helper.reverse(codeAddress), "role2", new String[]{"foo2","foo3"}, account, sdk.DEFAULT_GAS_LIMIT, 0);
```

4.Contract administrator will allocate role 1 to OntID1 and role 2 to OntID2, then OntID1 has the authority to call function foo1 and OntID2 has the authority to call function foo2 and foo3.

```
String txhash = sdk.nativevm().auth().assignOntIdsToRole(adminIdentity.ontid, password, adminIdentity.controls.get(0).getSalt(), 1,
Helper.reverse(codeAddress), "role1", new String[]{identity1.ontid}, account, sdk.DEFAULT_GAS_LIMIT, 0);

String txhash = sdk.nativevm().auth().assignOntIdsToRole(adminIdentity.ontid, password, adminIdentity.controls.get(0).getSalt(), 1,
Helper.reverse(codeAddress), "role2", new String[]{identity2.ontid}, account, sdk.DEFAULT_GAS_LIMIT, 0);
```

5.As ONTID1s role is allocated by contract administrator, its authority level default is 2, which means ONTID1 can transfer its authority delegation to another ONTIDX, the delegation interface Java-SDK is delegate, more details can be referred from the following interface information. When delegating authority, it is required to have the appointed principals authority level and delegation time. If the level of the delegate is 2, then the principals level can only be 1.

```
sdk.nativevm().auth().delegate(identity1.ontid,password,identity1.controls.get(0).getSalt(),1,Helper.reverse(codeAddress),
identityX.ontid,"role1",60*5,1,account,sdk.DEFAULT_GAS_LIMIT,0);
```

6.Verify if an ONTID has the authority to call a certain function via VerifyToken interface.

```
String result = sdk.nativevm().auth().verifyToken(identityX.ontid, password, identityX.controls.get(0).getSalt(), 1, Helper.reverse(codeAddress), "foo1");
```
Returned Value: 01 means has authority, 00 means no authority.

7. If the principals authority time has not finished, the delegate can revoke the authority that is delegated to others.

```
sdk.nativevm().auth().withdraw(identity1.ontid,password,identity1.controls.get(0).getSalt(),1,Helper.reverse(codeAddress),identityX.ontid,"role1",account,sdk.DEFAULT_GAS_LIMIT,0);
```

8. Contract administrator can pass his or her administration authority to other ONTID.

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
            public byte[] calllerOntID; //ontId Callers ONTID
            public string funcName;     // Function Name
            public int keyNo;           //ontId Which number of public key of Callers ONTID is used?
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

### Interface List

`Java-SDK` has encapsulated the call interface for authority contract. The authority can be managed through `Java-SDK`.

1.String sendTransfer (String adminOntId, String password, byte[] salt, String contractAddr, String newAdminOntID, long keyNo, Account payerAcct, long gaslimit, long gasprice)

| Specification      |      |   Description   |
| :--------: | :--------:| :------: |
| Function specification	 |   Contract administrator transfer the contract administration  |  This function must be called by the contract administrator, where adminOntIDs number will be used as the key number for the public key to verify the validity of the transaction signature. |
| Parameter specification    |   Field      |           Description        |
|                            | adminOntId |  Contract administrator’s ONTID  |
|                            | password |  Contract administrator’s password  |
|                            | slat |  Private key decryption parameter  |
|                            | contractAddr |  Contract address  |
|                            | newAdminOntID |  New administrator  |
|                            | keyNo |  Contract administrator’s public key number  |
|                            | payerAcct  |  Payer account  |
|                            | gaslimit | Gas Limit   |
|                            | gasprice  |  Gas price  |
|Returned value specification|Transaction hash|    |

2. String assignFuncsToRole (String adminOntID,String password,byte[] salt,String contractAddr,String role,String[] funcName,long keyNo,Account payerAcct,long gaslimit,long gasprice).

| Specification      |      |   Description   |
| :--------: | :--------:| :------: |
| Function specification	 |  Allocate function for roles  | Must be called by contract administrator; automatically bind all functions to role; if already bound, then automatically skip, and return to true. |
| Parameter specification    |   Field      |           Description        |
|                            | adminOntId | Contract administrator’s ONTID  |
|                            | password | Contract administrator’s password  |
|                            | slat | Private key decryption parameter  |
|                            | contractAddr | Contract address  |
|                            | funcName  | Function name array  |
|                            | role | Role  |
|                            | keyNo | Contract administrator’s public key number  |
|                            | payerAcct | Payer account   |
|                            | gaslimit | Gas Limit   |
|                            | gasprice  | Gas price  |
|Returned value specification|Transaction hash|    |

3.	String assignOntIDsToRole (String adminOntId,String password,byte[] salt, String contractAddr,String role,String[] ontIDs,long keyNo,Account payerAcct,long gaslimit,long gasprice)

| Specification      |      |   Description   |
| :--------: | :--------:| :------: |
| Function specification	 |  Binding role to real-life identity  | Must be called by contract administrator, ONT ID in ONTIDs array will be allocated a role and returned to true in the end. In current realization, authority token level is defaulted at 2. |
| Parameter specification    |   Field         |           Description        |
|                            | adminOntId      | Contract administrator’s ONTID  |
|                            | password        | Contract administrator’s password  |
|                            | slat            | Private key decryption parameter  |
|                            | contractAddr    | Contract address  |
|                            | role            | Role  |
|                            | ontIDs          | ONTID array  |
|                            | keyNo           | Contract administrator’s public key number  |
|                            | payerAcct       | Payer account   |
|                            | gaslimit        | Gas Limit   |
|                            | gasprice        | Gas price  |
|Returned value specification|Transaction hash |    |

4.String delegate (String ontid,String password,byte[] salt,String contractAddr,String toOntId,String role,long period,long level,long keyNo,Account payerAcct,long gaslimit,long gasprice)

Role owner can assign a role to other people, from is the ONT ID for assigner, to is the ONT ID for the assignee/delegate, role is the assigned role, period parameter specifies the term time of delegation by second.

Delegate can assign its role to more people, level parameter specifies the depth of the delegate level, for instance,

> level = 1: Delegate cannot assign its role. The current realization only support this case.

| Specification      |      |   Description   |
| :--------: | :--------:| :------: |
| Function specification	 |  Pass contract call authority to others  |   |
| Parameter specification    |   Field         |           Description        |
|                            | ontid           | ONTID that has the call authority for a certain function  |
|                            | password        | Contract administrator’s password  |
|                            | slat            | Private key decryption parameter  |
|                            | contractAddr    | Contract address  |
|                            | toOntId         | ONTID that receives contract call authority  |
|                            | role            | Role  |
|                            | period          | Time counted by second  |
|                            | keyNo           | ONTID public key number  |
|                            | payerAcct       | Payer account   |
|                            | gaslimit        | Gas Limit   |
|                            | gasprice        | Gas price  |
|Returned value specification|Transaction hash |    |

5.	String withdraw (String initiatorOntid,String password,byte[] salt,String contractAddr,String delegate, String role,long keyNo,Account payerAcct,long gaslimit,long gasprice).

| Specification      |      |   Description   |
| :--------: | :--------:| :------: |
| Function specification	 |  Revoke contract call authority (cooperate with delegate’s use)  |   |
| Parameter specification    |   Field         |           Description        |
|                            | initiatorOntid  | Transfer contract call authority to others’ OntID  |
|                            | password        | OntID passwords  |
|                            | slat            | Private key decryption parameter  |
|                            | contractAddr    | Contract address  |
|                            | delegate        | Delegate’s OntID  |
|                            | role            | Role  |
|                            | period          | Time counted by second  |
|                            | keyNo           | ONTID public key number  |
|                            | payerAcct       | Payer account   |
|                            | gaslimit        | Gas Limit   |
|                            | gasprice        | Gas price  |
|Returned value specification|Transaction hash |    |

6.	String verifyToken (String ontid,String password,byte[] salt,String contractAddr,String funcName,long keyNo).

| Specification      |      |   Description   |
| :--------: | :--------:| :------: |
| Function specification	 |  Revoke contract call authority (cooperate with delegate’s use)  |   |
| Parameter specification    |   Field         |           Description        |
|                            | initiatorOntid  | Transfer contract call authority to others’ OntID  |
|                            | ontid           | Verified OntID  |
|                            | password        | OntID passwords  |
|                            | slat            | Private key decryption parameter  |
|                            | contractAddr    | Contract address  |
|                            | funcName        | Function name  |
|                            | keyNo           | ONTID public key number  |
|Returned value specification|Transaction hash |    |
