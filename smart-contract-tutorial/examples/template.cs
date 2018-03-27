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