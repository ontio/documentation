import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;
import com.github.ontio.OntSdk;
import com.github.ontio.account.Account;
import com.github.ontio.common.Helper;
import com.github.ontio.core.transaction.Transaction;
import com.github.ontio.crypto.SignatureScheme;
import com.github.ontio.sdk.wallet.Identity;

import java.util.Base64;

/**
 * @author zhouq
 * @version 1.0
 * @date 2018/11/29
 */
public class Demo {

    public static void main(String[] args) {

        try {
            OntSdk ontSdk = getOntSdk();

            //1:创建数字资产账户 2：创建ONT ID  3：使用ONT ID签名验签  4：构造转账交易
            int flag = 4;

            if (flag == 1) {
                //create asset account
                Account account = createAssetAccount();

                String address = account.getAddressU160().toBase58();
                String prikey = Helper.toHexString(account.serializePrivateKey());
                String pubkey = Helper.toHexString(account.serializePublicKey());
                String wif = account.exportWif();

                System.out.println("wif: " + wif);
                System.out.println("address: " + address);
                System.out.println("privatekey: " + prikey);
                System.out.println("publickey: " + pubkey);


            } else if (flag == 2) {

                String wif = "";
                //import an asset account by wif
                Account account = new Account(Account.getPrivateKeyFromWIF(wif), ontSdk.defaultSignScheme);
                System.out.println("address:" + account.getAddressU160().toBase58());

                //import an asset account by privatekey
/*                String privateKey = "";
                Account account = new Account(Helper.hexToBytes(privateKey), ontSdk.defaultSignScheme);
                String address11 = account.getAddressU160().toBase58();
                String wif = account.exportWif();
                System.out.println("wif:" + wif);
                System.out.println("address:" + address11);*/

                String identityPassword = "ontta1129";
                Identity identity = registerOntId(account, identityPassword);

                String ontid = identity.ontid;
                String salt = identity.controls.get(0).salt;
                String encypPrivateKey = identity.controls.get(0).key;
                String privateKey = Account.getGcmDecodedPrivateKey(identity.controls.get(0).key, identityPassword, identity.ontid.split(":")[2], Base64.getDecoder().decode(identity.controls.get(0).salt), 16384, ontSdk.defaultSignScheme);
                System.out.println("ontid: " + ontid);
                System.out.println("salt: " + salt);
                System.out.println("encypPrivateKey: " + encypPrivateKey);
                System.out.println("privateKey: " + privateKey);

            } else if (flag == 3) {

                //identity encryptedprivatekey
                String encryptedPriKey = "4iHN+pTM6WKgnQC88NNjLcC/dSghc9qBeicwFvsQk5HIn2CAbqENuGm+/bIdndSO";
                //identity password
                String password = "123456";
                //identity salt
                String salt = "C2Nkuw7PjwOSN+9UCa87bA==";
                //identity OntId
                String ontId = "did:ont:AXXxiWCuJXmuPGnsBji4cqWqV1VrKx8nkM";
                //Scrypt-N
                int scryptN = 16384;

                //original data
                JSONArray c = new JSONArray();
                c.add("claim:cfca_authentication");
                c.add("claim:sensetime_authentication");

                JSONObject b = new JSONObject(true);
                b.put("claim_contexts", c);
                b.put("ontid", "did:ont:AXXxiWCuJXmuPGnsBji4cqWqV1VrKx8nkM");
                System.out.println("claim:" + b.toJSONString());

                JSONArray a = new JSONArray();
                a.add(b);

                JSONObject obj = new JSONObject(true);
                obj.put("callback_addr", "https://xxx");
                obj.put("description", "test");
                obj.put("name", "test");
                obj.put("ontid", ontId);
                obj.put("ta_info", a);

                String orignalData = obj.toJSONString();
                System.out.println("original data: " + orignalData);

                //sign
                String signedData = signatureData(ontId, salt, password, encryptedPriKey, scryptN, orignalData);
                System.out.println("The signed data: " + signedData);

                //verify signature
                Boolean verifyRs = verifySignature(ontId, orignalData, signedData);
                System.out.println("verify signature result: " + verifyRs);


            } else if (flag == 4) {

                String wif = "";
                //import an asset account by wif
                Account account = new Account(Account.getPrivateKeyFromWIF(wif), ontSdk.defaultSignScheme);

                String toAddress = "AVMUDu6MWF5hnfpPaDrXfTG356v1pZLoTh";
                int amount = 1;

                Transaction txn = makeTransferTxn(account, toAddress, amount);

                String txnStr = txn.toHexString();
                String txnHash = txn.hash().toHexString();
                System.out.println("transfertxn txnstr:" + txnStr);
                System.out.println("transfertxn txnhash:" + txnHash);

                //send transfer txn to blockchain
                //Boolean rs = ontSdk.getConnect().sendRawTransaction(txnStr);
            }

        } catch (Exception e) {
            e.printStackTrace();
        }

    }


