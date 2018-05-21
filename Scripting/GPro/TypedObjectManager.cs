using System.Runtime.CompilerServices;

public class TypedObjectManager : ITypedObject
{
// ## Generated Code ##
	public static string GetTypeID()
	{
		return "TypedObjectManager";
	}


	[MethodImplAttribute(MethodImplOptions.InternalCall)]
	public extern static System.Object Create(string arg0);


	[MethodImplAttribute(MethodImplOptions.InternalCall)]
	public extern static System.Object GetInstance(string arg0, int arg1);

// ## Generated Code ##
	public static T Create<T>()
	{
        string typeId = typeof(T).Name;
		return (T)Create(typeId);
	}

	public static T GetInstance<T>(int instanceId)
	{
		string typeId = typeof(T).Name;
		return (T)GetInstance(typeId, instanceId);
	}
}