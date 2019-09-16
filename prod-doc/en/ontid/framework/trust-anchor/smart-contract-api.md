# Claim - smart contract api

代码预览:

```c++
{
	"contractHash": "",
	"abi": {
		"hash": "",
		"entrypoint": "Main",
		"functions": [{
			"name": "Main",
			"parameters": [{
				"name": "operation",
				"type": "String"
			}, {
				"name": "args",
				"type": "Array"
			}],
			"returntype": "ByteArray"
		}, {
			"name": "Commit",
			"parameters": [{
				"name": "claimId",
				"type": "ByteArray"
			}, {
				"name": "committerId",
				"type": "ByteArray"
			}, {
				"name": "ownerId",
				"type": "ByteArray"
			}],
			"returntype": "Boolean"
		}, {
			"name": "Revoke",
			"parameters": [{
				"name": "claimId",
				"type": "ByteArray"
			}, {
				"name": "ontId",
				"type": "ByteArray"
			}],
			"returntype": "Boolean"
		}, {
			"name": "GetStatus",
			"parameters": [{
				"name": "claimId",
				"type": "ByteArray"
			}],
			"returntype": "ByteArray"
		}, {
			"name": "Upgrade",
			"parameters": [{
				"name": "code",
				"type": "ByteArray"
			}],
			"returntype": "Boolean"
		}],
		"events": [{
			"name": "ErrorMsg",
			"parameters": [{
				"name": "id",
				"type": "ByteArray"
			}, {
				"name": "error",
				"type": "String"
			}],
			"returntype": "Void"
		}, {
			"name": "Push",
			"parameters": [{
				"name": "id",
				"type": "ByteArray"
			}, {
				"name": "msg",
				"type": "String"
			}, {
				"name": "args",
				"type": "ByteArray"
			}],
			"returntype": "Void"
		}]
	}
}
```



#### 合约API：

##### 合约地址：729635b7135e9eab97daed4e0b48e9f18a71410d

1. 声明存证

```
bool Commit(byte[] claimId, byte[] committerOntId, byte[] ownerOntId);
```

可信声明存证合约提供存证服务即存证可信声明Id，签发者ONT身份，属主ONT身份等信息，以及记录可用性信息即是否被吊销等信息。



提供的接口主要是

2. 存证查询接口

```
byte[] GetStatus(byte[] claimId);
```

返回声明的状态，包含两部分信息：

- 状态：”未存证“， ”已存证“， ”存证被吊销“；

- 存证人ONT ID。

  

3. 吊销声明

```
bool Revoke(byte[] claimId, byte[] revokerOntId);
```

当且仅当声明已被存证，且revokerOntId等于存证人的ONT身份时，才能成功吊销；否则，吊销失败。

在存证合约中，声明的唯一标识就是声明的ID，这个将被作为第一个参数，committerOntId就是存证人的ONT身份，ownerOntId是可信声明属主的ONT身份。

当且仅当该声明没有被存证过，且`Commit`函数是由committer调用，才能存证成功；否则，存证失败。

存证成功后，该声明的状态就是*已存证*（committed）。