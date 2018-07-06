---
title: 
keywords: sample homepage
sidebar: ont_doc_zh
permalink: smart_contract_tutorial_auth_zh.html
folder: doc_zh
---


[English](./smart_contract_tutorial_auth_en.html) / 中文

<h1 align="center"> Ontology Java SDK User Guide </h1>
<p align="center" class="version">Version 1.0.0 </p>

# 权限管理

当前，智能合约的函数可以被任何人调用，这显然不符合现实要求。基于角色的权限管理的基本思想是，每个角色可以调用部分函数，每个实体可以被赋予多种角色（实体是由其ONT ID来标识）。

如果智能合约需要增加权限管理功能，那就必须记录合约中分配的角色，以及角色可调用的函数，哪些实体具有该角色等等信息。这个工作比较繁琐，可交由一个系统合约来管理。

具体请参考https://github.com/ontio/ontology-smartcontract/blob/master/smartcontract/native/auth/auth.md


* 权限合约管理

* 用法示例

* 接口列表


### 权限合约管理

Auth合约负责管理应用合约的函数调用权限，功能有合约管理员可以转让合约管理权限，合约管理员为角色分配函数，合约管理员绑定角色到实体身份，有合约函数调用权的实体将合约调用权代理给其他人，合约管理员收回合约调用权，实体验证合约调用token的有效性。

Auth合约实现了一套基于角色的权限管理方案，每个角色对应一些可调用的函数，管理员通过将角色分配给ONT ID，使之可以调用该角色下的函数。与此同时，角色是可以传递的，即A可以将某个角色代理给B，并指定代理时间，这样的话B就可以一段时间内也可以调用对应的函数。

### 用法示例

Ontology智能合约不支持在部署的时候执行初始化，所以合约管理员需要硬编码在合约代码中，即将合约管理员ONT ID在合约中定义成一个常量，具体请看下面的合约样例。Ontology智能合约可以调用verifyToken函数进行权限验证，同时为了方便开发者验证某个OntID是否有某个角色，Java-SDK也提供了verifyToken接口，可以实时查询角色的分配情况。

使用流程：

```
1. 将智能合约部署到链上。
2. 调用智能合约中的init方法，在合约代码中通过调用initContractAdmin方法，将合约中预先定义的管理员ONT ID，设置为该合约的管理员（注意:需先将管理员ONT ID注册到链上）。
3. 合约管理员设计需要用到的角色，并将角色和智能合约中的函数进行绑定，该步骤可以调用Java-SDK中的assignFuncsToRole接口进行设置。
4. 合约管理员将角色分配给ONT ID，拥有该角色的ONT ID将有权限调用该角色对应的函数，该步骤可以调用Java-SDK中的assignOntIDsToRole接口进行设置。
5. 拥有某个角色的ONT ID在调用该角色对应的函数之前，可以通过Java-SDK中的verifyToken接口验证该ontid是否有调用相应函数的权利。
```

结合下面的示例讲解使用流程：

1. 将智能合约部署到链上。
2. 调用该合约中init方法。

```
AbiInfo abiInfo = JSON.parseObject(abi,AbiInfo.class);
String name = "init";
AbiFunction function = abiInfo.getFunction(name);
function.setParamsValue();
String txhash = (String) sdk.neovm().sendTransaction(Helper.reverse(codeAddress),account,account,sdk.DEFAULT_GAS_LIMIT,0,function,false);
```

3. 合约管理员设计角色role1和role2，并将角色role1和函数foo1绑定，将角色role2和函数foo2、foo3绑定。

```
String txhash = sdk.nativevm().auth().assignFuncsToRole(adminIdentity.ontid, password, adminIdentity.controls.get(0).getSalt(),
1, Helper.reverse(codeAddress), "role1", new String[]{"foo1"}, account, sdk.DEFAULT_GAS_LIMIT, 0);

String txhash = sdk.nativevm().auth().assignFuncsToRole(adminIdentity.ontid, password, adminIdentity.controls.get(0).getSalt(), 1,
Helper.reverse(codeAddress), "role2", new String[]{"foo2","foo3"}, account, sdk.DEFAULT_GAS_LIMIT, 0);

```

