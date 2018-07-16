---
sidebar: SDKs_en
permalink: ontology_java_sdk_identity_claim_en.html
folder: doc_en/SDKs
---

English / [中文](./ontology_java_sdk_identity_claim_zh.html)

<h1 align="center"> Digital Identity </h1>
<p align="center" class="version">Version 0.9.0 </p>

# Overivew

Relevant descriptions of digital ID can be found in [ONT ID Protocol and Trust Framework](https://github.com/ontio/ontology-DID).

## Wallet file specification

A wallet file is a JSON data storage file that stores multiple digital identities and digital asset accounts.
You may refer to [Wallet File Specification](Wallet_File_Specification.md) for detailed information.

You need to create/open a wallet file to create a digital identity.


```
//If the wallet file does not exist, a wallet file will be auto-generated.
wm.openWalletFile("Demo3.json");
```

> Note: Only wallet file in the operating file format is currently supported, with extended support of database or other storage methods.



## Digital ID account management

* 1 Data structure

`ontid` A user’s only identity  
`label` The name of a user ID  
`lock` Indicates whether the user’s ID is locked, whose default value is false. Locked id info cannot get updated in the client  
`controls` The array of identity ControlData  
`extra` The field that client developer stores extra information, whose value may be null

```
//Identity data structure
public class Identity {
	public String label = "";
	public String ontid = "";
	public boolean isDefault = false;
	public boolean lock = false;
	public List<Control> controls = new ArrayList<Control>();
}
```


`algorithm` Encryption algorithm  
`parameters` The parameters used in the encryption algorithm  
`curve` Elliptic curve  
`id` The single identifier of control  
`key` NEP-2 private key


```
public class Control {
    public String algorithm = "ECDSA";
    public Map parameters = new HashMap() ;
    public String id = "";
    public String key = "";
}
```


* 2 Create a digital identity

Digital identity creation refers to generation of a digital identity with identity data structure and writing it to wallet file.

```
Identity identity = ontSdk.getWalletMgr().createIdentity("password");
//The account or identity created is stored in the memory only and a write api is required to write it to the wallet file.
ontSdk.getWalletMgr().writeWallet();
```


- 3 Register blockchain-based identity

Only after successfully registering an identity with the block chain can the identity be truly used.

There are two ways to register your identity with the chain

method one

Registrant specifies the account address for payment of transaction fees

```
Identity identity = ontSdk.getWalletMgr().createIdentity(password);
ontSdk.nativevm().ontId().sendRegister(identity,password,payer,payerpwd,gaslimit,gasprice);
```

method two

Send the constructed transaction to the server and let the server sign the transaction fee account.

```
Identity identity = ontSdk.getWalletMgr().createIdentity(password);
Transaction tx = ontSdk.nativevm().ontId().makeRegister(identity.ontid,password,payerAcc.address,ontSdk.DEFAULT_GAS_LIMIT,0);
ontSdk.signTx(tx,identity.ontid,password);
ontSdk.getConnect().sendRawTransaction(tx);
```

Upon successful registration, the corresponding DDO of the ONT ID will be stored in Ontology blockchain. Detailed information about DDO can be found in [ONT ID identity protocol and smart contract implementation](https://git.ont.network/Ontology_Open_Platform/ontid/src/master/docs/en/ONTID_protocol_spec.md).


* 4 Import account or identity

Users who have already created a digital identity or account may import it into a wallet file from SDK.

> **Note:** It is advised to check if an identity already exists on the blockchain before you import one. If DDO does not exist, it means that no such identity has been registered on the blockchain. Then you may need to use ontSdk.getOntIdTx().sendRegister(identity,"passwordtest") for registration.

```
Identity identity = ontSdk.getWalletMgr().importIdentity(encriptPrivateKey,password);
//write to wallet     
ontSdk.getWalletMgr().writeWallet();
```

Parameter Description：
encriptPrivateKey: Encrypted private key
password： Password used to encrypt the private key

* 5 Query blockchain-based identity

DDO of blockchain-based identity can be queried by entering ONT ID.


```
//get DDO by entering ONT ID
String ddo = ontSdk.nativevm().ontId().sendGetDDO(ontid);

//return in DDO format
{
	"Attributes": [{
		"Type": "String",
		"Value": "value1",
		"Key": "key1"
	}],
	"OntId": "did:ont:TA5UqF8iPqecMdBzTdzzANVeY8HW1krrgy",
	"Recovery": "TA6AhqudP1dcLknEXmFinHPugDdudDnMJZ",
	"Owners": [{
		"Type": "ECDSA",
		"Curve": "P256",
		"Value": "12020346f8c238c9e4deaf6110e8f5967cf973f53b778ed183f4a6e7571acd51ddf80e",
		"PubKeyId": "did:ont:TA5UqF8iPqecMdBzTdzzANVeY8HW1krrgy#keys-1"
	}, {
		"Type": "ECDSA",
		"Curve": "P256",
		"Value": "1202022fabd733d7d7d7009125bfde3cb0afe274769c78fd653079ecd5954ae9f52644",
		"PubKeyId": "did:ont:TA5UqF8iPqecMdBzTdzzANVeY8HW1krrgy#keys-2"
	}]
}
```

* 6 Remove identity


```
ontSdk.getWalletMgr().getWallet().removeIdentity(ontid);
//wrote to wallet
ontSdk.getWalletMgr().writeWallet();
```


* 7 Set default account or identity


```
ontSdk.getWalletMgr().getWallet().setDefaultIdentity(index);
ontSdk.getWalletMgr().getWallet().setDefaultIdentity(ontid);
```

* 8 Update blockchain-based DDO attribute

method one

specifies the account address for payment of transaction fees

```
//update an attribute
String sendAddAttributes(String ontid, String password, Attribute[] attributes,Account payerAcct,long gaslimit,long gasprice)
```


| Param   | Field   | Type  | Descriptions |      Remarks |
| ----- | ------- | ------ | ------------- | ----------- |
| input param | password| String | publisher's address | required, password to decrypt private key|
|   | ontid    | String | name of asset | required, ID |
|        | attributes | Attribute[]|  Attribute array | required |
|        | payerAcct    | Account | Payment transaction account    |  required |
|           | gaslimit      | long | gaslimit     | required |
|           | gasprice      | long | gas price    | required |
| output param | txhash   | String  | transaction hash | 64-bit string |


method two

Send the constructed transaction to the server and let the server sign the transaction fee account.
```
Transaction makeAddAttributes(String ontid, String password, Attribute[] attributes,String payer,long gaslimit,long gasprice)
```

example:
```
Transaction tx = ontSdk.nativevm().ontId().makeAddAttributes(ontid,password,attributes,payer,gaslimit,0);
ontSdk.signTx(tx,identity.ontid.replace(Common.didont,""),password);
ontSdk.getConnectMgr().sendRawTransaction(tx);
```

* 9 Remove blockchain-based DDO attribute

method one

```
String sendRemoveAttribute(String ontid,String password,String path,Account payerAcct,long gaslimit,long gasprice)
```

| Param        | Field   | Type   | Descriptions  |       Remarks       |
| -----        | ------- | ------ | ------------- | ------------------- |
| input param  | password| String | publisher's address | required, password to decrypt private key |
|   | ontid    | String | name of asset | required, ID |
|   | path    | String | path       | required |
|   | payerAcct    | Account  |Payment transaction account  | required，payer |
|   | gaslimit      | long | gaslimit     | required |
|   | gasprice      | long | gas price    | required |
| output param | txhash   | String  | transaction hash | 64-bit string |

method two

Send the constructed transaction to the server and let the server sign the transaction fee account.
```
Transaction makeRemoveAttribute(String ontid,String password,String path,String payer,long gaslimit,long gasprice)
```


example:
```
Transaction tx = ontSdk.nativevm().ontId().makeRemoveAttribute(ontid,password,path,payer,gaslimit,0);
ontSdk.signTx(tx,identity.ontid,password);
ontSdk.getConnectMgr().sendRawTransaction(tx);
```


* add publicKey

method one

```
String sendAddPubKey(String ontid, String password, String newpubkey,Account payerAcct,long gaslimit,long gasprice)
```

| Param      | Field   | Type  | Descriptions |             Remarks |
| ----- | ------- | ------ | ------------- | ----------- |
| input param| password| String | identity password | required |
|        | ontid    | String | identity ID   | required，identity Id |
|        | newpubkey| String  |public key       | required， newpubkey|
|        | payerAcct    | Account  | payerAcct       | required，payer |
|        | gaslimit      | long | gaslimit     | required |
|        | gasprice      | long | gas price    | required |
| output param | txhash   | String  | transaction hash  | transaction hash |


method two

Send the constructed transaction to the server and let the server sign the transaction fee account.
```
Transaction makeAddPubKey(String ontid,String password,String newpubkey,String payer,long gaslimit,long gasprice)
```

example
```
Transaction tx = ontSdk.nativevm().ontId().makeAddPubKey(ontid,password,newpubkey,payer,gas);
ontSdk.signTx(tx,identity.ontid.replace(Common.didont,""),password);
ontSdk.getConnectMgr().sendRawTransaction(tx);
```

method three(recovery)

```
String sendAddPubKey(String ontid,String recoveryAddr, String password, String newpubkey,Account payerAcct,long gaslimit,long gasprice)
```


| Param      | Field   | Type  | Descriptions |             Remarks |
| ----- | ------- | ------ | ------------- | ----------- |
| input param|ontid|String | identity ID   | required，identity Id |
|        | recoveryAddr| String | recovery address | required |
|        | password| String | recovery password | required |
|        | newpubkey| String  |public key       | required， newpubkey|
|        | payerAcct | Account  | payer       | required，payer |
|        | gaslimit      | long | gaslimit     | required |
|        | gasprice      | long | gas price    | required |
| output param | txhash   | String  | transaction hash  | transaction hash |


method four(recovery)
```
Transaction makeAddPubKey(String ontid,String recoveryAddr,String password,String newpubkey,String payer,long gaslimit,long gasprice)
```

parameter description,please refer to method three(recovery)


* remove publicKey

method one

```
String sendRemovePubKey(String ontid, String password, String removePubkey,Account payerAcct,long gaslimit,long gasprice)
```


| Param      | Field   | Type  | Descriptions |             Remarks |
| ----- | ------- | ------ | ------------- | ----------- |
| input param | password| String | identity password | required |
|        | ontid    | String | identity ID   | required，identity Id |
|        | removePubkey| String  |public key       | required， removePubkey|
|        | payerAcct    | Account  | payerAcct       | required，payer |
|   | gaslimit      | long | gaslimit     | required |
|   | gasprice      | long | gas price    | required |
| output param | txhash   | String  | transaction hash  | Transaction hash |


method two

Send the constructed transaction to the server and let the server sign the transaction fee account.

```
Transaction tx = ontSdk.nativevm().ontId().makeRemovePubKey(ontid,password,removePubkey,payer,gas);
ontSdk.signTx(tx,identity.ontid,password);
ontSdk.getConnectMgr().sendRawTransaction(tx);
```

method three(recovery)
```
String sendRemovePubKey(String ontid, String recoveryAddr,String password, String removePubkey,Account payerAcct,long gaslimit,long gasprice)
```

| Param      | Field   | Type  | Descriptions |             Remarks |
| ----- | ------- | ------ | ------------- | ----------- |
| input param | ontid    | String | identity ID   | required，identity Id |
|        | password| String | identity password | required |
|        | recoveryAddr| String | recovery password | required |
|        | removePubkey| String  |public key       | required， removePubkey|
|        | payerAcct    | Account  | payer       | required，payer |
|   | gaslimit      | long | gaslimit     | required |
|   | gasprice      | long | gas price    | required |
| output param | txhash   | String  | transaction hash  | Transaction hash |


method four(recovery)
```
Transaction makeRemovePubKey(String ontid,String recoveryAddr, String password, String removePubkey,String payer,long gaslimit,long gasprice)
```

parameter description,please refer to method four(recovery)

* add recovery

method one

```
String sendAddRecovery(String ontid, String password, String recoveryAddr,Account payerAcct,long gaslimit,long gasprice)
```

| Param      | Field   | Type  | Descriptions |             Remarks |
| ----- | ------- | ------ | ------------- | ----------- |
| input param | password| String | identity password | required |
|        | ontid    | String | identity ID   | required，identity Id |
|        | recovery| String  |recovery address | required，recovery|
|        | payerAcct    | Account  | payer       | required，payer |
|   | gaslimit      | long | gaslimit     | required |
|   | gasprice      | long | gas price    | required |
| output param | txhash   | String  | transaction hash  | Transaction hash |


method two

Send the constructed transaction to the server and let the server sign the transaction fee account.

```
Transaction makeAddRecovery(String ontid, String password, String recoveryAddr,String payer,long gaslimit,long gasprice)
```

example:
```
Transaction tx = ontSdk.nativevm().ontId().makeAddRecovery(ontid,password,recovery,payer,gas);
ontSdk.signTx(tx,identity.ontid,password);
ontSdk.getConnectMgr().sendRawTransaction(tx);
```

* 修改recovery


```
String sendChangeRecovery(String ontid, String newRecovery, String oldRecovery, String password,long gaslimit,long gasprice)
```

| Param      | Field   | Type  | Descriptions |             Remarks |
| ----- | ------- | ------ | ------------- | ----------- |
| input param | ontid    | String | identity ID   | required，identity Id |
|        | newRecovery| String  |newRecovery address | required，newRecovery|
|        | oldRecovery| String  |oldRecovery address | required，oldRecovery|
|        |  password | String  | oldRecovery password  | required |
|   | gaslimit      | long | gaslimit     | required |
|   | gasprice      | long | gas price    | required |
| output param | txhash   | String  | transaction hash  | transaction hash |



## Verifiable claim

### 1 Data structure specification

* Claim has the following data structure:

```
class Claim{
  header : Header
  payload : Payload
  signature : byte[]
}
```


```
class Header {
    public String Alg = "ONT-ES256";
    public String Typ = "JWT-X";
    public String Kid;
    }
```

`alg` attribute specifies the signature scheme to use. A list of supported values can be found here.
`typ` attribute can take one of the two values

    * JWT: This corresponds to the case that blockchain proof is not contained in the claim.
    * JWT-X: This corresponds to the case that blockchain proof is a part of the claim.

`kid`  attribute refers to the public key used for signature verification. It has the form <ontID>#keys-<id> as defined in ONT ID specification.


```
class Payload {
    public String Ver;
    public String Iss;
    public String Sub;
    public long Iat;
    public long Exp;
    public String Jti;
    @JSONField(name = "@context")
    public String Context;
    public Map<String, Object> ClmMap = new HashMap<String, Object>();
    public Map<String, Object> ClmRevMap = new HashMap<String, Object>();
    }
```

`ver` attribute specifies the version of the claim spec it follows.
`iss` attribute refers to the ONT ID of the issuer.
`sub` attribute refers to the ONT ID of the recipient.
`iat` attribute marks the time the claim was created and has the format of unix timestamp.
`exp` attribute marks the expiration time of the claim and has the format of unix timestamp.
`jti` attribute specifies the unique identifier of the verifiable claim.
`@context` attribute specifies the uri of claim content definition document which defines the meaning of each field and the type of the value;
`clm` attribute is an object which contains the claim content.
`clm-rev` attribute is an object which defines the revocation mechanism the claim use.



### 2 interface list

1. createOntIdClaim(String signerOntid, String password, String context, Map<String, Object> claimMap, Map metaData,Map clmRevMap,long expire)

     function description： create claim

    | Parameter      | Field   | Type  | Descriptions |            Remarks |
    | ----- | ------- | ------ | ------------- | ----------- |
    | input parameter | signerOntid| String | ontid | required |
    |        | password    | String | ontid password   | required |
    |        | context| String  |attribute specifies the uri of claim content definition document which defines the meaning of each field and the type of the value | required|
    |        | claimMap| Map  |content of claim | required|
    |        | metaData   | Map | claim issuer and subject's ontid | required |
    |        | clmRevMap   | Map | attribute is an object which defines the revocation mechanism the claim use | required |
    |        | expire   | long | attribute marks the expiration time of the claim and has the format of unix timestamp     | required |
    | output parameter| claim   | String  |   |  |

    refer to https://github.com/kunxian-xia/ontology-DID/blob/master/docs/en/claim_spec.md

2. boolean verifyOntIdClaim(String claim)

    function description： verify claim

    | Parameter      | Field   | Type  | Descriptions |            Remarks |
    | ----- | ------- | ------ | ------------- | ----------- |
    | input parameter | claim| String | trusted claim | required |
    | output parameter | true or false   | boolean  |   |  |


### 3 Sign and issue verifiable claim
Verifiable claim is constructed based on user input, which contains signed data.

```
Map<String, Object> map = new HashMap<String, Object>();
map.put("Issuer", dids.get(0).ontid);
map.put("Subject", dids.get(1).ontid);
Map clmRevMap = new HashMap();
clmRevMap.put("typ","AttestContract");
clmRevMap.put("addr",dids.get(1).ontid.replace(Common.didont,""));
String claim = ontSdk.nativevm().ontId().createOntIdClaim(dids.get(0).ontid,password, "claim:context", map, map,clmRevMap,System.currentTimeMillis()/1000 +100000);
```
> Note: The Issuer may have multiple public keys. The parameter ontid of createOntIdClaim specifies which public key to use.

### 3 Verify verifiable claim

```
boolean b = ontSdk.nativevm().ontId().verifyOntIdClaim(claim);
```


### 4 Use cases


```
Identity identity = ontSdk.getWalletMgr().createIdentity(password);
ontSdk.nativevm().ontId().sendRegister(identity2,password,payerAcc.address,password,ontSdk.DEFAULT_GAS_LIMIT,0);
String ontid = ident.ontid;
Map recordMap = new HashMap();
recordMap.put("key0", "world0");
recordMap.put("keyNum", 1234589);
recordMap.put("key2", false);
String hash = ontSdk.nativevm().ontId().sendAddAttributes(dids.get(0).ontid,password,attributes,payerAcc.address,password,ontSdk.DEFAULT_GAS_LIMIT,0);
```
> Note: When the attribute does not exist, calling the sendUpdateAttribute method will increase the corresponding attribute. When the attribute exists, the corresponding attribute will be updated. Attri represents the attribute name, "Json" is the attribute value data type, and recordMap represents the attribute value.

Claim issuance and verification:

```
Map<String, Object> map = new HashMap<String, Object>();
map.put("Issuer", dids.get(0).ontid);
map.put("Subject", dids.get(1).ontid);

Map clmRevMap = new HashMap();
clmRevMap.put("typ","AttestContract");
clmRevMap.put("addr",dids.get(1).ontid.replace(Common.didont,""));

String claim = ontSdk.nativevm().ontId().createOntIdClaim(dids.get(0).ontid,password, "claim:context", map, map,clmRevMap,System.currentTimeMillis()/1000 +100000);
boolean b = ontSdk.nativevm().ontId().verifyOntIdClaim(claim);
```