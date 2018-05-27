using System.Runtime.CompilerServices;

public class MeshRenderer : IComponent
{
// ## Generated Code ##
	public static string GetTypeID()
	{
		return "MeshRenderer";
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static int Get_MeshIndex(int instanceId);

	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void Set_MeshIndex(int instanceId, int val);

	public int MeshIndex
	{
		get { return Get_MeshIndex(InstanceID); }
		set { Set_MeshIndex(InstanceID, value); }
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static int Get_MaterialIndex(int instanceId);

	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void Set_MaterialIndex(int instanceId, int val);

	public int MaterialIndex
	{
		get { return Get_MaterialIndex(InstanceID); }
		set { Set_MaterialIndex(InstanceID, value); }
	}

// ## Generated Code ##
}