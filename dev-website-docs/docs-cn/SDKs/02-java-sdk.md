
## 快速开始

```java
import com.github.ontio.OntSdk;

OntSdk ontSdk = OntSdk.getInstance();
```

## 账户

不同于比特币的 UTXO(Unspent Transaction Output) 模型，本体采用了账户余额模型。

### 创建随机账户

```java
import com.github.ontio.OntSdk;
import com.github.ontio.account.Account;

public class AcctDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = OntSdk.getInstance();
            Account acct = new Account(ontSdk.defaultSignScheme);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

### 指定私钥创建账户

在账户余额模型中，钱包地址由公钥生成经哈希运算得到。因此，你可以通过提供私钥来得到公钥，进而得到该私钥所对应的钱包地址。

```java
import com.github.ontio.account.Account;
import com.github.ontio.crypto.SignatureScheme;

public class AcctDemo {
    public static void main(String[] args) {
        try {
            String privatekey = "533c5fc274893831726f0bcb3634232f10b3beb1c05515058534577752a22d94";
            Account acct = new Account(Helper.hexToBytes(privatekey), SignatureScheme.SHA256WITHECDSA);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

### 批量创建账户

```java
import com.github.ontio.OntSdk;
import com.github.ontio.account.Account;

public class AcctDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = OntSdk.getInstance();
            ontSdk.getWalletMgr().createAccounts(10, "password");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

<p class="info">在技术上，公私钥可以存储在数据库中，也可以按照本体的钱包规范存储在 <code>Keystore</code> 文件中。</p>

## 身份

### 创建随机身份

```java
import com.github.ontio.OntSdk;
import com.github.ontio.account.Account;

public class AcctDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = OntSdk.getInstance();
            ontSdk.openWalletFile("wallet.dat");
            Identity identity = ontSdk.getWalletMgr().createIdentity("password");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

### 指定私钥创建身份

```java
import com.github.ontio.OntSdk;
import com.github.ontio.account.Account;

public class AcctDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = OntSdk.getInstance();
            ontSdk.openWalletFile("wallet.dat");
            String privateKey = "49855b16636e70f100cc5f4f42bc20a6535d7414fb8845e7310f8dd065a97221";
            Identity identity = ontSdk.getWalletMgr().createIdentityFromPriKey("password", privateKey);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

## 钱包文件

在 `ontology-java-sdk` 中，`WalletMgr` 类会根据本体的钱包规范帮你管理你的钱包账户和身份信息（本质上是对私钥的管理）。

### 创建账户

在 `WalletMgr` 类中，`createAccounts` 方法用于生成指定数量的随机账户。

```java
package demo;

import com.github.ontio.OntSdk;

public class WalletDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = OntSdk.getInstance();
            ontSdk.openWalletFile("WalletDemo.json");
            ontSdk.getWalletMgr().createAccounts(1, "password");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

### 保存钱包文件

在 `WalletMgr` 类中，`writeWallet` 方法用于将当前内存中的钱包信息保存到 `Keystore` 文件中。

```java
package demo;

import com.github.ontio.OntSdk;

public class WalletDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = OntSdk.getInstance();
            ontSdk.openWalletFile("WalletDemo.json");
            ontSdk.getWalletMgr().createAccounts(1, "password");
            ontSdk.getWalletMgr().writeWallet();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

### 重置钱包文件

在 `WalletMgr` 类中，`resetWallet` 方法用于重置 `Keystore` 文件。

```java
package demo;

import com.github.ontio.OntSdk;

public class WalletDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = OntSdk.getInstance();
            ontSdk.openWalletFile("WalletDemo.json");
            ontSdk.getWalletMgr().resetWallet();
            ontSdk.getWalletMgr().writeWallet();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

### 获取钱包信息

在 `WalletMgr` 类中，`getWallet` 方法用于查看钱包文件信息。

```java
package demo;

import com.github.ontio.OntSdk;
import com.github.ontio.sdk.wallet.Wallet;

public class WalletDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = OntSdk.getInstance();
            ontSdk.openWalletFile("WalletDemo.json");
            Wallet walletInMem = ontSdk.getWalletMgr().getWallet();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

### 获取账户信息列表

在 `WalletMgr` 类中，利用 `getWallet` 方法获得钱包文件信息后，可以使用 `getAccounts` 方法获取账户信息列表。

```java
package demo;

import java.util.List;

import com.github.ontio.OntSdk;
import com.github.ontio.sdk.wallet.Account;

public class WalletDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = OntSdk.getInstance();
            ontSdk.openWalletFile("WalletDemo.json");
            List<Account> accounts = ontSdk.getWalletMgr().getWallet().getAccounts();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

## 地址

在本体中，地址分为单签地址（由一个公钥生成）与多签地址（由多个公钥生成）。

### 生成单签地址

```java
package demo;

import java.util.List;

import com.github.ontio.OntSdk;
import com.github.ontio.common.Helper;
import com.github.ontio.account.Account;

public class WalletDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = OntSdk.getInstance();
            String privateKey = "c19f16785b8f3543bbaf5e1dbb5d398dfa6c85aaad54fc9d71203ce83e505c07";
            Account acct = new Account(Helper.hexToBytes(privateKey), ontSdk.defaultSignScheme);
            Address acctAddr = acct.getAddressU160();
            String b58Addr = acctAddr.toBase58();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

### 生成多签地址

```java
package demo;

import java.util.List;

import com.github.ontio.OntSdk;
import com.github.ontio.common.Helper;
import com.github.ontio.account.Account;

public class WalletDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = OntSdk.getInstance();
            String privateKey0 = "c19f16785b8f3543bbaf5e1dbb5d398dfa6c85aaad54fc9d71203ce83e505c07";
            String privateKey1 = "49855b16636e70f100cc5f4f42bc20a6535d7414fb8845e7310f8dd065a97221";
            String privateKey2 = "1094e90dd7c4fdfd849c14798d725ac351ae0d924b29a279a9ffa77d5737bd96";
            Account acct1 = new Account(Helper.hexToBytes(privateKey1), ontSdk.defaultSignScheme);
            Account acct2 = new Account(Helper.hexToBytes(privateKey2), ontSdk.defaultSignScheme);
            Account acct3 = new Account(Helper.hexToBytes(privateKey3), ontSdk.defaultSignScheme);
            Address multiAddr = Address.addressFromMultiPubKeys(2, acct1.serializePublicKey(), acct2.serializePublicKey(), acct3.serializePublicKey());
            String b58MultiAddr = multiAddr.toBase58();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

<section class="warning">
  <ul>
    <li>目前多重签名所支持的最大公钥数为 <code>16</code>。</li>
    <li>在多重签名中，需要使用公钥列表中的不同的账户对同一笔交易进行签名，一个账户签名后，返回的带签名交易需要作为下一个账户签名的输入，直到满足签名门限 <code>m</code>。</li>
  </ul>
</section>

## 原生资产

在对原生资产 `ONT` 与 `ONG` 进行操作前，需要将你的 SDK 连接到本体网络（主网、`polaris` 测试网、私有网络）。

```java
package demo;

import com.github.ontio.OntSdk;

public class MakeTxDemo {
    public static OntSdk getOntSdk() throws Exception {
        String restUrl = "http://polaris1.ont.io:20334";
        String rpcUrl = "http://polaris1.ont.io:20336";
        String wsUrl = "http://polaris1.ont.io:20335";

        OntSdk sdk = OntSdk.getInstance();
        sdk.setRpc(rpcUrl);
        sdk.setRestful(restUrl);
        sdk.setDefaultConnect(sdk.getRpc());
        return sdk;
    }
}
```

### 查询余额

```java
package demo;

import com.github.ontio.OntSdk;

public class MakeTxDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = getOntSdk();
            Object balance = ontSdk.getConnect().getBalance("AZW8eBkXh5qgRjmeZjqY2KFGLXhKcX4i2Y");
            long ontBalance = ontSdk.nativevm().ont().queryBalanceOf("AZW8eBkXh5qgRjmeZjqY2KFGLXhKcX4i2Y");
            long ongBalance = ontSdk.nativevm().ong().queryBalanceOf("AZW8eBkXh5qgRjmeZjqY2KFGLXhKcX4i2Y");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static OntSdk getOntSdk() throws Exception {
        String rpcUrl = "http://polaris1.ont.io:20336";

        OntSdk sdk = OntSdk.getInstance();
        sdk.setRpc(rpcUrl);
        sdk.setDefaultConnect(sdk.getRpc());
        return sdk;
    }
}
```

### 查询名称

```java
package demo;

import com.github.ontio.OntSdk;

public class MakeTxDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = getOntSdk();
            String ontName = ontSdk.nativevm().ont().queryName();
            String ongName = ontSdk.nativevm().ong().queryName();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static OntSdk getOntSdk() throws Exception {
        String rpcUrl = "http://polaris1.ont.io:20336";

        OntSdk sdk = OntSdk.getInstance();
        sdk.setRpc(rpcUrl);
        sdk.setDefaultConnect(sdk.getRpc());
        return sdk;
    }
}
```

### 查询符号

```java
package demo;

import com.github.ontio.OntSdk;

public class MakeTxDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = getOntSdk();
            String ontSymbol = ontSdk.nativevm().ont().querySymbol();
            String ongSymbol = ontSdk.nativevm().ong().querySymbol();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static OntSdk getOntSdk() throws Exception {
        String rpcUrl = "http://polaris1.ont.io:20336";

        OntSdk sdk = OntSdk.getInstance();
        sdk.setRpc(rpcUrl);
        sdk.setDefaultConnect(sdk.getRpc());
        return sdk;
    }
}
```

### 查询精度

```java
package demo;

import com.github.ontio.OntSdk;

public class MakeTxDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = getOntSdk();
            long ontDecimals = ontSdk.nativevm().ont().queryDecimals();
            long ongDecimals = ontSdk.nativevm().ong().queryDecimals();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static OntSdk getOntSdk() throws Exception {
        String rpcUrl = "http://polaris1.ont.io:20336";

        OntSdk sdk = OntSdk.getInstance();
        sdk.setRpc(rpcUrl);
        sdk.setDefaultConnect(sdk.getRpc());
        return sdk;
    }
}
```

### 查询总供应量

```java
package demo;

import com.github.ontio.OntSdk;

public class MakeTxDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = getOntSdk();
            long ontSupply = ontSdk.nativevm().ont().queryTotalSupply();
            long ongSupply = ontSdk.nativevm().ong().queryTotalSupply();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static OntSdk getOntSdk() throws Exception {
        String rpcUrl = "http://polaris1.ont.io:20336";

        OntSdk sdk = OntSdk.getInstance();
        sdk.setRpc(rpcUrl);
        sdk.setDefaultConnect(sdk.getRpc());
        return sdk;
    }
}
```

### 转账

```java
package demo;

import com.github.ontio.OntSdk;
import com.github.ontio.account.Account;

public class MakeTxDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = getOntSdk();
            String privatekey = "523c5fcf74823831756f0bcb3634234f10b3beb1c05595058534577752ad2d9f";
            Account acct = new Account(Helper.hexToBytes(privatekey), ontSdk.defaultSignScheme);
            String b58RecvAddr = "ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD";
            String txHash = ontSdk.nativevm().ont().sendTransfer(acct, b58RecvAddr, 1, acct, 200000, 500);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static OntSdk getOntSdk() throws Exception {
        String rpcUrl = "http://polaris1.ont.io:20336";

        OntSdk sdk = OntSdk.getInstance();
        sdk.setRpc(rpcUrl);
        sdk.setDefaultConnect(sdk.getRpc());
        return sdk;
    }
}
```

## 签名

### 交易签名

对交易做签名：
ontSdk.signTx(tx, new com.github.ontio.account.Account[][]{{acct0}});
//多签地址的签名方法：
ontSdk.signTx(tx, new com.github.ontio.account.Account[][]{{acct1, acct2}});
//如果转出方与网络费付款人不是同一个地址，需要添加网络费付款人的签名


发送预执行（可选）：
Object obj = ontSdk.getConnect().sendRawTransactionPreExec(tx.toHexString());
System.out.println(obj);
成功返回：
{"State":1,"Gas":30000,"Result":"01"}
余额不足返回异常：
com.github.ontio.network.exception.RestfulException: {"Action":"sendrawtransaction","Desc":"SMARTCODE EXEC ERROR","Error":47001,"Result":"","Version":"1.0.0"}


发送交易：
ontSdk.getConnect().sendRawTransaction(tx.toHexString());


同步发送交易：
Object obj = ontSdk.getConnect().syncSendRawTransaction(tx.toHexString());

response success:
{
	"GasConsumed": 0,
	"Notify": [],
	"TxHash": "cb9e0d4a7a4aea0518bb39409613b8ef76798df3962feb8f8040e05329674890",
	"State": 1
}

response fail,reject by txpool:
com.github.ontio.sdk.exception.SDKException: {"Action":"getmempooltxstate","Desc":"UNKNOWN TRANSACTION","Error":44001,"Result":"","Version":"1.0.0"}

```



| 方法名       | 参数                                                                                | 参数描述                                                           |
| :----------- | :---------------------------------------------------------------------------------- | :----------------------------------------------------------------- |
| makeTransfer | String sender，String recvAddr,long amount,String payer,long gaslimit,long gasprice | 发送方地址，接收方地址，金额，网络费付款人地址，gaslimit，gasprice |
| makeTransfer | State\[\] states,String payer,long gaslimit,long gasprice                           | 一笔交易包含多个转账。                                             |


#### **多次签名**

如果转出方与网络费付款人不是同一个地址，需要添加网络费付款人的签名

```java

1.添加单签签名
ontSdk.addSign(tx,acct0);

2.添加多签签名
ontSdk.addMultiSign(tx,2,new byte[][]{acct.serializePublicKey(),acct2.serializePublicKey()},acct);
ontSdk.addMultiSign(tx,2,new byte[][]{acct.serializePublicKey(),acct2.serializePublicKey()},acct2);

3.多签签名分多次签
acct0签名：
ontSdk.addMultiSign(tx,2,new byte[][]{acct.serializePublicKey(),acct2.serializePublicKey()},acct);

acct1签名：
ontSdk.addMultiSign(tx,2,new byte[][]{acct.serializePublicKey(),acct2.serializePublicKey()},acct2);

```



## 网络

| 接口                                                   | 描述                 |
| :----------------------------------------------------- | :------------------- |
| ontSdk.getConnect().getNodeCount()                     | 查询节点数量         |
| ontSdk.getConnect().getBlock(15)                       | 查询块               |
| ontSdk.getConnect().getBlockJson(15)                   | 查询块               |
| ontSdk.getConnect().getBlockJson("txhash")             | 查询块               |
| ontSdk.getConnect().getBlock("txhash")                 | 查询块               |
| ontSdk.getConnect().getBlockHeight()                   | 查询当前块高         |
| ontSdk.getConnect().getTransaction("txhash")           | 查询交易             |
| ontSdk.getConnect().getStorage("contractaddress", key) | 查询智能合约存储     |
| ontSdk.getConnect().getBalance("address")              | 查询余额             |
| ontSdk.getConnect().getContractJson("contractaddress") | 查询智能合约         |
| ontSdk.getConnect().getSmartCodeEvent(59)              | 查询智能合约事件     |
| ontSdk.getConnect().getSmartCodeEvent("txhash")        | 查询智能合约事件     |
| ontSdk.getConnect().getBlockHeightByTxHash("txhash")   | 查询交易所在高度     |
| ontSdk.getConnect().getMerkleProof("txhash")           | 查询 Merkle 证明     |
| ontSdk.getConnect().sendRawTransaction("txhexString")  | 发送交易             |
| ontSdk.getConnect().sendRawTransaction(Transaction)    | 发送交易             |
| ontSdk.getConnect().sendRawTransactionPreExec()        | 发送预执行交易       |
| ontSdk.getConnect().getAllowance("ont","from","to")    | 查询允许使用值       |
| ontSdk.getConnect().getMemPoolTxCount()                | 查询交易池中交易总量 |
| ontSdk.getConnect().getMemPoolTxState()                | 查询交易池中交易状态 |

## 查询交易池

根据交易哈希 `TxHash` 可以查询交易在交易池（内存）中的状态。

```java
package demo;

import com.github.ontio.OntSdk;
import com.github.ontio.account.Account;

public class NetworkDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = getOntSdk();
            String txHash = "d441a967315989116bf0afad498e4016f542c1e7f8605da943f07633996c24cc";
            Object txState = ontSdk.getConnect().getMemPoolTxState(txHash);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static OntSdk getOntSdk() throws Exception {
        String rpcUrl = "http://polaris1.ont.io:20336";

        OntSdk sdk = OntSdk.getInstance();
        sdk.setRpc(rpcUrl);
        sdk.setDefaultConnect(sdk.getRpc());
        return sdk;
    }
}
```

## 查询合约事件

- 根据交易哈希 `TxHash` 查询交易对应的合约事件。

```java
package demo;

import com.github.ontio.OntSdk;
import com.github.ontio.account.Account;

public class NetworkDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = getOntSdk();
            String txHash = "d441a967315989116bf0afad498e4016f542c1e7f8605da943f07633996c24cc";
            Object event = ontSdk.getConnect().getSmartCodeEvent(txHash);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static OntSdk getOntSdk() throws Exception {
        String rpcUrl = "http://polaris1.ont.io:20336";

        OntSdk sdk = OntSdk.getInstance();
        sdk.setRpc(rpcUrl);
        sdk.setDefaultConnect(sdk.getRpc());
        return sdk;
    }
}
```

- 轮询（每隔3秒请求一次，最长等待60秒）交易哈希 `TxHash` 查询交易对应的合约事件。

```java
package demo;

import com.github.ontio.OntSdk;
import com.github.ontio.account.Account;

public class NetworkDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = getOntSdk();
            String txHash = "d441a967315989116bf0afad498e4016f542c1e7f8605da943f07633996c24cc";
            Object event = ontSdk.getConnect().waitResult(txHash);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static OntSdk getOntSdk() throws Exception {
        String rpcUrl = "http://polaris1.ont.io:20336";

        OntSdk sdk = OntSdk.getInstance();
        sdk.setRpc(rpcUrl);
        sdk.setDefaultConnect(sdk.getRpc());
        return sdk;
    }
}
```

- 根据区块高度查询智能合约事件，返回对应区块中的所有事件。

```java
package demo;

