using System.Runtime.CompilerServices;

public class MeshRenderer : IComponent
{
// ## Generated Code ##
	public static string GetTypeID()
	{
		return "MeshRenderer";
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static ITypedObject Get_Mesh(int instanceId);

	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void Set_Mesh(int instanceId, ITypedObject val);

	public ITypedObject Mesh
	{
		get { return Get_Mesh(InstanceID); }
		set { Set_Mesh(InstanceID, value); }
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static ITypedObject Get_Material(int instanceId);

	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void Set_Material(int instanceId, ITypedObject val);

	public ITypedObject Material
	{
		get { return Get_Material(InstanceID); }
		set { Set_Material(InstanceID, value); }
	}

// ## Generated Code ##
}