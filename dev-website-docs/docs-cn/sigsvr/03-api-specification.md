
## 概述

在默认情况下，签名机监听在本地的 `20000` 端口上. 其他服务通过 `HTTP POST` 方法请求服务。

```shell
curl http://localhost:20000/cli -X POST -H "Content-Type:application/json"
```

<section class = "info">
  <ul>
    <li>如果你想更改端口号，请使用 <code>--cliport</code> 选项进行配置。</li>
    <li>如果你想提供外部访问，请使用 <code>--cliaddress</code> 选项进行配置。</li>
  </ul>
</section>

### 请求结构

```json
{
  qid: "1",
  method: "method",
  account: "AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa",
  pwd: "password",
  params: {}
}
```

### 响应结构

```json
{
  qid: "1",
  method: "method",
  result: {
    signed_tx: "0000000"
  },
  error_code: 0,
  error_info: ""
}
```

### 错误码

| Error code | Error description         |
| :--------- | :------------------------ |
| 1001       | Invalid http method       |
| 1002       | Invalid http request      |
| 1003       | Invalid request parameter |
| 1004       | Unsupported method        |
| 1005       | Account is locked         |
| 1006       | Invalid transactions      |
| 1007       | ABI is not found          |
| 1008       | ABI is not matched        |
| 9999       | Unknown error             |

## 创建账户

- 请求

```json
{
  "qid":"1",
  "method":"createaccount",
  "pwd":"password",
  "params":{}
}
```

- 响应

```json
{
  "qid": "t",
  "method": "createaccount",
  "result": {
      "account": "AWn31ZiNpXk55C7R4dvoVGBBMvTxG6sh6f"
  },
  "error_code": 0,
  "error_info": ""
}
```

## 导出账户

- 请求

```json
{
  "qid":"t",
  "method":"exportaccount",
  "params":{}
}
```

- 响应

```json
{
    "qid": "t",
    "method": "exportaccount",
    "result": {
        "wallet_file": "./wallet_2018_02_25_17_31_59.dat",
        "account_num": 3
    },
    "error_code": 0,
    "error_info": ""
}
```

## 交易签名

- 请求

```json
{
  "qid":"1",
  "method":"sigrawtx",
  "account":"AR1ibsqRjiuZgBuHhVbpUpg8yUfC9QHXBp",
  "pwd":"password",
  "params":{
    "raw_tx":"00d130c56babf401000000000000204e000000000000655767ac654e29c7afdd1a1ba08ff9b562c884016e00c66b6a14655767ac654e29c7afdd1a1ba08ff9b562c88401c86a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a51c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b650000"
  }
}
```

- 响应

```json
{
  "qid": "1",
  "method": "sigrawtx",
  "result": {
    "signed_tx": "00d130c56babf401000000000000204e000000000000655767ac654e29c7afdd1a1ba08ff9b562c884016e00c66b6a14655767ac654e29c7afdd1a1ba08ff9b562c88401c86a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a51c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b6500014140a92bac20ea3949a0dd8b32173d789c292ec509aeb936a8658789c68a43c47a0ae83613292210da3dca78cc47995ecdd9c27f9d3ae3e16587212151b4059ad1ac232102f41138e3899872579ca713d90b889c83b3406a67e5799fa8448ec4e0a10c4cacac"
  },
  "error_code": 0,
  "error_info": ""
}
```

## 多重签名

- 请求

```json
{
  "qid":"1",
  "method":"sigmutilrawtx",
  "account":"AR1ibsqRjiuZgBuHhVbpUpg8yUfC9QHXBp",
  "pwd":"password",
  "params":{
    "raw_tx":"00d130c56babf401000000000000204e000000000000655767ac654e29c7afdd1a1ba08ff9b562c884016e00c66b6a14655767ac654e29c7afdd1a1ba08ff9b562c88401c86a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a51c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b650000",
    "m":2,
    "pub_keys":[
        "02f41138e3899872579ca713d90b889c83b3406a67e5799fa8448ec4e0a10c4cac",
        "02b76e86481df6e9814b203a41a0b040c87807d1bcfd18f8ea69c7d73ebf2b944a"
    ]
  }
}
```

- 响应

```json
{
  "qid": "1",
  "method": "sigmutilrawtx",
  "result": {
      "signed_tx": "00d130c56babf401000000000000204e000000000000655767ac654e29c7afdd1a1ba08ff9b562c884016e00c66b6a14655767ac654e29c7afdd1a1ba08ff9b562c88401c86a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a51c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65000141409cbc821f9905ea5682796f5059083128fa370f3abd7054110e0ea06e630a63db4dedb4cc32ed32884b2ca31fb7d005a5d16e74f33652e79d502c9f8cc1d03c4147522102b76e86481df6e9814b203a41a0b040c87807d1bcfd18f8ea69c7d73ebf2b944a2102f41138e3899872579ca713d90b889c83b3406a67e5799fa8448ec4e0a10c4cac52ae"
  },
  "error_code": 0,
  "error_info": ""
}
```

## 数据签名

- 请求

```shell
{
  "qid":"1",
  "method":"sigdata",
  "account":"AR1ibsqRjiuZgBuHhVbpUpg8yUfC9QHXBp",
  "pwd":"password",
  "params":{
    "raw_data":"48656C6C6F20776F726C64"
  }
}
```

- 响应

```shell
{
  "qid": "1",
  "method": "sigdata",
  "result": {
    "signed_data": "96c5901e36206fdb7f5086096d9465d47f5c6192c77d226244e701a52d64c9d26b79fc538db3e0d44df951d7a0146f07f7550af169c4499372ca7f72b5643cb0"
  },
  "error_code": 0,
  "error_info": ""
}
```

## 转账交易

- 请求



- 响应



## 智能合约

### Native 合约调用



### NeoVm 合约调用
