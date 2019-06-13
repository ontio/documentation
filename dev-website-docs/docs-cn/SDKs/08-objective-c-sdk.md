
# ONTWallet
用 Objective-C 编写的支持本体钱包的库.


## 安装

1. 下载项目到本地.
2. 将`ONTSDK`文件夹拷贝到你自己的项目中.
3. 在 `ONT.h` 文件中配置以下参数:
  - kONTMainNet: YES //主网, NO // 测试网;
  - kONTRpcURL: RPC Api base url;
  - kONTRestfulURL: Restful Api base url;
  - kONTDappServerNode: ONT DApp Api base url.


## 使用

### 钱包

#### 创建一个新钱包

```
ONTAccount *account = [[ONTAccount alloc] initWithName:@"ONT-Wallet" password:@"ONT1234567890"];
```

#### 使用助记词导入钱包

```
ONTAccount *account = [[ONTAccount alloc] initWithName:@"ONT-Wallet" password:@"ONT1234567890" mnemonicText:@"use dinner opinion jewel detail inquiry popular enough diary upper concert identify"];
```

#### 使用私钥 (hex)导入钱包

```
ONTAccount *account = [[ONTAccount alloc] initWithName:@"ONT-Wallet" password:@"ONT1234567890" privateKeyHex:@"c3cc0e31af0e085299b38962281fceeb39cca70ac4ecc3bbd46e25154a9fb317"];
```

#### 使用 wif 导入钱包

```
ONTAccount *account = [[ONTAccount alloc] initWithName:@"ONT-Wallet" password:@"ONT1234567890" wif:@"L3nKDP3Wh3zmVktyFPGFegEUhJrpRcorosqk71X91rmjxnXtAFqb"];
```

#### 使用 keystore 导入钱包

```
ONTAccount *account = [[ONTAccount alloc] initWithName:@"ONT-Wallet-1" password:@"ONT123ont" keystore:@"{\"scrypt\":{\"r\":8,\"p\":8,\"n\":4096,\"dkLen\":64},\"address\":\"APjeNaCXGAVVXKPe6n8wYgFjeh3mLoqHWV\",\"key\": \"mLMLOpaZWhEcKNAN+p8rd43bmxDdY4t4DIK2eh1N2D51qhUCpnFlf4dl+op4uTk6\",\"label\":\"ONT-Wallet\",\"type\":\"A\",\"algorithm\":\"ECDSA\",\"salt\":\"\\/3qtmiaVilaqMdKVPPOeKA==\",\"parameters\":{\"curve\":\"P-256\"}}"];
```

#### 发送 ONT 资产

```
ONTAccount *account = [[ONTAccount alloc] initWithName:@"ONT-Wallet" password:@"ONT1234567890" wif:@"L2pGnv7waHczPursyuGDCBBU6GuoVBHkKF6uKjeFfiy584LQUqir"];
NSString *txHex = [account makeTransferTxWithToken:ONTTokenTypeONT toAddress:@"AatvPQVe1RECTqoAxe9FtSdWGnABVjMExv" amount:@"10" gasPrice:500 gasLimit:20000];
NSLog(@"txHex == %@", txHex);

[[ONTRpcApi shareInstance] sendRawtransactionWithHexTx:txHex preExec:NO callback:^(NSString *txHash, NSError *error) {
    if (error) {
        NSLog(@"error == %@", error);
    } else {
        NSLog(@"txHash == %@", txHash);
    }
}];
```

#### 发送 ONG 资产

