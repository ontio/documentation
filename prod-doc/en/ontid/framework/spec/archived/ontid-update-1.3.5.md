## Abstract

The previous ONT ID design is simple and cannot satisfy some complex requirements.This proposal describes three improvements for ONT ID: controller, recovery and revoking.


## Specification

### Controller

An ONT ID can be controlled by other ONT ID(s), in the controller mode. Distinguished from the original self-sovereign mode, the controlled ONT ID can be used without binding keys. Meanwhile, the entity does not need to sign the transaction. The controller must provide valid signature instead. The controller can be either an ONT ID or a group of ONT IDs. All the IDs must be in the self-sovereign mode. In the case of group, the threshold control is supported. Following is an example of a (m, n)-threshold group:

```json
{
  "threshold": m,
  "members": [ID1, ID2, ... , IDn]
}
```

Furthermore, the group can be recursively defined, i.e. a group member can be another sub-group:

```json
{
  "threshold": m1,
  "members": [
    ID1,
    {
      "threshold": m2,
      "members": [ID2, ...]
    },
    ...
  ]
}
```

The controller can modify the controlled ID's attributes, as well as bind keys for the ID to convert it to the self-sovereign mode. On the contrary, a self-sovereign ID can not be converted to the controller mode.

### Recovery

Recovery is used for recovering or resetting the keys for ONT ID, in the case of key missing. This proposal suggests using the group control logic described in the above section to acheive better flexibility.

Recovery can only modify keys or update the Recovery setting for the ONT ID. Valid signature(s) must be provided in the transaction when operating.

### Revoking

In the previous design, ONT ID can not be deleted or revoked explicitly. When an ONT ID is not needed any more, the owner can just delete it and the related keys from his client, while the state remains on chain.

This proposal adds revoking mechanism to ONT ID. An ONT ID can be revoked by its owner or controller when it is not needed. Revoked ONT ID will be marked as "revoked", and its data, such as keys and attributes, will be deleted.



### Data structure

* Group：

A group consists of multiple members with threshold control. A member can be a registered ONT ID or another sub-group.

```
Group {
    threshold    //an integer
    members      //array of members
}
```


* Signer：

Signer defines the signer's ONT ID and the index of corresponding public key for checking witness.

```
Signer {
    id     //signer's ONT ID
    index  //index of the public key
}
```


### Methods


#### regIDWithController

Register a controller mode ONT ID. This method should be called by the controller.

Arguments：

|   |    type    |  description|
| --- | ------------ | --------------- |
| 0 | byte array | ONT ID to be registered|
| 1 | byte array | the controller|
| 2 | int or byte array | index of public key or serialized Signer array|

Argument 1 is the controller, whose signature must be contained in the transaction. The controller can be either an ONT ID or a serialized Group structure. The first 8 bytes can be used for discrimination. While argument 2 is correspondingly either a integer indecates the index of public key, or a byte array which is the serialization of a `Signer` array.

Event：("Register", ONT ID)

#### revokekID

Revoke a self-sovereign ONT ID. This method should be called by the ID's owner.

Arguments：

| |    type    |  description|
| -- | ------------ | --------------- |
| 0 | byte array | ONT ID|
|1 |  int  |  index of the owner's public key|

Argument 1 specifies the public key for checking witness

Event：("Revoke", ONT ID)


#### revokeIDByController

Controller revoke the controlled ONT ID. This method should be called by the controller.

Arguments：

|   |    type    |  description|
|---|------------|---------------|
| 0 | byte array | ONT ID |
| 1 | int or byte array | index of public key or serialized Signer array|

Event：("Revoke", ONT ID)

#### removeController

Remove the controller to convert the ONT ID to self-sovereign mode. This method can only be called by the owner, i.e. the ONT ID must have bound a key.

Arguments:

|   |    type    |  description|
|---|------------|---------------|
| 0 | byte array | ONT ID|
| 1 |  int | index of the owner's public key|

The owner's signature must be included in the transaction, while the argument 1 specifies the public key for checking witness.

Event：("RemoveController", ONT ID)


#### addKeyByController

Controller bind a public key to the controlled ONT ID.

Arguments：

|   |    type    |  description|
|---|------------|---------------|
| 0 | byte array | ONT ID|
| 1 | byte array | public key to be added|
| 2 | int or byte array | index of public key or serialized Signer array|


Event： ("PublicKey", "add by controller", ONT ID, new public key, index of the new public key)


#### addAttributesByController

Controller add attributes to the controlled ONT ID

Arguments:

|   |    type    |  description|
|---|------------|---------------|
| 0 | byte array | ONT ID|
| 1 | attribute array | array of attributes to be added|
| 2 | int or byte array | index of public key or serialized Signer array|


Event：("Attribute", "add by controller", ONT ID, key list of added attributes)


#### removeAttributeByController

Controller removes a specific attribute of the controlled ONT ID.

Arguments:

|   |    type    |  description|
|---|------------|---------------|
| 0 | byte array | ONT ID|
| 1 | byte array | key of attribute to be removed|
| 2 | int or byte array | index of public key or serialized Signer array|

Event：("Attribute", "remove by controller", ONT ID, key of removed attribute)

#### VerifyController

Verify whether the transaction is signed by controller.

Argumetns：

|   |    type    |  description|
|---|------------|---------------|
| 0 | byte array | ONT ID|
| 1 | int or byte array | index of public key or serialized Signer array|

Return：True/False

#### addRecovery

Set the recovery, which is defined by a Group structure. This method should be called by the owner.

Arguments:

|   |    type    |  description|
|---|------------|---------------|
| 0 | byte array | ONT ID|
| 1 | byte array | serialized the recovery group|
| 2 |   int   | index of the owner's public key|

Event：("Recovery", "add", ONT ID, recovery in JSON format)

#### changeRecovery

Change the recovery to a new group. This method should be called by the original recovery group.

Arguments:

|   |    type    |  description|
|---|------------|---------------|
| 0 | byte array | ONT ID|
| 1 | byte array | serialized new recovery group|
| 2 | byte array | serialized Signer array|

#### addKeyByRecovery

Recovery group bind a public key to the ONT ID.

Arguments:

|   |    type    |  description|
|---|------------|---------------|
| 0 |  byte array | ONT ID|
| 1 |  byte array | new public key|
| 2 |  byte array | serialized Signer array|

Event：("PublicKey", "add by recovery", ONT ID, new public key, index of new public key)

#### removeKeyByRecovery

Recovery group remove a bound public key.

Arguments:

|   |    type    |  description|
|---|------------|---------------|
| 0 | byte array | ONT ID|
| 1 |  int  | index of the public key to be removed|
| 2 | byte array | serialized Signer array|

Event：("PublicKey", "remove by recovery", ONT ID, removed public key, index of removed public key)