
# Punica-Cli

## Overview

Punica-Cli is a command line interface designed to allow devlopers to compile, deploy and invoke smart contracts without the need for a full SDK. Punica-Cli is currently available in two languages: [Punica Python CLI](https://github.com/punicasuite/punica-python) or [Punica TypeScript CLI](https://github.com/punicasuite/punica-ts).

### Features:
* Supports intelligent smart contract compilation, deployment, invocation and testing;
* Supports both Python and TypeScript programming languages;
* Download dApp templates via Punica-Box;
* Smart contract packaging management tools;
* Supports wallet file management.
<p><br>

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
**Note: If you are using Python, please ensure you have [Python v3.7](https://www.python.org/downloads/release/python-370/) or above installed.**
<p><br>


## Available Commands

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


### Initializing a New Project

You can create an empty Punica project with no smart contracts using the `init` command.

```shell
punica init
```

Once this operation has completed, you will have a project structure with the following items:

- `contracts/`: Directory for Ontology smart contracts.
- `src/`: Directory for DApp source file(s).
- `test/`: Directory for test files to test your application and contracts.
- `wallet/`: Directory for saved Ontology wallet file.

For more usage information, you can use `punica init --help`
```shell
punica init --help
Usage: punica init [OPTIONS]

  Initialize new and empty Ontology DApp project.

Options:
  -h, --help  Show this message and exit.
```

**Note**: If you are not running punica-cli in the root directory of your project, you need to use the `-p` or `--project` option to specify your DApp project path.
<p><br>

### Using a Punica-Box Project

For those just getting started, you can use Punica Boxes which are example dApps/project templates to help you.

We will be using the [Tutorialtoken-box](https://github.com/punica-box/tutorialtoken-box) through-out this tutorial which creates an OEP4 token that can be transferred between accounts.

Create a new directory for your Punica project:

```shell
mkdir tutorialtoken
cd tutorialtoken
```

Download ("unbox") the Tutorialtoken-box Box:

```shell
punica unbox tutorialtoken
```

For more usage information, you can use `punica unbox --help`
```shell
punica unbox --help
Usage: punica unbox [OPTIONS] BOX_NAME

  Download a Punica Box, a pre-built Ontology DApp project.

Options:
  -h, --help  Show this message and exit.
```

#### Configure the network used by Punica-Cli

The Tutorialtoken-box contains a file called `punica-config.json' in the project root directory which defauls to the Ontology Testnet.  You can alter the DefaultNet setting in this file to set which network Punica-Cli will use.

Example punica-config.json:
```json
{
  "networks": {
    "testNet": {
      "host": "http://polaris3.ont.io",
      "port": 20336
    },
    "mainNet": {
      "host": "http://dappnode1.ont.io",
      "port": 20336
    },
    "privateNet": {
      "host": "http://127.0.0.1",
      "port": 20336
    }
  },
  "defaultNet":"testNet"
}
```

**Notes**:
- You can use the `punica unbox <box-name>` command to download any of the other [Punica Boxes](http://punica.ont.io/boxes/).
- If you are not running punica-cli in the root directory of your project, you need to use the `-p` or `--project` option to specify your DApp project path.
<p><br>


### Compiling

We will now use the `compile` command to compile the Tutorialtoken-box smart contract:

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

For more usage information, you can use `punica compile --help`

```shell
punica compile --help
Usage: punica compile [OPTIONS] CONTRACT_NAME

  Compile the specified contracts to avm and abi file.

Options:
  --contracts Only compile the specified contract
  -h, --help  Show this message and exit.
```
**After you compile the smart contract ensure you have sufficient ONG in the account that will be paying for the deployment (see next step) or else deployment will fail.  The address for the Tutorialtoken-box is ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6**

**Note**: If you are not running punica-cli in the root directory of your project, you need to use the `-p` or `--project` option to specify your DApp project path.
<p><br>

### Deployment

To deploy the Tutotialtoken-box smart contract to the selected network, run the following:

```shell
punica deploy
```

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

For more usage information, you can use `punica deploy --help`

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

**Notes**:

- If you are not running punica-cli in the root directory of your project, you need to use the `-p` or `--project` option to specify your DApp project path.
- If multiple `avm` files exist in your `contracts/build` directory, you need to use the `--avm` option to specify which contract you want to deploy.
- If a multi-wallet file exist in your `wallet` directory, you may need to use the `--wallet` option to specify which wallet you want to use. If you do not specify a random wallet file in `wallet` directory will be used.
<p><br>

### Invocation

To setup your smart contract you must run the `punica invoke` command before invoking any specific functions.

```shell
punica invoke
```

Output:
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

In the `default-config.json` file of the Tutorialtoken-box is an 'invokeConfig' section that defines the functions of our smart contract. See example below:

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

To see the list of available functions:
```shell
punica invoke list
```

Response when running `punica invoke list' on the Tutorialtoken-box
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

For more usage information, you can use `punica invoke --help`

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

**Notes**:

- If you are not running punica-cli in the root directory of your project, you need to use the `-p` or `--project` option to specify your DApp project path.
- If a multi-wallet file exist in your `wallet` directory, you may need to use the `--wallet` option to specify which wallet you want to use. If you do not specify a random wallet file in `wallet` directory will be used.
<p><br>

### Node

Shows the download link for Solo-chain, a pre-built Ontology private-net.

For more usage information, you can use `punica node --help'
```shell
punica node --help
Usage: punica node [OPTIONS]

   Ontology Blockchain private net in test mode. please download from
   https://github.com/punicasuite/solo-chain/releases

Options:
   -h, --help  Show this message and exit.
```
<p><br>

### Scpm (not yet implemented)

The smart contract package manager allows you to download and publish punica boxes to the community repository.

```shell
punica scpm
Usage: punica scpm [OPTIONS]

   smart contract package manager，support download and publish.

Options:
   -h, --help  Show this message and exit.
```
<p><br>

### Smartx (not yet implemented)

SmartX is Ontology's online smart contract IDE and debugger.

```shell
punica smartx

Please go to Smartx for debugging smart contracts:
http://smartx.ont.io/#/
```
<p><br>

### Unit Testing

The test function allows you to run automated test against your smart contract using a test file.

For more usage information, you can use `punica test --help'
```shell
punica test -h
Usage: punica test [OPTIONS] COMMAND [ARGS]...

  Unit test with specified smart contract

Options:
  --file TEXT  Specify which test file will be used.
  -h, --help   Show this message and exit.

Commands:
  template  generate test template file
```
<p><br>

### Wallet

Allows you to manage your wallet with functions such as adding, listing or deleting accounts or OntID's as well as transfering assets (ONT/ONG).

Example:
```shell
punica wallet account list
Account:
        ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6
        AazEvfQPcQ2GEFFPLF1ZLwQ7K5jDn81hve
        Ad4H6AB3iY7gBGNukgBLgLiB6p3v627gz1
        ARLvwmvJ38stT9MKD78YtpDak3MENZkoxF
```

For more usage information, you can use `punica wallet --help'
```shell
punica wallet --help
Usage: punica wallet [OPTIONS] COMMAND [ARGS]...

   Manager your asset, ontid, account.

Options:
   -h, --help  Show this message and exit.

Commands:
   account  Manage your account.
   asset    Manage your asset, transfer, balance,...
   ontid    Manage your ont_id, list or add.

```