import com.github.ontio.OntSdk;
import com.github.ontio.account.Account;

public class NetworkDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = getOntSdk();
            Object event = ontSdk.getConnect().getSmartCodeEvent(0);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static OntSdk getOntSdk() throws Exception {
        String rpcUrl = "http://polaris1.ont.io:20336";

        OntSdk sdk = OntSdk.getInstance();
        sdk.setRpc(rpcUrl);
        sdk.setDefaultConnect(sdk.getRpc());
        return sdk;
    }
}
```

## 查询 Merkle 证明

```java
package demo;

import com.github.ontio.OntSdk;
import com.github.ontio.account.Account;

public class NetworkDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = getOntSdk();
            Object event = ontSdk.getConnect().getMerkleProof(0);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static OntSdk getOntSdk() throws Exception {
        String rpcUrl = "http://polaris1.ont.io:20336";

        OntSdk sdk = OntSdk.getInstance();
        sdk.setRpc(rpcUrl);
        sdk.setDefaultConnect(sdk.getRpc());
        return sdk;
    }
}
```
 





 
#### **一转多或多转多**

1. 构造多个state的交易
2. 签名
3. 一笔交易上限为1024笔转账


```java

Address sender1 = acct0.getAddressU160();
Address sender2 = Address.addressFromMultiPubKeys(2, acct1.serializePublicKey(), acct2.serializePublicKey());
int amount = 10;
int amount2 = 20;