```
ONTAccount *account = [[ONTAccount alloc] initWithName:@"ONT-Wallet" password:@"ONT1234567890" wif:@"L2pGnv7waHczPursyuGDCBBU6GuoVBHkKF6uKjeFfiy584LQUqir"];
NSString *txHex = [account makeTransferTxWithToken:ONTTokenTypeONG toAddress:@"AatvPQVe1RECTqoAxe9FtSdWGnABVjMExv" amount:@"3" gasPrice:500 gasLimit:20000];
NSLog(@"txHex == %@", txHex);

[[ONTRpcApi shareInstance] sendRawtransactionWithHexTx:txHex preExec:NO callback:^(NSString *txHash, NSError *error) {
    if (error) {
        NSLog(@"error == %@", error);
    } else {
        NSLog(@"txHash == %@", txHash);
    }
}];
```

#### 提取解绑的 ONG

```
ONTAccount *account = [[ONTAccount alloc] initWithName:@"ONT-Wallet" password:@"ONT1234567890" wif:@"L2pGnv7waHczPursyuGDCBBU6GuoVBHkKF6uKjeFfiy584LQUqir"];
NSString *txHex = [account makeClaimOngTxWithAddress:account.address.address amount:@"0.000000001" gasPrice:500 gasLimit:20000];
NSLog(@"Claim ONG txHex == %@", txHex);

[[ONTRpcApi shareInstance] sendRawtransactionWithHexTx:txHex preExec:NO callback:^(NSString *txHash, NSError *error) {
    NSLog(@"txHash == %@,error:%@",txHash, error);
    if (error) {
        NSLog(@"error == %@", error);
    } else {
        NSLog(@"txHash == %@", txHash);
    }
}];
```

#### 查询余额

```
[[ONTRpcApi shareInstance] getBalanceWithAddress:@"AatvPQVe1RECTqoAxe9FtSdWGnABVjMExv" callback:^(NSArray *balances, NSError *error) {
    if (error) {
        NSLog(@"error == %@", error);
    } else {
        for (ONTBalance *balance in balances) {
            NSLog(@"%@ == %@", balance.name, balance.balances);
        }
    }
}];
```


### OEP4

#### 查询余额

```
ONTAccount *account = [[ONTAccount alloc] initWithName:@"ONT" password:@"123456" privateKeyHex:@"5f2fe68215476abb9852cfa7da31ef00aa1468782d5ca809da5c4e1390b8ee45"];

[NeoVM shareInstance].oep4.contractAddress = @"b0bc9d8eb833c9903fa2e794f8413f6366f721ce";

[[NeoVM shareInstance].oep4 queryBalanceOf:account.address.address queryCallback:^(NSString *balance, NSError *error) {
    NSLog(@"balance == %@, %@", balance, [error localizedDescription]);
}];
```

#### 精度

```
[NeoVM shareInstance].oep4.contractAddress = @"b0bc9d8eb833c9903fa2e794f8413f6366f721ce";

[[NeoVM shareInstance].oep4 queryDecimalsWithQueryCallback:^(NSString *result, NSError *error) {
    NSLog(@"result == %@, %@", result, [error localizedDescription]);
}];
```

#### 总发行量

```
[NeoVM shareInstance].oep4.contractAddress = @"b0bc9d8eb833c9903fa2e794f8413f6366f721ce";

[[NeoVM shareInstance].oep4 queryTotalSupply:^(NSString *result, NSError *error) {
    NSLog(@"result == %@, %@", result, [error localizedDescription]);
}];

```

#### 名称

```
[NeoVM shareInstance].oep4.contractAddress = @"b0bc9d8eb833c9903fa2e794f8413f6366f721ce";

[[NeoVM shareInstance].oep4 queryName:^(NSString *result, NSError *error) {
    NSLog(@"result == %@, %@", result, [error localizedDescription]);
}];
```

#### 标志

```
[NeoVM shareInstance].oep4.contractAddress = @"b0bc9d8eb833c9903fa2e794f8413f6366f721ce";

[[NeoVM shareInstance].oep4 querySymbol:^(NSString *result, NSError *error) {
    NSLog(@"result == %@, %@", result, [error localizedDescription]);
}];
```

#### OEP4 转账

