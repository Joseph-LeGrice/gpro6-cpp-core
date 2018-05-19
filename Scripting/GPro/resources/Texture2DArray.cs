using System.Runtime.CompilerServices;

public class Texture2DArray : ITypedObject
{
// ## Generated Code ##
	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void InitializeWithBitmaps(int instanceid, string arg0);

	public void InitializeWithBitmaps(string arg0)
	{
		InitializeWithBitmaps(InstanceID, arg0);
	}

// ## Generated Code ##
}