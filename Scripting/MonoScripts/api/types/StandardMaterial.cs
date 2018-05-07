using System.Runtime.CompilerServices;

class StandardMaterial : ITypedObject
{
    [MethodImpl(MethodImplOptions.InternalCall)]    
    public extern static void SetShaderIndex(int resourceId);
    
    [MethodImpl(MethodImplOptions.InternalCall)]
    public extern static void RegisterShaderResource(int resourceViewId, int resourceSlot);

    [MethodImpl(MethodImplOptions.InternalCall)]
    public extern static void RegisterTextureSampler(int resourceId, int samplerSlot);

    [MethodImpl(MethodImplOptions.InternalCall)]
    public extern static void SetData(object data);
}