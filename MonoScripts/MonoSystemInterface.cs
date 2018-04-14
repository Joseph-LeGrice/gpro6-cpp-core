using System.Runtime.CompilerServices;


static class MonoSystemInterface
{
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern static void RegisterSystem(System.Object newSystem);
}