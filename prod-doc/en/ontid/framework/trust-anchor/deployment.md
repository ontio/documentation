# ONT ID Trust Anchor - deployment

## 1. Prerequisite

### Become a new `trust anchor`

- **Register ONT ID**

  You need to register your ONT ID first. We recommend you to register it through the official SDK.

  [ont-java-sdk](https://github.com/ontio/ontology-java-sdk) - SDK to create a digital identity.

- **Integrated Features of Verifiable Claim Management**

  To achieve the issuance and management of the standard verifiable claim. To support the functions including issuing, revoking, verifying, querying, and publishing the templates of verifiable claim.

  We provide components to quickly integrate these features.

- **Customized Development**

  Step 1: Combine the existing identification methods, customize the A1 interface, and open it to the client;

  Step 2: Use SDK to implement the A2 interface for verifying user identity of ONT ID;

  [ont-java-sdk](https://github.com/ontio/ontology-java-sdk) - SDK to validate user signature.

  Step 3: Set templates of verifiable claim based on your business demand；

  Step 4: Use the A3 interface through the CWC. As shown in above figure, the A3 interface will help the Trust Anchor to issue and send it to the trusted storage and blockchain.

  > Note：Please use official domain name URL to open the API of verifying verifiable claim to the public.



## 2. Configuration

Sample configuration file in json,

```json
{
  "ontId": "did:ont:AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV",
	"domain": "sampletrustanchor.ont",
	"enableONS": true,
	"defaultPayer": "AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV",
}
```

| Field Name | Type | Description |
| ---------- | ---- | ----------- |
| ontId       | String       | ONT ID of the host                  |
| domain | String | Registered domain in ONS |
| enableONS | boolean | Enable sub-domain for end user |
| defaultPayer | String | The payer of transaction gas fee from customer(s), if leave `blank`, the customer will pay the gas fee on their own |

### 2.1 Enable ONS



### 2.2 Set default payer



### 2.3 Config action(s)



### 2.4 Add customized action 

