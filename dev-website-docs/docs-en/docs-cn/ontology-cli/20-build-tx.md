
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