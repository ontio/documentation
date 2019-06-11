

C# SDK 的目标是帮助 .NET 开发者开发基于本体链的 DAPP。源码地址：[https://github.com/ontio-community/ontology-csharp-sdk](https://github.com/ontio-community/ontology-csharp-sdk)。

## 初始化

```c#
OntologySdk OntSDK = new OntologySdk(_node, ConnectionMethodFactory.ConnectionMethod.REST);

Console.WriteLine("random create private key: "+ Helper.Bytes2HexString(Helper.CreatePrivateKey()));

```

## 与节点交互

```c#

try { Console.WriteLine("Connecting to blockchain via: " + OntSDK.Connection.GetType()); } catch { };
try { Console.WriteLine("Block Height: " + OntSDK.Connection.getBlockHeight()); } catch { };
try { Console.WriteLine("ONT Balance: " + OntSDK.Connection.getAddressBalance(to)); } catch { };
try { Console.WriteLine("Node Count: " + OntSDK.Connection.getNodeCount()); } catch { };
try { Console.WriteLine("Block Height by Tx Hash: " + OntSDK.Connection.getBlockHeightByTxHash(TxHash)); } catch { };
try { Console.WriteLine("Block Hex (int): " + OntSDK.Connection.getBlockHex(15)); } catch { };
try { Console.WriteLine("Block Hex (hash): " + OntSDK.Connection.getBlockHex(BlockHash)); } catch { };
try { Console.WriteLine("Block Json (int): " + OntSDK.Connection.getBlockJson(15)); } catch { };
try { Console.WriteLine("Block Json (hash): " + OntSDK.Connection.getBlockJson(BlockHash)); } catch { };
try { Console.WriteLine("Transaction Hex by Tx Hash: " + OntSDK.Connection.getRawTransactionHex(TxHash)); } catch { };
try { Console.WriteLine("Transaction Json by Tx Hash: " + OntSDK.Connection.getRawTransactionJson(TxHash)); } catch { }; 
try { Console.WriteLine("Contract: " + OntSDK.Connection.getContractJson("49f0908f08b3ebce1e71dc5083cb9a8a54cc4a24")); } catch { };
try { Console.WriteLine("getSmartCodeEvent: " + OntSDK.Connection.getSmartCodeEvent(TxHash)); } catch { };
try { Console.WriteLine("getSmartCodeEvent: " + OntSDK.Connection.getSmartCodeEvent(0)); } catch { };

```

## 转账

```c#
NetworkResponse result = OntSDK.transfer("ONG", from, to, 5, payer, 20000,500, new List<byte[]>() { Helper.HexString2Bytes(privatekey) },true);
Console.WriteLine(result.JobjectResponse);
```

## 调用合约

```c#

var jarray = new JArray();
var arg1 = new JObject {
    { "name", "arg0-list" },
    { "value", new JArray { true, new JArray { true ,100}, 100, "Long:100000000000", "Address:AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ", "ByteArray:aabb", "String:hello" }}
};
var arg2 = new JObject {
    { "name", "arg1-str" },
    { "value", "hello" }
};
var arg3 = new JObject {
    { "name", "arg2-int" },
    { "value", 100 }
};
jarray.Add(arg1);
jarray.Add(arg2);
jarray.Add(arg3);

JObject function = new JObject { { "operation", "method name" }, { "args", jarray } };
JObject invokeConfig = new JObject {
    { "contractHash", "16edbe366d1337eb510c2ff61099424c94aeef02" },
    { "functions", new JArray() { function } },
    { "payer", "AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ"},
    { "gasLimit", 20000 },
    { "gasPrice", 500 }
};

JObject invokeAction = new JObject {
    { "action", "invoke" },
    { "version", "v1.0.0" },
    { "id", "1234" },
    { "params", new JObject { { "invokeConfig", invokeConfig } } }
};
Console.WriteLine(invokeAction);
Console.WriteLine();
// Console.ReadKey();

NetworkResponse result = OntSDK.invokeTransaction(invokeAction, new List<byte[]>() { Helper.HexString2Bytes(privatekey) },true);


```
