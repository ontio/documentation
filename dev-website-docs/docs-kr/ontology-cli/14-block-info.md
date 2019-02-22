
本体客户端 `Ontology-CLI` 提供了信息获取模块，可以在命令行中通过 `info` 命令进行以下操作：

- 查询交易信息
- 查询交易状态
- 查询区块信息
- 查询区块高度

此外，你可以通过 `help` 命令获取信息获取模块的帮助信息 。

```shell
ontology info help
```

## 交易信息

要根据交易哈希查询交易信息，使用`tx` 命令。

你可以在第一个终端将客户端连接到 `polaris` 测试网。

```shell
ontology --testmode
```

然后在第二个终端中查询 `polaris` 测试网中的交易信息。

请求正文如下：

```shell
$ ontology info tx 1ebde66ec3f309dad20a63f8929a779162a067c36ce7b00ffbe8f4cfc8050d79
{
   "Version": 0,
   "Nonce": 0,
   "GasPrice": 0,
   "GasLimit": 18446744073709551615,
   "Payer": "AFmseVrdL9f9oyCzZefL9tG6UbvhPbdYzM",
   "TxType": 209,
   "Payload": {
      "Code": "1c010114c27820271114214d747b0b577daf32a19911dcb90400ca9a3b04696e69741400000000000000000000000000000000000000010068164f6e746f6c6f67792e4e61746976652e496e766f6b65"
   },
   "Attributes": [],
   "Sigs": [],
   "Hash": "1ebde66ec3f309dad20a63f8929a779162a067c36ce7b00ffbe8f4cfc8050d79",
   "Height": 0
}
```

在返回的交易状态中，各字段的含义如下：

- `GasPrice`：交易对应的 GAS 价格。
- `GasLimit`：交易对应的 GAS 上限。
- `Payer`：支付交易费的账户。
- `Hash`：交易哈希。

## 交易状态

要根据交易哈希查询交易状态，使用`status` 命令。

你可以在第一个终端将客户端连接到 `polaris` 测试网。

```shell
ontology --testmode
```

然后在第二个终端中查询 `polaris` 测试网中的交易状态。

请求正文如下：

```shell
$ ontology info status 1ebde66ec3f309dad20a63f8929a779162a067c36ce7b00ffbe8f4cfc8050d79
Transaction states:
{
   "TxHash": "1ebde66ec3f309dad20a63f8929a779162a067c36ce7b00ffbe8f4cfc8050d79",
   "State": 1,
   "GasConsumed": 0,
   "Notify": [
      {
         "ContractAddress": "0100000000000000000000000000000000000000",
         "States": [
            "transfer",
            "AFmseVrdL9f9oyCzZefL9tG6UbvhPbdYzM",
            "AZW8eBkXh5qgRjmeZjqY2KFGLXhKcX4i2Y",
            1000000000
         ]
      }
   ]
}
```

在返回的交易状态中，各字段的含义如下：

- `State`：交易执行结果，若值为 `1`，表示交易执行成功。
- `GasConsumed`：执行交易所消耗的 `ONG`。
- `Notify` ：交易执行时所触发的事件。

## 区块信息

要根据区块高度或者区块哈希查询区块信息，使用`block` 命令。

你可以在第一个终端将客户端连接到 `polaris` 测试网。

```shell
ontology --testmode
```

然后在第二个终端中查询 `polaris` 测试网中的区块信息。

