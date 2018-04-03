void RuntimeNotify(char * message);
void JsonUnmashalInput(void * addr,int size,char * arg);
char * CallContract(char * address,char * method,char * args);
char * JsonMashalParams(void * arg);
void * malloc(int size);
int strcmp(char *a,char *b);

char * invoke(char * method,char * args){

        if (strcmp(method ,"init")==0 ){
                return "init success!";
        }

        if (strcmp(method, "getValue")==0){

		struct Input{
			char * key;
		};
		struct Input input;
		JsonUnmashalInput(&input,sizeof(input),args);

		struct Param{
			char * ptype;
			char * pvalue;
		};
		struct Param * newargs = (struct Param *)malloc(sizeof(struct Param));                

		newargs -> ptype = "string";
		newargs -> pvalue = input.key;

		char * res = CallContract("9007be541a1aef3d566aa219a74ef16e71644715","getStorage",JsonMashalParams(newargs));
               
                RuntimeNotify(res);
		return res;
        }
	if (strcmp(method,"putValue") == 0){
		
		struct Input{
                        char * key;
			char * value;
                };
                struct Input input;
                JsonUnmashalInput(&input,sizeof(input),args);


		struct Param{
                        char * ptype;
                        char * pvalue;
                };

                struct Param * newargs = (struct Param *)malloc(sizeof(struct Param)*2);

		newargs[0].ptype = "string";
		newargs[0].pvalue = input.key;

		newargs[1].ptype = "string";
		newargs[1].pvalue = input.value;

		char * res = CallContract("9007be541a1aef3d566aa219a74ef16e71644715","addStorage",JsonMashalParams(newargs));
		RuntimeNotify(res);
                return res;

	}
}
