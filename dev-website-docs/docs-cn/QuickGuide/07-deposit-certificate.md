
## 概述

某些特定类型的DApp可能有往链上存取数据的需求，本文档介绍了如何在链上进行数据存取操作。

链上数据的存储主要在于通过智能合约进行操作，以下是一个智能合约的demo,请在smartx中调试，[调试指南](https://dev-docs.ont.io/#/docs-cn/QuickGuide/00-dapp_development?id=%E5%9C%A8-smartx-%E4%B8%AD%E5%88%9B%E5%BB%BA%EF%BC%8C%E7%BC%96%E8%AF%91%E5%92%8C%E9%83%A8%E7%BD%B2%E6%99%BA%E8%83%BD%E5%90%88%E7%BA%A6%E5%88%B0%E7%A7%81%E6%9C%89%E9%93%BE)

```c#
using Ont.SmartContract.Framework;
using Ont.SmartContract.Framework.Services.Ont;
using Ont.SmartContract.Framework.Services.System;
using System;
using System.ComponentModel;
using System.Numerics;

namespace Ontology
{
    public class Ontology : SmartContract
    {
        [DisplayName("putRecord")]
        public static event Action<string, byte[], byte[]> PutEvent;

        [DisplayName("getRecord")]
        public static event Action<string, byte[]> GetEvent;

        public static Object Main(string operation, params object[] args)
        {
            if (operation == "Put")
            {
                if (args.Length != 2) return false;
                byte[] key = (byte[])args[0];
                byte[] value = (byte[])args[1];
                return Put(key, value);
            }

            if (operation == "Get")
            {
                if (args.Length != 1) return false;
                byte[] key = (byte[])args[0];
                return Get(key);
            }
            return false;
        }

        public static bool Put(byte[] key, byte[] value)
        {
            Storage.Put(Storage.CurrentContext, key, value);
            PutEvent("Put", key, value);
            Runtime.Log("Put");
            return true;
        }

        public static byte[] Get(byte[] key)
        {
            GetEvent("Get", key);
            Runtime.Log("Get");
            return Storage.Get(Storage.CurrentContext, key);
        }
    }
}
```
