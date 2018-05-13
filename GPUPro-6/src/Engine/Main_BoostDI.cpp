/*
#include "stdafx.h"

#include <unordered_map>

#include "Engine/Core/WindowManagement/WindowManager.h"

#include "Engine/Core/GameLoop.h"
#include "Engine/Core/Time/Time.h"

// ISystem's
#include "Engine/Core/SystemManagement/SystemContainer.h"
#include "Engine/Core/Graphics/GraphicsSystem.h"
#include "Engine/Core/Input/InputSystem.h"
#include "Engine/Core/Graphics/LightingSystem.h"
#include "Engine/Extra/Locomotion/NoClipLocomotion.h"

// IDrawCommands
#include "Engine/Core/Graphics/Drawing/SkyboxDrawCommand.h"
#include "Engine/Core/Graphics/Drawing/StandardOpaqueMaterialDrawCommand.h"
#include "Engine/Core/Graphics/Drawing/StandardTransparentMaterialDrawCommand.h"

// ConstantBuffers
#include "Engine/Core/Graphics/Buffers/ConstantBuffers/PerCameraBuffer.h"
#include "Engine/Core/Graphics/Buffers/ConstantBuffers/PerObjectBuffer.h"
#include "Engine/Core/Graphics/Buffers/ConstantBuffers/StandardMaterialBuffer.h"

// Scene + IComponents
#include "Engine/Core/SceneGraph/SceneGraph.hpp"
#include "Engine/Core/SceneGraph/SceneGraphManager.h"
#include "Engine/Core/SceneGraph/Components/Entity.h"
#include "Engine/Core/Components/Camera.h"
#include "Engine/Core/Components/Light.h"
#include "Engine/Core/Components/Transform.h"
#include "Engine/Core/Components/MeshRenderer.h"

// Etc
#include "Engine/Core/Mesh/MeshManager.h"
#include "Engine/Core/Graphics/BlendState.h"
#include "Engine/Core/Graphics/RasterizerState.h"
#include "Engine/Core/Graphics/Buffers/IndexBuffer.h"
#include "Engine/Core/Graphics/Buffers/VertexBuffer.h"
#include "Engine/Core/Graphics/Buffers/DepthStencilBuffer.h"

#pragma warning(push)
#pragma warning(disable:4100)
#pragma warning(disable:4458)

#include "boost/di.hpp"
#include "boost/di/extension/policies/uml_dumper.hpp"
#include "boost/di/extension/bindings/constructor_bindings.hpp"

namespace di = boost::di;

static const auto test_name = [] { return "test_name"; };

class A {
public:
	BOOST_DI_INJECT(A, (named = test_name) std::unordered_map<ComponentTypeID, std::vector<IComponent*>>& componentMap) { }
};

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	std::unordered_map<ComponentTypeID, std::vector<IComponent*>> componentMapping = {
		{ Transform::GetComponentType(), std::vector<IComponent*>() },
		{ Camera::GetComponentType(), std::vector<IComponent*>() },
		{ MeshRenderer::GetComponentType(), std::vector<IComponent*>() },
		{ Entity::GetComponentType(), std::vector<IComponent*>() },
		{ Light::GetComponentType(), std::vector<IComponent*>() }
	};

	auto injector = di::make_injector(
		// All ISystem's in use for the build:
		//di::bind<ISystem*[]>().to<
		//GraphicsSystem,
		//LightingSystem,
		//NoClipLocomotion,
		//InputSystem>(),

		// Specify all Draw Commands:
		//di::bind<IDrawCommand*[]>().to<
		//SkyboxDrawCommand,
		//StandardOpaqueMaterialDrawCommand,
		//StandardTransparentMaterialDrawCommand>(),

		// Specify Components?
		di::bind<>().named(test_name).to(componentMapping)
		//di::bind<>().named(component_map).to(componentMapping)
		// Specify the ITypedObjectManager::
		//di::bind<ITypedObjectManager>().to<TypedObjectManager>()  

		// Specify valid ResourceTypes?
		//di::bind<ITypedObject*[]>().to<
		//  Mesh,
		//  Shader,
		//  ShaderResource,
		//  StandardMaterial,
		//  SimpleMaterial,
		//  StructuredBuffer,
		//  Texture2D,
		//  Texture2DArray,
		//  TextureSampler>()
	);
	
	injector.create<A>();
	return 0;

	//GameLoop& game = injector.create<GameLoop&>();
	//SystemContainer& sc = injector.create<SystemContainer&>();
	//return game.Run(sc);
}

#pragma warning(pop)
*/