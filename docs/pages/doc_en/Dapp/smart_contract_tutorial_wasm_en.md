---
title: 
keywords: sample homepage
sidebar: Dapp_en
permalink: smart_contract_tutorial_wasm_en.html
folder: doc_en
---

English / [中文](./smart_contract_tutorial_wasm_zh.html)


<h1 align="center">WASM-VM Brief Introduction</h1>
<p align="center" class="version">Version 0.7.0 </p>

## What is Wasm?

WebAssembly (Wasm) is a virtual machine based on a binary operation stack structure. Wasm can be compiled into machine code and can execute the local methods and hardware faster and more efficiently. Through cooperation with JS, front-end can achieve faster and more complex calculations and applications.



![wasm1](lib/images/wasm1.png)



It can not only be applied to web applications by embedding in browsers, but can also be applied to other scenarios.

Wasm supports advanced language programming, and the current mature compiler supports C, C++, and Rust.



## WebAssembly work principle

WebAssembly is an assembly language that does not depend on a specific physical machine.  It can be understood as a conceptual machine language rather than an actual physical machine language. Therefore, WebAssembly instruction can be called virtual instruction, and can be faster and more directly mapped to the machine code!

![wasm2](lib/images/wasm2.jpg)



## Compiling source code to a .wasm file

At present, the best compiler tool for supporting WebAssembly is LLVM. There are many different front-end and back-end plug-ins that can be used in LLVM.

The developer can choose C, C++, Rust language, and other open-source code, and compile it in WebAssembly, or directly use the text format WebAssembly (wast) to develop directly.

The Emscripten tool can be used to compile WebAssembly. It converts the code into its own intermediate code (asm.js) through its own back-end, which is then converted into WebAssembly, which still actually uses LLVM.

![wasm2](lib/images/wasm3.png)

## Implementing a WebAssembly virtual machine

At present, WebAssembly is mainly for web applications, and the container is implemented mostly in mainstream browsers, and communicates with the outside world with JavaScript. However, its features are based on custom memory and sandboxes, which also makes it easily applicable to some lightweight scenarios, such as for virtual machines that perform smart contracts with blockchain. 

WebAssembly is based on a stack of virtual machines, and the instructions execution is  completed in the stack.

![wasm4](lib/images/wasm4.png)

