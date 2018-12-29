# 一 普通接口
### 1.开始日常统计接口：
    API：/api/v1/explorer/summaryAllInfo
    类型：POST
    参数：{}
    说明：开始日常统计，应用场景为重新统计、补充统计
    实现逻辑：依据type类型分别分页查询各个类型的所有合约信息
    结果展示：
    {
        "Action": "SummaryAllInfo",
        "Error": 0,
        "Desc": "SUCCESS",
        "Version": "1.0",
        "Result": null
    }

### 2.首页统计数据查询接口：
    API：/api/v1/explorer/summary/{amout}
    类型：GET
    说明：amout为查询最新区块、交易、ontId的数量
    实现逻辑：查询浏览器首页数据，包括峰值TPS、实时交易总数、 实时节点数、创始到前一天的地址总数、最新的amout个区块、 实时OntId总数、最新的amout个ontId、实时（前一分钟的平均值）TPS、实时区块高度、最新的amout笔交易
    结果展示：
    {
            "MaxTps": 10000,
            "TxnCount": 1436360,
            "NodeCount": 31,
            "AddressCount": 168452,
            "BlockList": [
                {
                    "PrevBlock": "70e2b4bd0f76baed2ebfe3b0ca1bbbd6fc6c587253b090338ea97765937b2752",
                    "TxnsRoot": "b1210f5ead19bd1df54fe836c3ed3da0aa21814187ed84476e5ee8f8c7119048",
                    "BlockTime": 1546064464,
                    "NextBlock": "",
                    "BookKeeper": "AXq1j9X5ndnwqXwSdKUPmXtqYcNqqziD35&AMvXn7U9S3Pq7hah16Euu7wX52UHtHyqNr&ALNdxK654mTcMzex9nsfnBXLEfiryhpNUB&AXq1j9X5ndnwqXwSdKUPmXtqYcNqqziD35&AWio34nsRGxaMtsuAwaKftuh2qMD1NqXaV",
                    "TxnNum": 1,
                    "Height": 1462662,
                    "Hash": "112a6025209180a2fb30d3646f1da8c0333bc0c87e0e38b8e336c148e089ce57",
                    "ConsensusData": "8922899334318662371",
                    "BlockSize": 1135
                }
            ],
            "OntIdCount": 138812,
            "OntIdList": [
                {
                    "TxnTime": 1546064188,
                    "TxnType": 209,
                    "Description": "register OntId",
                    "Fee": "0.010000000",
                    "TxnHash": "83b2148bbfd603bf6bf8eb52cec6d6b21856c260d3fccfac3b72f0681e037cd6",
                    "Height": 1462589,
                    "OntId": "did:ont:AHFEqsW6Z3AsqT6xtY6fVzxJzDdKgTZ7hH"
                }
            ],
            "CurrentTps": "0.20",
            "CurrentHeight": 1462662,
            "TxnList": [
                {
                    "TxnTime": 1546064464,
                    "TxnType": 209,
                    "ConfirmFlag": 1,
                    "Fee": "0.018590500",
                    "TxnHash": "b1210f5ead19bd1df54fe836c3ed3da0aa21814187ed84476e5ee8f8c7119048",
                    "Height": 1462662,
                    "BlockIndex": 1
                }
            ]
    }


### 3.TPS查询接口：
    API：/api/v1/explorer/summary/tps
    类型：GET
    说明：查询实时和峰值tps，实时tps统计规则：计算前一分钟内的平均TPS
    实现逻辑：查询浏览器首页数据，包括峰值TPS、实时TPS
    结果展示：
    {
            "MaxTps": 10000,
            "CurrentTps": "0.25"
    }


