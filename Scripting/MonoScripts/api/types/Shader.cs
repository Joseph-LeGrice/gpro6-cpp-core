using System.Runtime.CompilerServices;

class Shader : ITypedObject
{
    [MethodImpl(MethodImplOptions.InternalCall)]
    public extern static void InitVertexShader(string path, string name);

    [MethodImpl(MethodImplOptions.InternalCall)]
    public extern static void InitPixelShader(string path, string name);
}