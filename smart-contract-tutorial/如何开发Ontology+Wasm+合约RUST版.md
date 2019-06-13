# 如何开发Ontology Wasm 合约

## 1.  使用RUST编写合约

ontolo wasm合约不仅可以使用C++开发，也可以使用RUST开发,让我们从一个Hello world开始:


```rust
#![no_std]
extern crate ontio_std as ostd;
use ostd::abi::{Sink, ZeroCopySource};
use ostd::prelude::*;
use ostd::runtime;
use ostd::{str, String};

fn say_hello() -> String {
    return "hello world".to_string();
}
#[no_mangle]
pub fn invoke() {
    let input = runtime::input();
    let mut source = ZeroCopySource::new(&input);
    let action: &[u8] = source.read().unwrap();
    let mut sink = Sink::new(12);
    match action {
        b"say_hello" => sink.write(say_hello()),
        _ => panic!("unsupported action!"),
    }
    runtime::ret(sink.bytes())
}
#[test]
fn test_hello() {
    say_hello();
}
```

### 合约入口

入口函数的写法可以参考下面的例子。
`runtime::input()` 用于接收调用合约时输入的参数,在读取参数时,读到的第一个参数是方法名,然后是参数。

```rust
#[no_mangle]
pub fn invoke() {
    let input = runtime::input();
    let mut source = ZeroCopySource::new(&input);
    let action: &[u8] = source.read().unwrap();//读取方法名
    let mut sink = Sink::new(12);
    match action {                            //根据方法名进行跳转
        b"hello" => sink.write(say_hello()),
        _ => panic!("unsupported action!"),
    }
    runtime::ret(sink.bytes())             //将执行结果进行返回
}
```

定义了合约的对外接口, 在上面的例子中, 我们只支持```say_hello```这个方法

```rust
fn say_hello() -> String {
    return "hello world".to_string();
}
```

这个"hello world" 可以通过预执行的方式调用合约中的方法在客户端获得合约执行结果.

### 智能合约API

Ontology Wasm 提供如下API与区块链的底层进行交互

| API               | 参数                                        | 返回值  | 说明                                              |
| ----------------- | ------------------------------------------- | ------- | ------------------------------------------------- |
| timestamp         | None                                        | u64     | 当前区块的时间戳                                  |
| block_height      | None                                        | u32     | 当前区块高度                                      |
| self_address      | Nones                                       | Address | 当前合约地址                                      |
| caller_address    | None                                        | Address | 调用者合约地址(若不是通过合约调用,同self_address) |
| entry_address     | None                                        | Address | 入口合约地址(若不是通过合约调用, 同self_address)  |
| check_witness     | address                                     | bool    | 检查传入地址的签名                                |
| current_blockhash | None                                        | H256    | 当前区块hash                                      |
| current_txhash    | None                                        | H256    | 当前交易hash                                      |
| notify            | string                                      | void    | 发送通知事件                                      |
| call_contract     | address, params                             | Option<Vec<u8>>    | 调用普通合约(wasmvm/neovm)                        |
| get               | key                                         | Option<Vec<u8>>    | 读取存储                                          |
| put               | key, value                                  | void    | 写入存储                                          |
| delete            | key                                         | void    | 删除存储                                          |
| contract_create   | code, vmtype,name,version,author,email,desc | Address | 创建合约                                          |
| contract_migrate  | code, vmtype,name,version,author,email,desc | Address | 迁移(升级)合约                                    |
| contract_delete   | address                                     | void    | 删除合约                                          |
|                   |                                             |         |                                                   |

下面我们通过一个更加复杂的例子来演示如何通过这些API来开发一个完整的Wasm 智能合约.

### 红包合约

我们都会经常发红包,通过微信等聊天工具,我们可以给朋友发送红包,你收到的钱会记入到你的微信账户中,

类似于微信的流程,我们将尝试创建一个智能合约, 你可以发送一个ont , ong或者是标准的OEP4的token资产红包给你的朋友们,而他们抢到的红包可以直接转入到他们的钱包账户中.

#### 1. 创建合约

rust版合约是通过cargo管理工具创建和管理的.
首先,我们需要新建合约的lib文件。
```rust
cargo new --lib red-envlope
```
在生成的Cargo.toml文件中引入ontio-std库文件。
一个完整的Cargo.toml配置文件如下

