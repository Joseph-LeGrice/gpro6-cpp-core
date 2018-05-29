#include "stdafx.h"
#include "MonoMarshallHelpers.h"

#include "ScriptedSystemLoader.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/ResourceTypes/ManagedObject.h"
#include "Engine/Core/DataStructures/MaterialPropertyList.h"

extern std::string MonoMarshall::GetUTF8String(MonoString* ms)
{
	std::stringstream ss;
	char* monoString = mono_string_to_utf8(ms);
	ss << monoString;
	mono_free(static_cast<void*>(monoString));
	return ss.str();
}

std::wstring MonoMarshall::GetUTF16String(MonoString* ms)
{
	mono_unichar2* pathStr = mono_string_to_utf16(ms);
	std::wstringstream ss;
	int i = 0;
	while (pathStr[i] != NULL)
	{
		ss << static_cast<wchar_t>(pathStr[i]);
		i++;
	}
	mono_free(static_cast<void*>(pathStr));
	return ss.str();
}

extern std::vector<std::wstring> MonoMarshall::GetStringVector(MonoArray* ma)
{
	std::vector<std::wstring> result;
	uintptr_t l = mono_array_length(ma);
	for (int i = 0; i < l; i++)
	{
		MonoString* element = mono_array_get(ma, MonoString*, i);
		std::wstring strElement = GetUTF16String(element);
		result.push_back(strElement);
	}
	return result;
}

extern std::vector<MaterialProperty::Initializer> MonoMarshall::GetPropertyInitializerVector(MonoArray* ma)
{
	struct M2N
	{
		MonoString* m_propertyName;
		MaterialProperty::ValueType m_valueType;
	};

	std::vector<MaterialProperty::Initializer> result;
	uintptr_t l = mono_array_length(ma);
	for (int i = 0; i < l; i++)
	{
		M2N element = mono_array_get(ma, M2N, i);
		std::wstring strElement = GetUTF16String(element.m_propertyName);
		result.push_back({ strElement, element.m_valueType });
	}
	return result;
}

extern ToPtr MonoMarshall::GetNativePointer(MonoObject* obj)
{
	MonoClass* managedClass = mono_object_get_class(obj);
	ManagedTypeID className = mono_class_get_name(managedClass);
	MonoClassField* field = mono_class_get_field_from_name(managedClass, "m_instanceId");
	InstanceID managedInstanceId = -1;
	mono_field_get_value(obj, field, &managedInstanceId);
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	ITypedObject* nativeInstance = ntmip->GetNativeObject(className, managedInstanceId);
	return ToPtr(nativeInstance);
}

extern MonoObject* MonoMarshall::GetManagedObject(ToPtr obj)
{
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	ManagedObject* mo = ntmip->GetManagedObject(obj.GetTypeID(), obj.GetInstanceID());
	return mo->GetManagedObject();
}
