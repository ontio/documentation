# Punica-Cli

[punica-python](https://github.com/punicasuite/punica-python)
[punica-ts](https://github.com/punicasuite/punica-ts)
## Overview


Features:
* Supports intelligent contract compilation, deployment, invocation, and testing. Each item can be completed simply and efficiently through a single line of commands and testing through a configuration file.
* Supports both Python and TypeScript programming languages;
* download dApp templates and Punica-Box;
* Smart contract packaging management tools;
* Supports wallet file management.

Punica-cli offers an interactive command line tool with many useful functions:	
* Create an empty project
* Create a project with various boilerplate/template projects 
* Compile/deploy/invoke/test/debug smart contracts
* Publish your project to Punica box to share with community
* Start solo chain in local(WIP)
* Smart contracts package manager(WIP)
......

Punica has two implementions: Punica-python and Punica-ts


## Installation

```shell
pip install punica
```
```
npm install punica-ts -g
```
or 

```shell
python setup.py install
```


## Quickstart

To use most Punica commands, you need to run them against an existing Punica project. So the first step is to create a Punica project.


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

## Getting started


#### 4.1.1. Initializing a New Project

You can create a bare Punica project with no smart contracts included, use `punica init` command.

Once this operation is completed, you'll now have a project structure with the following items:

- `contracts/`: Directory for Ontology smart contracts.
- `src/`: Directory for DApp source file.
- `test/`: Directory for test files for testing your application and contracts.
- `wallet/`: Directory for save Ontology wallet file.

```shell
punica init --help
Usage: punica init [OPTIONS]

  Initialize new and empty Ontology DApp project.

Options:
  -h, --help  Show this message and exit.
```

**Note**: If you not run punica cli in you project root directory, you need to use `-p` or `--project` option to specify your DApp project's path.

#### 4.1.2. Creating a Box Project

You can create a bare project template, but for those just getting started, you can use Punica Boxes, which are example applications and project templates.

We'll use the [ontology-tutorialtoken box](https://github.com/wdx7266/ontology-tutorialtoken), which creates a OEP4 token that can be transferred between accounts:

- Create a new directory for your Punica project:

```shell
mkdir tutorialtoken
cd tutorialtoken
```

- Download ("unbox") the MetaCoin box:

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

- You can use the `punica unbox <box-name>` command to download any of the other Punica Boxes.
- If you not run punica cli in you project root directory, you need to use `-p` or `--project` option to specify your DApp project's path.



### 4.2. Compiling

You can use the following command to compile your Ontology smart contracts:

```shell
punica compile
```

If everything goes smoothly, you can find the `avm` and `abi` file in `contracts/build` folder.

```shell
contacts
    ├─build
    │      contract.avm
    │      contract_abi.json
```

For more usage, you can use `punica compile --help` command.

```shell
punica compile --help
Usage: punica compile [OPTIONS] CONTRACT_NAME

  Compile the specified contracts to avm and abi file.

Options:
  --contracts Only compile the specified contract
  -h, --help  Show this message and exit.
```

**Note**: If you not run punica cli in you project root directory, you need to use `-p` or `--project` option to specify your DApp project's path.

### 4.3. Deployment

To deploy your contract, run the following:

```shell
punica deploy
```

This will deploy your smart contract in `bin` directory.

A simple deployment process looks like this:

```shell
Using network 'testNet'.

Running deployment: oep4.avm
	Deploying...
	... 0x0131c56b6a00527ac46a51527ac46a00c3044e616d659c6409006593096c7566
	Deploy to: 0xf9f47e6a80482eb1c8831789f46dbc5a4f606222
Deploy successful to network...
	... 0xc08a440a7f93cc7229fee15b55455fac51ec15153753303bd252c710547ecb62
Enjoy your contract:)
```

For more usage, you can use `punica deploy --help` command.

```shell
punica deploy --help
Usage: punica deploy [OPTIONS]

  Deploys the specified contracts to specified chain.

Options:
  --network TEXT   Specify which network the contract will be deployed.
  --avm TEXT       Specify which avm file will be deployed.
  --wallet TEXT    Specify which wallet file will be used.
  -h, --help       Show this message and exit.
```

**Note**:

- If you not run punica cli in you project root directory, you need to use `-p` or `--project` option to specify your DApp project's path.
- If multi `avm` file exist in your `bin` directory, you need to use `--avm` option to specify which contract you want to deploy.
- If multi wallet file exist in your `wallet` directory, you may need to use `--wallet` option to specify which wallet you want to use. otherwise, a random wallet file in `wallet` directory will be used.

### 4.4. Invocation

If you want to invoke a list of function in your deployed smart contract, a convenience way is to use `Invoke` command.

Support we have an invoke config in our `default-config.json`:

```json
"invokeConfig":{
    "abi": "oep4_token_abi.json",
    "defaultPayer": "ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6",
    "gasPrice": 0,
    "gasLimit": 21000000,
    "functions": [
        {   
	    "name": "Name",
            "params": {},
            "signers": {},
            "preExec": true
        },
	{
            "name": "Symbol",
            "params": {},
            "signers": {},
            "preExec": true
        },
	{
            "name": "Decimal",
            "params": {},
            "signers": {},
            "preExec": true
        },
        {
	    "name": "TotalSupply",
            "params": {},
            "signers": {},
            "preExec": true
        },
        {
	    "name":"BalanceOf",
            "params": {
                "account": "ByteArray:ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6"
            },
            "signers": {},
            "preExec": true
        },
        {
	    "name": "Transfer",
            "params": {
                "from_acct": "ByteArray:ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6",
                "to_acct": "ByteArray:AazEvfQPcQ2GEFFPLF1ZLwQ7K5jDn81hve",
                "amount": 1
            },
            "signers": {
                "m": 1,
                "signer": ["ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6"]
            },
            "preExec": false
        },
        {
	    "name": "TransferMulti",
            "params": {
                "args": [
                    {
                        "from": "ByteArray:ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6",
                        "to": "ByteArray:AazEvfQPcQ2GEFFPLF1ZLwQ7K5jDn81hve",
                        "amount": 1
                    },
                    {
                        "from": "ByteArray:AazEvfQPcQ2GEFFPLF1ZLwQ7K5jDn81hve",
                        "to": "ByteArray:Ad4H6AB3iY7gBGNukgBLgLiB6p3v627gz1",
                        "amount": 2
                    }
                ]
            },
            "signers": {
                "m": 1,
                "signer": ["ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6", "AazEvfQPcQ2GEFFPLF1ZLwQ7K5jDn81hve"]
            },
            "payer": "ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6",
            "preExec": false
        },
        {
	    "name": "Allowance",
            "params": {
                "owner": "ByteArray:ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6",
                "spender": "ByteArray:AazEvfQPcQ2GEFFPLF1ZLwQ7K5jDn81hve"
            },
            "signers": {
                "m": 1,
                "signer": ["ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6"]
            },
            "preExec": false
        },
        {
	    "name": "TransferFrom",
            "params": {
                "sender": "ByteArray:AazEvfQPcQ2GEFFPLF1ZLwQ7K5jDn81hve",
                "from_acct": "ByteArray:ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6",
                "to_acct": "ByteArray:Ad4H6AB3iY7gBGNukgBLgLiB6p3v627gz1",
                "amount": 1
            },
            "signers": {
                "m": 1,
                "signer": ["ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6"]
            },
            "preExec": false
        },
        {
	    "name": "Init",
            "params": {},
            "signers": {},
            "preExec": true
        }
    ]
}
```
View the functions that can be called

```shell
punica list
```

The following output we will get:
```shell
All Functions:
         Init
         Name
         Symbol
         Decimal
         TotalSupply
         BalanceOf
         Transfer
         TransferMulti
         Allowance
         TransferFrom
```

To run our invoke function list, run the following:

`punica invoke`

The following output we will get:

```shell
Running invocation: oep4.json
Using network 'testNet'.

Unlock default payer account...
	Unlock account: ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6
    Please input account password: 
	Unlock successful...
Invoking Name...
	Invoke successful...
		... Invoke result: 546f6b656e4e616d65
Invoking Symbol......
	
```

For more usage, you can use `punica invoke --help` command.

```shell
punica invoke --help
Usage: punica invoke [OPTIONS]

  Invoke the function list in punica-config.

Options:
  --network TEXT   Specify which network the contract will be deployed.
  --wallet TEXT    Specify which wallet file will be used.
  --functions Text Specify which function will be used.
  -h, --help       Show this message and exit.
```

**Note**:

- If you not run punica cli in you project root directory, you need to use `-p` or `--project` option to specify your DApp project's path.
- If multi wallet file exist in your `wallet` directory, you may need to use `--wallet` option to specify which wallet you want to use. otherwise, a random wallet file in `wallet` directory will be used.

### 4.5 Node

```shell
sss:test sss$ punica node
Usage: punica node [OPTIONS]

   Ontology Blockchain private net in test mode. please download from
   https://github.com/punicasuite/solo-chain/releases

Options:
   -h, --help  Show this message and exit.
```

### 4.6. Scpm

```shell
sss:test sss$ punica scpm
Usage: punica scpm [OPTIONS]

   smart contract package manager，support download and publish.

Options:
   -h, --help  Show this message and exit.

```
### 4.7  Smartx

```shell
sss:test sss$ punica smartx

Please go to Smartx for debugging smart contracts:
http://smartx.ont.io/#/
```
### 4.8  Test

```shell
sss:test sss$ punica test -h
Usage: punica test [OPTIONS] COMMAND [ARGS]...

  Unit test with specified smart contract

Options:
  --file TEXT  Specify which test file will be used.
  -h, --help   Show this message and exit.

Commands:
  template  generate test template file
```
### 4.9  Wallet

```shell
sss:test sss$ punica wallet
Usage: punica wallet [OPTIONS] COMMAND [ARGS]...

   Manager your asset, ontid, account.

Options:
   -h, --help  Show this message and exit.

Commands:
   account  Manager your account.
   asset    Manager your asset, transfer, balance,...
   ontid    Manager your ont_id, list or add.

```

## 