State state = new State(sender1, recvAddr, amount);
State state2 = new State(sender2, recvAddr, amount2);
Transaction tx = ontSdk.nativevm().ont().makeTransfer(new State[]{state1,state2},sender1.toBase58(),30000,0);

//第一个转出方是单签地址，第二个转出方是多签地址：
ontSdk.signTx(tx, new com.github.ontio.account.Account[][]{{acct0}});
ontSdk.addMultiSign(tx,2,new byte[][]{acct1.serializePublicKey(),acct2.serializePublicKey()},acct1);
ontSdk.addMultiSign(tx,2,new byte[][]{acct1.serializePublicKey(),acct2.serializePublicKey()},acct2);
```

#### 使用签名机签名

 **构造交易并签名**

1. 构造交易，序列化交易，发送交易给签名机
2. 签名机接收到交易，反序列化，检查交易，添加签名
3. 发送交易

```java

序列化交易发送给签名机：
Transaction tx = ontSdk.nativevm().ont().makeTransfer(sender.toBase58(),recvAddr.toBase58(), amount,sender.toBase58(),30000,0);
String txHex = tx.toHexString();

接收方反序列化交易并签名：

Transaction txRx = Transaction.deserializeFrom(Helper.hexToBytes(txHex));


签名：
ontSdk.addSign(txRx,acct0);
```

**SDK与签名机交互**：

[例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/SignServerDemo.java)

```java
节点启动时打开签名机服务：
go run SigSvr.go


