---
title: 
keywords: sample homepage
sidebar: SDKs_en
permalink: ontology_java_sdk_asset_en.html
folder: doc_en/SDKs
---

English / [中文](./ontology_java_sdk_asset_zh.html)

<h1 align="center"> Digital assets </h1>
<p align="center" class="version">Version 0.9.0 </p>

# Digital assets

## Data structure
`address` base58 encoded account address  
`label` name of account  
`isDefault`indicates whether the account is a default one, whose default value is set as "false"  
`lock` indicates whether the account is locked by client users, who cannot spend in locked account  
`algorithm` name of encryption algorithm  
`parameters` encryption parameters  
`curve` elliptic curve  
`key` NEP-2 private key, whose value can be null (in case of read-only or non-standard address)  
`contract` smart contract, whose value can be null (in case of read-only address)
`encAlg` 私钥加密的算法名称，固定为aes-256-ctr.
`extra` extra information stored by client developer, whose value can be null
`signatureScheme` `signatureScheme` is a signature scheme used for transaction signatures.
`hash` hash algorithm for derived privateKey。
`passwordHash`  password hash
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
        public String encAlg = "aes-256-ctr";
        public String hash = "sha256";
        public String signatureScheme = "SHA256withECDSA";
        public String passwordHash = "";
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
> Note:  
> index: the account with such index number is set as the default account  
> address: the account with such address is set as the default account
----

## Native digital asset(Token)

ont and ong asset list

 1. String sendTransfer(Account sendAcct, String recvAddr, long amount, Account payerAcct, long gaslimit, long gasprice)

    function description： Transfer a certain amount of assets from the sender to the receiver's account

    parameter description：

    sendAcct： sender account

    recvAddr ： receive address

    amount ： asset amount

    payerAcct: Payment transaction account

    gaslimit：gaslimit

    gasprice ： gas price

    return value： transaction hash

 2. String sendApprove(Account sendAcct, String recvAddr, long amount, Account payerAcct, long gaslimit, long gasprice)

       function description： sendAcct account allows recvAddr to transfer amount of assets

       parameter description：

       sendAcct： sender account

       recvAddr： receive address

       amount： asset amount

       payerAcct: Payment transaction account

       gaslimit：gaslimit

       gasprice ： gas price

       return value：transaction hash

 3. String sendTransferFrom(Account sendAcct, String fromAddr, String toAddr, long amount, Account payerAcct, long gaslimit, long gasprice)

        function description： The sendAcct account transfers the amount of assets from the fromAddr account to the toAddr account

        parameter description：

        sendAcct： sender account

        fromAddr： from address

        toAddr： receive address

        amount： asset amount

        payerAcct: Payment transaction account

        gaslimit：gaslimit

        gasprice ： gas price

        return value：transaction hash

 4. long queryBalanceOf(String address)

         function description： Query the assetName asset balance of the account address

         parameter description：

         address：account address

         return value： balance of address

 5. long queryAllowance(String fromAddr,String toAddr)

         function description： query balance of the account address

         fromAddr： from address

         toAddr：to address

         return value： asset amount

 6. String queryName()

          function description： query  asset name information

          parameter description：

          return value：asset name detail information

 7. String querySymbol()

           function description： query  asset symbol Information

           parameter description：

           return value：Symbol information

 8. long queryDecimals()

            function description： query the accuracy of assetName assets

            parameter description：

            return value：decimal

 9. long queryTotalSupply()

             function description： query the total supply of assetName assets

             parameter description：

             return value：total Supply


Example:

```
//step1:get sdk instance
OntSdk sdk = OntSdk.getInstance();
sdk.setRpcConnection(url);
sdk.openWalletFile("OntAssetDemo.json");
//step2:get ontAssetTx instance
ont = sdk.nativevm().ont()
//step3:transfer
com.github.ontio.account.Account account1 = new com.github.ontio.account.Account(privateKey,SignatureScheme.SHA256WITHECDSA);
ont.sendTransfer(account1,"TA4pCAb4zUifHyxSx32dZRjTrnXtxEWKZr",10000,account1,ontSdk.DEFAULT_GAS_LIMIT,0);
```

## nep-5 smart contract digital assets

nep-5 document：
>https://github.com/neo-project/proposals/blob/master/nep-5.mediawiki

digital assets template:
>https://github.com/neo-project/examples/tree/master/ICO_Template


|function|params|return value|description|
|:--|:--|:--|:--|
|sendInit    |boolean preExec|String|If true, it indicates that the pre-execution is to test whether it has been initialized. If it is false, the contract parameters are initialized.|
|sendTransfer|String sendAddr, String password, String recvAddr, int amount|String|transfer assets|
|sendBalanceOf|String addr|String|Get account balance|
|sendTotalSupply||String|Get total supply|
|sendName||String|Get name|
|sendDecimals||String|Get accuracy|
|sendSymbol||String|Query Token abbreviation|


nep-5 smartcontract template：


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


## instruction


* What is codeaddress?


```
codeaddress is the unique identifier of smart contract.
```


* Why do we need to pass the account and its password when invoking?


```
User's signature, which is generated by the private key, is neccesary in the process of invoking a smart contract. And the private key is encrypted and stored in the wallet, which needs the password to decrypt.
```


* What is the pre-execution of smart contract when querying the assert and how to use it?


```
Operations of smart contract, such as get, do not need to go through any consensus node. They read data directly from the storage of smart contract, execute at current node, and return the result.
We can call the pre-execution interface while sending transactions.。
String result = (String) sdk.getConnectMgr().sendRawTransactionPreExec(txHex);
```


* How to view the push results when transferring funds？

See smart contract using websocket connection call contract method，details [smartcontract](./ontology_java_sdk_smartcontract_en.html).