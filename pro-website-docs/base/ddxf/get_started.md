<h1 align="center">Distributed Data Exchange Framework Component Getting Started Guide</h1>

<!-- TOC -->

- [1. Cryptography Component](#1-cryptography-component)
    - [1.1. Introduction](#11-introduction)
    - [1.2. Install](#12-install)
    - [1.3. Usage](#13-usage)
- [2. Smart Contract Library](#2-smart-contract-library)
    - [2.1. Introduction](#21-introduction)
    - [2.2. Install](#22-install)
- [3. InterPlanetary File System (IPFS)](#3-interplanetary-file-system-ipfs)
    - [3.1. How IPFS Works](#31-how-ipfs-works)
    - [3.2. IPFS HTTP API](#32-ipfs-http-api)
    - [3.3. Initialize your IPFS Repository](#33-initialize-your-ipfs-repository)
    - [3.4. Create your Private IPFS Network (optional)](#34-create-your-private-ipfs-network-optional)
    - [3.5. Run your IPFS Node](#35-run-your-ipfs-node)
    - [3.6. Client Library for IPFS API](#36-client-library-for-ipfs-api)
- [4. Demo Project: Interplanetary Album](#4-demo-project-interplanetary-album)
    - [4.1. Introduction](#41-introduction)
    - [4.2. Architecture](#42-architecture)
    - [4.3. Setting up the environment](#43-setting-up-the-environment)
    - [4.4. Learn by using it](#44-learn-by-using-it)

<!-- /TOC -->

## 1. Cryptography Component

### 1.1. Introduction

The Distributed Data Exchange Framework (also DDXF) Cryptography Component is based on Python 3.5 and provides a cryptography kit for DDXF. Currently, it contains the hash kit, encryption kit, signature kit, and Key Derivation Function (KDF) kit.

You can visit [here](https://github.com/NashMiao/ontology-ddxf-crypto) to get more information.

**Note**: This component has **NOT** been audited and might potentially be unsafe. Take precautions to clear memory properly and store the private keys safely. You need to test it fully before using in production!

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

You can visit [here](https://github.com/NashMiao/ontology-ddxf-contract) to get more information about DDXF.

**Note**: This contract library has **NOT** been audited and might potentially be unsafe. You need to test fully before using in production!

### 2.2. Install

You can get the library from GitHub:

```shell
git clone https://github.com/NashMiao/ontology-ddxf-contract.git
```

## 3. InterPlanetary File System (IPFS)

InterPlanetary File System (IPFS) is a protocol and network designed to create a content-addressable, peer-to-peer method of storing and sharing hypermedia in a distributed file system.

![](https://github.com/NashMiao/ontology-ddxf-bot/blob/master/img/ipfs.jpeg)

### 3.1. How IPFS Works

You may be interested about how IPFS works. In fact, when we add files to IPFS:

- Each file and all of the blocks within it are given a unique fingerprint called a cryptographic hash;
- IPFS removes duplications across the network;
- Each network node stores only content it is interested in, and some indexing information that helps figure out who is storing what;
- When looking up files, you're asking the network to find nodes storing the content behind a unique hash;
- Every file can be found by human-readable names using a decentralized naming system called IPNS.

### 3.2. IPFS HTTP API

When an IPFS node is running as a daemon, it exposes an HTTP API that allows you to control the node and run the same commands you can from the command line.

In many cases, using this API is preferable to embedding IPFS directly into your program — it allows you to maintain peer connections that are longer lived than your app and you can keep a single IPFS node running instead of several if your app can be launched multiple times. In fact, the IPFS CLI commands use this API when operating in online mode.

This API is intended to be the same across different IPFS implementations. However, not all implementations are equally up-to-date. The most feature-complete (and the current reference for this specification) is go-ipfs.

![](https://github.com/NashMiao/ontology-ddxf-bot/blob/master/img/ipfsHttp.png)

### 3.3. Initialize your IPFS Repository

IPFS stores all its settings and internal data in a directory called the repository. Before using IPFS for the first time, you’ll need to initialize the repository with the `ipfs init` command:

```shell
PS C:\Users> ipfs init
initializing IPFS node at C:\Users\.ipfs
generating 2048-bit RSA keypair...done
peer identity: QmbhtBLaPLLUXgon7Quue1JkLjRmoQmm97cqto9JdJ4KuR
to get started, enter:

        ipfs cat /ipfs/QmS4ustL54uo8FzR9455qaxZwuMiUhyvMcX9Ba8nUH4uVv/readme
```

The hash after `peer identity` is your node’s ID and will be different from the one shown in the above output. Other nodes on the network use it to find and connect to you. You can run `ipfs id` at any time to get it again if you need it.

### 3.4. Create your Private IPFS Network (optional)

The IPFS bootstrap list is a list of peers with which the IPFS daemon learns about other peers on the network. IPFS comes with a default list of trusted peers, but you are free to modify the list to suit your needs. One popular use for a custom bootstrap list is to create a personal IPFS network. You can get your IPFS bootstrap list using the `bootstrap` command.

```shell
PS C:\Users> ipfs bootstrap
/dnsaddr/bootstrap.libp2p.io/ipfs/QmNnooDu7bfjPFoTZYxMNLWUQJyrVwtbZg5gBMjTezGAJN
/dnsaddr/bootstrap.libp2p.io/ipfs/QmQCU2EcMqAqQPR2i9bChDtGNJchTbq5TbXJJ16u19uLTa
/dnsaddr/bootstrap.libp2p.io/ipfs/QmbLHAnMoJPWSCR5Zhtx6BHJX9KiKNN6tpvbUcqanj75Nb
/dnsaddr/bootstrap.libp2p.io/ipfs/QmcZf59bWwK5XFi76CZX8cbJ4BhTzzA3gU1ZjYZcYW3dwt
/ip4/104.131.131.82/tcp/4001/ipfs/QmaCpDMGvV2BGHeYERUEnRQAwe3N8SzbUtfsmvsqQLuvuJ
/ip4/104.236.179.241/tcp/4001/ipfs/QmSoLPppuBtQSGwKDZT2M73ULpjvfd3aZ6ha4oFGL1KrGM
/ip4/104.236.76.40/tcp/4001/ipfs/QmSoLV4Bbm51jM9C4gDYZQ9Cy3U6aXMJDAbzgu2fzaDs64
/ip4/128.199.219.111/tcp/4001/ipfs/QmSoLSafTMBsPKadTEgaXctDQVcqN88CNLHXMkTNwMKPnu
/ip4/178.62.158.247/tcp/4001/ipfs/QmSoLer265NRgSp2LA3dPaeykiS1J6DifTC88f5uVQKNAd
/ip6/2400:6180:0:d0::151:6001/tcp/4001/ipfs/QmSoLSafTMBsPKadTEgaXctDQVcqN88CNLHXMkTNwMKPnu
/ip6/2604:a880:1:20::203:d001/tcp/4001/ipfs/QmSoLPppuBtQSGwKDZT2M73ULpjvfd3aZ6ha4oFGL1KrGM
/ip6/2604:a880:800:10::4a:5001/tcp/4001/ipfs/QmSoLV4Bbm51jM9C4gDYZQ9Cy3U6aXMJDAbzgu2fzaDs64
/ip6/2a03:b0c0:0:1010::23:1001/tcp/4001/ipfs/QmSoLer265NRgSp2LA3dPaeykiS1J6DifTC88f5uVQKNAd
```

**Note**: You **must** understand the risks of adding or removing nodes form IPFS node's bootstrap list before you do so.

Therefore, if you want to create your own IPFS network, you need to remove the default list of trusted peers, and add the peers that you trust.

```shell
PS C:\Users> ipfs bootstrap rm --all
removed /dnsaddr/bootstrap.libp2p.io/ipfs/QmNnooDu7bfjPFoTZYxMNLWUQJyrVwtbZg5gBMjTezGAJN
removed /dnsaddr/bootstrap.libp2p.io/ipfs/QmQCU2EcMqAqQPR2i9bChDtGNJchTbq5TbXJJ16u19uLTa
removed /dnsaddr/bootstrap.libp2p.io/ipfs/QmbLHAnMoJPWSCR5Zhtx6BHJX9KiKNN6tpvbUcqanj75Nb
removed /dnsaddr/bootstrap.libp2p.io/ipfs/QmcZf59bWwK5XFi76CZX8cbJ4BhTzzA3gU1ZjYZcYW3dwt
removed /ip4/104.131.131.82/tcp/4001/ipfs/QmaCpDMGvV2BGHeYERUEnRQAwe3N8SzbUtfsmvsqQLuvuJ
removed /ip4/104.236.179.241/tcp/4001/ipfs/QmSoLPppuBtQSGwKDZT2M73ULpjvfd3aZ6ha4oFGL1KrGM
removed /ip4/104.236.76.40/tcp/4001/ipfs/QmSoLV4Bbm51jM9C4gDYZQ9Cy3U6aXMJDAbzgu2fzaDs64
removed /ip4/128.199.219.111/tcp/4001/ipfs/QmSoLSafTMBsPKadTEgaXctDQVcqN88CNLHXMkTNwMKPnu
removed /ip4/178.62.158.247/tcp/4001/ipfs/QmSoLer265NRgSp2LA3dPaeykiS1J6DifTC88f5uVQKNAd
removed /ip6/2400:6180:0:d0::151:6001/tcp/4001/ipfs/QmSoLSafTMBsPKadTEgaXctDQVcqN88CNLHXMkTNwMKPnu
removed /ip6/2604:a880:1:20::203:d001/tcp/4001/ipfs/QmSoLPppuBtQSGwKDZT2M73ULpjvfd3aZ6ha4oFGL1KrGM
removed /ip6/2604:a880:800:10::4a:5001/tcp/4001/ipfs/QmSoLV4Bbm51jM9C4gDYZQ9Cy3U6aXMJDAbzgu2fzaDs64
removed /ip6/2a03:b0c0:0:1010::23:1001/tcp/4001/ipfs/QmSoLer265NRgSp2LA3dPaeykiS1J6DifTC88f5uVQKNAd
```

**Tips**: With an empty list, we can restore the default bootstrap list with the `--default` option.

```shell
ipfs bootstrap add --default
```

To be extra cautious, you can also set the `LIBP2P_FORCE_PNET` environment variable to 1 to force the usage of private networks. If no private network is configured, the daemon will fail to start.

```shell
user@ubuntu:~$ export LIBP2P_FORCE_PNET=1
user@ubuntu:~$ echo $LIBP2P_FORCE_PNET
1
```

To create a private network, we also need to create a `swarm.key` file to enable the private network feature of IPFS. We will start by adding a key called the `swarm.key` that tells the IPFS nodes that they will be a part of a private network which all will share this `swarm.key` file.

If you have a Go environment, you can run the following command to install the `swarm.key` generation utility:

```shell
go get -u github.com/Kubuxu/go-ipfs-swarm-key-gen/ipfs-swarm-key-gen
```

After successfully installing this utility, you can run it in one of your nodes like this:

```shell
ipfs-swarm-key-gen > ~/.ipfs/swarm.key
```

Then, you need to copy the file generated to the IPFS directory of each node.

Now, you can add your new bootstrap node to build your private network. For example:

```shell
PS C:\Users> ipfs bootstrap add /ip4/192.168.181.141/tcp/4001/ipfs/QmYzdL2Pe3JvoqMZ1qvcVMnAWo4fVqyvw2S8XDnxHLK8MV
added /ip4/192.168.181.141/tcp/4001/ipfs/QmYzdL2Pe3JvoqMZ1qvcVMnAWo4fVqyvw2S8XDnxHLK8MV
```

### 3.5. Run your IPFS Node

Before we use the IPFS HTTP API, we need to run our IPFS node as a daemon.

```shell
PS C:\Users> ipfs daemon
```

If your node runs properly, you will see the following output:

```shell
Initializing daemon...
Swarm is limited to private network of peers with the swarm key
Swarm key fingerprint: e06fa4c6c256f4524bc3abb4a1515556
Swarm listening on /ip4/127.0.0.1/tcp/4001
Swarm listening on /ip4/169.254.120.205/tcp/4001
Swarm listening on /ip4/169.254.28.251/tcp/4001
Swarm listening on /ip4/169.254.77.95/tcp/4001
Swarm listening on /ip4/192.168.182.1/tcp/4001
Swarm listening on /ip4/192.168.50.211/tcp/4001
Swarm listening on /ip4/192.168.56.1/tcp/4001
Swarm listening on /ip4/192.168.99.1/tcp/4001
Swarm listening on /ip6/::1/tcp/4001
Swarm listening on /p2p-circuit/ipfs/QmauvPUxzGN32aBtHXGRGCbNPxkpCA5ZFc637ABFjGe2mF
Swarm announcing /ip4/127.0.0.1/tcp/4001
Swarm announcing /ip4/169.254.120.205/tcp/4001
Swarm announcing /ip4/169.254.28.251/tcp/4001
Swarm announcing /ip4/169.254.77.95/tcp/4001
Swarm announcing /ip4/192.168.182.1/tcp/4001
Swarm announcing /ip4/192.168.3.90/tcp/49660
Swarm announcing /ip4/192.168.50.211/tcp/4001
Swarm announcing /ip4/192.168.56.1/tcp/4001
Swarm announcing /ip4/192.168.99.1/tcp/4001
Swarm announcing /ip6/::1/tcp/4001
API server listening on /ip4/127.0.0.1/tcp/5001
Gateway (readonly) server listening on /ip4/127.0.0.1/tcp/8080
Daemon is ready
```

### 3.6. Client Library for IPFS API

- [Go](https://github.com/ipfs/go-ipfs-api)
- [Python](https://github.com/ipfs/py-ipfs-api)
- [JavaScript](https://github.com/ipfs/js-ipfs)

## 4. Demo Project: Interplanetary Album

### 4.1. Introduction

Interplanetary Album is a decentralized album based on the InterPlanetary File System (IPFS), Ontology Distributed Identity Framework (ONTID), and DDXF Cryptography Component.

You can visit [here](https://github.com/punica-box/interplanetary-album-box) to get more information.

### 4.2. Architecture

![](https://github.com/punica-box/interplanetary-album-box/blob/master/img/interplanetary-album.svg)

### 4.3. Setting up the environment

There are a few technical requirements before we start. Please install the following:

- [python 3.7](https://www.python.org/downloads/release/python-370/)
- [go-ipfs](https://dist.ipfs.io/#go-ipfs)

### 4.4. Learn by using it

We can run the interplanetary album in our browser:

```shell
python interplanetary_album.py
```

- If everything goes smoothly, your interplanetary album will run on `http://127.0.0.1:5000/`, and your IPFS node will run on http://127.0.0.1:5001/.

- If you want to quit it, you can press `CTRL+C` or close the terminal.

In the interplanetary-album project, IPFS addresses of pictures are bound with ONT ID and encrypted with its public key in the elliptic curve integrated encryption scheme (also ECIES). In other words, only the picture owner and the user he shared with can visit his picture in the IPFS Network.

![](https://github.com/punica-box/interplanetary-album-box/blob/master/img/loginSuccessful.png)
