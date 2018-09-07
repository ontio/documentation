---
title:
keywords: sample homepage
sidebar: SDKs_en
permalink: ontology_java_sdk_identity_claim_en.html
folder: doc_en/SDKs
giturl: https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/identity_claim.md
---

<h1 align="center"> Digital Identity</h1>

<p align="center" class="version">Version 1.0.0 </p>

English / [中文](./ontology_java_sdk_identity_claim_zh.html)

## Introduction

Relevant descriptions of digital ID can be found in [ONT ID Protocol and Trust Framework](https://github.com/ontio/ontology-DID).

## Wallet file specification

A wallet file is a JSON data storage file that stores multiple digital identities and digital asset accounts.
You may refer to [Wallet File Specification](./Wallet_File_Specification_en.html) for detailed information.

You need to create/open a wallet file to create a digital identity.


```
//If the wallet file does not exist, a wallet file will be auto-generated.
wm.openWalletFile("Demo3.json");
```

Note: Only a wallet file in the operating file format is currently supported, with extended support of database or other storage methods.



## Digital ID management

**Data structure**

`ontid` A user’s identity.
`label` The name of a user ID.
`lock` Indicates whether the user’s ID is locked, whose default value is false. Locked ID info cannot get updated in the client.  
`controls` The array of identity ControlData.
`extra` The field that client developer stores extra information, whose value may be null.

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


`algorithm` Encryption algorithm.
`parameters` The parameters used in the encryption algorithm.
`curve` Elliptic curve.
`id` The single identifier of control.
`key` NEP-2 private key.
`salt` Salt.
`hash` Hash algorithm.


```
public class Control {
    public String algorithm = "ECDSA";
    public Map parameters = new HashMap() ;
    public String id = "";
    public String key = "";
    public String salt = "";
    public String hash = "sha256";
    @JSONField(name = "enc-alg")
    public String encAlg = "aes-256-gcm";
    public String address = "";
}
```


### 1. Register a digital identity

Digital identity creation refers to generation of a digital identity with identity data structure and writing it to a wallet file.

```
Identity identity = ontSdk.getWalletMgr().createIdentity("password");
//The account or identity created is stored in the memory only and a write api is required to write it to the wallet file.
ontSdk.getWalletMgr().writeWallet();
```


**Register blockchain-based identity**

Only after successfully registering an identity with the blockchain can the identity be truly used.

There are two ways to register your identity with the chain:

* Registrant specifies the account address for payment of transaction fees.

```
Identity identity = ontSdk.getWalletMgr().createIdentity(password);
ontSdk.nativevm().ontId().sendRegister(identity,password,payer,payerpwd,gaslimit,gasprice);
```

* Send the constructed transaction to the server and let the server sign the transaction fee account.

```
Identity identity = ontSdk.getWalletMgr().createIdentity(password);
Transaction tx = ontSdk.nativevm().ontId().makeRegister(identity.ontid,password,salt,payerAcc.address,ontSdk.DEFAULT_GAS_LIMIT,0);
ontSdk.signTx(tx,identity.ontid,password,salt);
ontSdk.getConnect().sendRawTransaction(tx);
```

Upon successful registration, the corresponding DDO of the ONT ID will be stored in Ontology blockchain. Detailed information about DDO can be found in [ONT ID identity protocol and smart contract implementation]
https://github.com/ontio/ontology-DID/blob/master/README.md

### 2. Identity management

* Import account or identity

Users who have already created a digital identity or account may import it into a wallet file from the SDK.

**Note:** It is advised to check if an identity already exists on the blockchain before you import one. If DDO does not exist, it means that no such identity has been registered on the blockchain. Then you may need to use ontSdk.getOntIdTx().sendRegister(identity,"passwordtest") for registration.

```
Identity identity = ontSdk.getWalletMgr().importIdentity(encriptPrivateKey,password,salt,address);
//write to wallet     
ontSdk.getWalletMgr().writeWallet();
```

Parameter Descriptions:

encriptPrivateKey: Encrypted private key.
password: Password used to encrypt the private key.
salt: Private key decryption parameters.
address: Account address.

* Remove identity


```
ontSdk.getWalletMgr().getWallet().removeIdentity(ontid);
//wrote to wallet
ontSdk.getWalletMgr().writeWallet();
```


* Set default account or identity


```
ontSdk.getWalletMgr().getWallet().setDefaultIdentity(index);
ontSdk.getWalletMgr().getWallet().setDefaultIdentity(ontid);
```

### 3. Query blockchain-based identity

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


### 4. Ontid attribute

**Update blockchain-based DDO attribute**

* Specifies the account address for payment of transaction fees.

```
//update an attribute
String sendAddAttributes(String ontid, String password,byte[] salt, Attribute[] attributes,Account payerAcct,long gaslimit,long gasprice)
```


| Param   | Field   | Type  | Description |      Remarks |
| ----- | ------- | ------ | ------------- | ----------- |
| Input param | password| String | Publisher's address | Required, password to decrypt private key|
|   | ontid    | String | Name of asset | Required, ID |
|   | salt     | byte[] | |Required|
|        | attributes | Attribute[]|  Attribute array | Required |
|        | payerAcct    | Account | Payment transaction account    |  Required |
|           | gaslimit      | long | Gas limit     | Required |
|           | gasprice      | long | Gas price    | Required |
| Output param | txhash   | String  | Transaction hash | 64-bit string |


* Send the constructed transaction to the server and let the server sign the transaction fee account.

```
Transaction makeAddAttributes(String ontid, String password,byte[] salt, Attribute[] attributes,String payer,long gaslimit,long gasprice)
```

Example:
```
Transaction tx = ontSdk.nativevm().ontId().makeAddAttributes(ontid,password,salt,attributes,payer,gaslimit,0);
ontSdk.signTx(tx,identity.ontid.replace(Common.didont,""),password);
ontSdk.getConnectMgr().sendRawTransaction(tx);
```

**Remove blockchain-based DDO attribute**

* remove attribute

```
String sendRemoveAttribute(String ontid,String password,salt,String path,Account payerAcct,long gaslimit,long gasprice)
```

| Param        | Field   | Type   | Description  |       Remarks       |
| -----        | ------- | ------ | ------------- | ------------------- |
| Input param  | password| String | Publisher's address | Required, password to decrypt private key |
|   | ontid    | String | Name of asset | Required, ID |
|   | salt     | byte[] | |    required  |
|   | path    | String | Path       | Required |
|   | payerAcct    | Account  |Payment transaction account  | Required，payer |
|   | gaslimit      | long | Gas limit     | Required |
|   | gasprice      | long | Gas price    | Required |
| Output param | txhash   | String  | transaction hash | 64-bit string |

* Send the constructed transaction to the server and let the server sign the transaction fee account.
```
Transaction makeRemoveAttribute(String ontid,String password,byte[] salt,String path,String payer,long gaslimit,long gasprice)
```


Example:
```
Transaction tx = ontSdk.nativevm().ontId().makeRemoveAttribute(ontid,password,salt,path,payer,gaslimit,0);
ontSdk.signTx(tx,identity.ontid,password);
ontSdk.getConnectMgr().sendRawTransaction(tx);
```

### 5. Ontid publicKey

**Add publicKey**

* Add publicKey

```
String sendAddPubKey(String ontid, String password,byte[] salt, String newpubkey,Account payerAcct,long gaslimit,long gasprice)
```

| Param      | Field   | Type  | Description |             Remarks |
| ----- | ------- | ------ | ------------- | ----------- |
| Input param| password| String | Identity password | Required |
|         | salt     | byte[] | |    Required  |
|        | ontid    | String | Identity ID   | Required, identity ID |
|        | newpubkey| String  |Public key       | Required, new pubkey|
|        | payerAcct    | Account  | Payer account       | Required, payer |
|        | gaslimit      | long | Gas limit     | Required |
|        | gasprice      | long | Gas price    | Required |
| Output param | txhash   | String  | Transaction hash  | Transaction hash |


* Send the constructed transaction to the server and let the server sign the transaction fee account.
```
Transaction makeAddPubKey(String ontid,String password,String newpubkey,String payer,long gaslimit,long gasprice)
```

Example:
```
Transaction tx = ontSdk.nativevm().ontId().makeAddPubKey(ontid,password,salt,newpubkey,payer,gas);
ontSdk.signTx(tx,identity.ontid.replace(Common.didont,""),password);
ontSdk.getConnectMgr().sendRawTransaction(tx);
```

* by recovery

```
String sendAddPubKey(String ontid,String recoveryAddr, String password,byte[] salt, String newpubkey,Account payerAcct,long gaslimit,long gasprice)
```


| Param      | Field   | Type  | Description |             Remarks |
| ----- | ------- | ------ | ------------- | ----------- |
| Input param|ontid|String | Identity ID   | Required，identity ID |
|        | recoveryAddr| String | Recovery address | Required |
|        | password| String | Recovery password | Required |
|        | salt    | byte[] |                   | Required |
|        | newpubkey| String  |Public key       | Required, new pubkey|
|        | payerAcct | Account  | Payer       | Required, payer |
|        | gaslimit      | long | Gas limit     | Required |
|        | gasprice      | long | Gas price    | Required |
| Output param | txhash   | String  | Transaction hash  | Transaction hash |


* no salt
```
Transaction makeAddPubKey(String ontid,String recoveryAddr,String password,String newpubkey,String payer,long gaslimit,long gasprice)
```

Parameter description, please refer to method three (recovery)


**Remove publicKey**

* remove publicKey

```
String sendRemovePubKey(String ontid, String password,,byte[] salt, String removePubkey,Account payerAcct,long gaslimit,long gasprice)
```


| Param      | Field   | Type  | Description |             Remarks |
| ----- | ------- | ------ | ------------- | ----------- |
| Input param | password| String | Identity password | rRquired |
|        | salt | byte[] | | Required|
|        | ontid    | String | Identity ID   | Required，identity ID |
|        | removePubkey| String  |Public key       | Required, removePubkey|
|        | payerAcct    | Account  | Payer account       | Required，payer |
|   | gaslimit      | long | gaslimit     | Required |
|   | gasprice      | long | gas price    | Required |
| Output param | txhash   | String  | Transaction hash  | Transaction hash |


* Send the constructed transaction to the server and let the server sign the transaction fee account.

```
Transaction tx = ontSdk.nativevm().ontId().makeRemovePubKey(ontid,password,salt,removePubkey,payer,gas);
ontSdk.signTx(tx,identity.ontid,password);
ontSdk.getConnectMgr().sendRawTransaction(tx);
```

* By recovery

```
String sendRemovePubKey(String ontid, String recoveryAddr,String password,salt, String removePubkey,Account payerAcct,long gaslimit,long gasprice)
```

| Param      | Field   | Type  | Description |             Remarks |
| ----- | ------- | ------ | ------------- | ----------- |
| Input param | ontid    | String | Identity ID   | Required, identity ID |
|        | password| String | Identity password | Required |
|        | salt| byte[] |  | Required |
|        | recoveryAddr| String | Recovery password | Required |
|        | removePubkey| String  |Public key       | Required. remove pubkey|
|        | payerAcct    | Account  | Payer       | Required, payer |
|   | gaslimit      | long | Gas limit     | Required |
|   | gasprice      | long | Gas price    | Required |
| Output param | txhash   | String  | Transaction hash  | Transaction hash |


* No salt

```
Transaction makeRemovePubKey(String ontid,String recoveryAddr, String password,salt, String removePubkey,String payer,long gaslimit,long gasprice)
```

Parameter description, please refer to method four (recovery)

### 6. Ontid recovery

**Add recovery**

* add recovery

```
String sendAddRecovery(String ontid, String password,byte[] salt, String recoveryAddr,Account payerAcct,long gaslimit,long gasprice)
```

| Param      | Field   | Type  | Description |             Remarks |
| ----- | ------- | ------ | ------------- | ----------- |
| Input param | password| String | Identity password | Required |
|        | ontid    | String | Identity ID   | Required, identity ID |
|        | password | String | Identity password |Required|
|        | salt     | byte[] | Identity salt  | Required|
|        | recoveryAddr| String  |Recovery address | Required, recovery|
|        | payerAcct    | Account  | Payer       | Required, payer |
|   | gaslimit      | long | Gas limit     | Required |
|   | gasprice      | long | Gas price    | Required |
| Output param | txhash   | String  | Transaction hash  | Transaction hash |


* Send the constructed transaction to the server and let the server sign the transaction fee account.

```
Transaction makeAddRecovery(String ontid, String password,salt, String recoveryAddr,String payer,long gaslimit,long gasprice)
```

Example:
```
Transaction tx = ontSdk.nativevm().ontId().makeAddRecovery(ontid,password,salt,recovery,payer,gas);
ontSdk.signTx(tx,identity.ontid,password);
ontSdk.getConnectMgr().sendRawTransaction(tx);
```

* Recovery


```
String sendChangeRecovery(String ontid, String newRecovery, String oldRecovery, String password,salt,long gaslimit,long gasprice)
```

| Param      | Field   | Type  | Description |             Remarks |
| ----- | ------- | ------ | ------------- | ----------- |
| Input param | ontid    | String | Identity ID   | required，identity ID |
|        | newRecovery| String  |New recovery address | Required，newRecovery|
|        | oldRecovery| String  |Old recovery address | Required，oldRecovery|
|        |  password | String  | Old recovery password  | Required |
|        | salt| byte[] |  | Required |
|   | gaslimit      | long | Gas limit     | Required |
|   | gasprice      | long | Gas price    | Required |
| Output param | txhash   | String  | Transaction hash  | Transaction hash |




