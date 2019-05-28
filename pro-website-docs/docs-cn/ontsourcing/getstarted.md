# **存证服务对接说明**



## 一、接入说明和准备事项



在进行 ONT ID 授权登录接入之前，应用方需要先在 [ONT ID 开放平台]() 申请开通，通过审核后，获得相应的 ```APISecret```，可开始接入流程。
 
> **注意：** 目前开放平台仍旧在测试中，可以发送邮件到openplatform@ont.io 申请开通。



## 二、第三方接入存证API



**根据平台的需求，我们提供以下标准化接入流程，根据场景需求可以支持定制。**



![](/Volumes/Data/_backup/imageForNote/005BYqpgly1g3h12wl8icj30q10d2wgs.jpg)





### 绑定ONT ID 



ONT ID是一个去中心化的身份标识协议，为每个用户，公司，物品等任何实体建立基于密码学的身份标识ID。

 

存证业务发起之前，需要点晴为用户开通ONT ID绑定，之后使用用户ONT ID提交存证。ONT Sourcing 为项目方快速快通ONT ID。

 

获取ONTID之后，点晴可以通知用户已经开通区块链身份账户ONT ID。

 

**请求**

 

url：/api/v1/ontid/create

method：POST

 

```
{
	"user_phone":"86*18612341234"
}
```

 

|   字段名   |  Type  |                    描述                    |
| :--------: | :----: | :----------------------------------------: |
| user_email | String |              暂不支持邮箱注册              |
| user_phone | String | 中国大陆手机号（格式必须为86*18612341234） |

 

**响应**



```
{
    "result":
     {
            "user_ontid": "ont:did:A334fr..",
      },
    "error": 0,
    "action": "createOntid",
    "version": "1.0.0",
    "desc": "SUCCESS"
}
```

 

| **Field_Name** | **Type** | **Description**                 |
| -------------- | -------- | ------------------------------- |
| error          | int      | 错误码                          |
| action         | String   | 动作标志                        |
| desc           | String   | 成功返回ONTID，失败返回错误描述 |
| result         | String   | 成功返回true，失败返回""        |
| version        | String   | 版本号                          |

 

### 存证接口(单笔)

 

**请求**



url：/api/v1/attestation/put

method：POST



```json
{
"access_token":"eyJ0eXAiOiJKV1QiLCJhbGciOiJFUzI1NiJ9.eyJhdWQiOiJkaWQ6b250OkFVRG11NEoyVzF2cUpIRHRMUDhVeEhhdWoyZUtzUUh4dTYiLCJpc3MiOiJkaWQ6b250OkFhdlJRcVhlOVByYVY1dFlnQnF2VjRiVXE4TFNzdmpjV1MiLCJleHAiOjE1NTcyODM2MTAsImlhdCI6MTU1NzE5NzIxMCwianRpIjoiYmQ5NTZhNGI1YzYxNGYxN2I2YTgxNDkyZDI5NDIyYTQiLCJjb250ZW50Ijp7InR5cGUiOiJhY2Nlc3NfdG9rZW4iLCJvbnRpZCI6ImRpZDpvbnQ6QWExWFBhcEpIR0dqSFF0TjJIZHliOUFQdjdIZmlZeHRSeiJ9fQ.MDFiMjFkMjg5OGJmYjZlZGQzMmM5ZjY0ZWIxMDA0OGYxNGNkOGE2MTBhYTZmZGNiZTg4OWQyNzI0MjMwZDVjMjk3Y2Q3ZDhjMzlhOGYzZDJkYjE1YzFhMTcxM2Y3OTU4ZjkzYzRjOGI2NmU2ODM5YmFhNjE4NWRjMTlkZjU3YThkYQ",
	"user_ontid":"",
	"filehash":"111175b25e49f2767522d332057c3e6bb1144c842dce47913dc8222927999999",
	"metadata": {
            "name":"",
            "title": "",
            "tags": "",
            "description":"",
            "timestamp": "",
            "location":""
	},
	"context": {
	    "image": ["",""],
	    "text": ["",""]
	},
	"signature":"",
	"type": "TEXT",
	"async": true
}
```



| 字段名     | Type    | 描述                                                         |
| ---------- | ------- | :----------------------------------------------------------- |
| metadata   | JSON    | 以下是应用发起方对存证数据的定义说明(均为非必输字段)   {        Name:     Title;        Tags;        Description;        Timestamp;          Location;     } |
| user_ontid | String  | ONT ID Login之后，可以获得用户的ONT ID                       |
| context    | JSON    | 可以由应用方自定义存证内容，对于点晴按照以下模板：   {      TEXT数组；      IMAGE数组   } |
| signature  | String  | 用user_ontid对应的私钥对Metadata和context进行HASH和签名。（非必输） |
| async      | boolean | true表示异步，false表示同步，默认为false                     |





