const data = {
        "DesCN": "test",
        "DesEN": "test",
        "KycAuthTemplate": "authtemplate_kyc01",
        "KycCallBackAddr": "test",
        "Logo": "test",
        "NameCN": "test",
        "NameEN": "test",
        "OntId": "did:ont:A1eJrWSTt61ts1dzvKfZa3j5Mj7CuetR6w",
        "Type": "test"
    }

const content = JSON.stringify(data);
console.log('content: ' + content);
var encrypted = new Ont.Crypto.PrivateKey("OMXQHj3ZItI7Ku44GiOmFyuVY5yxMNFym1oxo/d8YZLUN+acg/vRyL3x1Spqrzxi");
var salt = "3kEAxK2vbtj7tFRiU0G1Nw=="
var ontid = "did:ont:AWeLrWSTt61tsZdzvKfZa3j5Mj7CuetR6w"
var address = new Ont.Crypto.Address(ontid.substr(8))
var password = "111111"
var scryptN = 4096
var params = {
    cost: scryptN,
    blockSize: 8,
    parallel: 8,
    size: 64
}
var pri 
try {
    pri = encrypted.decrypt(password, address, salt, params);
} catch(err) {
    console.log(err)
}

var msg = Ont.utils.str2hexstr(content);
var signature = pri.sign(msg);
var sigVal = signature.serializePgp().Value;

