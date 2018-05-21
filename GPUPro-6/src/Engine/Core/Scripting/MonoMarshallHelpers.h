#pragma once

#include <vector>

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

namespace MonoMarshall
{
	extern std::string GetUTF8String(MonoString* ms);
	extern std::wstring GetUTF16String(MonoString* ms);
	
	extern std::vector<std::wstring> GetStringVector(MonoArray* ma);

	extern Vector4 GetVector4(MonoObject* mo);
	extern Vector3 GetVector3(MonoObject* mo);
	extern Vector2 GetVector2(MonoObject* mo);

	extern Matrix4x4 GetMatrix4x4(MonoObject* mo);
	extern Matrix3x3 GetMatrix3x3(MonoObject* mo);
	
	extern Quaternion GetQuaternion(MonoObject* mo);

	extern MonoObject* GetManagedVector4(Vector4 val);
	extern MonoObject* GetManagedVector3(Vector3 val);
	extern MonoObject* GetManagedVector2(Vector2 val);

	extern MonoObject* GetManagedMatrix4x4(Matrix4x4 val);
	extern MonoObject* GetManagedMatrix3x3(Matrix3x3 val);

	extern MonoObject* GetManagedQuaternion(Quaternion val);
}