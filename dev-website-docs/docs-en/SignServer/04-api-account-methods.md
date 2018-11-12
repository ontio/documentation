# API Account Methods

- [Create Account](#create-account)
- [Export Account](#export-account)


## Create Account

Creates a new account and adds to wallet. Note that this does not create a backup of the new account. So please be sure to use the Export Account method regularly to properly backup any newly created wallets.

### Method Name
```
createaccount
```

### Request parameters
```
None
```

### Response
```
{
  "account": "XXX"             // The address of account created by sigsvr
}
```

### Example

Request:
```
{
  "qid": "t",
  "method": "createaccount",
  "pwd": "XXXX",              // The unlock password of account created by sigsvr
  "params": {}
}
```

Response:
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

## Export Accounts

Export accounts method will export all accounts in wallet data into a `.dat` wallet file. This can be used to backup the accounts managed by this service.


### Method Name
```
exportaccount
```


### Request parameters

```
{
  "wallet_path": "XXX"   // Path to save .dat wallet file to. If left blank, will default to the sigsvr default path.
}
```


### Response result

```
{
  "wallet_file": "XXX"   // Full path of exported wallet file.
  "account_num": "XXX"   // Number of accounts exported in the wallet file.
}
```


### Examples

Request:
```
{
  "qid": "t",
  "method": "exportaccount",
  "params": {}
}
```

Response:
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
