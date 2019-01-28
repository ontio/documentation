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