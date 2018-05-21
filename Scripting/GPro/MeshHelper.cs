using System.Runtime.CompilerServices;

public class MeshHelper : ITypedObject
{
// ## Generated Code ##
	public static string GetTypeID()
	{
		return "MeshHelper";
	}


	[MethodImplAttribute(MethodImplOptions.InternalCall)]
	public extern static System.Object CreateSphereUV_Internal();

// ## Generated Code ##

    public static Mesh CreateSphereUV()
    {
        return (Mesh)CreateSphereUV_Internal();
    }
}