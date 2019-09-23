# ONT ID signing server - deployment

## 1. Prerequisite

// Docker

## 2. Configuration

Sample configuration file in json,

```json
{
	"domain": "on.ont",
	"enableONS": true,
	"defaultPayer": "AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV",
	"actions": [{
			"type": "register",
			"onchainRec": false
		},
		{
			"type": "login",
			"onchainRec": false
		},
		{
			"type": "cus_action1",
			"onchainRec": true,
			"payer": "AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV",
			"qrcodeUrl": "",
			"callback": ""
		}
	]
}
```

| Field Name | Type | Description |
| ---------- | ---- | ----------- |
| domain | String | Registered domain in ONS |
| enableONS | boolean | Enable sub-domain for end user |
| defaultPayer | String | The payer of transaction gas fee from customer(s), if leave `blank`, the customer will pay the gas fee on their own |
| actions | Object array | Support action(s) for this domain. For detail, see the table below. |

Actions object.

| Field Name | Type    | Description                                                  |
| ---------- | ------- | ------------------------------------------------------------ |
| type       | String  | Action name of the service                                   |
| onchainRec | boolean | Whether to record the action behavior on chain               |
| payer      | Address | The gas fee payer of the action calling. <br/>If this field is `omit`, default payer will pay the gas fee; <br/>if this field is set to `blank`, the customer(s) will pay the gas fee on their own. |

### 2.1 Enable ONS

若启用ONS，则用户需要注册与自己ontid绑定的子域名，并在登录时使用子域名登录

### 2.2 Set default payer

设置default payer，需要在启动服务时，将payer对应的私钥在命令行输入，用于后续对交易的payer签名

### 2.3 Config action(s)

配置指定签名action的payer及是否上链

### 2.4 Add customized action 

自定义需要signing server签名的action

## 3. Create an Instance

## 4. Start a New Server

