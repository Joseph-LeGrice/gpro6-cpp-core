using System.Runtime.CompilerServices;

public class Shader : ITypedObject
{
// ## Generated Code ##
	public static string GetTypeID()
	{
		return "Shader";
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void InitVertexShader(int instanceid, string arg0, string arg1);

	public void InitVertexShader(string arg0, string arg1)
	{
		InitVertexShader(InstanceID, arg0, arg1);
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void InitPixelShader(int instanceid, string arg0, string arg1);

	public void InitPixelShader(string arg0, string arg1)
	{
		InitPixelShader(InstanceID, arg0, arg1);
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void InitGeometryShader(int instanceid, string arg0, string arg1);

	public void InitGeometryShader(string arg0, string arg1)
	{
		InitGeometryShader(InstanceID, arg0, arg1);
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void InitHullShader(int instanceid, string arg0, string arg1);

	public void InitHullShader(string arg0, string arg1)
	{
		InitHullShader(InstanceID, arg0, arg1);
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void InitDomainShader(int instanceid, string arg0, string arg1);

	public void InitDomainShader(string arg0, string arg1)
	{
		InitDomainShader(InstanceID, arg0, arg1);
	}

// ## Generated Code ##
}