4. 合约管理员将角色"role1"分配给ontId1,将角色"role2"分配给ontId2，则ontId1拥有调用函数foo1的权限，ontId2拥有调用函数foo2和函数foo3的权限。

```
String txhash = sdk.nativevm().auth().assignOntIdsToRole(adminIdentity.ontid, password, adminIdentity.controls.get(0).getSalt(), 1,
Helper.reverse(codeAddress), "role1", new String[]{identity1.ontid}, account, sdk.DEFAULT_GAS_LIMIT, 0);

String txhash = sdk.nativevm().auth().assignOntIdsToRole(adminIdentity.ontid, password, adminIdentity.controls.get(0).getSalt(), 1,
Helper.reverse(codeAddress), "role2", new String[]{identity2.ontid}, account, sdk.DEFAULT_GAS_LIMIT, 0);


```

5. 由于ontId1的角色是合约管理员分配的，其权限level默认是2，即ontId1可以将权限代理给其他ontidX，代理的Java-SDK接口是delegate,具体接口信息请参考下面的接口信息。
在代理权限的时候需要指定被代理人权限的级别以及代理时间，如果代理人的level是2，则被代理人的level只能是1。

```
sdk.nativevm().auth().delegate(identity1.ontid,password,identity1.controls.get(0).getSalt(),1,Helper.reverse(codeAddress),
identityX.ontid,"role1",60*5,1,account,sdk.DEFAULT_GAS_LIMIT,0);
```

6. 验证某个ontId是否有调用某个函数的权限，可以通过verifyToken接口查询。

```
String result = sdk.nativevm().auth().verifyToken(identityX.ontid, password, identityX.controls.get(0).getSalt(), 1, Helper.reverse(codeAddress), "foo1");

返回值: "01"表示有权限，"00"表示没有权限。
```

7. 如果被代理人的权限时间没有结束，代理人可以提前收回代理给别人的权限。

```
sdk.nativevm().auth().withdraw(identity1.ontid,password,identity1.controls.get(0).getSalt(),1,Helper.reverse(codeAddress),identityX.ontid,"role1",account,sdk.DEFAULT_GAS_LIMIT,0);
```

8. 合约管理员可以将自己的管理权限转移给其他的ontId

```
String txhash = sdk.nativevm().auth().sendTransfer(adminIdentity.ontid,password,adminIdentity.controls.get(0).getSalt(),1,Helper.reverse(codeAddress),adminIdentity.ontid,
account,sdk.DEFAULT_GAS_LIMIT,0);
```



Ontology合约示例：
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
            public byte[] contractAddr; //合约地址
            public byte[] calllerOntID; //调用者ontId
            public string funcName;     //调用的函数名
            public int keyNo;           //使用调用者ontId的第几把公钥
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


### 接口列表

Java-SDK已经封装好权限合约的调用接口，可以通过Java-SDK进行权限管理。

1. String sendTransfer(String adminOntId, String password, byte[] salt, String contractAddr, String newAdminOntID, long keyNo, Account payerAcct, long gaslimit, long gasprice)

    |说明||描述|
    |:--|:--|:--|
    |功能说明|合约管理员转让合约管理权限|此函数必须由合约管理员调用，即将会以adminOntID名下编号为keyNo的公钥来验证交易签名是否合法。|
    |参数说明|字段|描述|
    ||adminOntId|合约管理员ontid|
    ||password|合约管理员密码|
    ||slat |私钥解密参数|
    ||contractAddr|合约地址|
    ||newAdminOntID|新的管理员|
    ||keyNo|合约管理员的公钥编号|
    ||payerAcct|付费账户|
    ||gaslimit|gas价格|
    ||gasprice|gas价格|
    |返回值说明|交易hash||

