
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

- `POST` 方法

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

- `POST` 方法

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
