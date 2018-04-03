void RuntimeNotify(char * message);
char * ReadStringParam(char *addr);
char * CallContract(char * address,char * method,char * args);
char * RawMashalParams(void * arg);
void * malloc(int size);
int strcmp(char *a,char *b);

char * invoke(char * method,char * args){

        if (strcmp(method ,"init")==0 ){
                return "init success!";
        }

        if (strcmp(method, "getValue")==0){

		struct Param{
			char * ptype;
			char * pvalue;
		};
		char * key = ReadStringParam(args);
		struct Param * newargs = (struct Param *)malloc(sizeof(struct Param));                

		newargs -> ptype = "string";
		newargs -> pvalue = key;

		char * res = CallContract("90ca57034b30a3fe0da266c20b337ed2a0aa47a6","getStorage",RawMashalParams(newargs));
               
                RuntimeNotify(res);
		return res;
        }
	if (strcmp(method,"putValue") == 0){
		
		struct Param{
                        char * ptype;
                        char * pvalue;
                };
                char * key = ReadStringParam(args);
		char * value = ReadStringParam(args);

                struct Param * newargs = (struct Param *)malloc(sizeof(struct Param)*2);

		newargs[0].ptype = "string";
		newargs[0].pvalue = key;

		newargs[1].ptype = "string";
		newargs[1].pvalue = value;

		char * res = CallContract("90ca57034b30a3fe0da266c20b337ed2a0aa47a6","addStorage",RawMashalParams(newargs));
		RuntimeNotify(res);
                return res;

	}
}
