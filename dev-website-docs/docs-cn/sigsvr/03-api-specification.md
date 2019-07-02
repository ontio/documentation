
## 1. 概述

在默认情况下，签名机监听在本地的 `20000` 端口上. 其他服务通过 `HTTP POST` 方法请求服务。

```shell
curl http://localhost:20000/cli -X POST -H "Content-Type:application/json"
```

<section class = "info">
  <ul>
    <li>如果你想更改端口号，请使用 <code>--cliport</code> 选项进行配置。</li>
    <li>如果你想提供外部访问，请使用 <code>--cliaddress</code> 选项进行配置。</li>
  </ul>
</section>

### 请求结构

```json
{
  qid: "1",
  method: "method",
  account: "AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa",
  pwd: "password",
  params: {}
}
```

### 响应结构

```json
{
  qid: "1",
  method: "method",
  result: {
    signed_tx: "0000000"
  },
  error_code: 0,
  error_info: ""
}
```

### 错误码

| Error code | Error description         |
| :--------- | :------------------------ |
| 1001       | Invalid http method       |
| 1002       | Invalid http request      |
| 1003       | Invalid request parameter |
| 1004       | Unsupported method        |
| 1005       | Account is locked         |
| 1006       | Invalid transactions      |
| 1007       | ABI is not found          |
| 1008       | ABI is not matched        |
| 9999       | Unknown error             |

## 2. 创建账户

- 请求

```json
{
  "qid":"1",
  "method":"createaccount",
  "pwd":"password",
  "params":{}
}
```

- 响应

```json
{
  "qid": "t",
  "method": "createaccount",
  "result": {
      "account": "AWn31ZiNpXk55C7R4dvoVGBBMvTxG6sh6f"
  },
  "error_code": 0,
  "error_info": ""
}
```

## 3. 导出账户

- 请求

```json
{
  "qid":"t",
  "method":"exportaccount",
  "params":{}
}
```

- 响应

```json
{
    "qid": "t",
    "method": "exportaccount",
    "result": {
        "wallet_file": "./wallet_2018_02_25_17_31_59.dat",
        "account_num": 3
    },
    "error_code": 0,
    "error_info": ""
}
```

## 4. 交易签名

- 请求

```json
{
  "qid":"1",
  "method":"sigrawtx",
  "account":"AR1ibsqRjiuZgBuHhVbpUpg8yUfC9QHXBp",
  "pwd":"password",
  "params":{
    "raw_tx":"00d130c56babf401000000000000204e000000000000655767ac654e29c7afdd1a1ba08ff9b562c884016e00c66b6a14655767ac654e29c7afdd1a1ba08ff9b562c88401c86a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a51c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b650000"
  }
}
```

- 响应

```json
{
  "qid": "1",
  "method": "sigrawtx",
  "result": {
    "signed_tx": "00d130c56babf401000000000000204e000000000000655767ac654e29c7afdd1a1ba08ff9b562c884016e00c66b6a14655767ac654e29c7afdd1a1ba08ff9b562c88401c86a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a51c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b6500014140a92bac20ea3949a0dd8b32173d789c292ec509aeb936a8658789c68a43c47a0ae83613292210da3dca78cc47995ecdd9c27f9d3ae3e16587212151b4059ad1ac232102f41138e3899872579ca713d90b889c83b3406a67e5799fa8448ec4e0a10c4cacac"
  },
  "error_code": 0,
  "error_info": ""
}
```

## 5. 多重签名

- 请求

```json
{
  "qid":"1",
  "method":"sigmutilrawtx",
  "account":"AR1ibsqRjiuZgBuHhVbpUpg8yUfC9QHXBp",
  "pwd":"password",
  "params":{
    "raw_tx":"00d130c56babf401000000000000204e000000000000655767ac654e29c7afdd1a1ba08ff9b562c884016e00c66b6a14655767ac654e29c7afdd1a1ba08ff9b562c88401c86a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a51c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b650000",
    "m":2,
    "pub_keys":[
        "02f41138e3899872579ca713d90b889c83b3406a67e5799fa8448ec4e0a10c4cac",
        "02b76e86481df6e9814b203a41a0b040c87807d1bcfd18f8ea69c7d73ebf2b944a"
    ]
  }
}
```

- 响应

