

- [Sign Arbitrary Data](#sign-arbitrary-data)
- [Sign Raw Transaction](#sign-raw-transaction)
- [Sign Multiple Signature Raw Transaction](#sign-multiple-signature-raw-transaction)


## Sign Arbitrary Data

Signs arbitrary data as long as it is encoded as a hex string.


### Method Name
```
sigdata
```


### Request parameters

```
{
  "raw_data": "XXX"       // Unsigned data, Note that data must be encode as a hex string.
}
```


### Response result

```
{
  "signed_data": "XXX"    // Signed data, Note that data was encoded as a hex string.
}
```


### Examples

Request:
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

Response:
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

## Sign Raw Transaction

Signs a raw transaction.

### Method Name
```
sigrawtx
```


### Request parameters

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


### Examples

Request:
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

Response:
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

## Sign Multiple Signature Raw Transaction

Signs a multi signature raw transaction with a single specific account. If more than one account within the sigsvr needs to sign, the server needs to be called once for each signer.

### Method Name
```
sigmutilrawtx
```


### Request parameters

```
{
  "raw_tx": "XXX", // Unsigned transaction
  "m": xxx         // The minimum number of signatures required for multiple signatures
  "pub_keys": []   // Public key list of signature
}
```


### Response result

```
{
  "signed_tx": "XXX" // Signed transaction
}
```


### Examples

Request:
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

Response:
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
