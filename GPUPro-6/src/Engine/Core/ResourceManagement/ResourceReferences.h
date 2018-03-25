#pragma once

class GraphicsDevice;
class ResourceManager;

class ResourceReferences
{
public:
	ResourceReferences(GraphicsDevice& graphicsDevice, 
		ResourceManager& resourceManager) :
		m_graphicsDevice(graphicsDevice),
		m_resourceManager(resourceManager) { }

	GraphicsDevice& GetGraphicsDevice();
	ResourceManager& GetResourceManager();

private:
	GraphicsDevice& m_graphicsDevice;
	ResourceManager& m_resourceManager;
};