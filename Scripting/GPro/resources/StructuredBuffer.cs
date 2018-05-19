using System.Runtime.CompilerServices;

public class StructuredBuffer : ITypedObject
{
// ## Generated Code ##
	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static int GetMyResourceViewID(int instanceid);

	public int GetMyResourceViewID()
	{
		return GetMyResourceViewID(InstanceID);
	}

// ## Generated Code ##
}