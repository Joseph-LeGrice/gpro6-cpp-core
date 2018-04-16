using System.Runtime.CompilerServices;

class ResourceManager
{
	//static MonoObject* GetResource(int resourceIndex);
    //static MonoArray* GetAllResourcesOfType(MonoType resourceType);
    //static void DestroyResource(MonoObject* object);
    
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
	private extern static object CreateResource(string resourceType);
	
    public static T CreateResource<T>()
    {
        return (T)CreateResource(typeof(T).Name);
    }
	
}