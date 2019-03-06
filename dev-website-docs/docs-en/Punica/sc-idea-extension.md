



**PyCharm Plugin for Ontology** support for Ontology Smart Contract Development:

1. Contract Compilation (.py)
2. Contract Deployment (TestNet / MainNet / PrivateNet)
3. Contract Invocation (Payed / PreExec)
4. Contract Debugging (Step through / Breakpoints / Variables Preview)

## Installation

### Includes debugging

1. Install Node.js, by using your favorite way such as [Official Installation Package](https://nodejs.org/en/) or [Node Version Manager](https://github.com/creationix/nvm) etc.

2. Install `Ontdev` via Command Line `npm install -g ontdev`

3. [Download](https://github.com/punicasuite/pycharm-plugin-for-ontology/releases) and install the plugin's jar file from disk.

   1. In the **Settings/Preferences** dialog OSX shortcut `⌘,` Windows shortcut `Ctrl+Alt+S`, select **Plugins**
  
   2. In the **Plugins** dialog, click <img width="16" src="https://www.jetbrains.com/help/img/idea/2018.3/icons.general.gearPlain.svg@2x.png" /> and then click **Install Plugin from Disk..**
   
      <img width="450" src="./doc/imgs/install-1.png" />

### Without debugging

If there is no need of debugging in your project then the installations of Node.js environment and `Ontdev` are skippable. Just begin your installing from the former step 3.

You could also setup `Ontdev` after the project is created, the entry can be found by right click on the project root directory then click **Project settings**:

<img width="450" src="./doc/imgs/settings.png" />

## Tools

This plugin provides conversion between various literals:

* String <=> Hex string

* Address <=> Script hash

* Number <=> Hex string

* Byte array <=> Hex string

* Endian conversion

The entry could be found via **Tools -> Ontology Tools**:

<img width="450" src="./doc/imgs/tools.png" />