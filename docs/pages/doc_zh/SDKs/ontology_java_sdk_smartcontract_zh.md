---
title:
keywords: sample homepage
sidebar: SDKs_zh
permalink: ontology_java_sdk_smartcontract_zh.html
folder: doc_zh/SDKs
giturl: https://github.com/ontio/ontology-java-sdk/blob/master/docs/cn/smartcontract.md
---

<h1 align="center"> Java sdk 智能合约 </h1>

<p align="center" class="version">Version 1.0.0 </p>

[English](./ontology_java_sdk_smartcontract_en.html) / 中文

## 介绍

这个章节介绍如何通过Java SDK使用智能合约。

## 智能合约部署、调用、事件推送

> Note:目前java-sdk支持neo智能合约部署和调用，暂不支持WASM合约，NEO和WASM合约部署操作一样，调用略有不同，见下面详解：


### 部署

通过[SmartX](https://smartx.ont.io/)编译智能合约，可以在SmartX上直接部署合约，也可以通过java sdk部署合约。

```java
InputStream is = new FileInputStream("/Users/sss/dev/ontologytest/IdContract/IdContract.avm");
byte[] bys = new byte[is.available()];
is.read(bys);
is.close();
code = Helper.toHexString(bys);
ontSdk.setCodeAddress(Address.AddressFromVmCode(code).toHexString());

//部署合约
Transaction tx = ontSdk.vm().makeDeployCodeTransaction(code, true, "name",
                    "v1.0", "author", "email", "desp", account.getAddressU160().toBase58(),ontSdk.DEFAULT_DEPLOY_GAS_LIMIT,500);
String txHex = Helper.toHexString(tx.toArray());
ontSdk.getConnect().sendRawTransaction(txHex);
//等待出块
Thread.sleep(6000);
DeployCodeTransaction t = (DeployCodeTransaction) ontSdk.getConnect().getTransaction(txHex);
```

**makeDeployCodeTransaction**

```java
public DeployCode makeDeployCodeTransaction(String codeStr, boolean needStorage, String name, String codeVersion, String author, String email, String desp,String payer,long gaslimit,long gasprice) 

```

| 参数      | 字段   | 类型  | 描述 |             说明 |
| ----- | ------- | ------ | ------------- | ----------- |
| 输入参数 | codeHexStr| String | 合约code十六进制字符串 | 必选 |
|        | needStorage    | Boolean | 是否需要存储   | 必选 |
|        | name    | String  | 名字       | 必选|
|        | codeVersion   | String | 版本       |  必选 |
|        | author   | String | 作者     | 必选 |
|        | email   | String | emal     | 必选 |
|        | desp   | String | 描述信息     | 必选 |
|        | VmType   | byte | 虚拟机类型     | 必选 |
|        | payer   | String | 支付交易费用的账户地址     | 必选 |
|        | gaslimit   | long | gaslimit    | 必选 |
|        | gasprice   | long | gas价格   | 必选 |
| 输出参数 | tx   | Transaction  | 交易实例  |  |

### 调用

#### NEO智能合约调用

* 基本流程：

 1. 读取智能合约的abi文件；
 2. 构造调用智能合约函数；
 3. 构造交易；
 4. 交易签名(预执行不需要签名)；
 5. 发送交易。

* 示例

```java
//读取智能合约的abi文件
InputStream is = new FileInputStream("C:\\ZX\\NeoContract1.abi.json");
byte[] bys = new byte[is.available()];
is.read(bys);
is.close();
String abi = new String(bys);

//解析abi文件
AbiInfo abiinfo = JSON.parseObject(abi, AbiInfo.class);
System.out.println("codeHash:"+abiinfo.getHash());
System.out.println("Entrypoint:"+abiinfo.getEntrypoint());
System.out.println("Functions:"+abiinfo.getFunctions());
System.out.println("Events"+abiinfo.getEvents());

//设置智能合约codeAddress
ontSdk.setCodeAddress(abiinfo.getHash());

//获取账号信息
Identity did = ontSdk.getWalletMgr().getIdentitys().get(0);
AccountInfo info = ontSdk.getWalletMgr().getAccountInfo(did.ontid,"passwordtest");

//构造智能合约函数
AbiFunction func = abiinfo.getFunction("AddAttribute");
System.out.println(func.getParameters());
func.setParamsValue(did.ontid.getBytes(),"key".getBytes(),"bytes".getBytes(),"values02".getBytes(),Helper.hexToBytes(info.pubkey));
System.out.println(func);
//预执行
Object obj =  ontSdk.neovm().sendTransaction(Helper.reverse("872a56c4583570e46dde1346137b78fdb9fd3ce1"),null,null,0,0,func, true);
System.out.println(obj);
//执行
String hash = ontSdk.neovm().sendTransaction(Helper.reverse("872a56c4583570e46dde1346137b78fdb9fd3ce1"), acct1, acct1, 20060313, 500, func, true);
```

* AbiInfo结构(NEO合约调用的时候需要，WASM合约不需要)

```java
public class AbiInfo {
    public String hash;
    public String entrypoint;
    public List<AbiFunction> functions;
    public List<AbiEvent> events;
}
public class AbiFunction {
    public String name;
    public String returntype;
    public List<Parameter> parameters;
}
public class Parameter {
    public String name;
    public String type;
    public String value;
}
```

#### WASM智能合约调用-目前不支持WASM

* 基本流程：
  1. 构造调用合约中的方法需要的参数；
  2. 构造交易；
  3. 交易签名(如果是预执行不需要签名)；
  4. 发送交易。

* 示例：

```java
//设置要调用的合约地址codeAddress
ontSdk.getSmartcodeTx().setCodeAddress(codeAddress);
String funcName = "add";
//构造合约函数需要的参数
String params = ontSdk.vm().buildWasmContractJsonParam(new Object[]{20,30});
//指定虚拟机类型构造交易
Transaction tx = ontSdk.vm().makeInvokeCodeTransaction(ontSdk.getSmartcodeTx().getCodeAddress(),funcName,params.getBytes(),VmType.WASMVM.value(),payer,gas);
//发送交易
ontSdk.getConnect().sendRawTransaction(tx.toHexString());
```

#### 智能合约调用例子

合约中的方法
```c#

public static bool Transfer(byte[] from, byte[] to, object[] param)
{
    StorageContext context = Storage.CurrentContext;

    if (from.Length != 20 || to.Length != 20) return false;

    for (int i = 0; i < param.Length; i++)
    {

        TransferPair transfer = (TransferPair)param[i];
        byte[] hash = GetContractHash(transfer.Key);
        if (hash.Length != 20 || transfer.Amount < 0) throw new Exception();
        if (!TransferNEP5(from, to, hash, transfer.Amount)) throw new Exception();

    }
    return true;
}
struct TransferPair
{
     public string Key;
     public ulong Amount;
}
```

Java-SDK 调用Transfer函数的方法

分析：合约中的Transfer方法需要三个参数，前两个参数都是字节数组类型的参数，最后一个参数是对象数组，数组中的每个元素的结构可以通过TransferPair知道各个属性数据类型。

```java
String functionName = "Transfer";
//构造Transfer方法需要的param 数组
List list = new ArrayList();
List list2 = new ArrayList();
list2.add("Atoken");
list2.add(100);
list.add(list2);
List list3 = new ArrayList();
list3.add("Btoken");
list3.add(100);
list.add(list3);
//设置函数需要的参数
func.setParamsValue(account999.getAddressU160().toArray(),Address.decodeBase58("AacHGsQVbTtbvSWkqZfvdKePLS6K659dgp").toArray(),list);
String txhash = ontSdk.neovm().sendTransaction(Helper.reverse("44f1f4ee6940b4f162d857411842f2d533892084"),acct,acct,20000,500,func,false);
Thread.sleep(6000);
System.out.println(ontSdk.getConnect().getSmartCodeEvent(tx.hash().toHexString()));
```



> 如果需要监控推送结果，可以了解下面章节。

### 智能合约事件推送

创建websocket线程，解析推送结果。


#### 1. 设置websocket链接


```java
//lock 全局变量,同步锁
public static Object lock = new Object();

//获得ont实例
String ip = "http://127.0.0.1";
String wsUrl = ip + ":" + "20335";
OntSdk wm = OntSdk.getInstance();
wm.setWesocket(wsUrl, lock);
wm.setDefaultConnect(wm.getWebSocket());
wm.openWalletFile("OntAssetDemo.json");

```


#### 2. 启动websocket线程


```java
//false 表示不打印回调函数信息
ontSdk.getWebSocket().startWebsocketThread(false);

```


#### 3. 启动结果处理线程


```java
Thread thread = new Thread(
                    new Runnable() {
                        @Override
                        public void run() {
                            waitResult(lock);
                        }
                    });
            thread.start();
            //将MsgQueue中的数据取出打印
            public static void waitResult(Object lock) {
                    try {
                        synchronized (lock) {
                            while (true) {
                                lock.wait();
                                for (String e : MsgQueue.getResultSet()) {
                                    System.out.println("RECV: " + e);
                                    Result rt = JSON.parseObject(e, Result.class);
                                    //TODO
                                    MsgQueue.removeResult(e);
                                    if (rt.Action.equals("getblockbyheight")) {
                                        Block bb = Serializable.from(Helper.hexToBytes((String) rt.Result), Block.class);
                                        //System.out.println(bb.json());
                                    }
                                }
                            }
                        }
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
```


#### 4. 每6秒发送一次心跳程序，维持socket链接


```java
for (;;){
                    Map map = new HashMap();
                    if(i >0) {
                        map.put("SubscribeEvent", true);
                        map.put("SubscribeRawBlock", false);
                    }else{
                        map.put("SubscribeJsonBlock", false);
                        map.put("SubscribeRawBlock", true);
                    }
                    //System.out.println(map);
                    ontSdk.getWebSocket().setReqId(i);
                    ontSdk.getWebSocket().sendSubscribe(map);     
                Thread.sleep(6000);
            }
```


#### 5. 推送事例详解


以调用存证合约的put函数为例，

//存证合约abi.json文件部分内容如下

```json
{
    "hash":"0x27f5ae9dd51499e7ac4fe6a5cc44526aff909669",
    "entrypoint":"Main",
    "functions":
    [

    ],
    "events":
    [
        {
            "name":"putRecord",
            "parameters":
            [
                {
                    "name":"arg1",
                    "type":"String"
                },
                {
                    "name":"arg2",
                    "type":"ByteArray"
                },
                {
                    "name":"arg3",
                    "type":"ByteArray"
                }
            ],
            "returntype":"Void"
        }
    ]
}
```


当调用put函数保存数据时，触发putRecord事件，websocket 推送的结果是{"putRecord", "arg1", "arg2", "arg3"}的十六进制字符串

例子如下：

```json
RECV: 
{
	"Action": "Log",
	"Desc": "SUCCESS",
	"Error": 0,
	"Result": {
		"Message": "Put",
		"TxHash": "8cb32f3a1817d88d8562fdc0097a0f9aa75a926625c6644dfc5417273ca7ed71",
		"ContractAddress": "80f6bff7645a84298a1a52aa3745f84dba6615cf"
	},
	"Version": "1.0.0"
}
RECV: {
      	"Action": "Notify",
      	"Desc": "SUCCESS",
      	"Error": 0,
      	"Result": [{
      		"States": ["7075745265636f7264", "507574", "6b6579", "7b2244617461223a7b22416c6772697468656d223a22534d32222c2248617368223a22222c2254657874223a2276616c75652d7465737431222c225369676e6174757265223a22227d2c2243416b6579223a22222c225365714e6f223a22222c2254696d657374616d70223a307d"],
      		"TxHash": "8cb32f3a1817d88d8562fdc0097a0f9aa75a926625c6644dfc5417273ca7ed71",
      		"ContractAddress": "80f6bff7645a84298a1a52aa3745f84dba6615cf"
      	}],
      	"Version": "1.0.0"
      }
```


## FAQ


* contractAddress是什么

contractAddress是智能合约的唯一标识。

* 如何获得contractAddress ？

```java
InputStream is = new FileInputStream("IdContract.avm");
byte[] bys = new byte[is.available()];
is.read(bys);
is.close();
code = Helper.toHexString(bys);
System.out.println("Code:" + Helper.toHexString(bys));
System.out.println("CodeAddress:" + Address.AddressFromVmCode(code).toHexString());
```

> Note: 在获得codeAddress的时候，需要设置该合约需要运行在什么虚拟机上，目前支持的虚拟机是NEO和WASM。

* 调用智能合约invokeTransaction的过程，sdk中具体做了什么

```java
//step1：构造交易
//需先将智能合约参数转换成vm可识别的opcode
Transaction tx = ontSdk.vm().makeInvokeCodeTransaction(ontContractAddr, null, contract.toArray(), VmType.Native.value(), sender.toBase58(),gaslimit，gasprice);

//step2：对交易签名
ontSdk.signTx(tx, info1.address, password);

//step3：发送交易
ontSdk.getConnectMgr().sendRawTransaction(tx.toHexString());
```

* invoke时为什么要传入账号和密码

调用智能合约时需要用户签名，如果是预执行不需要签名，钱包中保存的是加密后的用户私钥，需要密码才能解密获取私钥。


* 查询资产操作时，智能合约预执行是怎么回事，如何使用？

如智能合约get相关操作，从智能合约存储空间里读取数据，无需走节点共识，只在该节点执行即可返回结果。发送交易时调用预执行接口。
```java
String result = (String) sdk.getConnect().sendRawTransactionPreExec(txHex);
```
