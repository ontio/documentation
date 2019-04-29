


## 钱包文件

钱包用户存储多个数字身份以及数字资产账户。钱包文件采用 JSON 格式对数据进行组织，各个字段的详细可以参考[钱包文件规范](https://ontio.github.io/documentation/Wallet_File_Specification_cn.html)。

### 创建钱包

```swift
let wallet = Wallet(name: "mickey")
```

### 保存钱包

```swift
let walletJson = try! JSONEncoder().encode(w).utf8string
```

### 导入钱包

```swift
let str = "wallet_json"
let w = try JSONDecoder().decode(Wallet.self, from: str.data(using: .utf8)!)
```

## 公私钥和地址

账户是基于公私钥创建的，地址是公钥转换而来。

### 创建私钥 

使用默认的参数创建:

```swift
let prikey = try! PrivateKey.random()
```

用到的默认参数在 Constant 类中:

```swift
public final class Constant {

  public static let defaultAlgorithm = JSON([
    "algorithm": "ECDSA",
    "parameters": [
      "curve": "P-256",
    ],
  ])

  public static let defaultScrypt = JSON([
    "cost": 4096,
    "blockSize": 8,
    "parallel": 8,
    "size": 64,
  ])
}
```

使用指定的参数创建私钥:

```swift
let prikey = try! PrivateKey(
  raw: try! Data.random(count: 32),
  algorithm: .sm2,
  parameters: KeyParameters(curve: .sm2p256v1)
)
```

### 导入私钥 

直接导入:

```swift
let prikey = try PrivateKey(
  hex: "ab80a7ad086249c01e65c4d9bb6ce18de259dcfc218cd49f2455c539e9112ca3",
  algorithm: .sm2,
  parameters: KeyParameters(curve: .sm2p256v1)
)
```

从 WIF 导入:

```swift
let pri = try PrivateKey.from(wif: "L4shZ7B4NFQw2eqKncuUViJdFRq6uk1QUb6HjiuedxN4Q2CaRQKW")
```

### 获取公钥

```swift
let pubkey = try prikey.getPublicKey()
```

### 获取地址

当获取了公钥实例后，可以通过下面方式获得对应的地址:

```swift
let pubkey = try prikey.getPublicKey()
let addr = try Address.from(pubkey: pubkey)
```

## 账户

### 创建账户

```swift
let acc = try! Account.create(pwd: "123456")
```

### 导入账户

从 keystore 导入:

```swift
let str = "keystore_content"
let acc = try Account.from(keystore: str, pwd: "111111")
```

从 WIF 导入:

```swift
let acc = try Account.from(wif: "L4shZ7B4NFQw2eqKncuUViJdFRq6uk1QUb6HjiuedxN4Q2CaRQKW", pwd: "111111")
```

从助记词导入:

```swift
let mnemonic = "doll remember harbor resource desert curious fatigue nature arrest fix nation rhythm"
let acc = try Account.from(mnemonic: mnemonic, pwd: "111111")
```

### 加入钱包

```swift
let wallet = Wallet(name: "mickey")
let acc = try! Account.create(pwd: "123456")
wallet.add(account: acc)
```

### 移除账户

```swift
let wallet = Wallet(name: "mickey")
let acc = wallet.accounts[0]
wallet.delete(account: acc)
```

## 资产

本体中有两种原生资产: ONT 和 ONG

### 转账

下面是一个比较完整的对 ONT 进行转账的例子:

```swift
// 转账发起地址
let from = address1!
// 收款地址
let to = try Address(value: "AL9PtS6F8nue5MwxhzXCKaTpRb3yhtsix5")

let ob = OntAssetTxBuilder()
let tx = try ob.makeTransferTx(
  tokenType: "ONT",
  from: from,
  to: to,
  amount: BigInt(300), // 转账金额
  gasPrice: gasPrice,
  gasLimit: gasLimit,
  payer: from // 交易费用提供方地址，这里同转账发起地址
)

let txb = TransactionBuilder()
// 使用 payer 的私钥签名交易
try txb.sign(tx: tx, prikey: prikey1!)

// 通过 rpc 将交易发送到链上
let rpc = WebsocketRpc(url: "ws://127.0.0.1:20335")
rpc!.open()
try! rpc!.send(rawTransaction: tx.serialize()).then {
  // 打印结果
  print($0)
}
```

转账 ONG 与上面的流程基本一样，只是 `tokenType` 值替换为 `ONG` 即可。

### 余额查询

使用 RPC 来进行余额查询:

```swift
try! rpc!.getBalance(address: Address(value:"AL9PtS6F8nue5MwxhzXCKaTpRb3yhtsix5")).then {
  // 打印结果
  print($0)
}
```

## 创建身份

ONT ID 是一个去中心化的身份标识，能够管理用户的各种数字身份认证。数字身份(Identity)是 ONT SDK 导出的一个核心类，该类包含代表身份的 ONT ID 属性。可以通过 SDK 来创建一个身份。创建身份的过程中会基于用户的私钥生成 ONT ID。

> 有关 ONT ID 的规范，见 [ONT ID 生成规范](https://ontio.github.io/documentation/ONTID_protocol_spec_en.html)

```swift
let prikey = try! PrivateKey.random()
let id = try! Identity.create(prikey: prikey!, pwd: "123456", label: "mickey")
```

## 注册身份

身份创建完成后，还需要将身份的 ONT ID 注册到链上，身份才算真正地创建完成。发送 ONT ID 上链是需要发送交易的过程。可以通过调用 SDK 提供的方法构造交易对象。一种比较典型的场景是通过传递刚刚创建的 ONT ID 和用户的私钥来构造交易对象。

```swift
// 构造 ontid
let prikey = try! PrivateKey.random()
let account = try! Account.create(pwd: "123456", prikey: prikey, label: "", params: nil)
let address = account!.address
let ontid = try! "did:ont:" + address!.toBase58()

// 构造交易
let b = OntidContractTxBuilder()
let tx = try b.buildRegisterOntidTx(
  ontid: ontid,
  pubkey: prikey1!.getPublicKey(), // ontid 相关公钥
  gasPrice: gasPrice,
  gasLimit: gasLimit,
  payer: address1 // 交易费用提供地址
)

// 构造交易，并使用交易费用提供地址对应的私钥交易签名
let txb = TransactionBuilder()
try txb.sign(tx: tx, prikey: prikey1!)

// 发送交易
try! rpc!.send(rawTransaction: tx.serialize()).then {
  // 打印结果
  print($0)
}
```

## 查询 DDO

```swift
// 构造交易
let b = OntidContractTxBuilder()
let tx = try b.buildGetDDOTx(ontid: ontid!)

// 签名交易
let txb = TransactionBuilder()
try txb.sign(tx: tx, prikey: prikey1!)

try! rpc!.send(rawTransaction: tx.serialize(), preExec: true).then {
  // 打印结果
  print($0)
}
```

## 部署合约

部署合约需要构建并发送相应的交易到链上执行。

构建合约需要提供合约内容的十六进制字符串，和一些配置参数。

配置参数如下：

| 参数          | 含义                                     |
| ------------- | ---------------------------------------- |
| \$code        | 合约内容，十六进制的字符串。             |
| \$name        | 合约的名称。普通字符串。可选值。         |
| \$codeVersion | 合约的版本。普通字符串。可选值。         |
| \$author      | 合约作者。普通字符串。可选值。           |
| \$email       | 合约作者的邮件地址。普通字符串。可选值。 |
| \$desc        | 合约的描述。普通字符串。可选值。         |
| \$needStorage | 是否需要使用存储。布尔值。可选值。       |

```swift
// 合约编译后的字节码
let code = NSData(contentsOfFile: path)!

// 构造、签名交易
let b = TransactionBuilder()
let tx = try b.makeDeployCodeTransaction(
  code: code as Data,
  name: "name",
  codeVersion: "1.0", 
  author: "alice",
  email: "email",
  desc: "desc",
  needStorage: true,
  gasPrice: gasPrice,
  gasLimit: "30000000",
  payer: address1!
)
try b.sign(tx: tx, prikey: prikey1!)

try! rpc!.send(rawTransaction: tx.serialize(), preExec: false, waitNotify: true).then {
  // 打印结果
  print($0)
}
```

## 调用合约

合约必须在成功部署后才能调用。 调用合约需要构建并发送相应的交易到链上执行。

### 通过 abi 文件构建交易

针对于 NEO 虚拟机的智能合约可以编译出相应的 `.avm` 文件和 `.abi` 文件。`.abi` 文件是以 JSON 格式存储，包含了描述智能合约的方法和参数的内容。可以通过读取`.abi` 文件方便的构建调用合约的交易。构建的交易可能还需要使用用户的私钥签名。

为了对合约方法进行调用，我们需要得到该方法的 abi 信息，以此构造调用请求。abi 信息所涉及的类包括: `AbiInfo`，`AbiFunction` 和 `Parameter`。

`AbiInfo` 类用于将 `.abi` 文件的内容体现到内存中，方便对其中的方法信息的操作。

```swift
// 载入 abi
let path = bundle.path(forResource: "NeoVmTests.abi", ofType: "json")!
let json = NSData(contentsOfFile: path)! as Data
let abiFile = try JSONDecoder().decode(AbiFile.self, from: json)
let abi = abiFile.abi

// 需要调用的合约方法
let fn = abi!.function(name: "hello")!

// 构造用于合约调用的交易
let b = TransactionBuilder()
let tx = try b.makeInvokeTransaction(
  fnName: fn.name,
  // 合约方法所需的参数，因为数值已经包含了类型信息
  // 所以只需要指定数值关联的形参名称即可
  params: [
    false.abiParameter(name: "msgBool"),
    300.abiParameter(name: "msgInt"),
    Data(bytes: [1, 2, 3]).abiParameter(name: "msgByteArray"),
    "string".abiParameter(name: "msgStr"),
    contract.abiParameter(name: "msgAddress"),
  ],
  contract: contract,
  gasPrice: "0",
  gasLimit: "30000000",
  payer: address1
)
try b.sign(tx: tx, prikey: prikey1!)

try! rpc!.send(rawTransaction: tx.serialize(), preExec: true).then {
  XCTAssertEqual("SUCCESS", $0["Desc"].string!)

  // 反序列化合约方法的调用返回值 
  let bool = Bool(hex: $0["Result", "Result", 0].string!)
  let int = Int(hex: $0["Result", "Result", 1].string!)
  let data = Data.from(hex: $0["Result", "Result", 2].string!)!
  let str = String(hex: $0["Result", "Result", 3].string!)!
  let addr = Data.from(hex: $0["Result", "Result", 4].string!)!
}
```

## 实例化 RPC 客户端

在进行 RPC 调用前，需要先对客户端进行实例化:

```swift
let rpc = WebsocketRpc(url: "ws://127.0.0.1:20335")!
rpc.open()
```

## 获取当前区块高度

```swift
rpc.getBlockHeight().then {
  print($0)
}
```

## 获取区块

```swift
rpc.getBlock(by: hash).then {
  print($0)
}

rpc.getBlock(by: height).then {
  print($0)
}
```

## 获得 block json 数据

```swift
rpc.getBlock(by: hash, json: true).then {
  print($0)
}
```

## 根据合约 hash 获得合约代码

```swift
rpc.getContract(by: hash, json: true).then {
  print($0)
}
```

## 查询余额

```swift
rpc.getBalance(address: addr).then {
  print($0)
}
```

## 获取区块链节点数

```swift
rpc.getNodeCount().then {
  print($0)
}
```

## 获得智能合约事件

```swift
rpc.getSmartCodeEvent(by: hash).then {
  print($0)
}

rpc.getSmartCodeEvent(by: height).then {
  print($0)
}
```

## 根据交易 hash 获得区块高度

```swift
rpc.getBlockHeight(by: hash).then {
  print($0)
}
```

## 获得 merkle proof

```swift
rpc.getMerkleProof(hash: hash).then {
  print($0)
}
```

## 根据交易 hash 获得交易 json 数据

```swift
rpc.getRawTransaction(txHash: hash, json: true).then {
  print($0)
}
```