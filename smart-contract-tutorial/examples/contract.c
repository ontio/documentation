
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

int add(int a, int b ){
        return a + b;
}

char * concat(char * a, char * b){
	int lena = arrayLen(a);
	int lenb = arrayLen(b);
	char * res = (char *)malloc((lena + lenb)*sizeof(char));
	for (int i = 0 ;i < lena ;i++){
		res[i] = a[i];
	}

	for (int j = 0; j < lenb ;j++){
		res[lena + j] = b[j];
	}
	return res;
}


int sumArray(int * a, int * b){

	int res = 0;
	int lena = arrayLen(a);
	int lenb = arrayLen(b);

	for (int i = 0;i<lena;i++){
		res += a[i];
	}
	for (int j = 0;j<lenb;j++){
		res += b[j];
	}
	return res;
}


char * invoke(char * method,char * args){

    if (strcmp(method ,"init")==0 ){
            return "init success!";
    }

    if (strcmp(method, "add")==0){
        struct Params {
                int a;
                int b;
        };
        struct Params *p = (struct Params *)malloc(sizeof(struct Params));

        ONT_JsonUnmashalInput(p,sizeof(struct Params),args);
        int res = add(p->a,p->b);
        char * result = ONT_JsonMashalResult(res,"int",1);
        ONT_Runtime_Notify(result);
        return result;
    }

	if(strcmp(method,"concat")==0){
		struct Params{
			char *a;
			char *b;
		};
		struct Params *p = (struct Params *)malloc(sizeof(struct Params));
		ONT_JsonUnmashalInput(p,sizeof(struct Params),args);
		char * res = concat(p->a,p->b);
		char * result = ONT_JsonMashalResult(res,"string",1);
		ONT_Runtime_Notify(result);
		return result;
	}
	
	if(strcmp(method,"sumArray")==0){
		struct Params{
			int *a;
			int *b;
		};
		struct Params *p = (struct Params *)malloc(sizeof(struct Params));
		ONT_JsonUnmashalInput(p,sizeof(struct Params),args);
		int res = sumArray(p->a,p->b);
		char * result = ONT_JsonMashalResult(res,"int",1);
		ONT_Runtime_Notify(result);
		return result;
	}

	if(strcmp(method,"addStorage")==0){

		struct Params{
			char * a;
			char * b;
		};
		struct Params *p = (struct Params *)malloc(sizeof(struct Params));
		ONT_JsonUnmashalInput(p,sizeof(struct Params),args);
		ONT_Storage_Put(p->a,p->b);
		char * result = ONT_JsonMashalResult("Done","string",1);
		ONT_Runtime_Notify(result);
		return result;
    }

	if(strcmp(method,"getStorage")==0){
		struct Params{
			char * a;
		};
		struct Params *p = (struct Params *)malloc(sizeof(struct Params));
		ONT_JsonUnmashalInput(p,sizeof(struct Params),args);
		char * value = ONT_Storage_Get(p->a);
		char * result = ONT_JsonMashalResult(value,"string",1);
		ONT_Runtime_Notify(result);
		return result;
	}

	if(strcmp(method,"deleteStorage")==0){

        struct Params{
                char * a;
        };
		struct Params *p = (struct Params *)malloc(sizeof(struct Params));
		ONT_JsonUnmashalInput(p,sizeof(struct Params),args);
        ONT_Storage_Delete(p->a);
        char * result = ONT_JsonMashalResult("Done","string",1);
        ONT_Runtime_Notify(result);
        return result;
    }
}
