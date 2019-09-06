# ONT ID signing server - deployment

## 1. Prerequisite



## 2. Configuration

Sample configuration file in json,

```json
{
	"domain": "on.ont",
	"enableONS": true,
	"defaultPayer": "AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV",
	"actions": [{
			"type": "register",
			"onchainRec": true,
			"payer": "AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK"
		},
		{
			"type": "login",
			"onchainRec": false
		},
		{
			"type": "cus_action1",
			"onchainRec": true,
			"payer": ""
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



### 2.2 Set default payer



### 2.3 Config action(s)



### 2.4 Add customized action 



## 3. Create an Instance

## 4. Start a New Server

