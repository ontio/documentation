# Web-app - on-chain action

1. 定义预设上链动作的模板 // TODO: 模板链接
2. 判断是否上链还是作为验签和驱动动作 // TODO：举例和链接
   3. 如果 上链，实现上链动作的智能合约 // TODO：举例和链接
4. 实现上链动作的后续链外动作 // TODO：举例和链接
5. 配置 Gas 代付钱包，预存 ONG
   1. 可以自行部署同步节点 // TODO：链接
   2. 监控钱包余额，不足时报警
6. [自定义配置上链操作](../../../framework/signing-server/deployment.md)
  
- 在 signing-server 配置文件`TODO:文件名`中注册自定义的on-chain action
  
   | field      | description                                                  |
   | ---------- | ------------------------------------------------------------ |
   | type       | action类型                                                   |
   | onchainRec | 设置为true表示需要上链,false表示不需要上链                   |
   | payer      | 若不配置，则由用户支付手续费，为""则由defaultPayer支付手续费，同时需要在启动服务时，将payer对应的私钥在命令行输入，用于后续对交易的payer签名 |
   | qrcodeUrl  | 1.onchainRec为true时，可以获取交易参数的url，ONT Auth会根据参数构造交易并让用户签名。<br/>2.onchainRec为false时,可以获取指定签名内容，ONT Auth会根据该内容让用 |
   | callback   | ONT Auth将签完名的交易发送给signing-server验签，验签通过会回调wep-app提供的callback。由wep-app决定并执行发送交易上链 |
