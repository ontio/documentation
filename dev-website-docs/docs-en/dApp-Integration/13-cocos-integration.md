
## Waht's Cocos Creator

Cocos Creator is a script development, entity-component and data-driven game development tool focused on content creation. An easy-to-follow content production workflow and a powerful suite of developer tools for game logic and high-performance game creation.

<div align="center"><img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/dapp-integration/cocos-structure.jpg" width="440px"></div>


<p class="info">
Cocos2d-x is a mature open source cross-platform game development framework that provides rich functions such as graphics rendering, GUI, audio, network, physics, user input, etc. It is widely used in game development and interactive application construction. Its core is written in C++ and supports development in C++, Lua or JavaScript. Cocos2d-x deploys to iOS, Android, HTML5, Windows and Mac systems with features focused on native mobile platforms.
</p>

## Getting Started

If you want to use Cocos Creator to develop blockchain games based on the ontology network, you can install the `ontology-dapi` required for the desktop browser and the `cyano-bridge` required for the mobile phone.

<p class="warning">
The <code>ontology-dapi</code> on the desktop browser cannot be used on the mobile side. Therefore, if you need multi-end adaptation, create different game scenarios for the desktop and mobile, and build them separately at build time.
</p>

### Desktop Browser

ontology-dapi is A lightweight Javascript library for interacting with Chrome Plugin which is integrated provider engine.

```bash
$ npm install ontology-dapi -S
```

We can use it as ES6 module in our game scene's script.

```JavaScript
import { client } from 'ontology-dapi';
```

We can also use it as CommonJS/ES6 module in our game scene's script.

```JavaScript
var client = require('ontology-dapi').client;
```

After we regist with Provider successful, we can use it in our project.

```JavaScript
client.registerClient({});
```

### Mobile Phone

cyano-bridge is library allows your dApp to interface with mobile wallet which is integrated provider engine.

```bash
$ npm install cyanobridge -S
```

We can use it as ES6 module in our game scene's TypeScript script.

```JavaScript
import { client } from 'cyanobridge';
```

We can also use it as CommonJS/ES6 module in our game scene's script.

```JavaScript
var client = require('cyanobridge').client;
```

After we regist with Provider successful, we can use it in our project.

```JavaScript
client.registerClient();
```

## Bitcoin Catcher Box

To give you a visual sense of the blockchain game, we deployed the sample project on GitHub pages.

### Desktop Browser

You can access games deployed in [here](https://punica-box.github.io/bitcoin-catcher-box/) in the Chrome kernel browser with Cyano Wallet installed.

<div align="center"><img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/dapp-integration/game-in-chrome.png" width="800px"></div>

<p class="warning">
The game's contract is currently only deployed on the polaris test network. So, before the experience, please switch your plugin wallet or mobile wallet to the polaris test network or any blockchain network that you have pre-deployed.
</p>

### Mobile Phone

You can access games deployed in [here](https://punica-box.github.io/bitcoin-catcher-box/) in a wallet that supports `CEP-1`, such as Cyano Wallet, Math Wallet.

<div align="center"><img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/dapp-integration/game-in-onto.jpg" width="280px"></div>

<p class="warning">
The game's contract is currently only deployed on the polaris test network. So, before the experience, please switch your plugin wallet or mobile wallet to the polaris test network or any blockchain network that you have pre-deployed.
</p>

### Getting Started

1. Install Punica CLI.

    ```bash
    $ pip3 install punica
    ```

2. Unbox the `bitcoin-catcher-box`.

    ```bash
    $ punica unbox bitcoin-catcher
    ```

3. Install dependency.

    ```bash
    $ npm install
    ```

4. Running Cocos Creator and opening Project.

<div align="center"><img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/dapp-integration/open-pj-in-cocos-creator.png" width="700px"></div>

### Document

For more information, you can visit [here](https://punica-box.gitbook.io/docs/bitcoin-catcher-box).
