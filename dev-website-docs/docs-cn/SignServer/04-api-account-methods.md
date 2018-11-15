
# API 账户方法

- [创建账户](#创建账户)
- [导出账户](#导出账户)


## 创建账户

创建一个新的账户并导入钱包，注意该操作并没有创建账户的备份，所以请确保已经使用导出账户方法来备份任何新建的钱包数据。

### 方法名
```
createaccount
```

### 请求参数
```
None
```

### 响应
```
{
  "account": "XXX"             // The address of account created by sigsvr
}
```

### 例子

Request:
```
{
  "qid": "t",
  "method": "createaccount",
  "pwd": "XXXX",              // The unlock password of account created by sigsvr
  "params": {}
}
```

响应:
```
{
  "qid": "t",
  "method": "createaccount",
  "result": {
    "account": "AG9nms6VMc5dGpbCgrutsAVZbpCAtMcB3W"
  },
  "error_code": 0,
  "error_info": ""
}
```

## 导出账户

导出Account方法将导出钱包文件中的所有账户到`.dat`文件中，这可用于备份此服务管理的帐户。。

### 方法名
```
exportaccount
```


### 请求参数

```
{
  "wallet_path": "XXX"   // Path to save .dat wallet file to. If left blank, will default to the sigsvr default path.
}
```


### 响应结果

```
{
  "wallet_file": "XXX"   // Full path of exported wallet file.
  "account_num": "XXX"   // Number of accounts exported in the wallet file.
}
```


### 例子

请求:
```
{
  "qid": "t",
  "method": "exportaccount",
  "params": {}
}
```

响应:
```
{
  "qid": "t",
  "method": "exportaccount",
  "result": {
    "wallet_file": "./wallet_2018_08_03_23_20_12.dat",
    "account_num": 9
  },
  "error_code": 0,
  "error_info": ""
}
```
