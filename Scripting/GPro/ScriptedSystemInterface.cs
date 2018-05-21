using System.Runtime.CompilerServices;

public class ScriptedSystemInterface : ITypedObject
{
// ## Generated Code ##
	public static string GetTypeID()
	{
		return "ScriptedSystemInterface";
	}


	[MethodImplAttribute(MethodImplOptions.InternalCall)]
	public extern static void RegisterSystemInstance(System.Object arg0);

// ## Generated Code ##
}