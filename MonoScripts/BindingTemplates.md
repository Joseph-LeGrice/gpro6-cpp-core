# Native Instance Method Binding

## C++
```
[NATIVE_RETURN_TYPE] [NATIVE_CLASS_NAME]API::[NATIVE_METHOD_NAME](int managedInstanceId, [NATIVE_METHOD_ARGS])
{
    ScriptedManager* sm = GlobalStaticReferences::Instance()->GetScriptedManager();
    ClassID nativeClassId = [NATIVE_CLASS_NAME]::GetTypeID();
    [NATIVE_CLASS_NAME]* nativeClassInstance = sm->GetNativeInstance(nativeClassId, managedInstanceId);
    nativeClassInstance->[NATIVE_METHOD_NAME]([NATIVE_METHOD_ARGS]);
}
```
```
mono_add_internal_call("[MANAGED_CLASS_NAME]::[MANAGED_METHOD_NAME](int,[MANAGED_METHOD_ARGS])", [NATIVE_CLASS_NAME]API::[NATIVE_METHOD_NAME]);
```
## C#
```
[MethodImpl(MethodImplOptions.InternalCall)]  
private extern static [MANAGED_RETURN_TYPE] [MANAGED_METHOD_NAME](int instanceid, [MANAGED_METHOD_ARGS]);  

public [MANAGED_RETURN_TYPE] [MANAGED_METHOD_NAME]([MANAGED_METHOD_ARGS])  
{  
    [MANAGED_METHOD_NAME](InstanceID, [MANAGED_METHOD_ARGS]);  
}
```

# Native Static Methods
## C++
```
static [NATIVE_RETURN_TYPE] [NATIVE_CLASS_NAME]::[NATIVE_METHOD_NAME]([NATIVE_METHOD_ARGS])
{
    [LOGIC]
}
```
```
mono_add_internal_call("[MANAGED_CLASS_NAME]::[MANAGED_METHOD_NAME]", [NATIVE_CLASS_NAME]::[NATIVE_METHOD_NAME]);
```
## C#
```
[MethodImplAttribute(MethodImplOptions.InternalCall)]  
[VISIBILITY] extern static [MANAGED_RETURN_TYPE] [MANAGED_METHOD_NAME]([MANAGED_METHOD_ARGS]);
```

# Custom C#

Sometimes we may want to add extra custom C# such as:
```
public static T CreateResource<T>()
{
    return (T)CreateResource(typeof(T).Name);
}
```
