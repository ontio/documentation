# Ontology Wasm API List

Ontology Wasm VM provides several APIs for developers .

## System APIs

System APIs provide basic operations.

| Name              | Parameters                         | Returns | Description                                                  |
| ----------------- | ---------------------------------- | ------- | ------------------------------------------------------------ |
| calloc            | int num, int size                   | void *  | Like standard c library, calloc function  allocates num * size memorys and initialize with byte '0', return the address (offset) in memory |
| malloc            | int size                           | void *  | Like standard c library, calloc function allocates num * size memorys without any initialize  return the address (offset) in memory |
| arrayLen    | void * s     | int  | Return an array (byte, int, int64) length |
| memcpy    | void * src, void * dest, int length | void | Copy 'length' specified block memory from 'src' to 'dest' |
| memset     | void * dest, char c, int length | int | set memory to char |

## Utility APIs

| Name      | Parameters              | Returns   | Description                                        |
| --------- | ----------------------- | --------- | -------------------------------------------------- |
| strcmp    | char * src, char * dest | int       | Compare two strings, return 0 if they are the same |
| strconcat | char * array            | char *    | concat strings to one string                       |
| Atoi      | char * s                | int       | convert string to  int32                           |
| Atoi64    | char * s                | long long | convert string to int64                            |
| Itoa      | int a                   | char *    | convert int32 to string                            |
| I64toa    | long long a,int radix   | char *    | convert int64 to string                            |
| SHA1      | char * s                | char *    | hash string with SHA1                              |
| SHA256    | char * s                | char *    | hash string with SHA256                            |



## Parameter APIs

| Name                    | Parameters                                                   | Returns   | Description                                      |
| ----------------------- | ------------------------------------------------------------ | --------- | ------------------------------------------------ |
| ONT_ReadInt32Param      | char * args                                                  | int       | read int parameter from input                    |
| ONT_ReadInt64Param      | char * args                                                  | long long | read int64 parameter from input                  |
| ONT_ReadStringParam     | char * args                                                  | char *    | read string parameter from input                 |
| ONT_JsonUnmashalInput   | void * addr,int size,char * args                             | void      | unmarshal json format input into struct          |
| ONT_JsonMashalResult    | void * val,char * type,int succeed                           | char *    | marshal json format string to return.            |
| ONT_JsonMashalParams    | void * s                                                     | char *    | marshal json format parameter to (wasm) contract |
| ONT_RawMashalParams     | void * s                                                     | char *    | marshal raw format parameter to (wasm) contract  |
| ONT_GetCallerAddress    |                                                              | char *    | get caller address                               |
| ONT_GetSelfAddress      |                                                              | char *    | get  self contract address                       |
| ONT_CallContract        | char * address,char * contractCode,char * method,char * args | char *    | call other contract                              |
| ONT_MarshalNativeParams | void * s                                                     | char *    | marshal parameter for(native) contract           |

to call Native contract , we need to pass the ```struct Transfer *``` to **MarshalNativeParams** to get the marshaled parameter string

```
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

```

## 

## Runtime APIs

| Name                     | Parameters                           | Returns | Description                                                  |
| ------------------------ | ------------------------------------ | ------- | ------------------------------------------------------------ |
| ONT_Runtime_CheckWitness | char * address                       | int     | check the witness of the given address. 0:  failed; 1:passed |
| ONT_Runtime_Notify       | char * message                       | void    | add notification                                             |
| ONT_Runtime_CheckSig     | char * pubkey,char * data,char * sig | int     | check signature. 0 :failed,1 :passed                         |
| ONT_Runtime_GetTime      |                                      | int     | get runtime  time                                            |
| ONT_Runtime_Log          | char * message                       | void    | add log                                                      |



## Attribute APIs

| Name                   | Parameters  | Returns | Description         |
| ---------------------- | ----------- | ------- | ------------------- |
| ONT_Attribute_GetUsage | char * data | int     | get attribute usage |
| ONT_Attribute_GetData  | char * data | char *  | get attribute data  |



## Block APIs

| Name                             | Parameters  | Returns | Description                  |
| -------------------------------- | ----------- | ------- | ---------------------------- |
| ONT_Block_GetCurrentHeaderHash   |             | char *  | get current header hash      |
| ONT_Block_GetCurrentHeaderHeight |             | int     | get current header height    |
| ONT_Block_GetCurrentBlockHash    |             | char *  | get current block hash       |
| ONT_Block_GetCurrentBlockHeight  |             | int     | get current block height     |
| ONT_Block_GetTransactionByHash   | char * hash | char *  | get transaction by hash      |
| ONT_Block_GetTransactionCount    | char * data | int     | get block transactions count |
| ONT_Block_GetTransactions        | char * data | char *  | get block transactions       |



## Blockchain APIs

| Name                             | Parameters     | Returns | Description             |
| -------------------------------- | -------------- | ------- | ----------------------- |
| ONT_BlockChain_GetHeight         |                | int     | get blockchain height   |
| ONT_BlockChain_GetHeaderByHeight | int height     | char *  | get header by height    |
| ONT_BlockChain_GetHeaderByHash   | char * hash    | char *  | get header by hash      |
| ONT_BlockChain_GetBlockByHeight  | int height     | char *  | get block by height     |
| ONT_BlockChain_GetBlockByHash    | char * hash    | char *  | get block by hash       |
| ONT_BlockChain_GetContract       | char * address | char *  | get contract by address |



## Header APIs

| Name                        | Parameters  | Returns   | Description          |
| --------------------------- | ----------- | --------- | -------------------- |
| ONT_Header_GetHash          | char * data | char *    | get header hash      |
| ONT_Header_GetVersion       | char * data | int       | get header version   |
| ONT_Header_GetPrevHash      | char * data | char *    | get previous hash    |
| ONT_Header_GetMerkleRoot    | char * data | char *    | get merkletree root  |
| ONT_Header_GetIndex         | char * data | int       | get header height    |
| ONT_Header_GetTimestamp     | char * data | int       | get header timestamp |
| ONT_Header_GetConsensusData | char * data | long long | get consensus data   |
| ONT_Header_GetNextConsensus | char * data | char *    | get next consensus   |



## Storage APIs

| Name               | Parameters              | Returns | Description                     |
| ------------------ | ----------------------- | ------- | ------------------------------- |
| ONT_Storage_Put    | char * key,char * value | void    | put key-value pair into storage |
| ONT_Storage_Get    | char * key              | char *  | get value by input key          |
| ONT_Storage_Delete | char *key               | void    | delete value by input key       |



## Transaction APIs

| Name                          | Parameters  | Returns | Description                |
| ----------------------------- | ----------- | ------- | -------------------------- |
| ONT_Transaction_GetHash       | char * data | char *  | get transaction hash       |
| ONT_Transaction_GetType       | char * data | int     | get transaction type       |
| ONT_Transaction_GetAttributes | char * data | char *  | get transaction attributes |



## 


