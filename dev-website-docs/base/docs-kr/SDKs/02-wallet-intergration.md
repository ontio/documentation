
이 문서의 개요는 다음과 같습니다.
* [개요](#wallet-integration-overview)
* [통합 안내서](#integration-Guide)
* [기본 계약 주소](#native-contract-address)

 
### 개요

#### Ontology SDK

SDK는 현재 프로그램에서 직접 호출되는 도구입니다.

지갑 기능에는 디지털 자산 및 디지털 신원에 대한 계정을 제공하는 기능이 포함됩니다. [wallet 사양](https://ontio.github.io/documentation/Wallet_File_Specification_en.html)

월렛 기능 
| Module                |                    Sub Module                    |     Test case      |
| ------------------    | :----------------------------------------------: | :------------------: |
| Wallet management    |           create                                 |     Use the mnemonic words when creating wallet(Based on BIP39 and BIP44 specifications)   |
|                       |          export                                 |    Export keystore      |
|                      |           import                                 |   Import keystore to wallet  |
|                      |                                                  |   Import from the mnemonic words  |
|                      |                                                  |   Import from private key      |
|                      |                                                  |    Import from WIF            |
|                      |         delete                                   |   Delete wallet account     |
|                      |        Information service                      |    Query balance of ONT&ONG |
|                      |                                                  |   Query details of ONT&ONG  |
|                      |                                                  |  Query unclaim ONT&ONG   |
|    Transfer Assets   |          Transfer                                |    ONT/ONG transfer        |
|                      |                                                  |      ONG Claim              |
|   ONT ID management  |         Create                                   |   Create a new ONT ID and write it in blockchain   |
|                      |        Import                                    |     Import keystore of ONT ID |
|                      |        Export                                    |     Export keystore of ONT ID |
|                      |       Information service                        |    Query ONT ID events , create, delete,etc.    |
|                      |                                                  |    Query ONT ID             |



현재 월렛 표준에 맞는 SDK

Java SDK ：[Java SDK](https://github.com/ontio/ontology-java-sdk/blob/master/docs) 

TypeScript SDK ：[Ts SDK](https://github.com/ontio/ontology-ts-sdk/tree/master/docs) 

Android SDK ：[Android SDK](https://github.com/ontio-community/ontology-andriod-sdk)

Golang SDK ：[Go SDK](https://github.com/ontio/ontology-go-sdk) 

Python SDK ：[Python SDK](https://github.com/ontio/ontology-python-sdk)

### 통합 가이드

* [iOS 월렛 통합](https://ontio.github.io/documentation/ontology_wallet_dev_ts_sdk_en.html)
* [Android 월렛 통합](https://ontio.github.io/documentation/ontology_wallet_dev_android_en.html)


### Native 컨트랙트 주소

contract | contract u160 address | Address
---|---|---
ONT Token | 0100000000000000000000000000000000000000| AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV
ONG Token | 0200000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbvhfRZMHJ
ONT ID | 0300000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6Ubvho7BUwN
Global Params | 0400000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbvhrUqmc2
Oracle | 0500000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbvhzQYRMK
Authorization Manager(Auth) | 0600000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6Ubvi9BuggV
Governance | 0700000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK
DDXF(Decentralized Exchange) | 0800000000000000000000000000000000000000 | AFmseVrdL9f9oyCzZefL9tG6UbviKTaSnK





 
