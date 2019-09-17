# Web-app - register

1.用户使用ONT Auth注册自我管理的ontid

2.Web-app 使用signing sdk或调用restful api `verify`接口，并传入参数`action=register`，用返回的数据生成二维码

3.Web-app 使用signing sdk或调用restful api `result`接口，将上一步成功返回的id作为参数传入，轮询该action的执行结果

4.用户使用ONT Auth扫描二维码并签名，发送给signing-server

5.signing-server收到ONT Auth的签名数据并验证签名，若验证通过则会将用户使用ONT Auth签名的ontid返回给Web-app，Web-app自行将用户账号和ontid进行绑定