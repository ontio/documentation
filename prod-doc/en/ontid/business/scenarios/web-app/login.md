# Web-app - login

1.Web-app 使用signing sdk或调用restful api `verify`接口，并传入参数`action=login`，用返回的数据生成二维码

2.Web-app 使用signing sdk或调用restful api `result`接口，将上一步成功返回的id作为参数传入，轮询该action的执行结果

3.用户使用ONT Auth扫描二维码并签名，发送给signing-server

4.signing-server收到ONT Auth的签名数据并验证签名，若验证通过则会返回给Web-app成功结果，不通过则返回给Web-app失败结果