
## 启动

```shell
./sigsvr
```

## 操作

通过下面的链接访问:
```
http://localhost:20000/cli
```

## 访问控制

### IP 地址

签名机默认通过 `127.0.0.1` 供本地访问，如果你想提供外部访问，请使用 `--cliaddress` 选项进行配置。

```shell
sigsvr --cliaddress 0.0.0.0
```

### 端口号

签名机默认监听在 `20000` 端口，如果你想更改端口号，请使用 `--cliport` 选项进行配置。

```shell
sigsvr --cliport 1024
```

## 导入账户

你可以通过 `import` 命令导入钱包账户。

- `--wallet`：用于指定签名机从哪个钱包文件中导入钱包账户，默认为 `./wallet.data`。
- `--walletdir`：用于指定签名机钱包数据的存储文件夹，默认为 `./wallet_data`。

```shell
$ sigsvr import
Import account success.
Total account number:3
Add account number:3
Update account number:0
```

## 日志记录

签名机提供了 7 种级别的日志记录，默认为第 2 级 `Info`。

- Trace
- Debug
- Info (default)
- Warn
- Error
- Fatal
- Max Level

```shell
sigsvr --loglevel 0
```