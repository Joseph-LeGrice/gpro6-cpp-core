using System.Runtime.CompilerServices;

public class Entity : ITypedObject
{
// ## Generated Code ##
	public static string GetTypeID()
	{
		return "Entity";
	}


	[MethodImplAttribute(MethodImplOptions.InternalCall)]
	public extern static System.Object AddComponentInternal(string arg0);


	[MethodImplAttribute(MethodImplOptions.InternalCall)]
	public extern static System.Object RemoveComponentInternal(string arg0);


	[MethodImplAttribute(MethodImplOptions.InternalCall)]
	public extern static System.Object GetComponentInternal(string arg0);

// ## Generated Code ##

	public T AddComponent<T>() where T : IComponent
	{
		string typeId = (string)typeof(T).GetMethod("GetTypeID").Invoke(null, new object[]{});
		return (T)AddComponentInternal(typeId);
	}

	public void RemoveComponent<T>() where T : IComponent
	{
		string typeId = (string)typeof(T).GetMethod("GetTypeID").Invoke(null, new object[]{});
		RemoveComponentInternal(typeId);
	}

	public T GetComponent<T>() where T : IComponent
	{
		string typeId = (string)typeof(T).GetMethod("GetTypeID").Invoke(null, new object[]{});
		return (T)GetComponentInternal(typeId);
	}
}