```shell
$ ontology info block 1
{
   "Hash": "80d66c3c7b8b56c86e5184c299a7063b6aba31222e16bb356dee7b9c34a4bc33",
   "Size": 1191,
   "Header": {
      "Version": 0,
      "PrevBlockHash": "44425ae42a394ec0c5f3e41d757ffafa790b53f7301147a291ab9b60a956394c",
      "TransactionsRoot": "fb2530764e458ef5b94147a687e85cbcf46ab575e1869730f792e57176d1a99b",
      "BlockRoot": "6a4b10e333cd4bc814f3023950f6d0c0988f71e9f958c4fbdda199943faf1f28",
      "Timestamp": 1530590965,
      "Height": 1,
      "ConsensusData": 321851621496534906,
      "ConsensusPayload": "7b226c6561646572223a332c227672665f76616c7565223a22424541365a3241624858556a343768377563732f4f6e646c6d6c3641647a4b5838422f4b79662b62354577772f554f68654274665555625966447648726a71492b585642684b6c736a6f31624c6546305066426a714d343d222c227672665f70726f6f66223a22336f586172416f6e4a6758732f2b46376f4c784233747670323231412f65723633687857596270454b477a6f6c34474c4b356e4763424d4d4e5a6872376f43564f46702b3079522f546739764837546a5a34485271513d3d222c226c6173745f636f6e6669675f626c6f636b5f6e756d223a302c226e65775f636861696e5f636f6e666967223a6e756c6c7d",
      "NextBookkeeper": "AFmseVrdL9f9oyCzZefL9tG6UbvhPbdYzM",
      "Bookkeepers": [
         "0205bc592aa9121428c4144fcd669ece1fa73fee440616c75624967f83fb881050",
         "030a34dcb075d144df1f65757b85acaf053395bb47b019970607d2d1cdd222525c",
         "021844159f97d81da71da52f84e8451ee573c83b296ff2446387b292e44fba5c98",
         "0205bc592aa9121428c4144fcd669ece1fa73fee440616c75624967f83fb881050",
         "020cc76feb375d6ea8ec9ff653bab18b6bbc815610cecc76e702b43d356f885835",
         "03aa4d52b200fd91ca12deff46505c4608a0f66d28d9ae68a342c8a8c1266de0f9"
      ],
      "SigData": [
         "0d0d15b43cc600f854921b7ec94398014240b39af913afb4eb431364867c44049aa51ae2f5ee266b747c01e5d01dedf774f7bd918ccee9e15066f88b46ccfd5f",
         "beae1a255c1d5fc5f98e96a06e94b043a4c8c6a1fd448509f44ff2eb34f5fd8a88b3d8768a98f603e346e680da86e5d56d8c8974deed47fa48f3acc666206d2d",
         "3fe38ca19525879530cd92b115bf9a6d2a4e9fde23b882de281cf3a373c3fad1bff6010cd5db4a6199de9eb3877a912577aef1b22c4eb765e5122436962d4353",
         "009d652ccc7ee247cbdfc464e40fbbf6891024911040fedf3ad1f79cf9f47ccda59868ce31c656d2c7a70a5212fb69e8ffbd8aaeb4ed59d2cd65d48322754af7",
         "ef327192819313d7d15eb7997c94990ec82e1ef8222a9081f131aa6b06177831c571fa07b2944dc14daba71c6ece4fd562096067fbd6d04f8e695243ac79afb1",
         "7217e37db874af405bda579d325050c740ea12bdbdca79d33ad321e6fd4a7ff7ecffe1b84ed146feb4ba9339c4e68a536d7f3ca38f53c6a76f28087cb7f82976"
      ],
      "Hash": "80d66c3c7b8b56c86e5184c299a7063b6aba31222e16bb356dee7b9c34a4bc33"
   },
   "Transactions": [
      {
         "Version": 0,
         "Nonce": 4234080082,
         "GasPrice": 0,
         "GasLimit": 30000,
         "Payer": "AazEvfQPcQ2GEFFPLF1ZLwQ7K5jDn81hve",
         "TxType": 209,
         "Payload": {
            "Code": "0162016152c108526567697374657267a38ab89075dbe8099524c2b652058d9ef31bd630"
         },
         "Attributes": [],
         "Sigs": [
            {
               "PubKeys": [
                  "035384561673e76c7e3003e705e4aa7aee67714c8b68d62dd1fb3221f48c5d3da0"
               ],
               "M": 1,
               "SigData": [
                  "017bc9abb516c1109765a1bc1e41b4418d97b0538b83c06a2bc57072ae3dcfb212263abe8f00d39739e1cd949a0bb533c3d6840e79c04f8d80d3ab51a1fb276b7a"
               ]
            }
         ],
         "Hash": "fb2530764e458ef5b94147a687e85cbcf46ab575e1869730f792e57176d1a99b",
         "Height": 0
      }
   ]
}
```

