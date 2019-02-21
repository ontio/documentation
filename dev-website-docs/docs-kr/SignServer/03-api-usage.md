
# API 용법

- [API 엔드 포인트](#api-endpoint)
- [지원되는 요청 메서드](#supported-request-methods)
- [요청 구조](#request-structure)
- [응답 구조](#response-structure)
  - [에러 코드](#error-codes)

## API 엔드 포인트

Signature Service는 기본적으로 다음 위치에서 사용할 수 있는 JSON RPC 서버:
```
http://localhost:20000/cli
```

## 지원되는 요청 메서드
```
POST
```

## 요청 구조

```
{
  qid: "XXX",      // Request ID. The response will echo back the same qid
  method: "XXX",   // Requested method name
  account: "XXX",  // Account for sign
  pwd: "XXX",      // Account password
  params: {}       // Input parameters for the requested method
}
```

## 응답 구조

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

### 에러 코드

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
