<div align="center">
<img src="https://avatars1.githubusercontent.com/u/43718245?s=400&amp;u=84eeb52003e5c32628fcc9cb23edd54d8596cf54&amp;v=4" height="200" width="200">
</div>

---

## Overview

 [Punica Box](http://punica.ont.io/boxes/) provides a variety of multi-language dApp examples and templates to help developers quick learn the fundamentals of programming on the Ontology blockchain.


Features：
* Example dApps for items such as ONT ID, OEP-4, OEP-5, etc.
* Developers can create their own boxes and add them to the community repository
* More development libraries will continue to be made be available for dApp development
<p><br>

## Using Punica-Box

In order to use a Punica-Box you first need to install either [Punica Python CLI](https://github.com/punicasuite/punica-python) or [Punica TypeScript CLI](https://github.com/punicasuite/punica-ts). Once installed and configured (see [documentation](http://dev-docs.ont.io/#/docs-en/Punica/punica-cli)) you begin by downloading (unboxing) a punica-box.

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


#### Compiling

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

#### Deployment

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

#### Invocation

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

To see a list of available functions for tutorialtoken-box use:
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

#### Scpm (not yet implemented)

The smart contract package manager allows you to download and publish punica boxes to the community repository.

```shell
punica scpm
Usage: punica scpm [OPTIONS]

   smart contract package manager，support download and publish.

Options:
   -h, --help  Show this message and exit.
```
<p><br>
