---
title: 
keywords: sample homepage
sidebar: ont_doc_zh
permalink: ontology_java_sdk_smartcontract_zh.html
folder: doc_zh
---

[English](./ontology_java_sdk_smartcontract_en.html) / 中文


<h1 align="center"> Ontology Java SDK User Guide </h1>
<p align="center" class="version">Version 0.7.0 </p>

# 智能合约基本说明

* codeAddress是什么

codeAddress是智能合约的唯一标识。

* 如何获得codeAddress ？

```
InputStream is = new FileInputStream("IdContract.avm");
byte[] bys = new byte[is.available()];
is.read(bys);
is.close();
code = Helper.toHexString(bys);
System.out.println("Code:" + Helper.toHexString(bys));
System.out.println("CodeAddress:" + Helper.getCodeAddress(code, VmType.NEOVM.value()));
```
> Note: 在获得codeAddress的时候，需要设置该合约需要运行在什么虚拟机上，目前支持的虚拟机是NEO和WASM。

* 调用智能合约invokeTransaction的过程，sdk中具体做了什么

```
//step1：构造交易
//需先将智能合约参数转换成vm可识别的opcode
Transaction tx = ontSdk.getSmartcodeTx().makeInvokeCodeTransaction(params, vmtype, fees);

//step2：对交易签名
ontSdk.signTx(tx, info1.address, password);

//step3：发送交易
ontSdk.getConnectMgr().sendRawTransaction(tx.toHexString());
```

* invoke时为什么要传入账号和密码

调用智能合约时需要用户签名，如果是预执行不需要签名，钱包中保存的是加密后的用户私钥，需要密码才能解密获取私钥。


* 查询资产操作时，智能合约预执行是怎么回事，如何使用？

如智能合约get相关操作，从智能合约存储空间里读取数据，无需走节点共识，只在该节点执行即可返回结果。发送交易时调用预执行接口。
```
String result = (String) sdk.getConnectMgr().sendRawTransactionPreExec(txHex);
```

## 智能合约部署和调用

> Note:目前java-sdk支持neo和wasm智能合约部署和调用，NEO和WASM合约部署操作一样，调用略有不同，见下面详解：


### 部署智能合约Demo例子
```
InputStream is = new FileInputStream("/Users/sss/dev/ontologytest/IdContract/IdContract.avm");
byte[] bys = new byte[is.available()];
is.read(bys);
is.close();
code = Helper.toHexString(bys);
ontSdk.setCodeAddress(Helper.getCodeAddress(code,VmType.NEOVM.value()));

//部署合约
String txhash = ontSdk.getSmartcodeTx().makeDeployCodeTransaction(code, true, "name", "1.0", "1", "1", "1", VmType.NEOVM.value());
System.out.println("txhash:" + txhash);
//等待出块
Thread.sleep(6000);
DeployCodeTransaction t = (DeployCodeTransaction) ontSdk.getConnectMgr().getTransaction(txhash);
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
|        | returnType   | ContractParameterType | 合约返回的数据类型     | 必选 |
| 输出参数 | txid   | String  | 交易编号  | 交易编号是64位字符串 |

## 智能合约调用

### NEO智能合约调用

* 基本流程：

 1. 读取智能合约的abi文件；
 2. 构造调用智能合约函数；
 3. 构造交易；
 4. 交易签名(预执行不需要签名)；
 5. 发送交易。

* 示例

```
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
//调用智能合约，sendInvokeSmartCodeWithSign方法封装好了构造交易，签名交易，发送交易步骤
String hash = ontSdk.getSmartcodeTx().sendInvokeSmartCodeWithSign(did.ontid, "passwordtest", func, (byte) VmType.NEOVM.value()););

```

* AbiInfo结构(NEO合约调用的时候需要，WASM合约不需要)

```
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

### WASM智能合约调用

* 基本流程：
  1. 构造调用合约中的方法需要的参数；
  2. 构造交易；
  3. 交易签名(如果是预执行不需要签名)；
  4. 发送交易。

* 示例：

```
//设置要调用的合约地址codeAddress
ontSdk.getSmartcodeTx().setCodeAddress(codeAddress);
String funcName = "add";
//构造合约函数需要的参数
String params = ontSdk.getSmartcodeTx().buildWasmContractJsonParam(new Object[]{20,30});
//指定虚拟机类型构造交易
Transaction tx = ontSdk.getSmartcodeTx().makeInvokeCodeTransaction(ontSdk.getSmartcodeTx().getCodeAddress(),funcName,params.getBytes(),VmType.WASMVM.value(),new Fee[0]);
//发送交易
ontSdk.getConnectMgr().sendRawTransaction(tx.toHexString());

```


> 如果需要监控推送结果，可以了解下面章节。

## 智能合约执行过程推送

创建websocket线程，解析推送结果。


### 1. 设置websocket链接


```
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


### 2. 启动websocket线程


```
//false 表示不打印回调函数信息
ontSdk.getWebSocket().startWebsocketThread(false);

```


### 3. 启动结果处理线程


```
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


### 4. 每6秒发送一次心跳程序，维持socket链接


```
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


### 5. 推送结果事例详解


以调用存证合约的put函数为例，

//存证合约abi.json文件部分内容如下

```
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

```
RECV: {"Action":"Log","Desc":"SUCCESS","Error":0,"Result":{"Message":"Put","TxHash":"8cb32f3a1817d88d8562fdc0097a0f9aa75a926625c6644dfc5417273ca7ed71","ContractAddress":"80f6bff7645a84298a1a52aa3745f84dba6615cf"},"Version":"1.0.0"}
RECV: {"Action":"Notify","Desc":"SUCCESS","Error":0,"Result":[{"States":["7075745265636f7264","507574","6b6579","7b2244617461223a7b22416c6772697468656d223a22534d32222c2248617368223a22222c2254657874223a2276616c75652d7465737431222c225369676e6174757265223a22227d2c2243416b6579223a22222c225365714e6f223a22222c2254696d657374616d70223a307d"],"TxHash":"8cb32f3a1817d88d8562fdc0097a0f9aa75a926625c6644dfc5417273ca7ed71","ContractAddress":"80f6bff7645a84298a1a52aa3745f84dba6615cf"}],"Version":"1.0.0"}
```