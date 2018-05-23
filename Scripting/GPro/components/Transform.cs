using System.Runtime.CompilerServices;

public class Transform : IComponent
{
// ## Generated Code ##
	public static string GetTypeID()
	{
		return "Transform";
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static Vector3 Get_position(int instanceId);

	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void Set_position(int instanceId, Vector3 val);

	public Vector3 position
	{
		get { return Get_position(InstanceID); }
		set { Set_position(InstanceID, value); }
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static Vector3 Get_scale(int instanceId);

	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void Set_scale(int instanceId, Vector3 val);

	public Vector3 scale
	{
		get { return Get_scale(InstanceID); }
		set { Set_scale(InstanceID, value); }
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static Quaternion Get_rotation(int instanceId);

	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void Set_rotation(int instanceId, Quaternion val);

	public Quaternion rotation
	{
		get { return Get_rotation(InstanceID); }
		set { Set_rotation(InstanceID, value); }
	}

// ## Generated Code ##
}