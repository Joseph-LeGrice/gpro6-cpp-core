using System.Runtime.CompilerServices;

public class TypedObjectManager : ITypedObject
{
// ## Generated Code ##
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

	public static T GetInstance<T>()
	{
		string typeId = typeof(T).Name;
		return (T)GetInstance(typeId);
	}
}