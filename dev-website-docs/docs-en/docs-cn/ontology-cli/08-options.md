
本体客户端支持的命令行参数如下表所示，你可以在需要的时候使用 `help` 命令在终端中查看。

<table cellspacing=0 border=1>
    <tr>
        <td style=min-width:50px>命令行参数</td>
        <td style=min-width:50px>选项</td>
        <td style=min-width:50px>描述</td>
    </tr>
    <tr>
        <td style=min-width:50px rowspan="5">系统参数</td>
    </tr>
    <tr>
        <td style=min-width:50px>--config</td>
        <td style=min-width:50px>指定客户端的创世区块配置文件路径（默认为主网创世区块的配置）</td>
    </tr>
    <tr>
        <td style=min-width:50px>--loglevel</td>
        <td style=min-width:50px>设置输出的日志级别（0-Trace，1-Debug，2-Info，3-Warn， 4-Error，5-Fatal，6-MaxLevel，默认为默2）</td>
    </tr>
    <tr>
        <td style=min-width:50px>--disable-event-log</td>
        <td style=min-width:50px>用于关闭智能合约执行时输出的事件日志以提升节点的交易执行性能（默认开启）</td>
    </tr>
    <tr>
        <td style=min-width:50px>--data-dir</td>
        <td style=min-width:50px>指定区块数据的存放目录（默认为 ./Chain）</td>
    </tr>
    <tr>
        <td style=min-width:50px rowspan="4">账户参数</td>
    </tr>
    <tr>
        <td style=min-width:50px>--wallet, -w</td>
        <td style=min-width:50px>指定客户端钱包文件的路径（默认为 ./wallet.dat）</td>
    </tr>
    <tr>
        <td style=min-width:50px>--account, -a</td>
        <td style=min-width:50px>指定客户端的账户地址（默认为钱包默认账户）</td>
    </tr>
    <tr>
        <td style=min-width:50px>--password, -p</td>
        <td style=min-width:50px>指定客户端启动的账户密码</td>
    </tr>
         <td style=min-width:50px rowspan="3">共识参数</td>
    <tr>
        <td style=min-width:50px>--enable-consensus</td>
        <td style=min-width:50px>用于启动网络共识（默认关闭）</td>
    </tr>
    <tr>
        <td style=min-width:50px>--max-tx-in-block</td>
        <td style=min-width:50px>用于设置区块最大的交易数量（默认为50000）</td>
    </tr>
    <tr>
        <td style=min-width:50px rowspan="5">点对点网络参数</td>
    </tr>
    <tr>
        <td style=min-width:50px>--networkid</td>
        <td style=min-width:50px>用于指定网络编号</td>
    </tr>
    <tr>
        <td style=min-width:50px>--nodeport</td>
        <td style=min-width:50px>用于指定P2P网络端口号（默认为20338）</td>
    </tr>
    <tr>
        <td style=min-width:50px>--consensus-port</td>
        <td style=min-width:50px>用于指定共识网络端口号（默认为20339）</td>
    </tr>
    <tr>
        <td style=min-width:50px>--dual-port</td>
        <td style=min-width:50px>启动双网络（P2P网络和共识网络，默认关闭）</td>
    </tr>
    <tr>
        <td style=min-width:50px rowspan="3">RPC 参数</td>
    </tr>
    <tr>
        <td style=min-width:50px>--disable-rpc</td>
        <td style=min-width:50px>用于关闭节点的 RPC 服务（默认启动）</td>
    </tr>
    <tr>
        <td style=min-width:50px>--rpcport</td>
        <td style=min-width:50px>用指定 RPC 服务器绑定的端口号</td>
    </tr>
    <tr>
        <td style=min-width:50px rowspan="3">Restful 参数</td>
    </tr>
    <tr>
        <td style=min-width:50px>--rest</td>
        <td style=min-width:50px>用于启动节点的 Resrful 服务</td>
    </tr>
    <tr>
        <td style=min-width:50px>--restport</td>
        <td style=min-width:50px>指定节点 Resrful 服务绑定的端口号（默认值为20334）</td>
    </tr>
    <tr>
        <td style=min-width:50px rowspan="3">WebSocket 参数</td>
    </tr>
    <tr>
        <td style=min-width:50px>--ws</td>
        <td style=min-width:50px>用于启动节点的 WebSocket 服务</td>
    </tr>
    <tr>
        <td style=min-width:50px>--wsport</td>
        <td style=min-width:50px>用于指定节点 WebSocket 服务绑定的端口号（默认为20335）</td>
    </tr>
    <tr>
        <td style=min-width:50px rowspan="3">测试模式参数</td>
    </tr>
    <tr>
        <td style=min-width:50px>--testmode</td>
        <td style=min-width:50px>用于启动单节点的测试网络进行开发和调试（gasprice 为0）</td>
    </tr>
    <tr>
        <td style=min-width:50px>--testmode-gen-block-time</td>
        <td style=min-width:50px>用于设置测试模式下的出块时间（默认为 6 秒，最小为 2 秒）</td>
    </tr>
    <tr>
        <td style=min-width:50px rowspan="6">交易参数</td>
    </tr>
    <tr>
        <td style=min-width:50px>--gasprice</td>
        <td style=min-width:50px>用于设定当前节点交易池接受交易的最低 gasprice （默认为500，测试模式为 0）</td>
    </tr>
    <tr>
        <td style=min-width:50px>--gaslimit</td>
        <td style=min-width:50px>用于设定当前节点交易池接受交易的最低 gaslimit （默认为20000）</td>
    </tr>
    <tr>
        <td style=min-width:50px>--disable-tx-pool-pre-exec</td>
        <td style=min-width:50px>用于关闭交易池中的交易预执行校验（默认开启）</td>
    </tr>
    <tr>
        <td style=min-width:50px>--disable-sync-verify-tx</td>
        <td style=min-width:50px>用于关闭 RPC、Restful、WebSocket 的同步验证交易</td>
    </tr>
    <tr>
        <td style=min-width:50px>--disable-broadcast-net-tx</td>
        <td style=min-width:50px>用于关闭交易池的广播交易（默认开启）</td>
    </tr>
