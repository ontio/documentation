
## 1. 快速开始

```java
import com.github.ontio.OntSdk;

OntSdk ontSdk = OntSdk.getInstance();
```

## 2. 网络

| 接口                                                | 描述                 |
| :-------------------------------------------------- | :------------------- |
| ontSdk.getConnect().getNodeCount()                  | 查询节点数量         |
| ontSdk.getConnect().getBlock()                      | 查询块               |
| ontSdk.getConnect().getBlockJson()                  | 查询块               |
| ontSdk.getConnect().getBlockHeight()                | 查询当前块高         |
| ontSdk.getConnect().getTransaction()                | 查询交易             |
| ontSdk.getConnect().getStorage()                    | 查询智能合约存储     |
| ontSdk.getConnect().getBalance()                    | 查询余额             |
| ontSdk.getConnect().getContractJson()               | 查询智能合约         |
| ontSdk.getConnect().getSmartCodeEvent()             | 查询智能合约事件     |
| ontSdk.getConnect().getBlockHeightByTxHash()        | 查询交易所在高度     |
| ontSdk.getConnect().getMerkleProof()        | 查询 Merkle 证明     |
| ontSdk.getConnect().sendRawTransaction()            | 发送交易             |
| ontSdk.getConnect().sendRawTransactionPreExec()     | 发送预执行交易       |
| ontSdk.getConnect().getAllowance() | 查询允许使用值       |
| ontSdk.getConnect().getMemPoolTxCount()             | 查询交易池中交易总量 |
| ontSdk.getConnect().getMemPoolTxState()             | 查询交易池中交易状态 |

### 2.1 交易池

根据交易哈希 `TxHash` 可以查询交易在交易池（内存）中的状态。

```java
package demo;

import com.github.ontio.OntSdk;
import com.github.ontio.account.Account;

public class NetworkDemo {
    public static void main(String[] args) {
        try {
            String rpcUrl = "http://polaris1.ont.io:20336";
            OntSdk sdk = OntSdk.getInstance();
            sdk.setRpc(rpcUrl);
            sdk.setDefaultConnect(sdk.getRpc());
            String txHash = "d441a967315989116bf0afad498e4016f542c1e7f8605da943f07633996c24cc";
            Object txState = ontSdk.getConnect().getMemPoolTxState(txHash);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

### 2.2 合约事件

- 根据交易哈希 `TxHash` 查询交易对应的合约事件。

```java
package demo;

import com.github.ontio.OntSdk;
import com.github.ontio.account.Account;

