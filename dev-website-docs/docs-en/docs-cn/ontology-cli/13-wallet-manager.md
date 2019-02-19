
本体客户端 `Ontology-CLI` 提供了钱包管理模块，可以在命令行中通过 `account` 命令实现：

- 对钱包账户的增加、删除、查看、修改。
- 对钱包账户的导入导出。

此外，你可以通过 `help` 命令获取钱包管理模块的帮助信息 。

```shell
ontology account help
```

## 签名算法

本体客户端 `Ontology-CLI` 支持 `ECDSA`、`SM2` 以及 `ED25519` 三类签名算法。

<table cellspacing=0>
    <tr>
        <td align="center" style=min-width:50px>签名分类</td>
        <td align="center" style=min-width:50px>密钥曲线</td>
        <td align="center" style=min-width:50px>密钥长度</td>
        <td align="center" style=min-width:50px>签名算法</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px rowspan="8">ECDSA</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>NIST P-224</td>
        <td align="center" style=min-width:50px>224 bit</td>
        <td align="center" style=min-width:50px>SHA224withECDSA</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>NIST P-256</td>
        <td align="center" style=min-width:50px>256 bit</td>
        <td align="center" style=min-width:50px>SHA256withECDSA</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>NIST P-384</td>
        <td align="center" style=min-width:50px>384 bit</td>
        <td align="center" style=min-width:50px>SHA384withECDSA</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px rowspan="4">NIST P-521</td>
        <td align="center" style=min-width:50px rowspan="4">521 bit</td>
        <td align="center" style=min-width:50px>SHA224withEdDSA</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>SHA256withEdDSA</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>SHA384withEdDSA</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>SHA512withEdDSA</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>SM2</td>
        <td align="center" style=min-width:50px>sm2p256v1</td>
        <td align="center" style=min-width:50px>256 bit</td>
        <td align="center" style=min-width:50px>SM3withSM2</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>Ed25519</td>
        <td align="center" style=min-width:50px>Curve25519</td>
        <td align="center" style=min-width:50px>256 bit</td>
        <td align="center" style=min-width:50px>SHA512withEdDSA</td>
    </tr>
</table>

