### CFCA real name  certification claim template

Claim of personal real-name information issued by CFCA.


```json
{
	"Id":"g84aj0f56d106a1c92e891b687fc4d9546fdf2en74a364776fa65a9j86b0387j",
	"Context":"https://example.com/realname/template/v1",
	"Content":{
		"IdNumber": "510806199002122991",
		"Name": "zhangsan"
	},
	"Metadata":{
		"CreateTime":"2018-02-02T12:11:50Z",
		"Issuer":"did:ont:THeNuzzVL5HWartjLpZDZHB1jNqeLFncCP",
		"Subject":"did:ont:TA5ubZyowXUdfTyXwy3Q7FkxJwRuNXC9aZ",
		"Revocation": { 
			"Type": "Contract",
			"Addr": "8055b362904715fd84536e754868f4c8d27ca3f6"
		}
	},
	"Signature":{
		"PublicKeyId": "did:ont:THeNuzzVL5HWartjLpZDZHB1jNqeLFncCP#keys-1",
		"Format":"pgp",
		"Algorithm":"ECDSAwithSHA256",
		"Value":"AUak5urs4L989dk1im4ACjutojS1EnfqRnuOrUPlyiPG6tCnDunCdDf50RlQr9mtj+YnvTq0yeqIxf72x8PAiRk="
	},
	
	"Proof":{
		"Type":"MerkleProof",
		"TxnHash":"0491abf615880f034874f1e8934f679b3bfa692036ba0648968e550a41e0038e",
		"ContractAddr": "8055b362904715fd84536e754868f4c8d27ca3f6",
		"BlockHeight":69,
		"MerkleRoot":"c64695da1f7ce728209bdaa7a1aa5be3143aa56d4e52c4f28346980c84958ca7",
		"Nodes":[
			{
				"Direction":"Right",
				"TargetHash":"08f1f8ac790b936b06aeb15aa5afa325a0ac05d7dc501eba456560bb260c4542"
			}, 
			{
				"Direction":"Left",
				"TargetHash":"0e9f352bd54c28577f774e6077433e98a0a2bc991512a0f70fceb6c8e2e55ae1"
			}
		]
	}
}
```

Content format definition as JSON file:
```
{
    "Type": "claim:cfca_authentication", 
    "IdNumber": {
        "Doc": "Unique number of certificate",
        "ValType": "String"
    }, 
    "Name": {
        "Doc": "The full name of certificate owner",
        "ValType": "String"
    }
}

```
