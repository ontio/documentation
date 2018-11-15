<h1 align="center">Distributed Data eXchange Framework Component Getting Started Guide</h1>

<!-- TOC -->

- [1. Cryptography Component](#1-cryptography-component)
    - [1.1. Introduction](#11-introduction)
    - [1.2. Install](#12-install)
    - [1.3. Usage](#13-usage)
- [2. Smart Contract Library](#2-smart-contract-library)
    - [2.1. Introduction](#21-introduction)
    - [2.2. Install](#22-install)

<!-- /TOC -->

## 1. Cryptography Component

### 1.1. Introduction

The Distributed Data eXchange Framework (also DDXF) Cryptography Component is a cryptography component based on Python3.5 and provide cryptography kit for DDXF. Currently, it contain hash kit, encryption kit, signature kit and Key Derivation Function (KDF) kit.

you can visit [here](https://github.com/NashMiao/ontology-ddxf-crypto) to get more information.

**Note**: This component has **NOT** been audited and might potentially be unsafe. Take precautions to clear memory properly, store the private keys safely. You need to test fully before using in production!

### 1.2. Install

Installation requires a Python 3.5 or later environment.

```shell
pip install ontology-ddxf-crypto
```

### 1.3. Usage

```python
import os

from crypto_component.encryption.ecies import ECIES
from ontology.wallet.wallet_manager import WalletManager

wallet_path = os.path.join(os.path.abspath(__file__), 'wallet.json')
wallet_manager = WalletManager()
wallet_manager.open_wallet(wallet_path)
msg = 'Hello DDXF!'
msg_bytes = msg.encode('utf-8')
aes_iv, encode_g_tilde, cipher_text = ECIES.encrypt_with_ont_id_in_cbc(msg, ont_id_acct)
decrypted_text_bytes = ECIES.decrypt_with_ont_id_in_cbc(aes_iv, encode_g_tilde, cipher_text, ont_id_acct)
decrypted_text = decrypted_text_bytes.decode('utf-8'))
```

## 2. Smart Contract Library

### 2.1. Introduction

The Distributed Data eXchange Framework (also DDXF) smart contract library is a data exchange contract library.

you can visit [here](https://github.com/NashMiao/ontology-ddxf-contract) to get more information.

**Note**: This contract library has **NOT** been audited and might potentially be unsafe. You need to test fully before using in production!

### 2.2. Install

You can get the library from GitHub easily.

```shell
git clone https://github.com/NashMiao/ontology-ddxf-contract.git
```