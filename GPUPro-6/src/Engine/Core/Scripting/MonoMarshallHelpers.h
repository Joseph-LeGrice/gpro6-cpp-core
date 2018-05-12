#pragma once

#include <vector>

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

namespace MonoMarshall
{
	extern std::wstring GetUTF16String(MonoString* ms);
	extern std::vector<std::wstring> GetStringVector(MonoArray* ma);
}