2. String assignFuncsToRole(String adminOntID,String password,byte[] salt,String contractAddr,String role,String[] funcName,long keyNo,Account payerAcct,long gaslimit,long gasprice)

    |说明||描述|
    |:--|:--|:--|
    |功能说明|为角色分配函数|必须由合约管理者调用，将所有函数自动绑定到role，若已经绑定，自动跳过，最后返回true。|
    |参数说明|字段|描述|
    ||adminOntId|合约管理员ontid|
    ||password|合约管理员密码|
    ||salt|私钥解密参数|
    ||contractAddr|合约地址|
    ||role|角色|
    ||funcName|函数名数组|
    ||keyNo|合约管理员的公钥编号|
    ||payerAcct|付费账户|
    ||gaslimit|gas价格|
    ||gasprice|gas价格|
    |返回值说明|交易hash||

3. String assignOntIDsToRole(String adminOntId,String password,byte[] salt, String contractAddr,String role,String[] ontIDs,long keyNo,Account payerAcct,long gaslimit,long gasprice)

     |说明||描述|
     |:--|:--|:--|
     |功能说明|绑定角色到实体身份|必须由合约管理者调用，ontIDs数组中的ONT ID被分配role角色，最后返回true。 在当前实现中，权限token的级别level默认等于2。|
     |参数说明|字段|描述|
     ||adminOntId|合约管理员ontid|
     ||password|合约管理员密码|
     ||salt|私钥解密参数|
     ||contractAddr|合约地址|
     ||role|角色|
     ||ontIDs|ontid数组|
     ||keyNo|合约管理员的公钥编号|
     ||payerAcct|付费账户|
     ||gaslimit|gas上限|
     ||gasprice|gas价格|
     |返回值说明|交易hash||

4. String delegate(String ontid,String password,byte[] salt,String contractAddr,String toOntId,String role,long period,long level,long keyNo,Account payerAcct,long gaslimit,long gasprice)

     角色拥有者可以将角色代理给其他人，from是转让者的ONT ID，to是代理人的ONT ID，role表示要代理的角色，period参数指定委托任期时间（以second为单位）。

     代理人可以再次将其角色代理给更多的人，level参数指定委托层次深度。例如，

         level = 1: 此时代理人就无法将其角色再次代理出去；当前实现只支持此情况。

     |说明||描述|
     |:--|:--|:--|
     |功能说明|将合约调用权代理给其他人||
     |参数说明|字段|描述|
     ||ontid|拥有合约中某个函数调用权的ontid|
     ||password|ontid密码|
     ||salt|私钥解密参数|
     ||contractAddr|合约地址|
     ||toOntId|接收合约调用权的ontid|
     ||role|角色|
     ||period|以秒为单位的时间|
     ||keyNo|ontid的公钥编号|
     ||payerAcct|付费账户|
     ||gaslimit|gas价格|
     ||gasprice|gas价格|
     |返回值说明|交易hash||

5. String withdraw(String initiatorOntid,String password,byte[] salt,String contractAddr,String delegate, String role,long keyNo,Account payerAcct,long gaslimit,long gasprice)

     角色拥有者可以提前将角色代理提前撤回，initiatorOntid是发起者，delegate是角色代理人，initiator将代理给delegate的角色提前撤回。

     |说明||描述|
     |:--|:--|:--|
     |功能说明|收回合约调用权（配合delegate使用）||
     |参数说明|字段|描述|
     ||initiatorOntid|将合约调用权转让给其他人的ontid|
     ||password|ontid密码|
     ||salt|私钥解密参数|
     ||contractAddr|合约地址|
     ||delegate|代理人ontid|
     ||role|角色|
     ||keyNo|ontid的公钥编号|
     ||payerAcct|付费账户|
     ||gaslimit|gas价格|
     ||gasprice|gas价格|
     |返回值说明|交易hash||

6. String verifyToken(String ontid,String password,byte[] salt,String contractAddr,String funcName,long keyNo)

      |说明||描述|
      |:--|:--|:--|
      |功能说明|验证合约调用token的有效性||
      |参数说明|字段|描述|
      ||ontid|验证的ontid|
      ||password|ontid密码|
      ||salt|私钥解密参数|
      ||contractAddr|合约地址|
      ||funcName|函数名|
      ||keyNo|ontid的公钥编号|
      |返回值说明|交易hash||
