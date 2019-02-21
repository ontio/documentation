
# API Convenience Methods
In order to simplify the signature process of common transaction convenience methods are provided.

- [Sign Transfer Transaction](#sign-transfer-transaction)
- [Sign Ontology Native Contract Invoke](#sign-native-contract-invoke)
- [Sign NeoVM Contract Invoke](#sign-neovm-contract-invoke)
- [Sign NeoVM Contract Invoke w/ ABI](#sign-neovm-contract-invoke-w/-abi)

## Network Fees
By default, each of the following methods will use the signing account to pay the network fee.

If you would like another account will pay the network fee:

1. Specify the payer account address as an optional input parameter.
2. Use the signed output, along with the payer account, as the input for a subsequent call to the `sigrawtx` method.

## Sign Transfer Transaction

An asset transfer from one account to another.

### Method Name
```
sigtransfertx
```


### Request parameters
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

Response:
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


## Sign Ontology Native Contract Invoke

The Native contract invocation transaction is constructed and signed according to the ABI.

Note:
This method requires ABI files for any contract to be invoked. These files should be located by default in the `./abi` directory, unless an override was provided as a parameter when the service was started using `--abi`. If no abi file is found for a given contract address, this method will return a 1007 error.

### Method Name
```
signativeinvoketx
```

### Request parameters

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

### Response result

```
{
  "signed_tx": "XXX"  // Signed Transaction
}
```

### Example 1: Transfer transaction via Native Contract Invoke

Request:
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

Response:
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

### Example 2: Withdraw ONG

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


## Sign NeoVM Contract Invoke

The NeoVM contract parameter supports the datatypes array, bytearray, string, int, and bool. When constructing parameters, it is necessary to provide parameter types and parameter values. The parameter values must all be cast to strings. The array datatype is an array that also contains type/value objects, which supports all the NeoVM supported parameter types.

### Method Name
```
signeovminvoketx
```

### Request parameters

```
{
  "gas_price": XXX,  // gasprice
  "gas_limit": XXX,  // gaslimit
  "address": "XXX",  // The NeoVM contract address to invoke
  "params": []       // The parameters of the NeoVM contract. All values are string type.
  "payer": "XXX",    // (OPTIONAL) The fee payer's account address
}
```

### Response result

```
{
  "signed_tx": "XXX"  // Signed Transaction
}
```

### Examples

Request:
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

Response:
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


## Sign NeoVM Contract Invoke w/ ABI

NeoVM contract invoke transaction constructed and signed according to the provided ABI.
Note that the parameter values must all be cast to strings.

### Method Name
```
signeovminvokeabitx
```

### Request parameters

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

### Response result

```
{
  "signed_tx": "XXX"      // Signed Transaction
}
```

### Examples

Request:
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

Response:
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
