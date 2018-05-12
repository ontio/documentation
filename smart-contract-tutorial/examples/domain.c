//system apis
void * calloc(int count,int length);
void * malloc(int size);
int arrayLen(void *a);
int memcpy(void * dest,void * src,int length);
int memset(void * dest,char c,int length);

//utility apis
int strcmp(char *a,char *b);
char * strconcat(char *a,char *b);
int Atoi(char * s);
long long Atoi64(char *s);
char * Itoa(int a);
char * I64toa(long long amount,int radix);
char * SHA1(char *s);
char * SHA256(char *s);

//parameter apis
int ONT_ReadInt32Param(char *args);
long long ONT_ReadInt64Param(char * args);
char * ONT_ReadStringParam(char * args);
void ONT_JsonUnmashalInput(void * addr,int size,char * arg);
char * ONT_JsonMashalResult(void * val,char * types,int succeed);
char * ONT_JsonMashalParams(void * s);
char * ONT_RawMashalParams(void *s);
char * ONT_GetCallerAddress();
char * ONT_GetSelfAddress();
char * ONT_CallContract(char * address,char * contractCode,char * method,char * args);
char * ONT_MarshalNativeParams(void * s);
char * ONT_MarshalNeoParams(void * s);

//Runtime apis
int ONT_Runtime_CheckWitness(char * address);
void ONT_Runtime_Notify(char * address);
int ONT_Runtime_CheckSig(char * pubkey,char * data,char * sig);
int ONT_Runtime_GetTime();
void ONT_Runtime_Log(char * message);

//Attribute apis
int ONT_Attribute_GetUsage(char * data);
char * ONT_Attribute_GetData(char * data);

//Block apis
char * ONT_Block_GetCurrentHeaderHash();
int ONT_Block_GetCurrentHeaderHeight();
char * ONT_Block_GetCurrentBlockHash();
int ONT_Block_GetCurrentBlockHeight();
char * ONT_Block_GetTransactionByHash(char * hash);
int * ONT_Block_GetTransactionCountByBlkHash(char * hash);
int * ONT_Block_GetTransactionCountByBlkHeight(int height);
char ** ONT_Block_GetTransactionsByBlkHash(char * hash);
char ** ONT_Block_GetTransactionsByBlkHeight(int height);


//Blockchain apis
int ONT_BlockChain_GetHeight();
char * ONT_BlockChain_GetHeaderByHeight(int height);
char * ONT_BlockChain_GetHeaderByHash(char * hash);
char * ONT_BlockChain_GetBlockByHeight(int height);
char * ONT_BlockChain_GetBlockByHash(char * hash);
char * ONT_BlockChain_GetContract(char * address);

//header apis
char * ONT_Header_GetHash(char * data);
int ONT_Header_GetVersion(char * data);
char * ONT_Header_GetPrevHash(char * data);
char * ONT_Header_GetMerkleRoot(char  * data);
int ONT_Header_GetIndex(char * data);
int ONT_Header_GetTimestamp(char * data);
long long ONT_Header_GetConsensusData(char * data);
char * ONT_Header_GetNextConsensus(char * data);

//storage apis
void ONT_Storage_Put(char * key,char * value);
char * ONT_Storage_Get(char * key);
void ONT_Storage_Delete(char * key);

//transaction apis
char * ONT_Transaction_GetHash(char * data);
int ONT_Transaction_GetType(char * data);
char * ONT_Transaction_GetAttributes(char * data);

//for debug only
void ContractLogDebug(char * msg);
void ContractLogInfo(char * msg);
void ContractLogError(char * msg);

//contract code below
char * registe(char *address,char * domain){
    if (arrayLen(domain) == 0) {
        return ONT_JsonMashalResult("empty domain not allowed","string",0);
    }

    char * occupy = ONT_Storage_Get(domain);
    if (arrayLen(occupy) > 0){
        return ONT_JsonMashalResult(strconcat(domain," has already registed!"),"string",0);
    } else{
        ONT_Storage_Put(domain,address);
        return ONT_JsonMashalResult(strconcat(domain," register succeed!"),"string",1);
    }
}

char * query(char * domain){
    char * address = ONT_Storage_Get(domain);
    return address;
}

int transfer(char * from ,char * to,char * domain){
    char * selfaddress = ONT_GetSelfAddress();
    if((strcmp(selfaddress,from) != 0)&&(ONT_Runtime_CheckWitness(from) == 0)){
        return 0;
    }

    char * address = ONT_Storage_Get(domain);
    if (strcmp(address,from) != 0){
        return 0;
    }else{
        ONT_Storage_Put(domain,to);
        return 1;
    }
}

