using System.Runtime.CompilerServices;

public class Texture2D : ITypedObject
{
	//// GENERATED
	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void InitializeWithBitmap(int instanceid, string arg0);
	public void InitializeWithBitmap(string arg0)
	{
		InitializeWithBitmap(InstanceID, arg0);
	}

	//// GENERATED
}