```json
{
  "qid": "1",
  "method": "sigmutilrawtx",
  "result": {
      "signed_tx": "00d130c56babf401000000000000204e000000000000655767ac654e29c7afdd1a1ba08ff9b562c884016e00c66b6a14655767ac654e29c7afdd1a1ba08ff9b562c88401c86a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a51c86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65000141409cbc821f9905ea5682796f5059083128fa370f3abd7054110e0ea06e630a63db4dedb4cc32ed32884b2ca31fb7d005a5d16e74f33652e79d502c9f8cc1d03c4147522102b76e86481df6e9814b203a41a0b040c87807d1bcfd18f8ea69c7d73ebf2b944a2102f41138e3899872579ca713d90b889c83b3406a67e5799fa8448ec4e0a10c4cac52ae"
  },
  "error_code": 0,
  "error_info": ""
}
```

## 6. 数据签名

- 请求

```json
{
  "qid":"1",
  "method":"sigdata",
  "account":"AR1ibsqRjiuZgBuHhVbpUpg8yUfC9QHXBp",
  "pwd":"password",
  "params":{
    "raw_data":"48656C6C6F20776F726C64"
  }
}
```

- 响应

```json
{
  "qid": "1",
  "method": "sigdata",
  "result": {
    "signed_data": "96c5901e36206fdb7f5086096d9465d47f5c6192c77d226244e701a52d64c9d26b79fc538db3e0d44df951d7a0146f07f7550af169c4499372ca7f72b5643cb0"
  },
  "error_code": 0,
  "error_info": ""
}
```

## 7. 转账交易

- 请求

- 响应



## 8. 智能合约

### 8.1 Native 合约调用
Native 合约调用交易根据 `ABI` 构造，并签名。

>注意：

> sigsvr 启动时，默认会在当前目录下查找 "./abi" 下的 `native` 合约 `abi` 。

> 如果 `naitve` 目录下没有该合约的 `abi` ，会返回 1007 错误。 `Native` 合约 `abi` 的查询路径可以通过 `--abi` 参数设定。

方法名称： `signativeinvoketx` 

请求参数：

```json
{
    "gas_price":XXX,    //gasprice
    "gas_limit":XXX,    //gaslimit
    "address":"XXX",    //调用native合约的地址
    "method":"XXX",     //调用native合约的方法
    "version":0,        //调用native合约的版本号
    "params":[
        //具体合约 Native合约调用的参数根据调用方法的ABI构造。所有值都使用字符串类型。
    ]
}
```
应答结果：
```json
{
    "signed_tx":XXX     //签名后的交易
}
```

以构造 `ont` 转账交易举例

请求：

```json
{
    "Qid":"t",
    "Method":"signativeinvoketx",
    "account":"XXX",
    "pwd":"XXX",
    "Params":{
    	"gas_price":0,
    	"gas_limit":20000,
    	"address":"0100000000000000000000000000000000000000",
    	"method":"transfer",
    	"version":0,
    	"params":[
    		[
    			[
    			"ATACcJPZ8eECdWS4ashaMdqzhywpRTq3oN",
    			"AeoBhZtS8AmGp3Zt4LxvCqhdU4eSGiK44M",
    			"1000"
    			]
    		]
    	]
    }
}
```
应答：

```json
{
    "qid": "t",
    "method": "signativeinvoketx",
    "result": {
        "signed_tx": "00d161b7315b000000000000000050c3000000000000084c8f4060607444fc95033bd0a9046976d3a9f57300c66b147ce25d11becca9aa8f157e24e2a14fe100db73466a7cc814fc8a60f9a7ab04241a983817b04de95a8b2d4fb86a7cc802e8036a7cc86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b6500014140c4142d9e066fea8a68303acd7193cb315662131da3bab25bc1c6f8118746f955855896cfb433208148fddc0bed5a99dfde519fe063bbf1ff5e730f7ae6616ee02321035f363567ff82be6f70ece8e16378871128788d5a067267e1ec119eedc408ea58ac"
    },
    "error_code": 0,
    "error_info": ""
}
```

signativeinvoketx 方法默认使用签名账户作为手续费支付方，如果需要使用其他账户作为手续费的付费账户，可以使用 `payer` 参数指定。

>注意：

>如果指定了手续费付费账户，还需要调用 `sigrawtx` 方法，使用手续费付费账户对 `signativeinvoketx` 方法生成的交易进行签名，否则会导致交易执行失败。