int delete(char * from,char * domain){
    if(ONT_Runtime_CheckWitness(from) == 0){
        return ONT_JsonMashalResult(strconcat(from," right check failed!"),"string",0);
    }
    char * address = ONT_Storage_Get(domain);
    if (strcmp(address,from) != 0){
        return 0;
    }else{
        ONT_Storage_Delete(domain);
        return 1;
    }
}

int transOnt(char * from ,char * to,long long amount){

    struct State{
            int ver;
            char * from;
            char * to ;
            long long amount;
        };

    struct Transfer {
        int ver;
        struct State * states
    };


    struct State * state = (struct State*)malloc(sizeof(struct State));
    state->ver = 1;
    state->amount = amount;
    state->from = from;
    state->to = to;

    struct Transfer * transfer =(struct Transfer*)malloc(sizeof(struct Transfer));
    transfer->ver = 1;
    transfer->states = state;

    char * args = ONT_MarshalNativeParams(transfer);
    char * result = ONT_CallContract("ff00000000000000000000000000000000000001","","transfer",args);
    if (strcmp(result,"true")==0){
        return 1;
    }else{
        return 0;
    }
}

int sell(char * owner,char * domain,long long basePrice){
    if(ONT_Runtime_CheckWitness(owner) == 0){
        return 0;
    }
    char * address = ONT_Storage_Get(domain);
    if (strcmp(address,owner) != 0){
        return 0;
    }else{
        int transResult = transfer(owner,ONT_GetSelfAddress(),domain);
        if (transResult > 0){
            ONT_Storage_Put(strconcat("ORIGIN_OWNER_",domain),owner);
            ONT_Storage_Put(strconcat("PRICE_",domain),I64toa(basePrice,10));
            return 1;
        }else{
            return 0;
        }
    }
}

