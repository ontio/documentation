//system apis
void * calloc(int count,int length);
void * malloc(int size);
int arrayLen(void *a);
int memcpy(void * dest,void * src,int length);
int memset(void * dest,char c,int length);

//utility apis
int strcmp(char *a,char *b);
void * strconcat(char *a,char *b);
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
char * ONT_MarshalNativeParams(void *);

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
char * ONT_Block_GetTransactionCount(int count);
char * ONT_Block_GetTransactions(char * data);

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
    if (arrayLen(address) == 0 ){
        return ONT_JsonMashalResult(strconcat(domain, " has not been registed!"),"string",0);
    }else{
        return ONT_JsonMashalResult(address,"string",1);
    }
}

char * transfer(char * from ,char * to,char * domain){
    if(ONT_Runtime_CheckWitness(from) == 0){
        return ONT_JsonMashalResult(strconcat(from," right check failed!"),"string",0);
    }

    char * address = ONT_Storage_Get(domain);
    if (strcmp(address,from) != 0){
        return ONT_JsonMashalResult(strconcat(from," does not have the domain!"),"string",0);
    }else{
        ONT_Storage_Put(domain,to);
        return ONT_JsonMashalResult(strconcat(domain, " transfered succeed!"),"string",1);
    }
}

char * delete(char * from,char * domain){
    if(ONT_Runtime_CheckWitness(from) == 0){
        return ONT_JsonMashalResult(strconcat(from," right check failed!"),"string",0);
    }
    char * address = ONT_Storage_Get(domain);
    if (strcmp(address,from) != 0){
        return ONT_JsonMashalResult(strconcat(from," does not have the domain!"),"string",0);
    }else{
        ONT_Storage_Delete(domain);
        return ONT_JsonMashalResult(strconcat(domain, " delete succeed!"),"string",1);
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
        ONT_Runtime_Notify(result);
        return result;
    }

    if(strcmp(method,"transfer") == 0){
        struct Params{
            char * from;
            char * to;
            char *domain;
        };
        struct Params * p = (struct Params *)malloc(sizeof(struct Params));
        ONT_JsonUnmashalInput(p,sizeof(struct Params),args);
        char * result = transfer(p->from,p->to,p->domain);
        ONT_Runtime_Notify(result);
        return result;
    }

    if(strcmp(method,"delete") == 0){
        struct Params{
            char * from;
            char *domain;
        };
        struct Params * p = (struct Params *)malloc(sizeof(struct Params));
        ONT_JsonUnmashalInput(p,sizeof(struct Params),args);
        char * result = delete(p->from,p->domain);
        ONT_Runtime_Notify(result);
        return result;
    }

    char * s =  ONT_JsonMashalResult(strconcat(method," not allowed"),"string",0);
    ONT_Runtime_Notify(s);
    return s;
}