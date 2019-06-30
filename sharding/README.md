English | [中文](Testnet_Dev_Manual_CN.md)

# Ontology Sharding

Ontology is committed to creating a componentized, freely configurable, cross-chain supporting, high performance, and scalable blockchain infrastructure, making deploying and calling decentralized applications much easier.

The Ontology Sharding TestNet has gone live and developers are welcome to have a try. Many features are still under development, so please let us know if you have any suggestions or feedback when using it.

## Features

- Multi-layer sharding network structure
- Sharding solution based on smart contract
- Support cross-shard message communication between smart contracts
- Support cross-shard atomic call


## TestNet Environment

The Ontology Sharding TestNet includes three shards, which can achieve cross-chain interaction.

|         |           | IP Address       | Rest     | P2P   |
| ----    | --------- | ---------------  | -------- | ----- |
| Root Shard | **Peer_{0,1}** | 139.217.111.185  | 20334    | 20338 | 
|            | **Peer_{0,2}** | 139.217.103.126  | 20334    | 20338 | 
|            | **Peer_{0,3}** | 139.217.111.232  | 20334    | 20338 | 
|            | **Peer_{0,4}** | 139.217.80.65    | 20334    | 20338 | 
|            | **Peer_{0,5}** | 139.217.111.194  | 20334    | 20338 | 
|            | **Peer_{0,6}** | 139.217.111.250  | 20334    | 20338 | 
|            | **Peer_{0,7}** | 139.217.103.26   | 20334    | 20338 | 
| Shard-A    | **Peer_{1,1}** | 139.217.111.185  | 30334    | 30338 | 
|            | **Peer_{1,2}** | 139.217.103.126  | 30334    | 30338 | 
|            | **Peer_{1,3}** | 139.217.111.232  | 30334    | 30338 | 
|            | **Peer_{1,4}** | 139.217.80.65    | 30334    | 30338 | 
|            | **Peer_{1,5}** | 139.217.111.194  | 30334    | 30338 | 
|            | **Peer_{1,6}** | 139.217.111.250  | 30334    | 30338 | 
|            | **Peer_{1,7}** | 139.217.103.26   | 30334    | 30338 | 
| Shard-B    | **Peer_{2,1}** | 139.217.111.185  | 40334    | 40338 | 
|            | **Peer_{2,2}** | 139.217.103.126  | 40334    | 40338 | 
|            | **Peer_{2,3}** | 139.217.111.232  | 40334    | 40338 | 
|            | **Peer_{2,4}** | 139.217.80.65    | 40334    | 40338 | 
|            | **Peer_{2,5}** | 139.217.111.194  | 40334    | 40338 | 
|            | **Peer_{2,6}** | 139.217.111.250  | 40334    | 40338 | 
|            | **Peer_{2,7}** | 139.217.103.26   | 40334    | 40338 | 

We can see from the table above that the sharding network has 21 nodes as shown in the figure below:
![shard-net](resources/sharding-net.jpg)

#### Multi-layer Sharding Network Structure

As can be seen from the above figure, all 21 nodes participate in the root shard, another 7 nodes form Shard-A, and 7 nodes form Shard-B.
The entire sharding network forms a two-layer structure with 7 nodes participating only in the Root Shard at the top. The second layer consists of two sharding subnetworks.

## How to get Test Tokens

Apply for test tokens here: https://developer.ont.io/applyOng
The site allows one address to apply for 1000 ONT and 10 ONG as test tokens.


## How to get Ontology

1. Clone the Ontology source code from [github.com/ontio/ontology.git]

```
$ git clone https://github.com/ontio/ontology.git
```

Then check out the "sharding" branch.


```
$ git checkout -b sharding remotes/origin/sharding
```

2. Fetch the dependent packages using Glide, a third-party package management tool  

```
$ cd $GOPATH/src/github.com/ontio/ontology
$ glide install
```

3. If necessary, update the dependent third party packages with Glide:

```
$ cd $GOPATH/src/github.com/ontio/ontology
$ glide update
```

4. Build the source code with make:

```
$ make all
```

After building the source code successfully, the generated Ontology application is the Ontology node application which supports the Ontology sharding.