```
[NeoVM shareInstance].oep4.contractAddress = @"b0bc9d8eb833c9903fa2e794f8413f6366f721ce";

ONTAccount *from = [[ONTAccount alloc] initWithName:@"ONT" password:@"123456" privateKeyHex:@"5f2fe68215476abb9852cfa7da31ef00aa1468782d5ca809da5c4e1390b8ee45"];

BOOL isPreExec = NO;
[[NeoVM shareInstance].oep4 sendTransfer:from
                                      to:@"ASrLANryFnqwSt76h2YbhssdZeRGagRYem"
                              withAmount:100000000
                              byGasPayer:from
                             useGasLimit:20000
                             useGasPrice:500
                                 preExec:isPreExec
                           queryCallback:^(id result, NSError *error) {
                                if (error) {
                                    NSLog(@"error == %@", error);
                                } else {
                                    if (isPreExec) {
                                        NSLog(@"result == %@", result);
                                    } else {
                                        NSString *txhash = (NSString *)result;
                                        NSLog(@"txhash == %@", txhash);
                                    }
                                }
}];
```


### ONTID

#### 创建 ONT ID

```
ONTIdentity *ontID = [[ONTIdentity alloc] initWithName:@"MyOntid" password:@"ONT123ont"];
NSLog(@"%@", ontID.ontid);
```

#### 在链上注册 ONT ID

```
ONTIdentity *ontID = [[ONTIdentity alloc] initWithName:@"MyOntid" password:@"ONT123ont"];
ONTAccount *account = [[ONTAccount alloc] initWithName:@"ONT" password:@"ONT123ont" privateKeyHex:@"c3cc0e31af0e085299b38962281fceeb39cca70ac4ecc3bbd46e25154a9fb317"];
NSString *txHex = [ontID makeRegisterOntIdTxWithPayer:account gasPrice:500 gasLimit:20000].toRawByte.hexString;

[[ONTRpcApi shareInstance] sendRawtransactionWithHexTx:txHex preExec:NO callback:^(NSString *txHash, NSError *error) {
    if (error) {
        NSLog(@"error == %@", error);
    } else {
        NSLog(@"txHash == %@", txHash);
    }
}];
```

#### 导入 ONT ID

```
ONTIdentity *ontID = [[ONTIdentity alloc] initWithName:@"MyOntid" password:@"ONT123ont" privateKeyHex:@"c3cc0e31af0e085299b38962281fceeb39cca70ac4ecc3bbd46e25154a9fb317"];
NSLog(@"%@", ontID.ontid);
```

#### 获取 DDO

```
NSString *ontid = @"did:ont:AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ";
NSString *txHex = [ONTIdentity makeGetDDOTransactionWithOntid:ontid].toRawByte.hexString;
NSLog(@"%@", txHex);

[[ONTRpcApi shareInstance] sendRawtransactionWithHexTx:txHex preExec:YES callback:^(NSString *resut, NSError *error) {
    if (error) {
        NSLog(@"error == %@", error);
    } else {
        NSLog(@"resut == %@", resut);
    }
}];
```

#### 解析 DDO

```
NSString *result = @"26010000002103f631f975560afc7bf47902064838826ec67794ddcdbcc6f0a9c7b91fc85025832d046b657931044a736f6e0f7b226b6579223a2268656c6c6f227d046b65793006537472696e670676616c75653114fa88f5244be19659bbd24477caeeacac7cbf781b";
NSString *ontId = @"did:ont:AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ";
NSDictionary *dicDDO = [ONTIdentity parserDDODataWithOntid:ontId result:result];
NSLog(@"%@", dicDDO);
```


## 其他

See more tests in the files "ViewController.m"、"ONTWalletTests.m", thx!



## 捐赠

- ONT Address：AR4iFxFdbjTkHKtStSKRvu5bgXXBcpZx9D



## 联系

- Wechat：18321857793（memo：ONT SDK）
- QQ：3500229193（memo：ONT SDK）
