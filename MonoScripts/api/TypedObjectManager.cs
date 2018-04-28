using System.Runtime.CompilerServices;

class TypedObjectManager
{
	//static MonoObject* GetResource(int resourceIndex);
    //static MonoArray* GetAllResourcesOfType(MonoType resourceType);
    //static void DestroyResource(MonoObject* object);
    
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
	private extern static object Create(string resourceType);
	
    public static T Create<T>()
    {
        return (T)Create(typeof(T).Name);
    }
	
}