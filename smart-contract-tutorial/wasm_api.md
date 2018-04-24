# Ontology Wasm API List

Ontology Wasm VM provides several APIs for developers .

## System

System APIs provide basic operations.

| Name              | Parameters                         | Returns | Description                                                  |
| ----------------- | ---------------------------------- | ------- | ------------------------------------------------------------ |
| calloc            | int num, int size                   | void *  | Like standard c library, calloc function  allocates num * size memorys and initialize with byte '0', return the address (offset) in memory |
| malloc            | int size                           | void *  | Like standard c library, calloc function allocates num * size memorys without any initialize  return the address (offset) in memory |
| strcmp            | char * src, char * dest             | int     | Compile two strings, return 0 if they are the same           |
| arrayLen          | void *                             | int     | Return an array (byte, int, int64) length                       |
| memcpy            | void * src, void * dest, int length | void    | Copy 'length' specified block memory from 'src' to 'dest'    |
| ReadInt32Param    | char *                             | int     | Read int parameter from input                                |
| ReadInt64Param    | char *                             | int     | Read int64 (long long) parameter from input                   |
| ReadStringParam   | char *                             | char *  | Read string (char *) parameter from input                    |
| JsonUnmashalInput | char *                             | void    | Unmashal input into specified struct                         |
| JsonMashalResult  | void * result, char * type          | char *  | Mashal result to json format string ``` {"type":"string","value":"samplestring"}``` |
| JsonMashalParams  | void *                             | char *  | Mashal struct to json format string, for call other wasm contract |
| RawMashalParams  | void *                             | char *  | Mashal struct to raw string, for call other wasm contract    |
| GetCallerAddress  |                                    | char *  | Return caller address                                        |
| Atoi | char * | int | convert string to  int32 |
| Atoi64 | char * | long long | convert string to int64 |
| Itoa | int | char * | convert int32 to string |
| I64toa | long long | char * | convert int64 to string |
| MarshalNativeParams | void * | char * | convert Transfer  struct to string (*1) |
|  | |  |  |

*1:to call Native contract , we need to pass the ```struct Transfer *``` to **MarshalNativeParams** to get the marshaled parameter string

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







## Ledger

Ledger APIs provide the ability to access the blockchain ledger.

| Name          | Parameters              | Returns | Description                                |
| ------------- | ----------------------- | ------- | ------------------------------------------ |
| PutStorage    | char * key, char * value | void    | Put the key-value pair into the ledger storage |
| GetStorage    | char * key              | char *  | Get the storage by input key               |
| DeleteStorage | char * key              | void    | Delete the storage by input key            |

## BlockChain

BlockChain APIs provide the ability to access blockchain attributes.

| Name                 | Parameters | Returns | Description                             |
| -------------------- | ---------- | ------- | --------------------------------------- |
| GetBlockHeight       |            | int     | Return current blockchain height        |
| GetBlockHashByNumber | int number | char *  | Return block hash by input block number |
| GetTimeStamp         |            | int     | Return current block timestamp          |

## Other

More APIs are added here.

| Name             | Parameters                                                   | Returns | Description                              |
| ---------------- | ------------------------------------------------------------ | ------- | ---------------------------------------- |
| CheckWitness     | char * address                                               | int     | Return 1 if the address is valid         |
| RuntimeNotify    | char * content                                               | void    | Add notification to SDK or other clients |
| CallContract     | char * address, char * code, char * methodname, char * parameters | char *  | Call other contract                      |
| ContractLogDebug | char * message                                               | void    | Add debug log                            |
| ContractLogInfo  | char * message                                               | void    | Add info log                             |
| ContractLogError | char * message                                               | void    | Add error log                            |

