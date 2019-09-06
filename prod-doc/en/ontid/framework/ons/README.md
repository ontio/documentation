# Ontology Name System

Ontology Name System (ONS) is an Enhancement Proposal of Ontology `ONT ID` framework. 
- [>>> URI schema and sample code](https://github.com/ontio/OEPs/pull/19)

ONS provides a naming service to map resource with `ONT ID`, with data privacy protection.

## ONS interface

同标准DNS，对于每一级域名长度的限制是63个字符，域名总长度则不能超过253个字符。

[subdomain].<二级域名>.<一级域名>.<顶级域名>

每个did最多可以绑定【100】个域名

| No   | name              | params                                                       | return             | auth                                                        | comment                 | event                                         |
| ---- | ----------------- | ------------------------------------------------------------ | ------------------ | ----------------------------------------------------------- | ----------------------- | --------------------------------------------- |
| 1    | registerDomain    | fulldomain:全域名；register：注册者ontid,；idx: wallet idx; validTo:有效期 | None               | 上级domain的owner，顶级域名为合约admin，最低为二级域名owner | 注册域名                | "registerDomain", "domain", "owner","validTo" |
| 2    | updateValidPeriod | fulldomain:全域名；idx: wallet idx;validTo:有效期            | None               | 上级domain的owner，顶级域名为合约admin，最低为二级域名owner | 更新有效时间            | "updateValidPeriod","domain","newvalid"       |
| 3    | deleteDomain      | fulldomain:全域名;idx: wallet idx                            | None               | domain owner，最低为二级域名owner                           | 删除域名                | "deleteDomain","domain"                       |
| 4    | bindValue         | fulldomain:全域名；idx: wallet idx;ctype:类型；value: 绑定的值 | None               | domain owner，最低为二级域名owner                           | 绑定值                  | "bindValue","domain","ctype","value"          |
| 5    | ownerOf           | fulldomain:全域名                                            | owner ontid        | none                                                        | 查询owner               |                                               |
| 6    | validTo           | fulldomain:全域名                                            | expire time        | none                                                        | 查询有效期限            |                                               |
| 7    | valueOf           | fulldomain:全域名                                            | bytearray          | none                                                        | 查询绑定值              |                                               |
| 8    | isDomainValid     | fulldomain:全域名                                            | bytearray          | none                                                        | 查询域名是否有效        |                                               |
| 9    | transfer          | fulldomain:全域名；idx:wallet idx；todid:转让到did           | None               | 该域名owner                                                 | 转让域名                | "transfer","domain","from","to"               |
| 10   | getDomains        | fulldomain                                                   | domains 已逗号分割 | None                                                        | 查询某个did下的所有域名 |                                               |

