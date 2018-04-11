using System;
using System.Runtime.CompilerServices;

class Program
{
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    private extern static void Test();

   static int Main(string[] args)
    {
        Test();
        Console.WriteLine("Hello World");
        TestSystem test = new TestSystem();
        Console.WriteLine("Made de object");

        return 0;
    }
}