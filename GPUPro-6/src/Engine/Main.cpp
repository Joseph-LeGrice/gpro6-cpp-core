#include "stdafx.h"




#include "Engine/Core/GameLoop.h"
#include "Engine/Core/Time/Time.h"

// ISystem's
#include "Engine/Core/Graphics/GraphicsSystem.h"
#include "Engine/Core/Input/InputSystem.h"
#include "Engine/Core/Graphics/LightingSystem.h"
#include "Engine/Extra/Locomotion/NoClipLocomotion.h"

#include "Engine/Core/Mesh/MeshManager.h"
#include "Engine/Core/Graphics/BlendState.h"
#include "Engine/Core/Graphics/Buffers/IndexBuffer.h"
#include "Engine/Core/Graphics/Buffers/VertexBuffer.h"
#include "Engine/Core/Graphics/Buffers/DepthStencilBuffer.h"

#pragma warning(push)
#pragma warning(disable:4100)
#pragma warning(disable:4458)

#include "Engine/di.hpp"
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
			InputSystem>()

		// Specify the IResourceManager::
		//, di::bind<IResourceManager>().to<ResourceManager>()

		// Specify all Draw Commands:
		//, di::bind<IDrawCommand*[]>().to<SkyboxDrawCommand, OpaqueDrawCommand, TranslucentDrawCommand>()

		// Specify Components?
		//, di::bind<IComponent*[]>().to<Camera, Transform>()
	);
	
	auto game = injector.create<GameLoop>();
	return game.Run();
}

#pragma warning(pop)