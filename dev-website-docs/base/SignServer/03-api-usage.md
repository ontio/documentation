


- [API Endpoint](#api-endpoint)
- [Supported Request Methods](#supported-request-methods)
- [Request structure](#request-structure)
- [Response structure](#response-structure)
  - [Error Codes](#error-codes)

## API Endpoint

The signature service is a JSON RPC server available by default at:
```
http://localhost:20000/cli
```

## Supported Request Methods
```
POST
```

## Request structure

```
{
  qid: "XXX",      // Request ID. The response will echo back the same qid
  method: "XXX",   // Requested method name
  account: "XXX",  // Account for sign
  pwd: "XXX",      // Account password
  params: {}       // Input parameters for the requested method
}
```

## Response structure

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

### Error Codes

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