```shell
$ ontology info block 73537d0363cdc01ae754ed5065001158b5e3400bced437f9fbebf53c96fe7cea
{
   "Hash": "73537d0363cdc01ae754ed5065001158b5e3400bced437f9fbebf53c96fe7cea",
   "Size": 1290,
   "Header": {
      "Version": 0,
      "PrevBlockHash": "80d66c3c7b8b56c86e5184c299a7063b6aba31222e16bb356dee7b9c34a4bc33",
      "TransactionsRoot": "999cdd9e1e6860fcdc3eb6040eff81ed23441f40fadccb076d3c432a7e09a611",
      "BlockRoot": "25dda03bd4a4050e9b95ba0259e8049ec4574aa118a4fc94db23288019e49e1f",
      "Timestamp": 1530590974,
      "Height": 2,
      "ConsensusData": 16494419932887429910,
      "ConsensusPayload": "7b226c6561646572223a342c227672665f76616c7565223a224242576231764b4c755a666953675849543171583164644f577a7265655733354c59324c677230624b4e2f5939612f4274304c7352346f34556441584170504f6d47464a546145747076527769725a466942497a49516f3d222c227672665f70726f6f66223a22734b3853556d37626e4d67535a51775030564c6949656233754b78706e6e2b774f32686b6f30326c6342563273523349326e78675a6b7a5141416b72733062506c74432f524f56674c6d53326c6a757074314a6c43773d3d222c226c6173745f636f6e6669675f626c6f636b5f6e756d223a302c226e65775f636861696e5f636f6e666967223a6e756c6c7d",
      "NextBookkeeper": "AFmseVrdL9f9oyCzZefL9tG6UbvhPbdYzM",
      "Bookkeepers": [
         "030a34dcb075d144df1f65757b85acaf053395bb47b019970607d2d1cdd222525c",
         "037c9e6c6a446b6b296f89b722cbf686b81e0a122444ef05f0f87096777663284b",
         "0205bc592aa9121428c4144fcd669ece1fa73fee440616c75624967f83fb881050",
         "030a34dcb075d144df1f65757b85acaf053395bb47b019970607d2d1cdd222525c",
         "03dff4c63267ae5e23da44ace1bc47d0da1eb8d36fd71181dcccf0e872cb7b31fa",
         "021844159f97d81da71da52f84e8451ee573c83b296ff2446387b292e44fba5c98",
         "03aa4d52b200fd91ca12deff46505c4608a0f66d28d9ae68a342c8a8c1266de0f9"
      ],
      "SigData": [
         "22b28c4a3a1785d8b86d1860600a6f0f37ccd197272080551c833a9d9a5304a7809d56978d7e4a6bb5d8309816736f250f14255c6f310f3c3fef44cd69f17190",
         "40a976369209b5e0ec7868d2547b1e1966426efdb48d875e0e1684a9a0bcc0d0ebd0356956bd49e557ee18ce42cbf74a39289d1ca7856eefe4b40638669bce5e",
         "34c95bb3d582e11419f816757be9e46f6e53ccd3320a703a05c60722575a546df91733acfb223936d184671540759b2e2c4cab6e9b3e6c1551bf52a9153cb44b",
         "739a85184ebbb69c77404ff9da0a401aafece6e96572f85e40b594e476f417dbd07b6d925b4b4c30b14b7a6dd6de972ce168a0a6ca8603341c9748abbbfdd6ad",
         "a009642c5c745919fc9e2dd9072c38b6623bcb2049202472dcb5331cca48727fd6a88770a82e77e6258761076d942408237d0b7acc7143940d273541231ffd58",
         "99e1e2cadde859eeeb1224d743926ae4ccfa76c1db768f6ee74545359dcba11c31ea01cde3f55e00fe44eaacefc62d5fc4145704742a5831cfdd2f20e6cd1160",
         "c7ed6cfb28248610d12e4b0cd9eabd1b5800df161415c4c12edee5664695f15d66d1c8fe0c13b3ee3e3e9ee9296c2b44fd91d4e4b16e670582269e159a815337"
      ],
      "Hash": "73537d0363cdc01ae754ed5065001158b5e3400bced437f9fbebf53c96fe7cea"
   },
   "Transactions": [
      {
         "Version": 0,
         "Nonce": 2903288265,
         "GasPrice": 0,
         "GasLimit": 30000,
         "Payer": "AazEvfQPcQ2GEFFPLF1ZLwQ7K5jDn81hve",
         "TxType": 209,
         "Payload": {
            "Code": "0162016152c108526567697374657267a38ab89075dbe8099524c2b652058d9ef31bd630"
         },
         "Attributes": [],
         "Sigs": [
            {
               "PubKeys": [
                  "035384561673e76c7e3003e705e4aa7aee67714c8b68d62dd1fb3221f48c5d3da0"
               ],
               "M": 1,
               "SigData": [
                  "01e16f0898740398b15d1f5e0b687d3b1c00df56f3e3cae43a1dc38af1a5749e746daf1db736eedfbf36344a4d53ab21167fb0e2e94b1067a139f88b3f32d4e29c"
               ]
            }
         ],
         "Hash": "999cdd9e1e6860fcdc3eb6040eff81ed23441f40fadccb076d3c432a7e09a611",
         "Height": 0
      }
   ]
}
```

## 区块高度

要获取所接入网络的当前区块高度，使用`curblockheight` 命令。

你可以在第一个终端将客户端连接到 `polaris` 测试网。

```shell
ontology --testmode
```

然后在第二个终端中查询 `polaris` 测试网的当前区块高度。

```shell
$ ontology info curblockheight
CurrentBlockHeight:241331
```
