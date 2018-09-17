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

A description of an Ontology Digital ID can be found in our [ONT ID Protocol and Trust Framework](https://github.com/ontio/ontology-DID) document.

<br>

## Digital ID management

**Identity data structure**

`ontid` The unique ID for this identity

`label` The name given to the identity by the user

`lock` ndicates whether the account is locked by the client user - Locked identities should not be updated by the client

`controls` An array of identity control Data

`extra` Extra information stored by client developer - value can be null

##### Example Identity data structure
```
public class Identity {
	public String label = "";
	public String ontid = "";
	public boolean isDefault = false;
	public boolean lock = false;
	public List<Control> controls = new ArrayList<Control>();
}
```

**Control data structure**

`algorithm` Name of the encryption algorithm used

`parameters` Encryption parameters

`curve` Elliptic curve used

`id` The control identifier

`key` NEP-2 private key

`salt` Private key decryption salt

`hash` Hash algorithm for derived privateKey


##### Example Control data structure
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


### Registering a digital identity

Digital identity creation refers to the generation of an Ontology digital identity with an appropriate identity data structure which would then be written to a wallet file.

##### Java SDK method to register a digital identity
```
Identity identity = ontSdk.getWalletMgr().createIdentity("password");
//any identity, once created is stored in memory only. A write api should be invoked to write to a wallet file.
ontSdk.getWalletMgr().writeWallet();
```


**Registering a blockchain-based digital identity**

Only after successfully registering a digital identity with the blockchain can the identity be truly used.

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

Upon successful registration, the corresponding DDO of the ONT ID will be stored on the Ontology blockchain. Detailed information about DDO can be found in [ONT ID identity protocol and smart contract implementation]
https://github.com/ontio/ontology-DID/blob/master/README.md



## Identity management

**Import identity**

Users who have already created a digital identity may import it into a wallet file via the SDK.

**Note:** It is advised to check if an identity already exists on the blockchain before you import one. If DDO does not exist, it means that no such identity has been registered on the blockchain. Then you may need to use ontSdk.getOntIdTx().sendRegister(identity,"passwordtest") for registration.

###### Example to import digital identity
```
Identity identity = ontSdk.getWalletMgr().importIdentity(encriptPrivateKey,password,salt,address);
//write to wallet     
ontSdk.getWalletMgr().writeWallet();
```

	Parameter Descriptions:
				encriptPrivateKey: Encrypted private key
				password: Password used to encrypt the private key
				salt: Private key decryption salt
				address: Account address
	
**Remove identity**

###### Example to remove digital identity
```
ontSdk.getWalletMgr().getWallet().removeIdentity(ontid);
//write to wallet
ontSdk.getWalletMgr().writeWallet();
```


**Set default identity**

###### Example to set default digital identity
```
ontSdk.getWalletMgr().getWallet().setDefaultIdentity(index);
ontSdk.getWalletMgr().getWallet().setDefaultIdentity(ontid);
```


## Query blockchain based digital identity

The DDO of a blockchain based digital identity can be queried by using the ONT ID.

###### Example to query blockhain for digital identity
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


## Ontid attributes

**Update blockchain-based DDO attribute**

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


###### Example to update an ontid attribute by specifying payer address for transaction fees
```
String sendAddAttributes(String ontid, String password,byte[] salt, Attribute[] attributes,Account payerAcct,long gaslimit,long gasprice)
Transaction tx = ontSdk.nativevm().ontId().sendAddAttributes(ontid,password,salt,attributes,payer,gaslimit,0);
ontSdk.signTx(tx,identity.ontid.replace(Common.didont,""),password);
ontSdk.getConnectMgr().sendRawTransaction(tx);

```

###### Example to update an ontid attribute by specifying that the node should sign

```
Transaction makeAddAttributes(String ontid, String password,byte[] salt, Attribute[] attributes,String payer,long gaslimit,long gasprice)
Transaction tx = ontSdk.nativevm().ontId().makeAddAttributes(ontid,password,salt,attributes,payer,gaslimit,0);
ontSdk.signTx(tx,identity.ontid.replace(Common.didont,""),password);
ontSdk.getConnectMgr().sendRawTransaction(tx);
```

**Remove blockchain-based DDO attribute**

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


###### Example to remove an ontid attribute by specifying payer address for transaction fees
```
String sendRemoveAttribute(String ontid,String password,salt,String path,Account payerAcct,long gaslimit,long gasprice)
Transaction tx = ontSdk.nativevm().ontId().sendRemoveAttribute(ontid,password,salt,path,payer,gaslimit,0);
ontSdk.signTx(tx,identity.ontid,password);
ontSdk.getConnectMgr().sendRawTransaction(tx);

```

###### Example to remove an ontid attribute by specifying that the node should sign
```
Transaction makeRemoveAttribute(String ontid,String password,byte[] salt,String path,String payer,long gaslimit,long gasprice)
Transaction tx = ontSdk.nativevm().ontId().makeRemoveAttribute(ontid,password,salt,path,payer,gaslimit,0);
ontSdk.signTx(tx,identity.ontid,password);
ontSdk.getConnectMgr().sendRawTransaction(tx);
```


## Ontid publicKey

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

**Add/update an ontid publicKey**
###### Example to add/update an ointid publicKey by specifying payer address for transaction fees
```
String sendAddPubKey(String ontid, String password,byte[] salt, String newpubkey,Account payerAcct,long gaslimit,long gasprice)
Transaction tx = ontSdk.nativevm().ontId().sendAddPubKey(ontid,password,salt,newpubkey,payer,gas,0);
ontSdk.signTx(tx,identity.ontid.replace(Common.didont,""),password);
ontSdk.getConnectMgr().sendRawTransaction(tx);
```

###### Example to add/update an ointid publicKey by specifying that the node should sign
```
Transaction makeAddPubKey(String ontid,String password,String newpubkey,String payer,long gaslimit,long gasprice)
Transaction tx = ontSdk.nativevm().ontId().makeAddPubKey(ontid,password,salt,newpubkey,payer,gas,0);
ontSdk.signTx(tx,identity.ontid.replace(Common.didont,""),password);
ontSdk.getConnectMgr().sendRawTransaction(tx);
```


##### Example to add/update an ointid publicKey using a recovery address
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

```
String sendAddPubKey(String ontid,String recoveryAddr, String password,byte[] salt, String newpubkey,Account payerAcct,long gaslimit,long gasprice)
```

##### Example to add/update an ointid publicKey using a recovery address without salt
```
Transaction makeAddPubKey(String ontid,String recoveryAddr,String password,String newpubkey,String payer,long gaslimit,long gasprice)
```

Parameter descriptions - please refer to recovery method above


**Remove publicKey**

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


###### Example to remove an ointid publicKey by specifying payer address for transaction fees
```
String sendRemovePubKey(String ontid, String password,byte[] salt, String removePubkey,Account payerAcct,long gaslimit,long gasprice)
Transaction tx = ontSdk.nativevm().ontId().sendRemovePubKey(ontid,password,salt,removePubkey,payer,gas,0);
ontSdk.signTx(tx,identity.ontid,password);
ontSdk.getConnectMgr().sendRawTransaction(tx);
```

###### Example to remove an ointid publicKey by specifying that the node should sign
```
String makeRemovePubKey(String ontid, String recoveryAddr,String password,salt, String removePubkey,String payer,long gaslimit,long gasprice)
Transaction tx = ontSdk.nativevm().ontId().makeRemovePubKey(ontid,password,salt,removePubkey,payer,gas,0);
ontSdk.signTx(tx,identity.ontid,password);
ontSdk.getConnectMgr().sendRawTransaction(tx);
```

##### Example to remove an ointid publicKey using a recovery address
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
```
String sendRemovePubKey(String ontid, String recoveryAddr,String password,salt, String removePubkey,Account payerAcct,long gaslimit,long gasprice)
```




##### Example to remove an ointid publicKey using a recovery address without salt
```
Transaction makeRemovePubKey(String ontid,String recoveryAddr, String password,salt, String removePubkey,String payer,long gaslimit,long gasprice)
```

Parameter descriptions - please refer to recovery method above



## Ontid recovery

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

**Add recovery address**

##### Example to add a recovery address to an ointid by specifying payer address for transaction fees
```
String sendAddRecovery(String ontid, String password,byte[] salt, String recoveryAddr,Account payerAcct,long gaslimit,long gasprice)
Transaction tx = ontSdk.nativevm().ontId().sendAddRecovery(ontid,password,salt,recovery,payer,gas,0);
ontSdk.signTx(tx,identity.ontid,password);
ontSdk.getConnectMgr().sendRawTransaction(tx);
```

##### Example to add a recovery address to an ointid by specifying that the node should sign
```
Transaction makeAddRecovery(String ontid, String password,salt, String recoveryAddr,String payer,long gaslimit,long gasprice)
Transaction tx = ontSdk.nativevm().ontId().makeAddRecovery(ontid,password,salt,recovery,payer,gas,0);
ontSdk.signTx(tx,identity.ontid,password);
ontSdk.getConnectMgr().sendRawTransaction(tx);
```

**Change recovery address**

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

##### Example to change the recovery address
```
String sendChangeRecovery(String ontid, String newRecovery, String oldRecovery, String password,salt,long gaslimit,long gasprice)
Transaction tx = ontSdk.nativevm().ontId().makeAddRecovery(ontid,newrecoveryaddress,oldrecoveryaddress,password,salt,gas,0);
ontSdk.signTx(tx,identity.ontid,password);
ontSdk.getConnectMgr().sendRawTransaction(tx);
