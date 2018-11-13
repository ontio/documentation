# API 便利方法
为了简化普通交易的签名过程，提供了下面的api。

- [签名转账交易](#签名转账交易)
- [签名 Ontology Native 合约调用](#签名-Ontology-Native-合约调用)
- [签名 NeoVM 合约调用](#签名-NeoVM-合约调用)
- [签名 NeoVM 使用API的合约调用](#签名-NeoVM-使用API的合约调用)

## 网络费用
下面的所有方法默认使用签名账户支付网络费。
如果你想用其他账户支付网络费：

1. 在输入参数时指定peyer地址。
2. 使用代签名的输出以及付款人账户作为后续调用`sigrawtx`方法的输入。

## 签名转账交易

资产从一个账户到另一个账户转账。


### 方法名
```
sigtransfertx
```


### 请求参数
```
{
  "gas_price": XXX,  // gasprice
  "gas_limit": XXX,  // gaslimit
  "asset": "ont",    // asset: ont or ong
  "from": "XXX",     // Payment account
  "to": "XXX",       // Receipt address
  "amount": "XXX"    // Transfer amount. Note that since the precision of ong is 9, it is necessary to multiply the actual transfer amount by 1000000000 when making ong transfer.
  "payer": "XXX",    // (OPTIONAL) The fee payer's account address
}
```


### 响应结果

```
{
  "signed_tx": "XXX" // Signed transaction
}
```


### 例子

请求:
```
{
  "qid": "t",
  "method": "sigtransfertx",
  "account": "XXX",
  "pwd": "XXX",
  "params": {
    "gas_price": 0,
    "gas_limit": 20000,
    "asset": "ont",
    "from": "ATACcJPZ8eECdWS4ashaMdqzhywpRTq3oN",
    "to": "AeoBhZtS8AmGp3Zt4LxvCqhdU4eSGiK44M",
    "amount": "10"
  }
}
```

响应:
```
{
  "qid": "t",
  "method": "sigtransfertx",
  "result": {
    "signed_tx": "00d118...efea9c"
  },
  "error_code": 0,
  "error_info": ""
}
```


## 签名 Ontology Native 合约调用

Native合约调用交易是通过abi文件进行构造和签名。

注意:
该方法需要abi文件对于任何合约的调用，这些文件默认的路径会`./abi`，除非当server启动的时候使用`--abi`指定了特定的abi文件目录，如果对于给定的合约地址，没有发现对应的abi文件，将会返回1007错误。

### 方法名
```
signativeinvoketx
```

### 请求参数

```
{
  "gas_price": XXX,  // gasprice
  "gas_limit": XXX,  // gaslimit
  "address": "XXX",  // The native contract address to invokes
  "method": "XXX",   // The method that invokes native contract
  "version": 0,      // The version that invokes native contract
  "params": []       // The parameters of the Native contract are constructed according to the ABI of calling method. All values ​​are string type.
  "payer": "XXX",    // (OPTIONAL) The fee payer's account address
}
```

### 响应结果

```
{
  "signed_tx": "XXX"  // Signed Transaction
}
```

### 例子1: 通过Native合约调用执行的转账交易

请求:
```
{
  "pid": "t",
  "method": "signativeinvoketx",
  "account": "XXX",
  "pwd": "XXX",
  "params": {
    "gas_price": 0,
    "gas_limit": 20000,
    "address": "0100000000000000000000000000000000000000",
    "method": "transfer",
    "version": 0,
    "params": [
      [
        [
          "ATACcJPZ8eECdWS4ashaMdqzhywpRTq3oN",
          "AeoBhZtS8AmGp3Zt4LxvCqhdU4eSGiK44M",
          "1000"
        ]
      ]
    ]
  }
}
```

响应:
```
{
  "qid": "t",
  "method": "signativeinvoketx",
  "result": {
    "signed_tx": "00d161...ea58ac"
  },
  "error_code": 0,
  "error_info": ""
}
```

### 例子 2: 提取ONG

```
{
  "qid": "t",
  "method": "signativeinvoketx",
  "account": "ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48",  // withdraw address
  "pwd": "XXX",
  "params": {
    "gas_price": 5000,
    "gas_limit": 20000,
    "address": "0200000000000000000000000000000000000000",
    "method": "transferFrom",
    "version": 0,
    "params": [
      "ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48",         // withdraw address
      "AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV",         // ONT contract address (in base58 style)
      "ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48",         // ONG receive address. Note that receive address can different with the withdraw address
      "310860000000000"                             // withdraw ong amount. Note that ONG has 9 decimals
    ]
  }
}
```


## 签名 NeoVM 合约调用

NeoVm合约参数支持的数据类型是array, bytearray, string, int, and bool，参数值值必须转换成strings, array数据类型是一个包含类型和值数组对象，并且该类型必须是NeoVm支持的。
 
### 方法名
```
signeovminvoketx
```

### 请求参数

```
{
  "gas_price": XXX,  // gasprice
  "gas_limit": XXX,  // gaslimit
  "address": "XXX",  // The NeoVM contract address to invoke
  "params": []       // The parameters of the NeoVM contract. All values are string type.
  "payer": "XXX",    // (OPTIONAL) The fee payer's account address
}
```

### 响应结果

```
{
  "signed_tx": "XXX"  // Signed Transaction
}
```

### 例子

请求:
```
{
  "qid": "t",
  "method": "signeovminvoketx",
  "account": "XXX",
  "pwd": "XXX",
  "params": {
    "gas_price": 0,
    "gas_limit": 50000,
    "address": "8074775331499ebc81ff785e299d406f55224a4c",
    "version": 0,
    "params": [
      {
        "type": "string",
        "value": "Time"
      },
      {
        "type": "array",
        "value": [
          {
            "type": "string",
            "value": ""
          }
        ]
      }
    ]
  }
}
```

响应:
```
{
  "qid": "t",
  "method": "signeovminvoketx",
  "result": {
    "signed_tx": "00d18f...034cc1"
  },
  "error_code": 0,
  "error_info": ""
}
```


## 签名 NeoVM 使用API的合约调用

通过提供的abi文件构造和签名Neovm合约调用

注意：参数值必须转换成strnigs类型的值

### 方法名
```
signeovminvokeabitx
```

### 请求参数

```
{
  "gas_price": XXX,       // gasprice
  "gas_limit": XXX,       // gaslimit
  "address": "XXX",       // The NeoVM contract address to invoke
  "params": [XXX],        // The parameters of the NeoVM contract are constructed according to the ABI of calling method. All values are string type.
  "contract_abi": XXX,    // The ABI of contract
  "payer": "XXX",         // (OPTIONAL) The fee payer's account address

}
```

### 响应结果

```
{
  "signed_tx": "XXX"      // Signed Transaction
}
```

### 例子

请求:
```
{
  "qid": "t",
  "method": "signeovminvokeabitx",
  "account": "XXX",
  "pwd": "XXX",
  "params": {
    "gas_price": 0,
    "gas_limit": 50000,
    "address": "80b82b5e31ad8b7b750207ad80579b5296bf27e8",
    "method": "add",
    "params": ["10", "10"],
    "contract_abi": {
      "hash": "0xe827bf96529b5780ad0702757b8bad315e2bb8ce",
      "entrypoint": "Main",
      "functions": [
        {
          "name": "Main",
          "parameters": [
            {
              "name": "operation",
              "type": "String"
            },
            {
              "name": "args",
              "type": "Array"
            }
          ],
          "returntype": "Any"
        },
        {
          "name": "Add",
          "parameters": [
            {
              "name": "a",
              "type": "Integer"
            },
            {
              "name": "b",
              "type": "Integer"
            }
          ],
          "returntype": "Integer"
        }
      ],
      "events": []
    }
  }
}
```

响应:
```
{
  "qid": "t",
  "method": "signeovminvokeabitx",
  "result": {
    "signed_tx": "00d16a...335eac"
  },
  "error_code": 0,
  "error_info": ""
}
```
