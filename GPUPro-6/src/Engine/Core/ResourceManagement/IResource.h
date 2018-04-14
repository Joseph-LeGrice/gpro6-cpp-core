#pragma once

typedef uint16_t ResourceTypeID;

class IResource
{
public:
	IResource(size_t resourceIndex) : 
		m_resourceIndex(resourceIndex) { }
    
	virtual ~IResource() = default;
    virtual void Release() = 0;

	size_t GetResourceIndex();

private:
	size_t m_resourceIndex;
};
