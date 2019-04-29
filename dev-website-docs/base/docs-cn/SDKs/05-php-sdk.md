
# 数字资产管理

## 钱包数据规范

钱包用户存储多个数字身份以及数字资产账户。钱包文件采用 JSON 格式对数据进行组织，各个字段的详细可以参考[钱包文件规范](钱包文件规范)。

### 打开、创建本地钱包

为了管理数字资产，首先需要创建或打开一个钱包文件:

```php
use ontio\sdk\Wallet;

// 打开已有钱包文件
$w = Wallet::fromFile('path_to_wallet_file');

// 创建本地钱包
$w = Wallet::create('example_wallet');
```

### 保存本地钱包

对钱包内容的修改，默认只作用于内存中的数据，如果需要将修改作用于钱包文件，则需要显式地进行保存:

```php
use ontio\sdk\Wallet;

// 打开已有钱包文件
$w = Wallet::fromFile('path_to_wallet_file');

// 一些修改操作...

// 将修改写入文件，默认写入到打开的位置，也可以指定另外的位置
$w->save('as_another_path_to_wallet_file');
```

## 公私钥和地址

账户是基于公私钥创建的，地址是公钥转换而来。

### 创建私钥

```php
use ontio\crypto\KeyType;
use ontio\crypto\KeyParameters;
use ontio\crypto\PrivateKey;

// 使用默认的参数创建私钥
// key type: KeyType::$Ecdsa
// key parameters: new KeyParameters(CurveLabel::$Secp256r1)
$key = PrivateKey::random();

// 使用指定的参数创建私钥
$key = PrivateKey::random(KeyType::$Sm2, new KeyParameters(CurveLabel::$Sm2P256v1));
```

### 导入私钥

```php
use ontio\crypto\PrivateKey;
use ontio\crypto\KeyParameters;
use ontio\common\ByteArray;

// 直接导入私钥
$prikey = new PrivateKey(
  ByteArray::fromHex('ab80a7ad086249c01e65c4d9bb6ce18de259dcfc218cd49f2455c539e9112ca3'),
  KeyType::$Sm2,
  new KeyParameters(CurveLabel::$Sm2P256v1)
);

// 由 wif 导入
$wif = 'L4shZ7B4NFQw2eqKncuUViJdFRq6uk1QUb6HjiuedxN4Q2CaRQKW'
$prikey = PrivateKey::fromWif($wif);
```

### 获取公钥

当获取了私钥实例后，可以通过调用实例上的方法来获取对应的公钥:

```php
// 获得 ontio\crypto\PublicKey 实例
$pubkey = $prikey->getPublicKey();
```

### 获取地址

当获取了公钥实例后，可以通过下面方式获得对应的地址:

```php
use ontio\crypto\Address;

$pubkey = $prikey->getPublicKey();
$addr = Address::fromPubKey($pubkey);
```

## 账户

### 创建账户

```php
use ontio\sdk\Account;

// '123456' 为密码，该密码用于加密私钥
$acc =  Account::create('123456');
```

### 导入账户

支持多种方式导入账户:

由 Keystore 导入:

```php
use ontio\sdk\Keystore;
use ontio\sdk\Account;

$data = '{"address":"AG9W6c7nNhaiywcyVPgW9hQKvUYQr5iLvk","key":"+UADcReBcLq0pn/2Grmz+UJsKl3ryop8pgRVHbQVgTBfT0lho06Svh4eQLSmC93j","parameters":{"curve":"P-256"},"label":"11111","scrypt":{"dkLen":64,"n":4096,"p":8,"r":8},"salt":"IfxFV0Fer5LknIyCLP2P2w==","type":"A","algorithm":"ECDSA"}';
$keystore = Keystore::fromJson($data);

$acc = Account::importFromKeystore($keystore, '111111');
```

由 wif 导入:

```php
use ontio\sdk\Account;

$wif = 'L4shZ7B4NFQw2eqKncuUViJdFRq6uk1QUb6HjiuedxN4Q2CaRQKW'
$prikey = Account::importFromWif('123456', $wif);
```

由助记词导入:

