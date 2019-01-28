
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
