
## 1. 本体提供了哪些语言 SDK？

SDK 链接 [https://dev-docs.ont.io/#/docs-cn/SDKs/00-overview](https://dev-docs.ont.io/#/docs-cn/SDKs/00-overview)

Ts sdk 的测试代码：[https://github.com/ontio/ontology-ts-sdk/tree/master/test](https://github.com/ontio/ontology-ts-sdk/tree/master/test)

## 2. 多签地址如何生成？

请参考 [例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/MutiSignDemo.java)

```java
    com.github.ontio.account.Account[] accounts = new com.github.ontio.account.Account[]{acct1,acct2,acct3};
    int M = 2;
    byte[][] pks = new byte[accounts.length][];
    for(int i=0;i<pks.length;i++){
        pks[i] = accounts[i].serializePublicKey();
    }
    Address sender = Address.addressFromMultiPubKeys(M, pks);

```
## 3. 如何实现 ONT 多转多？

```java
 State state1 = new State(sender1,recvAddr,amount);
 State state2 = new State(sender2,recvAddr,amount2);
 ransaction tx = ontSdk.nativevm().ont().makeTransfer(new State[]{state1,state2},sender1.toBase58(),30000,0);
```
请参考 [例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/MakeTxWithoutWalletDemo.java)


## 4. 如何实现 ONT/ONG , OEP4 转账？

```java
 ontSdk.nativevm().ont().sendTransfer(acct0,"AUe2KKPnNMnM7hLHj6dEPJ4PA2m4pyJt2d",200,acct0,gaslimit,gasprice);
```

ONT 转账 Java [参考例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/OntDemo.java)

ONG 转账 Java [参考例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/OngDemo.java)

OEP4 转账 Java [参考例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/Oep4Demo.java)


Ts SDK [例子](https://github.com/ontio/ontology-ts-sdk/blob/master/test/transfer.test.ts)

## 5. SDK 调用合约例子？

```java

    List paramList = new ArrayList<>();
    paramList.add("testHello".getBytes());

    List args = new ArrayList();
    args.add(true);
    args.add(100);
    args.add("test".getBytes());
    args.add("test");
    args.add(account.getAddressU160().toArray());

    paramList.add(args);
    byte[] params = BuildParams.createCodeParamsScript(paramList);

    String result = invokeContract(params, account, 20000, 500,true);
    System.out.println(result);
```

Java [参考例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/PunicaInitDemo.java)

Ts [参考例子](https://github.com/ontio/ontology-ts-sdk/blob/master/test/scParams.test.ts)

## 6. 通过 Json 构造交易？

参考 [例子](https://github.com/ontio/ontology-java-sdk/blob/master/src/main/java/demo/MakeTxWithJsonDemo.java)

```json
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
## 7. 签名、验证签名

请参考 [文档](https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/interface.md)


## 8. Gas 网络费

SDK 中构造交易时的 Payer 就是网络费付款人，gasPrice 固定值 500，gasLimit 最小值是 20000，所以每笔交易至少消耗 500 * 20000 = 0.01 ONG。


## 9. 查询合约

* 通过浏览器查询 [https://explorer.ont.io/contract/list/20/1](https://explorer.ont.io/contract/list/20/1)
* 通过 SDK 接口查询
* 根据节点 RPC 查询

## 10. 执行与预执行

```java
    result = ontSdk.getConnect().sendRawTransactionPreExec(tx.toHexString());
    result = ontSdk.getConnect().sendRawTransaction(tx.toHexString());
```

## 11. OEP4 的合约转账事件解析

```java

new String(Helper.hexToBytes(""));  //"transfer"
Address.parse("").toBase58();   //from和 to 转成base58地址
Helper.BigIntFromNeoBytes(Helper.hexToBytes("")); //金额，小端转大端显示

```


