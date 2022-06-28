# ONT Auth - register

1. 用户使用 ONT Auth 注册自我管理的`ONT ID` // TODO：概念的链接
2. 收到 web-app [资质审查](./acquire-claim.md) 的需求，[提供 claim](./provide-claim.md)，如果[审查通过](../web-app/verify-claim.md)
3. Web-app 注册流程，填写账户内容
4. 根据 web-app 引导，使用 ONT Auth 扫描二维码，签名并提交
   1. 发送给 signing-server
   2. signing-server 收到 ONT Auth 的签名数据并验证签名，若验证通过则会将用户使用 ONT Auth 签名的 `ONT ID` 返回给 web-app
   3. Web-app 自行将用户账号和 `ONT ID` 进行绑定
5. 完成注册

注册方案也可以采用 1-->2-->4-->3 的流程

// TODO：链接