import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;
import com.github.ontio.OntSdk;
import com.github.ontio.common.Helper;
import com.github.ontio.core.DataSignature;
import com.github.ontio.crypto.SignatureScheme;
import com.github.ontio.sdk.wallet.Identity;

import java.util.*;

/**
 * @version 0.9
 * @date 2018/10/23
 */
public class OntIdSignDemo {


    public static void main(String[] args) {

        try {
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
            JSONObject obj = new JSONObject();
            obj.put("OntId", ontId);
            obj.put("Ope", "kyc");
            obj.put("DesCN", "test");
            obj.put("DesEN", "test");
            obj.put("Logo", "test");
            obj.put("KycCallBackAddr", "test");
            obj.put("KycAuthTemplate", "authtemplate_kyc01");
            String orignalData = obj.toJSONString();
            System.out.println("original data: " + orignalData);

            //sign
            String signedData = signatureData(ontId, salt, password, encryptedPriKey, scryptN, orignalData);
            System.out.println("The signed data: " + signedData);

            //verify signature
            Boolean verifyRs = verifySignature(ontId, orignalData, signedData);
            System.out.println("verify signature result: " + verifyRs);

        } catch (Exception e) {
            e.printStackTrace();
        }

    }


    /**
     * use identity privatekey to sinature data
     *
     * @param ontId
     * @param salt
     * @param password
     * @param origData
     * @return
     * @throws Exception
     */
    public static String signatureData(String ontId, String salt, String password, String encryptedPriKey, int scryptN, String origData) throws Exception {

        System.out.println("#####################################");
        OntSdk ontSdk = getOntSdk();

        String prikey = com.github.ontio.account.Account.getGcmDecodedPrivateKey(encryptedPriKey, password, ontId.split(":")[2], Base64.getDecoder().decode(salt), scryptN, SignatureScheme.SHA256WITHECDSA);

        com.github.ontio.account.Account account = new com.github.ontio.account.Account(Helper.hexToBytes(prikey), ontSdk.defaultSignScheme);
        String signedData = Base64.getEncoder().encodeToString(ontSdk.signatureData(account, origData.getBytes()));

        return signedData;
    }

    /**
     * verify signature
     *
     * @param signerOntId
     * @return
     */
    public static Boolean verifySignature(String signerOntId, String origData, String signedData) throws Exception {

        System.out.println("#####################################");
        OntSdk ontSdk = getOntSdk();

        String issuerDdo = ontSdk.nativevm().ontId().sendGetDDO(signerOntId);
        String pubkeyStr = JSON.parseObject(issuerDdo).getJSONArray("Owners").getJSONObject(0).getString("Value");

        Boolean rs = ontSdk.verifySignature(Helper.hexToBytes(pubkeyStr), origData.getBytes(), Base64.getDecoder().decode(signedData));
        return rs;
    }



    public static OntSdk getOntSdk() throws Exception {

        OntSdk wm = OntSdk.getInstance();
        //testnet
        wm.setRestful("http://polaris1.ont.io:20334");
        //mainnet
        //wm.setRestful("http://dappnode1.ont.io:20334");
        wm.setDefaultConnect(wm.getRestful());
        wm.openWalletFile("account10.json");
        return wm;
    }

}
