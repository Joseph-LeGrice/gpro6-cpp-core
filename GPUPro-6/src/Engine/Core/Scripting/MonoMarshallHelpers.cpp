#include "stdafx.h"
#include "MonoMarshallHelpers.h"

#include "ScriptedSystemLoader.h"
#include "Engine/Core/GlobalStaticReferences.h"

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