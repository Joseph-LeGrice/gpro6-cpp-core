using System.Runtime.CompilerServices;

public class Light : IComponent
{
// ## Generated Code ##
	public static string GetTypeID()
	{
		return "Light";
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static float Get_Range(int instanceId);

	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void Set_Range(int instanceId, float val);

	public float Range
	{
		get { return Get_Range(InstanceID); }
		set { Set_Range(InstanceID, value); }
	}

// ## Generated Code ##
}