```toml
[package]
name = "helloworld"
version = "0.1.0"
authors = ["username <***@***.com>"]
edition = "2018"

[lib]
crate-type = ["cdylib"]
path = "src/lib.rs"

[dependencies]
hex = "0.3.2"
ontio-std = {path="../../ontio-std"}

[features]
default = ["ontio-std/bump-alloc"]
mock = ["ontio-std/mock"]
```
合约的逻辑代码可以写在lib.rs里面。

这个合约我们需要三个接口:

```create_red_envlope```  : 创建红包

```query_envlope``` : 查询红包信息

```claim_envlope``` :抢红包

在合约中,我们需要在存储中保存一些关键的数据,并且为这些数据的**KEY** 设置前缀以便于后面的查询

```rust
const re_prefix :&str = "RE_PREFIX_";
const sent_prefix :&str = "SENT_COUNT_";
const claim_prefix :&str = "CLAIM_PREFIX_";
```

因为我们的合约支持ONT 和ONG这两种ontology的原生资产, 我们可以预先定义好这两种资产的合约地址

```rust
const ONT_CONTRACT_ADDRESS: Address = base58!("AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV");
const ONG_CONTRACT_ADDRESS: Address = base58!("AFmseVrdL9f9oyCzZefL9tG6UbvhfRZMHJ");
```

**Note**: 不同于标准的智能合约, 原生合约(native contract)的合约地址是固定,而不是根据合约代码的hash计算而来



为了方便我们的struct类型数据的存储与访问，我们需要为其实现Encoder和Decoder接口,在需要将数据存储到数据库的时候,调用encode方法,将struct类型的数据序列化成字节数组,
在需要使用struct类型的数据的时候,我们可以调用decode方法将数据由字节数组转换成struct类型的数据。

```rust
struct ReceiveRecord {
    account:Address, //用户地址
    amount: u64,     //抢到的金额  
}
impl Encoder for ReceiveRecord {
    fn encode(&self, sink: &mut Sink) {
        sink.write(&self.account);
        sink.write(self.amount);
    }
}

impl Decoder for ReceiveRecord {
    fn decode(source: &mut Source) -> Result<Self, Error> {
        let account:Address = source.read().unwrap();
        let amount :u64= source.read().unwrap();
        return Ok(ReceiveRecord{
            account,
            amount,
        })
    }
}
struct EnvlopeStruct {
    token_addr:Address,       //资产token的地址
    total_amount: u64,        //红包总金额
    total_package_count: u64, //红包总数
    remain_amount:u64,        //当前剩余的金额
    remain_package_count: u64, //当前剩余的红包数
    records: Vec<ReceiveRecord>, //已经抢完的记录
}

impl Encoder for EnvlopeStruct {
    fn encode(&self, sink: &mut Sink) {
        sink.write(&self.token_addr);
        sink.write(self.total_amount);
        sink.write(self.total_package_count);
        sink.write(self.remain_amount);
        sink.write(self.remain_package_count);
        sink.write(self.records.len() as u32);
        for item in self.records.iter() {
            item.encode(sink);
        }
    }
}

impl Decoder for EnvlopeStruct{
    fn decode(source: &mut Source) -> Result<Self, Error> {
        let token_addr = source.read().unwrap();
        let total_amount = source.read().unwrap();
        let total_package_count = source.read().unwrap();
        let remain_amount = source.read().unwrap();
        let remain_package_count = source.read().unwrap();
        let l = source.read().unwrap_or(0u32);
        let mut records :Vec<ReceiveRecord>= Vec::new();
        for i in 0..l {
            let r = ReceiveRecord::decode(source).unwrap();
            records.push(r);
        }
        return Ok(EnvlopeStruct{
            token_addr,
            total_amount,
            total_package_count,
            remain_amount,
            remain_package_count,
            records,
        })
    }
}

```


准备工作差不多了,下面我们开始开发具体的接口逻辑.

#### 2. 创建红包

1. 创建红包需要指定创建者地址, 红包数量, 红包金额和资产的合约地址
```rust
fn create_red_envlope(owner: Address, pack_count: u64, amount: u64, token_addr: Address) -> bool {
        return true;
  }
```

2. 检查是否有创建者的签名, 否则交易回滚退出

