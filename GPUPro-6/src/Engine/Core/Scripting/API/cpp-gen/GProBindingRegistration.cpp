#include "stdafx.h"
#include "GProBindingRegistration.h"
#include "types/MeshAPI.h"
#include "types/TextureSamplerAPI.h"
#include "types/Texture2DArrayAPI.h"
#include "types/Texture2DAPI.h"
#include "types/StructuredBufferAPI.h"
#include "types/StandardMaterialAPI.h"
#include "types/SimpleMaterialAPI.h"
#include "types/ShaderResourceAPI.h"
#include "types/ShaderAPI.h"
#include "TypedObjectManagerAPI.h"
#include "ScriptedSystemInterfaceAPI.h"
#include "LoggingAPI.h"

using namespace GPro;

void GPro::RegisterAllCalls()
{
	MeshAPI::RegisterCalls();
	TextureSamplerAPI::RegisterCalls();
	Texture2DArrayAPI::RegisterCalls();
	Texture2DAPI::RegisterCalls();
	StructuredBufferAPI::RegisterCalls();
	StandardMaterialAPI::RegisterCalls();
	SimpleMaterialAPI::RegisterCalls();
	ShaderResourceAPI::RegisterCalls();
	ShaderAPI::RegisterCalls();
	TypedObjectManagerAPI::RegisterCalls();
	ScriptedSystemInterfaceAPI::RegisterCalls();
	LoggingAPI::RegisterCalls();
}