设置签名机URL：
String url = ip + ":" + "20000/cli";
OntSdk ontSdk = OntSdk.getInstance();
ontSdk.setSignServer(url);
        

String txHex = tx.toHexString();

请求单签交易：
ontSdk.getSignServer().sendSigRawTx(txHex);
 
请求多签交易： 
String[] signs = new String[]{"02039b196d5ed74a4d771ade78752734957346597b31384c3047c1946ce96211c2a7",
                    "0203428daa06375b8dd40a5fc249f1d8032e578b5ebb5c62368fc6c5206d8798a966"};
ontSdk.getSignServer().sendMultiSigRawTx(txHex,2,signs);

请求构造转账交易并签名：
ontSdk.getSignServer().sendSigTransferTx("ont","TU5exRFVqjRi5wnMVzNoWKBq9WFncLXEjK","TA5SgQXTeKWyN4GNfWGoXqioEQ4eCDFMqE",10,30000,0);
            

```

 **对数据做签名**

SDK提供直接对数据做签名的接口。[例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/SignatureDemo.java) 


```java
com.github.ontio.account.Account acct = new com.github.ontio.account.Account(ontSdk.defaultSignScheme);

byte[] data = "12345".getBytes();
byte[] signature = ontSdk.signatureData(acct, data);

System.out.println(ontSdk.verifySignature(acct.serializePublicKey(), data, signature));

