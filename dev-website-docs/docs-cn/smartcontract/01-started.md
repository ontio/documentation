


智能合约开发工具
* Smartx
* vscode插件

智能合约调用工具
* Smartx
* vscode插件
* SDKs
* dAPI


### 编译合约

* smartx
* punica-cli
* vscode插件

### 部署合约

在部署合约之前，开发者需要准备好要部署的合约，且该合约已经被正确编译为.avm文件。

开发者还需要有Ontology的钱包账户，且保证账户上有足够的ONG，用以支付部署合约的费用。

目前，在测试网上部署合约，gasprice可以设为500。

部署合约需要用户构建特定的交易，并发送到区块链上执行。当交易执行完成后，合约就部署完成。

Ontology提供了不同的SDK和合约开发工具SmartX，帮助用户部署合约。




### 调用合约

#### 调用部署合约所需gas消耗计算

通过智能合约的预执行，可以获得当前合约执行所需要的`Gaslimit`,从而为智能合约的实际执行设置`Gaslimit`设置提供参考，避免由于**ONG**余额不足造成的执行失败。

```
$ ./ontology contract invoke --address 79102ef95cf75cab8e7f9a583c9d2b2b16fbce70 --params string:Hello,[string:Hello] --prepare --return bool
Invoke:70cefb162b2b9d3c589a7f8eab5cf75cf92e1079 Params:["Hello",["Hello"]]
Contract invoke successfully
  Gaslimit:20000
  Return:true
```



### 智能合约调用

#### 1. 构建交易

当智能合约被部署到区块链上后，我们可以通过构建交易（Transaction），调用合约中的相应方法。

在构建交易之前，我们需要知道合约的abi文件和合约的hash地址。

##### 什么是abi文件？

一般开发者智能合约在编写完成后，会将使用相应编译器对合约进行编译，编译后一般会得到合约的abi文件和avm文件。avm文件是合约的字节码。当合约部署到区块链上时，合约字节码会存储在分配给合约的存储区里。 abi文件是描述了合约的具体结构的json文件，包含了合约的入口函数，接口函数，函数的参数列表和返回值，事件等。当我们了解了合约的abi文件，我们就了解了该合约的具体功能。

以smartx为例，我们有一个可以做简单加法计算的模板合约Arith， 编译完合约后，页面上会显示JSON格式的abi内容。用户可以选择下载abi.json文件。

![](https://upload-images.jianshu.io/upload_images/150344-297f0b59eb7b3e94.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

##### 什么是合约hash？

合约hash是对合约的avm内容进行某些hash运算得到的值，该值是用来区分不同合约的唯一值。abi文件里一般也含有合约hash值。





### 2. 发送交易

我们有多种方式发送交易：

1. 通过rpc接口发送交易
2. 通过restful接口发送交易
3. 通过websocket发送交易

通过rpc和restful接口发送交易，返回的结果是交易发送的状态和交易hash；

通过websocket发送交易，如果合约方法有事件推送，可以监听到推送的消息，该消息一般是合约执行成功的结果。

我们还可以通过以上接口，发送预执行的交易到链上。预执行意味着交易只在接收到该交易的节点上运行，不用等到区块共识后才能获得执行的结果。通过预执行交易，可以验证构建的交易是否正确，和获得该交易预计消耗的gas。

我们以TS SDK的restful接口为例，说明如何简单地发送交易。

````
import {RestClient} from 'Ont'
//construct the restful client
const client = new RestClient();

//we use the tx made in last step
client.sendRawTransaction(tx.serialize()).then(res => {
	//here is the result
    console.log(res);
})
````

### 3. 获取交易结果

在上一步我们通过restful的接口发送了交易到链上，返回的结果如下：

````
{
	"Action": "sendrawtransaction",
	"Desc": "SUCCESS",
	"Error": 0,
	"Id": null,
	"Result": "886b2cd35af7ea65e502077b70966652f4cf281244868814b8f3b2cf82776214",
	"Version": "1.0.0"
}
````

其中Result字段的值就是交易hash。我们可以通过restful接口查询交易的执行结果。

````
import {RestClient} from 'Ont'
const client = new RestClient();
client.getSmartCodeEvent('886b2cd35af7ea65e502077b70966652f4cf281244868814b8f3b2cf82776214').then(res => {
    console.log(res)
})
````

我们可以通过TS SDK中封装的restful接口查询该交易的执行结果，也可以通过postman等网络工具查询。查询的url如下：

````
http://{{NODE_URL}}/api/v1/smartcode/event/txhash/03295a1b38573f3a40cf75ae2bdda7e7fb5536f067ff5e47de44aeaf5447259b
````

这里的NODE_URL可以是测试网节点，也可以是本地节点。

查询得到的结果如下：

````
{
    "Action": "getsmartcodeeventbyhash",
    "Desc": "SUCCESS",
    "Error": 0,
    "Result": {
        "TxHash": "03295a1b38573f3a40cf75ae2bdda7e7fb5536f067ff5e47de44aeaf5447259b",
        "State": 1,
        "GasConsumed": 0,
        "Notify": [
            {
                "ContractAddress": "bd76a5917e0444d4b615b87c5912362164676dc7",
                "States": [
                    "02"
                ]
            }
        ]
    },
    "Version": "1.0.0"
}
````

通过观察结果里的数据可以判断该次交易是否执行成功。

```State``` 等于1表示执行成功；等于0表示执行失败。

````Notify```` 是合约方法执行中的消息推送。