</table>

**注意**：

- 网络编号不同不同将无法连接到区块链网络中
- 低于节点交易池接受交易的最低 `gasprice` 的交易将会被丢弃
- 记账节点需要使用 `--enable-consensus` 参数参与到网络共识
- 同一个网络所有节点的创世区块配置必须一致，否则会因为区块数据不兼容导致无法启动节点或同步区块数据
- 在命令行中输入的账户密码会被保存在系统的日志中，容易造成密码泄露，因此在生产环境中不建议使用 `--password`, `-p` 参数
- 默认情况下，共识网络复用 P2P 网络，因此不需要指定共识网络端口，在通过 `--dualport` 参数启动双网络后，则需要通过 `--consensus-port`
 参数单独设置共识网络端口号

### 节点部署

#### 主网记账节点部署

按照角色不同，节点可以分为记账节点和同步节点，记账节点参与网络共识，而同步节点只同步记账节点生成的区块。由于Ontology默认是不启动共识模块的，因此部署记账节点需要通过--enableconsensus命令行参数开启共。此外，Ontology节点默认会启动Rpc服务器，同时会输出智能合约输出的Event Log，因此如果没有特殊要求，可以使用--disablerpc和--disableeventlog命令行参数关闭rpc和eventlog模块。

推荐记账节点启动参数：

```
./ontology --enable-consensus --disable-rpc --disable-event-log
```
 - `enable-consensus` 是用来开启节点共识
 - `disable-rpc` 是处于节点安全考虑关闭rpc服务
 - `disable-event-log` 是关闭日志服务，这样可以提供更高的性能
如果节点没有使用默认的创世块配置文件和钱包账户，可以通过--config参数和--wallet、--account参数指定。
同时，如果记账节点需要修改交易池默认的最低gas price和gas limit，可以通过--gasprice和--gaslimit参数来设定。

#### 主网同步节点部署

由于同步节点只同步记账节点生成的区块，并不参与网络共识。

```
./ontology
```
如果节点没有使用默认的创世块配置文件，可以通过--config参数指定。同时由于没有启动共识模块，因此不需要钱包。

#### 部署测试网Polaris的同步节点

可以直接通过以下命令连接测试网

```
./ontology --networkid 2
```

#### 本地测试网部署

Ontology支持单节点网络部署，用于开发测试环境搭建。启动单节点测试网络只需要加上--testmode参数即可。

```
./ontology --testmode
```
如果节点没有使用默认的创世块配置文件和钱包账户，可以通过--config参数和--wallet、--account参数指定。
同时，如果记账节点需要修改交易池默认的最低gas price和gas limit，可以通过--gasprice和--gaslimit参数来设定。

启动单节点测试网络时，会同时启动共识、rpc、rest以及WebSocket模块。

## 钱包管理

钱包管理命令可以用来添加、查看、修改、删除、导入账户等功能。
使用 ./ontology account --help 命令可以查看钱包管理命令的帮助信息。

### 添加账户

Ontology支持多种加密算法，包括ECDSA、SM2以及ED25519。

在使用ECDSA加密算法时，可以支持多种密钥曲线，如：P-224、P-256、P-384、P-521；此外，在使用ECDSA加密算法时，还可以指定该密钥的签名方案，如：SHA224withECDSA、SHA256withECDSA、SHA384withECDSA、SHA512withEdDSA、SHA3-224withECDSA、SHA3-256withECDSA、SHA3-384withECDSA、SHA3-512withECDSA、RIPEMD160withECDSA。

在使用SM2加密算法时，使用sm2p256v1曲线，同时使用SM3withSM2签名算法。

使用ED25519加密算法时，使用25519曲线，使用SHA512withEdDSA签名算法。

**默认账户**

每个钱包都一个默认账户，一般情况下是第一个添加的账户。默认账户不能被删除，可以通过./ontology account set 命令来修改默认账户。

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

## 资产管理

资产管理命令可以查看账户的余额，执行ONT/ONG转账，提取ONG以及查看未绑定的ONG等操作。

### 查看账户余额

```
./ontology asset balance <address|index|label>
```
### ONT/ONG转账

