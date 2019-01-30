
<div align="center">
  <img src="https://raw.githubusercontent.com/punicasuite/punica-python/master/punica.png" height="200" width="200"><br><br>
</div>

<!-- TOC -->

# Punica Cli

- [1. 概览](#1-概览)
- [2. 安装](#2-安装)
- [3. 快速开始](#3-快速开始)
- [4. 开始使用](#4-开始使用)
    - [4.1. 创建一个项目](#41-创建一个项目)
        - [4.1.1. 初始化一个新项目](#411-初始化一个新项目)
	    - [4.1.2. 创建一个Box项目](#412-创建一个Box项目)
    - [4.2. 编译](#42-编译)
    - [4.3. 部署](#43-部署)
    - [4.4. 调用](#44-调用)
    - [4.5. Node](#45-node)
    - [4.6. Scpm](#46-scpm)
    - [4.7.  Smartx](#47-smartx)
    - [4.8.  测试](#48-测试)
    - [4.9.  钱包](#49-钱包)

## 1. 概览
欢迎使用Punica! Punica 机会拥有一切开发dapp所需要的功能。

### 特点
* Punica-Cli 支持智能合约编译，部署，调用，测试。
* Punica-Cli 实现了Python和TypeScript版本。
* Punica 网站提供了健全的文档和合约模板。
* 自动化生成dapp工程目录，提供多种box，是的开发者很容易的基于Punica-Boxes进行开发。
* 智能合约测试配置与smartx有相同的配置标准。
* 提供智能合约包管理工具。

```shell
punica
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

## 2. 安装

安装之前请先确保下面的工具已经安装

- [Python 3.7](https://www.python.org/downloads/release/python-370/)
- [Git](https://git-scm.com/)

然后，执行下面的命令进行安装

```shell
pip install punica
```

## 3. 快速开始

如果想使用Punica更多的命令，请先创建一个Punica 项目。


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
使用下面的命令生成一个新项目

```shell
sss$ punica init
Downloading...
Unpacking...
Unbox successful. Enjoy it!
```

## 4. 开始使用


### 4.1 创建一个项目

#### 4.1.1 初始化一个新项目

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

#### 4.1.2 创建一个Box项目

Punica Box 是punica dapp模板库，你可以下载你感兴趣的项目，然后基于该项目进行创建你的dapp。

- 创建一个新文件夹

```shell
mkdir tutorialtoken
cd tutorialtoken
```

- 下载Box

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

**Note**:

- 你可以使用`punica unbox <box-name>`免费下载任意的Box项目。
- 你可以在你的项目根目录使用punica的其他命令，也可以`-p` or `--project` 选项指定使用哪个项目。

### 4.2 编译

使用下面的命令编译你的合约


```shell
punica compile
```

如果执行成功，将会在contracts文件夹下生成build文件夹


```shell
contacts
    ├─build
    │      contract.avm
    │      contract_abi.json
```

如果你想使用punica更多的用法，你可以使用`punica compile --help`命令查看。

```shell
$ punica compile --help
Usage: punica compile [OPTIONS] CONTRACT_NAME

  Compile the specified contracts to avm and abi file.

Options:
  --contracts TEXT  Compile specified contracts files in contracts dir.
  --local BOOLEAN   Use local compiler.
  -h, --help        Show this message and exit.
```

`--contracts`选项用于指定编译哪个合约文件
`--local`选项用于指定使用哪个编译器

### 4.3 部署

部署之前，你要关心两个配置文件，一个是`punica-config.json`,该文件配置使用的区块链网络，另一个配置文件是contracts目录下面的default-config.json文件，
该文件用于配置部署合约的参数信息和调用合约中函数的参数。

部署命令

```shell
$ punica deploy
```

例子：
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

如果你想知道更多的用法你可以使用

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

- `--network TEXT` 用于指定使用的网络,默认使用punica-config.json里的配置文件
- `--avm TEXT` 用于指定使用的avm，默认使用defaul-config.json中配置的avm文件
- `--wallet TEXT`用于指定使用的钱包文件，默认使用wallet文件夹下的wallet.json文件
- `--config TEXT`用于指定使用的配置文件，默认使用defaul-config.json

### 4.4 调用

调用之前，请确保default-config.json文件中已经配好合约方法需要的参数。

`default-config.json`配置例子,省略了部分内容，完整内容请看[init box](https://github.com/punica-box/punica-init-default-box/blob/master/contracts/default-config.json)

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

请注意参数值的配置，
- "String:test", "String"表示合约中的函数需要的参数类型是String。
- "ByteArry:test", "ByteArray"表示合约中的函数需要的参数类型是ByteArray。
- "Address:AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ",表示将参数`AUr5QUfeBADq6BMY6Tp5yuMsUNGpsD7nLZ`按照Address的格式转换成字节数组。
- "Hex:0a"表示将参数`0a`按照hex的形式转换成字节数组


`default-config.json`配置完成后，可以通过下面的命令查看可以调用的函数


```shell
punica invoke list
```

输出结果是

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

使用下面的命令运行指定函数
```shell
sss$ punica invoke --functions testHello
Using network 'privateNet'.

Running invocation: hello_ontology_abi.json
Unlock default payer account...
Invoking  testHello
Invoke successful
Invoke result: ['01', '64', '74657374', '74657374', '0a', '8f651d459b4f146380dab28e7cfb9d4bb9c3fcd1']
```

如果你想查看invoke更多的信息，你可以执行下面的命令
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

- `--functions TEXT`表示指定要执行的函数，可以一次指定多个函数，例如：`punica invoke --functions testHello,testNumList`
- `--preexec TEXT`表示预执行，预执行表示不会将状态更新到区块链，适合于查询的函数。
其他的配置信息请参看上面的讲解。


### 4.5 Node


```shell
$ punica node
Usage: punica node [OPTIONS]

   Ontology Blockchain private net in test mode. please download from
   https://github.com/punicasuite/solo-chain/releases

Options:
   -h, --help  Show this message and exit.
```

### 4.6 Scpm

```shell
$ punica scpm
Usage: punica scpm [OPTIONS]

   smart contract package manager，support download and publish.

Options:
   -h, --help  Show this message and exit.

```
### 4.7 Smartx

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

### 4.8 钱包

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

