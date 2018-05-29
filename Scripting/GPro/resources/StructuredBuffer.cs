using System.Runtime.CompilerServices;

public class StructuredBuffer : ITypedObject
{
// ## Generated Code ##
	public static string GetTypeID()
	{
		return "StructuredBuffer";
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static ITypedObject GetResourceView(int instanceid);

	public ITypedObject GetResourceView()
	{
		return GetResourceView(InstanceID);
	}

// ## Generated Code ##
}