### 4.日常统计查询接口:
    API：/api/v1/explorer/summary/{type}/{starttime}/{endtime}
    类型：GET
    说明：type：每天、每周、每月
             starttime：某日00:00:00对应的时间戳，比如创始区块的当天时间： 2018-06-30 00：00：00 时间戳：1530288000
              endtime：某日00:00:00对应的时间戳
    实现逻辑：查询每日(包括地址增长统计、ontId增长统计)、每周、每月统计，包括统计记录的数量、统计的内容（每天（周、月）交易数量、活跃地址数、ontId增长（只有每天统计）、区块数量、ong交易额、ontId活跃数量、地址增长（只有每天统计）、ontId新增数量、增长地址数、ont交易额、每天（周、月）的时间）
    结果展示：
    {
            "Total": 14,
            "SummaryList": [
                ........,
                {
                    "TxnCount": 30631,
                    "ActiveAddress": 7239,
                    "OntIdSum": 138777,
                    "BlockCount": 23184,
                    "OngCount": "1652069.566708669",
                    "OntIdActiveCount": 133,
                    "AddressSum": 168452,
                    "OntIdNewCount": 133,
                    "NewAddress": 3796,
                    "OntCount": "21647209.000000000",
                    "Time": "2018-12-28"
                }
    }


### 5.合约统计查询接口:
    API：/api/v1/explorer/summary/contract/{contracthash}/{type}/{starttime}/{endtime}
    类型：GET
    说明：contracthash：合约hash
              type：每天、每周、每月
              starttime：某日00:00:00对应的时间戳，比如创始区块的当天时间： 2018-06-30 00：00：00 时间戳：1530288000
              endtime：某日00:00:00对应的时间戳
    实现逻辑：查询每日、每周、每月合约统计，包括ont总交易额、ong总交易额、总地址数、统计记录的数量、统计的内容（当天（周、月）交易数、活跃地址数、ong交易额、新增地址数、ont交易额、统计的时间）、总交易量
    结果展示：
    {
            "OntCountSum": "0.000000000",
            "OngCountSum": "14279.320109238",
            "AddressSum": 3699,
            "Total": 14,
            "SummaryList": [
                ......,
                {
                    "TxnCount": 6781,
                    "ActiveAddress": 281,
                    "OngCount": "1757.099128929",
                    "NewAddress": 180,
                    "OntCount": "0.000000000",
                    "Time": "2018-12-28"
                }
            ],
            "TxCountSum": 17574
    }


### 6.项目统计查询接口:
    API：/api/v1/explorer/summary/project/{project}/{type}/{starttime}/{endtime}
    类型：GET
    说明：project：projectName，为项目注册时的ontId后的地址
              type：每天、每周、每月
              starttime：某日00:00:00对应的时间戳，比如创始区块的当天时间： 2018-06-30 00：00：00 时间戳：1530288000
              endtime：某日00:00:00对应的时间戳
    实现逻辑：查询每日、每周、每月项目统计，包括ont总交易额、ong总交易额、项目的合约列表，总地址数、统计记录的数量、统计的内容（当天（周、月）交易数、活跃地址数、ong交易额、新增地址数、ont交易额、统计的时间）、总交易量
    结果展示：
    {
            "OntCountSum": "0.000000000",
            "OngCountSum": "35207.605447574",
            "ContractsList": [
                "4cfbe5d9e6b6d2e58f63b2883b26b540e0119c71",
                "5df56bb569bc88273000a2d2ca0e9c7ec83f1c23",
                "c11cc1adf9b2e7f2a9eedd6552b213a292fb10f9",
                "2c002727c7ce87d3842dd29a19224cdaaf7dbda4",
                "4e4a9b860fb7ffba41f91ea112712191bd7eca53"
            ],
            "AddressSum": 3738,
            "Total": 14,
            "SummaryList": [
                ......，
                {
                    "TxnCount": 6940,
                    "ActiveAddress": 329,
                    "OngCount": "6808.127538250",
                    "NewAddress": 206,
                    "OntCount": "0.000000000",
                    "Time": "2018-12-28"
                }
            ],
            "TxCountSum": 17809
    }


### 7.注册合约：
    API：/api/v1/explorer/contract/registerContractInfo
    类型：POST
    参数：
    非oep8：
    {
        "code": "6a55c36a54c3936a00527ac462c8ff6161616a53c36c7566",
        "abi": " {\"contractHash\": \"2a9cc8a5d0644283e7d7705abe5bbcb979c9bb03\"}",
        "name": "HyperDragons",
        "project": "HyperDragons",
        "contractHash": "3d9dee93447a024de49925ec64b39178c4ae4525",
        "type": "OEP5",
        "contactinfo": {
            "Website": "https://github.com/ontio"
        },
        "description": "contractsDescriptionTest",
        "logo": "https://luckynumber.one/index/img/logo.png"
    }

    oep8：
    {
        "code": "6a55c36a54c3936a00527ac462c8ff6161616a53c36c7566",
        "abi": " {\"contractHash\": \"db80b875208f1f87b53c80a06a3288a1b2a0ea76\"}",
        "name": "oep8Test",
        "project": "oep8Project",
        "contractHash": "db80b875208f1f87b53c80a06a3288a1b2a0ea77",
        "type": "OEP8",
        "contactinfo": {
            "Website": "https://github.com/ontio"
        },
        "description": "contractsDescriptionTest",
        "logo": "https://luckynumber.one/index/img/logo.png",
        "tokenId": "01,02,03,04,05"
    }
    说明：依据传入参数信息与contracts表中合约hash对应的记录进行数据更新，类型为oep时，还会生成对应的oep合约记录存储在对应的oep表中
    实现逻辑：依据传入数据的contracthash和数据库中的合约hash匹配，进行数据更新；当数据类型为oep时，会在对应的oep表中生成对应的token合约记录；当数据类型为oep8时，token合约不进行重新录入
    结果展示：
    {
        "Action": "SummaryAllInfo",
        "Error": 0,
        "Desc": "SUCCESS",
        "Version": "1.0",
        "Result": true
    }


# 二 合约接口
### 1.合约列表接口
    API：/api/v1/explorer/contract/{pagesize}/{pagenumber}
    类型：GET
    实现逻辑：分页查询contracts表中所有经过人工审核的所有合约，包括合约描述、合约每十分钟统计的总地址数、生成时间、合约ABI、创建者、合约CODE、合约Hash、合约名称、合约logo、合约类型（oep4、oep5、oep8等）、合约的资产交易额（一般只有token合约才有内容）、合约ong交易额、最新更新时间、合约联系信息、合约ont交易额、合约每十分钟统计的总交易数（TxCount）
    结果展示：
    {
            "ContractList": [
                {
                    "Description": "LuckyMoon is running on the Ontology public chain......",
                    "AddressCount": 535,
                    "CreateTime": 1545711228,
                    "ABI": "{\"contractHash\":\"fceb516248246d19a76a7afaaec3a9e7c9c7a847\".....}",
                    "Creator": "AHtwAHYGD6cxpd8bMKSnC9RtMQptdXewB3",
                    "Code": "028f00c56b6a00527ac46a51527ac46a00c304696e6......",
                    "ContractHash": "fceb516248246d19a76a7afaaec3a9e7c9c7a847",
                    "Name": "LuckyMoon",
                    "Logo": "https://app.ont.io/socialmedia/pic/LuckyMoon_logo.png",
                    "Type": "",
                    "tokencount": "[]",
                    "OngCount": "116974.860000000",
                    "UpdateTime": 1545711228,
                    "ContactInfo": "{\"Official Website\":\"https://luckymoon.io/\"}",
                    "OntCount": "0.000000000",
                    "TxCount": 36864
                }
            ],
            "Total": 9
    }


### 2.合约详情接口
    API：/api/v1/explorer/contract/{contracthash}/{pagesize}/{pagenumber}
    类型：GET
    说明：contracthash为合约hash；
    实现逻辑：依据合约hash查询合约的详情，分页查询合约的交易，包括合约描述、合约每十分钟统计的总地址数、生成时间、合约的资产交易额（一般只有token合约才有内容）、合约ABI、合约交易列表、创建者、合约CODE、合约名称、合约logo、合约每十分钟统计的总交易数（TxSum）、合约ong交易额、合约实时总交易数（Total）、最新更新时间、合约联系信息、合约ont交易额、
    结果展示：
    {
            "Description": "LuckyMoon is running on the Ontology public chain.......",
            "AddressCount": 535,
            "CreateTime": 1545711228,
            "TokenCount": "[]",
            "ABI": "{\"contractHash\":\"fceb516248246d19a76a7afaaec3a9e7c9c7a847\"}.........",
            "TxnList": [
                {
                    "TxnTime": 1546060521,
                    "TxnType": 209,
                    "ConfirmFlag": 1,
                    "Fee": "0.010658000",
                    "TxnHash": "6ff46c128acc88e5a88fc562a954a2ed0cfbdac662eb06da1d597200e787d9a8",
                    "Height": 1461545
                }
            ],
            "Creator": "AHtwAHYGD6cxpd8bMKSnC9RtMQptdXewB3",
            "Code": "028f00c56b6a00527ac46a51527ac46a00c304696e69749c640900......",
            "Name": "LuckyMoon",
            "Logo": "https://app.ont.io/socialmedia/pic/LuckyMoon_logo.png",
            "TxSum": 36864,
            "OngCount": "116974.860000000",
            "Total": 36928,
            "UpdateTime": 1545711228,
            "ContactInfo": "{\"Official Website\":\"https://luckymoon.io/\"}",
            "OntCount": "0.000000000"
    }


# 三 token接口
### 1.token合约列表接口
    API：/api/v1/explorer/oepcontract/{type}/{pagesize}/{pagenumber}
    类型：GET
    说明：type为oep4、oep5、oep8
    实现逻辑：依据type类型分别分页查询各个类型的所有合约信息，包括合约描述、token标识、生成时间、合约ABI、创建者、总供应量、合约CODE、合约Hash、合约名称、合约logo、合约ong交易额、最新更新时间、合约每十分钟统计的总地址数、合约联系信息、合约ont交易额、合约每十分钟统计的总交易数（TxCount）
    结果展示：
    {
            "ContractList": [
                {
                    "Description": "The renowned Idle RPG game is starting an amazing blockchain game journey with you",
                    "Symbol": "HD",
                    "CreateTime": 1545657514,
                    "ABI": "{\"contractHash\":\"4cfbe5d9e6b6d2e58f63b2883b26b540e0119c71\".........}",
                    "Creator": "AHmTbeWmLMANAvMzokbYGGmmStW6etBijG",
                    "TotalSupply": 465,
                    "Code": "02fa00c56b6a00527ac46a51527ac46a00c304696e69749c6409006559456c7566........",
                    "ContractHash": "4cfbe5d9e6b6d2e58f63b2883b26b540e0119c71",
                    "Name": "HyperDragons Go!",
                    "Logo": "https://app.ont.io/socialmedia/pic/hyd_go_logo_300.png",
                    "OngCount": "13997.696322586",
                    "UpdateTime": 1545657514,
                    "Addresscount": 3696,
                    "ContactInfo": "{\"Official Website\":\"https://hyd-go.alfakingdom.com/\"}",
                    "OntCount": "0.000000000",
                    "TxCount": 16883
                }
            ],
            "Total": 1
    }


### 2.token合约详情接口
    API：/api/v1/explorer/oepcontract/{type}/{contracthash}/{pagesize}/{pagenumber}
    类型：GET
    说明：type为oep4、oep5、oep8；
              contracthash为合约hash
    实现逻辑：依据type类型分别查询某合约的详细信息，分页查询合约的交易，包括合约描述、合约每十分钟统计的总地址数、token标识、生成时间、token合约的资产交易额、合约ABI、合约交易列表、创建者、总供应量、合约CODE、合约名称、合约logo、合约每十分钟统计的总交易数（TxSum）、合约ong交易额、合约实时交易数（Total）、最新更新时间、合约联系信息、合约ont交易额（oep8另外还有：token名称、tokenId）
    结果展示：
    oep5(HyperDragons):
    {
            "Description": "The renowned Idle RPG game is starting an amazing blockchain game journey with you",
            "AddressCount": 3695,
            "Symbol": "HD",
            "CreateTime": 1545657514,
            "TokenCount": "[{\"Amount\":1143.000000000,\"Assetname\":\"HyperDragons\"}]",
            "ABI": "{\"contractHash\":\"4cfbe5d9e6b6d2e58f63b2883b26b540e0119c71\".......}",
            "TxnList": [
                {
                    "TxnTime": 1546061057,
                    "TxnType": 209,
                    "ConfirmFlag": 1,
                    "Fee": "0.010000000",
                    "Assetname": "",
                    "TxnHash": "fd0661adc0f64d16f82ad6b8e3c8326a3007f449ced2acbb452d6efb91d858e7",
                    "Height": 1461693,
                    "Contracthash": "4cfbe5d9e6b6d2e58f63b2883b26b540e0119c71"
                }
            ],
            "Creator": "AHmTbeWmLMANAvMzokbYGGmmStW6etBijG",
            "TotalSupply": 465,
            "Code": "02fa00c56b6a00527ac46a51527ac46a00c304696e69749c6409006559456c7566........",
            "Name": "HyperDragons Go!",
            "Logo": "https://app.ont.io/socialmedia/pic/hyd_go_logo_300.png",
            "TxSum": 16932,
            "OngCount": "13997.696322586",
            "Total": 17245,
            "UpdateTime": 1545657514,
            "ContactInfo": "{\"Official Website\":\"https://hyd-go.alfakingdom.com/\"}",
            "OntCount": "0.000000000"
    }

    oep8(pumkin):
    {
            "Description": "The Collect Pumpkin smart contract is a sample of OEP-8 smart contract. OEP-8 smart contract allows you to transfer different amount of tokens for different crypto items from one address to another address or do batch transfer. It combines the advantages of fungible OEP-4 tokens and non-fungible OEP-5 tokens, satisfying the intense requirement from many different scenarios, especially blockchain games.",
            "AddressCount": 1642,
            "Symbol": {
                "01": "pumpkin01",
                "02": "pumpkin02",
                "03": "pumpkin03",
                "04": "pumpkin04",
                "05": "pumpkin05",
                "06": "pumpkin06",
                "07": "pumpkin07",
                "08": "pumpkin08"
            },
            "CreateTime": 1540542656,
            "TokenCount": "[{\"Amount\":211916.000000000,\"Assetname\":\"pumpkin01\"},{\"Amount\":53120.000000000,\"Assetname\":\"pumpkin02\"},{\"Amount\":211575.000000000,\"Assetname\":\"pumpkin03\"},{\"Amount\":210946.000000000,\"Assetname\":\"pumpkin04\"},{\"Amount\":210526.000000000,\"Assetname\":\"pumpkin05\"},{\"Amount\":210205.000000000,\"Assetname\":\"pumpkin06\"},{\"Amount\":211593.000000000,\"Assetname\":\"pumpkin07\"},{\"Amount\":4531.000000000,\"Assetname\":\"pumpkin08\"}]",
            "ABI": "{\"contractHash\":\"edf64937ca304ea8180fa92e2de36dc0a33cc712\"......}",
            "TxnList": [
                {
                    "TxnTime": 1546061661,
                    "TxnType": 209,
                    "ConfirmFlag": 1,
                    "Fee": "0.010000000",
                    "TxnHash": "95bacf218b59017c583bf9a64c92685c67ddd54601a888effc294dc863e530e4",
                    "Height": 1461865
                }
            ],
            "Creator": "AHDP1jtfMA1vMpy3Gy41vMfyVWQym4eTwu",
            "TotalSupply": {
                "01": "200000",
                "02": "200000",
                "03": "200000",
                "04": "200000",
                "05": "200000",
                "06": "200000",
                "07": "200000",
                "08": "50000"
            },
            "Code": "015ac56b6a00527ac46a51527ac46a00c3046e616d659c6424006a51c3c0519e640700006c7566616a.......",
            "Name": "CollectPumpkin",
            "Logo": "https://app.ont.io/socialmedia/pic/pumpkin.png",
            "TxSum": 7989,
            "OngCount": "0.000000000",
            "Total": 7989,
            "UpdateTime": 1540542656,
            "ContactInfo": "",
            "OntCount": "0.000000000",
            "TokenName": {
                "01": "pumpkin01",
                "02": "pumpkin02",
                "03": "pumpkin03",
                "04": "pumpkin04",
                "05": "pumpkin05",
                "06": "pumpkin06",
                "07": "pumpkin07",
                "08": "pumpkin08"
            },
            "TokenId": {
                "01": "01",
                "02": "02",
                "03": "03",
                "04": "04",
                "05": "05",
                "06": "06",
                "07": "07",
                "08": "08"
            }
    }


### 3.指定数字资产名称的token合约详情接口（主要针对oep8合约，存在多个数字资产）
    API：/api/v1/explorer/oepcontract/{type}/{contracthash}/{tokenname}/{pagesize}/{pagenumber}
    类型：GET
    说明：type为oep8；
              contracthash为合约hash；
              tokenname为资产名称，比如pumkin01
    实现逻辑：依据type类型分别查询某合约的详细信息，分页查询合约的交易，包括合约描述、合约每十分钟统计的总地址数、token标识、生成时间、token合约的资产交易额、合约ABI、合约交易列表、创建者、总供应量、合约CODE、合约名称、合约logo、合约每十分钟统计的总交易数（TxSum）、合约ong交易额、合约实时交易数（Total）、最新更新时间、合约联系信息、合约ont交易额
    结果展示：
    {
            "Description": "The Collect Pumpkin smart contract is a sample of OEP-8 smart contract. OEP-8 smart contract allows you to transfer different amount of tokens for different crypto items from one address to another address or do batch transfer. It combines the advantages of fungible OEP-4 tokens and non-fungible OEP-5 tokens, satisfying the intense requirement from many different scenarios, especially blockchain games.",
            "AddressCount": 1642,
            "Symbol": "pumpkin01",
            "CreateTime": 1540542656,
            "TokenCount": "[{\"Amount\":211916.000000000,\"Assetname\":\"pumpkin01\"},{\"Amount\":53120.000000000,\"Assetname\":\"pumpkin02\"},{\"Amount\":211575.000000000,\"Assetname\":\"pumpkin03\"},{\"Amount\":210946.000000000,\"Assetname\":\"pumpkin04\"},{\"Amount\":210526.000000000,\"Assetname\":\"pumpkin05\"},{\"Amount\":210205.000000000,\"Assetname\":\"pumpkin06\"},{\"Amount\":211593.000000000,\"Assetname\":\"pumpkin07\"},{\"Amount\":4531.000000000,\"Assetname\":\"pumpkin08\"}]",
            "ABI": "{\"contractHash\":\"edf64937ca304ea8180fa92e2de36dc0a33cc712\".......}",
            "TxnList": [
                {
                    "TxnTime": 1546027563,
                    "TxnType": 209,
                    "ConfirmFlag": 1,
                    "Fee": "0.010000000",
                    "TxnHash": "7572f31a4b057b575f1eab783bf86dc5c50b45a04175fbe27a40bf3ad1ea04f3",
                    "Height": 1455200
                }
            ],
            "Creator": "AHDP1jtfMA1vMpy3Gy41vMfyVWQym4eTwu",
            "TotalSupply": "200000",
            "Code": "015ac56b6a00527ac46a51527ac46a00c3046e616d659c6424.......",
            "Name": "CollectPumpkin",
            "Logo": "https://app.ont.io/socialmedia/pic/pumpkin.png",
            "TxSum": 7989,
            "OngCount": "0.000000000",
            "Total": 4912,
            "UpdateTime": 1540542656,
            "ContactInfo": "",
            "OntCount": "0.000000000",
            "TokenName": "pumpkin01",
            "TokenId": "01"
    }


# 四 基础接口
### 1.首页查询接口：
    API：/api/v1/explorer/summary
    类型：GET
    说明：查询首页数据
    实现逻辑：查询统计数据，包括交易总数、节点数、地址总数、ontId总数、当前区块高度
    结果展示：
    {
            "TxnCount": 1438212,
            "NodeCount": 31,
            "AddressCount": 168452,
            "OntIdCount": 138813,
            "CurrentHeight": 1464017
    }


### 2.负载均衡存活探测（可不关注）：
    API：/api/v1/explorer/detection
    类型：GET
    说明：负载均衡存活探测
    实现逻辑：
    结果展示：
        success


### 3.市场信息查询接口：
    API：/api/v1/explorer/marketing/info
    类型：GET
    说明：查询市场信息
    实现逻辑：
    结果展示：
    {
            "CurrentHeight": 1464443,
            "CurrentSupply": "59.75%"
    }


### 4.最新区块查询接口：
    API：/api/v1/explorer/blocklist/{amount}
    类型：GET
    说明：amount为查询区块的数量
    实现逻辑：在block表中查询最新的amount个区块信息
    结果展示：
    [
            {
                "PrevBlock": "a9f5320cec1d7ed194b5ee2b77554c3509ca9b6905183e4566e304688ac975c8",
                "TxnsRoot": "0ab30bc7d93de6ee5f0ed139baa2a19dee54416396df4a2ca87c72c2edf04c6f",
                "BlockTime": 1546071736,
                "NextBlock": "",
                "BookKeeper": "AMvXn7U9S3Pq7hah16Euu7wX52UHtHyqNr&AMvXn7U9S3Pq7hah16Euu7wX52UHtHyqNr&AWio34nsRGxaMtsuAwaKftuh2qMD1NqXaV&AL4CDqBikrj92pC3B747ZchYZAQf2fg1AC&AXq1j9X5ndnwqXwSdKUPmXtqYcNqqziD35",
                "TxnNum": 1,
                "Height": 1464474,
                "Hash": "9ff68aaaad4a37b35a69b87b671e435600038b52038acf0028f160e25947b3a9",
                "ConsensusData": "18098304490959637753",
                "BlockSize": 1118
            }，
            .......
    ]


### 5.区块分页查询接口：
    API：/api/v1/explorer/blocklist/{pagesize}/{pagenumber}
    类型：GET
    说明：按照区块高度倒序，分页查询区块
    实现逻辑：在block表，按照区块高度倒序，分页查询区块信息
    结果展示：
    {
            "BlockList": [
                {
                    "PrevBlock": "40b1f3044d23d7a7196814a982dd2b71cb8794ec925f1c5dcc35ed0d468cb527",
                    "TxnsRoot": "d3554c0f8a24049962f6fe0ebaabef513110ffe0cce5bca11a931c768bd756f9",
                    "BlockTime": 1546072002,
                    "NextBlock": "",
                    "BookKeeper": "AMvXn7U9S3Pq7hah16Euu7wX52UHtHyqNr&AL4CDqBikrj92pC3B747ZchYZAQf2fg1AC&AXq1j9X5ndnwqXwSdKUPmXtqYcNqqziD35&AMvXn7U9S3Pq7hah16Euu7wX52UHtHyqNr&ALeYCHTLVnM4G5iiHc1MGdvMQf8Wd5Tvu2",
                    "TxnNum": 1,
                    "Height": 1464541,
                    "Hash": "1a9371ad97674d40d5336f3ca5d1c225c048bd523bd800260d5e3987bbd1d0a6",
                    "ConsensusData": "13725366541490070219",
                    "BlockSize": 1121
                }
            ],
            "Total": 1464541
    }


### 6.区块查询接口：
    API：/api/v1/explorer/block/{param}
    类型：GET
    说明：param为区块hash或者区块高度
    实现逻辑：在block表，按照区块hash或者区块高度，查询区块信息
    结果展示：
    {
            "PrevBlock": "40b1f3044d23d7a7196814a982dd2b71cb8794ec925f1c5dcc35ed0d468cb527",
            "TxnsRoot": "d3554c0f8a24049962f6fe0ebaabef513110ffe0cce5bca11a931c768bd756f9",
            "BlockTime": 1546072002,
            "NextBlock": "921f8aea8e289a75df39fc0f8ea1847365d7c2d8d0574931c081ea18d0467381",
            "BookKeeper": "AMvXn7U9S3Pq7hah16Euu7wX52UHtHyqNr&AMvXn7U9S3Pq7hah16Euu7wX52UHtHyqNr&AL4CDqBikrj92pC3B747ZchYZAQf2fg1AC&ALeYCHTLVnM4G5iiHc1MGdvMQf8Wd5Tvu2&AXq1j9X5ndnwqXwSdKUPmXtqYcNqqziD35",
            "TxnNum": 1,
            "Height": 1464541,
            "TxnList": [
                {
                    "TxnTime": 1546072002,
                    "ConfirmFlag": 1,
                    "TxnHash": "d3554c0f8a24049962f6fe0ebaabef513110ffe0cce5bca11a931c768bd756f9",
                    "Height": 1464541
                }
            ],
            "Hash": "1a9371ad97674d40d5336f3ca5d1c225c048bd523bd800260d5e3987bbd1d0a6",
            "ConsensusData": "13725366541490070219",
            "BlockSize": 1121
    }


### 7.区块生成时间查询接口：
    API：/api/v1/explorer/generatetime/{amount}
    类型：GET
    说明：amount为查询区块生成时间的结果数量
    实现逻辑：在block表，按照区块高度倒序，查询amount个区块，分别统计每个区块的生成时间
    结果展示：
    [
            {
                "Height": 1464632,
                "GenerateTime": 1
            },
            {
                "Height": 1464631,
                "GenerateTime": 1
            }
    ]


### 8.两周内每天生成区块数查询接口：
    API：/api/v1/explorer/block/blockCountInTwoWeeks/{time}
    类型：GET
    说明：time为查询两周内每天生成区块数的截止时间
    实现逻辑：在block表，按照当前时间，统计最近2周内每天生成的区块数
    结果展示：
    [
            {
                "count": 2470,
                "day": 1546041600
            },
            {
                "count": 7623,
                "day": 1545955200
            },
            ......
    ]


### 9.分页查询ontId接口：
    API：/api/v1/explorer/ontidlist/{pagesize}/{pagenumber}
    类型：GET
    说明：按照区块高度倒序，分页查询ontId
    实现逻辑：在ontid_detail表，按照区块高度倒序，分页查询ontid的详情
    结果展示：
    {
            "OntIdList": [
                {
                    "TxnTime": 1546073571,
                    "TxnType": 209,
                    "Description": "register OntId",
                    "Fee": "0.010000000",
                    "TxnHash": "dd2cb286b64a6d5d5abfee14b8a695f4ff63b900c93552aac98a9765fe835248",
                    "Height": 1464931,
                    "OntId": "did:ont:AXj5qg84ptbCvnb4HBoaRbRsTNXGxC31t7"
                }
            ],
            "Total": 138819
     }


### 10.查询某ontId详情接口：
    API：/api/v1/explorer/ontid/{ontid}/{pagesize}/{pagenumber}
    类型：GET
    说明：ontid为指定ontId的内容
    实现逻辑：在ontid_detail表，依据指定的ontId，按照区块高度倒序，分页查询ontid的详情，包括ddo
    结果展示：
    {
            "TxnList": [
                {
                    "TxnTime": 1546073571,
                    "TxnType": 209,
                    "Description": "register OntId",
                    "Fee": "0.010000000",
                    "TxnHash": "dd2cb286b64a6d5d5abfee14b8a695f4ff63b900c93552aac98a9765fe835248",
                    "Height": 1464931,
                    "OntId": "did:ont:AXj5qg84ptbCvnb4HBoaRbRsTNXGxC31t7"
                }
            ],
            "TxnTotal": 1,
            "Ddo": {
                "Attributes": [],
                "OntId": "did:ont:AXj5qg84ptbCvnb4HBoaRbRsTNXGxC31t7",
                "Owners": [
                    {
                        "Type": "ECDSA",
                        "Curve": "P256",
                        "Value": "0339e286b95c75ad972ceb157cfd0ea3ce881fd09ecae073bb602ed27c246cd83b",
                        "PubKeyId": "did:ont:AXj5qg84ptbCvnb4HBoaRbRsTNXGxC31t7#keys-1"
                    }
                ]
            }
    }



### 11.最新交易查询接口：
    API：/api/v1/explorer/transactionlist/{amount}
    类型：GET
    说明：amount为按照区块高度倒序，查询最新的amount个交易详情
    实现逻辑：在txn_detail表，按照区块高度倒序，查询最新的amount个交易详情
    结果展示：
    {
            "TxnList": [
                {
                    "TxnTime": 1546074743,
                    "TxnType": 209,
                    "ConfirmFlag": 1,
                    "Fee": "0.010000000",
                    "TxnHash": "4a95a07953ceb8e2553d1491410ca30e3c5171171c30d72242a2742738768ca1",
                    "Height": 1465237,
                    "BlockIndex": 1
                }
            ]
     }


### 12.分页查询交易接口：
    API：/api/v1/explorer/transactionlist/{pagesize}/{pagenumber}
    类型：GET
    说明：按照区块高度倒序，查询交易详情
    实现逻辑：在txn_detail表，按照区块高度倒序，查询交易详情
    结果展示：
    {
            "Total": 1439598,
            "TxnList": [
                {
                    "TxnTime": 1546074869,
                    "TxnType": 209,
                    "ConfirmFlag": 1,
                    "Fee": "0.010000000",
                    "TxnHash": "9f48e78d36772942ccb74867c10ec5cefd6f5bc1ac28c7f20b53ac7ec214df02",
                    "Height": 1465267,
                    "BlockIndex": 2
                }
            ]
     }


### 13.依据交易hash查询交易接口：
    API：/api/v1/explorer/transaction/{txnhash}
    类型：GET
    说明：txnhash为交易hash
    实现逻辑：在txn_detail表，依据交易hash，查询交易详情
    结果展示：
    {
            "TxnTime": 1546074869,
            "TxnType": 209,
            "Description": "",
            "ConfirmFlag": 1,
            "Fee": "0.010000000",
            "TxnHash": "9f48e78d36772942ccb74867c10ec5cefd6f5bc1ac28c7f20b53ac7ec214df02",
            "Height": 1465267,
            "BlockIndex": 2
    }


### 14.分页查询某地址的交易接口：
    API：/api/v1/explorer/address/{address}/{pagesize}/{pagenumber}
    类型：GET
    说明：address为用户地址
    实现逻辑：在txn_detail表，依据用户地址，分页查询详情，并查询账户余额
    结果展示：
    {
            "AssetBalance": [
                {
                    "Balance": "2711.032209635",
                    "AssetName": "ong"
                },
                {
                    "Balance": "2.83305975",
                    "AssetName": "waitboundong"
                },
                {
                    "Balance": "30.25796524",
                    "AssetName": "unboundong"
                },
                {
                    "Balance": "83",
                    "AssetName": "ont"
                },
                {
                    "AssertType": "OEP8",
                    "Balance": "1",
                    "AssetName": "pumpkin08"
                },
                {
                    "AssertType": "OEP8",
                    "Balance": "10",
                    "AssetName": "pumpkin07"
                },
                {
                    "AssertType": "OEP8",
                    "Balance": "7",
                    "AssetName": "pumpkin06"
                },
                {
                    "AssertType": "OEP8",
                    "Balance": "8",
                    "AssetName": "pumpkin05"
                },
                {
                    "AssertType": "OEP8",
                    "Balance": "8",
                    "AssetName": "pumpkin04"
                },
                {
                    "AssertType": "OEP8",
                    "Balance": "9",
                    "AssetName": "pumpkin03"
                },
                {
                    "AssertType": "OEP8",
                    "Balance": "0",
                    "AssetName": "pumpkin02"
                },
                {
                    "AssertType": "OEP8",
                    "Balance": "7",
                    "AssetName": "pumpkin01"
                },
                {
                    "Balance": "50",
                    "AssetName": "totalpumpkin"
                },
                {
                    "AssertType": "OEP5",
                    "Balance": "1",
                    "AssetName": "HyperDragons"
                }
            ],
            "TxnList": [
                {
                    "TxnType": 209,
                    "ConfirmFlag": 1,
                    "Fee": "0.010000000",
                    "BlockIndex": 1,
                    "TransferList": [
                        {
                            "FromAddress": "AXH5dEfnLcxFmgP5bHsjj9TuSrNSYWzz1M",
                            "Amount": "0.010000000",
                            "ToAddress": "AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK",
                            "AssetName": "ong"
                        }
                    ],
                    "TxnTime": 1546075300,
                    "TxnHash": "3d942ef38d9802475246ac7159b41d8c2601da90a2541d8f5b0382fadd844e08",
                    "Height": 1465385
                }
            ]
    }



### 15.分页查询某地址的某种数字资产的交易接口：
    API：/api/v1/explorer/address/{address}/{assetname}/{pagesize}/{pagenumber}
    类型：GET
    说明：address为用户地址
              assetname为数字资产名称
    实现逻辑：在txn_detail表，依据用户地址和数字资产，分页查询详情，并查询账户余额
    结果展示：
    {
            "AssetBalance": [
                {
                    "Balance": "2711.032209635",
                    "AssetName": "ong"
                },
                {
                    "Balance": "2.833123245",
                    "AssetName": "waitboundong"
                },
                {
                    "Balance": "30.25796524",
                    "AssetName": "unboundong"
                },
                {
                    "Balance": "83",
                    "AssetName": "ont"
                },
                {
                    "AssertType": "OEP8",
                    "Balance": "1",
                    "AssetName": "pumpkin08"
                },
                {
                    "AssertType": "OEP8",
                    "Balance": "10",
                    "AssetName": "pumpkin07"
                },
                {
                    "AssertType": "OEP8",
                    "Balance": "7",
                    "AssetName": "pumpkin06"
                },
                {
                    "AssertType": "OEP8",
                    "Balance": "8",
                    "AssetName": "pumpkin05"
                },
                {
                    "AssertType": "OEP8",
                    "Balance": "8",
                    "AssetName": "pumpkin04"
                },
                {
                    "AssertType": "OEP8",
                    "Balance": "9",
                    "AssetName": "pumpkin03"
                },
                {
                    "AssertType": "OEP8",
                    "Balance": "0",
                    "AssetName": "pumpkin02"
                },
                {
                    "AssertType": "OEP8",
                    "Balance": "7",
                    "AssetName": "pumpkin01"
                },
                {
                    "Balance": "50",
                    "AssetName": "totalpumpkin"
                },
                {
                    "AssertType": "OEP5",
                    "Balance": "1",
                    "AssetName": "HyperDragons"
                }
            ],
            "TxnList": [
                {
                    "TxnType": 209,
                    "ConfirmFlag": 1,
                    "Fee": "0.035605500",
                    "BlockIndex": 1,
                    "TransferList": [
                        {
                            "FromAddress": "AXH5dEfnLcxFmgP5bHsjj9TuSrNSYWzz1M",
                            "Amount": "1.000000000",
                            "ToAddress": "00",
                            "AssetName": "pumpkin01"
                        }
                    ],
                    "TxnTime": 1544178750,
                    "TxnHash": "d037b9a589c977fd5a7628462a6a48243135e1f790a73d31d03c97baf045c484",
                    "Height": 1158011
                }
            ]
    }


### 16.查询某地址的某种数字资产截止时间之前的交易接口：
    API：/api/v1/explorer/address/timeandpage/{address}/{assetname}/{pagesize}/{endtime}
    类型：GET
    说明：address为用户地址
              assetname为数字资产名称
              pagesize为交易的数量
              endtime为截止时间
    实现逻辑：在txn_detail表，依据用户地址和数字资产、截止时间，查询交易的详情，并查询账户余额
    结果展示：
    {
            "AssetBalance": [
                {
                    "AssertType": "OEP8",
                    "Balance": "7",
                    "AssetName": "pumpkin01"
                },
                {
                    "Balance": "50",
                    "AssetName": "totalpumpkin"
                },
                {
                    "AssertType": "OEP5",
                    "Balance": "1",
                    "AssetName": "HyperDragons"
                }
            ],
            "TxnList": [
                {
                    "TxnType": 209,
                    "ConfirmFlag": 1,
                    "Fee": "0.028136500",
                    "BlockIndex": 3,
                    "TransferList": [
                        {
                            "FromAddress": "AHDP1jtfMA1vMpy3Gy41vMfyVWQym4eTwu",
                            "Amount": "1.000000000",
                            "ToAddress": "AXH5dEfnLcxFmgP5bHsjj9TuSrNSYWzz1M",
                            "AssetName": "pumpkin01"
                        }
                    ],
                    "TxnTime": 1540815001,
                    "TxnHash": "f9adcf2c7067111b30c6658314d2d164da49b32aa70b1bab66eb67710f40dc53",
                    "Height": 797379
                }
            ]
    }



### 17.按时间段查询某地址的某种数字资产的交易接口：
    API：/api/v1/explorer/address/time/{address}/{assetname}/{begintime}/{endtime}
    类型：GET
    说明：address为用户地址
              assetname为数字资产名称
              begintime为开始时间
              endtime为截止时间
    实现逻辑：在txn_detail表，依据用户地址和数字资产、时间段，查询交易的详情，并查询账户余额
    结果展示：
    {
            "AssetBalance": [
                {
                    "AssertType": "OEP8",
                    "Balance": "7",
                    "AssetName": "pumpkin01"
                },
                {
                    "Balance": "50",
                    "AssetName": "totalpumpkin"
                },
                {
                    "AssertType": "OEP5",
                    "Balance": "1",
                    "AssetName": "HyperDragons"
                }
            ],
            "TxnList": [
                {
                    "TxnType": 209,
                    "ConfirmFlag": 1,
                    "Fee": "0.035605500",
                    "BlockIndex": 1,
                    "TransferList": [
                        {
                            "FromAddress": "AXH5dEfnLcxFmgP5bHsjj9TuSrNSYWzz1M",
                            "Amount": "1.000000000",
                            "ToAddress": "00",
                            "AssetName": "pumpkin01"
                        }
                    ],
                    "TxnTime": 1544178750,
                    "TxnHash": "d037b9a589c977fd5a7628462a6a48243135e1f790a73d31d03c97baf045c484",
                    "Height": 1158011
                }
            ]
    }


### 18.按开始时间查询某地址的某种数字资产的交易接口：
    API：/api/v1/explorer/address/time/{address}/{assetname}/{begintime}
    类型：GET
    说明：address为用户地址
              assetname为数字资产名称
              begintime为开始时间
    实现逻辑：在txn_detail表，依据用户地址和数字资产、开始时间，查询交易的详情，并查询账户余额
    结果展示：
    {
            "AssetBalance": [
                {
                    "AssertType": "OEP8",
                    "Balance": "7",
                    "AssetName": "pumpkin01"
                },
                {
                    "Balance": "50",
                    "AssetName": "totalpumpkin"
                },
                {
                    "AssertType": "OEP5",
                    "Balance": "1",
                    "AssetName": "HyperDragons"
                }
            ],
            "TxnList": [
                {
                    "TxnType": 209,
                    "ConfirmFlag": 1,
                    "Fee": "0.035605500",
                    "BlockIndex": 1,
                    "TransferList": [
                        {
                            "FromAddress": "AXH5dEfnLcxFmgP5bHsjj9TuSrNSYWzz1M",
                            "Amount": "1.000000000",
                            "ToAddress": "00",
                            "AssetName": "pumpkin01"
                        }
                    ],
                    "TxnTime": 1544178750,
                    "TxnHash": "d037b9a589c977fd5a7628462a6a48243135e1f790a73d31d03c97baf045c484",
                    "Height": 1158011
                }
            ]
    }


### 19.查询某地址的数字资产接口：
    API：/api/v1/explorer/address/balance/{address}
    类型：GET
    说明：address为用户地址
    实现逻辑：在txn_detail表，依据用户地址，查询账户余额(除了ont、ong、南瓜资产，其他数字资产如果没有，则不显示)
    结果展示：
    [
            {
                "Balance": "2711.032209635",
                "AssetName": "ong"
            },
            {
                "Balance": "2.83349716",
                "AssetName": "waitboundong"
            },
            {
                "Balance": "30.25796524",
                "AssetName": "unboundong"
            },
            {
                "Balance": "83",
                "AssetName": "ont"
            },
            {
                "AssertType": "OEP8",
                "Balance": "1",
                "AssetName": "pumpkin08"
            },
            {
                "AssertType": "OEP8",
                "Balance": "10",
                "AssetName": "pumpkin07"
            },
            {
                "AssertType": "OEP8",
                "Balance": "7",
                "AssetName": "pumpkin06"
            },
            {
                "AssertType": "OEP8",
                "Balance": "8",
                "AssetName": "pumpkin05"
            },
            {
                "AssertType": "OEP8",
                "Balance": "8",
                "AssetName": "pumpkin04"
            },
            {
                "AssertType": "OEP8",
                "Balance": "9",
                "AssetName": "pumpkin03"
            },
            {
                "AssertType": "OEP8",
                "Balance": "0",
                "AssetName": "pumpkin02"
            },
            {
                "AssertType": "OEP8",
                "Balance": "7",
                "AssetName": "pumpkin01"
            },
            {
                "Balance": "50",
                "AssetName": "totalpumpkin"
            },
            {
                "AssertType": "OEP5",
                "Balance": "1",
                "AssetName": "HyperDragons"
            }
    ]


### 20.查询某地址的所有交易接口：
    API：/api/v1/explorer/address/queryaddressinfo/{address}
    类型：GET
    说明：address为用户地址
    实现逻辑：在txn_detail表，依据用户地址，查询所有交易详情
    结果展示：
    {
            "TxnList": [
                {
                    "TxnTime": "2018-12-27 12:00:02",
                    "FromAddress": "00",
                    "ConfirmFlag": 1,
                    "Fee": "0.013902500",
                    "Amount": "1.000000000",
                    "TxnHash": "fba067d40e86b03d2c43239b86a38e19fb969fe2aef990fe5b9f5be6f3af0b97",
                    "AssetName": "HyperDragons: 73",
                    "ToAddress": "AXH5dEfnLcxFmgP5bHsjj9TuSrNSYWzz1M"
                },
                .........
    }














