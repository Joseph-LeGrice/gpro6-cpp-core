using System.Runtime.CompilerServices;

public class Logging : ITypedObject
{
// ## Generated Code ##
	public static string GetTypeID()
	{
		return "Logging";
	}


	[MethodImplAttribute(MethodImplOptions.InternalCall)]
	public extern static void LogMessage(string arg0);

// ## Generated Code ##
}