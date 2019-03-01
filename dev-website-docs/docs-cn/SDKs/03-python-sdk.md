
## 安装

安装 `ontology-python-sdk` 需要 `Python 3.6` 或更高版本的环境。

- 从 PyPI 获取。

```shell
pip install ontology-python-sdk
```

- 点击[这里](https://github.com/ontio/ontology-python-sdk/releases)从 GitHub 获取。

## 快速开始

```python
from ontology.ont_sdk import OntologySdk

sdk = OntologySdk()
```

更多关于 `ontology-python-sdk` 的详细信息可以点击[这里](https://apidoc.ont.io/pythonsdk/)访问 API 文档。

## 网络

`ontology-python-sdk` 支持 RPC、Restful 以及 WebSocket 接口，你可以选择你需要的接口进行使用。

- 连接到 `polaris` 测试网

```python
sdk.rpc.connect_to_test_net()
sdk.restful.connect_to_test_net()
sdk.websocket.connect_to_test_net()
```

- 连接到主网

```python
sdk.rpc.connect_to_main_net()
sdk.restful.connect_to_main_net()
sdk.websocket.connect_to_main_net()
```

- 连接到本地节点

```python
sdk.rpc.connect_to_localhost()
sdk.restful.connect_to_localhost()
sdk.websocket.connect_to_localhost()
```

- 连接到自定义节点

```python
url = 'http://127.0.0.1:20334'
sdk.restful.set_address(url)
url = 'http://127.0.0.1:20335'
sdk.websocket.set_address(url)
url = 'http://127.0.0.1:20336'
sdk.rpc.set_address(url)
```

### Merkle 证明

`get_merkle_proof` 接口用于获取指定交易哈希所对应交易的 Merkle 证明。

```python
tx_hash = '12943957b10643f04d89938925306fa342cec9d32925f5bd8e9ea7ce912d16d3'
merkle_proof = sdk.rpc.get_merkle_proof(tx_hash)
```

<div align="center"><img src="https://raw.githubusercontent.com/ontio/documentation/master/dev-website-docs/assets/SDKs/merkle-tree.png" width="620px"></div>

<p class = "info">由于 <code>Merkle</code> 树的结构特征，通过使用默克尔证明技术，能够快速判断特定数据是否存在于默克尔树之中。</p>

## 钱包管理

```python
sdk.wallet_manager.open_wallet(wallet_path)
```

!> 钱包管理模块 **尚未** 经过安全审计，可能存在潜在的安全隐患。在生产环境中使用之前，请 **务必** 进行安全审计！

## 资产管理

```python
asset = sdk.native_vm.asset()
```

## OEP4

`OEP4`包使你能够轻松地与已经部署的Ontology OEP4智能合约进行交互。

!> <code>OEP4</code> 模块 **尚未** 经过安全审计，可能存在潜在的安全隐患。在生产环境中使用之前，请 **务必** 进行安全审计！

### Utils

`Utils`包为`Ontology Dapps`和其他`Ontology-Python-Sdk`包提供工具类方法。

|       | Main Function        |
| :---: | :------------------- |
|   1   | get_random_hex_str() |
|   2   | get_asset_address()  |
|   3   | get_random_bytes()   |

## 签名机

在使用签名机对交易进行签名时，其流程如下。

1. SDK 构造交易，将序列化后的交易发送给签名机。
2. 签名机收到交易，将交易反序列化。
3. 签名机完成交易的检查后，添加签名并发送交易。

<section class = "warning">
在使用签名机之前，请确保已经启动了签名机服务。
  <ul>
    <li>运行 go 程序。</li>
    <pre v-pre="" data-lang="shell"><code class="lang-shell">go run .\sigsvr.go</code></pre>
    <li>运行编译后的二进制应用程序。</li>
    <pre v-pre="" data-lang="shell"><code class="lang-shell">.\sigsvr</code></pre>
  </ul>
</section>

### 连接签名机

```python
from ontology.ont_sdk import OntologySdk

sdk = OntologySdk()
sdk.service.sig_svr.connect_to_localhost()
```

### 创建账户

```python
sdk.service.sig_svr.create_account('password')
```

### 导出账户

```python
sdk.service.sig_svr.export_account()
```

### 数据签名

```python
msg = '48656c6c6f2c20776f726c64'
b58_address = 'Ad4pjz2bqep4RhQrUAzMuZJkBC3qJ1tZuT'
sdk.service.sig_svr.sig_data(msg, b58_address, 'password')
```
