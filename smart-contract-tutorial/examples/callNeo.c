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
int * ONT_Block_GetTransactionCount(char * data);
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

char * invoke(char * method,char * args){

    if (strcmp(method,"putValue")== 0){
        struct Params{
            char * key;
            char * value;
        };
        struct Params * p = (struct Params *)malloc(sizeof(struct Params));
        ONT_JsonUnmashalInput(p,sizeof(struct Params),args);

        struct NeoArgs{
            char * ptype;
            char * pvalue;
        };

        struct NeoArgs * arg = (struct NeoArgs *)malloc(sizeof(struct NeoArgs) * 2);
        arg[0].ptype = "string";
        arg[0].pvalue = p->key;
        
        arg[1].ptype = "string";
        arg[1].pvalue = p->value;
        char * result = ONT_CallContract("80f6bff7645a84298a1a52aa3745f84dba6615cf","","Put",ONT_MarshalNeoParams(arg));
        char * res = ONT_JsonMashalResult(result,"string",1);
        ContractLogError(res);
        ONT_Runtime_Notify(res);
        return res;
    }
    if(strcmp(method,"getValue"==0)){
        struct Params{
            char * key;
        };
        struct Params * p = (struct Params *)malloc(sizeof(struct Params));
        ONT_JsonUnmashalInput(p,sizeof(struct Params),args);
        struct NeoArgs{
            char * ptype;
            char * pvalue;
        };

        struct NeoArgs * arg = (struct NeoArgs *)malloc(sizeof(struct NeoArgs));
        arg[0].ptype = "string";
        arg[0].pvalue = p->key;

        char * result = ONT_CallContract("80f6bff7645a84298a1a52aa3745f84dba6615cf","","Get",ONT_MarshalNeoParams(arg));
        char * res = ONT_JsonMashalResult(result,"string",1);
        ContractLogError(res);
        ONT_Runtime_Notify(res);
        return res;
    }

}
