#include "stdafx.h"
#include "Texture2DAPI.h"

#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/Graphics/ResourceTypes/Texture2D.h"
#include <glib.h>

std::wstring GetUTF16(MonoString* ms)
{
	mono_unichar2* pathStr = mono_string_to_utf16(ms);
	std::wstringstream ss;
	int i = 0;
	while (pathStr[i] != NULL)
	{
		ss << static_cast<wchar_t>(pathStr[i]);
		i++;
	}
	g_free(static_cast<void*>(pathStr));
	return ss.str();
}

void Texture2DAPI::InitializeWithBitmap(int instanceid, MonoString* path)
{
	std::wstring pathStr = GetUTF16(path);
	TypedObjectManager* rm = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Texture2D* t = rm->GetInstance<Texture2D>(instanceid);
	t->InitializeWithBitmap(pathStr.c_str());
}

void Texture2DAPI::RegisterMonoMethods()
{
	mono_add_internal_call("Texture2D::InitializeWithBitmap(int,string)", Texture2DAPI::InitializeWithBitmap);
}
