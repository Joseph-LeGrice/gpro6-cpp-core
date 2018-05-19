using System.Runtime.CompilerServices;

public class Light : ITypedObject
{
// ## Generated Code ##
	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern float Get_Range(int instanceId);

	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern void Set_Range(int instanceId, float val);

	public float Range
	{
		get { return Get_Range(InstanceID); }
		set { Set_Range(InstanceID, value); }
	}

// ## Generated Code ##
}