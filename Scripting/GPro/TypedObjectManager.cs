using System.Runtime.CompilerServices;

public class TypedObjectManager : ITypedObject
{
// ## Generated Code ##
	[MethodImplAttribute(MethodImplOptions.InternalCall)]
	public extern static System.Object Create(string arg0);

// ## Generated Code ##
	public static T Create<T>()
	{
        string typeId = typeof(T).Name;
		return (T)Create(typeId);
	}
}