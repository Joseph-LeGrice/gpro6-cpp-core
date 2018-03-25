#include "stdafx.h"
#include "IResource.h"

size_t IResource::GetResourceIndex()
{
	return m_resourceIndex;
}

ResourceReferences& IResource::GetResourceReferences()
{
	return m_resourceReferences;
}