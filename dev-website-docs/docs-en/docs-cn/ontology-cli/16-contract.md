
本体客户端 `Ontology-CLI` 提供了智能合约模块，可以在命令行中通过 `contract` 命令使用。

- `NeoVm` 智能合约的部署。
- `NeoVm` 智能合约的执行。
- `NeoVm` 智能合约的预执行。

我们以 `hello_ontology.py` 智能合约为例，在本地测试网上进行命令的讲解。

```python
from ontology.interop.System.Runtime import Notify


def main(operation, args):
    if operation == 'echo':
        return echo(args[0])
    return False

def echo(msg):
    Notify(['echo', msg])
    return msg

```

将该段智能合约代码使用编译器编译后可以得到相应的 `AVM` 字节码，将其以 `hello_ontology.avm` 为文件名保存到本地。

```shell
51c56b6c58c56b6a00527ac46a51527ac46a52527ac46a51c3046563686f7d9c7c75642700006a53527ac46a52c300c3516a53c3936a53527ac46a53c36a00c365f2006c7566620300006c75660111c56b6a00527ac46a51527ac46a51c300947600a0640c00c16a52527ac4620e007562030000c56a52527ac46a52c3c0517d9c7c75641c00006a53527ac46a52c300c36a54527ac4516a55527ac4625c006a52c3c0527d9c7c756421006a52c300c36a53527ac46a52c351c36a54527ac4516a55527ac4616232006a52c3c0537d9c7c756424006a52c300c36a53527ac46a52c351c36a54527ac46a52c352c36a55527ac462050000f100c176c96a56527ac46a53c36a57527ac46a57c36a54c37d9f7c756419006a56c36a57c3c86a57c36a55c3936a57527ac462e0ff6a56c36c756656c56b6a00527ac46a51527ac46a52527ac4620300046563686f6a52c352c176c9681553797374656d2e52756e74696d652e4e6f746966796a52c36c7566
```

其中，你可以用用来编译智能合约的工具如下所示。

- [SmartX](https://smartx.ont.io/)
- [Punica CLI](https://punica.ont.io/)
- [ontology-python-compiler](https://github.com/ontio/ontology-python-compiler)

此外，你需要开启一个终端，启动本地测试网。

```shell
ontology --testmode
```

## 部署智能合约

在智能合约模块中，`deploy` 命令用于根据交易哈希查询交易信息。

- `--needstore`：用于指定智能合约需要使用持久化的合约存储（默认不使用）。

- `--code`：用于指定存储智能合约 `AVM` 字节码文件的路径。

- `--name`：用于指定智能合约的名称。

- `--version`：用于指定智能合约的版本号。

- `--author`：用于指定智能合约的作者信息。

- `--email`：用于指定智能合约的联系人电子邮件。

- `--desc`：用于指定智能合约的描述信息。

- `--prepare, -p`：用于指定智能合约的预部署。

```shell
$ ontology contract deploy --code  .\hello_ontology.avm --name hello_ontology --version 1.0.0 --author NashMiao --email contact@ont.io --desc hello_ontology --gaslimit 20000000 -p
Contract pre-deploy successfully.
Gas consumed:20000000.
```

智能合约的预部署不会把合约部署到链上，也不会消耗任何 `ONG`。通过预部署，你可以知道部署当前合约所需要消耗的 `gas`。

```shell
$ ontology contract deploy --code  .\hello_ontology.avm --name hello_ontology --version 1.0.0 --author NashMiao --email contact@ont.io --desc hello_ontology --gaslimit 20000000
Password:
Deploy contract:
  Contract Address:0203e74032b6b65de9872180f9b600f13858357d
  TxHash:ffb0a02847d31641f05a498a19a4f9f7e7d7616d0ab163c641d16d11fb02955e

Tip:
  Using './ontology info status ffb0a02847d31641f05a498a19a4f9f7e7d7616d0ab163c641d16d11fb02955e' to query transaction status.
```

在输出的信息中，`Contract Address` 为合约的哈希地址，是对智能合约接口进行调用的依据。

> **注意**：
> - 节点默认的 `gas price` 为 500（测试模式下为 0）。
> - 账户实际支付的 `ONG` 费用为 `gasprice × gaslimit`。
> - 交易池会按照 `gas price` 由高到低的顺序，对交易池队列中的交易进行处理。
> - 部署智能合约时，`gas limit` 必须大于 `20000000`（合约的操作码 `opcode` 执行上限数 ）。
> - 交易的 `gas price` 不能小于接收该交易的节点所设置的最低 `gas price`，否则交易会被拒绝。
> - 交易的 `gas limit` 不能小于接收该交易的节点所设置的最低 `gas limit`，否则交易会被拒绝。

根据返回的交易哈希，我们可以查询智能合约部署交易的执行状态，`State` 字段为 `1`，表示智能合约部署成功。

```shell
$ ontology info status ffb0a02847d31641f05a498a19a4f9f7e7d7616d0ab163c641d16d11fb02955e
Transaction states:
{
   "TxHash": "ffb0a02847d31641f05a498a19a4f9f7e7d7616d0ab163c641d16d11fb02955e",
   "State": 1,
   "GasConsumed": 0,
   "Notify": []
}
```

> **注意**：通过 `ontology info status <TxHash>` 命令查询合约执行状态，如果返回 `UNKNOWN TRANSACTION`，表示该交易尚未被打包到区块中，可能有多种情况。
> - 交易还在交易池中排队等待被打包。
> - 交易因为 `gaslimit` 或者 `gasprice` 设置过低，导致交易被拒绝。

此外，你可以通过 `--account` 选项指定支付部署智能合约所需 `ONG` 的钱包账户。

## 执行智能合约

在本体客户端 `Ontology-CLI` 中，支持的参数类型为 `array`、`bytearray`、`string`、`int` 以及 `bool`。

- `array` 表示对象数组，数组元素可以是 `NeoVM` 支持的任意数量、任意类型的值。
- `bytearray` 表示字节数组，输入时需要将字节数组编码成十六进制字符串，如 `[]byte("HelloWorld")` 编码成十六进制字符串 `48656c6c6f576f726c64`。
- `string` 表示字符串字面值。
- `int` 表示整数。
- `bool` 表示布尔型变量，用 `true` 和 `false`表示。

> **注意**：`NeoVM` 虚拟机不支持浮点数值，需要将浮点数转换成整数。

`Ontology-CLI` 使用前缀法构造参数，参数前使用类型标识标注类型。

- 字符串参数表示为 `string:hello`。
- 整数参数表示为 `int:10`。
- 布尔类型参数表示为 `bool:true`。

多个参数使用","分隔。对象数组array类型用"[ ]"表示数组元素范围，如 [int:10,string:hello,bool:true]。


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