**响应：** 

**当 async** **为 true** **时**

```
{
    "result": true,
    "error": 0,
    "action": "putAttestation",
    "desc": "SUCCESS",
    "version": "1.0.0"
}
```



**当 async** **为 false** **时**

```json
{
    "version": "1.0.0",
    "desc": "SUCCESS",
    "result": {
        "txhash": "d6459de184af36ccbc786e19f30ea14961f29b85aa330ea58e07463a73532bac"
    },
    "error": 0,
    "action": "putAttestation"
}
```

 

ONT Sourcing 将txhash返回给第三方，用于标识这笔存证交易。

 

【后续应用处理】

存证完成需要等待区块确认，平台可以通过下面通知接口获取到结果，并提示用户通过访问https://sourcing.ont.io 查询存证结果。

 

### 存证结果通知

存证结果异步通知给项目方，项目方需要在注册时设置Callback回调地址。 

 

**请求：**

 

url：Callback回调地址

method：POST

 

```
{
           "ontid": "did:ont:Aa1XPapJHGGjHQtN2Hdyb9APv7HfiYxtRz",
            "detail": "some message about the file ...",
            "type": "TEXT",
            "timestamp": "2019-04-22T07:32:57.000+0000",
            "timestampSign": "950ef......",
            "filehash": "111175b25e49f2767522d332057c3e6bb1144c842dce47913dc8222927999999",
            "txhash": "ee973d13c6ed2d8c7391223b4fb6f5c785f402d81d41b02ab7590113cbb00752",
            "createTime": "2019-04-22T07:32:57.000+0000",
            "updateTime": null,
            "height": 1621684
}
```

 

 

 

### 存证接口（批量）

 

**请求**



url：/api/v1/attestations/put

method：POST



```json
{
    "access_token": "eyJ0eXAiOiJKV1QiLCJhbGciOiJFUzI1NiJ9.eyJhdWQiOiJkaWQ6b250OkFVRG11NEoyVzF2cUpIRHRMUDhVeEhhdWoyZUtzUUh4dTYiLCJpc3MiOiJkaWQ6b250OkFhdlJRcVhlOVByYVY1dFlnQnF2VjRiVXE4TFNzdmpjV1MiLCJleHAiOjE1NTc4OTM4MzYsImlhdCI6MTU1NzgwNzQzNiwianRpIjoiNjM3YzY4ODQxMzc1NGMxMGE1ZDM3NDY0MTcwMWQwMTIiLCJjb250ZW50Ijp7InR5cGUiOiJhY2Nlc3NfdG9rZW4iLCJvbnRpZCI6ImRpZDpvbnQ6QWExWFBhcEpIR0dqSFF0TjJIZHliOUFQdjdIZmlZeHRSeiJ9fQ.MDE1YmFjYTI0MTI3ODI2YmI0OWI5YzY1YjU4YTg1Njk5NmRkNjlmMTc1MTM3MGIwM2NhOTQ0ZTY4YzI2NzRjMWU2M2U1MTQ2ODZkYTE3ZWU4OGE2N2E4ZTE1MDQ4ODQzNDZiOTYxMGI4MjhjMzhmNGFkMGNiYTY4MDBhZDVjNDZhNw",
    "user_ontid": "",
    "async": true,
    "filelist": [
        {
            "filehash":"111175b25e49f2767522d332057c3e6bb1144c842dce47913dc8222927999999",
            "metadata": {
                    "name":"",
                    "title": "",
                    "tags": "",
                    "description":"",
                    "timestamp": "",
                    "location":""
            },
            "context": {
                "image": ["",""],
                "text": ["",""]
            },
            "signature":"",
            "type": "TEXT"
        },
        {
            "filehash":"111175b25e49f2767522d332057c3e6bb1144c842dce47913dc8222927999999",
            "metadata": {
                     "name":"",
                     "title": "",
                     "tags": "",
                     "description":"",
                     "timestamp": "",
                     "location":""
            },
            "context": {
                "image": ["",""],
                "text": ["",""]
            },
            "signature":"",
            "type": "TEXT"
        }
    ]
}
```





**响应**

**当 async** **为 true** **时**

```
{
    "result": true,
    "error": 0,
    "action": "putAttestations",
    "desc": "SUCCESS",
    "version": "1.0.0"
}
```



**当 async** **为 false** **时**

```json
{
    "result": [
        {
            "txhash": "58eb1b7414d51988899dbaf54ff891aca55eb7ba2f4a5b5008af18a874187d02"
        },
        {
            "txhash": "6cada409428b2d7f4e2186a2a95cd0bdbe82e643ff697b4077129438da0b2e9b"
        }
    ],
    "error": 0,
    "action": "putAttestations",
    "desc": "SUCCESS",
    "version": "1.0.0"
}
```

 

 

