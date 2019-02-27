
## 密码学组件

### 简介

去中心化数据交易框架（DDXF）密码学组件是一个基于 `Python3.5` 的加密组件，为 DDXF 提供加密工具包。目前，它包含哈希工具包、加密工具包、签名工具包和密钥派生（KDF）工具包。

你可以访问[这里](https://github.com/NashMiao/ontology-ddxf-crypto)来获取更多的信息。

!> 该组件**尚未**经过安全审计，可能存在安全隐患。在生产环境中使用之前，请**务必**进行安全审计！

### 安装

安装需要 `Python 3.5` 或更高版本的环境。

```shell
pip install ontology-ddxf-crypto
```

### 使用

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

## 智能合约库

### 简介

去中心化数据交易框架（DDXF）智能合约库是一个数据交换合约库。

你可以访问[这里](https://github.com/NashMiao/ontology-ddxf-contract)来获取更多的信息。

!> 该合约库**尚未**经过安全审计，可能存在安全隐患。在生产环境中使用之前，请**务必**进行安全审计！

### 安装

你可以从 GitHub 上获取此库。

```shell
git clone https://github.com/NashMiao/ontology-ddxf-contract.git
```

## 星际文件系统 （IPFS）

行星际文件系统（IPFS）是一种基于内容寻址的协议和一个点对点网络，旨在提供一种在分布式文件系统中存储和共享超媒体的方法。

### 星际文件系统是如何工作的？

你也许会对星际文件系统的工作方式感兴趣。实际上，当我们向IPFS添加文件时：

- 每个文件及其中的所有块都被赋予了一个称为加密哈希的唯一指纹。
- IPFS消除了网络上的重复。
- 每个网络节点仅存储它感兴趣的内容，以及一些索引信息，帮助确定谁在存储什么。
- 查找文件时，你通过一个唯一的哈希值去请求网络查找内容存储节点。
- 使用名为IPNS的去中心化命名系统，可通过人类可读的名称找到每个文件。

### 星际文件系统 HTTP API

当星际文件系统节点作为守护程序运行时，它会公开一个HTTP API，允许你控制节点并在命令行运行相同的命令。

在许多情况下，使用此API比在程序中直接嵌入星际文件系统更好——它允许你维护比你的应用程序更长的对等连接，并且如果你的应用程序会启动多次，你可以保持单个IPFS节点运行而不是多次。 实际上，IPFS CLI命令在联机模式下运行时会使用此API。

星际文件系统 HTTP API旨在使不同的星际文件系统实现保持相同的 HTTP API。但是，并非所有实现都同样是最新的，功能最完整（以及此规范的当前参考）是 go-ipfs。

![](https://raw.githubusercontent.com/punica-box/interplanetary-album-box/master/img/ipfsHTTP.png)

### 初始化你的星际文件系统存储库

星际文件系统将其所有设置和内部数据存储在称为存储库（repository）的目录中。 在第一次使用星际文件系统之前，您需要使用 `ipfs init` 命令初始化存储库：

```shell
$ ipfs init
initializing IPFS node at .ipfs
generating 2048-bit RSA keypair...done
peer identity: QmbhtBLaPLLUXgon7Quue1JkLjRmoQmm97cqto9JdJ4KuR
to get started, enter:

        ipfs cat /ipfs/QmS4ustL54uo8FzR9455qaxZwuMiUhyvMcX9Ba8nUH4uVv/readme
```

在 `peer identity` 之后的哈希值是你节点的ID，并且会与上面输出的值不同。网络上的其他节点使用它来查找并连接到你的节点。如果需要，您可以随时运行 `ipfs id` 以再次获取它。

### 创建你的私有星际文件系统网络（可选）

星际文件系统的引导列表是星际文件系统守护进程与网络上的其他对等节点进行通信的节点列表。星际文件系统附带一个可信节点的默认列表，但是你可以自由修改列表以满足特定的需要。自定义引导列表的一个常用用途是创建私有星际文件系统网络。你可以通过 `bootstrap` 命令获取星际文件系统引导列表。

```shell
$ ipfs bootstrap
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

!> 在执行此操作之前，你**务必**充分了解在星际文件系统节点的引导列表中添加或删除节点所可能带来的风险。

因此，如果要创建私有的星际文件系统网络，需要删除默认的可信节点，并添加你信任的节点。

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

<p class="info">当引导列表为空时，我们可以通过 <code>--default</code> 选项恢复默认的引导列表。</p>

```shell
ipfs bootstrap add --default
```

谨慎起见，你还可以将环境变量 `LIBP2P_FORCE_PNET` 设置为 `1` 以强制使用私有网络。如果未配置私有网络，则守护进程将无法启动。

```shell
$ export LIBP2P_FORCE_PNET=1
$ echo $LIBP2P_FORCE_PNET
1
```

要创建私有网络，我们还需要创建一个 `swarm.key` 文件来启用星际文件系统的私有网络功能。我们需要首先创建一个名为 `swarm.key` 的密钥，星际文件系统中共享`swarm.key` 文件的节点将成为私有网络的一部分。

如果你有Go环境，可以运行以下命令来安装一个用于生成 `swarm.key` 的实用程序：

```shell
go get -u github.com/Kubuxu/go-ipfs-swarm-key-gen/ipfs-swarm-key-gen
```

安装完成后，你可以在其中的一个节点中运行它，如下所示：

```shell
ipfs-swarm-key-gen > ~/.ipfs/swarm.key
```

然后，你需要将生成的 `swarm.key` 文件复制到每个星际文件系统节点的目录下。

现在，你可以添加新的引导列表以构建你的专用网络。例如：

```shell
$ipfs bootstrap add /ip4/192.168.181.141/tcp/4001/ipfs/QmYzdL2Pe3JvoqMZ1qvcVMnAWo4fVqyvw2S8XDnxHLK8MV
added /ip4/192.168.181.141/tcp/4001/ipfs/QmYzdL2Pe3JvoqMZ1qvcVMnAWo4fVqyvw2S8XDnxHLK8MV
```

### 运行你的星际文件系统节点

在我们使用星际文件系统 HTTP API 之前，我们需要将我们的星际文件系统节点作为守护进程运行。

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

### 星际文件系统客户端 API 库

- [Go](https://github.com/ipfs/go-ipfs-api)
- [Python](https://github.com/ipfs/py-ipfs-api)
- [JavaScript](https://github.com/ipfs/js-ipfs)

## 演示性项目：星际相册

### 简介

星际相册是一个基于星际文件系统（IPFS）、本体分布式身份框架（ONTID）和 DDXF 加密组件所构建的去中心化的相册。

你可以访问[这里](https://github.com/punica-box/interplanetary-album-box)来获取更多的信息。

### 架构

![interplanetary-album](https://raw.githubusercontent.com/punica-box/interplanetary-album-box/master/img/interplanetary-album.png)

### 环境搭建

我们需要为这个项目安装一些必不可少的软件：

- [python 3.7](https://www.python.org/downloads/release/python-370/)
- [go-ipfs](https://dist.ipfs.io/#go-ipfs)

### 做中学

我们可以在浏览器中运行我们的星际相册：

```shell
python interplanetary_album.py
```

- 如果一切顺利，我们的星际相册将运行在 `http://127.0.0.1:5000/`，而 `IPFS` 节点将运行在 `http://127.0.0.1:5001/` 。

- 如果你想退出程序，可以按下 `CTRL+C` 或者关闭终端。

在星际相册中，所有图片的 IPFS 地址都与 ONT ID 绑定，并通过椭圆曲线集成加密方案（ECIES）进行加密。也就是说，只有图片所有者和他共享的用户可以访问他在 IPFS 网络中的图片。

![](https://raw.githubusercontent.com/punica-box/interplanetary-album-box/master/img/loginSuccessful.png)

![](https://raw.githubusercontent.com/punica-box/interplanetary-album-box/master/img/collaspseAlbum.png)

![](https://raw.githubusercontent.com/punica-box/interplanetary-album-box/master/img/cardAlbum.png)

![](https://raw.githubusercontent.com/punica-box/interplanetary-album-box/master/img/sharePhoto.png)