For WebAssembly Instructions please refer to [webAssembly bianry code](https://github.com/ontio/ontology-wasm/blob/master/doc/wasm_binarycode.md )

WebAssembly can support four basic types:：

- int32

- int64

- float32

- float64

Therefore the function's parameters and return values can only be these four types, and each function can only have one return value.

If you want to use complex types, such as string, you need to perform additional operations on memory.

### Initialize memory

In the current WebAssembly MVP version, each module can own a linear memory (Linear Memory), and the size of memory is x * pages. Each page is fixed to 64K Bytes. Linear memory is essentially an untyped Byte array, and this array does not have any association with the actual memory of the physical machine, so the executed wWsm program in the sandbox will not affect the external.byte.

Data has saved some initialized information, such as constant string.

```c
char * hello(){
  return "hello world!";
}
```

The wast file after compiling (using Fiddle) is:

```wast
(module
 (table 0 anyfunc)
 (memory $0 1)
 (data (i32.const 16) "hello world!\00")
 (export "memory" (memory $0))
 (export "hello" (func $hello))
 (func $hello (; 0 ;) (result i32)
  (i32.const 16)
 )
)

```

We can see:

1. The module uses 1 page of memory, which is 64KB
2.  In the data field, the “hello world!"  string is initialized to the memory that begins at 16 offset memory.
3. The return value of hello() is the first address (offset) of the string in the memory, and exports the memory out.

Thus, the external call can find the array that begins from the offset and ends with ”\00" in the memory by returned ```i32.const 16```, which is “ hello world!". 

If we want to pass in a string parameter, how should the memory be used?

```c
char * hello(char * name){
  return concat("hello " ,name);
}
```

Modify the code, pass in the parameter name, and use concat to connect the string. The compiled wast code is:

```
(module
 (type $FUNCSIG$i (func (result i32)))
 (type $FUNCSIG$iii (func (param i32 i32) (result i32)))
 (import "env" "concat" (func $concat (param i32 i32) (result i32)))
 (table 0 anyfunc)
 (memory $0 1)
 (data (i32.const 16) "hello \00")
 (export "memory" (memory $0))
 (export "hello" (func $hello))
 (func $hello (; 1 ;) (param $0 i32) (result i32)
  (call $concat
   (i32.const 16)
   (get_local $0)
  )
 )
)

```

We can see the parameter type passed in is still i32, and that is the address of the string, and the constant string is still in the memory where the offset is 16.

```(import "env" "concat" (func $concat (param i32 i32) (result i32)))``` Since we do not implement the concat function in this module, the compiler will automatically recognize it as an external function (see the external function section).

If the parameter we pass in is "Alice", we need to set "Alice" in the memory of export before calling function hello and passing the address (offset) in Wasm.

The problem is: how to set the incoming string into the memory?

In the browser environment, it can be set directly by JavaScript. The use of WebAssembly in the browser environment will not be discussed in this article. Similar to JavaScript, memory is a []byte that can be exposed in the ontology-wasm vm, so that we can convert the parameter string to []byte and copy it to memory []byte, passing in the first address into the WebAssembly function. If it is a string returned by the WebAssembly function, we can also get the actual string in the memory based on the returned address.

You can already use WebAssembly VM, but there are still some problems:

1. The initialization position in the memory of different compilers to the constant string is not the same. For example, Fiddle starts with 16, and Emscripten is specified by the memoryBase passed in the global parameter.

2. Complex types, such as struct:

   ```c
   struct Example {
       char * name;
       char * gender;
       int age;
   };
   struct Example * p;
   ```

    When we need to use struct in the above example, we need to allocate corresponding memory:

   ![memory1](lib/images/memory1.png)





### Memory management

Since what WebAssembly VM uses is not the real physical memory, it needs us to realize ```malloc``` and ```calloc```, and realize the allocation and management of the virtual machine memory  (as the executor of smart contract, ontology-wasm does need long time continuous operation, so ```free()``` operation has not been added. If needed, the memory can be increased by adjusting the pages of memory).

We divide the memory into three zones:

![memory](lib/images/memory.png)

1. Const Area: Save initiated constant, from index 16, the address 0 is identified as NULL.

2. Basic Area: Save basic types of data.

3. Complex Area: Save complex types of data, such as struct, array, etc.

   ​

Every time we allocate memory, we need to record the information we allocate:

```go
MemPoints       map[uint64]*TypeLength
```

```go
const (
	PInt8 PType = iota
	PInt16
	PInt32
	PInt64
	PFloat32
	PFloat64
	PString
	PStruct
	PUnkown
)

type TypeLength struct {
	Ptype  PType
	Length int
}

```

key is the memory address of this allocation, and value is the allocation type and the total length of allocated memory, thus we can easily obtain information of the actual corresponding value according to the memory address.



### External functions

WebAssembly supports the introduction of other WebAssembly modules to call the functions. You only need to specify the path of the module to be called. If the function called in this module does not have a specific implementation, it is considered to be imported from env by default.

Thus we can conveniently call native by registering the function env, for example:

```
(import "env" "concat" (func $concat (param i32 i32) (result i32)))
```

We can easily use Golang to implement this concat method. Take two strings from the memory to make up new strings and assign them to the memory and press the resulting address into the execution stack.

To see the basic operations ontology-wasm vm, please refer to [Ontology Wasm API list](https://github.com/ontio/documentation/blob/master/smart-contract-tutorial/wasm_api.md).



At this point, we can implement a simple blocked-based smart contract execution virtual machine based on WebAssembly. With updates in WebAssembly standards we will continue to update this file.