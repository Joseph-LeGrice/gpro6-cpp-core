#include "stdafx.h"

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

#include "Engine/Core/SceneGraph/SceneGraphDefinition.hpp"

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

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	auto injector = di::make_injector(
		// All ISystem's in use for the build:
		di::bind<ISystem*[]>().to<
			GraphicsSystem,
			LightingSystem,
			NoClipLocomotion,
			InputSystem>(),

		// Specify all Draw Commands:
		di::bind<IDrawCommand*[]>().to<
            SkyboxDrawCommand,
            StandardOpaqueMaterialDrawCommand, 
            StandardTransparentMaterialDrawCommand>()

        // Specify the IResourceManager::
        //di::bind<IResourceManager>().to<ResourceManager>()  
        
        // Specify valid ResourceTypes?
        //di::bind<IResource*[]>().to<
        //  Mesh,
        //  Shader,
        //  ShaderResource,
        //  StandardMaterial,
        //  SimpleMaterial,
        //  StructuredBuffer,
        //  Texture2D,
        //  Texture2DArray,
        //  TextureSampler>()

		// Specify Components?
		//di::bind<IComponent*[]>().to<
		//  TransformComponent,
		//  CameraComponent,
		//  MeshRendererComponent,
		//  EntityComponent,
		//  LightComponent>()
	);

	GameLoop& game = injector.create<GameLoop&>();
	SystemContainer& sc = injector.create<SystemContainer&>();
	return game.Run(sc);

	//injector.create<GameLoop&>();
	return 0;
}

#pragma warning(pop)