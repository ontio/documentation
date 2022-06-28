# ONT Auth - provide claim

1. 用户使用 ONT Auth 注册自我管理的`ONT ID` // TODO：概念的链接
2. 获得来自 web-app 的资质认证需求（通过扫码二维码获得）
3. 调用二维码资质需求模板，查询个人名下已有的 claim 项
   1. 已经满足的
      1. 寻找对应的资质项，选取
      2. 根据选择项，生成新的匿名声明
   2. 未满足的
      1. 根据对应资质项的 `trust anchor`，[申请 claim](./acquire-claim.md)
      2. 重复 3.
4. 调用二维码回调方法，将匿名声明发送给 web-app