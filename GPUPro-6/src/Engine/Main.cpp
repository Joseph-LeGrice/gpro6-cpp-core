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
#include "Engine/Core/Scripting/ScriptedSystemLoader.h"
#include "Engine/Core/Scripting/ScriptedSystem.h"
#include "Engine/Extra/Locomotion/NoClipLocomotion.h"

// IDrawCommands
#include "Engine/Core/Graphics/Drawing/SkyboxDrawCommand.h"
#include "Engine/Core/Graphics/Drawing/StandardOpaqueMaterialDrawCommand.h"
#include "Engine/Core/Graphics/Drawing/StandardTransparentMaterialDrawCommand.h"

// Scene + IComponents
#include "Engine/Core/SceneGraph/SceneGraph.hpp"
#include "Engine/Core/SceneGraph/SceneGraphManager.h"
#include "Engine/Core/SceneGraph/Components/Entity.h"
#include "Engine/Core/Components/Camera.h"
#include "Engine/Core/Components/Light.h"
#include "Engine/Core/Components/Transform.h"
#include "Engine/Core/Components/MeshRenderer.h"

// Etc
#include "Engine/Core/RTTI/HelperMethods.h"
#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/Mesh/MeshManager.h"
#include "Engine/Core/Graphics/BlendState.h"
#include "Engine/Core/Graphics/RasterizerState.h"
#include "Engine/Core/Graphics/Buffers/IndexBuffer.h"
#include "Engine/Core/Graphics/Buffers/ConstantBuffer.h"
#include "Engine/Core/Graphics/Buffers/VertexBuffer.h"
#include "Engine/Core/Graphics/Buffers/DepthStencilBuffer.h"

// Resources
#include "Engine/Core/ResourceTypes/Mesh.h"
#include "Engine/Core/ResourceTypes/Shader.h"
#include "Engine/Core/ResourceTypes/ShaderResource.h"
#include "Engine/Core/ResourceTypes/Material.h"

#include "Engine/Core/ResourceTypes/StructuredBuffer.h"
#include "Engine/Core/ResourceTypes/Texture2D.h"
#include "Engine/Core/ResourceTypes/Texture2DArray.h"
#include "Engine/Core/ResourceTypes/TextureSampler.h"
#include "Core/GlobalStaticReferences.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	Time* time = new Time();
	GameLoop* gameLoop = new GameLoop(*time);
	
	// Scene Management
	SceneGraph* sceneGraph = new SceneGraph();
	SceneGraphManager* sceneGraphManager = new SceneGraphManager(*sceneGraph);

	// Graphics Device
	WindowManager* windowManager = new WindowManager();
	GraphicsDevice* gfxDevice = new GraphicsDevice(*windowManager);

	// Resource Manager
	TypedObjectManager* typedObjectManager = new TypedObjectManager();

	// Buffers
	IndexBuffer* indexBuffer = new IndexBuffer(*gfxDevice);
	VertexBuffer* vertexBuffer = new VertexBuffer(*gfxDevice);

	// Graphics State Helpers
	BlendState* blendState = new BlendState(*gfxDevice);
	MeshManager* meshManager = new MeshManager(*indexBuffer, *vertexBuffer, *typedObjectManager);
	RasterizerState* rasterizerState = new RasterizerState(*gfxDevice);
	DepthStencilBuffer* depthStencilBuffer = new DepthStencilBuffer(*windowManager, *gfxDevice);

	// ISystems
	std::vector<ISystem*>* allSystems = new std::vector<ISystem*>();
	
	ScriptedSystemLoader* monoSystemLoader = new ScriptedSystemLoader();
	allSystems->push_back(monoSystemLoader);
	
	GraphicsSystem* graphicSystem = new GraphicsSystem(
		*blendState,
		*meshManager,
		*gfxDevice,
		*depthStencilBuffer,
		*typedObjectManager,
		*rasterizerState
	);
	allSystems->push_back(graphicSystem);

	InputSystem* inputSystem = new InputSystem(*gameLoop);
	allSystems->push_back(inputSystem);

	LightingSystem* lightingSystem = new LightingSystem(*typedObjectManager);
	allSystems->push_back(lightingSystem);

	NoClipLocomotion* noClipLocomotion = new NoClipLocomotion(*typedObjectManager, *inputSystem);
	allSystems->push_back(noClipLocomotion);

	// System Container + Game Loop Entry
	SystemContainer* systemContainer = new SystemContainer(*allSystems);
	
	NativeToManagedInstanceMap* n2m = new NativeToManagedInstanceMap();

	GlobalStaticReferences* refs = new GlobalStaticReferences(
		systemContainer,
		monoSystemLoader,
		gfxDevice,
		typedObjectManager,
		n2m
	);

	RegisterAllTypes();

	int result = gameLoop->Run(*systemContainer);

	for (auto it = allSystems->begin(); it != allSystems->end(); it++)
	{
		delete *it;
	}

	for (auto it = commands->begin(); it != commands->end(); it++)
	{
		delete *it;
	}

	delete refs;
	delete systemContainer;

	delete depthStencilBuffer;
	delete rasterizerState;
	delete meshManager;
	delete blendState;

	delete vertexBuffer;
	delete indexBuffer;

	delete typedObjectManager;

	delete sceneGraphManager;
	delete sceneGraph;

	delete gameLoop;
	delete time;

	delete windowManager;
	delete gfxDevice;

	return result;
}