using System.Runtime.CompilerServices;

public class Texture2D : ITypedObject
{
// ## Generated Code ##
	public static string GetTypeID()
	{
		return "Texture2D";
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void InitializeWithBitmap(int instanceid, string arg0);

	public void InitializeWithBitmap(string arg0)
	{
		InitializeWithBitmap(InstanceID, arg0);
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static ITypedObject GetResource(int instanceid);

	public ITypedObject GetResource()
	{
		return GetResource(InstanceID);
	}

// ## Generated Code ##
}