```



### 2.5 ONG转账

ONG转账方法与ONT转账类似，但ONG的精度是9。
####  **ONG转账**


```json
ontSdk.nativevm().ong().makeTransfer(sender.toBase58(),recvAddr.toBase58(), amount,sender.toBase58(),30000,0);
```

####  **提取ong**

1. 查询是否有ong可以提取
2. 发送提取ong交易

```json
查询未提取ong:
String addr = acct0.getAddressU160().toBase58();
String ong = sdk.nativevm().ong().unboundOng(addr);

//提取ong
com.github.ontio.account.Account account = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey0), ontSdk.signatureScheme);
String hash = sdk.nativevm().ong().withdrawOng(account,toAddr,64000L,payerAcct,30000,500);

```



## 3. 批量交易

SDK发送注册Ontid和转账等交易时，根据钱包中账户和身份信息解密出私钥再做签名，这个过程大概需要1-2秒时间。为了节省发交易时间，可以多线程或多机器事先创建交易，再批量发送。

实现步骤如下，[例子](https://github.com/ontio/ontology-java-sdk/tree/master/src/main/java/demo/CreateManyTx.java)

### 3.1 批量构造交易

1. 打开文件
2. 构造交易，下面以构造注册Ontid交易为例。
3. 写入交易

> 构造交易时，如果新创建账户，需要用户自己保存账户私钥。

```
//open file, make registry ontid transaction, save tx to file.
File file = new File(filePath);
if (!file.exists()) {
    file.createNewFile();
}
com.github.ontio.account.Account payerAcct = new com.github.ontio.account.Account(Helper.hexToBytes(privatekey1), SignatureScheme.SHA256WITHECDSA);
FileOutputStream fos = new FileOutputStream(file);
for (int i = 0; i < 3; i++) {
    com.github.ontio.account.Account account = new com.github.ontio.account.Account(SignatureScheme.SHA256WITHECDSA);
    String ontid = Common.didont + account.getAddressU160().toBase58();
    Transaction tx = ontSdk.nativevm().ontId().makeRegister(ontid, Helper.toHexString(account.serializePublicKey()), payerAcct.getAddressU160().toBase58(), 20000, 500);
    ontSdk.addSign(tx, account);
    ontSdk.addSign(tx, payerAcct);
    System.out.println("PrivateKey:"+Helper.toHexString(account.serializePrivateKey())+",txhash:"+tx.hash().toString());

    fos.write(tx.toHexString().getBytes());
    fos.write(",".getBytes());
    fos.write(tx.hash().toString().getBytes());
    fos.write("\n".getBytes());
}


