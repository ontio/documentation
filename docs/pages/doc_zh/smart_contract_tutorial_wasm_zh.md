---
title: 
keywords: sample homepage
sidebar: ont_doc_zh
permalink: smart_contract_tutorial_wasm_zh.html
folder: doc_zh
---

[English](./smart_contract_tutorial_wasm_en.html) / 中文

<h1 align="center">WASM-VM 简介</h1>
<p align="center" class="version">版本 0.7.0 </p>


## 什么是wasm

WebAssembly(wasm) 是一个基于二进制操作指令的栈式结构的虚拟机，wasm可以被编译为机器码，可以更快，更高效的执行本地方法和硬件资源，通过和js协作，前端可以实现更快，更复杂的计算和应用。



![wasm1](lib/images/wasm1.png)



不仅可以嵌入浏览器增强web应用，也可以应用于其他的场景。

wasm 支持高级语言编程，目前比较成熟的编译器支持C \ C++ \Rust。



## WebAssembly的工作原理

WebAssembly 是一种不依赖于具体物理机器的汇编语言，可以抽象的理解成它是概念的机器语言，而不是实际的物理机器语言，因此，WebAssembly 指令也可称为虚拟指令，可以更快的更直接的映射的到机器码!

![wasm2](lib/images/wasm2.jpg)



## 编译源码到.wasm 文件

目前对于 WebAssembly 支持情况最好的编译器工具链是 LLVM。有很多不同的前端和后端插件可以用在 LLVM 上。

开发者可以选择 C \ C++ 或Rust语言等开发源代码，再编译成WebAssembly，或者直接使用文本格式的WebAssembly（wast）直接开发。

可以使用 Emscripten 工具来编译WebAssembly，它通过自己的后端先吧代码转换成自己的中间代码(asm.js)， 然后再转换成 WebAssembly ,实际上它背后也是使用的LLVM。

![wasm2](lib/images/wasm3.png)

## 实现一个WebAssembly虚拟机

现阶段，WebAssembly 主要还是以Web应用为主，执行的容器大多基于主流的浏览器，并且通过javascript与外部通信，但是它的基于自定义内存和沙盒的特性，也使得WebAssembly 可以很好的适用于一些轻量级的场景，如作为执行区块链智能合约的虚拟机。

WebAssembly 是基于栈式的虚拟机，指令的执行都是在栈内完成的：

![wasm4](lib/images/wasm4.png)

webAssembly 指令集参考：[webAssembly bianry code](wasm_binarycode.md )

WebAssembly 只支持4种基本类型：

- int32

- int64

- float32

- float64

所以函数的参数和返回值也只能是这四种类型，并且每个函数只能有一个返回值。

如果想要使用复杂的类型，比如 string，就需要额外对内存进行操作。

### 初始化内存

当前的 WebAssembly MVP版本，每一个module至多可以拥有一个线性内存(Linear Memory)，内存的大小为x * pages， 每页固定为64K Bytes，线性内存本质上就是一个无类型的byte数组，这个数组和物理机的实际内存不存在任何关联，所以在沙盒内的执行的wasm程序不会对外部产生影响。

Data段保存了一些初始化的信息，比如常量字符串。

```c
char * hello(){
  return "hello world!";
}
```

编译（使用Fiddle)后的wast文件为：

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

可以看到：

1. 本module 使用了 1页的内存 即64KB
2. 在data 段中，“hello world!" 字符串被初始化到偏移量为16开始的内存中
3. hello() 的返回值为字符串在内存中的首地址（偏移量），并且将内存 export出来。

这样，外部的调用就可以通过返回的```i32.const 16```，在内存中找到以偏移量16开始，”\00"结束的 byte 数组，即为“hello world!"。

如果我们想传入一个字符串参数，内存又该如何使用？

```c
char * hello(char * name){
  return concat("hello " ,name);
}
```

修改代码，传入参数name，并使用concat做字符串连接，编译后的wast代码为：

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

可以看到，传入的参数类型仍然是i32，即字符串的地址，常量字符串仍然在偏移量为16开始的内存中。

```(import "env" "concat" (func $concat (param i32 i32) (result i32)))``` 因为我们没有在本模块中实现concat函数，编译器自动将其识别为外部函数（参见外部函数部分）。

假如我们的传入参数为 "Alice",则我们需要在调用hello函数之前，将 "Alice"设置在export 的内存中，并将其地址(偏移量)传入到wasm中。

问题是：如何将传入的字符串设置到内存中？

在浏览器环境下，可以通过JavaScript直接设置，本文不讨论关于WebAssembly在浏览器环境下的使用，类似于Javascript，在ontology-wasm vm中内存是一个可以暴露出来的[]byte，这样我们就可以把参数的字符串转换成[]byte并拷贝到内存[]byte中，并将首地址传入WebAssembly函数，如果是WebAssembly 函数返回的字符串，我们同样可以根据返回的地址在内存中得到实际的字符串。

现在看起来我们已经可以使用这个WebAssembly VM了，但是仍然存在一些问题：

1. 不同的编译器对常量字符串在内存中的初始化位置并不相同：如Fiddle是从16开始，而 Emscripten由memoryBase这个传入的global 参数指定。

2. 复杂的类型，如struct

   ```c
   struct Example {
       char * name;
       char * gender;
       int age;
   };
   struct Example * p;
   ```

   当我们需要使用上例的struct 时，就需要为它分配相应的内存：

   ![memory1](lib/images/memory1.png)





### 管理内存

由于WebAssembly VM使用的并不是真正的物理内存，需要我们自己来实现```malloc```和```calloc```实现对虚拟机内存的分配和管理（ontology-wasm 作为智能合约的执行器，并不需要长时间的持续运行，所以暂时没有加入```free()```操作，如果有需要，通过调整内存的页数来增大内存）。

我们将内存分成3个区域：

![memory](lib/images/memory.png)

1. Const Area：保存初始化的常量，从index 16开始，地址0作为NULL的标识。

2. Basic Area ：保存基本类型的数据

3. Complex Area ：保存复杂类型数据，如struct, array 等。

   ​

每次分配内存后，我们需要记录本次分配的信息：

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

key 为本次分配的内存地址，value为本次分配的类型和分配内存的总长度 ，这样我们就可以很容易的根据内存地址来得到实际对应的值的信息。



### 外部函数

WebAssembly支持引入其他的WebAssembly 模块以调用其中的函数，只需要指定需要调用模块路径即可，如果在本模块内调用的函数并没有具体的实现，就会默认的被认为是从 env中导入。

这样，我们就可以通过注册env 的函数来方便的调用native 方法， 如：

```
(import "env" "concat" (func $concat (param i32 i32) (result i32)))
```

我们就可以很方便的以golang来实现这个concat方法，从内存中取得两个字符串，拼接成新的字符串并为其分配和放入内存中，再将结果的地址压入执行栈中。

ontology-wasm vm 实现了一些基本的操作，请参考 [Ontology Wasm API list](https://github.com/ontio/documentation/blob/master/smart-contract-tutorial/wasm_api.md)



至此，我们就可以实现一个简单的基于WebAssembly的区块链智能合约执行虚拟机，随着WebAssembly标准的更新，我们也会持续为ontology wasmvm 添加更多更强大的功能。