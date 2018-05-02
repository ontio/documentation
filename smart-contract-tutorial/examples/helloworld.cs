using Neo.SmartContract.Framework.Services.Neo;
using Neo.SmartContract.Framework;
using System;
using System.ComponentModel;

namespace Neo.SmartContract
{
    public class HelloWorld : Framework.SmartContract
    {
        public static object Main(string operation, params object[] args)
        {
            switch (operation)
            {
                case "Hello":
                    Hello((string)args[0]);
                    return true;
                default:
                    return false;
            }
        }
        public static void Hello(string msg)
        {
            Runtime.Log(msg);
        }
    }
}