int buy(char * buyer,char * domain,long long price){
    char * owner = ONT_Storage_Get(domain);
    char * self = ONT_GetSelfAddress();
    if (strcmp(owner,self)==0){
        long long currentprice = Atoi64(ONT_Storage_Get(strconcat("PRICE_",domain)));
        if(price > currentprice){
            int res = transOnt(buyer,self,price);
            if (res == 0){
                return 0;
            }

            char * oldbuyer = ONT_Storage_Get(strconcat("BUYER_",domain));
            if (arrayLen(oldbuyer) > 0 && currentprice > 0){
                res = transOnt(self,oldbuyer,currentprice);
                if (res == 0){
                    //exception case
                    ONT_Runtime_Notify(strconcat(strconcat(oldbuyer,I64toa(currentprice,10))," refund failed"));
                }
            }

            ONT_Storage_Put(strconcat("PRICE_",domain),I64toa(price,10));
            ONT_Storage_Put(strconcat("BUYER_",domain),buyer);
            return 1;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

long long getCurrentPrice(char * domain){
    char *price =  ONT_Storage_Get(strconcat("PRICE_",domain));
    if(arrayLen(price)==0){
        return 0;
    }else{
        return Atoi64(price);
    }
}

int deal(char * owner,char * domain){
    if(ONT_Runtime_CheckWitness(owner) == 0){
        return 0;
    }
    char * address = ONT_Storage_Get(strconcat("ORIGIN_OWNER_",domain));
    if (strcmp(address,owner) != 0){
        return 0;
    }else{
        long long currentprice = Atoi64(ONT_Storage_Get(strconcat("PRICE_",domain)));
        char * buyer =  ONT_Storage_Get(strconcat("BUYER_",domain));
        char * selfAddr = ONT_GetSelfAddress();
        int res = transOnt(selfAddr,owner,currentprice);
        if (res == 0){
            return 0;
        }else{
            res = transfer(selfAddr,buyer,domain);
            if(res == 0){
                return 0;
            }
            ONT_Storage_Delete(strconcat("BUYER_",domain));
            ONT_Storage_Delete(strconcat("ORIGIN_OWNER_",domain));
            ONT_Storage_Delete(strconcat("PRICE_",domain));
            return 1;
        }
    }
}

/*
*this is the common standard interface of ontology wasm contract
*/
char * invoke(char * method,char * args){

    if(strcmp(method,"register") == 0){

        struct Params{
            char *address;
            char *domain;
        };
        struct Params * p = (struct Params *)malloc(sizeof(struct Params));
        ONT_JsonUnmashalInput(p,sizeof(struct Params),args);

        char * result = registe(p->address,p->domain);
        ONT_Runtime_Notify(result);
        return result;
    }

    if(strcmp(method,"query") == 0){
        struct Params{
            char *domain;
        };
        struct Params * p = (struct Params *)malloc(sizeof(struct Params));
        ONT_JsonUnmashalInput(p,sizeof(struct Params),args);
        char * result = query(p->domain);
        char *str;
        if (arrayLen(result) == 0 ){
            str = ONT_JsonMashalResult(strconcat(result, " has not been registed!"),"string",0);
        }else{
            str = ONT_JsonMashalResult(result,"string",1);
        }
        ONT_Runtime_Notify(str);
        return str;
    }

    if(strcmp(method,"transfer") == 0){
        struct Params{
            char * from;
            char * to;
            char *domain;
        };
        struct Params * p = (struct Params *)malloc(sizeof(struct Params));
        ONT_JsonUnmashalInput(p,sizeof(struct Params),args);
        char * str;
        char * selfAddress = ONT_GetCallerAddress();
        if(strcmp(selfAddress,p->from)==0){
            str = ONT_JsonMashalResult(strconcat(p->from," is not allowed!"),"string","0");
        }else{
            int result = transfer(p->from,p->to,p->domain);
            if (result > 0){
                str = ONT_JsonMashalResult(strconcat(p->from," does not have the domain!"),"string",0);
            }else{
                str = ONT_JsonMashalResult(strconcat(p->domain, " transfered succeed!"),"string",1);
            }
        }
        ONT_Runtime_Notify(str);
        return str;
    }

    if(strcmp(method,"delete") == 0){
        struct Params{
            char * from;
            char *domain;
        };
        struct Params * p = (struct Params *)malloc(sizeof(struct Params));
        ONT_JsonUnmashalInput(p,sizeof(struct Params),args);
        int result = delete(p->from,p->domain);
        char * str;
        if (result > 0) {
            str = ONT_JsonMashalResult(strconcat(p->domain, " delete succeed!"),"string",1);

        }else{
            str = ONT_JsonMashalResult(strconcat(p->from," does not have the domain!"),"string",0);
        }
        ONT_Runtime_Notify(str);
        return str;
    }

    if(strcmp(method,"sell") == 0){
        struct Params{
            char * from;
            char * domain;
            long long basePrice;
        };
        struct Params * p = (struct Params *)malloc(sizeof(struct Params));
        ONT_JsonUnmashalInput(p,sizeof(struct Params),args);
        int sellres = sell(p->from,p->domain,p->basePrice);
        char * res;
        if (sellres){
            res = ONT_JsonMashalResult(strconcat(p->domain," sell succeed!"),"string",1);
        }else{
            res = ONT_JsonMashalResult(strconcat(p->domain," sell failed!"),"string",0);
        }
        ONT_Runtime_Notify(res);
        return res;
    }

    if(strcmp(method,"buy") == 0){
        struct Params{
            char * from;
            char * domain;
            long long price;
        };
        struct Params * p = (struct Params *)malloc(sizeof(struct Params));
        ONT_JsonUnmashalInput(p,sizeof(struct Params),args);
        int sellres = buy(p->from,p->domain,p->price);
        char * res;
        if (sellres){
            res = ONT_JsonMashalResult(strconcat(p->domain," buy succeed!"),"string",1);
        }else{
            res = ONT_JsonMashalResult(strconcat(p->domain," buy failed!"),"string",0);
        }
        ONT_Runtime_Notify(res);
        return res;
    }

     if(strcmp(method,"deal") == 0){
        struct Params{
            char * owner;
            char * domain;
        };
        struct Params * p = (struct Params *)malloc(sizeof(struct Params));
        ONT_JsonUnmashalInput(p,sizeof(struct Params),args);
        int sellres = deal(p->owner,p->domain);
        char * res;
        if (sellres == 1){
            res = ONT_JsonMashalResult(strconcat(p->domain," deal succeed!"),"string",1);
        }else{
            res = ONT_JsonMashalResult(strconcat(p->domain," deal failed!"),"string",0);
        }
        ONT_Runtime_Notify(res);
        return res;
    }

     if(strcmp(method,"currentPrice") == 0){
        struct Params{
            char * domain;
        };
        struct Params * p = (struct Params *)malloc(sizeof(struct Params));
        ONT_JsonUnmashalInput(p,sizeof(struct Params),args);
        long long price = getCurrentPrice(p->domain);
        char * res = ONT_JsonMashalResult(price,"int64",1);
        ONT_Runtime_Notify(res);
        return res;
    }

    char * s =  ONT_JsonMashalResult(strconcat(method," not allowed"),"string",0);
    ONT_Runtime_Notify(s);
    return s;
}
