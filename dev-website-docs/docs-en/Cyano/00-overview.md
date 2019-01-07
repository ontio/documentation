<p>
  <img width="300px" src="https://raw.githubusercontent.com/OntologyCommunityDevelopers/cyano-wallet/master/wallet.png">
  <img width="300px" src="https://raw.githubusercontent.com/OntologyCommunityDevelopers/cyano-wallet/master/wallet2.png">
</p>

Cyano is WebExtension (a.k.a Chrome plugin) and Mobile wallet implement dAPI([OEP-6](https://github.com/backslash47/OEPs/blob/oep-dapp-api/OEP-6/OEP-6.mediawiki) and [CEP1](https://github.com/ontio-cyano/CEPs/blob/master/CEP1.mediawiki)) for the **Ontology** blockchain.


DAPI is a lightweight decentralized API for DAPP based on Ontology. It supports DAPP to communicate with Ontology through chrome plug-in wallet, mobile wallet and desktop wallet. The DAPP requirements protocol for different platforms is slightly different, but the corresponding dAPI interfaces are similar. Currently supports two sets of agreements:

* The protocol of dAPI for chrome is [OEP-6](https://github.com/backslash47/OEPs/blob/oep-dapp-api/OEP-6/OEP-6.mediawiki)
* The protocol of dAPI for mobile is [CEP1](https://github.com/ontio-cyano/CEPs/blob/master/CEP1.mediawiki)

There are two roles of provider and client, namely wallet and DAPP. The dAPI for chrome interface is quite rich, and dAPI for mobile supports scanning and waking up the wallet in addition to supporting major interfaces such as login and calling contracts.



