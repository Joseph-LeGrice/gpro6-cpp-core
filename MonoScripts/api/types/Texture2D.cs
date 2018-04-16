using System.Runtime.CompilerServices;

class Texture2D : IResource
{
    [MethodImpl(MethodImplOptions.InternalCall)]
    private extern static void InitializeWithBitmap(int instanceid, string bitmapPath);

    public void InitializeWithBitmap(string bitmapPath)
    {
        InitializeWithBitmap(InstanceID, bitmapPath);
    }
}