
随着本体生态发展，越来越多的节点开放并接受用户授权质押，用户可以通过授权质押给节点获取额外的收益。本文介绍了在钱包中如何集成授权质押功能。

授权质押，可以通过 ```SDK``` 实现质押 [ontology-ts-sdk](https://github.com/ontio/ontology-ts-sdk), [ontology-java-sdk](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/GovernanceDemo.java) 。


> 参与质押数额须为 500 的整数倍，质押时间必须超过 1 个月，若中途退出，则视为主动放弃收益。

> 当前支持用户授权质押的钱包：[Owallet](https://github.com/ontio/OWallet/releases)


接下来介绍授权质押的接口：

## 1. 查询开发授权质押的节点列表

```javascript
import {GovernanceTxBuilder} from 'ontology-ts-sdk'
const url = 'http://polaris1.ont.io:20334';
const peerMap = await GovernanceTxBuilder.getPeerPoolMap(url)
```

```java
Map m = sdk.nativevm().governance().getPeerPoolMap();
```

该接口返回的结果是所有的节点详情。展示的列表需要对返回结果做一些处理，如按质押总数进行排序，匹配节点名称等。具体步骤可以参考 ```OWallet``` 的处理方式： [NodeAuthorization.js --> fetchNodeList()](https://github.com/ontio/OWallet/blob/master/src/renderer/store/modules/NodeAuthorization.js)

目前开放授权质押的节点如下：

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

## 2.查询授权质押详情

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
AuthorizeInfo 具有以下结构：

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
> 用户质押总数 = consensusPos + freezePos + newPos
> 
> 用户锁定中的 ONT = withdrawPos + withdrawFreezePos
> 
> 用户可提取的 ONT = withdrawUnfreezePos

## 3. 查询授权质押收益

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

## 4. 查询 ONT 解绑的 ONG

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
## 5. 给某个节点授权质押

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
> User can stake some units.
> 
> Stake amount = 500 ONT * units

```java
String txhash = sdk.nativevm().governance().authorizeForPeer(account1,new String[]{"02a98c15099d599b55c87834fd41bf9ad55408050b32bdc6ea88d6358717e19525"},new long[]{2000000},account1,20000,500);
```
## 6. 取消对某个节点的授权质押

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
> 
> The amount to cancel = 500 * units

```java
String txhash = sdk.nativevm().governance().unAuthorizeForPeer(account1,new String[]{"02a98c15099d599b55c87834fd41bf9ad55408050b32bdc6ea88d6358717e19525"},new long[]{20000},account1,20000,500);
```
## 7. 提取可提取的 ONT

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
## 8. 提取解绑的 ONG

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
## 9. 提取授权质押的收益

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