### 存证接口（点晴定制）



url：/api/v1/attestations/put/custom

method：POST



**请求**

```json
{
    "access_token": "eyJ0eXAiOiJKV1QiLCJhbGciOiJFUzI1NiJ9.eyJhdWQiOiJkaWQ6b250OkFNdmpVV1o2Y25BQVVzQk43dWpBQnRMUzlHbWVoOFNQU2oiLCJpc3MiOiJkaWQ6b250OkFhdlJRcVhlOVByYVY1dFlnQnF2VjRiVXE4TFNzdmpjV1MiLCJleHAiOjE1NTU5OTMzNjAsImlhdCI6MTU1NTkwNjk2MCwianRpIjoiMTYwY2FkNjNmZTdkNGY5MTk3NGFjZjQzYWNlMzkzNmYiLCJjb250ZW50Ijp7InR5cGUiOiJhY2Nlc3NfdG9rZW4iLCJvbnRpZCI6ImRpZDpvbnQ6QWExWFBhcEpIR0dqSFF0TjJIZHliOUFQdjdIZmlZeHRSeiJ9fQ.MDE5MzE3ODk4ODU2MGQ5NGQ3MTBmZTc2Mzg1ZWE0OWRiMmRjZjczZmU2NjAyYjU0NjI2YWE0MmJmZWYwYTFkYTE0ODI5YWVmYTJjNjNlMTA5N2Y2ZjM0YTJlMTJmOGYwNWNmYzRhZWI3NzlkOWEwMWY2NDY1Y2VjYWM1MzNjYjk5Ng",
    "user_ontid": "did:ont:Aa1XPapJHGGjHQtN2Hdyb9APv7HfiY7890",
    "filelist": [
        {
            "filehash": "e81475b25e49f2767522d332057c3e6bb1144c842dce47913dc8222927777777",
            "type": "INDEX",
            "detail": [
                  {
                      "textLine": [
                          "2d校园",
                          "文本",
                          " 2d校园",
                          "文本",
                          "2d校园",
                          "文本"
                      ],
                      "imageList": [
                          "56e481f7a93a924813440bee96b68f0742b014ed426b7535ad35d072984b2c0f",
                          "56e481f7a93a924813440bee96b68f0742b014ed426b7535ad35d072984b2c0f",
                          "56e481f7a93a924813440bee96b68f0742b014ed426b7535ad35d072984b2c0f"
                      ]
                  }
            ]
        },
        {
            "filehash": "e81475b25e49f2767522d332057c3e6bb1144c842dce47913dc8222927888888",
            "type": "IMAGE",
            "detail": [
                {
                    "imgUrl": "http://...."
                }
            ]
        },
        {
            "filehash": "e81475b25e49f2767522d332057c3e6bb1144c842dce47913dc8222927999999",
            "type": "IMAGE",
            "detail": [
                {
                    "imgUrl": "http://...."
                }
            ]
        },
        {
            "filehash": "e81475b25e49f2767522d332057c3e6bb1144c842dce47913dc8222927000000",
            "type": "IMAGE",
            "detail": [
                {
                    "imgUrl": "http://...."
                }
            ]
        }
    ]
}
```





| **Field_Name** | **Type** | **Description**                |
| -------------- | -------- | ------------------------------ |
| access_token   | String   | access_token                   |
| user_ontid     | String   | 空表示自己存证，否则表示被存证 |
| filelist       | String   | 批量文件(总数不能超过30条)     |
| type           | String   | INDEX/PDF/TEXT/IMAGE/VIDEO     |



**响应**

```json
{
    "result": true,
    "error": 0,
    "action": "putAttestationsCustom",
    "desc": "SUCCESS",
    "version": "1.0.0"
}
```



| Field_Name | Type   | Description                       |
| ---------- | ------ | --------------------------------- |
| error      | int    | 错误码                            |
| action     | String | 动作标志                          |
| desc       | String | 成功返回SUCCESS，失败返回错误描述 |
| result     | String | 成功返回true，失败返回""          |
| version    | String | 版本号                            |

 

 

 

### 取证接口



第三方平台也根据hash通过API主动取证。

 

**请求：**

 

url：/api/v1/contract/hash

method：POST

 

```
{
         "access_token": "eyJ0eXAiOiJKV1QiLCJhbGciOiJFUzI1NiJ9....",
         "hash":"e81475b25e49f2767522d332057c3e6bb1144c842dce47913dc8222927102c67"
}
```

 

