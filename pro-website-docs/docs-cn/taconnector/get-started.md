
我们以学信网（China Credentials Verification）学历认证为例，使用 `ontology-python-sdk` 讲解如何快速成为一个信任锚。

<div align="center"><img src="https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/trust-anchor-connector.png"></div>

目前，学信网能够提供如图所示的学籍在线验证报告。

<div align="center"><img src="https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/xjbg-sample.png"></div>

## 准备工作

安装 Python SDK：

```shell
pip install ontology-python-sdk
```

## 创建 SDK 实例

```python
sdk = OntologySdk()
```

## 创建钱包文件

```python
wallet_path = 'wallet.json'
sdk.wallet_manager.create_wallet_file(path)
```

## 创建有效的 ONT ID

- 在钱包文件中创建 ONT ID

```python
sdk.wallet_manager.open_wallet(wallet_path)
password = 'password'
identity = sdk.wallet_manager.create_identity('Label', password)
ont_id = identity.ont_id
sdk.wallet_manager.save()
```

- 在智能合约中注册ONT ID

```python
sdk.rpc.connect_to_test_net()
ctrl_acct = sdk.wallet_manager.get_control_account_by_index(ont_id, 0, password)
payer_acct = ctrl_acct
tx_hash = sdk.native_vm.ont_id().registry_ont_id(identity.ont_id, ctrl_acct, payer_acct, gas_limit, gas_price)
time.sleep(6)
event = sdk.rpc.get_smart_contract_event_by_tx_hash(tx_hash)
hex_contract_address = sdk.native_vm.ont_id().contract_address
notify = ContractEventParser.get_notify_list_by_contract_address(event, hex_contract_address)
```

## 生成可信申明

- 查询在智能合约中注册的公钥

```python
pub_keys = sdk.native_vm.ont_id().get_public_keys(ont_id)
```

- 创建可信声明

```python
pk = pub_keys[0]
kid = pk['PubKeyId']
iss_ont_id = identity2.ont_id
sub_ont_id = identity1.ont_id
exp = int(time())
context = 'https://example.com/template/v1'
clm = dict(Name='NashMiao', JobTitle='SoftwareEngineer', HireData=str(time()))
clm_rev = dict(type='AttestContract', addr='8055b362904715fd84536e754868f4c8d27ca3f6')

claim = sdk.service.claim()
claim.set_claim(kid, iss_ont_id, sub_ont_id, exp, context, clm, clm_rev)
claim.generate_signature(ctrl_acct)
gas_limit = 20000
gas_price = 500
blockchain_proof = claim.generate_blockchain_proof(ctrl_acct, payer_acct, gas_limit, gas_price)
```

- 生成 base64 编码的可信申明

```python
b64_claim = claim.generate_b64_claim()
```

## 验证可信申明

```python
claim.validate_blockchain_proof(blockchain_proof))
```