#### 转账参数

--wallet, -w
wallet指定转出账户钱包路径，默认值为:"./wallet.dat"

--gasprice
gasprice参数指定转账交易的gas price。交易的gas price不能小于接收节点交易池设置的最低gas price，否则交易会被拒绝。默认值为500（在testmode模型下为0）。当交易池中有交易在排队等待打包进区块时，交易池会按照gas price由高到低排序，gas price高的交易会被优先处理。

--gaslimit
gaslimit参数指定转账交易的gas limit。交易的gas limit不能小于接收节点交易池设置的最低gas limit，否则交易会被拒绝。gasprice * gaslimit 为账户实际支付的ONG 费用。 默认值为20000。

--asset
asset参数指定转账的资产类型，ont表示ONT，ong表示ONG。默认值为ont。

--from
from参数指定转出账户地址。

--to
to参数指定转入账户地址。

--amount
amount参数指定转账金额。注意：由于ONT的精度是1，因此如果输入的是个浮点值，那么小数部分的值会被丢弃；ONG的精度为9，因此超出9位的小数部分将会被丢弃。

--force, -f
转账的时候如果账户余额小于转账金额, 转账交易会被终止，如果此时仍想把交易发送出去，则可使用改参数强行提交交易。

**转账**

```
./ontology asset transfer --from=<address|index|label> --to=<address|index|label> --amount=XXX --asset=ont
```

### 授权转账

用户可以授权其他账户在授权额度内从本账户中转账。

#### 授权转账参数
--wallet, -w
wallet指定授权转出账户钱包路径，默认值为:"./wallet.dat"

--gasprice
gasprice参数指定转账交易的gas price。交易的gas price不能小于接收节点交易池设置的最低gas price，否则交易会被拒绝。默认值为500（在testmode模型下为0）。当交易池中有交易在排队等待打包进区块时，交易池会按照gas price由高到低排序，gas price高的交易会被优先处理。

--gaslimit
gaslimit参数指定转账交易的gas limit。交易的gas limit不能小于接收节点交易池设置的最低gas limit，否则交易会被拒绝。gasprice * gaslimit 为账户实际支付的ONG 费用。 默认值为20000。

--asset
asset参数指定转账的资产类型，ont表示ONT，ong表示ONG。默认值为ont。

--from
from参数指定授权转出的账户地址。

--to
to参数指定转授权入的账户地址。

--amount
amount参数指定授权转账金额。注意：由于ONT的精度是1，因此如果输入的是个浮点值，那么小数部分的值会被丢弃；ONG的精度为9，因此超出9位的小数部分将会被丢弃。

**授权转账**

```
./ontology asset approve --from=<address|index|label> --to=<address|index|label> --amount=XXX --asset=ont
```

### 查看授权转帐余额

授权用户转账后，用户可以根据需要分多次在授权额度内执行转账操作。查看授权转帐余额命令可以查看到未转账的余额。

#### 查看授权转帐余额参数

--wallet, -w
wallet指定转出账户钱包路径，默认值为:"./wallet.dat"

--asset
asset参数指定转账的资产类型，ont表示ONT，ong表示ONG。默认值为ont。

--from
from参数指定授权转出账户地址。

--to
to参数指定授权转入账户地址。

**查看授权转帐余额**

```
./ontology asset allowance --from=<address|index|label> --to=<address|index|label>
```

### 从授权账户中转账

通过用户授权后，可以从授权账户中转帐。

#### 从授权账户中转账参数
--wallet, -w
wallet指定执行授权转账账户的钱包路径，默认值为:"./wallet.dat"

--gasprice
gasprice参数指定转账交易的gas price。交易的gas price不能小于接收节点交易池设置的最低gas price，否则交易会被拒绝。默认值为500（在testmode模型下为0）。当交易池中有交易在排队等待打包进区块时，交易池会按照gas price由高到低排序，gas price高的交易会被优先处理。

--gaslimit
gaslimit参数指定转账交易的gas limit。交易的gas limit不能小于接收节点交易池设置的最低gas limit，否则交易会被拒绝。gasprice * gaslimit 为账户实际支付的ONG 费用。 默认值为20000。

--asset
asset参数指定转账的资产类型，ont表示ONT，ong表示ONG。默认值为ont。

--from
from参数指定授权转出账户地址。

--to
to参数指定转授权入账户地址。

--sender
sender参数指定实际执行授权转账的账户地址。如果没有指定sender参数，sender参数默认使用to参数的指定的账户地址。

--amount
amount参数指定转账金额，转账金额不能大于授权转账余额，否则交易会执行失败。注意：由于ONT的精度是1，因此如果输入的是个浮点值，那么小数部分的值会被丢弃；ONG的精度为9，因此超出9位的小数部分将会被丢弃。

**从授权账户中转账**

```
./ontology asset transferfrom --from=<address|index|label> --to=<address|index|label> --sender=<address|index|label> --amount=XXX
```

### 查看未解绑的ONG余额

ONG采用定时解绑策略解除绑定在ONT上的ONG。使用如下命令可以查看到当前账户未解绑的ONG余额。

