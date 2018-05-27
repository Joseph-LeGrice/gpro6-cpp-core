using System.Runtime.CompilerServices;

public class TypedObjectManager : ITypedObject
{
// ## Generated Code ##
	public static string GetTypeID()
	{
		return "TypedObjectManager";
	}


	[MethodImplAttribute(MethodImplOptions.InternalCall)]
	public extern static ITypedObject Create(string arg0);


	[MethodImplAttribute(MethodImplOptions.InternalCall)]
	public extern static ITypedObject GetInstance(string arg0, int arg1);

// ## Generated Code ##
	public static T Create<T>() where T : ITypedObject
	{
        string typeId = typeof(T).Name;
		return (T)Create(typeId);
	}

	public static T GetInstance<T>(int instanceId) where T : ITypedObject
	{
		string typeId = typeof(T).Name;
		return (T)GetInstance(typeId, instanceId);
	}
}