```
文件中数据格式：

```
交易，交易hash
交易，交易hash

00d1df24a313f401000000000000204e000000000000aa6e06c79f864152ab7f3139074aad822ffea8559800c66b2a6469643a6f6e743a414774577a7933693148453654516e31633265636b78527841516d524662467333686a7cc821036391476eed630fc1cffb1317545d9390f22d68cdc7092095dc1b78e4baeef27c6a7cc86c127265674944576974685075626c69634b65791400000000000000000000000000000000000000030068164f6e746f6c6f67792e4e61746976652e496e766f6b6500024241011928500aa1ac40d908e92c9db7c16be4063dda2cdabe9908206747c6303635578fde0be66032f586596e91c80f490a085e612be28b95da0edb319cb60f774e472321036391476eed630fc1cffb1317545d9390f22d68cdc7092095dc1b78e4baeef27cac424101bb1df17b91cd709ce38b4ec40db10c2dfd5e9ca7219dd5ca1c6200eaf60d8ccf1be9b85b9b22398204c6366ac20e8bb7797f21ebc17e7db540627b99d5a8bb41232102df6f28e327352a44720f2b384e55034c1a7f54ba31785aa3a338f613a5b7cc26ac,b7e2c99f449cb3403619bc5c5887c52f44993180c61c9fae85d5e772ce3d7fda
00d1039e89c7f401000000000000204e000000000000aa6e06c79f864152ab7f3139074aad822ffea8559800c66b2a6469643a6f6e743a416446335547344867515864515a5577714a53756536744a6f534e564237644d32596a7cc82102a1f44af3d81c6cb0aaa5e1d597b891c436b0c724ae446b5d9cb9039e09b9938c6a7cc86c127265674944576974685075626c69634b65791400000000000000000000000000000000000000030068164f6e746f6c6f67792e4e61746976652e496e766f6b65000242410168436b2f5da6db0b2b4260b587ba7bce3dba1597a400dec52d0f00a4aa77f37c9979d10c31a80888edd6a41da4c89596033ab9ee634886f26850b32e83681f4e232102a1f44af3d81c6cb0aaa5e1d597b891c436b0c724ae446b5d9cb9039e09b9938cac4241019ba8633b42d3427ab202cafcb1c50a65de30c65120a96d958f985aff7205fcc6230e64842ea5cdf4e6b2d0b8bef1b19c795bf392a0c1cc8a93bc9ec9bebc9a35232102df6f28e327352a44720f2b384e55034c1a7f54ba31785aa3a338f613a5b7cc26ac,a8bd8258c8819f0ecf0652bb1d8c08860a5b75d16e194f3d6cd395f5c2a9f7fe
00d1554170d9f401000000000000204e000000000000aa6e06c79f864152ab7f3139074aad822ffea8559800c66b2a6469643a6f6e743a41547a4d6e79556d42614369686355556872786472566d437173336d73426351685a6a7cc8210274af46f5f038d040e5096f4653df4e7ea5598567effe4542ad6f19cda6ea05846a7cc86c127265674944576974685075626c69634b65791400000000000000000000000000000000000000030068164f6e746f6c6f67792e4e61746976652e496e766f6b650002424101ea9d7dedf17ecfef8d1d03f4d00b819c16fab8275b5d77d811a1db8140d25722fc2200a60ea76e5a449cce4e127ceec73377cce1b227c624b8df9f95be55bf4123210274af46f5f038d040e5096f4653df4e7ea5598567effe4542ad6f19cda6ea0584ac424101e401877fc4892212a309b7de30d5d9dd675a7171f89d945fe44c3b9eba46df2c2966f54fefdf5eabfa651acf63332cf9475868aa3055531a97a1fffbd43b09b8232102df6f28e327352a44720f2b384e55034c1a7f54ba31785aa3a338f613a5b7cc26ac,bd888014a82cec39f72400e4b8c43e46702bd96a16172b144361cb7b3bc024f4

```

### 3.2 批量发送交易

1. 打开文件
2. 读取一行数据
3. 提取交易数据，发送交易数据

```
//read transaction from file, send transaction to node
FileReader fr = new FileReader(filePath);
BufferedReader bf = new BufferedReader(fr);
String txHex = null;
while ((txHex=bf.readLine())!=null){
    txHex = txHex.split(",")[0];
    Object obj = ontSdk.getConnect().sendRawTransactionPreExec(txHex);//change to sendRawTransaction
    System.out.println(obj);
}


```