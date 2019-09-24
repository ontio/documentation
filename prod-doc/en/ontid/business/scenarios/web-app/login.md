# Web-app - login

1. Web-app 
2. Web-app 配置 Gas 代付钱包，预存 ONG
   1. 可以自行部署同步节点 // TODO：链接
   2. 监控钱包余额，不足时报警
3. Web-app 使用 signing sdk 或调用 restful api 的 `verify`接口，用返回的数据生成二维码
   1. 预定义方法参数为：`login`
   2. // TODO：调用方法细节和链接，signing sdk？restful api ？ verify ？如何生成二维码
4. Web-app 使用 signing sdk 或调用 restful api 的  `result`接口，将上一步成功返回的 id 作为参数传入，轮询该 action 的执行结果 // TODO：方法细节和链接
   1. 用户使用 ONT Auth 扫描二维码并签名，发送给 signing-server // TODO：链接
   2. signing-server 收到 ONT Auth 的签名数据并验证签名，若验证通过则会返回给 web-app 成功结果，不通过则返回给 web-app 失败结果