```php
use ontio\sdk\Account;

$mnemonic = 'hill ready family useful detect bacon visit canoe recall circle topple claw sheriff universe robust lounge cluster duty vast excuse weasel grunt junk actor';

$acc = Account::importFromMnemonic($mnemonic);
```

### 加入钱包

账号导入成功后，如果需要作用到钱包上，需要将账户加入钱包:

```php
use ontio\sdk\Wallet;

$w = Wallet::fromFile('path_to_wallet_file');
$acc =  Account::create('123456');
$w->addAccount($acc);
$w->save(); // 写入文件
```

### 移除账户

```php
$w = Wallet::fromFile('path_to_wallet_file');
$acc = $w->accounts[1];
$w->deleteAccount($acc);
$w->save(); // 写入文件
```

## 资产

本体中有两种原生资产: ONT 和 ONG

### 转账

下面是一个比较完整的对 ONT 进行转账的例子:

```php
use ontio\crypto\Address;
use ontio\core\transaction\TransactionBuilder;
use ontio\smartcontract\nativevm\OntAssetTxBuilder;
use ontio\sdk\Wallet;
use ontio\network\JsonRpc;

// 钱包文件
$walletData = '{"name":"MyWallet","version":"1.1","scrypt":{"p":8,"n":16384,"r":8,"dkLen":64},"accounts":[{"address":"ASSxYHNSsh4FdF2iNvHdh3Np2sgWU21hfp","enc-alg":"aes-256-gcm","key":"t2Kk2jNL4BAoXlYn309DKfxogxJRNvsJ8+GG4kiMB+UvWGXEilYRzfIYeNZbfVbu","algorithm":"ECDSA","salt":"CdRa1hTiOaVESNfJJmcMNw==","parameters":{"curve":"P-256"},"label":"","publicKey":"0344ea636caaebf23c7cec2219a75bd6260f891413467922975447ba57f3c824c6","signatureScheme":"SHA256withECDSA","isDefault":true,"lock":false},{"address":"AL9PtS6F8nue5MwxhzXCKaTpRb3yhtsix5","enc-alg":"aes-256-gcm","key":"vwIgX3qJO+1XikdPAfjAu/clsgS2l2xkEWsRR9XZQ8OyFViX+r/6Yq+cV0wnKQUM","algorithm":"SM2","salt":"xzvrFkHAgsEeX64V+4mpLw==","parameters":{"curve":"sm2p256v1"},"label":"","publicKey":"131403a9b89a0443ded240c3dee97221353d000d0dc905b7c085f4ef558b234a75e122","signatureScheme":"SM3withSM2","isDefault":false,"lock":false}]}';

// 载入钱包
$wallet = Wallet::fromJson($walletData);

// '123456' 为账户密码
$fromPrikey = self::$wallet->accounts[0]->exportPrivateKey('123456', self::$wallet->scrypt);
$fromAddress = self::$wallet->accounts[0]->address;

// 交易费用参数
$gasLimit = '20000';
$gasPrice = '500';

// JsonRpc 客户端实例
$rpc = new JsonRpc('http://127.0.0.1:20336');

// 资产流向方
$to = new Address('AL9PtS6F8nue5MwxhzXCKaTpRb3yhtsix5');

// 构造交易数据
$ontBuilder = new OntAssetTxBuilder();
$tx = $ontBuilder->makeTransferTx('ONT', $fromAddress, $to, 170, $gasPrice, $gasLimit);

// 对交易进行签名
$txBuilder = new TransactionBuilder();
$txBuilder->signTransaction($tx, $fromPrikey);

// 发送交易
$rpc->sendRawTransaction($tx->serialize());
```

转账 ONG 与上面的流程基本一样，只是 `makeTransferTx` 第一个参数替换为 `ONG` 即可。

### 余额查询

使用 RPC 来进行余额查询:

```php
use ontio\network\JsonRpc;
use ontio\crypto\Address;

$rpc = new JsonRpc('http://127.0.0.1:20336');
$address = new Address('ASSxYHNSsh4FdF2iNvHdh3Np2sgWU21hfp');
$balance = $rpc->getBalance($address);
```
