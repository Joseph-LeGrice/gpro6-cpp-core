#include "stdafx.h"
#include "MonoMarshallHelpers.h"

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
	UNREFERENCED_PARAMETER(ma);
	return std::vector<std::wstring>();
}
