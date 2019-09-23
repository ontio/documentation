# Web-app - register

1. 用户使用 ONT Auth 注册自我管理的`ONT ID` // TODO：概念的链接
2. Web-app 配置 Gas 代付钱包，预存 ONG
   1. 可以自行部署同步节点 // TODO：链接
   2. 监控钱包余额，不足时报警
3. [资质审查](./acquire-claim.md)，如果[审查通过](./verify-claim.md)
4. Web-app 注册流程，账户内容准备
   3. 注册信息填写
   4. 老账户查重
   5. 新账户锁定，注册信息缓存
      - session 绑定缓存，过期删除
      - 由于异步返回，建议对账户锁定缓存
5. Web-app 使用 signing sdk 或调用 restful api  `verify` 接口，用返回的数据生成二维码。提醒用户安装 ONT Auth 并注册 `ONT ID`
   1. 预定义方法参数为：`register`
   2. // TODO：调用方法细节和链接，signing sdk？restful api ？ verify ？如何生成二维码
6. Web-app 使用signing sdk或调用restful api `result`接口，将上一步成功返回的id作为参数传入，轮询该action的执行结果 // TODO：方法细节和链接
   1. 用户使用 ONT Auth 扫描二维码并签名，发送给signing-server
   2. signing-server 收到 ONT Auth 的签名数据并验证签名，若验证通过则会将用户使用 ONT Auth 签名的 `ONT ID` 返回给 web-app
7. Web-app 自行将用户账号和 `ONT ID` 进行绑定，注册缓存信息转成用户账户信息

注册方案也可以采用 1-->2-->5-->6-->7-->3-->4 的流程

// TODO：链接