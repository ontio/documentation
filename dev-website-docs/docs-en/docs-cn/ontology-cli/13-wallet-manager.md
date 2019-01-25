
本体客户端 `Ontology-CLI` 提供了钱包管理模块，可以在命令行中通过 `account` 命令使用。

- 对钱包账户的增加、删除、查看、修改。
- 对钱包文件的导入导出。

此外，你可以通过 `help` 命令获取钱包管理模块的帮助信息 。

```shell
ontology account help
```

## 签名算法

本体客户端 `Ontology-CLI` 支持 `ECDSA`、`SM2` 以及 `ED25519` 三种签名算法。

<table cellspacing=0>
    <tr>
        <td style=min-width:50px>加密算法</td>
        <td style=min-width:50px>密钥曲线</td>
        <td style=min-width:50px>密钥长度（比特）</td>
        <td style=min-width:50px>签名模式</td>
    </tr>
    <tr>
        <td style=min-width:50px rowspan="8">ECDSA</td>
    </tr>
    <tr>
        <td style=min-width:50px>P-224</td>
        <td style=min-width:50px>224</td>
        <td style=min-width:50px>SHA224withECDSA</td>
    </tr>
    <tr>
        <td style=min-width:50px>P-256</td>
        <td style=min-width:50px>256</td>
        <td style=min-width:50px>SHA256withECDSA</td>
    </tr>
    <tr>
        <td style=min-width:50px>P-384</td>
        <td style=min-width:50px>384</td>
        <td style=min-width:50px>SHA384withECDSA</td>
    </tr>
    <tr>
        <td style=min-width:50px rowspan="4">P-521</td>
        <td style=min-width:50px rowspan="4">521</td>
        <td style=min-width:50px>SHA224withEdDSA</td>
    </tr>
    <tr>
        <td style=min-width:50px>SHA256withEdDSA</td>
    </tr>
    <tr>
        <td style=min-width:50px>SHA384withEdDSA</td>
    </tr>
    <tr>
        <td style=min-width:50px>SHA512withEdDSA</td>
    </tr>
    <tr>
        <td style=min-width:50px>SM2</td>
        <td style=min-width:50px>sm2p256v1</td>
        <td style=min-width:50px>256</td>
        <td style=min-width:50px>SM3withSM2</td>
    </tr>
    <tr>
        <td style=min-width:50px>Ed25519</td>
        <td style=min-width:50px>Curve25519</td>
        <td style=min-width:50px>256</td>
        <td style=min-width:50px>SHA512withEdDSA</td>
    </tr>
</table>

## 创建账户

你可以通过 `add` 命令添加账户。

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
> - 默认账户不能被删除，可以通过 `set` 命令的 `-d` 选项来修改默认账户。

```shell
ontology account list
ontology account set -d 2
ontology account list
```

#### 添加账户参数

--type,t
type参数用于设定加密算法，支持ecdsa, sm2和ed25519加密算法。

--bit-length,b
bit-length参数用于指定密钥长度，如果是ecdsa加密算法，可以选择p-224, p-256, p-384, p-521；如果是sm2加密算法，默认为sm2p256v1；如果是ed25519加密算法，默认为25519。

--signature-scheme,s
signature-scheme参数用于指定密钥签名方案，对于ecdsa加密算法，支持SHA224withECDSA、SHA256withECDSA、SHA384withECDSA、SHA512withEdDSA、SHA3-224withECDSA、SHA3-256withECDSA、SHA3-384withECDSA、SHA3-512withECDSA、RIPEMD160withECDSA这些签名方案；如果是sm2加密算法，默认使用SM3withSM2签名方案；如果使用的是ed25519加密算法，默认使用的是SHA512withEdDSA签名方案。

--default
default参数使用系统默认的密钥方案，默认的密钥方式将会使用ECDSA加密算法，使用P-256曲线以及SHA256withECDSA作为签名算法。

--label
label用于给新创建的账户设置标签，用于方便、快捷查找账户。注意，同一个钱包文件下，不能出现重复的label名。没有设置label的账户则为空字符串。

--wallet
wallet 参数用于指定钱包文件路径。如果钱包文件不存在，则会自动创建一个新的钱包文件。

--number
number参数用于需要创建的账户数量。可以通过number来批量创建账户。number默认值为1。

--ontid
ontid参数用来创建ONT ID，而不是普通账户。

**添加账户**

```
./ontology account add --default
```

通过 ./ontology account add --help 可以查看帮助信息。

### 查看账户

使用命令：

```
./ontology account list
```
可以查看当前钱包中的所有账户信息。比如：

```
$ ./ontology account list
Index:1    Address:TA587BCw7HFwuUuzY1wg2HXCN7cHBPaXSe  Label: (default)
Index:2    Address:TA5gYXCSiUq9ejGCa54M3yoj9kfMv3ir4j  Label:
```
其中，Index 为账户在钱包中的索引，索引从1开始，Addres 为账户地址，Label 为账户的标签，default表示当前账户是默认账户。
在Ontology cli中，可以通过Index、Address或非空的Label来查找账户。

使用--v 可以查看账户的详细信息。
通过 ./ontology account list --help 可以查看帮助信息。

### 修改账户

使用修改账户命令可以修改账户的标签，重新设置默认账户，修改账户密码，如果账户是ECDSA加密算法的密钥，还可以修改密钥的签名方案。
通过 ./ontology account set --help 可以查看帮助信息。

#### 修改账户参数

--as-default, -d
as-default参数设置账户为默认账户。

--wallet, -w
wallet参数指定当前操作的钱包路径，默认值为"./wallet.dat"。

--label, -l
label参数用于给账户设置新的标签。注意一个钱包文件中，不能有两个相同的lable。

--change-passwd
change-passwd参数用于修改账户密码。

--signature-scheme, -s
signature-scheme参数用于修改账户签名方案。如果账户使用的是ECDSA密钥，则可以修改如下ECDSA支持的签名方案：SHA224withECDSA、SHA256withECDSA、SHA384withECDSA、SHA512withEdDSA、SHA3-224withECDSA、SHA3-256withECDSA、SHA3-384withECDSA、SHA3-512withECDSA、RIPEMD160withECDSA。

**设置默认账户**

```
./ontology account set --d <address|index|label>
```
**修改账户标签**

```
./ontology account set --label=XXX <address|index|label>
```
**修改账户密码**

```
./ontology account set --changepasswd <address|index|label>
```

**修改ECDSA密钥签名方案**

```
./ontology account set --s=SHA256withECDSA <address|index|label>
```
### 删除账户

对于钱包中不需要的账户，可以删除。删除账户后无法恢复，所以请谨慎操作。注意：默认账户无法被删除。

```
/ontology account del <address|index|label>
```
### 导入账户

导入账户命令可以把另一个钱包中的账户导入到当前的钱包中。

#### 导入账户参数

--wallet,w
wallet参数指定当前钱包路径，用于接收导入钱包的账户。

--source,s
source参数指定被导入的钱包路径

```
./ontology account import -s=./source_wallet.dat
```

#### 通过WIF导入账户
获得WIF并把WIF存入key.txt文件，并通过以下命令导入
ontology account import --wif --source key.txt