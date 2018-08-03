---
title:
keywords: sample homepage
sidebar: SDKs_en
permalink: ontology_java_sdk_asset_en.html
folder: doc_en/SDKs
giturl: https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/asset.md
---

<h1 align="center"> Digital Assets </h1>

<p align="center" class="version">Version 1.0.0 </p>

English / [中文](./ontology_java_sdk_asset_zh.html)

## Data structure
`address`   Base58 encoded account address.  
`label` Name of account.  
`isDefault`Indicates whether the account is a default one, whose default value is set as "false".  
`lock`  Indicates whether the account is locked by client users, who cannot spend in locked account.  
`algorithm` Name of encryption algorithm.  
`parameters` Encryption parameters.  
`curve` Elliptic curve.  
`key` NEP-2 private key, whose value can be null (in case of read-only or non-standard address).  
`contract` Smart contract, whose value can be null (in case of read-only address).  
`encAlg` Private key encryption algorithm name, fixed at aes-256-ctr.  
`salt` Private key decryption parameters.  
`extra` Extra information stored by client developer, whose value can be null.  
`signatureScheme` `signatureScheme` Signature scheme used for transaction signatures.  
`hash` Hash algorithm for derived privateKey.

```
public class Account {
    public String label = "";
    public String address = "";
    public boolean isDefault = false;
    public boolean lock = false;
    public String algorithm = "";
    public Map parameters = new HashMap() ;
    public String key = "";
    @JSONField(name = "enc-alg")
    public String encAlg = "aes-256-gcm";
    public String salt = "";
    public String hash = "sha256";
    public String signatureScheme = "SHA256withECDSA";
    public Object extra = null;
}

```

## Digital asset account management

* Create digital asset account

```
OntSdk ontSdk = OntSdk.getInstance();
Account acct = ontSdk.getWalletMgr().createAccount("password");
//any account or identity, once created, are stored in the memory only. A write api should be invoked when writing to a wallet file.
ontSdk.getWalletMgr().writeWallet();
```

* Remove digital asset account

```
ontSdk.getWalletMgr().getWallet().removeAccount(address);
//write to wallet
ontSdk.getWalletMgr().writeWallet();
```

* Set default digital asset account

```
ontSdk.getWalletMgr().getWallet().setDefaultAccount(index);
ontSdk.getWalletMgr().getWallet().setDefaultAccount("address");
```
Note:  
> index: The account with such index number is set as the default account.  
> address: The account with such address is set as the default account.
----

## Native digital asset (token)

ONT and ONG asset list

 1. String sendTransfer (Account sendAcct, String recvAddr, long amount, Account payerAcct, long gaslimit, long gasprice)

    Function description: Transfer a certain amount of assets from the sender to the receiver's account.

    Parameter description：

    sendAcct: Sender account

    recvAddr: Receiver address

    amount: Asset amount

    payerAcct: Payment transaction account

    gaslimit: Gas limit

    gasprice: Gas price

    return value: Transaction hash

 2. String sendApprove (Account sendAcct, String recvAddr, long amount, Account payerAcct, long gaslimit, long gasprice)

       Function description: SendAcct account allows recvAddr to transfer amount of assets.

       Parameter description：

       sendAcct: Sender account

       recvAddr: Receive address

       amount: Asset amount

       payerAcct: Payment transaction account

       gaslimit: Gas limit

       gasprice: Gas price

       return value: Transaction hash

 3. String sendTransferFrom (Account sendAcct, String fromAddr, String toAddr, long amount, Account payerAcct, long gaslimit, long gasprice)

        Function description: The sendAcct account transfers the amount of assets from the fromAddr account to the toAddr account.

        Parameter description：

        sendAcct: Sender account

        fromAddr: From address

        toAddr: Receive address

        amount: Asset amount

        payerAcct: Payment transaction account

        gaslimit: Gas limit

        gasprice: Gas price

        return value: Transaction hash

 4. long queryBalanceOf (String address)

         Function description: Query the asset balance of the account address.

         Parameter description：

         address：Account address

         return value： Balance of address

 5. long queryAllowance (String fromAddr,String toAddr)

         Function description: Query balance of the account address.

         fromAddr: From address

         toAddr: To address

         return value: Asset amount

 6. String queryName()

          Function description: Query  asset name information.

          Parameter description：

          return value: Asset name detail information

 7. String querySymbol()

           Function description: Query  asset symbol Information.

           Parameter description：

           return value：Symbol information

 8. long queryDecimals()

            Function description: Query the accuracy of assets

            Parameter description：

            return value：decimal

 9. long queryTotalSupply()

             Function description： Query the total supply of  assets

             Parameter description：

             return value：total Supply


Example:

```
//step1:get sdk instance
OntSdk sdk = OntSdk.getInstance();
sdk.setRpc(url);
sdk.openWalletFile("OntAssetDemo.json");
//step2:get ontAssetTx instance
ont = sdk.nativevm().ont()
//step3:transfer
com.github.ontio.account.Account account1 = new com.github.ontio.account.Account(privateKey,SignatureScheme.SHA256WITHECDSA);
ont.sendTransfer(account1,"TA4pCAb4zUifHyxSx32dZRjTrnXtxEWKZr",10000,account1,ontSdk.DEFAULT_GAS_LIMIT,0);
```

