using System.Runtime.CompilerServices;

public class Texture2DArray : ITypedObject
{
// ## Generated Code ##
	public static string GetTypeID()
	{
		return "Texture2DArray";
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void InitializeWithBitmaps(int instanceid, System.Collections.Generic.List<string> arg0);

	public void InitializeWithBitmaps(System.Collections.Generic.List<string> arg0)
	{
		InitializeWithBitmaps(InstanceID, arg0);
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static int GetResourceViewID(int instanceid);

	public int GetResourceViewID()
	{
		return GetResourceViewID(InstanceID);
	}

// ## Generated Code ##
}