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
#include "Engine/Core/Graphics/Components/Camera.h"
#include "Engine/Core/Graphics/Components/Light.h"
#include "Engine/Core/Graphics/Components/Transform.h"
#include "Engine/Core/Graphics/Components/MeshRenderer.h"

// Etc
#include "Engine/Core/Mesh/MeshManager.h"
#include "Engine/Core/Graphics/BlendState.h"
#include "Engine/Core/Graphics/RasterizerState.h"
#include "Engine/Core/Graphics/Buffers/IndexBuffer.h"
#include "Engine/Core/Graphics/Buffers/VertexBuffer.h"
#include "Engine/Core/Graphics/Buffers/DepthStencilBuffer.h"

// Resources
#include "Engine/Core/ResourceManagement/ResourceManager.h"
#include "Engine/Core/ResourceManagement/ResourceReferences.h"
#include "Engine/Core/Graphics/ResourceTypes/Mesh.h"
#include "Engine/Core/Graphics/ResourceTypes/Shader.h"
#include "Engine/Core/Graphics/ResourceTypes/ShaderResource.h"
#include "Engine/Core/Graphics/ResourceTypes/Material/SimpleMaterial.h"
#include "Engine/Core/Graphics/ResourceTypes/Material/StandardMaterial.hpp"
#include "Engine/Core/Graphics/ResourceTypes/StructuredBuffer.h"
#include "Engine/Core/Graphics/ResourceTypes/Texture2D.h"
#include "Engine/Core/Graphics/ResourceTypes/Texture2DArray.h"
#include "Engine/Core/Graphics/ResourceTypes/TextureSampler.h"


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
	std::vector<ComponentTypeID> componentTypeList;
	componentTypeList.push_back(Transform::GetComponentType());
	componentTypeList.push_back(Camera::GetComponentType());
	componentTypeList.push_back(MeshRenderer::GetComponentType());
	componentTypeList.push_back(Entity::GetComponentType());
	componentTypeList.push_back(Light::GetComponentType());
	SceneGraph* sceneGraph = new SceneGraph(componentTypeList);
	SceneGraphManager* sceneGraphManager = new SceneGraphManager(*sceneGraph);

	// Graphics Device
	WindowManager* windowManager = new WindowManager();
	GraphicsDevice* gfxDevice = new GraphicsDevice(*windowManager);

	// Resource Manager
	std::vector<ResourceTypeID> resourceTypeList;
	resourceTypeList.push_back(Mesh::GetResourceType());
	resourceTypeList.push_back(Shader::GetResourceType());
	resourceTypeList.push_back(ShaderResource::GetResourceType());
	resourceTypeList.push_back(StructuredBuffer::GetResourceType());
	resourceTypeList.push_back(Texture2D::GetResourceType());
	resourceTypeList.push_back(Texture2DArray::GetResourceType());
	resourceTypeList.push_back(TextureSampler::GetResourceType());
	resourceTypeList.push_back(StandardMaterial::GetResourceType());
	resourceTypeList.push_back(SimpleMaterial::GetResourceType());
	ResourceManager* resourceManager = new ResourceManager(resourceTypeList, *gfxDevice);

	// Buffers
	IndexBuffer* indexBuffer = new IndexBuffer(*gfxDevice);
	VertexBuffer* vertexBuffer = new VertexBuffer(*gfxDevice);
	PerObjectBuffer* perObjectBuffer = new PerObjectBuffer(*gfxDevice);
	PerCameraBuffer* perCameraBuffer = new PerCameraBuffer(*gfxDevice);
	StandardMaterialBuffer* standardMaterialBuffer = new StandardMaterialBuffer(*gfxDevice);

	// Graphics State Helpers
	BlendState* blendState = new BlendState(*gfxDevice);
	MeshManager* meshManager = new MeshManager(*indexBuffer, *vertexBuffer, *resourceManager);
	RasterizerState* rasterizerState = new RasterizerState(*gfxDevice);
	DepthStencilBuffer* depthStencilBuffer = new DepthStencilBuffer(*windowManager, *gfxDevice);

	// IDrawCommands
	std::vector<IDrawCommand*>* commands = new std::vector<IDrawCommand*>();
	SkyboxDrawCommand* skyboxDrawCommand = new SkyboxDrawCommand(*gfxDevice, *perObjectBuffer, *sceneGraphManager, *resourceManager, *rasterizerState, *blendState);
	commands->push_back(skyboxDrawCommand);
	StandardOpaqueMaterialDrawCommand* standardOpaqueMaterialDrawCommand = new StandardOpaqueMaterialDrawCommand(*gfxDevice, *perObjectBuffer, *sceneGraphManager, *resourceManager, *rasterizerState, *blendState, *standardMaterialBuffer);
	commands->push_back(standardOpaqueMaterialDrawCommand);
	StandardTransparentMaterialDrawCommand* standardTransparentMaterialDrawCommand = new StandardTransparentMaterialDrawCommand(*gfxDevice, *perObjectBuffer, *sceneGraphManager, *resourceManager, *rasterizerState, *blendState, *standardMaterialBuffer);
	commands->push_back(standardTransparentMaterialDrawCommand);

	// ISystems
	std::vector<ISystem*>* allSystems = new std::vector<ISystem*>();
	GraphicsSystem* graphicSystem = new GraphicsSystem(
		*blendState,
		*meshManager,
		*gfxDevice,
		*depthStencilBuffer,
		*sceneGraphManager,
		*perObjectBuffer,
		*perCameraBuffer,
		*commands
	);
	allSystems->push_back(graphicSystem);

	InputSystem* inputSystem = new InputSystem(*gameLoop);
	allSystems->push_back(inputSystem);

	LightingSystem* lightingSystem = new LightingSystem(*sceneGraphManager, *resourceManager);
	allSystems->push_back(lightingSystem);

	NoClipLocomotion* noClipLocomotion = new NoClipLocomotion(*sceneGraphManager, *inputSystem);
	allSystems->push_back(noClipLocomotion);

	// System Container + Game Loop Entry
	SystemContainer* systemContainer = new SystemContainer(*allSystems);
	
	int result = gameLoop->Run(*systemContainer);

	for (auto it = allSystems->begin(); it != allSystems->end(); it++)
	{
		delete *it;
	}

	for (auto it = commands->begin(); it != commands->end(); it++)
	{
		delete *it;
	}

	delete systemContainer;

	delete depthStencilBuffer;
	delete rasterizerState;
	delete meshManager;
	delete blendState;

	delete standardMaterialBuffer;
	delete perCameraBuffer;
	delete perObjectBuffer;
	delete vertexBuffer;
	delete indexBuffer;

	delete resourceManager;

	delete sceneGraphManager;
	delete sceneGraph;

	delete gameLoop;
	delete time;

	delete windowManager;
	delete gfxDevice;

	return result;
}