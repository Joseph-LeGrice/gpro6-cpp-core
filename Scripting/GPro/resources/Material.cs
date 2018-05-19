using System.Runtime.CompilerServices;

public class Material : ITypedObject
{
// ## Generated Code ##
	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void SetShaderIndex(int instanceid, int arg0);

	public void SetShaderIndex(int arg0)
	{
		SetShaderIndex(InstanceID, arg0);
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void RegisterShaderResource(int instanceid, int arg0, int arg1);

	public void RegisterShaderResource(int arg0, int arg1)
	{
		RegisterShaderResource(InstanceID, arg0, arg1);
	}

// ## Generated Code ##
}