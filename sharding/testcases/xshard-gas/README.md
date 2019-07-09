
## Fee of shard transactions

All transaction fee in shard network is paid with ONG.
ONG in child shard is shadow of ONG in root shard, and managed by ONGx system contract in shard.

To send transctions in shard, user need deposit ONG to shard-asset system contract at root shard, ONGx will be mint at child shard.
Transaction fees are paid to shard governance contract, and split to shard nodes at consensus epoch switching over.
The fee splitting is done in two steps:
1. ONGx in shard goverance contract are burned
2. ONG in root shard is unfrozen from shard-asset system contract, and paid to shard nodes.

##### Fee of cross shard transactions

Transaction Tx_{A} in shard A can make remote-invocation to invoke another smart contract in shard B.  
This will trigger one cross-shard message from Tx_{A} to shard B, and smart contract processing in shard B.
All these fee should be paid by initiator of Tx_{A}.

Ontology sharding supports two types of cross-shard invocation, notify-based and transaction-based.
We take notify-based remote invocation as an example.  It takes the following steps:
1. Tx_{A} is sent to shard A
2. shard A processed Tx_{A}, remote-notify msg is created.
3. Fee of Tx_{A} is paid to shard A. (extra fee of remote-notify included)
4. remote-notify msg is sent to shard B
5. remote-notify msg is processed by shard B. 
6. Fee of remote-notify msg is paid by shard A.  (A own B one remote-notify fee)
7. at Shard B consensus epoch switching over, shard B request remote-notify fee from Shard A, 
8. remote-transaction fees between shard A and shard B are settled at root shard.

### Test cases

* asset deposit/withdraw at root shard
* asset mint/burn at shard
* free settlement after shard consensus epoch
* cross shard notification fee processing
* cross shard transaction fee processing
* cross shard fee settlement at root shard
