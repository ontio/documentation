# Claim store - deployment

## 1. Prerequisite



## 2. Configuration

Sample configuration file in json,

```json
{
  "ontId": "did:ont:AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV",
	"domain": "sampleclaimstore.ont",
	"enableONS": true,
	"defaultPayer": "AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV",
  "storeContract": "8e88e1bdfa720b0b79fd3784de248f4d8890decd",
	"plugins": [{
		"name": "chargeFeeSplit",
    "id": "e1471264-b2d1-45fa-9eb5-1a8ad6ce2b6c",
    "settings": {}
	}]
}
```

| Field Name   | Type         | Description                                                  |
| ------------ | ------------ | ------------------------------------------------------------ |
| ontId       | String       | ONT ID of the host                  |
| domain       | String       | Registered domain in ONS                                     |
| enableONS    | boolean      | Enable sub-domain for end user                               |
| defaultPayer | String       | The payer of transaction gas fee from customer(s), if leave `blank`, the customer will pay the gas fee on their own |
| storeContract | String | On-chain contract hash of claim store |
| plugins | Object array | Support action(s) for this domain. For detail, see the table below. |

Plugins object.

| Field Name | Type    | Description                                                  |
| ---------- | ------- | ------------------------------------------------------------ |
| name       | String  | Plugin name of the service in claim store                    |
| id         | String  | Unique ID of the plugin                                      |
| settings   | Object  | Setting detail for each plugin                               |

### 2.1 Enable ONS



### 2.2 Set default payer



### 2.3 Config plugin(s)



### 2.4 Add customized plugin



## 4. Start a new `claim store`



## Appendix I. Plugin list

