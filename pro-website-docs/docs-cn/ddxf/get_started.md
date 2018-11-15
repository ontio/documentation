<h1 align="center">去中心化数据交易框架组件上手指南</h1>

<!-- TOC -->

- [1. 密码学组件](#1-密码学组件)
    - [1.1. 简介](#11-简介)
    - [1.2. 安装](#12-安装)
    - [1.3. 使用](#13-使用)
- [2. 智能合约库](#2-智能合约库)
    - [2.1. 简介](#21-简介)
    - [2.2. 安装](#22-安装)

<!-- /TOC -->

## 1. 密码学组件

### 1.1. 简介

去中心化数据交易框架（DDXF）密码学组件是一个基于 `Python3.5` 的加密组件，为 DDXF 提供加密工具包。目前，它包含哈希工具包、加密工具包、签名工具包和密钥派生（KDF）工具包。

你可以访问[这里](https://github.com/NashMiao/ontology-ddxf-crypto)来获取更多的信息。

**注意**：该组件**尚未**经过审核，可能不安全。你需要采取预防措施去正确清除内存、安全存储私钥。在生产中使用前需要完全测试！

### 1.2. 安装

安装需要 `Python 3.5` 或更高版本的环境。

```shell
pip install ontology-ddxf-crypto
```

### 1.3. 使用

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

## 2. 智能合约库

### 2.1. 简介

去中心化数据交易框架（DDXF）智能合约库是一个数据交换合约库。

你可以访问[这里](https://github.com/NashMiao/ontology-ddxf-contract)来获取更多的信息。

**注意**：该合约库**尚未**经过审核，可能不安全。在生产中使用前需要完全测试！

### 2.2. 安装

你可以从 GitHub 上获取此库。

```shell
git clone https://github.com/NashMiao/ontology-ddxf-contract.git
```