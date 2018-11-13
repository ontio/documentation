# API 方法

- [签名任意的数据](#签名任意的数据)
- [签名原始交易](#签名原始交易)
- [签署多重签名交易](#签署多重签名交易)


## 签名任意的数据
签名任意十六进制编码的字符串


### 方法名
```
sigdata
```


### 请求参数

```
{
  "raw_data": "XXX"       // Unsigned data, Note that data must be encode as a hex string.
}
```


### 响应结果

```
{
  "signed_data": "XXX"    // Signed data, Note that data was encoded as a hex string.
}
```


### 例子

请求:
```
{
  "qid": "t",
  "method": "sigdata",
  "account": "XXX",
  "pwd": "XXX",
  "params": {
  	"raw_data": "48656C6C6F20776F726C64" // Hello world
  }
}
```

响应:
```
{
  "qid": "t",
  "method": "sigdata",
  "result": {
    "signed_data": "cab96e...7260cb"
  },
  "error_code": 0,
  "error_info": ""
}
```

## 签名交易

签名一个交易.

### 方法名
```
sigrawtx
```


### 请求参数

```
{
  "raw_tx": "XXX"      // Unsigned transaction
}
```


### Response result

```
{
  "signed_tx": "XXX"   //Signed transaction
}
```


### 例子

请求:
```
{
  "qid": "1",
  "method": "sigrawtx",
  "account": "XXX",
  "pwd": "XXX",
  "params": {
    "raw_tx": "00d141...0a0000"
  }
}
```

响应:
```
{
  "qid": "1",
  "method": "sigrawtx",
  "result": {
    "signed_tx": "00d141...00c6bb"
  },
  "error_code": 0,
  "error_info": ""
}
```

## 签署一个多重签名的交易

用一个指定的账户进行多签，如果签名机需要多个账户签名，签名机需要为每个签名账户调用该方法进行签名。

### 方法名
```
sigmutilrawtx
```


### 请求参数

```
{
  "raw_tx": "XXX", // Unsigned transaction
  "m": xxx         // The minimum number of signatures required for multiple signatures
  "pub_keys": []   // Public key list of signature
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
  "qid": "1",
  "method": "sigmutilrawtx",
  "account": "XXX",
  "pwd": "XXX",
  "params": {
    "raw_tx": "00d124...0a0000",
    "m": 2,
    "pub_keys": [
      "1202039b196d5ed74a4d771ade78752734957346597b31384c3047c1946ce96211c2a7",
      "120203428daa06375b8dd40a5fc249f1d8032e578b5ebb5c62368fc6c5206d8798a966"
    ]
  }
}
```

响应:
```
{
  "qid": "1",
  "method": "sigmutilrawtx",
  "result": {
    "signed_tx": "00d124...c5a41a"
  },
  "error_code": 0,
  "error_info": ""
}
```