    /**
     * create asset account
     * 创建数字资产账户
     *
     * @return
     * @throws Exception
     */
    public static Account createAssetAccount() throws Exception {

        System.out.println("##########createAssetAccount##########");
        OntSdk ontSdk = getOntSdk();
        Account account = new Account(ontSdk.defaultSignScheme);
        return account;
    }

    /**
     *  make transfer transaction
     * 构造转账交易
     *
     * @param account
     * @param toAddress
     * @param amount
     * @return
     * @throws Exception
     */
    public static Transaction makeTransferTxn(Account account, String toAddress, int amount) throws Exception {

        System.out.println("##############makeTransferTxn############");
        OntSdk ontSdk = getOntSdk();

        //transfer ONG
        Transaction txn = ontSdk.nativevm().ong().makeTransfer(account.getAddressU160().toBase58(), toAddress, amount * 1000000000L, account.getAddressU160().toBase58(), 20000, 500);
        ontSdk.signTx(txn, new Account[][]{{account}});

        //transfer ONT
/*        Transaction txn = ontSdk.nativevm().ont().makeTransfer(account.getAddressU160().toBase58(), toAddress, amount, account.getAddressU160().toBase58(), 20000, 500);
        ontSdk.signTx(txn, new Account[][]{{account}});*/

        return txn;
    }

    /**
     * register ontid
     * 注册ONT ID
     *
     * @param account
     * @param identityPassword
     * @return
     */
    public static Identity registerOntId(Account account, String identityPassword) throws Exception {

        System.out.println("##########registerOntId##########");
        OntSdk ontSdk = getOntSdk();

        Identity identity = ontSdk.getWalletMgr().createIdentity(identityPassword);

        //send register ontid transaction to blockchain.fee:0.01ONG ,paied by account
        String txnhash = ontSdk.nativevm().ontId().sendRegister(identity, identityPassword, account, 20000, 500);
        System.out.println("register ontid txnhash: " + txnhash);

        //write identity into account.json file
        ontSdk.getWalletMgr().writeWallet();

        return identity;
    }

    /**
     * use identity privatekey to sinature data
     * 使用ONT ID私钥对数据进行签名
     *
     * @param ontId
     * @param salt
     * @param password
     * @param origData
     * @return
     * @throws Exception
     */
    public static String signatureData(String ontId, String salt, String password, String encryptedPriKey, int scryptN, String origData) throws Exception {

        System.out.println("#########signatureData##############");
        OntSdk ontSdk = getOntSdk();

        String prikey = com.github.ontio.account.Account.getGcmDecodedPrivateKey(encryptedPriKey, password, ontId.split(":")[2], Base64.getDecoder().decode(salt), scryptN, SignatureScheme.SHA256WITHECDSA);

        com.github.ontio.account.Account account = new com.github.ontio.account.Account(Helper.hexToBytes(prikey), ontSdk.defaultSignScheme);
        String signedData = Base64.getEncoder().encodeToString(ontSdk.signatureData(account, origData.getBytes()));

        return signedData;
    }


    /**
     * verify signature
     * 使用ONT ID公钥对数据验签
     *
     * @param signerOntId 签名者ONT ID
     * @param origData    原始数据
     * @param signedData  签名值
     * @return
     * @throws Exception
     */
    public static Boolean verifySignature(String signerOntId, String origData, String signedData) throws Exception {

        System.out.println("############verifySignature###################");
        OntSdk ontSdk = getOntSdk();

        String issuerDdo = ontSdk.nativevm().ontId().sendGetDDO(signerOntId);
        String pubkeyStr = JSON.parseObject(issuerDdo).getJSONArray("Owners").getJSONObject(0).getString("Value");

        Boolean rs = ontSdk.verifySignature(Helper.hexToBytes(pubkeyStr), origData.getBytes(), Base64.getDecoder().decode(signedData));
        return rs;
    }


    public static OntSdk getOntSdk() throws Exception {

        OntSdk wm = OntSdk.getInstance();
        //测试网 testnet
        wm.setRestful("http://polaris1.ont.io:20334");
        //主网 mainnet
        //wm.setRestful("http://dappnode1.ont.io:20334");
        wm.setDefaultConnect(wm.getRestful());
        wm.openWalletFile("account.json");
        return wm;
    }


}
