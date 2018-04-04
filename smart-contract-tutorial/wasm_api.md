# Ontology Wasm API list

Ontology wasm VM provides several APIs for developers 

## system

system APIs provides basic operations

| Name              | Parameters                         | Returns | Description                                                  |
| ----------------- | ---------------------------------- | ------- | ------------------------------------------------------------ |
| calloc            | int num,int size                   | void *  | like standard c library, calloc function  allocates num * size memorys and initialize with byte '0', return the address (offset) in memory |
| malloc            | int size                           | void *  | like standard c library, calloc function allocates num * size memorys without any initialize  return the address (offset) in memory |
| strcmp            | char * src,char * dest             | int     | compile two strings ,return 0 if they are the same           |
| arrayLen          | void *                             | int     | return an array(byte,int,int64) length                       |
| memcpy            | void * src,void * dest, int length | void    | copy 'length' specified block memory from 'src' to 'dest'    |
| ReadInt32Param    | char *                             | int     | read int parameter from input                                |
| ReadInt64Param    | char *                             | int     | read int64(long long) parameter from input                   |
| ReadStringParam   | char *                             | char *  | read string (char *) parameter from input                    |
| JsonUnmashalInput | char *                             | void    | unmashal input into specified struct                         |
| JsonMashalResult  | void * result,char * type          | char *  | mashal result to json format string ``` {"type":"string","value":"samplestring"}``` |
| JsonMashalParams  | void *                             | char *  | mashal struct to json format string ,for call other wasm contract |
| rawMashalParams   | void *                             | char *  | mashal struct to raw string ,for call other wasm contract    |
| GetCallerAddress  |                                    | char *  | return caller address                                        |
| GetSelfAddress    |                                    | char *  | return self address                                          |

## Ledger

Ledger APIs provides the abilities to  access blockchain ledger

| Name          | Parameters              | Returns | Description                                |
| ------------- | ----------------------- | ------- | ------------------------------------------ |
| PutStorage    | char * key,char * value | void    | put the key-value pair into ledger storage |
| GetStorage    | char * key              | char *  | get the storage by input key               |
| DeleteStorage | char * key              | void    | delete the storage by input key            |

## BlockChain

BlockChain APIs provides the abilities to  access blockchain attributes.

| Name                 | Parameters | Returns | Description                             |
| -------------------- | ---------- | ------- | --------------------------------------- |
| GetBlockHeight       |            | int     | return current blockchain height        |
| GetBlockHashByNumber | int number | char *  | return block hash by input block number |
| GetTimeStamp         |            | int     | return current block timestamp          |

## Other
To be add more APIs here

| Name             | Parameters                                                   | Returns | Description                                                  |
| ---------------- | ------------------------------------------------------------ | ------- | ------------------------------------------------------------ |
| CheckWitness     | char * address                                               | int     | return 1 if the address is valid                             |
| RuntimeNotify    | char * content                                               | void    | add notification to SDK or other clients                     |
| CallContract     | char * address,char * method,char * parameters,char * isOffchian | char *  | call other contract,first parameter could be the contract address or byte code with Hex format and the last parameter should be "true" or "false" according to the "address" case |
| ContractLogDebug | char * message                                               | void    | add debug log                                                |
| ContractLogInfo  | char * message                                               | void    | add info log                                                 |
| ContractLogError | char * message                                               | void    | add error log                                                |