#### 举例1: 构造普通转账交易
```json
{
    "Qid":"t",
    "Method":"signativeinvoketx",
    "account":"XXX",
    "pwd":"XXX",
    "Params":{
    	"gas_price":0,
    	"gas_limit":20000,
    	"address":"0100000000000000000000000000000000000000",
    	"method":"transfer",
    	"version":0,
    	"payer":"ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48",
    	"params":[
    		[
    			[
    			"ATACcJPZ8eECdWS4ashaMdqzhywpRTq3oN",
    			"AeoBhZtS8AmGp3Zt4LxvCqhdU4eSGiK44M",
    			"1000"
    			]
    		]
    	]
    }
}
```

#### 举例2: 构造提取 ONG 交易

```json
{
	"Qid":"t",
	"Method":"signativeinvoketx",
	"account":"ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48",	  //提取账户
	"pwd":"XXX",
	"Params":{
		"gas_price":5000,
		"gas_limit":20000,
		"address":"0200000000000000000000000000000000000000",
		"method":"transferFrom",
		"version":0,
		"params":[
			"ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48",	//提取账户
			"AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV",   //ONT合约地址(base58格式)
			"ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48",  //ONG接受地址，可以于提取地址不一样
			"310860000000000"												//提取金额(需要在实际金额上乘以10的9次方)
		]
	}
}
```



### 8.2 NeoVm 合约调用

NeoVM 合约调用根据要调用的 `NeoVM` 合约构造调用交易，并签名。

NeoVM 参数合约支持 `array` 、 `bytearray` 、 `string` 、 `int` 以及 `bool` 类型，构造参数时需要提供参数类型及参数值，参数值统一使用字符串类型。

* `array` 是对象数组，数组元素支持任意 `NeoVM` 支持的参数类型和数量。

方法名称：`signeovminvoketx`

请求参数：
```json
{
    "gas_price":XXX,    //gasprice
    "gas_limit":XXX,    //gaslimit
    "address":"XXX",    //调用Neovm合约的地址
    "params":[
        //具体合约 Neovm合约调用的参数，根据需要调用的具体合约构造。所有值都使用字符串类型。
    ]
}
```
应答结果：
```json
{
    "signed_tx":XXX     //签名后的交易
}
```

举例
请求:

```json
{
    "qid": "t",
    "method": "signeovminvoketx",
    "account":"XXX",
    "pwd":"XXX",
    "params": {
    	"gas_price": 0,
    	"gas_limit": 50000,
    	"address": "8074775331499ebc81ff785e299d406f55224a4c",
    	"version": 0,
    	"params": [
    		{
    			"type": "string",
    			"value": "Time"
    		},
    		{
    			"type": "array",
    			"value": [
    				{
    					"type": "string",
    					"value": ""
    				}
    			]
    		}
    	]
    }
}
```
应答：

```json
{
    "qid": "t",
    "method": "signeovminvoketx",
    "result": {
        "signed_tx": "00d18f5e175b000000000000000050c3000000000000011e68f7bf0aaba1f18213639591f932556eb67480216700008074775331499ebc81ff785e299d406f55224a4c00080051c10454696d65000101231202026940ba3dba0a385c44e4a187af75a34e281b96200430db2cbc688a907e5fb54501014101b93bef619b4d7900b57f91e1810b268f9e10eb39fd563f23ce01323cde6273518000dc77d2d2231bc39428f1fa35d294990676015dbf6b4dfd2e6c9856034cc1"
    },
    "error_code": 0,
    "error_info": ""
}
```

signeovminvoketx 方法默认使用签名账户作为手续费支付方，如果需要使用其他账户作为手续费的付费账户，可以使用 `payer` 参数指定。

>注意：

>如果指定了手续费付费账户，还需要调用 `sigrawtx` 方法，使用手续费账户对 `signeovminvoketx` 方法生成的交易进行签名，否则会导致交易执行失败。

举例
```json
{
    "gas_price":XXX,    //gasprice
    "gas_limit":XXX,    //gaslimit
    "address":"XXX",    //调用Neovm合约的地址
    "payer":"XXX",      //手续费付费地址
    "params":[
        //具体合约 Neovm 合约调用的参数，根据需要调用的具体合约构造。所有值都使用字符串类型。
    ]
}
```