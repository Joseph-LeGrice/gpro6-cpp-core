using System.Runtime.CompilerServices;


static class SystemInterface
{
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern static void RegisterSystem(System.Object newSystem);
}