#### How to get the Ontology Sharding Management Tool

1. Clone the Ontology-tool codes from https://github.com/qiluge/ontology-tool.git

```
$ git clone https://github.com/qiluge/ontology-tool.git
```

2. Build the source code with go build

```
$ go build main.go -o ontology-tool
```

3. Configure config_test.json in the Ontology tool directory and update the fields as follows.

```
  "JsonRpcAddress": "http://139.217.111.185:20336",
  "WalletFile": "./your-wallet.dat",
  "Password": "your-password",
```

#### Activate Sharding Nodes
(Optional operations)
Download the configuration file [config.json] (./Config/config.json) of the Ontology Sharding TestNet and save it to the same directory in the Ontology application.
Activate the synchronous nodes of the Ontology Sharding TestNet.

```
$ ./ontology --config config.json --networkid 606
```

The complete activation process of a shard is as follows:

1. Create a shard: Apply for a shard ID in the Root Shard
2. Configure the shard: Configure parameters of the new shard, including consensus and related parameters of the Gas.
3. The nodes join the shard: the nodes in the Root Shard join the new sharding network through staking
4. Activate the shard

#### Create the Shard
Apply to create a shard with Ontology-tool. The parameters of creating the shard are saved to params/shardmgmt/ShardCreate.json. The command for creating shard is:
```
$ ./ontology-tool -t ShardInit
```

After the shard creation request is approved, a shard ID will be assigned to the shard and all subsequent configuration and operations will be based on this ID.

#### Configure the Shard
After obtaining the shard ID, the creator of the shard needs to configure the shard.
The parameters for configuring the shard are saved to params/shardmgmt/ShardConfig.json.
The parameters of the current shard configuration are as follows (may be increased on demand):

* Network Size: The node size of the sharding network
* N: The number of consensus nodes in the sharding network
* Block Msg Delay: The maximum delay of block message transmission in the sharding network consensus process (the unit is ms)
* Max Block Change View: The consensus round switch time of the sharding network (block number)
* Min Init Stake: The minimum stake amount required for becoming a node in the sharding network

Configure the shard with the command below:
```
$ ./ontology-tool -t ShardConfig
```

#### How do Nodes join the Sharding Network

After configuring the shard, the nodes in the Root Shard can join the sharding network via staking.
After joining the sharding network, the nodes need to activate new Ontology nodes for this shard.
To join the sharding network, nodes also need to use the Ontology-tool to apply. The parameters are saved to params/shardmgmt/ShardPeerJoin.json.
The parameters for applying to join the sharding network are as follows:

* Shard ID: The shard ID for applying to join the sharding network
* IP Address: The IP address and P2P port of the node that will be activated for the shard
* Public Key: The public key of the node
* Stake Amount: The stake amount of the node
：
Nodes apply to join the sharding network with the command below:

```
$ ./ontology-tool -t ShardPeerApply
```

After joining the sharding network, the nodes can apply to exit at any time.
If the shard has not yet been activated when the node applys to exit, the node will be able to exit immediately and get back its stake.
If the shard has been activated, the node will be able to exit after the consensus round according to the role of the node in the sharding network.
Nodes can apply to exit with the command below:

```
$ ./ontology-tool -t ShardPeerExit
```

#### Activate the Ontology Sharding Node

After joining the sharding network, nodes can activate the sharding and synchronize the blocks of the root shard.
Activate the sharding nodes with the command below:
```
$ ./ontology  --ShardID  <shard-ID>  --config config.json --networkid 606 --enable-consensus
```
After activating the Ontology sharding nodes, first you need to synchronize the blocks of the root shard and wait for the corresponding shard to activate.

#### Activate the Shard

After enough nodes have joined the sharding network,  the shard can then be activated.
The shard creator will activate the shard.
The parameters for activating the shard are saved to params/shardmgmt/ShardActivate.json.
Activate the shard with the command below:
```
$ ./ontology-tool -t ShardActivate
```

## Sharding Smart Contract Development

The Ontology Sharding adopts a sharding strategy for smart contracts, assigning smart contracts in the root shard to sharding, while assets can be kept in the root shard, thus simultaneously improving the performance of smart contracts and ensuring the security of blockchain assets.

