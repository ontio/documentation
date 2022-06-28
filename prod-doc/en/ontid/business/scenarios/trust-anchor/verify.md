# Trust anchor - verify claim

1. 确定 claim 验签公钥，开放给验签方
2. Web-app 根据用户提供的 claim，配合 Trust anchor 提供的公钥进行验签
3. 验签通过，claim 有效，进一步向链上查询 claim 状态
4. 链上状态通过，claim 校验通过