要了解更多关于ECDSA 密钥曲线的信息，可以访问 [NIST Digital Signature Standard (FIPS 186-3)](https://csrc.nist.gov/csrc/media/publications/fips/186/3/archive/2009-06-25/documents/fips_186-3.pdf)。

## 创建账户

要创建账户，使用 `add` 命令：

```shell
ontology account add
```

在添加账户的过程中，你需要按照提示选择签名算法、密钥曲线、签名模式。

使用 `-d` 选项可以使用默认选项快速创建账户：

```shell
ontology account add -d
```

要快速创建多个账户，使用 `-n` 选项：

```shell
ontology account add -n 5 -d
```

<p class="warning">
<ul>
<li>每个 <code>Keystore</code> 文件都应该有一个默认账户，一般情况下是第一个添加的账户，可以使用 <code>list</code> 命令查看默认账户。
<pre v-pre="" data-lang="shell"><code class="lang-shell">ontology account list</code></pre>
</li>
<li>默认账户不能被删除，可以通过 <code>set</code> 命令的 <code>-d</code> 选项来修改默认账户。
<pre v-pre="" data-lang="shell"><code class="lang-shell">ontology account <span class="token keyword">set</span> -d 2</code></pre>
</li>
</ul>
</p>

在账户管理模块中， `add` 命令所支持的选项如下表所示，也可以通过 `--help` 选项获取帮助信息。

```shell
ontology account add --help
```

|            选项            |            描述            |
| :------------------------: | :------------------------: |
|       `--type`, `-t`       |        指定签名算法        |
|    `--bit-length`, `-b`    |        指定密钥长度        |
| `--signature-scheme`, `-s` |        指定签名方案        |
|     `--default`, `-d`      | 使用默认的签名方案创建账户 |
|         `--label`          |   给新建账户设置账户标签   |
|         `--wallet`         |  指定 `Keystore` 文件路径  |
|      `--number`, `-n`      |   指定需要创建的账户数量   |

> **注意**：
>
> - 同一个 `Keystore` 文件下，不能出现重复的账户标签。
> - 未设置账户标签的账户为空字符串。
> - 如果使用 `--wallet` 选项指定的 `Keystore` 文件不存在，会自动创建一个新的 `Keystore` 文件。

## 创建 ONT ID

`add` 命令也可以用于创建 `ONT ID`，只需要添加 `--ontid` 选项即可：

```shell
ontology account add --ontid
```

在添加 `ONT ID` 的过程中，需要按照提示选择签名算法、密钥曲线、签名模式。

使用 `-d` 选项可以使用默认选项快速创建 `ONT ID`：

```shell
ontology account add --ontid -d
```

## 查看账户

要查看 `Keystore` 文件中的账户列表，使用 `list` 命令：

```shell
ontology account list
```

要查看更多信息，使用 `--verbose` 或 `-v` 选项：

```shell
ontology account list --verbose
```

> **注意**：
> - 账户在钱包中的索引  `Index`  从 1 开始。
> - `default` 对应的账户为默认账户。
> - 客户端 `Ontology-CLI` 支持通过索引 `Index`、账户地址 `Address` 以及非空账户标签 `Label` 来查找账户。

在账户管理模块中，`list` 命令所支持的选项如下表所示，也可以通过 `--help` 选项获取帮助信息。

```shell
ontology account list --help
```

|     选项      |                  描述                   |
| :-----------: | :-------------------------------------: |
| `--wallet`, `-w` |         指定 `Keystore` 文件         |
| `--verbose`, `-v` | 显示 `Keystore` 文件中账户的详细信息 |

## 修改账户

要对账户进行修改，使用`set` 命令：

```shell
ontology account set
```

在账户管理模块中，`set` 命令所支持的选项如下表所示，也可以通过 `--help` 选项获取帮助信息。

|        选项        |               描述                |
| :----------------: | :-------------------------------: |
|  `--as-default`, -d  |         指定默认账户          |
|    `--wallet`, `-w`    | 指定默认 `Keystore` 文件的路径 |
|  `--label`, `-l`   |      给账户设置新的标签       |
|  `--change-passwd` |         修改账户密码          |
| `--signature-scheme` |         修改签名算法          |

> **注意**：
>
> - 默认的钱包路径为 `./wallet.dat`。
> - 同一个`Keystore` 文件中，不能有两个相同的钱包标签。

## 删除账户

要删除（非默认）账户，使用`del` 命令：

```shell
ontology account del 2
ontology account del acct
ontology account del AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa
```

> 未备份的账户删除后将无法恢复，请谨慎操作。

## 导出账户

要导出钱包账户生成 `Keystore` 文件，使用`export` 命令：

```shell
ontology account export ./export_wallet.dat
```

在账户管理模块中，`export` 命令所支持的选项如下表所示，也可以通过 `--help` 选项获取帮助信息。

|       选项       |                     描述                     |
| :--------------: | :------------------------------------------: |
| `--wallet`, `-w` |                 指定导出钱包                 |
| `--low-security` | 降低导出 `Keystore` 文件中的账户保护安全等级 |

!> 如果不是出于特殊需要，如为了将 `Keystore` 文件导入到低性能设备当中，请勿使用 `--low-security` 选项。

## 导入账户

在账户管理模块中，`import` 命令用于将 `Keystore` 文件导入到钱包账户之中。

|      选项       |                    描述                    |
| :-------------: | :----------------------------------------: |
| `--wallet`, `w` | 用于指定接收导入钱包账户的 `Keystore` 文件 |
| -`-source`,`s`  |  用于指定被导入钱包账户的 `Keystore` 文件  |
|     `--wif`     |   用于指定被导入导入钱包账户的 WIF 文件    |

```shell
ontology account import -s ./export_wallet.dat
```

如果需要通过 `WIF` 导入钱包账户，你首先需要将52位的 `WIF` 文本保存到一个文件中，如 `wif`，然后使用如下命令导入。

```shell
ontology account import --wif ./wif
```

!> 请在导入完成后彻底清除设备中的 `WIF` 文件或将其置于安全的位置。

## 常见问题

- 什么是明文私钥？

  明文私钥是由（伪）随机数生成的，用来解锁对应钱包的一串字符。在交易场景下, 私钥用于生成交易所必须的签名，以证明资产的所有权。任何具有明文私钥的人，就能控制该私钥所对应的钱包账户。

- 什么是 WIF？
  
  WIF（Wallet Import Format）是将明文私钥以 Base58 校验和编码格式显示的钱包导入格式。WIF和私钥可以互转，因此也理解为是另一种形式的明文私钥。任何具有 WIF 的人，就能控制该 WIF 所对应的钱包账户。

- 什么是 Keystore？
  
  Keystore 允许你以加密的方式存储私钥。私钥被自定义密码所加密，一旦忘记密码, 就失去了对 Keystore 的使用权。因此，一定要妥善保管好 Keystore 以及密码。

- 什么是助记词？
  
  助记词是私钥的另一种表现形式。最早是由 BIP39 提案提出, 其目的是为了帮助用户记忆复杂的私钥字符串。助记词一般由 12、15、18、21 个单词构成, 这些单词都取自一个固定词库, 其生成顺序也是按照一定算法而来。

- 什么是 ONT ID？

  ONT ID 是现实世界中的实体（个人、组织、物品、内容等）在区块链上的身份标识。每⼀个 ONT ID 都对应着一个在区块链上的 ONT ID 描述对象（ONT DDO），用于记录 ONT ID 的控制人、公钥列表、属性对象和恢复人地址信息。

  本质上，ONT ID 是一种统一资源标识符（URL），由每个实体自己生成（生成算法需要保证极低的碰撞率），并向区块链网络进行注册（共识节点负责检查是否已被注册）。
