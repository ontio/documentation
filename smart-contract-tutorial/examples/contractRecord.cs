using Neo.SmartContract.Framework;
using Neo.SmartContract.Framework.Services.Neo;
using Neo.SmartContract.Framework.Services.System;
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
