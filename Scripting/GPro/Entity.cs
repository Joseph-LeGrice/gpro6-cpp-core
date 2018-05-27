using System.Runtime.CompilerServices;

public class Entity : ITypedObject
{
// ## Generated Code ##
	public static string GetTypeID()
	{
		return "Entity";
	}


	[MethodImplAttribute(MethodImplOptions.InternalCall)]
	public extern static ITypedObject AddComponentInternal(int arg0, string arg1);


	[MethodImplAttribute(MethodImplOptions.InternalCall)]
	public extern static void RemoveComponentInternal(int arg0, string arg1);


	[MethodImplAttribute(MethodImplOptions.InternalCall)]
	public extern static ITypedObject GetComponentInternal(int arg0, string arg1);

// ## Generated Code ##

	public T AddComponent<T>() where T : IComponent
	{
		string typeId = (string)typeof(T).GetMethod("GetTypeID").Invoke(null, new object[]{});
		return (T)AddComponentInternal(InstanceID, typeId);
	}

	public void RemoveComponent<T>() where T : IComponent
	{
		string typeId = (string)typeof(T).GetMethod("GetTypeID").Invoke(null, new object[]{});
		RemoveComponentInternal(InstanceID, typeId);
	}

	public T GetComponent<T>() where T : IComponent
	{
		string typeId = (string)typeof(T).GetMethod("GetTypeID").Invoke(null, new object[]{});
		return (T)GetComponentInternal(InstanceID, typeId);
	}
}