In the Ontology Sharding Network, all smart contracts are deployed in the root shard and smart contracts can run as follows:

* All-Shard: Smart contracts can run on all shards simultaneously.
* One-Shard: Smart contracts can only run on a single shard at one time.

The state of the smart contract running on All-Shard will be saved in all the shards it runs on, so the state of the All-Shard smart contract will have to be saved as an account. In the current Ontology Sharding network, smart contracts based on shardAsset contracts can implement smart contract state management in the form of accounts. For details, please refer to [OEP-9] (https://github.com/ontio/OEPs/pull/50).

#### Cross-Shard Smart Contract Development
Developing cross-shard smart contract development is basically the same as developing Ontology smart contract, except that two interfaces are added to the sharding network for calling cross-shard smart contract. Ontology provides two interfaces for cross-shard communication: <code>NotifyRemoteShard</code> and <code>InvokeRemoteShard</code> used for asynchronous and synchronous call. Since cross-shard communication relies on network transmission, Parameters transmitted during cross-shard communication should be serialized into byte array.

* NotifyRemoteShard
* InvokeRemoteShard

NotifyRemoteShard is used for asynchronous cross-shard call. However, the caller cannot get the call result of the callee, nor does it know when callee executes on the target shard or whether callee executes successfully or not.

InvokeRemoteShard is used for synchronous cross-shard call. The caller can get the call result of the callee and can see it as delayed execution of cross-contract call. Since the call result is returned via network transmission, the return result of the callee should be the serialized byte array.

## Deploy Sharding Smart Contract

New smart contract features are supported in the sharding environment. The two most important features are presented in the form of OEP. See [OEP-9] (https://github.com/ontio/OEPs/pull/50) and [OEP-11] (https://github.com/ontio/OEPs/pull/54) for more details.

To support these new features, the smart contract compiler has also been upgraded and has added Runtime API specifically for the new sharding network. At the moment, only the compiler for Python has been upgraded. See [Ontology Sharding Compiler](https://github.com/qiluge/ontology-python-compiler/tree/sharding) for the upgraded compiler. The method is the same as before.

Likewise, in order to support these new features in the sharding environment, the transaction structure has changed. Currently, only [ontology-go-sdk] (https://github.com/ontio/ontology-go-sdk/) Tree/sharding) supports sharding transactions.

Below is an example of cross-shard contract call [an OEP-9 example] (https://github.com/qiluge/ontology-xshard-contract/blob/master/xshardasset/xshardassetdemo.py).

### Compile

```
git clone https://github.com/qiluge/ontology-python-compiler
git clone https://github.com/qiluge/ontology-xshard-contract
cd ontology-python-compiler
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
git checkout -b sharding origin/sharding
./run.py -n ../ontology-xshard-contract/xshardasset/xshardassetdemo.py -m 1
```
After compiling, enter the directory ```ontology-xshard-contract/xshardasset```, which includes the following files:
```
xshardassetdemo.Func.Map
xshardassetdemo.abi.json
xshardassetdemo.avm
xshardassetdemo.avm.str
xshardassetdemo.debug.json
xshardassetdemo.py
xshardassetdemo.warning
```
```xshardassetdemo.avm.str``` is the compiled bytecode file.

### Deploy

According to the descriptions of [OEP-11], if the contract needs to be able to run across shards, the contract should be deployed on the root shard.
Smart contracts can be deployed using Ontology-Go-SDK. The sample codes are as follows:
```
    avmCode, err := ioutil.ReadFile("xshardassetdemo.avm.str")
    if err != nil {
        log.Error(err)
        return
    }
    InitSdk()
    testOntSdk.ClientMgr.GetRpcClient().SetAddress("http://139.217.111.185:20336")
    hash, err := testOntSdk.NeoVM.DeployNeoVMSmartContract(0, 20000000, testDefAcc, true, string(avmCode),
        "xshard asset demo", "1.0.0", "tester", "test@test.com", "xshard asset demo")
    if err != nil {
        log.Error(err)
        return
    }
    log.Infof("deploy success, tx hash: %s", hash.ToHexString())
```

## Call Sharding Smart Contract

You can call the sharding contract using two methods: Ontology-cli and Ontology-Go-SDK.

### Ontology-cli

The method of calling smart contract using Ontology-cli is the same as [existing cli] (https://github.com/ontio/ontology/blob/master/docs/specifications/cli_user_guide_CN.md), except that you need to add one more parameter ```- -ShardID```. The new ```--ShardID``` parameter is used to indicate contract on which shard is called. If not specified, the default is 0. There are two limitations to using Ontology-cli to call a sharding smart contract:
1. Ontology-cli needs to be compiled with the code in the [ontology sharding branch] (https://github.com/ontio/ontology/tree/sharding);
2. Only the synchronous nodes which activate the Sharding TestNet can use Ontology-cli. You need to synchronize the blocks on the shard whose contract you are going to call.

Example:
```
./ontology contract invoke --address 8ae002c5c3fe5bf8c3ef8a043fc618645c314c42 --params string:init,[int:0] --gasprice 0 --gaslimit 3000000 --ShardID 1 --rpcport 30336
```
The init method of the contract ```8ae002c5c3fe5bf8c3ef8a043fc618645c314c42``` will be called.
It should be noted that if the method of calling contract does not require parameters, cli still needs to transmit any random parameters, and it does not support more complex data types.

### Call Smart Contract with Ontology-Go-SDK

Unlike Ontology-cli, using Ontology-Go-SDK does not have the same limitations. For example, the sample codes for calling the cross-shard transfer of the smart contract example ```xshardassetdemo.py``` are as follows:

```
txHash, err := ctx.Ont.NeoVM.InvokeShardNeoVMContract(shardId, gasPrice,
                gasLimit, user, contractAddress,
                []interface{}{"xshardTransfer", []interface{}{from, toAddr, toShard, num}})
```

### Example

After you have deployed an OEP-9 contract, you can then make cross-shard transfer as follows:

1. Call ```init``` method to initialize the contract:
    ```
    contract, err := common.AddressFromHexString("8ae002c5c3fe5bf8c3ef8a043fc618645c314c42")
    if err != nil {
        log.Error(err)
        return
    }
    initTx, err := testOntSdk.NeoVM.InvokeNeoVMContract(0, 20000, testDefAcc, contract, []interface{}{"init", []interface{}{}})
    if err != nil {
        log.Error(err)
        return
    }
    log.Infof("init success, tx hash: %s", initTx.ToHexString())
    ```
2. After initialization, you can check the balance in the Owner account:

    ```
    value, err := ctx.Ont.NeoVM.PreExecInvokeShardNeoVMContract(0, contract,
        []interface{}{"balanceOf", []interface{}{user}})
    if err != nil {
        return fmt.Errorf("pre-execute err: %s", err)
    }
    info, err := value.Result.ToInteger()
    if err != nil {
        return fmt.Errorf("parse result failed, err: %s", err)
    }
    log.Infof("balance of %s is: %s", user.ToBase58(), info.String())
    ```
    The result is:

    ```
    balance of AZ3BTJt7jNGwJjVLsYJAyfLtCJ38Cd8Uri is: 100000000000000000
    ```

3. Transfer 1000000000 from the Owner account to the address ```AZqk4i7Zhfhc1CRUtZYKrLw4YTSq4Y9khN``` of Shard 1:

    ```
    txHash, err = ctx.Ont.NeoVM.InvokeShardNeoVMContract(0, 0, 200000, user, contractAddress,
                []interface{}{"xshardTransfer", []interface{}{from, toAddr, 1, 1000000000}})
    if err != nil {
        return fmt.Errorf("invokeNativeContract error :", err)
    }
    log.Infof("txHash is: %s", txHash.ToHexString())
    ```

Check the balance in the Owner account:

```
balance of AZ3BTJt7jNGwJjVLsYJAyfLtCJ38Cd8Uri is: 99999999000000000
```
After shard 1 has generated the block, you can check the balance of the address ```AZqk4i7Zhfhc1CRUtZYKrLw4YTSq4Y9khN``` on shard 1:

```
balance of AZ3BTJt7jNGwJjVLsYJAyfLtCJ38Cd8Uri is: 1000000000
```
