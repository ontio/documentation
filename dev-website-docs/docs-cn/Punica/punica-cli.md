

## 概述
Punica-CLI 具有以下特性：

* 支持智能合约编译、部署、调用和测试。
* 实现了 Python 和 TypeScript 版本。
* 自动化生成 dapp 工程目录，提供多种 box，为开发者基于 Punica-Boxes 开发提供便利。
* 智能合约测试配置与 smartx 有相同的配置标准。
* 提供智能合约包管理工具。

## 安装

安装之前请先确认已安装以下工具：

- [Python 3.7](https://www.python.org/downloads/release/python-370/)
- [Git](https://git-scm.com/)

然后，执行以下命令进行安装：

```shell
pip install punica
```

## 快速开始

如果想使用更多 Punica 命令，请先创建一个 Punica 项目。


```shell
$ punica
Usage: punica [OPTIONS] COMMAND [ARGS]...

Options:
  -p, --project PATH  Specify a punica project directory.
  -v, --version       Show the version and exit.
  -h, --help          Show this message and exit.

Commands:
  compile  Compile the specified contracts to avm and...
  deploy   Deploys the specified contracts to specified...
  init     Initialize new and empty Ontology DApp...
  invoke   Invoke the function list in default-config or...
  node     Ontology Blockchain private net in test mode.
  scpm     Smart contract package manager，support...
  smartx   Ontology smart contract IDE,SmartX...
  test     Unit test with specified smart contract
  unbox    Download a Punica Box, a pre-built Ontology...
  wallet   Manager your ontid, account, asset.
```
使用下面的命令生成一个新项目：

```shell
sss$ punica init
Downloading...
Unpacking...
Unbox successful. Enjoy it!
```

## 开始使用


### 创建项目

#### 初始化新项目

可以使用`punica init`命令创建一个空项目

```shell
$punica init --help
Usage: punica init [OPTIONS]

  Initialize new and empty Ontology DApp project.

Options:
  -h, --help  Show this message and exit.
```

使用下面的命令生成一个新项目

```shell
sss$ punica init
Downloading...
Unpacking...
Unbox successful. Enjoy it!
```

生成的项目结构如下：

- `contracts/`: 用于存放合约文件.
- `src/`: 用于存放dapp js和html等相关文件.
- `test/`: 合约代码测试文件.
- `wallet/`: 用于存放钱包文件.
- `punica-config.json` 用于配置区块链网络

#### 创建 Box 项目

Punica Box 是Punica dapp 模板库，你可以下载感兴趣的项目，然后基于该项目创建你的 dapp。

1. 创建一个新文件夹:

   ```shell
   mkdir tutorialtoken
   cd tutorialtoken
   ```

2. 下载 Box:

   ```shell
   punica unbox tutorialtoken
   ```


   ```shell
   punica unbox --help
   Usage: punica unbox [OPTIONS] BOX_NAME
   
     Download a Punica Box, a pre-built Ontology DApp project.
   
   Options:
     -h, --help  Show this message and exit.
   ```

> **注意**:
>
> - 你可以使用 `punica unbox <box-name>` 免费下载任意的 Box 项目。
> - 你可以在你的项目根目录使用 punica 的其他命令，也可以使用`-p` or `--project` 选项指定使用哪个项目。
>

### 编译

使用下面的命令编译你的合约：


```shell
punica compile
```

如果执行成功，将会在 contracts 文件夹下生成 build 文件夹：


```shell
contacts
    ├─build
    │      contract.avm
    │      contract_abi.json
```

如果想使用 punica 编译时的更多选项，使用`punica compile --help` 命令查看。

```shell
$ punica compile --help
Usage: punica compile [OPTIONS] CONTRACT_NAME

  Compile the specified contracts to avm and abi file.

Options:
  --contracts TEXT  Compile specified contracts files in contracts dir.
  --local BOOLEAN   Use local compiler.
  -h, --help        Show this message and exit.
```

- `--contracts`：指定编译的合约文件。
- `--local`：指定使用的编译器。

### 部署

部署之前，你需要关心以下两个配置文件：

- `punica-config.json`：配置使用的区块链网络
- `default-config.json`（contracts 目录下）：配置部署合约的参数信息和调用合约中函数的参数。

部署命令：

```shell
$ punica deploy
```

示例：
```shell
$ punica deploy
Using network 'privateNet'.

Running deployment: hello_ontology.avm
	Deploying...
	Deploy to: cb9f3b7c6fb1cf2c13a40637c189bdd066a272b4
Deploy successful to network...
	 Contract address is cb9f3b7c6fb1cf2c13a40637c189bdd066a272b4
	 Txhash is 041db938710e0c2977bbb8af1bdf97a3efae8256baa0ec74980c98734e25f650
```

要查看更多选项，可以使用以下命令：

```shell
sss:punica-init-default-box sss$ punica deploy -h
Usage: punica deploy [OPTIONS]

  Deploys the specified contracts to specified chain.

Options:
  --network TEXT  Specify which network the contracts will be deployed.
  --avm TEXT      Specify which avm file will be deployed.
  --wallet TEXT   Specify which wallet file will be used.
  --config TEXT   Specify which deploy config file will be used.
  -h, --help      Show this message and exit.
```

- `--network TEXT` ：指定使用的网络，默认使用 punica-config.json 里的配置文件
- `--avm TEXT` ：指定使用的 avm，默认使用 defaul-config.json 中配置的 avm 文件
- `--wallet TEXT`：指定使用的钱包文件，默认使用 walle t文件夹下的 wallet.json 文件
- `--config TEXT`：指定使用的配置文件，默认使用 defaul-config.json

### 调用

调用之前，请确保 default-config.json 文件中已经配好合约方法需要的参数。

`default-config.json `配置示例部分内容如下所示，完整内容请查看 [init box](https://github.com/punica-box/punica-init-default-box/blob/master/contracts/default-config.json)。

```json
{
    "defaultWallet": "wallet.json",
    "password": {
        "AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ": "password",
        "AecaeSEBkt5GcBCxwz1F41TvdjX3dnKBkJ": "password",
        "AQvZMDecMoCi2y4V6QKdJBtHW1eV7Vbaof": "password"
    },
    "deployConfig": {
        "name": "contract name ",
        "version": "contract version",
        "author": "the author of contract",
        "email": "email address",
        "desc": "a description for your contract",
        "needStorage": true,
        "payer": "AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ",
        "gasPrice": 0,
        "gasLimit": 31000000
    },
    "invokeConfig": {
        "abi": "hello_ontology_abi.json",
        "defaultPayer": "AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ",
        "gasPrice": 0,
        "gasLimit": 20000,
        "functions": [
            {
                "operation": "testByteArrayListAndStr", //合约中函数名
                "args": [                               //合约中需要的参数
                    {
                        "bytearrayList": [
                            "ByteArray:Hello",
                            "ByteArray:world"
                        ]
                    },
                    {
                        "msgStr": "String:hello"
                    }
                ],
                "signers": {},
                "preExec": true
            },
            {
                "operation": "testStructList",
                "args": [
                  {
                      "structList": [
                        [
                          "String:hello",
                          1
                        ],
                        [
                          "String:hello2",
                          2
                        ]
                      ]
                  }
                ],
                "signers": {},
                "preExec": true
            },
            {
                "operation": "testStructListAndStr",
                "args": [
                  {
                      "structList": [
                          [
                            "String:hello",
                             1
                          ],
                          [
                            "String:hello2",
                             2
                          ]
                      ]
                  },
                  {
                    "msgStr": "String:test"
                  }
                ],
                "signers": {},
                "preExec": true
            }
        ]
    }
}
```

参数值的配置如下：
- "String:test"："String" 表示合约中的函数需要的参数类型是 String。
- "ByteArry:test"："ByteArray" 表示合约中的函数需要的参数类型是 ByteArray。
- "Address:AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ"：表示将参数`AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ ` 按照 Address 的格式转换成字节数组。
- "Hex:0a"：表示将参数 `0a` 按照 hex 的形式转换成字节数组

`default-config.json` 配置完成后，可以通过下面的命令查看可以调用的函数


```shell
punica invoke list
```

输出结果为：

```shell
sss:punica-init-default-box sss$ punica invoke list
All Functions:
	 testHello
	 testNumList
	 testNumListAndStr
	 testStrListAndStr
	 testByteArrayListAndStr
	 testStructList
	 testStructListAndStr
```

使用下面的命令运行指定函数：
```shell
sss$ punica invoke --functions testHello
Using network 'privateNet'.

Running invocation: hello_ontology_abi.json
Unlock default payer account...
Invoking  testHello
Invoke successful
Invoke result: ['01', '64', '74657374', '74657374', '0a', '8f651d459b4f146380dab28e7cfb9d4bb9c3fcd1']
```

要查看invoke更多信息，执行下面的命令：
```shell
$ punica invoke -h
Usage: punica invoke [OPTIONS] COMMAND [ARGS]...

  Invoke the function list in default-config or specify config.

Options:
  --network TEXT    Specify which network the contracts will be deployed.
  --wallet TEXT     Specify which wallet file will be used.
  --functions TEXT  Specify which function will be executed.
  --config TEXT     Specify which config file will be used.
  --preexec TEXT    preExec the function.
  -h, --help        Show this message and exit.

Commands:
  list  List all the function in default-config or...
```

- `--functions TEXT`：指定要执行的函数，可以一次指定多个函数，例如：`punica invoke --functions testHello,testNumList`
- `--preexec TEXT`：预执行，预执行表示不会将状态更新到区块链，适合于查询的函数。
其他的配置信息请参看上面的讲解。


### Node


```shell
$ punica node
Usage: punica node [OPTIONS]

   Ontology Blockchain private net in test mode. please download from
   https://github.com/punicasuite/solo-chain/releases

Options:
   -h, --help  Show this message and exit.
```

### Scpm

```shell
$ punica scpm
Usage: punica scpm [OPTIONS]

   smart contract package manager，support download and publish.

Options:
   -h, --help  Show this message and exit.

```
### Smartx

```shell
$ punica smartx

Please go to Smartx for debugging smart contracts:
http://smartx.ont.io/#/
```
### 测试

```shell
$ punica test -h
Usage: punica test [OPTIONS] COMMAND [ARGS]...

  Unit test with specified smart contract

Options:
  --file TEXT  Specify which test file will be used.
  -h, --help   Show this message and exit.

Commands:
  template  generate test template file
```

### 钱包

```shell
$ punica wallet
Usage: punica wallet [OPTIONS] COMMAND [ARGS]...

   Manager your asset, ontid, account.

Options:
   -h, --help  Show this message and exit.

Commands:
   account  Manager your account.
   asset    Manager your asset, transfer, balance,...
   ontid    Manager your ont_id, list or add.

```

