#include "stdafx.h"
#include "MonoMarshallHelpers.h"

#include "ScriptedSystemLoader.h"
#include "Engine/Core/GlobalStaticReferences.h"

extern std::string MonoMarshall::GetUTF8String(MonoString* ms)
{
	std::stringstream ss;
	char* monoString = mono_string_to_utf8_checked(ms, nullptr);
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

extern Vector4 MonoMarshall::GetVector4(MonoObject* mo)
{
	Vector4* val = static_cast<Vector4*>(mono_object_unbox(mo));
	return *val;
}

extern Vector3 MonoMarshall::GetVector3(MonoObject* mo)
{
	Vector3* val = static_cast<Vector3*>(mono_object_unbox(mo));
	return *val;
}

extern Vector2 MonoMarshall::GetVector2(MonoObject* mo)
{
	Vector2* val = static_cast<Vector2*>(mono_object_unbox(mo));
	return *val;
}

extern Matrix4x4 MonoMarshall::GetMatrix4x4(MonoObject* mo)
{
	Matrix4x4* val = static_cast<Matrix4x4*>(mono_object_unbox(mo));
	return *val;
}

extern Matrix3x3 MonoMarshall::GetMatrix3x3(MonoObject* mo)
{
	Matrix3x3* val = static_cast<Matrix3x3*>(mono_object_unbox(mo));
	return *val;
}


extern Quaternion MonoMarshall::GetQuaternion(MonoObject* mo)
{
	Quaternion* val = static_cast<Quaternion*>(mono_object_unbox(mo));
	return *val;
}

extern MonoObject* MonoMarshall::GetManagedVector4(Vector4 val)
{
	ScriptedSystemLoader* ssl = GlobalStaticReferences::Instance()->GetMonoSystemLoader();
	return ssl->BoxValueInClass(&val, "Vector4");
}

extern MonoObject* MonoMarshall::GetManagedVector3(Vector3 val)
{
	ScriptedSystemLoader* ssl = GlobalStaticReferences::Instance()->GetMonoSystemLoader();
	return ssl->BoxValueInClass(&val, "Vector3");
}

extern MonoObject* MonoMarshall::GetManagedVector2(Vector2 val)
{
	ScriptedSystemLoader* ssl = GlobalStaticReferences::Instance()->GetMonoSystemLoader();
	return ssl->BoxValueInClass(&val, "Vector2");
}

extern MonoObject* MonoMarshall::GetManagedMatrix4x4(Matrix4x4 val)
{
	ScriptedSystemLoader* ssl = GlobalStaticReferences::Instance()->GetMonoSystemLoader();
	return ssl->BoxValueInClass(&val, "Matrix4x4");
}

extern MonoObject* MonoMarshall::GetManagedMatrix3x3(Matrix3x3 val)
{
	ScriptedSystemLoader* ssl = GlobalStaticReferences::Instance()->GetMonoSystemLoader();
	return ssl->BoxValueInClass(&val, "Matrix3x3");
}

extern MonoObject* MonoMarshall::GetManagedQuaternion(Quaternion val)
{
	ScriptedSystemLoader* ssl = GlobalStaticReferences::Instance()->GetMonoSystemLoader();
	return ssl->BoxValueInClass(&val, "Quaternion");
}