```rust
if runtime::check_witness(&owner) == false {
        return false;
    }
```

3. 如果是红包资产是ONT的时候,由于ONT的不可分割性(最小为1个ONT), 红包的金额要大于或等于红包的数量,保证每个红包最少有1个ONT.

```rust
if is_ont_address(token_addr.clone()) {
    assert!(amount >= pack_count);
}
```

4. 对于每个红包的创建者,我们需要记录一下他发送红包的总数量.

```rust
let key = [sent_prefix.as_bytes(), owner.as_ref()].concat();
let mut sent_count = database::get(&key).unwrap_or(0u64);
sent_count += 1;
database::put(&key, sent_count);
```


5. 生成红包hash, 这个hash 就是之后标识这个红包的ID

```rust
let hash_key = [owner.as_ref(), format!("{}", sent_count).as_bytes()].concat();
let hash = utils::sha256(hash_key);

mod utils {
    use super::*;
    pub fn sha256<D: AsRef<[u8]>>(data: D) -> String {
        let mut hasher = sha2::Sha256::new();
        hasher.input(data.as_ref());
        format!("{:?}", H256::from_slice(hasher.result().as_slice()))
    }
}
```



6. 根据token资产的类型,将资产转入合约中.

```rust
let re_key = [re_prefix.as_bytes(),hash_bytes].concat();
let self_addr = runtime::address();
if is_ont_address(token_addr.clone()) {
    let state = ont::State{
        from:owner.clone(),
        to:self_addr,
        amount:U256::from(amount),
    };
    let res = ont::transfer(&[state]);
    if !res {
        return false
    }
} else if is_ong_address(token_addr.clone()) {
    let state = ont::State{
        from:owner.clone(),
        to:self_addr,
        amount:U256::from(amount),
    };
    let res = ong::transfer(&[state]);
    if !res {
        return false
    }
} else {
    let mut sink = Sink::new(16);
    sink.write(("transfer".to_string(), self_addr, owner, U256::from(amount)));
    let res = runtime::call_contract(&token_addr, sink.bytes());
    if res.is_none() {
        return false;
    }
}
```



```rust
		struct envlopeStruct es ;
        es.tokenAddress = tokenAddr;
        es.totalAmount = amount;
        es.totalPackageCount = packcount;
        es.remainAmount = amount;
        es.remainPackageCount = packcount;
        es.records = {};
        storage_put(rekey, es);
```

7. 将红包信息保存在合约中

```rust
let es = EnvlopeStruct{
token_addr:token_addr.clone(),
total_amount:amount,
total_package_count:pack_count,
remain_amount: amount,
remain_package_count:pack_count,
records:Vec::new(),
};
database::put(re_key.clone(), es);
return true;
```

8. 发送创建红包的事件

一个简单的红包就创建完成了, 下一步我们需要实现如何查询这个红包的信息.

#### 2. 查询红包

查询红包的逻辑非常简单, 只需要将存储中的红包信息取出并格式化返回即可.

最后,其他的用户可以根据hash(红包的ID)来领取(抢)这个红包了.

```rust
fn query_envlope(hash: &str) -> String {
 let re_key = [re_prefix,hash].concat();
 let res:Option<EnvlopeStruct> = database::get::<_,EnvlopeStruct>(re_key);
 if let Some(r) = res {
     let mut records = "".to_string();
     for x in r.records.iter() {
         format!("{};{}", records, format!("account: {}, amount: {}", x.account.to_hex_string(),x.amount));
     }
     return format!("token_addr:{}, total_amount: {}, total_package_count: {}, remain_amount: {}, remain_package_count: {},\
     records:[{}]", r.token_addr.to_hex_string(), r.total_amount,r.total_package_count,r.remain_amount,r.remain_package_count,records);
 }
 return "".to_string()
}
```


#### 3. 领取红包

1. 领取红包需要输入领取人的账户, 和红包的hash.
```rust
  fn claim_envlope(account:Address, hash: &str) -> bool {
    return true;
  }
```

2. 同样, 我们需要验证领取账户的签名, 不允许替其他人抢红包, 而且每个账户每个红包智能抢一次.
```rust
if runtime::check_witness(account) == false {
        return false;
    }
    let claim_key = [claim_prefix.as_bytes(), hash.as_bytes(), account.as_ref()].concat();
    let claimed = database::get(claim_key.clone()).unwrap_or(0u64);
    if claimed != 0 {
        return false
    }
```

