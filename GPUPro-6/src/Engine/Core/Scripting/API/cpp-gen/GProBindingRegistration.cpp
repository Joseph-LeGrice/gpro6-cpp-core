#include "stdafx.h"
#include "GProBindingRegistration.h"
#include "resources/MeshAPI.h"
#include "resources/TextureSamplerAPI.h"
#include "resources/Texture2DArrayAPI.h"
#include "resources/Texture2DAPI.h"
#include "resources/StructuredBufferAPI.h"
#include "resources/StandardMaterialAPI.h"
#include "resources/SimpleMaterialAPI.h"
#include "resources/ShaderResourceAPI.h"
#include "resources/ShaderAPI.h"
#include "components/CameraAPI.h"
#include "components/LightAPI.h"
#include "components/MeshRendererAPI.h"
#include "components/TransformAPI.h"
#include "EntityAPI.h"
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
	CameraAPI::RegisterCalls();
	LightAPI::RegisterCalls();
	MeshRendererAPI::RegisterCalls();
	TransformAPI::RegisterCalls();
	EntityAPI::RegisterCalls();
	TypedObjectManagerAPI::RegisterCalls();
	ScriptedSystemInterfaceAPI::RegisterCalls();
	LoggingAPI::RegisterCalls();
}