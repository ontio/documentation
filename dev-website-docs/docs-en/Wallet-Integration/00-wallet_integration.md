
## Overview

Wallet access can be divided into two levels:
- [Asset Function Integration](https://dev-docs.ont.io/#/docs-en/Wallet-Integration/01-WalletDocking-asset-docking)
- [provider sdk integration](https://dev-docs.ont.io/#/docs-en/Wallet-Integration/02-WalletDocking-provider-sdk-docking)

![wallet-integration](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/wallet_integration_en.png)

After the two layers of integration are completed, the scene can be accessed.

You can use the test network and the main network to test whether the access is successful.

### Asset Function Integration

Asset function integration is the foundation of wallet integration. The wallet App integrates ONT's SDK, and with the open browser interface, it can realize digital asset operation, account management and other functions, and meet the basic asset management needs of a large number of ontology community members.

![Integration Description](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/sdk_en.png)

Once the asset features are integrated, the wallet can provide the following features:
- interact with the chain
-  account number
- Digital assets
- Digital identity
- Node pledge

### provider sdk integration

Once the asset functionality is integrated, you can choose to implement provider sdk integration on your wallet. Since the DApp in the ontology ecosystem will be developed according to the unified standard, the wallet App integration provider sdk can access a variety of ontologies DApps without the need to connect one by one, which greatly saves development time.

![Integration Description](https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/integration/provider_sdk_en.png)

After the wallet completes the provider sdk integration, it supports the following mainstream DApp scenarios:
- Scan code login, transfer, call smart contract
- Open, login, transfer, call smart contract in the wallet
- Open the web version, login, transfer, call smart contract

### Testing DApp links
Once the integration is complete, you can test the successful completion of the access by opening the following link in your wallet:

Test Network DAPP：
`http://101.132.193.149:5000/#/`

Main network DAPP：
`https://ont.bet/`