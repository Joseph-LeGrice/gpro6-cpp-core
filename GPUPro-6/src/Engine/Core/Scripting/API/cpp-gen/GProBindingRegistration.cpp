#include "stdafx.h"
#include "GProBindingRegistration.h"
#include "MeshAPI.h"
#include "TextureSamplerAPI.h"
#include "Texture2DArrayAPI.h"
#include "Texture2DAPI.h"
#include "StructuredBufferAPI.h"
#include "StandardMaterialAPI.h"
#include "SimpleMaterialAPI.h"
#include "ShaderResourceAPI.h"
#include "ShaderAPI.h"

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
}