3. 按照hash从存储中取出红包的信息, 判断这个红包是否没有被抢完.

```rust
let re_key = [re_prefix, hash].concat();
let es = database::get::<_, EnvlopeStruct>(re_key.clone());
if es.is_none() {
return false;
};
let mut est = es.unwrap();
if est.remain_amount <= 0 {
    return false;
}
if est.remain_package_count <= 0 {
    return false;
}
```

4. 新建一条领取的记录

```rust
let mut record = ReceiveRecord{
account:account.clone(),
amount:0,
};
```

5. 计算本次领取红包的资产数量, 如果是最后一个红包, 数量为剩余的金额, 否则根据当前区块hash计算随机数,确定本次领取的数量, 并更新红包信息.


```rust
let mut claim_amount = 0;
if est.remain_package_count == 1 {
    claim_amount = est.remain_amount;
    record.amount = claim_amount;
} else {
    let random = runtime::current_blockhash();
    let mut part = [0u8;8];
    part.copy_from_slice(&random.as_bytes()[..8]);
    let random_num = U256::from_little_endian(&part).as_u64();
    let percent = random_num%100+1;
    let mut claim_amount = est.remain_amount * percent / 100;

    if claim_amount == 0 {
        claim_amount = 1;
    } else if is_ont_address(est.token_addr.clone()){
        if est.remain_amount - claim_amount < est.remain_package_count - 1 {
            claim_amount = est.remain_amount - est.remain_package_count;
        }
    }
    record.amount = claim_amount;
}
est.remain_amount -= claim_amount;
est.remain_package_count -= 1;
est.records.push(record);
```

6. 根据计算结果, 将对应资产从合约中转到领取的账户.


```rust
let self_addr = runtime::address();
if is_ont_address(est.token_addr.clone()) {
let state = ont::State{
    from:self_addr,
    to:account.clone(),
    amount:U256::from(claim_amount),
};
return ont::transfer(&[state]);
} else if is_ong_address(est.token_addr.clone()) {
let state = ont::State{
    from:self_addr,
    to:account.clone(),
    amount:U256::from(claim_amount),
};
return ong::transfer(&[state]);
} else {
let mut sink = Sink::new(16);
sink.write(("transfer".to_string(), self_addr, account, U256::from(claim_amount)));
let res = runtime::call_contract(&est.token_addr, sink.bytes());
if res.is_none() {
    return false;
}
}
```



7. 记录领取的信息, 将更新后的红包信息写回存储并发送通知事件.

```rust
database::put(claim_key, claim_amount);
database::put(re_key, est);
return true;
```



至此, 一个简单的红包合约逻辑完成, 完整的合约代码如下:

