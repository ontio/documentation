
本体客户端 `Ontology-CLI` 提供了多签地址模块，用于根据公钥列表及签名门限 `M` 生成多重签名地址。可以在命令行中通过 `multisigaddr` 命令使用。

- `--pubkey`：用于指定多重签名地址的公钥列表，公钥之间用 `,` 分隔。
- `-m`：用于指定签名门限（默认为 `1`）。

要查看当前钱包账户中的公钥列表，使用 `ontology account list -v` 命令。

```shell
$ ontology multisigaddr --pubkey 1419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f36817042801013,02b76e86481df6e9814b203a41a0b040c87807d1bcfd18f8ea69c7d73ebf2b944a,02929e9d107f318d2cf8d99e4de47731e2d6a8eb8da5164e8d012373f06ac78157 -m 2
Pub key list:
Index 1 Address:AM6WtTARSpGsF8ugSnx9QZRu2wnP2Dk8Vo PubKey:02929e9d107f318d2cf8d99e4de47731e2d6a8eb8da5164e8d012373f06ac78157
Index 2 Address:AL4m8xiSrmxAjCEGVdZWADQgVuasozpnF9 PubKey:02b76e86481df6e9814b203a41a0b040c87807d1bcfd18f8ea69c7d73ebf2b944a
Index 3 Address:AQAUExGE2dQnw3bwJkz98DULGyxYJ6xBNa PubKey:1419e9b0d726b0712fb92015b8e41ee5e5bb3d0321485b13322c6f36817042801013

MultiSigAddress:ARCSXp1YYX5KUTogyTVczoypaAKc1h6o3h
```

<p class="warning">目前多重签名所支持的最大公钥数为 <code>16</code>。</p>
