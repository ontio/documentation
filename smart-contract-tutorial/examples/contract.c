void JsonUnmashalInput(void * addr,int size,char * arg);
char * JsonMashalResult(void * val,char * types);
int strcmp(char *a,char *b);
int arrayLen(char *a);
void * malloc(int size);
void RuntimeNotify(char * message);
void PutStorage(char * key,char *value);
char * GetStorage(char * key);
void DeleteStorage(char * key);


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
		res[lenb + j] = b[j];
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
                struct Params param;

                JsonUnmashalInput(&param,sizeof(param),args);
                int res = add(param.a,param.b);
                char * result = JsonMashalResult(res,"int");
                RuntimeNotify(result);
		return result;
        }

	if(strcmp(method,"concat")==0){
		struct Params{
			char *a;
			char *b;
		};
		struct Params param;
		JsonUnmashalInput(&param,sizeof(param),args);
		char * res = concat(param.a,param.b);
		char * result = JsonMashalResult(res,"string");
		RuntimeNotify(result);
		return result;
	}
	
	if(strcmp(method,"sumArray")==0){
		struct Params{
			int *a;
			int *b;
		};
		struct Params param;
		JsonUnmashalInput(&param,sizeof(param),args);
		int res = sumArray(param.a,param.b);
		char * result = JsonMashalResult(res,"int");
		RuntimeNotify(result);
		return result;
	}

	if(strcmp(method,"addStorage")==0){

		struct Params{
			char * a;
			char * b;
		};
		struct Params param;
		JsonUnmashalInput(&param,sizeof(param),args);
		PutStorage(param.a,param.b);
		char * result = JsonMashalResult("Done","string");
		RuntimeNotify(result);
		return result;
        }
	if(strcmp(method,"getStorage")==0){

		struct Params{
			char * a;
		};
		struct Params param;
		JsonUnmashalInput(&param,sizeof(param),args);
		char * value = GetStorage(param.a);
		char * result = JsonMashalResult(value,"string");
		RuntimeNotify(result);
		return result;
	}
	if(strcmp(method,"deleteStorage")==0){

                struct Params{
                        char * a;
                };
                struct Params param;
                JsonUnmashalInput(&param,sizeof(param),args);
                DeleteStorage(param.a);
                char * result = JsonMashalResult("Done","string");
                RuntimeNotify(result);
                return result;
        }
}
		
