
本体客户端 `Ontology-CLI` 提供了钱包管理模块，可以在命令行中通过 `account` 命令使用。

- 对钱包账户的增加、删除、查看、修改。
- 对钱包文件的导入导出。

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

> 如果你想要了解更多关于ECDSA 密钥曲线的信息，可以访问 [NIST Digital Signature Standard (FIPS 186-3)](https://csrc.nist.gov/csrc/media/publications/fips/186/3/archive/2009-06-25/documents/fips_186-3.pdf) 获取。

## 创建账户

账户管理模块中，`add` 命令用于添加账户。

```shell
ontology account add
```

在添加账户的过程中，你需要按照提示选择签名算法、密钥曲线、签名模式。

你也可以使用 `-d` 选项使用默认选项快速创建账户。

```shell
ontology account add -d
```

如果你需要快速创建多个账户，你可以使用 `-n` 选项。

```shell
ontology account add -n 5 -d
```

> **注意**：
> - 每个钱包文件都应该有一个默认账户，一般情况下是第一个添加的账户，你可以使用 `list` 命令查看默认账户。
>```shell
>ontology account list
>```
> - 默认账户不能被删除，可以通过 `set` 命令的 `-d` 选项来修改默认账户。
>```shell
>ontology account set -d 2
>```

如果你需要快速创建多个 `ONT ID`，你可以使用 `-n` 选项。

```shell
ontology account add -n 5 -d
```

在账户管理模块中， `add` 命令中所支持的选项如下表所示，你可以通过 `--help` 选项获取帮助信息。

```shell
ontology account add --help
```

|          选项          |            描述            |
| :--------------------: | :------------------------: |
|       --type, -t       |      用于指定签名算法      |
|    --bit-length, -b    |      用于指定密钥长度      |
| --signature-scheme, -s |      用于指定签名方案      |
|     --default, -d      | 使用默认的签名方案创建账户 |
|        --label         | 用于给新建账户设置账户标签 |
|        --wallet        |    用于指定钱包文件路径    |
|        --number        | 用于指定需要创建的账户数量 |

> **注意**：
> - 同一个钱包文件下，不能出现重复的账户标签。
> - 未设置账户标签的账户为空字符串。
> - 如果使用 `--wallet` 选项指定的钱包文件不存在，会自动创建一个新的钱包文件。

## 创建 ONT ID

账户管理模块中的 `add` 命令也可以用于创建 `ONT ID`，只需要添加 `--ontid` 选项即可。

```shell
ontology account add --ontid
```

在添加 `ONT ID` 的过程中，你需要按照提示选择签名算法、密钥曲线、签名模式。

你也可以使用 `-d` 选项使用默认选项快速创建 `ONT ID`。

```shell
ontology account add --ontid -d
```

## 查看账户

账户管理模块中，`list` 命令用于查看钱包文件中的账户列表。

```shell
ontology account list
```

如果你想查看更多信息，你可以使用 `--verbose` 或 `-v` 选项。

```shell
ontology account list --verbose
```

> **注意**：
> - 账户在钱包中的索引 `Index` 从1开始。
> - `default` 对应的账户未默认账户。
> - 客户端 `Ontology-CLI` 支持通过索引 `Index`、账户地址 `Address` 以及非空账户标签 `Label` 来查找账户。

在账户管理模块中，`list` 命令中所支持的选项如下表所示，你可以通过 `--help` 选项获取帮助信息。

```shell
ontology account list --help
```

|     选项      |               描述               |
| :-----------: | :------------------------------: |
| --wallet, -w  |         用于指定钱包文件         |
| --verbose, -v | 用于显示钱包文件中账户的详细信息 |

## 修改账户

在账户管理模块中，`set` 命令用于实现对账户的修改。

```shell
ontology account set
```

在账户管理模块中，`set` 命令所支持的选项如下表所示，你可以通过 `--help` 选项获取帮助信息。

|        选项        |            描述            |
| :----------------: | :------------------------: |
|  --as-default, -d  |      用于指定默认账户      |
|    --wallet, -w    | 用于指定默认钱包文件的路径 |
|    --label, -l     |   用于给账户设置新的标签   |
|  --change-passwd   |      用于修改账户密码      |
| --signature-scheme |      用于修改签名算法      |

> **注意**：
> - 默认的钱包路径为 `./wallet.dat`。
> - 同一个钱包文件中，不能有两个相同的钱包标签。

## 删除账户

在账户管理模块中，`set` 命令用于实现对账户的删除。

```shell
ontology account del 2
ontology account del acct
ontology account del AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa
```

> **注意**：
> - 未备份的账户删除后将无法恢复，请谨慎操作。
> - 默认账户无法删除。

## 导出账户

在账户管理模块中，`export` 命令用于导出钱包账户。

```shell
ontology account export ./export_wallet.dat
```

在账户管理模块中，`export` 命令所支持的选项如下表所示，你可以通过 `--help` 选项获取帮助信息。

|      选项      |                   描述                   |
| :------------: | :--------------------------------------: |
|  --wallet, -w  |             用于指定导出钱包             |
| --low-security | 用于降低导出钱包文件中的账户保护安全等级 |

> **注意**：如果不是出于特殊需要，如为了将钱包文件导入到低性能设备当中，请勿使用 `--low-security` 选项。

## 导入账户

在账户管理模块中，`import` 命令用于导入钱包账户。

|    选项     |                 描述                  |
| :---------: | :-----------------------------------: |
| --wallet, w |  用于指定接收导入钱包账户的钱包文件   |
| --source,s  |   用于指定被导入钱包账户的钱包文件    |
|    --wif    | 用于指定被导入导入钱包账户的 WIF 文件 |

```shell
ontology account import -s ./export_wallet.dat
```

如果需要通过 WIF 导入钱包账户，你首先需要将52位的 WIF 文本保存到一个文件中，如 `wif`，然后使用如下命令导入。

```shell
ontology account import --wif ./wif
```

> **注意**：请在导入完成后彻底清除设备中的 wif 文件或将其置于安全的位置。