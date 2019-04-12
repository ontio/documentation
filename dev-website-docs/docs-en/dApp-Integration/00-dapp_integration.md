This article provides a universal DApp access solution for developers who come to the ontologies to develop DApps, allowing developers to quickly build DApps.

## Main DApp Features

When DApp interacts with the ontology chain, it mainly has the following functions:

### log in

Allows verification of user identity or direct access to account/identity information.

### Payment

Implement DApp's payment function by calling smart contract.

### Calling a smart contract

For DApp, smart contracts implement all or part of their business logic. With the game example, you can purchase, sell, lease, or get random numbers and other different services and functions. See the Smart Contract for detailed business logic.

### Assets on the chain (optional)

Asset-winding is not required for DApp development, but some DApps require specific chain-based assets to run their internal logic.
According to different demand for assets, the ontology provides three different types of chain assets: OEP4, OEP5, and OEP8.

[What is OEP-4, OEP-5, OEP-8? ](https://dev-docs.ont.io/#/docs-en/dApp-Integration/11-Q&A?id=_1-%E4%BB%80%E4%B9%88%E6%98%AFoep -4%EF%BC%8Coep-5%EF%BC%8Coep-8-%EF%BC%9F)

## Access technology implementation

In order to achieve the above several functions, we provide two Dapp access technology solutions, two access methods can be used to log in, call smart contracts and other functions, developers can choose one of them to access development according to their needs

### ONT ID Open Platform (Integrated Solution)


The ONT ID open platform provides third-party applications for third-party applications such as login, payment, smart contract execution, and KYC.

The advantage of the ONT ID open platform is that with the trusted hosting mode, the user login DApp will no longer rely on the user's local wallet, greatly expanding the scope of DApp.

- [ONT ID Open Platform Integration] (docs-en/dApp-Integration/08-ontid_integration.md)

### DApi integration (decentralization scheme)


It introduces how DApp calls DApi in various scenarios, including operations such as logging in, calling smart contracts, and so on.

The advantage of DApi integration is that users can master all their assets and information, and it is now more convenient to use the supported wallet to log in to the DApp.

- [DApi Integration] (docs-en/dApp-Integration/09-dapi_integration.md)