public class NetworkDemo {
    public static void main(String[] args) {
        try {
            String rpcUrl = "http://polaris1.ont.io:20336";
            OntSdk sdk = OntSdk.getInstance();
            sdk.setRpc(rpcUrl);
            sdk.setDefaultConnect(sdk.getRpc());
            String txHash = "d441a967315989116bf0afad498e4016f542c1e7f8605da943f07633996c24cc";
            Object event = ontSdk.getConnect().getSmartCodeEvent(txHash);
        } catch (Exception e) {
            e.printStackTrace();
        }
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
            String rpcUrl = "http://polaris1.ont.io:20336";
            OntSdk sdk = OntSdk.getInstance();
            sdk.setRpc(rpcUrl);
            sdk.setDefaultConnect(sdk.getRpc());
            String txHash = "d441a967315989116bf0afad498e4016f542c1e7f8605da943f07633996c24cc";
            Object event = ontSdk.getConnect().waitResult(txHash);
        } catch (Exception e) {
            e.printStackTrace();
        }
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
            String rpcUrl = "http://polaris1.ont.io:20336";
            OntSdk sdk = OntSdk.getInstance();
            sdk.setRpc(rpcUrl);
            sdk.setDefaultConnect(sdk.getRpc());
            Object event = ontSdk.getConnect().getSmartCodeEvent(0);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

### 2.3 Merkle 证明

`getMerkleProof` 接口用于获取指定交易哈希所对应交易的 `Merkle` 证明。

```java
package demo;

import com.github.ontio.OntSdk;
import com.github.ontio.account.Account;

public class NetworkDemo {
    public static void main(String[] args) {
        try {
            String rpcUrl = "http://polaris1.ont.io:20336";
            OntSdk sdk = OntSdk.getInstance();
            sdk.setRpc(rpcUrl);
            sdk.setDefaultConnect(sdk.getRpc());
            String txHash = "65d3b2d3237743f21795e344563190ccbe50e9930520b8525142b075433fdd74";
            Object proof = ontSdk.getConnect().getMerkleProof(txHash);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

<div align="center"><img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/SDKs/merkle-tree.png" width="620px"></div>

<p class = "info">由于 <code>Merkle</code> 树的结构特征，通过使用默克尔证明技术，能够快速判断特定数据是否存在于默克尔树之中。</p>

## 3. 账户

不同于比特币的 `UTXO` (Unspent Transaction Output) 模型，本体采用了账户余额模型。

### 3.1 创建随机账户

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

### 3.2 指定私钥创建账户

在账户余额模型中，钱包地址由公钥生成,经哈希运算得到。因此，你可以通过提供私钥来得到公钥，进而得到该私钥所对应的钱包地址。

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

### 3.3 批量创建账户

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

## 4. 身份

### 4.1 创建随机身份

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

### 4.2 指定私钥创建身份

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

## 5. 钱包文件

在 `ontology-java-sdk` 中，`WalletMgr` 类会根据本体的钱包规范帮你管理你的钱包账户和身份信息（本质上是对私钥的管理）。

### 5.1 创建账户

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

### 5.2 保存钱包文件

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

### 5.3 重置钱包文件

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

### 5.4 获取钱包信息

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

### 5.5 获取账户信息列表

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

## 6. 地址

在本体中，地址分为单签地址（由一个公钥生成）与多签地址（由多个公钥生成）。

### 6.1 生成单签地址

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

### 6.2 生成多签地址

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

## 7. 原生资产

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

### 7.1 查询余额

```java
package demo;

import com.github.ontio.OntSdk;

public class MakeTxDemo {
    public static void main(String[] args) {
        try {
            OntSdk sdk = OntSdk.getInstance();
            String rpcUrl = "http://polaris1.ont.io:20336";
            sdk.setRpc(rpcUrl);
            sdk.setDefaultConnect(sdk.getRpc());
            Object balance = ontSdk.getConnect().getBalance("AZW8eBkXh5qgRjmeZjqY2KFGLXhKcX4i2Y");
            long ontBalance = ontSdk.nativevm().ont().queryBalanceOf("AZW8eBkXh5qgRjmeZjqY2KFGLXhKcX4i2Y");
            long ongBalance = ontSdk.nativevm().ong().queryBalanceOf("AZW8eBkXh5qgRjmeZjqY2KFGLXhKcX4i2Y");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}
```

### 7.2 查询名称

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

### 7.3 查询符号

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

### 7.4 查询精度

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

### 7.5 查询总供应量

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

### 7.6 转账

```java
package demo;

import com.github.ontio.OntSdk;
import com.github.ontio.account.Account;

public class MakeTxDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = OntSdk.getInstance();
            String rpcUrl = "http://polaris1.ont.io:20336";
            ontSdk.setRpc(rpcUrl);
            ontSdk.setDefaultConnect(ontSdk.getRpc());

            String privatekey = "523c5fcf74823831756f0bcb3634234f10b3beb1c05595058534577752ad2d9f";
            Account acct = new Account(Helper.hexToBytes(privatekey), ontSdk.defaultSignScheme);
            String b58RecvAddr = "ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD";
            String txHash = ontSdk.nativevm().ont().sendTransfer(acct, b58RecvAddr, 1, acct, 200000, 500);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

```java
package demo;

import com.github.ontio.OntSdk;
import com.github.ontio.account.Account;

public class MakeTxDemo {
    public static void main(String[] args) {
        try {
            OntSdk ontSdk = OntSdk.getInstance();
            String rpcUrl = "http://polaris1.ont.io:20336";
            ontSdk.setRpc(rpcUrl);
            ontSdk.setDefaultConnect(ontSdk.getRpc());

            String addr0 = "AXK2KtCfcJnSMyRzSwTuwTKgNrtx5aXfFX";
            String addr1 = "AVXf5w8WD2y6jV1Lzi36oSKYNif1C7Surc";
            Account acct0 = ontSdk.getWalletMgr().getAccount(addr0, "password");
            Account acct1 = ontSdk.getWalletMgr().getAccount(addr1, "password");

            State state1 = new State(acct0.getAddressU160(), acct1.getAddressU160(), 1);
            State state2 = new State(acct0.getAddressU160(), acct1.getAddressU160(), 2);
            Transaction tx = ontSdk.nativevm().ont().makeTransfer(new State[]{state1, state2}, addr0, 30000, 0);
            ontSdk.signTx(tx, new Account[][]{{acct0}});
            ontSdk.getConnect().sendRawTransaction(tx.toHexString());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

!> 一笔交易所包含的转账交易数上限为 1024 笔。

## 8. 签名

### 8.1 交易签名

```java
package demo;

import com.github.ontio.OntSdk;
import com.github.ontio.account.Account;
import com.github.ontio.core.transaction.Transaction;

public class MakeTxDemo {
    public static void main(String[] args) {
        try {
            OntSdk sdk = OntSdk.getInstance();
            String rpcUrl = "http://polaris1.ont.io:20336";
            ontSdk.setRpc(rpcUrl);
            ontSdk.setDefaultConnect(ontSdk.getRpc());

            String addr0 = "AXK2KtCfcJnSMyRzSwTuwTKgNrtx5aXfFX";
            String addr1 = "AVXf5w8WD2y6jV1Lzi36oSKYNif1C7Surc";
            String addr2 = "ARPBSDcPTRQbh1cHNKJ7UTRNTd2riucrMJ";
            Account acct0 = ontSdk.getWalletMgr().getAccount(addr0, "password");
            Account acct1 = ontSdk.getWalletMgr().getAccount(addr1, "password");
            Account acct2 = ontSdk.getWalletMgr().getAccount(addr2, "password");
            Transaction tx = ontSdk.nativevm().ont().makeTransfer(addr0, addr1, 1, addr2, 200000, 500);
            ontSdk.signTx(tx, new Account[][]{{acct0}, {acct2}});
            ontSdk.getConnect().sendRawTransaction(tx.toHexString());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

### 8.2 增加交易签名

```java
package demo;

import com.github.ontio.OntSdk;
import com.github.ontio.account.Account;
import com.github.ontio.core.transaction.Transaction;

public class MakeTxDemo {
    public static void main(String[] args) {
        try {
            OntSdk sdk = OntSdk.getInstance();
            String rpcUrl = "http://polaris1.ont.io:20336";
            ontSdk.setRpc(rpcUrl);
            ontSdk.setDefaultConnect(ontSdk.getRpc());

            String addr0 = "AXK2KtCfcJnSMyRzSwTuwTKgNrtx5aXfFX";
            String addr1 = "AVXf5w8WD2y6jV1Lzi36oSKYNif1C7Surc";
            String addr2 = "ARPBSDcPTRQbh1cHNKJ7UTRNTd2riucrMJ";
            Account acct0 = ontSdk.getWalletMgr().getAccount(addr0, "password");
            Account acct1 = ontSdk.getWalletMgr().getAccount(addr1, "password");
            Account acct2 = ontSdk.getWalletMgr().getAccount(addr2, "password");
            Transaction tx = ontSdk.nativevm().ont().makeTransfer(addr0, addr1, 1, addr2, 200000, 500);
            ontSdk.signTx(tx, new Account[][]{{acct0}});
            ontSdk.addSign(tx, acct1);
            ontSdk.getConnect().sendRawTransaction(tx.toHexString());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

!> 如果转出账户的地址和网络费支付账户的地址不同，需要在交易中添加转出账户与网络费支付账户的签名。

### 8.3 多签交易签名

```java
package demo;

import com.github.ontio.OntSdk;
import com.github.ontio.account.Account;
import com.github.ontio.core.transaction.Transaction;

public class MakeTxDemo {
    public static void main(String[] args) {
        try {
            OntSdk sdk = OntSdk.getInstance();
            String rpcUrl = "http://polaris1.ont.io:20336";
            ontSdk.setRpc(rpcUrl);
            ontSdk.setDefaultConnect(ontSdk.getRpc());

            String addr0 = "AXK2KtCfcJnSMyRzSwTuwTKgNrtx5aXfFX";
            String addr1 = "AVXf5w8WD2y6jV1Lzi36oSKYNif1C7Surc";
            String addr2 = "ARPBSDcPTRQbh1cHNKJ7UTRNTd2riucrMJ";
            Account acct0 = ontSdk.getWalletMgr().getAccount(addr0, "password");
            Account acct1 = ontSdk.getWalletMgr().getAccount(addr1, "password");
            Account acct2 = ontSdk.getWalletMgr().getAccount(addr2, "password");
            byte[] pubKey0 = acct0.serializePublicKey();
            byte[] pubKey1 = acct1.serializePublicKey();
            byte[][] pks = {pubKey0, pubKey1};
            String multiAddr = Address.addressFromMultiPubKeys(2, pubKey0, pubKey1).toBase58();

            Transaction tx = ontSdk.nativevm().ont().makeTransfer(multiAddr, addr2, 1, addr2, 200000, 500);

            ontSdk.addMultiSign(tx, 2, pks, acct0);
            ontSdk.addMultiSign(tx, 2, pks, acct1);
            ontSdk.addSign(tx, acct2);

            ontSdk.getConnect().sendRawTransaction(tx.toHexString());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

### 8.4 数据签名

```java
package demo;

import com.github.ontio.OntSdk;
import com.github.ontio.account.Account;

public class MakeTxDemo {
    public static void main(String[] args) {
        try {
            OntSdk sdk = OntSdk.getInstance();
            Account acct = new Account(ontSdk.defaultSignScheme);

            byte[] data = "text".getBytes();
            byte[] signature = ontSdk.signatureData(acct, data);

            ontSdk.verifySignature(acct.serializePublicKey(), data, signature);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```
