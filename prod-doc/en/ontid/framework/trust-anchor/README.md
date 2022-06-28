# Trust Anchor

Trust anchor refers to the partner that provides authentication services on the Ontology ecosystem. It may be government agencies, universities, banks, third-party authentication service agencies (e.g., CA agencies), biometric technology companies, etc. Trust anchors provides standardized and credible claims for entities for their qualification in certain areas. Trust anchors provides verification service for the claims. The claims will be managed by the entities on their own.

## 1. Major Terms of Service

* Trust Anchor is not allowed to store any user data without related qualifications or user permission.
* Trust Anchor should announce on the official website that it is the provider of Ontology identification and verification service and specify the registered ONT ID.
* Trust Anchor should guarantee the accuracy and authenticity of its user information. The Ontology team is not responsible for the authenticity of the user information submitted by the Trust Anchor. The Ontology team does not take responsibilities for the invalidity of legal documents due to false or incomplete user information. The relevant responsibility should be taken by the Trust Anchor itself to its users or third parties.
* Trust Anchor should have the capability of identification and authentication management. The principle requirements are as follows. The target requirements can be specified by Party A according to the specific service requirements.
* Have the hardware and the network facilities for identification and authentication;
* Have safety protection standards;
* Deploy the software of identification and authentication management provided by Ontology open source standard code;
* Based on the management process of identification and authentication, the Trust Anchor should provide at least the following services of verifiable claim: 
  1. the issuance of a verifiable claim; 
  2. the revocation of a verifiable claim; 3. Providing open services of verifiable claim in official domain URL.

## 2. Become a `claim provider`

[>>> The verifiable claim specification](../spec/claim.md)

- Use [RESTful api](./restful-api.md) to provide claims for your end users.
- Create a [new trust anchor](./deployment.md) to provide claims for your end users.
  - Use [`Ontology general trust anchor`](./saas-tenant.md) (SaaS) to provide your own credentials for your customers

