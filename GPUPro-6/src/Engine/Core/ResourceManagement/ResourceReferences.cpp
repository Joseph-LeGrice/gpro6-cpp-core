#include "stdafx.h"
#include "ResourceReferences.h"

GraphicsDevice& ResourceReferences::GetGraphicsDevice()
{
	return m_graphicsDevice;
}

ResourceManager& ResourceReferences::GetResourceManager()
{
	return m_resourceManager;
}
