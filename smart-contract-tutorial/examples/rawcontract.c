void JsonUnmashal(void * addr,int size,char * arg);
char * JsonMashal(void * val,char * types);
int strcmp(char *a,char *b);
int arrayLen(char *a);
void * malloc(int size);
int ReadInt32Param(char *addr);
char * ReadStringParam(char *addr);

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
               // struct Params {
               //         int a;
               //         int b;
               // };
               // struct Params param;

                //JsonUnmashal(&param,sizeof(param),args);
                
		int a = ReadInt32Param(args);
		int b = ReadInt32Param(args);
		int res = add(a,b);
                char * result = JsonMashal(res,"int");
                return result;
        }

	if(strcmp(method,"concat")==0){
		
		char * a = ReadStringParam(args);
		char * b = ReadStringParam(args);
		char * res = concat(a,b);
		char * result = JsonMashal(res,"string");
		return result;
	}
	
	if(strcmp(method,"sumArray")==0){
		struct Params{
			int *a;
			int *b;
		};
		struct Params param;
		JsonUnmashal(&param,sizeof(param),args);
		int res = sumArray(param.a,param.b);
		char * result = JsonMashal(res,"int");
		return result;
	}

}
	