```rust
#![cfg_attr(not(feature = "mock"), no_std)]
#![feature(proc_macro_hygiene)]
extern crate ontio_std as ostd;
use ostd::abi::{Sink, ZeroCopySource, Source, Error};
use ostd::prelude::*;
use ostd::runtime;
use ostd::{str, String};
use ostd::types::Address;
use ostd::database;
use ostd::base58;
use ostd::contract::{ont, ong};
use ostd::abi::{Decoder, Encoder};
use ostd::console;
use sha2::Digest;


const ONT_CONTRACT_ADDRESS: Address = base58!("AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV");
const ONG_CONTRACT_ADDRESS: Address = base58!("AFmseVrdL9f9oyCzZefL9tG6UbvhfRZMHJ");

const re_prefix :&str = "RE_PREFIX_";
const sent_prefix :&str = "SENT_COUNT_";
const claim_prefix :&str = "CLAIM_PREFIX_";


struct ReceiveRecord {
    account:Address,
    amount: u64,
}
impl Encoder for ReceiveRecord {
    fn encode(&self, sink: &mut Sink) {
        sink.write(&self.account);
        sink.write(self.amount);
    }
}

impl Decoder for ReceiveRecord {
    fn decode(source: &mut Source) -> Result<Self, Error> {
        let account:Address = source.read().unwrap();
        let amount :u64= source.read().unwrap();
        return Ok(ReceiveRecord{
            account,
            amount,
        })
    }
}

struct EnvlopeStruct {
    token_addr:Address,
    total_amount: u64,
    total_package_count: u64,
    remain_amount:u64,
    remain_package_count: u64,
    records: Vec<ReceiveRecord>,
}

impl Encoder for EnvlopeStruct {
    fn encode(&self, sink: &mut Sink) {
        sink.write(&self.token_addr);
        sink.write(self.total_amount);
        sink.write(self.total_package_count);
        sink.write(self.remain_amount);
        sink.write(self.remain_package_count);
        sink.write(self.records.len() as u32);
        for item in self.records.iter() {
            item.encode(sink);
        }
    }
}

impl Decoder for EnvlopeStruct{
    fn decode(source: &mut Source) -> Result<Self, Error> {
        let token_addr = source.read().unwrap();
        let total_amount = source.read().unwrap();
        let total_package_count = source.read().unwrap();
        let remain_amount = source.read().unwrap();
        let remain_package_count = source.read().unwrap();
        let l = source.read().unwrap_or(0u32);
        let mut records :Vec<ReceiveRecord>= Vec::new();
        for i in 0..l {
            let r = ReceiveRecord::decode(source).unwrap();
            records.push(r);
        }
        return Ok(EnvlopeStruct{
            token_addr,
            total_amount,
            total_package_count,
            remain_amount,
            remain_package_count,
            records,
        })
    }
}

fn create_red_envlope(owner: Address, pack_count: u64, amount: u64, token_addr: Address) -> bool {
    if runtime::check_witness(&owner) == false {
        return false;
    }
    if is_ont_address(token_addr.clone()) {
        assert!(amount >= pack_count);
    }
    let key = [sent_prefix.as_bytes(), owner.as_ref()].concat();
    let mut sent_count = database::get(&key).unwrap_or(0u64);
    sent_count += 1;
    database::put(&key, sent_count);
    let hash_key = [owner.as_ref(), format!("{}", sent_count).as_bytes()].concat();
    let hash = utils::sha256(hash_key);
    let hash_bytes = hash.as_bytes();
    let re_key = [re_prefix.as_bytes(),hash_bytes].concat();
    let self_addr = runtime::address();
    if is_ont_address(token_addr.clone()) {
        let state = ont::State{
            from:owner.clone(),
            to:self_addr,
            amount:U256::from(amount),
        };
        let res = ont::transfer(&[state]);
        if !res {
            return false
        }
    } else if is_ong_address(token_addr.clone()) {
        let state = ont::State{
            from:owner.clone(),
            to:self_addr,
            amount:U256::from(amount),
        };
        let res = ong::transfer(&[state]);
        if !res {
            return false
        }
    } else {
        let mut sink = Sink::new(16);
        sink.write(("transfer".to_string(), self_addr, owner, U256::from(amount)));
        let res = runtime::call_contract(&token_addr, sink.bytes());
        if res.is_none() {
            return false;
        }
    }
    let es = EnvlopeStruct{
        token_addr:token_addr.clone(),
        total_amount:amount,
        total_package_count:pack_count,
        remain_amount: amount,
        remain_package_count:pack_count,
        records:Vec::new(),
    };
    database::put(re_key.clone(), es);
    console::debug(h.as_str());
    runtime::notify(hash_bytes);
    return true;
}


fn query_envlope(hash: &str) -> String {
    let re_key = [re_prefix,hash].concat();
    let res:Option<EnvlopeStruct> = database::get::<_,EnvlopeStruct>(re_key);
    if let Some(r) = res {
        let mut records = "".to_string();
        for x in r.records.iter() {
            format!("{};{}", records, format!("account: {}, amount: {}", x.account.to_hex_string(),x.amount));
        }
        return format!("token_addr:{}, total_amount: {}, total_package_count: {}, remain_amount: {}, remain_package_count: {},\
        records:[{}]", r.token_addr.to_hex_string(), r.total_amount,r.total_package_count,r.remain_amount,r.remain_package_count,records);
    }
    return "".to_string()
}

fn claim_envlope(account:Address, hash: &str) -> bool {
    if runtime::check_witness(account) == false {
        return false;
    }
    let claim_key = [claim_prefix.as_bytes(), hash.as_bytes(), account.as_ref()].concat();
    let claimed = database::get(claim_key.clone()).unwrap_or(0u64);
    if claimed != 0 {
        return false
    }
    let re_key = [re_prefix, hash].concat();
    let es = database::get::<_, EnvlopeStruct>(re_key.clone());
    if es.is_none() {
        return false;
    }
    let mut est = es.unwrap();
    if est.remain_amount <= 0 {
        return false;
    }
    if est.remain_package_count <= 0 {
        return false;
    }
    let mut record = ReceiveRecord{
        account:account.clone(),
        amount:0,
    };
    let mut claim_amount = 0;
    if est.remain_package_count == 1 {
        claim_amount = est.remain_amount;
        record.amount = claim_amount;
    } else {
        let random = runtime::current_blockhash();
        let mut part = [0u8;8];
        part.copy_from_slice(&random.as_bytes()[..8]);
        let random_num = U256::from_little_endian(&part).as_u64();
        let percent = random_num%100+1;
        let mut claim_amount = est.remain_amount * percent / 100;

        if claim_amount == 0 {
            claim_amount = 1;
        } else if is_ont_address(est.token_addr.clone()){
            if est.remain_amount - claim_amount < est.remain_package_count - 1 {
                claim_amount = est.remain_amount - est.remain_package_count;
            }
        }
        record.amount = claim_amount;
    }
    est.remain_amount -= claim_amount;
    est.remain_package_count -= 1;
    est.records.push(record);
    let self_addr = runtime::address();
    if is_ont_address(est.token_addr.clone()) {
        let state = ont::State{
            from:self_addr,
            to:account.clone(),
            amount:U256::from(claim_amount),
        };
        return ont::transfer(&[state]);
    } else if is_ong_address(est.token_addr.clone()) {
        let state = ont::State{
            from:self_addr,
            to:account.clone(),
            amount:U256::from(claim_amount),
        };
        return ong::transfer(&[state]);
    } else {
        let mut sink = Sink::new(16);
        sink.write(("transfer".to_string(), self_addr, account, U256::from(claim_amount)));
        let res = runtime::call_contract(&est.token_addr, sink.bytes());
        if res.is_none() {
            return false;
        }
    }
    database::put(claim_key, claim_amount);
    database::put(re_key, est);
    return true;
}

fn is_ong_address(contract_addr: Address) -> bool {
    if contract_addr == ONG_CONTRACT_ADDRESS {
        return true;
    }
    false
}

fn is_ont_address(contract_addr: Address) -> bool {
    if contract_addr == ONT_CONTRACT_ADDRESS {
        return true;
    }
    false
}

#[no_mangle]
pub fn invoke() {
    let input = runtime::input();
    let mut source = ZeroCopySource::new(&input);
    let action: &[u8] = source.read().unwrap();
    let mut sink = Sink::new(12);
    match action {
        b"create_red_envlope" => {
            console::debug("11111");
            let (owner,pack_count, amount, token_addr) = source.read().unwrap();
            sink.write(create_red_envlope(owner,pack_count, amount, token_addr));
        },
        b"query_envlope" => {
            let hash = source.read().unwrap();
            sink.write(query_envlope(hash));
        }
        b"claim_envlope" => {
            let (account, hash) = source.read().unwrap();
            sink.write(claim_envlope(account, hash));
        }
        _ => panic!("unsupported action!"),
    }
    runtime::ret(sink.bytes())
}


mod utils {
    use super::*;
    pub fn sha256<D: AsRef<[u8]>>(data: D) -> String {
        let mut hasher = sha2::Sha256::new();
        hasher.input(data.as_ref());
        format!("{:?}", H256::from_slice(hasher.result().as_slice()))
    }
}
```



### 测试合约

1. 使用CLI

请参考: <https://github.com/ontio/ontology-wasm-cdt-cpp/blob/master/How_To_Run_ontologywasm_node.md>



2. 使用golang sdk

请参考:<https://github.com/ontio/ontology-wasm-cdt-cpp/blob/master/example/other/main.go>



本示例只是为了展示如何编写一个完整的ontology wasm 智能合约, 如何通过调用API和底层的区块链进行交互,如果要作为正式的产品, 还需要解决红包的隐私问题: 所有人都可以通过监控合约的事件来取得红包的hash, 意味着每个人都可以抢这个红包, 这个问题通过在创建红包时指定哪些账户能够领取来解决, 如果有兴趣, 您也可以尝试修改测试一下.
