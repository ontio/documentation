# ONT Auth transaction specification

This specification works from mobile-app `ONT Auth` to `signing server`.

Ref., https://dev-docs.ont.io/#/docs-en/dApp-Integration/02-DAppDocking-QRcode

## 1. Transaction params

A sample of transaction parameter.

```json
{
	"params": {
		"invokeConfig": {
			"gasLimit": 40000,
			"contractHash": "fb12993d6f13a2ec911f3bbfe534be90e4deeca4",
			"functions": [{
				"args": [{
					"name": "fulldomain",
					"value": "String:ning.on.ont"
				}, {
					"name": "registerdid",
					"value": "String:%ontid"
				}, {
					"name": "idx",
					"value": 1
				}, {
					"name": "validto",
					"value": -1
				}],
				"operation": "registerDomain"
			}],
			"payer": "AcdBfqe7SG8xn4wfGrtUbbBDxw2x1e8UKm",
			"gasPrice": 500
		},
		"ontidSign": true,
		"callback": "http://192.168.3.121:7878/api/v1/contract/invoke"
	}
}
```

### 1.1 invokeConfig

| Field Name   | Type         | Description                                                  |
| ------------ | ------------ | ------------------------------------------------------------ |
| gasLimit     | uint         | Gas fee to charge at most                                    |
| gasPrice     | uint         | Gas fee to charge per step                                   |
| contractHash | String       | The hash of contract                                         |
| functions    | Object array | Functions to call in this transaction                        |
| payer        | Address      | Payer of the transaction, to pay gas fee for the sender, leave blank for the sender to pay gas fee |

#### 1.1.1 function param

| Field Name | Type         | Description                                                  |
| ---------- | ------------ | ------------------------------------------------------------ |
| args       | Object array | Arguments used for the function call, each item stands for one arg<br/>The arg object is in the form of "`name : value`" pair, value type can be compound object, the type shall be defined in the value field, in the form of "`type:data`". |
| operation  | String       | The function name to call                                    |

`Arg` field of function param supports complex data type. For detail support, please contact Ontology dev community.

- Basic type:

  - boolean, e.g., `true`, `false`
  - integer, e.g., -1, 100
  - other types use `String` type, in form of "type:data". Type includes:
    - String, e.g., "String:hello"
    - ByteArray, e.g., "ByteArray:array string"
    - Long, e.g., "Long:100000000000"
    - Address, e.g., "Address:AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ"

- Array: e.g.,
  - ```json
    [
    	true, 
    	100, 
    	"Long:100000000000", 
    	"Address:AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ", 
    	"ByteArray:aabb", 
    	"String:hello", 
    	[
    		true, 
    		100
    	], 
    	{
    		"key": 6
    	}
    ]
    ```
  
- Map: e.g.,

  - ```json
    {
    	"key": "String:hello",
    	"key1": "ByteArray:aabb",
    	"key2": "Long:100000000000",
    	"key3": true,
    	"key4": 100,
    	"key5": [100],
    	"key6": {
    		"key": 6
    	}
    }
    ```

Esp., value start with "%" stands for a placeholder of the transaction, the vale will be replaced by `ONT Auth`.

| Placeholder Name | Description                                                  |
| ---------------- | ------------------------------------------------------------ |
| ontid            | The ONT ID to be signed by ONT Auth                          |
| msg              | The random message generated along with QA code to identify the scan request |
| expire           | Expire date time of the response, specially used in Ontology claim system |
| ~~claim~~        | [**TBD**] ~~Matched claim object~~                           |

### 1.2 ontidSign

In boolean type, indicate whether the action call shall be signed with user ONT ID. 

### 1.3 callback

ONT Auth will access the "`callback`" function after the transaction is constructed, the `callback` function will then send the transaction to Ontology blockchain.