| 字段名       | Type   | 描述                                                         |
| ------------ | ------ | ------------------------------------------------------------ |
| access_token | String | ONT ID Login之后，可以获得access_token                       |
| hash         | String | 数据HASH，HASH标准：对文字和图片统一使用BASE64 之后进行HASH256算法，之后得到的字符串 |

 

**响应：**

```json
{
"result": [
       {
            "ontid": "did:ont:Aa1XPapJHGGjHQtN2Hdyb9APv7HfiYxtRz",
            "companyOntid": "did:ont:Aa1XPapJHGGjHQtN2Hdyb9APv7HfiYxtRz",
            "detail": "some message about the file ...",
            "type": "TEXT",
            "timestamp": "2019-04-22T07:32:57.000+0000",
            "timestampSign": "950ef......",
            "filehash": "111175b25e49f2767522d332057c3e6bb1144c842dce47913dc8222927999999",
            "txhash": "ee973d13c6ed2d8c7391223b4fb6f5c785f402d81d41b02ab7590113cbb00752",
            "createTime": "2019-04-22T07:32:57.000+0000",
            "updateTime": null,
            "height": 1621684
        }
    ],
    "error": 0,
    "action": "selectByOntidAndHash",
    "desc": "SUCCESS",
    "version": "1.0.0"
}
```

| **Field_Name** | **Type** | **Description**                   |
| -------------- | -------- | --------------------------------- |
| error          | int      | 错误码                            |
| action         | String   | 动作标志                          |
| desc           | String   | 成功返回SUCCESS，失败返回错误描述 |
| result         | String   | 成功返回true，失败返回""          |
| version        | String   | 版本号                            |



### 错误码



| **返回代码** | **描述信息**          | **备注**   |
| ------------ | --------------------- | ---------- |
| 0            | SUCCESS               | 成功       |
| 61001        | INVALID_PARAMS        | 参数错误   |
| 71001        | ONTID_EXIST           | ontid错误  |
| 71002        | ONTID_NOT_EXIST       | ontid错误  |
| 80001        | BLOCKCHAIN_ERROR      | 本体链错误 |
| 100000       | INTERNAL_SERVER_ERROR |            |

 

 

### 根据交易hash删除存证



url：/api/v1/contract/hash/delete

method：POST

 

- 请求：

```
{
      "access_token": "eyJ0eXAiOiJKV1QiLCJhbGciOiJFUzI1NiJ9.eyJhdWQiOiJkaWQ6b250OkFNdmpVV1o2Y25BQVVzQk43dWpBQnRMUzlHbWVoOFNQU2oiLCJpc3MiOiJkaWQ6b250OkFhdlJRcVhlOVByYVY1dFlnQnF2VjRiVXE4TFNzdmpjV1MiLCJleHAiOjE1NTUwNTU3MzksImlhdCI6MTU1NDk2OTMzOSwianRpIjoiZjQ1ZmMyMmVkMjBhNDFhMGE1YzdhMzZhYjIxZTkxNTAiLCJjb250ZW50Ijp7InR5cGUiOiJhY2Nlc3NfdG9rZW4iLCJvbnRpZCI6ImRpZDpvbnQ6QU14clNHSHl4Z25XUzZxYzFRalROWWVFYXczWDNEdnpoZiJ9fQ.MDFiZDVhYWQ2MzRkNzlkOTU3ZjE3YWYyNDc3MDUyZGUxNzJjYjdmYjgxZWViOThmYTg2ODgyM2ZiYjM5ZjIyMjZiYWZlYTlkNGFkNjMwMzM0OWY4N2YyYzBiZDlmNzg5M2IzYjhiYjdkZTg1MjFmYzQ1MDMwOGY2NGRmM2E5ZjkwNg",
      "hash":"e81475b25e49f2767522d332057c3e6bb1144c842dce47913dc8222927102c67"
}
```

| **Field_Name** | **Type** | **Description** |
| -------------- | -------- | --------------- |
| access_token   | String   | access_token    |
| hash           | String   | 交易hash        |

- 响应：

```
{
    "version": "1.0.0",
    "error": 0,
    "action": "deleteByOntidAndHash",
    "result": true,
    "desc": "SUCCESS"
}
```

 

 

## 三、用户主动查证



点晴的用户可以主动访问https://sourcing.ont.io/#/

 

根据存证编号和ONT ID可以查询到存证列表，并可以公开查询存证证书。



 

## 四、测试和生产环境

 

请先使用仿真环境：

 

sourcing 仿真前台：http://40.73.69.106/#/

sourcing 仿真后台：http://40.73.69.106:7088/

 

sourcing 生产前台：https://sourcing.ont.io

sourcing 生产后台：https://sourcing.ont.io:7088/

 