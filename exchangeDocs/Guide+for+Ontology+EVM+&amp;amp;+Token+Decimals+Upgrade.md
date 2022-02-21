# Guide for Ontology EVM & Token Decimals Upgrade

# 1. Introduction
   
To provide better support for dApps on Ontology, the network now is EVM compatible. Transaction fees are still paid in ONG. However, now **ONT** has **9** decimals, and **ONG** has **18** decimals.

This guide introduces the upgrade work needed on your end to enjoy these features. 

# 2. List of Changes

## 2.1 Ontology Nodes

The Ontology miannet will be upgraded at the block height of [TBD], please finish the local node upgrade before that.

Ontology release link: [TBD]

## 2.2 Changes to ONT & ONG Deposit Events (required)

The events and logs for ONT / ONG transactions will be different after the upgrade, which affects your event listeners.

### 2.2.1 ONT Transaction Events

Contract address: "0100000000000000000000000000000000000000"

The array held by `States` can have 4 or 5 elements. 

a. When the transaction amount is an integer, the event remains the same.

**Example**

Transfer 1 ONT:

```
{
    "ContractAddress": "0100000000000000000000000000000000000000",
        "States": [
        "transfer",
        "AdeTj6K9UUmz5yfyc8SLX7mJSmCqDKK6yT",
        "AdeTj6K9UUmz5yfyc8SLX7mJSmCqDKK6yT",
        1
    ]
},
```

States[0]: "transfer" (fixed)

States[1]: from address

States[2]: to address

States[3]: amount (integer, no decimal place)

b. When the transaction amount is a decimal number, `States` looks like the below example.

**Example** 

Transfer 1.052999999 ONT:

```
{
    "ContractAddress": "0100000000000000000000000000000000000000",
        "States": [
        "transfer",
        "AdeTj6K9UUmz5yfyc8SLX7mJSmCqDKK6yT",
        "AdeTj6K9UUmz5yfyc8SLX7mJSmCqDKK6yT",
        1,
        52999999
    ]
}
```

States[0]: "transfer" (fixed)

States[1]: from address

States[2]: to address

States[3]: amount (integer representing digits before the decimal point, no decimal place)

States[4]: amount (integer representing digits after the decimal point, 9 digits maximum)

### 2.2.2 ONG Transaction Events

Contract address ”0200000000000000000000000000000000000000“

The array held by `States` can have 4 or 5 elements. 

a. When the number of the transaction amount only have 1 - 9 decimal places, the event remains the same.

**Example**

Transfer 0.000000001 ONG:

```
{
    "ContractAddress": "0200000000000000000000000000000000000000",
    "States": [
        "transfer",
        "AdeTj6K9UUmz5yfyc8SLX7mJSmCqDKK6yT",
        "AdeTj6K9UUmz5yfyc8SLX7mJSmCqDKK6yT",
        1
    ]
}
```
States[0]: "transfer" (fixed)

States[1]: from address

States[2]: to address

States[3]: amount (integer representing digits after the decimal point, 9 digits maximum)

b. When the number of the transaction amount have 10 - 18 decimal places, `States` looks like the below example.

**Example**

Transfer 0.00000000105 ONG:

```
{
"ContractAddress": "0200000000000000000000000000000000000000",
    "States": [
        "transfer",
        "AdeTj6K9UUmz5yfyc8SLX7mJSmCqDKK6yT",
        "AdeTj6K9UUmz5yfyc8SLX7mJSmCqDKK6yT",
        1,
        50000000
    ]
}
```

States[0]: "transfer" (fixed)

States[1]: from address

States[2]: to address

States[3]: amount (integer representing digits on the 1st - 9th decimal places, 9 digits maximum)

States[4]: amount (integer representing digits on the 10th - 18th decimal places, 9 digits maximum)

## 2.3 Withdraw ONT & ONG Using `tranferV2` (optional)

Previously, the `transfer` method is used for ONT and ONG withdrawals, which only takes an integer for the ONT withdrawal amount, or a  decimal with 9 places for the ONG withdrawal amount (the smallest number is 0.000000001). The `tranferV2` method is created to accommodate the decimals upgrade. 

The `transfer` method still functions as before, you can continue using the method and related code if you don't change existing withdrawal rules. If you want to adapt to the decimals upgrade, you need to make below changes:

### 2.3.1 Ontology SDKs

Please use the latest SDKs:

| SDK                                                    | Demo                                                                                                                                                                                                                                                                                                                                            |
| ------------------------------------------------------ | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| [Golang](https://github.com/ontio/ontology-go-sdk)     | [Demo](https://github.com/ontio/ontology-go-sdk/blob/6117f13ebd6b6411b5ee765eeee71b0fb5fc97ec/ont_sdk_v2_test.go)                                                                                                                                                                                                                               |
| [Java](https://github.com/ontio/ontology-java-sdk)     | [Demo 1](https://github.com/ontio/ontology-java-sdk/blob/c8e2da6d3a4b18dd6235b4ed81f47199856bbd59/src/test/java/com/github/ontio/smartcontract/nativevm/OntV2Test.java) [Demo 2](https://github.com/ontio/ontology-java-sdk/blob/c8e2da6d3a4b18dd6235b4ed81f47199856bbd59/src/test/java/com/github/ontio/smartcontract/nativevm/OngV2Test.java) |
| [TypeScript](https://github.com/ontio/ontology-ts-sdk) | [Demo](https://github.com/ontio/ontology-ts-sdk/blob/master/test/integration/v2/transfer.test.ts)                                                                                                                                                                                                                                           |

### 2.3.2 Signature Server
    
There are two ways to sign a transaction:

1. First, invoke the Ontology SDK method `transferV2` to construct a transaction, and get the raw transaction in hex format. Then call the Ontology signature server method `sigrawtx` to sign the transaction, and get the signed transaction in hex format. Last, call the node's `sendrawtx` method to broadcast the transaction.
   
2. Invoke the Ontology signature server method `sigtransfertxV2` to construct a transaction and sign it, and call the node's `sendrawtx` method to broadcast the transaction.


Please read the detailed doc for Ontology Signature Server [here](https://github.com/ontio/documentation/blob/master/exchangeDocs/sigsvr.md).