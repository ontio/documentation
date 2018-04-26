# Wasm Smart Contract

## Introduction
wasm (WebAssembly),是基于堆栈的虚拟机的二进制指令格式。Wasm被设计为可编译C/C++/Rust等高级语言的可移植目标，支持在Web上为客户端和服务器应用程序进行部署。 Ontology支持 wasm 格式编写的智能合约。

![WASM](https://raw.githubusercontent.com/ontio/documentation/master/smart-contract-tutorial/images/WASM.png)

## 编译

1. 首先我们准备一个简单的c 语言的合约，计算两个整数之和或连接两个字符串。

```c
void ONT_JsonUnmashalInput(void * addr,int size,char * arg);
char * ONT_JsonMashalResult(void * val,char * types,int succeed);
int strcmp(char *a,char *b);
int arrayLen(void *a);
void * malloc(int size);
int ONT_ReadInt32Param(char *args);
char * ONT_ReadStringParam(char * args);
void ONT_Runtime_Notify(char * address);

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

char * invoke(char * method,char * args){

        if (strcmp(method ,"init")==0 ){
                return "init success!";
        }

        if (strcmp(method, "add")==0){
                int a = ONT_ReadInt32Param(args);
                int b = ONT_ReadInt32Param(args);
                int res = add(a,b);
                char * result = ONT_JsonMashalResult(res,"int",1);
                ONT_Runtime_Notify(result);
                return result;
        }

	if(strcmp(method,"concat")==0){
		
		char * a = ONT_ReadStringParam(args);
		char * b = ONT_ReadStringParam(args);
		char * res = concat(a,b);
		char * result = ONT_JsonMashalResult(res,"string",1);
        ONT_Runtime_Notify(result);
		return result;
	}
	
}


```

下列函数为虚拟机的提供的API,需要在文件头部声明
```c
void ONT_JsonUnmashalInput(void * addr,int size,char * arg);
char * ONT_JsonMashalResult(void * val,char * types,int succeed);
int strcmp(char *a,char *b);
int arrayLen(void *a);
void * malloc(int size);
int ONT_ReadInt32Param(char *args);
char * ONT_ReadStringParam(char * args);
void ONT_Runtime_Notify(char * address);

```

ONT 的WASM 合约入口统一为```char * invoke(char * method,char * args)``` 。

**method** 为需要调用的方法名 

**args**  为传入参数，raw bytes

API ```int strcmp(char *a,char *b)``` ：字符串比较函数，可以用来判断需要调用的方法名

API ```char * ONT_JsonMashalResult(void * val,char * types)``` : 可以把结果序列化为Json格式





2. 把上面的C 文件编译成wasm格式的智能合约。
    * 可以使用Emscripten 工具 [http://kripken.github.io/emscripten-site/](http://http://kripken.github.io/emscripten-site/)
    * 使用在线编译器 WasmFiddle [https://wasdk.github.io/WasmFiddle](https://wasdk.github.io/WasmFiddle)

    使用WasmFiddle为例

    将C代码粘贴到"c"的编辑窗口内，请忽律"JS"窗口的内容，点击 "Build" 按钮，如果编译正确，可以在"Text Format"窗口中看到编译好的wast格式代码，如果编译错误，会在"output"窗口显示错误信息。

    ![fiddle](https://raw.githubusercontent.com/ontio/documentation/master/smart-contract-tutorial/images/fiddle.png)

    如果熟悉[wast语法](http://webassembly.org/docs/binary-encoding/)，您可以自行修改wast文件，

    并使用[wabt](https://github.com/WebAssembly/wabt)工具将wast 文件编译成wasm格式。

3. 点击"wasm"按钮，下载编译后的wasm 文件


### 使用Json格式传递参数

传入参数可以为Json格式：

```c
void ONT_JsonUnmashalInput(void * addr,int size,char * arg);
char * ONT_JsonMashalResult(void * val,char * types,int succeed);
int strcmp(char *a,char *b);
int arrayLen(void *a);
void * malloc(int size);
void ONT_Runtime_Notify(char * address);

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
                struct Params *param=(struct Param *)malloc(sizeof(struct Params));

                ONT_JsonUnmashalInput(param,sizeof(param),args);
                int res = add(param.a,param.b);
                char * result = ONT_JsonMashalResult(res,"int",1);
            	ONT_Runtime_Notify(result);
                return result;
        }

        if(strcmp(method,"concat")==0){
                struct Params{
                        char *a;
                        char *b;
                };
                struct Params param;
                struct Params *param=(struct Param *)malloc(sizeof(struct Param));
                ONT_JsonUnmashalInput(param,sizeof(param),args);
                char * res = concat(param.a,param.b);
                char * result = ONT_JsonMashalResult(res,"string",1);
            	ONT_Runtime_Notify(result);
                return result;
        }

        if(strcmp(method,"sumArray")==0){
                struct Params{
                        int *a;
                        int *b;
                };
                struct Params param;
                JsonUnmashal(param,sizeof(param),args);
                struct Params *param=(struct Param *)malloc(sizeof(struct Param));
                int res = sumArray(param.a,param.b);
                char * result = ONT_JsonMashalResult(res,"int",1);
            	ONT_Runtime_Notify(result);
                return result;
        }

}
                                                                                                                                      
```

本例新增了API ：
```c
void ONT_JsonUnmashalInput(void * addr,int size,char * arg);
```

API ```void ONT_JsonUnmashalInput(void * addr,int size,char * arg)``` ：可以把json格式的参数解析为定义的结构体。

编译和下载wasm文件的方式同上。

### 取得wasm文件的二进制内容
可以使用在线工具[http://tomeko.net/online_tools/file_to_hex.php?lang=en](http://tomeko.net/online_tools/file_to_hex.php?lang=en)
![hexadecimal](https://raw.githubusercontent.com/ontio/documentation/master/smart-contract-tutorial/images/hexadecimal.png)

## 部署合约



## 调用合约