```
./ontology asset unboundong <address|index|label>
```
### 提取解绑的ONG

使用提取命令可以提取当前所有未解绑的ONG。

#### 提取解绑的ONG参数

--wallet, -w
wallet参数指定提取账户的钱包路径，默认值为:"./wallet.dat"

--gasprice
gasprice参数指定转账交易的gas price。交易的gas price不能小于接收节点交易池设置的最低gas price，否则交易会被拒绝。默认值为500（在testmode模型下为0）。当交易池中有交易在排队等待打包进区块时，交易池会按照gas price由高到低排序，gas price高的交易会被优先处理。

--gaslimit
gaslimit参数指定转账交易的gas limit。交易的gas limit不能小于接收节点交易池设置的最低gas limit，否则交易会被拒绝。gasprice * gaslimit 为账户实际支付的ONG 费用。 默认值为20000。

**提取解绑的ONG**
```
./ontology asset withdrawong <address|index|label>
```
## 查询信息

查询信息命令可以查询区块、交易以及交易执行等信息。使用./ontology info block --help 命令可以查看帮助信息。

### 查询区块信息

```
./ontology info block <height|blockHash>
```
可以通过区块高度或者区块Hash 查询区块信息。

### 查询交易信息

```
./ontology info tx <TxHash>
```
可以通过交易Hash查询交易信息。

### 查询交易执行信息

```
./ontology info status <TxHash>
```
可以通过交易Hash查询交易的执行信息，返回示例如下：

```
{
   "TxHash": "4c00674d96b1d3d2c8152b905cae6f87fff0ec8acf28ca3e7465aac59de814a1",
   "State": 1,
   "GasConsumed": 0,
   "Notify": [
      {
         "ContractAddress": "ff00000000000000000000000000000000000001",
         "States": [
            "transfer",
            "TA587BCw7HFwuUuzY1wg2HXCN7cHBPaXSe",
            "TA5gYXCSiUq9ejGCa54M3yoj9kfMv3ir4j",
            10
         ]
      }
   ]
}
```
其中，State表示交易执行结果，State的值为1，表示交易执行成功，State值为0时，表示执行失败。GasConsumed表示交易执行消耗的ONG。Notify表示交易执行时输出的Event log。不同的交易可能会输出不同的Event log。

## 智能合约

智能合约操作支持NeoVM智能合约的部署，以及NeoVM智能合约的预执行和执行。

### 智能合约部署

