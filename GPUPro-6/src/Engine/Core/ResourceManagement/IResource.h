#pragma once

typedef uint16_t ResourceTypeID;

class ResourceReferences;

class IResource
{
public:
	IResource(size_t resourceIndex, ResourceReferences& resourceReferences) : 
		m_resourceIndex(resourceIndex),
		m_resourceReferences(resourceReferences) { }
    
	virtual ~IResource() = default;
    virtual void Release() = 0;

	size_t GetResourceIndex();

protected:
	ResourceReferences& GetResourceReferences();

private:
	size_t m_resourceIndex;
	ResourceReferences& m_resourceReferences;
};
