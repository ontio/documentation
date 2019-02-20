


- [API 端点](#api-端点)
- [支持的请求方法](#支持的请求方法)
- [请求结构](#请求结构)
- [响应结构](#响应结构)
  - [错误码](#错误码)

## API 端点
签名Server提供通过下面的链接提供rpc服务
```
http://localhost:20000/cli
```

## 支持的请求方法
```
POST
```

## 请求结构

```
{
  qid: "XXX",      // Request ID. The response will echo back the same qid
  method: "XXX",   // Requested method name
  account: "XXX",  // Account for sign
  pwd: "XXX",      // Account password
  params: {}       // Input parameters for the requested method
}
```

## 响应结构

```
{
  qid: "XXX",         // Request ID
  method: "XXX",      // Requested method name
  result: {           // Response result
    signed_tx: "XXX"  // Signed transaction
  },
  error_code: 0,      // Error code，zero represents success, non-zero represents failure
  error_info: ""      // Error description
}
```

### 错误码

Error code | Error description
---------- | -----------------
1001       | Invalid http method
1002       | Invalid http request
1003       | Invalid request parameter
1004       | Unsupported method
1005       | Account is locked
1006       | Invalid transactions
1007       | ABI is not found
1008       | ABI is not matched
9999       | Unknown error
