using System.Runtime.CompilerServices;

public class MeshHelper : ITypedObject
{
// ## Generated Code ##
	public static string GetTypeID()
	{
		return "MeshHelper";
	}


	[MethodImplAttribute(MethodImplOptions.InternalCall)]
	public extern static ITypedObject CreateSphereUV_Internal();


	[MethodImplAttribute(MethodImplOptions.InternalCall)]
	public extern static ITypedObject CreateQuad_Internal();

// ## Generated Code ##

    public static Mesh CreateSphereUV()
    {
        return (Mesh)CreateSphereUV_Internal();
    }

    public static Mesh CreateQuad()
    {
        return (Mesh)CreateQuad_Internal();
    }	
}