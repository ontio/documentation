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