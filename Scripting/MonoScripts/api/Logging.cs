using System.Runtime.CompilerServices;

static class Logging
{
    [MethodImpl(MethodImplOptions.InternalCall)]
    public extern static void LogMessage(string message);
}