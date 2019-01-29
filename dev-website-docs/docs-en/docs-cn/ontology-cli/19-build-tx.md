
本体客户端 `Ontology-CLI` 提供了构造交易模块，用于构造对原生资产 `ONT` 与 `ONG` 进行操作的交易。

> **注意**：为了使所构造的交易有效，交易在发送到链上之前，还需要使用钱包账户进行签名。

## 转账交易

```shell
$ ontology buildtx transfer --from 1 --to AaCe8nVkMRABnp5YgEjYZ9E5KYCxks2uce --asset ont --amount 10
Transfer raw tx:
00d1810144e2f401000000000000204e0000000000005c0708fbe99dcf821c1acf261dd61748b69d0c156e00c66b6a145c0708fbe99dcf821c1acf261dd61748b69d0c15c86a14ca216237583e7c32ba82ca352ecc30782f5a902dc86a5ac86c51c1087472616e736665721400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b650000
```
