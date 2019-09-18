# Web-app - on-chain action

[自定义配置上链操作](../../../framework/signing-server/deployment.md)

在signing-server配置文件中注册自定义的on-chain action

type:
````
action类型
````

onchainRec:
````
设置为true表示需要上链,false表示不需要上链
````

payer：
````
若不配置，则由用户支付手续费，为""则由defaultPayer支付手续费，同时需要在启动服务时，将payer对应的私钥在命令行输入，用于后续对交易的payer签名
````

qrcodeUrl：
````
1.onchainRec为true时，可以获取交易参数的url，ONT Auth会根据参数构造交易并让用户签名。
2.onchainRec为false时,可以获取指定签名内容，ONT Auth会根据该内容让用户签名
````

callback：
````
ONT Auth将签完名的交易发送给signing-server验签，验签通过会回调wep-app提供的callback。由wep-app决定并执行发送交易上链
````