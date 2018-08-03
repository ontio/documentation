---
title:
keywords: sample homepage
sidebar: SDKs_en
permalink: ontology_java_sdk_errorcode_en.html
folder: doc_en/SDKs
giturl: https://github.com/ontio/ontology-java-sdk/blob/master/docs/en/errorcode.md
---

<h1 align="center"> Error code </h1>

<p align="center" class="version">Version 1.0.0 </p>

English / [中文](./ontology_java_sdk_errorcode_zh.html)


| Return code | Description                   | Explanation                                     |
| :----------:|:-----------------------------:|:------------------------------------------------:|
| 0           | SUCCESS                       | Success                                          |
| 41001       | SESSION_EXPIRED               | Invalid session or timeout (need to login again) |
| 41002       | SERVICE_CEILING               | Reached the service limit                        |
| 41003       | ILLEGAL_DATAFORMAT            | Illegal data format                              |
| 41004       | INVALID_VERSION               | Invalid version                                  |
| 42001       | INVALID_METHOD                | Invalid method                                   |
| 42002       | INVALID_PARAMS                | Invalid parameters                               |
| 43001       | INVALID_TRANSACTION           | Invalid transaction                              |
| 43002       | INVALID_ASSET                 | Invalid asset                                    |
| 43003       | INVALID_BLOCK                 | Invalid block                                    |
| 44001       | UNKNOWN_TRANSACTION           | Transaction not found                            |
| 44002       | UNKNOWN_ASSET                 | Asset not found                                  |
| 44003       | UNKNOWN_BLOCK                 | Block not found                                  |
| 44004       | UNKNWN_CONTRACT               | Contract not found                                  |
| 45001       | INTERNAL_ERROR                | Internal error                                   |
| 47001       | SMARTCODE_ERROR               | smartcode error                                  |
|51001  |  InvalidParams |Account error, invalid params|
|51002  |  UnsupportedKeyType |Account error, unsupported key type|
|51003  |  InvalidMessage |Account error, invalid message|
|51004  |  WithoutPrivate |Account error, account without private key cannot generate signature|
|51005  |  InvalidSM2Signature |Account error, invalid SM2 signature parameter, ID (string) excepted|
|51006  |  AccountInvalidInput |Account error, account without public key cannot verify signature|
|51007  |  AccountWithoutPublicKey |Account error, unknown key type|
|51008  |  UnknownKeyType |Account error, null input|
|51009  |  NullInput |Account error, invalid data|
|51010  |  InvalidData |Account error, invalid params|
|51011  |  Decoded3bytesError |Account error, decoded 3 bytes error|
|51012  |  DecodePrikeyPassphraseError |Account error, decode prikey passphrase error|
|51013  |  PrikeyLengthError |Account error, prikey length error|
|51014  |  EncryptedPriKeyError |Account error, null prikey error|
|51015  |  encryptedPriKeyAddressPasswordErr |Account error, encrypted prikey address password not match|
|51016  |  EncriptPrivateKeyError |Account error, encript privatekey error|
|52001  |  InputError |Uint256 error, input error|
|52002  |  ChecksumNotValidate |Base58 Error, checksum does not validate|
|52003  |  InputTooShort |Base58 Error, input too short|
|52004  |  UnknownCurve |Curve Error, unknown curve|
|52006  |  UnknownAsymmetricKeyType |keyType Error, unknown asymmetric key type|
|52007  |  InvalidSignatureData |Signature error, invalid signature data: missing the ID parameter for SM3withSM2|
|52008  |  InvalidSignatureDataLen |Signature rrror, invalid signature data length|
|52009  |  MalformedSignature |Signature error, malformed signature|
|52010  |  UnsupportedSignatureScheme |Signature error, unsupported signature scheme|
|52011  |  DataSignatureErr |Signature error, data signature error|
|52012  |  UnSupportOperation |Address error, UnsupportedOperationException|
|53001  |  TxDeserializeError |Core error, transaction deserialize failed|
|53002  |  BlockDeserializeError |Core error, block deserialize failed|
|54001  |  MerkleVerifierErr |Wrong params: the tree size is smaller than the leaf index|
|54002  |  TargetHashesErr |TargetHashes error|
|54003  |  ConstructedRootHashErr ||
|54004  |  AsserFailedHashFullTree |Assert failed in hash full tree|
|54005  |  LeftTreeFull | Left tree always full |
|58001  |  SendRawTxError |SmartCodeTx error, sendRawTransaction error|
|58002  |  TypeError |SmartCodeTx error, type error|
|58003  |  NullCodeHash |OntIdTx error, null codeHash|
|58004  |  ParamError |OntIdTx error, param error|
|58005  |  ParamErr |OntIdTx error, param error|
|58006  |  DidNull |OntIdTx error, SendDid or receiverDid is null in metaData|
|58007  |  NotExistCliamIssuer |OntIdTx error, claim issuer doesn't exist|
|58007  |  NotFoundPublicKeyId |OntIdTx error, not found PublicKeyId|
|58008  |  PublicKeyIdErr |OntIdTx error, PublicKeyId error|
|58009  |  BlockHeightNotMatch |OntIdTx error, BlockHeight doesn't match|
|58010  |  NodesNotMatch |OntIdTx error, nodes don't match|
|58011  |  ResultIsNull |OntIdTx error, result is null|
|58012  |  CreateOntIdClaimErr |OntIdTx error, createOntIdClaim error|
|58013  |  VerifyOntIdClaimErr |OntIdTx error, verifyOntIdClaim error|
|58014  |  WriteVarBytesError |OntIdTx error, writeVarBytes error|
|58101  |  AssetNameError |OntAsset error,asset name error|
|58102  |  DidError |OntAsset error, Did error|
|58103  |  NullPkId |OntAsset error, null pkId|
|58104  |  NullClaimId |OntAsset error, null claimId|
|58105  |  OntAsset error, amount is less than or equal to zero|
|58106  |  ParamLengthNotSame |OntAsset error, param length is not the same|
|58201  |  NullKeyOrValue |RecordTx error, null key or value|
|58202  |  NullKey |RecordTx error, null key|
|58301  |  WebsocketNotInit |OntSdk error, WebSocket not init|
|58302  |  ConnRestfulNotInit |OntSdk error, connRestful not init|
|58401  |  SetParamsValueValueNumError |AbiFunction error, setParamsValue value num error|
|58402  |  InvalidUrlErr |Interfaces error, invalid url|
|58403  |  InvalidUrl |Interfaces error, invalid url|
|58501  |  GetAccountByAddressErr |WalletManager error, getAccountByAddress error|
|59000  |  OtherError| Other error|
