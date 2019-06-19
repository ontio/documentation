
With the development of Ontology ecosystem, more and more nodes are open to accept staking, and users can obtain additional benefits by authorizing staking to the node. This article describes how to integrate the  staking feature in your wallet.


Staking can be fulfilled by SDK - [ontology-ts-sdk](https://github.com/ontio/ontology-ts-sdk) and [ontology-java-sdk](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/GovernanceDemo.java)。


> The amount for participating in the staking must be an integral multiple of 500. The staking time must be more than one month. If you withdraw halfway, you will be deemed to voluntarily give up all the revenue.

> The wallet that supports staking now [Owallet](https://github.com/ontio/OWallet/releases)


## Staking

### Query the list of Ontology nodes 

```javascript
import {GovernanceTxBuilder} from 'ontology-ts-sdk'
const url = 'http://polaris1.ont.io:20334';
const peerMap = await GovernanceTxBuilder.getPeerPoolMap(url)
```

```java
Map m = sdk.nativevm().governance().getPeerPoolMap();
```

The result returned by this interface is details of all nodes. The displayed list needs to do some processing on the returned results, such as sorting by staking number, matching node names, and so on.More specific steps can refer to the processing method of OWallet. [NodeAuthorization.js --> fetchNodeList()](https://github.com/ontio/OWallet/blob/master/src/renderer/store/modules/NodeAuthorization.js)


The nodes currently open for staking are as follows:

```json
{
    name: 'Dubhe',
    pk: '02bcdd278a27e4969d48de95d6b7b086b65b8d1d4ff6509e7a9eab364a76115af7'
  },
  {
    name: 'Merak',
    pk: '0251f06bc247b1da94ec7d9fe25f5f913cedaecba8524140353b826cf9b1cbd9f4'
  },
  {
    name: 'Phecda',
    pk: '022e911fb5a20b4b2e4f917f10eb92f27d17cad16b916bce8fd2dd8c11ac2878c0'
  },
  {
    name: 'Megrez',
    pk: '0253719ac66d7cafa1fe49a64f73bd864a346da92d908c19577a003a8a4160b7fa'
  },
  {
    name: 'Alioth',
    pk: '022bf80145bd448d993abffa237f4cd06d9df13eaad37afce5cb71d80c47b03feb'
  },
  {
    name: 'Mixar',
    pk: '02765d98bb092962734e365bd436bdc80c5b5991dcf22b28dbb02d3b3cf74d6444'
  },
  {
    name: 'Alkaid',
    pk: '03c8f63775536eb420c96228cdccc9de7d80e87f1b562a6eb93c0838064350aa53'
  }
```

### Query staking details

```javascript
//@param pk {string} Public key of the node to stake
//@param userAddr {Address} Address of user
//@param url Url of network to connect

import {GovernanceTxBuilder, Crypto} from 'ontology-ts-sdk'
const url = getNodeUrl();
const userAddr = new Crypto.Address(address);
const authorizeInfo = await GovernanceTxBuilder.getAuthorizeInfo(pk, userAddr, url)
```

```java
String voteInfo= sdk.nativevm().governance().getAuthorizeInfo("02a98c15099d599b55c87834fd41bf9ad55408050b32bdc6ea88d6358717e19525",account.getAddressU160());
```

AuthorizeInfo has the following structure:

```javascript
class AuhtorizeInfo {
    peerPubkey: string = ''; //Node's public key
    address: Address; // User's wallet address
    consensusPos: number = 0; // Stake amount in consensus round
    freezePos: number = 0; // Stake amount in freeze status
    newPos: number = 0; // New stake amount
    withdrawPos: number = 0; // Stake amount locked in two round
    withdrawFreezePos: number = 0; Stake amount locked in one round
    withdrawUnfreezePos: number = 0; Claimable ONT
    }
```

> Total user staking number = consensusPos + freezePos + newPos
> Locked ONT number = withdrawPos + withdrawFreezePos
> Withdrawable ONT = withdrawUnfreezePos

### Query staking revenue 

```javascript
//@param userAddr {Address} User's wallet address
//@param url {string} Url of node

const url = getNodeUrl();
const userAddr = new Crypto.Address(address);        
const splitFee = await GovernanceTxBuilder.getSplitFeeAddress(userAddr, url)
```

```java
String res = sdk.nativevm().governance().getSplitFeeAddress(account1.getAddressU160().toBase58());
System.out.println("SplitFeeAddress:" + res);
```

```javascript
class SplitFeeAddress {
    address: Address; // User's wallet address
    amount: number = 0; // Stake profit ONG number
}
```

> The amount should divide by 1e9.

### Query unbound ONG amount 

```javascript
//@param addr {Address} User's wallet address
//@param url {string} Network's url

const url = getNodeUrl();
const addr = new Crypto.Address(address);
try {   
    let peerUnboundOng = await GovernanceTxBuilder.getPeerUnboundOng(addr, url);
    peerUnboundOng = new BigNumber(peerUnboundOng).div(1e9).toNumber();
    return peerUnboundOng;
} catch(err) {
    console.log(err);
}
```
> The result should divide by 1e9.

```java
String str = sdk.nativevm().governance().getPeerUbindOng("");
```

### Authorize the right of staking to a node

```javascript
import {GovernanceTxBuilder, Crypto} from 'ontology-ts-sdk'

//@param userAddr {Address} User's wallet address
//@param pks {[string]} Array of nodes' public keys
//@param amounts {[number]} Array of stake amounts
//@param payer {Address} Payer of the transaction
//@param GAS_PRICE {string} Normally set as 500
//@param GAS_LIMIT {string} Normally set as 20000

const userAddr = new Crypto.Address(this.stakeWallet.address)
const tx = GovernanceTxBuilder.makeAuthorizeForPeerTx(
    userAddr,
    pks,
    amounts,
    payer,
    GAS_PRICE,
    GAS_LIMIT
)
```
> User can stake some units.Stake amount = 500 ONT * units

```java
String txhash = sdk.nativevm().governance().authorizeForPeer(account1,new String[]{"02a98c15099d599b55c87834fd41bf9ad55408050b32bdc6ea88d6358717e19525"},new long[]{2000000},account1,20000,500);
```
### Cancel the staking authorization of a node

```javascript
import {GovernanceTxBuilder, Crypto} from 'ontology-ts-sdk'

//@param userAddr {Address} User's wallet address
//@param pks {[string]} Array of nodes' public keys
//@param amounts {[number]} Array of stake amounts
//@param payer {Address} Payer of the transaction
//@param GAS_PRICE {string} Normally set as 500
//@param GAS_LIMIT {string} Normally set as 20000

const userAddr = new Crypto.Address(this.stakeWallet.address);
const amount = Number(this.cancelAmount) * 500;
const tx = GovernanceTxBuilder.makeUnauthorizeForPeerTx(
    userAddr,
    pks,
    amounts,
    payer,
    GAS_PRICE,
    GAS_LIMIT
)
```
> The amount to cancel can not exceed the total amount in authorization.
> The amount to cancel = 500 * units

```java
String txhash = sdk.nativevm().governance().unAuthorizeForPeer(account1,new String[]{"02a98c15099d599b55c87834fd41bf9ad55408050b32bdc6ea88d6358717e19525"},new long[]{20000},account1,20000,500);
```
### Withdraw withdrawable ONT

```javascript
import {GovernanceTxBuilder, Crypto} from 'ontology-ts-sdk'

//@param userAddr {Address} User's wallet address
//@param pks {[string]} Array of nodes' public keys
//@param amounts {[number]} Array of stake amounts
//@param payer {Address} Payer of the transaction
//@param GAS_PRICE {string} Normally set as 500
//@param GAS_LIMIT {string} Normally set as 20000

const tx = GovernanceTxBuilder.makeWithdrawTx(
	userAddr,
	pks,
	amounts,
	payer,
	GAS_PRICE,
	GAS_LIMIT
)
```

```java
String txhash = sdk.nativevm().governance().withdraw(account,new String[]{"03e1e09221c9f513df76273f3cec0d033ee6056b159300d7b1072fc7020eadccbb"},new long[]{9999},payerAcct,sdk.DEFAULT_GAS_LIMIT,500);
```
### Withdraw unbound ONG

```javascript
import {GovernanceTxBuilder, Crypto} from 'ontology-ts-sdk'

//@param userAddr {Address} User's wallet address
//@param payer {Address} Payer of the transaction
//@param GAS_PRICE {string} Normally set as 500
//@param GAS_LIMIT {string} Normally set as 20000

const tx = GovernanceTxBuilder.makeWithdrawPeerUnboundOngTx(
    userAddr,
    payer,
    GAS_PRICE,
    GAS_LIMIT
)
```

```java
String txhash = sdk.nativevm().governance().withdrawOng(account1,account1,20000,500);
```
### Withdraw staking revenue 

```javascript
import {GovernanceTxBuilder, Crypto} from 'ontology-ts-sdk'

//@param userAddr {Address} User's wallet address
//@param payer {Address} Payer of the transaction
//@param GAS_PRICE {string} Normally set as 500
//@param GAS_LIMIT {string} Normally set as 20000

const tx = GovernanceTxBuilder.makeWithdrawFeeTx(
    userAddr,
    payer,
    GAS_PRICE,
    GAS_LIMIT
)
```

```java
String txhash = sdk.nativevm().governance().withdrawFee(account1,account1,20000,500);
```
