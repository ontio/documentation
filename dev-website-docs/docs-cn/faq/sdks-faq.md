
#### 1. 本体提供了哪些语言 SDK？

SDK 链接 [https://dev-docs.ont.io/#/docs-cn/SDKs/00-overview](https://dev-docs.ont.io/#/docs-cn/SDKs/00-overview)

ts sdk的测试代码：[https://github.com/ontio/ontology-ts-sdk/tree/master/test](https://github.com/ontio/ontology-ts-sdk/tree/master/test)

#### 2. 多签地址如何生成？

请参考 [例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/MutiSignDemo.java)
```

    com.github.ontio.account.Account[] accounts = new com.github.ontio.account.Account[]{acct1,acct2,acct3};
    int M = 2;
    byte[][] pks = new byte[accounts.length][];
    for(int i=0;i<pks.length;i++){
        pks[i] = accounts[i].serializePublicKey();
    }
    Address sender = Address.addressFromMultiPubKeys(M, pks);

```
#### 3. 如何实现ONT多转多？

```
 State state1 = new State(sender1,recvAddr,amount);
 State state2 = new State(sender2,recvAddr,amount2);
 ransaction tx = ontSdk.nativevm().ont().makeTransfer(new State[]{state1,state2},sender1.toBase58(),30000,0);
```
请参考 [例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/MakeTxWithoutWalletDemo.java)


#### 4. 如何实现ONT/ONG转账？

```
 ontSdk.nativevm().ont().sendTransfer(acct0,"AUe2KKPnNMnM7hLHj6dEPJ4PA2m4pyJt2d",200,acct0,gaslimit,gasprice);
```

ONT 转账Java参考例子 [https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/OntDemo.java](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/OntDemo.java)

ONG 转账Java参考例子 [https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/OngDemo.java](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/OngDemo.java)

#### 5. SDK 调用合约例子？


参考例子[https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/PunicaInitDemo.java](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/PunicaInitDemo.java)


#### 6. 通过 Json 构造交易？

参考例子 [https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/MakeTxWithJsonDemo.java](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/MakeTxWithJsonDemo.java)
```
{
	"action": "invoke",
	"version": "v1.0.0",
	"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",	
	"params": {
		"invokeConfig": {
			"contractHash": "16edbe366d1337eb510c2ff61099424c94aeef02",
			"functions": [{
				"operation": "method name",
				"args": [{
					"name": "arg0-list",
					"value": [true, 100, "Long:100000000000", "Address:AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ", "ByteArray:aabb", "String:hello", [true, 100], {
						"key": 6
					}]
				}, {
					"name": "arg1-map",
					"value": {
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
				}, {
					"name": "arg2-str",
					"value": "String:test"
				}]
			}],
			"payer": "AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ",
			"gasLimit": 20000,
			"gasPrice": 500
		}
	}
}


```
#### 7. 签名、验证签名

请参考文档 [https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/interface.md](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/interface.md)


#### 8. Gas 网络费

SDK 中构造交易时的 Payer 就是网络费付款人，gasPrice固定值500，gasLimit最小值是20000，所以每笔交易至少消耗500 * 20000 = 0.01 ONG。

