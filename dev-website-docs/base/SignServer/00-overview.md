

A service to facilitate account management and secure signing of messages to be broadcast to the Ontology blockchain. The signature service can be used as a part of a larger application server or as it's own stand-alone microservice. It is ideal for use in applications that require a automated transaction signing in a secure hosted environment, and provides a wide range of functionality which include:

## Account
- Creation
- Exports for secure backups

## Signing
- Arbitrary data in hex string format
- Raw transactions
- Raw Multiple Signature transactions

## Signing (convenience methods)
- Asset transfers (eg. ONT or ONG)
- Ontology Native Smart Contract invocations
- NEO VM Smart Contract invocations w/ parameterized arguments
- NEO VM Smart Contract invocations w/ unparameterized arguments + abi

__NOTE__: The service is solely responsible for signing of the provided input with the accounts it manages. The broadcast of all signed outputs must be handled by a separate service.
