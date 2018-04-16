#include "stdafx.h"
#include "Texture2DAPI.h"

void Texture2DAPI::InitializeWithBitmap(int instanceid, MonoString* path)
{
	const char* pathStr = mono_string_to_utf8(path);
	std::stringstream ss;
	ss << instanceid << " - " << pathStr;
	Log(ss.str());
}

void Texture2DAPI::RegisterMonoMethods()
{
	mono_add_internal_call("Texture2D::InitializeWithBitmap(int,string)", Texture2DAPI::InitializeWithBitmap);
}
