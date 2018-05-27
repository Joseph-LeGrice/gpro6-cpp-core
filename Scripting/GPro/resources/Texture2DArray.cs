using System.Runtime.CompilerServices;

public class Texture2DArray : ITypedObject
{
// ## Generated Code ##
	public static string GetTypeID()
	{
		return "Texture2DArray";
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void InitializeWithBitmaps(int instanceid, string[] arg0);

	public void InitializeWithBitmaps(string[] arg0)
	{
		InitializeWithBitmaps(InstanceID, arg0);
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static ITypedObject GetResource(int instanceid);

	public ITypedObject GetResource()
	{
		return GetResource(InstanceID);
	}

// ## Generated Code ##
}