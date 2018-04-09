# C# Smart Contract


> Note:These are the simplest intelligent contracts,In addition to the TODO part and the Class name, the other parts do not recommend changes.

### example 1： HelloWorld smart contract

```
using Neo.SmartContract.Framework.Services.Neo;

namespace Neo.SmartContract
{
    public class HelloWorld : Framework.SmartContract
    {
        public static void Main()
        {
            // TODO
            Storage.Put(Storage.CurrentContext, "Hello", "World");
        }
    }
}
```



### example 2：Smart contract template

```
using Neo.SmartContract.Framework;
using Neo.SmartContract.Framework.Services.Neo;
using Neo.SmartContract.Framework.Services.System;
using System;
using System.ComponentModel;
using System.Numerics;

namespace Neo.SmartContract
{
    public class contract1 : Framework.SmartContract
    {
        public static Object Main(string operation, params object[] args)
        {
            if (Runtime.Trigger == TriggerType.Application)
            {
                if (operation == "add")
                {
                    if (args.Length != 2) return false;
                    int a = (int)args[0];
                    int b = (int)args[1];
                    return Add(a, b);
                }
                if (operation == "compare")
                {
                    if (args.Length != 2) return false;
                    int a = (int)args[0];
                    int b = (int)args[1];
                    return Compare(a, b);
                }
            }
            return false;
        }

        public static int Add(int a, int b)
        {
            return a + b;
        }

        public static int Compare(int a, int b)
        {
            if (a > b)
            {
                return a;
            }
            return b;
        }
    }
}
```

### example 3：Domain service smart contract

```
using Neo.SmartContract.Framework;
using Neo.SmartContract.Framework.Services.Neo;
using Neo.SmartContract.Framework.Services.System;
using System;
using System.ComponentModel;
using System.Numerics;

namespace Neo.SmartContract
{
    public class Domain : Framework.SmartContract
    {
        public static object Main(string operation, params object[] args)
        {
            switch (operation)
            {
                case "query":
                    return Query((string)args[0]);
                case "register":
                    return Register((string)args[0], (byte[])args[1]);
                case "transfer":
                    return Transfer((string)args[0], (byte[])args[1]);
                case "delete":
                    return Delete((string)args[0]);
                default:
                    return false;
            }
        }

        public static byte[] Query(string domain)
        {
            return Storage.Get(Storage.CurrentContext, domain);
        }

        public static bool Register(string domain, byte[] owner)
        {
            if (!Runtime.CheckWitness(owner)) return false;
            byte[] value = Storage.Get(Storage.CurrentContext, domain);
            if (value != null) return false;
            Storage.Put(Storage.CurrentContext, domain, owner);
            return true;
        }

        public static bool Transfer(string domain, byte[] to)
        {
            byte[] from = Storage.Get(Storage.CurrentContext, domain);
            if (from == null) return false;
            if (!Runtime.CheckWitness(from)) return false;
            Storage.Put(Storage.CurrentContext, domain, to);
            return true;
        }

        public static bool Delete(string domain)
        {
            byte[] owner = Storage.Get(Storage.CurrentContext, domain);
            if (owner == null) return false;
            if (!Runtime.CheckWitness(owner)) return false;
            Storage.Delete(Storage.CurrentContext, domain);
            return true;
        }
    }
}

```

