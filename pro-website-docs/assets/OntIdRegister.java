import com.github.ontio.OntSdk;
import com.github.ontio.account.Account;
import com.github.ontio.common.Helper;
import com.github.ontio.sdk.wallet.Identity;

import java.util.Base64;

/**
 * @author zhouq
 * @version 1.0
 * @date 2018/11/29
 */
public class OntIdRegister {

    public static void main(String[] args) {

        try {
            OntSdk ontSdk = getOntSdk();

            String wif = "";
            //import an asset account by wif
            Account account = new Account(Account.getPrivateKeyFromWIF(wif), ontSdk.defaultSignScheme);
            System.out.println("address:" + account.getAddressU160().toBase58());


            //import an asset account by privatekey
/*            String privateKey = "";
            Account account = new Account(Helper.hexToBytes(privateKey), ontSdk.defaultSignScheme);
            String address11 = account.getAddressU160().toBase58();
            String wif = account.exportWif();
            System.out.println("wif:" + wif);
            System.out.println("address:" + address11);*/


            String identityPassword = "password";
            Identity identity = registerOntId(account, identityPassword);

            String ontid = identity.ontid;
            String salt = identity.controls.get(0).salt;
            String encypPrivateKey = identity.controls.get(0).key;
            String privateKey = Account.getGcmDecodedPrivateKey(identity.controls.get(0).key, identityPassword, identity.ontid.split(":")[2], Base64.getDecoder().decode(identity.controls.get(0).salt), 16384, ontSdk.defaultSignScheme);
            System.out.println("privateKey: " + privateKey);
            System.out.println("ontid: " + ontid);
            System.out.println("salt: " + salt);
            System.out.println("encypPrivateKey: " + encypPrivateKey);

        } catch (Exception e) {
            e.printStackTrace();
        }

    }


    /**
     * create asset account
     *
     * @return
     * @throws Exception
     */
    public static Account createAssetAccount() throws Exception {

        System.out.println("##########createAssetAccount##########");
        OntSdk ontSdk = getOntSdk();
        Account account = new Account(ontSdk.defaultSignScheme);

        String address = account.getAddressU160().toBase58();
        String prikey = Helper.toHexString(account.serializePrivateKey());
        String pubkey = Helper.toHexString(account.serializePublicKey());
        String wif = account.exportWif();

        System.out.println("wif: " + wif);
        System.out.println("address: " + address);
        System.out.println("privatekey: " + prikey);
        System.out.println("publickey: " + pubkey);

        return account;
    }


    /**
     * register ontid
     *
     * @param account
     * @param identityPassword
     * @return
     */
    public static Identity registerOntId(Account account, String identityPassword) throws Exception {

        System.out.println("##############registerOntId############");
        OntSdk ontSdk = getOntSdk();

        Identity identity = ontSdk.getWalletMgr().createIdentity(identityPassword);

        //send register ontid transaction to blockchain.fee:0.01ONG ,paied by account
        String txnhash = ontSdk.nativevm().ontId().sendRegister(identity, identityPassword, account, 20000, 500);
        System.out.println("register ontid txnhash: " + txnhash);

        //write identity into account.json file
        ontSdk.getWalletMgr().writeWallet();

        return identity;
    }


    public static OntSdk getOntSdk() throws Exception {

        OntSdk wm = OntSdk.getInstance();
        //testnet
        wm.setRestful("http://polaris1.ont.io:20334");
        //mainnet
        //wm.setRestful("http://dappnode1.ont.io:20334");
        wm.setDefaultConnect(wm.getRestful());
        wm.openWalletFile("account.json");
        return wm;
    }


}