智能部署前需要把在NeoVM合约编译器如：[SmartX](http://smartx.ont.io) 上编译好的Code，保存在本地的一个文本文件中。

#### 智能合约部署参数

--wallet, -w
wallet参数指定部署智能合约的账户钱包路径。默认值："./wallet.dat"。

--account, -a
account参数指定部署合约的账户。

--gasprice
gasprice参数指定部署合约交易的gas price。交易的gas price不能小于接收节点交易池设置的最低gas price，否则交易会被拒绝。默认值为500（在testmode模型下为0）。当交易池中有交易在排队等待打包进区块时，交易池会按照gas price由高到低排序，gas price高的交易会被优先处理。

--gaslimit
gaslimit参数指定部署合约交易的gas limit。交易的gas limit不能小于接收节点交易池设置的最低gas limit，否则交易会被拒绝。gasprice * gaslimit 为账户实际支付的ONG 费用。

**对于合约部署，gaslimit 值必须大于20000000，同时账户中必须保有足够的ONG余额。**

--needstore
needstore参数指定智能合约属否需要使用持久化存储，如果需要使用则需要带上该参数。默认为不使用。

--code
code参数指定智能合约代码路径。

--name
name参数指定智能合约的名称。

--version
version参数指定智能合约的版本号。

--author
author参数指定智能合约的作者信息。

--email
emial参数指定智能合约的联系人电子邮件。

--desc
desc参数可以指定智能合约的描述信息。

--prepare, -p
prepare参数用于预部署合约, 预部署不会把合约部署到Ontology上， 也不会消耗人任何ONG。通过预部署合约，用户可以知道当前合约部署所需要消耗的gas limit。

**智能合约部署**

```
./ontology contract deploy --name=xxx --code=xxx --author=xxx --desc=xxx --email=xxx --needstore --gaslimit=100000000
```

部署后会返回部署交易的TxHash以及合约地址，如：

```
Deploy contract:
  Contract Address:806fbee1fcfb554af47844edd4d4ce2918737747
  TxHash:99d719f51837acfa48f9cd2a21983fb993bc8d5a763b497802f7b872be2338fe
```

可以通过 ./ontology info status <TxHash> 命令查询合约执行状态。如果返回错误如：UNKNOWN TRANSACTION时，表示交易没有落帐，有可能交易还在交易池中排队等待被打包，也有可能表示交易因为gaslimit或者时gasprice设置过低，导致交易被拒绝。

如果返回的执行状态State等于0，表示交易执行失败，如果State等于1，表示交易执行成功，合约被成功部署。如：

```
Transaction states:
{
   "TxHash": "99d719f51837acfa48f9cd2a21983fb993bc8d5a763b497802f7b872be2338fe",
   "State": 1,
   "GasConsumed": 0,
   "Notify": []
}
```

Contract Address为根据合约Code生成的合约地址。

### 智能合约执行

NeoVM智能合约参数类型支持array、bytearray、string、int以及bool类型。其中array表示对象数组，数组元素可以是NeoVM支持的任意数量、任意类型的值；bytearray表示字节数组，输入时需要将byte数组用十六进制编码成字符串，如 []byte("HelloWorld") 编码成：48656c6c6f576f726c64；string表示字符串字面值；int表示整数，由于NeoVM虚拟机不支持浮点数值，因此需要将浮点数转换成整数；bool表示布尔型变量，用true，false表示。

在Ontology cli中，使用前缀法构造输入参数，参数前使用类型标识标注类型，如字符串参数表示为 string:hello; 整数参数表示为 int:10; 布尔类型参数表示为 bool:true等。多个参数使用","分隔。对象数组array类型用"[ ]"表示数组元素范围，如 [int:10,string:hello,bool:true]。

输入参数示例：

```
string:methodName,[string:arg1,int:arg2]
```

#### 智能合约执行参数

--wallet, -w
wallet参数指定智能合约执行的账户钱包路径。默认值："./wallet.dat"。

--account, -a
account参数指定执行合约的账户。

--gasprice
gasprice参数指定部署合约交易的gas price。交易的gas price不能小于接收节点交易池设置的最低gas price，否则交易会被拒绝。默认值为500（在testmode模型下为0）。当交易池中有交易在排队等待打包进区块时，交易池会按照gas price由高到低排序，gas price高的交易会被优先处理。

--gaslimit
gaslimit参数指定部署合约交易的gas limit。交易的gas limit不能小于接收节点交易池设置的最低gas limit，否则交易会被拒绝。gasprice * gaslimit 为账户实际支付的ONG 费用。

--address
address参数指定调用的合约地址

--params
params参数用于输入合约调用的参数，需要按照上面的说明编码输入参数。

--prepare, -p
prepare参数表示当前为预执行，执行交易不会被打包到区块中，也不会消耗任何ONG。预执行会返回合约方法的返回值，同时还会试算当前调用需要的gas limit。

--return
return参数用于配合--prepare参数使用，在预执行时通过--return参数标注的返回值类型来解析合约返回返回值，否则输出合约方法调用时返回的原始值。多个返回值类型用","分隔，如 string,int

**智能合约预执行**

```
./ontology contract invoke --address=XXX --params=XXX --return=XXX --p
```
返回示例：

```
Contract invoke successfully
Gas consumed:20000
Return:0
```
**智能合约执行**

```
./ontology contract invoke --address=XXX --params=XXX --gaslimit=XXX
```

智能合约在执行之前，可以通过预执行，试算出当前执行所需要的gas limit，以避免ONG余额不足导致执行失败。

### 直接执行智能合约字节码

智能合约部署后，cli支持直接执行NeoVM Code。

#### 直接执行智能合约字节码参数

--wallet, -w
wallet参数指定智能合约执行的账户钱包路径。默认值："./wallet.dat"。

--account, -a
account参数指定执行合约的账户。

--gasprice
gasprice参数指定部署合约交易的gas price。交易的gas price不能小于接收节点交易池设置的最低gas price，否则交易会被拒绝。默认值为0。当交易池中有交易在排队等待打包进区块时，交易池会按照gas price由高到低排序，gas price高的交易会被优先处理。

--gaslimit
gaslimit参数指定部署合约交易的gas limit。交易的gas limit不能小于接收节点交易池设置的最低gas limit，否则交易会被拒绝。gasprice * gaslimit 为账户实际支付的ONG 费用。

--prepare, -p
prepare参数表示当前为预执行，执行交易不会被打包到区块中，也不会消耗任何ONG。预执行会返回合约方法的返回值，同时还会试算当前调用需要的gas limit。

--code
code参数指定可执行的智能合约代码路径。

#### 直接执行智能合约字节码

```
./ontology contract invokeCode --code=XXX --gaslimit=XXX
```

## 区块导入导出

Ontology Cli支持导出本地节点的区块数据到一个压缩文件中，生成的压缩文件可以再导入其它Ontology节点中。出于安全考虑，导入的区块数据文件请确保是从可信的来源获取的。

### 导出区块

#### 导出区块参数

--rpcport
rpcport 参数用于指定Ontology节点的rpc端口号，默认值为20336。

--exportfile
exportfile 参数指定导出的文件路径。默认值为：./OntBlocks.dat

--startheight
startheight 参数指定导出区块的起始高度。默认值为0。

--endheight
endheight 参数用于指定导出区块的终止高度。默认值为0，表示导出所有区块。

--speed
speed 参数指定导出速度。分别用h表示high，m表示middle，l表示low。默认值为m。

区块导出

```
./ontology export
```

### 导入区块

#### 导入区块参数

--datadir
datadir 参数用于指定区块数据存储目录

--config
config 参数用于指定当前Ontology节点创世区块配置文件的路径。如果不指定，将使用Ontolog主网的创世块配置。

--disableeventlog
disableeventlog 参数用于关闭导入区块时生成合约日志功能。

--networkid
networkid 参数用于指定需要导入的网路ID。默认值为主网networkid。

--endheight
endheight 参数指定导入的目标区块高度。如果importheight指定的区块高度小于区块文件的最大高度时，只导入到importheight指定的高度，剩余的区块会停止导入。默认值为0，表示导入所有的区块。

--importfile
importfile 参数用于指定导入文件的路径。默认值为"./OntBlocks.dat"。

导入区块

```
./ontology import --importfile=./OntBlocks.dat
```

## 构造交易

构造交易命令用于构造各种交易的交易内容，如转账交易，授权转账交易等，构造出来的交易在发送到Ontology上之前，还需要用户的私钥签名。

### 构造转账交易

#### 构造转账交易参数

--gasprice
gasprice 参数用于设定交易执行的gasprice。默认值为500。

--gaslimit
gaslimit 参数用于设定交易执行的gaslimit。默认值为20000。

--payer
payer 参数用于设置交易手续费的付款账户。如果不设定，默认使用付款人账户(账户可以用地址、索引、标签表示)。

--asset
asset 参数用于设置资产类型，如ONT，ONG。

--from
from 参数用于设置转账扣款账户(账户可以用地址、索引、标签表示)。

--to
to参数用于设置转账收款人账户(账户可以用地址、索引、标签表示)。

--amount
amount参数用于设定转账金额。浮点类型，如果0.001个ong

--wallet
wallet 钱包路径。wallet参数用于解析账户的索引或者标签。如果账户使用的都是地址，则不需要此参数。

```
./ontology buildtx transfer --from=ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48 --to=AaCe8nVkMRABnp5YgEjYZ9E5KYCxks2uce --amount=10
```

返回如下：

```
Transfer raw tx:
00d1d376865bf401000000000000204e0000000000006a987e044e01e3b71f9bb60df57ab0458215ef0f6e00c66b6a146a987e044e01e3b71f9bb60df57ab0458215ef0fc86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a5ac86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
```

### 构造授权转账交易

#### 构造授权转账交易参数

--gasprice
gasprice 参数用于设定交易执行的gasprice。默认值为500。

--gaslimit
gaslimit 参数用于设定交易执行的gaslimit。默认值为20000。

--payer
payer 参数用于设置交易手续费的付款账户。如果不设定，默认使用付款人账户(账户可以用地址、索引、标签表示)。

--asset
asset 参数用于设置资产类型，如ONT，ONG。

--from
from 参数用于设置转账的扣款账户(账户可以用地址、索引、标签表示)。

--to
to参数用于设置转账收款人账户(账户可以用地址、索引、标签表示)。

--amount
amount参数用于设定转账金额。浮点类型，如果0.001个ong

--wallet
wallet 钱包路径。wallet参数用于解析账户的索引或者标签。如果账户使用的都是地址，则不需要此参数。

```
./ontology buildtx approve  --from=ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48 --to=AaCe8nVkMRABnp5YgEjYZ9E5KYCxks2uce --amount=10
```
返回如下：

```
Approve raw tx:
00d12178865bf401000000000000204e0000000000006a987e044e01e3b71f9bb60df57ab0458215ef0f6b00c66b6a146a987e044e01e3b71f9bb60df57ab0458215ef0fc86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a5ac86c07617070726f76651400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
```

### 构造从授权账户中转账交易

#### 构造从授权账户中转账交易参数

--gasprice
gasprice 参数用于设定交易执行的gasprice。默认值为500。

--gaslimit
gaslimit 参数用于设定交易执行的gaslimit。默认值为20000。

--payer
payer 参数用于设置交易手续费的付款账户。如果不设定，默认使用付款人账户(账户可以用地址、索引、标签表示)。

--asset
asset 参数用于设置资产类型，如ONT，ONG。

--sender
sender 参数用于设定交易发送账户，也就是被授权账户(账户可以用地址、索引、标签表示)。如果不设定，默认使用收款人账户。

--from
from 参数用于设置转账的扣款账户，也就是授权账户(账户可以用地址、索引、标签表示)。

--to
to参数用于设置转账收款人账户(账户可以用地址、索引、标签表示)。

--amount
amount参数用于设定转账金额。浮点类型，如0.001个ong

--wallet
wallet 钱包路径。wallet参数用于解析账户的索引或者标签。如果账户使用的都是地址，则不需要此参数。

```
./ontology buildtx transferfrom --sender=AMFrW7hrSRw1Azz6hQohni8BdStZDvectW --from=Aaxjf7utmjSstmTD1LjtYfhZ3CoWaxC7Tt --to=AMFrW7hrSRw1Azz6hQohni8BdStZDvectW --amount=10
```

返回如下：

```
00d10754875bf401000000000000204e0000000000003c2352095b7428debfd1c1519f5a8f45a474a4218700c66b6a143c2352095b7428debfd1c1519f5a8f45a474a421c86a14d2784bddeac73d20124f20f4fa9528f3365a4dd4c86a143c2352095b7428debfd1c1519f5a8f45a474a421c86a5ac86c0c7472616e7366657246726f6d1400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
```

### 构造提取ONG交易

#### 构造提取ONG交易参数

--gasprice
gasprice 参数用于设定交易执行的gasprice。默认值为500。

--gaslimit
gaslimit 参数用于设定交易执行的gaslimit。默认值为20000。

--payer
payer 参数用于设置交易手续费的付款账户。如果不设定，默认使用付款人账户(账户可以用地址、索引、标签表示)。

--receive
receive 参数用于设定提取的ONG接收账户。如果不设置，默认使用ONG提取账户。

--amount
amount参数用于设定提取的ONG金额。浮点类型，如0.001个ong。如果不填，默认提取该账户下的所有可以提取ONG。

--wallet
wallet 钱包路径。wallet参数用于解析账户的索引或者标签。如果账户使用的都是地址，则不需要此参数。

--rpcport
rpcport 参数用于设置RPC服务器的端口号。默认值为20336。

```
./ontology buildtx withdrawong ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48
```

返回如下：

```
Withdraw account:ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48
Receive account:ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48
Withdraw ONG amount:2321499191858975
Withdraw raw tx:
00d11b56875bf401000000000000204e0000000000006a987e044e01e3b71f9bb60df57ab0458215ef0f8e00c66b6a146a987e044e01e3b71f9bb60df57ab0458215ef0fc86a140000000000000000000000000000000000000001c86a146a987e044e01e3b71f9bb60df57ab0458215ef0fc86a071f57ad26643f08c86c0c7472616e7366657246726f6d1400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
```

## 对交易签名

使用buildtx 命令构造的交易，需要通过相关账户签名后，才是有效的交易。注意，如果交易手续费账户和付款账户不是同一个账户，则该交易需要付款人账户和手续费账户都签名。

### 交易签名命令参数

--wallet
wallet 参数用于指定钱包路径。

--account
account 参数用于指定签名账户，如果不设置，使用钱包默认账户。

--send
send 参数用于指定，交易签名后是否直接发送到Ontology网络上。

--prepare
prepare 参数用于指定，交易签名后是否本地预执行交易。

--rpcport
rpcport 参数用于指定RPC服务器端口号。默认值为20336。


```
./ontology sigtx --account=ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48 00d11b56875bf401000000000000204e0000000000006a987e044e01e3b71f9bb60df57ab0458215ef0f8e00c66b6a146a987e044e01e3b71f9bb60df57ab0458215ef0fc86a140000000000000000000000000000000000000001c86a146a987e044e01e3b71f9bb60df57ab0458215ef0fc86a071f57ad26643f08c86c0c7472616e7366657246726f6d1400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
```

返回如下：

```
RawTx after signed:
00d11b56875bf401000000000000204e0000000000006a987e044e01e3b71f9bb60df57ab0458215ef0f8e00c66b6a146a987e044e01e3b71f9bb60df57ab0458215ef0fc86a140000000000000000000000000000000000000001c86a146a987e044e01e3b71f9bb60df57ab0458215ef0fc86a071f57ad26643f08c86c0c7472616e7366657246726f6d1400000000000000000000000000000000000000020068164f6e746f6c6f67792e4e61746976652e496e766f6b65000141407331b7ba2a7708187ad4cb14146d2080185e42f0a39d572f58d25fa2e20f3066711b64f2b91d958683f7bfb904badeb0d6bc733506e665028a2c2968b77d5958232103c0c30f11c7fc1396e8595bf2e339d553d728ea6f21ae831e8ab704ca14fe8a56ac
```

## 生成多重签名地址

生成多重签名地址需要指定公钥列表PubKey，以及在公钥列表中的所需要的最少签名数量M。

### 生成多重签名地址参数
--pubkey
pubkey 参数用于指定多重签名的公钥列表，公钥之间用逗号','分隔。
账户公钥可以通过命令：

```
./ontology account list -v
```
查看。

目前多重签名支持的最大公钥数为16。

-m
m 参数用于指定所以的最少签名数。默认值为1。

```
./ontology multisigaddr --pubkey=03c0c30f11c7fc1396e8595bf2e339d553d728ea6f21ae831e8ab704ca14fe8a56,02b2b9fb60a0add9ef6715ffbac8bc7e81cb47cd06c157c19e6a858859c0158231 -m=1
```
返回如下：

```
Pub key list:
Index 1 Address:AaCe8nVkMRABnp5YgEjYZ9E5KYCxks2uce PubKey:02b2b9fb60a0add9ef6715ffbac8bc7e81cb47cd06c157c19e6a858859c0158231
Index 2 Address:ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48 PubKey:03c0c30f11c7fc1396e8595bf2e339d553d728ea6f21ae831e8ab704ca14fe8a56

MultiSigAddress:Ae4cxJiubmgueAVtNbjpmm2AGNgdKP6Ea7
```

## 对交易多重签名

多重签名需要不同的账户对同一个交易签名，一个账户签名后，返回的交易需要作为下一个账户签名的输入，直到满足m指定的交易签名数。

### 对交易多重签名参数

--wallet
wallet 参数用于指定钱包路径。

--account
account 参数用于指定签名账户，如果不设置，使用钱包默认账户。

--pubkey
pubkey 参数用于指定多重签名的公钥列表，公钥之间用逗号','分隔。

-m
m 参数用于指定所以的最少签名数。默认值为1。

--send
send 参数用于指定，交易签名后是否直接发送到Ontology网络上。

--prepare
prepare 参数用于指定，交易签名后是否本地预执行交易。

--rpcport
rpcport 参数用于指定RPC服务器端口号。默认值为20336。


```
./ontology multisigtx --account=ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48 --pubkey=03c0c30f11c7fc1396e8595bf2e339d553d728ea6f21ae831e8ab704ca14fe8a56,02b2b9fb60a0add9ef6715ffbac8bc7e81cb47cd06c157c19e6a858859c0158231 -m=1 00d1045f875bf401000000000000204e000000000000f47d92d27d02b93d21f8af16c9f05a99d128dd5a6e00c66b6a14f47d92d27d02b93d21f8af16c9f05a99d128dd5ac86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a5ac86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
```

返回如下：

```
RawTx after multi signed:
00d1045f875bf401000000000000204e000000000000f47d92d27d02b93d21f8af16c9f05a99d128dd5a6e00c66b6a14f47d92d27d02b93d21f8af16c9f05a99d128dd5ac86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a5ac86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65000141409dd2a46277f96566b9e9b4fc354be90b61776c58125cfbf36e770b1b1d50a16febad4bfadfc966fa575e90acf3b8308d7a0f637260b31321cb7ef6f741364d0e47512102b2b9fb60a0add9ef6715ffbac8bc7e81cb47cd06c157c19e6a858859c01582312103c0c30f11c7fc1396e8595bf2e339d553d728ea6f21ae831e8ab704ca14fe8a5652ae
```

## 发送交易

用户签好名后的交易可以通过发送交易命令提交到Ontology网络上。

### 发送交易参数

--rpcport
rpcport 参数用于设置RPC服务器的端口号。

--prepare
prepare 参数用于指定是否本地预执行该交易。预执行在本地执行，不会把交易发送到Ontology网路上，也不会提交到账户中。

```
./ontology sendtx 00d17c61875bf401000000000000204e0000000000006a987e044e01e3b71f9bb60df57ab0458215ef0f6e00c66b6a146a987e044e01e3b71f9bb60df57ab0458215ef0fc86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a5ac86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65000141409f32f1fd170d174959da26cb9df8f4a15049d255ed3953d92870d5739c4e8b8158ec3bde1e9ae9b4d9621b09311b5e49ed91dcbc64d3b5f74cf011eaa616c403232103c0c30f11c7fc1396e8595bf2e339d553d728ea6f21ae831e8ab704ca14fe8a56ac
```

返回如下：

```
  TxHash:f8ea91da985af249e808913b6398150079cdfb02273146e4eb69c43947a42db2

Tip:
  Using './ontology info status f8ea91da985af249e808913b6398150079cdfb02273146e4eb69c43947a42db2' to query transaction status.
```

如果是预执行返回如下：

```
Prepare execute transaction success.
Gas limit:20000
Result:01
```

## 查看交易信息

查看交易信息命令可以查看构造好的原始交易的字段信息。

如:

```
./ontology showtx 00d1045f875bf401000000000000204e000000000000f47d92d27d02b93d21f8af16c9f05a99d128dd5a6e00c66b6a14f47d92d27d02b93d21f8af16c9f05a99d128dd5ac86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a5ac86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65000141409dd2a46277f96566b9e9b4fc354be90b61776c58125cfbf36e770b1b1d50a16febad4bfadfc966fa575e90acf3b8308d7a0f637260b31321cb7ef6f741364d0e47512102b2b9fb60a0add9ef6715ffbac8bc7e81cb47cd06c157c19e6a858859c01582312103c0c30f11c7fc1396e8595bf2e339d553d728ea6f21ae831e8ab704ca14fe8a5652ae
```
返回如下：

```
{
   "Version": 0,
   "Nonce": 1535598340,
   "GasPrice": 500,
   "GasLimit": 20000,
   "Payer": "Ae4cxJiubmgueAVtNbjpmm2AGNgdKP6Ea7",
   "TxType": 209,
   "Payload": {
      "Code": "00c66b6a14f47d92d27d02b93d21f8af16c9f05a99d128dd5ac86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a5ac86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65",
      "GasLimit": 0
   },
   "Attributes": [],
   "Sigs": [
      {
         "PubKeys": [
            "02b2b9fb60a0add9ef6715ffbac8bc7e81cb47cd06c157c19e6a858859c0158231",
            "03c0c30f11c7fc1396e8595bf2e339d553d728ea6f21ae831e8ab704ca14fe8a56"
         ],
         "M": 1,
         "SigData": [
            "9dd2a46277f96566b9e9b4fc354be90b61776c58125cfbf36e770b1b1d50a16febad4bfadfc966fa575e90acf3b8308d7a0f637260b31321cb7ef6f741364d0e"
         ]
      }
   ],
   "Hash": "34559b63187d7ddf5a17ac7a2dabb8fcaa1bea6676eba78a174d038ff3c66f15",
   "Height": 0
}
```