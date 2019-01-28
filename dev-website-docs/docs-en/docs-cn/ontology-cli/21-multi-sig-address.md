
生成多重签名地址需要指定公钥列表PubKey，以及在公钥列表中的所需要的最少签名数量M。

### 生成多重签名地址参数
--pubkey
pubkey 参数用于指定多重签名的公钥列表，公钥之间用逗号','分隔。
账户公钥可以通过命令：

```
./ontology account list -v
```
查看。

目前多重签名支持的最大公钥数为16。

-m
m 参数用于指定所以的最少签名数。默认值为1。

```
./ontology multisigaddr --pubkey=03c0c30f11c7fc1396e8595bf2e339d553d728ea6f21ae831e8ab704ca14fe8a56,02b2b9fb60a0add9ef6715ffbac8bc7e81cb47cd06c157c19e6a858859c0158231 -m=1
```
返回如下：

```
Pub key list:
Index 1 Address:AaCe8nVkMRABnp5YgEjYZ9E5KYCxks2uce PubKey:02b2b9fb60a0add9ef6715ffbac8bc7e81cb47cd06c157c19e6a858859c0158231
Index 2 Address:ARVVxBPGySL56CvSSWfjRVVyZYpNZ7zp48 PubKey:03c0c30f11c7fc1396e8595bf2e339d553d728ea6f21ae831e8ab704ca14fe8a56

MultiSigAddress:Ae4cxJiubmgueAVtNbjpmm2AGNgdKP6Ea7
```
