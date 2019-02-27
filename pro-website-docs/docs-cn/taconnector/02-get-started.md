
## 简介

我们以学信网（China Credentials Verification）学历认证为例，使用 `ontology-python-sdk` 讲解如何快速成为一个信任锚。

<div align="center"><img src="https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/ta-connector/trust-anchor-connector.png"></div>

目前，学信网能够提供如图所示的学籍在线验证报告，更多关于学信网的介绍，你可以点击[这里](https://www.chsi.com.cn/)。

<div align="center"><img width=500px src="https://raw.githubusercontent.com/ontio/documentation/master/pro-website-docs/assets/ta-connector/xjbg-sample.png"></div>

如果你想成为学信网的信任锚，你可以根据用户提交的学籍在线验证码，为用户签发一份区块链上的学籍报告。

## 准备工作

- 使用 `pip` 安装 Python SDK：

```shell
pip install ontology-python-sdk
```

- 创建 SDK 实例

```python
sdk = OntologySdk()
```

从流程规范性上来看，使用 Python SDK 的第一步是对其进行实例化。

- 创建钱包文件

```python
wallet_path = 'wallet.json'
sdk.wallet_manager.create_wallet_file(path)
```

!> 在钱包文件中，存有你的账户、身份信息，请务必妥善保管，并进行安全备份。

- 在钱包文件中创建 ONT ID

```python
sdk.wallet_manager.open_wallet(wallet_path)
password = 'password'
identity = sdk.wallet_manager.create_identity('Label', password)
sdk.wallet_manager.save()
```

通过 SDK，你可以在本地快速生成一个 ONT ID。

- 在智能合约中注册ONT ID

```python
sdk.rpc.connect_to_test_net()
ctrl_acct = sdk.wallet_manager.get_control_account_by_index(ont_id, 0, password)
payer_acct = ctrl_acct
tx_hash = sdk.native_vm.ont_id().registry_ont_id(identity.ont_id, ctrl_acct, payer_acct, gas_limit, gas_price)
```

在钱包中生成的 OND ID 需要在智能合约中进行注册，才能真正有效。

- 查询 ONT ID 注册事件

```python
event = sdk.rpc.get_smart_contract_event_by_tx_hash(tx_hash)
hex_contract_address = sdk.native_vm.ont_id().contract_address
notify = ContractEventParser.get_notify_list_by_contract_address(event, hex_contract_address)
```

一般在交易发出 6 秒后，便可以根据交易哈希查询该笔交易是否已经成功执行并被写入到区块。

## 查询报告

学信网信任锚通过提供 Restful 服务（或者其他类型的服务），接收用户提交的学籍在线验证码，并向学信网数据库请求对应的学籍信息。

```python
def query_edu(q_code: str):
    url = ChesiccMethod.query_edu(q_code)
    response = requests.post(url, timeout=10)
    msg = response.content.decode('utf-8')
    return msg
```

## 报告规范化

根据用户所提交的学籍在线验证码，学信网信任锚能够从学信网获取到是非规范化的《教育部学籍在线验证报告》，为了生成一份区块链上的学籍报告，你需要将其转化为规范化的学籍报告。

以 `Python` 为例，通过使用流行的 HTML 与 XML 文件解析库 `Beautiful Soup`，你能够快速完成验证报告的规范化。

```python
def chsi_parser(page, get_img: bool = False):
    soup = BeautifulSoup(page, features='lxml-xml')
    result_table = soup.find('div', {'class': 'clearfix', 'id': 'resultTable'})
    info_dict = dict()
    if result_table is None:
        return info_dict
    if get_img:
        result_table.find('img', {'id': 'photoPositon'})
    info_list = result_table.find_all('td')[3:33]
    for index in range(0, len(info_list), 2):
        info_key = info_list[index].contents[0]
        info_value = info_list[index + 1].find('div').contents[0]
        info_dict[info_key] = info_value.replace(' ', '').replace('\n', '')
    return info_dict
```

## 可信申明的创建

在获得规范化验证报告之后，你需要为你的用户签发相应的可信申明。

- 查询在智能合约中注册的公钥

```python
pub_keys = sdk.native_vm.ont_id().get_public_keys(ont_id)
```

`get_public_keys` 接口会返回指定 ONT ID 在智能合约中注册的所有可用公钥。

信任锚通过该接口获取与其 ONT ID 相对应的公钥列表，然后选取其中的一把公钥，使用对应的私钥对可信申明进行签名，从而形成经过信任锚认证的可信申明。

- 创建可信声明

```python
pk = pub_keys[0]
kid = pk['PubKeyId']
iss_ont_id = identity.ont_id
sub_ont_id = 'did:ont:ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD'
exp = int(time())
context = 'https://example.com/template/v1'
clm = dict(Name='NashMiao', JobTitle='SoftwareEngineer', HireData=str(time()))
clm_rev = dict(type='AttestContract', addr='8055b362904715fd84536e754868f4c8d27ca3f6')

claim = sdk.service.claim()
claim.set_claim(kid, iss_ont_id, sub_ont_id, exp, context, clm, clm_rev)
```

- 签署可信申明

```python
claim.generate_signature(ctrl_acct)
```

- 链上存证

```python
blockchain_proof = claim.generate_blockchain_proof(ctrl_acct, payer_acct, 20000, 500)
```

- 生成 base64 编码的可信申明

```python
b64_claim = claim.generate_b64_claim()
```

## 可信申明的加密

出于安全考虑，信任锚需要根据用户的 ONT ID，对编码后的可信申明进行端到端的加密。

目前，在端到端加密模块，`ontology-python-sdk` 提供了 `CBC` 加密模式与 `GCM` 加密模式供用户选择，如果你需要更多的加密模式，可以点击[这里](https://github.com/ontio/ontology-python-sdk/issues)向我们题出需求。

- `CBC` 模式

```python
private_key_bytes = ECIES.generate_private_key()
public_key_bytes = ECIES.get_public_key_by_bytes_private_key(private_key_bytes)
msg = b'Attack!'
aes_iv, encode_g_tilde, cipher_text = ECIES.encrypt_with_cbc_mode(msg, public_key_bytes)
decrypt_msg = ECIES.decrypt_with_cbc_mode(cipher_text, private_key_bytes, aes_iv, encode_g_tilde)
```

- `GCM` 模式

```python
private_key_bytes = ECIES.generate_private_key()
public_key_bytes = ECIES.get_public_key_by_bytes_private_key(private_key_bytes)
msg = b'Attack!'
nonce, mac_tag, encode_g_tilde, cipher_text = ECIES.encrypt_with_gcm_mode(msg, b'', public_key_bytes)
decrypt_msg = ECIES.decrypt_with_gcm_mode(nonce, mac_tag, cipher_text, private_key_bytes, b'', encode_g_tilde)
```

## 可信申明的传输

信任锚在将加密后的可信申明通过互联网发送给用户。

```python
import request

response = requests.post(url, json=payload, headers=header, timeout=10)
```

## 可信申明的验证

用户可以在收到学籍信息的可信申明后，对其进行验证。同时，该申明作为用户的一个凭证，可以交给其他可信第三方进行验证，以证明用户学籍信息的真实有效性。

```python
claim = sdk.service.claim()
sdk.rpc.connect_to_main_net()
```

- 验证签名

```python
claim.validate_signature(b64_claim)
```

- 查询区块链证明

```python
claim.validate_blk_proof()
```

## 可信申明的维护

可信申明的状态有两种：有效、已吊销。在为可信申明生成区块链证明时，可信申明被注册，其状态为有效。

- 注册

```python
sdk.neo_vm.claim_record().commit(claim.claim_id, identity2_ctrl_acct, identity1.ont_id, acct1, gas_limit, gas_price)
```

`commit` 接口返回交易哈希，你可以根据该交易哈希查询可信申明注册事件。

- 查询注册事件

```python
event = sdk.neo_vm.claim_record().query_commit_event(tx_hash)
```

- 吊销

```python
sdk.neo_vm.claim_record().revoke(claim.claim_id, identity2_ctrl_acct, acct1, gas_limit, gas_price)
```

`revoke` 接口返回交易哈希，你可以根据该交易哈希查询可信申明吊销事件。

- 查询吊销事件

```python
event = sdk.neo_vm.claim_record().query_revoke_event(tx_hash)
```
