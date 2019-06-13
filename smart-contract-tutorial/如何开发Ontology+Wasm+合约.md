# 如何开发Ontology Wasm 合约

## 1.  使用C++编写合约 

和EOS一样， 开发者可以使用C++作为合约开发语言，按照惯例，我们还是从一个Hello world开始:



```cpp
#include<ontiolib/ontio.hpp>
#include<stdio.h>

using namespace ontio;
class hello:public contract {
    public:
    using contract::contract:
    void sayHello(){
        printf("hello world!");
    }
};
ONTIO_DISPATCH(hello, (sayHello));
```

### 合约入口

[cdt编译器](https://github.com/ontio/ontology-wasm-cdt-cpp)已经对入口和参数解析进行了封装，所以开发者不需要重新定义入口方法。

```cpp
ONTIO_DISPATCH(hello, (sayHello));
```

定义了合约的对外接口, 在上面的例子中, 我们只支持```sayHello```这个方法

```cpp
 printf("hello world!");
```

这个"hello world" 会在节点的日志中以"debug level" 打印出来, 在实际的应用中, ```printf``` 只能用作调试的目的, 一个实际的智能合约,需要实现更多更复杂的功能.

### 智能合约API

Ontology Wasm 提供如下API与区块链的底层进行交互

| API               | 参数                                        | 返回值  | 说明                                              |
| ----------------- | ------------------------------------------- | ------- | ------------------------------------------------- |
| timestamp         | None                                        | uint64  | 当前区块的时间戳                                  |
| block_height      | None                                        | uint32  | 当前区块高度                                      |
| self_address      | Nones                                       | address | 当前合约地址                                      |
| caller_address    | None                                        | address | 调用者合约地址(若不是通过合约调用,同self_address) |
| entry_address     | None                                        | address | 入口合约地址(若不是通过合约调用, 同self_address)  |
| check_witness     | address                                     | bool    | 检查传入地址的签名                                |
| current_blockhash | None                                        | H256    | 当前区块hash                                      |
| current_txhash    | None                                        | H256    | 当前交易hash                                      |
| notify            | string                                      | void    | 发送通知事件                                      |
| call_native       | address, params,        result              | void    | 调用ontology的native合约                          |
| call_contract     | address, params,result                      | void    | 调用普通合约(wasmvm/neovm)                        |
| storage_get       | key, result                                 | void    | 读取存储                                          |
| storage_put       | key, value                                  | void    | 写入存储                                          |
| storage_delete    | key                                         | void    | 删除存储                                          |
| contract_create   | code, vmtype,name,version,author,email,desc | address | 创建合约                                          |
| contract_migrate  | code, vmtype,name,version,author,email,desc | address | 迁移(升级)合约                                    |
| contract_delete   | address                                     | void    | 删除合约                                          |
|                   |                                             |         |                                                   |

下面我们通过一个更加复杂的例子来演示如何通过这些API来开发一个完整的Wasm 智能合约.

### 红包合约

我们都会经常发红包,通过微信等聊天工具,我们可以给朋友发送红包,你收到的钱会记入到你的微信账户中,

类似于微信的流程,我们将尝试创建一个智能合约, 你可以发送一个ont , ong或者是标准的OEP4的token资产红包给你的朋友们,而他们抢到的红包可以直接转入到他们的钱包账户中.

#### 1. 创建合约

```cpp
#include<ontiolib/ontio.hpp>

using namespace ontio;

class redEnvlope: public contract{
    
}
ONTIO_DISPATCH(redEnvlope, (createRedEnvlope)(queryEnvlope)(claimEnvlope));
```

首先,我们需要新建合约的源文件,暂且命名为redEnvlope.cpp

这个合约我们需要三个接口:

```createRedEnvlope```  : 创建红包

```queryEnvlope``` : 查询红包信息

```claimEnvlope``` :抢红包



```cpp
    std::string rePrefix = "RE_PREFIX_";
    std::string sentPrefix = "SENT_COUNT_";
    std::string claimPrefix = "CLAIM_PREFIX_";
```

在合约中,我们需要在存储中保存一些关键的数据,并且为这些数据的**KEY** 设置前缀以便于后面的查询



```cpp
    address ONTAddress = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
    address ONGAddress = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2};
```

因为我们的合约支持ONT 和ONG这两种ontology的原生资产, 我们可以预先定义好这两种资产的合约地址

**Note**: 不同于标准的智能合约, 原生合约(native contract)的合约地址是固定,而不是根据合约代码的hash计算而来

```cpp
    struct receiveRecord{
        address account;   //用户地址
        asset amount;      //抢到的金额  
        ONTLIB_SERIALIZE(receiveRecord,(account)(amount))
    };

    struct envlopeStruct{
        address tokenAddress;   //资产token的地址
        asset totalAmount;      //红包总金额
        asset totalPackageCount; //红包总数
        asset remainAmount;      //当前剩余的金额
        asset remainPackageCount; //当前剩余的红包数
        std::vector<struct receiveRecord> records;  //已经抢完的记录
        ONTLIB_SERIALIZE( envlopeStruct,  (tokenAddress)(totalAmount)(totalPackageCount)(remainAmount)(remainPackageCount)(records) )
    };
```

我们需要在合约中保存红包的信息, 如红包的资产信息(token的合约地址, 红包的总金额, 红包的个数等等),

**Note** : 

```
ONTLIB_SERIALIZE(receiveRecord,(account)(amount))
```

是由cdt 定义的宏操作,用于在将struct存储前进行序列化的操作. 

准备工作差不多了,下面我们开始开发具体的接口逻辑.

#### 2. 创建红包

```cpp
bool createRedEnvlope(address owner,asset packcount, asset amount,address tokenAddr ){

        return true;
    }
```

1. 创建红包需要指定创建者地址, 红包数量, 红包金额和资产的合约地址

```cpp
ontio_assert(check_witness(owner),"checkwitness failed");
```

2. 检查是否有创建者的签名, 否则交易回滚退出

   **NOTE**: ontio_assert(expr, errormsg)：当expr 为false时, 抛出异常并退出.

```cpp
		if (isONTToken(tokenAddr)){
            ontio_assert(amount >= packcount,"ont amount should greater than 		packcount");
        }
```

3. 如果是红包资产是ONT的时候,由于ONT的不可分割性(最小为1个ONT), 红包的金额要大于或等于红包的数量,保证每个红包最少有1个ONT.

```cpp
        key sentkey = make_key(sentPrefix,owner.tohexstring());
        asset sentcount = 0;
        storage_get(sentkey,sentcount);
        sentcount += 1;
        storage_put(sentkey,sentcount);
```

4. 对于每个红包的创建者,我们需要记录一下他发送红包的总数量.

```cpp
        H256 hash ;

        hash256(make_key(owner,sentcount),hash) ;

        key rekey = make_key(rePrefix,hash256ToHexstring(hash));
```

5. 生成红包hash, 这个hash 就是之后标识这个红包的ID



```cpp
	 	address selfaddr = self_address();
		if (isONTToken(tokenAddr)){

            bool result = ont::transfer(owner,selfaddr ,amount);
            ontio_assert(result,"transfer native token failed!");
           
        }else if (isONGToken(tokenAddr)){

            bool result = ong::transfer(owner,selfaddr ,amount);
            ontio_assert(result,"transfer native token failed!");
        }else{
            std::vector<char> params = pack(std::string("transfer"),owner,selfaddr,amount);
            bool res; 
            call_contract(tokenAddr,params, res );

            ontio_assert(res,"transfer oep4 token failed!");
        }
```

6. 根据token资产的类型,将资产转入合约中.

```cpp
		struct envlopeStruct es ;
        es.tokenAddress = tokenAddr;
        es.totalAmount = amount;
        es.totalPackageCount = packcount;
        es.remainAmount = amount;
        es.remainPackageCount = packcount;
        es.records = {};
        storage_put(rekey, es);
```

7. 将合约的信息保存在存储中

```cpp
        char buffer [100];
        sprintf(buffer, "{\"states\":[\"%s\", \"%s\", \"%s\"]}","createEnvlope",owner.tohexstring().c_str(),hash256ToHexstring(hash).c_str());

        notify(buffer);
        return true;
```

8. 发送创建红包的事件

一个简单的红包就创建完成了, 下一步我们需要实现如何查询这个红包的信息.

#### 2. 查询红包

```cpp
   std::string queryEnvlope(std::string hash){
        key rekey = make_key(rePrefix,hash);
        struct envlopeStruct es;
        storage_get(rekey,es);
        return formatEnvlope(es);
    }
```

查询红包的逻辑非常简单, 只需要将存储中的红包信息取出并格式化返回即可.

最后,其他的用户可以根据hash(红包的ID)来领取(抢)这个红包了.



#### 3. 领取红包

```cpp
  bool claimEnvlope(address account, std::string hash){
  	return true;
  }
```

1. 领取红包需要输入领取人的账户, 和红包的hash.

```cpp
ontio_assert(check_witness(account),"checkwitness failed");
key claimkey = make_key(claimPrefix,hash,account);
asset claimed = 0 ;
storage_get(claimkey,claimed);
ontio_assert(claimed == 0,"you have claimed this envlope!");
```

2. 同样, 我们需要验证领取账户的签名, 不允许替其他人抢红包, 而且每个账户每个红包智能抢一次.

```cpp
        key rekey = make_key(rePrefix,hash);
        struct envlopeStruct es;
        storage_get(rekey,es);
        ontio_assert(es.remainAmount > 0, "the envlope has been claimed over!");
        ontio_assert(es.remainPackageCount > 0, "the envlope has been claimed over!");
```

3. 按照hash从存储中取出红包的信息, 判断这个红包是否没有被抢完.

```cpp
        struct receiveRecord record ;
        record.account = account;
        asset claimAmount = 0;
```

4. 新建一条领取的记录

```cpp
		if (es.remainPackageCount == 1){
            claimAmount = es.remainAmount;
            record.amount = claimAmount;
        }else{
            H256 random = current_blockhash() ;
            char part[8];
            memcpy(part,&random,8);
            uint64_t random_num = *(uint64_t*)part;
            uint32_t percent = random_num % 100 + 1;

            claimAmount = es.remainAmount * percent / 100;
            //ont case
            if (claimAmount == 0){
                claimAmount = 1;
            }else if(isONTToken(es.tokenAddress)){
                if ( (es.remainAmount - claimAmount) < (es.remainPackageCount - 1)){
                    claimAmount = es.remainAmount - es.remainPackageCount + 1;
                }
            }

            record.amount = claimAmount;
        }
        es.remainAmount -= claimAmount;
        es.remainPackageCount -= 1;
        es.records.push_back(record);
```

5. 计算本次领取红包的资产数量, 如果是最后一个红包, 数量为剩余的金额, 否则根据当前区块hash计算随机数,确定本次领取的数量, 并更新红包信息.



```cpp
        address selfaddr = self_address();
        if (isONTToken(es.tokenAddress)){
            bool result = ont::transfer(selfaddr,account ,claimAmount);
            ontio_assert(result,"transfer ont token failed!");
        } else  if (isONGToken(es.tokenAddress)){
            bool result = ong::transfer(selfaddr,account ,claimAmount);
            ontio_assert(result,"transfer ong token failed!");
        } else{
            std::vector<char> params = pack(std::string("transfer"),selfaddr,account,claimAmount);

            bool res = false; 
            call_contract(es.tokenAddress,params, res );
            ontio_assert(res,"transfer oep4 token failed!");
        }
```

6. 根据计算结果, 将对应资产从合约中转到领取的账户.



```cpp
        storage_put(claimkey,claimAmount);
        storage_put(rekey,es);
        char buffer [100];        
        std::sprintf(buffer, "{\"states\":[\"%s\",\"%s\",\"%s\",\"%lld\"]}","claimEnvlope",hash.c_str(),account.tohexstring().c_str(),claimAmount);

        notify(buffer);
        return true;
```

7. 记录领取的信息, 将更新后的红包信息写回存储并发送通知事件.

至此, 一个简单的红包合约逻辑完成, 完整的合约代码如下:

```cpp
#include<ontiolib/ontio.hpp>
#include<ontiolib/base58.hpp>
#include <string>

using namespace ontio;

class redEnvlope: public contract{
    std::string rePrefix = "RE_PREFIX_";
    std::string sentPrefix = "SENT_COUNT_";
    std::string claimPrefix = "CLAIM_PREFIX_";
    address ONTAddress = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
    address ONGAddress = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2};


    struct receiveRecord{
        address account;
        asset amount;
        ONTLIB_SERIALIZE(receiveRecord,(account)(amount))
    };

    struct envlopeStruct{
        address tokenAddress;
        asset totalAmount;
        asset totalPackageCount;
        asset remainAmount;
        asset remainPackageCount;
        std::vector<struct receiveRecord> records;
        ONTLIB_SERIALIZE( envlopeStruct,  (tokenAddress)(totalAmount)(totalPackageCount)(remainAmount)(remainPackageCount)(records) )
    };

    public:
    using contract::contract;

    /*
    *   createRedEnvlope
    *   owner    : creator address
    *   packcount: count of the envlope
    *   amount   : total amount of the envlope
    *   tokenAddr: token address
    * */
    bool createRedEnvlope(address owner,asset packcount, asset amount,address tokenAddr ){
        //check the owner rights
        ontio_assert(check_witness(owner),"checkwitness failed");
        if (isONTToken(tokenAddr)){
            ontio_assert(amount >= packcount,"ont amount should greater than packcount");
        }

        key sentkey = make_key(sentPrefix,owner.tohexstring());
        asset sentcount = 0;
        storage_get(sentkey,sentcount);
        sentcount += 1;
        storage_put(sentkey,sentcount);

        H256 hash ;

        hash256(make_key(owner,sentcount),hash) ;

        key rekey = make_key(rePrefix,hash256ToHexstring(hash));
        address selfaddr = self_address();

        //determin the token type
        if (isONTToken(tokenAddr)){

            bool result = ont::transfer(owner,selfaddr ,amount);
            ontio_assert(result,"transfer native token failed!");
           
        }else if (isONGToken(tokenAddr)){

            bool result = ong::transfer(owner,selfaddr ,amount);
            ontio_assert(result,"transfer native token failed!");
        }else{
            std::vector<char> params = pack(std::string("transfer"),owner,selfaddr,amount);
            bool res; 
            call_contract(tokenAddr,params, res );

            ontio_assert(res,"transfer oep4 token failed!");
        }
        struct envlopeStruct es ;
        es.tokenAddress = tokenAddr;
        es.totalAmount = amount;
        es.totalPackageCount = packcount;
        es.remainAmount = amount;
        es.remainPackageCount = packcount;
        es.records = {};
        storage_put(rekey, es);

        char buffer [100];
        sprintf(buffer, "{\"states\":[\"%s\", \"%s\", \"%s\"]}","createEnvlope",owner.tohexstring().c_str(),hash256ToHexstring(hash).c_str());

        notify(buffer);
        return true;

    }

    /*
    * queryEnvlope
    * hash   : envlope hash
    * return : json
    **/

    std::string queryEnvlope(std::string hash){
        key rekey = make_key(rePrefix,hash);
        struct envlopeStruct es;
        storage_get(rekey,es);
        return formatEnvlope(es);
    }

    /*
    * claimEnvlope  
    * account : claimer account
    * hash : envlope hash
    * */
    bool claimEnvlope(address account, std::string hash){
        ontio_assert(check_witness(account),"checkwitness failed");
        key claimkey = make_key(claimPrefix,hash,account);
        asset claimed = 0 ;
        storage_get(claimkey,claimed);
        ontio_assert(claimed == 0,"you have claimed this envlope!");

        key rekey = make_key(rePrefix,hash);
        struct envlopeStruct es;
        storage_get(rekey,es);
        ontio_assert(es.remainAmount > 0, "the envlope has been claimed over!");
        ontio_assert(es.remainPackageCount > 0, "the envlope has been claimed over!");
        // std::vector<struct receiveRecord> records = es.records;
        struct receiveRecord record ;
        record.account = account;
        asset claimAmount = 0;

        if (es.remainPackageCount == 1){
            claimAmount = es.remainAmount;
            record.amount = claimAmount;
        }else{
            H256 random = current_blockhash() ;
            char part[8];
            memcpy(part,&random,8);
            uint64_t random_num = *(uint64_t*)part;
            uint32_t percent = random_num % 100 + 1;

            claimAmount = es.remainAmount * percent / 100;
            //ont case
            if (claimAmount == 0){
                claimAmount = 1;
            }else if(isONTToken(es.tokenAddress)){
                if ( (es.remainAmount - claimAmount) < (es.remainPackageCount - 1)){
                    claimAmount = es.remainAmount - es.remainPackageCount + 1;
                }
            }

            record.amount = claimAmount;

        }
        es.remainAmount -= claimAmount;
        es.remainPackageCount -= 1;
        es.records.push_back(record);

        address selfaddr = self_address();
        if (isONTToken(es.tokenAddress)){
            bool result = ont::transfer(selfaddr,account ,claimAmount);
            ontio_assert(result,"transfer ont token failed!");
        } else  if (isONGToken(es.tokenAddress)){
            bool result = ong::transfer(selfaddr,account ,claimAmount);
            ontio_assert(result,"transfer ong token failed!");
        } else{
            std::vector<char> params = pack(std::string("transfer"),selfaddr,account,claimAmount);

            bool res = false; 
            call_contract(es.tokenAddress,params, res );
            ontio_assert(res,"transfer oep4 token failed!");
        }
        storage_put(claimkey,claimAmount);
        storage_put(rekey,es);
        char buffer [100];        
        std::sprintf(buffer, "{\"states\":[\"%s\",\"%s\",\"%s\",\"%lld\"]}","claimEnvlope",hash.c_str(),account.tohexstring().c_str(),claimAmount);

        notify(buffer);
        return true;
    }
    
    private:
    bool isONGToken(address tokenAddr){
        return  tokenAddr == ONGAddress ;
    }
    bool isONTToken(address tokenAddr){
        return tokenAddr == ONTAddress ;
    }
    std::string hash256ToHexstring(H256 hash){
        std::string s;
        
		s.resize(64);
		int index = 0;
		for(auto it:hash) {
			uint8_t high = it/16, low = it%16;
			s[index] = (high<10) ? ('0' + high) : ('a' + high - 10);
			s[index + 1] = (low<10) ? ('0' + low) : ('a' + low - 10);
			index += 2;
		}
		return s;
    }

    std::string formatEnvlope(struct envlopeStruct es){
        char buf[100];
        std::vector<struct receiveRecord> records = es.records;
        std::sprintf(buf,"{\"tokenAddress\":\"%s\",\"totalAmount\":%lld,\"totalPackageAmount\":%lld,\"remainAmount\":%lld,\"remainPackageAmount\":%lld,\"claimers\":[",es.tokenAddress.tohexstring().c_str(),es.totalAmount,es.totalPackageCount,es.remainAmount,es.remainPackageCount);
        std::string s;
        if ( records.size() > 0){
            int i = 0;
            for (auto r :records){
                s += formatRecord(r);
                i++;
                if (i < records.size()){
                    s += ",";
                }
            }
        }
        s += "]}";
        std::string ss(buf);
        return ss +s;

    }

    std::string formatRecord(struct receiveRecord record){

        char buf[100] ;
        std::sprintf(buf,"{\"account\":\"%s\",\"amount\":%lld}",record.account.tohexstring().c_str(),record.amount);
        std::string s(buf);
        return s;
    }
};

ONTIO_DISPATCH(redEnvlope, (createRedEnvlope)(queryEnvlope)(claimEnvlope));

```



### 测试合约

1. 使用CLI

请参考: <https://github.com/ontio/ontology-wasm-cdt-cpp/blob/master/How_To_Run_ontologywasm_node.md>



2. 使用golang sdk

请参考:<https://github.com/ontio/ontology-wasm-cdt-cpp/blob/master/example/other/main.go>



本示例只是为了展示如何编写一个完整的ontology wasm 智能合约, 如何通过调用API和底层的区块链进行交互,如果要作为正式的产品, 还需要解决红包的隐私问题: 所有人都可以通过监控合约的事件来取得红包的hash, 意味着每个人都可以抢这个红包, 这个问题通过在创建红包时指定哪些账户能够领取来解决, 如果有兴趣, 您也可以尝试修改测试一下.