## NEP-5 smart contract digital assets

NEP-5 document：
>https://github.com/neo-project/proposals/blob/master/nep-5.mediawiki

Digital assets template:
>https://github.com/neo-project/examples/tree/master/ICO_Template


|Function|Params|Return value|Description|
|:--|:--|:--|:--|
|sendInit    |boolean preExec|String|If true, it indicates that the pre-execution is to test whether it has been initialized. If it is false, the contract parameters are initialized.|
|sendTransfer|String sendAddr, String password, String recvAddr, int amount|String|Transfer assets|
|sendBalanceOf|String addr|String|Get account balance|
|sendTotalSupply||String|Get total supply|
|sendName||String|Get name|
|sendDecimals||String|Get accuracy|
|sendSymbol||String|Query token abbreviation|


NEP-5 smartc ontract template:


```
using Neo.SmartContract.Framework;
using Neo.SmartContract.Framework.Services.Neo;
using Neo.SmartContract.Framework.Services.System;
using System;
using System.ComponentModel;
using System.Numerics;

namespace Nep5Template
{
    public class Nep5Template : SmartContract
    {
        //Token Settings
        public static string Name() => "Nep5Template Token";
        public static string Symbol() => "TMP";
        public static readonly byte[] community = "AXK2KtCfcJnSMyRzSwTuwTKgNrtx5aXfFX".ToScriptHash();
        public static byte Decimals() => 8;
        private const ulong factor = 100000000; //decided by Decimals()

        //ICO Settings
        private const ulong totalAmount = 1000000000 * factor;
        private const ulong communityCap = 1000000000 * factor;

        [DisplayName("transfer")]
        public static event Action<byte[], byte[], BigInteger> Transferred;

        public static Object Main(string operation, params object[] args)
        {
            if (Runtime.Trigger == TriggerType.Application)
            {
                if (operation == "init") return Init();
                if (operation == "totalSupply") return TotalSupply();
                if (operation == "name") return Name();
                if (operation == "symbol") return Symbol();
                if (operation == "transfer")
                {
                    if (args.Length != 3) return false;
                    byte[] from = (byte[])args[0];
                    byte[] to = (byte[])args[1];
                    BigInteger value = (BigInteger)args[2];
                    return Transfer(from, to, value);
                }
                if (operation == "balanceOf")
                {
                    if (args.Length != 1) return 0;
                    byte[] account = (byte[])args[0];
                    return BalanceOf(account);
                }
                if (operation == "decimals") return Decimals();
            }
            return false;
        }

        // init
        public static bool Init()
        {
            byte[] total_supply = Storage.Get(Storage.CurrentContext, "totalSupply");
            if (total_supply.Length != 0) return false;

            Storage.Put(Storage.CurrentContext, community, communityCap);
            Transferred(null, community, communityCap);

            Storage.Put(Storage.CurrentContext, "totalSupply", totalAmount);
            return true;
        }

        // get the total token supply
        // Get the total number of issued tokens
        public static BigInteger TotalSupply()
        {
            Runtime.CheckSig(new byte[1]{ 1 },  new byte[]{2},new byte[]{ 3});
            return Storage.Get(Storage.CurrentContext, "totalSupply").AsBigInteger();
        }

        // function that is always called when someone wants to transfer tokens.
        // transfer token
        public static bool Transfer(byte[] from, byte[] to, BigInteger value)
        {
            if (value <= 0) return false;
            if (!Runtime.CheckWitness(from)) return false;
            if (from == to) return true;
            BigInteger from_value = Storage.Get(Storage.CurrentContext, from).AsBigInteger();
            if (from_value < value) return false;
            if (from_value == value)
                Storage.Delete(Storage.CurrentContext, from);
            else
                Storage.Put(Storage.CurrentContext, from, from_value - value);
            BigInteger to_value = Storage.Get(Storage.CurrentContext, to).AsBigInteger();
            Storage.Put(Storage.CurrentContext, to, to_value + value);
            Transferred(from, to, value);
            return true;
        }

        // get the account balance of another account with address
        // Get the token's balance based on the address
        public static BigInteger BalanceOf(byte[] address)
        {
            return Storage.Get(Storage.CurrentContext, address).AsBigInteger();
        }
    }
}
```


## Instruction


* What is codeaddress?

codeaddress is the unique identifier of smart contract.

* Why do we need to pass the account and its password when invoking?

User's signature, which is generated by the private key, is neccesary in the process of invoking a smart contract. The private key is encrypted and stored in the wallet, which needs the password to decrypt.

* What is the pre-execution of smart contract when querying the assert and how to use it?

Operations of smart contract, such as get, do not need to go through any consensus node. They read data directly from the storage of smart contract, execute at current node, and return the result.
We can call the pre-execution interface while sending transactions.
String result = (String) sdk.getConnectMgr().sendRawTransactionPreExec(txHex);

* How to view the push results when transferring funds？

See smart contract using WebSocket connection call contract method, more details: [smartcontract](./ontology_java_sdk_smartcontract_en.html).
