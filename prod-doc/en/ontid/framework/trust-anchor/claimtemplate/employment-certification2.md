### Employment certification claim template

Claim of employment certification issued by the company to employees.

```json
{
	"Id":"ca4ab2f56d106dac92e891b6f7fc4d9546fdf2eb94a364208fa65a9996b03ba0",
	"Context":"https://example.com/salary/template/v1",
	"Content":{
		"IdNumber": "510806199002122991",
		"Name": "zhangsan",
		"Gender":"male",
		"JobTitle": "SoftwareEngineer",
		"MonthlySalary": 3000.00,
		"Hiredata": "2017-03-20"
	},
	"Metadata":{
		"CreateTime":"2017-04-01T12:01:20Z",
		"Issuer":"did:ont:TRAtosUZHNSiLhzBdHacyxMX4Bg3cjWy3r",
		"Subject":"did:ont:SI59Js0zpNSiPOzBdB5cyxu80BO3cjGT70",
		"Expires":"2018-06-01",
		"Revocation": { 
			"Type": "Contract",
			"Addr": "8055b362904715fd84536e754868f4c8d27ca3f6"
		}
	},
	"Signature":{
		"PublicKeyId": "did:ont:TRAtosUZHNSiLhzBdHacyxMX4Bg3cjWy3r#keys-1",
		"Format":"pgp",
		"Algorithm":"ECDSAwithSHA256",
		"Value":"rsjaenrxJm8qDmhtOHNBNOCOlvz/GC1c6CMnUb7KOb1jmHbMNGB63VXhtKflwSggyu1cVBK14/0t7qELqIrNmQ=="
	},
	"Proof":{
		"Type":"MerkleProof",
		"TxnHash":"c89e76ee58ae6ad99cfab829d3bf5bd7e5b9af3e5b38713c9d76ef2dcba2c8e0",
		"ContractAddr": "8055b362904715fd84536e754868f4c8d27ca3f6",
		"BlockHeight":10,
		"MerkleRoot":"bfc2ac895685fbb01e22c61462f15f2a6e3544835731a43ae0cba82255a9f904",
		"Nodes":[
			{
				"Direction":"Right",
				"TargetHash":"2fa49b6440104c2de900699d31506845d244cc0c8c36a2fffb019ee7c0c6e2f6"
			}, 
			{
				"Direction":"Left",
				"TargetHash":"fc4990f9758a310e054d166da842dab1ecd15ad9f8f0122ec71946f20ae964a4"
			}
		]
	}
}
```


Content format definition JSON file：
```
{
    "Type": "claim:employment_authentication", 
    "IdNumber": {
        "Doc": "Unique number of certificate",
        "ValType": "String"
    }, 
    "Name": {
        "Doc": "The full name of certificate owner",
        "ValType": "String"
    },
    "Gender": {
        "Doc": "The gender of certificate owner",
        "ValType": "String"
    }, 
    "JobTitle": {
        "Doc": "The job title of certificate owner",
        "ValType": "String"
    }, 
    "MonthlySalary": {
        "Doc": "The monthly salary of certificate owner",
        "ValType": "double"
    },
    "HireDate": {
        "Doc": "Hiring date",
        "ValType": "Time"
    }
}

```
