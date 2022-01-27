

<div align="center">
  <img src="https://raw.githubusercontent.com/ontio-community/bounty-program-report/master/image/sc-vscode-exten.png" height="200" width="200">
</div>

---

## Overview

Visual Studio Code combines the simplicity of a source code editor with powerful developer tooling, like IntelliSense code completion and debugging.

Before start, please check you have download [VSCode](https://code.visualstudio.com/).This extension adds support for development and testing of smart contracts on Ontology blockchain. **And please disable `pylint` when VSCode recommends it to you.**

<div align="center">
<img src="https://raw.githubusercontent.com/ontio-community/bounty-program-report/master/image/vscode.png" >
</div>  

**Features:**
1. Compile: VSCode supports Python smart contracts (.py) and CSharp smart contracts (.cs).
2. Deploy: Deploy smart contracts to MainNet / TestNet/ PrivateNet.
3. Invoke: Execute or pre-execute a smart contract.
4. Debug: Support debug procedure (StepIn, StepOut, Next, Continue, Stop, Restart), setting breakpoints, variables preview and set, and state store manipulation.

## Getting started


### 1. Extension Settings

This extension contributes the following settings:

- `ontology.network.type`: specifies which network will be used during deployment and invocation
- `ontology.network.private`: PrivateNet address in the form of http://host:port
- `ontology.wallet`: wallet file used during deployment and invocation (you can use \${workspaceFolder} in the path)
- `ontology.payer`: default payer address (must be found in wallet file)
- `ontology.deploy.gasLimit`: gas limit used during deployment
- `ontology.deploy.gasPrice`: gas price used during deployment
- `ontology.invoke.gasLimit`: gas limit used during invocation
- `ontology.invoke.gasPrice`: gas price used during invocation

Those settings can be changed in standard VSCode settings by clicking the gear box icon in lower left corner.

![Settings 1](https://raw.githubusercontent.com/ontio/vscode-ext-ontology/master/img/settings1.png)
![Settings 2](https://raw.githubusercontent.com/ontio/vscode-ext-ontology/master/img/settings2.png)


### 2. How to use Ontology extension?

Go to extensions market first, and then find and install the **VSCode Extension for Ontology extension**. Open any .py or .cs file in VS Code. The extension is now activated. This extension enhances the whole Smart contract development process.

#### 2.1 Compile

To compile a smart contract, show context menu on any .py or .cs file.

![Compile](https://raw.githubusercontent.com/ontio/vscode-ext-ontology/master/img/compile.png)

Press `Compile smart contract`. You will be notified about the outcome of compilation through notifications. The compilation will produce compiled code in .avm file and smart contract description file in \_abi.json file, both in `build` folder.

#### 2.2 Deploy

To deploy a smart contract, show context menu on compiled .avm file.

![Deploy 1](https://raw.githubusercontent.com/ontio/vscode-ext-ontology/master/img/deploy1.png)

Press `Deploy smart contract`. A new panel with description form will show up. Enter the necessary information and press `Deploy`. You will be notified about the outcome of compilation through notifications.

#### 2.3 Invoke & Debug

To invoke a method in the smart contract, opening the \_abi.json file. A new panel with smart contract methods will show up.

![Invoke 1](https://raw.githubusercontent.com/ontio/vscode-ext-ontology/master/img/invoke1.png)

Double click on any of the methods to show invocation form. Fill out all the parameters and click the `invoke` button.

![Invoke 2](https://raw.githubusercontent.com/ontio/vscode-ext-ontology/master/img/invoke2b.png)
![Invoke 3](https://raw.githubusercontent.com/ontio/vscode-ext-ontology/master/img/invoke3b.png)

You will be notified about the progress of invocation through notifications and a new panel with invocation result will show up.

![Invoke 4](https://raw.githubusercontent.com/ontio/vscode-ext-ontology/master/img/invoke4.png)

If you want to debug a smart contract  instead of invocation, pressing the `Debug` button. You can use standard debug features of VSCode like StepIn, StepOut, Next, Continue, Restart, Stop and breakpoints together with variables preview and set.



### 3. Extension author

- **Matus Zamborsky** - _Initial work_ - [Backslash47](https://github.com/backslash47)





